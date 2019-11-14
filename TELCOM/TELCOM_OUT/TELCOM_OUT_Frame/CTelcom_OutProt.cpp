// Copyright (C) 2007 SMS Siemag AG

#include "CTelcom_OutProt.h"
#include "CTelcom_OutTcpipTransport.h"
#include "telcom.h"
#include "CDateTime.h"
#include "CDataConversion.h"
#include "cCBS_StdLog_Task.h"
#include "CSMC_EventLogFrameController.h"
#include "CTelcom_QueueMonitoringTask.h"
#include "CTelcom_OutTask.h"

CTelcom_OutProt::CTelcom_OutProt() : m_WDCounter(0)
{
}

CTelcom_OutProt::~CTelcom_OutProt()
{
}

void CTelcom_OutProt::doMakeWatchdog(TCMessage& wdog)
{
  cCBS_StdLog_Task::getInstance()->log("Making a watchdog message...",3);

  try
  {
    CTelcom_OutTcpipTransport * Transport = static_cast<CTelcom_OutTcpipTransport*>(getTransport());

    //if ( Transport->isRedundancy
    //  && Transport->isConnectionControlledByIn )
    //{
    //  std::string oldConnection = Transport->getConnectInfo();
    //  Transport->checkAndSetRightConnection();

    //  if (Transport->getConnectInfo() != oldConnection)
    //  {
    //    disconnect();
    //    makeConnection();
    //  }
    //}

    wdog.clear();
    
    // MessageCounter in the header is 2 bytes long, running counter may not be greater than 65534
    if (m_WDCounter > 65534)
      m_WDCounter = 0;

    m_WDCounter++;

    std::string sWdog = ((StdTlgExpert*)getTlgExpert())->getWdogType(); 
    Tlg& tlg = *getTlgFactory()->getTlg( sWdog.c_str() );

    long msglen = tlg.getLen();
    tlg["Header"]["MessageLength"].set(msglen);
    long MsgID = translateType(tlg.getId());
    tlg["Header"]["MessageId"].set(MsgID);
    tlg["Header"]["MessageCount"].set(m_WDCounter);
    if (tlg["Header"].hasElem("UnitNo"))
      tlg["Header"]["UnitNo"].set(0L);
    else if (tlg["Header"].hasElem("Flags"))
      tlg["Header"]["Flags"].set(0L);

    CDateTime now;
    if (tlg.hasElem("CreateTime"))
    {
      tlg["CreateTime"][0] = now.getYear();
      tlg["CreateTime"][1] = now.getMonth();
      tlg["CreateTime"][2] = now.getDay();
      tlg["CreateTime"][3] = now.getHour();
      tlg["CreateTime"][4] = now.getMinute();
      tlg["CreateTime"][5] = now.getSecond();
      tlg["CreateTime"][6] = now.getMilliSecond();
      tlg["CreateTime"][7] = now.get_DST();
    }
    else
    {
      cCBS_StdLog_Task::getInstance()->log("OutProt::doMakeWatchdog: Element 'CreateTime' not found!", 2);
    }

    // prepare to serialize into Caller's TCMessage
    tlg.setSerializer(FormatMgr::instance()->getSerializer(remoteFormat));
    wdog.setBufFormat(remoteFormat);
    tlg.serialize(wdog.bufOstr());        // Copy the local message to TCMessage
    wdog.setType(tlg.getId());
    wdog.reset();                         // Prepare TCMessage for Reading


  }
  catch(EUnknownTlg &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, e.what(), "CTelcom_OutProt::doMakeWatchdog", "");
  }
  catch(EElemNotFound &e)
  {
    std::stringstream Message;
    Message << "CTelcom_OutProt::doMakeWatchdog: " << e.what() << e.getPath();
    cCBS_StdLog_Task::getInstance()->log(Message.str(), 1);
  }
  catch (ETAMError &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, e.what(), "CTelcom_OutProt::doMakeWatchdog", "");
  }
  catch (...)
  {
    cCBS_StdLog_Task::getInstance()->log("OutProt::OOPS... making of a Watchdog failed.", 1);
  }
}

long CTelcom_OutProt::translateType(std::string& _t)
{
  return m_MsgTypeTranlator.translate(_t);
}

void CTelcom_OutProt::onConnectHook()
{
  CTelcom_OutTask::getInstance()->setWorking(true);
  CTelcom_QueueMonitoringTask::getInstance()->resetLostMessagesConnect();
  CTelcom_QueueMonitoringTask::getInstance()->setReciver(getTransport()->getConnectInfo());
}

void CTelcom_OutProt::switchConnection()
{
  if (connected())
    disconnect();

  static_cast<CTelcom_OutTcpipTransport*>(getTransport())->switchConnection();
}

void CTelcom_OutProt::doOnConnectError(ETransport & ex, bool isTimeout)
{
  std::string Message;
  Message = "CTelcom_OutProt::doOnConnectError: ";
  Message += ex.what();

  if (isTimeout)
  {
    if (connected())
    {
      disconnect();
      Message += " communication disconnected because of timeout";
    }
  }

  Message += " at " + CDateTime().asString();

  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ConnectionError(sMessage, cCBS_StdInitBase::getInstance()->m_ServerName.c_str(), Message.c_str());

  CTelcom_OutTask::getInstance()->setWorking(false);
  CTelcom_OutTask::getInstance()->setStateDetails("doOnConnectError",Message.c_str(),1);
}


std::string CTelcom_OutProt::getStatisticsAsString()
{
  std::string RetValue;

  RetValue += "Number of processed telegrams: " + CDataConversion::LongToString(statistics.numProcessed) + "\n";
  RetValue += "Time of last telegram: " + CDateTime(statistics.dtLastTlg).toDBString() + "\n";
  RetValue += "Number of telegram errors: " + CDataConversion::LongToString(statistics.numTlgErrors) + "\n";
  RetValue += "Number of communication errors: " + CDataConversion::LongToString(statistics.numTransportErrors) + "\n";
  RetValue += "Time of last program start: " +  CDateTime(statistics.dtLastStartup).toDBString() + "\n";

  return RetValue;
}

int CTelcom_OutProt::doHandleTlgError(TC_Exception & e, TCMessage & msg)
{
  static int numErrors = 0;

  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ExceptionCaught(sMessage, e.what(), "CTelcom_OutProt::doHandleTlgError", msg.getBufString().c_str() );
  
  // default action: log error in base class
  (void)SProt::doHandleTlgError(e,msg);
 
  // do not confirm telegram (not used here).
  return tlgAbort;
}
