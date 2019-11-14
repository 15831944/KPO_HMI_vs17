// Copyright (C) 2011 SMS Siemag AG
#include <string>
#include "CIntfDataRuleSet.h"
#include "CIntfDataValidator.h"



//##ModelId=42A03823037F
std::string CIntfDataRuleSet::m_GT(">");

//##ModelId=429324E10067
std::string CIntfDataRuleSet::m_GE(">=");

//##ModelId=429324AA0370
std::string CIntfDataRuleSet::m_EQ("==");

//##ModelId=429324ED0372
std::string CIntfDataRuleSet::m_LE("<=");

//##ModelId=42A038230393
std::string CIntfDataRuleSet::m_LT("<");

//##ModelId=429326EC03AF
std::string CIntfDataRuleSet::m_NE("!=");



//##ModelId=42A034FD0226
CIntfDataRuleSet::CIntfDataRuleSet( const std::string & Name, 
                                    const std::string& Key, 
                                    const std::string& Comp, 
                                    const std::string &Value, 
                                    const std::string &Default)
: m_Name(Name)
, m_Key(Key)
, m_Comparator(Comp)
, m_Value(Value)
, m_Default(Default)
{
}



//##ModelId=42A034FD0208
CIntfDataRuleSet::~CIntfDataRuleSet()
{
}



//##ModelId=42A049FC02D5
std::string& CIntfDataRuleSet::getName()
{
	return m_Name;
}







//##ModelId=42A049E1012E
std::string& CIntfDataRuleSet::getComparator()
{
	return m_Comparator;
}

//##ModelId=42A049F20261
std::string& CIntfDataRuleSet::getDefault()
{
	return m_Default;
}

//##ModelId=42A04A1703A7
std::string& CIntfDataRuleSet::getValue()
{
	return m_Value;
}



//##ModelId=42A04A3D0295
std::string& CIntfDataRuleSet::getKey()
{
	return m_Key;
}

