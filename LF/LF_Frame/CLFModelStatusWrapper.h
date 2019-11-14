// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFMODELSTATUSWRAPPER_411A1CF8004D_INCLUDED
#define _INC_CLFMODELSTATUSWRAPPER_411A1CF8004D_INCLUDED

#include "CLFModelWrapper.h"

//##ModelId=411A1CF8004D
class CLFModelStatusWrapper 
: public CLFModelWrapper
{
public:
	//##ModelId=411A1D2001EF
	bool doOnGetModelStatus(CEventMessage &Event);

};

#endif /* _INC_CLFMODELSTATUSWRAPPER_411A1CF8004D_INCLUDED */
