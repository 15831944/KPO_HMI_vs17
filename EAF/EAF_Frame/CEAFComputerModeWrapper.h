// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFCOMPUTERMODEWRAPPER_411276DD0384_INCLUDED
#define _INC_CEAFCOMPUTERMODEWRAPPER_411276DD0384_INCLUDED

#include "CEAFModelWrapper.h"

//##ModelId=411276DD0384
class CEAFComputerModeWrapper 
: public CEAFModelWrapper
{
public:
	//##ModelId=411277130175
  bool doOnSetComputerMode( CEventMessage &Event );

	//##ModelId=4112777D0379
	bool doOnSetEAFMaintenanceMode( CEventMessage &Event );

	//##ModelId=429F1E93002E
	bool doOnActivateWTC( CEventMessage &Event );

	//##ModelId=429F1E93004C
	bool doOnDeactivateWTC( CEventMessage &Event );

};

#endif /* _INC_CEAFCOMPUTERMODEWRAPPER_411276DD0384_INCLUDED */
