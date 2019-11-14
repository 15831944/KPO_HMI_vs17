// Copyright (C) 2004 SMS Demag AG

#include "reemodel.h"

#include "iEventMessages_s.hh"
#include "iDM_Interface_s.hh"
#include "iSMC_DataProvider_S.hh"
#include "iSMC_DataDefinitions_s.hh"

#include "cCBS_StdEventLogFrameController.h"
#include "CIntfData.h"
#include "CHMDModelTask.h"
#include "cCBS_StdInitBase.h"
#include "CSMC_EventLogFrameController.h"
#include "CSMC_RecipeHandler.h"
#include "DEF_GC_MEASUREMENT_TYPE.h"

#include "errorlog.h"


//##ModelId=41188F23003F
#include "CHMDTreatmentManagerDataWrapper.h"

const int hmdLogLevel = 2;

std::string WriteReeInput( const ReeInput& HMDInput, const std::string& filename);

long CHMDTreatmentManagerDataWrapper::getProdPrac( const CEventMessage& Event)
{
  long ProdPrac = DEF::Inv_Long;

  string SteelGradeCode = this->getSteelGradeCode( Event); // +++ see there
  if( SteelGradeCode == CSMC_DBData::unspecString || SteelGradeCode.empty()) return ProdPrac;

  std::string HeatID  = Event.getHeatID();
  std::string TreatID = Event.getTreatID();

  if( !m_pPD_HEAT_DATA_PRODPRAC) return ProdPrac;
  if ( m_pPD_HEAT_DATA_PRODPRAC->select(HeatID,TreatID,m_PlantName, "Parameter") ) // ++++ Check if "Parameter" is ok
  {
    if ( m_pPD_HEAT_DATA_PRODPRAC->isNull( "PRODPRACID_MOD", 1))
    {
      ProdPrac = m_pPD_HEAT_DATA_PRODPRAC->getPRODPRACID_PLAN(1);
    }
    else 
    {
      ProdPrac = m_pPD_HEAT_DATA_PRODPRAC->getPRODPRACID_MOD(1);
    }
  }
  return ProdPrac;
}

string CHMDTreatmentManagerDataWrapper::getSteelGradeCode( const CEventMessage& Event) // +++ like RH?
{
  std::string HeatID  = Event.getHeatID();
  std::string TreatID = Event.getTreatID();

  std::string SteelGradeCode = DEF::Inv_String;
  if( !m_pPDH_HM_DATA) return "";
  if( m_pPDH_HM_DATA->select( HeatID, TreatID, m_PlantName)) // only 1 row can be selected
  {
    if( m_pPDH_HM_DATA->isNull("STEELGRADECODE_ACT", 1)) 
    {
      SteelGradeCode = m_pPDH_HM_DATA->getSTEELGRADECODE_PLAN(1);
    }
    else         
    {
      SteelGradeCode = m_pPDH_HM_DATA->getSTEELGRADECODE_ACT(1);      
    }
  }
  return SteelGradeCode;
}


//##ModelId=41188F23003F
bool CHMDTreatmentManagerDataWrapper::doOnStartOfHeat( CEventMessage &Event )
// HMD_EvMsg::evHMDStartHeat = "HMD_START_HEAT"
{
  bool RetValue = false;
  return RetValue;
}


//##ModelId=41188F4C02C9
bool CHMDTreatmentManagerDataWrapper::doOnHeatDeparture( CEventMessage &Event )
// HMD_EvMsg::evHMDHeatDeparture = "HMD_HEAT_DEPARTURE"
{
  bool RetValue = false;
  return RetValue;
}


//##ModelId=41188F6802E7
bool CHMDTreatmentManagerDataWrapper::doOnHeatCancel( CEventMessage &Event )
// HMD_EvMsg::evHMDHeatCancle = "HMD_HEAT_CANCEL"
{
  bool RetValue = false;
  return RetValue;
}

void CHMDTreatmentManagerDataWrapper::setComputerMode( const std::string& dataKey, CORBA::Long status)
{
  // DEF_MAT_HANDLE_STATUS::Available
  // DEF_MAT_HANDLE_STATUS::NotAvailable

  seqComputerModes pseqComputerMode;
  sComputerMode    theComputerMode;

  theComputerMode.Device = DEF_COMP_MODES::MatHandleModel;
  theComputerMode.Status = status;  
  CIntfData::insert(pseqComputerMode, theComputerMode);

  //theComputerMode.Device = DEF_COMP_MODES::BlowingModel;
  //theComputerMode.Status = status;  
  //CIntfData::insert(pseqComputerMode, theComputerMode);

  CModelResults_Impl* pModelResults =  m_pModelTask->getpModelResults();

  pModelResults->setComputerModes( dataKey.c_str(), DATA::ComputerModeAvail, pseqComputerMode);
}

// convert something to string
template <typename T>
inline std::string ToStr( T i, int w = 0)
{
	std::ostringstream os;
	os.width( static_cast<std::streamsize>( w));
	os << i;
	return os.str();
}

// convert something from string
template <typename T>
inline T FromStr( const std::string& in)
{
	std::istringstream is;
    is.str( in);
	T out;
	is >> out;
	return out;
}

//##ModelId=41188F7E002C
bool CHMDTreatmentManagerDataWrapper::doOnHandleHeatAnnouncement( CEventMessage& Event, double sulph, bool use_AIM_S_OPER)
// evHMDHeatAnnouncement = "HMD_HEAT_ANNOUNCEMENT";
{
  bool RetValue = true;

  if (!m_pConnection)
  {
    handleDBConnectionError();
    if (!m_pConnection) return false;
  }

  //MHMDModel *pMHMDModel = CHMDModelTask::getInstance()->getpModel();
  //if( pMHMDModel == NULL) return false;

  std::string HeatID  = Event.getHeatID();  // test 1234567
  std::string TreatID = Event.getTreatID(); // test 123
  std::string PlantID = Event.getPlantID();

  long ProdPrac = this->getProdPrac( Event); // "Parameter"

  // MODEL INPUT
	//****************
	
	//typedef struct _ReeInput{
	//	StartConditionsTyp Strt;
	//	BaseValueTableTyp Bvt;
	//	MaterialTyp Mat[3];
	//	PatternTyp Pat[3];
	//	float dur[7];
	//	float dAvgDur;
	//	float dCorrmono;//HDH_PP_PARA.CORR_FACT_MONO_INJ
	//	FreeboardTyp Freebd;
	//	CarbCorrSlagTyp CCorrSlag;
	//	CarbMono3Typ CMono3;
	//	SlagDurTyp SlgDur;
	//	TempCorrMgTyp TCorrMg;
	//	TempCorrCarbTyp TCorrCarb;
	//	float dTempLoss;//HDH_PP_TEMP_CORR
	//	float dPrevAdd[3];
	//	MonoCorrTyp MonoCorrLime;
	//	MonoCorrTyp MonoCorrCarbide;
  //  int iBVT_ROWS;
	//	//float FeLoss; //HDH_PP_PARA.CORR_FACT_FE_LOSS
	//}ReeInput;

  ReeInput  HMDInput; // global input structure (to be filled)

  // clean structure
  memset( &HMDInput, 0, sizeof(HMDInput));

  for( long a=0; a<3; ++a)
    HMDInput.dPrevAdd[a] = 0.0;

  if( !m_pHDH_PARAM) return false;
  if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"AveragePreparationDuration"))
  {
    HMDInput.dAvgDur = FromStr< double>( m_pHDH_PARAM->getVALUE(1));
  }
  else
    handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement: no AveragePreparationDuration in HD_PARAM");

  //typedef struct _StartConditionsTyp{
  //  float dAmt_iron;	
  //  float dAmt_slag;
  //  float dAim_sulphur;
  //  float dFreeboard;//PDH_HEAT_DATA.LADLE_FREEBOARD (wenn undefiniert oder 0: aus _BF)
  //  float dTemp_iron;
  //  float dCont_sulphur;
  //  int    bAvail_carbide;
  //  int    bAvail_lime;
  //  int    bAvail_mg;
  //  float dTimeAvail;
  //  float dAmt_soda;
  //  int   bPriceOptimum;
  //}StartConditionsTyp;
  

  StartConditionsTyp& StartConditions = HMDInput.Strt;

  double aimSOper = -1.0;

  if( !m_pPDH_HM_DATA) return false;
  if( m_pPDH_HM_DATA->select(  HeatID, TreatID,m_PlantName))
  {
    int calcMode = m_pPDH_HM_DATA->getCALC_MODE( 1);
    StartConditions.bPriceOptimum = (calcMode == 1); // 0 Standard, 1 Cost, 2 time

    StartConditions.dFreeboard = m_pPDH_HM_DATA->getLADLE_FREEBOARD_BF( 1);
    StartConditions.dAmt_soda = 0.0; // +++ ANKU

    // StartConditions.dTimeAvail
    if( !m_pPDH_HM_DATA->select( HeatID, TreatID, m_PlantName)) return false;
    CDateTime now; // +++ automatic actual time? (see CRHModelTask.cpp as well)
    CDateTime EndTime;
    if ( m_pPDH_HM_DATA->isNull( "TREATEND_MOD", 1))
    {
      EndTime   = m_pPDH_HM_DATA->getTREATEND_PLAN(1);
    }
    else 
    {
      EndTime = m_pPDH_HM_DATA->getTREATEND_MOD(1); 
    }
    CDeltaTime Diff = CDateTime::subTimes( EndTime, now); // +++

    StartConditions.dTimeAvail = Diff.asSeconds() / 60; // +++ unit?

	if( use_AIM_S_OPER)
	{
		if( !m_pPDH_HM_DATA->isNull( "AIM_S_OPER", 1))
			aimSOper = m_pPDH_HM_DATA->getAIM_S_OPER( 1);
		else
		    handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement: no data in PDH_HEAT_DATA.AIM_S_OPER");
	}
  }
  else
    handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement: no data in PD_HEATDATA");


  StartConditions.bAvail_carbide = false;
  StartConditions.bAvail_lime = false;
  StartConditions.bAvail_mg = false;
  StartConditions.dAvail_carbide = -1.0;
  StartConditions.dAvail_lime = -1.0;
  StartConditions.dAvail_mg = -1.0;

  string LCMCode[ 3];  // LimeCarbideMagnesiumCode

  //if( !m_pGT_MAT_AVAIL) return false;
  if( !m_pGT_MAT_PURP) return false;
