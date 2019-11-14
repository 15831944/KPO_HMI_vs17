// Copyright (C) 2003 SMS Demag AG

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
#include "CGC_STATUS.h"
#include "CPD_HEAT_PLANT_REF.h"
#include "CPD_HEAT_DATA.h"

#include "CIntfData.h"
#include "CProductID.h"
#include "CDataConversion.h"
#include "CDM_LFPlantManager.h"
#include "CDM_LFProductManager.h"

#include "CDM_LFSignalsAndMeasurementsEventHandler.h"
#include "CDM_LFTreatmentManagementEventHandler.h"
#include "CDM_LFAnalysisEventHandler.h"
#include "CDM_LFMaterialEventHandler.h"
#include "CDM_LFModesAndAvailabilitiesEventHandler.h"
#include "CDM_LFPurposeEventHandler.h"
#include "CDM_LFModelResultEventHandler.h"

#include "CDM_LFEventHandler.h"

#include "CDM_LFEventLogHandlerAnalysis.h"
#include "CDM_LFEventLogHandlerMaterial.h"
#include "CDM_LFEventLogHandlerModelResults.h"
#include "CDM_LFEventLogHandlerModesAndAvailabilities.h"
#include "CDM_LFEventLogHandlerPurpose.h"
#include "CDM_LFEventLogHandlerSignalsAndMeasurements.h"
#include "CDM_LFEventLogHandlerTreatmentManagement.h"

#include "CPDL_HEAT_DATA.h"
#include "CGC_Plant_Container.h"

#include "CDM_LFTask.h"

CDM_LFTask::CDM_LFTask()
{
}

CDM_LFTask::~CDM_LFTask()
{
}


 CDM_LFTask* CDM_LFTask::getInstance()
{
	if ( m_Instance == 0 )
	{
		m_Instance = new CDM_LFTask( );
	}
	return m_Instance;
}


CDM_LFTask* CDM_LFTask::m_Instance = 0;


bool CDM_LFTask::initialize()
{
	bool RetCode = true;

  // must be called first 
  RetCode = CDM_Task::initialize();

  // N2, Ar
  m_GasDataList.push_back(DEF_GAS::N2);
  m_GasDataList.push_back(DEF_GAS::Ar);

  m_pPlantManager             = new CDM_LFPlantManager();
  m_pProductManager           = new CDM_LFProductManager();

  initManager();

  m_pProductManagementInterface->setpDM_Task(this);

  return RetCode;
}


void CDM_LFTask::registerEventHandlers()
{
  cCBS_StdEvent_Task* pEventTask = cCBS_StdEvent_Task::getInstance();

  // register event handler classes
  CDM_EventHandler * EventHandler = 0;
  EventHandler = new CDM_LFTreatmentManagementEventHandler();
  pEventTask->registerEventHandler(EventHandler);

  EventHandler = new CDM_LFSignalsAndMeasurementsEventHandler();
  pEventTask->registerEventHandler(EventHandler);

  EventHandler = new CDM_LFAnalysisEventHandler();
  pEventTask->registerEventHandler(EventHandler);

  EventHandler = new CDM_LFMaterialEventHandler();
  pEventTask->registerEventHandler(EventHandler);

  EventHandler = new CDM_LFModesAndAvailabilitiesEventHandler();
  pEventTask->registerEventHandler(EventHandler);

  EventHandler = new CDM_LFPurposeEventHandler();
  pEventTask->registerEventHandler(EventHandler);

  EventHandler = new CDM_LFModelResultEventHandler();
  pEventTask->registerEventHandler(EventHandler);
}


void CDM_LFTask::registerEventLogHandlers()
{
  CDM_LFEventLogHandler * pEventLogHandler;

  pEventLogHandler = new CDM_LFEventLogHandlerAnalysis();
  registerEventLogHandler(pEventLogHandler);

  pEventLogHandler = new CDM_LFEventLogHandlerMaterial();
  registerEventLogHandler(pEventLogHandler);

  pEventLogHandler = new CDM_LFEventLogHandlerModelResults();
  registerEventLogHandler(pEventLogHandler);

  pEventLogHandler = new CDM_LFEventLogHandlerModesAndAvailabilities();
  registerEventLogHandler(pEventLogHandler);

  pEventLogHandler = new CDM_LFEventLogHandlerPurpose();
  registerEventLogHandler(pEventLogHandler);

  pEventLogHandler = new CDM_LFEventLogHandlerSignalsAndMeasurements();
  registerEventLogHandler(pEventLogHandler);

  pEventLogHandler = new CDM_LFEventLogHandlerTreatmentManagement();
  registerEventLogHandler(pEventLogHandler);

}



std::string CDM_LFTask::getProcessState(const std::string& ID)
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


void CDM_LFTask::sendInitialEvents()
{
  CEventMessage Message;

  std::string PlantID = DEF_SUBSYSTEMS::LF;
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
    Message.setMessage(LF_EvMsg::evLFPlantStatusRequest);
    Message.dispatch(SenderName,DestinationList);
    Message.setMessage(LF_EvMsg::evLFRequestMatAvail);
    Message.dispatch(SenderName,DestinationList);
  }
}

bool CDM_LFTask::setProductData(CEventMessage& Event)
{
  bool RetValue = false;
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();

  if (CDM_Task::setProductData(Event))
  {
    std::string Plant = m_pGC_Plant_Container->getPlant(PlantID);
    long PlantNo      = m_pGC_Plant_Container->getPlantNo(PlantID);

    cCBS_StdConnection * pConnection = getStdConnection();
    
    CPDL_HEAT_DATA PDL_HEAT_DATA(pConnection);

    if (PDL_HEAT_DATA.select(HeatID, TreatID, Plant))
    {
      long CarNo = PDL_HEAT_DATA.getCARNO(1);

      if ( m_pProductManager )
      {
        RetValue = m_pProductManager->setProductData(ProductID, CarNo);
      }
    }
  }

  return RetValue;
}

bool CDM_LFTask::isProductInProduction(const std::string& HeatID, const std::string& TreatID, const std::string& PlantID, std::string& OrderID)
{
  bool RetValue = false;

  if (m_pPD_HEAT_DATA && m_pPD_HEAT_PLANT_REF && m_pGC_Plant_Container && m_pGC_STATUS)
  {
    // first seperate Plant and PlantNo from PlantID
    std::string Plant = m_pGC_Plant_Container->getPlant(PlantID);
    long PlantNo      = m_pGC_Plant_Container->getPlantNo(PlantID);

    std::string Message;

    Message += "CDM_LFTask::isProductInProduction";
    Message += " checking " + HeatID + " " + TreatID + " " + PlantID;

    log(Message,3);

    std::vector<long> PlantRelatedStates;
    PlantRelatedStates.push_back(m_pGC_STATUS->getStatusNo(Plant,DEF_GC_STATUS::HeatAnnounced));
    PlantRelatedStates.push_back(m_pGC_STATUS->getStatusNo(Plant,DEF_GC_STATUS::TreatmentStart));
    
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
