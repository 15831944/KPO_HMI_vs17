// Copyright (C) 2004 SMS Demag AG
#if defined(WIN32) || defined(_WIN32) 
#pragma warning(disable:4786)
#pragma warning(disable:4503)
#endif

#include <string>
#include <sstream>

#include "iSMC_DataProvider_s.hh"
#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"

#include "CIntfEAF.h"
#include "CCfgEAF.h"
#include "CIntfTreatmentMap.h"

#include "CInv.h"
#include "CRS.h"
#include "CCtrlSystemCodesEAF.h"
#include "CProcPatCodesEAF.h"
#include "CTreatStatCodes.h"
#include "CTreatStatCodesEAF.h"
#include "CPracPhaseCodesEAF.h"
#include "CPurposeCodesEAF.h"
#include "CKeyStringsEAF.h"
#include "CSourceEAF.h"

#include "DEF_GC_MEASUREMENT_NAME.h"
#include "DEF_GC_MEASUREMENT_NAME_SCOPE.h"
#include "DEF_GC_PP_ORDER_SINGLE_AIMS.h"
#include "DEF_GC_COMP_STATUS.h"

#include  "CPD_RECIPE.h"
#include  "CPD_RECIPE_ENTRY.h"
#include  "CHDE_PP_FLAME_PROFILE.h"
#include  "CGTE_PP_FLAME_PROFILE.h"

#include "CPD_SCRAP_CONTAINER_ENTRY.h"

#include "CPD_SCRAP_CONTAINER_ORDER.h"
#include "CPD_SCRAP_CONTAINER_ORDER_ENTRY.h"
#include "CPD_SAMPLE_REF.h";
#include "CPD_PRETREATDATA.h";
#include "CPD_SAMPLE.h" ;

#include "CGT_MAT_PURP.h"
#include "CGT_MAT.h"
#include "CGC_PHASE.h"
#include "CGC_RESTRI_DEF.h"
#include "CGC_RECIPE_SOURCE.h"
#include "CGT_PARAM.h"

#include "CHD_RESTRI.h"
#include "CHD_RESTRI_ENTRY.h"
#include "CHD_GRADE.h"              // we need this due to constraint on HD_GRADE_ANL: "FK_HD_GRADE_ANL_HD_GRADE"
#include "CHD_GRADE_ANL.h"
#include "CHD_GRADE_EQUIV.h"
#include "CGT_EQUIV.h"

#include "CHD_TREATMODE.h"
#include "CHD_TREATMODE_ENTRY.h"
#include "CHD_GRADE_SINGLE_AIMS.h"
#include "CPP_ORDER_SINGLE_AIMS.h"

#include "CPP_HEAT.h"
#include "CPP_HEAT_PLANT.h"
#include "CGC_RECIPE_L1.h"
#include "CPD_MAT_AVAIL.h"
#include "CPD_HEAT_DATA.h"
#include "CPD_HEAT_DATA_PRODPRAC.h"
#include "CPD_HEAT_DATA_LIQADD.h"
#include "CPD_HOTHEEL.h"
#include "CGT_TREATMODE_ENTRY.h"

#include "CPD_LADLE.h"

#include "CParamMgr.h"
#include "cCBS_StdInitBase.h"
#include "CSMC_EventLogFrameController.h"
#include "CSMM.h"

// production practice - bottom stirring
#include "CHDE_PP_STIRR.h"
#include "CHDE_PP_STIRR_SPEC.h"
#include "CHDE_PP_EL.h"
#include "CHDE_PP_PROCESS_PARAM.h"
#include "CHDE_PP_EL_STEP_ENTRY.h"
#include "CHDE_PP_BURNER.h"
#include "CHDE_PP_BURNER_STEP_ENTRY.h"
#include "CHDE_PP_INJECTION.h"
#include "CGCE_INJECTION.h"
#include "CGCE_INJECTION_TYPE.h"
#include "CGCE_BURNER.h"
#include "CHDE_PP_INJECTION_STEP_ENTRY.h"
#include "CGC_COMBI_RECIPE_ENTRY.h"

#include "CHDE_PP_PROCESS.h"
#include "CHDE_PP_PROCESS_STEP_ENTRY.h"
#include "CPD_SAMPLE_ENTRY.h"
#include "DEF_GC_SCRAP_CONTAINER_TYPE.h"
#include "CHD_MAT_FEED.h"
#include "DEF_GCE_INJECTION_TYPE.h"
#include "DEF_GC_GRADE_ANL.h"
#include "DEF_GC_THERM_STAT.h"
#include "DEF_GC_LIQADD_STATUS.h"
#include "DEF_GC_PRODPRAC_DEF.h"
#include "DEF_GC_LIQADD_TYPE.h"

#include "CDataConversion.h"
#include "CEAFModelTask.h"
#include "CEAFModelWrapper.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_SCRAP_CONT_ORDER_STATUS.h"


//##ModelId=4146F7C8033B
CEAFModelWrapper::CEAFModelWrapper():
m_pGC_PhaseContainer(0),
m_pGC_PHASE(0),
m_pGC_RECIPE_SOURCE(0),
m_pGC_RESTRI_DEF(0),
m_pHD_RESTRI(0),
m_pHD_RESTRI_ENTRY(0),
m_pPD_HEAT_DATA(0),
m_pPD_HEAT_DATA_LIQADD(0),
m_pPD_HEAT_DATA_PRODPRAC(0),
m_pPD_HOTHEEL(0),
m_pGT_TREATMODE_ENTRY(0),
m_pPD_LADLE(0),
m_pHD_MAT_FEED(0),
m_pHD_GRADE(0),
m_pHD_GRADE_ANL(0),
m_pHD_GRADE_EQUIV(0),
m_pGT_EQUIV(0),
m_pHD_TREATMODE(0),
m_pHD_TREATMODE_ENTRY(0),
m_pHD_GRADE_SINGLE_AIMS(0),
m_pPP_ORDER_SINGLE_AIMS(0),

m_pGC_COMBI_RECIPE_ENTRY(0),

m_pPD_SCRAP_CONTAINER_ENTRY(0),

m_pPD_SCRAP_CONTAINER_ORDER(0),
m_pPD_SCRAP_CONTAINER_ORDER_ENTRY(0),
m_pPD_SAMPLE_REF(0),
m_pPD_PRETREATDATA(0),
m_pPD_SAMPLE(0),
m_pPD_SAMPLE_ENTRY(0),

m_PD_RECIPE(0),
m_PD_RECIPE_ENTRY(0),

m_pPD_MAT_AVAIL(0),
m_pPP_HEAT(0),
m_pPP_HEAT_PLANT(0),
m_pGT_MAT_PURP(0),
m_pGT_MAT(0),
m_pGC_RECIPE_L1(0),
m_pRecipeHandler(0),

m_pHDE_PP_EL(0),
m_pHDE_PP_PROCESS_PARAM(0),
m_pHDE_PP_EL_STEP_ENTRY(0),

m_pHDE_PP_BURNER(0),
m_pHDE_PP_BURNER_STEP_ENTRY(0),

m_pHDE_PP_INJECTION(0),
m_pHDE_PP_INJECTION_STEP_ENTRY(0),
m_pGCE_INJECTION(0),
m_pGCE_INJECTION_TYPE(0),
m_pHDE_PP_PROCESS(0),
m_pHDE_PP_PROCESS_STEP_ENTRY(0),

m_pHDE_PP_FLAME_PROFILE(0),
m_pGTE_PP_FLAME_PROFILE(0),

m_pHDE_PP_STIRR(0),
m_pHDE_PP_STIRR_SPEC(0),
m_NumberOfBasketsForHeat(0),
m_FractionOfLiquidMaterial(CInv::InvalidDouble)
{  

  m_pRecipeHandler = new CSMC_RecipeHandler();

}

//##ModelId=4146F7C80377
CEAFModelWrapper::~CEAFModelWrapper()
{
  deleteDBClasses();  
  delete m_pRecipeHandler;
}

//##ModelId=4201044A031C
void CEAFModelWrapper::initDBClasses()
{
  cCBS_StdConnection *pConnection = getStdConnection();

  m_pGC_PhaseContainer          = new CGC_PhaseContainer(pConnection, DEF_GC_PLANT_DEF::EAF);

  m_pGC_PHASE                     = new CGC_PHASE(pConnection); //not used
  m_pGC_RECIPE_SOURCE             = new CGC_RECIPE_SOURCE(pConnection);
  m_pGC_RESTRI_DEF                = new CGC_RESTRI_DEF(pConnection);

  m_pHD_RESTRI                    = new CHD_RESTRI(pConnection);
  m_pHD_RESTRI_ENTRY              = new CHD_RESTRI_ENTRY(pConnection);

  m_pPD_HEAT_DATA                 = new CPD_HEAT_DATA(pConnection);
  m_pPD_HEAT_DATA_LIQADD          = new CPD_HEAT_DATA_LIQADD(pConnection);
  m_pPD_HEAT_DATA_PRODPRAC        = new CPD_HEAT_DATA_PRODPRAC(pConnection);
  m_pPD_HOTHEEL                   = new CPD_HOTHEEL(pConnection);
  m_pGT_TREATMODE_ENTRY           = new CGT_TREATMODE_ENTRY(pConnection);

  m_pPD_LADLE                     = new CPD_LADLE(pConnection);

  m_pHD_GRADE                     = new CHD_GRADE(pConnection);
  m_pHD_GRADE_ANL                 = new CHD_GRADE_ANL(pConnection);
  m_pHD_GRADE_EQUIV               = new CHD_GRADE_EQUIV(pConnection);
  m_pGT_EQUIV                     = new CGT_EQUIV(pConnection);

  m_pHD_TREATMODE                 = new CHD_TREATMODE(pConnection);
  m_pHD_TREATMODE_ENTRY           = new CHD_TREATMODE_ENTRY(pConnection);
  m_pHD_GRADE_SINGLE_AIMS         = new CHD_GRADE_SINGLE_AIMS(pConnection);
  m_pPP_ORDER_SINGLE_AIMS         = new CPP_ORDER_SINGLE_AIMS(pConnection);

  m_pGC_COMBI_RECIPE_ENTRY        = new CGC_COMBI_RECIPE_ENTRY(pConnection);

  m_pHDE_PP_EL                    = new CHDE_PP_EL(pConnection);
  m_pHDE_PP_PROCESS_PARAM         = new CHDE_PP_PROCESS_PARAM(pConnection);
  m_pHDE_PP_EL_STEP_ENTRY         = new CHDE_PP_EL_STEP_ENTRY(pConnection);

  m_pHDE_PP_BURNER                = new CHDE_PP_BURNER(pConnection);
  m_pHDE_PP_BURNER_STEP_ENTRY     = new CHDE_PP_BURNER_STEP_ENTRY(pConnection);

  m_pPD_SCRAP_CONTAINER_ENTRY     = new CPD_SCRAP_CONTAINER_ENTRY(pConnection);

  m_pPD_SCRAP_CONTAINER_ORDER     = new CPD_SCRAP_CONTAINER_ORDER(pConnection);
  m_pPD_SCRAP_CONTAINER_ORDER_ENTRY = new CPD_SCRAP_CONTAINER_ORDER_ENTRY(pConnection);
  m_pPD_SAMPLE_REF                = new CPD_SAMPLE_REF(pConnection);
  m_pPD_PRETREATDATA              = new CPD_PRETREATDATA(pConnection);
  m_pPD_SAMPLE                    = new CPD_SAMPLE(pConnection);
  m_pPD_SAMPLE_ENTRY              = new CPD_SAMPLE_ENTRY(pConnection)  ;
  m_pHD_MAT_FEED                  = new CHD_MAT_FEED(pConnection);
  m_pHDE_PP_FLAME_PROFILE         = new CHDE_PP_FLAME_PROFILE(pConnection);
  m_pGTE_PP_FLAME_PROFILE         = new CGTE_PP_FLAME_PROFILE(pConnection);

  m_PD_RECIPE                     = new CPD_RECIPE      (pConnection);
  m_PD_RECIPE_ENTRY               = new CPD_RECIPE_ENTRY(pConnection);

  m_pPD_MAT_AVAIL                 = new CPD_MAT_AVAIL(pConnection);
  m_pPP_HEAT                      = new CPP_HEAT(pConnection);
  m_pPP_HEAT_PLANT                = new CPP_HEAT_PLANT(pConnection);
  m_pGT_MAT_PURP                  = new CGT_MAT_PURP(pConnection);
  m_pGT_MAT                       = new CGT_MAT (pConnection);;
  m_pGC_RECIPE_L1                 = new CGC_RECIPE_L1(pConnection);

  m_pHDE_PP_INJECTION             = new CHDE_PP_INJECTION(pConnection);

  //to convert LANCENAME to LanceNo
  m_pGCE_INJECTION                = new CGCE_INJECTION(pConnection);
  m_pGCE_BURNER                   = new CGCE_BURNER(pConnection);

  m_pHDE_PP_INJECTION_STEP_ENTRY  = new CHDE_PP_INJECTION_STEP_ENTRY(pConnection);

  m_pHDE_PP_BURNER                = new CHDE_PP_BURNER(pConnection);
  m_pHDE_PP_BURNER_STEP_ENTRY     = new CHDE_PP_BURNER_STEP_ENTRY(pConnection);


  m_pHDE_PP_PROCESS               = new CHDE_PP_PROCESS(pConnection);
  m_pHDE_PP_PROCESS_STEP_ENTRY    = new CHDE_PP_PROCESS_STEP_ENTRY(pConnection) ;

  m_pHDE_PP_STIRR                 = new CHDE_PP_STIRR(pConnection);
  m_pHDE_PP_STIRR_SPEC            = new CHDE_PP_STIRR_SPEC(pConnection);

  m_pHDE_PP_INJECTION_STEP_ENTRY  = new CHDE_PP_INJECTION_STEP_ENTRY(pConnection);

  m_pGCE_INJECTION_TYPE           = new CGCE_INJECTION_TYPE(pConnection);

}

//##ModelId=4201044B010B
void CEAFModelWrapper::deleteDBClasses()
{
  if (m_pGC_PhaseContainer)     {delete m_pGC_PhaseContainer; m_pGC_PhaseContainer = 0;}

  delete m_pGC_PHASE;
  delete m_pGC_RECIPE_SOURCE;
  delete m_pGC_RESTRI_DEF;
  delete m_pHD_RESTRI;
  delete m_pHD_RESTRI_ENTRY;
  delete m_pPD_HEAT_DATA;
  delete m_pPD_HEAT_DATA_LIQADD;
  delete m_pPD_HEAT_DATA_PRODPRAC; 
  delete m_pPD_HOTHEEL;
  delete m_pGT_TREATMODE_ENTRY;
  delete m_pPD_LADLE;
  delete m_pHD_GRADE;
  delete m_pHD_GRADE_ANL;
  delete m_pHD_GRADE_EQUIV;
  delete m_pGT_EQUIV;
  delete m_pHD_TREATMODE;
  delete m_pHD_TREATMODE_ENTRY;

  delete m_pHD_GRADE_SINGLE_AIMS;
  delete m_pPP_ORDER_SINGLE_AIMS;

  delete m_pGC_COMBI_RECIPE_ENTRY;

  delete m_pHDE_PP_EL; 
  delete m_pHDE_PP_PROCESS_PARAM; 
  delete m_pHDE_PP_EL_STEP_ENTRY; 
  delete m_pHD_MAT_FEED;
  delete m_pHDE_PP_FLAME_PROFILE;
  delete m_pGTE_PP_FLAME_PROFILE;

  delete m_pPD_SCRAP_CONTAINER_ENTRY;

  delete m_pPD_SCRAP_CONTAINER_ORDER;
  delete m_pPD_SCRAP_CONTAINER_ORDER_ENTRY;
  delete m_pPD_SAMPLE_REF;
  delete m_pPD_PRETREATDATA;
  delete m_pPD_SAMPLE;
  delete m_pPD_SAMPLE_ENTRY ;

  delete m_PD_RECIPE;
  delete m_PD_RECIPE_ENTRY;

  delete m_pPD_MAT_AVAIL;
  delete m_pPP_HEAT; 
  delete m_pPP_HEAT_PLANT; 
  delete m_pGT_MAT_PURP; 
  delete m_pGT_MAT;
  delete m_pGC_RECIPE_L1; 

  delete m_pHDE_PP_INJECTION; 
  delete m_pHDE_PP_INJECTION_STEP_ENTRY;

  delete m_pGCE_INJECTION; 
  delete m_pGCE_INJECTION_TYPE; 

  delete m_pHDE_PP_BURNER;
  delete m_pHDE_PP_BURNER_STEP_ENTRY; 

  delete m_pGCE_INJECTION;
  delete m_pGCE_BURNER;

  delete m_pHDE_PP_PROCESS;
  delete m_pHDE_PP_PROCESS_STEP_ENTRY; 

  delete m_pHDE_PP_STIRR;
  delete m_pHDE_PP_STIRR_SPEC; 
  
}

