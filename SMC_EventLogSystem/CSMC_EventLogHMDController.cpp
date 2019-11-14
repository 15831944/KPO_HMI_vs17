// Copyright (C) 2005 SMS Demag AG

#include <string>

#include "cCBS_StdLog_Task.h"
#include "CSMC_EventLogHMD.h"
#include "CSMC_EventLogHMDController.h"



//##ModelId=45F9259600E8
CSMC_EventLogHMDController* CSMC_EventLogHMDController::m_Instance = 0;

//##ModelId=45F9243F0307
CSMC_EventLogHMDController::~CSMC_EventLogHMDController()
{
	if (m_pEventLog) delete m_pEventLog;	
}

//##ModelId=45F9243F02DD
CSMC_EventLogHMDController::CSMC_EventLogHMDController() : m_pEventLog(0)
{
  std::string ProcessName = cCBS_StdLog_Task::getInstance()->getEventLogProcessName();
  std::string ServiceName = cCBS_StdLog_Task::getInstance()->getEventLogServiceName();
  std::string ContextName = cCBS_StdLog_Task::getInstance()->getEventLogContextName();
        
  m_pEventLog = new CSMC_EventLogHMD(ProcessName,ServiceName,ContextName);

  // fill container for usage of ini file configuration
  m_pEventLog->setDestinationListEntry("HMDBotLine"  ,CSMC_DestCodes::HMDBotLine);
  m_pEventLog->setDestinationListEntry("HMD_1BotLine",CSMC_DestCodes::HMD_1BotLine);
  m_pEventLog->setDestinationListEntry("HMD_2BotLine",CSMC_DestCodes::HMD_2BotLine);
  //m_pEventLog->setDestinationListEntry("HMD_3BotLine",CSMC_DestCodes::HMD_3BotLine);
  //m_pEventLog->setDestinationListEntry("HMD_4BotLine",CSMC_DestCodes::HMD_4BotLine);
  //m_pEventLog->setDestinationListEntry("HMD"  ,CSMC_DestCodes::HMD);
  //m_pEventLog->setDestinationListEntry("HMD_1",CSMC_DestCodes::HMD_1);
  //m_pEventLog->setDestinationListEntry("HMD_2",CSMC_DestCodes::HMD_2);
  //m_pEventLog->setDestinationListEntry("HMD_3",CSMC_DestCodes::HMD_3);
  //m_pEventLog->setDestinationListEntry("HMD_4",CSMC_DestCodes::HMD_4);

  m_pEventLog->initDestination();

}

//##ModelId=45F9243F0309
CSMC_EventLogHMDController* CSMC_EventLogHMDController::getInstance()
{
  if ( !m_Instance )
  {
    m_Instance = new CSMC_EventLogHMDController();
  }

	return m_Instance;
}

//##ModelId=45F9243F030B
CSMC_EventLogHMD* CSMC_EventLogHMDController::getpEventLog()
{
	return m_pEventLog;
}

