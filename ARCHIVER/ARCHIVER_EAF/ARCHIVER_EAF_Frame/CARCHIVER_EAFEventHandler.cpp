// Copyright (C) 2011 SMS Siemag AG
#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"
#include "cCBS_StdInitBase.h"
#include "CEventMessage.h"

#include "CARCHIVER_EAFEventHandler.h"

//##ModelId=419B7BD6000A
CARCHIVER_EAFEventHandler::CARCHIVER_EAFEventHandler(CARCHIVER_Task *Task)
:CARCHIVER_EventHandler(Task)
{
  this->m_MaterialHandlingWrapper.setTaskAndInitDBClasses(Task);
  this->m_ModelResultWrapper.setTaskAndInitDBClasses(Task);
  this->m_SignalsAndMeasurementWrapper.setTaskAndInitDBClasses(Task);
  this->m_TreatmentManagementWrapper.setTaskAndInitDBClasses(Task);
  this->m_AnalysisDataWrapper.setTaskAndInitDBClasses(Task);
  this->m_ComputerModesAndAvailabilityWrapper.setTaskAndInitDBClasses(Task);
  this->m_DelayWrapper.setTaskAndInitDBClasses(Task);
}

//##ModelId=419B7BD403E7
CARCHIVER_EAFEventHandler::~CARCHIVER_EAFEventHandler()
{
}

