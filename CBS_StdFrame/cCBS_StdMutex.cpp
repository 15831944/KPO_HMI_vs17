// Copyright (C) 1999 - 2004 SMS Demag AG

#include "cCBS_StdMutexHandler.h"
#include "cCBS_StdMutex.h"



//##ModelId=48AD1B360193
cCBS_StdMutex::~cCBS_StdMutex()
{
  cCBS_StdMutexHandler::getInstance()->unlock(m_MutexName);
}

//##ModelId=48AD1B360194
cCBS_StdMutex::cCBS_StdMutex(const std::string& MutexName /*= "cCBS_StdMutex"*/)
:m_MutexName(MutexName)
{
	cCBS_StdMutexHandler::getInstance()->lock(m_MutexName);
}

