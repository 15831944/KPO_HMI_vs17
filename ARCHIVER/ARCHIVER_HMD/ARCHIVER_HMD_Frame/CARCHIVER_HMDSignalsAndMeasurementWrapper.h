// Copyright (C) 2013 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_HMDSIGNALSANDMEASUREMENTWRAPPER_41DACADC0247_INCLUDED
#define _INC_CARCHIVER_HMDSIGNALSANDMEASUREMENTWRAPPER_41DACADC0247_INCLUDED

#include "CARCHIVER_SignalsAndMeasurementWrapper.h"
#include "CEventMessage.h"

class CPDH_CYCL_MEAS_DATA;
class CPDH_HM_DATA;
class CPD_PLANTSTATUS_PLANT;

class CARCHIVER_HMDSignalsAndMeasurementWrapper 
: public CARCHIVER_SignalsAndMeasurementWrapper
{
public:
	CARCHIVER_HMDSignalsAndMeasurementWrapper();

	virtual ~CARCHIVER_HMDSignalsAndMeasurementWrapper();

	bool doOnCyclicMeasurement(CEventMessage& Event);

protected:
	CPDH_CYCL_MEAS_DATA* m_pPDH_Cycl_Meas_Data;

  CPDH_HM_DATA* m_pPDH_HM_DATA;
	CPD_PLANTSTATUS_PLANT* m_pPD_PLANTSTATUS_PLANT;

	virtual void deleteDBClasses();

	virtual void initDBClasses();

};

#endif /* _INC_CARCHIVER_HMDSIGNALSANDMEASUREMENTWRAPPER_41DACADC0247_INCLUDED */
