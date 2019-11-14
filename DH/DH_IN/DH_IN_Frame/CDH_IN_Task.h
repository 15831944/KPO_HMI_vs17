// Copyright (C) 2006 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDH_IN_TASK_4582A4D100AC_INCLUDED
#define _INC_CDH_IN_TASK_4582A4D100AC_INCLUDED

#include "CDH_Task.h"
class CTlgHandlerFactory;
class CTelegram_Adapter;
class CDH_IN_Telcom_Impl;
class CDH_IN_Interface_Impl;

//##ModelId=4582A4D100AC
class CDH_IN_Task 
: public CDH_Task
{
public:
	//##ModelId=45868B29005E
	 CTelegram_Adapter* getpTelegramAdapter();

	//Register servants for incomming and outgoing data
	//##ModelId=4582C6AC02C0
	virtual void setCORBAConnections();

	//##ModelId=4582C6D801DC
	virtual ~CDH_IN_Task();

	//##ModelId=4582C71702A1
	static CDH_IN_Task* getInstance();

protected:
	//##ModelId=4582A7C60181
	CTelegram_Adapter* m_pTelegram_Adapter;

	//##ModelId=4582C608013A
	CTlgHandlerFactory* m_pTlgHandlerFactory;

	//Create telegram handler
	//##ModelId=4582C65401B8
	virtual bool initialize();

private:
	//##ModelId=4582C6E30295
	static CDH_IN_Task* m_Instance;

	//##ModelId=4582C6D70388
	CDH_IN_Task();

};

#endif /* _INC_CDH_IN_TASK_4582A4D100AC_INCLUDED */
