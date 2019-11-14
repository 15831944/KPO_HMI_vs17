// Copyright (C) 2007 SMS Demag AG

#include "CTSM_HMD_PhaseChangeAction.h"
#include "CTSM_HMD_SendEventAction.h"
#include "CTSM_HMD_StateMachineConstructCtrl.h"

//##ModelId=45A21E8D0310
CTSM_HMD_StateMachineConstructCtrl::CTSM_HMD_StateMachineConstructCtrl()
{
  CActionRegistration<CTSM_HMD_PhaseChangeAction>();
}

//##ModelId=45A21E8D02C1
IAction* CTSM_HMD_StateMachineConstructCtrl::createSendProductMessageAction(const std::string & eventMessageString, const std::string & eventReceiverName, long timeOffsetSeconds) const
{
  return new CTSM_HMD_SendEventAction(m_EventSenderName, eventReceiverName, eventMessageString, false, timeOffsetSeconds);
}

