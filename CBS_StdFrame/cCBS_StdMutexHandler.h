// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CCBS_STDMUTEXHANDLER_48AD1AE20215_INCLUDED
#define _INC_CCBS_STDMUTEXHANDLER_48AD1AE20215_INCLUDED

#include <string>
#include <map>

#include "cCBS_CriticalSection.h"

//##ModelId=48AD1AE20215
class cCBS_StdMutexHandler 
{
public:
	//##ModelId=48AD1B27025E
	cCBS_LocalMutex* findMutex(const std::string& MutexName);

	//##ModelId=48AD1B270268
	cCBS_LocalMutex* registerMutex(const std::string& MutexName);

	//##ModelId=48AD1B270272
	bool lock(const std::string& MutexName);

	//##ModelId=48AD1B27027C
	bool unlock(const std::string& MutexName);

	//##ModelId=48AD1B270286
	bool tryLock(const std::string& MutexName);

	//##ModelId=48AD1B270290
	static cCBS_StdMutexHandler* getInstance();

	//##ModelId=48AD1B2702A4
	virtual ~cCBS_StdMutexHandler();

	//##ModelId=48AD1B2702AE
	cCBS_StdMutexHandler();

	//##ModelId=48AD1B2702B8
	void log(const std::string& Message, long Level);

private:

	//##ModelId=48AD682F0231
	cCBS_LocalMutex theMutex;

	//##ModelId=48AD1B1F007E
	static cCBS_StdMutexHandler* m_Instance;

	//##ModelId=48AD1B1F00EC
	std::map<std::string,cCBS_LocalMutex*> m_MutexList;

};

#endif /* _INC_CCBS_STDMUTEXHANDLER_48AD1AE20215_INCLUDED */
