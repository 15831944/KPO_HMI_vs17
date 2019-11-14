// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_LFTREATMENTWRAPPER_45DAD0630010_INCLUDED
#define _INC_CARCHIVER_LFTREATMENTWRAPPER_45DAD0630010_INCLUDED

#include "CARCHIVER_TreatmentWrapper.h"

class CPDL_HEAT_DATA;
class CPDL_CYCL_MEAS_DATA;
class CEquipmentData;
class CPD_PRETREATDATA;
class CPD_HEAT_DATA_LIQADD;
class CGC_PHASE;
class CPD_PHASE_RES;
class CGC_LADLE_PARTS;
class CGC_LADLE_DEF;
class CHD_GRADE;
class CHDL_CYCL_MEAS_DATA;
class CHDL_HEAT_DATA;
class CHDL_PP_STIRR;
class CHDL_PP_STIRR_SPEC;
class CGC_HEAT_STATUS; 
class CPD_PLANTSTATUS;
class CPDL_HEAT_DATA_MELT;
class CPD_ELEC_TAPCH;

//##ModelId=462E23E002AC
class CARCHIVER_LFTreatmentWrapper 
	: public CARCHIVER_TreatmentWrapper
{
public:
	//##ModelId=462E23FB016F
	CARCHIVER_LFTreatmentWrapper();

	//##ModelId=462E23FB03B4
	virtual ~CARCHIVER_LFTreatmentWrapper();

	//##ModelId=462F85900300
  //do in DM, remove later
	//bool doOnHeatDeparture(CEventMessage& event);

	//##ModelId=462F8590033C
  //do in DM, remove later
	//bool doOnHeatAnnouncement(CEventMessage& Event);

	//##ModelId=462F85900378
	bool doOnHeatStart(CEventMessage& Event);

	//##ModelId=462F85910008
	bool doOnHeatAnnounceStatus(CEventMessage& Event);

	//##ModelId=462F85910044
  //do in DM, remove later
	//bool doOnHeatCancel(CEventMessage& Event);

	//##ModelId=462F85910094
	bool doOnUpdateAimDepartureTime(CEventMessage& Event);

	//##ModelId=462F859100EE
  bool doOnUpdateAimTemperature(CEventMessage& Event);

  bool doPhaseReport(CEventMessage& Event);

protected:
	//##ModelId=462E291700E9
	CEquipmentData *m_pEquipmentData;

	//##ModelId=462E292903D7
	CPDL_HEAT_DATA *m_pPDL_HEAT_DATA;

	//##ModelId=462E28FF0162
	CPDL_CYCL_MEAS_DATA *m_pPDL_CYCL_MEAS_DATA;

	CPD_PRETREATDATA *m_pPD_PRETREATDATA;

	CPD_HEAT_DATA_LIQADD *m_pPD_HEAT_DATA_LIQADD;
	CGC_PHASE *m_pGC_PHASE;
	CPD_PHASE_RES *m_pPD_PHASE_RES;
	CGC_LADLE_PARTS *m_pGC_LADLE_PARTS;
	CGC_LADLE_DEF *m_pGC_LADLE_DEF;
	CHD_GRADE* m_pHD_GRADE;
	CHDL_CYCL_MEAS_DATA* m_pHDL_CYCL_MEAS_DATA;
	CHDL_HEAT_DATA* m_pHDL_HEAT_DATA;
	CHDL_PP_STIRR* m_pHDL_PP_STIRR;
	CHDL_PP_STIRR_SPEC* m_pHDL_PP_STIRR_SPEC;
  CGC_HEAT_STATUS* m_pCGC_HEAT_STAT;
  CPD_PLANTSTATUS* m_pPD_PLANTSTATUS;
  CPDL_HEAT_DATA_MELT* m_pPDL_HEAT_DATA_MELT;
  CPD_ELEC_TAPCH* m_pPD_ELEC_TAPCH;

	//##ModelId=462E23FF02A2
	virtual void deleteDBClasses();

	//##ModelId=462E23FF0023
	virtual void initDBClasses();

};

#endif /* _INC_CARCHIVER_LFTREATMENTWRAPPER_45DAD0630010_INCLUDED */
