// Copyright (C) 2006 SMS Demag AG Germany

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CL3_EVENTHANDLER_4582BEB202C5_INCLUDED
#define _INC_CL3_EVENTHANDLER_4582BEB202C5_INCLUDED

#include "iDM_Interface_s.hh"
#include "CDH_EventHandler.h"
#include "CDH_OUT_Telcom_Impl.h"

#include "CPP_HEAT.h"
#include "CPD_HEAT_DATA.h"
#include "CPD_HEAT_DATA_STIRR.h"
#include "CEquipmentData.h"
#include "CPD_RECIPE.h"
#include "CPD_RECIPE_ENTRY.h"
#include "CPD_DELAYS.h"  
#include "CGT_MAT.h"
#include "CGT_MAT_PURP.h"
#include "CGT_DELAY_CODE.h"
#include "CPP_ORDER.h"
#include "CPD_PHASE_RES.h"
#include "CPP_HEAT_PLANT.h"
#include "CPDL_HEAT_DATA.h"
#include "CPDL_ACTIVITY_RES.h"
#include "CPDE_HEAT_DATA.h"
#include "CPDE_HEAT_DATA_BURN.h"
#include "CGC_STATUS.h"
#include "CGC_HEAT_STATUS.h"
#include "CPDE_CYCL_MEAS_DATA_INJ.h"
#include "CPD_LADLE_LIFE_DATA.h"
#include "CHD_RECIPE.h"
#include "CHD_RECIPE_ENTRY.h"
#include "CHD_SAMPLE.h"
#include "CHD_SAMPLE_ENTRY.h"
#include "CHD_SAMPLE_REF.h"
#include "CPD_HEAT_PLANT_REF.h"
#include "CPD_HEAT_REF.h"
#include "CPD_SAMPLE.h"
#include "CPD_SAMPLE_ENTRY.h"
#include "CPD_SAMPLE_REF.h"
#include "CGC_SAMPLELOC.h"
#include "CPD_ACTION.h"
#include "CPDH_HM_DATA.h"
#include "CPD_HOT_METAL.h"

#include "CGC_CREW_CAT.h"
#include "CGC_MEMBER_CAT.h"
#include "CPP_MEMBER_CREW_ASSIGNMENT.h"
#include "CPD_HEAT_DATA_LIQADD.h"
#include "CGC_Plantgroup_Container.h"

#include "CPP_HM.h"
#include "CPDH_ACTION.h"
#include "CHDH_EQUIP_COUNTER.h"


