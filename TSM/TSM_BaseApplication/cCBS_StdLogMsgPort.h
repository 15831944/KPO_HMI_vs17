// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CCBS_STDLOGMSGPORT_411B8006029F_INCLUDED
#define _INC_CCBS_STDLOGMSGPORT_411B8006029F_INCLUDED

#include "IMsgPort.h"

class cCBS_StdLogMsgPort 
: public IMsgPort
{
public:
	//This function prints out a given message string to an 
	//interface device that has to be defined by derivation.
	virtual void printOutMessage(int traceLevel, const char* msg);

};

#endif /* _INC_CCBS_STDLOGMSGPORT_411B8006029F_INCLUDED */
