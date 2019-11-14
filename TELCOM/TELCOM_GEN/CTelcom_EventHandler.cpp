// Copyright (C) 2007 SMS Demag AG

#include "CTelcom_EventHandler.h"
#include <corba.h>
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdEventLogFrame.h"
#include "CTelcom_Msg.h"


//##ModelId=45ABB42F033E
CTelcom_EventHandler::CTelcom_EventHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}

//##ModelId=45ABB4300156
CTelcom_EventHandler::~CTelcom_EventHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}

//##ModelId=45ABB43D0013
bool CTelcom_EventHandler::handleEvent(const FRIESEvent& Event)
{
  bool retval = false;
  CEventMessage theEvent(Event);
  std::string TlgName;

  if (theEvent.getMessage() == "SWITCH_CONNECTION")
  {
    std::stringstream Message;
    Message << "WARNING: 'SWITCH_CONNECTION' recived! Disconnect (if connected). Switch to communication partner:";
    cCBS_StdLog_Task::getInstance()->log(Message.str());

    if (m_pSProt->connected())
      m_pSProt->disconnect();

//JOGE    static_cast<CTELCOM_TcpipTransport*>(m_pSProt->getTransport())->switchConnection();
    retval = true;
  }
  else
  {
    // remove from message "TELEGRAM_" to compare with entry in the .ini file
    TlgName = theEvent.getMessage().substr(9,theEvent.getMessage().size());

    if (m_TelList.empty()
    ||(m_TelList.find(TlgName) != m_TelList.end()))
    {
      theEvent.setMessage(TlgName);
      std::stringstream Message;
      Message << "Message for me, was " << theEvent.getMessage();
      cCBS_StdLog_Task::getInstance()->log(Message.str());
      retval = handleEvent(theEvent);
    }
  }
  return retval;
}

//##ModelId=45ABB6A502F5
bool CTelcom_EventHandler::handleEvent(const CEventMessage& Message)
{
  //cCBS_StdLog_Task::getInstance()->log("handleEvent wants mutex TELCOM_BASE");
  //CSMC_Mutex Mutex("TELCOM_BASE");
  //cCBS_StdLog_Task::getInstance()->log("handleEvent HAS mutex TELCOM_BASE");

  // here we construct the required Telegram, fetch the 
  // necessary data from data provider and put it into
  // the send queue.
  ///////////////////////////////////////////////////////

  bool retval = true;

  Tlg *senttlg = 0;
  std::string msgId;
  msgId = Message.getMessage();
  
  try
  {
    m_pDataHandler = *(CTelcom_InTask::getInstance()->getpDH_Interface(Message.getSender()));
    if (m_pDataHandler)
    {
      senttlg = (m_pSProt->getTlgFactory())->makeTlg( msgId );// make tlg to fill it with data
      collectTelegramData (msgId, Message.getDataKey(), *senttlg); // fill telg with data
      // CRH_sRawMsg object will be stored in the queue.
      // CRH_sRawMsg objects will be deleted automatically in queue
      CTelcom_Msg *MsgForQueue = new CTelcom_Msg();
      //MsgForQueue->setPlantID(Message.getPlantID());
      //MsgForQueue->setProductID(Message.getOrderID());
      //MsgForQueue->setSender(Message.getSender());
      //MsgForQueue->set(*senttlg, msgId, m_pSProt->getLocalFormat(), m_pSProt->getRemoteFormat());

      ////insert into the queue
      //m_QueueWrapper->enque(MsgForQueue);

      if( senttlg )
        delete senttlg;

      // for report in getOwnStateDetails
      //CRH_sInterfaceTask::getInstance()->setLastEvt(msgId);
    }
    else
    {
      std::string Mess;
      Mess = "TELCOM_L1_RH_OUT: ERROR: Could not bound to " + Message.getSender();
      cCBS_StdLog_Task::getInstance()->log(Mess,1);
    }
  }
  catch( EUnknownTlg &e )
  {
    std::stringstream Message;
    Message << "TELCOM_L1_RH_OUT:Error in CRH_sEventReceiver::handleEvent for makeTlg:" << msgId << ":" << e.what();
    cCBS_StdLog_Task::getInstance()->log(Message.str());
    retval = false;            // indicate error
  }
  catch (...)
  {
    cCBS_StdLog_Task::getInstance()->log("TELCOM_L1_RH_OUT:Unknown Error in CRH_sEventReceiver::handleEvent ");
    retval = false;            // indicate error
  }

  return retval;
}

