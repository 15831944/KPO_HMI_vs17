// Copyright (C) 2009 SMS Siemag AG, Germany

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_SIGNALSANDMEASUREMENTWRAPPER_45D5A36B026A_INCLUDED
#define _INC_CARCHIVER_SIGNALSANDMEASUREMENTWRAPPER_45D5A36B026A_INCLUDED

#include <set>

#include "CARCHIVER_Wrapper.h"
#include "CEventMessage.h"


#include "CDataConversion.h"
#include "CEquipmentData.h"
#include "CHeatStatusContainer.h"
#include "DEF_GC_MEASUREMENT_TYPE.h"
#include "CPP_HEAT_PLANT.h"
#include "CPP_HEAT.h"
#include "CPP_ORDER.h"
#include "CPP_ORDER.h"
#include "CGC_PHASE.h"
#include "CGC_HEAT_STATUS.h"
#include "CGC_SAMPLELOC.h"
#include "CPD_SAMPLE.h"
#include "CPD_SAMPLE_ENTRY.h"
#include "CPD_ACTION.h"
#include "CHD_ACTION.h"
#include "CPD_LADLE.h"
#include "CPD_LADLE_LIFE_DATA.h"
#include "CPD_ELEC_SYSTEM.h"
#include "CPD_ELEC_TAPCH.h"
#include "CPD_TAPCH_DATA.h"
#include "CPD_COOLWATER.h"
#include "CPD_PHASE_RES.h"
#include "CPD_PHASE_RES_ANL.h"
#include "CPD_PRETREATDATA.h"
#include "CPD_HEAT_REF.h"
#include "CPD_PLANTSTATUS.h"
#include "CPD_WASTEGAS_CYCL_MEAS_DATA.h"
#include "CPD_HEAT_DATA.h"
#include "CPD_SAMPLE_REF.h"
#include "CPD_HEAT_DATA_LIQADD.h"
#include "CPD_RECIPE.h"
#include "CPD_RECIPE_ENTRY.h"
#include "CPD_MAT_FEED_CYCL_MEAS_DATA.h"
#include "CHD_SAMPLE.h"
#include "CHD_SAMPLE_ENTRY.h"


