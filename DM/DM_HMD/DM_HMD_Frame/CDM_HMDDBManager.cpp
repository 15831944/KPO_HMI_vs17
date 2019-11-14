#include "iSMC_DataDefinitions_s.hh"
#include "CSMC_EventLogFrameController.h"
#include "CDM_DataInterface_Impl.h"
#include "CDM_ProductManagementInterface_Impl.h"
#include "CDataConversion.h"
#include "iEventMessages_s.hh"

//GC, GT tables
#include "CGC_MEASUREMENT_TYPE.h"
#include "CGCH_CALC_MODE.h"
#include "CGCH_TREAT_TYPE.h"
#include "CGCH_EVENT_LOG.h"
#include "CGTH_PP_BLOWING.h"
#include "CGTH_PP_BASE_VAL.h"
#include "CGTH_PP_TEMP_CORR.h"
#include "CGTH_PP_BASE_VAL_STEP.h"
#include "CGTH_PP_INJECTION.h"

//HD tables
#include "CHD_SAMPLE.h"
#include "CHD_DELAYS.h"
#include "CHD_SAMPLE_ENTRY.h"
#include "CHD_SAMPLE_REF.h"
#include "CHDH_ACT_EVENT_RES.h"
#include "CHDH_ACTION.h"
#include "CHDH_GRADE_ANL.h"
#include "CHDH_GRADE.h"
#include "CHDH_HM_DATA_PHASE.h"
#include "CHDH_HM_PHASE_RES.h"
#include "CHDH_HM_RES.h"
#include "CHDH_HM_DATA.h"
#include "CHDH_HM_DATA_PRODPRAC.h"
#include "CHDH_PARAM_MATRIX.h"
#include "CHDH_PARAM.h"
#include "CHDH_PP_BLOWING.h"
#include "CHDH_PP_BASE_VAL.h"
#include "CHDH_PP_BASE_VAL_STEP.h"
#include "CHDH_PP_INJECTION.h"
#include "CHDH_PP_TEMP_CORR.h"

//PD tables
#include "CPD_LADLE.h"
#include "CPD_SAMPLE.h"
#include "CPD_SAMPLE_ENTRY.h"
#include "CPD_SAMPLE_REF.h"
#include "CPD_PLANTSTATUS.h"
#include "DEF_GC_ACTION_DEF.h"
#include "CEquipmentData.h"
#include "CDM_HMDDBManager.h"
#include "DEF_GC_MEASUREMENT_TYPE.h"
#include "CPD_LADLE_LIFE_DATA.h"
//-------------------------------------
#include "CPP_HM.h"
#include "CPD_DELAYS.h"
#include "CPD_HOT_METAL.h"
#include "CPD_HM_REF.h"
#include "CPDH_HM_RES.h"
#include "CPDH_ACT_EVENT_RES.h"
#include "CPDH_HM_DATA_PRODPRAC.h"
#include "CPDH_LANCE_DATA.h"
#include "CPDH_HM_DATA_PHASE.h"
#include "CPDH_HM_DATA.h"
#include "CPDH_HM_PHASE_RES.h"
#include "CPDH_ACTION.h"
#include "CPDH_CYCL_MEAS_DATA.h"
#include "CPDH_HM_DATA.h"
//#include "CPDH_ACTUAL_RES.h"
#include "CHDH_PARAM_MATRIX.h"
//#include "CPDH_HEAT_DATA.h"
//----------------- L3 tables ---------------
//#include "CT_HMD_L3_HEAT_REPORT.h"
//#include "CT_HMD_L3_DELAY_REPORT.h"

#include "CHeatStatusContainer.h"
#include "DEF_GC_HEAT_STATUS.h"
#include "CPD_PLANTSTATUS_PLANT.h"

#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_PLANTSTATUS.h"
#include "CGT_PARAM.h"
#include "DEF_GC_PLANTGROUP_DESC.h"
#include "CDM_EventHandler.h"



CDM_HMDDBManager::CDM_HMDDBManager(CDM_DBManagerTask* _task)
: CDM_DBManager(_task)
{
}

CDM_HMDDBManager::~CDM_HMDDBManager()
{
}

//copy PDH_CYCL_MEAS_DATA into HDH_CYCL_MEAS_DATA
bool CDM_HMDDBManager::copyHDHCyclMeasData(sHeatInfo &pHeatInfo, bool pCommit)
{
  bool result = (m_pDM_DBManagerTask != NULL);
  if (result)
  {
//    CHDH_CYCL_MEAS_DATA m_HDHCyclMeasData(m_pDM_DBManagerTask->getStdConnection());
//    result = result && m_HDHCyclMeasData.copy(pHeatInfo.HeatId, pHeatInfo.TreatId, pHeatInfo.Plant, pCommit, m_lastError);
  }
  return result;
}

void CDM_HMDDBManager::init()
{
  CDM_DBManager::init();
}

//copy PDH_HM_DATA into HDH_HM_DATA
bool CDM_HMDDBManager::copyHDHHMData(sHeatInfo &pHeatInfo, bool pCommit)
{
  bool result = (m_pDM_DBManagerTask != NULL);
  if (result)
  {
    CHDH_HM_DATA m_HDHHMData(m_pDM_DBManagerTask->getStdConnection());

    //Item already exist delete it -> delete all dependent items
/*    if (m_HDMHMData.exists(pHeatInfo.HeatId, pHeatInfo.TreatId, pHeatInfo.Plant))
    {
      CHDH_PP_BASE_VAL_STEP m_HDHPpBaseValStep(m_pDM_DBManagerTask->getStdConnection());
      CHDH_PP_BASE_VAL      m_HDHPpBaseVal(m_pDM_DBManagerTask->getStdConnection());
      CHDH_PP_BLOWING       m_HDHPpBlowing(m_pDM_DBManagerTask->getStdConnection());
      CHDH_PP_INJECTION     m_HDHPpInjection(m_pDM_DBManagerTask->getStdConnection());
      CHDH_PP_TEMP_CORR     m_HDHPpTempCorr(m_pDM_DBManagerTask->getStdConnection());
      long mPracNo = -1;


      if (result && m_HDHPpBaseValStep.exists(pHeatInfo.HeatId, pHeatInfo.TreatId, pHeatInfo.Plant))
        result = m_HDHPpBaseValStep.deleteRows();
      if (result && m_HDHPpBaseVal.exists(pHeatInfo.HeatId, pHeatInfo.TreatId, pHeatInfo.Plant))
        result = m_HDHPpBaseVal.deleteRows();
      if (result && m_HDHPpBlowing.exists(pHeatInfo.HeatId, pHeatInfo.TreatId, pHeatInfo.Plant))
        result = m_HDHPpBlowing.deleteRows();
      if (result && m_HDHPpInjection.exists(pHeatInfo.HeatId, pHeatInfo.TreatId, pHeatInfo.Plant))
        result = m_HDHPpInjection.deleteRows();
      if (result && m_HDHPpTempCorr.exists(pHeatInfo.HeatId, pHeatInfo.TreatId, pHeatInfo.Plant))
        result = m_HDHPpTempCorr.deleteRows();
    }

    result = result && m_HDMHMData.copy(pHeatInfo.HeatId, pHeatInfo.TreatId, pHeatInfo.Plant, pCommit, m_lastError);
*/
    }

  return result;
}

bool CDM_HMDDBManager::copyHDHPpBaseVal(sHeatInfo &pHeatInfo, bool pCommit)
{
  bool result = (m_pDM_DBManagerTask != NULL);
  if (result)
  {
    // put code
  }

  return result;
}

bool CDM_HMDDBManager::copyHDHPpBaseValStep(sHeatInfo &pHeatInfo, bool pCommit)
{
  bool result = (m_pDM_DBManagerTask != NULL);
  if (result)
  {
    // put code
  }

  return result;
}

bool CDM_HMDDBManager::copyHDHPpBlowing(sHeatInfo &pHeatInfo, bool pCommit)
{
  bool result = (m_pDM_DBManagerTask != NULL);
  if (result)
  {
    // put code
  }

  return result;
}

bool CDM_HMDDBManager::copyHDHPpInjection(sHeatInfo &pHeatInfo, bool pCommit)
{
  bool result = (m_pDM_DBManagerTask != NULL);
  if (result)
  {
    // put code
  }

  return result;
}

bool CDM_HMDDBManager::copyHDHPpTempCorr(sHeatInfo &pHeatInfo, bool pCommit)
{
  bool result = (m_pDM_DBManagerTask != NULL);
  if (result)
  {
    // put code
  }

  return result;
}

//handle data in PD_ tables when Announcement occures
bool CDM_HMDDBManager::handlePDTablesOnAnnounce(sHMInfo &pHMInfo, sDate &pTreatStartOper,sDate &pTreatEndOper,bool pCommit)
{
  bool result = (m_pDM_DBManagerTask != NULL);
  if (result)
  {
//Copy data into HD tables in ARCHIVER

//  Table:  PP_HM
    CPP_HM m_PPHM(m_pDM_DBManagerTask->getStdConnection());
    result = m_PPHM.doAnnouncement(pHMInfo.HMId,pHMInfo.ProdOrderId,pHMInfo.PlantNo,pHMInfo.onRequest,pHMInfo.HotMetalCounter);

//  Table: PDH_HM_REF
    CPD_HM_REF m_PDHMRef(m_pDM_DBManagerTask->getStdConnection());
    result = m_PDHMRef.doAnnouncement(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.PlantNo);

//  Table: PDH_HM_DATA
    CPDH_HM_DATA m_PDHHMData(m_pDM_DBManagerTask->getStdConnection());
    result = m_PDHHMData.doAnnouncement(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant,pTreatStartOper,pTreatEndOper,pHMInfo.HotMetalCounter,pHMInfo.ProdOrderId,pHMInfo.LadleFreeBoard,pHMInfo.HMWeight,pHMInfo.SlagWeight,pHMInfo.HMTemp,pHMInfo.SAim,pHMInfo.CalcMode,pHMInfo.TreatType,pHMInfo.SAct);

//  Table: PDH_HM_DATA_PHASE
    CPDH_HM_DATA_PHASE m_PDHHMDataPhase(m_pDM_DBManagerTask->getStdConnection());
    //result = m_PDHHMDataPhase.insert_PDH_HM_DATA_PHASE(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant,true); bcoz of this we have duplicate entries for preparation phase.

//  Table: PDH_HM_DATA_PRODPRAC
    CPDH_HM_DATA_PRODPRAC m_PDHHMDataProdPrac(m_pDM_DBManagerTask->getStdConnection());
    result = m_PDHHMDataProdPrac.doAnnouncement(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant,"Temp_Corr");
		result = m_PDHHMDataProdPrac.doAnnouncement(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant,"Blowing");
		result = m_PDHHMDataProdPrac.doAnnouncement(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant,"BaseVal");
		result = m_PDHHMDataProdPrac.doAnnouncement(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant,"Injection");

//automaticly fill the delays
//result = result && CDM_DBManager::AutomaticlyFillRelativeDelays( mHeatInfo.Plant,mHeatInfo.PlantNo,mHeatInfo.HeatId,mHeatInfo.TreatId,mUserCode,false );
  }

  return result;
}

