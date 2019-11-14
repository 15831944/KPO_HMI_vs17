// ------------------------------------------------------------------------------------------------
//  
//                            S M S  D e m a g  A G
//  
//                             All Rights Reserved
//  
//  
//  project       : SysMon
//  filename      : cSMON_EventHandlerTask.h
//  author        : bolc
//  department    : EAM 1
//  creation date : 05-Dec-2005
//  description   : Header file for event handler task. For description, see
//                  source file.
//  
// ------------------------------------------------------------------------------------------------
//  
//  change notes:
//  
//  version   dd-mm-yyyy     author   remarks
//   1.0      18-Oct-2006    bolc     original edit
//  
// ------------------------------------------------------------------------------------------------

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CCASTINGOPTEVENTHANDLERTASK_439074E3026F_INCLUDED
#define _INC_CCASTINGOPTEVENTHANDLERTASK_439074E3026F_INCLUDED

#include "cCBS_StdEventHdlTask.h"

class cCastingOptServer;

//Handles all icoming events.
class cSMON_EventHandlerTask 
: public cCBS_StdEventHdlTask
{
public:
  cSMON_EventHandlerTask();

  cSMON_EventHandlerTask(cCastingOptServer& CastingOptServer);

  virtual ~cSMON_EventHandlerTask();

  //Default handle event method. This method is called by 
  //the default event handler 
  //(cCBS_StdEventTaskEventHandler) that is nested in this 
  //class.
  //
  //The default implementation of this method writes the 
  //data of the current event to the standard test log 
  //depending on the current test log level.
  void handleEvent(const FRIESEvent& event);

protected:
  //Virtual task start up method. Called by the 
  //runtimeStartUp method after starting up the subtasks. 
  //The default implementation sets only the state of the 
  //task to Running. Note that the work state is not set.
  //
  //This implementation connects all event handlers to the 
  //event channel
  void ownStartUp();

  //Virtual task run down method. Called by the runDown 
  //method before stopping the subtasks. The default 
  //implementation sets only the state of the task to 
  //NotRunning. Note that the work state is not set.
  //
  //This implementation disconnects all event handlers from 
  //the event channel
  void ownRunDown();

  void getOwnStateDetails(CORBA::String_out details);

  std::string m_statustext;
};
// ------------------------------------------------------------------------------------------------
#endif

// end of file cSMON_EventHandlerTask.h