class CARCHIVER_SignalsAndMeasurementWrapper 
  : public CARCHIVER_Wrapper
{
public:

  CARCHIVER_SignalsAndMeasurementWrapper();

  virtual ~CARCHIVER_SignalsAndMeasurementWrapper();

protected:

  CPD_PHASE_RES* m_pPD_PHASE_RES;

  CPD_PHASE_RES_ANL* m_pPD_PHASE_RES_ANL;

  CPD_COOLWATER* m_pPD_COOLWATER;

  CPP_HEAT_PLANT* m_pPP_HEAT_PLANT;

  CPP_ORDER* m_pPP_ORDER;

  CPP_HEAT* m_pPP_HEAT;

  CGC_PHASE* m_pGC_PHASE;

  CPD_SAMPLE* m_pPD_SAMPLE;

  CPD_SAMPLE_ENTRY* m_pPD_SAMPLE_ENTRY;

  CPD_ACTION* m_pPD_ACTION;

  CHD_ACTION* m_pHD_ACTION;

  CPD_LADLE* m_pPD_LADLE;

  CPD_LADLE_LIFE_DATA* m_pPD_LADLE_LIFE_DATA;

  CPD_ELEC_SYSTEM* m_pPD_ELEC_SYSTEM;

  CPD_ELEC_TAPCH* m_pPD_ELEC_TAPCH;

  CEquipmentData* m_pEquipmentData;

  CHeatStatusContainer* m_pHeatStatusContainer;

  CPD_TAPCH_DATA* m_pPD_TAPCH_DATA;

  CPD_PRETREATDATA* m_pPD_PRETREATDATA;

  CPD_HEAT_REF* m_pPD_HEAT_REF;

  CPD_PLANTSTATUS* m_pPD_PLANTSTATUS;	

  CPD_WASTEGAS_CYCL_MEAS_DATA* m_pPD_WASTEGAS_CYCL_MEAS_DATA;

  CPD_HEAT_DATA* m_pPD_HEAT_DATA;

  CPD_SAMPLE_REF* m_pPD_SAMPLE_REF;

  CGC_SAMPLELOC* m_pGC_SAMPLELOC;

  CHD_SAMPLE* m_pHD_SAMPLE;

  CHD_SAMPLE_ENTRY* m_pHD_SAMPLE_ENTRY;

  CPD_HEAT_DATA_LIQADD* m_pPD_HEAT_DATA_LIQADD;
  CPD_RECIPE* m_pPD_RECIPE;
  CPD_RECIPE_ENTRY* m_pPD_RECIPE_ENTRY;

  CGC_HEAT_STATUS* m_pGC_HEAT_STATUS;

  CPD_MAT_FEED_CYCL_MEAS_DATA* m_pPD_MAT_FEED_CYCL_MEAS_DATA;

  cCBS_ODBC_DBError m_lastError;

  std::set<std::string> m_PurpList;

  bool handleBottomStirringStart(CEventMessage& Event, seqGasData& SeqGasData, double ECon = 0.0);

  bool handleBottomStirringEnd(CEventMessage& Event, seqGasData& SeqGasData, double ECon = 0.0);

  bool handleTopLanceBlowingStart(CEventMessage& Event, seqGasData& SeqGasData, double ECon = 0.0);

  bool handleTopLanceBlowingEnd(CEventMessage& Event, seqGasData& SeqGasData, double ECon = 0.0);

  bool handleOnBlowingStart(CEventMessage& Event, seqGasData& SeqGasData, double ECon = 0.0);

  bool handleOnBlowingEnd(CEventMessage& Event, seqGasData& SeqGasData, double ECon = 0.0);

  bool handleDeslagging(CEventMessage& Event, long status);

  bool handleTappingLadleStirring(CEventMessage& Event, long status);

  //bool handleSampleRef(CEventMessage& Event, long MeasType, long SampleCounter);


  //Temperature and CELOX handling. Writing data into 
  //PD_SAMPLE, PD_LADLEDATA, PD_REPORT
  bool handleTempOxyMeasurement(CEventMessage& Event,long TreatmentPosition);

  bool handleElectrodesInOperatingPosition(CEventMessage& Event, double  elecegy, long status);

  bool handleFurnaceBreaker(CEventMessage& Event, long status);

  bool handlePower(CEventMessage& Event, long  status, double elecegy);

  bool handleTapChange(CEventMessage& Event, long TapChangStatus);

  virtual void deleteDBClasses();

  virtual void initDBClasses();

  virtual bool handleCoolingWater(CEventMessage& Event);

  bool handleWasteGas(CEventMessage& Event);

  bool addSampleDetails(long SAMLPE_COUNTER, const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PLANTNO);

  bool updateHeatDataSampleRef(CEventMessage& Event, long SampleRef);

  bool updatePretreatSampleRef(CEventMessage& Event, long SampleRef );

  // writing PC_ACTION depending on Actoin as DEF_GC_ACTION_DEF::DeslaggingStart or DEF_GC_ACTION_DEF::DeslaggingEnd
  bool handleOnDeslagging(CEventMessage& Event, long Action );

  bool IncreaseLadleLifeDate(long LadleNo,std::string LadleType,bool Commit);

  bool SetAction(CEventMessage& Event, long ActionNo, const std::string& ActionValue, long ActionStatus, const std::string& ActionUnit, double ElecEgy, bool pCommit);
    
  bool handleMechanicalSystem(CEventMessage& Event, seqGasData& SeqGasData, double ElecCons, long ActionNo);

};

#endif /* _INC_CARCHIVER_SIGNALSANDMEASUREMENTWRAPPER_45D5A36B026A_INCLUDED */