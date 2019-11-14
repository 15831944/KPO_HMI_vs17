// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDH_HMI_TASK_40EE575103D3_INCLUDED
#define _INC_CDH_HMI_TASK_40EE575103D3_INCLUDED

#include "CDH_Task.h"
#include "CInterfaceAccess_Task.h"
class CDH_HMI_EventHandler;

class CHMI_EventHandlerFactory;

//##ModelId=45865F02014B
class CDH_HMI_Task : public CInterfaceAccess_Task
{
public:
	//##ModelId=4586739B0218
  virtual void setCORBAConnections();


	//##ModelId=4586739B023B
	virtual ~CDH_HMI_Task();

	//##ModelId=4586739B0272
	static CDH_HMI_Task* getInstance();

protected:
	//##ModelId=45882AEA0369
	CHMI_EventHandlerFactory* m_pHMI_EventHandlerFactory;

	//##ModelId=4586739B027D
	CDH_HMI_Task();

	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	//##ModelId=4586739B0290
	virtual bool initialize();

private:
	//##ModelId=4588272800D3
	static CDH_HMI_Task* m_pInstance;

};

#endif /* _INC_CDH_HMI_TASK_40EE575103D3_INCLUDED */
