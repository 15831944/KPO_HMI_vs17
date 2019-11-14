// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTSM_HMD_TASK_INCLUDED
#define _INC_CTSM_HMD_TASK_INCLUDED

#include "CTSM_Task.h"
#include "cCBS_StdEvent_Task.h"

class CTsmBaseApplication;
class CTSM_HMD_EventHandler;

//##ModelId=45A21C7C000F
class CTSM_HMD_Task : public CTSM_Task
  
{
public:
	//##ModelId=45A21E8D0180
	virtual void getOwnStateDetails(CORBA::String_out details);

	//##ModelId=45A21E8D020B
	virtual ~CTSM_HMD_Task();

	//##ModelId=45A21E8D023E
	static CTSM_HMD_Task* getInstance();

	CTSM_HMD_EventHandler* getEventHandler();

protected:
	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	//##ModelId=45A21E8D027A
	virtual bool initialize();

	//##ModelId=45A21E8D028E
	CTSM_HMD_Task();

	//##ModelId=45A225BB005F
	CTSM_HMD_EventHandler* m_pEventHandler;

private:
	//##ModelId=45A21EBB0220
	static CTSM_HMD_Task* Instance;
};

#endif /* _INC_CTSM_HMD_TASK_INCLUDED */
