// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_LFTASK_41A4A0D30033_INCLUDED
#define _INC_CARCHIVER_LFTASK_41A4A0D30033_INCLUDED

#include "CARCHIVER_Task.h"

class CARCHIVER_LFEventHandler;

//##ModelId=41A4A0D30033
class CARCHIVER_LFTask : public CARCHIVER_Task
  
{
public:
	//##ModelId=41A4A2B10135
	static CARCHIVER_LFTask* getInstance();

	//##ModelId=41A4A2B1014A
	virtual ~CARCHIVER_LFTask();

protected:

	//##ModelId=41A4A2B10167
	CARCHIVER_LFTask();

	//Creation of CARCHIVER_LFEventHandler and register on 
	//Event_Task.
	//Returns return code from base class
	//##ModelId=41A4A2B1018F
	virtual bool initialize();

private:
	//##ModelId=41A4A2B102A0
	static CARCHIVER_LFTask* m_Instance;
};

#endif /* _INC_CARCHIVER_LFTASK_41A4A0D30033_INCLUDED */
