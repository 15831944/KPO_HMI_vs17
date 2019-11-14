// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFModelStatusEventHandler_41762B3F00EC_INCLUDED
#define _INC_CLFModelStatusEventHandler_41762B3F00EC_INCLUDED

#include "CLFEventHandler.h"
#include "CLFModelStatusWrapper.h"

//##ModelId=41762B3F00EC
class CLFModelStatusEventHandler 
: public CLFEventHandler
{
protected:
	//##ModelId=41762D12004D
	CLFModelStatusWrapper LFModelStatusWrapper;

public:
	//##ModelId=41762D060229
	virtual bool handleEvent( CEventMessage& EventMessage);

	//##ModelId=462767AE0057
  CLFModelStatusEventHandler(CModelTask* pModelTask);
};

#endif /* _INC_CLFModelStatusEventHandler_41762B3F00EC_INCLUDED */
