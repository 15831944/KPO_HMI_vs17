// Copyright (C) 2011 SMS Siemag AG

#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <sstream>

#include "cCBS_AccessSync.h"
#include "cCBS_StdMutex.h"

#include "cCBS_StdLog_Task.h"
#include "cCBS_StdFrame_Component.h"
#include "cCBS_StdInitBase.h"

#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdCORBA_Task.h"
#include "cCBS_StdEventSender_Task.h"
#include "cCBS_StdEventHandler_Task.h"

#include "cCBS_StdEventHandler.h"
#include "cCBS_StdEvent_Task.h"


//##ModelId=40EAA0930239
cCBS_StdEvent_Task* cCBS_StdEvent_Task::m_Instance = 0;

std::string cCBS_StdEvent_Task::getStateDetails()
{
  std::map<std::string, cCBS_StdEventHandler_Task*> EventHandlerTaskList = getEventHandlerTaskList();
  std::map<std::string, cCBS_StdEventHandler_Task*>::iterator it;

  std::string StateDetails = getTaskName();

  StateDetails = StateDetails + "::getStateDetails()" + "\n";

  for ( it = EventHandlerTaskList.begin(); it != EventHandlerTaskList.end(); ++it)
  {
    if ( it->second )
    {
      StateDetails = StateDetails + it->second->getStateDetails() + "\n";
    }
  }

  return StateDetails;
}

//##ModelId=40EAA0930213
cCBS_StdEvent_Task::~cCBS_StdEvent_Task()
{
}

//##ModelId=40EAA0930216
cCBS_StdEvent_Task::cCBS_StdEvent_Task() 
{
  std::string TaskName      ;
  std::string ServiceName   ;
  std::string ChannelName   ;
  std::string ServiceName2  ;
  std::string ChannelName2  ;
  
  cCBS_StdEventHandler_Task * pCBS_StdEventHandler_Task = 0;
  cCBS_StdEventSender_Task * pCBS_StdEventSender_Task = 0;

  // ********************************************************************************************
  // reading values for EventHandlerTask == former Consumer
  // ********************************************************************************************
  std::vector<std::string> EventHandlerTaskList;

  if ( !cCBS_StdInitBase::getInstance()->replaceWithEntry("EventService","EventHandlerTaskList" ,EventHandlerTaskList) )
  {
    cCBS_StdInitBase::getInstance()->replaceWithEntry("EventService","EvChannelName"  ,ChannelName);
    cCBS_StdInitBase::getInstance()->replaceWithEntry("EventService","EvServiceName"  ,ServiceName);
    cCBS_StdInitBase::getInstance()->replaceWithEntry("EventService","EvChannelName2" ,ChannelName2);
    cCBS_StdInitBase::getInstance()->replaceWithEntry("EventService","EvServiceName2" ,ServiceName2);

    TaskName = "EventHandlerTask";

    pCBS_StdEventHandler_Task = new cCBS_StdEventHandler_Task(this, TaskName, ChannelName, ServiceName, ChannelName2, ServiceName2);

    registerEventHandlerTask(pCBS_StdEventHandler_Task, TaskName);

    registerSubTask(pCBS_StdEventHandler_Task, TaskName);
  }
  else
  {
    std::vector<std::string>::iterator it;

    for ( it = EventHandlerTaskList.begin(); it != EventHandlerTaskList.end(); ++it)
    {
      TaskName   = (*it);

      cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"EvChannelName"  ,ChannelName);
      cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"EvServiceName"  ,ServiceName);
      cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"EvChannelName2" ,ChannelName2);
      cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"EvServiceName2" ,ServiceName2);

      pCBS_StdEventHandler_Task = new cCBS_StdEventHandler_Task(this, TaskName, ChannelName, ServiceName, ChannelName2, ServiceName2);

      registerEventHandlerTask(pCBS_StdEventHandler_Task, TaskName);

      registerSubTask(pCBS_StdEventHandler_Task, TaskName);

    }
  }
  // ********************************************************************************************
  // reading values for EventSenderTask == former Sender
  // ********************************************************************************************
  std::vector<std::string> EventSenderTaskList;

  if ( !cCBS_StdInitBase::getInstance()->replaceWithEntry("EventService","EventSenderTaskList" ,EventSenderTaskList) )
  {
    cCBS_StdInitBase::getInstance()->replaceWithEntry("EventService","EvChannelName"  ,ChannelName);
    cCBS_StdInitBase::getInstance()->replaceWithEntry("EventService","EvServiceName"  ,ServiceName);
    cCBS_StdInitBase::getInstance()->replaceWithEntry("EventService","EvChannelName2" ,ChannelName2);
    cCBS_StdInitBase::getInstance()->replaceWithEntry("EventService","EvServiceName2" ,ServiceName2);

    TaskName = "EventSenderTask";

    pCBS_StdEventSender_Task = new cCBS_StdEventSender_Task(this, TaskName, ChannelName, ServiceName, ChannelName2, ServiceName2);

    registerEventSenderTask(pCBS_StdEventSender_Task, TaskName);

    registerSubTask(pCBS_StdEventSender_Task, TaskName);
  }
  else
  {
    std::vector<std::string>::iterator it;

    for ( it = EventSenderTaskList.begin(); it != EventSenderTaskList.end(); ++it)
    {
      TaskName   = (*it);

      cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"EvChannelName"  ,ChannelName);
      cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"EvServiceName"  ,ServiceName);
      cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"EvChannelName2" ,ChannelName2);
      cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"EvServiceName2" ,ServiceName2);

      pCBS_StdEventSender_Task = new cCBS_StdEventSender_Task(this, TaskName, ChannelName, ServiceName, ChannelName2, ServiceName2);

      registerEventSenderTask(pCBS_StdEventSender_Task, TaskName);

      registerSubTask(pCBS_StdEventSender_Task, TaskName);

    }
  }
}

