// Copyright (C) 2005 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_EVENTLOGLFCONTROLLER_42EA233F0334_INCLUDED
#define _INC_CSMC_EVENTLOGLFCONTROLLER_42EA233F0334_INCLUDED

#include "CSMC_EventLogLF.h"

//##ModelId=44FEAB3301DA
class CSMC_EventLogLFController 
{
protected:
	//##ModelId=44FEAB3301EE
	CSMC_EventLogLFController();

public:
	//##ModelId=45F925940230
	static CSMC_EventLogLFController* m_Instance;

	//##ModelId=44FEAB33022E
	CSMC_EventLogLF* m_pEventLog;

	//##ModelId=44FEAB330235
	virtual ~CSMC_EventLogLFController();


	//##ModelId=44FEAB330237
	static CSMC_EventLogLFController* getInstance();

	//##ModelId=44FEAB330239
	CSMC_EventLogLF* getpEventLog();

};

#endif /* _INC_CSMC_EVENTLOGLFCONTROLLER_42EA233F0334_INCLUDED */
