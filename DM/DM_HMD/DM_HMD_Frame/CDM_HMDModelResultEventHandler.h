// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_HMDMODELRESULTEVENTHANDLER_416E994C0136_INCLUDED
#define _INC_CDM_HMDMODELRESULTEVENTHANDLER_416E994C0136_INCLUDED

#include "CDM_HMDEventHandler.h"

//##ModelId=45139A7200B7
class CDM_HMDModelResultEventHandler 
: public CDM_HMDEventHandler
{
public:
	//##ModelId=45139A7200CF
	CDM_HMDModelResultEventHandler();

	//##ModelId=45139A7200D0
	virtual ~CDM_HMDModelResultEventHandler();

	//##ModelId=45139A7200D2
	virtual bool handleEvent(CEventMessage& evMessage);

	//! call copyModelEventData and 
	//! changeComputerModeAvailabilities in product manager 
	//##ModelId=45139A7200D5
	bool doHMDModelResult(CEventMessage& Event);

	//! call copyModelEventData
	//##ModelId=45139A7200CB
	bool doHMDModelResultOffline(CEventMessage& Event);

	//! call doHMDModelResult
	//##ModelId=45139A7200D9
	bool doHMDModelResultCode( CEventMessage& Event);

	//! call doHMDModelResultOffline
	//##ModelId=45139A7200C4
	bool doHMDModelResultCodeOffline(CEventMessage& Event);

	//! call changePlantInformation in plant manager
	//! call changeProductInformation in product manager
	//##ModelId=45139A7200DD
	bool doHMDHeatAnnounceStatus( CEventMessage& Event);

	//! call changePlantInformation in plant manager
	//! call changeProductInformation in product manager
	//##ModelId=45139A7200CD
	bool doHMDHeatAnnounceStatusOffline(CEventMessage& Event);

};

#endif /* _INC_CDM_HMDMODELRESULTEVENTHANDLER_416E994C0136_INCLUDED */
