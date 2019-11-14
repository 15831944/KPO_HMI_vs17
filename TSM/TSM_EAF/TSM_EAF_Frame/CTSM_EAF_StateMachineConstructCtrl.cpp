// Copyright (C) 2004 SMS Demag AG

#include "CTSM_EAF_Task.h"

#include "CTSM_EAF_PhaseChangeAction.h"
#include "CTSM_EAF_SendEventAction.h"
#include "CTSM_EAF_StateMachineConstructCtrl.h"

CTSM_EAF_StateMachineConstructCtrl::CTSM_EAF_StateMachineConstructCtrl()
: CTsmStateMachineConstructCtrl(getConstructionFileName())
{
  m_EventSenderName = getEventSenderName();

  CActionRegistration<CTSM_EAF_PhaseChangeAction>();
}

IAction* CTSM_EAF_StateMachineConstructCtrl::createSendProductMessageAction(const std::string & eventMessageString, const std::string & eventReceiverName, long timeOffsetSeconds) const
{
  return new CTSM_EAF_SendEventAction(m_EventSenderName, eventReceiverName, eventMessageString, false, timeOffsetSeconds);
}

std::string CTSM_EAF_StateMachineConstructCtrl::getConstructionFileName()
{
  std::string constructionFileName;
  std::string TaskName = CTSM_EAF_Task::getInstance()->getTaskName();

  cCBS_StdInitBase *pInitBase = cCBS_StdInitBase::getInstance();

  pInitBase->replaceWithEntry("PATH", "ConstructionFileName", constructionFileName);

  pInitBase->replaceWithEntry(TaskName, "ConstructionFileName", constructionFileName);

  return pInitBase->getXPACT_SMC() + constructionFileName;
}

std::string CTSM_EAF_StateMachineConstructCtrl::getEventSenderName()
{
  std::string tmp;
  std::string TaskName = CTSM_EAF_Task::getInstance()->getTaskName();

  cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage", "SenderName", tmp);
  
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName, "SenderName", tmp);

  return tmp;
}
