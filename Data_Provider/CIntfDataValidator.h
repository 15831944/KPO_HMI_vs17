// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CINTFDATAVALIDATOR_4292E2ED01EF_INCLUDED
#define _INC_CINTFDATAVALIDATOR_4292E2ED01EF_INCLUDED

#include <map>
#include "CIntfDataRuleValidatorString.h"
#include "CIntfDataRuleValidatorLong.h"
#include "CIntfDataRuleValidatorDouble.h"
#include "CIntfDataRuleValidatorAny.h"

#include "iData_Provider_s.hh"
class CIntfDataRuleSet;

class CData_Provider;
class CIntfDataValidatorLong;

//##ModelId=4292E2ED01EF
class CIntfDataValidator 
{
protected:
	//##ModelId=42934B7A00E4
	CData_Provider* m_pData_Provider;


private:
	//##ModelId=4292EF960395
	std::multimap<std::string,CIntfDataRuleSet*> m_RuleSetList;

public:
	//##ModelId=42A0348701B0
	CIntfDataRuleValidatorString m_ValidatorString;

	//##ModelId=42A0348A0006
	CIntfDataRuleValidatorLong m_ValidatorLong;

	//##ModelId=42A0348B03B4
	CIntfDataRuleValidatorDouble m_ValidatorDouble;

	//##ModelId=42A0348E01D8
	CIntfDataRuleValidatorAny m_ValidatorAny;

	//##ModelId=42A0371701A4
	bool validateAny(const std::string& Name, const std::string& Key, CORBA::Any& Value);

	//##ModelId=429D6FDC029F
	std::multimap<std::string,CIntfDataRuleSet*> getRuleSetList();

	//##ModelId=4293726D033F
	void EventLogValidationFailure(const std::string& Message);


	//##ModelId=42934C9A0238
	void log(const std::string& Message, long Level);

	//##ModelId=42934C6201F6
	void setpData_Provider(CData_Provider* value);

	//##ModelId=4293427802CC
	void loadRule(const std::string& Name, const std::string& Key, const std::string& Comp, const std::string& Value, const std::string& Default = DEF ::Inv_String      );

	//##ModelId=4293289901D3
	bool validateLong(const std::string& Name, const std::string& Key,  long& Value  );

	//##ModelId=429328A202DC
	bool validateDouble(const std::string& Name, const std::string& Key,  double& Value  );

	//##ModelId=4292FAF203D4
	CIntfDataValidator( );

	//##ModelId=4292E32701DE
	bool validateString(const std::string& Name, const std::string& Key,  std::string &Value  );

	//##ModelId=4292E35C028F
	void insertRuleSet(const std::string& Name,  CIntfDataRuleSet* pIntfDataRuleSet   );

};

#endif /* _INC_CINTFDATAVALIDATOR_4292E2ED01EF_INCLUDED */
