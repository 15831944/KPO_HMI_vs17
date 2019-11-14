// Copyright (C) 1999 - 2004 SMS Demag AG
#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <string>
#include <vector>
#include <sstream>

#include "cCBS_Time.h"
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdEventHandler.h"
#include "cCBS_StdFrame_TaskController.h"
#include "cCBS_StdMutex.h"

#include "cCBS_StdEvent_Task.h"

#include "cCBS_StdEventHandlerAdapter.h"


//##ModelId=410DFAA20171
cCBS_StdEventHandlerAdapter::cCBS_StdEventHandlerAdapter(cCBS_StdEvent_Task *pEventTask)
: m_pEvent_Task(pEventTask)
, m_NoOfIncomingEvents(0)
, m_pWorkerThread(0)
, m_ThresholdEventQueueNotWorking(-1)
{
  m_Receiver          = cCBS_StdInitBase::getInstance()->m_ServerName;
  m_EventHandlerName  = cCBS_StdInitBase::getInstance()->m_ServerName;

  // init times
  cCBS_Time::localTime(m_EventAcceptanceTime);
  cCBS_Time::localTime(m_EventReceptionTime);
  cCBS_Time::localTime(m_EventRejectionTime);

  cCBS_StdInitBase::getInstance()->replaceWithEntry("EventService","ThresholdEventQueueNotWorking",m_ThresholdEventQueueNotWorking);

  m_pWorkerThread = new cCBS_StdEventHandlerAdapter::cCBS_StdEventHandlerAdapterWorkerThread(this,m_EventHandlerName);
  m_pWorkerThread->setFreeOnTerminate(true);
  m_pWorkerThread->run();

}

cCBS_StdEventHandlerAdapter::cCBS_StdEventHandlerAdapter(cCBS_StdEvent_Task *pEventTask, const std::string EventHandlerName)
: m_pEvent_Task(pEventTask)
, m_NoOfIncomingEvents(0)
, m_pWorkerThread(0)
, m_EventHandlerName(EventHandlerName)
, m_ThresholdEventQueueNotWorking(-1)
{
  m_Receiver = cCBS_StdInitBase::getInstance()->m_ServerName;

  // init times
  cCBS_Time::localTime(m_EventAcceptanceTime);
  cCBS_Time::localTime(m_EventReceptionTime);
  cCBS_Time::localTime(m_EventRejectionTime);

  cCBS_StdInitBase::getInstance()->replaceWithEntry("EventService","ThresholdEventQueueNotWorking",m_ThresholdEventQueueNotWorking);

  m_pWorkerThread = new cCBS_StdEventHandlerAdapter::cCBS_StdEventHandlerAdapterWorkerThread(this,m_EventHandlerName);
  m_pWorkerThread->setFreeOnTerminate(true);
  m_pWorkerThread->run();

}



cCBS_StdEventHandlerAdapter::~cCBS_StdEventHandlerAdapter()
{
  if ( m_pWorkerThread )
  {
    // terminates thread
    m_pWorkerThread->setTerminateThread();
    m_pWorkerThread->waitForExit();

    //delete m_pWorkerThread;
  }
}


bool cCBS_StdEventHandlerAdapter::checkEventAcceptance(const FRIESEvent& Event)
{
  bool RetValue = false;

  std::vector<cCBS_StdEventHandler*> EventHandlerList = getEventHandlerList();
  std::vector<cCBS_StdEventHandler*>::iterator it;

  // find event handler to accept this event
  for ( it = EventHandlerList.begin(); it != EventHandlerList.end(); ++ it )
  {
    if ( (*it)->checkEventAcceptance(Event) )
    {
      RetValue = true;
      break;
    }
  }

  return RetValue;
}

bool cCBS_StdEventHandlerAdapter::checkReplaceEvent(const FRIESEvent& FirstEvent, const FRIESEvent& NewEvent)
{
  bool RetValue = false;

  std::vector<cCBS_StdEventHandler*> EventHandlerList = getEventHandlerList();
  std::vector<cCBS_StdEventHandler*>::iterator it;

  // find event handler to accept this event
  for ( it = EventHandlerList.begin(); it != EventHandlerList.end(); ++ it )
  {
    if ( (*it)->checkReplaceEvent(FirstEvent, NewEvent) )
    {
      RetValue = true;
      break;
    }
  }

  return RetValue;
}


bool cCBS_StdEventHandlerAdapter::handleEvent(const FRIESEvent& Event)
{
  if ( checkEventAcceptance(Event) )
  {
    if (m_pWorkerThread)
    {
      // This is important to be able to see if the process is still working if nothing else is seen.
      if ( m_pEvent_Task )
      {
        setStateDetails("cCBS_StdEventHandlerAdapter - reveiving last event : ", m_pEvent_Task->getCurrentTimeAsString());
      }

      // *******************************
      // insert event to EventList
      // and write state details
      // *******************************
      insertEvent(Event);
    }
  }

  return true;
}

