// ----------------------------------------------------------------------------
//  
//                            S M S  D e m a g  A G
//  
//                             All Rights Reserved
//  
//  
//  project       : CastingOpt
//  filename     :  cSMON_StatusCheckTask.h
//  author        : knop
//  department    : EAM1
//  creation date : 20-Sep-2005
//  description   : 
//  
// ----------------------------------------------------------------------------
//  
//  change notes:
//  
//  version   dd-mm-yyyy      author      remarks
//   0.97     20-Sep-2005     knop        original edit
//  
// ----------------------------------------------------------------------------

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSOM_STATUSCHECKTASK_41C93DBC000E_INCLUDED
#define _INC_CSOM_STATUSCHECKTASK_41C93DBC000E_INCLUDED

#include <string>
#include <iostream>
#include "cCBS_StdWorkerTask.h" 
#include "fevent_s.hh"
#include "cCBS_CorbaProxy.h"
class IntrfImpl;
class cSMON_CorbaClientTask;

//This is one of the main tasks of CastingOpt component. It 
//serves for calculation of taper setpoint depending on current mould heat flux ratios left and right 
//side.
class cSMON_StatusCheckTask 
: public cCBS_StdWorkerTask
{
private:

  cSMON_CorbaClientTask* m_CorbaClient;
  int iScanInterval;
  int m_ORBPingTimeOut;
	
public:
	//contructor
	cSMON_StatusCheckTask(IntrfImpl*);

	virtual ~cSMON_StatusCheckTask();

	virtual void getOwnStateDetails(CORBA::String_out details);

  virtual void createSubtasks();

protected:
  void init();
  
	IntrfImpl *m_CorbaInterface;

	//Virtual task start up method. Called by the 
	//runtimeStartUp method after starting up the subtasks. 
	//sets working state 'true' and starts execution of the thread function
	//This method may be redefined in order to implement application specific initialization or 
	//startup work.
	//Redefinition implementation should call cCBS_StdTask::ownStartUp as last statement.
	virtual void ownStartUp();

	//Virtual task run down method. Called by the runDown 
	//method before stopping the subtasks. The default 
	//implementation sets only the state of the task to 
	//NotRunning. Note that the work state is not set.
	//
	//This method may be redefined if the task represents for 
	//example a thread or a process. In this case, the method 
	//redefinition would stop thread execution.
	virtual void ownRunDown();

	//Work function called in a loop by the thread (via the 
	//work method). Can be redefined by subclasses. 
	//
	//The default implementation does nothing (except 
	//sleeping for 1 second). This method could have been 
	//declared abstract. Anyway, in order to allow instances 
	//of cCBS_Thread to be created (in the case where a 
	//thread function has been specified for execution), it 
	//has been implemented doing nothing.
	virtual void performWorkingStep();
};
//-------------------------------------------------------------------------------------------------
#endif /* _INC_CSOM_STATUSCHECKTASK_41C93DBC000E_INCLUDED */
