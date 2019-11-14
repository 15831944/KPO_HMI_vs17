// Copyright (C) 2007, 2009 SMS Siemag AG

#include <corba.h>
#include <sstream>
#include <vector>

#include "cCBS_StdLog_Task.h"
#include "cCBS_StdEventLogFrameController.h"

#include "CIntfData.h"
#include "CDataConversion.h"
#include "CSMC_EventLogFrameController.h"
#include "CSMC_RuntimeController.h"

#include "CDateTime.h"
#include "CTelcom_Task.h"
#include "CTelcom_CorbaMsgProcessor.h"

long CTelcom_CorbaMsgProcessor::OK = RProt::ctxTlgProcessor;
long CTelcom_CorbaMsgProcessor::TlgError = 1;
long CTelcom_CorbaMsgProcessor::UnknownTlgError = 2;
long CTelcom_CorbaMsgProcessor::CorbaError = 3;
long CTelcom_CorbaMsgProcessor::CorbaConnectionError = 4;
long CTelcom_CorbaMsgProcessor::TelcomError = 5;
long CTelcom_CorbaMsgProcessor::TAMError = 6;
long CTelcom_CorbaMsgProcessor::FactoryError = 7;


//##ModelId=45AB9554038D
CTelcom_CorbaMsgProcessor::CTelcom_CorbaMsgProcessor(CTelcom_Task * Telcom_task)
{
  m_pTelcom_Task = Telcom_task;
}

CTelcom_CorbaMsgProcessor::CTelcom_CorbaMsgProcessor()
{
  //cCBS_StdInitBase::getInstance()->getEntry("DataHandler","ServerName",m_ServerName);
}

CTelcom_CorbaMsgProcessor::~CTelcom_CorbaMsgProcessor()
{
}

void CTelcom_CorbaMsgProcessor::configure(const std::string& section, Configuration& c)
{
  //Here you can read ini file in section [tlgprocessor]
}

