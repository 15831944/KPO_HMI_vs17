// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_LFDELAYWRAPPER_462F1585013A_INCLUDED
#define _INC_CARCHIVER_LFDELAYWRAPPER_462F1585013A_INCLUDED

#include "CARCHIVER_DelayWrapper.h"


//##ModelId=462F1585013A
class CARCHIVER_LFDelayWrapper 
: public CARCHIVER_DelayWrapper
{
public:
	//##ModelId=462F15A903A4
	CARCHIVER_LFDelayWrapper();

	//##ModelId=462F15AA029A
	virtual ~CARCHIVER_LFDelayWrapper();

	//##ModelId=462F15DB02A7
  //do in DM, remove later
	//bool doOnDelayStatus(CEventMessage& Event);

protected:
	//##ModelId=462F15AC0168
	virtual void initDBClasses();

	//##ModelId=462F15AD0004
	virtual void deleteDBClasses();

};

#endif /* _INC_CARCHIVER_LFDELAYWRAPPER_462F1585013A_INCLUDED */
