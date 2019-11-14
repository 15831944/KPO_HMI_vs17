// Copyright (C) 2004 SMS Demag AG

#include <iostream>
#include <sstream>

#include "wrapthread.h"

#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdLog_Task.h"

#include "CSMC_MutexHandler.h"



CSMC_MutexHandler* CSMC_MutexHandler::m_Instance = 0;

CSMC_MutexHandler::~CSMC_MutexHandler()
{
  std::map<std::string,cCBS_Mutex*>::iterator it;

  for ( it = m_MutexList.begin() ; it != m_MutexList.end() ; ++it )
  {
    delete it->second;
  }
}

CSMC_MutexHandler::CSMC_MutexHandler()
{
}

CSMC_MutexHandler* CSMC_MutexHandler::getInstance()
{
  if ( m_Instance == 0 )
  {
    m_Instance = new CSMC_MutexHandler();
  }

	return m_Instance;
}

bool CSMC_MutexHandler::lock(const std::string& MutexName)
{
  bool RetValue = false;
  cCBS_Mutex* ActMutex = registerMutex(MutexName);

  if ( ActMutex && 0 == ActMutex->lock() )
  {
    RetValue = true;
  }

	return RetValue;
}

bool CSMC_MutexHandler::unlock(const std::string& MutexName)
{
  bool RetValue = false;
  cCBS_Mutex* ActMutex = findMutex(MutexName);

  if ( ActMutex && 0 == ActMutex->unlock() )
  {
    RetValue = true;
  }

	return RetValue;
}

bool CSMC_MutexHandler::tryLock(const std::string& MutexName)
{
  bool RetValue = false;

  cCBS_Mutex* ActMutex = registerMutex(MutexName);

  if (ActMutex)
  {
    long counter = 0;

    // provide against deadlock after 2 sec. !
    while ( (RetValue = ActMutex->tryLock()) == false && counter < 2000)
    {
      Sleep(1);
      counter++;
    }

    if ( counter > 1000 )
    {
      std::stringstream Message;
      Message << MutexName << " was locked " << counter << " times for thread " << GetCurrentThreadId() ;
      log(Message.str(),2);
    }
  }

  if (!RetValue)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_MutexAccessError(Message, MutexName.c_str(), GetCurrentThreadId(),"CSMC_MutexHandler::tryLock");
  }

	return RetValue;
}


cCBS_Mutex* CSMC_MutexHandler::registerMutex(const std::string& MutexName)
{
  theMutex.lock();

  cCBS_Mutex* ActMutex = findMutex(MutexName);

  // mutex not yet defined
  if ( !ActMutex )
  {
    ActMutex = new cCBS_Mutex();
    m_MutexList.insert( std::pair<std::string,cCBS_Mutex*>(MutexName,ActMutex) ); 
  }

  theMutex.unlock();

	return ActMutex;
}


cCBS_Mutex* CSMC_MutexHandler::findMutex(const std::string& MutexName)
{
  cCBS_Mutex* ActMutex = 0;

  std::map<std::string,cCBS_Mutex*>::iterator it;

  it = m_MutexList.find(MutexName);

  if ( it != m_MutexList.end() )
  {
    ActMutex = it->second;
  }

	return ActMutex;
}






void CSMC_MutexHandler::log(const std::string& Message, long Level)
{
  cCBS_StdLog_Task::getInstance()->log(Message,Level);
}