//handle data in HD_ tables when Announcement occures
bool CDM_HMDDBManager::handleHDTablesOnCancelHeat(sHMInfo &pHMInfo, bool pCommit)
{
  bool result = (m_pDM_DBManagerTask != NULL);
  if (result)
  {

//Delete or update data into HD tables in ARCHIVER


  //Table:  HDH_PP_TEMP_CORR
    CHDH_PP_TEMP_CORR m_HDHPTCORR(m_pDM_DBManagerTask->getStdConnection());
    result = m_HDHPTCORR.delete_HDH_PP_TEMP_CORR(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant);

		//  Table: HDH_PP_INJECTION
		CHDH_PP_INJECTION m_HDHPPInjection(m_pDM_DBManagerTask->getStdConnection());
    result = result &&  m_HDHPPInjection.delete_HDH_PP_INJECTION(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant);

//  Table: HDH_PP_BLOWING
    CHDH_PP_BLOWING m_HDHPPBlowing(m_pDM_DBManagerTask->getStdConnection());
    result = m_HDHPPBlowing.delete_HDH_PP_BLOWING(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant);

//  Table: HDH_PP_BASE_VAL_STEP
    CHDH_PP_BASE_VAL_STEP m_HDHPPBVStep(m_pDM_DBManagerTask->getStdConnection());
    result = m_HDHPPBVStep.delete_HDH_PP_BASE_VAL_STEP(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant);

//  Table: HDH_PP_BASE_VAL
    CHDH_PP_BASE_VAL m_HDHBVal(m_pDM_DBManagerTask->getStdConnection());
    result = m_HDHBVal.delete_HDH_PP_BASE_VAL(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant);

//  Table: HDH_PARAM_MATRIX
    CHDH_PARAM_MATRIX m_HDHPMatrix(m_pDM_DBManagerTask->getStdConnection());
    result = m_HDHPMatrix.delete_HDH_PARAM_MATRIX(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant);

//  Table: HDH_PARAM
    CHDH_PARAM m_HDHParam(m_pDM_DBManagerTask->getStdConnection());
    result = m_HDHParam.delete_HDH_PARAM(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant);

//  Table: HDH_HM_DATA_PRODPRAC
    CHDH_HM_DATA_PRODPRAC m_HDHHMDPPrac(m_pDM_DBManagerTask->getStdConnection());
    result = m_HDHHMDPPrac.delete_HDH_HM_DATA_PRODPRAC(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant);

//  Table: HDH_HM_DATA
    CHDH_HM_DATA m_HDHHMData(m_pDM_DBManagerTask->getStdConnection());
    result = m_HDHHMData.delete_HDH_HM_DATA(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant);

//  Table: HDH_ACTION
    CHDH_ACTION m_HDHAction(m_pDM_DBManagerTask->getStdConnection());
    result = m_HDHAction.delete_HDH_ACTION(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant);

////  Table: HDH_PARAM_MATRIX
//    CPDH_ACTION m_PDHAction(m_pDM_DBManagerTask->getStdConnection());
//    result = m_PDHAction.doCancelHeat(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant);
	}

  return result;
}
//handle data in PD_ tables when Heat Departure occures
bool CDM_HMDDBManager::handlePDTablesOnHeatDeparture(sHMInfo &pHMInfo, bool pCommit,long pLadleNo, const std::string& pLadleType,long mDurSinceHeatStart,long mDurSinceHeatAnnounce)
{
  bool result = (m_pDM_DBManagerTask != NULL);
  if (result)
  {

		//sankar
		CPD_PLANTSTATUS m_PDPStatus(m_pDM_DBManagerTask->getStdConnection());
		if(m_PDPStatus.select(pHMInfo.Plant,pHMInfo.PlantNo,1))
		{
				pHMInfo.HMTemp= m_PDPStatus.getTEMP(1);
		}

//  Table:  PDH_HM_DATA
    CPDH_HM_DATA m_PDHHMData(m_pDM_DBManagerTask->getStdConnection());
    result = m_PDHHMData.doHeatDeparture(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant,pHMInfo.TreatEndOper,pHMInfo.HMWeight,pHMInfo.SlagWeight,pHMInfo.HMTemp);

//  Table: PDH_ACTION
    CPDH_ACTION m_PDHAction(m_pDM_DBManagerTask->getStdConnection());
    result = m_PDHAction.doHeatDeparture(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant,mDurSinceHeatStart,mDurSinceHeatAnnounce);

//  Table: PD_PLANTSTATUS sankar
		CHeatStatusContainer  HeatStatusContainer(m_pDM_DBManagerTask->getStdConnection());
		long htStatus = HeatStatusContainer.getHeatStatus(pHMInfo.Plant, DEF_GC_HEAT_STATUS::LadleDeparture );

		CPD_PLANTSTATUS m_PDPlantstatus(m_pDM_DBManagerTask->getStdConnection());

		//SANKAR
    //result = m_PDPlantstatus.update_PDplantStatus(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant,htStatus); 
    result = m_PDPlantstatus.doHeatDeparture(pHMInfo.Plant,pHMInfo.PlantNo,htStatus,1,2);

		CPD_PLANTSTATUS_PLANT PD_PLANTSTATUS_PLANT(m_pDM_DBManagerTask->getStdConnection());
		PD_PLANTSTATUS_PLANT.switchTreatmentPosition(pHMInfo.Plant,pHMInfo.PlantNo,1,2,true,m_lastError);
		PD_PLANTSTATUS_PLANT.resetPlantStatus(pHMInfo.Plant,pHMInfo.PlantNo,1,true,m_lastError);
		
		// Table: PDH_HM_DATA_PHASE --- update
		CPDH_HM_DATA_PHASE m_PDHDPhase(m_pDM_DBManagerTask->getStdConnection());
		result = m_PDHDPhase.update_AfterHeatDeparture(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant,false);

		//SARS
		long hmCounter = CSMC_DBData::unspecLong;
		CPP_HM PP_HM(m_pDM_DBManagerTask->getStdConnection());
		if(PP_HM.select(pHMInfo.HMId))
		{
			hmCounter = PP_HM.getHOTMETAL_COUNTER(1);
		}
		CPD_LADLE PD_LADLE(m_pDM_DBManagerTask->getStdConnection());
		if(PD_LADLE.select(pLadleNo, pLadleType))
		{
			PD_LADLE.setHOTMETAL_CNT_PREV(PD_LADLE.getHOTMETAL_CNT_ACT(1));
			PD_LADLE.setHOTMETAL_CNT_ACT(hmCounter);
			PD_LADLE.update();
		}

//  Table: CPD_LADLE_LIFE_DATA  // To Do later as LF
    /*CPD_LADLE_LIFE_DATA m_PDLLData(m_pDM_DBManagerTask->getStdConnection());
    result = m_PDLLData.incrLadlePartLife(pLadleNo,pLadleType,result);*/
		//setPlantEquipmentAge   // to do later
		//update data into HD tables in ARCHIVER
//  Table:  HDH_HM_DATA
    CHDH_HM_DATA m_HDHHMData(m_pDM_DBManagerTask->getStdConnection());
    result = m_HDHHMData.update_HeatDeparture(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant,pHMInfo.TreatEndOper,pHMInfo.HMWeight,pHMInfo.SlagWeight,pHMInfo.HMTemp);

//  Table: HDH_ACTION
    CHDH_ACTION m_HDHAction(m_pDM_DBManagerTask->getStdConnection());
    result = m_HDHAction.update_HeatDeparture(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant,mDurSinceHeatStart,mDurSinceHeatAnnounce);

 // Table: HDH_HM_DATA_PHASE --- update
		CHDH_HM_DATA_PHASE m_HDHDPhase(m_pDM_DBManagerTask->getStdConnection());
		result = m_HDHDPhase.update_AfterHeatDeparture(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant,false);

//automaticly fill the delays
//result = result && CDM_DBManager::AutomaticlyFillRelativeDelays( mHeatInfo.Plant,mHeatInfo.PlantNo,mHeatInfo.HeatId,mHeatInfo.TreatId,mUserCode,false );

  }

  return result;
}
//handle data in PD_ tables when Heat Start occures
bool CDM_HMDDBManager::handlePDTablesOnHeatStart(sHMInfo &pHMInfo, bool pCommit,long mDurSinceHeatStart,long mDurSinceHeatAnnounce)
{
  bool result = (m_pDM_DBManagerTask != NULL);
  if (result)
  {

//  Table:  PDH_HM_DATA
    CPDH_HM_DATA m_PDHHMData(m_pDM_DBManagerTask->getStdConnection());
    result = m_PDHHMData.doHeatStart(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant,pHMInfo.TreatEndOper);

//  Table: PDH_ACTION
    CPDH_ACTION m_PDHAction(m_pDM_DBManagerTask->getStdConnection());
    result = m_PDHAction.doHeatStart(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant,mDurSinceHeatStart,mDurSinceHeatAnnounce);

//  Table: PD_PLANTSTATUS sankar
		CHeatStatusContainer  HeatStatusContainer(m_pDM_DBManagerTask->getStdConnection());
		long htStatus = HeatStatusContainer.getHeatStatus(pHMInfo.Plant, DEF_GC_HEAT_STATUS::TreatmentStart );
		CPD_PLANTSTATUS m_PDPlantstatus(m_pDM_DBManagerTask->getStdConnection());
    result = m_PDPlantstatus.OnHeatStart(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant,htStatus);

		//update data into HD tables in ARCHIVER
		
//	Table: HDH_HM_DATA
		CHDH_HM_DATA m_HDHHMData(m_pDM_DBManagerTask->getStdConnection());
		result=m_HDHHMData.update_HeatStart(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant,pHMInfo.TreatEndOper);

//  Table: HDH_ACTION
    CHDH_ACTION m_HDHAction(m_pDM_DBManagerTask->getStdConnection());
    result = m_HDHAction.update_HeatStart(pHMInfo.HMId,pHMInfo.TreatId,pHMInfo.Plant,mDurSinceHeatStart,mDurSinceHeatAnnounce);
//automaticly fill the delays
//result = result && CDM_DBManager::AutomaticlyFillRelativeDelays( mHeatInfo.Plant,mHeatInfo.PlantNo,mHeatInfo.HeatId,mHeatInfo.TreatId,mUserCode,false );
  }

  return result;
}
bool CDM_HMDDBManager::handlePDTablesOnDelayStatus(sHeatInfo &pHeatInfo, CDateTime &pStartTime, CDateTime &pEndTime, const string &pCode, const string &pUser, const string &pDelayComment,long Status, bool pCommit)
{
	bool RetValue = (m_pDM_DBManagerTask != NULL);
	if (RetValue)
	{
		CPD_DELAYS m_PDDelays(m_pDM_DBManagerTask->getStdConnection());

    if ( Status == DEF_GEN_STATES::Delete )
    {
      //check if Delay exists -> set exipiration date
      RetValue = RetValue && m_PDDelays.expireDelay(pHeatInfo.Plant, pHeatInfo.PlantNo, pCode, pStartTime, pUser, pCommit, m_lastError);
    }
    else
    {
      //check if Delay exists -> update existing, otherwise insert
      //RetValue = RetValue && m_PDDelays.updateOrInsert(pHeatInfo.HeatId, pHeatInfo.TreatId, pHeatInfo.Plant, pHeatInfo.PlantNo, pCode, pStartTime, pEndTime, pUser, pDelayComment, pCommit, m_lastError);      
			//sankar
      RetValue = RetValue && m_PDDelays.updateOrInsertHMD(pHeatInfo.HeatId, pHeatInfo.TreatId, pHeatInfo.Plant, pHeatInfo.PlantNo, pCode, pStartTime, pEndTime, pUser, pDelayComment, pCommit, m_lastError);      
		}

	}
	return RetValue;
}
//process Heat announcement
bool CDM_HMDDBManager::evHeatAnnouncement(CEventMessage &pMsg)
{
  bool result;
  sHMInfo mHMInfo;

  CDM_DataInterface_Impl *dataProvider = m_pDM_DBManagerTask->getpDataInterface();

  mHMInfo.ProdOrderId = pMsg.getOrderID() ; //checkStringParam(pMsg.getOrderID()); sankar
  mHMInfo.HMId = checkStringParam(pMsg.getHeatID());
  mHMInfo.TreatId = "01"; // URGENT - after preliminary testing, make the treatid dynamic based on number of treatments!
  mHMInfo.Plant = sPlantConst;
	string mPlantId =checkStringParam(pMsg.getPlantID());
	string mPlantno = mPlantId.substr(4,1);
	mHMInfo.PlantNo= atol(mPlantno.c_str());  
  mHMInfo.HotMetalCounter = dataProvider->getLong(pMsg.getDataKey(), DATA::HMCounter);
  mHMInfo.TreatEndOper = checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::TreatEndAim), true);
	mHMInfo.TreatStartOper = checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::TreatStartAim), true);
  mHMInfo.HMWeight = dataProvider->getDouble(pMsg.getDataKey(), DATA::HMWeight);
  mHMInfo.SlagWeight = dataProvider->getDouble(pMsg.getDataKey(), DATA::SlagMass);
  mHMInfo.HMTemp = dataProvider->getDouble(pMsg.getDataKey(), DATA::HMTemp);
  mHMInfo.SAim = dataProvider->getDouble(pMsg.getDataKey(), DATA::SulphurAim);
  mHMInfo.SAct = dataProvider->getDouble(pMsg.getDataKey(), DATA::SulphurAct);
  mHMInfo.LadleFreeBoard = dataProvider->getLong(pMsg.getDataKey(), DATA::LadleFreeBoard);
  mHMInfo.CalcMode = dataProvider->getLong(pMsg.getDataKey(), DATA::HMDCalcMode);
  mHMInfo.TreatType = dataProvider->getLong(pMsg.getDataKey(), DATA::HMDTreatType);
  mHMInfo.onRequest = dataProvider->getLong(pMsg.getDataKey(), DATA::ManuallyEntered);

  //Sankar
  sDate TreatEndOper = dataProvider->getDate(pMsg.getDataKey().c_str(),DATA::TreatEndAim);
  sDate TreatStartOper = dataProvider->getDate(pMsg.getDataKey().c_str(),DATA::TreatStartAim);


  result = handlePDTablesOnAnnounce(mHMInfo, TreatStartOper,TreatEndOper,false);
  if (result)
  {
    m_pDM_DBManagerTask->getStdConnection()->commit();
    pMsg.setHeatID(mHMInfo.HMId);
    pMsg.setTreatID(mHMInfo.TreatId);
    pMsg.setOrderID(mHMInfo.ProdOrderId);
  }
  else
  {
    m_pDM_DBManagerTask->getStdConnection()->rollback();
    string mHMIClientId = dataProvider->getString(pMsg.getDataKey(), DATA::HMIClientId);
    CDM_DBManager::handleError(pMsg, mHMIClientId);
  }

  return result;
}

