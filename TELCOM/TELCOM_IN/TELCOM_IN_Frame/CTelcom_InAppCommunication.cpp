// Copyright (C) 2007 SMS Demag AG
#pragma warning (disable: 4183 4290)

#include "CTelcom_InDbWriterTransport.h"

#include "CTelcom_InProt.h"
#include "CTelcom_InOracleTransport.h"

#include "CTelcom_CorbaMsgProcessor.h"
#include "CTelcom_FileTransport.h"
#include "CTelcom_InTcpipTransport.h"
#include "CTelcom_TlgExpert.h"
#include "CTelcom_InTask.h"
#include "CTelcom_InMsgTypeTranslator.h"
#include "Telcom_In_factory.h"

#include "cCBS_StdLog_Task.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"

#include "CTelcom_InAppCommunication.h"


//##ModelId=45ACAE8E01EF
CTelcom_InAppCommunication::CTelcom_InAppCommunication() 
: m_pAppAdatper(0)
{
  m_IsOraFlag = false;
}

//##ModelId=45ACAE8F0242
CTelcom_InAppCommunication::~CTelcom_InAppCommunication()
{
}

//##ModelId=45ACC9B301DE
void CTelcom_InAppCommunication::initComm()
{
  std::string HeaderName = "Head";                      // Name of the Header-Telegramms

  std::string appname = cCBS_StdInitBase::getInstance()->m_ServerName;

  try
  {
    m_pInProt = new CTelcom_InProt();

    // factory to create the telegrams
    m_pInProt->setTlgFactory(new Telcom_In_factory());
    m_pInProt->setHeaderTlgType(HeaderName);// used name of header telegram in excel

    // own factory for processor to create tlgs.
    // task to reach DHs.
    Telcom_In_factory * ptemp = new Telcom_In_factory();
    CTelcom_CorbaMsgProcessor * MsgPr = new CTelcom_CorbaMsgProcessor();
    MsgPr->setpTelcom_Task(CTelcom_InTask::getInstance());
    MsgPr->setFactory(ptemp);
    m_pInProt->setTlgProcessor(MsgPr);

    std::string strTransportProtocol = "";

    cCBS_StdInitBase::getInstance()->replaceWithEntry("SMS_Transport","transportProtocol",strTransportProtocol);
    
    if ( strTransportProtocol == std::string ("FileTransport") )
    {
      // Application object must be created first before 
      // create FormatMgr initialization in base class
      m_pAppAdatper = new AdapterApp("tspreceiver",telcom_version_str());

      // init FormatMgr and preparation of command line args
      CTelcom_Communication::initComm(); 

      CTelcom_FileTransport * pftr = new CTelcom_FileTransport();
      pftr->setFactory(new Telcom_In_factory());
      m_pInProt->setTransport(pftr);
    }
    else if ( strTransportProtocol == std::string ("OraAdapterApp") )
    {
      m_IsOraFlag = true;

      // Application object must be created first before 
      // create FormatMgr initialization in base class
      m_pOraAppAdatper = new CTelcom_OraAdapterApp(appname.c_str(), telcom_version_str());

      // init FormatMgr and preparation of command line args
      CTelcom_Communication::initComm();
      
      CTelcom_InDbWriterTransport* pftr = new CTelcom_InDbWriterTransport();
      //Instantiate and add the object be included, transportation (drivers for transport mechanism),
      m_pInProt->setTransport(pftr);
    }
    else if ( strTransportProtocol == std::string ("OracleTransport"))
    {
      // Application object must be created first before 
      // create FormatMgr initialization in base class
      m_pOraAppAdatper = new CTelcom_OraAdapterApp("tspreceiver",telcom_version_str());

      // init FormatMgr and preparation of command line args
      CTelcom_Communication::initComm();

      CTelcom_InOracleTransport * pTelcom_InOracleTransport = new CTelcom_InOracleTransport();
      pTelcom_InOracleTransport->setFactory(new Telcom_In_factory());
      m_pInProt->setTransport(pTelcom_InOracleTransport);
    }
    else
    {
      // Application object must be created first before 
      // create FormatMgr initialization in base class
      m_pAppAdatper = new AdapterApp("tspreceiver",telcom_version_str());

      // init FormatMgr and preparation of command line args
      CTelcom_Communication::initComm();

      m_pInProt->setTransport(new CTelcom_InTcpipTransport());
    }

    
    m_pInProt->setTlgExpert(new CTelcom_TlgExpert(new CTelcom_InMsgTypeTranslator()));

    if ( m_IsOraFlag )
    {
      if (m_pOraAppAdatper)
      {
        //The resulting object Prot activated
        m_pOraAppAdatper->setRProt(m_pInProt);
      }
      else
        cCBS_StdLog_Task::getInstance()->log("No application adapter has been created!", 0);
    }
    else
    {
      if (m_pAppAdatper)
      {
        // Attach Receive PRotocol to telcom application
        m_pAppAdatper->setRProt(m_pInProt);
      }
      else
        cCBS_StdLog_Task::getInstance()->log("No application adapter has been created!", 0);
    }
    
  }
  catch (...)
  {
    cCBS_StdLog_Task::getInstance()->log("CTelcom_InAppCommunication::initComm: Unable to initialize application", 0);
  }
}

//##ModelId=45ACEDCE0104
void CTelcom_InAppCommunication::startComm()
{
  try 
  {
    if ( m_IsOraFlag )
    {
      if (m_pOraAppAdatper)
      {
        m_pOraAppAdatper->init(m_argc, m_argv);

        std::string strDbConnectStr = static_cast<CTelcom_OraAdapterApp*>(m_pOraAppAdatper)->getDbConnectStr();

        m_pInProt->getTransport()->setConnectInfo(strDbConnectStr);

        m_pOraAppAdatper->run();
      }
      else
        cCBS_StdLog_Task::getInstance()->log("No application adapter has been created!", 0);
    }
    else
    {
      if (m_pAppAdatper)
      {
        m_pAppAdatper->init(m_argc, m_argv);
        m_pAppAdatper->run();
      }
      else
        cCBS_StdLog_Task::getInstance()->log("No application adapter has been created!", 0);
    }
  }
  catch (ETAMError &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, e.what(), "CTelcom_InAppCommunication::startComm()", "");
  }
  catch (...)
  {
    cCBS_StdLog_Task::getInstance()->log("CTELCOM_ReceiveCommunication::run():Caught a serious unknown error", 0);
  }

}

void CTelcom_InAppCommunication::stopComm()
{
  if (m_pInProt)
  {
    m_pInProt->setCommand(Prot::cmdExit);
  }
}

bool CTelcom_InAppCommunication::getStatus(std::string& _status)
{
  bool RetValue = true;

  try
  {
    if (m_pInProt)
    {
      if ( m_pInProt->connected() )
      {
        _status = "Connected to " + m_pInProt->getTransport()->getConnectInfo() + " at " + CDateTime().asString();
      }
      else
      {
         _status = "Not connected to " + m_pInProt->getTransport()->getConnectInfo() + " at " + CDateTime().asString();				 
      }
    }
    else
    {
      _status = "Error to get it";
      RetValue = false;
    }
  }
  catch(...)
  {
    RetValue = false;
  }

  return RetValue;
}