//  if( !m_pPD_BIN)return false;
//*********** Test Dipesh**********//
  if(sulph > 0)
	StartConditions.dCont_sulphur = sulph * 10000.0;
  else 
/*
m_pPD_HOT_METAL;
m_pPD_SAMPLE_REF;
m_pPD_SAMPLE_ENTRY;
*/



  {
	  /*
To obtain start Sulphur content:
		With HM_ID search PDH_HM_DATA.HOTMETAL_COUNTER
		With HOTMETAL_COUNTER search PD_HOT_METAL.SAMPLE_REF
		With SAMPLE_REF search PD_SAMPLE_REF.HOT_METAL
		With HOT_METAL=SAMPLE_COUNTER search PD_SAMPLE_ENTRY.MEASVALUE where MEASNAME=’S’
*/
 
	  if( m_pPDH_HM_DATA->select(HeatID, TreatID, m_PlantName)) 
	{
		if (m_pPD_HOT_METAL->select(m_pPDH_HM_DATA->getHOTMETAL_COUNTER(1))){
			if (m_pPD_SAMPLE_REF->select(m_pPD_HOT_METAL->getSAMPLE_REF(1))){
				if(m_pPD_SAMPLE_ENTRY->select(m_pPD_SAMPLE_REF->getHOT_METAL(1),"S")){
					StartConditions.dCont_sulphur = m_pPD_SAMPLE_ENTRY->getMEASVALUE( 1) * 10000.0; // % -> ppm
				}
				else {
					handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement/SAMPLE_ENTRY: no act [S]");
				}
			}
			else {
				handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement/SAMPLE_REF: no act [S]");
			}
		}
		else {
			handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement/HOT_METAL(HOTMETAL_COUNTER): no act [S]");
		}

	}
	else {
		handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement/HM_DATA: no act [S]");
	}	
  }
// get amounts blown so far anku
#define CONSIDERBLOWNAMTS
#ifdef CONSIDERBLOWNAMTS
	
	//if ( m_pPDH_CYCL_MEAS_DATA->selectOrderByRevTimeDesc(HeatID,TreatID,"HMD",CSMC_DBData::unspecDate))
	if ( m_pPDH_CYCL_MEAS_DATA->select_totalconsumedCac2MG(HeatID,TreatID,"HMD"))
  {

		HMDInput.dPrevAdd[LIME]=m_pPDH_CYCL_MEAS_DATA->getCONS_LIME( 1);
		HMDInput.dPrevAdd[CARBIDE]=m_pPDH_CYCL_MEAS_DATA->getCONS_CARBIDE( 1);
		HMDInput.dPrevAdd[MAGNESIUM]=m_pPDH_CYCL_MEAS_DATA->getCONS_MG( 1);

		HMDInput.dActFlow[LIME]			=m_pPDH_CYCL_MEAS_DATA->getFLOW_LIME( 1);
		HMDInput.dActFlow[CARBIDE]		=m_pPDH_CYCL_MEAS_DATA->getFLOW_CARBIDE( 1);
		HMDInput.dActFlow[MAGNESIUM]	=m_pPDH_CYCL_MEAS_DATA->getFLOW_MG( 1);

		HMDInput.dActLancePos			=m_pPDH_CYCL_MEAS_DATA->getLANCEPOS( 1);
  }
#else
		HMDInput.dPrevAdd[LIME]			=
		HMDInput.dPrevAdd[CARBIDE]		=
		HMDInput.dPrevAdd[MAGNESIUM]	=

		HMDInput.dActFlow[LIME]			=
		HMDInput.dActFlow[CARBIDE]		=
		HMDInput.dActFlow[MAGNESIUM]	=

		HMDInput.dActLancePos			=0.;
#endif



