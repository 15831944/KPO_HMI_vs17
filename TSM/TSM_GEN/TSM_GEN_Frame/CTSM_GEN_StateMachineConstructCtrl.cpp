// Copyright (C) 2004 SMS Demag AG

#include "CTSM_GEN_Task.h"

#include "CTSM_GEN_SendEventAction.h"
#include "CTSM_GEN_HeatTrackingAction.h"
#include "CTSM_GEN_StateMachineConstructCtrl.h"

CTSM_GEN_StateMachineConstructCtrl::CTSM_GEN_StateMachineConstructCtrl()
: CTsmStateMachineConstructCtrl(getConstructionFileName())
{
  m_EventSenderName = getEventSenderName();

  CActionRegistration<CTSM_GEN_HeatTrackingAction>();
}

IAction* CTSM_GEN_StateMachineConstructCtrl::createSendProductMessageAction(const std::string & eventMessageString, const std::string & eventReceiverName, long timeOffsetSeconds) const
{
  return new CTSM_GEN_SendEventAction(m_EventSenderName, eventReceiverName, eventMessageString, false, timeOffsetSeconds);
}

std::string CTSM_GEN_StateMachineConstructCtrl::getConstructionFileName()
{
  std::string constructionFileName;
  std::string TaskName = CTSM_GEN_Task::getInstance()->getTaskName();

  cCBS_StdInitBase *pInitBase = cCBS_StdInitBase::getInstance();

  pInitBase->replaceWithEntry("PATH", "ConstructionFileName", constructionFileName);

  pInitBase->replaceWithEntry(TaskName, "ConstructionFileName", constructionFileName);

  return pInitBase->getXPACT_SMC() + constructionFileName;
}

std::string CTSM_GEN_StateMachineConstructCtrl::getEventSenderName()
{
  std::string tmp;
  std::string TaskName = CTSM_GEN_Task::getInstance()->getTaskName();

  cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage", "SenderName", tmp);
  
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName, "SenderName", tmp);

  return tmp;
}

IAction* CTSM_GEN_StateMachineConstructCtrl::createSendPlantMessageAction(const std::string & eventMessageString, const std::string & eventReceiverName, long timeOffsetSeconds) const
{
  return new CTSM_GEN_SendEventAction(m_EventSenderName, eventReceiverName, eventMessageString, false, timeOffsetSeconds);
}
