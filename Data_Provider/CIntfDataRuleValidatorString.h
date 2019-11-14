// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CINTFDATARULEVALIDATORSTRING_42A033C80180_INCLUDED
#define _INC_CINTFDATARULEVALIDATORSTRING_42A033C80180_INCLUDED

#include <string>
#include "CIntfDataRuleValidator.h"

class CIntfDataRuleSet;

//##ModelId=42A033C80180
class CIntfDataRuleValidatorString 
: public CIntfDataRuleValidator
{
public:
	//##ModelId=42A0433A00AE
	bool validate(CIntfDataRuleSet* pRuleSet, std::string& Value);

};

#endif /* _INC_CINTFDATARULEVALIDATORSTRING_42A033C80180_INCLUDED */
