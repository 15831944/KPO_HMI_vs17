// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFTREATMENTMANAGERDATAWRAPPER_411789D00347_INCLUDED
#define _INC_CEAFTREATMENTMANAGERDATAWRAPPER_411789D00347_INCLUDED

#include <string>
using std::string;

#include "CEAFModelWrapper.h"
//##ModelId=411890DE0096
#include "CTreatmentManagerAimDataWrapper.h"

//##ModelId=411789D00347
class CEAFTreatmentManagerDataWrapper : public CTreatmentManagerAimDataWrapper, public CEAFModelWrapper
{
public:
	//##ModelId=411891F30153
	bool doOnHandleHeatAnnouncement(CEventMessage &Event);

  bool doOnChangeTreatmentMode(CEventMessage &Event);

	//##ModelId=41592F1A0070
  virtual bool doOnChangeAimData(CEventMessage &Event);

	virtual bool doOnChangeSteelGrade(CEventMessage &Event);


	//##ModelId=4118A122008A
	bool doOnChangeTapLadleData(CEventMessage &Event);

	//##ModelId=4118A065025F
	bool doOnChangeHotHeelData(CEventMessage &Event);

	//##ModelId=4118A0F901DF
	bool doOnHeatCancellation(CEventMessage &Event);

	//##ModelId=411891B10071
	bool doOnChangeProdPracBurner(CEventMessage &Event);

	//##ModelId=41189137017A
	bool doOnChangeProdPracJetMod(CEventMessage &Event, bool GetResults = true); // 2nd Argument is Krücke

	//##ModelId=4118A0A203C5
	bool doOnChangeManipGasLance(CEventMessage &Event);

	//##ModelId=4118918C032B
	bool doOnChangeProdPracElectric(CEventMessage &Event);

	//##ModelId=4118A18D012E
	bool doOnChangeProdPracRecipeControl(CEventMessage &Event);

	//##ModelId=429F142D0189
	bool doOnChangeProdPracInjection(CEventMessage &Event);

	//##ModelId=429F142D01B1
	bool doOnChangeProdPracOxygen(CEventMessage &Event);

	//##ModelId=429F142D01E3
	bool doOnChangeProdPracParameter(CEventMessage &Event); 

	//##ModelId=411891CC01ED
	bool doOnChangeProcPattern(CEventMessage &Event);

	//##ModelId=45EBDA3A0379
	bool doOnChangeProdPracPatternFeeding(CEventMessage &Event);
	//##ModelId=45EBDA3A0398
	bool doOnChangeProdPracBottomStirring(CEventMessage &Event); 

	bool doOnChangePlantStatus(CEventMessage &Event); 

};

#endif /* _INC_CEAFTREATMENTMANAGERDATAWRAPPER_411789D00347_INCLUDED */
