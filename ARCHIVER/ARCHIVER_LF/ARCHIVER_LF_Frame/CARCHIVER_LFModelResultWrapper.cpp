// Copyright (C) 2007 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"
#include "iEventMessages_s.hh"

#include "CIntfData.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_EventLogFrameController.h"
#include "cCBS_DBExc.h"
#include "CStirringDataHandler.h"
#include "CDataConversion.h"

#include "CHD_GRADE_ANL.h"

#include "CPDL_ACTIVITY_RES.h"
#include "CPDL_ACTUAL_RES.h"
#include "CPDL_PHASE_ELEC_RES.h"
#include "CPDL_PHASE_STIRRING_RES.h"

#include "CGC_PhaseContainer.h"

#include "DEF_GC_MEASUREMENT_NAME_SCOPE.h"
#include "DEF_GC_PHASE.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_STIRR_GAS_TYPE.h"

#include "CARCHIVER_LFTask.h"
#include "CARCHIVER_LFModelResultWrapper.h"


//##ModelId=41A4A37E0159
CARCHIVER_LFModelResultWrapper::CARCHIVER_LFModelResultWrapper()
:CARCHIVER_ModelResultWrapper()
,m_pPDL_ACTIVITY_RES(0)
,m_pPDL_ACTUAL_RES(0)
,m_pPDL_PHASE_ELEC_RES(0)
,m_pGC_PhaseContainer(0)
{
}


//##ModelId=41A4A37E014E
CARCHIVER_LFModelResultWrapper::~CARCHIVER_LFModelResultWrapper()
{
  deleteDBClasses();
}