//##ModelId=4201044B01BF
void CEAFModelWrapper::handleError(const char * Function, const char * Action)
{
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ExceptionCaught(sMessage, "", Function, Action);    
}
bool CEAFModelWrapper::checkIntfPtr(const CIntfEAF *pIntfEAF, const char * Function, const char * Action)
{
  return true;    // always fine for PNTZ
}

//##ModelId=4201044C0333
void CEAFModelWrapper::handleCORBAConnectionError(const char * Function, const char * Action)
{
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ExceptionCaught(sMessage, "",  Function, Action);    
}

//##ModelId=4201044E00AB
void CEAFModelWrapper::handleDBConnectionError(cCBS_DBExc &e, const char * Function, const char * Action)
{
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function, Action);

  handleDBConnectionError();
}

//##ModelId=420104510236
void CEAFModelWrapper::handleDBConnectionError()
{
  if (m_pModelTask)
  {
    m_pModelTask->handleDBConnectionError();
  }

}
//##ModelId=4118D23503AD
bool CEAFModelWrapper::doModelResult(CEventMessage &Event)
{
  bool RetValue = false;

  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);


  if (m_pModelTask) 
  {
    CIntfEAF* pIntf = 0;

    //dynamic cast is preferable to static - cast, see scott-meyers
    CEAFModelTask* pTask = dynamic_cast  <CEAFModelTask*>(m_pModelTask);
    if (pTask) pIntf = pTask->getpIntfEAF();

    if (pIntf)
      RetValue = pTask->callModelResultWrapper(ActPlant,Event);              // get results from model-interface
    else
      RetValue = pTask->callModelResultWrapper(ActPlant, Event, *this);      // get results from here by callback
  }

  return RetValue;
}



//##ModelId=45EBDA3C0183
CIntfEAF* CEAFModelWrapper::getpModelIntf()
{
  CIntfEAF* pIntf = 0;

  //dynamic cast is preferable to static - cast, see scott-meyers
  CEAFModelTask*  pTask = dynamic_cast <CEAFModelTask*>(m_pModelTask);
  if (pTask) pIntf = pTask->getpIntfEAF();

  if(!pIntf) log("pIntf is FALSE -- check please!!!",2);

  return pIntf;
}
const CCfgEAF* CEAFModelWrapper::getpCfgEAF() const
{
  const CCfgEAF* pCfgEAF = 0;

  //dynamic cast is preferable to static - cast, see scott-meyers
  CEAFModelTask*  pTask = dynamic_cast <CEAFModelTask*>(m_pModelTask);
  if (pTask)   pCfgEAF = pTask->getpCfgEAF();
  return pCfgEAF;
}

CCfgEAF* CEAFModelWrapper::getUnConstpCfgEAF()
{
  CCfgEAF* pCfgEAF = 0;

  //dynamic cast is preferable to static - cast, see scott-meyers
  CEAFModelTask*  pTask = dynamic_cast <CEAFModelTask*>(m_pModelTask);
  if (pTask)   pCfgEAF = pTask->getUnConstpCfgEAF();
  return pCfgEAF;
}

//##ModelId=422EFFDF031F
bool CEAFModelWrapper::setkeysForPracticeDataIfChanged(const std::string& HeatID, const std::string& TreatID, const std::string& Plant, long PriorityCode, long NewLastBasketNo)
{
  bool RetValue = false;     
  //long PriorityCode =0;  // 0: undefined, 1 : basket data, 2 : hot metal data, to be set depending on context of event

  double NewFraction       (CInv::InvalidDouble);
  double AimSteelWeight    (0.0);
  double LiquidSteelWeight (0.0);

  try // common catch
  {
    if (NewLastBasketNo == 0)  // no basket data found
    {
      CParamMgr* pParamMgr = 0;
      CEAFModelTask* pTask = dynamic_cast <CEAFModelTask*>(m_pModelTask);
      if (pTask) pParamMgr = pTask->getpParamMgr();

      if (pParamMgr) 
      {
        std::string skey ("DefltNoOfBaskets"); 
        NewLastBasketNo = pParamMgr->getLong(skey);
      }

      if (CInv::InvalidLong == NewLastBasketNo)
        NewLastBasketNo = 1;  // if no parameter defined, assume at least one basket.
    }


    if (m_pPD_HEAT_DATA->select(HeatID, TreatID, Plant)) // only 1 row can be selected
    {            
      if (m_pPD_HEAT_DATA->isNull(CPD_HEAT_DATA::AIMSTEELWGT_MOD, 1)) 
        AimSteelWeight = m_pPD_HEAT_DATA->getAIMSTEELWGT_PLAN(1);
      else         
        AimSteelWeight = m_pPD_HEAT_DATA->getAIMSTEELWGT_MOD(1);
    }
    if (AimSteelWeight <= 0.) AimSteelWeight = 100000.; // preset default value


    if (m_pPD_HEAT_DATA_LIQADD->select(HeatID, TreatID, Plant, CSMC_DBData::unspecLong))
    {            
      for (int i = 1; i <=   m_pPD_HEAT_DATA_LIQADD->getLastRow(); ++i)
        if (m_pPD_HEAT_DATA_LIQADD->getSTATUS(i) == DEF_GC_LIQADD_STATUS::ASSIGNED)
          LiquidSteelWeight += m_pPD_HEAT_DATA_LIQADD->getSTEELWEIGHT (i);
    }



    NewFraction = (LiquidSteelWeight / AimSteelWeight);
  }
  catch(...)
  {
    handleCORBAConnectionError("CEAFModelWrapper::setkeysForPracticeDataIfChanged()", "");
  }


  if (NewFraction != m_FractionOfLiquidMaterial)
  {
    m_FractionOfLiquidMaterial = NewFraction;
    RetValue = true;
  }
  return RetValue;

 
}



bool CEAFModelWrapper::sequence_set_treatmentmap_data(const std::string& HeatID, const std::string& TreatID, const std::string& Plant ,long TreatmentMode)
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();
  // create an treatmentmap object
  CCfgEAF *pCfgEAF = getUnConstpCfgEAF();  
  CIntfTreatmentMap IntfTreatmentMap(*pCfgEAF, *pIntfEAF) ;

  if (!pIntfEAF || !m_pModelTask || !checkDBConnection()) 
  {
    log("error CEAFModelWrapper::sequence_set_treatmentmap_data(), (pIntfEAF || m_pModelTask || checkDBConnection()) == false", 1);
    return RetValue;
  }

  try
  {  

    if (m_pHD_TREATMODE->select(HeatID, TreatID, Plant, TreatmentMode)) 
    {
      std::string treatDesc = m_pHD_TREATMODE->getDESCRIPTION(1);
      IntfTreatmentMap.setTreatmentMode( treatDesc, TreatmentMode );
    }

    if (m_pHD_TREATMODE_ENTRY->selectOrdered(HeatID, TreatID, Plant, TreatmentMode)) 
    {
      std::string strLastPhase;
      long nLastTreatPhaseNo;
      long nLength = m_pHD_TREATMODE_ENTRY->getLastRow();
      if( nLength > 0)
      {
        strLastPhase = m_pHD_TREATMODE_ENTRY->getTREATMENTPHASE(1);
        nLastTreatPhaseNo = m_pHD_TREATMODE_ENTRY->getTREATMENTPHASENO(1);
      }

      for (int i = 2; i <= m_pHD_TREATMODE_ENTRY->getLastRow(); i++) 
      {
        std::string treatPhase = m_pHD_TREATMODE_ENTRY->getTREATMENTPHASE(i);
        long nTreatPhaseNo = m_pHD_TREATMODE_ENTRY->getTREATMENTPHASENO(i);
        //IntfTreatmentMap->setTretmentStepToStartAfter( treatPhase, nTreatPhaseNo, strLastPhase, nLastTreatPhaseNo);
        IntfTreatmentMap.setTreatmentActivityToStartAfter( treatPhase, nTreatPhaseNo, strLastPhase, nLastTreatPhaseNo);
        nLastTreatPhaseNo = nTreatPhaseNo;
        strLastPhase = treatPhase;
      }

      RetValue = true;
    } 
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CEAFModelWrapper::sequence_set_treatmentmap_data()", ""  );    
  } 

  return RetValue;
}

//##ModelId=4200DE3B0125
bool CEAFModelWrapper::sequence_set_aim_data(const std::string& HeatID, const std::string& TreatID, const std::string& Plant, long PlantNo)
{
  bool RetValue = false;
  std::string Function = "CEAFModelWrapper::sequence_set_aim_data()" ;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !checkDBConnection()) 
  {
    log("Error " + Function + " , (pIntfEAF || checkDBConnection()) == false", 1);
    return RetValue;
  }
  else
  {
    log(Function, 3);
  }

  try
  { 
    if (m_pPD_HEAT_DATA->select(HeatID, TreatID, Plant)) 
    {            
      CDateTime     TreatStartTime, TreatEndTime;
      CDeltaTime    DurAimTime;
      std::string   EquivalenceName;
      double        Value = 0.;

      // ********************************
      // AIM WEIGHT
      // ********************************
      double aimWeight = -1;
      if (m_pPD_HEAT_DATA->isNull(CPD_HEAT_DATA::AIMSTEELWGT_MOD, 1)) 
      {
        aimWeight = m_pPD_HEAT_DATA->getAIMSTEELWGT_PLAN(1);
      }
      else         
      {
        aimWeight = m_pPD_HEAT_DATA->getAIMSTEELWGT_MOD(1);
      }

      if( (aimWeight != CSMC_DBData::unspecDouble) && (aimWeight > 0))
      {
        pIntfEAF->focusOnStatus(CTreatStatCodes::FinalDelivery);
        pIntfEAF->setAimMass(aimWeight);
      }
     
      // ********************************
      // AIM TEMP
      // ********************************
      double aimTemp = -1;
      if (m_pPD_HEAT_DATA->isNull(CPD_HEAT_DATA::AIMTEMP_MOD, 1)) 
      {
        aimTemp = m_pPD_HEAT_DATA->getAIMTEMP_PLAN(1);
      }
      else 
      {
        aimTemp = m_pPD_HEAT_DATA->getAIMTEMP_MOD(1);
      }

      if( (aimTemp != CSMC_DBData::unspecDouble) && (aimTemp > 0))
      {
        pIntfEAF->focusOnStatus(CTreatStatCodes::BefTapInVessel);
        pIntfEAF->setAimTemp(aimTemp);
      }

      // ********************************
      // STEEL GRADE
      // ********************************
      std::string SteelGradeCode;
      if (m_pPD_HEAT_DATA->isNull(CPD_HEAT_DATA::STEELGRADECODE_ACT, 1)) 
      {
        SteelGradeCode = m_pPD_HEAT_DATA->getSTEELGRADECODE_PLAN(1);      
      }
      else         
      {
        SteelGradeCode = m_pPD_HEAT_DATA->getSTEELGRADECODE_ACT(1);
      }

      // **********************************************************
      // according to UML design sequence must be called as follows
      // **********************************************************
      // pIntfEAF->declareEquivalenceName(EquivalenceName,isActive);
      // pIntfEAF->declareEquivalenceTerm(EquivalenceName,Value,true);
      // pIntfEAF->setAimSteelGradeCode(SteelGradeCode);      

      // try to find existing equivalences
      if ( m_pHD_GRADE_EQUIV->select(HeatID, TreatID, Plant, SteelGradeCode, CSMC_DBData::unspecString) )
      {
        // JAST EL_

        for ( long i = 1 ; i <= m_pHD_GRADE_EQUIV->getLastRow() ; ++i )
        {
          EquivalenceName = m_pHD_GRADE_EQUIV->getEQ_NAME(i);
            
          if ( m_pGT_EQUIV->select(EquivalenceName) )
          {
            //pIntfEAF->declareEquivalenceName(EquivalenceName,true);

            // handle offset
            Value = m_pGT_EQUIV->getOFFSET(1);
            //pIntfEAF->declareEquivalenceTerm(EquivalenceName,Value,true);

            std::map<std::string,double> Numerator    = m_pGT_EQUIV->getNumerator(EquivalenceName);
            std::map<std::string,double> Denominator  = m_pGT_EQUIV->getDenominator(EquivalenceName);
            std::map<std::string,double>::iterator it;

            // handle Numerator
            for ( it = Numerator.begin() ; it != Numerator.end(); ++it )
            {
              //pIntfEAF->declareEquivalenceTerm(EquivalenceName,it->second,true,it->first);
            }
            // handle Denominator
            for ( it = Denominator.begin() ; it != Denominator.end(); ++it )
            {
              //pIntfEAF->declareEquivalenceTerm(EquivalenceName,it->second,false,it->first);
            }
          }
          else
          {
            // JAST EL_
          }
        } // for ( long i = 1 ; i <= m_pHD_GRADE_EQUIV.getLastRow() ; ++i )
      } // if ( m_pHD_GRADE_EQUIV->select(HeatID, TreatID, m_PlantName, SteelGradeCode, CSMC_DBData::unspecString) )


      pIntfEAF->setAimSteelGradeCode(SteelGradeCode);      

      
      // ********************************
      // TREATMENT TIMES
      // ********************************
      if (!m_pPD_HEAT_DATA->isNull(CPD_HEAT_DATA::TREATSTART_ACT, 1)) 
      {
        TreatStartTime = m_pPD_HEAT_DATA->getTREATSTART_ACT(1);
      }
      else if (!m_pPD_HEAT_DATA->isNull(CPD_HEAT_DATA::TREATSTART_MOD, 1))
      {
        TreatStartTime = m_pPD_HEAT_DATA->getTREATSTART_MOD(1);
      }
      else 
      {
        TreatStartTime = m_pPD_HEAT_DATA->getTREATSTART_PLAN(1);
      }

      if (!m_pPD_HEAT_DATA->isNull(CPD_HEAT_DATA::TREATEND_ACT, 1))
      {
        TreatEndTime = m_pPD_HEAT_DATA->getTREATEND_ACT(1);
      }
      else if (!m_pPD_HEAT_DATA->isNull(CPD_HEAT_DATA::TREATEND_MOD, 1)) 
      {
        TreatEndTime = m_pPD_HEAT_DATA->getTREATEND_MOD(1);
      }
      else 
      {
        TreatEndTime = m_pPD_HEAT_DATA->getTREATEND_PLAN(1);
      }

      DurAimTime  = CDateTime::subTimes(TreatEndTime, TreatStartTime);

      double DurAim = DurAimTime.asSeconds();
      if (DurAim < 1.)
      {
        long l0 =0;       //dummy
        std::string skey ("DefltTreatDuration"); 
        pIntfEAF->getKeyedInformation("DParam",0, skey, l0,  DurAim);
      }
      else
      {
        DurAim = DurAim/60;
      }

      pIntfEAF->setAimDepartTime(DurAim); 

      // ********************************
      // ANALYSIS
      // ********************************
      bool IsAimEOT = false;

      pIntfEAF->focusOnStatus(CTreatStatCodes::FinalDelivery);

      if( m_pHD_GRADE_ANL->select(HeatID, TreatID, Plant, SteelGradeCode, CSMC_DBData::unspecString, CSMC_DBData::unspecString) )
      {     
        for (int i = 1; i <= m_pHD_GRADE_ANL->getLastRow(); ++i) 
        {
          std::string type = m_pHD_GRADE_ANL->getAIMTYPE(i);

          if( type == DEF_GC_GRADE_ANL::AimEOT || 
              type == DEF_GC_GRADE_ANL::MinEOT || 
              type == DEF_GC_GRADE_ANL::MaxEOT   )
          {
            IsAimEOT = true;

            if ( type == DEF_GC_GRADE_ANL::AimEOT ) type = DEF_GC_GRADE_ANL::Aim;
            if ( type == DEF_GC_GRADE_ANL::MaxEOT ) type = DEF_GC_GRADE_ANL::Max;
            if ( type == DEF_GC_GRADE_ANL::MinEOT ) type = DEF_GC_GRADE_ANL::Min;

            pIntfEAF->setAimAnl(type,m_pHD_GRADE_ANL->getENAME(i),m_pHD_GRADE_ANL->getANL(i));
          }
        }

        if ( IsAimEOT )
        {
          pIntfEAF->focusOnStatus(CTreatStatCodes::BefTapInVessel);
        }

        for (int i = 1; i <= m_pHD_GRADE_ANL->getLastRow(); ++i) 
        {
          std::string type = m_pHD_GRADE_ANL->getAIMTYPE(i);

          if( (type == DEF_GC_GRADE_ANL::Aim) || (type == DEF_GC_GRADE_ANL::Min) || (type == DEF_GC_GRADE_ANL::Max))
          {
            pIntfEAF->setAimAnl(m_pHD_GRADE_ANL->getAIMTYPE(i),m_pHD_GRADE_ANL->getENAME(i),m_pHD_GRADE_ANL->getANL(i));
          }
        }
      }

      // ********************************
      // BASICITY
      // ********************************
      if( m_pHD_GRADE_SINGLE_AIMS->select(HeatID, TreatID, Plant) )                
      {
        pIntfEAF->setAimBascy(m_pHD_GRADE_SINGLE_AIMS->getAIMBASCY(1));
      }

      // mrut 2014-03-07 work on Jira SMPJSWTWO-50, SMPJSWTWO-71
      // code to be verfied against data base
      // code is similar to code in .. set_Hot_heel_data

         std::string prodOrder = "";
         double AimHotMetal = -1;

          if (m_pPD_HEAT_DATA->isNull(CPD_HEAT_DATA::PRODORDERID_ACT, 1)) 
            prodOrder = m_pPD_HEAT_DATA->getPRODORDERID_PLAN(1);
          else         
            prodOrder = m_pPD_HEAT_DATA->getPRODORDERID_ACT(1);

          // mrut 2014-12-10 code to read aim hot metal weight within aim data
          // ********************************
          // HOT METAL WEIGHT
          // ********************************
           
          if(m_pPP_ORDER_SINGLE_AIMS->select(prodOrder,Plant,1, DEF_GC_PP_ORDER_SINGLE_AIMS::LIQADD) )
          {
            AimHotMetal = CDataConversion::StringToDouble(m_pPP_ORDER_SINGLE_AIMS->getVALUE(1));
            //pIntfEAF->setAimHotMetalMass(AimHotMetal);  //sars not compiling
          }


      RetValue = true;

    } 
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", Function.c_str(), ""  );    
  } 

  return RetValue;
}

