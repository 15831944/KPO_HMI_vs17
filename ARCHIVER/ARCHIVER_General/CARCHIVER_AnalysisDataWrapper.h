// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_ANALYSISDATAWRAPPER_45D2E6A502BD_INCLUDED
#define _INC_CARCHIVER_ANALYSISDATAWRAPPER_45D2E6A502BD_INCLUDED

#include "CEventMessage.h"
#include "CARCHIVER_Wrapper.h"
#include "CARCHIVER_Task.h"

class CPD_PRETREATDATA;
class CPD_LADLE;
class CPD_HEAT_DATA_LIQADD;
class CPP_HEAT;
class CPP_HEAT_PLANT;
class CPD_HEAT_DATA;
class CPD_SAMPLE;
class CPD_SAMPLE_REF;
class CPD_HOT_METAL;
class CPD_HOT_METAL_ORDER;
class CGC_PHASE;
class CPD_ACTION;
class CHD_SAMPLE;
class CHD_SAMPLE_ENTRY;
class CPD_PLANTSTATUS;


//##ModelId=45D2E6A502BD
class CARCHIVER_AnalysisDataWrapper 
: public CARCHIVER_Wrapper
{
public:
	//##ModelId=45D3032F0369
	CARCHIVER_AnalysisDataWrapper();

	//##ModelId=45D303300310
	virtual ~CARCHIVER_AnalysisDataWrapper();

protected:
	//##ModelId=45F97DEB0232
	CPD_HEAT_DATA* m_pPD_HEAT_DATA;

	bool updateHotMetalSampleRef(CEventMessage& Event, long SampleRef);
	bool updatePretreatSampleRef(CEventMessage& Event, long SampleRef);
	bool updateLiqAddSampleRef(CEventMessage& Event, long SampleRef);

	//write or update Sample Tables and in 
	//PD_LADLE_Anl switch to "prev" and set "last"
	//##ModelId=45D30D09016E
	bool writeHMAnalysis(CEventMessage& Event, seqAnalysisData &SeqAnalysisData);
	//insert into Sample Tables and switch in PD_LADLE_Data to 
	//"prev" and write last
	//##ModelId=45D30D0901AA
	bool writeHMSample(CEventMessage& Event);

	//##ModelId=45D42175017A
	CGC_PHASE* m_pGC_PHASE;

	//write sample in Sample Tables and update ladle data in 
	//PP_HEAT_PLANT
	//##ModelId=45D417B603CE
	bool writeSample(CEventMessage& Event,long TreatmentPosition);

	//Insert or update data in Sample Tables using GasData and 
	//
	//Update PD_LADLE_Data and PD_LADLE_Anl if ladle data 
	//available
	//##ModelId=45D4132C0293
	bool writeAnalysis(CEventMessage& Event, seqAnalysisData& SeqAnalysisData);

	//##ModelId=45D30B3B0265
	CPP_HEAT_PLANT* m_pPP_HEAT_PLANT;

	//##ModelId=45D30AC1031B
	CPD_PRETREATDATA* m_pPD_PRETREATDATA;

	//##ModelId=45D30B1D0092
	CPP_HEAT* m_pPP_HEAT;

  CPD_SAMPLE* m_pPD_SAMPLE;
  CPD_SAMPLE_REF* m_pPD_SAMPLE_REF;
  CPD_HOT_METAL* m_pPD_HOT_METAL;
  CPD_HOT_METAL_ORDER* m_pPD_HOT_METAL_ORDER;
  CHD_SAMPLE* m_pHD_SAMPLE;
  CHD_SAMPLE_ENTRY* m_pHD_SAMPLE_ENTRY;
  CPD_PLANTSTATUS* m_pPD_PLANTSTATUS;

  cCBS_ODBC_DBError m_lastError;

	//##ModelId=45D30B9D0138
	CPD_HEAT_DATA_LIQADD* m_pPD_HEAT_DATA_LIQADD;

	//##ModelId=45D30BC10042
	CPD_LADLE* m_pPD_LADLE;

  CPD_ACTION* m_pPD_ACTION;

	//##ModelId=45D3036C01DD
	virtual void deleteDBClasses();

	//##ModelId=45D3036D022E
	virtual void initDBClasses();

};

#endif /* _INC_CARCHIVER_ANALYSISDATAWRAPPER_45D2E6A502BD_INCLUDED */
