// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CCBS_STDMUTEX_48AD1AF90335_INCLUDED
#define _INC_CCBS_STDMUTEX_48AD1AF90335_INCLUDED

//##ModelId=48AD1AF90335
class cCBS_StdMutex 
{
public:
	//##ModelId=48AD1B360193
	virtual ~cCBS_StdMutex();

	//##ModelId=48AD1B360194
	cCBS_StdMutex(const std::string& MutexName = "cCBS_StdMutex");

private:
	//##ModelId=48AD1B3C0281
	std::string m_MutexName;

};

#endif /* _INC_CCBS_STDMUTEX_48AD1AF90335_INCLUDED */
