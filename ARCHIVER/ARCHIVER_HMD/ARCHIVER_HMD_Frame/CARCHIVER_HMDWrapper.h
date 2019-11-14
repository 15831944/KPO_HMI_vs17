// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_HMDWRAPPER_INCLUDED
#define _INC_CARCHIVER_HMDWRAPPER_INCLUDED

#include "CARCHIVER_Wrapper.h"

class CARCHIVER_HMDTask;

class CARCHIVER_HMDWrapper : public CARCHIVER_Wrapper
{
protected:
	CARCHIVER_HMDWrapper();

public:
	virtual ~CARCHIVER_HMDWrapper();
};

#endif /* _INC_CARCHIVER_HMDWRAPPER_INCLUDED */