//##ModelId=4200DE3B02CA
bool CEAFModelWrapper::sequence_set_tap_ladle_data(const std::string& HeatID, const std::string& TreatID, const std::string& Plant)
{
  bool RetValue = false;

  std::string Function = "CEAFModelWrapper::sequence_set_tap_ladle_data()" ;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !checkDBConnection()) 
  {
    log("Error " + Function + " , (pIntfEAF || checkDBConnection()) == false", 1);
    return RetValue;
  }
  else
  {
    log(Function, 3);
  }


  std::string LadleType;
  long  LadleNo = -1;
  std::string TempStatus;

  try 
  { 
    if (m_pPD_HEAT_DATA->select(HeatID, TreatID,Plant)) 
    {
      LadleType = m_pPD_HEAT_DATA->getLADLETYPE(1);
      LadleNo   = m_pPD_HEAT_DATA->getLADLENO(1);

      // Ladle Data. The Ladle Id is Ladletype + LadleNo
      pIntfEAF->setTapLadleId(LadleType + CDataConversion::LongToString(LadleNo) );              

      if (m_pPD_LADLE->select(LadleNo, LadleType)) 
      {
        TempStatus = m_pPD_LADLE->getTHERMALSTATUS(1);
        if (TempStatus == DEF_GC_THERM_STAT::C)                     // "C" stands for 'cold' ladle and means 'high' initial energy loss 
          pIntfEAF->setTapLadleTempLossStat(CTempLossStat::High);
        else if (TempStatus == DEF_GC_THERM_STAT::H)                // "H" for 'hot' ladle 
          pIntfEAF->setTapLadleTempLossStat(CTempLossStat::Low);
        else 
          pIntfEAF->setTapLadleTempLossStat(CTempLossStat::Medium);

        long SAMPLE_REF = CSMC_DBData::unspecLong;
        long PRETREAT_CNT_PREV  = m_pPD_LADLE->getPRETREAT_CNT_PREV(1);
        if ( ( PRETREAT_CNT_PREV != CSMC_DBData::unspecLong ) && ( m_pPD_PRETREATDATA->select(PRETREAT_CNT_PREV)))
        {
          pIntfEAF->setTapLadleIniSteelWgt(m_pPD_PRETREATDATA->getSTEELWEIGHT(1));
          pIntfEAF->setTapLadleIniSlagWgt(m_pPD_PRETREATDATA->getSLAGWEIGHT(1));
          SAMPLE_REF    = m_pPD_PRETREATDATA->getSAMPLE_REF(1);
        }

        if( (SAMPLE_REF != CSMC_DBData::unspecLong) && (m_pPD_SAMPLE_REF->select(SAMPLE_REF) ) )
        {
          long lSteel = m_pPD_SAMPLE_REF->getSTEEL(1);
          long lSlag = m_pPD_SAMPLE_REF->getSLAG(1);
          long lTemp = m_pPD_SAMPLE_REF->getTEMP(1);

          // update container because Eyuivalences can be added dynamically
          m_pChem_Elem_Container->init();

          if( (lTemp != CSMC_DBData::unspecLong ) && ( m_pPD_SAMPLE_ENTRY->select(lTemp,DEF_GC_MEASUREMENT_NAME::Temp)))
          {
            pIntfEAF->setTapLadleIniSteelTemp(m_pPD_SAMPLE_ENTRY->getMEASVALUE(1));
          }

          if( (lSteel != CSMC_DBData::unspecLong) && ( m_pPD_SAMPLE_ENTRY->select(lSteel,CSMC_DBData::unspecString)))
          {
            for ( long i = 1 ; i <= m_pPD_SAMPLE_ENTRY->getLastRow(); ++i )
            {
              if (m_pChem_Elem_Container->isSteelElem(m_pPD_SAMPLE_ENTRY->getMEASNAME(i))) 
              {
                pIntfEAF->setTapLadleIniSteelAna(m_pPD_SAMPLE_ENTRY->getMEASNAME(i),m_pPD_SAMPLE_ENTRY->getMEASVALUE(i));
              }
            }
          }

          if( (lSlag != CSMC_DBData::unspecLong) && (m_pPD_SAMPLE_ENTRY->select(lSlag,CSMC_DBData::unspecString)))
          {
            for ( long i = 1 ; i <= m_pPD_SAMPLE_ENTRY->getLastRow(); ++i )
            {
              if (m_pChem_Elem_Container->isSlagElem(m_pPD_SAMPLE_ENTRY->getMEASNAME(i))) 
              {
                pIntfEAF->setTapLadleIniSlagAna(m_pPD_SAMPLE_ENTRY->getMEASNAME(i),m_pPD_SAMPLE_ENTRY->getMEASVALUE(i));
              }
            }
          }
        }


      }

      RetValue = true;
    }

  } 
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", Function.c_str(), ""  );    
  } 


  return RetValue;
}


//##ModelId=4200DE3C0072
bool CEAFModelWrapper::sequence_set_hot_heel_data(const std::string& HeatID, const std::string& TreatID, const std::string& Plant, long PlantNo)
{
  bool RetValue = false;
  std::string Function = "CEAFModelWrapper::sequence_set_hot_heel_data()" ;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !checkDBConnection()) 
  {
    log("Error " + Function + " , (pIntfEAF || checkDBConnection()) == false", 1);
    return RetValue;
  }
  else
  {
    log(Function, 3);
  }

  try 
  { 
      if (m_pPD_HOTHEEL->select(Plant, PlantNo)) 
      {
        double steelMass = m_pPD_HOTHEEL->getSTEELMASS(1);
        double slagMass = m_pPD_HOTHEEL->getSLAGMASS(1);
        long sampleRef = m_pPD_HOTHEEL->getSAMPLE_REF(1);

        if((steelMass == 0) && (slagMass == 0))
        {
          return true;
        }

        if(steelMass != CSMC_DBData::unspecDouble)
          pIntfEAF->setHotHeelSteelMass(steelMass);  //model needs unit as kg

        if(slagMass != CSMC_DBData::unspecDouble)
          pIntfEAF->setHotHeelSlagMass(slagMass);  //model needs unit as kg
  

        if( (sampleRef != CSMC_DBData::unspecLong) && (m_pPD_SAMPLE_REF->select(sampleRef) ) )
        {
          long lSteel = m_pPD_SAMPLE_REF->getSTEEL(1);
          long lSlag = m_pPD_SAMPLE_REF->getSLAG(1);
          long lTemp = m_pPD_SAMPLE_REF->getTEMP(1);

          // update container because Eyuivalences can be added dynamically
          m_pChem_Elem_Container->init();

          if( (lTemp != CSMC_DBData::unspecLong ) && ( m_pPD_SAMPLE_ENTRY->select(lTemp,DEF_GC_MEASUREMENT_NAME::Temp)))
          {
            pIntfEAF->setHotHeelTemp(m_pPD_SAMPLE_ENTRY->getMEASVALUE(1));
          }

          if( (lSteel != CSMC_DBData::unspecLong) && ( m_pPD_SAMPLE_ENTRY->select(lSteel,CSMC_DBData::unspecString)))
          {
            for ( long i = 1 ; i <= m_pPD_SAMPLE_ENTRY->getLastRow(); ++i )
            {
              if (m_pChem_Elem_Container->isSteelElem(m_pPD_SAMPLE_ENTRY->getMEASNAME(i))) 
              {
                pIntfEAF->setHotHeelAnl(m_pPD_SAMPLE_ENTRY->getMEASNAME(i),m_pPD_SAMPLE_ENTRY->getMEASVALUE(i));
              }
            }
          }

          if( (lSlag != CSMC_DBData::unspecLong) && (m_pPD_SAMPLE_ENTRY->select(lSlag,CSMC_DBData::unspecString)))
          {
            for ( long i = 1 ; i <= m_pPD_SAMPLE_ENTRY->getLastRow(); ++i )
            {
              if (m_pChem_Elem_Container->isSlagElem(m_pPD_SAMPLE_ENTRY->getMEASNAME(i))) 
              {
                pIntfEAF->setHotHeelAnl(m_pPD_SAMPLE_ENTRY->getMEASNAME(i),m_pPD_SAMPLE_ENTRY->getMEASVALUE(i));
              }
            }
          }
        }

        if (m_pPD_HEAT_DATA->select(HeatID, TreatID, Plant)) 
        {
          std::string prodOrder = "";
          double aimHotHeel = -1;

          if (m_pPD_HEAT_DATA->isNull(CPD_HEAT_DATA::PRODORDERID_ACT, 1)) 
            prodOrder = m_pPD_HEAT_DATA->getPRODORDERID_PLAN(1);
          else         
            prodOrder = m_pPD_HEAT_DATA->getPRODORDERID_ACT(1);


          if(m_pPP_ORDER_SINGLE_AIMS->select(prodOrder,Plant,1,DEF_GC_PP_ORDER_SINGLE_AIMS::AIMHOTHEEL))
          {
            aimHotHeel = CDataConversion::StringToDouble(m_pPP_ORDER_SINGLE_AIMS->getVALUE(1));
            pIntfEAF->focusOnStatus(CTreatStatCodes::FinalInVessel);
            pIntfEAF->setAimMass(aimHotHeel);
          }

        }

        RetValue = true;

      } 

    }
    catch (...)
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "", Function.c_str(), ""  );    
    } 

  
  return RetValue;
}


//##ModelId=45EBDA3C02DB
bool CEAFModelWrapper::sequence_update_hot_heel_data(const std::string& HeatID, const std::string& TreatID, const std::string& Plant, long PlantNo, double SteelMass, double SlagMass, double Temperature)
{
  bool RetValue = false;

  std::string Function = "CEAFModelWrapper::sequence_update_hot_heel_data()" ;

  if (!checkDBConnection()) 
  {
    log("Error " + Function + " , (checkDBConnection()) == false", 1);
    return RetValue;
  }
  else
  {
    log(Function, 3);
  }

  try 
  {
    m_pPD_HOTHEEL->setHEATID    (HeatID);
    m_pPD_HOTHEEL->setTREATID   (TreatID);
    m_pPD_HOTHEEL->setPLANT     (Plant);
    m_pPD_HOTHEEL->setPLANTNO   (PlantNo);

    m_pPD_HOTHEEL->setSTEELMASS (SteelMass);
    m_pPD_HOTHEEL->setSLAGMASS  (SlagMass);

    if (m_pPD_HOTHEEL->select(Plant,PlantNo)) 
    {
      RetValue = m_pPD_HOTHEEL->update();   
    }
    else
    {
      RetValue = m_pPD_HOTHEEL->insert();  
    }

    if (RetValue)  m_pPD_HOTHEEL->commit();

  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", Function.c_str(), ""  );    
  } 

  return RetValue;
}


//##ModelId=4200DE3C01E5
bool CEAFModelWrapper::sequence_set_liquid_material_data(const std::string& HeatID, const std::string& TreatID, long TreatNo, long rowNum, const std::string& PlantID)
{
  bool RetValue = false;
  std::string Function = "CEAFModelWrapper::sequence_set_liquid_material_data()" ;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !checkDBConnection()) 
  {
    log("Error " + Function + " , (pIntfEAF  || checkDBConnection()) == false", 1);
    return RetValue;
  }
  else
  {
    log(Function, 3);
  }

  try 
  {
    std::string ThermStatus;
    std::stringstream LadleId;
    long LiqAddNo = 1;

    LadleId     << m_pPD_HEAT_DATA_LIQADD->getLADLETYPE(rowNum);
    LadleId     << m_pPD_HEAT_DATA_LIQADD->getLADLENO(rowNum);
    ThermStatus = m_pPD_HEAT_DATA_LIQADD->getTHERMALSTATUS(rowNum);
    LiqAddNo    = m_pPD_HEAT_DATA_LIQADD->getLIQADDNO(rowNum);

    if ( ThermStatus == DEF_GC_THERM_STAT::H )
      ThermStatus = CTempLossStat::Low;
    else if ( ThermStatus == DEF_GC_THERM_STAT::C )
      ThermStatus = CTempLossStat::High;
    else
      ThermStatus = CTempLossStat::Medium;

    // is information used in the model?
    pIntfEAF->setLadleData(LadleId.str(), ThermStatus); 

    pIntfEAF->setSteelMass(m_pPD_HEAT_DATA_LIQADD->getSTEELWEIGHT(rowNum));

    pIntfEAF->setSlagMass(m_pPD_HEAT_DATA_LIQADD->getSLAGWEIGHT(rowNum));


    pIntfEAF->setResidenceTimeInLadle(0.0);

    long SAMPLE_REF = m_pPD_HEAT_DATA_LIQADD->getSAMPLE_REF(rowNum);
    if( (SAMPLE_REF != CSMC_DBData::unspecLong) && (m_pPD_SAMPLE_REF->select(SAMPLE_REF) ) )
    {
      long lSteel = m_pPD_SAMPLE_REF->getSTEEL(1);
      long lSlag = m_pPD_SAMPLE_REF->getSLAG(1);
      long lTemp = m_pPD_SAMPLE_REF->getTEMP(1);

      // update container because Eyuivalences can be added dynamically
      m_pChem_Elem_Container->init();

      if ( (lTemp != CSMC_DBData::unspecLong) && m_pPD_SAMPLE->select(lTemp))
      {
        CDateTime Now;
        double SampleTime = CDateTime::subTimes(m_pPD_SAMPLE->getSAMPLETIME(1), Now).asSeconds();           
        pIntfEAF->setSteelTempTime(SampleTime/60);
      }
      else
      {
        pIntfEAF->setSteelTempTime(0.0);
      }


      if( (lTemp != CSMC_DBData::unspecLong ) && ( m_pPD_SAMPLE_ENTRY->select(lTemp,DEF_GC_MEASUREMENT_NAME::Temp)))
      {
        pIntfEAF->setSteelTemp(m_pPD_SAMPLE_ENTRY->getMEASVALUE(1));
      }

      if( (lSteel != CSMC_DBData::unspecLong) && ( m_pPD_SAMPLE_ENTRY->select(lSteel,CSMC_DBData::unspecString)))
      {
        for ( long i = 1 ; i <= m_pPD_SAMPLE_ENTRY->getLastRow(); ++i )
        {
          if (m_pChem_Elem_Container->isSteelElem(m_pPD_SAMPLE_ENTRY->getMEASNAME(i))) 
          {
            pIntfEAF->setAnlArr(m_pPD_SAMPLE_ENTRY->getMEASNAME(i),m_pPD_SAMPLE_ENTRY->getMEASVALUE(i));
          }
        }
      }

      if( (lSlag != CSMC_DBData::unspecLong) && (m_pPD_SAMPLE_ENTRY->select(lSlag,CSMC_DBData::unspecString)))
      {
        for ( long i = 1 ; i <= m_pPD_SAMPLE_ENTRY->getLastRow(); ++i )
        {
          if (m_pChem_Elem_Container->isSlagElem(m_pPD_SAMPLE_ENTRY->getMEASNAME(i))) 
          {
            pIntfEAF->setAnlArr(m_pPD_SAMPLE_ENTRY->getMEASNAME(i),m_pPD_SAMPLE_ENTRY->getMEASVALUE(i));
          }
        }
      }
    }
    else
    {
      std::stringstream SearchKey;
      SearchKey << HeatID << " ," << TreatID << " ," << PlantID << " ," << LiqAddNo;
      log("No sample ref in PD_HEAT_DATA_LIQADD->getSAMPLE_REF",0);
    }


    RetValue = true;
  } 
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", Function.c_str(), ""  );    
  }

  return RetValue;
}



