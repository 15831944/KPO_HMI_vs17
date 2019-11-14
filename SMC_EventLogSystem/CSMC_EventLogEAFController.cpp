// Copyright (C) 2005 SMS Demag AG

#include <string>

#include "cCBS_StdLog_Task.h"
#include "CSMC_EventLogEAF.h"
#include "CSMC_EventLogEAFController.h"



//##ModelId=42EA236B0201
CSMC_EventLogEAFController* CSMC_EventLogEAFController::m_Instance = 0;

//##ModelId=42EA25FB00F6
CSMC_EventLogEAFController::~CSMC_EventLogEAFController()
{
	if (m_pEventLog) delete m_pEventLog;
}

//##ModelId=42EA25FB0292
CSMC_EventLogEAFController::CSMC_EventLogEAFController() : m_pEventLog(0)
{
  std::string ProcessName = cCBS_StdLog_Task::getInstance()->getEventLogProcessName();
  std::string ServiceName = cCBS_StdLog_Task::getInstance()->getEventLogServiceName();
  std::string ContextName = cCBS_StdLog_Task::getInstance()->getEventLogContextName();
        
  m_pEventLog = new CSMC_EventLogEAF(ProcessName,ServiceName,ContextName);

  // fill container for usage of ini file configuration
  m_pEventLog->setDestinationListEntry("EAFBotLine"  ,CSMC_DestCodes::EAFBotLine);
  m_pEventLog->setDestinationListEntry("EAF_1BotLine",CSMC_DestCodes::EAF_1BotLine);
  m_pEventLog->setDestinationListEntry("EAF_2BotLine",CSMC_DestCodes::EAF_2BotLine);

  m_pEventLog->initDestination();

}

//##ModelId=42EA2604012B
CSMC_EventLogEAFController* CSMC_EventLogEAFController::getInstance()
{
	if ( !m_Instance )
  {
    m_Instance = new CSMC_EventLogEAFController();
  }

	return m_Instance;
}

//##ModelId=42EA26110093
CSMC_EventLogEAF* CSMC_EventLogEAFController::getpEventLog()
{
	return m_pEventLog;
}

