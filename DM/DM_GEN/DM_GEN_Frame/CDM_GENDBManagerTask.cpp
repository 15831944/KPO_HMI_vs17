// Copyright (C) 2009 SMS Demag AG
#include "CDM_GENTask.h"
#include "CDM_GENDBManagerTask.h"

CDM_GENDBManagerTask* CDM_GENDBManagerTask::m_Instance = 0;

CDM_GENDBManagerTask::CDM_GENDBManagerTask()
:m_pDM_GENDBManager(0)
{
}

CDM_GENDBManagerTask::~CDM_GENDBManagerTask()
{
}

CDM_GENDBManager* CDM_GENDBManagerTask::getDBManager()
{
  return m_pDM_GENDBManager;
}

CDM_DataInterface_Impl* CDM_GENDBManagerTask::getpDataInterface()
{
  return CDM_GENTask::getInstance()->getpDataInterface();
}

CDM_ProductManagementInterface_Impl* CDM_GENDBManagerTask::getpProductManagementInterface()
{
  return CDM_GENTask::getInstance()->getpProductManagementInterface();
}

CDM_PlantManagementInterface_Impl* CDM_GENDBManagerTask::getpPlantManagementInterface()
{
  return CDM_GENTask::getInstance()->getpPlantManagementInterface();
}

void CDM_GENDBManagerTask::handleDBConnectionError()
{
  CDM_GENTask::getInstance()->handleDBConnectionError();
}

CDM_GENDBManagerTask* CDM_GENDBManagerTask::getInstance()
{
	if ( m_Instance == 0 )
	{
		m_Instance = new CDM_GENDBManagerTask();
	}
	return m_Instance;
}

void CDM_GENDBManagerTask::initDBManager()
{
   m_pDM_GENDBManager = new CDM_GENDBManager(this);
   m_pDM_GENDBManager->init();
}

void CDM_GENDBManagerTask::ownRunDown()
{
	log("CDM_GENDBManagerTask: ownRunDown()", 1);
 
	setWorking(false);
  if(m_pDM_GENDBManager)
  {
    delete m_pDM_GENDBManager;
    m_pDM_GENDBManager = 0;
  }
}

void CDM_GENDBManagerTask::ownStartUp()
{
  try
  {
    setWorking(true);

    initDBManager();
  }
  catch(...) 
  {
    std::cout << "exception caught in CDM_GENDBManagerTask::ownStartUp()" << std::endl;
  }
}

bool CDM_GENDBManagerTask::initialize()
{
	bool RetValue = CDM_DBManagerTask::initialize();

  return RetValue;
}

cCBS_StdConnection* CDM_GENDBManagerTask::getStdConnection()
{
  return CDM_GENTask::getInstance()->getStdConnection();
}

void CDM_GENDBManagerTask::doOnTaskWorkingError()
{

  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ErrorTaskWorkingState(sMessage);
  
  setWorking(false);
}


