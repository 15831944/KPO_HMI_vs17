// Copyright (C) 2006 SMS Demag AG

#include "CTlgHandlerFactory.h"
#include "CTelegram_Adapter.h"
#include "CDH_IN_Task.h"
#include "cCBS_StdCORBA_Task.h"
#include "CDH_IN_Telcom_Impl.h"
#include "CDH_IN_Interface_Impl.h"


//##ModelId=4582C6E30295
CDH_IN_Task* CDH_IN_Task::m_Instance = 0;

//##ModelId=4582C6AC02C0
void CDH_IN_Task::setCORBAConnections()
{
  std::string ServerName  = cCBS_StdInitBase::getInstance()->m_ServerName;

  std::string InterfaceServantName = ServerName + "Interface";
  std::string TelcomServantName    = ServerName + "Telcom";

  cCBS_StdInitBase::getInstance()->replaceWithEntry(getTaskName(), "InterfaceServantName", InterfaceServantName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(getTaskName(), "TelcomServantName", TelcomServantName);

  CDH_IN_Telcom_Impl* m_pTelcomInterface_Impl = new CDH_IN_Telcom_Impl();
  CDH_IN_Interface_Impl* m_pDHInterface_Impl  = new CDH_IN_Interface_Impl();

  m_pTelcomInterface_Impl->setProviderName(TelcomServantName);
  m_pDHInterface_Impl->setProviderName(InterfaceServantName);

  // register servants
  cCBS_StdCORBA_Task * pCORBA_Task = cCBS_StdCORBA_Task::getInstance();
  if (pCORBA_Task)
  {
    pCORBA_Task->registerServant(m_pTelcomInterface_Impl,TelcomServantName);
    pCORBA_Task->registerServant(m_pDHInterface_Impl,InterfaceServantName);
  }

  // *********************************
  // instantiate Telegram_Adapter
  // *********************************
  m_pTelegram_Adapter = new CTelegram_Adapter(m_pTelcomInterface_Impl, m_pDHInterface_Impl, this);
}

//##ModelId=4582C6D801DC
CDH_IN_Task::~CDH_IN_Task()
{
}

//##ModelId=4582C71702A1
CDH_IN_Task* CDH_IN_Task::getInstance()
{
	if ( m_Instance == 0 )
	{
		m_Instance = new CDH_IN_Task();
	}
	return m_Instance;
}

//##ModelId=4582C65401B8
bool CDH_IN_Task::initialize()
{
  bool ret;
  ret = CDH_Task::initialize();

  m_pTlgHandlerFactory = new CTlgHandlerFactory();

  std::string ServerName  = cCBS_StdInitBase::getInstance()->m_ServerName;

  cCBS_StdInitBase::getInstance()->replaceWithEntry(getTaskName(), "FactoryServer", ServerName);

  CTelegram_Handler* th = m_pTlgHandlerFactory->createTlgHandler(ServerName);

  if ( th )
  {
    m_pTelegram_Adapter->registerHandler(th);
  }
  else
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "no factory member found", "CDH_IN_Task::initialize()", "");
  }

  return ret;
}

//##ModelId=4582C6D70388
CDH_IN_Task::CDH_IN_Task()
{
  m_Instance = 0;
}

//##ModelId=45868B29005E
 CTelegram_Adapter* CDH_IN_Task::getpTelegramAdapter()
{
	return m_pTelegram_Adapter;
}
