// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFMODELWRAPPER_4118CC3401F4_INCLUDED
#define _INC_CLFMODELWRAPPER_4118CC3401F4_INCLUDED

#include "CIntfLF.h"
#include "CSMM_ModelWrapper.h"
#include "CEventMessage.h"
#include "CLFModelTask.h"

#include "CGC_PHASE.h"
#include "CGC_RESTRI_DEF.h"
#include "CGC_RECIPE_SOURCE.h"
#include "CGCL_STIRR_INT.h"
#include "CGCL_STIRR_PHASE.h"
#include "CGT_PARAM.h"
#include "CGT_PARAM_MATRIX.h"
#include "CHD_RESTRI_ENTRY.h"
#include "CHD_RESTRI.h"
#include "CHD_GRADE_ANL.h"
#include "CHD_GRADE_EQUIV.h"
#include "CHD_TREATMODE.h"
#include "CHD_GRADE.h"
#include "CGT_EQUIV.h"
#include "CPP_HEAT.h"
#include "CPP_ORDER_SINGLE_AIMS.h"
#include "CGC_RECIPE_L1.h"
#include "CPD_MAT_AVAIL.h"
#include "CGT_MAT.h"
#include "CPD_HEAT_DATA.h"
#include "CPD_LADLE.h"
#include "CPD_SAMPLE.h"
#include "CPD_HEAT_DATA_LIQADD.h"
#include "CPD_SAMPLE_REF.h"
#include "CPD_PRETREATDATA.h"

#include "CPD_HEAT_DATA_PRODPRAC.h"

#include "CHDL_PP_EL_STEP.h"
#include "CHDL_PP_EL_STEP.h"
#include "CHDL_PP_EL.h"
#include "CHDL_PP_STIRR.h"
#include "CHDL_PP_STIRR_SPEC.h"
#include "CGCL_EL_PHASE.h"
#include "CGC_COMBI_RECIPE_ENTRY.h"
#include "CGCL_ACTIVITY.h"
#include "CChem_Elem_Container.h"
#include "CGC_Plant_Container.h"
#include "CSMC_RecipeHandler.h"

class CPD_SAMPLE_ENTRY;


//##ModelId=4118D691014F
class CLFModelWrapper : public CSMM_ModelWrapper
  
{
public:

	//##ModelId=462767AC0266
  CIntfLF* getpModelIntf();

	//##ModelId=417615BD0085
	virtual bool doModelResult(CEventMessage& Event);

	//##ModelId=4151820803E0
	virtual ~CLFModelWrapper();

	//##ModelId=42A06E2B0277
  virtual void initDBClasses();

	//##ModelId=42A06E2B02A9
	virtual void deleteDBClasses();

	//##ModelId=42A06E2B02E5
	void handleError(const char * Function, const char * Action);

	//##ModelId=42A06E2C000C
	void handleCORBAConnectionError(const char * Function, const char * Action);

	//##ModelId=42A06E2C0110
	void handleDBConnectionError(cCBS_DBExc &e, const char * Function, const char * Action);

	//##ModelId=42A06E2C02A1
  void handleDBConnectionError();

protected:

	//##ModelId=462767AC0307
  CSMC_RecipeHandler *m_pRecipeHandler;

	//##ModelId=4151820803CC
	CLFModelWrapper();

	//##ModelId=440DBF640362
	CChem_Elem_Container* m_pChem_Elem_Container;

  CGC_Plant_Container* m_pGC_Plant_Container;

	//##ModelId=415182090124
	bool sequence_set_aim_data(const std::string& HeatID, const std::string& TreatID, const std::string& Plant, long PlantNo, bool Online = true);

	//##ModelId=4151820901CF
	bool sequence_set_tap_ladle_data(const std::string& HeatID, const std::string& TreatID, const std::string& Plant);

	//##ModelId=4151820903D7
	bool sequence_set_production_practice_data_electric(CEventMessage& Event);

	//##ModelId=42A06E2D00E9
	bool sequence_set_production_practice_data_stirring(CEventMessage& Event);

	//##ModelId=42A06E2D037E
	bool sequence_set_production_practice_data_recipe_ctrl(CEventMessage& Event);

	//##ModelId=4151820A00E0
	bool sequence_set_liquid_material_data(const std::string& HeatID, const std::string& TreatID, const std::string& Plant, long TreatNo, std::string LadleType, long LadleNo, long SampleRef, double SteelWeight, double SlagWeight);

	//##ModelId=4151820A018A
  bool sequence_set_plant_status(const std::string& HeatID, const std::string& TreatID);

