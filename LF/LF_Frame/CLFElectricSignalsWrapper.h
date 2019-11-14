// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFELECTRICSIGNALSWRAPPER_41124357005E_INCLUDED
#define _INC_CLFELECTRICSIGNALSWRAPPER_41124357005E_INCLUDED

#include "CLFModelWrapper.h"
#include "CElectricalSignalsWrapper.h"

//##ModelId=41124357005E
class CLFElectricSignalsWrapper 
: public CElectricalSignalsWrapper
, public CLFModelWrapper
{
public:
	 bool doOnElectrodOutOperationPos(CEventMessage& Event);

	//##ModelId=41665E4E0003
	 bool doOnElectrodInOperationPos(CEventMessage& Event);

	//##ModelId=41665E4E02F2
	 bool doOnElectrodLifted(CEventMessage& Event);

	//##ModelId=41665E4F0113
	 bool doOnFurnBreakerOff(CEventMessage& Event);

	//##ModelId=41665E4F031E
	 bool doOnFurnBreakerOn(CEventMessage& Event);

	//##ModelId=41665E50010D
	 bool doOnPowerOff(CEventMessage& Event);

	//##ModelId=41665E5002A8
	 bool doOnPowerOn(CEventMessage& Event);

	//##ModelId=41665E5100A0
	 bool doOnTapChangeFinished(CEventMessage& Event);

	//##ModelId=41665E51024F
	 bool doOnTapChangeStart(CEventMessage& Event);

};

#endif /* _INC_CLFELECTRICSIGNALSWRAPPER_41124357005E_INCLUDED */
