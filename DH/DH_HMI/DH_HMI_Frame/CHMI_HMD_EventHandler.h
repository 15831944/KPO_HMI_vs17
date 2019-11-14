// Copyright (C) 2006 SMS Demag AG
// 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHMI_HMD_EVENTHANDLER_45882EEA0104_INCLUDED
#define _INC_CHMI_HMD_EVENTHANDLER_45882EEA0104_INCLUDED

#include "CHMI_EventHandler.h"

//##ModelId=45882EEA0104
class CHMI_HMD_EventHandler 
: public CHMI_EventHandler
{
public:
	virtual bool copyDMData(CEventMessage& Event, const std::string& Name = "", const std::string& Key = "");

	//This hook operation would be called automatically by 
	//handleEvent( FRISEVENT &event) 
	//when an event is received. And this operation must be 
	//implemented by the user or client
	//in order to use it.
	//##ModelId=45882FF0011D
	virtual bool handleEvent(CEventMessage& evMessage);

	//##ModelId=45882FF3021B
	CHMI_HMD_EventHandler(std::string& ServerName);

	//##ModelId=45882FF60247
	virtual ~CHMI_HMD_EventHandler();

};

#endif /* _INC_CHMI_HMD_EVENTHANDLER_45882EEA0104_INCLUDED */
