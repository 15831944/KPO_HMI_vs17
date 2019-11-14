// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMON_INTERFACE_4120871601AB_INCLUDED
#define _INC_CSMON_INTERFACE_4120871601AB_INCLUDED

#include "CBS_Tasks.h"

class IntrfImpl;


//Task which handles CORBA interface of SMON
class cSMON_Interface 
: public cCBS_Task
{
public:

	virtual void getOwnStateDetails(CORBA::String_out details);

	
	virtual ~cSMON_Interface();


	cSMON_Interface();

protected:
	//Virtual task run down method. Called by the runDown 
	//method before stopping the subtasks. The default 
	//implementation sets only the state of the task to 
	//NotRunning. Note that the work state is not set.
	//
	//This method may be redefined if the task represents for 
	//example a thread or a process. In this case, the method 
	//redefinition would stop thread execution.

	virtual void ownRunDown();

	//Virtual task start up method. Called by the 
	//runtimeStartUp method after starting up the subtasks. 
	//The default implementation sets only the state of the 
	//task to Running. Note that the work state is not set.
	//
	//This method may be redefined if the task represents for 
	//example a thread or a process. In this case, the method 
	//redefinition would start thread execution.

	virtual void ownStartUp();

private:
	
	IntrfImpl*		m_pServant;

};

#endif /* _INC_CSMON_INTERFACE_4120871601AB_INCLUDED */
