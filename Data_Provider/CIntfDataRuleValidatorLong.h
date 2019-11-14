// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CINTFDATARULEVALIDATORLONG_42A033E3031B_INCLUDED
#define _INC_CINTFDATARULEVALIDATORLONG_42A033E3031B_INCLUDED

#include <string>
#include "CIntfDataRuleValidator.h"

class CIntfDataRuleSet;

//##ModelId=42A033E3031B
class CIntfDataRuleValidatorLong 
: public CIntfDataRuleValidator
{
public:
	//##ModelId=42A04342010B
	bool validate(CIntfDataRuleSet* pRuleSet, long& Value);

};

#endif /* _INC_CINTFDATARULEVALIDATORLONG_42A033E3031B_INCLUDED */