//##ModelId=4200DE3D03BD
bool CEAFModelWrapper::sequence_set_plant_status(const std::string& HeatID, const std::string& TreatID)
{
  bool RetValue = false;

  // axho: data tables are not yet implemented 
  // TODO: Add your specialized code here.

  return RetValue;
}

//##ModelId=45EBDA3D02E9
bool CEAFModelWrapper::sequence_set_plant_status(const std::string& HeatID, const std::string& TreatID, DM::iDM_Interface_var& pDM_Interface, const std::string& DataKey)
{
  bool RetValue = false;

  std::string Function = "CEAFModelWrapper::sequence_set_plant_status()" ;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !checkDBConnection() || !pDM_Interface) 
  {
    log("Error: " + Function + " , (pIntfEAF || checkDBConnection()||pDM_Interface) == false", 1);
    return RetValue;
  }
  else
  {
    log(Function, 3);
  }

  try 
  {
    // mrut 2014-04-10 -- Jira JSPLANG-96 (JSL is also affected)
    bool IsDuringInitialisation = false;

    std::string ModelSteelGradeCode;
    std::string ModelTreatID;
    std::string ModelHeatID;

    pIntfEAF->getHeatData(ModelHeatID, ModelTreatID, ModelSteelGradeCode);

    if (  CInv::InvalidString !=  ModelHeatID  )
    {
      std::string ActPhase = pIntfEAF->getActualProcessPhase();

      log("ModelHeatID : " + ModelHeatID + " ActPhase : " + ActPhase,3);

      std::set <string> ValueSet;
      CProcPhaseCodesEAF::getValues(ValueSet);
      
      IsDuringInitialisation = (ValueSet.find(ActPhase) == ValueSet.end());                // no valid process phase yet. proberly not initialised yet

      /*if (ValueSet.find(ActPhase) != ValueSet.end())  //@SANKAR as per Jesper
      {
        log( "in this case, we can skip the processing, we are in a defined state already, it seems that at least one heat announcement allready has happened." ,3);
        return true;                         
      }*/
    }

    long FurnTapChangOn       = pDM_Interface->getLong(DataKey.c_str(), DATA::FurnTapChangOn);
    long ReactTapNo           = pDM_Interface->getLong(DataKey.c_str(), DATA::ReactTapNo);
    long VoltTapNo            = pDM_Interface->getLong(DataKey.c_str(), DATA::VoltTapNo);
    long EltrdRegCurve        = pDM_Interface->getLong(DataKey.c_str(), DATA::ElectrodRegCurve);
    long FurnBreakOn          = pDM_Interface->getLong(DataKey.c_str(), DATA::FurnBreakOn);
    long PowerOn              = pDM_Interface->getLong(DataKey.c_str(), DATA::PowerOn);

    long ElecPosUp            = pDM_Interface->getLong(DataKey.c_str(), DATA::ElecPosUp);
    long GantryPosIn          = pDM_Interface->getLong(DataKey.c_str(), DATA::GantryPosIn);

    long RoofPosUp            = pDM_Interface->getLong(DataKey.c_str(), DATA::RoofPosUp);
    long SlagDoorOpen         = pDM_Interface->getLong(DataKey.c_str(), DATA::SlagDoorOpen);


    std::string FurnaceStatus  = CIntfData::ToStdString(pDM_Interface->getString(DataKey.c_str(), DATA::FurnaceStatus));
    long DoYouLookThatOld =  pDM_Interface->getLong(DataKey.c_str(), DATA::FurnaceLife);

    if (FurnaceStatus == DEF_GC_THERM_STAT::C)     
      FurnaceStatus = CTempLossStat::High;
    else if (FurnaceStatus == DEF_GC_THERM_STAT::H)  
      FurnaceStatus = CTempLossStat::Low;
    else if (FurnaceStatus == DEF_GC_THERM_STAT::M) 
      FurnaceStatus = CTempLossStat::Medium;
    else
    {
      //external tracking for thermal status is required. if there is no status the model track it by itself.
      FurnaceStatus = CInv::InvalidString;
    }

    seqComputerModes SeqComputerModes = CIntfData::ToCORBAType(pDM_Interface->getComputerModes(DataKey.c_str(), DATA::ComputerModes));

    pIntfEAF->indicatePlantStatus();

    if (0!=FurnTapChangOn)
      pIntfEAF->hndlTapChgStart();
    else
      pIntfEAF->hndlTapChgEnd(VoltTapNo);


    if (CInv::InvalidLong != ReactTapNo && ReactTapNo >= 0)
    {
      // 2014-04-10 mrut
      // Using an existing method with manipulated parameter values
      // for the sake of compatibility between different projects -
      // allowing an update of model-kernel without a changed interface.
      pIntfEAF->hndlTapChgEnd (- ReactTapNo);
    }


    if (CInv::InvalidLong != EltrdRegCurve)
      pIntfEAF->hndlNewEltrdReguCurve(EltrdRegCurve);

    if (0!=FurnBreakOn)
      pIntfEAF->hndlFurnBrkrOn();

    if (0!=PowerOn)
      pIntfEAF->hndlPowerOn();
    else
      pIntfEAF->hndlPowerOff();

    //if (0 == ElecPosUp)                     // error !
    if (0 != ElecPosUp)
      pIntfEAF->hndlElectrodeLifted();
    else
      pIntfEAF->hndlElectrodesInOpPos();


    if (0!=GantryPosIn)
      pIntfEAF->hndlGantryPosIn();
    else
      pIntfEAF->hndlGantryPosOut();


    if (0!=SlagDoorOpen)
      pIntfEAF->hndlDoorOpen();
    else
      pIntfEAF->hndlDoorClosed();

    if(0 != RoofPosUp)
      pIntfEAF->hndlRoofPosUp();
    else
      pIntfEAF->hndlRoofPosDown();

    if ( (CInv::InvalidLong != DoYouLookThatOld)&& (0 <= DoYouLookThatOld) )
      pIntfEAF->setNoOfHeatsSinceLastRelining(DoYouLookThatOld);
    
    if ( (CInv::InvalidString != FurnaceStatus) && (!FurnaceStatus.empty()))
      pIntfEAF->setFurnStatus(FurnaceStatus);

    const CCfgEAF * pCfgEAF =  getpCfgEAF();
    const map<string, long> & CtrlSystemMap = pCfgEAF->getCtrlSystemSetptTyp();
          map<string, long>::const_iterator  CtrlSystemItEnd (CtrlSystemMap.end());
          map<string, long>::const_iterator  CtrlSystemIt    (CtrlSystemItEnd);

    for (int x = 0; x < CIntfData::getLength(SeqComputerModes); ++x) 
    {
      sComputerMode  ComputerMode;

      CIntfData::getAt(ComputerMode, SeqComputerModes, x);

      bool Status         = ComputerMode.Status == DEF_GC_COMP_STATUS::ComputerDynamicMode;
      std::string Device  = ComputerMode.Device;
      std::string CtrlSystemCode;
    
      if (Device == DEF_COMP_MODES::Electric )
      {
        CtrlSystemCode  = CCtrlSystemCodesEAF::Elec;
        Status          = (ComputerMode.Status == DEF_GC_COMP_STATUS::ComputerDynamicMode) || (ComputerMode.Status == DEF_GC_COMP_STATUS::ComputerPatternMode);
      }
      else if (Device == DEF_COMP_MODES::GasLance )
      {
            CtrlSystemIt    = CtrlSystemMap.find (CCtrlSystemCodesEAF::ManipGasLance);
        if (CtrlSystemIt   != CtrlSystemItEnd &&  CtrlSystemIt->second > 0)
            CtrlSystemCode  = CCtrlSystemCodesEAF::ManipGasLance;            // it is 'gas lance'
        else
            CtrlSystemCode  = CCtrlSystemCodesEAF::ManipOxygenLance;         // it is 'oxygen lance'

        Status          = (ComputerMode.Status == DEF_GC_COMP_STATUS::ComputerDynamicMode) || (ComputerMode.Status == DEF_GC_COMP_STATUS::ComputerPatternMode);
      }
      else if (Device == DEF_COMP_MODES::DynamicFeed )
      {
        CtrlSystemCode  = CCtrlSystemCodesEAF::BinMatDynFeed;
        Status          = (ComputerMode.Status == DEF_GC_COMP_STATUS::ComputerDynamicMode) || (ComputerMode.Status == DEF_GC_COMP_STATUS::ComputerPatternMode);
      }
      else if (Device == DEF_COMP_MODES::PatternFeed)
      {
        CtrlSystemCode  = CCtrlSystemCodesEAF::BinMatPatternFeed;
      }
      else if ( (Device == DEF_COMP_MODES::MatHandle) ||  (Device == DEF_COMP_MODES::TappingBatch) )
      {
        CtrlSystemCode  = CCtrlSystemCodesEAF::BatchMatHndlg;         //ups: not a 1:1 relation ?
      }
      else if (Device == DEF_COMP_MODES::Burner)
      {
        CtrlSystemCode  = CCtrlSystemCodesEAF::Burner;
      }
      else if (Device == DEF_COMP_MODES::Injection)  //
      {
        // 2014-04-10 mrut : to do : distinguish properly between C-lance(s) and other (different) lances.
        //                   for now , give preference to C-lance.
        //
        //    CtrlSystemIt    = CtrlSystemMap.find (CCtrlSystemCodesEAF::ManipInjectLance);
        //if (CtrlSystemIt   != CtrlSystemItEnd &&  CtrlSystemIt->second > 0)
        //    CtrlSystemCode  = CCtrlSystemCodesEAF::ManipInjectLance; 
        //else
        //    CtrlSystemCode  = CCtrlSystemCodesEAF::CarbonLance; 
 
            CtrlSystemIt    = CtrlSystemMap.find (CCtrlSystemCodesEAF::CarbonLance);
        if (CtrlSystemIt   != CtrlSystemItEnd &&  CtrlSystemIt->second > 0)
            CtrlSystemCode  = CCtrlSystemCodesEAF::CarbonLance; 
        else
            CtrlSystemCode  = CCtrlSystemCodesEAF::ManipInjectLance; 
      }
      else if (Device == DEF_COMP_MODES::Stirring)
      {
        CtrlSystemCode  = CCtrlSystemCodesEAF::BottomStirringDevice;
      }
      else
        continue;

      if ( !CtrlSystemCode.empty() )
      {
            CtrlSystemIt  = CtrlSystemMap.find (CtrlSystemCode);
        if (CtrlSystemIt != CtrlSystemItEnd && CtrlSystemIt->second > 0)
        {
          pIntfEAF->setCompuModeOnOrOff(CtrlSystemCode, Status && !IsDuringInitialisation);     // mrut 2014-04-10 -- Jira JSPLANG-96 (JSW is also affected)
        }
      }
    }

    if( isModelDevice(CCtrlSystemCodesEAF::WTC) ) 
    {	
      pIntfEAF->actvWallTempCtrl();
    }

    long CanWeHandleIt = pIntfEAF->hndlPlantStatus();

    RetValue = (CRS::OK == CanWeHandleIt);

  } 
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", Function.c_str(), ""  );    
  } 
  
  return RetValue;
}

bool CEAFModelWrapper::setNoOfBasket(CEventMessage &Event)
{
  bool RetValue = true;  

  std::string Function = "CEAFModelWrapper::setNoOfBasket()";

  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  if (!checkDBConnection())
  {
    log("Error: " + Function + " , (checkDBConnection()) == false", 1);
    return false;
  }
  else
  {
    log(Function, 3);
  }

  m_NumberOfBasketsForHeat = 0;
  if(m_pPD_SCRAP_CONTAINER_ORDER->select(ActPlant,Event.getOrderID(),CSMC_DBData::unspecLong))
  {
    for (int i=1; i <= m_pPD_SCRAP_CONTAINER_ORDER->getLastRow(); ++i) 
    {
      m_NumberOfBasketsForHeat++;
    }
  }

  return RetValue;

}

//##ModelId=4200DE44006A
bool CEAFModelWrapper::sequence_set_basket_data(const std::string& HeatID, const std::string& TreatID,CEventMessage &Event)
{
  bool RetValue = false;
  bool IsBasketSet = false;  

  std::string Function = "CEAFModelWrapper::sequence_set_basket_data()" ;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !checkDBConnection()) 
  {
    log("Error: " + Function + " , (pIntfEAF || checkDBConnection()) == false", 1);
    return RetValue;
  }
  else
  {
    log(Function, 3);
  }

  RetValue = true;


  //added handling of message for change of treament-map
  // if this sequence is called as a part of event-handling for heat anouncement or change of treatment-mode,
  // this sequence is part of something bigger.. We must not create an own event then.
  bool IndependentUseCase =  (EAF_EvMsg::evEAFHeatAnnouncement    != Event.getMessage())
                          && (EAF_EvMsg::evEAFChangeTreatmentMode != Event.getMessage());

  try 
  {
    std::string PlantID   = Event.getPlantID();
    std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
    long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

    if ( Event.getOrderID() != DEF::Inv_String )
    {
      if(m_pPD_SCRAP_CONTAINER_ORDER->select(ActPlant,Event.getOrderID(),CSMC_DBData::unspecLong))
      {
        for (int i=1; i <= m_pPD_SCRAP_CONTAINER_ORDER->getLastRow(); ++i) 
        {
            long ContainerSeq         = m_pPD_SCRAP_CONTAINER_ORDER->getCONTAINERINSEQ(i);
            long ContainerNo          = m_pPD_SCRAP_CONTAINER_ORDER->getCONTAINERNO(i);
            long ContainerLast        = m_pPD_SCRAP_CONTAINER_ORDER->getCONTAINERLAST(i);       
            std::string ContainerType = m_pPD_SCRAP_CONTAINER_ORDER->getCONTAINERTYPE(i);

            long STATUSNO        = m_pPD_SCRAP_CONTAINER_ORDER->getSTATUSNO(i);

            if(ContainerNo == CSMC_DBData::unspecLong || STATUSNO < DEF_GC_SCRAP_CONT_ORDER_STATUS::LoadingEnded )
            {
              if(m_pPD_SCRAP_CONTAINER_ORDER_ENTRY->select(ActPlant,Event.getOrderID(),ContainerSeq,CSMC_DBData::unspecLong))
              {
                if ( RetValue  )
                {
                  if ( IndependentUseCase )
                  {
                    pIntfEAF->indicateBasketData(); 
                  }

                  pIntfEAF->setBasketNo( ContainerSeq );
                  pIntfEAF->setBasketLast(ContainerLast == 1);

                  for(int j=1; j <= m_pPD_SCRAP_CONTAINER_ORDER_ENTRY->getLastRow(); ++j)
                  {
                    std::string sCode = m_pPD_SCRAP_CONTAINER_ORDER_ENTRY->getMAT_CODE(j);
                    double   dWgt     = m_pPD_SCRAP_CONTAINER_ORDER_ENTRY->getMATWEIGHT(j); 

                    if ( CRS::OK == pIntfEAF->setBasketMat(sCode, dWgt) )
                    {
                      IsBasketSet = true;
                    }
                  }

                  if ( IndependentUseCase )
                  {
                    RetValue  = doHandleEvent();  
                  }
                }//  if ( RetValue  )
              } // if(m_pPD_SCRAP_CONTAINER_ORDER_ENTRY->select(ActPlant,Event.getOrderID(),ContainerSeq,CSMC_DBData::unspecString))
            }
            else if(m_pPD_SCRAP_CONTAINER_ENTRY->select(ContainerNo,ContainerType,CSMC_DBData::unspecLong))
            {
              if ( RetValue )
              {
                if ( IndependentUseCase )
                {
                  pIntfEAF->indicateBasketData();
                }

                pIntfEAF->setBasketNo( ContainerSeq );
                pIntfEAF->setBasketLast(ContainerLast == 1);

                for(int j=1; j <= m_pPD_SCRAP_CONTAINER_ENTRY->getLastRow(); ++j)
                {
                  std::string sCode = m_pPD_SCRAP_CONTAINER_ENTRY->getMAT_CODE(j);
       
                  double   dWgt     = m_pPD_SCRAP_CONTAINER_ENTRY->getMATWEIGHT(j);

                  if ( dWgt == CSMC_DBData::unspecDouble || dWgt == 0. )
                  {
                    dWgt = m_pPD_SCRAP_CONTAINER_ENTRY->getMATWEIGHT_CHARGED(j);
                  }

                  if ( CRS::OK == pIntfEAF->setBasketMat(sCode, dWgt) )
                  {
                    IsBasketSet = true;
                  }
                }

                if ( IndependentUseCase )
                {
                  RetValue  = doHandleEvent();  
                }

              }
            }//else if(...)
       
        } // end of for(..)

        if( IsBasketSet && IndependentUseCase ) 
        { 
          RetValue &= doModelResult(Event);
        }

      }
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_InconsistentDataReceived(sMessage, "OrderId", Event.getMessage().c_str());
    }

  }// end try

  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", Function.c_str(), ""  );    
  } 

  return RetValue;
}