//**********END*******************//
  if( m_pGT_MAT->selectAvailable( CSMC_DBData::unspecString))
  {
    for( long i=1; i<=m_pGT_MAT->getLastRow(); ++i)
    {
      string matCode = m_pGT_MAT->getMAT_CODE( i);

	  double avlamt= -1.0;
/* kein bin???	 
	  if(m_pPD_BIN->select(matCode, m_PlantNo, "HMD", CSMC_DBData::unspecString))
	  {
		 avlamt=m_pPD_BIN->getBINAVAILWGT(1);
	  }
*/
      if( matCode == "")
          continue;

      // select(const string& MAT_CODE, const string& PURP_CODE, const string& PLANT, long PLANTNO)
      if( m_pGT_MAT_PURP->selectByPlant(  m_PlantName, m_PlantNo, matCode, "Carbide")) // ++++ Add purposecode
      {
        StartConditions.bAvail_carbide = true;
		StartConditions.dAvail_carbide=avlamt;

        LCMCode[ CARBIDE] = matCode;
      }
      if( m_pGT_MAT_PURP->selectByPlant(  m_PlantName, m_PlantNo, matCode, "Magnesium")) // ++++ Add purposecode
      {
        StartConditions.bAvail_mg = true;
        StartConditions.dAvail_mg=avlamt;

        LCMCode[ MAGNESIUM] = matCode;
      }
      if( m_pGT_MAT_PURP->selectByPlant(  m_PlantName, m_PlantNo, matCode, "Lime")) // ++++ Add purposecode
      {
        StartConditions.bAvail_lime = true;
		StartConditions.dAvail_lime=avlamt;

        LCMCode[ LIME] = matCode;
      }
      if( StartConditions.bAvail_carbide && 
        StartConditions.bAvail_mg &&
        StartConditions.bAvail_lime)
        break;
    }
  }
  if( !StartConditions.bAvail_carbide && 
    !StartConditions.bAvail_mg &&
    !StartConditions.bAvail_lime)
    handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement: no Carbide, Magnesium or Lime material available (purpose code not set?)");
    

  if( !m_pPDH_HM_DATA) return false;
  if( m_pPDH_HM_DATA->select( HeatID, TreatID, m_PlantName)){
    StartConditions.dAmt_iron	 = m_pPDH_HM_DATA->getHM_WEIGHT_START(1);
    StartConditions.dAmt_slag  = m_pPDH_HM_DATA->getSLAG_WEIGHT_START(1);
    StartConditions.dTemp_iron = m_pPDH_HM_DATA->getHM_TEMP_START(1);

//Alternatively start temperature :
	if (m_pPD_HOT_METAL->select(m_pPDH_HM_DATA->getHOTMETAL_COUNTER(1))){



   //if (m_pPD_SAMPLE_REF->selectbySteelTemp(m_pPD_HOT_METAL->getSAMPLE_REF(1))) //key for temperature
	 //{  
   //		if(m_pPD_SAMPLE_ENTRY->select(m_pPD_SAMPLE_REF->getHOT_METAL(1),"Temp"))
		//	{
		//			StartConditions.dTemp_iron= m_pPD_SAMPLE_ENTRY->getMEASVALUE( 1) * 10000.0; // % -> ppm
		//	}
		//	else 
		//	{
		//		handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement/SAMPLE_ENTRY No Start Temp");
		//	}
		//}
		//else 
		//{
		//		handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement/SAMPLE_REF: No Start Temp");
		//}


			if(m_pPD_SAMPLE_ENTRY->select(m_pPD_SAMPLE_REF->getSampleCounter(m_pPD_HOT_METAL->getSAMPLE_REF(1),DEF_GC_MEASUREMENT_TYPE::Temp ),"Temp"))
			{
					//StartConditions.dTemp_iron= m_pPD_SAMPLE_ENTRY->getMEASVALUE( 1) * 10000.0; // % -> ppm
					StartConditions.dTemp_iron= m_pPD_SAMPLE_ENTRY->getMEASVALUE( 1) ; // sankar
			}
			else 
			{
				handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement/SAMPLE_ENTRY No Start Temp");
			}


	}
	else {
			handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement/HOT_METAL(HOTMETAL_COUNTER):No Start Temp");
	}
  }

  else {
		handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement/HM_DATA: No Start Temp");
  }	

  // StartConditions.dCont_sulphur
  //if( !m_pPD_HEATDATA_LIQADD_ANL) return false;
  
 // if(sulph > 0)
	//StartConditions.dCont_sulphur = sulph * 10000.0;
 // else 
 // {
	//if( m_pPD_HEATDATA_LIQADD_ANL->select( CSMC_DBData::unspecLong, TreatID, HeatID, "S", m_PlantName)) // +++ 1st param liqAddNo?
	//{
	//	StartConditions.dCont_sulphur = m_pPD_HEATDATA_LIQADD_ANL->getANL( 1) * 10000.0; // % -> ppm
	//}
	//else
	//	handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement: no act [S]");
 // }
  string SteelGradeCode = getSteelGradeCode( Event);

  // StartConditions.dAim_sulphur
  if( aimSOper > 0. && aimSOper < 0.1)
  {
	  StartConditions.dAim_sulphur = aimSOper * 10000.0; // % -> ppm ;
  }
  else
  {
	  /*
	  if( !m_pHDH_GRADE_ANL) return false;
	  if( m_pHDH_GRADE_ANL->select( HeatID, TreatID, m_PlantName, SteelGradeCode,"S", "Aim"))
	  {
		  StartConditions.dAim_sulphur = m_pHDH_GRADE_ANL->getANL( 1) * 10000.0; // % -> ppm ;
	  }*/
		if( !m_pPDH_HM_DATA) return "";
		if( m_pPDH_HM_DATA->select( HeatID, TreatID, m_PlantName)){ 
			StartConditions.dAim_sulphur = m_pPDH_HM_DATA->getAIM_S_OPER( 1) * 10000.0; // % -> ppm ;
		}
		else
			handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement: no aim [S]");
  }

	//typedef struct _BaseValueTableTyp{// HDH_PP_BASE_VAL (_STEP)
	//	float  BlowingRelation; //HDH_PP_BASE_VAL
	//	float	MgContent;//HDH_PP_BASE_VAL
	//	float	CaC2Content;//HDH_PP_BASE_VAL
	//	float	Mg[BVT_ROWS][BVT_COLUMNS];//HDH_PP_BASE_VAL_STEP
	//	float  SStart[BVT_ROWS];//HDH_PP_BASE_VAL_STEP
	//	float  SFinal[BVT_COLUMNS];//HDH_PP_BASE_VAL
	//}BaseValueTableTyp;
  BaseValueTableTyp& BaseValueTable = HMDInput.Bvt;
  if( !m_pHDH_PP_BASE_VAL) return false;
  if( !m_pHDH_PP_BASE_VAL_STEP) return false;
  //if( m_pHDH_PP_BASE_VAL->selectByPracno(0,ProdPrac))
  if( m_pHDH_PP_BASE_VAL->select(HeatID, TreatID, m_PlantName))
  {
    BaseValueTable.BlowingRelation = m_pHDH_PP_BASE_VAL->getBLOW_RELATION( 1);
    BaseValueTable.MgContent = m_pHDH_PP_BASE_VAL->getMG_CONTENT( 1);
    BaseValueTable.CaC2Content = m_pHDH_PP_BASE_VAL->getCAF2_CONTENT( 1); // +++
    BaseValueTable.SFinal[ 0] = m_pHDH_PP_BASE_VAL->getS_AIM_1( 1);
    BaseValueTable.SFinal[ 1] = m_pHDH_PP_BASE_VAL->getS_AIM_2( 1);
    BaseValueTable.SFinal[ 2] = m_pHDH_PP_BASE_VAL->getS_AIM_3( 1);
    BaseValueTable.SFinal[ 3] = m_pHDH_PP_BASE_VAL->getS_AIM_4( 1);
    BaseValueTable.SFinal[ 4] = m_pHDH_PP_BASE_VAL->getS_AIM_5( 1);
  }
  else
    handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement: no data in HDH_PP_BASE_VAL");

  HMDInput.iBVT_ROWS = BVT_ROWS;
  for( long s=1; s<=BVT_ROWS; ++s)
  {
    if( m_pHDH_PP_BASE_VAL_STEP->select( HeatID, TreatID, m_PlantName, ProdPrac,  s))
    {
      BaseValueTable.SStart[ s-1] = m_pHDH_PP_BASE_VAL_STEP->getS_START( 1);

      BaseValueTable.Mg[s-1][0]   = m_pHDH_PP_BASE_VAL_STEP->getS_STEP_1( 1); // +++
      BaseValueTable.Mg[s-1][1]   = m_pHDH_PP_BASE_VAL_STEP->getS_STEP_2( 1);
      BaseValueTable.Mg[s-1][2]   = m_pHDH_PP_BASE_VAL_STEP->getS_STEP_3( 1);
      BaseValueTable.Mg[s-1][3]   = m_pHDH_PP_BASE_VAL_STEP->getS_STEP_4( 1);
      BaseValueTable.Mg[s-1][4]   = m_pHDH_PP_BASE_VAL_STEP->getS_STEP_5( 1);
    }
    else
      handleError("CHMDTreatmentManagerDataWrapper", ("doOnHandleHeatAnnouncement: no data in HDH_PP_BASE_VAL_STEP. Step: " + ToStr(s)).c_str());
  }

  //typedef struct _FreeboardTyp{
  //  float Fbrd[2];//HDH_PP_PARA.MGFREEB_RATE_FREEB_1 _2
  //  float MgRate[2];//HDH_PP_PARA.MGFREEB_RATE_
  //}FreeboardTyp;
  // typedef struct _CarbCorrSlagTyp{//HDH_PP_PARA.CORR_MONO1... 
  //	float Slag[4];
  //	float Corr[4];
  //   }CarbCorrSlagTyp;
  // typedef struct _CarbMono3Typ{//HDH_PP_PARA.CALC_MONO2...
  //	float Mg[5];
  //	float Carbide[5];
  //}CarbMono3Typ;
  // typedef struct _SlagDurTyp{//HDH_PP_PARA.DESL_RELATION_SLAG_WGT... und ...RELATION_DESL_DUR...
  //	float Slag[5];
  //	float Duration[5];
  //}SlagDurTyp;
	//typedef struct _MonoCorrTyp{ //HDH_PP_PARA.CORR_FACT_MONO_LIME_S_END ...MONO_LIME_CORR
	//	float dSend[4];
	//	float dCorr[4];
	//}MonoCorrTyp;
  //if( !m_pHDH_PP_PARA) return false;
  if( !m_pHDH_PARAM) return false;
  FreeboardTyp& Freeboard = HMDInput.Freebd;
  CarbCorrSlagTyp& CarbCorrSlag = HMDInput.CCorrSlag;
  CarbMono3Typ& CarbMono3 = HMDInput.CMono3;
  SlagDurTyp& SlagDur = HMDInput.SlgDur;
  MonoCorrTyp& MonoCorrLime = HMDInput.MonoCorrLime;
  MonoCorrTyp& MonoCorrCarbide = HMDInput.MonoCorrCarbide;

  double MgEquivLime;
  double MgEquivCarbide;

    /*Muster*/



	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"MG_EQUIV_LIME"))	MgEquivLime = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));       // save for later use


	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"MG_EQUIV_LIME"))	MgEquivLime = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));       // save for later use
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"MG_EQUIV_CARBIDE"))    MgEquivCarbide = FromStr< double>( m_pHDH_PARAM->getVALUE( 1)); // save for later use

	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_FACT_MONO_INJ"))    HMDInput.dCorrmono = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));

	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"MGFREEB_RATE_FREEB_1"))    Freeboard.Fbrd[ 0] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"MGFREEB_RATE_FREEB_2"))    Freeboard.Fbrd[ 1] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"MGFREEB_RATE_MG_1"))    Freeboard.MgRate[ 0] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"MGFREEB_RATE_MG_2"))    Freeboard.MgRate[ 1] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));

	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_MONO1_SLAG_WGT_1"))    CarbCorrSlag.Slag[ 0] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_MONO1_SLAG_WGT_2"))    CarbCorrSlag.Slag[ 1] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_MONO1_SLAG_WGT_3"))    CarbCorrSlag.Slag[ 2] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_MONO1_SLAG_WGT_4"))    CarbCorrSlag.Slag[ 3] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_MONO1_FACT_1"))    CarbCorrSlag.Corr[ 0] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_MONO1_FACT_2"))    CarbCorrSlag.Corr[ 1] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_MONO1_FACT_3"))    CarbCorrSlag.Corr[ 2] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_MONO1_FACT_4"))    CarbCorrSlag.Corr[ 3] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));

	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CALC_MONO2_MG_1"))    CarbMono3.Mg[ 0] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CALC_MONO2_MG_2"))    CarbMono3.Mg[ 1] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CALC_MONO2_MG_3"))    CarbMono3.Mg[ 2] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CALC_MONO2_MG_4"))    CarbMono3.Mg[ 3] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CALC_MONO2_MG_5"))    CarbMono3.Mg[ 4] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CALC_MONO2_CARB_1"))    CarbMono3.Carbide[ 0] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CALC_MONO2_CARB_2"))    CarbMono3.Carbide[ 1] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CALC_MONO2_CARB_3"))    CarbMono3.Carbide[ 2] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CALC_MONO2_CARB_4"))    CarbMono3.Carbide[ 3] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CALC_MONO2_CARB_5"))    CarbMono3.Carbide[ 4] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));

	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"DESL_RELATION_SLAG_WGT_1"))    SlagDur.Slag[ 0] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"DESL_RELATION_SLAG_WGT_2"))    SlagDur.Slag[ 1] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"DESL_RELATION_SLAG_WGT_3"))    SlagDur.Slag[ 2] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"DESL_RELATION_SLAG_WGT_4"))    SlagDur.Slag[ 3] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"DESL_RELATION_SLAG_WGT_5"))    SlagDur.Slag[ 4] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"DESL_RELATION_DESL_DUR_1"))    SlagDur.Duration[ 0] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"DESL_RELATION_DESL_DUR_2"))    SlagDur.Duration[ 1] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"DESL_RELATION_DESL_DUR_3"))    SlagDur.Duration[ 2] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"DESL_RELATION_DESL_DUR_4"))    SlagDur.Duration[ 3] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"DESL_RELATION_DESL_DUR_5"))    SlagDur.Duration[ 4] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));

	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_FACT_MONO_LIME_S_END_1"))    MonoCorrLime.dSend[ 0] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_FACT_MONO_LIME_S_END_2"))    MonoCorrLime.dSend[ 1] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_FACT_MONO_LIME_S_END_3"))    MonoCorrLime.dSend[ 2] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_FACT_MONO_LIME_S_END_4"))    MonoCorrLime.dSend[ 3] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_FACT_MONO_LIME_CORR_1"))    MonoCorrLime.dCorr[ 0] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_FACT_MONO_LIME_CORR_2"))    MonoCorrLime.dCorr[ 1] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_FACT_MONO_LIME_CORR_3"))    MonoCorrLime.dCorr[ 2] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_FACT_MONO_LIME_CORR_4"))    MonoCorrLime.dCorr[ 3] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));

	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_FACT_MONO_CARB_S_END_1"))    MonoCorrCarbide.dSend[ 0] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1)); // +++ add to DB
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_FACT_MONO_CARB_S_END_2"))    MonoCorrCarbide.dSend[ 1] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_FACT_MONO_CARB_S_END_3"))    MonoCorrCarbide.dSend[ 2] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_FACT_MONO_CARB_S_END_4"))    MonoCorrCarbide.dSend[ 3] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_FACT_MONO_CARB_CORR_1"))    MonoCorrCarbide.dCorr[ 0] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1)); // +++ add to DB
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_FACT_MONO_CARB_CORR_2"))    MonoCorrCarbide.dCorr[ 1] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_FACT_MONO_CARB_CORR_3"))    MonoCorrCarbide.dCorr[ 2] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
	if( m_pHDH_PARAM->select( HeatID, TreatID, m_PlantName, CSMC_DBData::unspecLong,  ProdPrac,"CORR_FACT_MONO_CARB_CORR_4"))    MonoCorrCarbide.dCorr[ 3] = FromStr< double>( m_pHDH_PARAM->getVALUE( 1));
 // else
 //     handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement: no data in HDH_PP_PARA");

	  //typedef struct _MaterialTyp{//GT_MAT
  //	float TempCoeff;//aus ENTHALPY and SPEC_HEAT
  //	float Price;// PRICE
  //	float MgEqui;//MG_EQUIVALENT
  //	float CaOCont;//GT_MAT_CHEM
  //	float CaC2Cont;//GT_MAT_CHEM
  //	float CCont;//GT_MAT_CHEM
  //	float MgCont;//GT_MAT_CHEM
  //	float AddRateMin;//HDH_PP_INJECTION über Purpose code GT_MAT_PURP 'Lime', 'Carbide', 'Magnesium' -purposes
  //	float AddRateStd;//HDH_PP_INJECTION 
  //	float AddRateMax;//HDH_PP_INJECTION 
  //	float AddRateMinMono;//HDH_PP_INJECTION 
  //	float AddRateStdMono;//HDH_PP_INJECTION 
  //	float AddRateMaxMono;//HDH_PP_INJECTION 
  //}MaterialTyp;
  if( !m_pGT_MAT) return false;
  if( !m_pGT_MAT_PURP) return false;
  if( !m_pGT_MAT_CHEM) return false;
  if( !m_pHDH_PP_INJECTION) return false;
  for( long m=0; m<3; ++m)
  {
    string matCode;
    if( m == LIME) matCode = LCMCode[ LIME]; 
    else if( m == CARBIDE) matCode = LCMCode[ CARBIDE]; 
    else if( m == MAGNESIUM) matCode = LCMCode[ MAGNESIUM]; 



    MaterialTyp& Material = HMDInput.Mat[ m]; // Mat[ 3] +++
	//Material.AddRateMin = 0;
	//Material.AddRateStd = 0;
	//Material.AddRateMax = 0;
	//Material.AddRateMinMono = 0;
	//Material.AddRateStdMono = 0;
	//Material.AddRateMaxMono = 0;

	if (matCode.length()>0){
		if( m_pGT_MAT->select( matCode)) // +++ matCode
		{
		  Material.TempCoeff = m_pGT_MAT->getENTHALPY( 1) / m_pGT_MAT->getSPEC_HEAT( 1) /* ???-> */ / 1000.0; // +++ formula
		  Material.Price = m_pGT_MAT->getPRICE( 1);
		  if( matCode == LCMCode[ LIME])
			Material.MgEqui = MgEquivLime;
		  else if( matCode == LCMCode[ CARBIDE])
			Material.MgEqui = MgEquivCarbide;
		  else // Magnesium
			Material.MgEqui = 1.0;
		  //Material.MgEqui = m_pGT_MAT->getMG_EQUIVALENT( 1);
		}
		if( m_pGT_MAT_CHEM->select( matCode, "CaO" )) // +++ matCode 
		{
		  Material.CaOCont = m_pGT_MAT_CHEM->getVALUE( 1); // [%]
		}
		if( m_pGT_MAT_CHEM->select( matCode, "CaC2" )) // +++ matCode
		{
		  Material.CaC2Cont = m_pGT_MAT_CHEM->getVALUE( 1);
		}
		if( m_pGT_MAT_CHEM->select( matCode, "C" )) // +++ matCode
		{
		  Material.CCont = m_pGT_MAT_CHEM->getVALUE( 1);
		}
		if( m_pGT_MAT_CHEM->select( matCode, "Mg" )) // +++ matCode
		{
		  Material.MgCont = m_pGT_MAT_CHEM->getVALUE( 1);
		}
	}
	else {
		    if( m == LIME) handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement: no data GT_MAT / LIME"); 
			else if( m == CARBIDE) handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement: no data GT_MAT / CARBIDE "); 
			else if( m == MAGNESIUM) handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement: no data GT_MAT / MAGNESIUM"); 

		
        
	}
    //if( m_pGT_MAT_PURP->select( matCode, 'Lime', m_PlantName, m_PlantNo) // +++
    if( m == LIME)
    {
      if( m_pHDH_PP_INJECTION->select( HeatID, TreatID,m_PlantName, ProdPrac))
      {
        Material.AddRateMin = m_pHDH_PP_INJECTION->getCO_INJ_LIME_MIN( 1);
        Material.AddRateStd = m_pHDH_PP_INJECTION->getCO_INJ_LIME_AIM( 1);
        Material.AddRateMax = m_pHDH_PP_INJECTION->getCO_INJ_LIME_MAX( 1);
        Material.AddRateMinMono = m_pHDH_PP_INJECTION->getMONO_INJ_LIME_MIN( 1);
        Material.AddRateStdMono = m_pHDH_PP_INJECTION->getMONO_INJ_LIME_AIM( 1);
        Material.AddRateMaxMono = m_pHDH_PP_INJECTION->getMONO_INJ_LIME_MAX( 1);
      }
      else
        handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement: no data in HDH_PP_INJECTION lime");
    }
    //if( m_pGT_MAT_PURP->select( matCode, 'Carbide', m_PlantName, m_PlantNo) // +++
    if( m == CARBIDE)
    {
      if( m_pHDH_PP_INJECTION->select( HeatID, TreatID, m_PlantName, ProdPrac))
      {
        Material.AddRateMin = m_pHDH_PP_INJECTION->getCO_INJ_CARBIDE_MIN( 1);
        Material.AddRateStd = m_pHDH_PP_INJECTION->getCO_INJ_CARBIDE_AIM( 1);
        Material.AddRateMax = m_pHDH_PP_INJECTION->getCO_INJ_CARBIDE_MAX( 1);
        Material.AddRateMinMono = m_pHDH_PP_INJECTION->getMONO_INJ_CARBIDE_MIN( 1);
        Material.AddRateStdMono = m_pHDH_PP_INJECTION->getMONO_INJ_CARBIDE_AIM( 1);
        Material.AddRateMaxMono = m_pHDH_PP_INJECTION->getMONO_INJ_CARBIDE_MAX( 1);
      }
      else
        handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement: no data in HDH_PP_INJECTION carbide");
    }
    //if( m_pGT_MAT_PURP->select( matCode, 'Magnesium', m_PlantName, m_PlantNo) // +++
    if( m == MAGNESIUM)
    {
      if( m_pHDH_PP_INJECTION->select( HeatID, TreatID,m_PlantName,ProdPrac ))
      {
        Material.AddRateMin = m_pHDH_PP_INJECTION->getCO_INJ_MG_MIN( 1);
        Material.AddRateStd = m_pHDH_PP_INJECTION->getCO_INJ_MG_AIM( 1);
        Material.AddRateMax = m_pHDH_PP_INJECTION->getCO_INJ_MG_MAX( 1);

        // +++ add column to DB
        //Material.AddRateMinMono = m_pHDH_PP_INJECTION->getMONO_INJ_MG_MIN( 1);
        //Material.AddRateStdMono = m_pHDH_PP_INJECTION->getMONO_INJ_MG_AIM( 1);
        //Material.AddRateMaxMono = m_pHDH_PP_INJECTION->getMONO_INJ_MG_MAX( 1);
      }
      else
        handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement: no data in HDH_PP_INJECTION magnesium");
    }
  }
  //typedef struct _PatternTyp{//HDH_PP_BLOWING
  //  float CoRel;
  //  float FixedLime;
  //  float FixedCarbide;
  //  float MinLime;
  //  float MinCarbide;
  //  float MinMagnesia;
  //}PatternTyp;
  //	PatternTyp Pat[3];
  if( !m_pHDH_PP_BLOWING) return false;
  if( m_pHDH_PP_BLOWING->select( HeatID, TreatID, m_PlantName, ProdPrac ))
  {
    for( long p=0; p<5; ++p)
    {
      PatternTyp& Pattern = HMDInput.Pat[ p];

	  //Pattern.CoRel =        0;
	  //Pattern.FixedLime =    0;
	  //Pattern.FixedCarbide = 0;
	  //Pattern.MinLime =      0;
	  //Pattern.MinCarbide =   0;
	  //Pattern.MinMagnesium = 0;

	if( p == CO_LIME)
      {
        Pattern.CoRel =        m_pHDH_PP_BLOWING->getCO_LIME_STD_REL( 1);
        Pattern.FixedLime =    m_pHDH_PP_BLOWING->getCO_LIME_FIX_LIME( 1);
        Pattern.FixedCarbide = m_pHDH_PP_BLOWING->getCO_LIME_FIX_CARBIDE( 1);
        Pattern.MinLime =      m_pHDH_PP_BLOWING->getCO_LIME_MIN_LIME( 1);
        Pattern.MinCarbide =   m_pHDH_PP_BLOWING->getCO_LIME_MIN_CARBIDE( 1);
        Pattern.MinMagnesium =  m_pHDH_PP_BLOWING->getCO_LIME_MIN_MG( 1);
      }
      if( p == CO_CARBIDE)
      {
        Pattern.CoRel =        m_pHDH_PP_BLOWING->getCO_CARB_STD_REL( 1);
        Pattern.FixedLime =    m_pHDH_PP_BLOWING->getCO_CARB_FIX_LIME( 1);
        Pattern.FixedCarbide = m_pHDH_PP_BLOWING->getCO_CARB_FIX_CARBIDE( 1);
        Pattern.MinLime =      m_pHDH_PP_BLOWING->getCO_CARB_MIN_LIME( 1);
        Pattern.MinCarbide =   m_pHDH_PP_BLOWING->getCO_CARB_MIN_CARBIDE( 1);
        Pattern.MinMagnesium =  m_pHDH_PP_BLOWING->getCO_CARB_MIN_MG( 1);
      }
      if( p == ECO)
      {
        Pattern.CoRel =        m_pHDH_PP_BLOWING->getECO_STD_REL( 1);
        Pattern.FixedLime =    m_pHDH_PP_BLOWING->getECO_FIX_LIME( 1);
        Pattern.FixedCarbide = m_pHDH_PP_BLOWING->getECO_FIX_CARBIDE( 1);
        Pattern.MinLime =      m_pHDH_PP_BLOWING->getECO_MIN_LIME( 1);
        Pattern.MinCarbide =   m_pHDH_PP_BLOWING->getECO_MIN_CARBIDE( 1);
        Pattern.MinMagnesium =  m_pHDH_PP_BLOWING->getECO_MIN_MG( 1);
      }
    }
  }
  else
    handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement: no data in HDH_PP_BLOWING");

  //typedef struct _TempCorrMgTyp{ //HDH_PP_TEMP_CORR
  //	float CoRel[TEMPCORR_MG_ROWS];
  //	float Corr[TEMPCORR_MG_ROWS];
  //}TempCorrMgTyp;
  // typedef struct _TempCorrCarbTyp{ //HDH_PP_TEMP_CORR
  //	float Temp[TEMPCORR_CARB_ROWS];
  //	float Corr[TEMPCORR_CARB_ROWS];
  //}TempCorrCarbTyp;
  if( !m_pHDH_PP_TEMP_CORR) return false;
  TempCorrMgTyp& TempCorrMg = HMDInput.TCorrMg;
  TempCorrCarbTyp& TempCorrCarb = HMDInput.TCorrCarb;
  //if( m_pHDH_PP_TEMP_CORR->select(ProdPrac, CSMC_DBData::unspecDate /* ordered */, m_PlantNo)) // order added to select method
  if( m_pHDH_PP_TEMP_CORR->select(HeatID, TreatID, m_PlantName, ProdPrac))
  {
    HMDInput.dTempLoss = m_pHDH_PP_TEMP_CORR->getTEMP_LOSS( 1);

    TempCorrMg.CoRel[ 0] = m_pHDH_PP_TEMP_CORR->getMG_CORR_CO_RELATION_1( 1);
    TempCorrMg.CoRel[ 1] = m_pHDH_PP_TEMP_CORR->getMG_CORR_CO_RELATION_2( 1);
    TempCorrMg.CoRel[ 2] = m_pHDH_PP_TEMP_CORR->getMG_CORR_CO_RELATION_3( 1);
    TempCorrMg.CoRel[ 3] = m_pHDH_PP_TEMP_CORR->getMG_CORR_CO_RELATION_4( 1);
    TempCorrMg.CoRel[ 4] = m_pHDH_PP_TEMP_CORR->getMG_CORR_CO_RELATION_5( 1);
    TempCorrMg.Corr[ 0] = m_pHDH_PP_TEMP_CORR->getMG_CORR_FACTOR_10K_1( 1);
    TempCorrMg.Corr[ 1] = m_pHDH_PP_TEMP_CORR->getMG_CORR_FACTOR_10K_2( 1);
    TempCorrMg.Corr[ 2] = m_pHDH_PP_TEMP_CORR->getMG_CORR_FACTOR_10K_3( 1);
    TempCorrMg.Corr[ 3] = m_pHDH_PP_TEMP_CORR->getMG_CORR_FACTOR_10K_4( 1);
    TempCorrMg.Corr[ 4] = m_pHDH_PP_TEMP_CORR->getMG_CORR_FACTOR_10K_5( 1);
    TempCorrCarb.Temp[ 0] = m_pHDH_PP_TEMP_CORR->getCARBIDE_CORR_TEMP_1( 1);
    TempCorrCarb.Temp[ 1] = m_pHDH_PP_TEMP_CORR->getCARBIDE_CORR_TEMP_2( 1);
    TempCorrCarb.Temp[ 2] = m_pHDH_PP_TEMP_CORR->getCARBIDE_CORR_TEMP_3( 1);
    TempCorrCarb.Temp[ 3] = m_pHDH_PP_TEMP_CORR->getCARBIDE_CORR_TEMP_4( 1);
    TempCorrCarb.Temp[ 4] = m_pHDH_PP_TEMP_CORR->getCARBIDE_CORR_TEMP_5( 1);
    TempCorrCarb.Corr[ 0] = m_pHDH_PP_TEMP_CORR->getCARBIDE_CORR_FACTOR_1( 1);
    TempCorrCarb.Corr[ 1] = m_pHDH_PP_TEMP_CORR->getCARBIDE_CORR_FACTOR_2( 1);
    TempCorrCarb.Corr[ 2] = m_pHDH_PP_TEMP_CORR->getCARBIDE_CORR_FACTOR_3( 1);
    TempCorrCarb.Corr[ 3] = m_pHDH_PP_TEMP_CORR->getCARBIDE_CORR_FACTOR_4( 1);
    TempCorrCarb.Corr[ 4] = m_pHDH_PP_TEMP_CORR->getCARBIDE_CORR_FACTOR_5( 1);
  }
  else
      handleError("CHMDTreatmentManagerDataWrapper", "doOnHandleHeatAnnouncement: no data in HDH_PP_TEMP_CORR");

  //struct CalcAmountsTyp{
  //  double dLime[5];
  //  double dCarbide[5];
  //  double dMagnesium[5];
  //};
  //struct CalcFlowTyp{
  //  double dLime[5];			//5 Process Phases
  //  double dCarbide[5];
  //  double dMagnesium[5];
  //};
  //struct ReeOutput{
  //  int		iTreatmentKind;
  //  CalcAmountsTyp CalcAmount[5]; //5 Treatment kinds
  //  CalcFlowTyp    CalcFlow[5];
  //  double	dSlagAmount[5];
  //  double	dDurationDeslagging[5];
  //  double	dTemperatureAfter[5];
  //  double	dCost[5];
  //  double	dDuration[5];
  //  float	  iwarn;
  //};

  ReeOutput HMDOutput;

  string filename;
  filename = "HMD_" + HeatID + "__" + TreatID + "__" + PlantID + ".hmd";
  string hmdInputString = WriteReeInput( HMDInput, filename);
  log(hmdInputString, hmdLogLevel);

  // call model call here
  int res = reemodel( HMDInput , &HMDOutput);

  int iWarn = static_cast<int>(HMDOutput.iwarn);

  if( false)//res == -1)
  {
    // CBS_EventLogMessage.h
    /*
    struct sEventLogMessage
    {
    //##ModelId=42DBB46400DE
    short language; // 0,1,2
    CBS_LocalTime serverDateTime; // = CBS_LocalTime... CDateTime
    CBS_LocalTime applDateTime;   // dito
    std::string originLocation;   // = CBS_StdFrameInitBase::m_ServerName
    long destination;             // C:\bhushan\SMC\packages\SMC\include\SMC_EventLogSystem\CSMC_DestCodes.h
    std::string plantUnit;        // RH
    std::string aggregate;        // 1 / CBS_StdFrameInitBase
    std::string productId;        // Externe Product ID von Task :: getExternalHeatID()
    std::string processState;     // z.B Vacuum Pressure
    long eventId;                 // 12004 ??? JAST
    long eventIdAlter;            // NICHT NUTZEN
    std::string messageText;      // klar
    std::string messageText2;   
    c_e_severity_t severity;      // E_INFO, E_WARNING usw. aus C:\bhushan\SMC\packages\package3.272.01_ora10\include\CBS_EventLog\errorlog.h
    bool trigger;                 // ???
    long opAckn;                  // 0,1   bei 1 kommt PupUp beim operator !!!!!!
    std::string spare1;           // __FILE__ __LINE__
    std::string spare2;           // interne Product ID aus Event->getProductID()
    std::string spare3;           // frei
    std::wstring uniMessage;      // klar !
    };
    */
    //CModelResults_Impl* pModelResults =  m_pModelTask->getpModelResults();

    //if ( pModelResults )
    //{
    //  // its generate unique key
    //  m_Key = pModelResults->generateDataKey( Event.getProductID().c_str());

    //  setComputerMode( m_Key, DEF_MAT_HANDLE_STATUS::NotAvailable);
    //}

    sEventLogMessage msg;

    msg.language = 1;
    //msg.serverDateTime = 
    //msg.applDateTime =
    //msg.originLocation = CBS_StdFrameInitBase::m_ServerName;
    msg.destination = CSMC_DestCodes::HMDBotLine;
    msg.plantUnit = "HMD";
    //msg.aggregate =
    //msg.productId = CRHModelTask::getInstance()->getExternalHeatID();
    msg.processState = "Model calculation";
    msg.eventId = 12004; // ??? JAST

    std::ostringstream os;
    os << HMDOutput.iwarn;
    msg.messageText = string( "HMD model error #") + os.str();
    msg.severity = static_cast<c_e_severity_t>(E_FATAL_ERROR);
    msg.opAckn = 0;
    msg.spare1 = "Reemodel.cpp";
    msg.spare2 = Event.getProductID();

    std::wostringstream wos;
    wos << HMDOutput.iwarn;
    msg.uniMessage = L"HMD model error #" + wos.str(); //  msg.messageText;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    // virtual long sendMessage(sEventLogMessage& EventLogMessage); // aus cCBS_StdEventLog
    pEventLog->sendMessage( msg);

	 log("***********************SeqHMDModelResult ERROR start**************************************",hmdLogLevel);
	 log(msg.messageText,hmdLogLevel);
	 log("***********************SeqHMDModelResult ERROR end **************************************",hmdLogLevel);





    //return false;
  }

  //struct sHMDCalc
  //{
  //  seqDouble Lime;
  //  seqDouble Carbide;
  //  seqDouble Magnesium;
  //};
  //sequence< sHMDCalc> seqHMDCalc;

  //struct sHMDModelResult
  //{
  //  int		     iTreatmentKind;
  //  seqHMDCalc CalcAmount; //5 Treatment kinds
  //  seqHMDCalc CalcFlow;
  //  seqDouble	 SlagAmount;
  //  seqDouble	 DurationDeslagging;
  //  seqDouble	 TemperatureAfter;
  //  seqDouble	 Cost;
  //  seqDouble	 Duration;
  //  long   	   iwarn;
  //};
  try {
    // convert output /////////////
    sHMDModelResult HMDModelResult;

    HMDModelResult.TreatmentKind = HMDOutput.iTreatmentKind + 1;
    HMDModelResult.IWarn = static_cast<CORBA::Long>( HMDOutput.iwarn);
    for( long tk=0; tk<5; ++tk)
    {
      // new array for separate warning/error for each treatment type
      //CIntfData::insert( HMDModelResult.IWarn, HMDOutput.llwarn[ tk]); SANKAR not compiled

      //struct sHMDCalc {
      //  /* treatment duration in sec */
      //  DEF::seqDouble Lime;
      //  /* Calculated material with priority(bin seq no) */
      //  seqBatchPrio Material;
      //  /* Analysis at treatment end */
      //  seqAnalysis Analysis;
      //  /* Aim temp at treatment end in C° */
      //  DEF::seqDouble Carbide;
      //  DEF::seqDouble Magnesium;
      //};

      sHMDCalc actCalcAmount;
      sHMDCalc actCalcFlow;

      // reduce to three phases
      // add 2,3,4 together
      double amtLime[ 3];
      double amtCarbide[ 3];
      double amtMagnesium[ 3];
      double flowLime[ 3];
      double flowCarbide[ 3];
      double flowMagnesium[ 3];
      for( long ph=0; ph<3; ++ph)
      {
        amtLime[ ph] = amtCarbide[ ph] = amtMagnesium[ ph] = 0.0;
        flowLime[ ph] = flowCarbide[ ph] = flowMagnesium[ ph] = 0.0;
      }
      if(tk == ECO)
      {
        amtLime[ 0] = HMDOutput.CalcAmount[ tk].dLime[ 0];
        amtCarbide[ 0] = HMDOutput.CalcAmount[ tk].dCarbide[ 0];
        amtMagnesium[ 0] = HMDOutput.CalcAmount[ tk].dMagnesium[ 0];

        amtLime[ 1] = HMDOutput.CalcAmount[ tk].dLime[ 1]+HMDOutput.CalcAmount[ tk].dLime[ 2]+HMDOutput.CalcAmount[ tk].dLime[ 3];
        amtCarbide[ 1] = HMDOutput.CalcAmount[ tk].dCarbide[ 1]+HMDOutput.CalcAmount[ tk].dCarbide[ 2]+HMDOutput.CalcAmount[ tk].dCarbide[ 3];
        amtMagnesium[ 1] = HMDOutput.CalcAmount[ tk].dMagnesium[ 1]+HMDOutput.CalcAmount[ tk].dMagnesium[ 2]+HMDOutput.CalcAmount[ tk].dMagnesium[ 3];

        amtLime[ 2] = HMDOutput.CalcAmount[ tk].dLime[ 4];
        amtCarbide[ 2] = HMDOutput.CalcAmount[ tk].dCarbide[ 4];
        amtMagnesium[ 2] = HMDOutput.CalcAmount[ tk].dMagnesium[ 4];

        flowLime[ 0] = HMDOutput.CalcFlow[ tk].dLime[ 0];
        flowCarbide[ 0] = HMDOutput.CalcFlow[ tk].dCarbide[ 0];
        flowMagnesium[ 0] = HMDOutput.CalcFlow[ tk].dMagnesium[ 0];

        flowLime[ 1] = HMDOutput.CalcFlow[ tk].dLime[ 2]; //+HMDOutput.CalcFlow[ tk].dLime[ 2]+HMDOutput.CalcFlow[ tk].dLime[ 3];
        flowCarbide[ 1] = HMDOutput.CalcFlow[ tk].dCarbide[ 2]; //+HMDOutput.CalcFlow[ tk].dCarbide[ 2]+HMDOutput.CalcFlow[ tk].dCarbide[ 3];
        flowMagnesium[ 1] = HMDOutput.CalcFlow[ tk].dMagnesium[ 2]; //+HMDOutput.CalcFlow[ tk].dMagnesium[ 2]+HMDOutput.CalcFlow[ tk].dMagnesium[ 3];

        flowLime[ 2] = HMDOutput.CalcFlow[ tk].dLime[ 4];
        flowCarbide[ 2] = HMDOutput.CalcFlow[ tk].dCarbide[ 4];
        flowMagnesium[ 2] = HMDOutput.CalcFlow[ tk].dMagnesium[ 4];

        for( long ph=0; ph<3; ++ph)
        {
          CIntfData::insert( actCalcAmount.Lime,      amtLime[ph]);
          CIntfData::insert( actCalcAmount.Carbide,   amtCarbide[ ph]);
          CIntfData::insert( actCalcAmount.Magnesium, amtMagnesium[ ph]);

          CIntfData::insert( actCalcFlow.Lime,      flowLime[ ph]);
          CIntfData::insert( actCalcFlow.Carbide,   flowCarbide[ ph]);
          CIntfData::insert( actCalcFlow.Magnesium, flowMagnesium[ ph]);
        }    
      }
      else if( (tk == CO_LIME) || (tk == CO_CARBIDE))
      {
        for( long ph=1; ph<4; ++ph)
        {
          CIntfData::insert( actCalcAmount.Lime,      HMDOutput.CalcAmount[ tk].dLime[ ph]);
          CIntfData::insert( actCalcAmount.Carbide,   HMDOutput.CalcAmount[ tk].dCarbide[ ph]);
          CIntfData::insert( actCalcAmount.Magnesium, HMDOutput.CalcAmount[ tk].dMagnesium[ ph]);

          CIntfData::insert( actCalcFlow.Lime,      HMDOutput.CalcFlow[ tk].dLime[ ph]);
          CIntfData::insert( actCalcFlow.Carbide,   HMDOutput.CalcFlow[ tk].dCarbide[ ph]);
          CIntfData::insert( actCalcFlow.Magnesium, HMDOutput.CalcFlow[ tk].dMagnesium[ ph]);
        }    
      }
      else
      {
        amtLime[ 2] = HMDOutput.CalcAmount[ tk].dLime[ 4];
        amtCarbide[ 2] = HMDOutput.CalcAmount[ tk].dCarbide[ 4];
        amtMagnesium[ 2] = HMDOutput.CalcAmount[ tk].dMagnesium[ 4];

        flowLime[ 2] = HMDOutput.CalcFlow[ tk].dLime[ 4];
        flowCarbide[ 2] = HMDOutput.CalcFlow[ tk].dCarbide[ 4];
        flowMagnesium[ 2] = HMDOutput.CalcFlow[ tk].dMagnesium[ 4];

        for( long ph=0; ph<3; ++ph)
        {
          CIntfData::insert( actCalcAmount.Lime,      amtLime[ph]);
          CIntfData::insert( actCalcAmount.Carbide,   amtCarbide[ ph]);
          CIntfData::insert( actCalcAmount.Magnesium, amtMagnesium[ ph]);

          CIntfData::insert( actCalcFlow.Lime,      flowLime[ ph]);
          CIntfData::insert( actCalcFlow.Carbide,   flowCarbide[ ph]);
          CIntfData::insert( actCalcFlow.Magnesium, flowMagnesium[ ph]);
        }    
      }
      //for( long ph=0; ph<5; ++ph)
      //{
      //  CIntfData::insert( actCalcAmount.Lime,      HMDOutput.CalcAmount[ tk].dLime[ ph]);
      //  CIntfData::insert( actCalcAmount.Carbide,   HMDOutput.CalcAmount[ tk].dCarbide[ ph]);
      //  CIntfData::insert( actCalcAmount.Magnesium, HMDOutput.CalcAmount[ tk].dMagnesium[ ph]);

      //  CIntfData::insert( actCalcFlow.Lime,      HMDOutput.CalcFlow[ tk].dLime[ ph]);
      //  CIntfData::insert( actCalcFlow.Carbide,   HMDOutput.CalcFlow[ tk].dCarbide[ ph]);
      //  CIntfData::insert( actCalcFlow.Magnesium, HMDOutput.CalcFlow[ tk].dMagnesium[ ph]);
      //}    
      CIntfData::insert( HMDModelResult.CalcAmount,         actCalcAmount); 
      CIntfData::insert( HMDModelResult.CalcFlow,           actCalcFlow);

      CIntfData::insert( HMDModelResult.SlagAmount,         HMDOutput.dSlagAmount[ tk]);
      CIntfData::insert( HMDModelResult.DurationDeslagging, HMDOutput.dDurationDeslagging[ tk]);
      CIntfData::insert( HMDModelResult.TemperatureAfter,   HMDOutput.dTemperatureAfter[ tk]);
      CIntfData::insert( HMDModelResult.Cost,               HMDOutput.dCost[ tk]);
      CIntfData::insert( HMDModelResult.Duration,           HMDOutput.dDuration[ tk]);
    }

    // all results are in HMDModelResult now
    // send it
    CModelResults_Impl* pModelResults =  m_pModelTask->getpModelResults();

    if ( pModelResults )
    {
      // its generate unique key
      m_Key = pModelResults->generateDataKey( Event.getProductID().c_str());

      setComputerMode( m_Key, DEF_GEN_STATES::Available);

      //doResultGeneral(Event);
      // +++ generate result structure
      // 0 invalid, 1 cyclcic, 2 prediction
      CEventMessage StatusEvent(Event);

      // actual writing of result
      seqHMDModelResult SeqHMDModelResult;
      CIntfData::insert( SeqHMDModelResult, HMDModelResult);
      pModelResults->setHMDModelResult( m_Key.c_str(), DATA::HMDPredRes, SeqHMDModelResult);

	  log("***********************SeqHMDModelResult start**************************************",hmdLogLevel);
	  log(CIntfData::getContent(CIntfData::ToAny(SeqHMDModelResult)),hmdLogLevel);
	  log("***********************SeqHMDModelResult end **************************************",hmdLogLevel);

      //m_pModelResults->setLong(m_Key.c_str(), DATA::HeatAnnounceStatus, AnnounceStatus);
      string ResultMessage = HMD_EvMsg::evHMDModelResult;
      StatusEvent.setMessage( ResultMessage ); // 
      StatusEvent.setDataKey( m_Key );

      // use EventMessage entry as default for SenderName
      std::string SenderName;
      cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage","SenderName",SenderName);

      // overwrite if necessary by inifile entry
      std::string TaskName    = m_pModelTask->getTaskName();
      cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"SenderName",SenderName);

      RetValue = dispatchEvent(SenderName,"",StatusEvent); //CBS Event Channel (CORBA)
      //} // if( Message==RH_EvMsg::evRHHeatAnnouncement ||
    }
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CHMDTreatmentManagerDataWrapper::doOnHandleHeatAnnouncement()",
      ""
      );    
  }

  return RetValue;
}

