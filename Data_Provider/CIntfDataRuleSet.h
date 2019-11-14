// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CINTFDATARULESET_4292ED7600CB_INCLUDED
#define _INC_CINTFDATARULESET_4292ED7600CB_INCLUDED

#include <string>
#include "iData_Provider_s.hh"

class CIntfDataValidator;

//##ModelId=42A034450369
class CIntfDataRuleSet 
{
protected:
public:
	//##ModelId=42A04A3D0295
	std::string& getKey();

	//##ModelId=42A049E1012E
	std::string& getComparator();

	//##ModelId=42A049F20261
	std::string& getDefault();

	//##ModelId=42A04A1703A7
	std::string& getValue();

	//##ModelId=42A049FC02D5
	std::string& getName();

	//##ModelId=42A038230375
	static std::string m_NE;

	//##ModelId=42A03823036B
	static std::string m_EQ;

	//##ModelId=42A03823037F
	static std::string m_GT;

	//##ModelId=42A038230393
	static std::string m_LT;

	//##ModelId=42A03823039D
	static std::string m_GE;

	//##ModelId=42A0382303A7
	static std::string m_LE;

	//##ModelId=42A034FD0208
	virtual ~CIntfDataRuleSet();

	//##ModelId=42A034FD0226
	CIntfDataRuleSet( const std::string & Name, const std::string& Key, const std::string& Comp, const std::string &Value, const std::string &Default = DEF::Inv_String);

private:
	//##ModelId=42A035B803C2
	std::string m_Key;
	//##ModelId=42A035AC02D4
	std::string m_Name;
	//##ModelId=42A035BE0353
	std::string m_Comparator;
	//##ModelId=42A035CA018F
	std::string m_Value;

	//##ModelId=42A035CF03DB
	std::string m_Default;






};

#endif /* _INC_CINTFDATARULESET_4292ED7600CB_INCLUDED */
