// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDATA_PROVIDER_RUNTIMECONTROLLER_42E7596800C1_INCLUDED
#define _INC_CDATA_PROVIDER_RUNTIMECONTROLLER_42E7596800C1_INCLUDED

#include <string>

#include "cCBS_Time.h"
#include "CData_Provider.h"

//##ModelId=42E7596800C1
class CData_Provider_RuntimeController 
{
public:
	//##ModelId=42E77F380346
	void logTime(const std::string &Action);

	//##ModelId=42E759D202B8
	virtual ~CData_Provider_RuntimeController();

	//##ModelId=42E759D202C2
	CData_Provider_RuntimeController(CData_Provider* pDataProvider, const std::string& FunctionName, const std::string &Key, const std::string &Name);


protected:
	//##ModelId=42E75A510120
	CData_Provider * m_pData_Provider;

private:
	//##ModelId=42E759D202CC
	void log(const std::string& Message, long Level);

	//##ModelId=42E75EC40026
	std::string m_Key;

	//##ModelId=42E75ECB0294
	std::string m_Name;

	//##ModelId=42E759CB00C3
	std::string m_FunctionName;

	//##ModelId=42E759CB00CD
	CBS_LocalTime m_CreationTime;

};

#endif /* _INC_CDATA_PROVIDER_RUNTIMECONTROLLER_42E7596800C1_INCLUDED */
