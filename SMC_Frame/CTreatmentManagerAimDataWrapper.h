// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTREATMENTMANAGERAIMDATAWRAPPER_41139DA8031C_INCLUDED
#define _INC_CTREATMENTMANAGERAIMDATAWRAPPER_41139DA8031C_INCLUDED

class CEventMessage;

//##ModelId=41139DA8031C
class CTreatmentManagerAimDataWrapper 
{
public:
	//##ModelId=41139F8C023A
	virtual bool doOnChangeAimData(CEventMessage &Event);

protected:
	//AimMass
	//AimTemp
	//GradeCode
	//DepartureTime
	//##ModelId=411A46EF02CF
	bool doSetHeatOrderAimData(CEventMessage &Event);

	//##ModelId=411A4695006B
	bool doSetGradeAimAnalysisData(CEventMessage &Event);

};

#endif /* _INC_CTREATMENTMANAGERAIMDATAWRAPPER_41139DA8031C_INCLUDED */
