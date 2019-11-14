// Copyright (C) 2006 SMS Demag AG
// 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHMI_LF_EVENTHANDLER_45882EC202A9_INCLUDED
#define _INC_CHMI_LF_EVENTHANDLER_45882EC202A9_INCLUDED


#include "CHMI_EventHandler.h"

//##ModelId=45882EC202A9
class CHMI_LF_EventHandler 
: public CHMI_EventHandler
{
public:
	virtual bool copyDMData(CEventMessage& Event, const std::string& Name = "", const std::string& Key = "");

	//##ModelId=4588300300A8
	virtual bool handleEvent(CEventMessage& evMessage);

	//##ModelId=458830080325
	CHMI_LF_EventHandler(std::string& ServerName);

	//##ModelId=4588300C0212
	virtual ~CHMI_LF_EventHandler();

};

#endif /* _INC_CHMI_LF_EVENTHANDLER_45882EC202A9_INCLUDED */