//##ModelId=4200DE3E016F
bool CEAFModelWrapper::sequence_set_all_heat_related_production_practice_data (const std::string& HeatID, const std::string& TreatID, const std::string& Plant, long PlantNo)
{
  bool RetValue = true;


  // recipe restrictions are mandatory
  RetValue &= sequence_set_production_practice_data_recipe_ctrl           ( HeatID, TreatID, Plant, PlantNo);

  // electricity is mandatory
  RetValue &= sequence_set_production_practice_data_electric              ( HeatID, TreatID, Plant);


  const CCfgEAF * pCfgEAF =  getpCfgEAF();
  const map<string, long> & CtrlSystemMap = pCfgEAF->getCtrlSystemSetptTyp();      
        map<string, long>::const_iterator   CtrlSystemItEnd (CtrlSystemMap.end());

  //does model support pattern feeding?
  if (CtrlSystemMap.find (CCtrlSystemCodesEAF::BinMatPatternFeed) != CtrlSystemItEnd)
      RetValue &= sequence_set_production_practice_data_pattern_feeding     ( HeatID, TreatID, Plant);


  //does model support burner?
  if ( isModelDevice(CCtrlSystemCodesEAF::Burner) )
    RetValue &= sequence_set_production_practice_data_burner                ( HeatID, TreatID, Plant, PlantNo);
  // what about oxgen side-lances?

  //does model support jet modules?
  if ( isModelDevice(CCtrlSystemCodesEAF::JetModule) )
    RetValue &= sequence_set_production_practice_data_jet_module            ( HeatID, TreatID, Plant, PlantNo);

  //does model support injection lances?
  if (!(pCfgEAF->getSetOfInjectionPurposes().empty()) )
    RetValue &= sequence_set_production_practice_data_injection             ( HeatID, TreatID, Plant, PlantNo);

  //does model support gas lances?
  // next line due to JSPL?
  // 5 O2-lances handled by burner interface (O2-side-lances), referenced by CMeasConsCodesEAF::OxygenLance
  //
  //if ( isModelDevice(CCtrlSystemCodesEAF::ManipOxygenLance) )
  //
  if ( isModelDevice(CCtrlSystemCodesEAF::ManipGasLance) ||          // both are adressing gas-lances, only the name is different.
       isModelDevice(CCtrlSystemCodesEAF::ManipOxygenLance) )   
    RetValue &= sequence_set_production_practice_data_manipulator_gas_lance ( HeatID, TreatID, Plant); 

  //does model support bottom stirring?
  if ( isModelDevice(CCtrlSystemCodesEAF::BottomStirringDevice) )
    RetValue &= sequence_set_production_practice_data_bottom_stirring       ( HeatID, TreatID, Plant);

  return RetValue;
}


//##ModelId=4200DE3F0026
bool CEAFModelWrapper::sequence_set_production_practice_data_burner(const std::string& HeatID, const std::string& TreatID, const std::string& Plant, long PlantNo)
{
  bool RetValue     = false;

  std::string Function = "CEAFModelWrapper::sequence_set_production_practice_data_burner()" ;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !checkDBConnection()) 
  {
    log("Error: " + Function + " , (pIntfEAF || checkDBConnection()) == false", 1);
    return RetValue;
  }
  else
  {
    log(Function, 3);
  }

  RetValue = true;
  
  #if defined (EAF_BURNER)      
    std::string tempPracPhase, thisPracPhase;

    try 
    {
      ////EAFPracticePattern   BurnerPractice;            // not used ony more - was done for PNTZ

      long BurnerDataStatus = 0;
      long TreatmentModeNo  = getTreatmentModeNo(HeatID, TreatID, Plant);
      long ProdPracPt       = getProdPracticePointer(HeatID, TreatID, Plant, DEF_GC_PRODPRAC_DEF::Burner);

      if (m_pHDE_PP_BURNER_STEP_ENTRY->selectOrdered(HeatID, TreatID, Plant, ProdPracPt,TreatmentModeNo,CSMC_DBData::unspecLong,CSMC_DBData::unspecString,CSMC_DBData::unspecString,CSMC_DBData::unspecLong) )  
      {
        std::string GasType   = CInv::InvalidString;
        double      FlowVal   = CInv::InvalidDouble;
        double      StepEgy   = CInv::InvalidDouble;
        long        DeviceNo  = CInv::InvalidLong;

        std::string CurrentPracPhase = "zzzzzzzzz";
        long focusOnPracPhaseSuccess = CRS::OK;

        pIntfEAF->focusOnBurnerData();
        pIntfEAF->setProdPracPtBurner(ProdPracPt);

        for (int i = 1; i <= m_pHDE_PP_BURNER_STEP_ENTRY->getLastRow(); i++) 
        {
          thisPracPhase = m_pHDE_PP_BURNER_STEP_ENTRY->getPRACPHASE(i);
          // obsolete std::map <string , double> BurnerFlowMap;

          long DeviceNo = 0;
          if (m_pGCE_BURNER->select(Plant,PlantNo,m_pHDE_PP_BURNER_STEP_ENTRY->getBURNERNAME(i)))
          {
            DeviceNo = m_pGCE_BURNER->getL1_BURNERNO(1);
          }

          double SpecEgy = m_pHDE_PP_BURNER_STEP_ENTRY->getSPECEGY(i);       // kwh/kg
          long   ElecEgy = m_pHDE_PP_BURNER_STEP_ENTRY->getELEC_ENERGY(i);   // kwh

                 StepEgy = CDataConversion::SetInvalidToDefault (SpecEgy, (double)ElecEgy, CSMC_DBData::unspecDouble);              // model can decide if it is abs or spec

          long FlameProfileNo = m_pHDE_PP_BURNER_STEP_ENTRY->getFLAMEPROFILENO(i);

          std::string BurnerName = m_pHDE_PP_BURNER_STEP_ENTRY->getBURNERNAME(i);

          if( CurrentPracPhase != thisPracPhase )
          {
            CurrentPracPhase        = thisPracPhase;         
            focusOnPracPhaseSuccess = pIntfEAF->focusOnPracPhase(CurrentPracPhase); 
          }

          if ( CRS::OK == focusOnPracPhaseSuccess )
          {
            if (m_pHDE_PP_FLAME_PROFILE->select(HeatID, TreatID, Plant, BurnerName, FlameProfileNo))
            {
              double OxyFlow = m_pHDE_PP_FLAME_PROFILE->getOXYGENFLOW(1);
              double GasFlow = m_pHDE_PP_FLAME_PROFILE->getGASFLOW   (1);

              // we use Nm³/min internally
              //GasFlow = GasFlow/60; // unit per min 
              //OxyFlow = OxyFlow/60; // unit per min

              pIntfEAF->setPracBurnStepData( DeviceNo, StepEgy, GasFlow, OxyFlow);
            }
          }

        } //end of for(...)
      }
      else
      {
        std::stringstream Msg;
        Msg << Function << " No data for HeatID= " << HeatID << " TreatID= " << TreatID << " Plant= " << Plant << " ProdPracPt= " << ProdPracPt << " TreatmentModeNo= " << TreatmentModeNo ;   
        log(Msg.str(),2);
      }

    }
    catch(...)
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "", Function.c_str(), ""  );    
    } 

  #endif

  return RetValue;

}



bool CEAFModelWrapper::sequence_set_production_practice_data_electric(const std::string& HeatID, const std::string& TreatID, const std::string& Plant)
{
  bool RetValue    = false;

  std::string Function = "CEAFModelWrapper::sequence_set_production_practice_data_electric()" ;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !checkDBConnection()) 
  {
    log("Error: " + Function + " , (pIntfEAF || checkDBConnection()) == false", 1);
    return RetValue;
  }
  else
  {
    log(Function, 3);
  }

  RetValue = true;

  try 
  {
    std::string thisPracPhase, tempPracPhase;
    //EAFPracticePattern   ElectricPractice;           // not used ony more - was done for PNTZ

    long ElecDataStatus   = 0;
    long TreatmentModeNo  = getTreatmentModeNo(HeatID, TreatID, Plant);
    long ProdPracPointer  = getProdPracticePointer(HeatID, TreatID, Plant, DEF_GC_PRODPRAC_DEF::Process);      

    if ( (m_pHDE_PP_PROCESS_STEP_ENTRY->selectOrdered(HeatID, TreatID, Plant, ProdPracPointer, TreatmentModeNo, CSMC_DBData::unspecLong, CSMC_DBData::unspecString, CSMC_DBData::unspecLong)) && (m_pHDE_PP_PROCESS_STEP_ENTRY->getLastRow() > 0) )
    {
      double      StepEgy   = CInv::InvalidDouble;

      std::string CurrentPracPhase = "zzzzzzzzz";
      long focusOnPracPhaseSuccess = CRS::OK;

      pIntfEAF->focusOnElecData();
      pIntfEAF->setProdPracPtElec(ProdPracPointer);

     for (long j = 1; j <= m_pHDE_PP_PROCESS_STEP_ENTRY->getLastRow(); ++j )
      {
        thisPracPhase = m_pHDE_PP_PROCESS_STEP_ENTRY->getPRACPHASE(j);

        bool    StepEgyIsVariable = (m_pHDE_PP_PROCESS_STEP_ENTRY->getMODELCALC(j) > 0);
        long    VoltTap           =  m_pHDE_PP_PROCESS_STEP_ENTRY->getVOLTTAP(j);
        long    ImpCurve          =  m_pHDE_PP_PROCESS_STEP_ENTRY->getIMPCURVE(j);
        long    REACTORTAP        =  m_pHDE_PP_PROCESS_STEP_ENTRY->getREACTORTAP(j);

                REACTORTAP  = CDataConversion::SetInvalidToDefault(REACTORTAP, -1, CSMC_DBData::unspecLong);

        double  SpecEgy           = m_pHDE_PP_PROCESS_STEP_ENTRY->getSPECEGY (j);
         long   ElecEgy           = m_pHDE_PP_PROCESS_STEP_ENTRY->getELEC_ENERGY(j);

                StepEgy = CDataConversion::SetInvalidToDefault (SpecEgy, (double)ElecEgy, CSMC_DBData::unspecDouble);              // model can decide if it is abs or spec


        if (StepEgyIsVariable) StepEgy *= (-1.0);             // use negative signum to indicate variable step

        if( CurrentPracPhase != thisPracPhase )
        {
          CurrentPracPhase        = thisPracPhase;
          focusOnPracPhaseSuccess = pIntfEAF->focusOnPracPhase(CurrentPracPhase); 

          if ( CRS::OK == focusOnPracPhaseSuccess )
          {
            if ( m_pHDE_PP_PROCESS_PARAM->select(HeatID, TreatID, Plant, ProdPracPointer, TreatmentModeNo, CSMC_DBData::unspecLong, CurrentPracPhase) )
            { 
              double CorrFactBsk           = m_pHDE_PP_PROCESS_PARAM->getMELTDOWNRATEBSK(1);
              double MaxEgyWthtBskData     = m_pHDE_PP_PROCESS_PARAM->getMAXEGYWITHOUTBSKDATA(1);
              double MaxEgyWithBskData     = m_pHDE_PP_PROCESS_PARAM->getMAXEGYWITHBSKDATA(1);

              double BeginEgyWallTempCtrl  = m_pHDE_PP_PROCESS_PARAM->getBEGINEGYWALLTEMPCTRL(1);
              double MsgRemEgy             = m_pHDE_PP_PROCESS_PARAM->getREMEGY(1);
              double AimTemp               = m_pHDE_PP_PROCESS_PARAM->getAIMTEMP(1);


              if ( CorrFactBsk != CSMC_DBData::unspecDouble && CorrFactBsk != 0.)
                pIntfEAF->setCorrFactBsk(CorrFactBsk);

              if ( MaxEgyWthtBskData != CSMC_DBData::unspecDouble && MaxEgyWthtBskData != 0.)
                pIntfEAF->setMaxEgyWthtBskData( MaxEgyWthtBskData);

              if ( MaxEgyWithBskData != CSMC_DBData::unspecDouble && MaxEgyWithBskData != 0.)
                pIntfEAF->setMaxEgyBsk( MaxEgyWithBskData);                    

              if ( BeginEgyWallTempCtrl != CSMC_DBData::unspecDouble && BeginEgyWallTempCtrl != 0.)
                pIntfEAF->setBeginEgyWallTempCtrl(BeginEgyWallTempCtrl);       

              if ( MsgRemEgy != CSMC_DBData::unspecDouble && MsgRemEgy != 0.)
                pIntfEAF->setMsgRemEgy( MsgRemEgy);

              if ( AimTemp != CSMC_DBData::unspecDouble && AimTemp != 0.)
                pIntfEAF->setTargetEndTemp( AimTemp);

            } 
          }
        }

        if ( CRS::OK == focusOnPracPhaseSuccess )
        {
          if ( StepEgy    != CSMC_DBData::unspecDouble && 
               VoltTap    != CSMC_DBData::unspecLong &&
               ImpCurve   != CSMC_DBData::unspecLong )
          {
            ElecDataStatus = pIntfEAF->setPracElecStepData (StepEgy, VoltTap, ImpCurve, REACTORTAP);  
            RetValue = RetValue && (ElecDataStatus == CRS::OK);
          }
          else
          {
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_DBReadWarning(sMessage, "SPECEGY - VOLTTAP - IMPCURVE", "HDE_PP_PROCESS_STEP_ENTRY", "data not completely defined");
          }
        }

      } // end of for(...)   
    }
    else
    {
      std::stringstream Msg;
      Msg << Function << " No data for HeatID= " << HeatID << " TreatID= " << TreatID << " Plant= " << Plant << " ProdPracPointer= " << ProdPracPointer << " TreatmentModeNo= " << TreatmentModeNo ;   
      log(Msg.str(),2);
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", Function.c_str(), ""  );    
  } 
  
  return RetValue;
}

