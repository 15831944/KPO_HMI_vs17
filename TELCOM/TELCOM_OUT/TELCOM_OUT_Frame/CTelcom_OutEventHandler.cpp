// Copyright (C) 2007 SMS Demag AG

#include "CTelcom_Msg.h"
#include "CTelcom_QueueManager.h"
#include "CTelcom_OutTask.h"
#include "CTelcom_OutProt.h"

#include "CDataConversion.h"
#include "CEventMessageReady.h"

#include "CSMC_EventLogFrameController.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdInitBase.h"
//#include "cCBS_StdLog_Task.h"
#include "cCBS_StdEvent_Task.h"
#include "cCBS_StdMutex.h"
#include "CIntfData.h"

#include "CTelcom_OutEventHandler.h"

//##ModelId=45ABB42F033E
CTelcom_OutEventHandler::CTelcom_OutEventHandler() : m_pQueueManager(0)
{
  m_TelegramOffsetTime = 0;

  cCBS_StdInitBase::getInstance()->replaceWithEntry("TELEGRAM", "TelegramOffsetTime", m_TelegramOffsetTime);

  std::vector<std:: string> TelList;
  std::vector<std:: string>::iterator ii;
  cCBS_StdInitBase::getInstance()->getEntryList("TELEGRAM", "HandleTelegram", TelList);

  for (ii=TelList.begin(); ii!=TelList.end(); ii++)
  {
    m_TelList.insert(*ii);
  }
}

//##ModelId=45ABB4300156
CTelcom_OutEventHandler::~CTelcom_OutEventHandler()
{
}

//##ModelId=45ABB43D0013
bool CTelcom_OutEventHandler::handleEvent(const FRIESEvent& Event)
{
  bool retval = false;
  CEventMessage      theEvent(Event);
  CEventMessageReady EventMessageReady(theEvent);

  std::string TlgName;
  std::string Message = theEvent.getMessage();

  if (Message == "SWITCH_CONNECTION")
  {
    cCBS_StdLog_Task::getInstance()->log("WARNING: 'SWITCH_CONNECTION' recived! Disconnect (if connected). Switch to communication partner:", 2);

    if (m_pProtocol)
    {
      m_pProtocol->switchConnection();
    }

    retval = true;
  }
  else
  {
    // wait for TelegramOffsetTime if set
    if ( m_TelegramOffsetTime > 0 )
    {
      Sleep(m_TelegramOffsetTime);
      cCBS_StdLog_Task::getInstance()->log("sleeping for " + CDataConversion::LongToString(m_TelegramOffsetTime) + " msecs", 3);
    }

    // remove from message "TELEGRAM_" to compare with entry in the .ini file
    TlgName = Message.substr(9,Message.size());

    if (m_TelList.empty()
    ||(m_TelList.find(TlgName) != m_TelList.end()))
    {
      cCBS_StdEvent_Task::getInstance()->setStateDetails("Actual Event Message", theEvent.getContent(), 0);

      theEvent.setMessage(TlgName);
      cCBS_StdLog_Task::getInstance()->log("Message for me, was " + TlgName, 3);
      
      if ( handleEvent(theEvent) )
      {
        retval = true;

        // event log with original Message !
        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_EventHandled(sMessage, theEvent.getSender().c_str(),theEvent.getReceiver().c_str(),Message.c_str());

        EventMessageReady.dispatch(EventMessageReady.getSender(),EventMessageReady.getReceiver());

      }
    }
  }
  return retval;
}

