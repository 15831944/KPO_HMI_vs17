// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_HMDEVENTLOGHANDLERSIGNALSANDMEASUREMENTS_420B8F80020C_INCLUDED
#define _INC_CDM_HMDEVENTLOGHANDLERSIGNALSANDMEASUREMENTS_420B8F80020C_INCLUDED

#include "CDM_HMDEventLogHandler.h"

//##ModelId=45139A7200F8
class CDM_HMDEventLogHandlerSignalsAndMeasurements 
: public CDM_HMDEventLogHandler
{
public:
	//##ModelId=45139A7200FF
	virtual bool EventLog(CEventMessage& Event);

};

#endif /* _INC_CDM_HMDEVENTLOGHANDLERSIGNALSANDMEASUREMENTS_420B8F80020C_INCLUDED */