//##ModelId=4200DE410214
bool CEAFModelWrapper::sequence_set_production_practice_data_recipe_ctrl(const std::string& HeatID, const std::string& TreatID, const std::string& Plant, long PlantNo)
{
  bool RetValue     = false;  
  std::string Function = "CEAFModelWrapper::sequence_set_production_practice_data_recipe_ctrl()" ;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !checkDBConnection()) 
  {
    log("Error: " + Function + " , (pIntfEAF || checkDBConnection()) == false", 1);
    return RetValue;
  }
  else
  {
    log(Function, 3);
  }

  RetValue = true;
  
  long ProdPracPointerRestriction  = getProdPracticePointer(HeatID,TreatID, Plant, DEF_GC_PRODPRAC_DEF::Restriction);
  long ProdPracPointerPlant        = getProdPracticePointer(HeatID,TreatID, Plant, DEF_GC_PRODPRAC_DEF::Plant);
  long TreatmentModeNo             = getTreatmentModeNo(HeatID, TreatID, Plant);

  try 
  {
    const long        LiqAddNo     = CSMC_DBData::unspecLong;
    const long        LineNo       = CSMC_DBData::unspecLong;

    // model could run without any restriction !
    // section deleted - JAST
    //if (!m_pHD_RESTRI->select( HeatID, TreatID, Plant, DescrPP, ProdPracPointer, TreatmentModeNo, LiqAddNo))
    //{
    //  std::stringstream SearchKey;
    //  SearchKey << HeatID << " " << TreatID << " " << Plant << " "  << " ProdPac " << ProdPracPointer;
    //  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    //  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    //  pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.str().c_str(),"HD_RESTRI");

    //  return false;
    //}

    m_pGC_COMBI_RECIPE_ENTRY->selectByPlant(Plant);

    for (int i = 1; i <= m_pGC_COMBI_RECIPE_ENTRY->getLastRow(); i++)
    {
      const std::string CombinationName   = m_pGC_COMBI_RECIPE_ENTRY->getCOMBINATION_NAME(i);
      const std::string RecipeName        = m_pGC_COMBI_RECIPE_ENTRY->getRECIPENAME(i);
      const long        RecipeNo          = 1;
      const std::string RecipeSource      = m_pGC_COMBI_RECIPE_ENTRY->getSOURCE(i);

      std::string       RecipeNameModel;
		  long              RecipeNoModel     = 0;

      if ( m_pRecipeHandler->translateToModelRecipe(Plant, RecipeName, RecipeNo, RecipeNameModel, RecipeNoModel) )
      {
        if ( !isValidModelRecipeName(RecipeNameModel) )
        {
          continue;
        }

        // mrut 2013-11-06 recoded to avoid useless calls
        bool RecipeIsInFocus = false;


        // ******************************************************************************************
        // handling plant restrictions
        // ******************************************************************************************
        if (ProdPracPointerPlant != CInv::InvalidLong && 
            m_pHD_RESTRI_ENTRY->selectBySourceAndCombiName( HeatID, TreatID, Plant, PlantNo, DEF_GC_PRODPRAC_DEF::Plant, ProdPracPointerPlant, CSMC_DBData::unspecLong, CSMC_DBData::unspecLong, LineNo, RecipeSource, CombinationName ) )
        {      
          for (int j = 1; j <= m_pHD_RESTRI_ENTRY->getLastRow(); ++j)
          {
            std::string Mat_PurpCode;
            std::string RestriType    = m_pHD_RESTRI_ENTRY->getRESTRITYPE(j);;

            if (m_pHD_RESTRI_ENTRY->isNull(CHD_RESTRI_ENTRY::MAT_CODE, j))
            {
              Mat_PurpCode = m_pHD_RESTRI_ENTRY->getPURP_CODE(j);
            }
            else
            {
              Mat_PurpCode = m_pHD_RESTRI_ENTRY->getMAT_CODE(j);
            }

            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_HandleRestriction(sMessage, RecipeSource.c_str(), CombinationName.c_str(), Mat_PurpCode.c_str() );
            
            if (m_pGC_RESTRI_DEF->select(RestriType))
            {
              // mrut 2013-11-06 recoded to avoid useless calls
              bool MinimumGiven = (!m_pHD_RESTRI_ENTRY->isNull(CHD_RESTRI_ENTRY::RESTRI_VALMIN, j) && (m_pHD_RESTRI_ENTRY->getRESTRI_VALMIN(j) > 0.0));
              bool MaximumGiven = (!m_pHD_RESTRI_ENTRY->isNull(CHD_RESTRI_ENTRY::RESTRI_VALMAX, j) );

              if (!RecipeIsInFocus && (MinimumGiven || MaximumGiven) )
              {
                if(RecipeSource.empty() || isCombiRecipe(RecipeNameModel) )
                {
                  pIntfEAF->focusOnRecipe(RecipeNameModel,RecipeNoModel,true);
                }
                else
                {
                  pIntfEAF->focusOnRecipeOrig(RecipeNameModel,RecipeNoModel,RecipeSource,true);
                }
                RecipeIsInFocus = true;
              }

              if (MinimumGiven)
              {
                  pIntfEAF->setMatRestr(Mat_PurpCode, m_pHD_RESTRI_ENTRY->getRESTRI_VALMIN(j),m_pGC_RESTRI_DEF->getRESTRITYPEMODEL_MIN(1));
              }

              if (MaximumGiven)
              {
                pIntfEAF->setMatRestr(Mat_PurpCode, m_pHD_RESTRI_ENTRY->getRESTRI_VALMAX(j),m_pGC_RESTRI_DEF->getRESTRITYPEMODEL_MAX(1));                
              }
            }
          } // for
        } // 

        // ******************************************************************************************
        // handling material restrictions
        // ******************************************************************************************
        if (ProdPracPointerRestriction != CInv::InvalidLong && 
            m_pHD_RESTRI_ENTRY->selectBySourceAndCombiName( HeatID, TreatID, Plant, PlantNo, DEF_GC_PRODPRAC_DEF::Restriction, ProdPracPointerRestriction, TreatmentModeNo, LiqAddNo, LineNo, RecipeSource, CombinationName ) )
        {      
          for (int j = 1; j <= m_pHD_RESTRI_ENTRY->getLastRow(); ++j)
          {
            std::string Mat_PurpCode;
            std::string RestriType    = m_pHD_RESTRI_ENTRY->getRESTRITYPE(j);;

            if (m_pHD_RESTRI_ENTRY->isNull(CHD_RESTRI_ENTRY::MAT_CODE, j))
            {
              Mat_PurpCode = m_pHD_RESTRI_ENTRY->getPURP_CODE(j);
            }
            else
            {
              Mat_PurpCode = m_pHD_RESTRI_ENTRY->getMAT_CODE(j);
            }

            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_HandleRestriction(sMessage, RecipeSource.c_str(), CombinationName.c_str(), Mat_PurpCode.c_str() );
            
            if (m_pGC_RESTRI_DEF->select(RestriType))
            {

              // mrut 2013-11-06 recoded to avoid useless calls
              bool MinimumGiven = (!m_pHD_RESTRI_ENTRY->isNull(CHD_RESTRI_ENTRY::RESTRI_VALMIN, j) && (m_pHD_RESTRI_ENTRY->getRESTRI_VALMIN(j) > 0.0) );
              bool MaximumGiven = (!m_pHD_RESTRI_ENTRY->isNull(CHD_RESTRI_ENTRY::RESTRI_VALMAX, j) );

              if (!RecipeIsInFocus && (MinimumGiven || MaximumGiven) )
              {
                if(RecipeSource.empty() || isCombiRecipe(RecipeNameModel) )
                {
                  pIntfEAF->focusOnRecipe(RecipeNameModel,RecipeNoModel,true);
                }
                else
                {
                  pIntfEAF->focusOnRecipeOrig(RecipeNameModel,RecipeNoModel,RecipeSource,true);
                }
                RecipeIsInFocus = true;
              }

              if (MinimumGiven)
              {
                  pIntfEAF->setMatRestr(Mat_PurpCode, m_pHD_RESTRI_ENTRY->getRESTRI_VALMIN(j),m_pGC_RESTRI_DEF->getRESTRITYPEMODEL_MIN(1));
              }

              if (MaximumGiven)
              {
                pIntfEAF->setMatRestr(Mat_PurpCode, m_pHD_RESTRI_ENTRY->getRESTRI_VALMAX(j),m_pGC_RESTRI_DEF->getRESTRITYPEMODEL_MAX(1));                
              }

            }
          } // for
        } // 
      } 
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorHandlingRecipe(sMessage, RecipeName.c_str(), RecipeNo, Function.c_str());
      }

    } 





        /////////////////////////////////////////////////////////////////////////////////////////
        /*std::set <std::string> RecipeSourceSet;        
        CSourceEAF::getValues (RecipeSourceSet);       //inserts all defined values into passed container.

        for (int i = 1; i <= m_pGC_COMBI_RECIPE_ENTRY->getLastRow(); i++)
        {
          const std::string SystemRecipeName   = m_pGC_COMBI_RECIPE_ENTRY->getRECIPECOMBI(i);
          const long              RecipeNumber = m_pGC_COMBI_RECIPE_ENTRY->getRECIPECOMBINO(i);
          const std::string       RecipeSource = m_pGC_COMBI_RECIPE_ENTRY->getSOURCE(i);

          if ( RecipeSourceSet.find(RecipeSource) == RecipeSourceSet.end() )  continue;         // recipe source not valid for EAF ;ignore restriction

          if (m_pHD_RESTRI_ENTRY->select( HeatID, TreatID, Plant,ProdPracPointer,TreatmentModeNo, CSMC_DBData::unspecLong, SystemRecipeName, RecipeNumber, RecipeSource, CSMC_DBData::unspecLong))
          {
            std::pair < std::pair <std::string, long>, std::string> RecipeKey =
              make_pair ( make_pair(SystemRecipeName, RecipeNumber), RecipeSource);

            // check catalogue of versions for model's recipes (table GC_RECIPE_L1)
            if (!m_pGC_RECIPE_L1  || !m_pGC_RECIPE_L1->select(Plant, SystemRecipeName, CSMC_DBData::unspecLong) )
            {
              std::stringstream Key;
              Key << Plant <<  " " << SystemRecipeName;

              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLogFrame::initMessage(__FILE__,__LINE__);
              pEventLog->EL_ErrorSearchingData(sMessage,Key.str().c_str(),"m_pGC_RECIPE_L1");

              continue;
            }

            // we expect the model's recipename to be constant for identical system recipe names
            const std::string RecipeNameModel     = m_pGC_RECIPE_L1->getRECIPENAME_MODEL(1);

            // required due to constraint on PD_RECIPE_Source/source must not be empty - 
            // makes no sense for combi-recipes however.
            const char* pchar = RecipeNameModel.c_str();

            const bool EmptySource = ((*pchar) == '$') || RecipeSource.empty();
            //combi-Recipe has no source

            const std::string RecipeSourceModel   = EmptySource ? "" : RecipeSource;

            RecipeKey = make_pair ( make_pair(RecipeNameModel, RecipeNumber), RecipeSourceModel);


            std::string Mat_PurpCode;
            std::string RestriType;
            std::string RestriTypeModel;
            double RestriValue;
            std::pair < std::string, std::string>  RestrCodeAndType;

            // iterating on result set
            for (int j = 1; j <= m_pHD_RESTRI_ENTRY->getLastRow(); ++j)
            {
              // special operations for param Mat_PurpCode 
              if (m_pHD_RESTRI_ENTRY->isNull(CHD_RESTRI_ENTRY::MAT_CODE, j))
                Mat_PurpCode = m_pHD_RESTRI_ENTRY->getPURP_CODE(j);
              else
                Mat_PurpCode = m_pHD_RESTRI_ENTRY->getMAT_CODE(j);

              // special operation for param RestriType            
              RestriType = m_pHD_RESTRI_ENTRY->getRESTRITYPE(j);


              if (m_pGC_RESTRI_DEF->select(RestriType))
              { 
                if (!m_pHD_RESTRI_ENTRY->isNull(CHD_RESTRI_ENTRY::RESTRI_VALMIN, j))
                {                  
                  RestriValue = m_pHD_RESTRI_ENTRY->getRESTRI_VALMIN(j);
                  if (RestriValue > 0.)
                  {
                    RestriTypeModel  = m_pGC_RESTRI_DEF->getRESTRITYPEMODEL_MIN(1);
                    RestrCodeAndType = make_pair(Mat_PurpCode, RestriTypeModel);

                    (Restrictions.Recipe[RecipeKey])[RestrCodeAndType] = RestriValue;
                  }                      
                }

                if (!m_pHD_RESTRI_ENTRY->isNull(CHD_RESTRI_ENTRY::RESTRI_VALMAX, j))
                {                  
                  RestriValue       = m_pHD_RESTRI_ENTRY->getRESTRI_VALMAX(j);
                  RestriTypeModel   = m_pGC_RESTRI_DEF->getRESTRITYPEMODEL_MAX(1);
                  RestrCodeAndType  = make_pair(Mat_PurpCode, RestriTypeModel);
                  (Restrictions.Recipe[RecipeKey])[RestrCodeAndType] = RestriValue;
                }
              }

            } // for
            
          } // if select m_pHD_RESTRI_ENTRY
          else
          {
            std::stringstream Msg;
            Msg << Function << " No data for HeatID= " << HeatID << " TreatID = " << TreatID << " Plant= " << Plant << " ProdPracPointer= " << ProdPracPointer << " TreatmentModeNo= " << TreatmentModeNo ;   
            log(Msg.str(),2);
          }
        } //for (int i = 1; i <= m_pGC_COMBI_RECIPE_ENTRY->getLastRow(); i++)


      ///////////////////////////////
      //      MODEL - interfacing
      ///////////////////////////////
      if (RetValue && !Restrictions.Recipe.empty())
      {
          RetValue = pass_practice_data_recipe_restrictions_to_model (pIntfEAF, Restrictions );
      }*/
      /////////////////////////////////////////////////////////////////////////////////////////

  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", Function.c_str(), ""  );    
  } 


  return RetValue;
}


//##ModelId=467645DC023E
bool CEAFModelWrapper::sequence_set_production_practice_ProcessPattern(const std::string& HeatID, const std::string& TreatID)
{
  bool    RetValue  = true;
  return  RetValue;
}


//##ModelId=4200DE4201C5
bool CEAFModelWrapper::sequence_set_production_practice_data_injection(const std::string& HeatID, const std::string& TreatID, const std::string& Plant, long PlantNo)
{
  bool RetValue     = false;
  std::string thisPracPhase, tempPracPhase;
  
  thisPracPhase = "zzzzzzzzz";

  double      Flow     = CInv::InvalidDouble;
  double      StecEgy  = CInv::InvalidDouble;
  long        DeviceNo = 0;
  std::string PurposeCode;
  std::string InjectType;
  std::string GasType;

  std::string Function = "CEAFModelWrapper::sequence_set_production_practice_data_injection()" ;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !checkDBConnection()) 
  {
    log("Error: " + Function + " , (pIntfEAF || checkDBConnection()) == false", 1);
    return RetValue;
  }
  else
  {
    log(Function, 3);
  }

  RetValue = true;

  // definition in config.h
  #if defined (EAF_INJECTION_LANCES)  || defined (EAF_GAS_LANCES)

  try 
  {
    const CCfgEAF * pCfgEAF     =  getpCfgEAF();
    const std::set<std::string> & SetOfInjectionPurposes = pCfgEAF->getSetOfInjectionPurposes();

    bool WeHaveMaterialInjection = false;
    bool WeHaveGasInjection      = false;


    long InjectionDataStatus = 0;
    //EAFPracticePattern   InjectionPractice;           // not used ony more - was done for PNTZ

    long ProdPracPointer          = getProdPracticePointer(HeatID, TreatID, Plant, DEF_GC_PRODPRAC_DEF::Injection);
    long TreatmentModeNo          = getTreatmentModeNo(HeatID, TreatID, Plant);
    long focusOnPracPhaseSuccess  = CRS::OK;


    if (m_pHDE_PP_INJECTION_STEP_ENTRY->selectOrdered(HeatID, TreatID, Plant, ProdPracPointer,TreatmentModeNo,CSMC_DBData::unspecLong,CSMC_DBData::unspecString,CSMC_DBData::unspecString,CSMC_DBData::unspecLong))  
    {
      int  i = 0;

      for (i = 1; i <= m_pHDE_PP_INJECTION_STEP_ENTRY->getLastRow(); ++i) 
      {
        PurposeCode = m_pGCE_INJECTION_TYPE->getPurposeCodeByInjType(m_pHDE_PP_INJECTION_STEP_ENTRY->getINJTYPE(i));

        if (SetOfInjectionPurposes.find(PurposeCode) != SetOfInjectionPurposes.end())
        {
          WeHaveMaterialInjection = true;
        }
        else
        {
          WeHaveGasInjection = true;                  // i and the model expect a gas-type here !! (e.g. O2 or N2)
        }
      }

  #if defined (EAF_INJECTION_LANCES) 
      if (WeHaveMaterialInjection)
      {
         pIntfEAF->focusOnProcPatData();
         pIntfEAF->setProcPatPt(ProdPracPointer);

         thisPracPhase = "";    // what a name , what a shame.

         for (i = 1; i <= m_pHDE_PP_INJECTION_STEP_ENTRY->getLastRow(); ++i) 
         {
           InjectType  = m_pHDE_PP_INJECTION_STEP_ENTRY->getINJTYPE(i);
           PurposeCode = m_pGCE_INJECTION_TYPE->getPurposeCodeByInjType(InjectType);

           if (SetOfInjectionPurposes.find(PurposeCode) != SetOfInjectionPurposes.end())
           {

             if(thisPracPhase != m_pHDE_PP_INJECTION_STEP_ENTRY->getPRACPHASE(i))
             {
               thisPracPhase           = m_pHDE_PP_INJECTION_STEP_ENTRY->getPRACPHASE(i);
               focusOnPracPhaseSuccess = pIntfEAF->focusOnPracPhase(thisPracPhase);
             }

             if ( CRS::OK == focusOnPracPhaseSuccess )
             {

               double SpecEgy = m_pHDE_PP_INJECTION_STEP_ENTRY->getSPECEGY(i);      // kwh/kg
               long   ElecEgy = m_pHDE_PP_INJECTION_STEP_ENTRY->getELEC_ENERGY(i);  // kwh

               // model can decide if it is abs or spec
               double StepEgy  = CDataConversion::SetInvalidToDefault(SpecEgy, (double)ElecEgy, CSMC_DBData::unspecDouble); 

               Flow    = m_pHDE_PP_INJECTION_STEP_ENTRY->getINJFLOW(i);

               pIntfEAF->setProcPatStepData( CProcPatCodesEAF::AbsAfterStartOfArc,
                                             StepEgy,
                                             PurposeCode,
                                             0.0,                       // no amount  ?  still open whether an amount or a rate should be given
                                             Flow,                      // good l1 and the device itself can handle a fixed rate only, but a variable amount.
                                             CProcPatCodesEAF::Rate);
             }

           }
         }
      }
  #endif




  #if defined (EAF_GAS_LANCES) 
      if (WeHaveGasInjection)
      {

         pIntfEAF->focusOnManipGasLanceData();
         pIntfEAF->setProdPracPtManipGasLance(ProdPracPointer);

         thisPracPhase = "";    // what a name , what a shame.

         for (i = 1; i <= m_pHDE_PP_INJECTION_STEP_ENTRY->getLastRow(); ++i) 
         {
           InjectType  = m_pHDE_PP_INJECTION_STEP_ENTRY->getINJTYPE(i);
           PurposeCode = m_pGCE_INJECTION_TYPE->getPurposeCodeByInjType(InjectType);

           if (SetOfInjectionPurposes.find(PurposeCode) == SetOfInjectionPurposes.end())
           {

             if(thisPracPhase != m_pHDE_PP_INJECTION_STEP_ENTRY->getPRACPHASE(i))
             {
               thisPracPhase           = m_pHDE_PP_INJECTION_STEP_ENTRY->getPRACPHASE(i);
               focusOnPracPhaseSuccess = pIntfEAF->focusOnPracPhase(thisPracPhase);
             }

             if ( CRS::OK == focusOnPracPhaseSuccess )
             {
               double SpecEgy = m_pHDE_PP_INJECTION_STEP_ENTRY->getSPECEGY(i);      // kwh/kg
               long   ElecEgy = m_pHDE_PP_INJECTION_STEP_ENTRY->getELEC_ENERGY(i);  // kwh

               // model can decide if it is abs or spec
               StepEgy = CDataConversion::SetInvalidToDefault(SpecEgy,(double)ElecEgy, CSMC_DBData::unspecDouble); 

               Flow     = m_pHDE_PP_INJECTION_STEP_ENTRY->getINJFLOW(i);
               
               std::string DeviceName = m_pHDE_PP_INJECTION_STEP_ENTRY->getDEVICENAME(i);

               // determine lance number
               long LanceNo = 0;
               if (m_pGCE_INJECTION->select(Plant,PlantNo,DeviceName))
               {
                 LanceNo = m_pGCE_INJECTION->getL1_DEVICENO(1);
               }

               // determin gas type according to INJTYPE
               if ( InjectType == DEF_GCE_INJECTION_TYPE::OxygenInjection )
               {
                 GasType = DEF_GAS::O2;
               }

               pIntfEAF->setPracManipGasLanceStepData( LanceNo, StepEgy, GasType, Flow);   // we use Nm³/min internally, don't we ?
             }

           }
         }
      }
  #endif

    }
    else
    {
      std::stringstream Msg;
      Msg << Function << " No data for HeatID= " << HeatID << " TreatID= " << TreatID << " Plant= " << Plant << " ProdPracPointer= " << ProdPracPointer << " TreatmentModeNo= " << TreatmentModeNo ;   
      log(Msg.str(),2);
    }

  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", Function.c_str(), ""  );    
  } 

  #endif

  return RetValue;
}

