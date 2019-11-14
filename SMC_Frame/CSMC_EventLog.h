// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEVENTLOG_4124864101BF_INCLUDED
#define _INC_CEVENTLOG_4124864101BF_INCLUDED

#include "cCBS_StdEventLog.h"

//##ModelId=4124864101BF
class CSMC_EventLog 
: public cCBS_StdEventLog
{
protected:
	//##ModelId=420388770159
	virtual void changeEventLogMessage(sEventLogMessage& EventLogMessage);

public:
};

#endif /* _INC_CEVENTLOG_4124864101BF_INCLUDED */
