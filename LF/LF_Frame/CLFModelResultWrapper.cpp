// Copyright (C) 2004 SMS Demag AG

#include <sstream>

#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_EventLogFrameController.h"

#include "CEventMessage.h"

#include "CCtrlSystemCodesLF.h"
#include "CStirrPhaseCodesLF.h"
#include "CStirringDataHandler.h"

#include "CTempLossStat.h"
#include "CRS.h"
#include "CInv.h"

#include "CStirrPhaseCodesLF.h"
#include "CProcPhaseCodesLF.h"
#include "CStirrPhaseCodesLF.h"
#include "CSubRecipeCodesLF.h"
#include "CSourceLF.h"
#include "CDataConversion.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_PHASE.h"
#include "DEF_GC_RECIPE_SOURCE.h"
#include "DEF_GC_STIRR_GAS_TYPE.h"
#include "DEF_GCL_STIRR_PHASE.h"

#include "CGC_PhaseContainer.h"
#include "CPDL_ACTUAL_RES.h"
#include "CPDL_PHASE_STIRRING_RES.h"
#include "CPDL_PHASE_ELEC_RES.h"
#include "CPD_MAT_FEED_RES.h"
#include "CPD_MAT_AVAIL.h"
#include "CPD_PHASE_RES.h"
#include "CPD_PHASE_RES_PLANT.h"
#include "CPDL_ACTIVITY_RES.h"

#include "CLFModelResultWrapper.h"

//##ModelId=4151820803CC
CLFModelResultWrapper::CLFModelResultWrapper()
{
}

//##ModelId=4151820803E0
CLFModelResultWrapper::~CLFModelResultWrapper()
{
}

//##ModelId=417615BD0085
bool CLFModelResultWrapper::doModelResult(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFModelResultWrapper::doModelResult(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string Message   = Event.getMessage();

  try // common catch
  {
    std::string ResultMessage;

    // define incoming events for identifying offline calculations here !!!
    m_pModelResults =  m_pModelTask->getpModelResults();

    // its generate unique key
    m_Key = m_pModelResults->generateDataKey(Event.getProductID().c_str());

    doResultGeneral(Event);

    // check model interface for calculation type
    long TypeOfCalc = pIntfLF->getTypeOfCalc();

    std::stringstream msg1;
    msg1  << " -> Event occour for " << Event.getMessage() << " with Heat = " << Event.getHeatID() << " and Treat = " << Event.getTreatID() << " and TypeOfCalc = " << TypeOfCalc << " and value of CRS::ResultTypeGeneral = " << CRS::ResultTypeGeneral << " and value of CRS::ResultTypeWithoutRecipes = " << CRS::ResultTypeWithoutRecipes ;
    log(msg1.str(),3);

    long AnnounceStatus = 1;
    
    // if Event = evLFHeatAnnouncement send event evAODHeatAnnounceStatus to Archiver
    if (Message==LF_EvMsg::evLFHeatAnnouncement ||
        Message==LF_EvMsg::evLFHeatAnnouncementOffline)
    {
      ResultMessage = LF_EvMsg::evLFHeatAnnounceStatus;

      if (m_pModelTask->getOfflineCalculationStatus(ProductID))
      {
        ResultMessage = LF_EvMsg::evLFHeatAnnounceStatusOffline;
      }

      AnnounceStatus = (TypeOfCalc >= 2)?1:0;
      CEventMessage StatusEvent(Event);
      m_HeatCyclCalcNo = 0; 
      m_HeatPredCalcNo = 0;

      m_pModelResults->setLong(m_Key.c_str(), DATA::HeatAnnounceStatus, AnnounceStatus);
      StatusEvent.setMessage(ResultMessage);
      StatusEvent.setDataKey(m_Key);

      // use EventMessage entry as default for SenderName
      std::string SenderName;
      cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage","SenderName",SenderName);

      // overwrite if necessary by inifile entry
      std::string TaskName    = m_pModelTask->getTaskName();
      cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"SenderName",SenderName);

      RetValue = dispatchEvent(SenderName,"",StatusEvent);
    }

    // read respective data from model interface
    if (TypeOfCalc <= CRS::ResultTypeGeneral)
    {
      ResultMessage = LF_EvMsg::evLFModelResultCode;
      if (m_pModelTask->getOfflineCalculationStatus(ProductID))
      {
        ResultMessage = LF_EvMsg::evLFModelResultCodeOffline;
      }

    }
    else 
    {
      m_HeatCyclCalcNo += 1;
      doModelActualSetpoints(Event);
      ResultMessage = LF_EvMsg::evLFModelResultActualSetpoints;
      if (m_pModelTask->getOfflineCalculationStatus(ProductID))
      {
        ResultMessage = LF_EvMsg::evLFModelResultActualSetpointsOffline;
      }

      if (TypeOfCalc > CRS::ResultTypeWithoutRecipes)
      {
        m_HeatPredCalcNo += 1;
        doMatRecipeSetpoints(Event);
        ResultMessage = LF_EvMsg::evLFModelResultRecipeSetpoints;
      }
      if (m_pModelTask->getOfflineCalculationStatus(ProductID))
      {
        ResultMessage = LF_EvMsg::evLFModelResultRecipeSetpointsOffline;
      }
    }

    m_pModelResults->showContent(m_Key.c_str(),4);

    // generate return event and send it to event channel
    if (!ResultMessage.empty() && (Event.getMessage()!=LF_EvMsg::evLFHeatDeparture) )
    {
      CEventMessage ModelEvent(Event);
      ModelEvent.setMessage(ResultMessage);
      ModelEvent.setDataKey(m_Key);

      std::string SenderName;
      cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage","SenderName",SenderName);

      // overwrite if necessary by inifile entry
      std::string TaskName    = m_pModelTask->getTaskName();
      cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"SenderName",SenderName);

      //In case of LF_EvMsg::evLFHeatDeparture the Modelresults are only dumpt
      //The data for the actual calculation are not available any more
      if (Event.getMessage()!=LF_EvMsg::evLFHeatDeparture)
        RetValue = dispatchEvent(SenderName,"",ModelEvent);
      else
        log("heat Depature. Resultdate will not be considered",1);
    }
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "","CLFModelResultWrapper::doModelResult()", "" );    
  }

  return RetValue;
}

//##ModelId=4176160E02BD
bool CLFModelResultWrapper::doResultGeneral(CEventMessage& Event)
{
  bool RetValue = true;

  CIntfLF *pIntfLF = getpModelIntf();

  long ResultCode = pIntfLF->getResultCode();

  m_pModelResults->setLong(m_Key.c_str(), DATA::LFResCode, ResultCode);

  std::stringstream tmp;

  tmp << "General Model results:" << std::endl;
  tmp << "Result code:  " <<  ResultCode << std::endl;
  tmp << "LFComputerModeAvail:  " <<  std::endl;

  seqComputerModes SeqComputerModes;
  sComputerMode ComputerMode;

  ComputerMode.Device = DEF_COMP_MODES::MatHandle;
  ComputerMode.Status = pIntfLF->isCompuModeAvl(CCtrlSystemCodesLF::MatHndlg);
  CIntfData::insert(SeqComputerModes, ComputerMode);
  tmp << "Device/Status" <<  ComputerMode.Device <<"/"<<ComputerMode.Status << std::endl;

  ComputerMode.Device = DEF_COMP_MODES::MatHandleModel;
  CIntfData::insert(SeqComputerModes, ComputerMode);
  tmp << "Device/Status" <<  ComputerMode.Device <<"/"<<ComputerMode.Status << std::endl;

  ComputerMode.Device = DEF_COMP_MODES::Electric;
  ComputerMode.Status = pIntfLF->isCompuModeAvl(CCtrlSystemCodesLF::ElecHeatg);
  CIntfData::insert(SeqComputerModes, ComputerMode);
  tmp << "Device/Status" <<  ComputerMode.Device <<"/"<<ComputerMode.Status << std::endl;

  ComputerMode.Device = DEF_COMP_MODES::ElectricModel;
  ComputerMode.Status = pIntfLF->isCompuModeAvl(CCtrlSystemCodesLF::ElecHeatg);
  CIntfData::insert(SeqComputerModes, ComputerMode);
  tmp << "Device/Status" <<  ComputerMode.Device <<"/"<<ComputerMode.Status << std::endl;

  ComputerMode.Device = DEF_COMP_MODES::Stirring;
  ComputerMode.Status = pIntfLF->isCompuModeAvl(CCtrlSystemCodesLF::BotStirr);
  CIntfData::insert(SeqComputerModes, ComputerMode);
  tmp << "Device/Status" <<  ComputerMode.Device <<"/"<<ComputerMode.Status << std::endl;

  ComputerMode.Device = DEF_COMP_MODES::StirringModel;
  ComputerMode.Status = pIntfLF->isCompuModeAvl(CCtrlSystemCodesLF::BotStirr);
  CIntfData::insert(SeqComputerModes, ComputerMode);
  tmp << "Device/Status" <<  ComputerMode.Device <<"/"<<ComputerMode.Status << std::endl;

  m_pModelResults->setComputerModes(m_Key.c_str(), DATA::ComputerModeAvail, SeqComputerModes);

  if ( getTraceLevel() >= 3 )
  {
    log(tmp.str(), 3);
  }

  return RetValue;
}



