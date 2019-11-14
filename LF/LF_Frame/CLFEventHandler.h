// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFEVENTHANDLER_412334CF02FD_INCLUDED
#define _INC_CLFEVENTHANDLER_412334CF02FD_INCLUDED

#include "CModelEventHandler.h"
#include "CEventMessage.h"
#include "CLFModelWrapper.h"

class CLFModelTask;

//##ModelId=415179CE020B
class CLFEventHandler : public CModelEventHandler
{
public:

	//##ModelId=42A94C350384
	std::string getLadleTransferCarID();

protected:

	//##ModelId=41517BC203E1
	CLFEventHandler(CModelTask* pModelTask);

};

#endif /* _INC_CLFEVENTHANDLER_412334CF02FD_INCLUDED */
