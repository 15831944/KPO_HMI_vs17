// Copyright (C) 1999 - 2000 SMS Demag AG

#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <string>
#include <vector>
using namespace std;



#include "cCBS_StdEvent_Task.h"
#include "cCBS_StdCORBA_Task.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"

#include "CDM_GENTask.h"
#include "CDM_GENTreatmentManagementEventHandler.h"
#include "CDM_GENAnalysisEventHandler.h"
#include "CDM_GENMaterialEventHandler.h"
#include "CDM_GENModesAndAvailabilitiesEventHandler.h"
#include "CDM_GENModelResultEventHandler.h"

#include "CDM_GENEventHandler.h"
#include "CDM_GENHMIEventHandler.h"
#include "CDM_GENL3EventHandler.h"
#include "CDM_GENCCSEventHandler.h"

#include "CDM_GENPlantManager.h"
#include "CDM_GENProductManager.h"

CDM_GENTask* CDM_GENTask::m_Instance = 0;

CDM_GENTask::CDM_GENTask()
{
	// ToDo: Add your specialized code here and/or call the base class
}

CDM_GENTask::~CDM_GENTask()
{
}


 CDM_GENTask* CDM_GENTask::getInstance()
{
  if ( m_Instance == 0 )
  {
	  m_Instance = new CDM_GENTask( );
  }
  return m_Instance;
}


bool CDM_GENTask::initialize()
{
	bool RetCode = true;

  // must be called first 
  RetCode = CDM_Task::initialize();

  m_pPlantManager   = new CDM_GENPlantManager();
  m_pProductManager = new CDM_GENProductManager();

  initManager();

  return RetCode;
}


void CDM_GENTask::registerEventHandlers()
{
  cCBS_StdEvent_Task* pEventTask = cCBS_StdEvent_Task::getInstance();

  // register event handler classes
  CDM_EventHandler * pEventHandler = 0;

  pEventHandler = new CDM_GENCCSEventHandler();
  pEventTask->registerEventHandler( pEventHandler );

  pEventHandler = new CDM_GENL3EventHandler();
  pEventTask->registerEventHandler( pEventHandler );

  pEventHandler = new CDM_GENHMIEventHandler();
  pEventTask->registerEventHandler( pEventHandler );

  pEventHandler = new CDM_GENTreatmentManagementEventHandler();
  pEventTask->registerEventHandler( pEventHandler );

  pEventHandler = new CDM_GENModesAndAvailabilitiesEventHandler();
  pEventTask->registerEventHandler( pEventHandler );

  pEventHandler =  new CDM_GENAnalysisEventHandler();
  pEventTask->registerEventHandler( pEventHandler );
}


void CDM_GENTask::registerEventLogHandlers()
{
	// ToDo: Add your specialized code here
	
	static_cast<void>(0);
}

std::string CDM_GENTask::getProcessState(const std::string& ID)
{
  std::string RetValue;
  return RetValue;
}