//##ModelId=41761645038E
bool CLFModelResultWrapper::doModelActualSetpoints(CEventMessage& Event)
{
  bool RetValue = false;
  std::stringstream tmp;
  
  std::string Function = "CLFModelResultWrapper::doModelActualSetpoints()";

  CIntfLF *pIntfLF = getpModelIntf();

  if (!m_pModelResults)
  {
    handleError("CLFModelResultWrapper()", "doModelActualSetpoints: m_pModelResults = 0");
    return RetValue;
  }

  if (!checkDBConnection())
  {
    log("Error: " + Function + " , (checkDBConnection()) == false", 1);
    return false;
  }

  try 
  {
    std::string HeatId    = Event.getHeatID();
    std::string TreatId   = Event.getTreatID(); 
    std::string PlantID   = Event.getPlantID();
    std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
    long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

    m_pModelResults->setLong(m_Key.c_str(),DATA::HeatCyclCalcNo,m_HeatCyclCalcNo);
    m_pModelResults->setString(m_Key.c_str(),DATA::EventNameLastCyclCalc,Event.getMessage().c_str());

    if ( getTraceLevel() >= 3 )
    {
      tmp << "Actual Model Setpoints:" << std::endl;
      tmp << "Message: " << Event.getProductID() << " " <<Event.getMessage() << std::endl;
      tmp << "CalcNo:  " << m_HeatCyclCalcNo << std::endl;
      tmp << "ActualProcessPhase:  " << pIntfLF->getActualProcessPhase() << std::endl;
    }

    //call for retrieving current heating phase: 
    std::string HeatingStepCode = CProcPhaseCodesLF::Actual;    
    pIntfLF-> focusOnFirstPrdStepElec(HeatingStepCode);


    long VoltTap  = 0;
    long ImpCurve = 0;

    pIntfLF->getSetptElec(VoltTap, ImpCurve);

    bool    PullElecReq = (1L == pIntfLF->isPullElecReq());
    bool    ElecLockReq =        pIntfLF->isElecLockReq();
    double  Egy         =        pIntfLF->getRemEgy();

    m_pModelResults->setString(m_Key.c_str(), DATA::ElecPhaseName,    HeatingStepCode.c_str());

    m_pModelResults->setLong(m_Key.c_str(),DATA::VoltTapNoAim,        VoltTap);
    m_pModelResults->setLong(m_Key.c_str(),DATA::ElectrodRegCurveAim, ImpCurve);

    m_pModelResults->setLong(m_Key.c_str(),DATA::ElecPullReq,         PullElecReq);      
    m_pModelResults->setLong(m_Key.c_str(),DATA::ElecInhibitReq,      ElecLockReq);

    m_pModelResults->setDouble(m_Key.c_str(), DATA::TotalRemElecEgy,  Egy);

    //focusOnFirstPrdStepElec returns step with first alphabetical order by default
    std::string StirrStepCode = CProcPhaseCodesLF::Actual;

    std::string IntensityName;
    long        Priority;
    double      GasFlow;
    std::string GasType;

    pIntfLF->getActSuggestedStirringPhaseData(StirrStepCode, Priority, IntensityName, GasFlow, GasType);

    long Intensity = m_pGCL_STIRR_INT->getIntensityFromFlow( long(GasFlow) );

    bool TakeTempReq      = pIntfLF->isTakeTempReq();
    bool SteelSampleReq   = pIntfLF->isTakeSamplReq();

    double RemTreatDur    = pIntfLF->getRemDur();


    m_pModelResults->setDouble(m_Key.c_str(), DATA::LFActSetPointStirrFlow,     GasFlow);
                                          
    m_pModelResults->setLong(m_Key.c_str(),   DATA::LFActSetPointStirrIntensity,Intensity);

    m_pModelResults->setString(m_Key.c_str(), DATA::LFActSetPointStirrGasType,  GasType.c_str());

    m_pModelResults->setString(m_Key.c_str(), DATA::LFActStirrActivity,         StirrStepCode.c_str());

    m_pModelResults->setBoolean(m_Key.c_str(),DATA::TempMeasReq,                TakeTempReq);

    m_pModelResults->setBoolean(m_Key.c_str(),DATA::SteelSampleReq,             SteelSampleReq);

    m_pModelResults->setDouble(m_Key.c_str(), DATA::RemTreatDur,                RemTreatDur);         // = double


    if ( getTraceLevel() >= 3 )
    {
      tmp<<"HeatingStepCode: " << HeatingStepCode << std::endl;
      tmp<<"Aim Tap/Curve:   " << VoltTap         << ImpCurve << std::endl;
      tmp<<"TotalRemElecEgy: " << Egy             << std::endl;
      tmp<<"Pull Electrodes: " << PullElecReq     << std::endl;
      tmp<<"ElecInhibitReq:  " << ElecLockReq     << std::endl;


      tmp << "StirrStepCode "             << StirrStepCode  << std::endl;
      tmp << "AimFlow/Intesity/Gas "      << GasFlow        << "/"<< Intensity <<"/"<< GasType << std::endl;
      tmp << "Temperature taken required "<< TakeTempReq    << std::endl;
      tmp << "Sample taken required "     << SteelSampleReq << std::endl;
      tmp << "RemTreatDur "               << RemTreatDur    << std::endl;
    }

    // get Prediction Results
    seqPredRes        PredRes;

    if ( m_pGC_PHASE->selectOrdered(ActPlant, CSMC_DBData::unspecLong) )
    {
      for (int i = 1; i <= m_pGC_PHASE->getLastRow(); i++)
      {
        if (pIntfLF->focusOnStatus(m_pGC_PHASE->getPHASENAME(i)) == CRS::OK)
        {
          getModelResultsAtStatus(HeatId, TreatId, ActPlant, m_pGC_PHASE->getPHASENAME(i), m_pGC_PHASE->getPHASENO(i), PredRes);

          if ( isActualProcessPhase(m_pGC_PHASE->getPHASENAME(i), m_pGC_PHASE->getPHASENO(i)) )
          {
            m_pModelResults->setString(m_Key.c_str(),DATA::PhaseModel  , m_pGC_PHASE->getPHASENAME(i).c_str());
            m_pModelResults->setLong  (m_Key.c_str(),DATA::PhaseNoModel, m_pGC_PHASE->getPHASENO(i));
          }

        }
      }
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage,ActPlant.c_str(),"GC_PHASE");
    }

    // write result data into model result interface
    m_pModelResults->setPredRes(m_Key.c_str(), DATA::LFPredRes, PredRes);

    if ( getTraceLevel() >= 4 )
    {
      log(CIntfData::getContent(CIntfData::ToAny(PredRes)), 4);
    }

    // get Prediction Calculation results

    double TotalRemHeatingDur = 0.;
    seqLFElecPredRes  ElecPredRes;
    seqLFStirrPredRes StirrPredRes;

    getPredCalcResults(TotalRemHeatingDur, ElecPredRes, StirrPredRes);

    m_pModelResults->setDouble(m_Key.c_str(), DATA::TotalRemElecDur, TotalRemHeatingDur);

    m_pModelResults->setLFElecPredRes(m_Key.c_str(), DATA::LFElecPredRes, ElecPredRes);

    m_pModelResults->setLFStirrPredRes(m_Key.c_str(), DATA::LFStirrPredRes, StirrPredRes);

    seqComputerModes SeqComputerModes  = CIntfData::ToCORBAType(m_pModelResults->getComputerModes(m_Key.c_str(), DATA::ComputerModeAvail));

    if ( PredRes.length() > 0 || ElecPredRes.length() > 0 )
    {
      log("***********************************************************",3);
      log("****** New setpoints from LF-Model were calculated  *******",3);
      log("***********************************************************",3);
      m_pModelResults->showContent(m_Key.c_str(),4);

      RetValue = writeActualSetpointsToDB(Event, 
                                          PredRes, 
                                          ElecPredRes, 
                                          SeqComputerModes, 
                                          StirrPredRes);
      if ( !RetValue )
      {
        log("******************************************************",1);
        log("ERROR: Writing setpoints to DB was not successfull!!!!",1);
        log("******************************************************",1);
        m_pModelResults->showContent(m_Key.c_str(),1);
      }
    }
    else
    {
      log("***********************************************************",1);
      log("****** ERROR: Model did not calculate any new setpoints ***",1);
      log("***********************************************************",1);
    }

    log(tmp.str(), 3);

    RetValue = true;
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFModelResultWrapper::doModelActualSetpoints()", ""  );    
  }

    return RetValue;
}

