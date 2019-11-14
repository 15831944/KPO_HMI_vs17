// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_MUTEXHANDLER_42C3ADC902B5_INCLUDED
#define _INC_CSMC_MUTEXHANDLER_42C3ADC902B5_INCLUDED

#include <string>
#include <map>

#include "cCBS_Mutex.h"

//##ModelId=42C3ADC902B5
class CSMC_MutexHandler 
{
public:
	//##ModelId=42C3AE0400E3
	cCBS_Mutex* findMutex(const std::string& MutexName);

	//##ModelId=42C3AE0400E5
	cCBS_Mutex* registerMutex(const std::string& MutexName);

	//##ModelId=42C3AE0400ED
	bool lock(const std::string& MutexName);

	//##ModelId=42C3AE0400F7
	bool unlock(const std::string& MutexName);

	//##ModelId=42C3AE0400F9
	bool tryLock(const std::string& MutexName);

	//##ModelId=42C3AE040101
	static CSMC_MutexHandler* getInstance();

	//##ModelId=42C3AE04010B
	virtual ~CSMC_MutexHandler();

	//##ModelId=42C3AE040115
	CSMC_MutexHandler();

	//##ModelId=42C3AE04011F
	void log(const std::string& Message, long Level);

private:
	//##ModelId=42C3B2420320
	cCBS_Mutex theMutex;

	//##ModelId=42C3AE0B029C
	static CSMC_MutexHandler* m_Instance;

	//##ModelId=42C3AE0B02A6
	std::map<std::string,cCBS_Mutex*> m_MutexList;

};

#endif /* _INC_CSMC_MUTEXHANDLER_42C3ADC902B5_INCLUDED */