//Process Cancel Heat
bool CDM_HMDDBManager::evCancelHeat(CEventMessage &pMsg)
{
bool result = true;
  //sHeatInfo mHeatInfo;
	sHMInfo mHMInfo;
  CDM_DataInterface_Impl *dataProvider = m_pDM_DBManagerTask->getpDataInterface();
  mHMInfo.HMId			= checkStringParam(pMsg.getHeatID());
  mHMInfo.TreatId			= checkStringParam(pMsg.getTreatID());
  mHMInfo.Plant				= sPlantConst;   //checkStringParam(pMsg.getPlantID());
	string mPlantId =checkStringParam(pMsg.getPlantID());
	string mPlantno = mPlantId.substr(4,1);
	mHMInfo.PlantNo= atol(mPlantno.c_str()); 
  string mHeatCustId;
  
//Delete or update data into HD tables in ARCHIVER
		result=handleHDTablesOnCancelHeat(mHMInfo,false);

  //Table:  PP_HM ---update the field PLANNED=1
    CPP_HM m_PPHM(m_pDM_DBManagerTask->getStdConnection());
    result = m_PPHM.doCancelHeat(mHMInfo.HMId,mHMInfo.ProdOrderId,mHMInfo.PlantNo);

		//  Table: PD_PLANTSTATUS sankar
		CHeatStatusContainer  HeatStatusContainer(m_pDM_DBManagerTask->getStdConnection());
		long htStatus = 0; //HeatStatusContainer.getHeatStatus(pHMInfo.Plant, DEF_GC_HEAT_STATUS::??? );
		CPD_PLANTSTATUS m_PDPlantstatus(m_pDM_DBManagerTask->getStdConnection());
    result = result &&  m_PDPlantstatus.doHeatCancel(mHMInfo.Plant,mHMInfo.PlantNo,htStatus);
		
    CPD_PLANTSTATUS_PLANT PD_PLANTSTATUS_PLANT(m_pDM_DBManagerTask->getStdConnection());
		result = result && PD_PLANTSTATUS_PLANT.resetPlantStatus(mHMInfo.Plant,mHMInfo.PlantNo, 1, false, m_lastError); //sankar

//  Table: PDH_HM_DATA --- delete row
    CPDH_HM_DATA m_PDHHMData(m_pDM_DBManagerTask->getStdConnection());
    result = m_PDHHMData.doCancelHeat(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant);

//  Table: PDH_HM_REF --- delete row
    CPD_HM_REF m_PDHMRef(m_pDM_DBManagerTask->getStdConnection());
    result = m_PDHMRef.doCancelHeat(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.PlantNo);

//  Table: PDH_HM_DATA_PRODPRAC ----delete row
    CPDH_HM_DATA_PRODPRAC m_PDHHMDataProdPrac(m_pDM_DBManagerTask->getStdConnection());
    result = m_PDHHMDataProdPrac.doCancelHeat(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant);

//  Table: PDH_ACTION ---delete row
    CPDH_ACTION m_PDHAction(m_pDM_DBManagerTask->getStdConnection());
    result = m_PDHAction.doCancelHeat(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant);


		//sankar - as analysis & Temp will not be deleted because it comes from L3
	 /*long hmCounter = CSMC_DBData::unspecLong;
	 long smplRefCounter = CSMC_DBData::unspecLong;
	 long smplCounterHM = CSMC_DBData::unspecLong;
	 long smplCounterTemp = CSMC_DBData::unspecLong;

   CPP_HM   m_pPP_HHM(m_pDM_DBManagerTask->getStdConnection());
   if( m_pPP_HHM.select( mHMInfo.HMId ) )
   {
	   hmCounter = m_pPP_HHM.getHOTMETAL_COUNTER(1);
   }

   CPD_HOT_METAL   m_pPD_HOT_METAL(m_pDM_DBManagerTask->getStdConnection());
   if( m_pPD_HOT_METAL.select( hmCounter) )
   {
	   smplRefCounter = m_pPD_HOT_METAL.getSAMPLE_REF(1);
   }

    CPD_SAMPLE_REF m_PDSmplRef(m_pDM_DBManagerTask->getStdConnection());
    if( m_PDSmplRef.select( smplRefCounter) )
    {
	   smplCounterHM = m_PDSmplRef.getHOT_METAL(1);
	   smplCounterTemp = m_PDSmplRef.getTEMP(1);
    }

		m_PDSmplRef.updateSAMPLE_REF(smplRefCounter,CSMC_DBData::unspecLong,DEF_GC_MEASUREMENT_TYPE::HM);
		m_PDSmplRef.updateSAMPLE_REF(smplRefCounter,CSMC_DBData::unspecLong,DEF_GC_MEASUREMENT_TYPE::Temp);


    CPD_SAMPLE m_PDSmpl(m_pDM_DBManagerTask->getStdConnection());
    CPD_SAMPLE_ENTRY m_PDSmplEntry(m_pDM_DBManagerTask->getStdConnection());

		if (smplCounterHM != CSMC_DBData::unspecLong)
		{
			m_PDSmplEntry.deleteSample(smplCounterHM);
			m_PDSmpl.deleteRow(smplCounterHM);
		}

		if (smplCounterTemp != CSMC_DBData::unspecLong)
		{
			m_PDSmplEntry.deleteSample(smplCounterTemp);
			m_PDSmpl.deleteRow(smplCounterTemp);
		}
		*/
		m_pDM_DBManagerTask->getStdConnection()->commit();

		//automaticly fill the delays
//result = result && CDM_DBManager::AutomaticlyFillRelativeDelays( mHeatInfo.Plant,mHeatInfo.PlantNo,mHeatInfo.HeatId,mHeatInfo.TreatId,mUserCode,false );
  
	//CDM_DBManager::splitPlantPlantNo(mHeatInfo.Plant, mHeatInfo.Plant, mHeatInfo.PlantNo);

  ////get CarId from PDL bbecause in event interface it is not exist
  ///*CPDL_HEAT_DATA   m_pPDL_Heat_Data(m_pDM_DBManagerTask->getStdConnection());
  //long   mCarNo = 1;

  //CPDL_HEAT_DATA   m_pPDLHeatData(m_pDM_DBManagerTask->getStdConnection());
  //if( m_pPDLHeatData.select( mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant ) )
  //{
	 // mCarNo = m_pPDLHeatData.getCARNO(1);
  //}*/

  ////Schedule Heat
  //result = CDM_DBManager::heatScheduleOnCancelHeat(mHeatInfo, mHeatCustId, false);

  ////Add Action
  ////result = result && insertAction(pMsg.getProductID(),mHeatInfo,DEF_GC_ACTION_DEF::Cancel,false);

  //if (result)
  //  m_pDM_DBManagerTask->getStdConnection()->commit();
  //else
  //{
  //  m_pDM_DBManagerTask->getStdConnection()->rollback();
  //  string mHMIClientId = dataProvider->getString(pMsg.getDataKey(), DATA::HMIClientId);
  //  CDM_DBManager::handleError(pMsg, mHMIClientId);
  //}
  return result;

}

//Process Departure heat
bool CDM_HMDDBManager::evHeatDeparture(CEventMessage &pMsg)
{
bool result = true;

  //sHeatInfo mHeatInfo;
	sHMInfo mHMInfo;
  CDM_DataInterface_Impl *dataProvider = m_pDM_DBManagerTask->getpDataInterface();
  mHMInfo.HMId		= checkStringParam(pMsg.getHeatID());
  mHMInfo.TreatId		= "01";   // checkStringParam(pMsg.getTreatID());
  mHMInfo.Plant			= sPlantConst;      //checkStringParam(pMsg.getPlantID());
	string mPlantId =checkStringParam(pMsg.getPlantID());
	string mPlantno = mPlantId.substr(4,1);
	mHMInfo.PlantNo= atol(mPlantno.c_str());  
	mHMInfo.ProdOrderId="";
	mHMInfo.TreatEndOper=checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::TreatEndAim),true);
  string mOrderId		= checkStringParam(pMsg.getOrderID());
  string mUserCode		= checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::UserCode));
	mHMInfo.HMWeight = dataProvider->getDouble(pMsg.getDataKey(), DATA::HMWeight);
  mHMInfo.SlagWeight = dataProvider->getDouble(pMsg.getDataKey(), DATA::SlagMass);
  mHMInfo.HMTemp = dataProvider->getDouble(pMsg.getDataKey(), DATA::HMTemp);
  mHMInfo.SAim = dataProvider->getDouble(pMsg.getDataKey(), DATA::SulphurAim);
  mHMInfo.SAct = dataProvider->getDouble(pMsg.getDataKey(), DATA::SulphurAct);
  mHMInfo.LadleFreeBoard = dataProvider->getLong(pMsg.getDataKey(), DATA::LadleFreeBoard);
  mHMInfo.CalcMode = dataProvider->getLong(pMsg.getDataKey(), DATA::HMDCalcMode);
  mHMInfo.TreatType = dataProvider->getLong(pMsg.getDataKey(), DATA::HMDTreatType);
  mHMInfo.onRequest = dataProvider->getLong(pMsg.getDataKey(), DATA::ManuallyEntered);

	string ldNo = checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::LadleNo));
	long mLadleNo = CDataConversion::StringToLong(ldNo);

	string mLadleType    = checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::LadleType));

	long mDurSinceHeatStart = dataProvider->getLong(pMsg.getDataKey(),DATA::DurSinceHeatStart);
	long mDurSinceHeatAnnounce = dataProvider->getLong(pMsg.getDataKey(),DATA::DurSinceHeatAnnounce);
	if (mDurSinceHeatStart<0)
		mDurSinceHeatStart=0;
	if (mDurSinceHeatAnnounce<0)
		mDurSinceHeatAnnounce=0;

	 //sankar heat departure come more than one time then it will block othewise age of equipment will grow automatically
		CPD_PLANTSTATUS PD_PLANTSTATUS(m_pDM_DBManagerTask->getStdConnection());
		if(PD_PLANTSTATUS.select(mHMInfo.Plant,mHMInfo.PlantNo,1))
		{
				long statusNO = PD_PLANTSTATUS.getHEATSTATUSNO(1);
				CHeatStatusContainer  hsContainer(m_pDM_DBManagerTask->getStdConnection());
				long htStatus = hsContainer.getHeatStatus(mHMInfo.Plant, DEF_GC_HEAT_STATUS::LadleDeparture );

				if(statusNO == htStatus)
					return true;
		}

	//sankar
	double heatTotalWeight = 0.;
	CPDH_HM_DATA m_PDH_hmData(m_pDM_DBManagerTask->getStdConnection());
	if(m_PDH_hmData.select(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant))
	{
		  if(!m_PDH_hmData.isNull(CPDH_HM_DATA::HM_WEIGHT_START,1) )
			    heatTotalWeight = m_PDH_hmData.getHM_WEIGHT_START(1);

		  if(!m_PDH_hmData.isNull(CPDH_HM_DATA::HM_WEIGHTSTART_MOD,1)  && m_PDH_hmData.getHM_WEIGHTSTART_MOD(1) > 0)
			    heatTotalWeight = m_PDH_hmData.getHM_WEIGHTSTART_MOD(1);

		  if(!m_PDH_hmData.isNull(CPDH_HM_DATA::HM_WEIGHT_END,1)  && m_PDH_hmData.getHM_WEIGHT_END(1) > 0)
			    heatTotalWeight = m_PDH_hmData.getHM_WEIGHT_END(1);
	}

	sHeatInfo HeatInfo;
	HeatInfo.HeatId =  mHMInfo.HMId;
	HeatInfo.TreatId =  mHMInfo.TreatId;
	HeatInfo.Plant =  mHMInfo.Plant;
	HeatInfo.PlantNo = mHMInfo.PlantNo;
  CDM_DBManager::setEquipmentAgeByHeat(HeatInfo, false);
  CDM_DBManager::setEquipmentAgeByWeight(HeatInfo, heatTotalWeight, false);



	result = handlePDTablesOnHeatDeparture(mHMInfo, false,mLadleNo,mLadleType,mDurSinceHeatStart,mDurSinceHeatAnnounce);
	// L3 Tables
	// Table: T_HMD_L3_HEAT_REPORT
	//CT_HMD_L3_HEAT_REPORT m_CTHMDL3HEATREPORT(m_pDM_DBManagerTask->getStdConnection());
	//result = m_CTHMDL3HEATREPORT.HMD_L3_Report(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant);
  if (result)
  {
    m_pDM_DBManagerTask->getStdConnection()->commit();
    pMsg.setHeatID(mHMInfo.HMId);
    pMsg.setTreatID(mHMInfo.TreatId);
    pMsg.setOrderID(mHMInfo.ProdOrderId);
  }
  else
  {
    m_pDM_DBManagerTask->getStdConnection()->rollback();
    string mHMIClientId = dataProvider->getString(pMsg.getDataKey(), DATA::HMIClientId);
    CDM_DBManager::handleError(pMsg, mHMIClientId);
  }

  return result;
}


//Process heat start
bool CDM_HMDDBManager::evHeatStart(CEventMessage &pMsg)
{
bool result = true;

  //sHeatInfo mHeatInfo;
	sHMInfo mHMInfo;
  CDM_DataInterface_Impl *dataProvider = m_pDM_DBManagerTask->getpDataInterface();
  mHMInfo.HMId		= checkStringParam(pMsg.getHeatID());
  mHMInfo.TreatId		= "01";  //checkStringParam(pMsg.getTreatID());
  mHMInfo.Plant			=  sPlantConst;  //checkStringParam(pMsg.getPlantID());
	
	string mPlantId =pMsg.getPlantID();
	string mPlantno = mPlantId.substr(4,1);
	mHMInfo.PlantNo= atol(mPlantno.c_str()); 

	mHMInfo.ProdOrderId="";
	mHMInfo.TreatEndOper=checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::TreatEndAim),true);
  string mOrderId		= checkStringParam(pMsg.getOrderID());
  string mUserCode		= checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::UserCode));
	long mDurSinceHeatStart = dataProvider->getLong(pMsg.getDataKey(),DATA::DurSinceHeatStart);
	long mDurSinceHeatAnnounce = dataProvider->getLong(pMsg.getDataKey(),DATA::DurSinceHeatAnnounce);
	if (mDurSinceHeatStart<0)
		mDurSinceHeatStart=0;
	if (mDurSinceHeatAnnounce<0)
		mDurSinceHeatAnnounce=0;

	result = handlePDTablesOnHeatStart(mHMInfo, false,mDurSinceHeatStart,mDurSinceHeatAnnounce);
  if (result)
  {
    m_pDM_DBManagerTask->getStdConnection()->commit();
    pMsg.setHeatID(mHMInfo.HMId);
    pMsg.setTreatID(mHMInfo.TreatId);
    pMsg.setOrderID(mHMInfo.ProdOrderId);
  }
  else
  {
    m_pDM_DBManagerTask->getStdConnection()->rollback();
    string mHMIClientId = dataProvider->getString(pMsg.getDataKey(), DATA::HMIClientId);
    CDM_DBManager::handleError(pMsg, mHMIClientId);
  }

  return result;
}

