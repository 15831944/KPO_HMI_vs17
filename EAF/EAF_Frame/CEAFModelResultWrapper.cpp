// Copyright (C) 2004 SMS Demag AG
#include <string>
#include <sstream>
#include <vector>
#include <deque>
#include <list>

#include "iSMC_DataProvider_s.hh"
#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"

#include "cCBS_StdInitBase.h"
#include "CSMC_EventLogFrameController.h"

#include "CIntfEAF.h"
#include "CCfgEAF.h"

#include "CInv.h"
#include "CRS.h"
#include "CCtrlSystemCodesEAF.h"
//#include "CProdPracTypCodesEAF.h"
#include "CProcPatCodesEAF.h"
#include "CTreatStatCodesEAF.h"
#include "CProcPhaseCodesEAF.h"
//#include "CPracPhaseCodesEAF.h"
#include "CKeyStringsEAF.h"
#include "CParamMgr.h"

#include "CProcCtrl.h"
//#include "CPurposeMgr.h"
//#include "CModel.h"

#include "CDataConversion.h"
#include "CGasLanceDataHandler.h"
#include "CStirringDataHandler.h"

#include "CGCE_BURNER.h"
#include "CGCE_INJECTION_TYPE.h"
#include "CGCE_INJECTION.h"
#include "CGC_COMBI_RECIPE_ENTRY.h"
#include "CGC_RECIPE_L1.h"
#include "CGC_RECIPE_SOURCE.h"

#include "CGTE_PP_FLAME_PROFILE.h"
#include "CGT_MAT.h"
#include "CGT_TREATMODE_ENTRY.h"

#include "CGC_PhaseContainer.h"
#include "CHD_TREATMODE.h"
#include "CPDE_ACTUAL_RES.h"
#include "CPDE_PHASE_BURNER_RES.h"
#include "CPDE_PHASE_INJECT_RES.h"
#include "CPDE_PHASE_PROCESS_RES.h"
#include "CPDE_PHASE_STIRRING_RES.h"
#include "CPD_MAT_AVAIL.h"
#include "CPD_MAT_FEED_RES.h"
#include "CPD_PHASE_RES.h"
#include "CPD_PHASE_RES_PLANT.h"
#include "CPD_PLANTSTATUS.h"
#include "CPP_ORDER_SINGLE_AIMS.h"

#include "DEF_GCE_BURNER.h"
#include "DEF_GCE_BURNER_GASTYPE.h"
#include "DEF_GC_PHASE.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_PP_ORDER_SINGLE_AIMS.h"
#include "DEF_GC_RECIPE_SOURCE.h"
#include "DEF_GCE_INJECTION_TYPE.h"
#include "DEF_GCE_INJECTION.h"
#include "DEF_GC_STIRR_GAS_TYPE.h"

#include "CEAFModelResultWrapper.h"

//##ModelId=45EBDA40021E
CEAFModelResultWrapper::CEAFModelResultWrapper()
{
}

//##ModelId=45EBDA40021C
CEAFModelResultWrapper::~CEAFModelResultWrapper()
{
}

bool CEAFModelResultWrapper::doModelResult(CEventMessage &Event, CEAFModelWrapper& ToCallBack)
{
  bool RetValue = false;

  return RetValue;
}

//##ModelId=45EBDA400214
bool CEAFModelResultWrapper::doModelResult(CEventMessage &Event)
{
  bool RetValue = false;

  std::string Scope = "CEAFModelResultWrapper::doModelResult()" ;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !checkDBConnection()) 
  {
    log("Error: " + Scope + " , (pIntfEAF || checkDBConnection()) == false", 1);
    return RetValue;
  }

  try 
  {
      std::string ResultMessage;
      
      m_pModelResults =  m_pModelTask->getpModelResults();

      std::string ActualProcessPhase (pIntfEAF->getActualProcessPhase());
      std::string Old_Key = (ActualProcessPhase == "Preparation")? "" : m_Key;

      // it generates unique key
      m_Key = m_pModelResults->generateDataKey(Event.getProductID());
      
      // get result code and computer mode-availabilities
      doModelGeneralResult(Event);

      // check model interface for calculation type
      long TypeOfCalc = pIntfEAF->getTypeOfCalc();
      
      std::stringstream msg1;
      msg1 << Scope << " -> Event occurred for " << Event.getMessage() << " with Heat = " << Event.getHeatID() << " and Treat = " << Event.getTreatID() << " and TypeOfCalc = " << TypeOfCalc << " and value of CRS::ResultTypeGeneral = " << CRS::ResultTypeGeneral << " and value of CRS::ResultTypeComplete = " << CRS::ResultTypeComplete ;
      log(msg1.str(),3);
      

      bool CurrentEventIsHeatAnnouncement =  (Event.getMessage() == EAF_EvMsg::evEAFHeatAnnouncement);
      if (CurrentEventIsHeatAnnouncement)
      {
        long AnnounceStatus = (TypeOfCalc > CRS::ResultTypeGeneral) ? 1:0;    //setpoints available ?

        m_HeatCyclCalcNo = 0;
        m_HeatPredCalcNo = 0;

        CEventMessage StatusEvent(Event);
        StatusEvent.setMessage(EAF_EvMsg::evEAFHeatAnnounceStatus);
        StatusEvent.setDataKey(m_Key);
 
        m_pModelResults->setLong(m_Key.c_str(), DATA::HeatAnnounceStatus, AnnounceStatus);

        // use EventMessage entry as default for SenderName
        std::string SenderName;
        cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage","SenderName",SenderName);

        // overwrite if necessary by inifile entry
        std::string TaskName    = m_pModelTask->getTaskName();
        cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"SenderName",SenderName);
        RetValue = dispatchEvent(SenderName,"",StatusEvent);

        if (AnnounceStatus == 0)
        { 
          std::stringstream msg;
          msg << Scope << " -> Model Announcement failed for " << Event.getHeatID() << "_" << Event.getTreatID();
          log(msg.str(), 1);
          return RetValue;        
        }

      }
  

      // read respective data from model interface
      if (TypeOfCalc <= CRS::ResultTypeGeneral)
      {
        ResultMessage = EAF_EvMsg::evEAFModelResultCode;                // only messages and computer modes
      }                                                                 
      else 
      {
        m_HeatCyclCalcNo += 1;
        doModelActualSetpoints(Event, Old_Key);                         
        ResultMessage = EAF_EvMsg::evEAFModelResultActualSetpoints;     // new actual setpoints available, except recipes
        if (TypeOfCalc == CRS::ResultTypeComplete )
        {
          m_HeatPredCalcNo += 1;                                          // also new recipe results available
          doMatRecipeSetpoints(Event);
          ResultMessage = EAF_EvMsg::evEAFModelResultRecipeSetpoints;
        }
      }

      m_pModelResults->showContent(m_Key.c_str(), 4);

      // generate return event and send it to event channel
      if (!ResultMessage.empty())
      {
        CEventMessage ModelEvent(Event);
        ModelEvent.setMessage(ResultMessage);
        ModelEvent.setDataKey(m_Key);

        // use EventMessage entry as default for SenderName
        std::string SenderName;
        cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage","SenderName",SenderName);

        // overwrite if necessary by inifile entry
        std::string TaskName    = m_pModelTask->getTaskName();
        cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"SenderName",SenderName);

        RetValue = dispatchEvent(SenderName,"",ModelEvent);
      }
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", Scope.c_str(), ""  );    
  } 

  return RetValue;
}

//##ModelId=467645DE0398
bool CEAFModelResultWrapper::doModelGeneralResult(CEventMessage &Event)
{
  bool RetValue = true;
  std::string Scope = "CEAFModelResultWrapper::doModelGeneralResult()" ;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF) 
  {
    log("Error: " + Scope + "  , (pIntfEAF  == false", 1);
    return RetValue;
  }

  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  m_pModelResults->setLong(m_Key.c_str(), DATA::EAFResCode, pIntfEAF->getResultCode());

  // get Computer Modes and Availabilities

  bool ElectricalStatus  (true); 
  bool PatternFeedStatus (true); 
  bool DynamicFeedStatus (true); 
  
  seqComputerModes SeqComputerModes;
    sComputerMode      ComputerMode;

  const CCfgEAF *      ModelConfiguration = getpCfgEAF();
  const map<string, long> & CtrlSystemMap = ModelConfiguration->getCtrlSystemSetptTyp();      
        map<string, long>::const_iterator   CtrlSystemItEnd (CtrlSystemMap.end());
        map<string, long>::const_iterator   CtrlSystemIt    (CtrlSystemItEnd);

  // material handling
      CtrlSystemIt  = CtrlSystemMap.find  (CCtrlSystemCodesEAF::BatchMatHndlg);
  if (CtrlSystemIt != CtrlSystemItEnd &&   CtrlSystemIt->second > 0)
  {
    ComputerMode.Device = DEF_COMP_MODES::MatHandle;
    ComputerMode.Status = pIntfEAF->isCompuModeAvl(CCtrlSystemCodesEAF::BatchMatHndlg);
    CIntfData::insert(SeqComputerModes, ComputerMode);

    ComputerMode.Device = DEF_COMP_MODES::MatHandleModel;
    CIntfData::insert(SeqComputerModes, ComputerMode);
  }

  //Stirring
  // #if defined (EAF_BOTTOM_STIRRING) // why?
      CtrlSystemIt  = CtrlSystemMap.find (CCtrlSystemCodesEAF::BottomStirringDevice);
  if (CtrlSystemIt != CtrlSystemItEnd &&  CtrlSystemIt->second > 0)
  {
    ComputerMode.Device = DEF_COMP_MODES::Stirring;
    ComputerMode.Status = pIntfEAF->isCompuModeAvl(CCtrlSystemCodesEAF::BottomStirringDevice);
    CIntfData::insert(SeqComputerModes, ComputerMode);

    ComputerMode.Device = DEF_COMP_MODES::StirringModel;
    CIntfData::insert(SeqComputerModes, ComputerMode);
  }
  //#endif  //why?

  //Injection
  //#if defined (EAF_INJECTION_LANCES)            //why?

  pair <std::string, long> ControlSystem ; 

  if ( CRS::OK == ModelConfiguration->getCmpModeForPurpose(CPurposeCodesEAF::CarbonInjection, ControlSystem) )
  //
  //CtrlSystemIt = CtrlSystemMap.find (CCtrlSystemCodesEAF::CarbonLance);
  //if (CtrlSystemIt != CtrlSystemItEnd && CtrlSystemIt->second > 0)
  {
    ComputerMode.Device = DEF_COMP_MODES::Injection;
    ComputerMode.Status = pIntfEAF->isCompuModeAvl(ControlSystem.first);
    CIntfData::insert(SeqComputerModes, ComputerMode);

    ComputerMode.Device = DEF_COMP_MODES::InjectionModel;
    CIntfData::insert(SeqComputerModes, ComputerMode);
  }
 // #endif

  //burner
  // #if defined (EAF_BURNER)
      CtrlSystemIt  = CtrlSystemMap.find (CCtrlSystemCodesEAF::Burner);
  if (CtrlSystemIt != CtrlSystemItEnd &&  CtrlSystemIt->second > 0)
  {
    ComputerMode.Device = DEF_COMP_MODES::Burner; 
    ComputerMode.Status = pIntfEAF->isCompuModeAvl(CCtrlSystemCodesEAF::Burner);
    CIntfData::insert(SeqComputerModes, ComputerMode);

    ComputerMode.Device = DEF_COMP_MODES::BurnerModel; 
    CIntfData::insert(SeqComputerModes, ComputerMode);
  }
  // #endif

  // electric
      CtrlSystemIt  = CtrlSystemMap.find (CCtrlSystemCodesEAF::Elec);
  if (CtrlSystemIt != CtrlSystemItEnd &&  CtrlSystemIt->second > 0)
  {
    ElectricalStatus    = pIntfEAF->isCompuModeAvl(CCtrlSystemCodesEAF::Elec);

    ComputerMode.Device = DEF_COMP_MODES::Electric;
    ComputerMode.Status = ElectricalStatus ? 1 :0;

    CIntfData::insert(SeqComputerModes, ComputerMode);

    ComputerMode.Device = DEF_COMP_MODES::ElectricModel;
    CIntfData::insert(SeqComputerModes, ComputerMode);
  }

  //door lance
  //#if defined (EAF_GAS_LANCES)

  // mrut 2010-05-31 - sorry
  std::pair <std::string, long> Id;
    
        CtrlSystemIt  = CtrlSystemMap.find (CCtrlSystemCodesEAF::ManipOxygenLance);
  if ( (CtrlSystemIt != CtrlSystemItEnd &&  CtrlSystemIt->second > 0) ||
     ( CRS::OK == ModelConfiguration->getCmpModeForPurpose(CCtrlSystemCodesEAF::ManipOxygenLance, Id ) ) )
  {
    ComputerMode.Device = DEF_COMP_MODES::GasLance;
    ComputerMode.Status = pIntfEAF->isCompuModeAvl(CCtrlSystemCodesEAF::ManipOxygenLance);
    CIntfData::insert(SeqComputerModes, ComputerMode);

    ComputerMode.Device = DEF_COMP_MODES::GasLanceModel;
    CIntfData::insert(SeqComputerModes, ComputerMode);
  }
  //#endif

  //dynamic feeding
  //#if defined(EAF_DYNAMIC_FEEDING)
      CtrlSystemIt  = CtrlSystemMap.find (CCtrlSystemCodesEAF::BinMatDynFeed);
  if (CtrlSystemIt != CtrlSystemItEnd &&  CtrlSystemIt->second > 0)
  {
    DynamicFeedStatus   = pIntfEAF->isCompuModeAvl(CCtrlSystemCodesEAF::BinMatDynFeed);

    ComputerMode.Device = DEF_COMP_MODES::DynamicFeed ; 
    ComputerMode.Status = DynamicFeedStatus ? 1 :0;
    CIntfData::insert(SeqComputerModes, ComputerMode);

    ComputerMode.Device = DEF_COMP_MODES::DynamicFeedModel ;  
    CIntfData::insert(SeqComputerModes, ComputerMode);
  }
  //#endif

  //pattern feeding
  //#if defined(EAF_PATTERN_FEEDING)
      CtrlSystemIt  = CtrlSystemMap.find (CCtrlSystemCodesEAF::BinMatPatternFeed);
  if (CtrlSystemIt != CtrlSystemItEnd &&  CtrlSystemIt->second > 0)
  {
    PatternFeedStatus   = pIntfEAF->isCompuModeAvl(CCtrlSystemCodesEAF::BinMatPatternFeed);

    ComputerMode.Device = DEF_COMP_MODES::PatternFeed;  
    ComputerMode.Status = PatternFeedStatus ? 1 :0;
    CIntfData::insert   (SeqComputerModes, ComputerMode);
 
    ComputerMode.Device = DEF_COMP_MODES::PatternFeedModel; 
    CIntfData::insert(SeqComputerModes, ComputerMode);
  }
  //#endif

  // cmp. mode process (from JSL,JSPL), combines electrical and feeding modes
  ComputerMode.Device = DEF_COMP_MODES::Process;  
  ComputerMode.Status = (ElectricalStatus && PatternFeedStatus && DynamicFeedStatus) ? 1: 0;
  CIntfData::insert(SeqComputerModes, ComputerMode);


  // missing : 
  //           JetModule (to be clarified)
  //           pdc, OxygenLance, ...        (to be adapted for other customers..)
  m_pModelResults->setComputerModes(m_Key.c_str(), DATA::ComputerModeAvail, SeqComputerModes);

  return RetValue;
}

