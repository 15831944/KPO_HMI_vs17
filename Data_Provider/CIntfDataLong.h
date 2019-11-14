// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CINTFDATALONG_40B6F0AE0019_INCLUDED
#define _INC_CINTFDATALONG_40B6F0AE0019_INCLUDED

#include "CIntfData.h"

//##ModelId=40B6F0AE0019
class CIntfDataLong : public CIntfData
  
{
private:
	//##ModelId=40B6FE4000BF
	long m_Data;

public:
  //##ModelId=40D29EBF00C7
  virtual void showContent(long Level);

	//##ModelId=44FE999A0172
  virtual std::string getContent();

	//##ModelId=40B72F290130
	virtual ~CIntfDataLong();

	//##ModelId=40B72F2A03DB
	CIntfDataLong( CData_Provider * pData_Provider, const std::string &Name, const std::string &Key);

	//##ModelId=40B6F651030D
	long getData();

	//##ModelId=40B6F6510317
	void setData(long value);

};

#endif /* _INC_CINTFDATALONG_40B6F0AE0019_INCLUDED */