bool CDM_HMDDBManager::evHeatEnd(CEventMessage &pMsg)
{
bool result = true;

  //sHeatInfo mHeatInfo;
	sHMInfo mHMInfo;
  CDM_DataInterface_Impl *dataProvider = m_pDM_DBManagerTask->getpDataInterface();
  mHMInfo.HMId		= checkStringParam(pMsg.getHeatID());
  mHMInfo.TreatId		= "01";  //checkStringParam(pMsg.getTreatID());
  mHMInfo.Plant			=  sPlantConst;  //checkStringParam(pMsg.getPlantID());
	
	string mPlantId =pMsg.getPlantID();
	string mPlantno = mPlantId.substr(4,1);
	mHMInfo.PlantNo= atol(mPlantno.c_str()); 

	mHMInfo.ProdOrderId="";
	mHMInfo.TreatEndOper=checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::TreatEndAim),true);
  string mOrderId		= checkStringParam(pMsg.getOrderID());
  string mUserCode		= checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::UserCode));
	long mDurSinceHeatStart = dataProvider->getLong(pMsg.getDataKey(),DATA::DurSinceHeatStart);
	long mDurSinceHeatAnnounce = dataProvider->getLong(pMsg.getDataKey(),DATA::DurSinceHeatAnnounce);
	if (mDurSinceHeatStart<0)
		mDurSinceHeatStart=0;
	if (mDurSinceHeatAnnounce<0)
		mDurSinceHeatAnnounce=0;

  CPDH_ACTION m_PDHAction(m_pDM_DBManagerTask->getStdConnection());
  result = m_PDHAction.doHeatEnd(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant,mDurSinceHeatStart,mDurSinceHeatAnnounce);

  if (result)
  {
    m_pDM_DBManagerTask->getStdConnection()->commit();
    pMsg.setHeatID(mHMInfo.HMId);
    pMsg.setTreatID(mHMInfo.TreatId);
    pMsg.setOrderID(mHMInfo.ProdOrderId);
  }
  else
  {
    m_pDM_DBManagerTask->getStdConnection()->rollback();
    string mHMIClientId = dataProvider->getString(pMsg.getDataKey(), DATA::HMIClientId);
    CDM_DBManager::handleError(pMsg, mHMIClientId);
  }

  return result;
}

bool CDM_HMDDBManager::evDelayStatus(CEventMessage &pMsg)
{
  bool result = true;
  
  sHeatInfo mHeatInfo;
  CDM_DataInterface_Impl *dataProvider = m_pDM_DBManagerTask->getpDataInterface();
  mHeatInfo.HeatId	= checkStringParam(pMsg.getHeatID());
  mHeatInfo.TreatId	= checkStringParam(pMsg.getTreatID());
  mHeatInfo.Plant		= checkStringParam(pMsg.getPlantID());
  string mUserCode	= checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::UserCode));	
  CDateTime	 mStartTime	= dataProvider->getDate(pMsg.getDataKey().c_str(), DATA::DelayStartDate);
  CDateTime	 mEndTime	= dataProvider->getDate(pMsg.getDataKey().c_str(), DATA::DelayEndDate);
  string mDelayCode	= checkStringParam(dataProvider->getString(pMsg.getDataKey(), DATA::DelayCode));
	//string mCommentOperator	= checkStringParam(dataProvider->getString(pMsg.getDataKey(), DATA::DelayDescription));
	string mCommentOperator	= checkStringParam(dataProvider->getString(pMsg.getDataKey(), DATA::Comment));
  CDM_DBManager::splitPlantPlantNo(mHeatInfo.Plant, mHeatInfo.Plant, mHeatInfo.PlantNo);
	long Status = dataProvider->getLong(pMsg.getDataKey().c_str(), DATA::Status);

  result = handlePDTablesOnDelayStatus(mHeatInfo, mStartTime, mEndTime, mDelayCode, mUserCode,mCommentOperator,Status, false);

  CHD_DELAYS m_HDDelay(m_pDM_DBManagerTask->getStdConnection());
  result = result && m_HDDelay.copy_HMD(mHeatInfo.Plant,mHeatInfo.PlantNo,false,m_lastError);

  if (result)
    m_pDM_DBManagerTask->getStdConnection()->commit();
  else
  {
    m_pDM_DBManagerTask->getStdConnection()->rollback();
    string mHMIClientId = dataProvider->getString(pMsg.getDataKey(), DATA::HMIClientId);
    CDM_DBManager::handleError(pMsg, mHMIClientId);
  }
  
  return result;
}

bool CDM_HMDDBManager::evHotMetalSampleTaken(CEventMessage &pMsg)
{
  bool result = true;
  CDateTime now;
  sHeatInfo mHeatInfo;
  CDM_DataInterface_Impl *dataProvider = m_pDM_DBManagerTask->getpDataInterface();
  mHeatInfo.HeatId	= checkStringParam(pMsg.getHeatID());
  mHeatInfo.TreatId	= "01"; //checkStringParam(pMsg.getTreatID());
  mHeatInfo.Plant		= sPlantConst; //checkStringParam(pMsg.getPlantID());
	string mPlantId =checkStringParam(pMsg.getPlantID());
	string mPlantno = mPlantId.substr(4,1);
	mHeatInfo.PlantNo= atol(mPlantno.c_str()); 
	string mProdOrderID = "";   //checkStringParam(dataProvider->getSample(pMsg.getDataKey(),DATA::OrderId));
  string mSampleData    = checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::SampleData));
	string mUserCode      = checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::UserCode));
	string mSampleUsable  = checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::SampleUsable));
	long mOnRequest     = dataProvider->getLong(pMsg.getDataKey(),DATA::ManuallyEntered);
	long mLadleNo     = dataProvider->getLong(pMsg.getDataKey(),DATA::LadleNo);
	string mLadleType    = checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::LadleType));

  //SampleCounter not used
  //long mSampleCounter = -1;//dataProvider->getLong(pMsg.getDataKey(),DATA::SampleCounter);
  //CDM_DBManager::splitPlantPlantNo(mHeatInfo.Plant, mHeatInfo.Plant, mHeatInfo.PlantNo);
	
  // Table: PD_SAMPLE  // ladleno, ladletype, measuretype, user --values needed
	CPD_SAMPLE m_PDSample(m_pDM_DBManagerTask->getStdConnection());
	long mSampleCounter = m_PDSample.getNextSAMPLE_COUNTER(); 
	CGC_MEASUREMENT_TYPE m_GCMeasumentType(m_pDM_DBManagerTask->getStdConnection());
	long mMeasTypeNo = DEF_GC_MEASUREMENT_TYPE::HM;
	result = result && m_PDSample.insertPSSample(mSampleCounter,mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,mHeatInfo.PlantNo,mLadleNo,mLadleType,mMeasTypeNo,now.assDate(),"",false,m_lastError);
  

  //Update of PD_PLANT_STATUS when Temperature and sample taken
	//sankar not required
	//CPD_PLANTSTATUS m_PDPStatus(m_pDM_DBManagerTask->getStdConnection());
  //result  = result && m_PDPStatus.update_PDplantStatus(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,110);
  //result = CDM_DBManager::copyHDSamples(mHeatInfo, mSampleCounter, false);

  if (result)
    m_pDM_DBManagerTask->getStdConnection()->commit();
  else
  {
    m_pDM_DBManagerTask->getStdConnection()->rollback();
    string mHMIClientId = dataProvider->getString(pMsg.getDataKey(), DATA::HMIClientId);
    CDM_DBManager::handleError(pMsg, mHMIClientId);
  }

  return result;
}

bool CDM_HMDDBManager::evSlagSampleTaken(CEventMessage &pMsg)
{
  bool result = true;
  CDateTime now;
  sHeatInfo mHeatInfo;
  CDM_DataInterface_Impl *dataProvider = m_pDM_DBManagerTask->getpDataInterface();
  mHeatInfo.HeatId	= checkStringParam(pMsg.getHeatID());
  mHeatInfo.TreatId	= "01"; //checkStringParam(pMsg.getTreatID());
  mHeatInfo.Plant		= sPlantConst; //checkStringParam(pMsg.getPlantID());
	

	string mPlantId =pMsg.getPlantID();
	string mPlantno = mPlantId.substr(4,1);
	mHeatInfo.PlantNo= atol(mPlantno.c_str()); 

	string mProdOrderID = "";   //checkStringParam(dataProvider->getSample(pMsg.getDataKey(),DATA::OrderId));
  string mSampleData    = checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::SampleData));
	string mUserCode      = checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::UserCode));
	string mSampleUsable  = checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::SampleUsable));
	long mOnRequest     = dataProvider->getLong(pMsg.getDataKey(),DATA::ManuallyEntered);
	long mLadleNo     = dataProvider->getLong(pMsg.getDataKey(),DATA::LadleNo);
	string mLadleType    = checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::LadleType));

  //SampleCounter not used
  //long mSampleCounter = -1;//dataProvider->getLong(pMsg.getDataKey(),DATA::SampleCounter);
  //CDM_DBManager::splitPlantPlantNo(mHeatInfo.Plant, mHeatInfo.Plant, mHeatInfo.PlantNo);
	
  // Table: PD_SAMPLE  // ladleno, ladletype, measuretype, user --values needed
	CPD_SAMPLE m_PDSample(m_pDM_DBManagerTask->getStdConnection());
	long mSampleCounter = m_PDSample.getNextSAMPLE_COUNTER(); 
	CGC_MEASUREMENT_TYPE m_GCMeasumentType(m_pDM_DBManagerTask->getStdConnection());
	long mMeasTypeNo = DEF_GC_MEASUREMENT_TYPE::Slag;
	result = result && m_PDSample.insertPSSample(mSampleCounter,mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,mHeatInfo.PlantNo,mLadleNo,mLadleType,mMeasTypeNo,now.assDate(),"",false,m_lastError);
  

  if (result)
    m_pDM_DBManagerTask->getStdConnection()->commit();
  else
  {
    m_pDM_DBManagerTask->getStdConnection()->rollback();
    string mHMIClientId = dataProvider->getString(pMsg.getDataKey(), DATA::HMIClientId);
    CDM_DBManager::handleError(pMsg, mHMIClientId);
  }

  return result;
}