//##ModelId=4152996E0321
bool CARCHIVER_EAFEventHandler::handleEvent(CEventMessage& Event)
{
  bool RetValue = true;

  std::string ActMessage = Event.getMessage();

  if ( ActMessage == EAF_EvMsg::evEAFModelResultActualSetpoints || 
       ActMessage == EAF_EvMsg::evEAFModelResultActualSetpointsOffline ) 
  {
    m_ModelResultWrapper.doOnActualSetpoints(Event);
  }
  else if (ActMessage == EAF_EvMsg::evEAFModelResultRecipeSetpoints || 
           ActMessage == EAF_EvMsg::evEAFModelResultRecipeSetpointsOffline )
  {
    m_ModelResultWrapper.doOnActualSetpoints(Event);
    m_ModelResultWrapper.doOnRecipeSetpoints(Event); 
  }
  else if (ActMessage == EAF_EvMsg::evEAFCyclicMeasurement )
  {
    m_SignalsAndMeasurementWrapper.doOnCyclicMeasurement(Event);
  }
  else if (ActMessage == EAF_EvMsg::evEAFDeslaggingStart)
  {
    m_SignalsAndMeasurementWrapper.doOnDeslagging(Event, DEF_GEN_STATES::Start);
  }
  else if (ActMessage == EAF_EvMsg::evEAFDeslaggingEnd)
  {
    m_SignalsAndMeasurementWrapper.doOnDeslagging(Event, DEF_GEN_STATES::Stop);
  }
  else if(ActMessage == EAF_EvMsg::evEAFMaterialHandlingReport)
  {
    // function moved to tracking 
    // m_MaterialHandlingWrapper.doOnMaterialHandlingReport(Event);
  }
  else if(ActMessage == EAF_EvMsg::evEAFLiqMatHandlReport)
  {
    m_MaterialHandlingWrapper.doOnLiqMatHandlingReport(Event);
  }
  else if(ActMessage == EAF_EvMsg::evEAFSteelSampleTaken)
  {
    m_AnalysisDataWrapper.doOnSampleTaken(Event, true); 
  }
  else if(ActMessage == EAF_EvMsg::evEAFSlagSampleTaken)
  {
    m_AnalysisDataWrapper.doOnSampleTaken(Event, false); 
  }
  else if(ActMessage == EAF_EvMsg::evEAFTempMeasurement ||
          ActMessage == EAF_EvMsg::evEAFCeloxMeasurement)
  {
    m_SignalsAndMeasurementWrapper.doOnTempMeasurement(Event); 
  }
  else if(ActMessage == EAF_EvMsg::evEAFElectrodesInOperatingPosition)
  {
    m_SignalsAndMeasurementWrapper.doOnElectrodesInOperatingPosition(Event); 
  }
  else if(ActMessage == EAF_EvMsg::evEAFElectrodesOutOperatingPosition)
  {
    m_SignalsAndMeasurementWrapper.doOnElectrodesInOperatingPosition(Event); 
  }
  // do on FurnaceBreaker
  else if (ActMessage == EAF_EvMsg::evEAFFurnaceBreakerOff)
  {
    m_SignalsAndMeasurementWrapper.doOnFurnaceBreaker(Event,DEF_GEN_STATES::Off);
  }
  else if (ActMessage == EAF_EvMsg::evEAFFurnaceBreakerOn)
  {
    m_SignalsAndMeasurementWrapper.doOnFurnaceBreaker(Event,DEF_GEN_STATES::On);               
  }

  // do on Power    
  else if (ActMessage == EAF_EvMsg::evEAFPowerOff)
  {
    m_SignalsAndMeasurementWrapper.doOnPower(Event,DEF_GEN_STATES::Off);          
  }
  else if (ActMessage == EAF_EvMsg::evEAFPowerOn)
  {
    m_SignalsAndMeasurementWrapper.doOnPower(Event,DEF_GEN_STATES::On);                         
  }  
  // do on TapChange    
  else if (ActMessage == EAF_EvMsg::evEAFTapChangeStart )
  {
    m_SignalsAndMeasurementWrapper.doOnTapChange(Event, DEF_GEN_STATES::On);                     
  }
  else if (ActMessage == EAF_EvMsg::evEAFTapChangeFinished)
  {
    m_SignalsAndMeasurementWrapper.doOnTapChange(Event, DEF_GEN_STATES::Off);                     
  }
  // do on Heat Start   
  else if ( ActMessage == EAF_EvMsg::evEAFHeatStart)
  {
    m_TreatmentManagementWrapper.doOnHeatStart(Event);  
  }
  // do on computer mode on / off
  else if (ActMessage == EAF_EvMsg::evEAFSetComputerMode)
  {
    m_ComputerModesAndAvailabilityWrapper.doOnSetComputerMode(Event);
  }
  else if (ActMessage == EAF_EvMsg::evEAFManipInjectLanceStart)
  {
    m_SignalsAndMeasurementWrapper.doOnManipInjectLanceStart(Event);
  }
  else if (ActMessage == EAF_EvMsg::evEAFManipInjectLanceStop)
  {
    m_SignalsAndMeasurementWrapper.doOnManipInjectLanceStop(Event);
  }
  else if (ActMessage == EAF_EvMsg::evEAFManipGasLanceStart)
  {
    m_SignalsAndMeasurementWrapper.doOnManipGasLanceStart(Event);
  }
  else if (ActMessage == EAF_EvMsg::evEAFManipGasLanceStop)
  {
    m_SignalsAndMeasurementWrapper.doOnManipGasLanceStop(Event);
  }  
  else if (ActMessage == EAF_EvMsg::evEAFBurnerStart)
  {
    m_SignalsAndMeasurementWrapper.doOnBurnerStart(Event);
  }
  else if (ActMessage == EAF_EvMsg::evEAFBurnerStop)
  {
    m_SignalsAndMeasurementWrapper.doOnBurnerStop(Event);
  }
  else if (ActMessage == EAF_EvMsg::evEAFBottomStirringStart)
  {
    m_SignalsAndMeasurementWrapper.doOnStirrStatusData(Event,DEF_GEN_STATES::On);
  }
  else if (ActMessage == EAF_EvMsg::evEAFBottomStirringEnd)
  {
    m_SignalsAndMeasurementWrapper.doOnStirrStatusData(Event,DEF_GEN_STATES::Off);
  }
  else if (ActMessage == EAF_EvMsg::evEAFPhaseChange)
  {
    m_TreatmentManagementWrapper.doPhaseReport(Event);
  }
  else if (ActMessage == EAF_EvMsg::evEAFDoorClosed                 || 
           ActMessage == EAF_EvMsg::evEAFDoorOpened                 ||
           ActMessage == EAF_EvMsg::evEAFRoofArrivesInUpPosition    ||
           ActMessage == EAF_EvMsg::evEAFRoofArrivesInDownPosition  ||
           ActMessage == EAF_EvMsg::evEAFGantrySwungIn              ||
           ActMessage == EAF_EvMsg::evEAFGantrySwungOut           )
  {
    m_SignalsAndMeasurementWrapper.doOnMechanicalSystem(Event);
    m_MaterialHandlingWrapper.doBasketDischarge(Event);
  }

  else
  {
    RetValue = false; // The event is for this handler, but the handler doesn't have a do-method
  }

  if ( RetValue )
  {
    log(Event,3);
  }

  return RetValue;
}
