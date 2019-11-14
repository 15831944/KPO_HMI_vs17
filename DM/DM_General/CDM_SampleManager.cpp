// Copyright (C) 2004 SMS Demag AG
#include <iomanip>
#include <sstream>

#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"

#include "cCBS_StdLog_Task.h"
#include "CSMC_EventLogFrameController.h"
#include "CEventMessage.h"
#include "CIntfData.h"

#include "CSampleCode.h"


#include "CDM_SampleManager.h"


CDM_SampleManager::~CDM_SampleManager()
{
}

CDM_SampleManager::CDM_SampleManager() 
{
}

std::string CDM_SampleManager::generateSampleId(long SampleType, const std::string& PlantId, const std::string& ProcessStage, long SampleNo, const std::string& SampleLocation)
{
  CSampleCode SampleCode;

  return SampleCode.getSampleCode(SampleType, PlantId, ProcessStage, SampleNo, SampleLocation);
}