//##ModelId=45EBDA3E027B
bool CEAFModelWrapper::sequence_set_production_practice_data_pattern_feeding(const std::string& HeatID, const std::string& TreatID, const std::string& Plant)
{
  bool RetValue     = false;

  std::string Function = "CEAFModelWrapper::doModsequence_set_production_practice_data_pattern_feedingelResult()" ;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !checkDBConnection()) 
  {
    log("Error: " + Function + " , (pIntfEAF || checkDBConnection()) == false", 1);
    return RetValue;
  }
  else
  {
    log(Function, 3);
  }

  RetValue = true;

  #if defined (EAF_PATTERN_FEEDING)        
    std::string  tempPracPhase, thisPracPhase;
    thisPracPhase = "ZZZZZZ";

    try 
    {
      pIntfEAF->focusOnProcPatData(); 

      long ProdPracPointer  = getProdPracticePointer(HeatID, TreatID, Plant, DEF_GC_PRODPRAC_DEF::Process);
      long TreatmentModeNo  = getTreatmentModeNo(HeatID, TreatID, Plant);


      pIntfEAF->setProcPatPt(ProdPracPointer);

      if (m_pHD_MAT_FEED->selectOrdered(HeatID, TreatID, Plant, ProdPracPointer, TreatmentModeNo,CSMC_DBData::unspecString, CSMC_DBData::unspecLong,CSMC_DBData::unspecString,CSMC_DBData::unspecLong)) 
      {    
        long focusOnPracPhaseSuccess = CRS::OK;

        for (int i=1; i<=m_pHD_MAT_FEED->getLastRow(); ++i) 
        {

          if(thisPracPhase != m_pHD_MAT_FEED->getPRACPHASE(i))
          {
            thisPracPhase           = m_pHD_MAT_FEED->getPRACPHASE(i);
            focusOnPracPhaseSuccess = pIntfEAF->focusOnPracPhase(thisPracPhase);
          }

          long   StepNo  = m_pHD_MAT_FEED->getSTEPNO(i);
          double StepEgy = 0;
          if (m_pHDE_PP_PROCESS_STEP_ENTRY->selectOrdered(HeatID, TreatID, Plant, ProdPracPointer, TreatmentModeNo, CSMC_DBData::unspecLong, thisPracPhase, StepNo))
          {
            double SpecEgy = m_pHDE_PP_PROCESS_STEP_ENTRY->getSPECEGY(1);       // kwh/kg
            long   ElecEgy = m_pHDE_PP_PROCESS_STEP_ENTRY->getELEC_ENERGY(1);   // kwh

            // model can decide if it is abs or spec
            StepEgy = CDataConversion::SetInvalidToDefault(SpecEgy, (double)ElecEgy, CSMC_DBData::unspecDouble); 
          }

          long flag = m_pHD_MAT_FEED->getFEEDINGRATE_INPUT(1);
          if ( flag == DEF::Inv_Long)
          {
            flag = 0;
          }

          if ( CRS::OK == focusOnPracPhaseSuccess )
          {
            if(flag == 0)
            {
              pIntfEAF->setProcPatStepData( CProcPatCodesEAF::AbsAfterStartOfArc,        // MomTyp
                                            StepEgy,                                     // 
                                            m_pHD_MAT_FEED->getMAT_CODE(i),  
                                            0.0,                                         // Amount
                                            m_pHD_MAT_FEED->getFEEDINGRATE_ABS(i), 
                                            CProcPatCodesEAF::Rate);                     // MeasUnit
            }
            else
            {
              pIntfEAF->setProcPatStepData( CProcPatCodesEAF::AbsAfterStartOfArc,        // MomTyp
                                            StepEgy,                                     // change as per Jesper; m_pHD_MAT_FEED->getEFFY_ELEC(i),  // getEFFY_ELEC(i)/1000.,
                                            m_pHD_MAT_FEED->getMAT_CODE(i),  
                                            0.0,                                         // Amount
                                            m_pHD_MAT_FEED->getFEEDINGRATE_REL(i)/1000,  // Relative feeding rate in kg/minMW -> kg/minKW 
                                            CProcPatCodesEAF::SpecRate);                 // MeasUnit
            }
          }
        }        
      }
      else
      {
        std::stringstream Msg;
        Msg << Function << " No data for HeatID= " << HeatID << " TreatID= " << TreatID << " Plant= " << Plant << " ProdPracPointer= " << ProdPracPointer << " TreatmentModeNo= " << TreatmentModeNo ;   
        log(Msg.str(),2);
      }

    }
    catch(...)
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "", Function.c_str(), ""  );    
    } 

  #endif 


  return RetValue;
}


//##ModelId=4200DE3F021B
bool CEAFModelWrapper::sequence_set_production_practice_data_jet_module(const std::string& HeatID, const std::string& TreatID, const std::string& Plant, long PlantNo )
{
  bool RetValue         = false;
  long ProdPracPointer  = -1;

  std::string Function = "CEAFModelWrapper::sequence_set_production_practice_data_jet_module()" ;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !checkDBConnection()) 
  {
    log("Error: " + Function + " , (pIntfEAF || checkDBConnection()) == false", 1);
    return RetValue;
  }
  else
  {
    log(Function, 3);
  }

  RetValue = true;


  #if defined (EAF_JET_MODULES)    
    std::string  tempPracPhase, thisPracPhase;
    thisPracPhase = "zzzzzzzzzzz";
    long focusOnPracPhaseSuccess  = CRS::OK;

    try  
    {
      pIntfEAF->focusOnJetModuleData();

      ProdPracPointer       = getProdPracticePointer(HeatID, TreatID, Plant, "JetModules");
      long TreatmentModeNo  = getTreatmentModeNo(HeatID, TreatID, Plant);

      if (CInv::InvalidLong != ProdPracPointer) pIntfEAF->setProdPracPtJetModule(ProdPracPointer);

      if (m_pHDE_PP_INJECTION_STEP_ENTRY->selectOrdered(HeatID, TreatID, Plant, ProdPracPointer, TreatmentModeNo, CSMC_DBData::unspecLong, CSMC_DBData::unspecString, CSMC_DBData::unspecString, CSMC_DBData::unspecLong)) 
      {
        for (int i=1; i<=m_pHDE_PP_INJECTION_STEP_ENTRY->getLastRow(); ++i) 
        {
          if(thisPracPhase != m_pHDE_PP_INJECTION_STEP_ENTRY->getPRACPHASE(i))
          {
            thisPracPhase           = m_pHDE_PP_INJECTION_STEP_ENTRY->getPRACPHASE(i);
            focusOnPracPhaseSuccess = pIntfEAF->focusOnPracPhase(thisPracPhase);
          }

          if ( CRS::OK == focusOnPracPhaseSuccess )
          {
            if(m_pHDE_PP_INJECTION_STEP_ENTRY->getINJTYPE(i) != DEF_GCE_INJECTION_TYPE::CarbonInjection) continue;

            long LanceNo = 0;
            if (m_pGCE_INJECTION->select(Plant,PlantNo,m_pHDE_PP_INJECTION_STEP_ENTRY->getDEVICENAME(i)))
            {
              LanceNo = m_pGCE_INJECTION->getL1_DEVICENO(1);
            }

            pIntfEAF->setProdPracPtJetModule(LanceNo);

            pIntfEAF->setPracCarbonJetStepData( LanceNo,  // jetModuleNo 
              m_pHDE_PP_INJECTION_STEP_ENTRY->getSPECEGY(i),  // StepEgy, lohm, abs. egy? getSPECEGY(i)/1000.
              m_pHDE_PP_INJECTION_STEP_ENTRY->getINJFLOW(i),  // CarbonFlow
              0.0,  // GasFlow
              0.0); //O2Flow

          } 
        }//end of for(...)
      } 

    }
    catch(...)
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "", Function.c_str(), ""  );    
    } 

  #endif


  return RetValue;
}




//##ModelId=45EBDA3F0067
bool CEAFModelWrapper::sequence_set_production_practice_data_bottom_stirring(const std::string& HeatID, const std::string& TreatID, const std::string& Plant)
{
  bool RetValue         = false;
  long ProdPracPointer  = -1;


  std::string Function = "CEAFModelWrapper::sequence_set_production_practice_data_bottom_stirring()" ;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !checkDBConnection()) 
  {
    log("Error: " + Function + " , (pIntfEAF || checkDBConnection()) == false", 1);
    return RetValue;
  }
  else
  {
    log(Function, 3);
  }

  RetValue = true;

  #if defined (EAF_BOTTOM_STIRRING)      
    std::string  tempPracPhase,thisPracPhase;
    std::string CurrentPracPhase ="zzzzzz";
    long focusOnPracPhaseSuccess  = CRS::OK;

    try 
    {
      ProdPracPointer = getProdPracticePointer(HeatID, TreatID, Plant, DEF_GC_PRODPRAC_DEF::Stirring); //"BottStirr"
      long TreatmentModeNo  = getTreatmentModeNo(HeatID, TreatID, Plant);

      if (m_pHDE_PP_STIRR_SPEC->selectByOrder(HeatID, TreatID, Plant, ProdPracPointer,TreatmentModeNo, CSMC_DBData::unspecLong,CSMC_DBData::unspecString,CSMC_DBData::unspecLong)) 
      {        
        pIntfEAF->focusOnBottomStirringData();
        if (CInv::InvalidLong != ProdPracPointer) pIntfEAF->setProdPracPtBottomStirring(ProdPracPointer);

        for (int i=1; i<=m_pHDE_PP_STIRR_SPEC->getLastRow(); i++) 
        {
          if(CurrentPracPhase != m_pHDE_PP_STIRR_SPEC->getPRACPHASE(i))
          {
            thisPracPhase           = m_pHDE_PP_STIRR_SPEC->getPRACPHASE(i);
            focusOnPracPhaseSuccess = pIntfEAF->focusOnPracPhase(thisPracPhase);
          }

          if ( CRS::OK == focusOnPracPhaseSuccess )
          {
            double SpecEgy = m_pHDE_PP_STIRR_SPEC->getSPECEGY(i);       // kwh/kg
            long   ElecEgy = m_pHDE_PP_STIRR_SPEC->getELEC_ENERGY(i);   // kwh

            // model can decide if it is abs or spec
            double StepEgy = CDataConversion::SetInvalidToDefault(SpecEgy, (double)ElecEgy, CSMC_DBData::unspecDouble); 

            long StirringDataStatus = pIntfEAF->setProdPracBottomStirringStepData( StepEgy, m_pHDE_PP_STIRR_SPEC->getSTIRRGASTYPE(i),m_pHDE_PP_STIRR_SPEC->getSTIRRFLOW(i) );        
          }
        }

      }
      else
      {
        std::stringstream Msg;
        Msg << Function << " No data for HeatID= " << HeatID << " TreatID= " << TreatID << " Plant= " << Plant << " ProdPracPointer= " << ProdPracPointer << " TreatmentModeNo= " << TreatmentModeNo ;   
        log(Msg.str(),2);
      }
    }
    catch(...)
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "", Function.c_str(), ""  );    
    } 

  #endif

  return RetValue;
}




//##ModelId=4200DE4301C7
bool CEAFModelWrapper::sequence_set_production_practice_data_manipulator_gas_lance(const std::string& HeatID, const std::string& TreatID, const std::string& Plant)
{

  bool RetValue         = false;
  long ProdPracPointer  = -1;
  std::string  tempPracPhase, thisPracPhase;
  thisPracPhase = "zzzzzzz";

  std::string Function = "CEAFModelWrapper::sequence_set_production_practice_data_manipulator_gas_lance()" ;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !checkDBConnection()) 
  {
    log("Error: " + Function + " , (pIntfEAF || checkDBConnection()) == false", 1);
    return RetValue;
  }
  else
  {
    log(Function, 3);
  }

  RetValue = true;

  #if defined (EAF_GAS_LANCES)    // to do : check next code block
    try 
    {
      ProdPracPointer       = getProdPracticePointer(HeatID, TreatID, Plant, DEF_GC_PRODPRAC_DEF::Process);    
      long TreatmentModeNo  = getTreatmentModeNo(HeatID, TreatID, Plant);
      long focusOnPracPhaseSuccess  = CRS::OK;

      pIntfEAF->focusOnManipGasLanceData();

      if (CInv::InvalidLong != ProdPracPointer) pIntfEAF->setProdPracPtManipGasLance(ProdPracPointer);

      if (m_pHDE_PP_PROCESS_STEP_ENTRY->selectOrdered(HeatID, TreatID, Plant, ProdPracPointer, TreatmentModeNo, CSMC_DBData::unspecLong, CSMC_DBData::unspecString, CSMC_DBData::unspecLong))
      {
        for (int i = 1; i <= m_pHDE_PP_PROCESS_STEP_ENTRY->getLastRow(); ++i) 
        {
          if(thisPracPhase != m_pHDE_PP_PROCESS_STEP_ENTRY->getPRACPHASE(i))
          {
            thisPracPhase           = m_pHDE_PP_PROCESS_STEP_ENTRY->getPRACPHASE(i);
            focusOnPracPhaseSuccess = pIntfEAF->focusOnPracPhase(thisPracPhase); 
          }

          if ( CRS::OK == focusOnPracPhaseSuccess )
          {
            double SpecEgy = m_pHDE_PP_PROCESS_STEP_ENTRY->getSPECEGY(i);       // kwh/kg
            long   ElecEgy = m_pHDE_PP_PROCESS_STEP_ENTRY->getELEC_ENERGY(i);   // kwh

            // model can decide if it is abs or spec
            double StepEgy = CDataConversion::SetInvalidToDefault(SpecEgy, (double)ElecEgy, CSMC_DBData::unspecDouble); 

            Flow    = m_pHDE_PP_PROCESS_STEP_ENTRY->getO2_FLOW(i);              // apply unit conversion factor for O2 here  -> m³ / min

            pIntfEAF->setPracManipGasLanceStepData( 1,                          // dev #
              StepEgy, 
              DEF_GAS::O2,
              Flow);                                                            // we use Nm³/min internally
          }
        } 

      }
      else
      {
        std::stringstream Msg;
        Msg << Function << " No data for HeatID= " << HeatID << " TreatID= " << TreatID << " Plant= " << Plant << " ProdPracPointer= " << ProdPracPointer << " TreatmentModeNo= " << TreatmentModeNo ;   
        log(Msg.str(),2);
      }

    }
    catch(...)
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "", Function.c_str(), ""  );    
    } 

  #endif

  return RetValue;
}