bool CDM_HMDDBManager::evTempMeasurement(CEventMessage &pMsg)
{
bool result = true;
CDateTime now;
	sHeatInfo mHeatInfo;
  CDM_DataInterface_Impl *dataProvider = m_pDM_DBManagerTask->getpDataInterface();
  mHeatInfo.HeatId	= checkStringParam(pMsg.getHeatID());
  mHeatInfo.TreatId	= "01";   //checkStringParam(pMsg.getTreatID());
  mHeatInfo.Plant		= sPlantConst;
  string mPlantId =checkStringParam(pMsg.getPlantID());
	string mPlantno = mPlantId.substr(4,1);
	mHeatInfo.PlantNo= atol(mPlantno.c_str());  
	//string HMDLancePos      = checkStringParam(dataProvider->getString(Event.getDataKey(),DATA::LancePos));
	/*string HMDBlowingMode   = checkStringParam(dataProvider->getString(Event.getDataKey(),DATA::HMDBlowingMode));
	string HMDBlowRateMg      = checkStringParam(dataProvider->getString(Event.getDataKey(),DATA::HMDBlowingRateMg));
	string HMDBlowingRateCarbide      = checkStringParam(dataProvider->getString(Event.getDataKey(),DATA::HMDBlowingRateCarbide));
	string HMDBlowMg      = checkStringParam(dataProvider->getString(Event.getDataKey(),DATA::HMDBlowMg));
	string HMDDeslaggingStat      = checkStringParam(dataProvider->getString(Event.getDataKey(),DATA::DeslaggingStatus));
	string HMDPoderInjGasFlowRate_N2      = checkStringParam(dataProvider->getString(Event.getDataKey(),DATA::HMDPoderInjGasFlowRate_N2));
	string HMDPoderInjGasPressure_N2      = checkStringParam(dataProvider->getString(Event.getDataKey(),DATA::HMDPoderInjGasPressure_N2));
	string HMDTotalCoolingWaterConsumed      = checkStringParam(dataProvider->getString(Event.getDataKey(),DATA::HMDTotalCoolingWaterConsumed));
	string HMDTotalArConsumed      = checkStringParam(dataProvider->getString(Event.getDataKey(),DATA::HMDTotalArConsumed));
	string HMDTotalNConsumed      = checkStringParam(dataProvider->getString(Event.getDataKey(),DATA::HMDTotalNConsumed));*/
	
  /*string ProductID     = Event.getProductID();
  string mSteelGrade   = checkStringParam(dataProvider->getString(Event.getDataKey(),DATA::SteelGradeCode))*/;

		//sankar
	  long mLadleNo = CSMC_DBData::unspecLong;
		string mLadleType;
		CPD_PLANTSTATUS m_PDPStatus(m_pDM_DBManagerTask->getStdConnection());
		if(m_PDPStatus.select(mHeatInfo.Plant,mHeatInfo.PlantNo,1))
		{
				mLadleNo = m_PDPStatus.getLADLENO(1);
				mLadleType = m_PDPStatus.getLADLETYPE(1);
		}

		//sankar
	//long mLadleNo     = dataProvider->getLong(pMsg.getDataKey(),DATA::LadleNo);
	//string mLadleType    = checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::LadleType));

		// Table: PD_SAMPLE  // ladleno, ladletype, measuretype, user --values needed
		CPD_SAMPLE m_PDSample(m_pDM_DBManagerTask->getStdConnection());
		long mSampleCounter = m_PDSample.getNextSAMPLE_COUNTER();
		CGC_MEASUREMENT_TYPE m_GCMeasumentType(m_pDM_DBManagerTask->getStdConnection());
		long mMeasTypeNo = DEF_GC_MEASUREMENT_TYPE::Temp;
		result = result && m_PDSample.insertPSSample(mSampleCounter,mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,mHeatInfo.PlantNo,mLadleNo,mLadleType,mMeasTypeNo,now.assDate(),"",false,m_lastError);
		
		//sankar
		//CDateTime now2;
		CDM_ProductManagementInterface_Impl *dataProductmanagement = m_pDM_DBManagerTask->getpProductManagementInterface();
		double d1 = dataProductmanagement->getDouble(pMsg.getProductID(),DATA::DurSinceHeatAnnounce);
		double d2 = dataProductmanagement->getDouble(pMsg.getProductID(),DATA::DurSinceHeatStart);
		result = result && m_PDSample.updateSampleTimes(mSampleCounter,now,now,now,d1,d2,false);

		// Table: PD_SAMPLE_ENTRY
		double mTemp=dataProvider->getLong(pMsg.getDataKey(),DATA::MeasTemp);
		//mTemp=1433;
		CPD_SAMPLE_ENTRY m_PDSampleEntry(m_pDM_DBManagerTask->getStdConnection());
		result = result && m_PDSampleEntry.insertSample(mSampleCounter,"Temp",mTemp);

		// Table: PD_SAMPLE_REF 
		CPD_SAMPLE_REF m_PDSampleRef(m_pDM_DBManagerTask->getStdConnection());
		result = result && m_PDSampleRef.evHMDAnalysis(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,"Temp",mMeasTypeNo,false);

		// Table: PD_PLANT_STATUS
		CPD_PLANTSTATUS m_PDPlantStatus(m_pDM_DBManagerTask->getStdConnection());
		//result = result && m_PDPlantStatus.OnTempMeasurement(mSampleCounter,mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,mTemp,false);
		result = result && m_PDPlantStatus.updateTempTaken(mHeatInfo.Plant,mHeatInfo.PlantNo,mTemp,now,1,false,m_lastError); //sankar

		// Table: HD_SAMPLE
		CHD_SAMPLE m_HDSample(m_pDM_DBManagerTask->getStdConnection());
		result = result && m_HDSample.OnTempMeasurement(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,mHeatInfo.PlantNo,mSampleCounter,false,m_lastError);

		// Table: HD_SAMPLE_ENTRY
		CHD_SAMPLE_ENTRY m_HDSEntry(m_pDM_DBManagerTask->getStdConnection());
		result = result && m_HDSEntry.copy(mSampleCounter,false,m_lastError);

		//// Table: HD_SAMPLE_REF
		//CHD_SAMPLE_REF m_HDSampleRef(m_pDM_DBManagerTask->getStdConnection());
		//result = result && m_HDSampleRef.evTempMeasurement(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,false);

  if (result)
    m_pDM_DBManagerTask->getStdConnection()->commit();
  else
  {
    m_pDM_DBManagerTask->getStdConnection()->rollback();
    //CDM_DBManager::handleError(Event);
  }

  return result;
}

bool CDM_HMDDBManager::evCeloxMeasurement(CEventMessage &pMsg)
{
bool result = true;
/*
  sHeatInfo mHeatInfo;
  CDM_DataInterface_Impl *dataProvider = m_pDM_DBManagerTask->getpDataInterface();
  mHeatInfo.HeatId	= checkStringParam(pMsg.getHeatID());
  mHeatInfo.TreatId	= checkStringParam(pMsg.getTreatID());
  mHeatInfo.Plant		= checkStringParam(pMsg.getPlantID());
  long mSampleCounter = -1;//dataProvider->getLong(pMsg.getDataKey(),DATA::SampleCounter);

  CDM_DBManager::splitPlantPlantNo(mHeatInfo.Plant, mHeatInfo.Plant, mHeatInfo.PlantNo);
  bool result = true;

  result = CDM_DBManager::copyHDSamples(mHeatInfo, mSampleCounter, false);

  if (result)
    m_pDM_DBManagerTask->getStdConnection()->commit();
  else
  {
    m_pDM_DBManagerTask->getStdConnection()->rollback();
    string mHMIClientId = dataProvider->getString(pMsg.getDataKey(), DATA::HMIClientId);
    CDM_DBManager::handleError(pMsg, mHMIClientId);
  }
*/
  return result;
}

bool CDM_HMDDBManager::evHotMetalAnalysisReceived(CEventMessage &pMsg)
{
  
  bool result = true;
	CDateTime now;
	sHeatInfo mHeatInfo;
  CDM_DataInterface_Impl *dataProvider = m_pDM_DBManagerTask->getpDataInterface();
  dataProvider->showContent(pMsg.getDataKey(),3);
  mHeatInfo.HeatId	= checkStringParam(pMsg.getHeatID());
  mHeatInfo.TreatId	= "01";   //checkStringParam(pMsg.getTreatID());
  mHeatInfo.Plant		= sPlantConst;

	string mPlantId = pMsg.getPlantID();
	string mPlantno = mPlantId.substr(4,1);
	mHeatInfo.PlantNo = atol(mPlantno.c_str()); 

	long mOnRequest     = dataProvider->getLong(pMsg.getDataKey(),DATA::ManuallyEntered);
	//setpDM_Interface(pMsg.getSender(),DM::EVENT);
  //SeqAnalysisData = dataProvider->getString(pMsg.getDataKey(),DATA::HMMeasAnalysis);
	sDate mSampleTime	= dataProvider->getDate(pMsg.getDataKey().c_str(), DATA::HMSampleTime);
  long mSampleLoc		= dataProvider->getLong(pMsg.getDataKey(), DATA::SampleLocation);
	string mUserCode      = checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::UserCode));
	if (mUserCode ==DEF::Inv_String)
		mUserCode=" ";
	CGC_MEASUREMENT_TYPE m_GCMeasumentType(m_pDM_DBManagerTask->getStdConnection());
	long mMeasTypeNo = DEF_GC_MEASUREMENT_TYPE::HM;
	long mSampCounterPrev = DEF::Inv_Long;
	seqAnalysis mAnalArray = *dataProvider->getAnalysis(pMsg.getDataKey().c_str(), DATA::HMMeasAnalysis);
	
	
	string SampleId      = checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::SampleId));

  //string ProductID     = Event.getProductID();
  //string mSteelGrade   = checkStringParam(dataProvider->getString(Event.getDataKey(),DATA::SteelGradeCode));

	//sankar
	  long mLadleNo = CSMC_DBData::unspecLong;
		string mLadleType;
		CPD_PLANTSTATUS m_PDPStatus(m_pDM_DBManagerTask->getStdConnection());
		if(m_PDPStatus.select(mHeatInfo.Plant,mHeatInfo.PlantNo,1))
		{
				mLadleNo = m_PDPStatus.getLADLENO(1);
				mLadleType = m_PDPStatus.getLADLETYPE(1);
		}

		//sankar
	//long mLadleNo     = dataProvider->getLong(pMsg.getDataKey(),DATA::LadleNo);
	//string mLadleType    = checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::LadleType));


  if (mLadleType ==DEF::Inv_String)
		mLadleType="H";
	CPD_SAMPLE			m_PDSample(m_pDM_DBManagerTask->getStdConnection());
	CPD_SAMPLE_ENTRY	m_PDSampleEntry(m_pDM_DBManagerTask->getStdConnection());

	 //sankar
	 long mSampleCounter;
   if(m_PDSample.selectLastSampleWithoutAnalysisHMD(mHeatInfo.HeatId, mHeatInfo.TreatId, mHeatInfo.Plant, mHeatInfo.PlantNo, mMeasTypeNo) )
   {
      // there is only one attempt to find the oldest sample without sample data
      mSampleCounter = m_PDSample.getSAMPLE_COUNTER(1); 
			m_PDSampleEntry.insertAnalysis(mSampleCounter, mAnalArray, true, m_lastError);
    }
	 else
	 {
		//get next Sample counter
		mSampleCounter = m_PDSample.getNextSAMPLE_COUNTER();

		result = result && m_PDSample.insertByPrevSample_HMD(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,mHeatInfo.PlantNo,mSampleCounter, mSampleCounter, mSampleTime, mOnRequest, mUserCode,mLadleType,mLadleNo,mMeasTypeNo, true, m_lastError);
		result = result && m_PDSampleEntry.insertAnalysis(mSampleCounter, mAnalArray, true, m_lastError);
	 }
   result = result && m_PDSample.updateSampleDetails(mSampleCounter,CSMC_DBData::unspecString,CSMC_DBData::unspecLong,CSMC_DBData::unspecString,1,mUserCode,SampleId,CSMC_DBData::unspecLong);


	// Table: PD_SAMPLE_REF 
	CPD_SAMPLE_REF m_PDSampleRef(m_pDM_DBManagerTask->getStdConnection());
	result = result && m_PDSampleRef.evHMDAnalysis(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,"HOT_METAL",mMeasTypeNo,true); //sankar

// Table: HD_SAMPLE
	CHD_SAMPLE m_HDSample(m_pDM_DBManagerTask->getStdConnection());
	result = result && m_HDSample.OnTempMeasurement(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,mHeatInfo.PlantNo,mSampleCounter,true,m_lastError);

// Table: HD_SAMPLE_ENTRY
	CHD_SAMPLE_ENTRY m_HDSEntry(m_pDM_DBManagerTask->getStdConnection());
	result = result && m_HDSEntry.copy(mSampleCounter,true,m_lastError);

	result = result && m_PDPStatus.updateSampleCounter(mHeatInfo.Plant,mHeatInfo.PlantNo,CSMC_DBData::unspecString,CSMC_DBData::unspecString,mSampleCounter,1,true,m_lastError); //sankar

	/*if (result)
    m_pDM_DBManagerTask->getStdConnection()->commit();
  else
  {
    m_pDM_DBManagerTask->getStdConnection()->rollback();
    CDM_DBManager::handleError(pMsg);
  }*/
	return result;
}

bool CDM_HMDDBManager::evSlagAnalysisReceived(CEventMessage &pMsg)
{
   bool result = true;
	CDateTime now;
	sHeatInfo mHeatInfo;
  CDM_DataInterface_Impl *dataProvider = m_pDM_DBManagerTask->getpDataInterface();
  mHeatInfo.HeatId	= checkStringParam(pMsg.getHeatID());
  mHeatInfo.TreatId	= "01";   //checkStringParam(pMsg.getTreatID());
  mHeatInfo.Plant		= sPlantConst;

	string mPlantId =pMsg.getPlantID();
	string mPlantno = mPlantId.substr(4,1);
	mHeatInfo.PlantNo = atol(mPlantno.c_str()); 

	long mOnRequest     = dataProvider->getLong(pMsg.getDataKey(),DATA::ManuallyEntered);
	//setpDM_Interface(pMsg.getSender(),DM::EVENT);
  //SeqAnalysisData = dataProvider->getString(pMsg.getDataKey(),DATA::HMMeasAnalysis);
	sDate mSampleTime	= dataProvider->getDate(pMsg.getDataKey().c_str(), DATA::SlagSampleTime);
  long mSampleLoc		= dataProvider->getLong(pMsg.getDataKey(), DATA::SampleLocation);
	string mUserCode      = checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::UserCode));
	if (mUserCode ==DEF::Inv_String)
		mUserCode=" ";
	CGC_MEASUREMENT_TYPE m_GCMeasumentType(m_pDM_DBManagerTask->getStdConnection());
	long mMeasTypeNo = DEF_GC_MEASUREMENT_TYPE::Slag;
	long mSampCounterPrev = DEF::Inv_Long;
	seqAnalysis mAnalArray = *dataProvider->getAnalysis(pMsg.getDataKey().c_str(), DATA::SlagMeasAnalysis);
	
	string SampleId      = checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::SampleId));

  //string ProductID     = Event.getProductID();
  //string mSteelGrade   = checkStringParam(dataProvider->getString(Event.getDataKey(),DATA::SteelGradeCode));

	//sankar
	  long mLadleNo = CSMC_DBData::unspecLong;
		string mLadleType;
		CPD_PLANTSTATUS m_PDPStatus(m_pDM_DBManagerTask->getStdConnection());
		if(m_PDPStatus.select(mHeatInfo.Plant,mHeatInfo.PlantNo,1))
		{
				mLadleNo = m_PDPStatus.getLADLENO(1);
				mLadleType = m_PDPStatus.getLADLETYPE(1);
		}

  //sankar
	//long mLadleNo     = dataProvider->getLong(pMsg.getDataKey(),DATA::LadleNo);  // to do ladle no of analysis to get HM_ID for lab analysis
	//string mLadleType    = checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::LadleType));

  if (mLadleType ==DEF::Inv_String)
		mLadleType="H";
	CPD_SAMPLE			m_PDSample(m_pDM_DBManagerTask->getStdConnection());
	CPD_SAMPLE_ENTRY	m_PDSampleEntry(m_pDM_DBManagerTask->getStdConnection());

	//sankar
	 long mSampleCounter = CSMC_DBData::unspecLong;
   if(m_PDSample.selectLastSampleWithoutAnalysisHMD(mHeatInfo.HeatId, mHeatInfo.TreatId, mHeatInfo.Plant, mHeatInfo.PlantNo, mMeasTypeNo) )
   {
      // there is only one attempt to find the oldest sample without sample data
      mSampleCounter = m_PDSample.getSAMPLE_COUNTER(1); 
			m_PDSampleEntry.insertAnalysis(mSampleCounter, mAnalArray, true, m_lastError);
    }
	 else
	 {
		//get next Sample counter
		mSampleCounter = m_PDSample.getNextSAMPLE_COUNTER();
		result = result && m_PDSample.insertByPrevSample_HMD(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,mHeatInfo.PlantNo,mSampleCounter, mSampleCounter, mSampleTime, mOnRequest, mUserCode,mLadleType,mLadleNo,mMeasTypeNo, true, m_lastError);
		result = result && m_PDSampleEntry.insertAnalysis(mSampleCounter, mAnalArray, true, m_lastError);
	 }

   result = result && m_PDSample.updateSampleDetails(mSampleCounter,CSMC_DBData::unspecString,CSMC_DBData::unspecLong,CSMC_DBData::unspecString,1,mUserCode,SampleId,CSMC_DBData::unspecLong);


	// Table: PD_SAMPLE_REF 
	CPD_SAMPLE_REF m_PDSampleRef(m_pDM_DBManagerTask->getStdConnection());
	result = result && m_PDSampleRef.evHMDAnalysis(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,"SLAG",mMeasTypeNo,true);

