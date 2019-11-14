// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_TREATMENTWRAPPER_45D56EBE00F0_INCLUDED
#define _INC_CARCHIVER_TREATMENTWRAPPER_45D56EBE00F0_INCLUDED

#include "CARCHIVER_Wrapper.h"
#include "CEventMessage.h"
#include "CPD_HEAT_DATA.h"
#include "CPD_HEAT_DATA_PRODPRAC.h"
#include "CPD_ACTION.h"
#include "CPP_HEAT_PLANT.h"
#include "CPP_HEAT.h"
#include "CPD_HEAT_DATA_LIQADD.h"
#include "CPP_ORDER.h"
#include "CPD_PRETREATDATA.h"
#include "CPD_HEAT_YIELDS.h"
#include "CPD_LADLE.h"
#include "CPD_RECIPE.h"
#include "CGT_MAT_PURP.h"
#include "CPD_DELAYS.h"
#include "CHeatStatusContainer.h"
#include "CGC_HEAT_STATUS.h"
#include "CEquipmentData.h"
#include "CPD_HEAT_REF.h"
#include "CGT_GRADE_PRODPRAC.h"
#include "CPD_HEAT_PLANT_REF.h"
#include "CPD_PLANTSTATUS.h"
#include "CHD_GRADE.h"
#include "CPP_SHIFT_CREW_ASSIGNMENT.h"
#include "CPD_SAMPLE.h"
#include "CPD_SAMPLE_ENTRY.h"
#include "CHD_COOLWATER.h"
#include "CHD_LADLE_LIFE_DATA.h"
#include "CHD_PHASE_RES.h"
#include "CHD_PHASE_RES_ANL.h"
#include "CHD_PHASE_RES_PLANT.h"
#include "CHD_WASTEGAS_CYCL_MEAS_DATA.h"
#include "CPD_ELEC_SYSTEM.h"
#include "CGC_PHASE.h"
#include "CPD_PHASE_RES.h"
#include "CPP_ORDER_SINGLE_AIMS.h"
#include "CPD_PHASE_RES_ANL.h"
#include "CGC_PLANTGROUP.h"
#include "CGC_Plant_Container.h"
#include "CPD_SCRAP_CONTAINER_ORDER.h"
#include "CPD_HOT_METAL.h"
#include "CPD_HOT_METAL_ORDER.h"

class CARCHIVER_TreatmentWrapper 
  : public CARCHIVER_Wrapper
{
protected:

  std::vector<std::string> m_LadlePartCode;

  CEquipmentData* m_pEquipmentData;

  CGC_HEAT_STATUS* m_pGC_HEAT_STATUS;

  CHeatStatusContainer* m_pHeatStatusContainer;

  CPD_DELAYS* m_pPD_DELAYS;

  CGT_MAT_PURP* m_pGT_MAT_PURP;

  CPD_LADLE* m_pPD_LADLE;

  CPD_HEAT_YIELDS* m_pPD_HEAT_YIELDS;

  CPD_PRETREATDATA* m_pPD_PRETREATDATA;

  CPP_ORDER* m_pPP_ORDER;

  CPD_HEAT_DATA_LIQADD* m_pPD_HEAT_DATA_LIQADD;

  CPD_HEAT_DATA_PRODPRAC* m_pPD_HEAT_DATA_PRODPRAC;

  CPD_ACTION* m_pPD_ACTION;

  CHD_LADLE_LIFE_DATA* m_pHD_LADLE_LIFE_DATA;

  CHD_PHASE_RES* m_pHD_PHASE_RES;

  CHD_PHASE_RES_ANL* m_pHD_PHASE_RES_ANL;

  CHD_PHASE_RES_PLANT* m_pHD_PHASE_RES_PLANT;

  CHD_WASTEGAS_CYCL_MEAS_DATA* m_pHD_WASTEGAS_CYCL_MEAS_DATA;

  CPD_ELEC_SYSTEM* m_pPD_ELEC_SYSTEM;

  CGC_PHASE* m_pGC_PHASE;

  CPD_PHASE_RES* m_pPD_PHASE_RES;

  CPP_ORDER_SINGLE_AIMS* m_pPP_ORDER_SINGLE_AIMS;

  CPP_HEAT_PLANT* m_pPP_HEAT_PLANT;	

  CPP_HEAT* m_pPP_HEAT;

  CPD_HEAT_DATA* m_pPD_HEAT_DATA;

  CPD_HEAT_REF* m_pPD_HEAT_REF;

  CGT_GRADE_PRODPRAC* m_pGT_GRADE_PRODPRAC;

  CPD_HEAT_PLANT_REF* m_pPD_HEAT_PLANT_REF;

  CPD_PLANTSTATUS* m_pPD_PLANTSTATUS;

  CHD_GRADE* m_pHD_GRADE;

  CPP_SHIFT_CREW_ASSIGNMENT* m_pPP_SHIFT_CREW_ASSIGNMENT;

  CPD_SAMPLE* m_pPD_SAMPLE;

  CPD_SAMPLE_ENTRY* m_pPD_SAMPLE_ENTRY;

  CHD_COOLWATER* m_pHD_COOLWATER;

  CPD_PHASE_RES_ANL* m_pPD_PHASE_RES_ANL;

  CPD_SCRAP_CONTAINER_ORDER* m_pPD_SCRAP_CONTAINER_ORDER;

  CPD_HOT_METAL* m_pPD_HOT_METAL;

  CPD_HOT_METAL_ORDER* m_pPD_HOT_METAL_ORDER;

  CGC_PLANTGROUP * m_pGC_PLANTGROUP;
  CGC_Plant_Container * m_pGC_Plant_Container;

  cCBS_ODBC_DBError m_lastError;

  virtual void initDBClasses();
  virtual void deleteDBClasses();

  bool handleTappingStart(CEventMessage& Event);
  bool handleUpdateAimSteelWeight(CEventMessage& Event, double Weight);
  bool handleUpdateAimDepartureTime(CEventMessage& Event, CDateTime& depTime);
  bool handleUpdateAimTemperature(CEventMessage& Event, double temp);
  bool handleHeatAnnounceStatus(CEventMessage& Event, double AimTapWeightCalc);
  bool handleHeatStart(CEventMessage& Event);
  
public:

  CARCHIVER_TreatmentWrapper();

  virtual ~CARCHIVER_TreatmentWrapper();

};

#endif /* _INC_CARCHIVER_TREATMENTWRAPPER_45D56EBE00F0_INCLUDED */
