// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHMDEVENTHANDLER_412334CF02FD_INCLUDED
#define _INC_CHMDEVENTHANDLER_412334CF02FD_INCLUDED

#include "CModelEventHandler.h"
#include "CEventMessage.h"

//##ModelId=412334CF02FD
class CHMDEventHandler : public CModelEventHandler
{
public:

  //##ModelId=43315FE5015D
	virtual bool handleEvent(CEventMessage& EventMessage) = 0;

protected:

  //##ModelId=412334FE02FC
	CHMDEventHandler(CModelTask* pModelTask);

};

#endif /* _INC_CHMDEVENTHANDLER_412334CF02FD_INCLUDED */
