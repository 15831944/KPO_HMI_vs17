// Copyright (C) 2009 SMS Demag AG
#include "CDM_EAFTask.h"
#include "CDM_EAFDBManagerTask.h"


CDM_EAFDBManagerTask* CDM_EAFDBManagerTask::m_Instance = 0;

CDM_EAFDBManagerTask::CDM_EAFDBManagerTask()
:m_pDM_EAFDBManager(0)
{
}

CDM_EAFDBManagerTask::~CDM_EAFDBManagerTask()
{
}

CDM_EAFDBManager* CDM_EAFDBManagerTask::getDBManager()
{
  return m_pDM_EAFDBManager;
}


CDM_DataInterface_Impl* CDM_EAFDBManagerTask::getpDataInterface()
{
  return CDM_EAFTask::getInstance()->getpDataInterface();
}

CDM_ProductManagementInterface_Impl* CDM_EAFDBManagerTask::getpProductManagementInterface()
{
  return CDM_EAFTask::getInstance()->getpProductManagementInterface();
}

CDM_PlantManagementInterface_Impl* CDM_EAFDBManagerTask::getpPlantManagementInterface()
{
  return CDM_EAFTask::getInstance()->getpPlantManagementInterface();
}

void CDM_EAFDBManagerTask::handleDBConnectionError()
{
  CDM_EAFTask::getInstance()->handleDBConnectionError();
}

CDM_EAFDBManagerTask* CDM_EAFDBManagerTask::getInstance()
{
	if ( m_Instance == 0 )
	{
		m_Instance = new CDM_EAFDBManagerTask();
	}
	return m_Instance;
}

void CDM_EAFDBManagerTask::initDBManager()
{
   m_pDM_EAFDBManager = new CDM_EAFDBManager(this);
   m_pDM_EAFDBManager->init();
}

void CDM_EAFDBManagerTask::ownRunDown()
{
	log("CDM_EAFDBManagerTask: ownRunDown()", 1);
 
	setWorking(false);
  if(m_pDM_EAFDBManager)
  {
    delete m_pDM_EAFDBManager;
    m_pDM_EAFDBManager = 0;
  }
}

void CDM_EAFDBManagerTask::ownStartUp()
{
  try
  {
    setWorking(true);

    initDBManager();
  }
  catch(...) 
  {
    std::cout << "exception caught in CDM_EAFDBManagerTask::ownStartUp()" << std::endl;
  }
}

bool CDM_EAFDBManagerTask::initialize()
{
	bool RetValue = CDM_DBManagerTask::initialize();

  return RetValue;
}

cCBS_StdConnection* CDM_EAFDBManagerTask::getStdConnection()
{
  return CDM_EAFTask::getInstance()->getStdConnection();
}

void CDM_EAFDBManagerTask::doOnTaskWorkingError()
{

  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ErrorTaskWorkingState(sMessage);
  
  setWorking(false);
}

