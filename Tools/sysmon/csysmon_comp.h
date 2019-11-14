// // ----------------------------------------------------------------------------
// // 
// //                            S M S  D e m a g  A G
// // 
// //                             All Rights Reserved
// // 
// // 
// //  project       : Shougang 
// //  filename      : 
// //  originator    : 
// //  department    : 
// //  creation date : 
// //  description   : 
// // 
// // ----------------------------------------------------------------------------
// // 
// //  change notes:
// // 
// //  version  dd-mmm-yyyy author  remarks
// //  0.1      06-JUN-2001 	 First Version
// // 
// // ----------------------------------------------------------------------------
// // 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_cSysMon_COMP_4314B511006A_INCLUDED
#define _INC_cSysMon_COMP_4314B511006A_INCLUDED

#define EV_STCM_PRESET_PULSE_TIMER 200101

#include "cSMON_EventHandlerTask.h"

#include <CBS_General.h>
#include <CBS_Tasks.h>
#include <CBS_StdAPI/cCBS_StdComponent.h>
#include <CBS_Threads/cCBS_Mutex.h>
#include <map>
#include <string>

class cSMON_StatusCheckTask;
class cSMON_CorbaClientTask;

class IntrfImpl;
class cSMON_Interface;

//##ModelId=4314B511006A
class cSysMon_Comp 
: public cCBS_StdComponent
{
public:
	//##ModelId=4314B556024A
	virtual ~cSysMon_Comp();

	//##ModelId=4314B55700BD
	cSysMon_Comp();

	//Virtual subtask creation method. Called by activate 
	//after initialization. Subclasses may implement this 
	//method to create their subtasks.
	//##ModelId=4314B5610169
	virtual void createSubtasks();

	//##ModelId=4314B5670047
	virtual void getOwnStateDetails(CORBA::String_out details);

  virtual void afterSubtaskEnd();

	//##ModelId=4322A859003D
	static cSysMon_Comp * getSysMon_Comp();

	void setLastResponse(const char* system, const char* lastTime);

	void setStatus(const char* system, bool status);

	IntrfImpl* m_IntrfImpl;

private:

	//##ModelId=4322A85900EA
	static cSysMon_Comp* m_comp;

  cSMON_StatusCheckTask* m_StatusCheck;

  cSMON_EventHandlerTask m_EventHandleTask; 

	cSMON_Interface* m_Interface;

};

#endif /* _INC_cSysMon_COMP_4314B511006A_INCLUDED */