//##ModelId=417616770372
bool CLFModelResultWrapper::doMatRecipeSetpoints(CEventMessage& Event)
{
  bool RetValue = false;

  std::string Function     = "CLFModelResultWrapper::doMatRecipeSetpoints";

  CIntfLF *pIntfLF = getpModelIntf();
  
  if (!pIntfLF || !m_pModelTask || !checkDBConnection()) 
  {
    log("error CLFModelResultWrapper::doMatRecipeSetpoints(), (pIntfLF && m_pModelTask && checkDBConnection()) == false", 1);
    return RetValue;
  }

  try 
  {
    std::string PlantID   = Event.getPlantID();
    std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
    long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

    m_pModelResults->setLong  (m_Key.c_str(),DATA::HeatPredCalcNo,       m_HeatPredCalcNo);
    m_pModelResults->setString(m_Key.c_str(),DATA::EventNameLastPredCalc,Event.getMessage().c_str());

    seqRecipeList MatRecList;

    if ( m_pGC_RECIPE_SOURCE->selectByPlant(ActPlant) )
    {
      for (int i = 1; i <= m_pGC_RECIPE_SOURCE->getLastRow(); i++)
      {
        const std::string RecipeName    = m_pGC_RECIPE_SOURCE->getRECIPENAME(i);
        const long        RecipeNo      = 1; 
        const std::string RecipeSource  = m_pGC_RECIPE_SOURCE->getSOURCE(i);

        if(RecipeSource == DEF_GC_RECIPE_SOURCE::All)     
        {
          continue;
        }

		    std::string RecipeNameModel;
		    long  RecipeNoModel = 0;

        if ( m_pRecipeHandler->translateToModelRecipe(ActPlant, RecipeName, RecipeNo, RecipeNameModel, RecipeNoModel) )
        {
          if (RecipeNameModel == CSubRecipeCodesLF::HighPriority)
          {
            continue;
          }

          pIntfLF->focusOnRecipeOrig(RecipeNameModel, RecipeNoModel, RecipeSource, true);

          sBatchPrio    strBatch;
          std::string   Code;
          seqBatchPrio  seqBatch;
          sRecipe       strRecipe;
          double        TotalMass   = 0.;
          std::string   HeatID;
          std::string   TreatID;
          std::string   Grade;

          while (pIntfLF->getMatSetpoint(Code, strBatch.BatchData.Mass, strBatch.BatchData.MatFeedSpeed, strBatch.ChargPrio) == CRS::OK)
          {
            strBatch.BatchData.MatCode = Code.c_str();
            if (strBatch.ChargPrio < 0) 
            {
              strBatch.ChargPrio = 1;
            }

            // use calculated material wight only if it is > minimum weight chargable by bin and > minimum weight to regarded for the material itself

            double MinChargeAbleWeightBin = 0.0;
            double MinChargeAbleWeightMat = 0.0;
            
            if ( m_pGT_MAT )
            {
              MinChargeAbleWeightMat = m_pGT_MAT->getMinWeightOfMatCode(Code);
            }

            if ( m_pPD_MAT_AVAIL )
            {
              MinChargeAbleWeightBin = m_pPD_MAT_AVAIL->getMinWeightOfMatCode(ActPlant, ActPlantNo, RecipeSource, CSMC_DBData::unspecLong, Code);
            }

            // check existance of data in DB
            MinChargeAbleWeightBin = CDataConversion::SetInvalidToDefault(MinChargeAbleWeightBin, 0.0, CSMC_DBData::unspecDouble);
            MinChargeAbleWeightMat = CDataConversion::SetInvalidToDefault(MinChargeAbleWeightMat, 0.0, CSMC_DBData::unspecDouble);

            // detect valid weight to be regarded by model result
            double MinChargeAbleWeight    = max( MinChargeAbleWeightBin , MinChargeAbleWeightMat );
          
            // check if material must be regarded
            if (strBatch.BatchData.Mass >= MinChargeAbleWeight)
            {
              CIntfData::insert(seqBatch, strBatch);
              TotalMass += strBatch.BatchData.Mass;
            }
            else
            {
              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_MinChargeableWeightViolated(sMessage, RecipeName.c_str(), strBatch.BatchData.MatCode, strBatch.BatchData.Mass, MinChargeAbleWeight );
            }
          }

          // wagn 2009-08-13 added : condition to prevent sending of empty-recipe telegrams (to avoid too much traffic) 
          // (this requires triggering of an explicit clearing of recipes on L1, which is provided in CLF_EventHandler of DH since today)   
          if (CIntfData::getLength(seqBatch) > 0)
          { 
            pIntfLF->getHeatData(HeatID, TreatID, Grade);
            strRecipe.RecipeName_Model         = RecipeNameModel.c_str();
            strRecipe.RecipeNo_Model           = RecipeNoModel;   
            strRecipe.RecipeSource             = RecipeSource.c_str();
            strRecipe.RecipeContent            = seqBatch;
            strRecipe.RecipeData.RecipeStatus  = 0;
            strRecipe.RecipeData.HomogDuration = pIntfLF->getHomogenizationDur();
            strRecipe.RecipeData.TotalMass     = TotalMass;
            strRecipe.RecipeData.BulkVolume    = 0.0;
            strRecipe.ChargeMoment             = 0.0;
            strRecipe.Product.HeatId           = HeatID.c_str();
            strRecipe.Product.TreatId          = TreatID.c_str();
            strRecipe.Product.Plant            = ActPlant.c_str();

            // use CSMC_RecipeHandler 
            std::string RecipeName_DB;    
            long        RecipeNo_DB = -1;

            if (m_pRecipeHandler)
            {
              m_pRecipeHandler->checkModelRecipeData(ActPlant,
                                                    HeatID,
                                                    TreatID,
                                                    RecipeSource,
                                                    RecipeNameModel,
                                                    RecipeNoModel,
                                                    RecipeName_DB,
                                                    RecipeNo_DB);
            }

            strRecipe.RecipeName  = RecipeName_DB.c_str();              // system recipe name        
            strRecipe.RecipeNo    = RecipeNo_DB;                        // recipe (free) version number 

            if ( std::string(strRecipe.RecipeName).empty() || strRecipe.RecipeNo == DEF::Inv_Long )
            {
              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_ErrorProcessingData(sMessage,"CLFModelResultWrapper::doMatRecipeSetpoints",RecipeNameModel.c_str() );
            }
            else
            {
              CIntfData::insert(MatRecList, strRecipe);
            }
          } // if (CIntfData::getLength(seqBatch) > 0)
        } // if ( m_pRecipeHandler->translateToModelRecipe(Plant, Recipe, RecipeNo, RecipeNameModel, RecipeNoModel) )
        else
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorHandlingRecipe(sMessage, RecipeName.c_str(), RecipeNo, Function.c_str());
        }

      } // for (int i = 1; i <= m_pGC_RECIPE_SOURCE->getLastRow(); i++)
    }

    m_pModelResults->setRecipeList(m_Key.c_str(), DATA::LFMatRecipe, MatRecList);

    // An empty recipe list mus be written also into DB,
    // because it is deleting the old calculated (not used) one.
    // Therefore the following if block should only log something depending on (non-)empty recipe list.
    // Additional remark: The Level1 will also get a new material setpoint telegram list,
    // but only consists of a so called delete recipe (Zero recipeno) if the calculated recipe list is empty!
    if ( MatRecList.length() > 0 )
    {
      log("***********************************************************",3);
      log("********* New recipes from Model were calculated **********",3);
      log("***********************************************************",3);
    }
    else
    {
      log("***********************************************************",1);
      log("****** ERROR: Model did not calculate any new recipes *****",1);
      log("***********************************************************",1);
    }      
    m_pModelResults->showContent(m_Key.c_str(),4);

    RetValue = writeRecipeSetpointsToDB(Event, MatRecList);
        
    if ( !RetValue )
    {
      log("ERROR: Writing Recipes to DB was not successfull!!!!", 1);
    }

  }    
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFModelResultWrapper::doMatRecipeSetpoints()", ""  );    

  }

  return RetValue;
}