// Table: HD_SAMPLE
	CHD_SAMPLE m_HDSample(m_pDM_DBManagerTask->getStdConnection());
	result = result && m_HDSample.OnTempMeasurement(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,mHeatInfo.PlantNo,mSampleCounter,true,m_lastError);

// Table: HD_SAMPLE_ENTRY
	CHD_SAMPLE_ENTRY m_HDSEntry(m_pDM_DBManagerTask->getStdConnection());
	result = result && m_HDSEntry.copy(mSampleCounter,true,m_lastError);


	/*if (result)
    m_pDM_DBManagerTask->getStdConnection()->commit();
  else
  {
    m_pDM_DBManagerTask->getStdConnection()->rollback();
    CDM_DBManager::handleError(pMsg);
  }*/
	return result;
}

void CDM_HMDDBManager::log(const std::string& _message, long _level)
{
  if (m_pDM_DBManagerTask)
    m_pDM_DBManagerTask->log(_message, _level);
}

//Different Plant has different Equipments, so need to do separately
bool CDM_HMDDBManager::setPlantEquipmentAge(sHeatInfo &pHeatInfo)
{
  bool result = (m_pDM_DBManagerTask != NULL);
  if (result)
  {
    /*
    CEquipmentData m_pEquipmentData(m_pDM_DBManagerTask->getStdConnection());

    //increase life by 1 for ELECTRODE1, ELECTRODE2, ELECTRODE3, ROOF
    result = result && m_pEquipmentData.setEquipmentAge(pHeatInfo.Plant, pHeatInfo.PlantNo, "ELECTRODE1");
    result = result && m_pEquipmentData.setEquipmentAge(pHeatInfo.Plant, pHeatInfo.PlantNo, "ELECTRODE2");
    result = result && m_pEquipmentData.setEquipmentAge(pHeatInfo.Plant, pHeatInfo.PlantNo, "ELECTRODE3");
    result = result && m_pEquipmentData.setEquipmentAge(pHeatInfo.Plant, pHeatInfo.PlantNo, "ROOF");

    if (!result)
      m_lastError = m_pEquipmentData.getLastError();
    */
  }
  return result;
}

bool CDM_HMDDBManager::doHeatDeparture(CEventMessage &pMsg)
{
  bool result = true;

  sHeatInfo mHeatInfo;
  CDM_DataInterface_Impl *dataProvider = m_pDM_DBManagerTask->getpDataInterface();
  mHeatInfo.HeatId    = checkStringParam(pMsg.getHeatID());
  mHeatInfo.TreatId    = "01";  //checkStringParam(pMsg.getTreatID());
  string mOrderId      = checkStringParam(pMsg.getOrderID());
  string mUserCode    = checkStringParam(dataProvider->getString(pMsg.getDataKey(),DATA::UserCode));
  string ProductID    = pMsg.getProductID();
  long mSampleCounter = -1;

 
  
  return result;
}

bool CDM_HMDDBManager::doHeatAnnouncement(CEventMessage &Event)
{
  bool result = true;

  //sHeatInfo mHeatInfo;
	sHMInfo mHMInfo;
  CDM_DataInterface_Impl *dataProvider = m_pDM_DBManagerTask->getpDataInterface();
  //get parameters
  /*mHeatInfo.HeatId     = Event.getHeatID();
  mHeatInfo.TreatId    = Event.getTreatID();
  mHeatInfo.Plant      = Event.getPlantID();*/
	mHMInfo.HMId=Event.getHeatID();
	mHMInfo.TreatId=Event.getTreatID();   //Event.getTreatID();
	//mHMInfo.Plant=Event.getPlantID();
	mHMInfo.Plant = sPlantConst; 
	//mHMInfo.PlantNo = dataProvider->getLong(Event.getDataKey(), DATA::PlantID);
	string mPlantId =Event.getPlantID();
	string mPlantno = mPlantId.substr(4,1);
	mHMInfo.PlantNo= atol(mPlantno.c_str()); 
  string mOrderId      = Event.getOrderID();
  string ProductID     = Event.getProductID();
  string mSteelGrade   = checkStringParam(dataProvider->getString(Event.getDataKey(),DATA::SteelGradeCode));
	double mHMWeight=dataProvider->getDouble(Event.getDataKey(), DATA::HMWeight);
	double mSlagWeight=dataProvider->getDouble(Event.getDataKey(), DATA::SlagMass);
	string ladleNo = checkStringParam(dataProvider->getString(Event.getDataKey(), DATA::LadleNo));
	mHMInfo.HMTemp=dataProvider->getDouble(Event.getDataKey(), DATA::HMTemp);

	CDateTime TempMeasTime;
	TempMeasTime << dataProvider->getDate(Event.getDataKey().c_str(), DATA::TempMeasTime);

	
	long ldlid;
	long mUnitGroupNo=0;
	if(mHMInfo.PlantNo==2)
		mUnitGroupNo=1102;
	else
		mUnitGroupNo=1101;
	ldlid = CDataConversion::StringToLong(ladleNo);
	
	//  Table: PDH_ACTION
    CPDH_ACTION m_PDHAction(m_pDM_DBManagerTask->getStdConnection());
    result = m_PDHAction.doAnnouncement(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant);

		//  Table: PD_PLANTSTATUS sankar
		CHeatStatusContainer  HeatStatusContainer(m_pDM_DBManagerTask->getStdConnection());
		long htStatus = HeatStatusContainer.getHeatStatus(mHMInfo.Plant, DEF_GC_HEAT_STATUS::HeatAnnounced );

		CPD_PLANTSTATUS m_PDPlantstatus(m_pDM_DBManagerTask->getStdConnection());
    result = result &&  m_PDPlantstatus.doHeatAnnouncement(mHMInfo.HMId,mHMInfo.ProdOrderId,mHMInfo.TreatId,mHMInfo.Plant,mHMInfo.PlantNo,mHMWeight,mSlagWeight,ldlid,mHMInfo.HMTemp,htStatus);
		result = result && m_PDPlantstatus.updateTempTaken(mHMInfo.Plant,mHMInfo.PlantNo,mHMInfo.HMTemp,TempMeasTime,1,false,m_lastError); //sankar

 
  //Copy data into HD tables

		// copy data from PDH_HM_DATA to HDH_HM_DATA
		CHDH_HM_DATA m_HDHHData(m_pDM_DBManagerTask->getStdConnection());
		result = result && m_HDHHData.copyHDH_HM_Data(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant,false);

		// copy data from GT_PARAM to HDH_PARAM
		CHDH_PARAM m_HDHParam(m_pDM_DBManagerTask->getStdConnection());
		result = result && m_HDHParam.doAnnouncement(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant,mUnitGroupNo);
		
		// copy data from GT_PARAM_MATRIX to HDH_PARAM_MATRIX
		CHDH_PARAM_MATRIX m_HDHPMatrix(m_pDM_DBManagerTask->getStdConnection());
		result = result && m_HDHPMatrix.copyHDHParamMatrix(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant,false);

		// copy data from GTH_PP_TEMP_CORR to HDH_PP_TEMP_CORR   
		CHDH_PP_TEMP_CORR m_HDHPTCorr(m_pDM_DBManagerTask->getStdConnection());
		result = result && m_HDHPTCorr.copyHDHPTempCorr(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant,mHMInfo.PlantNo,false);

		// copy data from GTH_PP_BLOWING to HDH_PP_BLOWING
		CHDH_PP_BLOWING m_HDHPPBlowing(m_pDM_DBManagerTask->getStdConnection());
		result = result && m_HDHPPBlowing.copyHDHPPBlowing(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant,mHMInfo.PlantNo,false);

		// copy data from GTH_PP_BASE_VAL to HDH_PP_BASE_VAL
		CHDH_PP_BASE_VAL m_HDHPPBVal(m_pDM_DBManagerTask->getStdConnection());
		result = result && m_HDHPPBVal.copyHDHPPBaseVal(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant,mHMInfo.PlantNo,false);

		// copy data from GTH_PP_BASE_VAL_STEP to HDH_PP_BASE_VAL_STEP
		CHDH_PP_BASE_VAL_STEP m_HDHPPBVStep(m_pDM_DBManagerTask->getStdConnection());
		result = result && m_HDHPPBVStep.copyHDHPPBaseValStep(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant,mHMInfo.PlantNo,false);

		// copy data from GTH_PP_INJECTION to HDH_PP_INJECTION
		CHDH_PP_INJECTION m_HDHPPInjection(m_pDM_DBManagerTask->getStdConnection());
		result = result && m_HDHPPInjection.copyHDHPPInjection(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant,mHMInfo.PlantNo,false);

		// copy data from PDH_HM_DATA to HDH_GRADE
		CHDH_GRADE m_HDHGrade(m_pDM_DBManagerTask->getStdConnection());
		result = result && m_HDHGrade.copyHDHGrade(mSteelGrade,mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant,false);

		// copy data from PDH_HM_DATA_PRODPRAC to HDH_HM_DATA_PRODPRAC
		CHDH_HM_DATA_PRODPRAC m_HDHHDProdprac(m_pDM_DBManagerTask->getStdConnection());
		result = result && m_HDHHDProdprac.copyHDHHDPRODPRAC(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant,false);

		// copy data from GT_GRADE_ANL to HDH_GRADE_ANL
		CHDH_GRADE_ANL m_HDHGAnl(m_pDM_DBManagerTask->getStdConnection());
		result = result && m_HDHGAnl.copyHDHGAnl(mSteelGrade,mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant,false);

		// copy data from PDH_HM_DATA to HDH_HM_DATA
		//CHDH_HM_DATA m_HDHHData(m_pDM_DBManagerTask->getStdConnection());
		//result = result && m_HDHHData.copyHDH_HM_Data(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant,false);

		// copy data from PDH_ACTION to HDH_ACTION
		CHDH_ACTION m_HDHAction(m_pDM_DBManagerTask->getStdConnection());
		result = result && m_HDHAction.copyHDH_Action(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant,false);

		//  Table: HDH_HM_DATA_PHASE
    //CHDH_HM_DATA_PHASE m_HDHHMDataPhase(m_pDM_DBManagerTask->getStdConnection());
    //result = m_HDHHMDataPhase.insert_HDH_HM_DATA_PHASE(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant,true); no need for this as it creates duplication.

		//sankar
		/*CPDH_HM_RES m_PDHHRes(m_pDM_DBManagerTask->getStdConnection());
		CHDH_HM_RES mHDH_HM_RES(m_pDM_DBManagerTask->getStdConnection());
		result = m_PDHHRes.update_HeatAnnounce(mHMInfo.HMId);
		result = mHDH_HM_RES.update_HeatAnnounce(mHMInfo.HMId);
		*/
		//sankar
		long SampleCounter = CSMC_DBData::unspecLong;
		seqAnalysis AnalArray = *dataProvider->getAnalysis(Event.getDataKey().c_str(), DATA::HMMeasAnalysis);
		double mTemp = dataProvider->getLong(Event.getDataKey(),DATA::MeasTemp);

		CPD_SAMPLE PD_SAMPLE(m_pDM_DBManagerTask->getStdConnection());
		CPD_SAMPLE_ENTRY PD_SAMPLE_ENTRY(m_pDM_DBManagerTask->getStdConnection());
		CHD_SAMPLE m_HDSample(m_pDM_DBManagerTask->getStdConnection());
		CHD_SAMPLE_ENTRY m_HDSEntry(m_pDM_DBManagerTask->getStdConnection());

		if(PD_SAMPLE.selectByType_HMD(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant,mHMInfo.PlantNo,DEF_GC_MEASUREMENT_TYPE::HM))
		{
			SampleCounter = PD_SAMPLE.getSAMPLE_COUNTER(1);
			if(SampleCounter != CSMC_DBData::unspecLong)
			{
				result = result &&  PD_SAMPLE_ENTRY.deleteSample(SampleCounter);
				result = result &&  PD_SAMPLE_ENTRY.insertAnalysis(SampleCounter,AnalArray,false,m_lastError);
				result = result && m_HDSample.OnTempMeasurement(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant,mHMInfo.PlantNo,SampleCounter,false,m_lastError);
				result = result && m_HDSEntry.copy(SampleCounter,false,m_lastError);
			}
		}
		else
		{
			evHotMetalAnalysisReceived(Event);
		}

		if(PD_SAMPLE.selectByType_HMD(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant,mHMInfo.PlantNo,DEF_GC_MEASUREMENT_TYPE::Temp))
		{
			SampleCounter = PD_SAMPLE.getSAMPLE_COUNTER(1);
			if(SampleCounter != CSMC_DBData::unspecLong)
			{
				result = result &&  PD_SAMPLE_ENTRY.deleteSample(SampleCounter);
				result = result &&  PD_SAMPLE_ENTRY.insertSample(SampleCounter,"Temp",mTemp);
				result = result && m_HDSample.OnTempMeasurement(mHMInfo.HMId,mHMInfo.TreatId,mHMInfo.Plant,mHMInfo.PlantNo,SampleCounter,false,m_lastError);
				result = result && m_HDSEntry.copy(SampleCounter,false,m_lastError);
			}
		}
		else
		{
			evTempMeasurement(Event);
		}
		
		

  if (result)
    m_pDM_DBManagerTask->getStdConnection()->commit();
  else
  {
    m_pDM_DBManagerTask->getStdConnection()->rollback();
    CDM_DBManager::handleError(Event);
  }

  return result;
}

