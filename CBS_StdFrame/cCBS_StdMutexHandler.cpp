// Copyright (C) 2004 SMS Demag AG

#include <iostream>
#include <sstream>

#include "cCBS_StdEventLogFrameController.h"

#include "cCBS_StdLog_Task.h"
#include "cCBS_StdMutexHandler.h"



//##ModelId=48AD1B1F007E
cCBS_StdMutexHandler* cCBS_StdMutexHandler::m_Instance = 0;

//##ModelId=48AD1B2702A4
cCBS_StdMutexHandler::~cCBS_StdMutexHandler()
{
  std::map<std::string,cCBS_LocalMutex*>::iterator it;

  for ( it = m_MutexList.begin() ; it != m_MutexList.end() ; ++it )
  {
    delete it->second;
  }
}

//##ModelId=48AD1B2702AE
cCBS_StdMutexHandler::cCBS_StdMutexHandler()
{
}

//##ModelId=48AD1B270290
cCBS_StdMutexHandler* cCBS_StdMutexHandler::getInstance()
{
  if ( m_Instance == 0 )
  {
    m_Instance = new cCBS_StdMutexHandler();
  }

	return m_Instance;
}


//##ModelId=48AD1B27025E
cCBS_LocalMutex* cCBS_StdMutexHandler::findMutex(const std::string& MutexName)
{
  cCBS_LocalMutex* ActMutex = 0;

  std::map<std::string,cCBS_LocalMutex*>::iterator it;

  it = m_MutexList.find(MutexName);

  if ( it != m_MutexList.end() )
  {
    ActMutex = it->second;
  }

	return ActMutex;
}

//##ModelId=48AD1B270268
cCBS_LocalMutex* cCBS_StdMutexHandler::registerMutex(const std::string& MutexName)
{
  theMutex.lock();

  cCBS_LocalMutex* ActMutex = findMutex(MutexName);

  // mutex not yet defined
  if ( !ActMutex )
  {
    ActMutex = new cCBS_LocalMutex();
    m_MutexList.insert( std::pair<std::string,cCBS_LocalMutex*>(MutexName,ActMutex) ); 
  }

  theMutex.unlock();

	return ActMutex;
}

//##ModelId=48AD1B270272
bool cCBS_StdMutexHandler::lock(const std::string& MutexName)
{
  bool RetValue = false;
  cCBS_LocalMutex* ActMutex = registerMutex(MutexName);

  if ( ActMutex && 0 == ActMutex->lock() )
  {
    RetValue = true;
  }

	return RetValue;
}

//##ModelId=48AD1B27027C
bool cCBS_StdMutexHandler::unlock(const std::string& MutexName)
{
  bool RetValue = false;
  cCBS_LocalMutex* ActMutex = findMutex(MutexName);

  if ( ActMutex && 0 == ActMutex->unlock() )
  {
    RetValue = true;
  }

	return RetValue;
}

//##ModelId=48AD1B270286
bool cCBS_StdMutexHandler::tryLock(const std::string& MutexName)
{
  bool RetValue = false;

  cCBS_LocalMutex* ActMutex = registerMutex(MutexName);

  if (ActMutex)
  {
    long counter = 0;

    // provide against deadlock after 5 sec. !
    while ( (RetValue = ActMutex->tryLock()) == false && counter < 5000)
    {
      Sleep(1);
      counter++;
    }

    if ( counter > 2000 )
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
    pEventLog->EL_MutexAccessError(Message, MutexName.c_str(), GetCurrentThreadId(),"cCBS_StdMutexHandler::tryLock");
  }

	return RetValue;
}




//##ModelId=48AD1B2702B8
void cCBS_StdMutexHandler::log(const std::string& Message, long Level)
{
  cCBS_StdLog_Task::getInstance()->log(Message,Level);
}