//##ModelId=42A06E2B023B
void CLFModelResultWrapper::getPredCalcResults(double & TotalRemHeatingDur, seqLFElecPredRes  & ElecPredRes, seqLFStirrPredRes & StirrPredRes)
{
  std::string Function = "CLFModelResultWrapper::getPredCalcResults()";

  std::stringstream ExceptionMsg;

  CIntfLF *pIntfLF = getpModelIntf();


  long   TransfVoltTap  = 0;
  long   EltrdRegCurve  = 0;
  long   Enable         = 0;
  long   Order          = 0;
  long   Priority       = 0;
  long   lIntensity     = 0;
  double Egy          = 0.;
  double Duration     = 0.;
  double StepLength   = 0.;
  double StirringFlow = 0.;;
  double SteelMass    = 0.;
  double SlagMass     = 0.;
  double Temp         = 0.;

  std::string   PrdStepCode;
  std::string   Intensity;
  std::string   GasType;

  if (!checkDBConnection())
  {
    log("Error: " + Function + " , (checkDBConnection()) == false", 1);
    return;
  }

  try // common catch
  {
    m_pGCL_STIRR_INT->select(CSMC_DBData::unspecLong);


    // for determination of total remaining heating duration ++
    pIntfLF->focusOnStatus(CProcPhaseCodesLF::Actual);
    
    // Returns: elapsed time since start of heat until status (Proces phase) is reached.
    // If status is not yet reached, the time is predicted.
    // If status is already reached, the time is measured.
    double DurSinceAnnouncement = pIntfLF->getElapsedTimeUntilStatus();     // minutes

    double TotalRemHeatingDur   = 0.0;
    // for determination of total remaining heating duration --

    // electrical pattern
    ///////////////////////

    // returns step code in PrdStepCode
    pIntfLF->focusOnFirstPrdStepElec(PrdStepCode);

    double EgyTot = 0.0;
    // loop over all electrical prediction steps
    do // while (CRS::OK == pIntfLF->focusOnNextPrdStepElec(PrdStepCode));
    {
      //Method to get the model results for an electrical prediction step.
      if(CRS::OK == pIntfLF->getPredStepDataElec(TransfVoltTap, EltrdRegCurve, Egy))
      {
        sLFElecPredRes ElecStepRes;
        // Phase is substr of returned ElecStepCode with length of orig. length - 2

        // LF_MODEL should return phase and step seperately ! 
        string Phase = PrdStepCode.substr(0,PrdStepCode.length()-2);

        // Step Number is the last character of ElecStepCode
        string Step  = PrdStepCode.substr(PrdStepCode.length()-1, 1);

        if (m_pGCL_EL_PHASE->selectByPracPhaseDescr(Phase))
        {
          Phase=m_pGCL_EL_PHASE->getPRACPHASE(1);
        }
        else
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorSearchingData(sMessage,Phase.c_str(),"GCL_EL_PHASE");
        }
          
        pIntfLF->getPredStepData      (Duration,  StepLength,   Enable,  Order);
        pIntfLF->getPredStepDataStirr (Intensity, StirringFlow, GasType, Priority);

        Duration      = setToRange(Duration,-1,0);
        StepLength    = setToRange(StepLength,-1,0);
        StirringFlow  = setToRange(StirringFlow,-1,0);

        ElecStepRes.StirrIntensity   = CSMC_DBData::unspecLong; 

        for (int i = 1; i <= m_pGCL_STIRR_INT->getLastRow(); i++)
        {
          if (m_pGCL_STIRR_INT->getINTCODEMODEL(i) == Intensity)
          {
            ElecStepRes.StirrIntensity   = m_pGCL_STIRR_INT->getINTENSITY(i); 
            break;
          }
        }

        ElecStepRes.BaseMass           = pIntfLF->getSteelMassAtStatus(); 
        ElecStepRes.ElecPhase          = Phase.c_str();
        ElecStepRes.Step               = CDataConversion::StringToLong(Step);
        ElecStepRes.VoltTap            = TransfVoltTap;
        ElecStepRes.ImpCurve           = EltrdRegCurve;

        std::stringstream tmp1;
        tmp1 << " #####BaseMass : " << ElecStepRes.BaseMass ;
        //correction for heating pattern invalid double energies
        if  (CInv::InvalidDouble != Egy)
          EgyTot += Egy;
        else
          Egy = 0.0;

        ElecStepRes.ElecEgy            = EgyTot;
        
        //if (CLFModelTask::getInstance()->AimSteelWeight > 0.0) //GEPA 20100423 AimSteelWgt is nonsense and here always 0
        if (ElecStepRes.BaseMass > 0.0)
        {          
          tmp1 << " |EGY : " << Egy;  ;
          tmp1 << " |EGYTOT : " << EgyTot;  
          //ElecStepRes.SpecEgy          = Egy/(CLFModelTask::getInstance()->AimSteelWeight);
          ElecStepRes.SpecEgy          = Egy/(ElecStepRes.BaseMass); 
        }
        else
          ElecStepRes.SpecEgy            = 0.0;

        tmp1 << " |calc Spec : " << ElecStepRes.SpecEgy;  
        log(tmp1.str(),3);

        ElecStepRes.ElecEgyStep        = Egy;

        ElecStepRes.StirrIntensityCode = Intensity.c_str(); 
        ElecStepRes.StirrFlow          = StirringFlow;        // we use Nm³/min internally
        ElecStepRes.GasType            = GasType.c_str();
        ElecStepRes.Priority           = Priority;
        ElecStepRes.DurStep            = StepLength;
        ElecStepRes.Enable             = Enable;
        ElecStepRes.Order              = Order;
        ElecStepRes.DurUntilEndOfStep  = setToRange(Duration+ StepLength,-1,0);
        ElecStepRes.DurUntilStartOfStep= Duration; 

        if ( getTraceLevel() >= 3 )
        {
          std::stringstream tmp;
          tmp << "              Phase: " << ElecStepRes.ElecPhase           << std::endl
              << "DurUntilStartOfStep: " << ElecStepRes.DurUntilStartOfStep << std::endl
              << "  DurUntilEndOfStep: "   << ElecStepRes.DurUntilEndOfStep << std::endl
              << "            DurStep: " << ElecStepRes.DurStep             << std::endl
              << "            ElecEgy: " << ElecStepRes.ElecEgy             << std::endl
              << "            SpecEgy: " << ElecStepRes.SpecEgy             << std::endl
              << "            VoltTap: " << ElecStepRes.VoltTap             << std::endl
              << "           ImpCurve: " << ElecStepRes.ImpCurve            << std::endl
              << "               Step: " << ElecStepRes.Step                << std::endl
              << "         StepLength: " << StepLength                      << std::endl
              << "           Duration: " << Duration;                   

          log(tmp.str(),3);
        }

        CIntfData::insert(ElecPredRes, ElecStepRes);

        //Set value for total remaining heating dur
        if (ElecStepRes.DurUntilEndOfStep > DurSinceAnnouncement)
        {
          if (ElecStepRes.DurUntilStartOfStep < DurSinceAnnouncement)
            TotalRemHeatingDur += (ElecStepRes.DurUntilEndOfStep - DurSinceAnnouncement);
          else
            TotalRemHeatingDur += Duration;
        }
      }
    } while (CRS::OK == pIntfLF->focusOnNextPrdStepElec(PrdStepCode));


    if ( getTraceLevel() >= 4 )
    {
      log(CIntfData::getContent(CIntfData::ToAny(ElecPredRes)), 4);
    }
    // stirring pattern
    /////////////////////


    pIntfLF-> focusOnActivity("Switch-First-Next-Logic");

    pIntfLF-> focusOnFirstPrdStep(PrdStepCode);
    //
    do
    {
      //Method to get the model results for a stirring prediction step.
      if(CRS::OK == pIntfLF->getPredStepDataStirr(Intensity, StirringFlow, GasType, Priority))
      {
        sLFStirrPredRes StirrStepRes;

        pIntfLF->getPredStepData(Duration, StepLength, Enable, Order);

        StirrStepRes.StirrIntensity = CSMC_DBData::unspecLong; 
        for (int i = 1; i <= m_pGCL_STIRR_INT->getLastRow(); i++)
        {
			    if (m_pGCL_STIRR_INT->getINTCODEMODEL(i) == Intensity)
          {
			      StirrStepRes.StirrIntensity = m_pGCL_STIRR_INT->getINTENSITY(i); 
            break;
          }
        }

        SteelMass = pIntfLF->getSteelMassAtStatus();
        SlagMass  = pIntfLF->getSlagMassAtStatus();
        Temp      = pIntfLF->getTempAtStatus();

        // initialize sequence !
        StirrStepRes.SteelMass            = 0;
        StirrStepRes.SlagMass             = 0;       
        StirrStepRes.Temp                 = 0;
        StirrStepRes.VoltTap              = 0;
        StirrStepRes.ImpCurve             = 0;
        StirrStepRes.ElecEgy              = 0;

        if (SteelMass > 0.)
          StirrStepRes.SteelMass          = SteelMass;
        if (SlagMass  > 0.)
          StirrStepRes.SlagMass           = SlagMass;       
        if (Temp      > 0.)
          StirrStepRes.Temp               = Temp;
        
        pIntfLF->getPredStepDataElec(TransfVoltTap, EltrdRegCurve, Egy);

        if (TransfVoltTap > 0)
          StirrStepRes.VoltTap            = TransfVoltTap;
        if (EltrdRegCurve > 0)
          StirrStepRes.ImpCurve           = EltrdRegCurve;
        if (Egy           > 0.)
          StirrStepRes.ElecEgy            = Egy;

        StirrStepRes.StirrPhase           = PrdStepCode.c_str();
        StirrStepRes.StirrIntensityCode   = Intensity.c_str();

        StirrStepRes.StirrFlow            = StirringFlow; // we use Nm³/min internally
        StirrStepRes.GasType              = GasType.c_str();
        StirrStepRes.Priority             = Priority;
        StirrStepRes.DurStep              = StepLength;
        StirrStepRes.DurUntilStartOfStep  = Duration;
        StirrStepRes.DurUntilEndOfStep    = Duration + StepLength;
   
        //set order and enable info. to archive
        StirrStepRes.Order                = Order;

        if ( PrdStepCode != DEF_GCL_STIRR_PHASE::SlagBreaking    && 
          PrdStepCode != DEF_GCL_STIRR_PHASE::CoolingStirring && 
          PrdStepCode != DEF_GCL_STIRR_PHASE::CleanStirring   && 
          PrdStepCode != DEF_GCL_STIRR_PHASE::SoftStirring )
        {         
          StirrStepRes.Enable               = 0;
        }
        else
        {
          // this activity are enabled by model and activated by operator (push button L1)!!!
          //   StirrPhase == DEF_GCL_STIRR_PHASE::SlagBreaking     
          //   StirrPhase == DEF_GCL_STIRR_PHASE::CoolingStirring  
          //   StirrPhase == DEF_GCL_STIRR_PHASE::CleanStirring   
          //   StirrPhase == DEF_GCL_STIRR_PHASE::SoftStirring 
          StirrStepRes.Enable               = Enable;
        }

		    StirrStepRes.isPatternOrActivity  = 0;

        if ( getTraceLevel() >= 3 )
        {
          std::stringstream tmp;
          tmp << "         StirrPhase: " << StirrStepRes.StirrPhase           << std::endl
              << "DurUntilStartOfStep: " << StirrStepRes.DurUntilStartOfStep  << std::endl
              << "            DurStep: " << StirrStepRes.DurStep              << std::endl
              << " StirrIntensityCode: " << StirrStepRes.StirrIntensityCode   << std::endl
              << "            GasType: " << StirrStepRes.GasType              << std::endl
              << "          SteelMass: " << StirrStepRes.SteelMass            << std::endl
              << "          StirrFlow: " << StirrStepRes.StirrFlow;
          log(tmp.str(),3);
        }

        CIntfData::insert(StirrPredRes, StirrStepRes);
      }
    } while (CRS::OK == pIntfLF->focusOnNextPrdStep(PrdStepCode));

    if (m_pGCL_ACTIVITY->select(CSMC_DBData::unspecString))
    {
      for (int j=1;j<=m_pGCL_ACTIVITY->getLastRow();j++)
      {
        if (CRS::OK==pIntfLF->focusOnActivity(m_pGCL_ACTIVITY->getACTIVITYNAME(j)))
        {  //Method to get the model results for a stirring prediction step.
          sLFStirrPredRes StirrStepRes;

          if(CRS::OK == pIntfLF->getPredStepDataStirr(Intensity, StirringFlow, GasType, Priority))
          {
            //pIntfLF->getPredStepData(Duration, StepLength, Enable, Order);
            StirrStepRes.StirrIntensity = CSMC_DBData::unspecLong;

            for (int i = 1; i <= m_pGCL_STIRR_INT->getLastRow(); i++)
            {
  		        if (m_pGCL_STIRR_INT->getINTCODEMODEL(i) == Intensity)
              {
	              StirrStepRes.StirrIntensity = m_pGCL_STIRR_INT->getINTENSITY(i); 
	              lIntensity = m_pGCL_STIRR_INT->getINTENSITY(i); 
                break;
              }
            }
          }
          else // otherwise the activity like AimDur, ActDur and MinDur are not displayed in the graph
          {
            if (m_pGCL_STIRR_INT->getLastRow() >=1)
              Intensity = m_pGCL_STIRR_INT->getINTCODEMODEL(1);
            else
              Intensity = "";

            GasType   = "N2";
            lIntensity   = 0;
            StirringFlow = 0.0;
            Priority     = 0;
          }
          
          pIntfLF->getPredStepData(Duration, StepLength, Enable, Order);

          StirrStepRes.VoltTap              = 0;
          StirrStepRes.ImpCurve             = 0;
          StirrStepRes.ElecEgy              = 0;

          if (TransfVoltTap > 0)
            StirrStepRes.VoltTap            = TransfVoltTap;
          if (EltrdRegCurve > 0)
            StirrStepRes.ImpCurve           = EltrdRegCurve;
          if (Egy           > 0.)
            StirrStepRes.ElecEgy            = Egy;
            
          SteelMass                         = pIntfLF->getSteelMassAtStatus();
          SlagMass                          = pIntfLF->getSlagMassAtStatus();
          Temp                              = pIntfLF->getTempAtStatus();

          if (SteelMass > 0.)
            StirrStepRes.SteelMass          = SteelMass;
          if (SlagMass  > 0.)
            StirrStepRes.SlagMass           = SlagMass;       
          if (Temp      > 0.)
            StirrStepRes.Temp               = Temp;

          string ActivityName               = m_pGCL_ACTIVITY->getACTIVITYNAME(j);
          StirrStepRes.StirrPhase           = ActivityName.c_str();
          StirrStepRes.StirrIntensity       = lIntensity;
          StirrStepRes.StirrIntensityCode   = Intensity.c_str();
          StirrStepRes.StirrFlow            = StirringFlow;         // we use Nm³/min internally
          StirrStepRes.GasType              = GasType.c_str();
          StirrStepRes.Priority             = Priority;
          StirrStepRes.DurStep              = StepLength;
          StirrStepRes.DurUntilEndOfStep    = Duration + StepLength;
          StirrStepRes.DurUntilStartOfStep  = Duration ;

          //set order and enable info. to archive
          StirrStepRes.Order                = Order;
          StirrStepRes.Enable               = Enable;
          StirrStepRes.isPatternOrActivity  = 1;

            if ( getTraceLevel() >= 3 )
            {
              std::stringstream tmp;
              tmp << "         StirrPhase: " << StirrStepRes.StirrPhase           << std::endl                
                  << "        StirrEnable: " << StirrStepRes.Enable               << std::endl
                  << "DurUntilStartOfStep: " << StirrStepRes.DurUntilStartOfStep  << std::endl
                  << "            DurStep: " << StirrStepRes.DurStep              << std::endl
                  << " StirrIntensityCode: " << StirrStepRes.StirrIntensityCode   << std::endl
                  << "            GasType: " << StirrStepRes.GasType              << std::endl
                  << "          SteelMass: " << StirrStepRes.SteelMass            << std::endl
                  << "          StirrFlow: " << StirrStepRes.StirrFlow            << std::endl
                  << "StirrActivitys";
              log(tmp.str(),3);
            }

          CIntfData::insert(StirrPredRes, StirrStepRes);
          //}  if(CRS::OK == pIntfLF->getPredStepDataStirr(Intensity, StirringFlow, GasType, Priority))
        } // if (CRS::OK==pIntfLF->focusOnActivity(m_pGCL_ACTIVITY->getACTIVITYNAME(j)))
      } // for (int j=1;j<=m_pGCL_ACTIVITY->getLastRow();j++)
    } // if (m_pGCL_ACTIVITY->select(CSMC_DBData::unspecString))

    if ( getTraceLevel() >= 4 )
    {
      log(CIntfData::getContent(CIntfData::ToAny(StirrPredRes)), 4);
    }

  }
  catch(cCBS_DBExc &e) 
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Function.c_str(), ExceptionMsg.str().c_str());
    
    CLFModelWrapper::handleDBConnectionError();
  } // db catch
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      Function.c_str(), std::string("Unknown exception").c_str());    
  }
}


