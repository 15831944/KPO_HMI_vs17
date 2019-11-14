// Copyright (C) 2004 SMS Demag AG, Germany

#include "iEventMessages_s.hh"
#include "CDM_LFTask.h"
#include "CEventMessage.h"
#include "CDM_LFPhaseChangeController.h"


CDM_LFPhaseChangeController::~CDM_LFPhaseChangeController()
{
  // ToDo: Add your specialized code here and/or call the base class
}

CDM_LFPhaseChangeController::CDM_LFPhaseChangeController()
{
  init();
}

void CDM_LFPhaseChangeController::init()
{
  // Rules for transitions from "UndefinedPhase"
  // target phase "Preparation"
  createTransitionRule("UndefinedPhase", LF_EvMsg::evLFHeatAnnouncement, "Preparation");

  // Rules for transitions from "Preparation"
  // target phase "Adjusting"
  createTransitionRule("Preparation", LF_EvMsg::evLFInitialHeating, "Adjusting");
  createTransitionRule("Preparation", LF_EvMsg::evLFPowerOn, "Adjusting");
  createTransitionRule("Preparation", LF_EvMsg::evLFMainHeating, "Adjusting");
  createTransitionRule("Preparation", LF_EvMsg::evLFSteelSampleTaken, "Adjusting");
  createTransitionRule("Preparation", LF_EvMsg::evLFAlloyingMaterialDischarged, "Adjusting");
  createTransitionRule("Preparation", LF_EvMsg::evLFTempMeasurement, "Adjusting");
  createTransitionRule("Preparation", LF_EvMsg::evLFCeloxMeasurement, "Adjusting");


  // target phase "Departed"
  createTransitionRule("Preparation", LF_EvMsg::evLFHeatDeparture, "Departed");
  // target phase "UndefinedPhase"
  createTransitionRule("Preparation", LF_EvMsg::evLFHeatCancellation, "UndefinedPhase");
  // target phase "CleanStirring"
  createTransitionRule("Preparation", LF_EvMsg::evLFCleanlinessStirring, "CleanStirring");


  // Rules for transitions from "Adjusting"
  // target phase "CleanStirring"
  createTransitionRule("Adjusting", LF_EvMsg::evLFCleanlinessStirring, "CleanStirring");
  // target phase "Departed"
  createTransitionRule("Adjusting", LF_EvMsg::evLFHeatDeparture, "Departed");
  // target phase "UndefinedPhase"
  createTransitionRule("Adjusting", LF_EvMsg::evLFHeatCancellation, "UndefinedPhase");


  // Rules for transitions from "CleanStirring"
  // target phase "Departed"
  createTransitionRule("CleanStirring", LF_EvMsg::evLFHeatDeparture, "Departed");
  // target phase "UndefinedPhase"
  createTransitionRule("CleanStirring", LF_EvMsg::evLFHeatCancellation, "UndefinedPhase");
}

void CDM_LFPhaseChangeController::log(const std::string& Message, long Level)
{
  CDM_LFTask::getInstance()->log(Message, Level);
}



bool CDM_LFPhaseChangeController::handleEvent(CEventMessage& evMessage)
{
  bool RetValue = false;
  std::string ProductID = evMessage.getProductID();
  std::string Message   = evMessage.getMessage();
  std::string ActualPhase;
  std::string EventTriggeredPhase;
  std::string NewPhase;

  std::map<std::string,std::string>::const_iterator It = m_ActualPhase.find(ProductID);

  if (It ==  m_ActualPhase.end())
  {
    ActualPhase = "UndefinedPhase";
    m_ActualPhase.insert(std::pair<std::string,std::string>(ProductID, ActualPhase));
  }
  else
    ActualPhase = It->second;


  std::string ActualRule = ActualPhase + Message;

  It = m_TransitionRules.find(ActualRule);

  if (It != m_TransitionRules.end()) // Current phase and actual event lead to an phase change
  {
    EventTriggeredPhase = It->second;
  }

  // check if phase change is overwritten due to DM values or measurements.
  std::string ForcedPhase(EventTriggeredPhase);
  std::stringstream str;

  if (performForcedPhaseChange(ForcedPhase))
  {
    // Value of event triggered EventTriggeredPhase was changed by DM
    str << "Event triggered phase change to " << EventTriggeredPhase << " was overridden by DM for product: " <<  ProductID
        << ", new phase: " << ForcedPhase;

    NewPhase = ForcedPhase;
    log(str.str(), 1);
  }
  else
  {
    // Event trigerred phase change only
    str << "Event triggered phase change to " << EventTriggeredPhase << " for product: " <<  ProductID;

    NewPhase = EventTriggeredPhase;
    log(str.str(), 1);
  }

  m_ActualPhase[ProductID] = ForcedPhase;

  if ( ActualPhase != NewPhase)
  {
    // Update variable in DM
    m_ActualPhase[ProductID] = NewPhase;
    RetValue = true;
  }
	return RetValue;
}


bool CDM_LFPhaseChangeController::performForcedPhaseChange(std::string& EventTriggeredPhase)
{
  log("CDM_LFPhaseChangeController::performeForcedPhaseChange not yet implemented!", 9);
  // return true if argument EventTriggeredPhase for the product was update
	return false;
}

