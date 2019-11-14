// Copyright (C) 2005 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_EVENTLOGCONTROLLER_42EA18BF0176_INCLUDED
#define _INC_CSMC_EVENTLOGCONTROLLER_42EA18BF0176_INCLUDED

#include "CSMC_EventLogFrame.h"

//##ModelId=42EA18BF0176
class CSMC_EventLogFrameController 
{
protected:
	//##ModelId=42EA19A703B7
	CSMC_EventLogFrameController();

public:
	//##ModelId=42EA19650201
	static CSMC_EventLogFrameController* m_Instance;

	//##ModelId=42EA1951014E
	CSMC_EventLogFrame* getpEventLog();

	//##ModelId=42EA19A70206
	virtual ~CSMC_EventLogFrameController();


	//##ModelId=42EA19AF010F
	static CSMC_EventLogFrameController* getInstance();

private:
	//##ModelId=42EA190D0114
	CSMC_EventLogFrame* m_pEventLog;

};

#endif /* _INC_CSMC_EVENTLOGCONTROLLER_42EA18BF0176_INCLUDED */
