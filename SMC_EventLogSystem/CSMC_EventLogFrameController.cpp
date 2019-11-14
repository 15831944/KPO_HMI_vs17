// Copyright (C) 2005 SMS Demag AG

#include <string>

#include "cCBS_StdLog_Task.h"
#include "CSMC_EventLogFrame.h"
#include "CSMC_EventLogFrameController.h"


//##ModelId=42EA19650201
CSMC_EventLogFrameController* CSMC_EventLogFrameController::m_Instance = 0;

//##ModelId=42EA1951014E
CSMC_EventLogFrame* CSMC_EventLogFrameController::getpEventLog()
{
	return m_pEventLog;
}

//##ModelId=42EA19A70206
CSMC_EventLogFrameController::~CSMC_EventLogFrameController()
{
	if (m_pEventLog) delete m_pEventLog;	
}

//##ModelId=42EA19A703B7
CSMC_EventLogFrameController::CSMC_EventLogFrameController() 
: m_pEventLog(0)
{
  std::string ProcessName = cCBS_StdLog_Task::getInstance()->getEventLogProcessName();
  std::string ServiceName = cCBS_StdLog_Task::getInstance()->getEventLogServiceName();
  std::string ContextName = cCBS_StdLog_Task::getInstance()->getEventLogContextName();
  
  m_pEventLog = new CSMC_EventLogFrame(ProcessName,ServiceName,ContextName);

  // fill container for usage of ini file configuration
  m_pEventLog->setDestinationListEntry("ComputerRoom" ,CSMC_DestCodes::ComputerRoom);
  m_pEventLog->setDestinationListEntry("AllBotLines"  ,CSMC_DestCodes::AllBotLines);

  m_pEventLog->initDestination();

}

//##ModelId=42EA19AF010F
CSMC_EventLogFrameController* CSMC_EventLogFrameController::getInstance()
{
  if ( !m_Instance )
  {
    m_Instance = new CSMC_EventLogFrameController();
  }

	return m_Instance;
}

