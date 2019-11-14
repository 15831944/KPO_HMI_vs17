// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CCBS_STDLOGMESSAGEHANDLER_411A19A1034B_INCLUDED
#define _INC_CCBS_STDLOGMESSAGEHANDLER_411A19A1034B_INCLUDED

#include <string>


//Base Class to be derived for realizing specific Log output 
//mechanisms. Derived Classes must be registered using 
//cCBS_StdLog_Task::registerLogHandler.
class cCBS_StdLogHandler 
{
protected:
	long m_Type;

public:
  cCBS_StdLogHandler();

  virtual ~cCBS_StdLogHandler();

	static long m_FileType;

	static long m_EventLogType;

	static long m_DisplayType;

	static long m_AsyncFileType;

	virtual void log(const std::string& Message, long Level) = 0;

  // Returns queue size if queue mechanism is available
  // otherwise -1;
  virtual long getQueueSize() { return -1; };

  // return type description
  std::string getType();
};

#endif /* _INC_CCBS_STDLOGMESSAGEHANDLER_411A19A1034B_INCLUDED */
