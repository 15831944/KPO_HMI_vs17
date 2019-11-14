// Copyright (C) 2007 SMS Siemag AG

#include <sstream>
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdDB_Task.h"
#include "cCBS_StdFrame.h"
#include "cCBS_StdEventHandlerAdapter.h"

#include "CTelcom_Task.h"


DH_Telcom::iDH_Telcom_var& CTelcom_Task::getpDH_Interface(std::string& ServerName, const std::string & InterfaceTypeName)
{
  m_pDH_Interface = 0;

  try
  {
    if ( ServerName != DEF::Inv_String && !ServerName.empty() )
    {
      m_pDH_Interface = m_pDHProxyManager->getObjRefByServerName (ServerName, InterfaceTypeName);

      if (!m_pDH_Interface)
      {
        m_pDHProxyManager->handleConnectionErrorByServerName(ServerName, InterfaceTypeName);
        m_pDH_Interface = m_pDHProxyManager->getObjRefByServerName(ServerName, InterfaceTypeName);
      }
    }
    else
    {
      cCBS_StdCORBA_Task::getInstance()->log("ServerName not usable",1);
    }
  }
  catch(...)
  {

	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                        "CTelcom_Task::getpDH_Interface()",
                                        "getObjRefByServerName");

    m_pDH_Interface = 0;

  }

  if ( m_pDH_Interface == 0 )
  {
    throw CORBA::INV_OBJREF ();
  }


  return m_pDH_Interface;

}

CTelcom_Task::CTelcom_Task()
{
}

CTelcom_Task::~CTelcom_Task()
{
}

bool CTelcom_Task::initialize()
{
  // must be called first
	bool ret = CSMC_FrameTask::initialize();

  setCORBAConnections();
  return ret;
}

bool CTelcom_Task::checkDBConnection()
{
  bool RetValue = cCBS_StdDB_Task::getInstance()->checkConnection(m_DBName, m_DBUser, m_DBPassword);

  if ( !RetValue )
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(Message,"DB connection check failed","CSMC_FrameTask::checkDBConnection()","Can not establish database connection");
  }

  return RetValue;
}
