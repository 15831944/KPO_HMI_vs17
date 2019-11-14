// Copyright (C) 2004 SMS Demag AG

#include "cCBS_StdInitBase.h"
#include "CTsmSendEventAction.h"
#include "CTsmStateMachineConstructCtrl.h"


CTsmStateMachineConstructCtrl::CTsmStateMachineConstructCtrl()
: CStateMachineFileConstructCtrl(getConstructionFileName())
{
  m_EventSenderName = getEventSenderName();
}

CTsmStateMachineConstructCtrl::CTsmStateMachineConstructCtrl(std::string ConstructionFileName)
: CStateMachineFileConstructCtrl(ConstructionFileName)
{
  m_EventSenderName = getEventSenderName();
}


IAction* CTsmStateMachineConstructCtrl::createSendPlantMessageAction(const std::string & eventMessageString, const std::string & eventReceiverName, long timeOffsetSeconds) const
{
  return new CTsmSendEventAction(m_EventSenderName, eventReceiverName, eventMessageString, true, timeOffsetSeconds);
}

IAction* CTsmStateMachineConstructCtrl::createSendProductMessageAction(const std::string & eventMessageString, const std::string & eventReceiverName, long timeOffsetSeconds) const
{
  return new CTsmSendEventAction(m_EventSenderName, eventReceiverName, eventMessageString, false, timeOffsetSeconds);
}

IAction* CTsmStateMachineConstructCtrl::createCallStateMachineActionPlant(CStateMachine* pStateMachine, const std::string& eventMessage) const
{
	return CStateMachineFileConstructCtrl::createCallStateMachineActionPlant(pStateMachine, eventMessage);
}

IAction* CTsmStateMachineConstructCtrl::createCallStateMachineActionProduct(CStateMachine* pStateMachine, const std::string& eventMessage) const
{
	return CStateMachineFileConstructCtrl::createCallStateMachineActionProduct(pStateMachine, eventMessage);
}

std::string CTsmStateMachineConstructCtrl::getConstructionFileName()
{

  std::string constructionFileName;
  cCBS_StdInitBase *pInitBase = cCBS_StdInitBase::getInstance();

  pInitBase->replaceWithEntry("PATH", "ConstructionFileName", constructionFileName);
  return pInitBase->getXPACT_SMC() + constructionFileName;
}

std::string CTsmStateMachineConstructCtrl::getEventSenderName()
{
  std::string tmp;
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage", "SenderName", tmp);

  return tmp;
}
