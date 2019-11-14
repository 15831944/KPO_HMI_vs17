//-------------------------------------------------------------------------------------------------
// 
//                           S M S  D e m a g  A G 
// 
//                            All Rights Reserved 
// 
// 
// project       : cSMON_CorbaClientTask 
// filename      : cSMON_CorbaClientTask.h 
// author        : Bjoern Knops
// department    : EAM1
// creation date : 10-Oct-2005
// description   : Task for Corba connection to PLCs and Models
// 
//-------------------------------------------------------------------------------------------------
// 
// change notes: 
// 
// version  dd-mm-yyyy    author   remarks 

//-------------------------------------------------------------------------------------------------

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMON_CORBACLIENTTASK_411B843802F1_INCLUDED
#define _INC_CSMON_CORBACLIENTTASK_411B843802F1_INCLUDED

#include "cCBS_StdCorbaClientTask.h"
#include "cCBS_CorbaProxy.h"

struct s_Components
  {
    std::string CompName;
    std::string CorbaName;
    cCBS_CorbaProxy<iCBS_Task>* CBSProxy;    
  };


//This class provides access to connected systems for 
//fetching process data.
class cSMON_CorbaClientTask 
: public cCBS_StdCorbaClientTask
{

public:
	cSMON_CorbaClientTask(cCBS_Corba & corbaMode);

  ~cSMON_CorbaClientTask();

protected:
	//Virtual task start up method. Called by the 
	//runtimeStartUp method after starting up the subtasks. 
	//The default implementation sets only the state of the 
	//task to Running. Note that the work state is not set.
	//
	//This method may be redefined if the task represents for 
	//example a thread or a process. In this case, the method 
	//redefinition would start thread execution.
	void ownStartUp();

private:
  void getOwnStateDetails(CORBA::String_out details);

public:
  std::vector<s_Components> m_CorbaProxies;

};

#endif /* _INC_CSMON_CORBACLIENTTASK_411B843802F1_INCLUDED */
//-------------------------------------------------------------------------------------------------
// end of file cSMON_CorbaClientTask.h