int CTelcom_CorbaMsgProcessor::processTlg(TCMessage& msg)
{
  /////////////////////////////////////////////////////////////////
  // Here after each successful message receipt. Fill Telegram object 
  // and process it to a CORBA servent
  /////////////////////////////////////////////////////////////////

  int RetValue = CTelcom_CorbaMsgProcessor::TlgError;
  
  std::stringstream Message;
  Message << "Received a message."; 
  // Following is Code works but is not exactly *good* [tm] (uses code to find code!)

  Message << "Msg Type is " << msg.getType();
  cCBS_StdLog_Task::getInstance()->log(Message.str(), 1);

  std::vector<std::string> ProxyList;
  std::vector<std::string>::iterator it;

  if ( cCBS_StdInitBase::getInstance()->getEntryList("DataHandler","ServerName",ProxyList) )
  {
    bool isTelegramHandled = false;

    for ( it = ProxyList.begin(); it != ProxyList.end() ; ++it )
    {
      std::string CorbaProxy = (*it);

      try
      {
        // to avoid setting of not used telegram data to wrong DH
        // in case DH is not to be configured to handle only certain telegrams
        // and to save some processing time
        std::vector<std::string> HandleTelegram;
        std::vector<std::string>::iterator it_ht;
        
        //set to true if current proxy should receive this telegram
        bool HandleByProxy = false;

        cCBS_StdInitBase::getInstance()->getEntryList(CorbaProxy, "HandleTelegram", HandleTelegram);

        for ( it_ht = HandleTelegram.begin(); it_ht != HandleTelegram.end() ; ++it_ht )
        {
          if ( msg.getType() == (*it_ht) )
          {
            HandleByProxy = true;
            break; // found that this corba proxy handles the telegram, break
          }
        }

        //to be compatible with old style ini files sent to all proxies for which the list is empty
        if ( HandleByProxy || HandleTelegram.empty() )
        {

          DH_Telcom::iDH_Telcom_var pCorbaServant = m_pTelcom_Task->getpDH_Interface(CorbaProxy);
      
          if (pCorbaServant)
          {
            if (m_pFactory)
            {
              // get tlg referance to store data from received msg
              Tlg *rectlg = m_pFactory->getTlg(msg.getType());
              // loader to load msg buffer. Message will be saved in local format 
              std::string lFormat("CSV");
              cCBS_StdInitBase::getInstance()->replaceWithEntry("rprot", "localFormat", lFormat);
              rectlg->setLoader(FormatMgr::instance()->getLoader(lFormat));
              // load msg buffer into telegram
              std::string fordebugger = msg.getBufString();
              rectlg->load(msg.getBufString());
      
              if ( cCBS_StdLog_Task::getInstance()->getTraceLevel() > 5 )
              {
                // Log time difference between time stamp in Telegrams and current system time
                // Of course only for those telegrams having a time stamp named CreateTime.
                //
                if   (rectlg->hasElem ("CreateTime") )
                {
                  try    // just to be sure we dont get a show-stopping exception due to unexpected tlg definition
                  {
                    long Y = (*rectlg)["CreateTime"][0].asInteger();
                    long M = (*rectlg)["CreateTime"][1].asInteger();
                    long D = (*rectlg)["CreateTime"][2].asInteger();
                    long h = (*rectlg)["CreateTime"][3].asInteger();
                    long m = (*rectlg)["CreateTime"][4].asInteger();
                    long s = (*rectlg)["CreateTime"][5].asInteger();
                    long ms = (*rectlg)["CreateTime"][6].asInteger();
                    long dst = (*rectlg)["CreateTime"][7].asInteger();
                    CDateTime tlgTime (Y,M,D,h,m,s,ms, dst);
                    CDateTime now;
                    CDeltaTime dt = CDateTime::subTimes (now, tlgTime);
                    std::stringstream logText;
                    logText << "Received Tlg <" << msg.getType() <<"> with time Stamp " <<  tlgTime << ", Difference = " << dt << "s.";
                    cCBS_StdLog_Task::getInstance()->log(logText.str(),6);

                  }
                  catch (...)
                  { 
                    // Here in case of trouble while evaluating the time stamp or calculating the time difference.
                    std::stringstream logText;
                    logText << "Received Tlg <" << msg.getType() << ">: Exception caught while evaluating time stamp.";
                    cCBS_StdLog_Task::getInstance()->log(logText.str(),1);
                  }
                }
                // else: Telegram has no time stamp, we cannot do anything here.
              }//if ( cCBS_StdLog_Task::getInstance()->getTraceLevel() > 5 )

              // write tlg elements into DH interface
              RetValue = forwardMessage(msg.getType(), *rectlg, pCorbaServant);

              //this telegram was handled now, regardless of the return value
              isTelegramHandled = true;
            }//if (m_pFactory)
            else
            {
              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_ErrorPointerHandling(sMessage, "CTelcom_CorbaMsgProcessor::processTlg(TCMessage& msg)","m_pFactory was not set");

              RetValue = CTelcom_CorbaMsgProcessor::FactoryError;
            }
          }//if (pCorbaServant)
          else
          {
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ExceptionCaught(sMessage, "HandleTelegram", "No valid reference to DH. Check ini file configuration",msg.getType().c_str());

            RetValue = CTelcom_CorbaMsgProcessor::CorbaConnectionError;
          }
        }//if ( HandleByProxy || HandleTelegram.empty() )
      }
      catch( EUnknownTlg &e )
      {
        std::string Action;
        Action = "Writing Telegram data to DH for : ";
        Action += msg.getType();

        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ExceptionCaught(sMessage, e.what(), "CTelcom_CorbaMsgProcessor::processTlg(TCMessage& msg)",Action.c_str());

        RetValue = CTelcom_CorbaMsgProcessor::UnknownTlgError;
      }
      catch (ETAMError &e)
      {
        std::string Action;
        Action = "Writing Telegram data to DH for : ";
        Action += msg.getType();

        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__, __LINE__);
        pEventLog->EL_ExceptionCaught(sMessage, e.what(), "CTelcom_CorbaMsgProcessor::processTlg(TCMessage& msg)", Action.c_str());

        RetValue = CTelcom_CorbaMsgProcessor::TAMError;
      }
      catch( ... )
      {
        std::string Action;
        Action = "Writing Telegram data to DH for : ";
        Action += msg.getType();

        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ExceptionCaught(sMessage, "Unknown exception", "CTelcom_CorbaMsgProcessor::processTlg(TCMessage& msg)",Action.c_str());

        RetValue = CTelcom_CorbaMsgProcessor::TlgError;

      }
    } // for ( it = ProxyList.begin(); it != ProxyList.end() ; ++i )

    //if none of the configured DH handled the telegram give a warning message
    if (!isTelegramHandled)
    {
      cCBS_StdEventLogFrame* pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "HandleTelegram", "No proxy handles this telegram. Check ini file configuration!",msg.getType().c_str());
      RetValue = CTelcom_CorbaMsgProcessor::UnknownTlgError;
    }
  } // if ( cCBS_StdInitBase::getInstance()->getEntryList("DataHandler","ServerName",ProxyList) )

  return RetValue; // according to documentation 0 indicated successful processing
}