//##ModelId=40EAA0930218
cCBS_StdEvent_Task* cCBS_StdEvent_Task::getInstance()
{
  if ( m_Instance == 0 )
  {
    m_Instance = new cCBS_StdEvent_Task();
  }
  return m_Instance;
}


//##ModelId=40EAA0930229
bool cCBS_StdEvent_Task::handleEvent(const FRIESEvent & Event)
{
  bool RetValue = false;

  std::map<std::string, cCBS_StdEventHandler_Task*> EventHandlerTaskList = getEventHandlerTaskList();

  std::map<std::string, cCBS_StdEventHandler_Task*>::iterator it;

  for ( it = EventHandlerTaskList.begin(); it != EventHandlerTaskList.end(); ++it)
  {
    if ( it->second )
    {
      it->second->handleEvent(Event);
      RetValue = true;
    }
  }

  return RetValue;
}

//##ModelId=40EAA0930226
void cCBS_StdEvent_Task::ownStartUp()
{
  cCBS_StdFrame_Task::ownStartUp();
  setWorking(true);
}

//##ModelId=40EAA0930223
void cCBS_StdEvent_Task::ownRunDown()
{
  cCBS_StdFrame_Task::ownRunDown();
  setWorking(false);
}

//##ModelId=40EAA0930220
bool cCBS_StdEvent_Task::initialize()
{
  return cCBS_StdFrame_Task::initialize();
}



//##ModelId=40EAA093022E
void cCBS_StdEvent_Task::afterSubtaskStart()
{
}

//##ModelId=40EAA0930231
bool cCBS_StdEvent_Task::sendEvent(const FRIESEvent& Event)
{
  return sendEvent(Event, true );
}


//##ModelId=48A53B920193
bool cCBS_StdEvent_Task::sendEvent(const FRIESEvent& Event, bool External)
{
  return sendEvent(Event, External, "");
}

bool cCBS_StdEvent_Task::sendEvent(const FRIESEvent& Event, bool External, const std::string& TaskName)
{
  bool RetValue = false;

  std::map<std::string, cCBS_StdEventSender_Task*> EventSenderTaskList = getEventSenderTaskList();
  std::map<std::string, cCBS_StdEventSender_Task*>::iterator it;

  for ( it = EventSenderTaskList.begin(); it != EventSenderTaskList.end(); ++it)
  {
    if ( !TaskName.empty() )
    {
      if ( TaskName == it->first )
      {
        if (External)
        {
          RetValue = it->second->sendEvent(Event);
        }
        else
        {
          RetValue = handleEvent(Event);
        }

        break;
      }
    }
    else
    {
      if (External)
      {
        RetValue = it->second->sendEvent(Event);
      }
      else
      {
        RetValue = handleEvent(Event);
      }
    }
  }
  
  return RetValue;
}




