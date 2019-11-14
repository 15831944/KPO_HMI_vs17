// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTSM_GEN_TASK_40EBC4E90363_INCLUDED
#define _INC_CTSM_GEN_TASK_40EBC4E90363_INCLUDED

#include "CTSM_Task.h"

class CTsmBaseApplication;
#include "CTSM_GEN_EventHandler.h"

class CTSM_GEN_Task : public CTSM_Task
     
{
public:
	virtual ~CTSM_GEN_Task();

	static CTSM_GEN_Task* getInstance();

  std::string getReceiverName()
  {
    if ( m_pEventHandler )
    {
      return m_pEventHandler->getReceiverName();
    }
    return std::string();
  };

protected:
	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	virtual bool initialize();

	CTSM_GEN_Task();
    
	CTSM_GEN_EventHandler* m_pEventHandler;

private:
	static CTSM_GEN_Task* Instance;

};

#endif /* _INC_CTSM_GEN_TASK_40EBC4E90363_INCLUDED */
