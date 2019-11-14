// Copyright (C) 2009 SMS Demag AG


#include "CDM_HMDTask.h"
#include "CDM_HMDDBManagerTask.h"


CDM_HMDDBManagerTask::CDM_HMDDBManagerTask()
: m_pDM_HMDDBManager(0)
{
}

CDM_HMDDBManagerTask::~CDM_HMDDBManagerTask()
{
if(m_pDM_HMDDBManager)
  {
    delete m_pDM_HMDDBManager;
    m_pDM_HMDDBManager = 0;
  }
}

CDM_HMDDBManager* CDM_HMDDBManagerTask::getDBManager()
{
  return m_pDM_HMDDBManager;
}

CDM_DataInterface_Impl* CDM_HMDDBManagerTask::getpDataInterface()
{
  return CDM_HMDTask::getInstance()->getpDataInterface();
}

CDM_ProductManagementInterface_Impl* CDM_HMDDBManagerTask::getpProductManagementInterface()
{
  return CDM_HMDTask::getInstance()->getpProductManagementInterface();
}

CDM_PlantManagementInterface_Impl* CDM_HMDDBManagerTask::getpPlantManagementInterface()
{
  return CDM_HMDTask::getInstance()->getpPlantManagementInterface();
}

void CDM_HMDDBManagerTask::handleDBConnectionError()
{
  CDM_HMDTask::getInstance()->handleDBConnectionError();
}

void CDM_HMDDBManagerTask::getOwnStateDetails(CORBA::String_out details)
{
  std::ostringstream buf;
	// mrut 2015-01-20: next line deleted due to memory leakage
	//cCBS_Task::getOwnStateDetails(details);
	buf << '\n' << "CDM_HMDDBManagerTask!" << std::ends;
	details = CORBA::string_dup(buf.str().c_str());
}

void CDM_HMDDBManagerTask::initDBManager()
{
  m_pDM_HMDDBManager = new CDM_HMDDBManager(this);
  m_pDM_HMDDBManager->init();

}

void CDM_HMDDBManagerTask::ownRunDown()
{
	log("CDM_HMDDBManagerTask: ownRunDown()",3);

	setWorking(false);
}

void CDM_HMDDBManagerTask::ownStartUp()
{
  try
  {
    setWorking(true);

    initDBManager();

  }
  catch(...) 
  {
    std::cout << "exception caught in CDM_HMDDBManagerTask::ownStartUp()" << std::endl;
  }
}

CDM_HMDDBManagerTask* CDM_HMDDBManagerTask::m_Instance = 0;

CDM_HMDDBManagerTask* CDM_HMDDBManagerTask::getInstance()
{
	if ( m_Instance == 0 )
	{
		m_Instance = new CDM_HMDDBManagerTask();
	}
	return m_Instance;
}

bool CDM_HMDDBManagerTask::initialize()
{
	bool RetValue = cCBS_StdFrame_Task::initialize();

  return RetValue;
}

cCBS_StdConnection* CDM_HMDDBManagerTask::getStdConnection()
{
	return CDM_HMDTask::getInstance()->getStdConnection();
}

void CDM_HMDDBManagerTask::doOnTaskWorkingError()
{

  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ErrorTaskWorkingState(sMessage);
  
  setWorking(false);
}

