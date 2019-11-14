// Copyright (C) 2007 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_S.hh"
#include "iEventMessages_s.hh"
#include "iDM_Interface_s.hh"


#include "CEventMessage.h"
#include "CIntfData.h"

#include "CARCHIVER_Task.h"
#include "CARCHIVER_DelayWrapper.h"



//##ModelId=462DD3F200A6
CARCHIVER_DelayWrapper::CARCHIVER_DelayWrapper() 
{
}

//##ModelId=462DD3F203B4
CARCHIVER_DelayWrapper::~CARCHIVER_DelayWrapper()
{
  deleteDBClasses();
}


//##ModelId=462DD53D0187
void CARCHIVER_DelayWrapper::initDBClasses()
{
}

//##ModelId=462DD53E008F
void CARCHIVER_DelayWrapper::deleteDBClasses()
{
}

