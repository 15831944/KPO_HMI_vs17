// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CELECTRICALSIGNALSWRAPPER_4111FCDB01EA_INCLUDED
#define _INC_CELECTRICALSIGNALSWRAPPER_4111FCDB01EA_INCLUDED

class CEventMessage;


//##ModelId=4111FCDB01EA
class CElectricalSignalsWrapper 
{
public:
	//##ModelId=4111FF510178
	virtual bool doOnElectrodLifted(CEventMessage &Event);

	//##ModelId=4111FFBA0358
	virtual bool doOnElectrodInOperationPos(CEventMessage &Event);

	//##ModelId=41120263035C
	virtual bool doOnPowerOn(CEventMessage &Event);

	//##ModelId=411202800016
	virtual bool doOnPowerOff(CEventMessage &Event);

	//##ModelId=4112029B02CA
	virtual bool doOnTapChangeStart(CEventMessage &Event);

	//##ModelId=411202CC0008
	virtual bool doOnTapChangeFinished(CEventMessage & Event);

	//##ModelId=411245C502F2
	virtual bool doOnFurnBreakerOff(CEventMessage & Event);

	//##ModelId=411245E502F2
	virtual bool doOnFurnBreakerOn(CEventMessage &Event);

};

#endif /* _INC_CELECTRICALSIGNALSWRAPPER_4111FCDB01EA_INCLUDED */
