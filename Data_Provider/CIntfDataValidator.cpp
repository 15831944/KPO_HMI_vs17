// Copyright (C) 2011 SMS Siemag AG

#include <sstream>
#include <string>
#include <map>

#include "CIntfData.h"
#include "CIntfDataRuleSet.h"
#include "CData_Provider.h"
#include "cCBS_StdInitBase.h"

#include "CIntfDataValidator.h"


//##ModelId=4292FAF203D4
CIntfDataValidator::CIntfDataValidator( )
: m_pData_Provider(0)
{
  m_ValidatorString.setpValidator(this);
  m_ValidatorLong.setpValidator(this);
  m_ValidatorDouble.setpValidator(this);
  m_ValidatorAny.setpValidator(this);
}

//##ModelId=42934C6201F6
void CIntfDataValidator::setpData_Provider(CData_Provider* value)
{
	m_pData_Provider = value;
	return;
}

//##ModelId=4292E35C028F
void CIntfDataValidator::insertRuleSet(const std::string& Name,  CIntfDataRuleSet* pIntfDataRuleSet   )
{
  std::multimap<std::string,CIntfDataRuleSet*>::iterator it;

  if (pIntfDataRuleSet)
  {
    it = m_RuleSetList.find(Name);
    m_RuleSetList.insert(it,std::pair<std::string,CIntfDataRuleSet*>(Name,pIntfDataRuleSet));
  }
  else
  {
    log("CIntfDataValidator::insertRuleSet() : pIntfDataRuleSet invalid!",1);
  }
}


//##ModelId=4292E32701DE
bool CIntfDataValidator::validateString(const std::string& Name, const std::string& Key,  std::string &Value  )
{
  bool RetValue = true;

  std::multimap<std::string,CIntfDataRuleSet*>::iterator it;

  it = m_RuleSetList.find(Name);

  for ( it ; it != m_RuleSetList.end(); ++it)
  {
    // find all rules for the name to be checked
    if ( it->second->getName() == Name )
    {
      m_ValidatorString.validate(it->second,Value);
    }
  }

	return RetValue;
}

//##ModelId=4293289901D3
bool CIntfDataValidator::validateLong(const std::string& Name, const std::string& Key,  long& Value  )
{
  bool RetValue = true;

  std::multimap<std::string,CIntfDataRuleSet*>::iterator it;

  it = m_RuleSetList.find(Name);

  for ( it ; it != m_RuleSetList.end(); ++it)
  {
    // find all rules for the name to be checked
    if ( it->second->getName() == Name )
    {
      m_ValidatorLong.validate(it->second,Value);
    }
  }

	return RetValue;
}

//##ModelId=429328A202DC
bool CIntfDataValidator::validateDouble(const std::string& Name, const std::string& Key,  double& Value  )
{
  bool RetValue = true;

  std::multimap<std::string,CIntfDataRuleSet*>::iterator it;

  it = m_RuleSetList.find(Name);

  for ( it ; it != m_RuleSetList.end(); ++it)
  {
    // find all rules for the name to be checked
    if ( it->second->getName() == Name )
    {
      m_ValidatorDouble.validate(it->second,Value);
    }
  }

	return RetValue;
}


//##ModelId=42A0371701A4
bool CIntfDataValidator::validateAny(const std::string& Name, const std::string& Key, CORBA::Any& Value)
{
  bool RetValue = true;

  std::multimap<std::string,CIntfDataRuleSet*>::iterator it;

  it = m_RuleSetList.find(Name);

  for ( it ; it != m_RuleSetList.end(); ++it)
  {
    // find all rules for the name to be checked
    if ( it->second->getName() == Name )
    {
      m_ValidatorAny.validate(it->second,Value);
    }
  }

	return RetValue;
}



//##ModelId=4293427802CC
void CIntfDataValidator::loadRule(const std::string& Name, 
                                  const std::string& Key, 
                                  const std::string& Comp, 
                                  const std::string& Value, 
                                  const std::string& Default   )
{
  std::string Type = CIntfData::String;

  CIntfDataRuleSet *pRuleSet = new CIntfDataRuleSet(Name,Key,Comp,Value,Default);

  insertRuleSet(Name,pRuleSet);
}

//##ModelId=42934C9A0238
void CIntfDataValidator::log(const std::string& Message, long Level)
{
  if (m_pData_Provider)
  {
    m_pData_Provider->log(Message,Level);
  }
}



//##ModelId=4293726D033F
void CIntfDataValidator::EventLogValidationFailure(const std::string& Message)
{
  if (m_pData_Provider)
  {
    m_pData_Provider->EventLogValidationFailure(Message);
  }
}



//##ModelId=429D6FDC029F
std::multimap<std::string,CIntfDataRuleSet*> CIntfDataValidator::getRuleSetList()
{
	return m_RuleSetList;
}
