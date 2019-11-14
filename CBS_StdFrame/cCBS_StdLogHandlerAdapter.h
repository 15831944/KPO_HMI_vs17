// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CCBS_STDLOGMESSAGEADAPTER_411A19870036_INCLUDED
#define _INC_CCBS_STDLOGMESSAGEADAPTER_411A19870036_INCLUDED

#include <vector>

class cCBS_StdLogMessageHandler;

class cCBS_StdLogHandler;

//Class handling all registered LogHandlers and directing Log 
//Messages.
class cCBS_StdLogHandlerAdapter 
{
public:
	//Dirceting LogMessage to LogHandlers.
	void log(const std::string  & Message, long Level);

	//Adding LogHandler to LogMessageHandlerList
	void registerLogHandler(cCBS_StdLogHandler* MessageHandler);

  std::vector<cCBS_StdLogHandler*> getLogHandler() const;

private:
  std::vector<cCBS_StdLogHandler*>  m_LogMessageHandlerList;

};

#endif /* _INC_CCBS_STDLOGMESSAGEADAPTER_411A19870036_INCLUDED */
