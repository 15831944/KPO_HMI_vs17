// Copyright (C) 2006 SMS Demag AG Germany

#include "CEventHandlerFactory.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEvent_Task.h"
#include "CDH_OUT_Task.h"
#include "CDH_OUT_Telcom_Impl.h"
#include "CDH_EventHandler.h"


CDH_OUT_Task* CDH_OUT_Task::m_Instance = 0;

CDH_OUT_Task* CDH_OUT_Task::getInstance()
{
	if ( m_Instance == 0 )
	{
		m_Instance = new CDH_OUT_Task();
	}
	return m_Instance;
}

bool CDH_OUT_Task::initialize()
{
  bool ret;
	ret = CDH_Task::initialize();

  m_pEventHandlerFactory = new CEventHandlerFactory();

  std::string ServerName  = cCBS_StdInitBase::getInstance()->m_ServerName;

  cCBS_StdInitBase::getInstance()->replaceWithEntry("FACTORY","ServerName",ServerName);

  CDH_EventHandler* evh = m_pEventHandlerFactory->createEventHandler(ServerName);
  
  if ( evh )
  {
    cCBS_StdEvent_Task::getInstance()->registerEventHandler(evh);
  }
  else
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "no factory member found", "CDH_OUT_Task::initialize()", "");
  }


  return ret;
}

void CDH_OUT_Task::setCORBAConnections()
{
	m_pDMProxyManager = new CProxyManager<DM::iDM_Interface>();
	m_pDHProxyManager = new CProxyManager<DH::iDH_Interface>();
	
  // Proxy names under "DataManager" in ini-file will be read 
  //and all object references to this proxies will be holed 
  //from nameservice.
  m_pDMProxyManager->registerProxies("DataManager");

  m_pDHProxyManager->registerProxies("DataHandler");

  // register interface for telcoms access
  cCBS_StdCORBA_Task * pCORBA_Task = cCBS_StdCORBA_Task::getInstance();
  if (pCORBA_Task)
  {
    m_pInterface_OUT = new CDH_OUT_Telcom_Impl();

    // register servant(s)
    std::string ServerName  = cCBS_StdInitBase::getInstance()->m_ServerName;

    std::string TelcomServantName    = ServerName + "Telcom";

    cCBS_StdInitBase::getInstance()->replaceWithEntry(getTaskName(), "TelcomServantName", TelcomServantName);
    
    pCORBA_Task->registerServant(m_pInterface_OUT, TelcomServantName);
  }// end if (pCORBA_Task)
}

CDH_OUT_Task::CDH_OUT_Task()
{
}

CDH_OUT_Task::~CDH_OUT_Task()
{
}

