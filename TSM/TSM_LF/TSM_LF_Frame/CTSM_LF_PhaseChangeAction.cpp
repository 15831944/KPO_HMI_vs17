// Copyright (C) 2004 SMS Demag AG

#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"
#include "CSMC_EventLogFrame.h"
#include "CSMC_EventLogFrameController.h"
#include "CTrackingObject.h"
#include "CProductState.h"
#include "CEventMessage.h"
#include "CEventMessageCtrl.h"
#include "CTSM_LF_PhaseChangeAction.h"

#include "CTSM_LF_Task.h"

std::string CTSM_LF_PhaseChangeAction::relatedEventName("TSM_LF_TRACK_PHASE");

void CTSM_LF_PhaseChangeAction::execute(CTrackingObject* pObjectForAction)
{
  std::map<std::string, std::string>::const_iterator It;

  std::string actPhase = pObjectForAction->getProcessStatus();
  std::string productID= CEventMessage::getOriginalProductID(pObjectForAction->getObjectID());
  std::string msg = CEventMessageCtrl::getEventMessage().getMessage();

  std::string previousPhase;
  It = CTSM_LF_PhaseChangeAction::PreviousStates.find(productID);
  if (It == CTSM_LF_PhaseChangeAction::PreviousStates.end())
  {
    // We don't like to see a phase like INITIAL_PRODUCT_STATE in
    // the DM, so update the container for the next change only and terminate
    CTSM_LF_PhaseChangeAction::PreviousStates[productID] = actPhase;
    return;
  }
  else
    previousPhase = It->second;

  CTSM_LF_PhaseChangeAction::PreviousStates[productID] = actPhase;

	CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_StateTransition(sMessage,"Phase",previousPhase.c_str(),actPhase.c_str(),productID.c_str(),msg.c_str());

  std::vector<std::string> EventReceiverNames;
  CTSM_Task::getEventReceiverNames(EventReceiverNames,CEventMessageCtrl::getEventMessage().getSender());

  std::vector<std::string>::iterator it;
  for ( it = EventReceiverNames.begin(); it != EventReceiverNames.end(); ++it)
  {
    // with specific DM (DM_LF_1) if available
    std::string ServerDM = (*it);

    DM::iDM_Interface_var m_pDM_Interface = CTSM_LF_Task::getInstance()->getpDM_Interface(ServerDM, DM::PRODUCT);
    if (m_pDM_Interface)
    {
      m_pDM_Interface->setString(productID.c_str(), DATA::PhaseTracker, actPhase.c_str());
    }
  }
}

CTSM_LF_PhaseChangeAction::~CTSM_LF_PhaseChangeAction()
{
}

CTSM_LF_PhaseChangeAction::CTSM_LF_PhaseChangeAction()
{
}

