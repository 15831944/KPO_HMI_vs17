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

#include "DEF_GC_STATUS.h"

#include "CGC_Plant_Container.h"
#include "CPD_HEAT_PLANT_REF.h"
#include "CPD_HEAT_DATA.h"
#include "CGC_STATUS.h"

#include "CProductID.h"
#include "CDataConversion.h"

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
  cCBS_StdEvent_Task* pEventTask = cCBS_StdEvent_Task::getInstance();

  // register event handler classes
  CDM_EventHandler * EventHandler = 0;
  EventHandler = new CDM_EAFTreatmentManagementEventHandler();
  pEventTask->registerEventHandler(EventHandler);

  EventHandler = new CDM_EAFSignalsAndMeasurementsEventHandler();
  pEventTask->registerEventHandler(EventHandler);

  EventHandler = new CDM_EAFAnalysisEventHandler();
  pEventTask->registerEventHandler(EventHandler);

  EventHandler = new CDM_EAFMaterialEventHandler();
  pEventTask->registerEventHandler(EventHandler);

  EventHandler = new CDM_EAFModesAndAvailabilitiesEventHandler();
  pEventTask->registerEventHandler(EventHandler);

  EventHandler = new CDM_EAFPurposeEventHandler();
  pEventTask->registerEventHandler(EventHandler);

  EventHandler = new CDM_EAFModelResultEventHandler();
  pEventTask->registerEventHandler(EventHandler);
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
      double Value = m_pProductManagementInterface->getDouble(ID.c_str(),DATA::ElecCons);

      RetValue << "E: " << CDataConversion::SetInvalidToDefault(CDataConversion::RoundToLong(Value), 0) << "  ";
    } // if ( m_pProductManager->findProduct(ProductID,HeatID,TreatID) )
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
  
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"SenderName",SenderName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"DestinationName", DestinationList);

  std::vector<std::string> PlantList;
  std::vector<std::string>::iterator it;
  
  cCBS_StdInitBase::getInstance()->getEntryList("PLANT","PlantId",PlantList);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"PlantId",PlantList);

  Message.setPlantEvent(true);
  for ( it = PlantList.begin() ; it != PlantList.end(); it ++)
  { 
    Message.setPlantID( (*it) );
    Message.setMessage(EAF_EvMsg::evEAFPlantStatusRequest);
    Message.dispatch(SenderName,DestinationList);
    Message.setMessage(EAF_EvMsg::evEAFRequestMatAvail);
    Message.dispatch(SenderName,DestinationList);
  }
}

bool CDM_EAFTask::isProductInProduction(const std::string& HeatID, const std::string& TreatID, const std::string& PlantID, std::string& OrderID)
{
  bool RetValue = false;

  if (m_pPD_HEAT_DATA && m_pPD_HEAT_PLANT_REF && m_pGC_Plant_Container && m_pGC_STATUS)
  {
    // first seperate Plant and PlantNo from PlantID
    std::string Plant = m_pGC_Plant_Container->getPlant(PlantID);
    long PlantNo      = m_pGC_Plant_Container->getPlantNo(PlantID);

    std::string Message;

    Message += "CDM_EAFTask::isProductInProduction";
    Message += " checking " + HeatID + " " + TreatID + " " + PlantID;

    log(Message,3);

    std::vector<long> PlantRelatedStates;
    PlantRelatedStates.push_back(m_pGC_STATUS->getStatusNo(Plant,DEF_GC_STATUS::HeatAnnounced));
    PlantRelatedStates.push_back(m_pGC_STATUS->getStatusNo(Plant,DEF_GC_STATUS::TreatmentStart));
    PlantRelatedStates.push_back(m_pGC_STATUS->getStatusNo(Plant,DEF_GC_STATUS::Melting));
    PlantRelatedStates.push_back(m_pGC_STATUS->getStatusNo(Plant,DEF_GC_STATUS::Tapping));
    
    // heat in production means in addition that TREATEND_ACT is not set ( == NULL )
    if ( m_pPD_HEAT_DATA->select(HeatID, TreatID, Plant) )
    {
      for (int i = 1; i<=m_pPD_HEAT_DATA->getLastRow(); i++)
      {
        if ( m_pPD_HEAT_PLANT_REF->isHandledAtPlant(m_pPD_HEAT_DATA->getHEATID(i), m_pPD_HEAT_DATA->getPLANT(i), PlantRelatedStates) )
        {
          log("Heat " + m_pPD_HEAT_DATA->getHEATID(i) + " is still in production ",3);

          OrderID = m_pPD_HEAT_DATA->getPRODORDERID_ACT(i);

          RetValue = true;
          break;
        }
        else
        {
          log("Heat " + m_pPD_HEAT_DATA->getHEATID(i) + " is NOT longer in production ",2);
        }
      }

      if ( !RetValue )
      {
        std::string HeatID_Cust;
        std::string TreatID_Cust;

        getCustData(HeatID, TreatID, Plant, HeatID_Cust, TreatID_Cust);

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_HeatNotInProduction(sMessage,HeatID_Cust.c_str(),TreatID_Cust.c_str(),Plant.c_str());
      }

    }
    else
    {
      log("Heat not selected at database, heat is out of production or not known! ",2);
    }
  }
  
  return RetValue;
}
