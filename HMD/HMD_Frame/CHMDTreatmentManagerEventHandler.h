// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHMDTREATMENTMANAGEREVENTHANDLER_4118B170035D_INCLUDED
#define _INC_CHMDTREATMENTMANAGEREVENTHANDLER_4118B170035D_INCLUDED

#include "CHMDEventHandler.h"
#include "CHMDTreatmentManagerDataWrapper.h"

//##ModelId=4118B170035D
class CHMDTreatmentManagerEventHandler 
: public CHMDEventHandler
{
protected:
	//##ModelId=4125E9FF02C1
	CHMDTreatmentManagerDataWrapper HMDTreatmentManagerDataWrapper;

public:
	//##ModelId=412331B3034F
	virtual bool handleEvent( CEventMessage& EventMessage);

  CHMDTreatmentManagerEventHandler(CModelTask* pModelTask);
};

#endif /* _INC_CHMDTREATMENTMANAGEREVENTHANDLER_4118B170035D_INCLUDED */