//##ModelId=45ABB6A50313
bool CTelcom_EventHandler::collectTelegramData(std::string TlgType, const std::string& key, Tlg& theTlg)
{
  bool retval = true;      // assume success
  try
  {
    cCBS_StdLog_Task::getInstance()->log("--- Tel. Collection -----",1);
    theTlg.clear();

    int elNo = theTlg.countElems();
    for (int ii=0; ii<elNo; ii++)   // get each element's value
      retval = retval && getSendValues (key, (theTlg)[ii]);

    cCBS_StdLog_Task::getInstance()->log("--- Finished Tel. Coll ----",1);
  }
  catch (ETAMError &e)
  {
    std::string Action;
    Action = "TAM Error converting Telegram : ";
    Action += TlgType;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,
                                  e.what(),
                                  "CTelcom_EventHandler::collectTelegramData",
                                  Action.c_str());
    retval = false;
  }
  catch (...)
  {
    std::string Action;
    Action = "Converting Telegram : ";
    Action += TlgType;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,
                                  "Unknown Exception",
                                  "CTelcom_EventHandler::collectTelegramData",
                                  Action.c_str());
    retval = false;
}

//##ModelId=45ABB6A5033B
bool CTelcom_EventHandler::getSendValues(const std::string& Name, TlgElem& te)
{
  bool retval=true;       // assume success.
  std::string stName = te.getName();
  const char * elemName = stName.c_str();

  // if within a compound, there is no name. Use Parent's name instead
  if   (strlen(elemName) == 0)
    elemName = te.getParent()->getName().c_str();

  // IMPORTANT: DO NOT TRY TO FETCH HEADER DATA FROM DH. SET WITHIN CTELCOM_RawMsg !
  if   (! strcmp (elemName, "Header"))   
    return retval;
 
  try 
  {
    switch (te.getType())
    {
      case TlgElem::tInteger:
        try
        {
          long tmp = m_pDataHandler->getLong (Name.c_str(), elemName);
          if (tmp != DEF::Inv_Long)
            te.set(tmp);
          else
          {
            std::string mes;
            mes = "Invalid data receifed for ";
            mes += Name + " element " + te.getName();
            log(mes,2);
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
                                        "getSendValues Integer",
                                        "");
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
                                        "getSendValues for Integer",
                                        "");
          retval = false;
        }
      break;
      case TlgElem::tNumber:
        try
        {
          te.set (m_pDataHandler->getDouble (Name.c_str(), elemName) );
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
                                        "getSendValues Number",
                                        "");
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
                                        "getSendValues for Number",
                                        "");
          retval = false;
        }
      break;
      case TlgElem::tBool:
        try
        {
          te.set(m_pDataHandler->getBoolean (Name.c_str(),elemName) );
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
                                        "getSendValues Bool",
                                        "");
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
                                        "getSendValues for Bool",
                                        "");
          retval = false;
        }
      break;
      case TlgElem::tString:
      {
        std::string tmp;
        try
        {
          tmp = m_pDataHandler->getString (Name.c_str(), elemName);
          if (tmp != DEF::Inv_String)
            te.set (tmp );
          else
          {
            std::string mes;
            mes = "Invalid data receifed for ";
            mes += Name + " element " + te.getName();
            log(mes,2);
          }
        }
        catch (ETAMError &e)
        {
          std::stringstream Message;
          Message << "Set string in telegram failed: " 
                  << e.what()
                  << " Value is: "
                  <<  tmp;
          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ExceptionCaught(sMessage,
                                        Message.str().c_str(),
                                        "getSendValues String",
                                        "");
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
                                        "getSendValues for String",
                                        "");
          retval = false;
        }
      }
      break;
      case TlgElem::tDateTime:
      {
        // HERE SOMETHING IS STILL MISSING. LOOKS LIKE
        // sDate dateStruct = ;  // and fill this structure somehow, then
        //m_pDataHandler->setDate (Name.c_str(), elemName, dateStruct);
        std::stringstream Message;
        Message << "Element as DateTime is not supported. Element is: " << elemName ;
        cCBS_StdLog_Task::getInstance()->log(Message.str());
        retval=false;
      }
      break;
      case TlgElem::tArray:
      // Distinguish Array of Compounds from Array of primitives
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
              DEF::seqLong *pls;
              CORBA::Any_var anyStuff;
              anyStuff = m_pDataHandler->getAny (Name.c_str(), elemName);
              anyStuff >>= pls;
              if (pls)
              {
                DEF::seqLong ls (*pls);
                if   (ls.length() >= ndim)
                { 
                  for (unsigned int ii=0; ii<ndim; ii++) 
                  {
                    long ll = ls[ii];
                    te.getElem(ii).set  (ls[ii]);
                  }
                }
                else
                {
                  std::stringstream Message;
                  Message << "Too short sequence retrieved for: " << elemName ;
                  cCBS_StdLog_Task::getInstance()->log(Message.str());
                }
              }
              else
              {
                std::string mes;
                mes = "Invalid data receifed for ";
                mes += Name + " element ";
                mes += elemName;
                log(mes,2);
              }
            }
            break;
            case TlgElem::tNumber:
            {
              DEF::seqDouble *pds;
              CORBA::Any_var anyStuff;
              anyStuff = m_pDataHandler->getAny(Name.c_str(), elemName);
              anyStuff >>= pds;
              if (pds)
              {
                DEF::seqDouble ds (*pds);
                if   (ds.length() >= ndim)
                {
                  for (unsigned int ii=0; ii<ndim; ii++) 
                    te.getElem(ii).set (ds[ii]);
                }
                else
                {
                  std::stringstream Message;
                  Message << "Too short sequence retrieved for: " << elemName ;
                  cCBS_StdLog_Task::getInstance()->log(Message.str());
                }
              }
              else
              {
                std::string mes;
                mes = "Invalid data receifed for ";
                mes += Name + " element ";
                mes += elemName;
                log(mes,2);
              }
            }
            break;
            case TlgElem::tBool:
            {
              DEF::seqBoolean  *pds;
              CORBA::Any_var anyStuff;
              anyStuff = m_pDataHandler->getAny (Name.c_str(), elemName);
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
                  Message << "Too short sequence retrieved for: " << elemName ;
                  cCBS_StdLog_Task::getInstance()->log(Message.str());
                }
              }
              else
              {
                std::string mes;
                mes = "Invalid data receifed for ";
                mes += Name + " element ";
                mes += elemName;
                log(mes,2);
              }
            }
            break;
            case TlgElem::tDateTime:
            {
//                DEF::seqBoolean  *pds;
//                CORBA::Any anyStuff;
//                anyStuff <<= m_pDataHandler->getAny (Name.c_str(), elemName);
//                anyStuff >>= pds;
//                DEF::seqBoolean  ds (*pds);
//                if   (ds.length() >= ndim)
//                {
//                  for (unsigned int ii=0; ii<ndim; ii++) 
//                    te.set (ds[ii]);
//                }
//                else
//                {
//                  xxxx(<<"Too short sequence retrieved for " << elemName << ENDL);
//                }
              cCBS_StdLog_Task::getInstance()->log("DateTime arrays not yet coded");
           }
            case TlgElem::tString:
            {
              DEF::seqString *pds;
              CORBA::Any_var anyStuff;
              anyStuff = m_pDataHandler->getAny (Name.c_str(), elemName);
              anyStuff >>= pds;
              if (pds)
              {
                DEF::seqString ds (*pds);
                if   (ds.length() >= ndim)
                {
                  for (unsigned int ii=0; ii<ndim; ii++) 
                    te.getElem(ii).set (ds[ii]);
                }
                else
                {
                  std::stringstream Message;
                  Message << "Too short sequence retrieved for: " << elemName ;
                  cCBS_StdLog_Task::getInstance()->log(Message.str());
                }
              }
              else
              {
                std::string mes;
                mes = "Invalid data receifed for ";
                mes += Name + " element ";
                mes += elemName;
                log(mes,2);
              }
            }
            break;
            default:
              cCBS_StdLog_Task::getInstance()->log("Invalid Message Definition: Array of Compounds...");
            break;
          }
      }// case TlgElem::Array
      break;
      case TlgElem::tRecord:
      {
        // Here only if it's not within an array of records.
        int nelems = te.countElems(); 
        for (int ii=0; ii<nelems; ii++)
          getSendValues (Name, te.getElem(ii));

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
                                  "Unknown exception",
                                  "CTelcom_EventHandler::getSendValues",
                                  "");
  }
  return retval;
}