//##ModelId=45EBDA4001DC
bool CEAFModelResultWrapper::doModelActualSetpoints(CEventMessage &Event, const std::string& Old_Key)
{
  bool RetValue = false;


//------------ read the data from Event ------------------
  std::string HeatId    = Event.getHeatID();
  std::string TreatId   = Event.getTreatID(); 
  std::string ProductId = Event.getProductID();
  std::string OrderId   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantId   = Event.getPlantID();

  std::string Scope = "CEAFModelResultWrapper::doModelActualSetpoints()" ;

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getMessage() << " from " << Event.getSender()
    << ", " << ProductId << ", " << HeatId
    << ", " << TreatId   << ", " << DataKey;



  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !checkDBConnection()) 
  {
    log("Error " + Scope + " , (pIntfEAF || checkDBConnection()) == false", 1);
    return RetValue ;
  }

  if (!m_pModelResults)
  {
    log("Error " + Scope + " , (m_pModelResults  == false", 1);
    return RetValue ;
  }


  m_pModelResults->setLong  (m_Key.c_str(),DATA::HeatCyclCalcNo,        m_HeatCyclCalcNo);
  m_pModelResults->setString(m_Key.c_str(),DATA::EventNameLastCyclCalc, Event.getMessage().c_str());
  
  
  seqPredRes              PredRes;
  seqEAFProcessPredRes    ElecPredRes; 
  seqEAFInjectLance       InjctPredRes;
  seqEAFGasLancePredRes   GasLancePredRes; 
  seqEAFGasLancePredRes   BottomStirrPredRes; 
  seqEAFBurnerPredRes     BurnerPredRes; 
  seqEAFMatFeedPredRes    MatFeedPredRes;
  
  try 
  {
    double EgyConsElecSincePhaseStart   = 0.0;
    double EgyConsElecTotal             = 0.0;
    double DurPhase                     = 0.0;
    double DurTotal                     = 0.0;
    double RemTreatDurSinceHeatAnnounce = 0.0;
    long   LastBsk                      = 0;
    long   IsCharged                    = 0;
    std::string MPhaseTyp;
    long   MPhaseNo=0;
    

    double DurationOfPrepPhase = -1;  // preset (invalid)

    std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantId);
    long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantId);

    
    pIntfEAF->getKeyedInformation("EgyConsElecSincePhaseStart", 0L,   MPhaseTyp, MPhaseNo,  EgyConsElecSincePhaseStart);
    pIntfEAF->getKeyedInformation("EgyConsElecTotal", 0L,             MPhaseTyp, MPhaseNo,  EgyConsElecTotal);
    pIntfEAF->getKeyedInformation("MphasTypandNo",    0L,             MPhaseTyp, MPhaseNo,  EgyConsElecTotal);
    pIntfEAF->getKeyedInformation("CKeyStringsEAF::ProcSphasChgd",0L, MPhaseTyp, IsCharged, EgyConsElecTotal);    
    pIntfEAF->getKeyedInformation("LastBskNo",0L, MPhaseTyp, LastBsk , DurTotal);
    pIntfEAF->getKeyedInformation("DurPhase" ,0L, MPhaseTyp, IsCharged, DurPhase);
    pIntfEAF->getKeyedInformation("DurTotal" ,0L, MPhaseTyp, IsCharged, DurTotal);
   
    // **************************************************************************************************************************************
    // Data of particular importance for the stability of the output-pattern:
    // 
    // This seems simple, but may offer a variety of traps for the optimistic programmer. A key issue is to know which phase we are 
    // in at the moment and if a phase-change has occured since the last pattern update by the model.
    //
    //                                  Therefore, BE WARNED to work on this issue.
    //
    // **************************************************************************************************************************************

     { // logging Treatment Information
        std::stringstream tmp;
        tmp << " Treatment Information: " << MPhaseTyp << MPhaseNo << ", Charged = "  << IsCharged 
                       << ", DurPhase = " << DurPhase              << ", DurTotal = " << DurTotal;                 
        log(tmp.str(), 2);
      }

    // ///////////////////////////////////////////////////////////////////
    // get treatment status results 
    // ///////////////////////////////////////////////////////////////////
    std::string ActualStatus  (CTreatStatCodesEAF::Actual);
    std::string HotHeelStatus (CTreatStatCodesEAF::HotHeel);

    long ret =  pIntfEAF->focusOnTreatStat (ActualStatus);
    if  (ret == CRS::OK) 
         getModelResultsAtStatus (HeatId, TreatId, ActPlant, ActualStatus, 0, PredRes);

         ret = pIntfEAF->focusOnTreatStat (HotHeelStatus);
    if  (ret == CRS::OK) 
         getModelResultsAtStatus (HeatId, TreatId, ActPlant, HotHeelStatus, 0, PredRes);


    // todo : handle return code of getModelResultsAtStatus ?!?
    //        what, if ret is not ok ??

    // ///////////////////////////////////////////////////////////////////
    // get process phase's predicted status values 
    // ///////////////////////////////////////////////////////////////////  
    deque < pair<std::string, long> > PhasesToCallFor;

    //@SANKAR : read all treatment phases from table 
    long TreatmentModeNo = -1 ;

    if (m_pHD_TREATMODE && m_pHD_TREATMODE->select(Event.getHeatID(), Event.getTreatID(),  ActPlant, CSMC_DBData::unspecLong) ) 
    {
      TreatmentModeNo =  m_pHD_TREATMODE->getTREATMODENO(1);
    }

    if(m_pGT_TREATMODE_ENTRY && m_pGT_TREATMODE_ENTRY->selectOrdered(ActPlant,ActPlantNo,TreatmentModeNo,CSMC_DBData::unspecString,CSMC_DBData::unspecLong))
    {
      for (int k = 1; k <=   m_pGT_TREATMODE_ENTRY->getLastRow(); ++k)
        PhasesToCallFor.push_back (make_pair( m_pGT_TREATMODE_ENTRY->getTREATMENTPHASE(k),m_pGT_TREATMODE_ENTRY->getTREATMENTPHASENO(k)) );
    }
    
    //        what, if read is not ok ??

    deque < pair<std::string, long> >::iterator Phit (PhasesToCallFor.begin());
    for (;Phit != PhasesToCallFor.end(); ++Phit)
    {
      const std::string & ProcPhase   ( Phit->first );
      long           ProcPhaseNo ( Phit->second);

      long ret = pIntfEAF->focusOnProcPhase(ProcPhase, ProcPhaseNo);
      if ( ret== CRS::OK)
      {
        double ElapsedTimeUntilEndOfProcPhase = setToRange(pIntfEAF->getElapsedTimeUntilEndOfProcPhase(), 0, 0);
        double ElapsedTimeUntilStatus         = setToRange(pIntfEAF->getElapsedTimeUntilStatus(), 0, 0);

        RemTreatDurSinceHeatAnnounce         += setToRange(pIntfEAF->getDurOfStatus());

        if (DurationOfPrepPhase < 0.)            // preparation considered as first step
            DurationOfPrepPhase = ElapsedTimeUntilEndOfProcPhase;


        //RemTreatDur = max(RemTreatDur, ElapsedTimeUntilEndOfProcPhase - ElapsedTimeUntilStatus);

        getModelResultsAtStatus(HeatId, TreatId, ActPlant, ProcPhase, ProcPhaseNo, PredRes);
                               
        // to do: check, if next block may be put upward after  :   long ret =  pIntfEAF->focusOnTreatStat (ActualStatus);
        if ( isActualProcessPhase(ProcPhase, ProcPhaseNo) )
        {
          //-  merge from JSPL - only for valid for actual phase
          PredRes[CIntfData::getLength(PredRes)-1].GenRes.MetTimeStamp.Elec_Moment = EgyConsElecTotal;

          m_pModelResults->setString(m_Key.c_str(),DATA::PhaseModel  , ProcPhase.c_str());
          m_pModelResults->setLong  (m_Key.c_str(),DATA::PhaseNoModel, ProcPhaseNo );
        }
      }
    }

    std::stringstream tmp;
    tmp << " Treatment duration information for " << Event.getHeatID() << ": ";  

    CDateTime Now;
    CDateTime EndPhase;

    EndPhase = m_pModelTask->getActHeatAnnouncementTime(Event);

    EndPhase = CDataConversion::SetInvalidToDefault(EndPhase,Now);

    tmp  << " ActHeatAnnouncementTime = " << EndPhase.asString();

    EndPhase.addTime(RemTreatDurSinceHeatAnnounce * 60.0);

    tmp  << ", RemTreatDurSinceHeatAnnounce = " << RemTreatDurSinceHeatAnnounce;

    tmp  << ", EndPhaseTime = " << EndPhase.asString();

    CDeltaTime dtTime  = CDateTime::subTimes(EndPhase, Now);
    double RemTreatDur = dtTime.asSeconds()/60;

    tmp  << ", RemTreatDur = " << RemTreatDur;

    m_pModelResults->setDouble(m_Key.c_str(), DATA::RemTreatDur,                RemTreatDur);         // = double

    log(tmp.str(), 4);

      
    // ///////////////////////////////////////////////////////////////////
    // get process phase's predicted setpoints
    // ///////////////////////////////////////////////////////////////////

    for (Phit = PhasesToCallFor.begin();Phit != PhasesToCallFor.end(); ++Phit)
    {
      const std::string & ProcPhaseType   ( Phit->first  );
      long           ProcPhaseNumber ( Phit->second );
      
      if( (ProcPhaseType == DEF_GC_PHASE::Preparation) || (ProcPhaseType == DEF_GC_PHASE::Tapping) || (ProcPhaseType == DEF_GC_PHASE::Tapped) )
        continue;       // (no continuous setpoints)

      long ret = pIntfEAF->focusOnProcPhase(ProcPhaseType, ProcPhaseNumber);
      if ( ret== CRS::OK)
      {
        double BaseMass = pIntfEAF->getBaseMass();

        // Electric, GasLance(O2) & Carbon Injection(C)
        getPredCalcResults(ActPlant, ActPlantNo, ProcPhaseType, ProcPhaseNumber, ElecPredRes, GasLancePredRes, InjctPredRes, BottomStirrPredRes, BaseMass);

        // burner
        getPredCalcResults(ActPlant, ActPlantNo, ProcPhaseType, ProcPhaseNumber, BurnerPredRes, BaseMass);
        
        // feeding pattern
        getPredCalcResults(ActPlant, ActPlantNo, ProcPhaseType, ProcPhaseNumber, MatFeedPredRes, BaseMass);
        
      }
    }

      // Electric energy block start
      // *******************************************************************************************************************************
      //mrut 2012-10-19
      //
      // what is to be done here is to merge a previous pattern with a new pattern.
      // The model holds its patterns for different setpoints separately.
      // However, it turned out that a merge may be done only  for the electrical pattern, as only there we have
      // a unique step number returned by the model. This means all this works only, if all subpatterns are
      // synchronised, at least those that appear in the same tabel on the l1.
      //
      // Indeed it seems that the pattern(s) have to be merged by a step identification number,
      // as the model may unexpectedly change the steps attribute values, like energy, time etc.
      // Therefore these are not suitable to compare or merge two patterns.
      // Only a step id can clearly relate a step of a previous pattern to a step of a current pattern.
      // *******************************************************************************************************************************
      //
      // mrut 2014-02-06, work on JIRA SMPJSWTWO-47, SMPJSWTWO-55 : determination of material amount for feeding
      // mrut 2006-05-29: sorting by electrical energy moved here
      SORT_SEQ(ElecPredRes, sEAFProcessPredRes, ElecEgy);
      //
      //new sequence is sorted now, for any old sequence we assume that is was already sorted.

      // now ,determine the active step for material feeding, if feeding patter is aligned to electrical pattern, use electric step, otherwise feeding step.
      long          TmpSeqLenElectric = CIntfData::getLength(ElecPredRes);
      long          TmpSeqLenMatFeed  = CIntfData::getLength(MatFeedPredRes);
      long CurrentlyActiveStepMatFeed = (TmpSeqLenElectric <= 0)? -1 : ( (TmpSeqLenElectric == TmpSeqLenMatFeed)? ElecPredRes[0].Step : MatFeedPredRes[0].Step);


      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //                                prediction steps processing, merging of old steps with new steps
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      {

      // //////////////////////////////////// //
      // //////////////////////////////////// //
      // >> compare with previous result !!   //
      // //////////////////////////////////// //
      // //////////////////////////////////// //

      // mrut 2006-01-25 next is required to achieve a stable result pattern:
      //                 actual energy consumption & flag if basket charged.
      //

      double Egy_Ref = (IsCharged == 1)?  EgyConsElecTotal : (EgyConsElecTotal - EgyConsElecSincePhaseStart);
      double Dur_Ref = (IsCharged == 1)?          DurTotal : (DurTotal - DurPhase);


      // get alignment configuration from model

      const CCfgEAF *      ModelConfiguration = getpCfgEAF();

      bool GasLancesAligned   = ModelConfiguration->isProcessProfileAlignedFor(CMeasConsCodesEAF::ManipGasLance);         // oxygen lances
      bool InjLancesAligned   = ModelConfiguration->isProcessProfileAlignedFor(CMeasConsCodesEAF::MatFeedInGeneral);      // for C-Injectors and lances
      bool PatternFeedAligned = ModelConfiguration->isProcessProfileAlignedFor(CMeasConsCodesEAF::PatternFeed);           // for feeding pattern
      bool BotmStirrAligned   = ModelConfiguration->isProcessProfileAlignedFor(CMeasConsCodesEAF::BottomStirringDevice);  // for bottom stirring
      bool BurnerAligned      = ModelConfiguration->isProcessProfileAlignedFor(CMeasConsCodesEAF::Burner);                // for burner
 
      // tracing
      {
        std::stringstream msg;
        if (Old_Key != m_PrevSetpointsKey)
        {
          msg << "!! Old_Key != PrevSetpointsKey !! " << " Old_Key: "<< Old_Key << "|| PrevSetpointsKey: " << m_PrevSetpointsKey;
          log(msg.str(), 2);msg.str("");
        }
        msg << "PrevSetpointsKey: " << m_PrevSetpointsKey << "|| CurrentKey: " << m_Key;
        log(msg.str(), 2);msg.str("");
      }


      // get previous results for comparison
      // /////////////////////////////////////

      //reset previous setpoints on heat announcement
      if ( EAF_EvMsg::evEAFHeatAnnouncement == Event.getMessage() )
        m_PrevSetpointsKey.clear();

      seqEAFProcessPredRes* OldSeqPtr   = (m_PrevSetpointsKey.empty())? 0 : m_pModelResults->getEAFProcessPredRes(m_PrevSetpointsKey.c_str(), DATA::EAFProcessPredRes);


      if (OldSeqPtr == 0)
      {
        // save current key value for next cycle
        m_PrevSetpointsKey = m_Key;

        std::stringstream msg;
        msg << "!! OldSeqPtr is Null !!";
        log(msg.str(), 2);msg.str("");
      }
      else if ( CIntfData::getLength(*OldSeqPtr) <= 0 )                 // mrut 2013-11-13 Itst J-SW  : "what is this ?"
      {                                                                 // if previous sequence is empty, we should proceed.
        // save current key value for next cycle
        m_PrevSetpointsKey = m_Key;

        std::stringstream msg;
        msg << "!! Old Sequence is Empty !!";
        log(msg.str(), 2);msg.str("");
      }
      else
      {

        const seqEAFProcessPredRes &OldElecPredRes = *OldSeqPtr;

        long OldSeqLen = CIntfData::getLength(OldElecPredRes);
        long    SeqLen = CIntfData::getLength(   ElecPredRes);

        // both sequences are sorted here


        // declare a set of temporary containers
        seqEAFProcessPredRes  TmpElecPredRes;                   // mandatory electrical data


        seqEAFGasLancePredRes TmpOxygPredRes;                   // for oxygen - lances / gas lances
        seqEAFGasLancePredRes TmpBottomStirrPredRes;            // for bottom stirring
        seqEAFInjectLance     TmpInjctPredRes;                  // for injection lances / gas lances

        seqEAFBurnerPredRes   TmpBurnerPredRes;                 // for burner
        seqEAFMatFeedPredRes  TmpMatFeedPredRes;                // for feeding


        // declare a set of pointers for previous setpoints
        seqEAFGasLancePredRes* OldSeqPtr_Oxyg        = 0;
        seqEAFGasLancePredRes* OldSeqPtr_BottomStirr = 0;   
        seqEAFInjectLance*     OldSeqPtr_Injct   =     0;
        seqEAFBurnerPredRes*   OldSeqPtr_Burner  =     0;        
        seqEAFMatFeedPredRes*  OldSeqPtr_Feeding =     0;

 
         if ( !m_PrevSetpointsKey.empty() )
         {
           if ( GasLancesAligned)
           {
                OldSeqPtr_Oxyg = m_pModelResults->getEAFGasLancePredRes(m_PrevSetpointsKey.c_str(), DATA::EAFGasLancePredRes);
                if ( CIntfData::getLength(*OldSeqPtr_Oxyg) <= 0) 
                     OldSeqPtr_Oxyg =0;
           }
           if ( InjLancesAligned )
           {
                OldSeqPtr_Injct =  m_pModelResults->getEAFInjectLance    (m_PrevSetpointsKey.c_str(), DATA::EAFInjectLance);
                if ( CIntfData::getLength(*OldSeqPtr_Injct) <= 0) 
                     OldSeqPtr_Injct =0;
           }
           if ( BotmStirrAligned )
           {
                OldSeqPtr_BottomStirr = m_pModelResults->getEAFGasLancePredRes(m_PrevSetpointsKey.c_str(), DATA::EAFBottomStirrPredRes);
                if ( CIntfData::getLength(*OldSeqPtr_BottomStirr) <= 0) 
                     OldSeqPtr_BottomStirr =0;
           }

           if ( PatternFeedAligned )
           {
                OldSeqPtr_Feeding    =  m_pModelResults->getEAFMatFeedPredRes (m_PrevSetpointsKey.c_str(), DATA::EAFMatFeedPredRes);
                if ( CIntfData::getLength(*OldSeqPtr_Feeding) <= 0) 
                     OldSeqPtr_Feeding =0;
           }

           if ( BurnerAligned )
           {
                OldSeqPtr_Burner = m_pModelResults->getEAFBurnerPredRes  (m_PrevSetpointsKey.c_str(), DATA::EAFBurnerPredRes);
                 if ( CIntfData::getLength(*OldSeqPtr_Burner) <= 0) 
                     OldSeqPtr_Burner =0;
          }
         }
 


        // save current key value for next cycle
        m_PrevSetpointsKey = m_Key;

        //-------------------
        // logging + general
        //-------------------

        bool ChangedData = false;

        while (!ChangedData)
        {

          bool YetDone = false;   // allready done ?


          std::string  Phase_Ref;
	              long   BskNo_Ref      = 0;
                long   iStep_Ref      = 0;

          long iNew =0;
          while ( iNew < SeqLen )
          {
            std::string  Phase_New (ElecPredRes[iNew].Phase);

            if ( (Phase_Ref != Phase_New) ||
                 (BskNo_Ref != ElecPredRes[iNew].PhaseNo) )
            {
              iStep_Ref  = 0;
              Phase_Ref  = ElecPredRes[iNew].Phase;
              BskNo_Ref  = ElecPredRes[iNew].PhaseNo;
            }

            if (!YetDone) // do only once
            {
              YetDone = !YetDone;   // ! ;) !

              // any missing steps for allready finished process phases?
              // (several phases may-be, however, if one found, it is ok to set the flag)
              //////////////////////////////////////////////////////////////////////////////

              long iOld =0;
              std::string  Phase_Old  (OldElecPredRes[iOld].Phase);
              long         BskNo_Old = OldElecPredRes[iOld].PhaseNo;

              if ( (Phase_Ref != Phase_Old) ||    
                   (BskNo_Ref != BskNo_Old)    )  
              { 
                // we found that the new result sequence starts with an other proc. phase than the previous result 
                ChangedData = true;
              }
            }//end if (!YetDone)


            // steps from previous process phases checked now, next to check
            // steps for the current process phase.
            //////////////////////////////////////////////////////////////////////////////

            if ( ElecPredRes[iNew].Step > (++iStep_Ref) )
            {
              // the new result sequence does not start with step one,
              // or some other step is missing.
              ChangedData = true;
            }
            else
            {
              ++iNew;
            }

            if (ChangedData)
              break;

          }// end while



          if (ChangedData)
          {
            { // electric.tric
            std::stringstream msg;
            msg << "Old Sequence ElecPredRes[" << OldSeqLen<< "]";
            log(msg.str(), 2);msg.str("");
            for (long i = 0; i < OldSeqLen; ++i)
            {
              std::stringstream tmp;
              tmp << "Phase: " << OldElecPredRes[i].Phase << "[" << OldElecPredRes[i].PhaseNo << "]" << ", Step: " << OldElecPredRes[i].Step
                << "\n  DurUntilEndOfStep: " << OldElecPredRes[i].DurUntilEndOfStep
                << "\n            ElecEgy: " << OldElecPredRes[i].ElecEgy;
              log(tmp.str(), 2);
            }

            std::stringstream msg2;
            msg2 << "New Sequence ElecPredRes[" << SeqLen<< "]";
            log(msg2.str(), 2);msg2.str("");
            for (long i = 0; i < SeqLen; ++i)
            {
              std::stringstream tmp;
              tmp << "Phase: " << ElecPredRes[i].Phase << "[" << ElecPredRes[i].PhaseNo << "]" << ", Step: " << ElecPredRes[i].Step
                << "\n  DurUntilEndOfStep: " << ElecPredRes[i].DurUntilEndOfStep
                << "\n            ElecEgy: " << ElecPredRes[i].ElecEgy;
              log(tmp.str(), 2);
            }
          }

            if (OldSeqPtr_Feeding)
            {

              const seqEAFMatFeedPredRes &OldMatFeedPredRes = *OldSeqPtr_Feeding;

              long OldSeqLen = CIntfData::getLength(OldMatFeedPredRes);

              std::stringstream msg;
              msg << "Old Sequence MatFeedPredRes[" << OldSeqLen<< "]";
              log(msg.str(), 2);msg.str("");
              for (long i = 0; i < OldSeqLen; ++i)
              {
                std::stringstream tmp;
                tmp << "Phase: " << OldMatFeedPredRes[i].PhaseName << "[" << OldMatFeedPredRes[i].BasketNo << "]" << ", Step: " << OldMatFeedPredRes[i].Step
                  << "\n  DurUntilEndOfStep: " << OldMatFeedPredRes[i].DurUntilEndOfStep
                  << "\n            ElecEgy: " << OldMatFeedPredRes[i].Egy;
                log(tmp.str(), 2);
              }


              //MatFeedPredRes
              long NewSeqLen = CIntfData::getLength(MatFeedPredRes);

              std::stringstream msg2;
              msg2 << "New Sequence MatFeedPredRes[" << SeqLen<< "]";
              log(msg2.str(), 2);msg2.str("");
              for (long i = 0; i < SeqLen; ++i)
              {
                std::stringstream tmp;
                tmp << "Phase: " << MatFeedPredRes[i].PhaseName << "[" << MatFeedPredRes[i].BasketNo << "]" << ", Step: " << MatFeedPredRes[i].Step
                  << "\n  DurUntilEndOfStep: " << MatFeedPredRes[i].DurUntilEndOfStep
                  << "\n            ElecEgy: " << MatFeedPredRes[i].Egy;
                log(tmp.str(), 2);
              }
            }

          }

          break; // break anyway

        }// end while (!ChangedData)


        //-------------------
        // logging finished
        //-------------------

        bool YetDoneTakeOver = false;   // allready done ?
        bool YetDoneClipping = false;   // allready done ?


        bool ProfileFinished = (    (  SeqLen  == 0 )
                                 || (MPhaseTyp == CProcPhaseCodesEAF::Tapping)
                                 || (MPhaseTyp == CProcPhaseCodesEAF::AfterTapping) );


        //this will copy the complete previous result, when the new result is empty (process is finished).
        if (ProfileFinished )
        {
          TmpElecPredRes = OldElecPredRes;

          if (OldSeqPtr_Oxyg)
              TmpOxygPredRes          = *OldSeqPtr_Oxyg;            // for oxygen - lances / gas lances 

          if (OldSeqPtr_BottomStirr)
              TmpBottomStirrPredRes   = *OldSeqPtr_BottomStirr;     // for bottom stirring

          if (OldSeqPtr_Injct)
              TmpInjctPredRes         = *OldSeqPtr_Injct;           // for injection lances / gas lances

          if (OldSeqPtr_Burner)
              TmpBurnerPredRes        = *OldSeqPtr_Burner;          // for burner

          if (OldSeqPtr_Feeding)
              TmpMatFeedPredRes       = *OldSeqPtr_Feeding;         // for feeding
        }
        else
        {
          std::string  Phase_Ref;
	              long   BskNo_Ref      = 0;
                long   iStep_Ref      = 0;
                long   iPhase_Ref_cnt = 0;        // counts how often phase changes in result pattern

          long iNew =0;
          while ( iNew < SeqLen )
          {
            std::string  Phase_New (ElecPredRes[iNew].Phase);

            if ( (Phase_Ref != Phase_New) ||
                 (BskNo_Ref != ElecPredRes[iNew].PhaseNo) )
            {
              ++iPhase_Ref_cnt;   // new phase in result pattern

              iStep_Ref  = 0;
              Phase_Ref  = ElecPredRes[iNew].Phase;
              BskNo_Ref  = ElecPredRes[iNew].PhaseNo;
            }

            if (!YetDoneTakeOver) // do only once
            {
              YetDoneTakeOver = !YetDoneTakeOver;   // ;)

              // get missing steps for allready finished process phases from previous array.
              // (several phases may-be)
              //////////////////////////////////////////////////////////////////////////////
              long        ExpecStepNo       = 0;    // expected number of step within process phase
              long        ModelStepNo       = 0;
              double      ModelStepEgyAccum = 0.;
              std::string ModelDummyString;

              long iOld =0;
              std::string  Phase_Old  (OldElecPredRes[iOld].Phase);
              long         BskNo_Old = OldElecPredRes[iOld].PhaseNo;

              std::string ModelPhase__PriorToPhase_Ref (Phase_Ref);
              long        ModelPhaseNoPriorToBskNo_Ref (BskNo_Ref);

              long ModelFindsAPhaseToQuit = pIntfEAF->getKeyedInformation("getPrevProcPhase",iOld, 
                                            ModelPhase__PriorToPhase_Ref, ModelPhaseNoPriorToBskNo_Ref, 
                                            ModelStepEgyAccum);

              while( (Phase_Ref != Phase_Old) ||    // to be checked whether this loop should be "broken" when refining is reached
                     (BskNo_Ref != BskNo_Old)    )  // reason : there could be an additional basket in the new sequence but not in the old. Then the complete old sequence would get copied.
              {                                     // Also, a change of treatment-map during the process will cause severe trouble.
                                                    // To do: instead of comparison in while (..) you need dto check, whether Phase-old 
                                                    // has reached the phase in Treatment-map before the current ("actual") phase.
                // processing
                //-----------

                sEAFProcessPredRes      ElecStepRes (OldElecPredRes[iOld]);

                ++ExpecStepNo;

                // instead of clipping -implementation get step-egy from Modello
                long ModelReturns = pIntfEAF->getKeyedInformation("getPredStepElec",iOld, ModelDummyString, ModelStepNo, ModelStepEgyAccum);
                if ( ModelReturns == CRS::OK && ModelStepNo == ExpecStepNo )
                 {// the model recognizes this step as a valid one and uses the same step number within a process phase.
                  // means it is the same step in the model and here. However, step energy may has been clipped. 
                   if ( (ModelStepEgyAccum >= 0.0) && (ModelStepEgyAccum != ElecStepRes.ElecEgy) )
                    {
                        double Delta_Egy = ElecStepRes.ElecEgy - ModelStepEgyAccum;
                
                        ElecStepRes.ElecEgy     -= Delta_Egy;
                        ElecStepRes.ElecEgyStep -= Delta_Egy;
                            
                        if (ElecStepRes.BaseMass > 0)
                        {
                          ElecStepRes.SpecEgy     = ElecStepRes.ElecEgy    /ElecStepRes.BaseMass;
                          ElecStepRes.SpecEgyStep = ElecStepRes.ElecEgyStep/ElecStepRes.BaseMass;
                        }
                    }

                    CIntfData::insert(TmpElecPredRes, ElecStepRes);


                    if (OldSeqPtr_Oxyg   && (iOld < CIntfData::getLength((* OldSeqPtr_Oxyg))))
                    {
                      sEAFGasLancePredRes    OxygStepRes( (* OldSeqPtr_Oxyg)[iOld]);
                      CIntfData::insert  (TmpOxygPredRes, OxygStepRes);
                    }
                    if (OldSeqPtr_BottomStirr && (iOld < CIntfData::getLength((* OldSeqPtr_BottomStirr))))
                    {
                      sEAFGasLancePredRes   BottomStirrStepRes( (* OldSeqPtr_BottomStirr)[iOld]);
                      CIntfData::insert (TmpBottomStirrPredRes, BottomStirrStepRes);
                    }
                    if (OldSeqPtr_Injct   && (iOld < CIntfData::getLength((* OldSeqPtr_Injct))))
                    {
                      sEAFInjectLance       InjctStepRes( (* OldSeqPtr_Injct)[iOld]);
                      CIntfData::insert (TmpInjctPredRes, InjctStepRes);
                    }
                    if (OldSeqPtr_Burner  && (iOld < CIntfData::getLength((* OldSeqPtr_Burner))))
                    {
                      sEAFBurnerPredRes     BurnerStepRes( (* OldSeqPtr_Burner)[iOld]);
                      CIntfData::insert (TmpBurnerPredRes, BurnerStepRes);
                    }
                    if (OldSeqPtr_Feeding && (iOld < CIntfData::getLength((* OldSeqPtr_Feeding))))
                    {
                      sEAFMatFeedPredRes    MatFeedStepRes( (* OldSeqPtr_Feeding)[iOld]);
                      CIntfData::insert (TmpMatFeedPredRes, MatFeedStepRes);
                    }

                 } // if ( ModelReturns == CRS::OK && ModelStepNo == ExpecStepNo )

                if (++iOld == OldSeqLen)
                  break;

                if (    (Phase_Old != std::string(OldElecPredRes[iOld].Phase))         // recount steps with each new phase
                     || (BskNo_Old != OldElecPredRes[iOld].PhaseNo) )
                {                                                         // A new phase has come
                    ExpecStepNo     = 0;
                    if (    (ModelPhase__PriorToPhase_Ref == Phase_Old)   // it seems the passed process phases have been checked now.
                         && (ModelPhaseNoPriorToBskNo_Ref == BskNo_Old) ) // so:
                     break;                                               // break the while-loop and hopefully this catches also the case of treatment-map change.
                }

                Phase_Old = OldElecPredRes[iOld].Phase;
                BskNo_Old = OldElecPredRes[iOld].PhaseNo;

              } // end while
            }//end if (!YetDone)


            // steps from previous process phases should be ok now, 
            // next is to check steps for the current process phase.
            //////////////////////////////////////////////////////////////////////////////

            if ( ElecPredRes[iNew].Step > (++iStep_Ref) )
            {
              // index iNew will not be incremented in this case
                // get missing step from previous array
                long iOld =0;
                for (; iOld < OldSeqLen; ++iOld)
                {
                  std::string  Phase_Old (OldElecPredRes[iOld].Phase);
                  if ( (Phase_Ref == Phase_Old)                     &&
                       (BskNo_Ref == OldElecPredRes[iOld].PhaseNo) &&
                       (iStep_Ref == OldElecPredRes[iOld].Step)        )
                  {
                    sEAFProcessPredRes   ElecStepRes (OldElecPredRes[iOld]);
                    CIntfData::insert(TmpElecPredRes, ElecStepRes);
            

                    if (OldSeqPtr_Oxyg   && (iOld < CIntfData::getLength((* OldSeqPtr_Oxyg))))
                    {
                      sEAFGasLancePredRes    OxygStepRes( (* OldSeqPtr_Oxyg)[iOld]);
                      CIntfData::insert  (TmpOxygPredRes, OxygStepRes);
                    }
                    if (OldSeqPtr_BottomStirr && (iOld < CIntfData::getLength((* OldSeqPtr_BottomStirr))))
                    {
                      sEAFGasLancePredRes   BottomStirrStepRes( (* OldSeqPtr_BottomStirr)[iOld]);
                      CIntfData::insert (TmpBottomStirrPredRes, BottomStirrStepRes);
                    }
                    if (OldSeqPtr_Injct   && (iOld < CIntfData::getLength((* OldSeqPtr_Injct))))
                    {
                      sEAFInjectLance       InjctStepRes( (* OldSeqPtr_Injct)[iOld]);
                      CIntfData::insert (TmpInjctPredRes, InjctStepRes);
                    }
                    if (OldSeqPtr_Burner  && (iOld < CIntfData::getLength((* OldSeqPtr_Burner))))
                    {
                      sEAFBurnerPredRes     BurnerStepRes( (* OldSeqPtr_Burner)[iOld]);
                      CIntfData::insert (TmpBurnerPredRes, BurnerStepRes);
                    }
                    if (OldSeqPtr_Feeding && (iOld < CIntfData::getLength((* OldSeqPtr_Feeding))))
                    {
                      sEAFMatFeedPredRes    MatFeedStepRes( (* OldSeqPtr_Feeding)[iOld]);
                      CIntfData::insert (TmpMatFeedPredRes, MatFeedStepRes);
                    }

                    break;
                  }
                }
            }
            else
            {
              // insert step right away

              sEAFProcessPredRes   ElecStepRes (ElecPredRes[iNew]);
              CIntfData::insert(TmpElecPredRes, ElecStepRes);


              if (GasLancesAligned && (iNew < CIntfData::getLength(GasLancePredRes)) )
              {
                sEAFGasLancePredRes   OxygStepRes (GasLancePredRes[iNew]);
                CIntfData::insert (TmpOxygPredRes, OxygStepRes);
              }

              if (BotmStirrAligned && (iNew < CIntfData::getLength(BottomStirrPredRes)) )
              {
                sEAFGasLancePredRes   BottomStirrStepRes (BottomStirrPredRes[iNew]);
                CIntfData::insert (TmpBottomStirrPredRes, BottomStirrStepRes);
              }

              if (InjLancesAligned && iNew < CIntfData::getLength(InjctPredRes))
              {
                sEAFInjectLance       InjctStepRes( InjctPredRes[iNew]);
                CIntfData::insert (TmpInjctPredRes, InjctStepRes);
              }

              if (BurnerAligned && iNew < CIntfData::getLength(BurnerPredRes))
              {
                sEAFBurnerPredRes     BurnerStepRes( BurnerPredRes[iNew]);
                CIntfData::insert (TmpBurnerPredRes, BurnerStepRes);
              }


             if (PatternFeedAligned && iNew < CIntfData::getLength(MatFeedPredRes))
              {
                sEAFMatFeedPredRes    MatFeedStepRes (MatFeedPredRes[iNew]);
                CIntfData::insert (TmpMatFeedPredRes, MatFeedStepRes);
              }

              ++iNew;
            }

          }// end while

        } // end if else (ProfileFinished )

        // fill target container (sequence) //
        //////////////////////////////////////

        ElecPredRes     = TmpElecPredRes;

        if (GasLancesAligned)
            GasLancePredRes = TmpOxygPredRes;

        if (BotmStirrAligned)
            BottomStirrPredRes = TmpBottomStirrPredRes;
 
        if (InjLancesAligned)
            InjctPredRes    = TmpInjctPredRes;

        if (BurnerAligned)
           BurnerPredRes = TmpBurnerPredRes;
 
        if (PatternFeedAligned)
            MatFeedPredRes  = TmpMatFeedPredRes;

      }

      // //////////////////////////////////// //
      // //////////////////////////////////// //
      // << compare with previous result !!   //
      // //////////////////////////////////// //
      // //////////////////////////////////// //

      //
      // Iterate over the sequences and calculate values like:
      // DurUntilStartOfStep, DurStep,....
      
      double CumulatedStepEgy = 0;                     // mrut, 2013-11-11, Itst J-SW: vok, no energy in preparation, right? .. or left??
      double CumulatedStepDur = DurationOfPrepPhase;

      // flag to take care not modify old steps, this could destroy data of baskets bef. the previous 
      // e.g. act =3 destroyed = 1.
      bool   StepProcessingOn = false;

      long   SeqLen = CIntfData::getLength(ElecPredRes);

      std::stringstream msg;
      msg << "Result Sequence ElecPredRes[" << SeqLen<< "]" << "Dur_Ref: " << Dur_Ref << " Egy_Ref: " << Egy_Ref << "IsCharged: " << IsCharged;
      log(msg.str(), 2);msg.str("");
      for (long i = 0; i < SeqLen; ++i)
      {
          std::string StepPhase (ElecPredRes[i].Phase);

          bool ActPhase = (!IsCharged) ?
                (      (StepPhase == MPhaseTyp) && (ElecPredRes[i].PhaseNo ==MPhaseNo)   )  :    // StepPhase == "ActPhase"
                (    ( (StepPhase == MPhaseTyp) && (ElecPredRes[i].PhaseNo ==MPhaseNo+1) )       // StepPhase == "next basket" or
                  || ( (StepPhase == "LiquidCharge")    && (!StepProcessingOn) )                 // "Liquid charge", if no "next basket" found.
                  || ( (StepPhase == "BskAndLiqChgNo:") && (!StepProcessingOn) )                 // "Liquid charge", if no "next basket" found.
                  || ( (StepPhase == "HeatLiqChgNo:")   && (!StepProcessingOn) )                 // "Liquid charge", if no "next basket" found.
                );


          if (ActPhase && ElecPredRes[i].Step == 1)
          {
            StepProcessingOn = true;
            CumulatedStepDur = Dur_Ref;

            // take care of graphics
            // there is a slight time-gap, so we close it better to avoid black-holes.
            if ( (CProcPhaseCodesEAF::Refining == StepPhase) && (i>0) )
            {
             // mrut 2011-02-03
             // try to solve a problem concerning wrong times and missing step-energies
             // check for a 'gap' only insofar, as there may be a gap between the previous end-time
             // and the current start-time due to delays in production.
             // CumulatedStepDur = ElecPredRes[i-1].DurUntilStartOfStep;
             //
             if (CumulatedStepDur > ElecPredRes[i-1].DurUntilEndOfStep)   // you might consider an additional tolerance..
               // there should not be a delay between end of prev. phase and refining start. 
               CumulatedStepDur = ElecPredRes[i-1].DurUntilEndOfStep;
            }

            CumulatedStepEgy = Egy_Ref;
          }
          else if (CProcPhaseCodesEAF::Preparation == MPhaseTyp)
            StepProcessingOn = true;

          if (StepProcessingOn)
          {
			 
		        // ++ JIRA FUXINTWO-771 :Prediction of electrical step duration for first step is extended by basket charing time 
			      if ( (ElecPredRes[i].Step   ==  1) &&             // first step of phase
                 (ElecPredRes[i].PhaseNo  > 1)    )           // but not for first phase (after preparation)
			      {
              CEAFModelTask* pTask = dynamic_cast <CEAFModelTask*>(m_pModelTask);
              if (pTask) 
	            {
	              CParamMgr* pParamMgr = pTask->getpParamMgr();
		            if (pParamMgr) 
		            {
		              double AvgChargingDur  = pParamMgr->getDouble("AvgChargingDurPerPhase", StepPhase);
			            if  (  AvgChargingDur != CInv::InvalidDouble)
                  {
                       CumulatedStepDur  = max (0.0, CumulatedStepDur - AvgChargingDur);  // reduce duration of step by charging duration
                  }
                }
              }
            }

            // mrut, 2013-11-11, Itst J-SW: unbelieveable, incredible, incroyable, incredibile !
            //
            //ElecPredRes[i].DurUntilStartOfStep = CumulatedStepDur;
            //ElecPredRes[i].DurStep = max(0.,ElecPredRes[i].DurUntilEndOfStep - CumulatedStepDur);
            //CumulatedStepDur += ElecPredRes[i].DurStep;

            //ElecPredRes[i].ElecEgyStep = ElecPredRes[i].ElecEgy - CumulatedStepEgy;

            //CumulatedStepEgy = ElecPredRes[i].ElecEgy;

            ElecPredRes[i].DurUntilStartOfStep = CumulatedStepDur;
            ElecPredRes[i].DurStep     = max(0.,ElecPredRes[i].DurUntilEndOfStep - CumulatedStepDur);                 // dur. is set to zero if we are beyond, means step was skipped somehow
            CumulatedStepDur          += ElecPredRes[i].DurStep;
         
            ElecPredRes[i].ElecEgyStep = max (ElecPredRes[i].ElecEgyStep, ElecPredRes[i].ElecEgy - CumulatedStepEgy); // step egy. is not modified if we are beyond, means step was skipped somehow
                      CumulatedStepEgy = max (ElecPredRes[i].ElecEgy, CumulatedStepEgy); 


            if (ElecPredRes[i].BaseMass > 0)
            {
              ElecPredRes[i].SpecEgy     = ElecPredRes[i].ElecEgy/ElecPredRes[i].BaseMass;
              ElecPredRes[i].SpecEgyStep = ElecPredRes[i].ElecEgyStep/ElecPredRes[i].BaseMass;
            }
          }

        std::stringstream tmp;
        tmp << "Phase: " << ElecPredRes[i].Phase << "[" << ElecPredRes[i].PhaseNo << "]" << ", Step: " << ElecPredRes[i].Step
          << "\n   DurUntilEndOfStep: " << ElecPredRes[i].DurUntilEndOfStep
          << "\n             DurStep: " << ElecPredRes[i].DurStep
          << "\n DurUntilStartOfStep: " << ElecPredRes[i].DurUntilStartOfStep
          << "\n             ElecEgy: " << ElecPredRes[i].ElecEgy
          << "\n         ElecEgyStep: " << ElecPredRes[i].ElecEgyStep
          << "\n             SpecEgy: " << ElecPredRes[i].SpecEgy
          << "\n         SpecEgyStep: " << ElecPredRes[i].SpecEgyStep;
        log(tmp.str(), 2);
      }


      // horrible: due to different declarations of sematically identical item, three methods have to be used ... 1 for feeding,  2&3 for others ...
      if (PatternFeedAligned)
          alignResultPattern_1 (ElecPredRes, true,   "MatFeedPredRes", Dur_Ref, Egy_Ref, MatFeedPredRes);

      if (GasLancesAligned)
          alignResultPattern_2 (ElecPredRes, false, "GasLancePredRes", Dur_Ref, Egy_Ref, GasLancePredRes);

      if (BotmStirrAligned)
          alignResultPattern_2 (ElecPredRes, false, "BottomStirrPredRes", Dur_Ref, Egy_Ref, BottomStirrPredRes);
 
      if (BurnerAligned)
          alignResultPattern_2 (ElecPredRes, false, "BurnerPredRes", Dur_Ref, Egy_Ref, BurnerPredRes);

      if (InjLancesAligned)
          alignResultPattern_3 (ElecPredRes, false, "InjctPredRes", Dur_Ref, Egy_Ref, InjctPredRes);

 


      } // electrical steps
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //                electrical steps preparation finished here
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //Electric energy block end



    //we may need some code to calculate some accumulated values of the patterns.
    RetValue = calculateInjectionAmounts(InjctPredRes);


    // mrut 2014-02-06, work on JIRA SMPJSWTWO-47, SMPJSWTWO-55 : determination of material amount for feeding
    RetValue = calculateMatFeedingPatternAmounts( MatFeedPredRes, CurrentlyActiveStepMatFeed );

 
    RetValue = true;        // oh, i see: it's true, brother.

    ///////////////////////////////////////////////////////
    // write prediction results into CORBA interface
    ///////////////////////////////////////////////////////
    m_pModelResults->setPredRes(m_Key.c_str(), DATA::EAFPredRes, PredRes);
    m_pModelResults->setLong(m_Key.c_str(), DATA::EAFPredResLength, PredRes.length());
   
    std::string Message = Event.getMessage();
    //if ( EAF_EvMsg::evEAFHeatAnnouncement == Message )
    //{
    m_pModelResults->setEAFProcessPredRes(m_Key.c_str(), DATA::EAFProcessPredRes, ElecPredRes); 
    m_pModelResults->setLong(m_Key.c_str(), DATA::EAFElecPredResLength, ElecPredRes.length());   
    //}

 
    if ( isModelDevice(CCtrlSystemCodesEAF::ManipGasLance) )              //does model support gas lances?
    {
      m_pModelResults->setEAFGasLancePredRes(m_Key.c_str(), DATA::EAFGasLancePredRes, GasLancePredRes); 
      m_pModelResults->setLong(m_Key.c_str(), DATA::EAFGasLancePredResLength, GasLancePredRes.length()); 
    }

    if ( isModelDevice(CCtrlSystemCodesEAF::ManipInjectLance) )           //does model support injection lances?
    {
      m_pModelResults->setEAFInjectLance(m_Key.c_str(), DATA::EAFInjectLance, InjctPredRes);      
      m_pModelResults->setLong(m_Key.c_str(), DATA::EAFInjectLanceLength, InjctPredRes.length());
    }

    if ( isModelDevice(CCtrlSystemCodesEAF::BottomStirringDevice) )       //does model support bottom stirring?
    {
      m_pModelResults->setEAFGasLancePredRes(m_Key.c_str(), DATA::EAFBottomStirrPredRes, BottomStirrPredRes); 
      m_pModelResults->setLong(m_Key.c_str(), DATA::EAFBottomStirrPredResLength, BottomStirrPredRes.length()); 
    }

   if ( isModelDevice(CCtrlSystemCodesEAF::Burner) )                      //does model support burners?
   {
      m_pModelResults->setEAFBurnerPredRes(m_Key.c_str(), DATA::EAFBurnerPredRes, BurnerPredRes);         
      m_pModelResults->setLong(m_Key.c_str(), DATA::EAFBurnerPredResLength, BurnerPredRes.length());
   }
   // what about oxgen side-lances?
   // what about jet modules?


   // feeding ...
   //
    //SANKAR: as per Darko
    //std::string Message = Event.getMessage();
    //if ( EAF_EvMsg::evEAFHeatAnnouncement == Message )
    //{
     const CCfgEAF * pCfgEAF =  getpCfgEAF();
     const map<string, long> & CtrlSystemMap = pCfgEAF->getCtrlSystemSetptTyp();      
           map<string, long>::const_iterator   CtrlSystemItEnd (CtrlSystemMap.end());

      //does model support pattern feeding?
      if (CtrlSystemMap.find (CCtrlSystemCodesEAF::BinMatPatternFeed) != CtrlSystemItEnd)
      {
        m_pModelResults->setEAFMatFeedPredRes(m_Key.c_str(), DATA::EAFMatFeedPredRes, MatFeedPredRes);
        m_pModelResults->setLong(m_Key.c_str(), DATA::EAFMatFeedPredResLength, MatFeedPredRes.length());
      }

    //}

    // ******************************
    //    actual setpoint handling
    // ******************************

    long VoltTap  = 0;
    long RegCurve = 0;
    long ReactTap = 0;
    pIntfEAF->getElArcSetptAct(ReactTap,VoltTap,RegCurve);    

    m_pModelResults->setLong(m_Key.c_str(), DATA::ReactTapNoAim,ReactTap);
    m_pModelResults->setLong(m_Key.c_str(), DATA::VoltTapNoAim,VoltTap);
    m_pModelResults->setLong(m_Key.c_str(), DATA::ElectrodRegCurveAim,RegCurve);

    long ActSetptPullEltrd = pIntfEAF->getActSetptPullEltrd(); 
    long ElecLockReq       = pIntfEAF->isElecLockReq();
    m_pModelResults->setLong(m_Key.c_str(), DATA::ElecPullReq, ActSetptPullEltrd);      
    m_pModelResults->setLong(m_Key.c_str(), DATA::ElecInhibitReq,ElecLockReq);
    //m_pModelResults->setLong(m_Key.c_str(), DATA::??, pIntfEAF->isActBskDataReq());

    std::stringstream ssMsg;
    ssMsg << "ActSetpoint ReactTap" << ReactTap << " VoltTap: "<< VoltTap << " , RegCurve:" << RegCurve << " , ActSetptPullEltrd:" << ActSetptPullEltrd << " , ElecLockReq:" << ElecLockReq;
    log(ssMsg.str(),2);

    log("showContent ActualModelOutput", 4);
    m_pModelResults->showContent(m_Key.c_str(),4);

    long DeviceNo   = 0;
    double gasFlow  = 0;
    double O2Flow   = 0;
    double InjValue = 0;

    std::string gasType,InjType;
    seqGasLanceData seqGLD;

    seqGasLanceData seqDataBurner;

    //burner 
    #if defined (EAF_BURNER)

    const CCfgEAF * pModelConfiguration =  getpCfgEAF();

    //------------------------------------------------------------------------------------------ BurnerAct

    long HowManyBurners = 0;
          pModelConfiguration->getNoOfCtrlDevices(CCtrlSystemCodesEAF::Burner,HowManyBurners);

    long       burnerNo  = 0;
    while ( (++burnerNo <= HowManyBurners) && CRS::OK == pIntfEAF->getActSetptBurner(burnerNo,gasFlow,O2Flow))
    {
      // mrut 2010-05-31: Step ++;
      seqGasData seqGD;
      sGasData sGData;

      sGData.GasType = DEF_GCE_BURNER_GASTYPE::O2.c_str();
      sGData.GasValue = O2Flow;
      CIntfData::insert(seqGD,sGData);

      sGData.GasType = DEF_GCE_BURNER_GASTYPE::BG.c_str();
      sGData.GasValue = gasFlow;
      CIntfData::insert(seqGD,sGData);

      sGasLanceData  sData;
      sData.LanceData = seqGD;

      std::string BurnerName = m_pGCE_BURNER->getBurnerNameByPlant(ActPlant,ActPlantNo,burnerNo);

      if ( BurnerName != CSMC_DBData::unspecString )
      {
        sData.Device = BurnerName.c_str();
      }
        
      CIntfData::insert(seqDataBurner,sData);
      //m_pModelResults->setLong(m_Key.c_str(), DATA::??,pIntfEAF->isBurnerLockReq(burnerNo));

      std::stringstream ssMsg;
      ssMsg << "getActSetptBurner()-> BurnerName: "<< BurnerName << " , GasFlow:" << gasFlow*60  << " , O2Flow:" << O2Flow*60 ;
      log(ssMsg.str(),2);

      gasFlow = 0.;
      O2Flow = 0.;
    }

    //------------------------------------------------------------------------------------------ BurnerAct

    //------------------------------------------------------------------------------------------ SideLanceAct

    long HowManySideLance =0;
    long SideLanceNo   = 0;

    pModelConfiguration->getNoOfCtrlDevices(CCtrlSystemCodesEAF::OxygenLance,HowManySideLance);

    while ( (++SideLanceNo <= HowManySideLance) && CRS::OK == pIntfEAF->getActSetptOxySideLance(SideLanceNo, gasFlow, O2Flow))
    {
      seqGasData seqGD;
      sGasData sGData;

      sGData.GasType = DEF_GCE_BURNER_GASTYPE::O2.c_str();
      sGData.GasValue = O2Flow*60;
      CIntfData::insert(seqGD,sGData);

      sGData.GasType = DEF_GCE_BURNER_GASTYPE::BG.c_str();
      sGData.GasValue = gasFlow*60;
      CIntfData::insert(seqGD,sGData);

      sGasLanceData  sData;
      sData.LanceData = seqGD;

      std::string BurnerName = m_pGCE_BURNER->getBurnerNameByPlant(ActPlant,ActPlantNo,SideLanceNo);

      if ( BurnerName != CSMC_DBData::unspecString )
      {
        sData.Device = BurnerName.c_str();
      }
        
      CIntfData::insert(seqDataBurner,sData);
      //m_pModelResults->setLong(m_Key.c_str(), DATA::??,pIntfEAF->isBurnerLockReq(burnerNo));

      std::stringstream ssMsg;
      ssMsg << "getActSetptOxySideLance(" << SideLanceNo << ")-> BurnerName: "<< BurnerName << " , GasFlow:" << gasFlow*60  << " , O2Flow:" << O2Flow*60 ;
      log(ssMsg.str(),2);

      gasFlow = 0.;
      O2Flow = 0.;
    }// while ( (++SideLanceNo <= HowManySideLance) && CRS::OK == pIntfEAF->getActSetptOxySideLance(SideLanceNo, gasFlow, O2Flow))

    //------------------------------------------------------------------------------------------ SideLanceAct

    m_pModelResults->setGasLanceData(m_Key.c_str(), DATA::EAFBurnerAmount ,seqDataBurner);
    #endif

    //(not necessarily manipulator)- gas lances
    #if defined (EAF_GAS_LANCES)
      seqGasLanceData seqDataLance;

      DeviceNo = 0;
      while (++DeviceNo  && CRS::OK == pIntfEAF->getActSetptManipGasLance(DeviceNo,gasType,gasFlow))
      {
        std::string DeviceName;

        if ( m_pGCE_INJECTION )
        {
          DeviceName = m_pGCE_INJECTION->getDeviceNameByL1InjectorNo(ActPlant, ActPlantNo, DeviceNo, DEF_GCE_INJECTION_TYPE::OxygenInjection);
        }
        seqGasData seqGD;
        sGasData sGData;

        sGData.GasType  = gasType.c_str();
        sGData.GasValue = gasFlow;          // Nm3/min --> Nm3/h wiil be done in DH_OUT
        CIntfData::insert(seqGD,sGData);

        sGasLanceData  sData;
        sData.LanceData = seqGD;
        sData.Device    = DeviceName.c_str();
        CIntfData::insert(seqDataLance,sData);

        std::stringstream ssMsg;
        ssMsg << "getActSetptManipGasLance(" << DeviceNo << ")-> DeviceName: "<< DeviceName << " , GasFlow:" << gasFlow;
        log(ssMsg.str(),2);
      }

      m_pModelResults->setGasLanceData(m_Key.c_str(), DATA::EAFGasLanceAmount ,seqDataLance);

      //m_pModelResults->setLong(m_Key.c_str(), DATA::??,pIntfEAF->isManipGasLanceLockReq(DeviceNo));
    #endif

    #if defined (EAF_INJECTION_LANCES) 

          seqInjectLanceData seqInj;

          if ( m_pGCE_INJECTION_TYPE->select(CSMC_DBData::unspecString) )
          {
            std::stringstream ssMsg;
            for ( long row = 1; row <= m_pGCE_INJECTION_TYPE->getLastRow(); ++row )
            {
              std::string RelatedPurpCode = m_pGCE_INJECTION_TYPE->getPURP_CODE_1(row);

              if ( CRS::OK == pIntfEAF->getActSetptManipInjectLance(RelatedPurpCode,InjValue))
              {
                sInjectLanceData sInj;
                // mrut 2012-10-22
                // sInj.InjectionType = RelatedPurpCode.c_str();
                sInj.InjectionType = m_pGCE_INJECTION_TYPE->getINJTYPE(row).c_str();
                sInj.Value = InjValue;

                CIntfData::insert(seqInj, sInj);

                ssMsg << "getActSetptManipInjectLance("<< RelatedPurpCode << ")-> Value:" << InjValue << std::endl;        
                //m_pModelResults->setLong(m_Key.c_str(), DATA::BurnerStatus,pIntfEAF->isManipInjectLanceLockReq(??));
              }
              else
              {
                ssMsg << "getActSetptManipInjectLance("<< RelatedPurpCode << ")-> not available" << std::endl;
              }

              log(ssMsg.str(),2);
            }      
          }// if ( m_pGCE_INJECTION_TYPE->select(CSMC_DBData::unspecString) )

          m_pModelResults->setInjectLanceData(m_Key.c_str(), DATA::EAFInjectLanceAmount, seqInj);
    #endif

    #if defined (EAF_PATTERN_FEEDING) || defined (EAF_DYNAMIC_FEEDING)
    {
 
     std::stringstream ssMsg;
     seqBatch     seqb;

      std::string MatCode;
      double MatRate = 0.;
      double MatMass  = 0.;

      // mrut 2013-09-10
      // work on JSPLANG-241 : Transformation of the relative feeding rate to be done within the EAF model 
      //         Problem     : The model does not consider the current electrical power for the 'actual' feeding rate setpoint.
      //                       Instead, it uses the power value from the practice data also for the actual setpoints.
      //                       To simplify the code, the interface cannot be changed easily, this would affect other classes.
      //                       from     pIntfEAF->getActSetptMatFeed (MatCode, MatRate, MatMass)
      //                       to       pIntfEAF->getActSetptMatFeed (MatCode, MatRate, MatSpecRate, MatMass).
      //         Problem     : The model does not return a mass setpoint for 'pattern-feeding'. MatMass is zero always for pattern feeding.
      //                        no longer since 2014-02-10; lbl JSPL 201
      //
      // work on JSPLANG-241 / 242 / 243
            //// mrut 2014-02-18 next functionality removed from wrapper, functionality should be in model right now.
            //// The impact of the blowing rate will be defined as a rule: If all burners are working according to the O2 flow rate set-up, there will be no correction. 
            //// If the O2 flow rate is less than set-up or some of the burners are out of operation, the feeding rate will be decreased accordingly. 
            //// The factor will be valid for the whole O2 blowing system depending on the steel grade. 
            //// FR_reduced = FR_practice * ( 1 - DELTA_POWER_O2 / (ELEC_POWER + AIM_O2_POWER))
  


      long      MatFeedStep  = 0; 
      while ( ++MatFeedStep <= 20 && CRS::OK == pIntfEAF->getActSetptMatFeed (MatCode, MatRate, MatMass) )
      {    
        sBatch   sbp;
        sbp.MatCode = MatCode.c_str();
        sbp.MatFeedSpeed = MatRate;        // feeding rate, based on predicted /now current  -electrical power.
        sbp.FeedingRateRel2Energy = 0.;    // feeding rate, but based on current (not predicted) electrical power. // set o. because it is spare as per DARKO

        sbp.Mass = 0.;
        if ( MatMass > 0 )
            sbp.Mass = MatMass;



        ssMsg << "Model FeedingRate(Rel) "   << MatRate    << std::endl;
        ssMsg << "Model Mass  "              << MatMass    << std::endl;         // in current model version it is zero; mrut :  no longer since JSPL 201
  
        ssMsg << "getActSetptMatFeed("<< MatCode << ")-> Mass " << sbp.Mass << " MatFeedSpeed " << sbp.MatFeedSpeed << std::endl;
  
        CIntfData::insert(seqb, sbp);    
      } 

      m_pModelResults->setBatch(m_Key.c_str(), DATA::RecipeContent ,seqb);
      log(ssMsg.str(),3);
    }
    #endif
  
    #if defined (EAF_BOTTOM_STIRRING)
    double gasValue;
    if ( CRS::OK == pIntfEAF->getActSetptBottomStirring(gasType,gasValue) )
    {
      m_pModelResults->setString(m_Key.c_str(), DATA::EAFActSetPointStirrGasType,gasType);
      m_pModelResults->setDouble(m_Key.c_str(), DATA::EAFActSetPointStirrFlow,gasValue);
    }                  
    #endif

    //Aim weight
    if (m_pPP_ORDER_SINGLE_AIMS->select(Event.getOrderID(),ActPlant, 1,DEF_GC_PP_ORDER_SINGLE_AIMS::AIMSTEEL)) 
    {
      double aimSteelWeight = CSMC_DBData::unspecDouble;
      std::stringstream ss;
      ss << m_pPP_ORDER_SINGLE_AIMS->getVALUE(1); ss >> aimSteelWeight;
      if(aimSteelWeight != DEF::Inv_Double)
      {
        m_pModelResults->setDouble(m_Key.c_str(), DATA::AimWeight ,aimSteelWeight);
      }
    }

    
    double oxySetpoint = pIntfEAF->getActSetptOxyAmount();          // rappel !
    if(oxySetpoint != DEF::Inv_Double)
    {
      m_pModelResults->setDouble(m_Key.c_str(), DATA::RemO2Lance, pIntfEAF->getActSetptOxyAmount());
    }



    RetValue = true;

    seqComputerModes SeqComputerModes  = CIntfData::ToCORBAType(m_pModelResults->getComputerModes(m_Key.c_str(), DATA::ComputerModeAvail));

    if ( PredRes.length() > 0 || ElecPredRes.length() > 0 )
    {
      log("***********************************************************",3);
      log("****** New setpoints from EAF-Model were calculated *******",3);
      log("***********************************************************",3);
      m_pModelResults->showContent(m_Key.c_str(),4);

      RetValue = writeActualSetpointsToDB(Event, 
                                          PredRes, 
                                          ElecPredRes, 
                                          GasLancePredRes,
                                          InjctPredRes, 
                                          SeqComputerModes, 
                                          BurnerPredRes, 
                                          MatFeedPredRes, 
                                          BottomStirrPredRes, 
                                          seqDataBurner, 
                                          seqInj);
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
  }     
  catch (cCBS_DBExc &e)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Scope.c_str(), ExceptionMsg.str().c_str());

    CEAFModelWrapper::handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, sExc._name(), Scope.c_str(), ExceptionMsg.str().c_str());    
  }
  catch(std::exception & e)
  {
    RetValue = false;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, e.what(), Scope.c_str(), ExceptionMsg.str().c_str()); 
  }
  catch(...)
  {
    RetValue = false;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", Scope.c_str(), std::string("Unknown exception").c_str());    
  }

  return RetValue;
}

