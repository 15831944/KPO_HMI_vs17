// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_S.hh"
#include "iEventMessages_s.hh"
#include "iDM_Interface_s.hh"

#include "CARCHIVER_EAFDelayWrapper.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_DBExc.h"
#include "cCBS_StdCORBA_Task.h"
#include "CSMC_EventLogFrameController.h"

//##ModelId=41EE7D35025E
CARCHIVER_EAFDelayWrapper::CARCHIVER_EAFDelayWrapper()
{

}

//##ModelId=41EE7D02032C
CARCHIVER_EAFDelayWrapper::~CARCHIVER_EAFDelayWrapper()
{
	deleteDBClasses();
}

//##ModelId=41EE7D9D00E1
void CARCHIVER_EAFDelayWrapper::deleteDBClasses()
{
  //zhpf
  CARCHIVER_DelayWrapper::deleteDBClasses();

}

//##ModelId=41EE7D9D0394
void CARCHIVER_EAFDelayWrapper::initDBClasses()
{
  CARCHIVER_DelayWrapper::initDBClasses();
}
