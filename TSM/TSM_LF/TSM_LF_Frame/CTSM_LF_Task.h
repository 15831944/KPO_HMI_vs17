// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTSM_LF_TASK_40EBC4E90363_INCLUDED
#define _INC_CTSM_LF_TASK_40EBC4E90363_INCLUDED

#include "CTSM_Task.h"

class CTsmBaseApplication;
class CTSM_LF_EventHandler;

class CTSM_LF_Task : public CTSM_Task
  
{
public:

	virtual ~CTSM_LF_Task();

	static CTSM_LF_Task* getInstance();

	CTSM_LF_EventHandler* getEventHandler();

protected:
	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	virtual bool initialize();

	CTSM_LF_Task();

	CTSM_LF_EventHandler* m_pEventHandler;

private:
	static CTSM_LF_Task* Instance;
};

#endif /* _INC_CTSM_LF_TASK_40EBC4E90363_INCLUDED */