//##ModelId=45EBDA4001E1
bool CEAFModelResultWrapper::getModelResultsAtStatus( const std::string& HeatID, const std::string& TreatID, const std::string& Plant, 
                                                      const std::string&  Phase, 
                                                      long                PhaseNo, 
                                                      seqPredRes&         SeqPredRes)
{
  bool RetValue = true;
  std::string Scope = "CEAFModelResultWrapper::getModelResultsAtStatus()";

  sPredRes strPredRes;
  CIntfEAF *pIntfEAF = getpModelIntf();

  try
  {  
    strPredRes.Phase   = Phase.c_str();
    strPredRes.PhaseNo = PhaseNo;

    if ( isActualProcessPhase(Phase,PhaseNo) )
    {
      strPredRes.PhaseActive = 1;
    }
    else
    {
      strPredRes.PhaseActive = 0;
    }


    double steelweight = pIntfEAF->getSteelMassAtStatus();
    double slagweight  = pIntfEAF->getSlagMassAtStatus();
    double temp        = pIntfEAF->getTempAtStatus();
    //double durphase    = pIntfEAF->getElapsedTimeUntilStatus();

    strPredRes.GenRes.SteelWeight = setToRange(steelweight, 0, 0);
    strPredRes.GenRes.SlagWeight  = setToRange(slagweight, 0, 0);
    strPredRes.GenRes.Temp        = setToRange(temp, 0, 0);  
    //strPredRes.GenRes.DurPhase    = setToRange(durphase, 0, 0);

    if ((strPredRes.GenRes.Temp == 0) && (strPredRes.GenRes.DurPhase == 0)) 
    {
      return RetValue;
    }
   
    //if ( DEF_GC_PHASE::Actual == Phase)
    //  strPredRes.GenRes.MetTimeStamp.DurSinceHeatAnnouncement = durphase;
    //else
    //  strPredRes.GenRes.MetTimeStamp.DurSinceHeatAnnouncement = setToRange(pIntfEAF->getElapsedTimeUntilEndOfProcPhase(), 0, 0);

    strPredRes.GenRes.DurPhase    = setToRange(pIntfEAF->getDurOfStatus());
    strPredRes.GenRes.MetTimeStamp.DurSinceHeatAnnouncement = setToRange(pIntfEAF->getElapsedTimeUntilStatus(), 0, 0);

    strPredRes.GenRes.MetTimeStamp.O2_Moment   = 0;
    strPredRes.GenRes.MetTimeStamp.Ar_Moment   = 0;
    strPredRes.GenRes.MetTimeStamp.N2_Moment   = 0;
    strPredRes.GenRes.MetTimeStamp.Elec_Moment = 0;             

    sAnalysis   strAnalysis;
    seqAnalysis SeqAnalysis;    
    std::string Name;
    double      Content;

    while (pIntfEAF->getAnlAtStatus(Name, Content) == CRS::OK)
    {
      strAnalysis.Element       = Name.c_str();
      strAnalysis.Concentration = setToRange(Content,0,0);      
      CIntfData::insert(SeqAnalysis, strAnalysis);
    }

    handleEquivalences(HeatID, TreatID, Plant, SeqAnalysis);

    // Fuxin-merge. to be activated & checked?? +
    //adaptCalcAnalysis(HeatID, TreatID, Plant, SeqAnalysis);
    // Fuxin-merge. to be activated & checked?? -

    strPredRes.GenRes.Analysis = SeqAnalysis;
    CIntfData::insert(SeqPredRes,strPredRes);

    if ( DEF_GC_PHASE::Actual == Phase)
    {
      m_pModelResults->setDouble(m_Key.c_str(), DATA::TempAct, strPredRes.GenRes.Temp);
    }

  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", Scope.c_str(), ""  );    
  }
  
  return RetValue;
}

