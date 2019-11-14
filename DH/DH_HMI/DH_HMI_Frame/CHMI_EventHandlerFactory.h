// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHMI_EVENTHANDLERFACTORY_458674970354_INCLUDED
#define _INC_CHMI_EVENTHANDLERFACTORY_458674970354_INCLUDED

#include <string>
#include "CFactoryBase.h"

class CDH_EventHandler;

class CHMI_EventHandlerFactory 
: public CFactoryBase
{
public:
	CDH_EventHandler* createEventHandler(std::string& ServerName);

	CHMI_EventHandlerFactory();

	virtual ~CHMI_EventHandlerFactory();

};

#endif /* _INC_CHMI_EVENTHANDLERFACTORY_458674970354_INCLUDED */
