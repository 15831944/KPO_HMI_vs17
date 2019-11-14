// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_EAFEVENTLOGHANDLERMODESANDAVAILABILITIES_420CC09702C7_INCLUDED
#define _INC_CDM_EAFEVENTLOGHANDLERMODESANDAVAILABILITIES_420CC09702C7_INCLUDED

#include "CDM_EAFEventLogHandler.h"

class CDM_EAFEventLogHandlerModesAndAvailabilities 
: public CDM_EAFEventLogHandler
{
public:
	virtual bool EventLog(CEventMessage& Event);

};

#endif /* _INC_CDM_EAFEVENTLOGHANDLERMODESANDAVAILABILITIES_420CC09702C7_INCLUDED */