//##ModelId=45EBDA400203
void CEAFModelResultWrapper::getPredCalcResults( const std::string& Plant, long PlantNo, const std::string& Phase, long BasketNo,seqEAFBurnerPredRes& BurnerPredRes, double BaseMass )
{

  const CCfgEAF * pModelConfiguration =  getpCfgEAF();

  ////////////////////////////////////////////////////////////////////
  //                      get burner pattern
  ////////////////////////////////////////////////////////////////////
  #if defined (EAF_BURNER)
    std::string Scope = "CEAFModelResultWrapper::getPredCalcResults()" ;


    long HowManyBurners =0;
    pModelConfiguration->getNoOfCtrlDevices(CCtrlSystemCodesEAF::Burner,HowManyBurners);

    CIntfEAF *pIntfEAF = getpModelIntf();

    if (!pIntfEAF || !checkDBConnection()) 
    {
      log("Error " + Scope + " , (pIntfEAF || checkDBConnection()) == false", 1);
      return ;
    }

    std::stringstream strMsg;
    try
    {
      long ret = pIntfEAF->focusOnBurnerData();
      
      if (ret != CRS::OK)   return;

      long   Step = 0;   
      sEAFBurnerPredRes     BurnerStepRes;  
                            BurnerStepRes.Phase               = Phase.c_str();  
                            BurnerStepRes.PhaseNo             = BasketNo;
                            BurnerStepRes.Step                = 0;     
                            BurnerStepRes.BaseMass            = BaseMass;   
                            BurnerStepRes.DurStep             = 0.;               
                            BurnerStepRes.SpecEgy             = 0.;               
                            BurnerStepRes.ElecEgy             = 0.;  
                            BurnerStepRes.GasFlow             = 0.;  
                            BurnerStepRes.O2Flow              = 0.;
                            BurnerStepRes.ElecEgyStep         = 0.;
                            BurnerStepRes.DurUntilEndOfStep   = 0.;
                            BurnerStepRes.DurUntilStartOfStep = 0.;
                            BurnerStepRes.SpecEgyStep         = 0.;
                            BurnerStepRes.FlameProfile_Burner = 0;
                            
                            

      while (Step <= 20 && CRS::OK == pIntfEAF->getPredStepBurner(BurnerStepRes.DurUntilEndOfStep, BurnerStepRes.ElecEgy))
      {
        ++Step;
        BurnerStepRes.Step = Step;
        BurnerStepRes.ElecEgy = setToRange(BurnerStepRes.ElecEgy,0,0,999999);

        long BurnerNo =0;
        std::string GasType ="";
        double GasFlow = 0.;
        double O2Flow = 0.;
        

        long   Step2 = 0;
        while (Step2 < HowManyBurners &&  CRS::OK == pIntfEAF->getPredStepDataBurner(BurnerNo, GasFlow, O2Flow) )
        {
          std::string BurnerName = m_pGCE_BURNER->getBurnerNameByPlant(Plant,PlantNo,BurnerNo);

          BurnerStepRes.BurnerName  = BurnerName.c_str();
          BurnerStepRes.GasFlow     = GasFlow ; 
          BurnerStepRes.O2Flow      = O2Flow  ; 
          //data from model by unit:Nm3/min but data from table by unit: Nm3/h  -- SANKAR
          if(m_pGTE_PP_FLAME_PROFILE->selectbyFlowData(Plant,PlantNo,BurnerName,O2Flow*60,GasFlow*60))
          {
            BurnerStepRes.FlameProfile_Burner = m_pGTE_PP_FLAME_PROFILE->getFLAMEPROFILENO(1);
          }

          CIntfData::insert(BurnerPredRes, BurnerStepRes);

          ++Step2;

          std::stringstream ssMsg;
          ssMsg << "getPredStepDataBurner()-> Phase :" << BurnerStepRes.Phase << ", PhaseNo: " << BurnerStepRes.PhaseNo << ",  Step: " << BurnerStepRes.Step << " , ElecEgy:" << BurnerStepRes.ElecEgy << " , BurnerName: "<< BurnerStepRes.BurnerName << " , GasFlow:" << BurnerStepRes.GasFlow  << " , O2Flow:" << BurnerStepRes.O2Flow ;
          log(ssMsg.str(),3);

        }

      } 

    }
    catch (...)
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "", Scope.c_str(), ""  );    

    }
  #endif

}
  

