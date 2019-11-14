// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_RUNTIMECONTROLLER_42E743820304_INCLUDED
#define _INC_CSMC_RUNTIMECONTROLLER_42E743820304_INCLUDED

#include <string>
#include "CDateTime.h"
#include "cCBS_Time.h"


//##ModelId=42E743820304
class CSMC_RuntimeController 
{
public:
	//##ModelId=42E7819B02A1
	void logTime(const std::string& Action);


	//##ModelId=42E7439E0305
	virtual ~CSMC_RuntimeController();

	//##ModelId=42E7439F00CD
	CSMC_RuntimeController(const std::string& FunctionName);

private:
	//##ModelId=42E744A5017C
	void log(const std::string& Message, long Level);

	//##ModelId=42E743B80208
	std::string m_FunctionName;

	//##ModelId=42E743C20053
	CBS_LocalTime m_CreationTime;

};

#endif /* _INC_CSMC_RUNTIMECONTROLLER_42E743820304_INCLUDED */
