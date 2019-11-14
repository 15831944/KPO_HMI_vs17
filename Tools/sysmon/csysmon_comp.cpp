// ----------------------------------------------------------------------------
// 
//                            S M S  D e m a g  A G
// 
//                             All Rights Reserved
// 
// 
//  project       : SysMon
//  filename      : cSysMon_Comp.cpp
//  originator    : Bjoern Knops
//  department    : EAM1
//  creation date : 
//  description   : 
// 
// ----------------------------------------------------------------------------
// 
//  change notes:
// 
//  version  dd-mmm-yyyy author  remarks
//  0.1                          First Version
// 
// ----------------------------------------------------------------------------
// 
#include "cSysMon_Comp.h"
#include "CBS_Utilities\cCBS_ConfigBase.h"
#include "IntrfImpl.h"
#include "cSMON_Interface.h"
#include "cSysMon_Comp.h"
#include "cSMON_StatusCheckTask.h"
#define _CLOG9
#include "CBS_Clog.h"


//##ModelId=4322A85900EA
cSysMon_Comp * cSysMon_Comp::m_comp = NULL;

//##ModelId=4322A859003D
cSysMon_Comp * cSysMon_Comp::getSysMon_Comp()
{
	return cSysMon_Comp::m_comp;
}

void cSysMon_Comp::setLastResponse(const char* system, const char* lastTime)
{
	this->m_IntrfImpl->setLastResponse(system, lastTime);
}

void cSysMon_Comp::setStatus(const char* system, bool status)
{
	this->m_IntrfImpl->setStatus(system, status);
}

//##ModelId=4314B556024A
cSysMon_Comp::~cSysMon_Comp()
{
	// ToDo: Add your specialized code here and/or call the base class

}

//##ModelId=4314B55700BD
cSysMon_Comp::cSysMon_Comp()
:m_EventHandleTask()
{
	// ToDo: Add your specialized code here and/or call the base class
	this->m_comp = this;
}

//##ModelId=4314B5610169
void cSysMon_Comp::createSubtasks()
{
	// ToDo: Add your specialized code here or after the call to base class
	
	CBS_TaskData taskData;
	taskData.critical     = true;
	taskData.autoRecovery = true;
	taskData.priority     = MCBS::MCBS_PrioNormal;

	m_IntrfImpl = new IntrfImpl();

	m_Interface = new cSMON_Interface();
	m_Interface->activate(m_componentPOA, "SysMon_Interface");		// object is assigned to POA, now is registered and accessable as CORBA object
	addSubtask(m_Interface->getTaskName(),									// add to TASK internal list of subtasks, application internal
		       m_Interface->getReference(),
			   taskData);
	CLOG1(<<"Interface created...");

  m_EventHandleTask.activate(m_componentPOA,"SysMon_EventHandlerTask");
  addSubtask(m_EventHandleTask.getTaskName(),m_EventHandleTask.getReference(),taskData);  
  CLOG1(<<"SysMon_EventHandlerTask created"<<std::endl);

  m_StatusCheck = new cSMON_StatusCheckTask(m_IntrfImpl);
  m_StatusCheck->activate(m_componentPOA,"SysMon_StatusCheck");
  addSubtask(m_StatusCheck->getTaskName(),m_StatusCheck->getReference(),taskData);
  CLOG1(<<"SysMon_StatusCheckTask created"<<std::endl);
	/*initEventServers();*/
  //start up all tasks
  this->startUp(RuntimeMode);
}

//##ModelId=4314B5670047
void cSysMon_Comp::getOwnStateDetails(CORBA::String_out details)
{
	// ToDo: Add your specialized code here or after the call to base class	
	cCBS_Task::getOwnStateDetails(details);
}

//##Begin Model Documentation
//Virtual method called after the subtask runDown call. 
//Can be redefined by subclasses. The default 
//implementation does nothing.
//##End Model Documentation
//##ModelId=411B74C001B3
void cSysMon_Comp::afterSubtaskEnd()
{
  CLOG6( << "afterSubtaskEnd: going to finish. Shut down ORB connection." << std::endl);  // TODO: this ok?
	try
  {
    CBS::getORB()->shutdown(false);                   // terminates CORBA -> server.run() returns
  }                                                   // TODO: see omniOrb internet pages for fixing the bug with shutting down..
  catch (...)                                         // TODO: check: is there any 'real' exception to catch?
  {
    CLOG1(<< "afterSubtaskEnd: error when trying to shutdown ORB connection!" << std::endl);
  }
}



