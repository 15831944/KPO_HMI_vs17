#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_SRVTASK_40EE575103D3_INCLUDED
#define _INC_CARCHIVER_SRVTASK_40EE575103D3_INCLUDED

#include "CARCHIVER_Task.h"

class CARCHIVER_SRVTask : public CARCHIVER_Task
{
public:
	static CARCHIVER_SRVTask* getInstance();

	virtual ~CARCHIVER_SRVTask();
	
protected:

	CARCHIVER_SRVTask();

	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	virtual bool initialize();

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
	static CARCHIVER_SRVTask* m_Instance;	
};

#endif /* _INC_CARCHIVER_SRVTASK_40EE575103D3_INCLUDED */
