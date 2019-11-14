// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_HMDTASK_41A4A0D30033_INCLUDED
#define _INC_CARCHIVER_HMDTASK_41A4A0D30033_INCLUDED

#include "CARCHIVER_Task.h"

class CARCHIVER_HMDEventHandler;

//##ModelId=45D587FD014D
class CARCHIVER_HMDTask 
: public CARCHIVER_Task
{
public:
	//##ModelId=45D5899B0306
	static CARCHIVER_HMDTask* getInstance();

	//##ModelId=45D5899B0338
	virtual ~CARCHIVER_HMDTask();

	//##ModelId=45D5899B0387
	CARCHIVER_HMDTask();

	//##ModelId=45D5899B03AF
	virtual void getOwnStateDetails(CORBA::String_out details);

protected:
	//! create and register HMD event handler
	//##ModelId=45D5899C000D
	virtual bool initialize();

private:
	//##ModelId=4670F158032A
	 static CARCHIVER_HMDTask* m_Instance;
};

#endif /* _INC_CARCHIVER_HMDTASK_41A4A0D30033_INCLUDED */
