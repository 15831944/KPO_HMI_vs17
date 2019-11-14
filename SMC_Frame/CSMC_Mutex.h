// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_MUTEX_42C3AE100235_INCLUDED
#define _INC_CSMC_MUTEX_42C3AE100235_INCLUDED

#include <string>

class CSMC_MutexHandler;

//##ModelId=42C3AE100235
class CSMC_Mutex 
{
public:
	//##ModelId=42C3AE2901CD
	virtual ~CSMC_Mutex();

	//##ModelId=42C3AE2901CE
	CSMC_Mutex(const std::string& MutexName = "CSMC_Mutex");

private:
	//##ModelId=42C3AE2E01AC
	std::string m_MutexName;

};

#endif /* _INC_CSMC_MUTEX_42C3AE100235_INCLUDED */