//##ModelId=41188FB000F6
bool CHMDTreatmentManagerDataWrapper::doOnChangeProdPracData( CEventMessage &Event ) 
// evHMDChangeProdPracData = "HMD_CHANGE_PROD_PRAC_DATA";
{
	return this->CHMDTreatmentManagerDataWrapper::doOnHandleHeatAnnouncement( Event , -1.0);
}

//##ModelId=41188FDC03AC
bool CHMDTreatmentManagerDataWrapper::doOnChangeTapLadleData( CEventMessage &Event ) 
// HMD_EvMsg::evHMDChangeTapLadleData = "HMD_CHANGE_TAP_LADLE_DATA"
{
  bool RetValue = false;

  return RetValue;
}


// this method is from TreatmentAimDataWrapper 
//##ModelId=412F2BBB033D
bool CHMDTreatmentManagerDataWrapper::doOnChangeAimData( CEventMessage &Event ) 
// HMD_EvMsg::evHMDChangeAimData = "HMD_CHANGE_AIM_DATA"
{
  return this->CHMDTreatmentManagerDataWrapper::doOnHandleHeatAnnouncement( Event, -1.0, true );
}
bool CHMDTreatmentManagerDataWrapper::doOnTempMeasurement( CEventMessage &Event ) 
// HMD_EvMsg::evHMDChangeAimData = "HMD_CHANGE_AIM_DATA"
{
  return this->CHMDTreatmentManagerDataWrapper::doOnHandleHeatAnnouncement( Event, -1.0, true );
}

