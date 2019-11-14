// Copyright (C) 2007 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_S.hh"
#include "iEventMessages_s.hh"
#include "iDM_Interface_s.hh"

#include "CIntfData.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_DBExc.h"
#include "cCBS_StdCORBA_Task.h"
#include "CSMC_EventLogFrameController.h"
#include "CEventMessage.h"
#include "CDateTime.h"

#include "CARCHIVER_HMDAnalysisDataWrapper.h"



CARCHIVER_HMDAnalysisDataWrapper::CARCHIVER_HMDAnalysisDataWrapper()
{
}

CARCHIVER_HMDAnalysisDataWrapper::~CARCHIVER_HMDAnalysisDataWrapper()
{
}

void CARCHIVER_HMDAnalysisDataWrapper::deleteDBClasses()
{
  CARCHIVER_AnalysisDataWrapper::deleteDBClasses();
}

void CARCHIVER_HMDAnalysisDataWrapper::initDBClasses()
{
  CARCHIVER_AnalysisDataWrapper::initDBClasses();
}

