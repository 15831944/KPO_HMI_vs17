// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHMDTREATMENTMANAGERDATAWRAPPER_411789D00347_INCLUDED
#define _INC_CHMDTREATMENTMANAGERDATAWRAPPER_411789D00347_INCLUDED

#include <string>
using std::string;

//##ModelId=411789D00347
#include "CHMDModelWrapper.h"

//##ModelId=411789D00347
class CHMDTreatmentManagerDataWrapper : 
  public CHMDModelWrapper
{

  long CHMDTreatmentManagerDataWrapper::getProdPrac( const CEventMessage& Event);
  string CHMDTreatmentManagerDataWrapper::getSteelGradeCode( const CEventMessage& Event);
  void setComputerMode( const std::string& dataKey, CORBA::Long status);

public:
	//##ModelId=412F2BBB033D
	bool doOnChangeAimData(CEventMessage &Event);

	//##ModelId=41188F23003F
	bool doOnStartOfHeat(CEventMessage &Event);

	//##ModelId=41188F4C02C9
	bool doOnHeatDeparture(CEventMessage &Event);

	//##ModelId=41188F6802E7
	bool doOnHeatCancel(CEventMessage &Event);

	//##ModelId=41188F7E002C
	bool doOnHandleHeatAnnouncement( CEventMessage& Event, double sulph, bool use_AIM_S_OPER = true);

	//##ModelId=41188FB000F6
	bool doOnChangeProdPracData(CEventMessage &Event);

	//##ModelId=41188FDC03AC
	bool doOnChangeTapLadleData(CEventMessage &Event) ;

	bool doOnAnalysisReceived(CEventMessage &Event) ;

	bool doOnTempMeasurement(CEventMessage &Event) ;

};

#endif /* _INC_CHMDTREATMENTMANAGERDATAWRAPPER_411789D00347_INCLUDED */
