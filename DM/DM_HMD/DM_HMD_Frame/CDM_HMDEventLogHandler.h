// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_HMDEVENTLOGHANDLER_INCLUDED
#define _INC_CDM_HMDEVENTLOGHANDLER_INCLUDED

#include "CDM_EventLogHandler.h"

//##ModelId=45139A720135
class CDM_HMDEventLogHandler 
: public CDM_EventLogHandler
{
public:
	//##ModelId=45139A72013D
	virtual std::string getProcessState(const std::string& ID);

	virtual std::string getExternalHeatID(const std::string& ID);

	virtual std::string getExternalTreatID(const std::string& ID);

	//##ModelId=45139A720140
	virtual ~CDM_HMDEventLogHandler();

	//##ModelId=45139A720142
	CDM_HMDEventLogHandler();

};

#endif /* _INC_CDM_HMDEVENTLOGHANDLER_INCLUDED */
