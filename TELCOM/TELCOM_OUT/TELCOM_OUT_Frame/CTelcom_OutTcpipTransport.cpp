// Copyright (C) 2011 SMS Demag AG

#include "CTelcom_OutTcpipTransport.h"
#include "CTelcom_OutTask.h"
#include "cCBS_StdLog_Task.h"
#include "CSMC_EventLogFrameController.h"
#include "CTelcom_OutProt.h"
#include "CTelcom_OutAppCommunication.h"



CTelcom_OutTcpipTransport::CTelcom_OutTcpipTransport()
{
}

CTelcom_OutTcpipTransport::~CTelcom_OutTcpipTransport()
{
}

int CTelcom_OutTcpipTransport::doDisconnect()
{
  CTelcom_OutTask::getInstance()->setWorking(false);

  int sta;

  sta = TcpipTransport::doDisconnect();
  if (sta == -1)
  {
    cCBS_StdLog_Task::getInstance()->log("Dis-Connection timeout.", 1);
  }
  else
  {
	  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_LostConnection(sMessage,cCBS_StdInitBase::getInstance()->m_ServerName.c_str());

    cCBS_StdLog_Task::getInstance()->log("CTelcom_OutTcpipTransport::doDisconnect: Dis-Connected!", 1);
  }
  return sta;
}

int CTelcom_OutTcpipTransport::doConnect()
{
  /*******************************
  // if more than one connection (redundant CPUs)
  // check which is actual
  if ( isRedundancy
    && isConnectionControlledByIn )
  {
    checkAndSetRightConnection();
  }
  *******************************/

  checkAndSetRightConnection();

  return TcpipTransport::doConnect();
}

int CTelcom_OutTcpipTransport::doListen()
{
  /*******************************
  if ( isRedundancy
    && isConnectionControlledByIn )
  {
    std::string oldConnection = getConnectInfo();

    checkAndSetRightConnection();

    if (getConnectInfo() != oldConnection)
    {
      CTelcom_OutTask::getInstance()->getpOutAppCommunication()->getOutProt()->disconnect();
      CTelcom_OutTask::getInstance()->getpOutAppCommunication()->getOutProt()->makeConnection();
    }

  }//if ( isRedundancy ...
  *******************************/

  // checkAndSetRightConnection return true if connect info has been changed
  if ( checkAndSetRightConnection() )
  {
    CTelcom_OutTask::getInstance()->getpOutAppCommunication()->getOutProt()->disconnect();
    CTelcom_OutTask::getInstance()->getpOutAppCommunication()->getOutProt()->makeConnection();
  }

  return TcpipTransport::doListen();
}

bool CTelcom_OutTcpipTransport::checkAndSetRightConnection()
{
  bool ConnectInfoChanged = false;

  std::string Action = "Reading DH interface data from ServerTask ";

  try
  {
    cCBS_StdInitBase *pStdInitBase = cCBS_StdInitBase::getInstance();
    if ( pStdInitBase && isRedundancy && isConnectionControlledByIn )
    {
      // Example of configuration
      // [DataHandler]
      // DH_CPU = DH_L1_BOF_1_IN
      //
      // [DH_L1_BOF_1_IN]
      // DH_CPU_KEY = PLC10
      // 
      std::string DH;
      std::string Task;
      std::string Key = "WDOG";
      pStdInitBase->getEntry("DataHandler", "DH_CPU", DH);
      pStdInitBase->replaceWithEntry(DH, "DH_CPU_KEY", Key);
      pStdInitBase->getEntry(DH, "ServerTask", Task);

      DH_Telcom::iDH_Telcom_var m_pDataHandler = CTelcom_OutTask::getInstance()->getpDH_Interface(Task, "TELCOM");

      if (m_pDataHandler)
      {
        std::string ActConnection = getConnectInfo();

        long cpu1 = m_pDataHandler->getLong(Key.c_str(), "CPU1_Active");

        if (cpu1 != DEF::Inv_Long && cpu1 == 1)
        {
          if ( ActConnection != m_ConnectInfo2 )
          {
            setConnectInfo(m_ConnectInfo2);
            ConnectInfoChanged = true;
          }
        }

        long cpu0 = m_pDataHandler->getLong(Key.c_str(), "CPU0_Active");
        if (cpu0 != DEF::Inv_Long && cpu0 == 1)
        {
          if ( ActConnection != m_ConnectInfo1 )
          {
            setConnectInfo(m_ConnectInfo1);
            ConnectInfoChanged = true;
          }
        }
      }
    }//if (pStdInitBase)
  }

  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc,
      "CTelcom_OutTcpipTransport::checkAndSetRightConnection",
      Action);
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc,
      "CTelcom_OutTcpipTransport::checkAndSetRightConnection",
      Action);
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException("CTelcom_OutTcpipTransport::checkAndSetRightConnection",
      Action);
  }

  return ConnectInfoChanged;
}

void CTelcom_OutTcpipTransport::send(const TCMessage & msg)
{
  // if more than one connection (redundant CPUs)
  // check which is actual
  if ( checkAndSetRightConnection() )
  {
    CTelcom_OutTask::getInstance()->getpOutAppCommunication()->getOutProt()->disconnect();
    CTelcom_OutTask::getInstance()->getpOutAppCommunication()->getOutProt()->makeConnection();
  }
  TcpipTransport::send(msg);
}

void CTelcom_OutTcpipTransport::switchConnection()
{
  // If connection should be controlled by DH_IN
  // the connectInfo will be set corresponding to the active CPU sent by TELCOM_IN. 
  // In other case the switch of connectInfo is done independent of CPU information.
  //
  cCBS_StdLog_Task::getInstance()->log("*** CTelcom_OutTcpipTransport::switchConnection ***",4);
  if ( isRedundancy )
  {
    if ( isConnectionControlledByIn )
    {
      cCBS_StdLog_Task::getInstance()->log("Connection partner controlled by receiver.",4);
      checkAndSetRightConnection();
    }
    else
    {
      cCBS_StdLog_Task::getInstance()->log("Connection is configured to switch between the two possible partners.",4);
      CTelcom_TcpipTransport::switchConnection();
    }

    std::string Message;
    Message = "CTelcom_OutTcpipTransport: Change to " + getConnectInfo();
    cCBS_StdLog_Task::getInstance()->log(Message,3);
  }
}//void CTelcom_OutTcpipTransport::switchConnection()

void CTelcom_OutTcpipTransport::configure(const std::string& section, bas::Configuration& c)
{
  cCBS_StdLog_Task::getInstance()->log("*** CTelcom_OutTcpipTransport::configure ***",3);  

  CTelcom_TcpipTransport::configure(section,c);

  // safe temporary
  std::string t = section;

  c.setSection("SMS_Definition");

  isConnectionControlledByIn = c.getbool("isConnectionControlledByIn", false);

  // restore
  c.setSection(t);
}