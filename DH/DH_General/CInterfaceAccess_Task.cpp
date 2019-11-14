// Copyright (C) 2006 SMS Demag AG Germany
#include "CInterfaceAccess_Task.h"


DM::iDM_Interface_var& CInterfaceAccess_Task::getpDM_Interface(const std::string& ServerName, const std::string& InterfaceTypeName)
{
  m_pDM_Interface = 0;

  try
  {
    if (m_pDMProxyManager)
    {
      m_pDM_Interface = m_pDMProxyManager->getObjRefByServerName(ServerName,InterfaceTypeName);
      if (!m_pDM_Interface)
      {
        m_pDMProxyManager->handleConnectionErrorByServerName(ServerName,InterfaceTypeName);
        m_pDM_Interface = m_pDMProxyManager->getObjRefByServerName(ServerName,InterfaceTypeName);
      }
    }
  }
  catch(...)
  {
    m_pDM_Interface = 0;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,
      "Getting CORBA Object ",
      "CInterfaceAccess_Task::getpDM_Interface()",
      "getObjRefByServerName()");
  }

  if ( m_pDM_Interface == 0 )
  {
    throw CORBA::INV_OBJREF ();
  }

  return m_pDM_Interface;
}

//TODO: prevent warning about local variable address returned, or we should change it to return var not var&
DH::iDH_Interface_var& CInterfaceAccess_Task::getpDH_Interface(const std::string& ServerName, const std::string& InterfaceTypeName)
{
  m_pDH_Interface = 0;

  if (m_pDHProxyManager)
  {
    m_pDH_Interface = m_pDHProxyManager->getObjRefByServerName(ServerName,InterfaceTypeName);
    if (!m_pDH_Interface)
    {
      m_pDHProxyManager->handleConnectionErrorByServerName(ServerName,InterfaceTypeName);
      m_pDH_Interface = m_pDHProxyManager->getObjRefByServerName(ServerName,InterfaceTypeName);
    }
  }

  return m_pDH_Interface;
}

CInterfaceAccess_Task::CInterfaceAccess_Task() 
: m_pInterface_OUT(0)
, m_pDM_Interface(0)
{
}

CInterfaceAccess_Task::~CInterfaceAccess_Task()
{
}

CSMC_DataProvider_Impl* CInterfaceAccess_Task::getpInterface_OUT()
{
	return m_pInterface_OUT;
}

