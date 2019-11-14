// Copyright (C) 2004 SMS Demag AG, Germany

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_LFEVENTLOGHANDLER_420CCF950289_INCLUDED
#define _INC_CDM_LFEVENTLOGHANDLER_420CCF950289_INCLUDED

#include "CDM_EventLogHandler.h"

class CDM_LFEventLogHandler 
: public CDM_EventLogHandler
{
public:
	virtual std::string getProcessState(const std::string& ID);

  virtual std::string getExternalHeatID(const std::string& ID);
  virtual std::string getExternalTreatID(const std::string& ID);

  virtual long getEventLogDestination(const std::string& ID);

  virtual sEventLogMessage initEventLogMessage(const std::string& File, long Line, const std::string& ID);

  virtual sEventLogMessage initEventLogMessage(const std::string& File, long Line);


	virtual ~CDM_LFEventLogHandler();

	CDM_LFEventLogHandler();

};

#endif /* _INC_CDM_LFEVENTLOGHANDLER_420CCF950289_INCLUDED */