//##ModelId=41A4A37E0180
bool CARCHIVER_LFModelResultWrapper::doOnActualSetpoints(CEventMessage& Event)
{
  bool RetValue = true;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_LFModelResultsWrapper::doOnActualSetpoints");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************

  try
  {
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }

    setpDM_Interface(Event.getSender(),DM::PRODUCT);

    CDateTime HeatAnnounceTime;
    HeatAnnounceTime.SetTime    (m_pDM_Interface->getDate(ProductID.c_str(),DATA::HeatAnnounceTime));

    double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatAnnounceTime);
    double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatStartTime);
    long TreatmentPosition      = m_pDM_Interface->getLong(ProductID.c_str(), DATA::TreatmentPosition);


    seqPredRes SeqPredRes       = CIntfData::ToCORBAType(m_pDM_Interface->getPredRes(ProductID.c_str(),DATA::LFPredRes));
    
    long PredResSeqLength            = CIntfData::getLength(SeqPredRes);

    cCBS_ODBC_DBError CBS_ODBC_DBError;

    // check for existing sample reference, insert nwe one if required and update PD_HEAT_DATA
    if ( m_pPD_HEAT_DATA && m_pPD_HEAT_DATA->select(HeatID, TreatID, ActPlant) )
    {
      // select data
      double STEELMASS_START  = m_pPD_HEAT_DATA->getSTEELMASS_START(1);
      double SLAGMASS_START   = m_pPD_HEAT_DATA->getSLAGMASS_START(1);

      // determine existing or new SAMPLE_REF
      long SAMPLE_REF         = m_pPD_HEAT_DATA->getSAMPLE_REF(1);

      if ( m_pPD_SAMPLE_REF && SAMPLE_REF == CSMC_DBData::unspecLong )
      {
        SAMPLE_REF = m_pPD_SAMPLE_REF->insertNewSAMPLE_REF(false);
        m_pPD_HEAT_DATA->setSAMPLE_REF(SAMPLE_REF);
      }

      sPredRes PredRes;
      for (int i = 0 ; i < PredResSeqLength ; ++i)
      {
        CIntfData::getAt(PredRes, SeqPredRes, i);
        std::string sPhase = PredRes.Phase;
        long ResPhaseNo     = m_pGC_PhaseContainer->getResPhaseNo(sPhase,PredRes.PhaseNo);
        long PhaseNo        = PredRes.PhaseNo;

        // perform for valid phase numbers only
        if( ResPhaseNo != CSMC_DBData::unspecLong)
        {
          if ( RetValue && sPhase == DEF_GC_PHASE::CleanStirring )
          {
            // update expected treatment end "TREATEND_CALC" 
            CDateTime EndPhase;
            EndPhase = HeatAnnounceTime;
            EndPhase.addTime((PredRes.GenRes.MetTimeStamp.DurSinceHeatAnnouncement) * 60.0);

            m_pPD_HEAT_DATA->setTREATEND_CALC(EndPhase);

            if ( m_pPD_PLANTSTATUS )
            {
              m_pPD_PLANTSTATUS->updateExptreatmentend(ActPlant, ActPlantNo, EndPhase, TreatmentPosition, true, CBS_ODBC_DBError);
            }

            // perform commit to prevent dead-lock between archiver and tracker
            RetValue = RetValue && writeFinalCalculatedAnalysis(HeatID, TreatID, ActPlant, ActPlantNo, SAMPLE_REF, PredRes.GenRes.Analysis, PredRes.GenRes.Temp, true);
          }

          if ( RetValue && sPhase == DEF_GC_PHASE::Actual )
          {
            // perform commit to prevent dead-lock between archiver and tracker
            RetValue = RetValue && writeCalculatedAnalysis(HeatID, TreatID, ActPlant, ActPlantNo, SAMPLE_REF, PredRes.GenRes.Analysis, PredRes.GenRes.Temp, true);

            if ( PredRes.GenRes.SteelWeight > 0. || PredRes.GenRes.SlagWeight > 0. || PredRes.GenRes.Temp > 0 )
            {
              if ( PredRes.GenRes.SteelWeight > 0. )
              {
                if ( STEELMASS_START == CSMC_DBData::unspecDouble || STEELMASS_START <= 0. )
                {
                  m_pPD_HEAT_DATA->setSTEELMASS_START(PredRes.GenRes.SteelWeight);
                }

                m_pPD_HEAT_DATA->setSTEELMASS(PredRes.GenRes.SteelWeight);
              }

              if ( PredRes.GenRes.SlagWeight > 0. )
              {
                if ( SLAGMASS_START == CSMC_DBData::unspecDouble || SLAGMASS_START <= 0. )
                {
                  m_pPD_HEAT_DATA->setSLAGMASS_START(PredRes.GenRes.SlagWeight);
                }

                m_pPD_HEAT_DATA->setSLAGMASS(PredRes.GenRes.SlagWeight);
              }

              if ( PredRes.GenRes.Temp > 0 )
              {
                m_pPD_HEAT_DATA->setFINALTEMP(CDataConversion::RoundToLong(PredRes.GenRes.Temp));
              }
            } // if ( PredRes.GenRes.SteelWeight > 0. || PredRes.GenRes.SlagWeight > 0.)           
          } // if ( RetValue && sPhase == DEF_GC_PHASE::Actual )
        } // if( ResPhaseNo != CSMC_DBData::unspecLong)

        if (!RetValue)
        {
          break;
        }
      } // for (int i = 0 ; i < PredResSeqLength ; ++i)

      RetValue = RetValue && m_pPD_HEAT_DATA->update();

      if (RetValue)
      {
        m_pPD_HEAT_DATA->commit();
      }
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBWriteError(sMessage,"","PD_HEAT_DATA","");

        m_pPD_HEAT_DATA->rollback();
      }
    } // if ( m_pPD_HEAT_DATA && m_pPD_HEAT_DATA->select(HeatID, TreatID, ActPlant) )
  }
  catch (cCBS_DBExc &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Scope.c_str(), ExceptionMsg.str().c_str()); 
    RetValue = false;
    handleDBConnectionError();
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


