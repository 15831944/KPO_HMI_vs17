// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CCHANGEPHYSICALMATERIALAVAILIBILITYWRAPPER_411254590024_INCLUDED
#define _INC_CCHANGEPHYSICALMATERIALAVAILIBILITYWRAPPER_411254590024_INCLUDED

class CEventMessage;

#include <string>


//##ModelId=411254590024
class CChangePhysicalMaterialAvailibilityWrapper 
{
public:
	//##ModelId=411101F3015D
	virtual bool doOnChangedPhysicalMatAvail( CEventMessage & Event);

};

#endif /* _INC_CCHANGEPHYSICALMATERIALAVAILIBILITYWRAPPER_411254590024_INCLUDED */
