// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CCELOXMEASUREMENTWRAPPER_4111FD2E000F_INCLUDED
#define _INC_CCELOXMEASUREMENTWRAPPER_4111FD2E000F_INCLUDED

class CEventMessage;


//##ModelId=4111FD2E000F
class CCeloxMeasurementWrapper 
{
public:
	//##ModelId=411200EA0313
	virtual bool doOnCeloxMeasurement(CEventMessage & Event      );

};

#endif /* _INC_CCELOXMEASUREMENTWRAPPER_4111FD2E000F_INCLUDED */