//##ModelId=41761773000D
void CLFModelResultWrapper::getMatRecipeSetpoints(const std::string & Plant, long PlantNo, const std::string & RecipeName, long RecipeNo, const std::string & Source, seqRecipeList &MatRecList)
{
  std::string Function = "CLFModelResultWrapper::getMatRecipeSetpoints()";

  sRecipe       strRecipe;
  sBatchPrio    strBatch;
  seqBatchPrio  seqBatch;
  long          MatSetpoint = 0;
  double        TotalMass   = 0;

  std::string   Code;
  std::string   HeatId, TreatId, Grade;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask || !checkDBConnection()) 
  {
    log("error CLFModelResultWrapper::getMatRecipeSetpoints(), (pIntfLF && m_pModelTask && checkDBConnection()) == false", 1);
    return ;
  }

  try // common catch
  {
    if(Source == DEF_GC_RECIPE_SOURCE::All)     
    {
      log("Source was ALL, returning getMatRecipeSetpoints without reading model interface ",2);  
      return;
    }

    // check catalogue of versions for model's recipes (table GC_RECIPE_L1)
		std::string RecipeNameModel;
		long  RecipeNoModel = 0;

    if ( m_pRecipeHandler->translateToModelRecipe(Plant, RecipeName, RecipeNo, RecipeNameModel, RecipeNoModel) )
    {
      if (RecipeNameModel != CSubRecipeCodesLF::HighPriority)
      {
        long retcode = pIntfLF->focusOnRecipeOrig(RecipeNameModel, RecipeNoModel, Source, true);

        std::stringstream tmp;
        tmp << "Model Recipe Result: " << RecipeNameModel ;

        if (RecipeNoModel!=0)
        {
          tmp << RecipeNoModel;
        }
        tmp << "|" << Source << std::endl;

        do // while (MatSetpoint == CRS::OK);
        {
          if(CRS::OK == (MatSetpoint = pIntfLF->getMatSetpoint(Code, strBatch.BatchData.Mass, strBatch.BatchData.MatFeedSpeed, strBatch.ChargPrio)))
          {
            tmp << Code <<" " << strBatch.BatchData.Mass << " Prio: " << strBatch.ChargPrio <<" FeedSpeed: " << strBatch.BatchData.MatFeedSpeed << std::endl;

            if (strBatch.ChargPrio < 0) 
            {
              strBatch.ChargPrio = 1; 
            }

            strBatch.BatchData.MatCode = Code.c_str();
            // compare Mass with appropriate MinWgt in PD_MAT_AVAIL 

            // if MatCode not found in PD_MAT_AVAIL store Batch
            // if Mass < MinWgt from PD_MAT_AVAIL don't store Batch
            tmp << " Model Result: " <<Code<<" "<< strBatch.BatchData.Mass;

            // use calculated material wight only if it is > minimum weight chargable by bin and > minimum weight to regarded for the material itself

            double MinChargeAbleWeightBin = 0.0;
            double MinChargeAbleWeightMat = 0.0;
            
            if ( m_pGT_MAT )
            {
              MinChargeAbleWeightMat = m_pGT_MAT->getMinWeightOfMatCode(Code);
            }

            if ( m_pPD_MAT_AVAIL )
            {
              MinChargeAbleWeightBin = m_pPD_MAT_AVAIL->getMinWeightOfMatCode(Plant, PlantNo, Source, CSMC_DBData::unspecLong, Code);
            }

            // check existance of data in DB
            MinChargeAbleWeightBin = CDataConversion::SetInvalidToDefault(MinChargeAbleWeightBin, 0.0, CSMC_DBData::unspecDouble);
            MinChargeAbleWeightMat = CDataConversion::SetInvalidToDefault(MinChargeAbleWeightMat, 0.0, CSMC_DBData::unspecDouble);

            // detect valid weight to be regarded by model result
            double MinChargeAbleWeight    = max( MinChargeAbleWeightBin , MinChargeAbleWeightMat );
          
            // check if material must be regarded
            if (strBatch.BatchData.Mass >= MinChargeAbleWeight)
            {
              CIntfData::insert(seqBatch, strBatch);
              TotalMass += strBatch.BatchData.Mass;
            }
            else
            {
              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_MinChargeableWeightViolated(sMessage, RecipeName.c_str(), strBatch.BatchData.MatCode, strBatch.BatchData.Mass, MinChargeAbleWeight );
            }

            tmp << std::endl;

          }
        } while (MatSetpoint == CRS::OK);

        tmp << "Recipe Mass: " << TotalMass << std::endl << std::endl;
        log(tmp.str(),3);


        // wagn 2009-08-13 added : condition to prevent sending of empty-recipe telegrams (to avoid too much traffic) 
        // (this requires triggering of an explicit clearing of recipes on L1, which is provided in CLF_EventHandler of DH since today)   
        if (CIntfData::getLength(seqBatch) > 0)
        {  
          strRecipe.RecipeName_Model         = RecipeName.c_str();
          strRecipe.RecipeName_Model         = RecipeNameModel.c_str();
          strRecipe.RecipeNo_Model           = RecipeNoModel;   
          strRecipe.RecipeSource             = Source.c_str();
          strRecipe.RecipeContent            = seqBatch;
          strRecipe.RecipeData.RecipeStatus  = 0;
          strRecipe.RecipeData.HomogDuration = pIntfLF->getHomogenizationDur();
          strRecipe.RecipeData.TotalMass     = TotalMass;
          strRecipe.RecipeData.BulkVolume    = 0.0;
          strRecipe.ChargeMoment             = 0.0;

          pIntfLF->getHeatData(HeatId, TreatId, Grade);
          strRecipe.Product.HeatId  = HeatId.c_str();
          strRecipe.Product.TreatId = TreatId.c_str();
          strRecipe.Product.Plant   = Plant.c_str();

          // use CSMC_RecipeHandler 
          std::string RecipeName_DB;    
          long        RecipeNo_DB = -1;

          if (m_pRecipeHandler)
          {
            m_pRecipeHandler->checkModelRecipeData(Plant,
                                                   HeatId,
                                                   TreatId,
                                                   Source,
                                                   RecipeNameModel,
                                                   RecipeNoModel,
                                                   RecipeName_DB,
                                                   RecipeNo_DB);
          }

          strRecipe.RecipeName  = RecipeName_DB.c_str();              // system recipe name        
          strRecipe.RecipeNo    = RecipeNo_DB;                        // recipe (free) version number 

          if ( std::string(strRecipe.RecipeName).empty() || strRecipe.RecipeNo == DEF::Inv_Long )
          {
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorProcessingData(sMessage,"CLFModelResultWrapper::getMatRecipeSetpoints",RecipeNameModel.c_str() );
          }
          else
          {
            CIntfData::insert(MatRecList, strRecipe);
          }
        } // if (CIntfData::getLength(seqBatch) > 0)
      } // if (RecipeNameModel != CSubRecipeCodesLF::HighPriority)
    } // if ( m_pRecipeHandler->translateToModelRecipe(Plant, Recipe, RecipeNo, RecipeNameModel, RecipeNoModel) )
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingRecipe(sMessage, RecipeName.c_str(), RecipeNo, Function.c_str());
    }

  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFModelResultWrapper::getMatRecipeSetpoints()", ""  );    
  }



}

