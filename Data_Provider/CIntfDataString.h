// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CINTFDATASTRING_40B740AA00DF_INCLUDED
#define _INC_CINTFDATASTRING_40B740AA00DF_INCLUDED

#include "CIntfData.h"

//##ModelId=40B740AA00DF
class CIntfDataString : public CIntfData
  
{
public:
  //##ModelId=40D29EFA0003
  virtual void showContent(long Level);

	//##ModelId=44FE999A00BE
  virtual std::string getContent();

	//##ModelId=40B740D200EC
	std::string  getData();

	//##ModelId=40B740D200F6
	void setData(const std::string& value);

	//##ModelId=40B740D20100
	virtual ~CIntfDataString();

	//##ModelId=40B740D2010A
	CIntfDataString( CData_Provider * pData_Provider, const std::string &Name, const std::string &Key);

private:
	//##ModelId=40B740E00093
	std::string m_Data;

};

#endif /* _INC_CINTFDATASTRING_40B740AA00DF_INCLUDED */
