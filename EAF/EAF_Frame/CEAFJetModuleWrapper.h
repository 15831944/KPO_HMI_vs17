// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFJETMODULEWRAPPER_411224FF00CC_INCLUDED
#define _INC_CEAFJETMODULEWRAPPER_411224FF00CC_INCLUDED

#include "CEAFModelWrapper.h"

//##ModelId=411224FF00CC
class CEAFJetModuleWrapper 
: public CEAFModelWrapper
{
public:
	//##ModelId=4112253B0129
	bool doOnJetModuleStart( CEventMessage &Event );

	//##ModelId=41122551023C
	bool doOnJetModuleStop( CEventMessage &Event );

};

#endif /* _INC_CEAFJETMODULEWRAPPER_411224FF00CC_INCLUDED */
