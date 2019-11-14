// Copyright (C) 2011 SMS Siemag AG

#include "CIntfDataValidator.h"
#include "CIntfDataRuleValidator.h"



//##ModelId=42A042D200DA
void CIntfDataRuleValidator::log(const std::string& Message, long Level)
{
	if (m_pValidator)
  {
    m_pValidator->log(Message,Level);
  }
}

//##ModelId=42A042D200E4
void CIntfDataRuleValidator::EventLogValidationFailure(const std::string& Message)
{
	if (m_pValidator)
  {
    m_pValidator->EventLogValidationFailure(Message);
  }
}

//##ModelId=42A042D9035B
void CIntfDataRuleValidator::setpValidator(CIntfDataValidator* value)
{
	m_pValidator = value;
	return;
}

//##ModelId=42A042F10325
CIntfDataRuleValidator::~CIntfDataRuleValidator()
{
	
}

//##ModelId=42A042F2010A
CIntfDataRuleValidator::CIntfDataRuleValidator() : m_pValidator(0)
{
	
}