//##ModelId=45EBDA4001ED
void CEAFModelResultWrapper::getPredCalcResults(  const std::string& Plant, long PlantNo, 
                                                  const std::string& Phase, long BasketNo, seqEAFProcessPredRes& ElecPredRes,  
                                                  seqEAFGasLancePredRes&  GasLancePredRes, seqEAFInjectLance& InjctPredRes, 
                                                  seqEAFGasLancePredRes&  BottomStirrPredRes, double BaseMass)
{

  std::string Scope = "CEAFModelResultWrapper::getPredCalcResults()" ;

  CIntfEAF *pIntfEAF = getpModelIntf();


  if (!pIntfEAF || !checkDBConnection()) 
  {
    log("Error " + Scope + " , (pIntfEAF || checkDBConnection()) == false", 1);
    return ;
  }

  std::stringstream strMsg;
  try 
  {

    ////////////////////////////////////////////////////
    // get electrical prediction results for the Phase //
    ////////////////////////////////////////////////////
    long ret = pIntfEAF->focusOnElecData();

    sEAFProcessPredRes    ElecStepRes;                                                              
                          ElecStepRes.Phase             = Phase.c_str();  
                          ElecStepRes.PhaseNo           = BasketNo;
                          ElecStepRes.Step              = 0;
                          ElecStepRes.VoltTap           = 0;
                          ElecStepRes.ImpCurve          = 0;
                          ElecStepRes.ReactorTap        = 0;
                          ElecStepRes.DurStep           = 0.;            
                          ElecStepRes.Temp              = 0.;
                          ElecStepRes.DurUntilEndOfStep = 0.;
                          ElecStepRes.DurUntilStartOfStep = 0.;
                          ElecStepRes.SpecEgyStep       = 0.;
                          ElecStepRes.SpecEgy           = 0.;             
                          ElecStepRes.ElecEgyStep       = 0.;
                          ElecStepRes.ElecEgy           = 0.;
                          ElecStepRes.O2Flow            = 0.;
                          ElecStepRes.O2Amount          = 0.;
                          ElecStepRes.BaseMass          = BaseMass;      
                          
   
    long   Step = 0;
    while (Step <= 20 && CRS::OK == pIntfEAF->getPredStepElec(ElecStepRes.Step,
                                                              ElecStepRes.DurUntilEndOfStep,
                                                              ElecStepRes.ElecEgy,
                                                              ElecStepRes.Temp,
                                                              ElecStepRes.VoltTap,
                                                              ElecStepRes.ImpCurve, 
                                                              ElecStepRes.ReactorTap)
           )
    {
      //if ( ElecStepRes.DurUntilEndOfStep <= 0 )  break;
      ElecStepRes.ElecEgy = setToRange(ElecStepRes.ElecEgy,0,0,999999);
      ++Step;

      //ElecStepRes.Step = Step; //as per Martin : step number was returned by model.

      CIntfData::insert(ElecPredRes, ElecStepRes);

      std::stringstream ssMsg;
      ssMsg << "getPredStepElec()-> Phase: " << ElecStepRes.Phase << ", PhaseNo: " << ElecStepRes.PhaseNo << ", Step: " << ElecStepRes.Step << " , ElecEgy:" << ElecStepRes.ElecEgy;
      log(ssMsg.str(),3);
    }  
    
    
    ////////////////////////////////////////////////////
    // get gas lance prediction results for the Phase //
    ////////////////////////////////////////////////////
    #if defined (EAF_GAS_LANCES)
      Step = 0;
      ret = pIntfEAF->focusOnManipGasLanceData();

      sEAFGasLancePredRes  GasLanceStepRes  ;               
                           GasLanceStepRes.Phase                = Phase.c_str();  
                           GasLanceStepRes.PhaseNo              = BasketNo;
                           GasLanceStepRes.Step                 = 0;
                           GasLanceStepRes.DurStep              = 0.;            
                           GasLanceStepRes.DurUntilEndOfStep    = 0.;
                           GasLanceStepRes.DurUntilStartOfStep  = 0.;
                           GasLanceStepRes.SpecEgyStep          = 0.;
                           GasLanceStepRes.SpecEgy              = 0.;             
                           GasLanceStepRes.ElecEgyStep          = 0.;
                           GasLanceStepRes.ElecEgy              = 0.;
                           GasLanceStepRes.BaseMass             = BaseMass;      

      while ( Step <= 20 && CRS::OK == pIntfEAF->getPredStepManipGasLance(GasLanceStepRes.DurUntilEndOfStep,GasLanceStepRes.ElecEgy) ) 
      {
        ++Step;
        GasLanceStepRes.Step    = Step;
        GasLanceStepRes.ElecEgy = setToRange(GasLanceStepRes.ElecEgy,0,0,999999);

        long LanceNo        = 0;
        std::string GasType = "";
        double GasFlow      = 0.;

        seqDeviceGasData SeqDeviceGasData;

        long   loop  =  0;
        while (loop <= 10 && CRS::OK == pIntfEAF->getPredStepDataManipGasLance(LanceNo, GasType, GasFlow)  )
        {
          ++loop;

          std::string DeviceName    = m_pGCE_INJECTION->getDeviceNameByL1InjectorNo(Plant, PlantNo, LanceNo, DEF_GCE_INJECTION_TYPE::OxygenInjection );

          sDeviceGasData DeviceGasData;
          DeviceGasData.Device = DeviceName.c_str();

          // Nm3/min --> Nm3/h will be done in DH_OUT
          seqGasData SeqGasFlow;

          sGasData GasData;
          GasData.GasType   = GasType.c_str();
          GasData.GasValue  = GasFlow;

          CIntfData::insert(SeqGasFlow,GasData);

          DeviceGasData.GasData    = SeqGasFlow;  

          CIntfData::insert(SeqDeviceGasData,DeviceGasData);

          std::stringstream ssMsg;
          ssMsg << "getPredStepManipGasLance()-> Phase: " << GasLanceStepRes.Phase << ", PhaseNo: " << GasLanceStepRes.PhaseNo << ", Step: " << GasLanceStepRes.Step << ", Device: " << DeviceGasData.Device << " , ElecEgy:" << GasLanceStepRes.ElecEgy << " , O2Flow :" << GasFlow ;
          log(ssMsg.str(),3);
        } 

        if ( loop > 0 )
        {
          GasLanceStepRes.GasFlow = SeqDeviceGasData;
        }

        CIntfData::insert(GasLancePredRes, GasLanceStepRes);

      } 
    #endif


    //////////////////////////////////////////////////////////
    // get injection lance prediction results for the Phase //
    //////////////////////////////////////////////////////////
    #if defined (EAF_INJECTION_LANCES) 
      Step = 0;
      ret = pIntfEAF->focusOnManipInjectLanceData();

      sEAFInjectLance   InjctStepRes;                                                                       
                        InjctStepRes.Phase                = Phase.c_str();   
                        InjctStepRes.PhaseNo              = BasketNo;
                        InjctStepRes.Step                 = 0;          
                        InjctStepRes.DurStep              = 0.0;             
                        InjctStepRes.Egy                  = 0.0;  
                        InjctStepRes.RemEgy               = 0.0;  
                        InjctStepRes.DurUntilEndOfStep    = 0.0;  
                        InjctStepRes.DurUntilStartOfStep  = 0.0;  
                        InjctStepRes.SpecEgyStep          = 0.0;               
                        InjctStepRes.ElecEgyStep          = 0.0;
                        InjctStepRes.SpecEgy              = 0.0;
                        InjctStepRes.BaseMass             = BaseMass;

        // prepare for current recived phase set points
        while (Step < 21 && CRS::OK == pIntfEAF->getPredStepManipInjectLance(InjctStepRes.DurUntilEndOfStep, InjctStepRes.Egy))
        {
          ++Step;
          InjctStepRes.Step       = Step;
          InjctStepRes.Egy        = setToRange(InjctStepRes.Egy, 0, 0, 999999);
          InjctStepRes.RemEgy     = InjctStepRes.Egy;

          std::string PurpCode;
          std::string MatCode;
          double Value = 0.;

          seqInjectLanceData SeqInjectLanceData;

          long   loop = 0;
          while (loop < 11 && CRS::OK == pIntfEAF->getPredStepDataManipInjectLance(PurpCode, MatCode, Value) )
          {
            std::string InjType = m_pGCE_INJECTION_TYPE->getInjTypeByPurposeCode(PurpCode, CSMC_DBData::unspecString);

            sInjectLanceData   InjectLanceData;
            InjectLanceData.InjectionType  = InjType.c_str();
            InjectLanceData.MatCode        = MatCode.c_str();
            InjectLanceData.Value          = Value;

            // add device-name to avoid archiving exception
            std::string DeviceName = m_pGCE_INJECTION->getDeviceNameByL1InjectorNo(Plant, PlantNo, CSMC_DBData::unspecLong, InjType);
            InjectLanceData.Device = DeviceName.c_str();

            CIntfData::insert(SeqInjectLanceData, InjectLanceData);

            ++loop;

            std::stringstream ssMsg;
            ssMsg << "getPredStepManipInjectLance()-> Phase: " << InjctStepRes.Phase 
                  << " , PhaseNo: " << InjctStepRes.PhaseNo 
                  << " , Step: "    << InjctStepRes.Step 
                  << " , ElecEgy:"  << InjctStepRes.Egy 
                  << " , DeviceName:"     << InjectLanceData.Device  
                  << " , InjectMatCode:"  << InjectLanceData.MatCode 
                  << " , InjectMatValue:" << InjectLanceData.Value;
            log(ssMsg.str(),3);

          }
          if (loop > 0)
          {            
            InjctStepRes.InjectFlow = SeqInjectLanceData;  
          }

          CIntfData::insert(InjctPredRes,InjctStepRes);                            

        }
    #endif


    ////////////////////////////////////////////////////
    // get bottom stirring prediction results for the Phase //
    ////////////////////////////////////////////////////
    #if defined (EAF_BOTTOM_STIRRING)
      Step = 0;
      ret = pIntfEAF->focusOnBottomStirringData();

      sEAFGasLancePredRes  BottomStirrStepRes  ;               
                           BottomStirrStepRes.Phase               = Phase.c_str();  
                           BottomStirrStepRes.PhaseNo             = BasketNo;
                           BottomStirrStepRes.Step                = 0;
                           BottomStirrStepRes.DurStep             = 0.;            
                           BottomStirrStepRes.DurUntilEndOfStep   = 0.;
                           BottomStirrStepRes.DurUntilStartOfStep = 0.;
                           BottomStirrStepRes.SpecEgyStep         = 0.;
                           BottomStirrStepRes.SpecEgy             = 0.;             
                           BottomStirrStepRes.ElecEgyStep         = 0.;
                           BottomStirrStepRes.BaseMass            = BaseMass;      

      while ( Step <= 20 && CRS::OK == pIntfEAF->getPredStepBottomStirring(BottomStirrStepRes.DurUntilEndOfStep,BottomStirrStepRes.ElecEgy) ) 
      {
        ++Step;
        BottomStirrStepRes.Step     = Step;
        BottomStirrStepRes.ElecEgy  = setToRange(BottomStirrStepRes.ElecEgy,0,0,999999);

        long LanceNo = 0;
        std::string GasType = "";
        double GasFlow = 0.;

        seqDeviceGasData SeqDeviceGasData;

        long   Step2  =  0;

        while (Step2 <= 10 && CRS::OK == pIntfEAF->getPredStepDataBottomStirring(GasType, GasFlow)  )
        {
          sDeviceGasData DeviceGasData;

          seqGasData  seqFlow;

          sGasData sFlow;
          sFlow.GasType = GasType.c_str();
          sFlow.GasValue = GasFlow;
          CIntfData::insert(seqFlow, sFlow);

          // mrut 2013-11-09 Int.test JSW missing statement added:
          DeviceGasData.GasData = seqFlow;  

          CIntfData::insert(SeqDeviceGasData,DeviceGasData);

          ++Step2;

          std::stringstream ssMsg;
          ssMsg << "getPredStepBottomStirring()-> Phase: " << BottomStirrStepRes.Phase << ", PhaseNo: " << BottomStirrStepRes.PhaseNo << ", Step: " << BottomStirrStepRes.Step << " , ElecEgy:" << BottomStirrStepRes.ElecEgy << " , GasType:" << sFlow.GasType  << " , GasValue:" << sFlow.GasValue ;
          log(ssMsg.str(),3);
        } 

        //if (Step2>0)
        //{            
          BottomStirrStepRes.GasFlow = SeqDeviceGasData;  
          CIntfData::insert(BottomStirrPredRes, BottomStirrStepRes);                           
        //}


      } 
    #endif

  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", Scope.c_str(), ""  );    
  }

}

