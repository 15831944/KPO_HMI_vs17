// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CINTFDATARULEVALIDATORANY_42A0342F0293_INCLUDED
#define _INC_CINTFDATARULEVALIDATORANY_42A0342F0293_INCLUDED

#include <corba.h>
#include "CIntfDataRuleValidator.h"

class CIntfDataRuleSet;

//##ModelId=42A0342F0293
class CIntfDataRuleValidatorAny 
: public CIntfDataRuleValidator
{
public:
	//##ModelId=42A043530247
	bool validate(CIntfDataRuleSet* pRuleSet, CORBA::Any& Value);

};

#endif /* _INC_CINTFDATARULEVALIDATORANY_42A0342F0293_INCLUDED */