bool CDM_HMDDBManager::AutomaticlyFillRelativeDelays(CEventMessage &Event,bool pCommit,bool &isDelay)
{
  bool result = true;

	//SARS
	isDelay = false;
  sHeatInfo HeatInfo;
  setHeatInfo(Event, HeatInfo);

	CGT_PARAM     GT_PARAM(m_pDM_DBManagerTask->getStdConnection());
	CPDH_HM_DATA  PDH_HM_DATA(m_pDM_DBManagerTask->getStdConnection());
		
  if( PDH_HM_DATA.select(HeatInfo.HeatId,HeatInfo.TreatId,HeatInfo.Plant ) )
  {
    CDateTime	 mActTreatStart,mActTreatEnd;

    mActTreatStart = PDH_HM_DATA.getTREATSTART_ACT(1);
    mActTreatEnd = PDH_HM_DATA.getTREATEND_ACT(1);
	  string mDelayCode = "1109";  

    CDeltaTime actProdDur = CDateTime::subTimes(mActTreatEnd, mActTreatStart);
    double DefltTreatDurHMD = 1800.0; // 30 minutes in seconds
		if(GT_PARAM.select(DEF_GC_PLANTGROUP_DESC::All_HMD,"DefltTreatDuration", 0, CSMC_DBData::unspecLong))
    {
      DefltTreatDurHMD = CDataConversion::StringToDouble(GT_PARAM.getVALUE(1)) * 60.0; //DB contains minutes, we need seconds
    }
                  
    if( actProdDur.asSeconds() > DefltTreatDurHMD)
    {
      CDateTime mdelayStartTime; 
			mdelayStartTime = CDateTime::addTimes(DefltTreatDurHMD,mActTreatStart) ; 

			CDM_DataInterface_Impl *dataProvider = m_pDM_DBManagerTask->getpDataInterface();
			dataProvider->setString(Event.getDataKey(), DATA::DelayCode, mDelayCode);
			dataProvider->setDate(Event.getDataKey().c_str(), DATA::DelayStartDate, mdelayStartTime.assDate());
			dataProvider->setDate(Event.getDataKey().c_str(), DATA::DelayEndDate, mActTreatEnd.assDate());
			dataProvider->setString(Event.getDataKey(), DATA::UserCode, "ADM");
			dataProvider->setString(Event.getDataKey(), DATA::Comment, " "); //Operator has to fill via HMI.
			dataProvider->setLong(Event.getDataKey(), DATA::Status, DEF_GEN_STATES::New);

			isDelay = true;
    }   
  }

  return result;
}

bool CDM_HMDDBManager::doCyclicMeasurement(CEventMessage &Event)
{
	bool result = true;

	//sHeatInfo mHeatInfo;
	//CDM_DataInterface_Impl *dataProvider = m_pDM_DBManagerTask->getpDataInterface();
	//mHeatInfo.HeatId    = checkStringParam(Event.getHeatID());
	//mHeatInfo.Plant= sPlantConst;
	//mHeatInfo.TreatId    = "01"; //checkStringParam(pMsg.getTreatID());
	//long   mBlowingMode          = dataProvider->getLong(Event.getDataKey(),DATA::HMDBlowType);
	//double mBlownMg              = dataProvider->getDouble(Event.getDataKey(),DATA::MagnAmount);
	//double mBlownLime            = dataProvider->getDouble(Event.getDataKey(),DATA::LimeAmount);
	//double mBlowncarbide         = dataProvider->getDouble(Event.getDataKey(),DATA::CarbAmount);

	////sankar
	//long mDeslaggStat      = dataProvider->getDouble(Event.getDataKey(),DATA::DeslaggingStatus);
	//CPDH_ACTION m_PDHAction(m_pDM_DBManagerTask->getStdConnection());

	//if(mDeslaggStat ==1)
	//{
	//  if (!m_PDHAction.select(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,1009)) 
	//		m_PDHAction.insert_Deslagging(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,mDeslaggStat,"Initial Deslagging Start",1009);
	//	else
	//	if (!m_PDHAction.select(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,1007)) 
	//		m_PDHAction.insert_Deslagging(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,mDeslaggStat,"Final Deslagging Start",1007);
	//}

	//if(mDeslaggStat == 0)
	//{
	//  if ( !m_PDHAction.select(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,1010) && m_PDHAction.select(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,1009))
	//		m_PDHAction.insert_Deslagging(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,mDeslaggStat,"Initial Deslagging End",1010);
	//	else
	//  if ( !m_PDHAction.select(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,1008) && m_PDHAction.select(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,1007)) 
	//	  m_PDHAction.insert_Deslagging(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,mDeslaggStat,"Final Deslagging End",1008);
	//}
	//
	//CPD_PLANTSTATUS_PLANT PD_PLANTSTATUS_PLANT(m_pDM_DBManagerTask->getStdConnection());
	//result = result && PD_PLANTSTATUS_PLANT.updateStatus(mHeatInfo.Plant, mHeatInfo.PlantNo, 1, 2,  DEF_GC_PLANTSTATUS::LIME, CDataConversion::LongToString((long)mBlownLime), false, m_lastError);
	//result = result && PD_PLANTSTATUS_PLANT.updateStatus(mHeatInfo.Plant, mHeatInfo.PlantNo, 1, 2,  DEF_GC_PLANTSTATUS::MG, CDataConversion::LongToString((long)mBlownMg), false, m_lastError);
	//result = result && PD_PLANTSTATUS_PLANT.updateStatus(mHeatInfo.Plant, mHeatInfo.PlantNo, 1, 2,  DEF_GC_PLANTSTATUS::CARBIDE, CDataConversion::LongToString((long)mBlowncarbide), false, m_lastError);


	//if (result)
	//	m_pDM_DBManagerTask->getStdConnection()->commit();
	//else
	//{
	//	m_pDM_DBManagerTask->getStdConnection()->rollback();
	//	CDM_DBManager::handleError(Event);
	//}

	return result;
}

void CDM_HMDDBManager::setHMInfo(const CEventMessage& Event, sHMInfo& HMInfo)
{
  log("++++++ CDM_HMDDBManager::setHMInfo",3);

  HMInfo.HMId               = Event.getHeatID();
  HMInfo.TreatId            = Event.getTreatID();
  HMInfo.Plant              = Event.getPlantID();
  HMInfo.ProductId          = Event.getProductID();
  HMInfo.ProdOrderId        = Event.getOrderID();

  // some more validation checks are required
  if ( HMInfo.HMId.empty() )
    HMInfo.HMId = DEF::Inv_String;

  if ( HMInfo.TreatId.empty() )
    HMInfo.TreatId = DEF::Inv_String;

  if ( HMInfo.Plant.empty() )
    HMInfo.Plant = DEF::Inv_String;

  if ( HMInfo.ProductId.empty() )
    HMInfo.ProductId = DEF::Inv_String;

  if ( HMInfo.ProdOrderId.empty() )
    HMInfo.ProdOrderId = DEF::Inv_String;

  CDM_DBManager::splitPlantPlantNo(HMInfo.Plant, HMInfo.Plant, HMInfo.PlantNo);
}

bool CDM_HMDDBManager::doPhaseDataChange(CEventMessage &Event)
{
	bool RetValue = true;
  sHMInfo HMInfo;
  setHMInfo(Event, HMInfo);

  CPDH_HM_DATA_PHASE PDH_HM_DATA_PHASE(m_pDM_DBManagerTask->getStdConnection());
  CHDH_HM_DATA_PHASE HDH_HM_DATA_PHASE(m_pDM_DBManagerTask->getStdConnection());

	CDM_DataInterface_Impl *pDataInterface = m_pDM_DBManagerTask->getpDataInterface();
	CDM_ProductManagementInterface_Impl * productProvider = m_pDM_DBManagerTask->getpProductManagementInterface();

  std::string PhaseAct  = pDataInterface->getString(Event.getDataKey(), DATA::PhaseAct);

	double PhaseMgAmount   = productProvider->getDouble(HMInfo.ProductId,DATA::PhaseMagnAmount);
	double PhaseLimeAmount = productProvider->getDouble(HMInfo.ProductId,DATA::PhaseLimeAmount);
	double PhaseCarbAmount = productProvider->getDouble(HMInfo.ProductId,DATA::PhaseCarbAmount);
	double mDuration        = productProvider->getDouble(HMInfo.ProductId,DATA::BlowDur);
	

	if (PhaseMgAmount < 0)
		PhaseMgAmount = 0;

	if (PhaseLimeAmount < 0)
		PhaseLimeAmount = 0;
	
	if (PhaseCarbAmount < 0)
		PhaseCarbAmount = 0;

	if (mDuration < 0)
		mDuration = 10;

  // Table: PDH_HM_DATA_PHASE --- first close the last open phase, then insert the new phase
  if ( RetValue && PDH_HM_DATA_PHASE.selectOpenPhase( HMInfo.HMId, HMInfo.TreatId, HMInfo.Plant ) )
  {
    // The selectOpenPhase is offering the phases in descending order related to start time.
    // Therefore we use the first one as the current open phase.
    std::string PhaseName = PDH_HM_DATA_PHASE.getPHASE( 1 );
    CDateTime   StartTime = PDH_HM_DATA_PHASE.getSTART_TIME( 1 );

    RetValue = RetValue && PDH_HM_DATA_PHASE.closeOpenPhase( HMInfo.HMId, HMInfo.TreatId, HMInfo.Plant, PhaseName, StartTime,
                                                             PhaseCarbAmount, PhaseLimeAmount, PhaseMgAmount,
                                                             false, m_lastError );
  }
  // Now insert the new phase
  RetValue = RetValue && PDH_HM_DATA_PHASE.InsertNewPhase( HMInfo.HMId, HMInfo.TreatId, HMInfo.Plant, PhaseAct, false, m_lastError );


	if (RetValue)
    m_pDM_DBManagerTask->getStdConnection()->commit();
  else
  {
    m_pDM_DBManagerTask->getStdConnection()->rollback();
    CDM_DBManager::handleError(Event);
  }

  return RetValue;
}
bool CDM_HMDDBManager::doOnPowerBlowing(CEventMessage &Event, bool res)
{
	bool result = true;
	sHeatInfo mHeatInfo;
  CDM_DataInterface_Impl *dataProvider = m_pDM_DBManagerTask->getpDataInterface();

  mHeatInfo.HeatId=Event.getHeatID();
	mHeatInfo.TreatId="01";     //Event.getTreatID();
	mHeatInfo.Plant=sPlantConst;//    Event.getPlantID();
	
	long mLanceId = dataProvider->getLong(Event.getDataKey(),DATA::LanceId);
	mLanceId=1; // to do later
	
	CPDH_HM_DATA m_PDHHData(m_pDM_DBManagerTask->getStdConnection());
	if (res)
	{
		result = m_PDHHData.update_InjectStartTime(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,false);
		CPDH_LANCE_DATA m_PDHLData(m_pDM_DBManagerTask->getStdConnection());
		result = result && m_PDHLData.doONPowerBlowing(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,mLanceId,false);
	}
	else
	{
		result=m_PDHHData.update_InjectEndTime(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,false);
	}


	//sankar
	  	CDM_ProductManagementInterface_Impl * productProvider = m_pDM_DBManagerTask->getpProductManagementInterface();

		string ProductID  = Event.getProductID();

		double mPhaseMgAmount   = productProvider->getDouble(ProductID,DATA::PhaseMagnAmount);
		double mPhaseLimeAmount = productProvider->getDouble(ProductID,DATA::PhaseLimeAmount);
		double mPhaseCarbAmount = productProvider->getDouble(ProductID,DATA::PhaseCarbAmount);
		double mDuration        = productProvider->getDouble(ProductID,DATA::BlowDur);
	

		if (mPhaseMgAmount<0)
			mPhaseMgAmount=0;

		if (mPhaseLimeAmount<0)
			mPhaseLimeAmount=0;
	
		if (mPhaseCarbAmount<0)
			mPhaseCarbAmount=0;

		if (mDuration<0)
			mDuration=10;

	  if ( Event.getMessage() == HMD_EvMsg::evHMDPowderBlowingEnd )
		{			
			// Table: PDH_HM_DATA_PHASE --- update
			CPDH_HM_DATA_PHASE m_PDHDPhase(m_pDM_DBManagerTask->getStdConnection());
			result = result &&  m_PDHDPhase.doBlowEnd(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,mDuration,mPhaseCarbAmount,mPhaseMgAmount,mPhaseLimeAmount,false);

			// Table: HDH_HM_DATA_PHASE --- update
			CHDH_HM_DATA_PHASE m_HDHDPhase(m_pDM_DBManagerTask->getStdConnection());
			result = result && m_HDHDPhase.doBlowEnd(mHeatInfo.HeatId,mHeatInfo.TreatId,mHeatInfo.Plant,mDuration,mPhaseCarbAmount,mPhaseMgAmount,mPhaseLimeAmount,false);
		}

  if (result)
    m_pDM_DBManagerTask->getStdConnection()->commit();
  else
  {
    m_pDM_DBManagerTask->getStdConnection()->rollback();
    CDM_DBManager::handleError(Event);
  }

  return result;
}