// insert new event at front of EventList and replace existing event if required
void cCBS_StdEventHandlerAdapter::insertEvent(const FRIESEvent& NewEvent)
{
  // *******************************
  // synchronize container memory
  // *******************************
  cCBS_StdMutex CBS_StdMutex(m_EventHandlerName);

  // ******************************************
  // replace first event of queue is configured
  // ******************************************
  size_t m_EventListSize = m_EventList.size();

  if ( m_EventListSize > 0 && checkReplaceEvent( m_EventList.front(), NewEvent ) )
  {
    m_EventList.erase(m_EventList.begin());
  }

  // ******************************************
  // insert new event on first position
  // ******************************************
  m_EventList.insert(m_EventList.begin(), NewEvent);

  // *******************************
  // write state details
  // *******************************
  std::stringstream Detail;
      
  Detail << m_EventListSize;

  setStateDetails("Events in queue of EventHandler", Detail.str() );

}

// get next event from EventList and remove it from list
bool cCBS_StdEventHandlerAdapter::getNextEvent(FRIESEvent& NextEvent)
{
  bool RetValue = false;

  // *******************************
  // synchronize container memory
  // *******************************
  cCBS_StdMutex CBS_StdMutex(m_EventHandlerName);

  // **********************
  // get last event of list
  // **********************
  if ( ! m_EventList.empty() )
  {
    NextEvent = m_EventList.back();
    m_EventList.pop_back();

    RetValue = true;
  }

  return RetValue;
}



bool cCBS_StdEventHandlerAdapter::doEvent(const FRIESEvent& Event)
{
  bool IsHandled = false;
  bool IsAccepted = false;

  // instantiating task controller
  // will work in RELEASED version only !
  // terminates task AND component, if execution of event will take longer than
  // configured time from [ProcessControl] ControlTime = ...
  cCBS_StdFrame_TaskController Controller( m_pEvent_Task );

  try
  {
    std::vector<cCBS_StdEventHandler*> EventHandlerList = getEventHandlerList();
    std::vector<cCBS_StdEventHandler*>::iterator it;

    // check if an event handler is available
    if ( ! EventHandlerList.empty() )
    {
      doBeforeEventHandling(); // remark actual time and reset counters

      for ( it = EventHandlerList.begin(); it != EventHandlerList.end(); ++ it )
      {
        //IsAccepted = false;

        //// search for event handler that accepts the event !
        //if ( (*it)->checkEventAcceptance(Event) )
        //{
          IsAccepted = true;

          (*it)->beforeHandleEvent(Event);

          // search for event handler that handels the event !
          IsHandled = (*it)->handleEvent(Event);

          (*it)->afterHandleEvent(Event);

          // if event is handled somewhere, break iteration!
          if (IsHandled)
          {
            break;
          }
        //}
      } // for ( it = EventHandlerList.begin(); it != EventHandlerList.end(); ++ it )

      // event should be accepted but was not handled
      if (IsAccepted && !IsHandled) 
      {
        doAfterEventHandling(0);

        it = EventHandlerList.begin();
        (*it)->doOnEventHandlingError(Event);
      }
      else if (IsAccepted && IsHandled) 
      {
        doAfterEventHandling(1);
      }
      else if (!IsAccepted) 
      {
        doAfterEventHandling(-1);
      }
    } // if ( ! EventHandlerList.empty() )
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(Message,"","cCBS_StdEventHandlerAdapter::handleEvent","Handling Event");
  }

  return IsHandled;
}





//##ModelId=40EBCAAE027E
// inserting new item to actual container
bool cCBS_StdEventHandlerAdapter::registerEventHandler(cCBS_StdEventHandler* pEventHandler)
{
  cCBS_StdMutex CBS_StdMutex("m_EventHandlerList");

  m_EventHandlerList.insert(m_EventHandlerList.begin(), pEventHandler);

  return true;

}

// returning a copy of actual container
std::vector<cCBS_StdEventHandler*> cCBS_StdEventHandlerAdapter::getEventHandlerList()
{
  cCBS_StdMutex CBS_StdMutex("m_EventHandlerList");

  std::vector<cCBS_StdEventHandler*> EventHandlerList = m_EventHandlerList;

  return EventHandlerList;

}

//##ModelId=40EBCAAE02A6
void cCBS_StdEventHandlerAdapter::log(const std::string& Message, long Level)
{
  if (m_pEvent_Task)
  {
    m_pEvent_Task->log(Message, Level);
  }
}


//##ModelId=42DF9F210199
void cCBS_StdEventHandlerAdapter::doOnEventRejection()
{
}


//##ModelId=42DF9EB90104
void cCBS_StdEventHandlerAdapter::doBeforeEventHandling()
{
  // reset time
  cCBS_Time::localTime(m_EventReceptionTime);
}


