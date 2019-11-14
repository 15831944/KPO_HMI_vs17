// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFCHANGEPHYSICALMATERIALAVAILIBILITYWRAPPER_4112638C0101_INCLUDED
#define _INC_CEAFCHANGEPHYSICALMATERIALAVAILIBILITYWRAPPER_4112638C0101_INCLUDED

#include "CChangePhysicalMaterialAvailibilityWrapper.h"
#include "CEAFModelWrapper.h"

//##ModelId=429F1E93006A
class CEAFChangePhysicalMaterialAvailibilityWrapper 
: public CChangePhysicalMaterialAvailibilityWrapper
, public CEAFModelWrapper
{
public:
	//##ModelId=429F1E93009D
	virtual bool doOnChangedPhysicalMatAvail( CEventMessage &Event );

};

#endif /* _INC_CEAFCHANGEPHYSICALMATERIALAVAILIBILITYWRAPPER_4112638C0101_INCLUDED */
