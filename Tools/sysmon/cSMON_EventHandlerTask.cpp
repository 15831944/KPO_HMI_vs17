// ------------------------------------------------------------------------------------------------
//  
//                            S M S  D e m a g  A G
//  
//                             All Rights Reserved
//  
//  
//  project       : SysMon
//  filename      : cSMON_EventHandlerTask.cpp
//  author        : bolc
//  department    : EAM 1
//  creation date : 2006-10-18
//  description   : Task for handling of Level 2 events. Initial purpose is for
//                  re-opening of log files but might be extended in the future.
//  
// ------------------------------------------------------------------------------------------------
//  
//  change notes:
//  
//  version   dd-mm-yyyy     author   remarks
//  
// ------------------------------------------------------------------------------------------------

#include "cSMON_EventHandlerTask.h"
#define _CLOG9
#include "CBS_Clog.h"
#include "L2Events.h"

//##Begin Model Documentation
//
//##End Model Documentation
cSMON_EventHandlerTask::cSMON_EventHandlerTask()
: cCBS_StdEventHdlTask(), m_statustext("none")
{
}

//##Begin Model Documentation
//
//##End Model Documentation
cSMON_EventHandlerTask::~cSMON_EventHandlerTask()
{
}

// ------------------------------------------------------------------------------------------------
//##Begin Model Documentation
//Default handle event method. This method is called by 
//the default event handler 
//(cCBS_StdEventTaskEventHandler) that is nested in this 
//class.
//
//The default implementation of this method writes the 
//data of the current event to the standard test log 
//depending on the current test log level.
//##End Model Documentation
void cSMON_EventHandlerTask::handleEvent(const FRIESEvent& event)
{
  //CastingOptServer
  //cCBS_StdEventHdlTask::handleEvent(event);
  //CLOG9(<< "handleEvent: received event id " << event.id << ", event type " << event.type << std::endl);
  m_statustext = "";
  char buf[10];
  ltoa(event.type,buf,10);
  m_statustext.append(buf);

  std::string bla;
  //bla.clear(
  if ((EV_L2_REOPEN_LOGS==event.id) || (EV_L2_REOPEN_LOGS==event.type)) // we never know who uses what..
  {
    try
    {
      cLog::CLogTrace::get().reopenLogFiles();

      //CastingOptServer->get_StdTestLog()->reopenAll();

      CLOG9(<< "handleEvent: triggered reopen log-files " << std::endl);
    }
    catch(...)
    {
      std::cout << "EventHandler: caught unknown exception when re-opening log files!" << std::endl;
    }
  }
}
// ------------------------------------------------------------------------------------------------
//##Begin Model Documentation
//Virtual task start up method. Called by the 
//runtimeStartUp method after starting up the subtasks. 
//The default implementation sets only the state of the 
//task to Running. Note that the work state is not set.
//
//This implementation connects all event handlers to the 
//event channel
//##End Model Documentation
void cSMON_EventHandlerTask::ownStartUp()
{
  // ToDo: Add your specialized code here or after the call to base class
  
  cCBS_StdEventHdlTask::ownStartUp();
  setWorking(true);
}
// ------------------------------------------------------------------------------------------------
//##Begin Model Documentation
//Virtual task run down method. Called by the runDown 
//method before stopping the subtasks. The default 
//implementation sets only the state of the task to 
//NotRunning. Note that the work state is not set.
//
//This implementation disconnects all event handlers from 
//the event channel
//##End Model Documentation
void cSMON_EventHandlerTask::ownRunDown()
{
  // ToDo: Add your specialized code here or after the call to base class
  
  cCBS_StdEventHdlTask::ownRunDown();
}
// ------------------------------------------------------------------------------------------------
void cSMON_EventHandlerTask::getOwnStateDetails(CORBA::String_out details)
{
  if (CBS_Working == getOwnWorkState())
  {
    std::string text = "Last event was type: ";
    text.append(m_statustext);
    details = CORBA::string_dup(text.c_str());
  }
  else
    details = CORBA::string_dup("We are not working!");
}
// end of file cCastingOptEventHandlerTask.cpp

