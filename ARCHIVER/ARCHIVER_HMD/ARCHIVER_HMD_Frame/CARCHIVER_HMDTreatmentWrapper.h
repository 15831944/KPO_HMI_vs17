// Copyright (C) 2013 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_HMDTREATMENTWRAPPER_45D5D76801F2_INCLUDED
#define _INC_CARCHIVER_HMDTREATMENTWRAPPER_45D5D76801F2_INCLUDED

#include "CARCHIVER_TreatmentWrapper.h"

class CARCHIVER_HMDTreatmentWrapper 
: public CARCHIVER_TreatmentWrapper
{
public:
	bool doOnHeatDeparture(CEventMessage& Event);
  bool copyHDH_HMData(CEventMessage& Event, bool Commit);
  bool copyHDH_Action(CEventMessage& Event, bool Commit);
  bool copyHDH_HMPhaseData(CEventMessage& Event, bool Commit);
  bool copyHDH_CyclMeasData(CEventMessage& Event, bool Commit);

  // USAD: no any implementation has to be done for following functions in ARCHIVER, only in CDM_HMDDBManager
	//bool doOnHeatAnnouncement(CEventMessage& Event); 
	//bool doOnUpdateAimDepartureTime(CEventMessage& Event);
	//bool doOnHeatCancel(CEventMessage& Event);
	//bool doOnHeatStart(CEventMessage& Event);
	//bool doOnHeatEnd(CEventMessage& Event);
	//bool doOnHeatAnnounceStatus(CEventMessage& Event);
  //bool doOnChangeAimData(CEventMessage& Event);
  //bool doOnChangeTreatmentType(CEventMessage& Event);

	CARCHIVER_HMDTreatmentWrapper();
	virtual ~CARCHIVER_HMDTreatmentWrapper();

protected:

	virtual void deleteDBClasses();
	virtual void initDBClasses();

};

#endif /* _INC_CARCHIVER_HMDTREATMENTWRAPPER_45D5D76801F2_INCLUDED */
