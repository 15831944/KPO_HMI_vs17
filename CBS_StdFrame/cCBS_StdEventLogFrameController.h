// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CCBS_STDEVENTLOGFRAMECONTROLLER_42EA214501D8_INCLUDED
#define _INC_CCBS_STDEVENTLOGFRAMECONTROLLER_42EA214501D8_INCLUDED

#include "cCBS_StdEventLogFrame.h"

//##ModelId=42EA214501D8
class cCBS_StdEventLogFrameController 
{
protected:
	//##ModelId=42EA2196031F
	static cCBS_StdEventLogFrameController* m_Instance;
	//##ModelId=42EA218F00A0
	cCBS_StdEventLogFrameController();

public:

	//##ModelId=42EA21C601E7
	cCBS_StdEventLogFrame* m_pEventLog;

	//##ModelId=42EA218E0309
	virtual ~cCBS_StdEventLogFrameController();


	//##ModelId=42EA21AB0257
	static cCBS_StdEventLogFrameController* getInstance();

	//##ModelId=42EA21DD01B0
	 cCBS_StdEventLogFrame* getpEventLog() ;

};

#endif /* _INC_CCBS_STDEVENTLOGFRAMECONTROLLER_42EA214501D8_INCLUDED */
