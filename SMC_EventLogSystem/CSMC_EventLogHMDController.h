// Copyright (C) 2005 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_EVENTLOGHMDCONTROLLER_42EA233F0334_INCLUDED
#define _INC_CSMC_EVENTLOGHMDCONTROLLER_42EA233F0334_INCLUDED

#include "CSMC_EventLogHMD.h"

//##ModelId=45F9215F01C0
class CSMC_EventLogHMDController 
{
protected:
	//##ModelId=45F9243F02DD
	CSMC_EventLogHMDController();

public:
	//##ModelId=45F9259600E8
	static CSMC_EventLogHMDController* m_Instance;

	//##ModelId=45F9243F0301
	CSMC_EventLogHMD* m_pEventLog;

	//##ModelId=45F9243F0307
	virtual ~CSMC_EventLogHMDController();


	//##ModelId=45F9243F0309
	static CSMC_EventLogHMDController* getInstance();

	//##ModelId=45F9243F030B
	CSMC_EventLogHMD* getpEventLog();

};

#endif /* _INC_CSMC_EVENTLOGHMDCONTROLLER_42EA233F0334_INCLUDED */
