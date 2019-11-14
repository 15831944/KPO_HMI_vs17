// Copyright (C) 2011 SMS Demag AG

#include "iEventMessages_s.hh"
#include "cCBS_StdInitBase.h"
#include "CEventMessage.h"
#include "CEventMessageReady.h"

#include "CARCHIVER_HMDEventHandler.h"

CARCHIVER_HMDEventHandler::CARCHIVER_HMDEventHandler(CARCHIVER_Task *Task)
:CARCHIVER_EventHandler(Task)
{
  m_MaterialHandlingWrapper.setTaskAndInitDBClasses(Task);
  m_SignalsAndMeasurementWrapper.setTaskAndInitDBClasses(Task);
  //m_AnalysisDataWrapper.setTaskAndInitDBClasses(Task);
  m_ComputerModeWrapper.setTaskAndInitDBClasses(Task);
  //m_PhaseReportWrapper.setTaskAndInitDBClasses(Task);
  m_TreatmentWrapper.setTaskAndInitDBClasses(Task);

  m_HMIReceiver = "DH_HMI_HMD";
  cCBS_StdInitBase::getInstance()->replaceWithEntry("DH_HMI", "DestinationName", m_HMIReceiver);
}

CARCHIVER_HMDEventHandler::~CARCHIVER_HMDEventHandler()
{
}

bool CARCHIVER_HMDEventHandler::handleEvent(CEventMessage& Event)
{
  bool RetValue = true;
  bool SendToHMI = false;
  std::string Message = Event.getMessage();

  log(Event,3);

  if (Message == HMD_EvMsg::evHMDCyclicMeasurement )
  {
    m_SignalsAndMeasurementWrapper.doOnCyclicMeasurement(Event);
  }
  else if (Message == HMD_EvMsg::evHMDPowderBlowingStart )
  {
    m_MaterialHandlingWrapper.doOnPowderBlowing(Event, true);
  }
  else if (Message == HMD_EvMsg::evHMDPowderBlowingEnd )
  {
    m_MaterialHandlingWrapper.doOnPowderBlowing(Event, false);
  }
  else if (Message == HMD_EvMsg::evHMDHeatDeparture )
  {
    m_TreatmentWrapper.doOnHeatDeparture(Event);
    SendToHMI = true;
  }
  else if (Message == HMD_EvMsg::evHMDSetComputerModeOn ||
           Message == HMD_EvMsg::evHMDSetComputerModeOff )
  {
    m_ComputerModeWrapper.doOnSetComputerMode(Event);
  }
  // (Temporary) deactivated, because the Tracking_HMD is also writing the phase into PD and HD tables.
  // Archiver_HMD is only writing the values into PD tabels.
  // And the handling of copying the PD tables into HD tables at LadleDeparture is still unclear.
  //else if (Message == HMD_EvMsg::evHMDPhasePreparation                ||
  //         Message == HMD_EvMsg::evHMDPhaseMonoInjectionLimeStart     ||
  //         Message == HMD_EvMsg::evHMDPhaseMonoInjectionCarbideStart  ||
  //         Message == HMD_EvMsg::evHMDPhaseMonoInjectionContinued     ||
  //         Message == HMD_EvMsg::evHMDPhaseMonoInjectionLimeEnd       ||
  //         Message == HMD_EvMsg::evHMDPhaseMonoInjectionCarbideEnd    ||
  //         Message == HMD_EvMsg::evHMDPhaseDeslagging)
  //{
  //  m_PhaseReportWrapper.doOnHeatProductionPhaseReport(Event);
  //}
  else if (Message == HMD_EvMsg::evHMDMaterialAvailability)
  {
    m_MaterialHandlingWrapper.doOnMaterialAvailability(Event);
  }
  else
  {
    RetValue = false; // The event is for this handler, but the handler doesn't have a do-method
  }

  log("",3);
  log("----------------------------------------------------------------------------",3);

  if (RetValue)
  {
    CEventMessageReady EventMessageReady(Event);
    if (SendToHMI)
    {
      EventMessageReady.dispatch(EventMessageReady.getSender(),m_HMIReceiver);
    }
  }

  return RetValue;
}