//##ModelId=417616ED0304
bool CLFModelResultWrapper::getModelResultsAtStatus(const std::string& HeatID, const std::string& TreatID, const std::string& Plant, const std::string & Phase, long PhaseNo, seqPredRes& seqPredRes)
{
  bool RetValue = true;

  CIntfLF *pIntfLF = getpModelIntf();

  sPredRes             strPredRes;
  try // common catch
  {
    strPredRes.Phase    = Phase.c_str();
    strPredRes.PhaseNo  = PhaseNo;

    if ( isActualProcessPhase(Phase,PhaseNo) )
    {
      strPredRes.PhaseActive = 1;
    }
    else
    {
      strPredRes.PhaseActive = 0;
    }

    if ( CRS::OK == pIntfLF->focusOnStatus(Phase) )
    {
      strPredRes.GenRes.SteelWeight = pIntfLF->getSteelMassAtStatus();
      strPredRes.GenRes.SlagWeight  = pIntfLF->getSlagMassAtStatus();
      strPredRes.GenRes.Temp        = pIntfLF->getTempAtStatus();  

      // mrut 2012-11-14 : taken over from Essar

      ////// Returns: elapsed time since start of heat until status (Proces phase) is reached.
      ////// If status is not yet reached, the time is predicted.
      ////// If status is already reached, the time is measured.
      ////strPredRes.GenRes.DurPhase    = setToRange(pIntfLF->getDurOfStatus());
      ////// warning pIntfLF->getElapsedTimeUntilStatus() give elapsed time of start status
      ////double DateUntEndPhase = setToRange(pIntfLF->getElapsedTimeUntilStatus(), 0, 0) + strPredRes.GenRes.DurPhase;
      ////strPredRes.GenRes.MetTimeStamp.DurSinceHeatAnnouncement = DateUntEndPhase;

      // Returns: elapsed time since start of heat until status (Proces phase) is reached.
      // If status is not yet reached, the time is predicted.
      // If status is already reached, the time is measured.

      // >> mrut 2012-04-17 IBN Essar: warning pIntfLF->getElapsedTimeUntilStatus() give elapsed time of start status
      //
        strPredRes.GenRes.DurPhase                               = 0.0;
        strPredRes.GenRes.MetTimeStamp.DurSinceHeatAnnouncement  = setToRange(pIntfLF->getElapsedTimeUntilStatus(), 0, 0);
        if ( Phase != CProcPhaseCodesLF::Actual)                // due to the fact that time is stored differently for current phase (current time ) and finished phase (start time)
          strPredRes.GenRes.DurPhase                            += setToRange(pIntfLF->getDurOfStatus());

        strPredRes.GenRes.MetTimeStamp.DurSinceHeatAnnouncement += strPredRes.GenRes.DurPhase;
      // << mrut 2012-04-17 IBN Essar: warning pIntfLF->getElapsedTimeUntilStatus() give elapsed time of start status


      strPredRes.GenRes.MetTimeStamp.O2_Moment   = 0.;
      strPredRes.GenRes.MetTimeStamp.Ar_Moment   = 0.;
      strPredRes.GenRes.MetTimeStamp.N2_Moment   = 0.;
      strPredRes.GenRes.MetTimeStamp.Elec_Moment = 0.;

      sAnalysis   strAnalysis;
      seqAnalysis seqAnalysis;    
      std::string Name = "";
      double      Content;
      long        AnlAtStatus = 0;

      // To get the individual element or compound and corresponding content of the list 
      // the method must be called repeatedly until no value is returned (return value 1).
      do
      {
        AnlAtStatus = pIntfLF->getAnlAtStatus(Name, Content);
        if (AnlAtStatus != CRS::ErrorGen)
        {
          strAnalysis.Element = Name.c_str();
          strAnalysis.Concentration = Content;      
          CIntfData::insert(seqAnalysis,strAnalysis);
        }
      } while (AnlAtStatus != CRS::ErrorGen);


      //The Model gives no result for actual in case of LF departure.
      //Then we avoid to fill results for the status.
      if (   (strPredRes.GenRes.SteelWeight==0.)
        &&(strPredRes.GenRes.SlagWeight==0.)
        &&(strPredRes.GenRes.Temp==0.)
        &&(CIntfData::getLength(seqAnalysis)==0)
        )
      { 
        std::stringstream tmp;
        tmp << "Results LF Model for Phase " <<Phase << PhaseNo << " are not available;!";
        log(tmp.str(),1);
      }
      else
      {
        strPredRes.GenRes.Analysis = seqAnalysis;
        CIntfData::insert(seqPredRes,strPredRes);
      }

      if ( DEF_GC_PHASE::Actual == Phase)
      {
        m_pModelResults->setDouble(m_Key.c_str(), DATA::TempAct, strPredRes.GenRes.Temp);
      }
    }// if ( CRS::OK == pIntfLF->focusOnStatus(Phase) )
    else
    {
      std::stringstream tmp;
      tmp << "Results LF Model for Phase " << Phase << PhaseNo << " are not available;!";
      log(tmp.str(),1);
    }
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,  "", "CLFModelResultWrapper::getModelResultsAtStatus()", "");    
  }

  return RetValue;
}

