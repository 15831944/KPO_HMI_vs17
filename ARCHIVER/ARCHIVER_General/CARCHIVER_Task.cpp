// Copyright (C) 2007 SMS Siemag AG

#include <string>
#include "iDM_Interface_s.hh"

#include "cCBS_StdCORBA_Task.h"
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdDB_Task.h"
#include "cCBS_StdEventLogFrameController.h"

#include "CARCHIVER_Task.h"


//##ModelId=42971E420005
CARCHIVER_Task::CARCHIVER_Task() 
: m_pDM_Interface(0)
{
  m_pDM_ProxyManager = new CProxyManager<DM::iDM_Interface>();
}

//##ModelId=42971E4102FF
CARCHIVER_Task::~CARCHIVER_Task()
{
}

bool CARCHIVER_Task::initialize()
{
  bool ret = CSMC_FrameTask::initialize();

  setCORBAConnections();

  return ret;
}

//##ModelId=42971EE1020C
DM::iDM_Interface_var& CARCHIVER_Task::getpDM_Interface()
{
  return m_pDM_Interface;
}

//##ModelId=45F6E0130110
void CARCHIVER_Task::setpDM_Interface(const std::string& ServerName, const std::string& InterfaceTypeName)
{
  m_pDM_Interface = 0;

  cCBS_StdCORBA_Task* pCORBA_Task = cCBS_StdCORBA_Task::getInstance();

  if (pCORBA_Task && m_pDM_ProxyManager)
  {
    try
    {
      m_pDM_Interface = m_pDM_ProxyManager->getObjRefByServerName(ServerName,InterfaceTypeName);

      if (!m_pDM_Interface)
      {
        m_pDM_ProxyManager->handleConnectionErrorByServerName(ServerName,InterfaceTypeName);
        m_pDM_Interface = m_pDM_ProxyManager->getObjRefByServerName(ServerName,InterfaceTypeName);
      }
    }
    catch(...)
    {
      m_pDM_Interface = 0;

      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,
        "Getting CORBA Object ",
        "CARCHIVER_Task::setpDM_Interface()",
        "getObjRefByServerName()");
    }

    if ( m_pDM_Interface == 0 )
    {
      throw CORBA::INV_OBJREF ();
    }
  } // if (pCORBA_Task)
}


//##ModelId=42971EF40051
void CARCHIVER_Task::setCORBAConnections()
{
  // find multiple interfaces in ini file
  cCBS_StdCORBA_Task * pCORBA_Task = cCBS_StdCORBA_Task::getInstance();
  cCBS_StdInitBase *pStdInitBase = cCBS_StdInitBase::getInstance();

  std::vector<std::string> List;

  if (pCORBA_Task && m_pDM_ProxyManager)
  {
    // Proxy names under "DataManager" in ini-file will be read 
    //and all object references to this proxies will be holed 
    //from nameservice.
    m_pDM_ProxyManager->registerProxies("DataManager");
  }
}


//##ModelId=42B8117302EB
void CARCHIVER_Task::log(const std::string& Message, long Level)
{
  // log if trace level of actual Task => output level from message
  if ( (long)getTraceLevel() >= Level )
  {
    cCBS_StdLog_Task::getInstance()->writeLog(Message,Level);
  }
}

