// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFMODELWRAPPER_4118CC3401F4_INCLUDED
#define _INC_CEAFMODELWRAPPER_4118CC3401F4_INCLUDED

#include <vector>
#include <map>

#include "CSMM_ModelWrapper.h"

#include "CIntfEAF.h"
#include "CInv.h"

#include "CEventMessage.h"
#include "CModelResults_Impl.h"
#include "CSMC_RecipeHandler.h"
#include "CGC_PhaseContainer.h"
#include "CPD_SAMPLE_REF.h"
#include "CPD_HEAT_DATA.h"

class CGC_COMBI_RECIPE_ENTRY;
class CHDE_PP_BURNER_STEP_ENTRY;
class CHDE_PP_BURNER;
class CHDE_PP_INJECTION_STEP_ENTRY;
class CHDE_PP_INJECTION;
class CGCE_INJECTION;
class CGCE_BURNER;
class CHDE_PP_EL;
class CHDE_PP_PROCESS_PARAM;
class CHDE_PP_EL_STEP_ENTRY;
class CGCE_PROC_PHASE_CODES_EAF;
class CGCE_INJECTION_TYPE;
class CGT_MAT;
class CGT_MAT_PURP;
class CGC_PHASE;
class CGC_RESTRI_DEF;
class CGC_RECIPE_SOURCE;
class CHD_RESTRI_ENTRY;
class CHD_RESTRI;
class CPD_MAT_AVAIL;
class CPP_HEAT;
class CPP_HEAT_PLANT;
class CHD_GRADE;
class CHD_GRADE_ANL;
class CHD_GRADE_EQUIV;
class CGT_EQUIV;
class CPD_LADLE;
class CPD_HEAT_DATA_PRODPRAC;
class CPD_HEAT_DATA_LIQADD;
class CPD_HOTHEEL;
class CGT_TREATMODE_ENTRY;

class CHD_TREATMODE;
class CHD_TREATMODE_ENTRY;
class CHD_GRADE_SINGLE_AIMS;
class CPP_ORDER_SINGLE_AIMS;
class CPD_SCRAP_CONTAINER_ENTRY;


class CPD_SCRAP_CONTAINER_ORDER;
class CPD_SCRAP_CONTAINER_ORDER_ENTRY;
class CPD_PRETREATDATA;
class CPD_SAMPLE;
class CHDE_PP_PROCESS;
class CHDE_PP_PROCESS_STEP_ENTRY;
class CPD_SAMPLE_ENTRY;
class CPD_RECIPE;
class CPD_RECIPE_ENTRY;

// production practice - bottom stirring
class CHDE_PP_STIRR;
class CHDE_PP_STIRR_SPEC;
class CHD_MAT_FEED;
class CHDE_PP_FLAME_PROFILE;
class CGTE_PP_FLAME_PROFILE;

class CHDE_FLAME_PROFILE;
class CChgLocs;               // first class ? 


//##ModelId=4118D1D1018C
class CEAFModelWrapper : public CSMM_ModelWrapper  
{

public:

  const CCfgEAF* getpCfgEAF() const;

  CCfgEAF* getUnConstpCfgEAF();

  //##ModelId=45EBDA3C0183
  CIntfEAF* getpModelIntf();

  //##ModelId=4118D23503AD
  bool doModelResult(CEventMessage &Event);

  //##ModelId=4146F7C80377
  virtual ~CEAFModelWrapper();

  //##ModelId=4201044A031C
  virtual void initDBClasses();

  //##ModelId=4201044B010B
  virtual void deleteDBClasses();

  //##ModelId=4201044B01BF
  void handleError(const char * Function, const char * Action);

  //##ModelId=4201044C0333
  void handleCORBAConnectionError(const char * Function, const char * Action);

  //##ModelId=4201044E00AB
  void handleDBConnectionError(cCBS_DBExc &e, const char * Function, const char * Action);

  //##ModelId=420104510236
  void handleDBConnectionError();

protected:

  //##ModelId=4146F7C8033B
  CEAFModelWrapper();

  bool isModelDevice(const string& DeviceName);

  long getTreatmentModeNo(CEventMessage &Event);
  long getTreatmentModeNo(const std::string & HeatID, const std::string & TreatID, const std::string& Plant);

  bool setNoOfBasket(CEventMessage &Event);

