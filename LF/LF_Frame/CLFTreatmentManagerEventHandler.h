// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFTREATMENTMANAGEREVENTHANDLER_4118B9630218_INCLUDED
#define _INC_CLFTREATMENTMANAGEREVENTHANDLER_4118B9630218_INCLUDED

#include "CLFEventHandler.h"
#include "CLFTreatmentManagerDataWrapper.h"

//##ModelId=4118B9630218
class CLFTreatmentManagerEventHandler 
: public CLFEventHandler
{
public:
	//##ModelId=4118B972029C
	virtual bool handleEvent( CEventMessage& EventMessage);

	//##ModelId=462767AA030B
  CLFTreatmentManagerEventHandler(CModelTask* pModelTask);

protected:
	//##ModelId=4165559203A7
	CLFTreatmentManagerDataWrapper LFTreatmentManagerDataWrapper;

};

#endif /* _INC_CLFTREATMENTMANAGEREVENTHANDLER_4118B9630218_INCLUDED */