bool CLFModelResultWrapper::isActualProcessPhase(const std::string& Phase, long PhaseNo)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF ) 
  {
    log("Error CLFModelResultWrapper::isActualProcessPhase, pIntfLF == false", 1);
    return RetValue ;
  }


  std::string ActProcessPhase = Phase;

  if ( PhaseNo > 0 )
  {
    ActProcessPhase = ActProcessPhase + CDataConversion::LongToString(PhaseNo);
  }

  if ( ActProcessPhase == pIntfLF->getActualProcessPhase() )
  {
    RetValue = true;
  }

  return RetValue;
}

double CLFModelResultWrapper::getDurationSince(DM::iDM_Interface_var& pDM_Interface,const std::string &Key, const char* Name)
{
  double Dur = DEF::Inv_Double;

  if (pDM_Interface)
  {
    std::stringstream LogMessage;
    LogMessage << " Calculate duration since:";
    LogMessage << Name;

    CDateTime now;
    CDateTime start;
    CDeltaTime dtTime;

    start.SetTime(pDM_Interface->getDate(Key.c_str(), Name));

    Dur = (double)(now.asTime_T() - start.asTime_T()) / 60;
    LogMessage << ". Duration (min): " << Dur;
    log(LogMessage.str(),3);
  }
  return Dur;
}


//****** writes new calculated setpoints to DataBase ****************************************
bool CLFModelResultWrapper::writeActualSetpointsToDB(CEventMessage &Event,
                                                      const seqPredRes            &SeqPredRes,
                                                      const seqLFElecPredRes      &SeqLFElecPredRes,
                                                      const seqComputerModes      &ComputerModeAvail,
                                                      const seqLFStirrPredRes     &SeqLFStirrPredRes)
{
  log("++++++ CLFModelResultWrapper::writeActualSetpointsToDB",3);
  bool RetValue = false;

  //------------ read the data from Event ------------------
  std::string HeatId    = Event.getHeatID();
  std::string TreatId   = Event.getTreatID(); 
  std::string ProductId = Event.getProductID();
  std::string OrderId   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantId   = Event.getPlantID();

  std::string Function     = "CLFModelResultWrapper::writeActualSetpointsToDB";
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getMessage() << " from " << Event.getSender()
    << ", " << ProductId << ", " << HeatId
    << ", " << TreatId   << ", " << DataKey;

  try
  {
    DM::iDM_Interface_var pDM_Interface = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT);

    if (m_pModelTask && pDM_Interface && m_pModelResults)
    {
      std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantId);
      long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantId);

      if (!checkDBConnection())
      {
        log(Function + " : database connection error",0);
        return false;
      }// if (!checkDBConnection())
      else
      {
        RetValue = true;

        //Required initialisation for database
        cCBS_StdConnection *pConnection = m_pModelTask->getStdConnection();
        CGC_PhaseContainer      GC_PhaseContainer(pConnection, ActPlant);
        CPDL_ACTUAL_RES         PDL_ACTUAL_RES(pConnection);
        CPDL_PHASE_STIRRING_RES PDL_PHASE_STIRRING_RES(pConnection);
        CPDL_PHASE_ELEC_RES     PDL_PHASE_ELEC_RES(pConnection);
        CPD_MAT_FEED_RES        PD_MAT_FEED_RES(pConnection);
        CPD_PHASE_RES           PD_PHASE_RES(pConnection);
        CPD_PHASE_RES_PLANT     PD_PHASE_RES_PLANT(pConnection);
        CPDL_ACTIVITY_RES       PDL_ACTIVITY_RES(pConnection);

        // main part
        CDateTime HeatAnnounceTime;
        HeatAnnounceTime.SetTime    (pDM_Interface->getDate(Event.getProductID().c_str(),DATA::HeatAnnounceTime));

        double DurSinceHeatAnnounce = getDurationSince(pDM_Interface, ProductId.c_str(), DATA::HeatAnnounceTime);
        double DurSinceHeatStart    = getDurationSince(pDM_Interface, ProductId.c_str(), DATA::HeatStartTime);

        std::string PhaseAct        = CIntfData::ToStdString(pDM_Interface->getString(ProductId.c_str(),DATA::PhaseAct));
        long PhaseNoAct             = pDM_Interface->getLong(ProductId.c_str(),DATA::PhaseNoAct);

        double ElecCons             = pDM_Interface->getDouble(ProductId.c_str(),DATA::ElecCons);
        double ElecConsPhase        = pDM_Interface->getDouble(ProductId.c_str(),DATA::ElecConsPhase);

        // use actual model value
        long ElecPullReq                  = m_pModelResults->getLong(m_Key.c_str(),DATA::ElecPullReq);
        long ElecLockReq                  = m_pModelResults->getLong(m_Key.c_str(),DATA::ElecInhibitReq);
        long VoltTapNoAim                 = m_pModelResults->getLong(m_Key.c_str(),DATA::VoltTapNoAim);
        long ElectrodRegCurveAim          = m_pModelResults->getLong(m_Key.c_str(),DATA::ElectrodRegCurveAim);

        if(ElecCons == DEF::Inv_Double ) ElecCons = 0.;

        log(Event.getMessage(),4);

        log(CIntfData::getContent(CIntfData::ToAny(SeqPredRes)),5);
        log(CIntfData::getContent(CIntfData::ToAny(SeqLFElecPredRes)),5);
        log(CIntfData::getContent(CIntfData::ToAny(SeqLFStirrPredRes)),5);
        log(CIntfData::getContent(CIntfData::ToAny(ComputerModeAvail)),5);

        if (CIntfData::getLength(SeqLFElecPredRes) > 0)
        {
          RetValue = RetValue && PDL_PHASE_ELEC_RES.writeResults(HeatId, TreatId, ActPlant, DurSinceHeatAnnounce, SeqLFElecPredRes);
          if (RetValue)
          {
            PDL_PHASE_ELEC_RES.commit();
          }
          else
          {
            PDL_PHASE_ELEC_RES.rollback();
          }
        }
        else
        {
          log("Warning: struct  SeqLFElecPredRes is empty!", 2);      
        }

        if (CIntfData::getLength(SeqLFStirrPredRes) > 0) 
        {
          RetValue = RetValue && PDL_PHASE_STIRRING_RES.writeResults(HeatId, TreatId, ActPlant, HeatAnnounceTime, SeqLFStirrPredRes);
          if (RetValue)
          {
            PDL_PHASE_STIRRING_RES.commit();
          }
          else
          {
            PDL_PHASE_STIRRING_RES.rollback();
          }
        }
        else
        {
          log("Warning: struct  SeqLFStirrPredRes is empty!", 2);
        }

        if (CIntfData::getLength(SeqLFStirrPredRes) > 0)
        {
          RetValue = RetValue && PDL_ACTIVITY_RES.writeResults(HeatId, TreatId, ActPlant, HeatAnnounceTime, SeqLFStirrPredRes, SeqLFElecPredRes, SeqPredRes);
          if (RetValue)
          {
            PDL_ACTIVITY_RES.commit();
          }
          else
          {
            PDL_ACTIVITY_RES.rollback();
          }
        }
        else
        {
          log("Warning: struct  SeqLFStirrPredRes is empty!", 2);
        }

        if (CIntfData::getLength(SeqPredRes) > 0) 
        {
          RetValue = RetValue && PDL_ACTUAL_RES.writeResults(HeatId, TreatId, ActPlant, PhaseAct, DurSinceHeatAnnounce, DurSinceHeatStart, ElecPullReq, ElecLockReq, SeqPredRes, 
            SeqLFElecPredRes, SeqLFStirrPredRes, ComputerModeAvail);
          if (RetValue)
          {
            PDL_ACTUAL_RES.commit();
          }
          else
          {
            PDL_ACTUAL_RES.rollback();
          }

          // ***********************************************
          // write result into PD_PHASE_RES and PD_PHASE_RES_PLANT
          // ***********************************************
          RetValue = PD_PHASE_RES.write(HeatId, TreatId, ActPlant, SeqPredRes, HeatAnnounceTime, false);

          if ( RetValue && PD_PHASE_RES.selectOrderedByDuration(HeatId,TreatId,ActPlant,true) )
          {
            double Duration_Prev  = 0.;

            for ( long i = 1 ; i <= PD_PHASE_RES.getLastRow(); ++i )
            {
              std::string PhaseName;
              long        PhaseNo         = CSMC_DBData::unspecLong;
              long        RESULTVALNO_EGY        = 1;
              long        RESULTVALNO_DUR        = 2;
              long        RESULTVALNO_EGY_PHASE  = 4;
              long        RES_PHASENO     = PD_PHASE_RES.getRES_PHASENO(i);
              double      Duration        = PD_PHASE_RES.getDURUNTENDOFPHASE(i);
              double      Energy          = 0.;
              double      EnergyPhase     = 0.;
              double      PhaseDur        = 0.;

              if ( RES_PHASENO != CSMC_DBData::unspecLong )
              {
                if ( Duration != CSMC_DBData::unspecDouble )
                {
                  Duration      = CDataConversion::RoundToDecimals(Duration,1);
                  Duration_Prev = CDataConversion::RoundToDecimals(Duration_Prev,1);

                  // Duration_Prev is always <= Duration due to selection ASC
                  PhaseDur  = Duration - Duration_Prev;
                }

                if ( GC_PhaseContainer.getPhaseDataByResPhaseNo(PhaseName,PhaseNo,RES_PHASENO) )
                {
                  // special data handling for phase "ACTUAL"
                  if ( PhaseName == DEF_GC_PHASE::Actual )
                  {
                    Energy = ElecCons;
                  }
                  else
                  {
                    // special data handling for phase "ADJUSTING" as summary of all electrical activities
                    if ( PhaseName == DEF_GC_PHASE::Adjusting )
                    {
                      for (int i = 0 ; i < CIntfData::getLength(SeqLFElecPredRes) ; ++i)
                      {
                        sLFElecPredRes ElecPredRes;
                        CIntfData::getAt(ElecPredRes,SeqLFElecPredRes,i);

                        // SeqElecRes contains accumulated electical values !
                        // we use the highest calculated energy
                        Energy       = max( Energy,      ElecPredRes.ElecEgy );
                        EnergyPhase += ElecPredRes.ElecEgyStep;
                      }
                    }// if ( PhaseName == DEF_GC_PHASE::Adjusting )
                  }
                }// if ( GC_PhaseContainer->getPhaseDataByResPhaseNo(PhaseName,PhaseNo,RES_PHASENO) )

                Energy      = CDataConversion::SetInvalidToDefault(Energy      , 0., CSMC_DBData::unspecDouble);
                EnergyPhase = CDataConversion::SetInvalidToDefault(EnergyPhase , 0., CSMC_DBData::unspecDouble);
                PhaseDur    = CDataConversion::SetInvalidToDefault(PhaseDur    , 0., CSMC_DBData::unspecDouble);

                RetValue = RetValue && PD_PHASE_RES_PLANT.write(HeatId, TreatId, ActPlant, RES_PHASENO, RESULTVALNO_EGY,         Energy,        false);
                //RetValue = RetValue && PD_PHASE_RES_PLANT->write(HeatId, TreatId, ActPlant, RES_PHASENO, RESULTVALNO_EGY_PHASE,   EnergyPhase,   true);
                RetValue = RetValue && PD_PHASE_RES_PLANT.write(HeatId, TreatId, ActPlant, RES_PHASENO, RESULTVALNO_DUR,         PhaseDur,      false);

                Duration_Prev = Duration;
              }
            } // for ( long i = 1 ; i <= PD_PHASE_RES->getLastRow(); ++i )
          }
          else
          {
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorSearchingData(sMessage,"","PD_PHASE_RES");
          }

          if (RetValue)
          {
            PD_PHASE_RES_PLANT.commit();
          }
          else
          {
            PD_PHASE_RES_PLANT.rollback();
          }
        }
        else
        {
          log("Warning: struct SeqPredRes is empty!", 2);
        }

        if ( RetValue )
        {
          m_pModelTask->getStdConnection()->commit();
        }
        else
        {
          m_pModelTask->getStdConnection()->rollback();

          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorReceivingModelResult(sMessage,HeatId.c_str(),TreatId.c_str(),ActPlant.c_str(),"missing prediction results");
        }
      }// if (checkDBConnection())
    }//if (m_pModelTask && pDM_Interface)
    else 
    {
      if (!m_pModelTask)
      {
        CLFModelWrapper::handleError("CLFModelResultWrapper", "m_pModelTask is null");
        RetValue = false;
      }
      if (!pDM_Interface)
      {
        CLFModelWrapper::handleError("CLFModelResultWrapper", "pDM_Interface is null");
        RetValue = false;
      }
      if (!m_pModelResults)
      {
        CLFModelWrapper::handleError("CLFModelResultWrapper", "m_pModelResults is null");
        RetValue = false;
      }
    }
  }
  catch (cCBS_DBExc &e)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Function.c_str(), ExceptionMsg.str().c_str());
    CLFModelWrapper::handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Function.c_str(), ExceptionMsg.str().c_str());    
  }
  catch(std::exception & e)
  {
    RetValue = false;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,e.what(),
      Function.c_str(), ExceptionMsg.str().c_str()); 
  }
  catch(...)
  {
    RetValue = false;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      Function.c_str(), std::string("Unknown exception").c_str());    
  }

  return RetValue;
}