//##ModelId=45EBDA4001F4
void CEAFModelResultWrapper::getPredCalcResults(  const std::string&      Plant, long PlantNo,
                                                  const std::string&      Phase, long BasketNo,
                                                  seqEAFMatFeedPredRes&   MatFeedPredRes, double BaseMass)
{

  /////////////////////////////////////////////////////////
  //          get feeding pattern
  /////////////////////////////////////////////////////////

  std::string Scope = "CEAFModelResultWrapper::getPredCalcResults()" ;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !checkDBConnection()) 
  {
    log("Error " + Scope + " , (pIntfEAF || checkDBConnection()) == false", 1);
    return ;
  }

  std::stringstream strMsg;
  try 
  {

    #if defined(EAF_PATTERN_FEEDING)
      long   Step = 0;
      long    ret = pIntfEAF->focusOnMatFeedData();

      sEAFMatFeedPredRes  MatFeedStepRes;
                          MatFeedStepRes.PhaseName      = Phase.c_str();
                          MatFeedStepRes.BasketNo       = BasketNo;
                          MatFeedStepRes.Step           = 0;
                          MatFeedStepRes.DurStep        = 0.0;
                          MatFeedStepRes.DurUntilEndOfStep    =  0.0;
                          MatFeedStepRes.DurUntilStartOfStep  =  0.0;
                          MatFeedStepRes.Egy            = 0.0;
                          MatFeedStepRes.SpecEgy        = 0.0;
                          MatFeedStepRes.ElecEgyStep    =  0.0;
                          MatFeedStepRes.BaseMass       = BaseMass;                          
                          MatFeedStepRes.SpecEgyStep    =  0.0;

        while ( Step <= 20 && CRS::OK == pIntfEAF->getPredStepMatFeed(MatFeedStepRes.DurUntilEndOfStep, MatFeedStepRes.Egy) )
        {
          ++Step;
	        MatFeedStepRes.Step =  Step;
          MatFeedStepRes.Egy = setToRange(MatFeedStepRes.Egy,0,0,999999);

      	  seqBatch  MatFeedDataSeq;
          std::string MatCode ="";
          double      MatFeedSpeed = 0.;
          long   Step2 = 0;
          while (Step2 <= 10 && CRS::OK == pIntfEAF->getPredStepDataMatFeed(MatCode, MatFeedSpeed) )
          {
            sBatch    MatFeedData;

            MatFeedData.MatCode =       MatCode.c_str();
            MatFeedData.MatFeedSpeed =  MatFeedSpeed;
            MatFeedData.FeedingRateRel2Energy =  0.; // set o. because it is spare as per DARKO
            MatFeedData.Mass = 0.;
            MatFeedData.Source = 0;
            CIntfData::insert(MatFeedDataSeq, MatFeedData);          
            ++Step2;

            std::stringstream ssMsg;
            ssMsg << "getPredStepMatFeed()-> Phase: " << MatFeedStepRes.PhaseName << ", PhaseNo: " << MatFeedStepRes.BasketNo << ", Step: " << MatFeedStepRes.Step << " , ElecEgy:" << MatFeedStepRes.Egy << " , MatCode:" << MatFeedData.MatCode  << " , MatFeedSpeed:" << MatFeedData.MatFeedSpeed ;
            log(ssMsg.str(),3);

          }

          //if (Step2 >0)
          //{
            MatFeedStepRes.MatFeedData = MatFeedDataSeq;                
            CIntfData::insert(MatFeedPredRes,MatFeedStepRes);           
          //}        
        }  

    #endif
    
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", Scope.c_str(), ""  );    
  }

}

//##ModelId=45EBDA4001DF
bool CEAFModelResultWrapper::doMatRecipeSetpoints(CEventMessage &Event)
{
  bool RetValue = true;
  std::string Scope = "CEAFModelResultWrapper::doMatRecipeSetpoints()" ;

  std::string TreatID   = Event.getTreatID(); 
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !checkDBConnection()) 
  {
    log("Error: " + Scope + " , (pIntfEAF || checkDBConnection()) == false", 1);
    return RetValue;
  }

  try 
  {
    m_pModelResults->setLong  (m_Key.c_str(),DATA::HeatPredCalcNo,m_HeatPredCalcNo);
    m_pModelResults->setString(m_Key.c_str(),DATA::EventNameLastPredCalc,Event.getMessage().c_str());

   
    seqRecipeList  MatRecList;

    if ( m_pGC_COMBI_RECIPE_ENTRY->selectByPlant(ActPlant) )
    {
      for (int i = 1; i <= m_pGC_COMBI_RECIPE_ENTRY->getLastRow(); i++)
      {
        const std::string RecipeName   = m_pGC_COMBI_RECIPE_ENTRY->getRECIPENAME(i);
        const long        RecipeNo     = 1;
        const std::string RecipeSource = m_pGC_COMBI_RECIPE_ENTRY->getSOURCE(i);

		    std::string RecipeNameModel;
		    long  RecipeNoModel = 0;

        if ( m_pRecipeHandler->translateToModelRecipe(ActPlant, RecipeName, RecipeNo, RecipeNameModel, RecipeNoModel) )
        {
          if ( !isValidModelRecipeName(RecipeNameModel) )
          {
            continue;
          }

          if(RecipeSource.empty() || isCombiRecipe(RecipeNameModel))
            pIntfEAF->focusOnRecipe(RecipeNameModel,RecipeNoModel,true);
          else
            pIntfEAF->focusOnRecipeOrig(RecipeNameModel,RecipeNoModel,RecipeSource,true);

          sBatchPrio    strBatch;
          std::string   Code;
          seqBatchPrio  seqBatch;
          sRecipe       strRecipe;
          double        TotalMass   = 0.;
          std::string   HeatID;
          std::string   TreatID;
          std::string   Grade;

          while (pIntfEAF->getMatSetpoint(Code, strBatch.BatchData.Mass, strBatch.BatchData.MatFeedSpeed, strBatch.ChargPrio) == CRS::OK)
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

          if (CIntfData::getLength(seqBatch) > 0)
          {
            pIntfEAF->getHeatData(HeatID, TreatID, Grade);
            strRecipe.RecipeName_Model         = RecipeNameModel.c_str();
            strRecipe.RecipeNo_Model           = RecipeNoModel;   
            strRecipe.RecipeSource             = RecipeSource.c_str();
            strRecipe.RecipeContent            = seqBatch;
            strRecipe.RecipeData.RecipeStatus  = 0;
            strRecipe.RecipeData.HomogDuration = pIntfEAF->getHomogenizationDur();
            strRecipe.RecipeData.TotalMass     = TotalMass;
            strRecipe.RecipeData.BulkVolume    = 0.0;
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

            strRecipe.RecipeName  = RecipeName_DB.c_str();
            strRecipe.RecipeNo    = RecipeNo_DB;   

            if ( std::string(strRecipe.RecipeName).empty() || strRecipe.RecipeNo == DEF::Inv_Long )
            {
              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_ErrorProcessingData(sMessage,Scope.c_str(),RecipeNameModel.c_str() );
            }
            else
            {
              CIntfData::insert(MatRecList, strRecipe);
            }
          }
        } 
        else
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorHandlingRecipe(sMessage, RecipeName.c_str(), RecipeNo, Scope.c_str());
        }

      } // for (int i = 1; i <= m_pGC_COMBI_RECIPE_ENTRY->getLastRow(); i++)
    }

    m_pModelResults->setRecipeList(m_Key.c_str(), DATA::EAFMatRecipe,       MatRecList);


    /////////////////////////////////////////////////////////////////
    /*seqRecipeList MatRecList;   
    m_pGC_RECIPE_SOURCE->select(CSMC_DBData::unspecString,CSMC_DBData::unspecLong,ActPlant, CSMC_DBData::unspecString);

    std::map < pair < pair <std::string, long>, std::string>, long >  RecipeList;     // it is a map to be able to search easily
                pair < pair <std::string, long>, std::string>          Entry;
                      pair <std::string, long>                        RecipePair;



    m_pGC_COMBI_RECIPE_ENTRY->selectByPlant(ActPlant);
    for (int i = 1; i <= m_pGC_COMBI_RECIPE_ENTRY->getLastRow(); i++)
    {

      RecipePair = make_pair(m_pGC_COMBI_RECIPE_ENTRY->getRECIPECOMBI  (i),
                              m_pGC_COMBI_RECIPE_ENTRY->getRECIPECOMBINO(i));

      Entry = make_pair(RecipePair, m_pGC_COMBI_RECIPE_ENTRY->getSOURCE(i));

      if ( RecipeList.find(Entry) == RecipeList.end() )
            RecipeList[ Entry ] = 1;

    }

    std::map < pair < pair <std::string, long>, std::string>, long > ::iterator itEnd (RecipeList.end());
    std::map < pair < pair <std::string, long>, std::string>, long > ::iterator it    (RecipeList.begin());

    for (; it != itEnd; ++it)
    {
        const std::string RecipeName   ( ((it->first).first).first  ) ;   // first things first!
        const        long RecipeNumber ( ((it->first).first).second ) ;  
        const std::string RecipeSource (  (it->first).second        ) ;

        if ( (RecipeName != DEF_GC_RECIPENAME::HighPrioBatch) && (RecipeSource != DEF_GC_RECIPE_SOURCE::All) )
          getMatRecipeSetpoints(TreatID, RecipeName, RecipeNumber, RecipeSource, MatRecList);
    }

    m_pModelResults->setRecipeList(m_Key.c_str(), DATA::EAFMatRecipe,       MatRecList);
    m_pModelResults->setLong      (m_Key.c_str(), DATA::EAFMatRecipeLength, MatRecList.length());
    */
    /////////////////////////////////////////////////////////////////

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
    pEventLog->EL_ExceptionCaught(sMessage, "", Scope.c_str() , ""  );    
  }
 
  return RetValue;
}

//##ModelId=45EBDA40020E
void CEAFModelResultWrapper::getMatRecipeSetpoints( const std::string& Plant, 
                                                    const long         PlantNo,   
                                                    const std::string& treatid, 
                                                    const std::string& RecipeName, 
                                                    const long         RecipeNo, 
                                                    const std::string& Source, 
                                                    seqRecipeList&     MatRecList) 
{
  sRecipe       strRecipe;
  sBatchPrio    strBatch;
  seqBatchPrio  seqBatch;
  long          MatSetpoint = 0;
  double        TotalMass   = 0;
  double        FeedSpeed   = 0;
  std::string   Code;
  std::string   HeatID;
  std::string   TreatID;
  std::string   Grade;

  CIntfEAF *pIntfEAF = getpModelIntf();

  std::string Scope = "CEAFModelResultWrapper::getMatRecipeSetpoints()" ;

  try
  {
    strRecipe.RecipeContent.length(0);

    // check catalogue of versions for model's recipes (table GC_RECIPE_L1)
		std::string RecipeNameModel;
		long  RecipeNoModel = 0;

    if ( m_pRecipeHandler->translateToModelRecipe(Plant, RecipeName, RecipeNo, RecipeNameModel, RecipeNoModel) )
    {
      if ( isValidModelRecipeName(RecipeNameModel) )
      {
        const std::string CheckableRecipeName = (RecipeNoModel>0)?  CSMM::toString(RecipeNameModel,RecipeNoModel) : RecipeNameModel;

        const set<string>& RecipeSet = getpCfgEAF()->getRecipe();
        const set<string>& SourceSet = getpCfgEAF()->getSource();

        if (      (!Source.empty() && SourceSet.find( Source )            == SourceSet.end() ) 
              ||  (                   RecipeSet.find(CheckableRecipeName) == RecipeSet.end() ) 
            )
        {
            std::stringstream msg;
            msg << "Skipping results for recipe " << RecipeNameModel<< " " << RecipeNoModel << " " << Source;
            log(msg.str(), 2);msg.str("");
            return;
        }


        if ( isCombiRecipe(RecipeNameModel) || Source.empty() )  //combi-Recipe has no source
          pIntfEAF->focusOnRecipe   (RecipeNameModel, RecipeNo, true);
        else
          pIntfEAF->focusOnRecipeOrig (RecipeNameModel, RecipeNo, Source, true);


        do
        {
          if(CRS::OK == (MatSetpoint = pIntfEAF->getMatSetpoint(Code, strBatch.BatchData.Mass, strBatch.BatchData.MatFeedSpeed , strBatch.ChargPrio)))
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
              MinChargeAbleWeightBin = m_pPD_MAT_AVAIL->getMinWeightOfMatCode(Plant, PlantNo, Source, CSMC_DBData::unspecLong, Code);
            }

            // check existance of data in DB
            MinChargeAbleWeightBin = CDataConversion::SetInvalidToDefault(MinChargeAbleWeightBin, 0.0, CSMC_DBData::unspecDouble);
            MinChargeAbleWeightMat = CDataConversion::SetInvalidToDefault(MinChargeAbleWeightMat, 0.0, CSMC_DBData::unspecDouble);

            // detect valid weight to be regarded by model result
            double MinChargeAbleWeight    = max( MinChargeAbleWeightBin , MinChargeAbleWeightMat );

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
        } while (MatSetpoint == CRS::OK);

        if (CIntfData::getLength(seqBatch) > 0)
        {
          pIntfEAF->getHeatData(HeatID, TreatID, Grade);
          strRecipe.RecipeName_Model         = RecipeNameModel.c_str();
          strRecipe.RecipeNo_Model           = RecipeNo;   
          strRecipe.RecipeSource             = Source.c_str();
          strRecipe.RecipeContent            = seqBatch;
          strRecipe.RecipeData.RecipeStatus  = 0;
          strRecipe.RecipeData.HomogDuration = pIntfEAF->getHomogenizationDur();
          strRecipe.RecipeData.TotalMass     = TotalMass;
          strRecipe.RecipeData.BulkVolume    = 0.0;
          strRecipe.Product.HeatId           = HeatID.c_str();
          strRecipe.Product.TreatId          = treatid.c_str();
          strRecipe.Product.Plant            = Plant.c_str();

          // use CSMC_RecipeHandler 
          std::string RecipeName_DB;    
          long        RecipeNo_DB = -1;

          if (m_pRecipeHandler)
          {
            m_pRecipeHandler->checkModelRecipeData(Plant,
                                                  HeatID,
                                                  treatid,
                                                  Source,
                                                  RecipeNameModel,
                                                  RecipeNo,
                                                  RecipeName_DB,
                                                  RecipeNo_DB);
          }

          strRecipe.RecipeName  = RecipeName_DB.c_str();
          strRecipe.RecipeNo    = RecipeNo_DB;   

          CIntfData::insert(MatRecList, strRecipe);

        }
      } // if ( isValidModelRecipeName(RecipeNameModel) )
    } 
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingRecipe(sMessage, RecipeName.c_str(), RecipeNo, Scope.c_str());
    }

  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", Scope.c_str(), ""  );    
  }

}



bool CEAFModelResultWrapper::isActualProcessPhase(const std::string& Phase, long PhaseNo)
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) 
  {
    log("Error CEAFModelResultWrapper::isActualProcessPhase, pIntfEAF == false", 1);
    return RetValue ;
  }


  std::string ActProcessPhase = Phase;

  if ( PhaseNo > 0 )
  {
    ActProcessPhase = ActProcessPhase + CDataConversion::LongToString(PhaseNo);
  }

  if ( ActProcessPhase == pIntfEAF->getActualProcessPhase() )
  {
    RetValue = true;
  }

  return RetValue;
}

