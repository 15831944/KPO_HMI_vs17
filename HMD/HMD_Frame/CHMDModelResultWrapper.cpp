// Copyright (C) 2004 SMS Demag AG

#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"

#include "CHMDModelResultWrapper.h"

#include "CEventMessage.h"

#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdInitBase.h"

#include "CSMC_RecipeHandler.h"
#include "CSMC_EventLogFrameController.h"


//##ModelId=4124B120022C
CHMDModelResultWrapper::CHMDModelResultWrapper()
{
}

//##ModelId=4124B121004D
CHMDModelResultWrapper::~CHMDModelResultWrapper()
{
}



//##ModelId=4118CDE2024D
bool CHMDModelResultWrapper::doModelResult(CEventMessage &Event)
{
  bool RetValue = false;

  return RetValue;
}

//##ModelId=4135CB690333
bool CHMDModelResultWrapper::doResultCodeAndMessage(CEventMessage &Event)
{
  bool RetValue = true;

  return RetValue;
}

//##ModelId=4119D83500CF
bool CHMDModelResultWrapper::doModelActualSetpoints(CEventMessage &Event)
{
  bool RetValue = false;
  return RetValue;
}

//##ModelId=4135CB6601ED
bool CHMDModelResultWrapper::doMatRecipeSetpoints(CEventMessage &Event)
{
  bool RetValue = false;
  return RetValue;
}

