// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_HMDMODESANDAVAILABILITIESEVENTHANDLER_412F158503B0_INCLUDED
#define _INC_CDM_HMDMODESANDAVAILABILITIESEVENTHANDLER_412F158503B0_INCLUDED

#include "CDM_HMDEventHandler.h"

//##ModelId=45139A72008E
class CDM_HMDModesAndAvailabilitiesEventHandler 
: public CDM_HMDEventHandler
{
public:
	//##ModelId=45139A72009C
	CDM_HMDModesAndAvailabilitiesEventHandler();

	//##ModelId=45139A72009D
	virtual ~CDM_HMDModesAndAvailabilitiesEventHandler();

	//##ModelId=45139A72009F
	virtual bool handleEvent(CEventMessage& evMessage);

	//##ModelId=45139A7200AC
	bool doHMDSetComputerModeOn(CEventMessage& Event);

	//##ModelId=45139A7200AE
	bool doHMDSetComputerModeOff(CEventMessage& Event);

	//##ModelId=45139A7200AA
	bool doHMDSetComputerMode(CEventMessage& Event);

};

#endif /* _INC_CDM_HMDMODESANDAVAILABILITIESEVENTHANDLER_412F158503B0_INCLUDED */