  // adaption of ANL, ANL given as referecne
  // method writes EventLog if ANL of ENAME is changes by Parameter
  bool adaptAimAnl(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PLANTNO, const std::string& AIMTYPE, const std::string& ENAME, double& ANL);

  // set new ladle and LadleTempLossStat
  bool sequence_set_ladle_data(const std::string& HeatID, const std::string& TreatID, const std::string& Plant);

	//##ModelId=42A06E2E02FF
  CModelResults_Impl* m_pModelResults;

	//##ModelId=42A06E2E0359
	CGC_PHASE* m_pGC_PHASE;

	//##ModelId=42A06E2E0395
	CGC_RESTRI_DEF* m_pGC_RESTRI_DEF; 

	//##ModelId=42A06E2E03D1
	CGC_RECIPE_SOURCE *m_pGC_RECIPE_SOURCE;

	//##ModelId=42A06E2F002F
  CGC_COMBI_RECIPE_ENTRY *m_pGC_COMBI_RECIPE_ENTRY;

	//##ModelId=42A06E2F006B
  CGCL_STIRR_INT *m_pGCL_STIRR_INT;

	//##ModelId=42A06E2F00B1
  CGCL_STIRR_PHASE *m_pGCL_STIRR_PHASE;

	//##ModelId=42A06E2F00ED
	CGT_PARAM         * m_pGT_PARAM; 
	CGT_PARAM_MATRIX  * m_pGT_PARAM_MATRIX  ; 

	CHD_RESTRI* m_pHD_RESTRI; 

	//##ModelId=42A06E2F0170
	CHD_RESTRI_ENTRY* m_pHD_RESTRI_ENTRY; 

	//##ModelId=42A06E2F01B6
	CHD_GRADE_ANL*    m_pHD_GRADE_ANL;
	CHD_GRADE_EQUIV*  m_pHD_GRADE_EQUIV;

	CHD_TREATMODE*  m_pHD_TREATMODE;

	CHD_GRADE* m_pHD_GRADE;
	CGT_EQUIV* m_pGT_EQUIV;

	//##ModelId=42A06E2F01F2
  CPD_MAT_AVAIL *m_pPD_MAT_AVAIL;

  CGT_MAT *m_pGT_MAT;


	//##ModelId=42A06E2F022E
  CPD_HEAT_DATA* m_pPD_HEAT_DATA;

	//##ModelId=42A06E2F0274
  CPP_HEAT* m_pPP_HEAT;
  CPP_ORDER_SINGLE_AIMS* m_pPP_ORDER_SINGLE_AIMS;

	//##ModelId=462767AC03DA
  CGC_RECIPE_L1* m_pGC_RECIPE_L1;


	//##ModelId=42A06E2F02F6
	CPD_HEAT_DATA_LIQADD* m_pPD_HEAT_DATA_LIQADD;

	//##ModelId=42A06E2F033C
  CPD_SAMPLE_REF* m_pPD_SAMPLE_REF;
  CPD_PRETREATDATA* m_pPD_PRETREATDATA;


	//##ModelId=42A06E2F0378
	CPD_LADLE* m_pPD_LADLE;

	//##ModelId=42A06E2F03BE
	CPD_SAMPLE* m_pPD_SAMPLE;

	//##ModelId=42A06E30001D
	CPD_HEAT_DATA_PRODPRAC* m_pPD_HEAT_DATA_PRODPRAC;

	//##ModelId=42A06E3000A9
  CHDL_PP_EL_STEP* m_pHDL_PP_EL_STEP;
	//##ModelId=42A06E3000EF
  CHDL_PP_EL* m_pHDL_PP_EL;

  CHDL_PP_STIRR* m_pHDL_PP_STIRR;

	//##ModelId=42A06E300185
  CHDL_PP_STIRR_SPEC* m_pHDL_PP_STIRR_SPEC;
	//##ModelId=42A06E3001D5
  CGCL_EL_PHASE* m_pGCL_EL_PHASE;
	//##ModelId=42A06E30021B
  CGCL_ACTIVITY* m_pGCL_ACTIVITY;

  CPD_SAMPLE_ENTRY* m_pPD_SAMPLE_ENTRY;

  long getProdPracticePointer(const std::string & HeatID, const std::string & TreatID, const std::string& Plant, const std::string & PracticeCode);

  long getTreatmentModeNo(CEventMessage &Event);
  long getTreatmentModeNo(const std::string & HeatID, const std::string & TreatID, const std::string& Plant);

};

#endif /* _INC_CLFMODELWRAPPER_4118CC3401F4_INCLUDED */