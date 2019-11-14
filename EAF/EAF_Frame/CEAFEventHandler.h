// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFEVENTHANDLER_412334CF02FD_INCLUDED
#define _INC_CEAFEVENTHANDLER_412334CF02FD_INCLUDED

#include "CModelEventHandler.h"
#include "CEventMessage.h"

//##ModelId=4146C2F6032D
class CEAFEventHandler : public CModelEventHandler
{
public:
	//##ModelId=4225884201F2
	virtual bool handleEvent(CEventMessage& EventMessage) = 0;

	//##ModelId=4146C35E0114
	virtual ~CEAFEventHandler();

protected:
	//##ModelId=4146C35E0113
	CEAFEventHandler(CModelTask* pModelTask);
};

#endif /* _INC_CEAFEVENTHANDLER_412334CF02FD_INCLUDED */
