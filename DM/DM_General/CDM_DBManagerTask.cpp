// Copyright (C) 2009 SMS Demag AG
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CDM_EventLogHandler.h"

#include "CDM_DBManagerTask.h"

CDM_DBManagerTask::CDM_DBManagerTask()
{
}

CDM_DBManagerTask::~CDM_DBManagerTask()
{
}

void CDM_DBManagerTask::log(const std::string& Message, long Level)
{
  cCBS_StdLog_Task::getInstance()->log(Message, Level);
}

bool CDM_DBManagerTask::initialize()
{
	return CSMC_FrameTask::initialize();
}

void CDM_DBManagerTask::doOnTaskWorkingError()
{
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ErrorTaskWorkingState(sMessage);
  
  setWorking(false);
}

