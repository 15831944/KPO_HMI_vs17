// Copyright (C) 2010 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_AsyncFileLogHandler_INCLUDED
#define _INC_CSMC_AsyncFileLogHandler_INCLUDED

#include "cCBS_StdLogHandler.h"
#include "CSMC_LogThread.h"

class CSMC_AsyncFileLogHandler 
: public cCBS_StdLogHandler
{
private:
  CSMC_LogThread m_LogThread;

public:
	virtual ~CSMC_AsyncFileLogHandler();

  CSMC_AsyncFileLogHandler(const std::string& Filename = "");

	void log(const std::string& Message, long Level);

  long getQueueSize();
};

#endif /* _INC_CSMC_AsyncFileLogHandler_INCLUDED */
