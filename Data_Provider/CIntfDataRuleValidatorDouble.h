// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CINTFDATARULEVALIDATORDOUBLE_42A033F20151_INCLUDED
#define _INC_CINTFDATARULEVALIDATORDOUBLE_42A033F20151_INCLUDED

#include <string>
#include "CIntfDataRuleValidator.h"

class CIntfDataRuleSet;

//##ModelId=42A033F20151
class CIntfDataRuleValidatorDouble 
: public CIntfDataRuleValidator
{
public:
	//##ModelId=42A0434A02E3
	bool validate(CIntfDataRuleSet* pRuleSet, double& Value);

};

#endif /* _INC_CINTFDATARULEVALIDATORDOUBLE_42A033F20151_INCLUDED */
