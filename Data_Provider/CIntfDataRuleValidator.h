// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CINTFDATARULEVALIDATOR_42A042930283_INCLUDED
#define _INC_CINTFDATARULEVALIDATOR_42A042930283_INCLUDED

class CIntfDataValidator;

//##ModelId=42A042930283
class CIntfDataRuleValidator 
{
public:
	//##ModelId=42A042D200DA
	void log(const std::string& Message, long Level);

	//##ModelId=42A042D200E4
	void EventLogValidationFailure(const std::string& Message);

	//##ModelId=42A042D9035B
	void setpValidator(CIntfDataValidator* value);

	//##ModelId=42A042F10325
	virtual ~CIntfDataRuleValidator();

	//##ModelId=42A042F2010A
	CIntfDataRuleValidator();

protected:
	//##ModelId=42A042A70125
	CIntfDataValidator* m_pValidator;

};

#endif /* _INC_CINTFDATARULEVALIDATOR_42A042930283_INCLUDED */
