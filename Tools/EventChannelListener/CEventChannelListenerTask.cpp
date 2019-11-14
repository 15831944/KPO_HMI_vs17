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

#include "CDM_EAFSignalsAndMeasurementsEventHandler.h"
#include "CDM_EAFTreatmentManagementEventHandler.h"
#include "CDM_EAFAnalysisEventHandler.h"
#include "CDM_EAFMaterialEventHandler.h"
#include "CDM_EAFModesAndAvailabilitiesEventHandler.h"
#include "CDM_EAFPurposeEventHandler.h"
#include "CDM_EAFModelResultEventHandler.h"
#include "CDM_EAFEventHandler.h"
#include "CDM_EAFEventLogHandlerAnalysis.h"
#include "CDM_EAFEventLogHandlerMaterial.h"
#include "CDM_EAFEventLogHandlerModelResults.h"
#include "CDM_EAFEventLogHandlerModesAndAvailabilities.h"
#include "CDM_EAFEventLogHandlerPurpose.h"
#include "CDM_EAFEventLogHandlerSignalsAndMeasurements.h"
#include "CDM_EAFEventLogHandlerTreatmentManagement.h"

#include "CDM_EAFTask.h"


CDM_EAFTask::CDM_EAFTask()
{
}

CDM_EAFTask::~CDM_EAFTask()
{
}


 CDM_EAFTask* CDM_EAFTask::getInstance()
{
	if ( m_Instance == 0 )
	{
		m_Instance = new CDM_EAFTask( );
	}
	return m_Instance;
}


bool CDM_EAFTask::initialize()
{
	bool RetCode = true;

  // must be called first 
  RetCode = CDM_Task::initialize();

  m_pPlantManager             = new CDM_EAFPlantManager();
  m_pProductManager           = new CDM_EAFProductManager();

  initManager();

  m_pProductManagementInterface->setpDM_Task(this);

  return RetCode;
}


 void CDM_EAFTask::registerEventHandlers()
{
  m_pEventTask = cCBS_StdEvent_Task::getInstance();

  // register event handler classes
  if (m_pEventTask)
  {
    CDM_EventHandler * EventHandler = 0;
    EventHandler = new CDM_EAFTreatmentManagementEventHandler();
    m_pEventTask->registerEventHandler(EventHandler);

    EventHandler = new CDM_EAFSignalsAndMeasurementsEventHandler();
    m_pEventTask->registerEventHandler(EventHandler);

    EventHandler = new CDM_EAFAnalysisEventHandler();
    m_pEventTask->registerEventHandler(EventHandler);

    EventHandler = new CDM_EAFMaterialEventHandler();
    m_pEventTask->registerEventHandler(EventHandler);

    EventHandler = new CDM_EAFModesAndAvailabilitiesEventHandler();
    m_pEventTask->registerEventHandler(EventHandler);

    EventHandler = new CDM_EAFPurposeEventHandler();
    m_pEventTask->registerEventHandler(EventHandler);

    EventHandler = new CDM_EAFModelResultEventHandler();
    m_pEventTask->registerEventHandler(EventHandler);

  }
}


void CDM_EAFTask::registerEventLogHandlers()
{
  CDM_EAFEventLogHandler * pEventLogHandler;

  pEventLogHandler = new CDM_EAFEventLogHandlerAnalysis();
  registerEventLogHandler(pEventLogHandler);

  pEventLogHandler = new CDM_EAFEventLogHandlerMaterial();
  registerEventLogHandler(pEventLogHandler);

  pEventLogHandler = new CDM_EAFEventLogHandlerModelResults();
  registerEventLogHandler(pEventLogHandler);

  pEventLogHandler = new CDM_EAFEventLogHandlerModesAndAvailabilities();
  registerEventLogHandler(pEventLogHandler);

  pEventLogHandler = new CDM_EAFEventLogHandlerPurpose();
  registerEventLogHandler(pEventLogHandler);

  pEventLogHandler = new CDM_EAFEventLogHandlerSignalsAndMeasurements();
  registerEventLogHandler(pEventLogHandler);

  pEventLogHandler = new CDM_EAFEventLogHandlerTreatmentManagement();
  registerEventLogHandler(pEventLogHandler);
}

CDM_EAFTask* CDM_EAFTask::m_Instance = 0;

std::string CDM_EAFTask::getProcessState(const std::string& ID)
{
  std::stringstream RetValue;

  // search Process state data for ID = Product ID
  if ( m_pProductManager && m_pProductManagementInterface )
  {
    std::string ProductID(ID);

    if ( m_pProductManager->findProduct(ProductID) )
    {
      // ElecCons if valid
      long ElecCons = m_pProductManagementInterface->getLong(ID.c_str(),DATA::ElecCons);

      if ( ElecCons != DEF::Inv_Long )
      {
        RetValue << ElecCons << " kWh ";
      }
    }
  }

  return RetValue.str();
}

void CDM_EAFTask::sendInitialEvents()
{
  CEventMessage Message;

  std::string PlantID = DEF_SUBSYSTEMS::EAF;
  std::vector<std::string> DestinationList;
  std::string SenderName;
  std::string TaskName = getTaskName();
  
  cCBS_StdInitBase::getInstance()->getEntry(TaskName,"PlantId",PlantID);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"SenderName",SenderName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"DestinationName", DestinationList);

  std::vector<std::string> PlantList;
  std::vector<std::string>::iterator it;
  
  cCBS_StdInitBase::getInstance()->getEntryList(TaskName,"PlantId",PlantList);

  for ( it = PlantList.begin() ; it != PlantList.end(); it ++)
  { 
    Message.setPlantID( (*it) );
    Message.setMessage(EAF_EvMsg::evEAFPlantStatusRequest);
    Message.setPlantEvent(true);
    Message.dispatch(SenderName,DestinationList);
  }
}

