// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFCHANGEPHYSICALMATERIALAVAILIBILITYWRAPPER_41125F5C0151_INCLUDED
#define _INC_CLFCHANGEPHYSICALMATERIALAVAILIBILITYWRAPPER_41125F5C0151_INCLUDED

#include "CChangePhysicalMaterialAvailibilityWrapper.h"
#include "CLFModelWrapper.h"

//##ModelId=41125F5C0151
class CLFChangePhysicalMaterialAvailibilityWrapper 
: public CChangePhysicalMaterialAvailibilityWrapper
, public CLFModelWrapper
{
public:
	//##ModelId=4166902303D5
	 bool doOnChangedPhysicalMatAvail(CEventMessage& Event);

};

#endif /* _INC_CLFCHANGEPHYSICALMATERIALAVAILIBILITYWRAPPER_41125F5C0151_INCLUDED */
