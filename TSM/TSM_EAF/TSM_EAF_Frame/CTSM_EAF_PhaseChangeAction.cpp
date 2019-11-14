// Copyright (C) 2004 SMS Demag AG

#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"
#include "CSMC_EventLogFrame.h"
#include "CSMC_EventLogFrameController.h"
#include "CTrackingObject.h"
#include "CProductState.h"
#include "CEventMessage.h"
#include "CEventMessageCtrl.h"
#include "CTSM_EAF_Task.h"

#include "CTSM_EAF_PhaseChangeAction.h"

std::string CTSM_EAF_PhaseChangeAction::relatedEventName("TSM_EAF_TRACK_PHASE");

void CTSM_EAF_PhaseChangeAction::execute(CTrackingObject* pObjectForAction)
{
  std::map<std::string, std::string>::const_iterator It;

  std::string actPhase = pObjectForAction->getProcessStatus();
  std::string productID= CEventMessage::getOriginalProductID(pObjectForAction->getObjectID());
  std::string msg = CEventMessageCtrl::getEventMessage().getMessage();

  std::string previousPhase;
  It = CTSM_EAF_PhaseChangeAction::PreviousStates.find(productID);
  if (It == CTSM_EAF_PhaseChangeAction::PreviousStates.end())
  {
    // We don't like to see a phase like INITIAL_PRODUCT_STATE in
    // the DM, so update the container for the next change only and terminate
    CTSM_EAF_PhaseChangeAction::PreviousStates[productID] = actPhase;
    return;
  }
  else
    previousPhase = It->second;

  CTSM_EAF_PhaseChangeAction::PreviousStates[productID] = actPhase;

	CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  sMessage.severity = c_e_info;
  pEventLog->EL_StateTransition(sMessage,"Phase",previousPhase.c_str(),actPhase.c_str(),productID.c_str(),msg.c_str());

  std::string ServerDM = "DM_EAF";
  // Replace DM_LF with specific DM (DM_LF_1,...) if available
  cCBS_StdInitBase::getInstance()->replaceWithEntry("DataManager", "ServerName", ServerDM);

  DM::iDM_Interface_var m_pDM_Interface = CTSM_EAF_Task::getInstance()->getpDM_Interface(ServerDM, DM::PRODUCT);

  if (m_pDM_Interface) 
  {
    std::string PrevPhaseTracker = m_pDM_Interface->getString(productID.c_str(), DATA::PhaseTracker);
    long PrevPhaseNoTracker      = m_pDM_Interface->getLong(productID.c_str()  , DATA::PhaseNoTracker);

    if ( PrevPhaseTracker == actPhase )
    {
      PrevPhaseNoTracker++;
    }
    else
    {
      if ( "MeltBskNo:" == actPhase ||  "HeatLiqChgNo:" == actPhase || "BskAndLiqChgNo:" == actPhase )
      {
        PrevPhaseNoTracker = 1;
      }
      else
      {
        PrevPhaseNoTracker = 0;
      }
    }

    m_pDM_Interface->setString(productID.c_str(), DATA::PhaseTracker  , actPhase.c_str());
    m_pDM_Interface->setLong  (productID.c_str(), DATA::PhaseNoTracker, PrevPhaseNoTracker);

    double ElecCons           = m_pDM_Interface->getDouble(productID.c_str(), DATA::ElecCons);

    m_pDM_Interface->setDouble(productID.c_str(), DATA::ElecConsPhaseStart, ElecCons);
    m_pDM_Interface->setDouble(productID.c_str(), DATA::ElecConsPhase      ,0.0);

    CEventMessage actualMessage = CEventMessageCtrl::getEventMessage();

    // Call event directly using the application
    std::string SenderName = actualMessage.getSender();
    std::string TaskName   = CTSM_EAF_Task::getInstance()->getTaskName();

    std::vector<std::string> DestinationList;
    cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"SenderName",SenderName);
    cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"DestinationName", DestinationList);

    actualMessage.setMessage(EAF_EvMsg::evEAFPhaseChange);

    actualMessage.dispatch(SenderName,DestinationList);
  }
}

CTSM_EAF_PhaseChangeAction::~CTSM_EAF_PhaseChangeAction()
{
}

CTSM_EAF_PhaseChangeAction::CTSM_EAF_PhaseChangeAction()
{
}

