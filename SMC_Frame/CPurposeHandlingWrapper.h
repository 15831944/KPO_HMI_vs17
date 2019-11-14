// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CPURPOSEHANDLINGWRAPPER_410FCCC201F5_INCLUDED
#define _INC_CPURPOSEHANDLINGWRAPPER_410FCCC201F5_INCLUDED

#include <string>

class CEventMessage;

//##ModelId=410FCCC201F5
class CPurposeHandlingWrapper 
{
public:
	//##ModelId=410FCD2600C4
	virtual bool doOnUpdatePurpose( CEventMessage & Event);

};

#endif /* _INC_CPURPOSEHANDLINGWRAPPER_410FCCC201F5_INCLUDED */
