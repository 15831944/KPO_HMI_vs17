// Copyright (C) 2004 SMS Demag AG

#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"

#include "CDateTime.h"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_EventLogFrameController.h"

#include "CEventMessage.h"
#include "CDataConversion.h"

#include "DEF_GC_MEASUREMENT_NAME.h"

#include "CLFModelTestResultWrapper.h"


CLFModelTestResultWrapper::CLFModelTestResultWrapper()
{
}


CLFModelTestResultWrapper::~CLFModelTestResultWrapper()
{
}


bool CLFModelTestResultWrapper::doModelResult(CEventMessage& Event)
{
  bool RetValue = true;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask || !checkDBConnection()) 
  {
    log("error CLFModelTestResultWrapper::doModelResult, (pIntfLF || m_pModelTask || checkDBConnection()) == false", 1);
    return RetValue;
  }

  try // common catch
  {
    std::string HeatID    = Event.getHeatID();
    std::string TreatID   = Event.getTreatID();
    std::string Plant     = Event.getPlantID();
    std::string ProductID = Event.getProductID();
    std::string Message   = Event.getMessage();

    //---------B A T C H
    seqBatchPrio          SeqBatchPrio;
    sBatchPrio            BatchPrio;
    sBatch                Batch;
    seqLFElecPredRes      SeqLFElecPredRes;
    sLFElecPredRes        LFElecPredRes;
    CDateTime             RevTime;
    seqLFStirrPredRes     SeqLFStirrPredRes;
    sLFStirrPredRes       LFStirrPredRes;
    seqAnalysis           SeqAnalysis;
    sAnalysis             Analysis;
    sPredRes              PredRes;
    seqPredRes            SeqPredRes;
    sGenRes               GenRes;
    seqRecipeList         SeqRecipeList;
    sRecipe               Recipe;
    
    //---------P r e d  R e s
    Analysis.Element = DEF_GC_MEASUREMENT_NAME::C.c_str();
    Analysis.Concentration = 4.2;
    CIntfData::insert(SeqAnalysis, Analysis);
    Analysis.Element = DEF_GC_MEASUREMENT_NAME::P.c_str();
    Analysis.Concentration = 0.1;
    CIntfData::insert(SeqAnalysis, Analysis);

    //-------Met Time Stamp
    sMetTimeStamp MetTimeStamp;
    CDateTime Now;
    sDate RevDate     = Now.assDate();
    sDate ActionDate  = Now.assDate();;
    
    MetTimeStamp.O2_Moment                = 11.000;
    MetTimeStamp.N2_Moment                = 12.000;
    MetTimeStamp.Ar_Moment                = 13.000;
    MetTimeStamp.Elec_Moment              = 14.000;
    MetTimeStamp.DurSinceHeatAnnouncement = 15.000;
    MetTimeStamp.DurSinceStartOfHeat      = 16.000;
    MetTimeStamp.RevDate                  = RevDate;
    MetTimeStamp.ActionDate               = ActionDate;
    
    //------GenRes
    GenRes.MetTimeStamp = MetTimeStamp;
    GenRes.Analysis     = SeqAnalysis;
    GenRes.SlagWeight   = 1000.000;
    GenRes.SteelWeight  = 2000.000;
    GenRes.Temp         = 1500.000;
    GenRes.DurPhase     = 1200.000;

    PredRes.Phase       = DEF_LF_PHASES::Actual;
    PredRes.PhaseNo     = 1;
    PredRes.GenRes      = GenRes;
    PredRes.PhaseActive = 1;

    CIntfData::insert(SeqPredRes, PredRes);

    PredRes.Phase       = DEF_LF_PHASES::Preparation;
    PredRes.PhaseNo     = 2;
    PredRes.GenRes      = GenRes;
    PredRes.PhaseActive = 1;

    CIntfData::insert(SeqPredRes, PredRes);

    PredRes.Phase       = DEF_LF_PHASES::Adjusting;
    PredRes.PhaseNo     = 3;
    PredRes.GenRes      = GenRes;
    PredRes.PhaseActive = 0;

    CIntfData::insert(SeqPredRes, PredRes);

    PredRes.Phase       = DEF_LF_PHASES::CleanStirring;
    PredRes.PhaseNo     = 4;
    PredRes.GenRes      = GenRes;
    PredRes.PhaseActive = 0;

    CIntfData::insert(SeqPredRes, PredRes);

    //---------BATCH
    Batch.MatCode       = "6100";
    Batch.Mass          = 200.7;
    Batch.MatFeedSpeed  = 70.3;
    BatchPrio.BatchData = Batch;
    BatchPrio.ChargPrio = 1;

    CIntfData::insert(SeqBatchPrio, BatchPrio);

    Batch.MatCode       = "3100";
    Batch.Mass          = 103.7;
    Batch.MatFeedSpeed  = 73.3;
    BatchPrio.BatchData = Batch;
    BatchPrio.ChargPrio = 2;

    CIntfData::insert(SeqBatchPrio, BatchPrio);

    Batch.MatCode       = "3501";
    Batch.Mass          = 250.7;
    Batch.MatFeedSpeed  = 72.3;
    BatchPrio.BatchData = Batch;
    BatchPrio.ChargPrio = 3;

    CIntfData::insert(SeqBatchPrio, BatchPrio);

    Batch.MatCode       = "3601";
    Batch.Mass          = 150.7;
    Batch.MatFeedSpeed  = 71.3;
    BatchPrio.BatchData = Batch;
    BatchPrio.ChargPrio = 4;

    CIntfData::insert(SeqBatchPrio, BatchPrio);

    //--------- 1. R E C I P E
    Recipe.RecipeName               = "SlagForm";
    Recipe.RecipeNo                 = 1;
    Recipe.RecipeSource             = "Bin";
    Recipe.MatFeedRate              = 7003;
    Recipe.ChargeMoment             = 111.1;
    Recipe.RecipeContent            = SeqBatchPrio;
    Recipe.RecipeData.HomogDuration = 700;
    Recipe.RecipeData.BulkVolume    = 77;
    Recipe.RecipeData.TotalMass     = 66.6;
    Recipe.Product.HeatId           = HeatID.c_str();
    Recipe.Product.TreatId          = TreatID.c_str();
    Recipe.Product.Plant            = Plant.c_str();

    CIntfData::insert(SeqRecipeList, Recipe);
    
    // ---------2. R E C I P E
    Recipe.RecipeName               = "AlloyFinal";
    Recipe.RecipeNo                 = 1;
    Recipe.RecipeSource             = "Bin";
    Recipe.MatFeedRate              = 0;
    Recipe.ChargeMoment             = 222.2;
    Recipe.RecipeContent            = SeqBatchPrio;
    Recipe.RecipeData.HomogDuration = 703;
    Recipe.RecipeData.BulkVolume    = 79;
    Recipe.RecipeData.TotalMass     = 55.5;
    Recipe.Product.HeatId           = HeatID.c_str();
    Recipe.Product.TreatId          = TreatID.c_str();
    Recipe.Product.Plant            = Plant.c_str();

    CIntfData::insert(SeqRecipeList, Recipe);

    //----------ELEC PRED RES
    for (long jj = 1; jj < 3; jj++)
    {
      LFElecPredRes.BaseMass            = 12.00;
      LFElecPredRes.DurStep             = 34.00+jj;
      LFElecPredRes.DurUntilEndOfStep   = 76.00;
      LFElecPredRes.DurUntilStartOfStep = 234.00;
      LFElecPredRes.ElecEgy             = 45.23;
      LFElecPredRes.ElecEgyStep         = 151;
      LFElecPredRes.ElecPhase           = DEF_LF_PHASES::HeatingInitial;
      LFElecPredRes.Enable              = 1;
      LFElecPredRes.GasType             = DEF_GAS::Ar;
      LFElecPredRes.ImpCurve            = jj;
      LFElecPredRes.Order               = 343;
      LFElecPredRes.Priority            = 1;
      LFElecPredRes.RevDate             = RevTime.assDate();
      LFElecPredRes.SpecEgy             = 332;
      LFElecPredRes.Step                = jj;
      LFElecPredRes.StirrFlow           = 323;
      LFElecPredRes.StirrIntensity      = 643;
      LFElecPredRes.StirrIntensityCode  = "6100";
      LFElecPredRes.VoltTap             = 4;

      CIntfData::insert(SeqLFElecPredRes, LFElecPredRes);
    }

    for (long jj = 1; jj < 3; jj++)
    {
      LFElecPredRes.BaseMass            = 12.00;
      LFElecPredRes.DurStep             = 35.00+jj;
      LFElecPredRes.DurUntilEndOfStep   = 76.00;
      LFElecPredRes.DurUntilStartOfStep = 234.00;
      LFElecPredRes.ElecEgy             = 45.23;  
      LFElecPredRes.ElecEgyStep = 142;
      LFElecPredRes.ElecPhase = DEF_LF_PHASES::HeatingMain;
      LFElecPredRes.Enable = 1;
      LFElecPredRes.GasType = DEF_GAS::Ar;
      LFElecPredRes.ImpCurve = 3+jj;
      LFElecPredRes.Order = 343;
      LFElecPredRes.Priority = 1;
      LFElecPredRes.RevDate = RevTime.assDate();
      LFElecPredRes.SpecEgy = 332;
      LFElecPredRes.Step = jj;
      LFElecPredRes.StirrFlow = 323;
      LFElecPredRes.StirrIntensity = 643;
      LFElecPredRes.StirrIntensityCode = "3601";
      LFElecPredRes.VoltTap = 5;

      CIntfData::insert(SeqLFElecPredRes, LFElecPredRes);
    }

    for (long jj = 1; jj < 3; jj++)
    {
      LFElecPredRes.BaseMass = 12.00;
      LFElecPredRes.DurStep  = 36.00+jj;
      LFElecPredRes.DurUntilEndOfStep = 76.00;
      LFElecPredRes.DurUntilStartOfStep = 234.00;
      LFElecPredRes.ElecEgy = 45.23;
      LFElecPredRes.ElecEgyStep = 133;
      LFElecPredRes.ElecPhase = DEF_LF_PHASES::HeatingFinal;
      LFElecPredRes.Enable = 1;
      LFElecPredRes.GasType = DEF_GAS::Ar;
      LFElecPredRes.ImpCurve = 2+jj;
      LFElecPredRes.Order = 343;
      LFElecPredRes.Priority = 1;
      LFElecPredRes.RevDate = RevTime.assDate();
      LFElecPredRes.SpecEgy = 332;
      LFElecPredRes.Step = jj;
      LFElecPredRes.StirrFlow = 323;
      LFElecPredRes.StirrIntensity = 643;
      LFElecPredRes.StirrIntensityCode = "3100";
      LFElecPredRes.VoltTap = 6;

      CIntfData::insert(SeqLFElecPredRes, LFElecPredRes);
    }

    //----------Stirr Pred Res
    // get all phases from the table
    std::string PhaseName;
    if (m_pGCL_STIRR_PHASE->select(CSMC_DBData::unspecString))
    {
      long length = m_pGCL_STIRR_PHASE->getLastRow();
      // there are only 19 fields in the telegramm
      if (length > 19)
        length = 19;
      for (long k = 1; k <= length; k++)
      {
        PhaseName = m_pGCL_STIRR_PHASE->getPRACPHASE(k);//DEF_LF_PHASES::Cooling;
        LFStirrPredRes.StirrPhase = PhaseName.c_str();
        if (m_pGCL_STIRR_PHASE->getFLAGDUR(k) > 0)
        {
          LFStirrPredRes.DurStep = k;
        }
        else
        {
          LFStirrPredRes.DurStep = 0;
        }

        LFStirrPredRes.DurUntilEndOfStep = 2434;
        LFStirrPredRes.DurUntilStartOfStep = 1235;
        LFStirrPredRes.ElecEgy = 452;
        LFStirrPredRes.Enable = 2;
        LFStirrPredRes.GasType = DEF_GAS::N2;
        LFStirrPredRes.ImpCurve = 534;
        LFStirrPredRes.isPatternOrActivity = 0;
        LFStirrPredRes.Order = k;
        LFStirrPredRes.Priority = 99;
        LFStirrPredRes.SlagMass = 452;
        LFStirrPredRes.SteelMass = 6342 + k;
        LFStirrPredRes.StirrIntensity = 1;
        LFStirrPredRes.StirrFlow = LFStirrPredRes.StirrIntensity;
        LFStirrPredRes.StirrIntensityCode = "435";
        LFStirrPredRes.Temp = 2314;
        LFStirrPredRes.VoltTap = 1245;

        CIntfData::insert(SeqLFStirrPredRes, LFStirrPredRes);
      }
      // if there were less rows, set the last many times
      if (length < 19)
      {
        for (long k = length; k <= 19; k++)
        {
          CIntfData::insert(SeqLFStirrPredRes, LFStirrPredRes);
        }
      }
    }


    // define incoming events for identifying offline calculations here !!!
    m_pModelResults =  m_pModelTask->getpModelResults();

    std::string DataKey = m_pModelResults->generateDataKey(ProductID);

    m_pModelResults->setRecipeList(DataKey.c_str(), DATA::LFMatRecipe, SeqRecipeList);
    m_pModelResults->setLFStirrPredRes(DataKey.c_str(), DATA::LFStirrPredRes, SeqLFStirrPredRes);
    m_pModelResults->setLFElecPredRes(DataKey.c_str(), DATA::LFElecPredRes, SeqLFElecPredRes);
    m_pModelResults->setPredRes(DataKey.c_str(), DATA::LFPredRes, SeqPredRes);

    // ****************************
    // ************* Computer Modes
    // ****************************
    
    seqComputerModes pseqComputerMode;
    sComputerMode    theComputerMode;

    theComputerMode.Device = DEF_COMP_MODES::Electric;
    theComputerMode.Status = DEF_GEN_STATES::Available;
    CIntfData::insert(pseqComputerMode, theComputerMode);

    theComputerMode.Device = DEF_COMP_MODES::Stirring;
    theComputerMode.Status = DEF_GEN_STATES::Available;
    CIntfData::insert(pseqComputerMode, theComputerMode);

    theComputerMode.Device = DEF_COMP_MODES::MatHandle;
    theComputerMode.Status = DEF_GEN_STATES::Available;  
    CIntfData::insert(pseqComputerMode, theComputerMode);

    theComputerMode.Device = DEF_COMP_MODES::Level2Error;
    theComputerMode.Status = DEF_GEN_STATES::NotAvailable;
    CIntfData::insert(pseqComputerMode, theComputerMode);

    theComputerMode.Device = DEF_COMP_MODES::RejectHeatL1;
    theComputerMode.Status = DEF_GEN_STATES::NotAvailable;
    CIntfData::insert(pseqComputerMode, theComputerMode);

    theComputerMode.Device = DEF_COMP_MODES::MatHandleL1Error;
    theComputerMode.Status = DEF_GEN_STATES::NotAvailable;
    CIntfData::insert(pseqComputerMode, theComputerMode);

    m_pModelResults->setComputerModes(DataKey.c_str(), DATA::ComputerModeAvail, pseqComputerMode);
    m_pModelResults->setComputerModes(DataKey.c_str(), DATA::ComputerModes, pseqComputerMode);


    // ****************************
    // ************* Sample Req
    // ****************************
    m_pModelResults->setBoolean(DataKey.c_str(), DATA::TempMeasReq, false);
    m_pModelResults->setBoolean(DataKey.c_str(), DATA::SteelSampleReq, false);

    // ****************************
    // ************* sent event
    // ****************************

    std::string ResultMessage;

    // if Event = evLFHeatAnnouncement send event evAODHeatAnnounceStatus to Archiver
    if (Message==LF_EvMsg::evLFHeatAnnouncement ||
        Message==LF_EvMsg::evLFHeatAnnouncementOffline)
    {
      ResultMessage = LF_EvMsg::evLFHeatAnnounceStatus;

      if (m_pModelTask->getOfflineCalculationStatus(ProductID))
      {
        ResultMessage = LF_EvMsg::evLFHeatAnnounceStatusOffline;
      }

      CEventMessage StatusEvent(Event);
      StatusEvent.setMessage(ResultMessage);

      // use EventMessage entry as default for SenderName
      std::string SenderName;
      cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage","SenderName",SenderName);

      // overwrite if necessary by inifile entry
      std::string TaskName    = m_pModelTask->getTaskName();
      cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"SenderName",SenderName);

      RetValue = dispatchEvent(SenderName,"",StatusEvent);
    }

    ResultMessage = LF_EvMsg::evLFModelResultRecipeSetpoints;

    if (m_pModelTask->getOfflineCalculationStatus(ProductID))
    {
      ResultMessage = LF_EvMsg::evLFModelResultRecipeSetpointsOffline;
    }

    CEventMessage ModelEvent(Event);
    ModelEvent.setMessage(ResultMessage);
    ModelEvent.setDataKey(DataKey);

    // use EventMessage entry as default for SenderName
    std::string SenderName;
    cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage","SenderName",SenderName);

    // overwrite if necessary by inifile entry
    std::string TaskName    = m_pModelTask->getTaskName();
    cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"SenderName",SenderName);

    //In case of LF_EvMsg::evLFHeatDeparture the Modelresults are only dumpt
    //The data for the actual calculation are not available any more
    if (Event.getMessage()!=LF_EvMsg::evLFHeatDeparture)
    {
      RetValue = dispatchEvent(SenderName,"",ModelEvent);
    }
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFModelTestResultWrapper::doModelResult()", "");    
  }

  return RetValue;

}