// Copyright (C) 2006 SMS Demag AG Germany

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEVENTHANDLERFACTORY_4582B8780136_INCLUDED
#define _INC_CEVENTHANDLERFACTORY_4582B8780136_INCLUDED

#include "CFactoryBase.h"
#include <string>

class CDH_EventHandler;
class CAOD_EventHandler;
class CEAF_EventHandler;
class CLF_EventHandler;
class CLab_EventHandler;
class CL3_EventHandler;
class CCCS_EventHandler;
class CIPQS_EventHandler;
class CInterfaceAccess_Task;

//##ModelId=4582B8780136
class CEventHandlerFactory 
: public CFactoryBase
{
public:
	//##ModelId=4582B990019C
	CEventHandlerFactory();

	//##ModelId=4582B99303D2
	virtual ~CEventHandlerFactory();

	//##ModelId=4582BD5302F6
	CDH_EventHandler* createEventHandler(std::string& ServerName  );
};

#endif /* _INC_CEVENTHANDLERFACTORY_4582B8780136_INCLUDED */
