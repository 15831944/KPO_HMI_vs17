// Copyright (C) 1999 - 2004 SMS Demag AG
#include <string>

#include "cCBS_StdLog_Task.h"
#include "cCBS_StdEventLogFrame.h"

#include "cCBS_StdEventLogFrameController.h"



//##ModelId=42EA2196031F
cCBS_StdEventLogFrameController* cCBS_StdEventLogFrameController::m_Instance = 0;

//##ModelId=42EA218E0309
cCBS_StdEventLogFrameController::~cCBS_StdEventLogFrameController()
{
	if (m_pEventLog) delete m_pEventLog;
}

//##ModelId=42EA218F00A0
cCBS_StdEventLogFrameController::cCBS_StdEventLogFrameController() 
: m_pEventLog(0)
{
  std::string ProcessName = cCBS_StdLog_Task::getInstance()->getEventLogProcessName();
  std::string ServiceName = cCBS_StdLog_Task::getInstance()->getEventLogServiceName();
  std::string ContextName = cCBS_StdLog_Task::getInstance()->getEventLogContextName();

  cCBS_StdLog_Task::getInstance()->log("Process Name: " + ProcessName + ", Service Name: " + ServiceName + ", Context Name: " + ContextName + " used to create event log.", 3);
  
  m_pEventLog = new cCBS_StdEventLogFrame(ProcessName,ServiceName,ContextName);
}

//##ModelId=42EA21AB0257
cCBS_StdEventLogFrameController* cCBS_StdEventLogFrameController::getInstance()
{
  if ( !m_Instance )
  {
    m_Instance = new cCBS_StdEventLogFrameController();
  }

	return m_Instance;

}

//##ModelId=42EA21DD01B0
 cCBS_StdEventLogFrame* cCBS_StdEventLogFrameController::getpEventLog() 
{
	return m_pEventLog;
}

