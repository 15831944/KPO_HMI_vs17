// Copyright (C) 2004 SMS Demag AG

#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"
#include "CSMC_EventLogFrame.h"
#include "CSMC_EventLogFrameController.h"
#include "CTrackingObject.h"
#include "CProductState.h"
#include "CEventMessage.h"
#include "CEventMessageCtrl.h"
#include "CTSM_HMD_PhaseChangeAction.h"

#include "CTSM_HMD_Task.h"

//##ModelId=45A21E8E0024
std::string CTSM_HMD_PhaseChangeAction::relatedEventName("TSM_HMD_TRACK_PHASE");

//##ModelId=45A21E8E002F
void CTSM_HMD_PhaseChangeAction::execute(CTrackingObject* pObjectForAction)
{
  std::map<std::string, std::string>::const_iterator It;

  std::string actPhase = pObjectForAction->getProcessStatus();
  std::string productID= CEventMessage::getOriginalProductID(pObjectForAction->getObjectID());
  std::string msg = CEventMessageCtrl::getEventMessage().getMessage();

  std::string previousPhase;
  It = CTSM_HMD_PhaseChangeAction::PreviousStates.find(productID);
  if (It == CTSM_HMD_PhaseChangeAction::PreviousStates.end())
  {
    // We don't like to see a phase like INITIAL_PRODUCT_STATE in
    // the DM, so update the container for the next change only and terminate
    CTSM_HMD_PhaseChangeAction::PreviousStates[productID] = actPhase;
    return;
  }
  else
    previousPhase = It->second;

  CTSM_HMD_PhaseChangeAction::PreviousStates[productID] = actPhase;

	CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_StateTransition(sMessage,"Phase",previousPhase.c_str(),actPhase.c_str(),productID.c_str(),msg.c_str());

  std::string ServerDM = "DM_HMD";
  // Replace DM_HMD with specific DM (DM_HMD_1,...) if available
  cCBS_StdInitBase::getInstance()->replaceWithEntry("DataManager", "ServerName", ServerDM);

  DM::iDM_Interface_var m_pDM_Interface = CTSM_HMD_Task::getInstance()->getpDM_Interface(ServerDM, DM::PRODUCT);
  if (m_pDM_Interface)
  {
    m_pDM_Interface->setString(productID.c_str(), DATA::PhaseAct, actPhase.c_str());
    m_pDM_Interface->setDouble(productID.c_str(), DATA::PhaseLimeAmount, 0.0);
    m_pDM_Interface->setDouble(productID.c_str(), DATA::PhaseCarbAmount, 0.0);
    m_pDM_Interface->setDouble(productID.c_str(), DATA::PhaseMagnAmount, 0.0);
  }
}

//##ModelId=45A21E8E0010
CTSM_HMD_PhaseChangeAction::~CTSM_HMD_PhaseChangeAction()
{
}

//##ModelId=45A21E8E001A
CTSM_HMD_PhaseChangeAction::CTSM_HMD_PhaseChangeAction()
{
}

