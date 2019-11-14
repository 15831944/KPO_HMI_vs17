// Copyright (C) 2004 SMS Demag AG

#include "cCBS_StdLog_Task.h"
#include "cCBS_StdLogMsgPort.h"

void cCBS_StdLogMsgPort::printOutMessage(int traceLevel, const char* msg)
{
  cCBS_StdLog_Task *pLogTask = cCBS_StdLog_Task::getInstance();

  if (pLogTask)
    pLogTask->log(msg, 1);
}