bool CDM_HMDDBManager::doModelResult(CEventMessage &Event)
{
	bool RetValue = false;

	//SANKAR change for model result

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string Plant     = DEF_GC_PLANT_DEF::HMD;
  //std::string ActPlant  = m_pPlantID_Interpreter->getPlantName(PlantID);
	std::string ActPlant = "HMD";

  // Unified exception handling *******************************************************
  std::string Scope("CDM_HMDDBManager::doOnModelResult");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << ProductID << ", " << HeatID
               << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************

	CDM_DataInterface_Impl *dataProvider = m_pDM_DBManagerTask->getpDataInterface();


    log("***********************SANKAR start ::**************************************",3);
    CDM_ProductManagementInterface_Impl *dataProductmanagement = m_pDM_DBManagerTask->getpProductManagementInterface();
	m_pDM_DBManagerTask->getpDataInterface()->showContent(DataKey.c_str(),3);
    m_pDM_DBManagerTask->getpProductManagementInterface()->showContent(ProductID,3);

	log("***********************SANKAR end::**************************************",3);

  try
  {
    /*if (!m_pConnection)
    {
      handleDBConnectionError();
      if (!m_pConnection) return false;
    }*/

    double d1;
    double d2;
    seqHMDModelResult SeqHMDModelResult;
    sHMDModelResult   HMDModelResult;
    seqComputerModes  SeqComputerModesAvail;
    std::string ActPhase;
    CDateTime now;

    //setpDM_Interface(Event.getSender(),DM::PRODUCT);
    //d1             = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatAnnounceTime);
    //d2             = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatStartTime);
	//ActPhase       = CIntfData::ToStdString(m_pDM_Interface->getString(ProductID.c_str(),DATA::PhaseAct));

	//d1 = dataProvider->getLong(Event.getDataKey(),DATA::DurSinceHeatAnnounce);
	//d2 = dataProvider->getLong(Event.getDataKey(),DATA::DurSinceHeatStart);
	//ActPhase = checkStringParam(dataProvider->getString(Event.getDataKey(),DATA::PhaseAct));

	  long TreatmentType =0;
      CPDH_HM_DATA m_PDHHMData(m_pDM_DBManagerTask->getStdConnection());
      if(m_PDHHMData.select(HeatID,TreatID,ActPlant))
	  {
         TreatmentType  = m_PDHHMData.getTREAT_TYPE_OPER(1);
	  }



	d1 = dataProductmanagement->getDouble(Event.getProductID(),DATA::DurSinceHeatAnnounce);
	d2 = dataProductmanagement->getDouble(Event.getProductID(),DATA::DurSinceHeatStart);
	ActPhase = checkStringParam(dataProductmanagement->getString(Event.getProductID(),DATA::PhaseAct));

    //SeqHMDModelResult     = CIntfData::ToCORBAType(m_pDM_Interface->getHMDModelResult(ProductID.c_str(),DATA::HMDPredRes));
    //SeqComputerModesAvail = CIntfData::ToCORBAType(m_pDM_Interface->getComputerModes(ProductID.c_str(),DATA::ComputerModeAvail));
	//SeqHMDModelResult     = *dataProvider->getHMDModelResult(Event.getDataKey().c_str(),DATA::HMDPredRes);
	//SeqComputerModesAvail     = *dataProvider->getComputerModes(Event.getDataKey().c_str(),DATA::HMDPredRes);

	SeqHMDModelResult     = *dataProductmanagement->getHMDModelResult(Event.getProductID().c_str(),DATA::HMDPredRes);
	SeqComputerModesAvail     = *dataProductmanagement->getComputerModes(Event.getProductID().c_str(),DATA::ComputerModeAvail);

	log("***********************SeqPredRes**************************************",3);
    log(CIntfData::getContent(CIntfData::ToAny(SeqHMDModelResult)),3);
    log("***********************SeqComputerModes**************************************",3);
    log(CIntfData::getContent(CIntfData::ToAny(SeqComputerModesAvail)),3);


        CPDH_HM_RES mPDH_HM_RES(m_pDM_DBManagerTask->getStdConnection());
        CPDH_HM_PHASE_RES mPDH_HM_PHASE_RES(m_pDM_DBManagerTask->getStdConnection());
		CHDH_HM_RES mHDH_HM_RES(m_pDM_DBManagerTask->getStdConnection());
        	    
        sHMDCalc        HMDCalcAmount;
        sHMDCalc        HMDCalcFlow;
		CIntfData::getAt(HMDModelResult, SeqHMDModelResult, 0);
        		
		for(long i=0; i<5; ++i)
    {
		  CDateTime   Now;
		  sComputerMode ComputerMode;
	      long CMode = 0;
		  long SeqLength = CIntfData::getLength(SeqComputerModesAvail);

		  for (int x = 0; x < SeqLength; x++)
		  {
				CIntfData::getAt(ComputerMode, SeqComputerModesAvail, x);
				std::string Device = ComputerMode.Device;
				if (Device == DEF_COMP_MODES::Blowing)
				{
					CMode = ComputerMode.Status;
				}
		  }
		  double CODur = HMDModelResult.Duration[i];
			
		  //RetValue = mPDH_HM_RES.writeResults(HeatID,TreatID,ActPlant,i,Now,d1,HMDModelResult.SlagAmount[i],HMDModelResult.TemperatureAfter[i],CMode,CODur);
		  //RetValue = mHDH_HM_RES.writeResults(HeatID,TreatID,ActPlant,i,Now,d1,HMDModelResult.SlagAmount[i],HMDModelResult.TemperatureAfter[i],CMode,CODur);

			//sankar
		  RetValue = mPDH_HM_RES.writeResults(HeatID,TreatID,ActPlant,i,Now,d1,HMDModelResult.SlagAmount[i],HMDModelResult.TemperatureAfter[i],CMode,CODur);
		  RetValue = mHDH_HM_RES.writeResults(HeatID,TreatID,ActPlant,i,Now,d1,HMDModelResult.SlagAmount[i],HMDModelResult.TemperatureAfter[i],CMode,CODur);

		  seqHMDCalc tempCalcAmount = HMDModelResult.CalcAmount;
		  seqHMDCalc tempCalcFlow   = HMDModelResult.CalcFlow;
		  CIntfData::getAt(HMDCalcAmount, tempCalcAmount, i);
		  CIntfData::getAt(HMDCalcFlow, tempCalcFlow, i);
	      
		  for(long m=0; m<3; ++m)
		  {
			  double consLime = HMDCalcAmount.Lime[m];
			  double flowLime = HMDCalcFlow.Lime[m];
			  double consMg = HMDCalcAmount.Magnesium[m];
			  double flowMg = HMDCalcFlow.Magnesium[m];
			  double consCarbide = HMDCalcAmount.Carbide[m];
			  double flowCarbide = HMDCalcFlow.Carbide[m];

				//sankar
			  //RetValue = RetValue & mPDH_HM_PHASE_RES.writeResults(HeatID,TreatID,ActPlant,i,m+1,Now,consLime,consMg,consCarbide,flowLime,flowMg,flowCarbide,(long)HMDModelResult.TreatmentKind);
			  RetValue = RetValue & mPDH_HM_PHASE_RES.writeResults(HeatID,TreatID,ActPlant,i,m+1,Now,consLime,consMg,consCarbide,flowLime,flowMg,flowCarbide,(long)HMDModelResult.TreatmentKind);
		  }

        }


    //Writing TreatementKind Suggested By Model Into PDH_HEAT_DATA To display on HMI.
    long ModelResSeqLength = CIntfData::getLength(SeqHMDModelResult);
    if (ModelResSeqLength > 0)
    {
      CIntfData::getAt(HMDModelResult, SeqHMDModelResult, 0);  //There will be only 1 TreatmentKind suggested by Model
      CPDH_HM_DATA m_PDHHMData(m_pDM_DBManagerTask->getStdConnection());
	  double Saim =0.,HMwghtEnd=0,Sact=0. ;
      if(m_PDHHMData.select(HeatID,TreatID,ActPlant))
	  {
         Saim           = m_PDHHMData.getAIM_S_OPER(1);
         Sact           = m_PDHHMData.getAIM_S_GRADE(1);
         HMwghtEnd      = m_PDHHMData.getHM_WEIGHTSTART_MOD(1); 

		 m_PDHHMData.setTREAT_TYPE_MODEL(HMDModelResult.TreatmentKind );

		 if (m_PDHHMData.update())
           m_PDHHMData.commit();
         else
           m_PDHHMData.rollback();
	  }

      CPP_HM m_PPHM(m_pDM_DBManagerTask->getStdConnection());
      CPD_HOT_METAL m_PD_HOT_METAL(m_pDM_DBManagerTask->getStdConnection());
	  CPD_SAMPLE_REF m_PD_SAMPLE_REF(m_pDM_DBManagerTask->getStdConnection());
	  CPD_SAMPLE_ENTRY m_PD_SAMPLE_ENTRY(m_pDM_DBManagerTask->getStdConnection());

	  long HMCounter,smplRef,smplCounterHM;
      double smplVal = 0.;

      if(m_PPHM.select(HeatID))
	  {
         HMCounter           = m_PPHM.getHOTMETAL_COUNTER(1);
	  }

     if(m_PD_HOT_METAL.select(HMCounter))
     {
         smplRef           = m_PD_HOT_METAL.getSAMPLE_REF(1);
     }

     if(m_PD_SAMPLE_REF.select(smplRef))
     {
         smplCounterHM           = m_PD_SAMPLE_REF.getHOT_METAL(1);
     }

     if(m_PD_SAMPLE_ENTRY.select(smplCounterHM,"S"))
     {
         smplVal           = m_PD_SAMPLE_ENTRY.getMEASVALUE(1);
     }

     if (Sact != 0) smplVal = Sact;

     double Sdiffppm = (smplVal - Saim)* 10000;    

     double Sdiffkg  = (Sdiffppm * HMwghtEnd)/1000000;      

	   for(long j=1; j<=5; ++j)
	   {
		   if(mPDH_HM_RES.select(HeatID,TreatID,ActPlant,TreatmentType, CSMC_DBData::unspecString))
		   {
				mPDH_HM_RES.setSULPHUR_PPM_AIM(Saim * 10000);
				mPDH_HM_RES.setSULPHUR_DELTA_PPM(Sdiffppm);
				mPDH_HM_RES.setSULPHUR_DELTA_KG(Sdiffkg);
		  
				mPDH_HM_RES.update();
		   }
	   }
	   mPDH_HM_RES.commit();

    }
    else
      log("WARNING: struct SeqHMDModelResult from PRODUCT_MANAGEMENT_INTERFACE is empty!",2);
   

    //write result into PD_PHASE_RES_PLANT
    std::string Sender    = Event.getSender();

    //setpDM_Interface(Sender,DM::PRODUCT);


    //setpDM_Interface(Sender,DM::PLANT);

  }
  catch (cCBS_DBExc &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Scope.c_str(), ExceptionMsg.str().c_str()); 
    RetValue = false;
//    handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(...)
  {
    std::string Msg("Unknown exception:");
    Msg += ExceptionMsg.str();
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "",
      Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  
return RetValue;
}

bool CDM_HMDDBManager::evHMDModelResult(CEventMessage &Event, bool res)
{
	return true;
}

string CDM_HMDDBManager::checkStringParam(const string &pValue, bool bClear)
{
  string result = pValue;
  int ipos = 0;
  while((ipos = result.find("'", ipos)) > -1)
  {
    result = result.replace(ipos, 1, "''");
    ipos = ipos + 2;
  }
  if (bClear && result == DEF::Inv_String)
    result = "";
  return result;
}