double CEAFModelResultWrapper::getDurationSince(DM::iDM_Interface_var& pDM_Interface,const std::string &Key, const char* Name)
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
bool CEAFModelResultWrapper::writeActualSetpointsToDB(CEventMessage &Event,
                                                      const seqPredRes            &SeqPredRes,
                                                      const seqEAFProcessPredRes  &SeqProcessPredRes,
                                                      const seqEAFGasLancePredRes &SeqGasLancePredRes,
                                                      const seqEAFInjectLance     &SeqInjectLanceRes,
                                                      const seqComputerModes      &SeqComputerModes,
                                                      const seqEAFBurnerPredRes   &SeqBurnerPredRes,
                                                      const seqEAFMatFeedPredRes  &SeqMatFeedPredRes,
                                                      const seqEAFGasLancePredRes &SeqBottomStirrPredRes,
                                                      const seqGasLanceData       &SegEAFBurnerAmount,
                                                      const seqInjectLanceData    &SegEAFInjectLanceAmount)
{
  log("++++++ CEAFModelResultWrapper::writeActualSetpointsToDB",3);
  bool RetValue = false;

  //------------ read the data from Event ------------------
  std::string HeatId    = Event.getHeatID();
  std::string TreatId   = Event.getTreatID(); 
  std::string ProductId = Event.getProductID();
  std::string OrderId   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantId   = Event.getPlantID();

  std::string Function     = "CEAFModelResultWrapper::writeActualSetpointsToDB";
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
        CPD_PLANTSTATUS           PD_PLANTSTATUS(pConnection);

        CGC_PhaseContainer      GC_PhaseContainer(pConnection, ActPlant);
        CPDE_ACTUAL_RES         PDE_ACTUAL_RES(pConnection);
        CPDE_PHASE_BURNER_RES   PDE_PHASE_BURNER_RES(pConnection);
        CPDE_PHASE_INJECT_RES   PDE_PHASE_INJECT_RES(pConnection);
        CPDE_PHASE_PROCESS_RES  PDE_PHASE_PROCESS_RES(pConnection);
        CPDE_PHASE_STIRRING_RES PDE_PHASE_STIRRING_RES(pConnection);
        CPD_MAT_FEED_RES        PD_MAT_FEED_RES(pConnection);
        CPD_PHASE_RES           PD_PHASE_RES(pConnection);
        CPD_PHASE_RES_PLANT     PD_PHASE_RES_PLANT(pConnection);

        // main part
        CDateTime HeatAnnounceTime;
        HeatAnnounceTime.SetTime    (pDM_Interface->getDate(Event.getProductID().c_str(),DATA::HeatAnnounceTime));
        long TreatmentPosition      (pDM_Interface->getLong(Event.getProductID().c_str(),DATA::TreatmentPosition));

        double DurSinceHeatAnnounce = getDurationSince(pDM_Interface, ProductId.c_str(), DATA::HeatAnnounceTime);
        double DurSinceHeatStart    = getDurationSince(pDM_Interface, ProductId.c_str(), DATA::HeatStartTime);

        std::string PhaseAct              = CIntfData::ToStdString(pDM_Interface->getString(ProductId.c_str(),DATA::PhaseAct));
        long PhaseNoAct                   = pDM_Interface->getLong(ProductId.c_str(),DATA::PhaseNoAct);
        
        seqGasLanceData   GasLanceFlow, BurnerFlow;
        GasLanceFlow    = CIntfData::ToCORBAType(pDM_Interface->getGasLanceData(ProductId.c_str(), DATA::GasLanceFlow));

        // use actual model value
        long ElecPullReq                  = m_pModelResults->getLong(m_Key.c_str(),DATA::ElecPullReq);
        long ElecLockReq                  = m_pModelResults->getLong(m_Key.c_str(),DATA::ElecInhibitReq);
        long VoltTapNoAim                 = m_pModelResults->getLong(m_Key.c_str(),DATA::VoltTapNoAim);
        long ElectrodRegCurveAim          = m_pModelResults->getLong(m_Key.c_str(),DATA::ElectrodRegCurveAim);
        long ReactTapNoAim                = m_pModelResults->getLong(m_Key.c_str(),DATA::ReactTapNoAim);

        pDM_Interface                     = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PLANT);
        double ElecCons                   = pDM_Interface->getDouble(DEF_PLANT::Furnace, DATA::ElecCons);
        double ElecConsPhase              = pDM_Interface->getDouble(DEF_PLANT::Furnace, DATA::ElecConsPhase);

        // using intermediate sequence to merge it from SeqInjectLanceRes and SeqGasLancePredRes
        seqEAFInjectLance  SeqEAFInjectLanceRes = SeqInjectLanceRes;

        log(Event.getMessage(),4);

        log(CIntfData::getContent(CIntfData::ToAny(SeqPredRes))              ,5);
        log(CIntfData::getContent(CIntfData::ToAny(SeqProcessPredRes))       ,5);
        log(CIntfData::getContent(CIntfData::ToAny(SeqGasLancePredRes))      ,5);
        log(CIntfData::getContent(CIntfData::ToAny(SeqBottomStirrPredRes))   ,5);
        log(CIntfData::getContent(CIntfData::ToAny(SeqInjectLanceRes))       ,5);
        log(CIntfData::getContent(CIntfData::ToAny(SeqComputerModes))        ,5);
        log(CIntfData::getContent(CIntfData::ToAny(SeqBurnerPredRes))        ,5);
        log(CIntfData::getContent(CIntfData::ToAny(SeqMatFeedPredRes))       ,5);
        log(CIntfData::getContent(CIntfData::ToAny(SegEAFBurnerAmount))      ,5);
        log(CIntfData::getContent(CIntfData::ToAny(SegEAFInjectLanceAmount)) ,5);


        if(ElecCons == DEF::Inv_Double ) ElecCons = 0.;

        if (CIntfData::getLength(SeqPredRes) > 0) 
        {
          RetValue = RetValue && PDE_ACTUAL_RES.writeResults(HeatId, TreatId, ActPlant, DurSinceHeatAnnounce, DurSinceHeatStart, ElecPullReq, ElecLockReq, SeqPredRes, 
            SeqComputerModes, VoltTapNoAim, ElectrodRegCurveAim, ElecCons, PhaseAct, PhaseNoAct, SegEAFBurnerAmount, SegEAFInjectLanceAmount);

          if (RetValue)
          {
            PDE_ACTUAL_RES.commit();
          }
          else
          {
            PDE_ACTUAL_RES.rollback();
          }
        }
        else
        {
          log("Warning: struct  SeqPredRes is empty!", 2);
        }

        if (CIntfData::getLength(SeqProcessPredRes) > 0) 
        {
          RetValue = RetValue && PDE_PHASE_PROCESS_RES.writeResults(HeatId, TreatId, ActPlant, DurSinceHeatAnnounce, SeqProcessPredRes);

          if (RetValue)
          {
            PDE_PHASE_PROCESS_RES.commit();
          }
          else
          {
            PDE_PHASE_PROCESS_RES.rollback();
          }
        }
        else
        {
          log("Warning: struct  SeqProcessPredRes is empty!", 2);
        }

        // gas lances to be handled as oxygen injector
        // extending SeqEAFInjectLanceRes with gas lance data here
        if (CIntfData::getLength(SeqGasLancePredRes) > 0) 
        {
          for (int i = 0 ; i < CIntfData::getLength(SeqGasLancePredRes) ; i++)
          {
            sEAFGasLancePredRes EAFGasLancePredRes;
            CIntfData::getAt(EAFGasLancePredRes,SeqGasLancePredRes,i);

            sEAFInjectLance EAFInjectLance;

            EAFInjectLance.PhaseNo              = EAFGasLancePredRes.PhaseNo;
            EAFInjectLance.Phase                = EAFGasLancePredRes.Phase;
            EAFInjectLance.Step                 = EAFGasLancePredRes.Step;
            EAFInjectLance.BaseMass             = EAFGasLancePredRes.BaseMass;
            EAFInjectLance.SpecEgy              = EAFGasLancePredRes.SpecEgy;
            EAFInjectLance.DurUntilStartOfStep  = EAFGasLancePredRes.DurUntilStartOfStep;
            EAFInjectLance.DurUntilEndOfStep    = EAFGasLancePredRes.DurUntilEndOfStep;
            EAFInjectLance.DurStep              = EAFGasLancePredRes.DurStep;
            EAFInjectLance.Egy                  = EAFGasLancePredRes.ElecEgy;
            EAFInjectLance.Phase                = EAFGasLancePredRes.Phase;

            seqDeviceGasData SeqDeviceGasData   = EAFGasLancePredRes.GasFlow;

            for (int j = 0 ; j < CIntfData::getLength(SeqDeviceGasData) ; j++)
            {
              sDeviceGasData DeviceGasData;

              CIntfData::getAt(DeviceGasData, SeqDeviceGasData, j);

              std::string Device                  = DeviceGasData.Device;
              seqGasData SeqGasData               = DeviceGasData.GasData;
              sGasData GasData;

              if ( Device != CSMC_DBData::unspecString && !Device.empty() )
              {
                if ( CIntfData::getAt(GasData, SeqGasData, 0) )
                {
                  seqInjectLanceData InjectFlows;
                  sInjectLanceData InjectData;

                  InjectData.MatCode        = GasData.GasType;
                  InjectData.Value          = GasData.GasValue;
                  InjectData.InjectionType  = DEF_GCE_INJECTION_TYPE::OxygenInjection.c_str();
                  InjectData.Device         = Device.c_str();

                  CIntfData::insert(InjectFlows,InjectData);

                  EAFInjectLance.InjectFlow = InjectFlows;
                }

                CIntfData::insert(SeqEAFInjectLanceRes, EAFInjectLance);
              }
            }
          }
        }
        else
        {
          log("Warning: struct  SeqGasLancePredRes is empty!", 2);
        }

        if (CIntfData::getLength(SeqMatFeedPredRes) > 0) 
        {
          RetValue = RetValue && PD_MAT_FEED_RES.writeResults(HeatId, TreatId, ActPlant, SeqMatFeedPredRes);

          //// build batch when DynamicFeeding is not availible from the model
          //seqBatch SeqBatch;

          //for (long i = 0; i < CIntfData::getLength(SeqMatFeedingRes); ++i)
          //{
          //  sEAFMatFeedPredRes EAFMatFeedPredRes;
          //  CIntfData::getAt(EAFMatFeedPredRes,SeqMatFeedingRes,i);

          //  seqBatch seqMatFeedData = EAFMatFeedPredRes.MatFeedData;
          //  double DurStep          = CDataConversion::SetInvalidToDefault(EAFMatFeedPredRes.DurStep  ,0.);

          //  for(long p = 0; p < CIntfData::getLength(seqMatFeedData); ++p)
          //  {
          //    sBatch NewBatch;
          //    CIntfData::getAt(NewBatch,seqMatFeedData,p);

          //    NewBatch.Mass = DurStep * NewBatch.MatFeedSpeed;

          //    CSMC_DataProvider_Impl::addBatch(SeqBatch, NewBatch);

          //  }
          //}

          //// prepare data for PD_RECIPE
          //sRecipeInfo SRecipeInfo;
          //SRecipeInfo.RecipeName    = "DynamicFeeding";
          //SRecipeInfo.RecipeSource  = DEF_GC_RECIPE_SOURCE::Bin;
          //SRecipeInfo.RecipeStatus  = DEF_GC_RECIPE_STATUS::Calculated;
          //SRecipeInfo.RecipeNo      = 1;
          //SRecipeInfo.RecipeTarget  = "Furnace";

          //sMetTimeStamp TimeStamp;
          //TimeStamp.O2_Moment   = DEF::Inv_Double;
          //TimeStamp.Ar_Moment   = DEF::Inv_Double;
          //TimeStamp.N2_Moment   = DEF::Inv_Double;
          //TimeStamp.Elec_Moment = ElecCons;

          //RetValue = RetValue && m_pPD_RECIPE->writeBatch(HeatId, TreatId, ActPlant, SRecipeInfo, TimeStamp, SeqBatch);

          if (RetValue)
          {
            PD_MAT_FEED_RES.commit();
          }
          else
          {
            PD_MAT_FEED_RES.rollback();
          }
        }
        else
        {
          log("Warning: struct  SeqMatFeedingRes is empty!", 2);
        }

        // mrut 2013-11-09
        // moved up as writing the burner pattern throws execption and we do not get a pattern on L1, so we cant run in cmp-mode.
        if (CIntfData::getLength(SeqBottomStirrPredRes) > 0)
        {
          RetValue = RetValue && PDE_PHASE_STIRRING_RES.writeResults(HeatId, TreatId, ActPlant, DurSinceHeatAnnounce, SeqBottomStirrPredRes);
          if (RetValue)
          {
            PDE_PHASE_STIRRING_RES.commit();
          }
          else
          {
            PDE_PHASE_STIRRING_RES.rollback();
          }
        }
        else
        {
          log("Warning: struct  SeqBottomStirrPredRes is empty!", 2);
        }


        if (CIntfData::getLength(SeqEAFInjectLanceRes)  > 0)
        {
          RetValue = RetValue && PDE_PHASE_INJECT_RES.writeResults(HeatId, TreatId, ActPlant, DurSinceHeatAnnounce, SeqEAFInjectLanceRes);
          if (RetValue)
          {
            PDE_PHASE_INJECT_RES.commit();
          }
          else
          {
            PDE_PHASE_INJECT_RES.rollback();
          }
        }
        else
        {
          log("Warning: struct  SeqEAFInjectLanceRes is empty!", 2);
        }

        if (CIntfData::getLength(SeqBurnerPredRes) > 0)
        {
          RetValue = RetValue && PDE_PHASE_BURNER_RES.writeResults(HeatId, TreatId, ActPlant, ActPlantNo, DurSinceHeatAnnounce, SeqBurnerPredRes);
          if (RetValue)
          {
            PDE_PHASE_BURNER_RES.commit();
          }
          else
          {
            PDE_PHASE_BURNER_RES.rollback();
          }
        }
        else
        {
          log("Warning: struct  SeqBurnerPredRes is empty!", 2);
        }

        ////if (CIntfData::getLength(SeqBottomStirrPredRes) > 0)
        ////{
        ////  RetValue = RetValue && PDE_PHASE_STIRRING_RES.writeResults(HeatId, TreatId, ActPlant, DurSinceHeatAnnounce, SeqBottomStirrPredRes);
        ////  if (RetValue)
        ////  {
        ////    PDE_PHASE_STIRRING_RES.commit();
        ////  }
        ////  else
        ////  {
        ////    PDE_PHASE_STIRRING_RES.rollback();
        ////  }
        ////}
        ////else
        ////{
        ////  log("Warning: struct  SeqBottomStirrPredRes is empty!", 2);
        ////}

        if (CIntfData::getLength(SeqPredRes) > 0) 
        {
          // ***********************************************
          // write result into PD_PHASE_RES and PD_PHASE_RES_PLANT
          // ***********************************************
          RetValue = PD_PHASE_RES.write(HeatId, TreatId, ActPlant, SeqPredRes, HeatAnnounceTime, false);

          if ( RetValue && PD_PHASE_RES.selectOrderedByDuration(HeatId, TreatId, ActPlant, true) )
          {
            double Duration_Prev  = 0.;

            for ( long i = 1 ; i <= PD_PHASE_RES.getLastRow(); ++i )
            {
              std::string PhaseName;
              long        PhaseNo          = CSMC_DBData::unspecLong;
              long        RESULTVALNO_EGY        = 1;
              long        RESULTVALNO_DUR        = 2;
              long        RESULTVALNO_FLOW       = 3;
              long        RESULTVALNO_EGY_PHASE  = 4;
              long        RES_PHASENO      = PD_PHASE_RES.getRES_PHASENO(i);
              double      Duration         = PD_PHASE_RES.getDURUNTENDOFPHASE(i);
              double      Energy           = 0.;
              double      EnergyPhase      = 0.;
              double      o2Flow           = 0.;
              double      PhaseDur         = 0.;
              

              if ( RES_PHASENO != CSMC_DBData::unspecLong )
              {
                if ( Duration != CSMC_DBData::unspecDouble )
                {
                  Duration      = CDataConversion::RoundToDecimals(Duration,1);
                  Duration_Prev = CDataConversion::RoundToDecimals(Duration_Prev,1);

                  // Duration_Prev is always <= Duration due to selection ASC
                  PhaseDur  = Duration - Duration_Prev;
                }

                double Oxygen_Injector_1flow = 0.;
                double Oxygen_Injector_2flow = 0.;

                if ( GC_PhaseContainer.getPhaseDataByResPhaseNo(PhaseName,PhaseNo,RES_PHASENO) )
                {
                  // special data handling for phase "ACTUAL"
                  if ( PhaseName == DEF_GC_PHASE::Actual )
                  {
                    Energy      = ElecCons;
                    EnergyPhase = ElecConsPhase;

                    CGasLanceDataHandler GasLanceDataHandlerGasLanceFlow(GasLanceFlow);
                    std::set<std::string> DeviceListLances = GasLanceDataHandlerGasLanceFlow.getDeviceList();
                    std::set<std::string>::iterator itLances ;

                    for ( itLances = DeviceListLances.begin() ; itLances != DeviceListLances.end(); ++itLances)
                    {
                      std::string Device  = (*itLances);

                      o2Flow = GasLanceDataHandlerGasLanceFlow.getGasValue(Device, DEF_GAS::O2) ;
                    }
                  }
                  else
                  {
                    for (int i = 0 ; i < CIntfData::getLength(SeqProcessPredRes) ; ++i)
                    {
                      sEAFProcessPredRes EAFProcessPredRes;
                      CIntfData::getAt(EAFProcessPredRes,SeqProcessPredRes,i);

                      if ( (std::string)EAFProcessPredRes.Phase == PhaseName && EAFProcessPredRes.PhaseNo == PhaseNo )
                      {
                        Energy       = max(Energy      , EAFProcessPredRes.ElecEgy);
                        EnergyPhase += EAFProcessPredRes.ElecEgyStep;
                        o2Flow       = max(o2Flow      , EAFProcessPredRes.O2Flow);
                      }
                    }

                    sEAFInjectLance InjectLance;
                    for (int i = 0 ; i < CIntfData::getLength(SeqEAFInjectLanceRes) ; i++)
                    {                   
                      CIntfData::getAt(InjectLance,&SeqEAFInjectLanceRes,i);

                      seqInjectLanceData SeqInjectLanceData = InjectLance.InjectFlow;
                      for (int j = 0 ; j < CIntfData::getLength(SeqInjectLanceData) ; j++)
                      {
                        sInjectLanceData   InjectLanceData;
                        CIntfData::getAt(InjectLanceData, SeqInjectLanceData, j);

                        if ( ((std::string)InjectLanceData.InjectionType == DEF_GCE_INJECTION_TYPE::OxygenInjection) && (std::string)InjectLance.Phase == PhaseName && InjectLance.PhaseNo == PhaseNo )
                        {
                          if ( DEF_GCE_INJECTION::Oxygen_Injector_1 == (std::string)InjectLanceData.Device)
                          {
                            Oxygen_Injector_1flow       = max(Oxygen_Injector_1flow      , InjectLanceData.Value);
                          }
                          if ( DEF_GCE_INJECTION::Oxygen_Injector_2 == (std::string)InjectLanceData.Device)
                          {
                            Oxygen_Injector_2flow       = max(Oxygen_Injector_2flow      , InjectLanceData.Value);
                          }
                        }// if ( ((std::string)InjectLanceData.InjectionType == DEF_GCE_INJECTION_TYPE::OxygenInjection) && (std::string)InjectLance.Phase == PhaseName && InjectLance.PhaseNo == PhaseNo )
                      }// for (int j = 0 ; j < CIntfData::getLength(SeqInjectLanceData) ; j++)
                    }//for (int i = 0 ; i < CIntfData::getLength(SeqEAFInjectLanceRes) ; i++)
                  }
                }// if ( GC_PhaseContainer.getPhaseDataByResPhaseNo(PhaseName,PhaseNo,RES_PHASENO) )


                o2Flow += Oxygen_Injector_1flow;
                o2Flow += Oxygen_Injector_2flow;

                Energy      = CDataConversion::SetInvalidToDefault(Energy      , 0., CSMC_DBData::unspecDouble);
                EnergyPhase = CDataConversion::SetInvalidToDefault(EnergyPhase , 0., CSMC_DBData::unspecDouble);
                PhaseDur    = CDataConversion::SetInvalidToDefault(PhaseDur    , 0., CSMC_DBData::unspecDouble);
                o2Flow      = CDataConversion::SetInvalidToDefault(o2Flow      , 0., CSMC_DBData::unspecDouble);

                RetValue = RetValue && PD_PHASE_RES_PLANT.write(HeatId, TreatId, ActPlant, RES_PHASENO, RESULTVALNO_EGY,        Energy,      false);
                RetValue = RetValue && PD_PHASE_RES_PLANT.write(HeatId, TreatId, ActPlant, RES_PHASENO, RESULTVALNO_EGY_PHASE,  EnergyPhase, false);
                RetValue = RetValue && PD_PHASE_RES_PLANT.write(HeatId, TreatId, ActPlant, RES_PHASENO, RESULTVALNO_DUR,        PhaseDur,    false);
                RetValue = RetValue && PD_PHASE_RES_PLANT.write(HeatId, TreatId, ActPlant, RES_PHASENO, RESULTVALNO_FLOW,       o2Flow,      false);

                Duration_Prev = Duration;

              }// if ( RES_PHASENO != CSMC_DBData::unspecLong )
            }// for ( long i = 1 ; i <= m_pPD_PHASE_RES->getLastRow(); ++i )
          }// if ( PD_PHASE_RES.selectOrderedByDuration(HeatId, TreatId, ActPlant, true) )
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

        // ***********************************************
        // write calculated analyses, weights and temperature
        // ***********************************************
        // check for existing sample reference, insert new one if required and update PD_HEAT_DATA
        if ( m_pPD_HEAT_DATA
          && m_pPD_HEAT_DATA->select(HeatId, TreatId, ActPlant) )
        {
          // determine existing or new SAMPLE_REF
          long SAMPLE_REF = m_pPD_HEAT_DATA->getSAMPLE_REF(1);

          if ( m_pPD_SAMPLE_REF 
            && SAMPLE_REF == CSMC_DBData::unspecLong )
          {
            SAMPLE_REF = m_pPD_SAMPLE_REF->insertNewSAMPLE_REF(false);
            m_pPD_HEAT_DATA->setSAMPLE_REF(SAMPLE_REF);

            // ********************************************************************************************************
            // Commit here immediately to avoid any deadlock.
            // ********************************************************************************************************
            // A deadlock can happen when model wrapper updates first PD_Heat_Data and then PD_Sample tables
            // but simultaniously another process (like tracking) updates first PD_sample tables and then PD_Heat_Data.
            // This different sequence of modifications on the multiple tables (and the same rows inside them)
            // without any commit in between is causing a deadlock when executed concurrently.
            // Therefore a commit is required here!
            // If a rollback is performed due to any error, then no table modification is done in PD_Sample tables,
            // because RetValue is false. But a single loop over the prediction is made due to implementation logic.
            // ********************************************************************************************************
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
          }

          sPredRes PredRes;
          for (int i = 0 ; i < CIntfData::getLength( SeqPredRes ) ; ++i)
          {
            CIntfData::getAt(PredRes, SeqPredRes, i);
            std::string sPhase = PredRes.Phase;

            if ( (sPhase == DEF_GC_PHASE::Tapping) ||
                 (sPhase == DEF_GC_PHASE::Actual )    )
            {
              long ResPhaseNo    = m_pGC_PhaseContainer->getResPhaseNo(sPhase,PredRes.PhaseNo);
              long PhaseNo       = PredRes.PhaseNo;

              // perform for valid phase numbers only
              if( ResPhaseNo != CSMC_DBData::unspecLong)
              {

                if ( RetValue 
                   && sPhase == DEF_GC_PHASE::Tapping )
              {
                // update expected treatment end "TREATEND_CALC" 
                CDateTime EndPhase;
                EndPhase = HeatAnnounceTime;
                EndPhase.addTime((PredRes.GenRes.MetTimeStamp.DurSinceHeatAnnouncement) * 60.0);

                // Jira SMPJSWTWO-78
                // Fuxin-merge. confirmed by guda +
                // The Fuxin change is correct: the treatment end time calculated by the model must be updated in PD_HEAT_DATA.
                // The older MAIN version used at this point PD_HEAT_DATA.TREATEND_MOD. 
                // Instead of it, PD_HEAT_DATA.TREATEND_CALC is correct. Since an update has been possibly done before,
                // the IF-statement ensures that the table row is read again.
                //
                if ( m_pPD_HEAT_DATA
                  && m_pPD_HEAT_DATA->select(HeatId, TreatId, ActPlant) )
                {
                  // Note: PD_Heat_Data.TreatEnd_MOD should never be overwritten by model (only by manual operator input)
                  m_pPD_HEAT_DATA->setTREATEND_CALC(EndPhase);
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
                }// if ( m_pPD_HEAT_DATA
                // Fuxin-merge. confirmed by guda -



                cCBS_ODBC_DBError CBS_ODBC_DBError;
                PD_PLANTSTATUS.updateExptreatmentend(ActPlant, ActPlantNo, EndPhase, TreatmentPosition, true, CBS_ODBC_DBError);

                // Write calculated final analysis with commit (see deadlock comment above)
                RetValue = RetValue && writeFinalCalculatedAnalysis( Event, SAMPLE_REF, PredRes.GenRes.Analysis, PredRes.GenRes.Temp, true);
              }

                if ( RetValue 
                   && sPhase == DEF_GC_PHASE::Actual )
              {
                // Write calculated actual analysis with commit (see deadlock comment above)
                RetValue = RetValue && writeCalculatedAnalysis( Event, SAMPLE_REF, PredRes.GenRes.Analysis, PredRes.GenRes.Temp, true);

                // Write calculated weights and temperature with commit (see deadlock comment above)
                RetValue = RetValue && writeCalculatedWeightsAndTemp( Event, PredRes.GenRes.SteelWeight, PredRes.GenRes.SlagWeight, PredRes.GenRes.Temp, true);

              } // if ( RetValue && sPhase == DEF_GC_PHASE::Actual )
            } // if( ResPhaseNo != CSMC_DBData::unspecLong)
              if (!RetValue)
                break;

            }
          } // for (int i = 0 ; i < PredResSeqLength ; ++i)

        } // if ( m_pPD_HEAT_DATA && m_pPD_HEAT_DATA->select(HeatID, TreatID, ActPlant) )

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
        CEAFModelWrapper::handleError("CEAFModelResultWrapper", "m_pModelTask is null");
        RetValue = false;
      }
      if (!pDM_Interface)
      {
        CEAFModelWrapper::handleError("CEAFModelResultWrapper", "pDM_Interface is null");
        RetValue = false;
      }
      if (!m_pModelResults)
      {
        CEAFModelWrapper::handleError("CEAFModelResultWrapper", "m_pModelResults is null");
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
    CEAFModelWrapper::handleDBConnectionError();
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
bool CEAFModelResultWrapper::writeRecipeSetpointsToDB(CEventMessage& Event, seqRecipeList &SeqRecipeList)
{
  log("++++++ CEAFModelResultWrapper::writeRecipeSetpointsToDB",3);
  bool RetValue = false;

  //------------ read the data from Event ------------------
  std::string HeatId    = Event.getHeatID();
  std::string TreatId   = Event.getTreatID(); 
  std::string ProductId = Event.getProductID();
  std::string OrderId   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantId   = Event.getPlantID();

  std::string Function     = "CEAFModelResultWrapper::writeRecipeSetpointsToDB";
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
        CEAFModelWrapper::handleError("CEAFModelResultWrapper", "m_pModelTask is null");
        RetValue = false;
      }
      if (!pDM_Interface)
      {
        CEAFModelWrapper::handleError("CEAFModelResultWrapper", "pDM_Interface is null");
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
    CEAFModelWrapper::handleDBConnectionError();
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

bool CEAFModelResultWrapper::calculateInjectionAmounts          (seqEAFInjectLance & SeqEAFInjectLance)
{
  // calculates injected amounts per step and adds or replaces values in passed sequence

  bool RetValue = true;

  long SeqLen = CIntfData::getLength(SeqEAFInjectLance);

  for (long i = 0; i < SeqLen; ++i)
  {
    sEAFInjectLance  EAFInjectLance;
    CIntfData::getAt(EAFInjectLance, SeqEAFInjectLance, i );

    double DurStep                              = EAFInjectLance.DurStep;
    seqInjectLanceData SeqInjectLanceDataFlow   = EAFInjectLance.InjectFlow;
    seqInjectLanceData SeqInjectLanceDataAmount; 

    long  len  = CIntfData::getLength(SeqInjectLanceDataFlow);
    for ( long j = 0; j < len; ++j)
    {
      sInjectLanceData    InjectLanceDataFlow;      
      CIntfData::getAt   (InjectLanceDataFlow, SeqInjectLanceDataFlow, j );
      
      //double StepAmount = InjectLanceDataFlow.Value * DurStep;  

      sInjectLanceData InjectLanceDataAmount (InjectLanceDataFlow);      // create a copy
                       InjectLanceDataAmount.Value *= DurStep;

      CIntfData::insert(SeqInjectLanceDataAmount, InjectLanceDataAmount);
    }

    EAFInjectLance.InjectAmount = SeqInjectLanceDataAmount;
  }

  return RetValue;
}

bool CEAFModelResultWrapper::calculateMatFeedingPatternAmounts(seqEAFMatFeedPredRes  & MatFeedPredRes, long CurrentlyActiveStepMatFeed)
{
  // mrut 2014-02-06, work on JIRA SMPJSWTWO-47 determination of material amount for feeding / determine amount here, instead of in EAF_Handler.
  // calculates amounts per step of the feeding pattern ( process pattern) and adds or replaces values in passed sequence

  bool RetValue = true;


  long TmpSeqLenMatFeed = CIntfData::getLength(MatFeedPredRes);

  if ( TmpSeqLenMatFeed > 0 ) 
  {                                                                                       // the two patterns are aligned
    // read parameter to determine delta time for offset on setpoint for feeding mass.
    double DeltaTimeForMassSetptOffset = 0.5;                                             // minutes 

    CEAFModelTask* pTask = dynamic_cast <CEAFModelTask*>(m_pModelTask);
    if (pTask) 
	  {
	    CParamMgr* pParamMgr = pTask->getpParamMgr();
		  if (pParamMgr) 
		  {
		    double Param_DeltaTimeForMassSetptOffset  = pParamMgr->getDouble ("DeltaTimeForMassSetptOffset", true);
			  if  (  Param_DeltaTimeForMassSetptOffset !=  CInv::InvalidDouble )
                      DeltaTimeForMassSetptOffset  = Param_DeltaTimeForMassSetptOffset;
      }
    }

    std::stringstream tmp;
 
    for (long i = 0; i < TmpSeqLenMatFeed; ++i)
    {
        tmp << "Phase: " << MatFeedPredRes[i].PhaseName << "[" << MatFeedPredRes[i].BasketNo << "]" << ", Step: " << MatFeedPredRes[i].Step;

        long LocLen = CIntfData::getLength(MatFeedPredRes[i].MatFeedData);
        for(long j = 0; j < LocLen; ++j)
        {
          double LocMatFeedSpeed = MatFeedPredRes[i].MatFeedData[j].MatFeedSpeed;
          double LocMass         = MatFeedPredRes[i].DurStep  *  LocMatFeedSpeed;

          if (MatFeedPredRes[i].Step == CurrentlyActiveStepMatFeed)                       // SMPJSWTWO-55 : add a blind mass to avoid too early feeding stop by level-1
              LocMass += (DeltaTimeForMassSetptOffset * LocMatFeedSpeed);

          MatFeedPredRes[i].MatFeedData[j].Mass = LocMass;

          tmp <<  "\n  " <<  MatFeedPredRes[i].MatFeedData[j].MatCode <<   ": MatFeedSpeed = " << MatFeedPredRes[i].MatFeedData[j].MatFeedSpeed << ", Mass = " <<  MatFeedPredRes[i].MatFeedData[j].Mass;
        }
        tmp <<  "\n  ";
    }
    log(tmp.str(), 2);
  }

         RetValue = ( TmpSeqLenMatFeed > 0 );
  return RetValue;
}

// due to different declarations of sematically identical items, three methods have to be used ... 1 for feeding,  2 for others ...
template<class T> 
void CEAFModelResultWrapper::alignResultPattern_1(const seqEAFProcessPredRes & ProcPredRes, 
                                                  bool LoggingOn, const std::string & ResultSeqName, const double Dur_Ref, const double Egy_Ref,
                                                  T & PredResultToAlign)
{
    long SeqLen   (CIntfData::getLength(ProcPredRes) );
    if ( SeqLen == CIntfData::getLength(PredResultToAlign))         // both pattern have the same length
     { 
       if ( LoggingOn )
       {
         std::stringstream msg;
         msg << "Result Sequence "<<  ResultSeqName << "[" << SeqLen<< "]" << "Dur_Ref: " << Dur_Ref << " Egy_Ref: " << Egy_Ref;
         log(msg.str(), 2);msg.str("");
       }

       for (long i = 0; i < SeqLen; ++i)
       {
          PredResultToAlign[i].DurUntilStartOfStep =  ProcPredRes[i].DurUntilStartOfStep;
          PredResultToAlign[i].DurUntilEndOfStep   =  ProcPredRes[i].DurUntilEndOfStep;
          PredResultToAlign[i].DurStep             =  ProcPredRes[i].DurStep;
          PredResultToAlign[i].Step                =  ProcPredRes[i].Step;

          PredResultToAlign[i].Egy                 =  ProcPredRes[i].ElecEgy;
          PredResultToAlign[i].ElecEgyStep         =  ProcPredRes[i].ElecEgyStep;
          PredResultToAlign[i].SpecEgy             =  ProcPredRes[i].SpecEgy;
          PredResultToAlign[i].SpecEgyStep         =  ProcPredRes[i].SpecEgyStep;

         if ( LoggingOn )
         {
            std::stringstream tmp;
            tmp << "Phase: " << PredResultToAlign[i].PhaseName << "[" << PredResultToAlign[i].BasketNo << "]" << ", Step: " << PredResultToAlign[i].Step
              << "\n   DurUntilEndOfStep: " << PredResultToAlign[i].DurUntilEndOfStep
              << "\n             DurStep: " << PredResultToAlign[i].DurStep
              << "\n DurUntilStartOfStep: " << PredResultToAlign[i].DurUntilStartOfStep
              << "\n                 Egy: " << PredResultToAlign[i].Egy
              << "\n         ElecEgyStep: " << PredResultToAlign[i].ElecEgyStep
              << "\n             SpecEgy: " << PredResultToAlign[i].SpecEgy
              << "\n         SpecEgyStep: " << PredResultToAlign[i].SpecEgyStep;
            log(tmp.str(), 2);
         }
        }
     }
}


// due to different declarations of sematically identical item, three methods have to be used ... 1 for feeding,  2&3 for others ...
template<class T> 
void CEAFModelResultWrapper::alignResultPattern_2 (const seqEAFProcessPredRes & ProcPredRes, 
                                                   bool LoggingOn, const std::string & ResultSeqName, const double Dur_Ref, const double Egy_Ref,
                                                   T & PredResultToAlign)
{
    long SeqLen   (CIntfData::getLength(ProcPredRes) );
    if ( SeqLen == CIntfData::getLength(PredResultToAlign))         // both pattern have the same length
     { 
       if ( LoggingOn )
       {
         std::stringstream msg;
         msg << "Result Sequence "<<  ResultSeqName << "[" << SeqLen<< "]" << "Dur_Ref: " << Dur_Ref << " Egy_Ref: " << Egy_Ref;
         log(msg.str(), 2);msg.str("");
       }

       for (long i = 0; i < SeqLen; ++i)
       {
          PredResultToAlign[i].DurUntilStartOfStep =  ProcPredRes[i].DurUntilStartOfStep;
          PredResultToAlign[i].DurUntilEndOfStep   =  ProcPredRes[i].DurUntilEndOfStep;
          PredResultToAlign[i].DurStep             =  ProcPredRes[i].DurStep;
          PredResultToAlign[i].Step                =  ProcPredRes[i].Step;

          PredResultToAlign[i].ElecEgy             =  ProcPredRes[i].ElecEgy;
          PredResultToAlign[i].ElecEgyStep         =  ProcPredRes[i].ElecEgyStep;
          PredResultToAlign[i].SpecEgy             =  ProcPredRes[i].SpecEgy;
          PredResultToAlign[i].SpecEgyStep         =  ProcPredRes[i].SpecEgyStep;

         if ( LoggingOn )
         {
            std::stringstream tmp;
            tmp << "Phase: " << PredResultToAlign[i].Phase << "[" << PredResultToAlign[i].PhaseNo << "]" << ", Step: " << PredResultToAlign[i].Step
              << "\n   DurUntilEndOfStep: " << PredResultToAlign[i].DurUntilEndOfStep
              << "\n             DurStep: " << PredResultToAlign[i].DurStep
              << "\n DurUntilStartOfStep: " << PredResultToAlign[i].DurUntilStartOfStep
              << "\n                 Egy: " << PredResultToAlign[i].ElecEgy
              << "\n         ElecEgyStep: " << PredResultToAlign[i].ElecEgyStep
              << "\n             SpecEgy: " << PredResultToAlign[i].SpecEgy
              << "\n         SpecEgyStep: " << PredResultToAlign[i].SpecEgyStep;
            log(tmp.str(), 2);
         }
        }
     }
}

// due to different declarations of sematically identical item, three methods have to be used ... 1 for feeding,  2&3 for others ...
// 3: for injection it read Egy, not elecEgy...
template<class T> 
void CEAFModelResultWrapper::alignResultPattern_3 (const seqEAFProcessPredRes & ProcPredRes, 
                                                   bool LoggingOn, const std::string & ResultSeqName, const double Dur_Ref, const double Egy_Ref,
                                                   T & PredResultToAlign)
{
    long SeqLen   (CIntfData::getLength(ProcPredRes) );
    if ( SeqLen == CIntfData::getLength(PredResultToAlign))         // both pattern have the same length
     { 
       if ( LoggingOn )
       {
         std::stringstream msg;
         msg << "Result Sequence "<<  ResultSeqName << "[" << SeqLen<< "]" << "Dur_Ref: " << Dur_Ref << " Egy_Ref: " << Egy_Ref;
         log(msg.str(), 2);msg.str("");
       }

       for (long i = 0; i < SeqLen; ++i)
       {
          PredResultToAlign[i].DurUntilStartOfStep =  ProcPredRes[i].DurUntilStartOfStep;
          PredResultToAlign[i].DurUntilEndOfStep   =  ProcPredRes[i].DurUntilEndOfStep;
          PredResultToAlign[i].DurStep             =  ProcPredRes[i].DurStep;
          PredResultToAlign[i].Step                =  ProcPredRes[i].Step;

          PredResultToAlign[i].Egy                 =  ProcPredRes[i].ElecEgy;
          PredResultToAlign[i].ElecEgyStep         =  ProcPredRes[i].ElecEgyStep;
          PredResultToAlign[i].SpecEgy             =  ProcPredRes[i].SpecEgy;
          PredResultToAlign[i].SpecEgyStep         =  ProcPredRes[i].SpecEgyStep;

         if ( LoggingOn )
         {
            std::stringstream tmp;
            tmp << "Phase: " << PredResultToAlign[i].Phase << "[" << PredResultToAlign[i].PhaseNo << "]" << ", Step: " << PredResultToAlign[i].Step
              << "\n   DurUntilEndOfStep: " << PredResultToAlign[i].DurUntilEndOfStep
              << "\n             DurStep: " << PredResultToAlign[i].DurStep
              << "\n DurUntilStartOfStep: " << PredResultToAlign[i].DurUntilStartOfStep
              << "\n                 Egy: " << PredResultToAlign[i].Egy
              << "\n         ElecEgyStep: " << PredResultToAlign[i].ElecEgyStep
              << "\n             SpecEgy: " << PredResultToAlign[i].SpecEgy
              << "\n         SpecEgyStep: " << PredResultToAlign[i].SpecEgyStep;
            log(tmp.str(), 2);
         }
        }
     }
}

