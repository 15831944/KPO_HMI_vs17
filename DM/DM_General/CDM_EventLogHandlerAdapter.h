// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_EVENTLOGHANDLERADAPTER_420B65AF02C6_INCLUDED
#define _INC_CDM_EVENTLOGHANDLERADAPTER_420B65AF02C6_INCLUDED

class CDM_EventLogHandler;
class CDM_DataInterface_Impl;
class CEventMessage;

class CDM_EventLogHandlerAdapter 
{
public:
	void registerEventLogHandler(CDM_EventLogHandler* EventLogHandler);

	bool EventLog(CEventMessage& Event);

private:
	std::vector<CDM_EventLogHandler*> m_EventLogHandlerlist;

};

#endif /* _INC_CDM_EVENTLOGHANDLERADAPTER_420B65AF02C6_INCLUDED */