//##ModelId=45ABB6A502F5
bool CTelcom_OutEventHandler::handleEvent(const CEventMessage& Message)
{
  cCBS_StdMutex CBS_StdMutex("CTelcom_OutEventHandler::handleEvent");

  // here we construct the required Telegram, fetch the 
  // necessary data from data provider and put it into
  // the send queue.
  ///////////////////////////////////////////////////////

  bool retval = true;

  Tlg *senttlg = 0;

  std::string msgId   = Message.getMessage();
  std::string Sender  = Message.getSender();

  try
  {
    m_pDataHandler = 0;

    if ( Sender != DEF::Inv_String && !Sender.empty() )
    {
      m_pDataHandler = CTelcom_OutTask::getInstance()->getpDH_Interface(Sender);
    }

    senttlg = m_TlgFactory.makeTlg(msgId);// make tlg to fill it with data   

    if (m_pDataHandler)
    {
      collectTelegramData(Message.getDataKey(), *senttlg); // fill telg with data
    }
    // sRawMsg object will be stored in the queue.
    // sRawMsg objects will be deleted automatically in queue
    CTelcom_Msg *MsgForQueue = new CTelcom_Msg();
    MsgForQueue->setPlantID(Message.getPlantID());
    MsgForQueue->setOrderID(Message.getOrderID());
    MsgForQueue->setSender(Message.getSender());
    MsgForQueue->setTlg(senttlg);

    //insert into the queue
    m_pQueueManager->enqueueTelcomMsg(MsgForQueue);
  }
  catch( EUnknownTlg &e )
  {
    std::string Action;
    Action = "Could not generate telegram for message ";
    Action += msgId;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, e.what(), "CTelcom_OutEventHandler::handleEvent(const CEventMessage& Message)",Action.c_str());

    retval = false;            // indicate error
  }
  catch (...)
  {
    std::string Action;
    Action = "Reading Telegram data from DH for : ";
    Action += msgId;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "Unknown exception", "CTelcom_OutEventHandler::handleEvent(const CEventMessage& Message)",Action.c_str());

    retval = false;            // indicate error
  }

  return retval;
}

//##ModelId=45ABB6A50313
bool CTelcom_OutEventHandler::collectTelegramData(const std::string& DataKey, Tlg& theTlg)
{
  bool retval = true;      // assume success

  try
  {
    cCBS_StdLog_Task::getInstance()->log("--- Tel. Collection -----",1);
    theTlg.clear();

    // reset member for each new telegram
    CORBA::Any_var NewActAny;
    m_ActAny = NewActAny;

    int elNo = theTlg.countElems();
    for (int ii=0; ii<elNo; ii++)   // get each element's value
      retval = retval && getElementValue(theTlg.getId(), DataKey, (theTlg)[ii], 0);

    cCBS_StdLog_Task::getInstance()->log("--- Finished Tel. Coll ----",1);
  }
  catch (ETAMError &e)
  {
    std::string Action;
    Action = "TAM Error converting Telegram : ";
    Action += theTlg.getId();//TlgType;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, e.what(),
                                  "CTelcom_OutEventHandler::collectTelegramData",
                                  Action.c_str());
    retval = false;
  }
  catch (...)
  {
    std::string Action;
    Action = "Converting Telegram : ";
    Action += theTlg.getId();//TlgType;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "Unknown Exception",
                                  "CTelcom_OutEventHandler::collectTelegramData",
                                  Action.c_str());
    retval = false;
  }
  return retval;
}