bool CHMDTreatmentManagerDataWrapper::doOnAnalysisReceived( CEventMessage &Event ) 
// HMD_EvMsg::evHMDHotMetalAnalysisReceived = "HMD_HOT_METAL_ANALYSIS_RECEIVED"
{
	std::string DataKey   = Event.getDataKey();

	seqAnalysisData SeqAnalysisData;
	
    // collect data from event data interface
    //setpDM_Interface(Event.getSender(),DM::EVENT);

    //SeqAnalysisData = CIntfData::ToCORBAType(m_pDM_Interface->getAnalysisData(DataKey.c_str(),DATA::HMMeasAnalysis));


	SeqAnalysisData = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(), CHMDModelTask::EVENT)->
      getAnalysisData( Event.getDataKey().c_str(), DATA::HMMeasAnalysis));

	seqAnalysis      MeasAnalysis;
	sAnalysisData    AnalysisStruct;
	double			sulph= -1.0;
	if (CIntfData::getAt(AnalysisStruct, SeqAnalysisData, 0))
	{
		MeasAnalysis  = AnalysisStruct.Analysis;

		std::string ElementName;
		long Length = CIntfData::getLength(MeasAnalysis);

		for (long i = 0; i < Length; ++i)
		{
			sAnalysis Anl;
			CIntfData::getAt(Anl, &MeasAnalysis, i);
			ElementName = Anl.Element;
			if(ElementName == "S") 
				sulph = Anl.Concentration;
		
		}
	
		/*for( long k = 0; k < CIntfData::getLength( MeasAnalysis); ++k)
		{
		sAnalysis AN;
		CIntfData::getAt( AN, AD.Analysis, k);

		string elName = AN.Element;
		if(elName=="S") sulph=AN.Concentration;
		int elIx = ElementIndexNoThrowBhushan( elName);
		if( elIx != -1)
			modelAnalysis[ elIx] = AN.Concentration / 100.0; 
		else
			cout << "unknown element: " << elName << endl;
		}*/
	}
  return this->CHMDTreatmentManagerDataWrapper::doOnHandleHeatAnnouncement( Event, sulph, true );
}