//##ModelId=4582BEB202C5
class CL3_EventHandler 
: public CDH_EventHandler
{
public:
	//This hook operation would be called automatically by 
	//handleEvent( FRISEVENT &event) 
	//when an event is received. And this operation must be 
	//implemented by the user or client
	//in order to use it.
	//##ModelId=4587AB5503E4
	virtual bool handleEvent(CEventMessage& evMessage);

	//##ModelId=4582C0AF01AE
	CL3_EventHandler( );

	//##ModelId=4582C0AF0322
	virtual ~CL3_EventHandler();

  /************************************************************************/
  /* Add by Zhu Xinhong for Severskij
  */
  //##ModelId=45E6D6BC026A
  DM::iDM_Interface_var  m_pDM_Interface;
  //##ModelId=45E6D6BC0273
  CSMC_DataProvider_Impl* m_pTelcom_Interface;
  
  
	bool provideData_ScheduleResponse(CEventMessage &Event); 
	bool provideData_DelayReport(CEventMessage &Event); 
	bool provideData_HeatStatus(CEventMessage &Event); 
	bool provideData_HeatReportMaterial(CEventMessage &Event);   
  bool provideData_ProductionDataEAF(CEventMessage& Event);    
  bool provideData_ProductionDataLF(CEventMessage& Event); 
  bool provideData_ProductionDataHMD(CEventMessage& Event); 	
	bool provideData_sampleTaken(CEventMessage &Event); 
	bool provideData_temperatureTaken(CEventMessage &Event); 
	string getCustSampleCode(const std::string& CustHeatID, const std::string& Plant, long PlantNo,long SampleNo);
	void getCrewInformation(const std::string& CrewCode, std::string& CrewName, std::string& SuperVisorName,std::string& OptrName);

  void getSteelAnalysisStream(DEF::seqString& SteelAnalysisDB);
  void getSlagAnalysisStream(DEF::seqString& SlagAnalysisDB);

protected:

  CEquipmentData      * m_pEquipmentData;
  CPP_HEAT            * m_pPP_HEAT;
  CPP_HEAT_PLANT      * m_pPP_HEAT_PLANT;
  CPP_ORDER           * m_pPP_ORDER;

  CPD_HEAT_DATA       * m_pPD_HEAT_DATA;
  CPD_HEAT_DATA_STIRR * m_pPD_HEAT_DATA_STIRR;
  CPD_HEAT_REF        * m_pPD_HEAT_REF;
  CPD_HEAT_PLANT_REF  * m_pPD_HEAT_PLANT_REF;

  CPD_RECIPE          * m_pPD_RECIPE;
  CPD_RECIPE_ENTRY    * m_pPD_RECIPE_ENTRY;

  CHD_RECIPE          * m_pHD_RECIPE;
  CHD_RECIPE_ENTRY    * m_pHD_RECIPE_ENTRY;

  CPD_DELAYS          * m_pPD_DELAYS;
  CPD_PHASE_RES       * m_pPD_PHASE_RES;

  CPD_LADLE_LIFE_DATA * m_pPD_LADLE_LIFE_DATA;

  CHD_SAMPLE          * m_pHD_SAMPLE;
  CHD_SAMPLE_ENTRY    * m_pHD_SAMPLE_ENTRY;
  CHD_SAMPLE_REF      * m_pHD_SAMPLE_REF;

  CPD_ACTION          * m_pPD_ACTION;

  CPD_SAMPLE          * m_pPD_SAMPLE;
  CPD_SAMPLE_ENTRY    * m_pPD_SAMPLE_ENTRY;
  CPD_SAMPLE_REF      * m_pPD_SAMPLE_REF;
  CGC_SAMPLELOC       * m_pGC_SAMPLELOC;
  
  CGT_MAT             * m_pGT_MAT;
  CGT_MAT_PURP        * m_pGT_MAT_PURP;
  CGT_DELAY_CODE      * m_pGT_DELAY_CODE;
  CGC_STATUS          * m_pGC_STATUS;
  CGC_HEAT_STATUS     * m_pGC_HEAT_STATUS;

  CPDE_HEAT_DATA      * m_pPDE_HEAT_DATA;

  CPDL_HEAT_DATA      * m_pPDL_HEAT_DATA;
  CPDL_ACTIVITY_RES   * m_pPDL_ACTIVITY_RES;
	CPDH_HM_DATA        * m_pPDH_HM_DATA;
	CPD_HOT_METAL       * m_pPD_HOT_METAL;

	CGC_CREW_CAT                 * m_pGC_CREW_CAT;
	CGC_MEMBER_CAT               * m_pGC_MEMBER_CAT;
	CPP_MEMBER_CREW_ASSIGNMENT   * m_pPP_MEMBER_CREW_ASSIGNMENT;

	CPD_HEAT_DATA_LIQADD   * m_pPD_HEAT_DATA_LIQADD;
	
	CPDE_HEAT_DATA_BURN   * m_pPDE_HEAT_DATA_BURN;
	
	CGC_Plantgroup_Container * m_pGC_Plantgroup_Container;

	CPP_HM * m_pPP_HM;
	CPDH_ACTION * m_pPDH_ACTION;
	CHDH_EQUIP_COUNTER * m_pHDH_EQUIP_COUNTER;

};

#endif /* _INC_CL3_EVENTHANDLER_4582BEB202C5_INCLUDED */
