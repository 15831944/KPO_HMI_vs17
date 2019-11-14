// Copyright (C) 2004 SMS Demag AG

#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdInitBase.h"
#include "CSMC_EventLogFrameController.h"

#include "CLFEventHandler.h"
#include "CLFModelTask.h"

//##ModelId=41517BC203E1
CLFEventHandler::CLFEventHandler(CModelTask *pModelTask)
: CModelEventHandler(pModelTask)
{
}