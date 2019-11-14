// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_EAFDELAYWRAPPER_41EE7AFD008A_INCLUDED
#define _INC_CARCHIVER_EAFDELAYWRAPPER_41EE7AFD008A_INCLUDED

#include "CEventMessage.h"

#include "CARCHIVER_DelayWrapper.h"

//##ModelId=41EE7AFD008A
class CARCHIVER_EAFDelayWrapper 
: public CARCHIVER_DelayWrapper
{
public:
	//##ModelId=41EE7D02032C
	virtual ~CARCHIVER_EAFDelayWrapper();

	//##ModelId=41EE7D35025E
	CARCHIVER_EAFDelayWrapper();

	//##ModelId=41EE7DA50359
  //do in DM, remove later
	//bool doOnDelayStatus(CEventMessage& Event);

protected:


	//##ModelId=41EE7D9D00E1
	virtual void deleteDBClasses();

	//##ModelId=41EE7D9D0394
	virtual void initDBClasses();

};

#endif /* _INC_CARCHIVER_EAFDELAYWRAPPER_41EE7AFD008A_INCLUDED */
