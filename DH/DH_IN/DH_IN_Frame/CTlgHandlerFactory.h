// Copyright (C) 2006 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTLGHANDLERFACTORY_4582A74201DC_INCLUDED
#define _INC_CTLGHANDLERFACTORY_4582A74201DC_INCLUDED

#include <string>
#include "CFactoryBase.h"

class CTelegram_Handler;

//##ModelId=4582A74201DC
class CTlgHandlerFactory 
: public CFactoryBase
{
public:
	//##ModelId=4582C55C027A
	CTelegram_Handler*  createTlgHandler(std::string& ServerName);

	//##ModelId=4582C5FF0304
	CTlgHandlerFactory();

	//##ModelId=4582C6000176
	virtual ~CTlgHandlerFactory();

};

#endif /* _INC_CTLGHANDLERFACTORY_4582A74201DC_INCLUDED */