//##ModelId=462F4F8803AF
bool CARCHIVER_LFModelResultWrapper::doOnRecipeSetpoints(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  std::string OrderID   = Event.getOrderID();

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_LFModelResultWrapper::doOnRecipeSetpoints");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << ProductID << ", " << HeatID
               << ", " << TreatID   << ", " << DataKey
               << Scope << std::endl;
  //***********************************************************************************

  try
  {
    //--------------------- moved from CARCHIVER_LFModelResultsWrapper to CSMM_ModelWrapper
    //if (!checkDBConnection())
    //{
    //  log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
    //  return false;
    //}

    //setpDM_Interface(Event.getSender(),DM::EVENT);
    //seqRecipeList SeqRecipeList     = CIntfData::ToCORBAType(m_pDM_Interface->getRecipeList(DataKey.c_str(),DATA::LFMatRecipe));
 
    //setpDM_Interface(Event.getSender(),DM::PRODUCT);
    //seqStirringData StirringAmount  = CIntfData::ToCORBAType(m_pDM_Interface->getStirringData(ProductID.c_str(),DATA::StirringAmount));
    //double ElecCons                 = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::ElecCons);

    //CStirringDataHandler StirringAmountHandler;
    //StirringAmountHandler.fill(StirringAmount);

    //double Ar_Value = StirringAmountHandler.getAccumulatedGasValue(DEF_GC_STIRR_GAS_TYPE::Ar);
    //double N2_Value = StirringAmountHandler.getAccumulatedGasValue(DEF_GC_STIRR_GAS_TYPE::N2);

    //sRecipe Recipe;
    //for ( long i = 0 ; i < CIntfData::getLength(SeqRecipeList); ++i )
    //{
    //  sRecipe Recipe;
    //  CIntfData::getAt(Recipe,SeqRecipeList,i);
    //  Recipe.TimeStamp.Elec_Moment = ElecCons;
    //  Recipe.TimeStamp.O2_Moment = 0.;
    //  Recipe.TimeStamp.Ar_Moment = Ar_Value;
    //  Recipe.TimeStamp.N2_Moment = N2_Value;
    //}

    //handleRecipeSetpoints(Event, SeqRecipeList);

  }
  catch (cCBS_DBExc &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Scope.c_str(), ExceptionMsg.str().c_str()); 
    RetValue = false;
    handleDBConnectionError();
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


//##ModelId=41ADE84A0098
void CARCHIVER_LFModelResultWrapper::initDBClasses()
{
  CARCHIVER_ModelResultWrapper::initDBClasses();

  cCBS_StdConnection *pConnection = getStdConnection();

  m_pGC_PhaseContainer      = new CGC_PhaseContainer(pConnection, DEF_GC_PLANT_DEF::LF);
  m_pPDL_ACTUAL_RES         = new CPDL_ACTUAL_RES(pConnection);
  m_pPDL_PHASE_ELEC_RES     = new CPDL_PHASE_ELEC_RES(pConnection); 
  m_pPDL_PHASE_STIRRING_RES = new CPDL_PHASE_STIRRING_RES(pConnection); 
  m_pPDL_ACTIVITY_RES       = new CPDL_ACTIVITY_RES(pConnection);
}


//##ModelId=41ADE8490398
void CARCHIVER_LFModelResultWrapper::deleteDBClasses()
{
  CARCHIVER_ModelResultWrapper::deleteDBClasses();

  if (m_pGC_PhaseContainer)      {delete m_pGC_PhaseContainer; m_pGC_PhaseContainer = 0; }
  if (m_pPDL_ACTUAL_RES)         {delete m_pPDL_ACTUAL_RES; m_pPDL_ACTUAL_RES = 0; }
  if (m_pPDL_PHASE_ELEC_RES)     {delete m_pPDL_PHASE_ELEC_RES; m_pPDL_PHASE_ELEC_RES = 0; }
  if (m_pPDL_PHASE_STIRRING_RES) {delete m_pPDL_PHASE_STIRRING_RES; m_pPDL_PHASE_STIRRING_RES = 0; }
  if (m_pPDL_ACTIVITY_RES)       {delete m_pPDL_ACTIVITY_RES; m_pPDL_ACTIVITY_RES = 0; }
}