  // mrut  2006-03-01 after meeting with pike
	//##ModelId=45EBDA3C02DB
  bool sequence_update_hot_heel_data(const std::string& HeatID, const std::string& TreatID, const std::string& Plant, long PlantNo, double SteelMass, double SlagMass, double Temperature);

  // returns value of practice pointer as read from table PD_HEAT_DATA_PRODPRAC
	//##ModelId=467645DB017E
  long getProdPracticePointer(const std::string & HeatID, const std::string & TreatID, const std::string& Plant, const std::string & PracticeCode); 

  //##ModelId=4200DE3B0125
  bool sequence_set_aim_data(const std::string& HeatID, const std::string& TreatID, const std::string& Plant, long PlantNo);

  bool sequence_set_treatmentmap_data(const std::string& HeatID, const std::string& TreatID, const std::string& Plant,long TreatmentMode);

  //##ModelId=4200DE3B02CA
  bool sequence_set_tap_ladle_data(const std::string& HeatID, const std::string& TreatID, const std::string& Plant);

  //##ModelId=4200DE3C0072
  bool sequence_set_hot_heel_data(const std::string& HeatID, const std::string& TreatID, const std::string& Plant, long PlantNo);

  //##ModelId=4200DE3C01E5
  bool sequence_set_liquid_material_data(const std::string& HeatID, const std::string& TreatID, long TreatNo, long AddNo, const std::string& PlantID);

  //##ModelId=4200DE3D03BD
  bool sequence_set_plant_status(const std::string& HeatID, const std::string& TreatID);

  //mrut 2006-01-26 looks like plant status data must be fetched from interface.
	//##ModelId=45EBDA3D02E9
  bool sequence_set_plant_status(const std::string& HeatID, const std::string& TreatID, DM::iDM_Interface_var& pDM_Interface, const std::string& DataKey);

  //##ModelId=4200DE44006A
  bool sequence_set_basket_data(const std::string& HeatID, const std::string& TreatID,CEventMessage &Event);

  // one common method for all practices, independent from any practice pointer, will read heat-related tabel only
  //##ModelId=4200DE3E016F
  bool sequence_set_all_heat_related_production_practice_data     (const std::string& HeatID, const std::string& TreatID, const std::string& Plant, long PlantNo);

  //##ModelId=4200DE400230
  bool sequence_set_production_practice_data_electric             (const std::string& HeatID, const std::string& TreatID, const std::string& Plant);

  
  //##ModelId=4200DE3F0026
  bool sequence_set_production_practice_data_burner               (const std::string& HeatID, const std::string& TreatID, const std::string& Plant, long PlantNo);

	//##ModelId=467645DC0099
  bool sequence_set_production_practice_data_jet_module           (const std::string& HeatID, const std::string& TreatID, const std::string& Plant, long PlantNo);

  //##ModelId=4200DE410214
  bool sequence_set_production_practice_data_recipe_ctrl          (const std::string& HeatID, const std::string& TreatID, const std::string& Plant, long PlantNo);

	//##ModelId=467645DC023E
  bool sequence_set_production_practice_ProcessPattern            (const std::string& HeatID, const std::string& TreatID);

  //##ModelId=4200DE4201C5
  bool sequence_set_production_practice_data_injection            (const std::string& HeatID, const std::string& TreatID, const std::string& Plant, long PlantNo);

	//##ModelId=467645DD0004
  bool sequence_set_production_practice_data_pattern_feeding      (const std::string& HeatID, const std::string& TreatID, const std::string& Plant);

	//##ModelId=467645DD01B3
  bool sequence_set_production_practice_data_bottom_stirring      (const std::string& HeatID, const std::string& TreatID, const std::string& Plant);

  //##ModelId=4200DE3F030B
  bool sequence_set_production_practice_data_manipulator_gas_lance(const std::string& HeatID, const std::string& TreatID, const std::string& Plant);

  // check if keys for practice data have changed, sets the corresponding attribute values,
  // and returns true incase the values have changed and practice data should be updated.
  // Priority code needed to consider differences betweeen planned and actual processing,
  // concerning number of baskets and hot metal -weight.
  // PriorityCode  -  0: undefined, 1 : basket data, 2 : hot metal data, to be set depending on context of event
  //
  //##ModelId=422EFFDF031F
  bool setkeysForPracticeDataIfChanged(const std::string& HeatID, const std::string& TreatID, const std::string& Plant, long PriorityCode =0, long NewLastBasketNo=CInv::InvalidLong);

  //>>
  bool doHandleEvent();

