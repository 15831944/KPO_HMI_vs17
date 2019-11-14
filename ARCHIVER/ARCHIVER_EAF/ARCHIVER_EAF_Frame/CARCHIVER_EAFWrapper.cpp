// Copyright (C) 2011 SMS Siemag AG
#include "iSMC_DataDefinitions_s.hh"
#include "CSMC_EventLogFrameController.h"

#include "CARCHIVER_EAFWrapper.h"
#include <sstream>

//##ModelId=41AC494600FD
CARCHIVER_EAFWrapper::CARCHIVER_EAFWrapper()
{
}

//##ModelId=41AC49460252
CARCHIVER_EAFWrapper::~CARCHIVER_EAFWrapper()
{
	deleteDBClasses();
}

//##ModelId=42AFFF8A03CA
void CARCHIVER_EAFWrapper::initDBClasses()
{
	CARCHIVER_Wrapper::initDBClasses();
	
}

//##ModelId=42B006340328
void CARCHIVER_EAFWrapper::deleteDBClasses()
{
	CARCHIVER_Wrapper::deleteDBClasses();
	
}
