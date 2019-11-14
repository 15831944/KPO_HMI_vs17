// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTEMPERATURMEASUREMENTWRAPPER_4111FDA30298_INCLUDED
#define _INC_CTEMPERATURMEASUREMENTWRAPPER_4111FDA30298_INCLUDED

class CEventMessage;

//##ModelId=4111FDA30298
class CTemperaturMeasurementWrapper 
{
public:
	//##ModelId=415D5C02031F
	virtual bool doOnTempMeasurement(CEventMessage & Event);

};

#endif /* _INC_CTEMPERATURMEASUREMENTWRAPPER_4111FDA30298_INCLUDED */