//****** writes new calculated setpoints to DataBase ****************************************
bool CLFModelResultWrapper::writeRecipeSetpointsToDB(CEventMessage& Event, seqRecipeList &SeqRecipeList)
{
  log("++++++ CLFModelResultWrapper::writeRecipeSetpointsToDB",3);
  bool RetValue = false;

  //------------ read the data from Event ------------------
  std::string HeatId    = Event.getHeatID();
  std::string TreatId   = Event.getTreatID(); 
  std::string ProductId = Event.getProductID();
  std::string OrderId   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantId   = Event.getPlantID();

  std::string Function     = "CLFModelResultWrapper::writeRecipeSetpointsToDB";
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getMessage() << " from " << Event.getSender()
    << ", " << ProductId << ", " << HeatId
    << ", " << TreatId   << ", " << DataKey;

  try
  {
    DM::iDM_Interface_var pDM_Interface = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT);

    if (m_pModelTask && pDM_Interface)
    {
      std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantId);
      long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantId);

      // PRODUCT INTERFACE
      double DurSinceHeatAnnounce     = getDurationSince(pDM_Interface, ProductId.c_str(), DATA::HeatAnnounceTime);
      double DurSinceHeatStart        = getDurationSince(pDM_Interface, ProductId.c_str(), DATA::HeatStartTime);

      // update TimeStamp with measured values to store at PD_RECIPE
      double ElecCons                 = pDM_Interface->getDouble(ProductId.c_str(), DATA::ElecCons);      
      seqStirringData StirringAmount  = CIntfData::ToCORBAType(pDM_Interface->getStirringData(ProductId.c_str(),DATA::StirringAmount));

      CStirringDataHandler StirringAmountHandler;
      StirringAmountHandler.fill(StirringAmount);

      double O2_Moment = 0.0;
      double Ar_Moment = StirringAmountHandler.getAccumulatedGasValue(DEF_GC_STIRR_GAS_TYPE::Ar);
      double N2_Moment = StirringAmountHandler.getAccumulatedGasValue(DEF_GC_STIRR_GAS_TYPE::N2);

      for ( long i = 0 ; i < CIntfData::getLength(SeqRecipeList); ++i )
      {
        sRecipe Recipe;
        CIntfData::getAt(Recipe,SeqRecipeList,i);

        Recipe.TimeStamp.Elec_Moment  = ElecCons;
        Recipe.TimeStamp.O2_Moment    = O2_Moment;
        Recipe.TimeStamp.Ar_Moment    = Ar_Moment;
        Recipe.TimeStamp.N2_Moment    = N2_Moment;

        CIntfData::setAt(SeqRecipeList,Recipe, i);
      }

      RetValue = CSMM_ModelWrapper::writeRecipeSetpointsToDB(Event, SeqRecipeList, DurSinceHeatAnnounce, DurSinceHeatStart);

    }//if (m_pModelTask && pDM_Interface)
    else 
    {
      if (!m_pModelTask)
      {
        CLFModelWrapper::handleError("CLFModelResultWrapper", "m_pModelTask is null");
        RetValue = false;
      }
      if (!pDM_Interface)
      {
        CLFModelWrapper::handleError("CLFModelResultWrapper", "pDM_Interface is null");
        RetValue = false;
      }
    }
  }
  catch (cCBS_DBExc &e)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Function.c_str(), ExceptionMsg.str().c_str());
    CLFModelWrapper::handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Function.c_str(), ExceptionMsg.str().c_str());    
  }
  catch(std::exception & e)
  {
    RetValue = false;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,e.what(),
      Function.c_str(), ExceptionMsg.str().c_str()); 
  }
  catch(...)
  {
    RetValue = false;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      Function.c_str(), std::string("Unknown exception").c_str());    
  }

  return RetValue;
}

