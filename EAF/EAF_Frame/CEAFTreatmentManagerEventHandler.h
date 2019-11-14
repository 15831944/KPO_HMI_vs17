// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFTREATMENTMANAGEREVENTHANDLER_4118B170035D_INCLUDED
#define _INC_CEAFTREATMENTMANAGEREVENTHANDLER_4118B170035D_INCLUDED

#include "CEAFEventHandler.h"
#include "CEAFTreatmentManagerDataWrapper.h"

//##ModelId=4118B7B702DB
class CEAFTreatmentManagerEventHandler 
: public CEAFEventHandler
{
protected:
	//##ModelId=41494F400223
	CEAFTreatmentManagerDataWrapper EAFTreatmentManagerDataWrapper;

public:
	//##ModelId=4118B7C70111
	virtual bool handleEvent( CEventMessage &EventMessage);

	//##ModelId=467645D602CB
  CEAFTreatmentManagerEventHandler(CModelTask* pModelTask);
};

#endif /* _INC_CEAFTREATMENTMANAGEREVENTHANDLER_4118B170035D_INCLUDED */