int CTelcom_CorbaMsgProcessor::forwardMessage(const std::string& TlgType, Tlg& theTlg, DH_Telcom::iDH_Telcom_var pCorbaInf)
{
  CSMC_RuntimeController RuntimeController("CTelcom_CorbaMsgProcessor::forwardMessage");

  cCBS_StdLog_Task::getInstance()->log("--- Tel. Processing ---",3);
  std::stringstream   tmp;          // need an IoStream for Loading
  
  int RetValue = CTelcom_CorbaMsgProcessor::TlgError;
  std::string DataKey;

  try
  {
    CORBA::String_var DataKey_var = pCorbaInf->generateDataKey(TlgType.c_str());
    DataKey = DataKey_var;

    int elno = theTlg.countElems();
    for (int ii=0; ii<elno; ii++)
    {
      RetValue = writeToInterface(DataKey, theTlg[ii],pCorbaInf);

      if ( RetValue != CTelcom_CorbaMsgProcessor::OK )
      {
        break;
      }
    }

    try
    {
      CSMC_RuntimeController RuntimeController("CTelcom_CorbaMsgProcessor::forwardMessage - pCorbaInf->complete");

      RetValue = pCorbaInf->complete(DataKey.c_str(), TlgType.c_str()); 

      if ( RetValue != CTelcom_CorbaMsgProcessor::OK ) // only "0" indicates success
      {
        std::string ErrorMessage = "ErrorCode: " + CDataConversion::LongToString(RetValue);

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorHandlingTelegram(sMessage, TlgType.c_str(), ErrorMessage.c_str() );
      }
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_TelegramHandled(sMessage, TlgType.c_str(), "");
      }

    }
    catch(CORBA::Exception& cExc)
    {
      std::string Action;
      Action = "invoking 'complete' for ";
      Action += TlgType;

      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, cExc._name(), "CTelcom_CorbaMsgProcessor::forwardMessage(...)",Action.c_str());

      RetValue = CTelcom_CorbaMsgProcessor::CorbaError;
    }
    catch(...)
    {
      std::string Action;
      Action = "invoking 'complete' for ";
      Action += TlgType;

      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "Unknwon exception", "CTelcom_CorbaMsgProcessor::forwardMessage(...)",Action.c_str());

      RetValue = CTelcom_CorbaMsgProcessor::CorbaError;
    }
  }
  catch (ETAMError &e)
  {
    std::string Action;
    Action += TlgType;
    Action = ": The obnoxious CSV string was: ";
    Action += tmp.str();

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, e.what(), "CTelcom_CorbaMsgProcessor::forwardMessage(...)",Action.c_str());

    RetValue = CTelcom_CorbaMsgProcessor::TAMError;
  }
  catch(CORBA::Exception& cExc)
  {
    std::string Action;
    Action += TlgType + ": Generated DataKey:" + DataKey;
  
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, cExc._name(), "CTelcom_CorbaMsgProcessor::forwardMessage(...)",Action.c_str());
  
    RetValue = CTelcom_CorbaMsgProcessor::CorbaError;
  }
  catch (...)
  {

    std::string Action;
    Action += TlgType;

    Action += ": The obnoxious CSV string was: ";
    Action += tmp.str();

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "Unknown exception", "CTelcom_CorbaMsgProcessor::forwardMessage(...)",Action.c_str());

    RetValue = CTelcom_CorbaMsgProcessor::TlgError;
  }

  cCBS_StdLog_Task::getInstance()->log("--- Finished Tlg. Processing ---",2);

  return RetValue;
}

