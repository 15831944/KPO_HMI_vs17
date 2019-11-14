// Copyright (C) 2004 SMS Demag AG, Germany

#include "CDM_LFTask.h"
#include "CDM_LFEventLogHandler.h"



CDM_LFEventLogHandler::~CDM_LFEventLogHandler()
{
}

CDM_LFEventLogHandler::CDM_LFEventLogHandler()
{
  m_pDataInterface              = CDM_LFTask::getInstance()->getpDataInterface();
  m_pProductManagementInterface = CDM_LFTask::getInstance()->getpProductManagementInterface();
  m_pPlantManagementInterface   = CDM_LFTask::getInstance()->getpPlantManagementInterface();
}



std::string CDM_LFEventLogHandler::getProcessState(const std::string& ID)
{
  return CDM_LFTask::getInstance()->getProcessState(ID);
}

std::string CDM_LFEventLogHandler::getExternalHeatID(const std::string& ID)
{
 return CDM_LFTask::getInstance()->getExternalHeatID(ID);
}

std::string CDM_LFEventLogHandler::getExternalTreatID(const std::string& ID)
{
 return CDM_LFTask::getInstance()->getExternalTreatID(ID);
}

long CDM_LFEventLogHandler::getEventLogDestination(const std::string& ID)
{
 return CDM_LFTask::getInstance()->getEventLogDestination(ID);
}

sEventLogMessage CDM_LFEventLogHandler::initEventLogMessage(const std::string& File, long Line, const std::string& ID)
{
  return CDM_LFTask::getInstance()->initEventLogMessage(File,Line,ID);
}

sEventLogMessage CDM_LFEventLogHandler::initEventLogMessage(const std::string& File, long Line)
{
  return CDM_LFTask::getInstance()->initEventLogMessage(File,Line);
}
