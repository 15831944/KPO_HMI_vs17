// Copyright (C) 2004 SMS Demag AG

#include "CSMC_MutexHandler.h"
#include "CSMC_Mutex.h"


//##ModelId=42C3AE2901CD
CSMC_Mutex::~CSMC_Mutex()
{
  CSMC_MutexHandler::getInstance()->unlock(m_MutexName);
}

//##ModelId=42C3AE2901CE
CSMC_Mutex::CSMC_Mutex(const std::string& MutexName /*= "CSMC_Mutex"*/)
:m_MutexName(MutexName)
{
  CSMC_MutexHandler::getInstance()->lock(m_MutexName); //classes that instantiate this class expect to hold the mutex so we need to lock here
}

