// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_LFSIGNALSANDMEASUREMENTWRAPPER_41DACADC0247_INCLUDED
#define _INC_CARCHIVER_LFSIGNALSANDMEASUREMENTWRAPPER_41DACADC0247_INCLUDED

#include "CEventMessage.h"

#include "CARCHIVER_SignalsAndMeasurementWrapper.h"

class CPDL_CYCL_MEAS_DATA;
class CPDL_HEAT_DATA;
class CPD_HEAT_DATA_STIRR;
class CPD_HEAT_DATA_STIRR;
class CPDL_HEAT_DATA_MELT;
class CPD_HEAT_DATA;


//##ModelId=41DACADC0247
class CARCHIVER_LFSignalsAndMeasurementWrapper 
: public CARCHIVER_SignalsAndMeasurementWrapper
{
public:
	//##ModelId=44C5C727038E
	bool doOnEmergencyLanceStirring(CEventMessage& Event, long status);

	//##ModelId=41F7702600D0
	bool doOnStirringStartEnd(CEventMessage& Event, long status);

	//##ModelId=41F7706E02FA
	bool doOnStirringBypassOnOff(CEventMessage& Event, long status);

	//##ModelId=446222940167
	bool doOnHeating(CEventMessage& Event);

	//##ModelId=41DACB3301EA
	CARCHIVER_LFSignalsAndMeasurementWrapper();

	//##ModelId=41DACB330348
	virtual ~CARCHIVER_LFSignalsAndMeasurementWrapper();

	//##ModelId=41DACB5B027E
	bool doOnCyclicMeasurement(CEventMessage& Event);

	//##ModelId=44B4F03801E2
	bool doOnTempMeasurement(CEventMessage& Event);
	
	//##ModelId=462F67730255
	bool doOnElectrodesInOperatingPosition(CEventMessage& Event);
	
	//##ModelId=462F677302A5
	bool doOnFurnaceBreaker(CEventMessage& Event, long status);
	
	//##ModelId=462F677302EB
	bool doOnPower(CEventMessage& Event, long status);
	
	//##ModelId=462F6773033B
	bool doOnTapChange(CEventMessage& Event, long TapChangStatus);

  bool doOnMechanicalSystem(CEventMessage& Event);

protected:
	//##ModelId=41F7716B0069
	CPD_HEAT_DATA_STIRR* m_pPD_HEAT_DATA_STIRR;

	//##ModelId=41EE3EE603B6
	CPDL_HEAT_DATA* m_pPDL_HEAT_DATA;

	//##ModelId=41DACB42014B
	CPDL_CYCL_MEAS_DATA* m_pPDL_CYCL_MEAS_DATA;

	//##ModelId=462E2E9B03C8
	CPDL_HEAT_DATA_MELT* m_pPDL_HEAT_DATA_MELT;


	CPD_HEAT_DATA* m_pPD_HEAT_DATA;

	//##ModelId=41DACB360035
	virtual void deleteDBClasses();

	//##ModelId=41DACB3602F2
  virtual void initDBClasses();

  bool handleCyclicData(CEventMessage& Event);

  bool handleCoolingWater(CEventMessage& Event);

};

#endif /* _INC_CARCHIVER_LFSIGNALSANDMEASUREMENTWRAPPER_41DACADC0247_INCLUDED */
