// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CINTFDATADOUBLE_40BC44440231_INCLUDED
#define _INC_CINTFDATADOUBLE_40BC44440231_INCLUDED

#include "CIntfData.h"

//##ModelId=40BC44440231
class CIntfDataDouble : public CIntfData
  
{
public:
  //##ModelId=40D29EEF00EE
  virtual void showContent(long Level);

	//##ModelId=44FE999A021C
  virtual std::string getContent();

	//##ModelId=40BC445A02BF
	virtual ~CIntfDataDouble();

	//##ModelId=40BC445A02C9
	CIntfDataDouble( CData_Provider * pData_Provider, const std::string &Name, const std::string &Key);

	//##ModelId=40BC458C014C
	double getData();

	//##ModelId=40BC458C032D
	void setData(double value);

private:
	//##ModelId=40BC44AF0312
	double m_Data;

};

#endif /* _INC_CINTFDATADOUBLE_40BC44440231_INCLUDED */
