// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CINTFDATASEQUENCE_40B6F0BD00E3_INCLUDED
#define _INC_CINTFDATASEQUENCE_40B6F0BD00E3_INCLUDED

#include "CIntfData.h"
#include <string>
#include <sstream>
#include <list>
#include <algorithm>

//##ModelId=40B6F0BD00E3
class CIntfDataAny : public CIntfData
  
{
protected:
	//##ModelId=40B6F12C0060
	CORBA::Any m_pData;

	//##ModelId=4292EF3B0237
  long m_Indent;

public:
	//##ModelId=426CEACC0221
	std::string getContent();


  //##ModelId=412C5A6B00DD
	virtual void showContent(long Level);

	//##ModelId=40B6F10803E4
	CORBA::Any& getData();

	//##ModelId=40B6F1090006
	void setData(CORBA::Any& value);

	//##ModelId=40B6F1090010
	CIntfDataAny( CData_Provider* pData_Provider, const std::string &Name, const std::string &Key);

	//##ModelId=40B6F1090012
	virtual ~CIntfDataAny();

private:

  // Have a factory for DynAny objects
	//##ModelId=412F35AD0129
  DynamicAny::DynAnyFactory_var m_DynAnyFact;
};

#endif /* _INC_CINTFDATASEQUENCE_40B6F0BD00E3_INCLUDED */
