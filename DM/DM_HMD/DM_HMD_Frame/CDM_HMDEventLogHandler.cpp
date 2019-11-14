// Copyright (C) 2007 SMS Demag AG

#include "CDM_HMDTask.h"
#include "CDM_HMDEventLogHandler.h"

//##ModelId=45139A720140
CDM_HMDEventLogHandler::~CDM_HMDEventLogHandler()
{
}

//##ModelId=45139A720142
CDM_HMDEventLogHandler::CDM_HMDEventLogHandler()
{
  m_pDataInterface = CDM_HMDTask::getInstance()->getpDataInterface();
}

//##ModelId=45139A72013D
std::string CDM_HMDEventLogHandler::getProcessState(const std::string& ID)
{
 return CDM_HMDTask::getInstance()->getProcessState(ID);
}

std::string CDM_HMDEventLogHandler::getExternalHeatID(const std::string& ID)
{
 return CDM_HMDTask::getInstance()->getExternalHeatID(ID);
}

std::string CDM_HMDEventLogHandler::getExternalTreatID(const std::string& ID)
{
 return CDM_HMDTask::getInstance()->getExternalTreatID(ID);
}

