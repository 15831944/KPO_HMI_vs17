// Copyright (C) 2005 SMS Demag AG

#include "CDM_EAFTask.h"
#include "CDM_EAFEventLogHandler.h"


CDM_EAFEventLogHandler::~CDM_EAFEventLogHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}

CDM_EAFEventLogHandler::CDM_EAFEventLogHandler()
{
  m_pDataInterface = CDM_EAFTask::getInstance()->getpDataInterface();
  m_pProductManagementInterface = CDM_EAFTask::getInstance()->getpProductManagementInterface();
  m_pPlantManagementInterface   = CDM_EAFTask::getInstance()->getpPlantManagementInterface();
}

std::string CDM_EAFEventLogHandler::getProcessState(const std::string& ID)
{
  return CDM_EAFTask::getInstance()->getProcessState(ID);
}

std::string CDM_EAFEventLogHandler::getExternalHeatID(const std::string& ID)
{
 return CDM_EAFTask::getInstance()->getExternalHeatID(ID);
}

std::string CDM_EAFEventLogHandler::getExternalTreatID(const std::string& ID)
{
 return CDM_EAFTask::getInstance()->getExternalTreatID(ID);
}

long CDM_EAFEventLogHandler::getEventLogDestination(const std::string& ID)
{
 return CDM_EAFTask::getInstance()->getEventLogDestination(ID);
}

sEventLogMessage CDM_EAFEventLogHandler::initEventLogMessage(const std::string& File, long Line, const std::string& ID)
{
  return CDM_EAFTask::getInstance()->initEventLogMessage(File,Line,ID);
}

sEventLogMessage CDM_EAFEventLogHandler::initEventLogMessage(const std::string& File, long Line)
{
  return CDM_EAFTask::getInstance()->initEventLogMessage(File,Line);
}
