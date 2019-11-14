// Copyright (C) 1991 - 1999 Rational Software Corporation

#include <sstream>
#include <fstream>

#include "cCBS_StdInitBase.h"
#include "cCBS_StdLog_Task.h"
#include "CSMC_EventLogFrameController.h"

#include "CEventMessage.h"

#include "CTraceLogCleanerEventHandler.h"

CTraceLogCleanerEventHandler::CTraceLogCleanerEventHandler()
{
}

CTraceLogCleanerEventHandler::~CTraceLogCleanerEventHandler()
{
}





bool CTraceLogCleanerEventHandler::handleEvent(const FRIESEvent& Event)
{
	CEventMessage EventMessage(Event);

  std::string Message = EventMessage.getMessage();

  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_EventChannelMessage(sMessage,EventMessage.getContent().c_str());
	
	return true;
}



bool CTraceLogCleanerEventHandler::checkEventAcceptance(const FRIESEvent& Event)
{
	return true;
}


bool CTraceLogCleanerEventHandler::doOnEventHandlingError(const FRIESEvent& Event)
{
	return true;
}

bool CTraceLogCleanerEventHandler::doOnEventMessage(const CEventMessage& EventMessage)
{
  return true;
}


