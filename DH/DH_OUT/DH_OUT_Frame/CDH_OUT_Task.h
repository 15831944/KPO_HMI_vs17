// Copyright (C) 2006 SMS Demag AG Germany

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDH_OUT_TASK_4582A5F401A0_INCLUDED
#define _INC_CDH_OUT_TASK_4582A5F401A0_INCLUDED

#include "CInterfaceAccess_Task.h"

class CEventHandlerFactory;

//##ModelId=4582A5F401A0
class CDH_OUT_Task 
: public CInterfaceAccess_Task
{
public:
	//##ModelId=4586E31D018C
	virtual ~CDH_OUT_Task();

	//##ModelId=4582B3F402AC
	static CDH_OUT_Task* getInstance();

protected:
	//##ModelId=4582B396037D
	virtual bool initialize();

	//##ModelId=4582B3B60382
	virtual void setCORBAConnections();

private:
	//##ModelId=4582B3CF0200
	static CDH_OUT_Task* m_Instance;

	//##ModelId=4582B89F0343
	CEventHandlerFactory* m_pEventHandlerFactory;

	//##ModelId=4582B3C301CA
	CDH_OUT_Task();

};

#endif /* _INC_CDH_OUT_TASK_4582A5F401A0_INCLUDED */