//##ModelId=40EBCAAE01D4
bool cCBS_StdEvent_Task::registerEventHandler(cCBS_StdEventHandler* pEventHandler, const std::string& TaskName /*= "" */)
{
  bool RetValue = false;

  std::string ActTaskName(TaskName);

  // check if TaskName is valid, otherwise take defaults from ini file
  if ( ActTaskName.empty() )
  {
    ActTaskName = "EventHandlerTask";

    // check if other Tasks have been defined, use first entry as default now!
    std::vector<std::string> EventHandlerTaskList;

    if ( cCBS_StdInitBase::getInstance()->replaceWithEntry("EventService","EventHandlerTaskList" ,EventHandlerTaskList) )
    {
      std::vector<std::string>::iterator it;

      for ( it = EventHandlerTaskList.begin(); it != EventHandlerTaskList.end(); ++it)
      {
        ActTaskName = (*it); 
        break;
      }
    }
  }

  std::map<std::string, cCBS_StdEventHandler_Task*> EventHandlerTaskList = getEventHandlerTaskList();
  std::map<std::string, cCBS_StdEventHandler_Task*>::iterator it;

  // check if TaskName is valid, otherwise take ServerName or EventTaskName from ini file
  for ( it = EventHandlerTaskList.begin(); it != EventHandlerTaskList.end(); ++it)
  {
    if ( it->first == ActTaskName )
    {
      pEventHandler->setEventHandlerTaskName(ActTaskName);
      RetValue = it->second->registerEventHandler(pEventHandler);
    }
  }

  return RetValue;
}
  


//##ModelId=41499CA60384
void cCBS_StdEvent_Task::log(const std::string & Message, long Level)
{
  cCBS_StdFrame_Task::log(Message, Level);
}

//##ModelId=44FE88B301BD
long cCBS_StdEvent_Task::checkWorkingState()
{
  std::map<std::string, cCBS_StdEventHandler_Task*> EventHandlerTaskList = getEventHandlerTaskList();

  std::map<std::string, cCBS_StdEventHandler_Task*>::iterator it;

  for ( it = EventHandlerTaskList.begin(); it != EventHandlerTaskList.end(); ++it)
  {
    if ( it->second->isWorking() )
    {
      setWorking(true);
    }
    else
    {
      setWorking(false);
      break;
    }
  }

  return getOwnWorkState();
}


//##ModelId=48AD0F1A0108
void cCBS_StdEvent_Task::doOnThreadControlError()
{
  cCBS_StdFrame_Task::doOnThreadControlError();
}

// inserting new item to actual container
void cCBS_StdEvent_Task::registerEventHandlerTask(cCBS_StdEventHandler_Task* pCBS_StdEventHandler_Task, const std::string TaskName)
{
  cCBS_StdMutex CBS_StdMutex("m_EventHandlerTaskList");

  std::map<std::string, cCBS_StdEventHandler_Task*>::iterator it = m_EventHandlerTaskList.find(TaskName);
  
  if ( it == m_EventHandlerTaskList.end() )
  {
    m_EventHandlerTaskList.insert ( std::pair<std::string,cCBS_StdEventHandler_Task*> (TaskName, pCBS_StdEventHandler_Task) );
  }
}

// inserting new item to actual container
void cCBS_StdEvent_Task::registerEventSenderTask(cCBS_StdEventSender_Task* pCBS_StdEventSender_Task, const std::string TaskName)
{
  cCBS_StdMutex CBS_StdMutex("m_EventSenderTaskList");

  std::map<std::string, cCBS_StdEventSender_Task*>::iterator it = m_EventSenderTaskList.find(TaskName);
  
  if ( it == m_EventSenderTaskList.end() )
  {
    m_EventSenderTaskList.insert ( std::pair<std::string,cCBS_StdEventSender_Task*> (TaskName, pCBS_StdEventSender_Task) );
  }
}

// returning a copy of actual container
std::map<std::string, cCBS_StdEventHandler_Task*> cCBS_StdEvent_Task::getEventHandlerTaskList()
{
  cCBS_StdMutex CBS_StdMutex("m_EventHandlerTaskList");

  std::map<std::string, cCBS_StdEventHandler_Task*> EventHandlerTaskList = m_EventHandlerTaskList;

  return EventHandlerTaskList;
}

// returning a copy of actual container
std::map<std::string, cCBS_StdEventSender_Task*> cCBS_StdEvent_Task::getEventSenderTaskList()
{
  cCBS_StdMutex CBS_StdMutex("m_EventSenderTaskList");

  std::map<std::string, cCBS_StdEventSender_Task*> EventSenderTaskList = m_EventSenderTaskList;

  return EventSenderTaskList;
}