int CTelcom_CorbaMsgProcessor::writeToInterface(const std::string& DataKey, const TlgElem& te, DH_Telcom::iDH_Telcom_var pCorbaInf)
{
  int RetValue = CTelcom_CorbaMsgProcessor::OK; // indicated success

  std::string elemName = te.getName();
  
  // if within a compound, there is no name. Use Parent's name instead
  if (elemName.empty())
  {
    elemName = te.getParent()->getName();
  }

  try 
  {
    if (te.isNull())
    {
      std::stringstream Message;
      Message << " Element " << elemName << " is null. " 
              << " It will not be written to the interface. ";
      cCBS_StdLog_Task::getInstance()->log(Message.str(),2); 
      return RetValue;
    }


    switch (te.getType())
    {
      case TlgElem::tInteger:
        pCorbaInf->setLong (DataKey.c_str(), elemName.c_str(), te.asInteger());
        break;
      case TlgElem::tNumber:
        pCorbaInf->setDouble (DataKey.c_str(), elemName.c_str(), te.asNumber());
        break;
      case TlgElem::tBool:
        pCorbaInf->setBoolean (DataKey.c_str(), elemName.c_str(), te.asInteger()? true:false);
        break;
      case TlgElem::tString:
        pCorbaInf->setString (DataKey.c_str(), elemName.c_str(), te.asString().c_str());
        break;
      case TlgElem::tDateTime:
        {
          tm xtm = te.asDateTime();
          tm* ptm = &xtm;
          pCorbaInf->setDate (DataKey.c_str(), elemName.c_str(), CDateTime(mktime(ptm)).assDate());
        }
        break;
      case TlgElem::tArray:
        // Distinguish Array of Compounds from Array of primitives
        {
          int ndim     = te.countElems();               // Get Dimension
          int ncompdim = te.getElem(0).countElems();    // Get Compound Dimension

          std::stringstream logText;
          logText << " Length of  < ndim : " << ndim << "> and ncompdim : " << ncompdim ;
          cCBS_StdLog_Task::getInstance()->log(logText.str(), 6);

          if   (ndim > 0 && ncompdim > 1)
          {
            // we have an array of compounds
            // fill sequence of <compound type> 
            seqTlgRecord SeqTlgRecord;

            for (int ii=0; ii<ndim; ii++) 
            {
              std::string TlgRecordName = te.getElem(ii).getName();
              sTlgRecord TlgRecord;

              seqTlgRecordElem SeqTlgRecordElem;

              for (int jj=0; jj<ncompdim; jj++) 
              {
                int Type                      = te.getElem(ii).getElem(jj).getType();
                std::string TlgRecordElemName = te.getElem(ii).getElem(jj).getName();

                sTlgRecordElem TlgRecordElem;

                CORBA::Any anyStuff;

                switch (Type)    // depend on type of 1st element
                {
                case TlgElem::tInteger:
                  {
                    long TlgValue = te.getElem(ii).getElem(jj).asInteger();
                    anyStuff <<= TlgValue;
                  }
                  break;
                case TlgElem::tDateTime:
                  {
                    //std::string String = te.getElem(ii).getElem(jj).asString();
                    //anyStuff <<= String.c_str(); 
                    tm xtm = te.getElem(ii).getElem(jj).asDateTime();
                    tm* ptm = &xtm;
                    CDateTime theDate(mktime(ptm));
                    anyStuff <<= theDate.toDBString().c_str();
                  }
                  break;
                case TlgElem::tNumber:
                  {
                    double TlgValue = te.getElem(ii).getElem(jj).asNumber();
                    anyStuff <<= TlgValue;
                  }
                  break;
                case TlgElem::tBool:
                  {
                    long TlgValue = te.getElem(ii).getElem(jj).asInteger();
                    anyStuff <<= TlgValue;
                  }
                  break;
                case TlgElem::tString:
                  {
                    std::string String = te.getElem(ii).getElem(jj).asString();
                    anyStuff <<= String.c_str(); 
                  }
                  break;
                default:
                  cCBS_StdLog_Task::getInstance()->log("Invalid Message Definition: Array of Compounds...", 1);
                  break;
                } // end switch (te.getElem(0).getType())

                TlgRecordElem.Name  = TlgRecordElemName.c_str();
                TlgRecordElem.Type  = Type;
                TlgRecordElem.Value = anyStuff;

                CIntfData::insert(SeqTlgRecordElem,TlgRecordElem);
              } // for (int jj=0; jj<ncompdim; jj++) 

              TlgRecord.Name          = TlgRecordName.c_str();
              TlgRecord.TlgRecordElem = SeqTlgRecordElem;

              CIntfData::insert(SeqTlgRecord,TlgRecord);
            } // for (int ii=0; ii<ndim; ii++) 

            CORBA::Any anyStuff;
            anyStuff <<= SeqTlgRecord;
            pCorbaInf->setAny (DataKey.c_str(), elemName.c_str(), anyStuff);


//            cCBS_StdLog_Task::getInstance()->log("ERROR: This kind of type is not treated!",2);
            //////////////////////////////////////////////////////////////
          }
          else
          {
            // we have an array of primitives: make sequence of <primitive type>
            // and put into Corba ANY
            switch (te.getElem(0).getType())    // depend on type of 1st element
            {
            case TlgElem::tInteger:
              {
                  DEF::seqLong ls;
                  ls.length(ndim);
                  for (int ii=0; ii<ndim; ii++) 
                    ls[ii]=te.getElem(ii).asInteger();
                  CORBA::Any anyStuff;
                  anyStuff <<= ls;
                  pCorbaInf->setAny (DataKey.c_str(), elemName.c_str(), anyStuff);
              }
              break;
            case TlgElem::tDateTime:
              {
                std::vector<std::string> stdVector; 
                for (int ii=0; ii<ndim; ii++)
                  stdVector.push_back (te.getElem(ii).asString());
  //                pCorbaInf->setDate (elemName.c_str(), stdVector);
              }
              break;
            case TlgElem::tNumber:
              {
                  DEF::seqDouble ls;
                  ls.length(ndim);
                  for (int ii=0; ii<ndim; ii++) 
                    ls[ii]=te.getElem(ii).asNumber();
                  CORBA::Any anyStuff;
                  anyStuff <<= ls;
                  pCorbaInf->setAny (DataKey.c_str(), elemName.c_str(), anyStuff);
              }
              break;
            case TlgElem::tBool:
              {
                  DEF::seqBoolean  ls;
                  ls.length(ndim);
                  for (int ii=0; ii<ndim; ii++) 
                    ls[ii]=te.getElem(ii).asNumber()? true:false ;
                  CORBA::Any anyStuff;
                  anyStuff <<= ls;
                  pCorbaInf->setAny (DataKey.c_str(), elemName.c_str(), anyStuff);
              }
              break;
            case TlgElem::tString:
              {
                  DEF::seqString ls;
                  ls.length(ndim);
                  for (int ii=0; ii<ndim; ii++) 
                    ls[ii]=CORBA::string_dup (te.getElem(ii).asString().c_str());
                  CORBA::Any anyStuff;
                  anyStuff <<= ls;
                  pCorbaInf->setAny (DataKey.c_str(), elemName.c_str(), anyStuff);
              }
              break;
            default:
              cCBS_StdLog_Task::getInstance()->log("Invalid Message Definition: Array of Compounds...", 1);
              break;
            } // end switch (te.getElem(0).getType())
          }
        }
        break;
      case TlgElem::tRecord:
        // Here only if it's not within an array of records.
        {
          int nelems = te.countElems(); 
          for (int ii=0; ii<nelems; ii++)
            writeToInterface(DataKey, te.getElem(ii), pCorbaInf);
        }

        break;
      default:
        break;
    } // END   switch (te.getType())
  }
  catch(CORBA::Exception& cExc)
  {
    std::stringstream Message;
    Message << "Could not write TelegramElement " << te.getName() << "," << te.getPath();
    cCBS_StdLog_Task::getInstance()->log(Message.str(), 1);

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, cExc._name(), "CTelcom_CorbaMsgProcessor::writeToInterface(...)","");    

    RetValue = CTelcom_CorbaMsgProcessor::CorbaError;
  }
  catch (...)
  {
    std::stringstream Message;
    Message << "Could not write TelegramElement " << te.getName() << "," << te.getPath();
    cCBS_StdLog_Task::getInstance()->log(Message.str(), 1);
    
    RetValue = CTelcom_CorbaMsgProcessor::TAMError;
  }

  return RetValue;
}

void CTelcom_CorbaMsgProcessor::setFactory(TlgFactory* Factory)
{
	m_pFactory = Factory;
}

void CTelcom_CorbaMsgProcessor::setpTelcom_Task(CTelcom_Task* value)
{
	m_pTelcom_Task = value;
}