//##ModelId=467645D7029B
void CEAFModelWrapper::getNextLowerLiqAddAmountValue(long & LiqAddAmountMax, const long LiqAddAmountToCompare, const double LiqAddAmountAct) const
{
  // get the value closest to, but still less than the actual liqAddn value.
  // implies idea is that a pp with a specified liqAddnRatio L is valid for heat with an actual ratio R >= L.

  if (  (LiqAddAmountAct*100 > LiqAddAmountToCompare) && (LiqAddAmountMax < LiqAddAmountToCompare))
  {
    LiqAddAmountMax = LiqAddAmountToCompare;
  }

}


// returns a warning if NewPhase does not match to used basket number
//##ModelId=467645D8013E
long CEAFModelWrapper::focusOnPracticePhase(string & LastFocusedPracPhase, const std::string & NewPracPhase, long PlannedNumberOfBaskets)
{
  //logic for jisco
  if (  (PlannedNumberOfBaskets == 1) && (  (NewPracPhase == CPracPhaseCodesEAF::FirstBsk) || (NewPracPhase == CPracPhaseCodesEAF::ImedBsk ) )    )
    return CRS::WarnGen;

  if ( (PlannedNumberOfBaskets==2) && (NewPracPhase == CPracPhaseCodesEAF::ImedBsk) ) 
    return CRS::WarnGen;

  if (LastFocusedPracPhase != NewPracPhase)
  {
    if (NewPracPhase == "LiqAdd")
    {
#if !defined (EAF_LIQUID_METAL)
      return CRS::WarnGen;
#else
      getpModelIntf()->focusOnPracPhase(CPracPhaseCodesEAF::LiquidCharge);
#endif
    }
    else
    {
      getpModelIntf()->focusOnPracPhase(NewPracPhase);
    }
  }

  LastFocusedPracPhase = NewPracPhase;
  return CRS::OK;
}


//##ModelId=467645DB017E
long CEAFModelWrapper::getProdPracticePointer(const std::string & HeatID, const std::string & TreatID, const std::string& Plant, const std::string & PracticeCode)
{
  long ProdPracPointer = CInv::InvalidLong;

  if (m_pPD_HEAT_DATA_PRODPRAC->select(HeatID,TreatID,Plant,PracticeCode)) 
  { 
    if (!m_pPD_HEAT_DATA_PRODPRAC->isNull(CPD_HEAT_DATA_PRODPRAC::PRODPRACID_MOD, 1))
    {
      ProdPracPointer = m_pPD_HEAT_DATA_PRODPRAC->getPRODPRACID_MOD(1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_UseOfProdPracPt(sMessage, PracticeCode.c_str(), ProdPracPointer,"PRODPRACID_MOD");
    }
    else if (!m_pPD_HEAT_DATA_PRODPRAC->isNull(CPD_HEAT_DATA_PRODPRAC::PRODPRACID_PLAN, 1))
    {
      ProdPracPointer = m_pPD_HEAT_DATA_PRODPRAC->getPRODPRACID_PLAN(1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_UseOfProdPracPt(sMessage, PracticeCode.c_str(), ProdPracPointer,"PRODPRACID_PLAN");
    }
    else 
    {
      ProdPracPointer = (DEF_GC_PRODPRAC_DEF::Parameter == PracticeCode) ? 0 : 1; // for parameter set, the default is zero
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_UseOfProdPracPt(sMessage, PracticeCode.c_str(), ProdPracPointer,"default");
    }
  }
  else
  {
    std::string SearchKey = HeatID + " " + TreatID + PracticeCode;
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.c_str(),"PD_HEAT_DATA_PRODPRAC");
  }
  return ProdPracPointer;
}

long CEAFModelWrapper::getTreatmentModeNo(CEventMessage &Event)
{
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string OrderID   = Event.getOrderID();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);

  return getTreatmentModeNo(HeatID,TreatID,ActPlant);

}


long CEAFModelWrapper::getTreatmentModeNo(const std::string & HeatID, const std::string & TreatID, const std::string& Plant)
{
  long TreatmentModeNo = CInv::InvalidLong;

  if (m_pHD_TREATMODE && m_pHD_TREATMODE->select(HeatID, TreatID, Plant, CSMC_DBData::unspecLong)) 
  { 
    TreatmentModeNo = m_pHD_TREATMODE->getTREATMODENO(1);
  }
  else if ( m_pPP_HEAT && m_pPP_HEAT->select(HeatID) )
  {
    std::string PRODORDERID = m_pPP_HEAT->getPRODORDERID(1);

    if ( PRODORDERID != CSMC_DBData::unspecString )
    {
      if (m_pPP_ORDER_SINGLE_AIMS && m_pPP_ORDER_SINGLE_AIMS->select(PRODORDERID, Plant, 1,DEF_GC_PP_ORDER_SINGLE_AIMS::TREATMENTMODE)) 
      {
        TreatmentModeNo = CDataConversion::StringToLong(m_pPP_ORDER_SINGLE_AIMS->getVALUE(1));
      }
      else
      {
        std::string SearchKey = PRODORDERID + " " + DEF_GC_PP_ORDER_SINGLE_AIMS::TREATMENTMODE;
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.c_str(),"m_pPP_ORDER_SINGLE_AIMS");
      }
    }
  }
  else
  {
    std::string SearchKey = HeatID + " " + DEF_GC_PP_ORDER_SINGLE_AIMS::TREATMENTMODE;
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.c_str(),"m_pPP_ORDER_SINGLE_AIMS");
  }

  return TreatmentModeNo;
}


//##ModelId=467645D8033C
void CEAFModelWrapper::logErrorProcessingData (long ProdPracPointer, const char* Text)
{
  std::stringstream SearchKey;
  SearchKey << "ProdPracPt " << ProdPracPointer;
  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ErrorProcessingData(sMessage,Text,SearchKey.str().c_str());
}

//##ModelId=467645D900DB
bool CEAFModelWrapper::checkWetherLanceTypeIsInjection(const std::string& LANCENAME)
{
  bool IsItTrue = false;

  //this was removed because it table seems not present for bhushan.
  /*if (!checkDBConnection())
  {
  handleDBConnectionError();
  if (!checkDBConnection()) return false;
  }
  if (m_pGCE_INJECTION->select (LanceNo)) IsItTrue = (m_pGCE_INJECTION->getLANCEFLAG(1) == 1);*/ 

  return IsItTrue;
}


//////////////////////////////////////////////////////////////////////////////////////////
//              the following methods MAY BE REDIRECTED IN FUTURE (PIMPL)
//////////////////////////////////////////////////////////////////////////////////////////

bool CEAFModelWrapper::doHandleEvent()
{
  CIntfEAF *pIntfEAF = getpModelIntf();
  if (pIntfEAF)
    return (!CRS::isError( pIntfEAF->hndlEvent()));
  else 
    return true;
}

bool CEAFModelWrapper::doHndlHeatCanc()
{
  CIntfEAF *pIntfEAF = getpModelIntf();
  if (pIntfEAF)
    return (!CRS::isError( pIntfEAF->hndlHeatCanc()));
  else 
    return true;
}


bool CEAFModelWrapper::doIndicateHeatAnnouncement(const std::string& HeatId, const std::string& TreatNo, long ParamPracPt)
{
  CIntfEAF *pIntfEAF = getpModelIntf();
  if (pIntfEAF)    
    return (!CRS::isError( pIntfEAF->indicateHeatAnnouncement(HeatId, TreatNo, ParamPracPt)) );
  else
  {
    return true;

    /*CParamMgr* pParamMgr = 0;
    //dynamic cast is preferable to static - cast, see scott-meyers
    CEAFModelTask* pTask = dynamic_cast <CEAFModelTask*>(m_pModelTask);
    if (pTask)  pParamMgr = pTask->getpParamMgr();

    if (!pParamMgr)
      return false;   

    if (pParamMgr->getActualPracNo() != ParamPracPt)
    {
      pParamMgr->setActualPracNo(ParamPracPt);
      long RC = pParamMgr->updateAll();
      return (RC > 0);
    }*/

  }

}

bool CEAFModelWrapper::doIndicateChgTreatmentMode()
{
  bool RetValue = true;

  CIntfEAF  *pIntfEAF = getpModelIntf();
  CCfgEAF   *pCfgEAF  = getUnConstpCfgEAF();  

  if (pIntfEAF && pCfgEAF)
  {
     CIntfTreatmentMap IntfTreatmentMap(*pCfgEAF, *pIntfEAF) ;

     return (!CRS::isError( IntfTreatmentMap.indicateReplacementOfTreatmentMap() ));
  }

  return RetValue;
}

bool CEAFModelWrapper::doIndicateBasketData()
{
  CIntfEAF *pIntfEAF = getpModelIntf();
  if (pIntfEAF)
    return (!CRS::isError( pIntfEAF->indicateBasketData()) );
  else 
    return true;
}

bool CEAFModelWrapper::doIndicateChgAimData()
{
  CIntfEAF *pIntfEAF = getpModelIntf();
  if (pIntfEAF)
    return (!CRS::isError( pIntfEAF->indicateChgAimData()) );
  else 
    return true;
}

bool CEAFModelWrapper::doIndicateChgProcPat()
{
  CIntfEAF *pIntfEAF = getpModelIntf();
  if (pIntfEAF)
    return (!CRS::isError( pIntfEAF->indicateChgProcPat()) );
  else 
    return true;
}

bool CEAFModelWrapper::doIndicateChgProdPracElec()
{
  CIntfEAF *pIntfEAF = getpModelIntf();
  if (pIntfEAF)
    return (!CRS::isError( pIntfEAF->indicateChgProdPracElec()) );
  else 
    return true;
}
bool CEAFModelWrapper::doIndicateChgHotHeelData()
{
  CIntfEAF *pIntfEAF = getpModelIntf();
  if (pIntfEAF)
    return (!CRS::isError( pIntfEAF->indicateChgHotHeelData()) );
  else 
    return true;
}


bool CEAFModelWrapper::doIndicateChgProdPracBurner()
{
  #if defined(EAF_GAS_LANCES)     
  CIntfEAF *pIntfEAF = getpModelIntf();
  if (pIntfEAF)
    return (!CRS::isError( pIntfEAF->indicateChgProdPracManipGasLance()) );
  else 
  #endif

    return true;
}

bool CEAFModelWrapper::doIndicateChgProdPracJetModule()
{
  #if defined(EAF_JET_MODULES)
  CIntfEAF *pIntfEAF = getpModelIntf();
  if (pIntfEAF)
    return (!CRS::isError( pIntfEAF->indicateChgProdPracJetModule()) );
  else 
  #endif

  return true;

}
bool CEAFModelWrapper::doIndicateChgProdPracRecipeCtrl()   
{
  CIntfEAF *pIntfEAF = getpModelIntf();
  if (pIntfEAF)
    return (!CRS::isError( pIntfEAF->indicateChgProdPracRecipeCtrl()) );
  else 
    return true;
  
}

bool CEAFModelWrapper::doIndicateChgProdPracManipGasLance() 
{
#if defined (EAF_GAS_LANCES) || defined (EAF_BOTTOM_STIRRING)
  CIntfEAF *pIntfEAF = getpModelIntf();
  if (pIntfEAF)
    return (!CRS::isError( pIntfEAF->indicateChgProdPracManipGasLance()) );
  else 
    return true;
#else
  return false;
#endif
  
}
bool CEAFModelWrapper::doIndicateChgProdPracBottomStirring()
{
#if defined (EAF_GAS_LANCES) || defined (EAF_BOTTOM_STIRRING)
  CIntfEAF *pIntfEAF = getpModelIntf();
  if (pIntfEAF)
    return (!CRS::isError( pIntfEAF->indicateChgProdPracBottomStirring()) );
  else 
    return true;
#else
  return false;
#endif
}
bool CEAFModelWrapper::doIndicateChgTapLdlData()
{
  CIntfEAF *pIntfEAF = getpModelIntf();
  if (pIntfEAF)
    return (!CRS::isError( pIntfEAF->indicateChgTapLdlData()) );
  else 
    return true;
}

bool CEAFModelWrapper::isModelDevice(const string& DeviceName)
{
  bool RetVelue = false;
  long DeviceCount = 0;
  const CCfgEAF * pCfgEAF =  getpCfgEAF();

  if ( pCfgEAF )
  {
    pCfgEAF->getNoOfCtrlDevices(DeviceName, DeviceCount);
    if ( DeviceCount > 0 )
    {
      RetVelue = true;
    }
  }

  return RetVelue;

}

// check if ModelRecipe is valid, e.g. "NoModel" might not be forwarded to model interface
bool CEAFModelWrapper::isValidModelRecipeName(const std::string& ModelRecipeName)
{
  bool RetVelue = true;

  if ( ModelRecipeName == "NoModel" )
  {
    RetVelue = false;
  }

  return RetVelue;
}

// check whether it is a combi-recipe, which by definition does not have recipe sources.
// a combi-recipe must have a Dollar-character as the first letter.
bool CEAFModelWrapper::isCombiRecipe(const std::string& ModelRecipeName)
{
  bool RetVelue = false;

  if ( ModelRecipeName.find("$") != ModelRecipeName.npos )
  {
    RetVelue = true;
  }

  return RetVelue;
}

bool CEAFModelWrapper::handleEquivalences(const std::string & HeatID, const std::string & TreatID, const std::string& Plant, seqAnalysis & SeqAnalysis)
{
  bool result = true;

  if (result)
  {
    std::string STEELGRADECODE_ACT;

    // ***************************************************
    // select some PD and PP Data first
    // ***************************************************
    if ( m_pPD_HEAT_DATA->select(HeatID,TreatID,Plant) )
    {
      STEELGRADECODE_ACT  = m_pPD_HEAT_DATA->getSTEELGRADECODE_ACT(1);
    }

    //  get list of elements from HD_GRADE_ANL
    //std::set<std::string> ENAMEList = m_pHD_GRADE_ANL->getENAMEList(HeatID,TreatID,Plant,STEELGRADECODE_ACT,CSMC_DBData::unspecString, DEF_GC_MEASUREMENT_NAME_SCOPE::Equiv);
    std::set<std::string> ENAMEList = m_pGT_EQUIV->getEQUIVList();
    std::set<std::string>::iterator it;

    for( it = ENAMEList.begin(); it != ENAMEList.end(); ++it )
    {
      std::string ENAME = *it;

      // is there an equivalence defined for this element?
      double EquivValue = m_pGT_EQUIV->getEquivValue(ENAME, SeqAnalysis);

      // update SeqAnalysis if valid value is detected
      if ( EquivValue != CSMC_DBData::unspecDouble )
      {
        sAnalysis   Analysis;
        seqAnalysis SeqAnalysisSource;
        sAnalysis   AnalysisSource;
        
        AnalysisSource.Element        = ENAME.c_str();
        AnalysisSource.Concentration  = EquivValue;

        CIntfData::insert(SeqAnalysisSource,AnalysisSource);

        UPDATE_SEQ(&SeqAnalysisSource,AnalysisSource,&SeqAnalysis,Analysis,Element,std::string);
      }
    }
  }

  return result;
}