//##ModelId=42E0F0D7035D
void cCBS_StdEventHandlerAdapter::doAfterEventHandling(long Success)
{
  if ( Success == -1) // event rejected
  {
    m_NoOfIncomingEvents++;
  }

  if ( Success == 1 )           // event accepted and handled 
  {
    // log information about rejected events from event channel first
    if ( m_NoOfIncomingEvents > 5 )
    {
        std::stringstream Message;
        Message << m_NoOfIncomingEvents
                << " events rejected!";

        log(Message.str(),4);

        m_NoOfIncomingEvents = 0;
    }

    if (m_pEvent_Task && m_pEvent_Task->getTraceLevel() > 3) // start trace with 4
    {
      // calculate time between now and event reception time 
      CBS_LocalTime Now;
      cCBS_Time::localTime(Now);

      long DiffTime = cCBS_Time::diffTime(Now,m_EventReceptionTime);

      if (DiffTime > 50)
      {
        std::stringstream Message;
        Message << "******************** "
                << "Notifying " 
                << DiffTime 
                << " msecs for handling event"
                << " ********************";

        log(Message.str(),4);
      }
    }
    cCBS_Time::localTime(m_EventAcceptanceTime); 

  }
  else if ( Success == 0 )      // event accepted but not handled 
  {
    // calculate time between now and event reception time 
    CBS_LocalTime Now;
    cCBS_Time::localTime(Now);

    if (m_pEvent_Task && m_pEvent_Task->getTraceLevel() > 3) // start trace with 4 
    {
      long DiffTime = cCBS_Time::diffTime(Now,m_EventReceptionTime);

      if (DiffTime > 50)
      {
        std::stringstream Message;
        Message << "******************** "
                << "Notifying " 
                << DiffTime 
                << " msecs for trying to handle event"
                << " ********************";

        log(Message.str(),4);
      }
    }
  }
}

std::string cCBS_StdEventHandlerAdapter::getStateDetails()
{
  cCBS_StdMutex Mutex("cCBS_StdEventHandlerAdapter_StateDetailItems");

  std::string StateDetails = m_EventHandlerName;

  StateDetails = StateDetails + "::getStateDetails()" + '\n';

  std::map<std::string, std::string>::iterator it;

  for ( it = m_StateDetailItems.begin(); it != m_StateDetailItems.end(); ++it )
  {
    StateDetails = StateDetails + it->first + " : " + it->second + '\n';
  }

  return StateDetails;

}

void cCBS_StdEventHandlerAdapter::setStateDetails(const std::string& item, const std::string& value)
{
  cCBS_StdMutex Mutex("cCBS_StdEventHandlerAdapter_StateDetailItems");

  std::map<std::string, std::string>::iterator it = m_StateDetailItems.find(item);

  if ( it == m_StateDetailItems.end() )
  {
    m_StateDetailItems.insert( std::pair<std::string,std::string> (item, value) );
  }
  else
  {
    it->second = value;
  }
}


// ******************************************************************
// ******************************************************************
// Thread handling
// ******************************************************************
// ******************************************************************


cCBS_StdEventHandlerAdapter::cCBS_StdEventHandlerAdapterWorkerThread::cCBS_StdEventHandlerAdapterWorkerThread(cCBS_StdEventHandlerAdapter* pEventHandlerAdapter, const std::string& EventHandlerName)
: m_pEventHandlerAdapter(pEventHandlerAdapter)
, m_EventHandlerName(EventHandlerName)
{
}


cCBS_StdEventHandlerAdapter::cCBS_StdEventHandlerAdapterWorkerThread::~cCBS_StdEventHandlerAdapterWorkerThread()
{
}

//Virtual work method. Sleeps for the specified ControlTime and checks status 
//will run down task and component in case of errors

void cCBS_StdEventHandlerAdapter::cCBS_StdEventHandlerAdapterWorkerThread::work()
{
  try
  {
    while( !getTerminateThread() )
    {
      performWorkingStep();
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","cCBS_StdEventHandlerAdapter::cCBS_StdEventHandlerAdapterWorkerThread::work()","performing Working Step");
  }
}


void cCBS_StdEventHandlerAdapter::cCBS_StdEventHandlerAdapterWorkerThread::terminate()
{
  setTerminateThread();
}

void cCBS_StdEventHandlerAdapter::cCBS_StdEventHandlerAdapterWorkerThread::performWorkingStep()
{
  try
  {
    if ( !getTerminateThread() )
    {
      if (m_pEventHandlerAdapter )
      {
        // This is important to be able to see if the process is still working if nothing else is seen.
        if ( m_pEventHandlerAdapter->m_pEvent_Task )
        {
          m_pEventHandlerAdapter->setStateDetails("cCBS_StdEventHandlerAdapter - executing last event : ", m_pEventHandlerAdapter->m_pEvent_Task->getCurrentTimeAsString());
        }

        FRIESEvent E;

        // ****************************************************
        // get next event from EventList of EventHandlerAdapter
        // ****************************************************
        if ( m_pEventHandlerAdapter->getNextEvent(E) )
        {
          m_pEventHandlerAdapter->doEvent( E );
        }
      }
    }

    sleep(5);
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","cCBS_StdEventHandlerAdapter::cCBS_StdEventHandlerAdapterWorkerThread::performWorkingStep()","");
  }
}

// ******************************************************************
// ******************************************************************
// end Thread handling
// ******************************************************************
// ******************************************************************
