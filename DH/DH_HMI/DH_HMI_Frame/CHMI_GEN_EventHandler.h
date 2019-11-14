// Copyright (C) 2006 SMS Demag AG
// 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHMI_GEN_EVENTHANDLER_45882E8A030E_INCLUDED
#define _INC_CHMI_GEN_EVENTHANDLER_45882E8A030E_INCLUDED

#include "CHMI_EventHandler.h"

//##ModelId=45882E8A030E
class CHMI_GEN_EventHandler 
: public CHMI_EventHandler
{
public:
	//This hook operation would be called automatically by 
	//handleEvent( FRISEVENT &event) 
	//when an event is received. And this operation must be 
	//implemented by the user or client
	//in order to use it.
	//##ModelId=45882F8402D2
	virtual bool handleEvent(CEventMessage& evMessage);

	//##ModelId=45882FAA01B6
	CHMI_GEN_EventHandler(std::string& ServerName);

	//##ModelId=45882FAE021F
	virtual ~CHMI_GEN_EventHandler();

};

#endif /* _INC_CHMI_GEN_EVENTHANDLER_45882E8A030E_INCLUDED */
