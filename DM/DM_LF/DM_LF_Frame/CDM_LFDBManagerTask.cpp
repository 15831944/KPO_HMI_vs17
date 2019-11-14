// Copyright (C) 2009 SMS Demag AG


#include "CDM_LFTask.h"
#include "CDM_LFDBManagerTask.h"


CDM_LFDBManagerTask::CDM_LFDBManagerTask()
: m_pDM_LFDBManager(0)
{
}

CDM_LFDBManagerTask::~CDM_LFDBManagerTask()
{
  if(m_pDM_LFDBManager)
  {
    delete m_pDM_LFDBManager;
    m_pDM_LFDBManager = 0;
  }
}

CDM_LFDBManager* CDM_LFDBManagerTask::getDBManager()
{
  return m_pDM_LFDBManager;
}

CDM_DataInterface_Impl* CDM_LFDBManagerTask::getpDataInterface()
{
  return CDM_LFTask::getInstance()->getpDataInterface();
}

CDM_ProductManagementInterface_Impl* CDM_LFDBManagerTask::getpProductManagementInterface()
{
  return CDM_LFTask::getInstance()->getpProductManagementInterface();
}

CDM_PlantManagementInterface_Impl* CDM_LFDBManagerTask::getpPlantManagementInterface()
{
  return CDM_LFTask::getInstance()->getpPlantManagementInterface();
}

void CDM_LFDBManagerTask::handleDBConnectionError()
{
  CDM_LFTask::getInstance()->handleDBConnectionError();
}

void CDM_LFDBManagerTask::initDBManager()
{
  m_pDM_LFDBManager = new CDM_LFDBManager(this);
  m_pDM_LFDBManager->init();

}

void CDM_LFDBManagerTask::ownRunDown()
{
	log("CDM_LFDBManagerTask: ownRunDown()", 1);

	setWorking(false);
  if(m_pDM_LFDBManager)
  {
    delete m_pDM_LFDBManager;
    m_pDM_LFDBManager = 0;
  }

}

void CDM_LFDBManagerTask::ownStartUp()
{
  try
  {
    setWorking(true);

    initDBManager();

  }
  catch(...) 
  {
    std::cout << "exception caught in CDM_LFDBManagerTask::ownStartUp()" << std::endl;
  }
}

CDM_LFDBManagerTask* CDM_LFDBManagerTask::m_Instance = 0;

CDM_LFDBManagerTask* CDM_LFDBManagerTask::getInstance()
{
	if ( m_Instance == 0 )
	{
		m_Instance = new CDM_LFDBManagerTask();
	}
	return m_Instance;
}

bool CDM_LFDBManagerTask::initialize()
{
	bool RetValue = CDM_DBManagerTask::initialize();

  return RetValue;
}

cCBS_StdConnection* CDM_LFDBManagerTask::getStdConnection()
{
  return CDM_LFTask::getInstance()->getStdConnection();
}

void CDM_LFDBManagerTask::doOnTaskWorkingError()
{

  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ErrorTaskWorkingState(sMessage);
  
  setWorking(false);
}

