// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_GENMODESANDAVAILABILITIESEVENTHANDLER_412F158503B0_INCLUDED
#define _INC_CDM_GENMODESANDAVAILABILITIESEVENTHANDLER_412F158503B0_INCLUDED

#include "CDM_GENEventHandler.h"

class CDM_GENModesAndAvailabilitiesEventHandler 
: public CDM_GENEventHandler
{
public:
	CDM_GENModesAndAvailabilitiesEventHandler();

	virtual ~CDM_GENModesAndAvailabilitiesEventHandler();

	//This hook operation would be called automatically by 
	//handleEvent( FRISEVENT &event) 
	//when an event is received. And this operation must be 
	//implemented by the user or client
	//in order to use it.
	virtual bool handleEvent(CEventMessage& evMessage);

	bool doGENSetGasAvailability(CEventMessage& Event);

	bool doGENSetTopLanceAvailability(CEventMessage& Event);

	bool doGENSetTuyeresAvailability(CEventMessage& Event);

	bool doGENSetAvailabilities(CEventMessage& Event);

	bool doGENSetComputerMode(CEventMessage& Event);

	bool doGENSetComputerModeBlowingOn(CEventMessage& Event);

	bool doGENSetComputerModeBlowingOff(CEventMessage& Event);

	bool doGENSetComputerModeMatHandlingOn(CEventMessage& Event);

	bool doGENSetComputerModeMatHandlingOff(CEventMessage& Event);

};

#endif /* _INC_CDM_GENMODESANDAVAILABILITIESEVENTHANDLER_412F158503B0_INCLUDED */
