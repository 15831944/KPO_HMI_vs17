// Copyright (C) 2006 SMS Demag AG

#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "CHMI_EventHandlerFactory.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdEvent_Task.h"
#include "CDH_HMI_Task.h"
#include "CDH_HMI_Interface_Impl.h"
#include "CDH_EventHandler.h"


//##ModelId=4588272800D3
CDH_HMI_Task* CDH_HMI_Task::m_pInstance = 0;

//##ModelId=4586739B0272
CDH_HMI_Task* CDH_HMI_Task::getInstance()
{
  if( m_pInstance == 0 )
    m_pInstance = new CDH_HMI_Task();

  return m_pInstance;
}

//##ModelId=4586739B0290
bool CDH_HMI_Task::initialize()
{
  bool ret = CDH_Task::initialize();

  // instantiate and register all Event Handlers
  m_pHMI_EventHandlerFactory = new CHMI_EventHandlerFactory();

  std::string ServerName  = cCBS_StdInitBase::getInstance()->m_ServerName;
  std::string TaskName    = getTaskName();

  cCBS_StdLog_Task::getInstance()->log("CDH_HMI_Task::initialize(): create eventhandler for TaskName = " + TaskName,3);

  std::vector<std::string> FactoryServerList;
  std::vector<std::string>::iterator it;

  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName, "FactoryServer", FactoryServerList);

  if ( FactoryServerList.empty() )
  {
    FactoryServerList.push_back(ServerName);
  }


  for ( it = FactoryServerList.begin(); it != FactoryServerList.end(); ++it)
  {
    std::string FactoryServer = (*it);

    CDH_EventHandler* evh = m_pHMI_EventHandlerFactory->createEventHandler(FactoryServer);

    if (evh)
    {
      evh->setpTask(this); // to initialize handler with reciver, sender by using task name

      cCBS_StdEvent_Task::getInstance()->registerEventHandler(evh);
      evh->setpDHTask(this);
    }
    else
    {
      cCBS_StdLog_Task::getInstance()->log("ERROR: CDH_HMI_Task::initialize(): No event handler created for ServerName " + FactoryServer,0);
    }
  } // for ( it = FactoryServerList.begin(); it != FactoryServerList.end(); ++it)

  return ret;
}

//##ModelId=4586739B023B
CDH_HMI_Task::~CDH_HMI_Task()
{
  if ( m_pDMProxyManager )
    delete m_pDMProxyManager;
}

//##ModelId=4586739B027D
CDH_HMI_Task::CDH_HMI_Task()
{
  m_pDMProxyManager = new CProxyManager<DM::iDM_Interface>();
}


//##ModelId=4586739B0218
void CDH_HMI_Task::setCORBAConnections()
{
  if (m_pDMProxyManager)
  {
    // Proxy names under "DataManager" in ini-file will be read 
    //and all object references to this proxies will be holed 
    //from nameservice.
    m_pDMProxyManager->registerProxies("DataManager");
  }

  std::string ServerName  = cCBS_StdInitBase::getInstance()->m_ServerName;
  std::string ServantName = ServerName + "Interface";
  std::string TaskName    = getTaskName();

  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName, "ServantName", ServantName);

  // create object for HMI access
  m_pInterface_OUT = new CDH_HMI_Interface_Impl();

  // register servants
  cCBS_StdCORBA_Task * pCORBA_Task = cCBS_StdCORBA_Task::getInstance();
  if (pCORBA_Task)
  {
    pCORBA_Task->registerServant(m_pInterface_OUT,ServantName);
  }
}