  bool doHndlHeatCanc();

  bool doIndicateHeatAnnouncement(const std::string& HeatId, const std::string& TreatNo = "01" , long ParamPracPt = 0);
  bool doIndicateBasketData();

  bool doIndicateChgTreatmentMode();

  bool doIndicateChgAimData();
  bool doIndicateChgProcPat();
  bool doIndicateChgProdPracElec();
  bool doIndicateChgHotHeelData();

  bool doIndicateChgProdPracBurner();
  bool doIndicateChgProdPracJetModule();       
  bool doIndicateChgProdPracRecipeCtrl();       
  bool doIndicateChgProdPracManipGasLance();     
  bool doIndicateChgProdPracBottomStirring();       

  bool doIndicateChgTapLdlData();

  bool checkIntfPtr(const CIntfEAF *pIntfEAF, const char * Function, const char * Action);

  // check if ModelRecipe is valid, e.g. "NoModel" might not be forwarded to model interface
  bool isValidModelRecipeName(const std::string& ModelRecipeName);

  // check whether it is a combi-recipe, which by definition does not have recipe sources.
  // a combi-recipe must have a Dollar-character as the first letter.
  bool isCombiRecipe(const std::string& ModelRecipeName);

  bool handleEquivalences(const std::string & HeatID, const std::string & TreatID, const std::string& Plant, seqAnalysis & SeqAnalysis);



  //##ModelId=4200E3840037
  CModelResults_Impl* m_pModelResults;

	//##ModelId=45EBDA3C025F
  CSMC_RecipeHandler *  m_pRecipeHandler;

  CGC_PhaseContainer*  m_pGC_PhaseContainer;

  //##ModelId=42C2CB1301CB
  CGT_MAT_PURP* m_pGT_MAT_PURP;

  CGT_MAT * m_pGT_MAT;

  //##ModelId=422EFFE00213
  CGC_PHASE* m_pGC_PHASE;
  //##ModelId=428DB4F90061
  CGC_COMBI_RECIPE_ENTRY *m_pGC_COMBI_RECIPE_ENTRY;

  //##ModelId=422EFFE0026D
  CGC_RESTRI_DEF* m_pGC_RESTRI_DEF; 

  //##ModelId=4200DE45017A
  CGC_RECIPE_SOURCE *m_pGC_RECIPE_SOURCE;
	//##ModelId=45EBDA3F024C
  CGC_RECIPE_L1* m_pGC_RECIPE_L1;

   //##ModelId=422EFFE00386
  CHD_RESTRI_ENTRY* m_pHD_RESTRI_ENTRY; 
  //##ModelId=428DB4F90179
  CHD_RESTRI* m_pHD_RESTRI; 

  //##ModelId=4200E4550035
  CPD_MAT_AVAIL *m_pPD_MAT_AVAIL;

  //##ModelId=422EFFE003E0
  CPP_HEAT* m_pPP_HEAT;

  //##ModelId=422EFFE1005C
  CPP_HEAT_PLANT* m_pPP_HEAT_PLANT;


  CHD_GRADE* m_pHD_GRADE;

  //##ModelId=422EFFE100B6
  CHD_GRADE_ANL* m_pHD_GRADE_ANL;
  CHD_GRADE_EQUIV*  m_pHD_GRADE_EQUIV;
  CGT_EQUIV*  m_pGT_EQUIV;

  CHD_TREATMODE* m_pHD_TREATMODE;
  CHD_TREATMODE_ENTRY* m_pHD_TREATMODE_ENTRY;
  CHD_GRADE_SINGLE_AIMS* m_pHD_GRADE_SINGLE_AIMS;
  CPP_ORDER_SINGLE_AIMS* m_pPP_ORDER_SINGLE_AIMS;


  //##ModelId=422EFFE1011A
  CPD_LADLE* m_pPD_LADLE;
  //##ModelId=422EFFE101D9
  CPD_HEAT_DATA_PRODPRAC* m_pPD_HEAT_DATA_PRODPRAC;
  //##ModelId=422EFFE1023D
  CPD_HEAT_DATA* m_pPD_HEAT_DATA;
  //##ModelId=422EFFE102A1
  CPD_HEAT_DATA_LIQADD* m_pPD_HEAT_DATA_LIQADD;
  //##ModelId=422EFFE10305
  CPD_HOTHEEL* m_pPD_HOTHEEL;

  CGT_TREATMODE_ENTRY* m_pGT_TREATMODE_ENTRY;

