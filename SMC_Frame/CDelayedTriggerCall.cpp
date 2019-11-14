// Copyright (C) 2009 SMS Demag AG

#include "CEventMessage.h"
#include "cCBS_StdEventLogFrameController.h"

#include "CDelayedTriggerCall.h"

CDelayedTriggerCall::CDelayedTriggerCall(CEventMessage& arg, long msec)
{
	CDelayedTriggerCall::CDelayTrig *pTrig = new CDelayedTriggerCall::CDelayTrig(arg, msec);
}

CDelayedTriggerCall::~CDelayedTriggerCall()
{
}

CDelayedTriggerCall::CDelayTrig::CDelayTrig(CEventMessage& arg, long msec)
: m_eventMessage(arg)
, m_delayTime(msec)
{
  setFreeOnTerminate(true);
  run();
}

CDelayedTriggerCall::CDelayTrig::~CDelayTrig()
{
}

void CDelayedTriggerCall::CDelayTrig::work()
{
  sleep(m_delayTime);
  try
  {
    // To avoid processing the dispatch list because of empty arguments, we have to
    // use the original sender and receiver
    m_eventMessage.dispatch(m_eventMessage.getSender(),m_eventMessage.getReceiver());
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CDelayedTriggerCall::CDelayTrig::work()","Dispaching Event");
  }
}

