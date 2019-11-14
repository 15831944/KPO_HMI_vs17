// Copyright (C) 2007 SMS Demag AG

#include "iEventMessages_s.hh"
#include "cCBS_StdInitBase.h"
#include "CEventMessage.h"

#include "CARCHIVER_LFEventHandler.h"

//##ModelId=41A4A2B102E5
CARCHIVER_LFEventHandler::CARCHIVER_LFEventHandler(CARCHIVER_Task *Task)
:CARCHIVER_EventHandler(Task)
{
  m_MaterialHandlingWrapper.setTaskAndInitDBClasses(Task);
  m_SignalsAndMeasurementWrapper.setTaskAndInitDBClasses(Task);
  m_TreatmentWrapper.setTaskAndInitDBClasses(Task);
  m_AnalysisDataWrapper.setTaskAndInitDBClasses(Task);
  m_ComputerModeWrapper.setTaskAndInitDBClasses(Task);
  m_ModelResultWrapper.setTaskAndInitDBClasses(Task);
  m_DelayWrapper.setTaskAndInitDBClasses(Task);
}

//##ModelId=41A4A2B102DA
CARCHIVER_LFEventHandler::~CARCHIVER_LFEventHandler()
{
}

//##ModelId=42B04BDE022E
bool CARCHIVER_LFEventHandler::handleEvent(CEventMessage& Event)
{
  bool RetValue = true;
  std::string Message = Event.getMessage();

  if (Message == LF_EvMsg::evLFModelResultActualSetpoints  ||
      Message == LF_EvMsg::evLFModelResultActualSetpointsOffline )
  {
    m_ModelResultWrapper.doOnActualSetpoints(Event);
  }	
  else if (Message == LF_EvMsg::evLFModelResultRecipeSetpoints  ||
           Message == LF_EvMsg::evLFModelResultRecipeSetpointsOffline )
  {
    m_ModelResultWrapper.doOnActualSetpoints(Event);
    m_ModelResultWrapper.doOnRecipeSetpoints(Event);
  }
  else if (Message == LF_EvMsg::evLFCyclicMeasurement )
  {
    m_SignalsAndMeasurementWrapper.doOnCyclicMeasurement(Event);
  }
  else if (Message == LF_EvMsg::evLFMaterialHandlingReport)
  {
    // function moved to tracking 
    // m_MaterialHandlingWrapper.doOnMaterialHandlingReport(Event);
  }
  else if (Message == LF_EvMsg::evLFLiqMatHandlReport)
  {
    m_MaterialHandlingWrapper.doOnLiqMatHandlingReport(Event);
  }
  else if (Message == LF_EvMsg::evLFSteelSampleTaken )
  {
    m_AnalysisDataWrapper.doOnSampleTaken(Event);
  }
  else if (Message == LF_EvMsg::evLFSlagSampleTaken)
  {
    m_AnalysisDataWrapper.doOnSampleTaken(Event);
  }
  else if (Message == LF_EvMsg::evLFSetComputerMode)
  {
    m_ComputerModeWrapper.doOnSetComputerMode(Event);
  }
  else if (Message == LF_EvMsg::evLFHeatStart)
  {
    m_TreatmentWrapper.doOnHeatStart(Event);
  }
  else if (Message == LF_EvMsg::evLFUpdateAimTemperature)
  {
    m_TreatmentWrapper.doOnUpdateAimTemperature(Event);
  }  
  else if (Message == LF_EvMsg::evLFUpdateAimDepartureTime)
  {
    m_TreatmentWrapper.doOnUpdateAimDepartureTime(Event);
  }
  else if (Message == LF_EvMsg::evLFHeatAnnounceStatus||
    Message == LF_EvMsg::evLFHeatAnnounceStatusOffline )
  {
    m_TreatmentWrapper.doOnHeatAnnounceStatus(Event);
  }
  else if (Message == LF_EvMsg::evLFBottomStirringStart )
  {
    m_SignalsAndMeasurementWrapper.doOnStirringStartEnd(Event, DEF_GEN_STATES::On);
  }
  else if (Message == LF_EvMsg::evLFBottomStirringEnd )
  {
    m_SignalsAndMeasurementWrapper.doOnStirringStartEnd(Event, DEF_GEN_STATES::Off);
  }
  else if (Message == LF_EvMsg::evLFBottomStirringByPassOn )
  {
    m_SignalsAndMeasurementWrapper.doOnStirringBypassOnOff(Event, DEF_GEN_STATES::On);
  }
  else if (Message == LF_EvMsg::evLFBottomStirringByPassOff )
  {
    m_SignalsAndMeasurementWrapper.doOnStirringBypassOnOff(Event, DEF_GEN_STATES::Off);
  }
  else if (Message == LF_EvMsg::evLFFinalHeating    ||
    Message == LF_EvMsg::evLFInitialHeating  ||
    Message == LF_EvMsg::evLFMainHeating     ||
    Message == LF_EvMsg::evLFTemperatureHold )
  {
    m_SignalsAndMeasurementWrapper.doOnHeating(Event);
  }
  else if (Message == LF_EvMsg::evLFEmergencyLanceStirringStart )
  {
    m_SignalsAndMeasurementWrapper.doOnEmergencyLanceStirring(Event, DEF_GEN_STATES::On);
  }
  else if (Message == LF_EvMsg::evLFEmergencyLanceStirringEnd )
  {
    m_SignalsAndMeasurementWrapper.doOnEmergencyLanceStirring(Event, DEF_GEN_STATES::Off);
  }
  else if (Message == LF_EvMsg::evLFTempMeasurement ||
           Message == LF_EvMsg::evLFCeloxMeasurement)
  {
    m_SignalsAndMeasurementWrapper.doOnTempMeasurement(Event);
  }
  else if (Message == LF_EvMsg::evLFElectrodesInOperatingPosition)
  {
    m_SignalsAndMeasurementWrapper.doOnElectrodesInOperatingPosition(Event);
  }
  else if (Message == LF_EvMsg::evLFElectrodesOutOperatingPosition)
  {
    m_SignalsAndMeasurementWrapper.doOnElectrodesInOperatingPosition(Event);
  }
  else if (Message == LF_EvMsg::evLFFurnaceBreakerOn)
  {
    m_SignalsAndMeasurementWrapper.doOnFurnaceBreaker(Event, DEF_GEN_STATES::On);
  }
  else if (Message == LF_EvMsg::evLFFurnaceBreakerOff)
  {
    m_SignalsAndMeasurementWrapper.doOnFurnaceBreaker(Event, DEF_GEN_STATES::Off);
  }
  else if (Message == LF_EvMsg::evLFPowerOn)
  {
    m_SignalsAndMeasurementWrapper.doOnPower(Event,DEF_GEN_STATES::On);
  }
  else if (Message == LF_EvMsg::evLFPowerOff)
  {
    m_SignalsAndMeasurementWrapper.doOnPower(Event, DEF_GEN_STATES::Off);
  }
  else if (Message == LF_EvMsg::evLFTapChangeStart)
  {
    m_SignalsAndMeasurementWrapper.doOnTapChange(Event, DEF_GEN_STATES::On);
  }
  else if (Message == LF_EvMsg::evLFTapChangeFinished)
  {
    m_SignalsAndMeasurementWrapper.doOnTapChange(Event, DEF_GEN_STATES::Off);
  }
  else if (Message == LF_EvMsg::evLFImpCurveChanged)
  {
    m_SignalsAndMeasurementWrapper.doOnTapChange(Event, DEF_GEN_STATES::Off);
  }
  else if (Message == LF_EvMsg::evLFPhaseReport)
  {
    RetValue = m_TreatmentWrapper.doPhaseReport(Event); 
  }
  else if (Message == LF_EvMsg::evLFRoofArrivesInUpPosition    ||
           Message == LF_EvMsg::evLFRoofArrivesInDownPosition  ||
           Message == LF_EvMsg::evLFGantrySwungIn              ||
           Message == LF_EvMsg::evLFGantrySwungOut           )
  {
    m_SignalsAndMeasurementWrapper.doOnMechanicalSystem(Event);
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
