// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFBOTTOMSTIRRINGWRAPPER_4112476C0305_INCLUDED
#define _INC_CLFBOTTOMSTIRRINGWRAPPER_4112476C0305_INCLUDED

#include "CLFModelWrapper.h"

//##ModelId=4112476C0305
class CLFBottomStirringWrapper 
: public CLFModelWrapper
{
public:
	//##ModelId=411247B50146
	bool doOnStirringEnd(CEventMessage &Event);

	//##ModelId=411247C901E8
	bool doOnStirringStart(CEventMessage &Event);

	//##ModelId=411A19DE013E
	bool doOnStirringBypassOff(CEventMessage &Event);

	//##ModelId=411A1A6600E0
	bool doOnStirringBypassOn(CEventMessage &Event);

};

#endif /* _INC_CLFBOTTOMSTIRRINGWRAPPER_4112476C0305_INCLUDED */
