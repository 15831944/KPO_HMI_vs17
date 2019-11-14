// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFELECTRICSIGNALSWRAPPER_41121D3801D9_INCLUDED
#define _INC_CEAFELECTRICSIGNALSWRAPPER_41121D3801D9_INCLUDED

#include "CEAFModelWrapper.h"
#include "CElectricalSignalsWrapper.h"

//##ModelId=41121D3801D9
class CEAFElectricSignalsWrapper 
: public CElectricalSignalsWrapper
, public CEAFModelWrapper
{
public:
	virtual bool doOnElectrodOutOperationPos( CEventMessage &Event );

	//##ModelId=4158273E0307
	virtual bool doOnElectrodInOperationPos( CEventMessage &Event );

	//##ModelId=4158273F021A
	virtual bool doOnElectrodLifted( CEventMessage &Event );

	//##ModelId=415827400370
	virtual bool doOnFurnBreakerOn( CEventMessage &Event );

	//##ModelId=41582741012D
	virtual bool doOnPowerOff( CEventMessage &Event );

	//##ModelId=41582741030D
	virtual bool doOnPowerOn( CEventMessage &Event );

	//##ModelId=41582742014A
	virtual bool doOnTapChangeFinished( CEventMessage &Event );

	//##ModelId=4158274203A6
	virtual bool doOnTapChangeStart( CEventMessage &Event );

	//##ModelId=41582743034C
	virtual bool doOnFurnBreakerOff( CEventMessage &Event );

	//##ModelId=41121E110340
	bool doOnRegCurvNumChange( CEventMessage &Event );

	//##ModelId=41121F2F03D1
	bool doOnActivWallTempContr( CEventMessage &Event );

	//##ModelId=41121F910117
	bool doOnDeactivVallTempContr( CEventMessage &Event );

};

#endif /* _INC_CEAFELECTRICSIGNALSWRAPPER_41121D3801D9_INCLUDED */
