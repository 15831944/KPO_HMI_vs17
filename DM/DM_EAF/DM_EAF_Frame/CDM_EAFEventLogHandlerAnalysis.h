// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_EAFEVENTLOGHANDLERANALYSIS_420CC07902DF_INCLUDED
#define _INC_CDM_EAFEVENTLOGHANDLERANALYSIS_420CC07902DF_INCLUDED

#include "CDM_EAFEventLogHandler.h"

class CDM_EAFEventLogHandlerAnalysis 
: public CDM_EAFEventLogHandler
{
public:
	virtual bool EventLog(CEventMessage& Event);

};

#endif /* _INC_CDM_EAFEVENTLOGHANDLERANALYSIS_420CC07902DF_INCLUDED */
