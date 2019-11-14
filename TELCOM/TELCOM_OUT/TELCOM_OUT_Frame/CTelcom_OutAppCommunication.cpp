// Copyright (C) 2007 SMS Demag AG
#pragma warning (disable: 4183 4290)

#include <sstream>

#include "CTelcom_OutDbWriterTransport.h"

#include "CTelcom_OutProt.h"
#include "CTelcom_FileTransport.h"
#include "CTelcom_OutTcpipTransport.h"
#include "CTelcom_TlgExpert.h"
#include "CTelcom_QueueManager.h"
#include "Telcom_Out_factory.h"
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CDateTime.h"

#include "CTelcom_OutAppCommunication.h"


CTelcom_OutAppCommunication::CTelcom_OutAppCommunication() 
: m_pAppAdatper(0), m_pOutProt(0), m_pQueueManager(0)
{
  m_IsOraFlag = false;
}

CTelcom_OutAppCommunication::~CTelcom_OutAppCommunication()
{
  //if   (m_pQueueManager)
  //{
  //  delete m_pQueueManager; m_pQueueManager=0;
  //}

  //if   (m_pOutProt)
  //{
  //  delete m_pOutProt; m_pOutProt=0;
  //}

  //if   (m_pAppAdatper)
  //{
  //  delete m_pAppAdatper; m_pAppAdatper=0;
  //}
}

//##ModelId=45AE4FCA0359
void CTelcom_OutAppCommunication::initComm()
{
  std::string HeaderName = "Head";                      // Name of the Header-Telegramms

  std::string appname = cCBS_StdInitBase::getInstance()->m_ServerName;

  try
  {
    m_pOutProt = new CTelcom_OutProt();

    // factory to create the telegrams
    m_pOutProt->setTlgFactory (new Telcom_Out_factory());
    m_pOutProt->setHeaderTlgType(HeaderName);// used name of header telegram in excel

    std::string strTransportProtocol = "";

    cCBS_StdInitBase::getInstance()->replaceWithEntry("SMS_Transport","transportProtocol",strTransportProtocol);
    
    if ( strTransportProtocol == std::string ("FileTransport") )
    {
      // Application object must be created first before 
      // create FormatMgr initialization in base class
      m_pAppAdatper = new AdapterApp(appname.c_str(),telcom_version_str());

      // init FormatMgr and preparation of command line args
      CTelcom_Communication::initComm();

      CTelcom_FileTransport * pftr = new CTelcom_FileTransport();
      pftr->setFactory(new Telcom_Out_factory());
      m_pOutProt->setTransport(pftr);
    }
    else if ( strTransportProtocol == std::string ("OraAdapterApp") )
    {
      m_IsOraFlag = true;

      // Application object must be created first before 
      // create FormatMgr initialization in base class
      m_pOraAppAdatper = new CTelcom_OraAdapterApp(appname, telcom_version_str());

      // init FormatMgr and preparation of command line args
      CTelcom_Communication::initComm();
      
      CTelcom_OutDbWriterTransport* pftr = new CTelcom_OutDbWriterTransport();
      //Instantiate and add the object be included, transportation (drivers for transport mechanism),
      m_pOutProt->setTransport(pftr);
    }
    else
    {
      // Application object must be created first before 
      // create FormatMgr initialization in base class
      m_pAppAdatper = new AdapterApp(appname.c_str(),telcom_version_str());

      // init FormatMgr and preparation of command line args
      CTelcom_Communication::initComm();

      m_pOutProt->setTransport(new CTelcom_OutTcpipTransport());
    }

    m_pQueueManager = new CTelcom_QueueManager();
    m_pQueueManager->setProtocol(m_pOutProt);
    m_pQueueManager->setMsgTypeTranslator(new CTelcom_OutMsgTypeTranslator());
    m_pOutProt->setSrcTransport (new QueueTransport(*m_pQueueManager));

    m_pOutProt->setTlgExpert(new CTelcom_TlgExpert(new CTelcom_OutMsgTypeTranslator()));

    if ( m_IsOraFlag )
    {
      if (m_pOraAppAdatper)
      {
        //The resulting object Prot activated
        m_pOraAppAdatper->setSProt(m_pOutProt);
      }
      else
        cCBS_StdLog_Task::getInstance()->log("No application adapter has been created!", 1);
    }
    else
    {
      if (m_pAppAdatper)
      {
        //The resulting object Prot activated
        m_pAppAdatper->setSProt(m_pOutProt);
      }
      else
        cCBS_StdLog_Task::getInstance()->log("No application adapter has been created!", 1);
    }
  }
  catch (TC_Exception &e) 
  {
    std::stringstream Message;
    Message << "CTelcom_OutAppCommunication::initComm: " << e.what();
    cCBS_StdLog_Task::getInstance()->log(Message.str(), 1);
  }
  catch (...)
  {
    cCBS_StdLog_Task::getInstance()->log("CTelcom_OutAppCommunication::initComm: Unable to initialize application", 1);
  }
}

//##ModelId=45AE4FCB0209
void CTelcom_OutAppCommunication::startComm()
{
  try 
  {
    if ( m_IsOraFlag )
    {
      if (m_pOraAppAdatper)
      {
        m_pOraAppAdatper->init(m_argc, m_argv);

        std::string strDbConnectStr = static_cast<CTelcom_OraAdapterApp*>(m_pOraAppAdatper)->getDbConnectStr();

        m_pOutProt->getTransport()->setConnectInfo(strDbConnectStr);
        
        m_pOraAppAdatper->run();
      }
      else
        cCBS_StdLog_Task::getInstance()->log("No application adapter has been created!", 1);
    }
    else
    {
      if (m_pAppAdatper)
      {
        m_pAppAdatper->init(m_argc, m_argv);
        m_pAppAdatper->run();
      }
      else
        cCBS_StdLog_Task::getInstance()->log("No application adapter has been created!", 1);
    }
  }
  catch (ETAMError &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, e.what(), "CTelcom_OutAppCommunication::startComm", "");
  }
  catch (...)
  {
    cCBS_StdLog_Task::getInstance()->log("ERROR: startComm: Caught a serious unknown error", 1);
  }
}

//##ModelId=45AE4FCC011C
void CTelcom_OutAppCommunication::stopComm()
{
  if (m_pOutProt)
    m_pOutProt->setCommand(Prot::cmdExit);
}

//##ModelId=45AF9CEB014E
CTelcom_QueueManager* CTelcom_OutAppCommunication::getQueueManager()
{
	return m_pQueueManager;
}

//##ModelId=45B4EBC1025A
CTelcom_OutProt* CTelcom_OutAppCommunication::getOutProt()
{
  return m_pOutProt;
}

bool CTelcom_OutAppCommunication::getStatus(std::string& _status)
{
  bool RetValue = true;

  try
  {
    if (m_pOutProt)
    {
      if ( m_pOutProt->connected() )
      {
        _status = "Connected to " + m_pOutProt->getTransport()->getConnectInfo() + " at " + CDateTime().asString();
      }
      else
      {
         _status = "Not connected to " + m_pOutProt->getTransport()->getConnectInfo() + " at " + CDateTime().asString();
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

