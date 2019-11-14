// Copyright (C) 2007 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"

#include "CARCHIVER_HMDTask.h"
#include "CARCHIVER_HMDWrapper.h"

//##ModelId=41A4A9F40246
CARCHIVER_HMDWrapper::CARCHIVER_HMDWrapper()
{
  m_pArchiverTask = CARCHIVER_HMDTask::getInstance();
  m_PlantID = DEF_DB_PLANT::HMD;
}

//##ModelId=41A4A9F40373
CARCHIVER_HMDWrapper::~CARCHIVER_HMDWrapper()
{
}