  CPD_SCRAP_CONTAINER_ENTRY* m_pPD_SCRAP_CONTAINER_ENTRY;

  CPD_SCRAP_CONTAINER_ORDER* m_pPD_SCRAP_CONTAINER_ORDER;
  CPD_SCRAP_CONTAINER_ORDER_ENTRY* m_pPD_SCRAP_CONTAINER_ORDER_ENTRY;
  CPD_SAMPLE_REF* m_pPD_SAMPLE_REF;
  CPD_PRETREATDATA* m_pPD_PRETREATDATA;
  CPD_SAMPLE* m_pPD_SAMPLE;
  CPD_SAMPLE_ENTRY* m_pPD_SAMPLE_ENTRY;

  CPD_RECIPE*       m_PD_RECIPE;
  CPD_RECIPE_ENTRY* m_PD_RECIPE_ENTRY;


  //##ModelId=422EFFE201E4
  CHDE_PP_BURNER_STEP_ENTRY* m_pHDE_PP_BURNER_STEP_ENTRY;
  //##ModelId=428DB4F902CE
  CHDE_PP_BURNER* m_pHDE_PP_BURNER;

  //##ModelId=422EFFE202BF
  CHDE_PP_INJECTION_STEP_ENTRY* m_pHDE_PP_INJECTION_STEP_ENTRY;
  //##ModelId=428DB4F903DC
  CHDE_PP_INJECTION* m_pHDE_PP_INJECTION;


	//##ModelId=467645DE01D4
  CGCE_INJECTION*      m_pGCE_INJECTION;
  CGCE_BURNER*               m_pGCE_BURNER;

 //##ModelId=429F0C9F02EF
  CGCE_INJECTION_TYPE*  m_pGCE_INJECTION_TYPE;


  //##ModelId=428DB4FA010D
  CHDE_PP_EL* m_pHDE_PP_EL;

  //##ModelId=422EFFE20393
  CHDE_PP_PROCESS_PARAM* m_pHDE_PP_PROCESS_PARAM;

  //##ModelId=422EFFE30087
  CHDE_PP_EL_STEP_ENTRY* m_pHDE_PP_EL_STEP_ENTRY;

  //##ModelId=422EFFE300F5
  CGCE_PROC_PHASE_CODES_EAF* m_pGCE_Proc_Phase_Codes_EAF;

  CHDE_PP_PROCESS* m_pHDE_PP_PROCESS;
	CHDE_PP_PROCESS_STEP_ENTRY* m_pHDE_PP_PROCESS_STEP_ENTRY;

  CHD_MAT_FEED* m_pHD_MAT_FEED;
  CHDE_PP_FLAME_PROFILE* m_pHDE_PP_FLAME_PROFILE;
  CGTE_PP_FLAME_PROFILE* m_pGTE_PP_FLAME_PROFILE;

	//##ModelId=45EBDA4000C4
  CHDE_PP_STIRR*            m_pHDE_PP_STIRR;        
	//##ModelId=45EBDA400112
  CHDE_PP_STIRR_SPEC*       m_pHDE_PP_STIRR_SPEC;  

	//##ModelId=467645DE0224
  CHDE_FLAME_PROFILE*              m_pHDE_FLAME_PROFILE;


private:

  // total number of baskets for heat (last available information - planned or actual)
  // Date is relevant for selection of production practice 
	//##ModelId=467645DA032B
  long m_NumberOfBasketsForHeat;

  // liquid weight / aim weight (last available information - planned or actual)
  // Date is relevant for selection of production practice 
	//##ModelId=467645DB0070
  double m_FractionOfLiquidMaterial;

	//##ModelId=467645D7029B
  void getNextLowerLiqAddAmountValue (long & LiqAddAmountMax, const long LiqAddAmountToCompare, const double  LiqAddAmountAct) const;

  // returns a warning if NewPhase does not match to used basket number
	//##ModelId=467645D8013E
  long focusOnPracticePhase   (string & LastFocusedPracPhase, const std::string & NewPracPhase, long PlannedNumberOfBaskets);

	//##ModelId=467645D8033C
  void logErrorProcessingData (long ProdPracPointer, const char* Text);

	//##ModelId=467645D900DB
  bool checkWetherLanceTypeIsInjection (const std::string& LANCENAME);

};

#endif /* _INC_CEAFMODELWRAPPER_4118CC3401F4_INCLUDED */