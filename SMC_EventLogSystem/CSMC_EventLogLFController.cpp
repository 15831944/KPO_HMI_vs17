// Copyright (C) 2005 SMS Demag AG

#include <string>

#include "cCBS_StdLog_Task.h"
#include "CSMC_EventLogLF.h"
#include "CSMC_EventLogLFController.h"



//##ModelId=45F925940230
CSMC_EventLogLFController* CSMC_EventLogLFController::m_Instance = 0;

//##ModelId=44FEAB330235
CSMC_EventLogLFController::~CSMC_EventLogLFController()
{
	if (m_pEventLog) delete m_pEventLog;	
}

//##ModelId=44FEAB3301EE
CSMC_EventLogLFController::CSMC_EventLogLFController() : m_pEventLog(0)
{
  std::string ProcessName = cCBS_StdLog_Task::getInstance()->getEventLogProcessName();
  std::string ServiceName = cCBS_StdLog_Task::getInstance()->getEventLogServiceName();
  std::string ContextName = cCBS_StdLog_Task::getInstance()->getEventLogContextName();
        
  m_pEventLog = new CSMC_EventLogLF(ProcessName,ServiceName,ContextName);

  // fill container for usage of ini file configuration
  m_pEventLog->setDestinationListEntry("LFBotLine"  ,CSMC_DestCodes::LFBotLine);
  m_pEventLog->setDestinationListEntry("LF_1BotLine",CSMC_DestCodes::LF_1BotLine);
  m_pEventLog->setDestinationListEntry("LF_2BotLine",CSMC_DestCodes::LF_2BotLine);

  m_pEventLog->initDestination();

}

//##ModelId=44FEAB330237
CSMC_EventLogLFController* CSMC_EventLogLFController::getInstance()
{
  if ( !m_Instance )
  {
    m_Instance = new CSMC_EventLogLFController();
  }

	return m_Instance;
}

//##ModelId=44FEAB330239
CSMC_EventLogLF* CSMC_EventLogLFController::getpEventLog()
{
	return m_pEventLog;
}