//##ModelId=45ABB6A5033B
bool CTelcom_OutEventHandler::getElementValue(const std::string& TlgName, const std::string& DataKey, TlgElem& te, int TlgElemIndex)
{
  bool retval=true;       // assume success.
  std::string stName = te.getName();
  const char * elemName = stName.c_str();

  // if within a compound, there is no name. Use Parent's name instead
  if   (strlen(elemName) == 0)
  {
    stName = te.getParent()->getName();
    elemName = stName.c_str();
  }

  // IMPORTANT: DO NOT TRY TO FETCH HEADER DATA FROM DH. SET WITHIN CTELCOM_RawMsg !
  if   (! strcmp (elemName, "Header"))   
    return retval;
  else if   (! strcmp (elemName, "MessageLength"))   
    return retval;
  else if   (! strcmp (elemName, "MessageId"))   
    return retval;
  else if   (! strcmp (elemName, "MessageCount"))   
    return retval;
  else if   (! strcmp (elemName, "UnitNo"))   
    return retval;
 
  std::string Action = "Telegram " + TlgName + " - field <" + elemName + "> ";

  try 
  {
    switch (te.getType())
    {
    case TlgElem::tInteger:
      {
        Action += " : get Long";
        try
        {
          long tmp = m_pDataHandler->getLong(DataKey.c_str(), elemName);

          if (tmp != DEF::Inv_Long)
          {
            // field sizes check
            int fieldlength = te.getLen();
            if(fieldlength <= 2) // short
            {
              if ( -MAXSHORT > tmp || tmp > MAXSHORT )
              {
                tmp = MINSHORT;

                std::string mes = "Value is out of range for ";
                mes += Action + " DataKey " + DataKey + " element " + elemName;

                CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),mes.c_str());
              }
            }// if(fieldlength <= 2) // short

            te.set(tmp);
          }
          else
          {
            std::string mes;
            mes = "Invalid data received for ";
            mes += Action + " DataKey " + DataKey + " element " + elemName;

            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),mes.c_str());
          }
        }
        catch (ETAMError &e)
        {
          std::stringstream Message;
          Message << "Set Integer in telegram failed: " 
                  << e.what();

          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ExceptionCaught(sMessage,
                                        Message.str().c_str(),
                                        "getElementValue",
                                        Action.c_str());
          retval = false;
        }
        catch (CORBA::SystemException& sExc)
        {
          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ExceptionCaught(sMessage, sExc._name(), "getElementValue", Action.c_str());
          retval = false;
        }
        catch (...)
        {
          std::stringstream Message;
          Message << "Exception during getting value from CORBA interface for element: " << elemName ;
          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ExceptionCaught(sMessage,
                                        Message.str().c_str(),
                                        "getElementValue",
                                        Action.c_str());
          retval = false;
        }
      }
      break;
    case TlgElem::tNumber:
      {
        Action += " : get Double";
        try
        {
          double tmp = m_pDataHandler->getDouble(DataKey.c_str(), elemName);

          if ( tmp != DEF::Inv_Double )
          {
            // field sizes check
            int fieldlength = te.getLen();
            if(fieldlength <= 4) // float
            {
              if ( -FLT_MAX > tmp || tmp > FLT_MAX )
              {
                tmp = DEF::Inv_Float;

                std::string mes = "Value is out of range for ";
                mes += Action + " DataKey " + DataKey + " element " + elemName;

                CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),mes.c_str());
              }
            }// if(fieldlength <= 4) // float

            te.set (tmp);
          }
          else
          {
            std::string mes;
            mes = "Invalid data received for ";
            mes += Action + " DataKey " + DataKey + " element " + elemName;

            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),mes.c_str());
          }
        }
        catch (ETAMError &e)
        {
          std::stringstream Message;
          Message << "Set Double in telegram failed: " 
                  << e.what();
          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ExceptionCaught(sMessage,
                                        Message.str().c_str(),
                                        "getElementValue",
                                        Action.c_str());
          retval = false;
        }
        catch (CORBA::SystemException& sExc)
        {
          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ExceptionCaught(sMessage, sExc._name(), "getElementValue", Action.c_str());
          retval = false;
        }
        catch (...)
        {
          std::stringstream Message;
          Message << "Exception during getting value from CORBA interface for element: " << elemName ;
          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ExceptionCaught(sMessage,
                                        Message.str().c_str(),
                                        "getElementValue",
                                        Action.c_str());
          retval = false;
        }
      }
      break;
    case TlgElem::tBool:
      {
        Action += " : get Voolean";
        try
        {      
          te.set(m_pDataHandler->getBoolean(DataKey.c_str(),elemName) );
        }
        catch (ETAMError &e)
        {
          std::stringstream Message;
          Message << "Set Bool in telegram failed: " 
                  << e.what();
          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ExceptionCaught(sMessage,
                                        Message.str().c_str(),
                                        "getElementValue",
                                        Action.c_str());
          retval = false;
        }
        catch (CORBA::SystemException& sExc)
        {
          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ExceptionCaught(sMessage, sExc._name(), "getElementValue", Action.c_str());
          retval = false;
        }
        catch (...)
        {
          std::stringstream Message;
          Message << "Exception during getting value from CORBA interface for element: " << elemName ;
          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ExceptionCaught(sMessage,
                                        Message.str().c_str(),
                                        "getElementValue",
                                        Action.c_str());
          retval = false;
        }
      }
      break;
    case TlgElem::tString:
      {
        Action += " : get String";

        try
        {
          CORBA::String_var CORBA_tmp = m_pDataHandler->getString(DataKey.c_str(), elemName);

          std::string tmp = std::string(CORBA_tmp);

          if ( tmp != DEF::Inv_String)
          {  
            // field sizes check
            unsigned int fieldlength = te.getLen();

            if( fieldlength < tmp.length() ) //
            {
              // is automatically cut
              // tmp = DEF::Inv_Char;

              std::string mes = "Value is out of range for ";
              mes += Action + " DataKey " + DataKey + " element " + elemName;

              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),mes.c_str());

            }// if( fieldlength < tmp.length() ) //

            te.set (tmp );
          }
          else
          {
            std::string mes;
            mes = "Invalid data received for ";
            mes += Action + " DataKey " + DataKey + " element " + elemName;

            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),mes.c_str());
          }
        }
        catch (ETAMError &e)
        {
          std::stringstream Message;
          Message << "Set string in telegram failed: " 
            << e.what();

          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ExceptionCaught(sMessage,
                                        Message.str().c_str(),
                                        "getElementValue",
                                        Action.c_str());
          retval = false;
        }
        catch (CORBA::SystemException& sExc)
        {
          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ExceptionCaught(sMessage, sExc._name(), "getElementValue", Action.c_str());
          retval = false;
        }
        catch (...)
        {
          std::stringstream Message;
          Message << "Exception during getting value from CORBA interface for element: " << elemName ;
          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ExceptionCaught(sMessage,
                                        Message.str().c_str(),
                                        "getElementValue",
                                        Action.c_str());
          retval = false;
        }
      }
      break;
    case TlgElem::tDateTime:
      {
        Action += " : get DateTime";

        //sankar
				unsigned int ndim = te.countElems(); 
				if (ndim == 0)
				{
					CDateTime Time;
	        sDate dt = m_pDataHandler->getDate(DataKey.c_str(), elemName);
					Time << dt;

					if (Time != CDateTime::InvalidDateTime() )
					{
						time_t t = Time.asTime_T(); 

						tm *dt = localtime(&t);

						te.set ((*dt));
					}
					else
					{
						std::stringstream Message;
						Message << "Invalid DateTime is not stored in DB. Element is: " << elemName ;


						CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
						sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
						pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Message.str().c_str());
					}
				}
				else
				{
					CORBA::Any_var anyStuff;
					anyStuff = m_pDataHandler->getAny(DataKey.c_str(), elemName);
					CDateTime Time(anyStuff);

					if (Time != CDateTime::InvalidDateTime() )
					{
						time_t t = Time.asTime_T(); 

						tm *dt = localtime(&t);

						te.set ((*dt));
					}
					else
					{
						std::stringstream Message;
						Message << "Invalid DateTime is not stored in DB. Element is: " << elemName ;


						CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
						sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
						pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Message.str().c_str());
					}

				}



      }// case TlgElem::tDateTime:
      break;
    case TlgElem::tArray:
      // Distinguish Array of Compounds from Array of primitives
      {
        try
        {
          unsigned int ndim = te.countElems();               // Get Dimension
          if   (ndim >1 && te.getElem(0).countElems() >1)
          {
            // we have an array of compounds
            // fill sequence of <compound type> 
            // AT THE TIME BEING, THIS DOES NOT EXIST IN THIS INTERFACE 
            ///////////////////////////////////////////////////////////
          }
          // we have an array of primitives: make sequence of <primitive type>
          // and put into Corba ANY

          switch (te.getElem(0).getType())    // depend on type of 1st element
          {
          case TlgElem::tInteger:
            {
              Action += " - get integer array";

              DEF::seqLong *pls = 0;
              CORBA::Any_var anyStuff;
              anyStuff = m_pDataHandler->getAny(DataKey.c_str(), elemName);
              anyStuff >>= pls;
              if (pls)
              {
                DEF::seqLong ls (*pls);
                if (ls.length() >= ndim)
                { 
                  for (unsigned int ii=0; ii<ndim; ii++) 
                  {
                    long tmp = ls[ii];

                    if ( tmp != DEF::Inv_Long )
                    {
                      // field sizes check
                      int fieldlength = te.getElem(0).getLen();
                      if(fieldlength <= 2) // short
                      {
                        if ( -MAXSHORT > tmp || tmp > MAXSHORT )
                        {
                          tmp = MINSHORT;

                          std::string mes = "Value is out of range for ";
                          mes += Action + " DataKey " + DataKey + " element " + elemName;

                          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                          pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),mes.c_str());
                        }
                      }// if(fieldlength <= 2) // short

                      te.getElem(ii).set  (tmp);
                    }
                    else
                    {
                      std::string mes;
                      mes = "Invalid data received for ";
                      mes += Action + " DataKey " + DataKey + " element " + elemName;

                      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),mes.c_str());
                    }
                  }// for (unsigned int ii=0; ii<ndim; ii++) 
                }// if   (ls.length() >= ndim)
                else
                {
                  std::stringstream Message;
                  Message << "Too short sequence received for: " << elemName ;

                  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                  pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Message.str().c_str());
                }
              }
              else
              {
                std::string mes;
                mes = "Invalid data received for ";
                mes += Action + " DataKey " + DataKey + " element " + elemName;

                CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),mes.c_str());
              }
            }
            break;
          case TlgElem::tNumber:
            {
              Action += " - get number array";

              DEF::seqDouble *pds = 0;
              CORBA::Any_var anyStuff;
              anyStuff = m_pDataHandler->getAny(DataKey.c_str(), elemName);
              anyStuff >>= pds;

              if (pds)
              {
                DEF::seqDouble ds (*pds);

                if ( ds.length() >= ndim )
                {
                  for (unsigned int ii=0; ii<ndim; ii++)
                  {
                    double tmp = ds[ii];

                    if ( tmp != DEF::Inv_Double )
                    {
                      // field sizes check
                      int fieldlength = te.getElem(0).getLen();
                      if(fieldlength <= 4) // float
                      {
                        if ( -FLT_MAX > tmp || tmp > FLT_MAX )
                        {
                          tmp = DEF::Inv_Float;

                          std::string mes = "Value is out of range for ";
                          mes += Action + " DataKey " + DataKey + " element " + elemName;

                          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                          pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),mes.c_str());
                        }
                      }// if(fieldlength <= 4) // float

                      te.getElem(ii).set (tmp);
                    }
                    else
                    {
                      std::string mes;
                      mes = "Invalid data received for ";
                      mes += Action + " DataKey " + DataKey + " element " + elemName;

                      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),mes.c_str());
                    }
                  } //for (unsigned int ii=0; ii<ndim; ii++)
                }// if ( ds.length() >= ndim ) 
                else
                {
                  std::stringstream Message;
                  Message << "Too short sequence received for: " << elemName ;

                  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                  pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Message.str().c_str());
                }
              }
              else
              {
                std::string mes;
                mes = "Invalid data received for ";
                mes += Action + " DataKey " + DataKey + " element " + elemName;

                CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),mes.c_str());
              }
            }
            break;
          case TlgElem::tBool:
            {
              Action += " - get boolean array";

              DEF::seqBoolean  *pds = 0;
              CORBA::Any_var anyStuff;
              anyStuff = m_pDataHandler->getAny(DataKey.c_str(), elemName);
              anyStuff >>= pds;
              if (pds)
              {
                DEF::seqBoolean  ds (*pds);
                if   (ds.length() >= ndim)
                {
                  for (unsigned int ii=0; ii<ndim; ii++) 
                    te.getElem(ii).set (ds[ii]);
                }
                else
                {
                  std::stringstream Message;
                  Message << "Too short sequence received for: " << elemName ;

                  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                  pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Message.str().c_str());
                }
              }
              else
              {
                std::string mes;
                mes = "Invalid data received for ";
                mes += Action + " DataKey " + DataKey + " element " + elemName;

                CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),mes.c_str());
              }
            }
            break;
          case TlgElem::tDateTime:
            {
//                DEF::seqBoolean  *pds;
//                CORBA::Any anyStuff;
//                anyStuff <<= m_pDataHandler->getAny (DataKey.c_str(), elemName);
//                anyStuff >>= pds;
//                DEF::seqBoolean  ds (*pds);
//                if   (ds.length() >= ndim)
//                {
//                  for (unsigned int ii=0; ii<ndim; ii++) 
//                    te.set (ds[ii]);
//                }
//                else
//                {
//                  xxxx(<<"Too short sequence received for " << elemName << ENDL);
//                }
              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),"DateTime arrays not yet coded");
            }
            break;
          case TlgElem::tString:
            {
              Action += " - get string array";

              DEF::seqString *pds = 0;
              CORBA::Any_var anyStuff;
              anyStuff = m_pDataHandler->getAny(DataKey.c_str(), elemName);
              anyStuff >>= pds;
              if (pds)
              {
                DEF::seqString ds (*pds);

                if ( ds.length() >= ndim )
                {
                  for (unsigned int ii=0; ii<ndim; ii++)
                  {
                    CORBA::String_var CORBA_tmp = ds[ii];

                    std::string tmp = std::string(CORBA_tmp);

                    if ( tmp != DEF::Inv_String)
                    {  
                      // field sizes check
                      unsigned int fieldlength = te.getElem(0).getLen();

                      if( fieldlength < tmp.length() ) //
                      {
                        // is automatically cut
                        // tmp = DEF::Inv_Char;

                        std::string mes = "Value is out of range for ";
                        mes += Action + " DataKey " + DataKey + " element " + elemName;

                        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                        pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),mes.c_str());

                      }// if( fieldlength < tmp.length() ) //

                      te.getElem(ii).set (tmp);
                    }
                    else
                    {
                      std::string mes;
                      mes = "Invalid data received for ";
                      mes += Action + " DataKey " + DataKey + " element " + elemName;

                      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),mes.c_str());
                    }
                  }// for (unsigned int ii=0; ii<ndim; ii++) 
                }// if ( ds.length() >= ndim )
                else
                {
                  std::stringstream Message;
                  Message << "Too short sequence received for: " << elemName ;

                  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                  pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Message.str().c_str());
                }
              }
              else
              {
                std::string mes;
                mes = "Invalid data received for ";
                mes += Action + " DataKey " + DataKey + " element " + elemName;

                CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),mes.c_str());
              }
            }
            break;
          case TlgElem::tRecord:
            {
              CORBA::Any_var anyStuff;
              anyStuff = m_pDataHandler->getAny(DataKey.c_str(), elemName);

              m_ActAny = anyStuff;
  
              // Here only if it's not within an array of records.
              int nelems = te.countElems(); 
              for (int ii=0; ii<nelems; ii++)
              {
                getElementValue(TlgName, DataKey, te.getElem(ii), ii);
              }
            }
            break;
          default:
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),"Invalid Message Definition: Array of Compounds...");
            break;
          }
        }
        catch (ETAMError &e)
        {
          std::string Message;
          Message = "Set array element in telegram failed: ";
          Message += e.what();

          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ExceptionCaught(sMessage,
                                        Message.c_str(),
                                        "getElementValue",
                                        Action.c_str());
          retval = false;
        }
        catch (CORBA::SystemException& sExc)
        {
          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ExceptionCaught(sMessage, sExc._name(), "getElementValue", Action.c_str());
          retval = false;
        }
      }// case TlgElem::Array
      break;
    case TlgElem::tRecord:
      {

        //CORBA::Object_var dynObj                  = CBS::getORB()->resolve_initial_references("DynAnyFactory");//ffra :11/10/2018:changed as per hadeed
		CORBA::Object_var dynObj = cCBS_ORB::getORB()->resolve_initial_references("DynAnyFactory");//ffra ::11/10/2018: changed as per hadeed
        DynamicAny::DynAnyFactory_var DynAnyFact  = DynamicAny::DynAnyFactory::_narrow(dynObj);

        if ( !CIntfData::isValidAny(m_ActAny) )
        {
          CORBA::Any_var anyStuff;
          anyStuff = m_pDataHandler->getAny(DataKey.c_str(), elemName);

          m_ActAny = anyStuff;
        }

        if ( CIntfData::isValidAny(m_ActAny) )
        {
          DynamicAny::DynAny_var da = DynAnyFact->create_dyn_any (m_ActAny);

          CORBA::TypeCode_var tc(da->type());
          while (tc->kind() == CORBA::tk_alias)
          {
            tc = tc->content_type();
          }
          
          if ( tc->kind() == CORBA::tk_sequence )
          {
            DynamicAny::DynSequence_var ds = DynamicAny::DynSequence::_narrow(da);

            if ( ds->seek(TlgElemIndex) )
            {
              DynamicAny::DynAny_var cm(ds->current_component());

              int nelems = te.countElems(); 
              for (int ii=0; ii<nelems; ii++)
              {
               // getElementValue(TlgName, DataKey, te.getElem(ii), TlgElemIndex);           
                CTelcom_OutEventHandler::getDynContent(cm, te.getElem(ii), ii);
              }
            }
          }
          else
          {
            // Here only if it's not within an array of records.
            int nelems = te.countElems(); 
            for (int ii=0; ii<nelems; ii++)
            {
             // getElementValue(TlgName, DataKey, te.getElem(ii), TlgElemIndex);           
              getElementValue(m_ActAny, te.getElem(ii), TlgElemIndex, DynAnyFact);
            }
          }
        }
      } // end of case TlgElem::tRecord
      break;
    default:
      break;
    }
  } // Try
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,
                                  "Unknown",
                                  "CTELCOM_SendEventReceiver::getElementValue",
                                  Action.c_str());
    retval = false;
  }
  return retval;
}

//##ModelId=45AF9E3103DB
void CTelcom_OutEventHandler::setQueueManager(CTelcom_QueueManager* value)
{
	m_pQueueManager = value;
}

//##ModelId=45B4E56F01DF
void CTelcom_OutEventHandler::setProtocol(CTelcom_OutProt* value)
{
	m_pProtocol = value;
}
