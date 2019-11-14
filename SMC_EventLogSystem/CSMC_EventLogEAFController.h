// Copyright (C) 2005 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_EVENTLOGEAFCONTROLLER_42EA231F005D_INCLUDED
#define _INC_CSMC_EVENTLOGEAFCONTROLLER_42EA231F005D_INCLUDED

#include "CSMC_EventLogEAF.h"

//##ModelId=42EA231F005D
class CSMC_EventLogEAFController 
{
protected:
	//##ModelId=42EA25FB0292
	CSMC_EventLogEAFController();

public:
	//##ModelId=42EA236B0201
	static CSMC_EventLogEAFController* m_Instance;

	//##ModelId=42EA238E016B
	CSMC_EventLogEAF* m_pEventLog;

	//##ModelId=42EA25FB00F6
	virtual ~CSMC_EventLogEAFController();


	//##ModelId=42EA2604012B
	static CSMC_EventLogEAFController* getInstance();

	//##ModelId=42EA26110093
	CSMC_EventLogEAF* getpEventLog();

};

#endif /* _INC_CSMC_EVENTLOGEAFCONTROLLER_42EA231F005D_INCLUDED */
