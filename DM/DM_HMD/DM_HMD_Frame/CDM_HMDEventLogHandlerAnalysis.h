// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_HMDEVENTLOGHANDLER_420B3E18010D_INCLUDED
#define _INC_CDM_HMDEVENTLOGHANDLER_420B3E18010D_INCLUDED

#include "CDM_HMDEventLogHandler.h"

//##ModelId=45139A72012B
class CDM_HMDEventLogHandlerAnalysis 
: public CDM_HMDEventLogHandler
{
public:
	//##ModelId=45139A720132
	virtual bool EventLog(CEventMessage& Event);

};

#endif /* _INC_CDM_HMDEVENTLOGHANDLER_420B3E18010D_INCLUDED */
