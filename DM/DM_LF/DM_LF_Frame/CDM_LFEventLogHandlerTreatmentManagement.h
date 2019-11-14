// Copyright (C) 2004 SMS Demag AG, Germany

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_LFEVENTLOGHANDLERTREATMENTMANAGEMENT_428B07AE033D_INCLUDED
#define _INC_CDM_LFEVENTLOGHANDLERTREATMENTMANAGEMENT_428B07AE033D_INCLUDED

#include "CDM_LFEventLogHandler.h"

class CDM_LFEventLogHandlerTreatmentManagement 
: public CDM_LFEventLogHandler
{
public:
	virtual bool EventLog(CEventMessage& Event);

};

#endif /* _INC_CDM_LFEVENTLOGHANDLERTREATMENTMANAGEMENT_428B07AE033D_INCLUDED */
