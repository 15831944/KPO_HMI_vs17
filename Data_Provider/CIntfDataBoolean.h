// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CINTFDATABOOLEAN_40BC54B9017A_INCLUDED
#define _INC_CINTFDATABOOLEAN_40BC54B9017A_INCLUDED

#include "CIntfData.h"

//##ModelId=40BC54B9017A
class CIntfDataBoolean : public CIntfData
  
{
public:
  //##ModelId=40D29EEA029F
  virtual void showContent(long Level);

	//##ModelId=44FE999A02D0
  virtual std::string getContent();

	//##ModelId=40BC54EF006E
	CIntfDataBoolean( CData_Provider * pData_Provider, const std::string &Name, const std::string &Key);

	//##ModelId=40BC5510000A
	virtual ~CIntfDataBoolean();

	//##ModelId=40BC551200AD
	bool getData();

	//##ModelId=40BC55120252
	void setData(bool value);

private:
	//##ModelId=40BC54D50231
	bool m_Data;

};

#endif /* _INC_CINTFDATABOOLEAN_40BC54B9017A_INCLUDED */
