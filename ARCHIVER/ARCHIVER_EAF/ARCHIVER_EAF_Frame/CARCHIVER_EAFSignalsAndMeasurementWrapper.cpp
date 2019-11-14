 // Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"
#include "iDM_Interface_s.hh"
#include "iEventMessages_s.hh"

#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_DBExc.h"

#include "CIntfData.h"
#include "CSMC_DataProvider_Impl.h"
#include "CSMC_EventLogFrameController.h"
#include "CStirringDataHandler.h"
#include "CStatusHandler.h"
#include "CGasDataHandler.h"

#include "CPDE_CYCL_MEAS_DATA.h"
#include "CPDE_HEAT_DATA.h"
#include "CPD_HEAT_DATA_STIRR.h"
#include "CPDE_HEAT_DATA_INJ.h"
#include "CPDE_HEAT_DATA_BURN.h"
#include "CPDE_HEAT_DATA_MELT.h"

#include "CPDE_CYCL_MEAS_DATA_INJ.h"
#include "CPDE_CYCL_MEAS_DATA_BURN.h"
#include "CPD_ELEC_SYSTEM.h"


#include "DEF_GC_TREATMENTPHASE_DEF.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GCE_BURNER.h"
#include "DEF_GCE_BURNER_GASTYPE.h"
#include "DEF_GC_STIRR_GAS_TYPE.h"
#include "DEF_GC_RECIPE_SOURCE.h"
#include "DEF_GC_RECIPE_STATUS.h"

#include "CARCHIVER_EAFSignalsAndMeasurementWrapper.h"

CARCHIVER_EAFSignalsAndMeasurementWrapper::~CARCHIVER_EAFSignalsAndMeasurementWrapper()
{
  deleteDBClasses(); 
}
CARCHIVER_EAFSignalsAndMeasurementWrapper::CARCHIVER_EAFSignalsAndMeasurementWrapper()
{
}
void CARCHIVER_EAFSignalsAndMeasurementWrapper::deleteDBClasses()
{
  CARCHIVER_SignalsAndMeasurementWrapper::deleteDBClasses();
  if (m_pPD_ELEC_SYSTEM)           {delete m_pPD_ELEC_SYSTEM; m_pPD_ELEC_SYSTEM = 0;}
  if (m_pPDE_CYCL_MEAS_DATA)       {delete m_pPDE_CYCL_MEAS_DATA; m_pPDE_CYCL_MEAS_DATA = 0;}
  if (m_pPDE_HEAT_DATA )           {delete m_pPDE_HEAT_DATA; m_pPDE_HEAT_DATA  = 0;}
  if (m_pPD_HEAT_DATA_STIRR)      {delete m_pPD_HEAT_DATA_STIRR; m_pPD_HEAT_DATA_STIRR =0;}
  if (m_pPDE_CYCL_MEAS_DATA_INJ)   {delete m_pPDE_CYCL_MEAS_DATA_INJ; m_pPDE_CYCL_MEAS_DATA_INJ =0;} 
  if (m_pPDE_CYCL_MEAS_DATA_BURN)  {delete m_pPDE_CYCL_MEAS_DATA_BURN; m_pPDE_CYCL_MEAS_DATA_BURN =0;} 
  if (m_pPDE_HEAT_DATA_INJ)        {delete m_pPDE_HEAT_DATA_INJ; m_pPDE_HEAT_DATA_INJ = 0;}
  if (m_pPDE_HEAT_DATA_BURN)        {delete m_pPDE_HEAT_DATA_BURN; m_pPDE_HEAT_DATA_BURN = 0;}
  if (m_pPDE_HEAT_DATA_MELT)        {delete m_pPDE_HEAT_DATA_MELT; m_pPDE_HEAT_DATA_MELT = 0;}
}
void CARCHIVER_EAFSignalsAndMeasurementWrapper::initDBClasses()
{
  CARCHIVER_SignalsAndMeasurementWrapper::initDBClasses();

  cCBS_StdConnection *pConnection = getStdConnection();

  m_pPD_ELEC_SYSTEM          = new CPD_ELEC_SYSTEM(pConnection);
  m_pPDE_CYCL_MEAS_DATA      = new CPDE_CYCL_MEAS_DATA(pConnection);	
  m_pPDE_HEAT_DATA           = new CPDE_HEAT_DATA(pConnection);		
  m_pPD_HEAT_DATA_STIRR     = new CPD_HEAT_DATA_STIRR(pConnection);
  m_pPDE_CYCL_MEAS_DATA_INJ  = new CPDE_CYCL_MEAS_DATA_INJ(pConnection);
  m_pPDE_CYCL_MEAS_DATA_BURN = new CPDE_CYCL_MEAS_DATA_BURN(pConnection);
  m_pPDE_HEAT_DATA_INJ       = new CPDE_HEAT_DATA_INJ(pConnection);
  m_pPDE_HEAT_DATA_BURN      = new CPDE_HEAT_DATA_BURN(pConnection);
  m_pPDE_HEAT_DATA_MELT      = new CPDE_HEAT_DATA_MELT(pConnection);
}
bool CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnCyclicMeasurement(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnCyclicMeasurement");
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

    // base class methods
    handleCoolingWater(Event);
    handleWasteGas(Event);

    // EAF specific methods
    handleBurner(Event);
    handleInjection(Event);
    handleMatFeeding(Event);
    handleCyclicData(Event);

    RetValue = true;
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
bool CARCHIVER_EAFSignalsAndMeasurementWrapper::handleCyclicData(CEventMessage& Event)
{
  bool RetValue = false;

  std::string HeatID  = Event.getHeatID();
  std::string TreatID = Event.getTreatID();
  std::string PlantID = Event.getPlantID();
  std::string Sender  = Event.getSender();
  std::string DataKey = Event.getDataKey();
  std::string ProductID = Event.getProductID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  CDateTime now;

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_EAFSignalsAndMeasurementWrapper::handleCyclicData");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************


  setpDM_Interface(Sender,DM::PRODUCT);
  double DurSinceHeatAnnounce     = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatAnnounceTime);
  double DurSinceHeatStart        = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatStartTime);
  long ElecPhaseNo                = m_pDM_Interface->getLong(ProductID.c_str(), DATA::ElecPhaseNo);
  double TempAct                  = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::TempAct);

  seqStirringData StirringAmount  = CIntfData::ToCORBAType(m_pDM_Interface->getStirringData(ProductID.c_str(), DATA::StirringAmount));
  seqStirringData StirringFlow    = CIntfData::ToCORBAType(m_pDM_Interface->getStirringData(ProductID.c_str(), DATA::StirringFlow));
  std::string StirringGasType     = CIntfData::ToStdString(m_pDM_Interface->getString(ProductID.c_str(),       DATA::StirringGasType));

  setpDM_Interface(Sender,DM::PLANT);
  seqComputerModes EAFComputerModes = CIntfData::ToCORBAType(m_pDM_Interface->getComputerModes(DEF_PLANT::Furnace, DATA::ComputerModes));    
  long VoltTapNo                    = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::VoltTapNo);
  long PowerOn                      = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::PowerOn);
  long EltrdRegCurve                = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::ElectrodRegCurve);
  long ElecPosUp                    = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::ElecPosUp);
  long FurnBreakOn                  = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::FurnBreakOn);
  long FurnTapChangOn               = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::FurnTapChangOn);
  long RoofPosUp                    = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::RoofPosUp);
  long GantryPosIn                  = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::GantryPosIn);
  long SlagDoorOpen                 = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::SlagDoorOpen);
  long ReactTapNo                   = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::ReactTapNo);
  double ElecCons                   = m_pDM_Interface->getDouble(DEF_PLANT::Furnace, DATA::ElecCons);

  CStirringDataHandler StirringDataHandlerFlow(StirringFlow);
  CStirringDataHandler StirringDataHandlerAmount(StirringAmount);

  // ******************************************************************
  // write data to DB
  // ******************************************************************
  if ( m_pPD_HEAT_DATA->select(HeatID, TreatID, ActPlant) )
  {
    m_pPDE_CYCL_MEAS_DATA->setHEATID(HeatID);
    m_pPDE_CYCL_MEAS_DATA->setTREATID(TreatID);
    m_pPDE_CYCL_MEAS_DATA->setPLANT(ActPlant);
    m_pPDE_CYCL_MEAS_DATA->setREVTIME(now);
    m_pPDE_CYCL_MEAS_DATA->setDURSINCEHEATANNOUNCE(DurSinceHeatAnnounce);
    m_pPDE_CYCL_MEAS_DATA->setDURSINCESTARTOFHEAT(DurSinceHeatStart);
    m_pPDE_CYCL_MEAS_DATA->setELEC_CONS(ElecCons);
    m_pPDE_CYCL_MEAS_DATA->setCURPHASE_L1(ElecPhaseNo);
    m_pPDE_CYCL_MEAS_DATA->setVOLTTAP(VoltTapNo);
    m_pPDE_CYCL_MEAS_DATA->setIMPCURVE(EltrdRegCurve);
    m_pPDE_CYCL_MEAS_DATA->setELECTRODEPOS(ElecPosUp);
    m_pPDE_CYCL_MEAS_DATA->setFURNACEBREAKERSTATUS(FurnBreakOn);
    m_pPDE_CYCL_MEAS_DATA->setTAPCHANGERSTATUS(FurnTapChangOn);
    m_pPDE_CYCL_MEAS_DATA->setPOWERSTATUS(PowerOn);
    m_pPDE_CYCL_MEAS_DATA->setROOFPOS(RoofPosUp);
    m_pPDE_CYCL_MEAS_DATA->setGANTRYPOS(GantryPosIn);
    m_pPDE_CYCL_MEAS_DATA->setSLAGDOORPOSITION(SlagDoorOpen);
    //m_pPDE_CYCL_MEAS_DATA->setSTIRRGASTYPE(StirringGasType);
    m_pPDE_CYCL_MEAS_DATA->setREACTORTAP(ReactTapNo);
    m_pPDE_CYCL_MEAS_DATA->setTEMP_ACT(TempAct);
    

		//SARS
    double STIRR_N2_FLOW = StirringDataHandlerFlow.getAccumulatedGasValue(DEF_GAS::N2);
    double STIRR_N2_CONS = StirringDataHandlerAmount.getAccumulatedGasValue(DEF_GAS::N2);
    m_pPDE_CYCL_MEAS_DATA->setSTIRR_N2_FLOW(STIRR_N2_FLOW);
    m_pPDE_CYCL_MEAS_DATA->setSTIRR_N2_CONS(STIRR_N2_CONS);

    double STIRR_AR_FLOW = StirringDataHandlerFlow.getAccumulatedGasValue(DEF_GAS::Ar);
    double STIRR_AR_CONS = StirringDataHandlerAmount.getAccumulatedGasValue(DEF_GAS::Ar);
    m_pPDE_CYCL_MEAS_DATA->setSTIRR_AR_FLOW(STIRR_AR_FLOW);
    m_pPDE_CYCL_MEAS_DATA->setSTIRR_AR_CONS(STIRR_AR_CONS);

    if ( STIRR_N2_FLOW != DEF::Inv_Double && STIRR_N2_CONS != DEF::Inv_Double)
    {
      m_pPDE_CYCL_MEAS_DATA->setSTIRRGASTYPE(DEF_GAS::N2);
    }

    if ( STIRR_AR_FLOW != DEF::Inv_Double && STIRR_AR_CONS != DEF::Inv_Double)
    {
      m_pPDE_CYCL_MEAS_DATA->setSTIRRGASTYPE(DEF_GAS::Ar);
    }

		//SARS
    /*if (StirringGasType == DEF_GC_STIRR_GAS_TYPE::Ar) 
    {
      m_pPDE_CYCL_MEAS_DATA->setSTIRR_AR_FLOW(StirringDataHandlerFlow.getAccumulatedGasValue(DEF_GAS::Ar));
      //m_pPDE_CYCL_MEAS_DATA->setSTIRR_AR_CONS(StirringDataHandlerAmount.getAccumulatedGasValue(DEF_GAS::Ar));
    }
    if (StirringGasType == DEF_GC_STIRR_GAS_TYPE::N2) 
    {
      m_pPDE_CYCL_MEAS_DATA->setSTIRR_N2_FLOW(StirringDataHandlerFlow.getAccumulatedGasValue(DEF_GAS::N2));
      //m_pPDE_CYCL_MEAS_DATA->setSTIRR_N2_CONS(StirringDataHandlerAmount.getAccumulatedGasValue(DEF_GAS::N2));
    }*/

    for ( long i = 0 ; i < CIntfData::getLength(EAFComputerModes) ; ++i)
    {
      sComputerMode ComputerMode;
      CIntfData::getAt(ComputerMode, EAFComputerModes, i);

      std::string Device = ComputerMode.Device;

      if ( Device == DEF_COMP_MODES::MatHandle)
      {
        m_pPDE_CYCL_MEAS_DATA->setCOMPMODE_MAT(ComputerMode.Status);
      }
      else if (Device == DEF_COMP_MODES::GasLance)
      {
        m_pPDE_CYCL_MEAS_DATA->setCOMPMODE_BURNER(ComputerMode.Status);
      }
      else if (Device == DEF_COMP_MODES::Injection)
      {
        m_pPDE_CYCL_MEAS_DATA->setCOMPMODE_INJ(ComputerMode.Status);
      }
      else if (Device == DEF_COMP_MODES::Electric)
      {
        m_pPDE_CYCL_MEAS_DATA->setCOMPMODE_ELEC(ComputerMode.Status);
      }
      else if (Device == DEF_COMP_MODES::Stirring)
      {
        m_pPDE_CYCL_MEAS_DATA->setCOMPMODE_ELEC(ComputerMode.Status);
      }
    }

    if(m_pPDE_CYCL_MEAS_DATA->insert())
    {
      m_pPDE_CYCL_MEAS_DATA->commit();
      RetValue = true;
    }
    else
    {
      m_pPDE_CYCL_MEAS_DATA->rollback();

      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PDE_CYCL_MEAS_DATA", Scope.c_str());

    }
  }
  else
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadError(sMessage, "", "PP_HEAT_PLANT", Scope.c_str());
  }

  return RetValue;
}
bool CARCHIVER_EAFSignalsAndMeasurementWrapper::handleInjection(CEventMessage& Event)
{
  bool RetValue = false;

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string Sender    = Event.getSender();
  std::string DataKey   = Event.getDataKey();
  std::string ProductID = Event.getProductID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);

  std::string Scope("CARCHIVER_EAFSignalsAndMeasurementWrapper::handleInjection");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;

  setpDM_Interface(Sender,DM::PRODUCT);
  double DurSinceHeatAnnounce           = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatAnnounceTime);
  double DurSinceHeatStart              = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatStartTime);
  double ElecCons                       = m_pDM_Interface->getDouble(       ProductID.c_str(), DATA::ElecCons);

  seqInjectLanceData InjectLanceAmount  = CIntfData::ToCORBAType(m_pDM_Interface->getInjectLanceData(ProductID.c_str(), DATA::InjectLanceAmount));
  seqInjectLanceData InjectLanceFlow    = CIntfData::ToCORBAType(m_pDM_Interface->getInjectLanceData(ProductID.c_str(), DATA::InjectLanceFlow));
  seqStatus InjectorStatus              = CIntfData::ToCORBAType(m_pDM_Interface->getStatus         (ProductID.c_str(), DATA::InjectorStatus));
  
  InjLanceWrite(HeatID, TreatID, ActPlant, DurSinceHeatAnnounce, DurSinceHeatStart, ElecCons, 
                InjectorStatus, InjectLanceAmount, InjectLanceFlow);

  return RetValue;
}
bool CARCHIVER_EAFSignalsAndMeasurementWrapper::handleBurner(CEventMessage& Event)
{
  bool RetValue = false;

  std::string HeatID  = Event.getHeatID();
  std::string TreatID = Event.getTreatID();
  std::string PlantID = Event.getPlantID();
  std::string Sender  = Event.getSender();
  std::string DataKey = Event.getDataKey();
  std::string ProductID = Event.getProductID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);

  std::string Scope("CARCHIVER_EAFSignalsAndMeasurementWrapper::handleBurner");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;

  setpDM_Interface(Sender,DM::PRODUCT);
  double DurSinceHeatAnnounce       = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatAnnounceTime);
  double DurSinceHeatStart          = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatStartTime);
  double ElecCons                   = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::ElecCons);

  seqStatus seqBurnerStatus         = CIntfData::ToCORBAType(m_pDM_Interface->getStatus(ProductID.c_str(), DATA::BurnerStatus));
  seqGasLanceData SeqBurnerFlow     = CIntfData::ToCORBAType(m_pDM_Interface->getGasLanceData(ProductID.c_str(), DATA::BurnerFlow));
  seqGasLanceData SeqBurnerAmount   = CIntfData::ToCORBAType(m_pDM_Interface->getGasLanceData(ProductID.c_str(), DATA::BurnerAmount));

  seqStatus seqGasLanceStatus       = CIntfData::ToCORBAType(m_pDM_Interface->getStatus(ProductID.c_str(), DATA::GasLanceStatus));
  seqGasLanceData SeqGasLanceAmount = CIntfData::ToCORBAType(m_pDM_Interface->getGasLanceData(ProductID.c_str(), DATA::GasLanceAmount));
  seqGasLanceData SeqGasLanceFlow   = CIntfData::ToCORBAType(m_pDM_Interface->getGasLanceData(ProductID.c_str(), DATA::GasLanceFlow));

  seqGasLanceGasAvail  EAFBurnerAvail;

  BurnerWrite(HeatID, TreatID, ActPlant, DurSinceHeatAnnounce, DurSinceHeatStart, ElecCons, 
              seqBurnerStatus, seqGasLanceStatus, EAFBurnerAvail, SeqBurnerFlow, SeqBurnerAmount, SeqGasLanceFlow, SeqGasLanceAmount);


  return RetValue;
}
bool CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnStirrStatusData(CEventMessage& Event, long status)
{
  bool RetValue = false;

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string Sender    = Event.getSender();
  std::string DataKey   = Event.getDataKey();
  std::string ProductID = Event.getProductID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  CDateTime Now;

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnStirrStatusData");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************

  // last known flow is stored at product interface
  setpDM_Interface(Sender,DM::PRODUCT);
  seqStirringData StirringFlow    = CIntfData::ToCORBAType(m_pDM_Interface->getStirringData(ProductID.c_str(), DATA::StirringFlow));
  seqStatus       StirringStatus  = CIntfData::ToCORBAType(m_pDM_Interface->getStatus      (ProductID.c_str(), DATA::StirringStatus));
  seqStirringData StirringAmount  = CIntfData::ToCORBAType(m_pDM_Interface->getStirringData(ProductID.c_str(), DATA::StirringAmount));

  

  // extract data from sequences
  CStirringDataHandler StirringDataHandlerFlow(StirringFlow);
  CStirringDataHandler StirringDataHandlerAmount(StirringAmount);
  
  for ( long i = 0 ; i < CIntfData::getLength(StirringAmount); ++i )
  {
    sStirringData StirringData;
    CIntfData::getAt(StirringData,StirringAmount,i);

    std::string Device      = StirringData.Device;
    seqGasData SeqGasData   = StirringData.GasData;

    // check state of StirringStatus with event related state
    // stirring start and respective device is swiched ON
    if ( status == DEF_GEN_STATES::On && status == CStatusHandler::getDeviceStatus(StirringStatus, Device, DEF_STATUS_NAME::Stirring) )
    {
      for ( long j = 0; j < CIntfData::getLength(SeqGasData); ++j )
      {
        sGasData GasData;
        CIntfData::getAt(GasData,SeqGasData,j);

        std::string GasType = GasData.GasType;
        double Stirr_Cons   = GasData.GasValue;
        double Stirr_Flow   = StirringDataHandlerFlow.getGasValue(Device,GasType); 

        m_pPD_HEAT_DATA_STIRR->setHEATID(HeatID);
        m_pPD_HEAT_DATA_STIRR->setTREATID(TreatID);
        m_pPD_HEAT_DATA_STIRR->setPLANT(ActPlant);
        m_pPD_HEAT_DATA_STIRR->setDEVICENAME(Device);
        m_pPD_HEAT_DATA_STIRR->setSTIRRGASTYPE(GasType);
        m_pPD_HEAT_DATA_STIRR->setSTARTTIME(Now);

        m_pPD_HEAT_DATA_STIRR->setIS_BYPASS (0); // not used at EAF, but needed

//        m_pPD_HEAT_DATA_STIRR->setFLOW(Stirr_Flow);
        m_pPD_HEAT_DATA_STIRR->setCONS(Stirr_Cons);

        RetValue = m_pPD_HEAT_DATA_STIRR->insert();
        if ( !RetValue )
        {
          break;
        }
      } // for ( long j = 0; j < CIntfData::getLength(SeqGasData); ++j )
    } // if ( status == DEF_GEN_STATES::On && status == CStatusHandler::getDeviceStatus(StirringStatus,Device) )

    // stirring stop and respective device is swiched OFF
    if ( status == DEF_GEN_STATES::Off && status == CStatusHandler::getDeviceStatus(StirringStatus, Device, DEF_STATUS_NAME::Stirring) )
    {
      for ( long j = 0; j < CIntfData::getLength(SeqGasData); ++j )
      {
        sGasData GasData;
        CIntfData::getAt(GasData,SeqGasData,j);

        std::string GasType     = GasData.GasType;
        double Stirr_Cons       = GasData.GasValue;
        double Stirr_Flow       = StirringDataHandlerFlow.getGasValue(Device,GasType); 
        long TreatmentPosition  = 1; // SARS 2; // tap Ladle
        long isBypass           = 0; 

        if ( m_pPD_HEAT_DATA_STIRR->selectActual(HeatID, TreatID, ActPlant, TreatmentPosition, Device, isBypass, GasType) )
        {
          m_pPD_HEAT_DATA_STIRR->setENDTIME(Now); //SARS

//          m_pPD_HEAT_DATA_STIRR->setFLOW(Stirr_Flow);
          m_pPD_HEAT_DATA_STIRR->setCONS(Stirr_Cons);
        }

        RetValue = m_pPD_HEAT_DATA_STIRR->update();
        if ( !RetValue )
        {
          break;
        }
      } // for ( long j = 0; j < CIntfData::getLength(SeqGasData); ++j )
    } // if ( status == DEF_GEN_STATES::On && status == CStatusHandler::getDeviceStatus(StirringStatus,Device) )


    if (RetValue)
    {
      m_pPD_HEAT_DATA_STIRR->commit();
    }
    else
    {
      m_pPD_HEAT_DATA_STIRR->rollback();

      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PD_HEAT_DATA_STIRR", Scope.c_str());
    }
  } // for ( long i = 0 ; i < CIntfData::getLength(StirringAmount); ++i )

  return RetValue;
}
bool CARCHIVER_EAFSignalsAndMeasurementWrapper::handleMatFeeding(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string Sender    = Event.getSender();
  std::string DataKey   = Event.getDataKey();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_EAFSignalsAndMeasurementWrapper::handleMatFeeding");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************


  CDateTime now;

  setpDM_Interface(Sender,DM::PRODUCT);
  seqBatch SeqMatFeedingData  = CIntfData::ToCORBAType(m_pDM_Interface->getBatch(ProductID.c_str(), DATA::MatFeedingData));
  double MomentElec           = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::ElecCons); 
  double MomentO2             = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::MomentO2);
  double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatAnnounceTime);
  double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatStartTime);

  if ( m_pPD_MAT_FEED_CYCL_MEAS_DATA && m_pPD_RECIPE )
  {
    if ( CIntfData::getLength(SeqMatFeedingData) > 0 )
    {
      if( m_pPD_MAT_FEED_CYCL_MEAS_DATA->writeBatch(HeatID, TreatID, ActPlant, SeqMatFeedingData, MomentElec, MomentO2, DurSinceHeatAnnounce, false ) )
      {
        // prepare data for PD_RECIPE
        sRecipeInfo RecipeInfoDischargeStart;
        RecipeInfoDischargeStart.RecipeName    = "DynamicFeeding";
        RecipeInfoDischargeStart.RecipeSource  = DEF_GC_RECIPE_SOURCE::Bin;
        RecipeInfoDischargeStart.RecipeStatus  = DEF_GC_RECIPE_STATUS::DischargeStart;
        RecipeInfoDischargeStart.DurSinceHeatAnnounce  = DurSinceHeatAnnounce;
        RecipeInfoDischargeStart.DurSinceHeatStart     = DurSinceHeatStart;
        RecipeInfoDischargeStart.RecipeNo      = 1;
        RecipeInfoDischargeStart.RecipeTarget  = "Furnace";

        // prepare data for PD_RECIPE
        sRecipeInfo RecipeInfoDischarged;
        RecipeInfoDischarged.RecipeName    = "DynamicFeeding";
        RecipeInfoDischarged.RecipeSource  = DEF_GC_RECIPE_SOURCE::Bin;
        RecipeInfoDischarged.RecipeStatus  = DEF_GC_RECIPE_STATUS::Discharged;
        RecipeInfoDischarged.DurSinceHeatAnnounce  = DurSinceHeatAnnounce;
        RecipeInfoDischarged.DurSinceHeatStart     = DurSinceHeatStart;
        RecipeInfoDischarged.RecipeNo      = 1;
        RecipeInfoDischarged.RecipeTarget  = "Furnace";

        sMetTimeStamp TimeStamp;
        TimeStamp.DurSinceHeatAnnouncement = DurSinceHeatAnnounce;
        TimeStamp.DurSinceStartOfHeat      = DurSinceHeatStart;
        TimeStamp.O2_Moment   = MomentO2;
        TimeStamp.Ar_Moment   = DEF::Inv_Double;
        TimeStamp.N2_Moment   = DEF::Inv_Double;
        TimeStamp.Elec_Moment = MomentElec;

        // using only valid materials with mass > 0
        seqBatch SeqBatch;

        for(long i= 0; i < CIntfData::getLength(SeqMatFeedingData); ++i)
        {
          sBatch NewBatch;
          CIntfData::getAt(NewBatch,SeqMatFeedingData,i);

          if ( string(NewBatch.MatCode) != string(DEF::Inv_String) && !string(NewBatch.MatCode).empty() )
          {
            CSMC_DataProvider_Impl::addBatch(SeqBatch, NewBatch);
          }
        }

        if ( CIntfData::getLength(SeqBatch) != 0)
        {
          if ( !m_pPD_RECIPE->select(HeatID, TreatID, ActPlant, RecipeInfoDischargeStart.RecipeName, RecipeInfoDischargeStart.RecipeNo, RecipeInfoDischargeStart.RecipeSource, RecipeInfoDischargeStart.RecipeStatus) )
          {
            RetValue = m_pPD_RECIPE->writeBatch(HeatID, TreatID, ActPlant, RecipeInfoDischargeStart, TimeStamp, SeqBatch, false, m_lastError);
          }
          else
          {
            RetValue = m_pPD_RECIPE->writeBatch(HeatID, TreatID, ActPlant, RecipeInfoDischarged, TimeStamp, SeqBatch, false, m_lastError);
          }

          if(RetValue)
          {
            m_pPD_RECIPE->commit();
          }
          else
          {
            m_pPD_RECIPE->rollback();

            cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PD_RECIPE", Scope.c_str());
          }
        }// if ( CIntfData::getLength(SeqBatch) != 0)
      }// if( m_pPD_MAT_FEED_CYCL_MEAS_DATA->writeBatch(HeatID, TreatID, ActPlant, SeqMatFeedingData, MomentElec, MomentO2, DurSinceHeatAnnounce, false ) )
      else
      {
        m_pPD_RECIPE->rollback();

        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PD_MAT_FEED_CYCL_MEAS_DATA", Scope.c_str());

      }
    }
    else
    {
      log(Scope + " SeqMatFeedingData empty",2);
    }
  }
  else
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"m_pPD_MAT_FEED_CYCL_MEAS_DATA or m_pPD_RECIPE undefined",Scope.c_str(),"");
    RetValue = false;
  }
  return RetValue;
}
bool CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnDeslagging(CEventMessage& Event, long status)
{
  return handleDeslagging(Event, status);
}
bool CARCHIVER_EAFSignalsAndMeasurementWrapper::InjLanceWrite(const std::string& HeatID, const std::string& TreatID, const std::string& Plant, 
                                                              double durSinceHeatAnnouncement, double durSinceStartOfHeat, double ElecCons, 
                                                              const seqStatus &  InjectorStatus, const seqInjectLanceData & InjectLanceAmount, const seqInjectLanceData & InjectLanceFlow )
{
  bool RetValue = false;

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_EAFSignalsAndMeasurementWrapper::InjLanceWrite");
  std::stringstream ExceptionMsg;
  //***********************************************************************************

  try
  {
    CDateTime now;
    long seqLenght = CIntfData::getLength(InjectLanceAmount);

    if(seqLenght < 1)
    {
      return true;
    }

    //InjectLanceMat,InjectLanceFlow,InjectLanceAmount should have the same length
    //If they are not, then follow the InjectLanceMat length
    for (int i = 0 ; i < seqLenght ; ++i)
    {
      sInjectLanceData InjectLanceDataAmount;
      CIntfData::getAt(InjectLanceDataAmount,&InjectLanceAmount,i);

      std::string MatCode = (std::string)InjectLanceDataAmount.MatCode;

      if ( MatCode != DEF::Inv_String && !MatCode.empty() )
      {
        m_pPDE_CYCL_MEAS_DATA_INJ->setINJ_MAT(MatCode);

        m_pPDE_CYCL_MEAS_DATA_INJ->setHEATID(HeatID);
        m_pPDE_CYCL_MEAS_DATA_INJ->setTREATID(TreatID);
        m_pPDE_CYCL_MEAS_DATA_INJ->setPLANT(Plant);
        m_pPDE_CYCL_MEAS_DATA_INJ->setREVTIME(now);
        m_pPDE_CYCL_MEAS_DATA_INJ->setDEVICENAME((std::string)InjectLanceDataAmount.Device);
        m_pPDE_CYCL_MEAS_DATA_INJ->setDURSINCEHEATANNOUNCE(durSinceHeatAnnouncement);
        m_pPDE_CYCL_MEAS_DATA_INJ->setDURSINCESTARTOFHEAT(durSinceStartOfHeat);
        m_pPDE_CYCL_MEAS_DATA_INJ->setELEC_CONS(ElecCons);

        m_pPDE_CYCL_MEAS_DATA_INJ->setINJ_AMOUNT(InjectLanceDataAmount.Value);

        sInjectLanceData InjectLanceDataFlow ;
        CIntfData::getAt(InjectLanceDataFlow,&InjectLanceFlow,i);
        m_pPDE_CYCL_MEAS_DATA_INJ->setINJ_FLOW(InjectLanceDataFlow.Value);

        sStatus Status;
        if ( CIntfData::getAt(Status,&InjectorStatus,i) )
        {
          m_pPDE_CYCL_MEAS_DATA_INJ->setSTATUS(Status.Status);
        }

        RetValue = m_pPDE_CYCL_MEAS_DATA_INJ->insert();

        if (RetValue)
        {
          m_pPDE_CYCL_MEAS_DATA_INJ->commit();
        }
        else
        {
          m_pPDE_CYCL_MEAS_DATA_INJ->rollback();

          std::string Msg = HeatID + " - " + TreatID + " - " + MatCode;
          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_DBWriteError(sMessage,Msg.c_str(),"PDE_CYCL_MEAS_DATA_INJ", Scope.c_str());
        }
      }// if ( MatCode != DEF::Inv_String && !MatCode.empty() )
    }
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

bool CARCHIVER_EAFSignalsAndMeasurementWrapper::BurnerWrite(const std::string& HeatID, const std::string& TreatID, const std::string& PlantID, 
                                                            double durSinceHeatAnnouncement,  double durSinceStartOfHeat,   double ElecCons, 
                                                            seqStatus & seqBurnerStatus,  seqStatus & seqGasLanceStatus, const seqGasLanceGasAvail & EAFBurnerAvail,   
                                                            const seqGasLanceData & seqBurnerFlow,   const seqGasLanceData & seqBurnerAmount,
                                                            const seqGasLanceData & seqGasLanceFlow,   const seqGasLanceData & seqGasLanceAmount )
{
  bool RetValue = true;
  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_EAFSignalsAndMeasurementWrapper::BurnerWrite");
  std::stringstream ExceptionMsg;
  //***********************************************************************************

  try
  {
    CDateTime now;

    for (long i = 0; i < CIntfData::getLength(seqGasLanceFlow); i++) //SARS: replace by seqBurnerFlow
    {
      RetValue = false;

      sGasLanceData GasLanceData;
      CIntfData::getAt(GasLanceData,seqGasLanceFlow,i);

      std::string DeviceName = GasLanceData.Device;

      m_pPDE_CYCL_MEAS_DATA_BURN->setHEATID(HeatID);
      m_pPDE_CYCL_MEAS_DATA_BURN->setTREATID(TreatID);
      m_pPDE_CYCL_MEAS_DATA_BURN->setPLANT(PlantID);
      m_pPDE_CYCL_MEAS_DATA_BURN->setREVTIME(now);
      m_pPDE_CYCL_MEAS_DATA_BURN->setBURNERNAME(DeviceName);
      m_pPDE_CYCL_MEAS_DATA_BURN->setDURSINCEHEATANNOUNCE(durSinceHeatAnnouncement);
      m_pPDE_CYCL_MEAS_DATA_BURN->setDURSINCESTARTOFHEAT(durSinceStartOfHeat);
      m_pPDE_CYCL_MEAS_DATA_BURN->setELEC_CONS(ElecCons);

      for(int j = 0; j < CIntfData::getLength(seqBurnerStatus); j++)
      {
        sStatus BurnerStatus;
        CIntfData::getAt(BurnerStatus,seqBurnerStatus,j);

        if( DeviceName == (std::string)BurnerStatus.Device )
        {
          m_pPDE_CYCL_MEAS_DATA_BURN->setSTATUS(BurnerStatus.Status);
        }
      }

      for (long k = 0; k < CIntfData::getLength(GasLanceData.LanceData); k++)
      {
        sGasData GasData;
        CIntfData::getAt(GasData,GasLanceData.LanceData,k);

        std::string GasType     = GasData.GasType;
        double      GasValue    = GasData.GasValue;

        if (GasType == DEF_GCE_BURNER_GASTYPE::O2)
        {
          RetValue = true;
          m_pPDE_CYCL_MEAS_DATA_BURN->setO2_FLOW(GasValue );
        }
        else if(GasType == DEF_GCE_BURNER_GASTYPE::BG)
        {
          RetValue = true;
          m_pPDE_CYCL_MEAS_DATA_BURN->setGAS_FLOW(GasValue);       
        }
      }

      // iterate over EAFBurnerAmount and look for DeviceName
      for (long l = 0; l < CIntfData::getLength(seqGasLanceAmount); l++) //SARS replace by seqBurnerAmount
      {
        sGasLanceData GasLanceData;
        CIntfData::getAt(GasLanceData,seqGasLanceAmount,l);

        if( RetValue && DeviceName == (std::string)GasLanceData.Device )
        {
          for (long m = 0; m < CIntfData::getLength(GasLanceData.LanceData); m++)
          {
            sGasData GasData;
            CIntfData::getAt(GasData,GasLanceData.LanceData,m);
            std::string GasType     = GasData.GasType;
            double      GasValue    = GasData.GasValue;
            
            if (GasType == DEF_GCE_BURNER_GASTYPE::O2)
            {
              m_pPDE_CYCL_MEAS_DATA_BURN->setO2_AMOUNT(GasValue );
            }
            else if(GasType == DEF_GCE_BURNER_GASTYPE::BG)
            {
              m_pPDE_CYCL_MEAS_DATA_BURN->setGAS_AMOUNT(GasValue); 
            }
          }
        }
      }
      if (m_pPDE_CYCL_MEAS_DATA_BURN->insert())
      {
        m_pPDE_CYCL_MEAS_DATA_BURN->commit();
        RetValue = true;
      }
      else
      {
        m_pPDE_CYCL_MEAS_DATA_BURN->rollback();

        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PDE_CYCL_MEAS_DATA_BURN", Scope.c_str());
      }
    }// for (long i = 0; i < CIntfData::getLength(seqBurnerFlow); i++)

    // ------------------------------------------------------------------------


		//SARS
    /*for (long i = 0; i < CIntfData::getLength(seqGasLanceFlow); i++)
    {
      RetValue = false;

      sGasLanceData GasLanceData;
      CIntfData::getAt(GasLanceData,seqGasLanceFlow,i);

      std::string DeviceName = GasLanceData.Device;

      m_pPDE_CYCL_MEAS_DATA_BURN->setHEATID(HeatID);
      m_pPDE_CYCL_MEAS_DATA_BURN->setTREATID(TreatID);
      m_pPDE_CYCL_MEAS_DATA_BURN->setPLANT(PlantID);
      m_pPDE_CYCL_MEAS_DATA_BURN->setREVTIME(now);
      m_pPDE_CYCL_MEAS_DATA_BURN->setBURNERNAME(DeviceName);
      m_pPDE_CYCL_MEAS_DATA_BURN->setDURSINCEHEATANNOUNCE(durSinceHeatAnnouncement);
      m_pPDE_CYCL_MEAS_DATA_BURN->setDURSINCESTARTOFHEAT(durSinceStartOfHeat);
      m_pPDE_CYCL_MEAS_DATA_BURN->setELEC_CONS(ElecCons);

      for(int j = 0; j < CIntfData::getLength(seqGasLanceStatus); j++)
      {
        sStatus GasLanceStatus;
        CIntfData::getAt(GasLanceStatus,seqGasLanceStatus,j);

        if( DeviceName == (std::string)GasLanceStatus.Device )
        {
          m_pPDE_CYCL_MEAS_DATA_BURN->setSTATUS(GasLanceStatus.Status);
        }
      }

      for (long k = 0; k < CIntfData::getLength(GasLanceData.LanceData); k++)
      {
        sGasData GasData;
        CIntfData::getAt(GasData,GasLanceData.LanceData,k);

        std::string GasType     = GasData.GasType;
        double      GasValue    = GasData.GasValue;

        if (GasType == DEF_GCE_BURNER_GASTYPE::O2)
        {
          RetValue = true;
          m_pPDE_CYCL_MEAS_DATA_BURN->setO2_FLOW(GasValue );
        }
        else if(GasType == DEF_GCE_BURNER_GASTYPE::BG)
        {
          RetValue = true;
          m_pPDE_CYCL_MEAS_DATA_BURN->setGAS_FLOW(0.);       
        }
      }

      // iterate over EAFBurnerAmount and look for DeviceName
      for (long l = 0; l < CIntfData::getLength(seqGasLanceAmount); l++)
      {
        sGasLanceData GasLanceData;
        CIntfData::getAt(GasLanceData,seqGasLanceAmount,l);

        if( RetValue && DeviceName == (std::string)GasLanceData.Device )
        {
          for (long m = 0; m < CIntfData::getLength(GasLanceData.LanceData); m++)
          {
            sGasData GasData;
            CIntfData::getAt(GasData,GasLanceData.LanceData,m);
            std::string GasType     = GasData.GasType;
            double      GasValue    = GasData.GasValue;

            if (GasType == DEF_GCE_BURNER_GASTYPE::O2)
            {
              m_pPDE_CYCL_MEAS_DATA_BURN->setO2_AMOUNT(GasValue );
            }
            else if(GasType == DEF_GCE_BURNER_GASTYPE::BG)
            {
              RetValue = true;
              m_pPDE_CYCL_MEAS_DATA_BURN->setGAS_FLOW(0.);       
            }
          }
        }
      }
      if (m_pPDE_CYCL_MEAS_DATA_BURN->insert())
      {
        m_pPDE_CYCL_MEAS_DATA_BURN->commit();
        RetValue = true;
      }
      else
      {
        m_pPDE_CYCL_MEAS_DATA_BURN->rollback();

        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PDE_CYCL_MEAS_DATA_BURN", Scope.c_str());
      }
    }*/
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
bool CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnTempMeasurement(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string OrderID   = Event.getOrderID();
  std::string Sender    = Event.getSender();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnTempMeasurement");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************

  setpDM_Interface(Sender,DM::PRODUCT);
  long TreatmentPosition = m_pDM_Interface->getLong(ProductID.c_str(), DATA::TreatmentPosition);

  try
  {
    if (! checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }

    RetValue = handleTempOxyMeasurement(Event, TreatmentPosition);

    if(RetValue)
    {
      setpDM_Interface(Event.getSender(),DM::EVENT);

      double MeasTemp  = m_pDM_Interface->getDouble(DataKey.c_str(), DATA::MeasTemp);

      CDateTime Now;

      RetValue = m_pPD_PLANTSTATUS->updateTempTaken(ActPlant, ActPlantNo, MeasTemp, Now, 1 , true , m_lastError);

    }
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
bool CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnElectrodesInOperatingPosition(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnElectrodesInOperatingPosition");
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

    setpDM_Interface(Event.getSender(),DM::EVENT);
    long ElecPosUp = m_pDM_Interface->getLong(DataKey.c_str(), DATA::ElecPosUp);    

    setpDM_Interface(Event.getSender(),DM::PLANT);
    double ElecCons     = m_pDM_Interface->getDouble(DEF_PLANT::Furnace, DATA::ElecCons);

    RetValue = handleElectrodesInOperatingPosition(Event,ElecCons,ElecPosUp);
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
bool CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnFurnaceBreaker(CEventMessage& Event, long status)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string OrderID   = Event.getOrderID();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnFurnaceBreaker");
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

    setpDM_Interface(Event.getSender(),DM::PLANT);
    double ElecCons       = m_pDM_Interface->getDouble(DEF_PLANT::Furnace, DATA::ElecCons);

    //set new duration, electric energy info to PD_Elec_System;change heat status
    RetValue = handleFurnaceBreaker(Event,status);

    //energy, melting start/end time
    CDateTime   now;

    if( m_pPDE_HEAT_DATA->select(HeatID,TreatID,ActPlant) )
    {
      if(status == DEF_GEN_STATES::On)
      {
        if ( m_pPDE_HEAT_DATA->getMELTDOWNSTARTTIME(1) == CSMC_DBData::unspecDate )
        {
          m_pPDE_HEAT_DATA->setMELTDOWNSTARTTIME(now);
        }
      }
      else if (status == DEF_GEN_STATES::Off)
      {    
        m_pPDE_HEAT_DATA->setMELTDOWNENDTIME(now);
      }

      if ( m_pPDE_HEAT_DATA->getTOTAL_ELEC_EGY(1) > ElecCons )
      {
        ElecCons = m_pPDE_HEAT_DATA->getTOTAL_ELEC_EGY(1);
      }

      m_pPDE_HEAT_DATA->setTOTAL_ELEC_EGY(ElecCons);

      RetValue =  RetValue && m_pPDE_HEAT_DATA->update();

      if(RetValue)
      {
        m_pPDE_HEAT_DATA->commit();
      }
      else
      {
        m_pPDE_HEAT_DATA->rollback();

        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PDE_HEAT_DATA", Scope.c_str());
      }
    }
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
bool CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnPower(CEventMessage& Event, long status)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnPower");
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

    CDateTime Now;

    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    CDateTime HeatAnnounceTime         ( m_pDM_Interface->getDate  (ProductID.c_str(), DATA::HeatAnnounceTime));
    double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatAnnounceTime);
    double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatStartTime);

    double ElecCons             = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::ElecCons);
    std::string PhaseAct        = m_pDM_Interface->getString(ProductID.c_str(), DATA::PhaseTracker);
    long PhaseNoAct             = m_pDM_Interface->getLong(ProductID.c_str(),   DATA::PhaseNoTracker);

    /********************************************************/

    // check and convert data 
    PhaseAct = CDataConversion::SetInvalidToDefault(PhaseAct,DEF_GC_TREATMENTPHASE_DEF::Preparation);

    std::string Phase = PhaseAct;

    if ( PhaseNoAct > 0 )
    {
      Phase += " " + CDataConversion::LongToString(PhaseNoAct); 
    }

    if ( m_pPDE_HEAT_DATA_MELT )
    {
      if ( status == DEF_GEN_STATES::On )
      {
        m_pPDE_HEAT_DATA_MELT->writeDataOnPhaseStart(HeatID, TreatID, ActPlant, Phase, ElecCons);
      }
      else if ( status == DEF_GEN_STATES::Off )
      {
        m_pPDE_HEAT_DATA_MELT->writeDataOnPhaseEnd(HeatID, TreatID, ActPlant, CSMC_DBData::unspecString, ElecCons);
      }
    }

    // get power-on time and calculate power-off time
    double PowerOnDur   = max( m_pPDE_HEAT_DATA_MELT->getPowerOnDur(HeatID, TreatID, ActPlant, HeatAnnounceTime, Now), 0.0 );
    double PowerOffDur  = max( m_pPDE_HEAT_DATA_MELT->getPowerOffDur(HeatID, TreatID, ActPlant, HeatAnnounceTime, Now), 0.0);

    //for insert PowerOffDur and PowerOnDur in table PDE_HEAT_DATA
    if (m_pPDE_HEAT_DATA && m_pPDE_HEAT_DATA->select(HeatID, TreatID, ActPlant))
    {
      m_pPDE_HEAT_DATA->setPOWER_ON_DUR(PowerOnDur);
      m_pPDE_HEAT_DATA->setPOWER_OFF_DUR(PowerOffDur);

      if ( m_pPDE_HEAT_DATA->getTOTAL_ELEC_EGY(1) > ElecCons )
      {
        ElecCons = m_pPDE_HEAT_DATA->getTOTAL_ELEC_EGY(1);
      }

      m_pPDE_HEAT_DATA->setTOTAL_ELEC_EGY(ElecCons);

      if (m_pPDE_HEAT_DATA->update())
      {
        RetValue = true;
        m_pPDE_HEAT_DATA->commit();
      }
      else
      {
        m_pPDE_HEAT_DATA->rollback();

        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PDE_HEAT_DATA", Scope.c_str());
      }
    }

    //set new duration, electric energy info to PD_ELEC_SYSTEM
    RetValue = handlePower(Event,status,ElecCons);
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
bool CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnTapChange(CEventMessage& Event, long TapChangStatus)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_GENSignalsAndMeasurementWrapper::doOnTapChange");
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

    //set new voltap, impcurve, duration and eletric energy info to PD_Elec_Tapch
    RetValue =  handleTapChange(Event, TapChangStatus);

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
bool CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnManipInjectLanceStart(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();  
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnManipInjectLanceStart");
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

    std::string Sender = Event.getSender();
    setpDM_Interface(Sender,DM::PRODUCT);
    seqInjectLanceData InjectLanceAmount = CIntfData::ToCORBAType(m_pDM_Interface->getInjectLanceData(ProductID.c_str(), DATA::InjectLanceAmount));

    for ( int i = 0; i < CIntfData::getLength(InjectLanceAmount); i ++)
    {
      CDateTime Now;

      sInjectLanceData InjectLanceData;
      CIntfData::getAt(InjectLanceData,InjectLanceAmount,i);

      std::string MatCode = (std::string)InjectLanceData.MatCode;

      if ( MatCode != DEF::Inv_String && !MatCode.empty() )
      {
        m_pPDE_HEAT_DATA_INJ->setHEATID(HeatID);
        m_pPDE_HEAT_DATA_INJ->setTREATID(TreatID);
        m_pPDE_HEAT_DATA_INJ->setPLANT(ActPlant);
        m_pPDE_HEAT_DATA_INJ->setDEVICENAME((std::string)InjectLanceData.Device);
        m_pPDE_HEAT_DATA_INJ->setSTARTTIME(Now);
        m_pPDE_HEAT_DATA_INJ->setINJ_MAT(MatCode);
        m_pPDE_HEAT_DATA_INJ->setINJ_AMOUNT(InjectLanceData.Value);

        RetValue = m_pPDE_HEAT_DATA_INJ->insert();      

        if (RetValue)
        {
          m_pPDE_HEAT_DATA_INJ->commit();
        }
        else
        {
          m_pPDE_HEAT_DATA_INJ->rollback();

          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PDE_HEAT_DATA_INJ", Scope.c_str());
        }
      }// if ( MatCode != DEF::Inv_String && !MatCode.empty() )
    }

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
bool CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnManipInjectLanceStop(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();  
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnManipInjectLanceStop");
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

    std::string Sender = Event.getSender();
    setpDM_Interface(Sender,DM::PRODUCT);
    seqInjectLanceData InjectLanceAmount = CIntfData::ToCORBAType(m_pDM_Interface->getInjectLanceData(ProductID.c_str(),DATA::InjectLanceAmount));

    for ( int i = 0; i < CIntfData::getLength(InjectLanceAmount); i ++)
    {
      CDateTime Now;

      sInjectLanceData InjectLanceData;
      CIntfData::getAt(InjectLanceData,InjectLanceAmount,i);

      std::string MatCode = (std::string)InjectLanceData.MatCode;

      if ( MatCode != DEF::Inv_String && !MatCode.empty() )
      {
        RetValue = m_pPDE_HEAT_DATA_INJ->selectNotStopInj(HeatID,TreatID,ActPlant, (std::string)InjectLanceData.Device, MatCode);

        m_pPDE_HEAT_DATA_INJ->setINJ_MAT(MatCode);
        m_pPDE_HEAT_DATA_INJ->setINJ_AMOUNT(InjectLanceData.Value);
        m_pPDE_HEAT_DATA_INJ->setENDTIME(Now);

				//SARS
				double cons = 0;
				cons = InjectLanceData.Value;
        CDeltaTime DurTime = CDateTime::subTimes(Now, m_pPDE_HEAT_DATA_INJ->getSTARTTIME(1));
        m_pPDE_HEAT_DATA_INJ->setINJ_FLOW(cons/((DurTime.asSeconds()/3600)*60)); //per min
        m_pPDE_HEAT_DATA_INJ->setDURATION((DurTime.asSeconds()/3600)*60); 

        if (RetValue)
        {
          RetValue = m_pPDE_HEAT_DATA_INJ->update(); 
        }
        else
        {
          m_pPDE_HEAT_DATA_INJ->setHEATID(HeatID);
          m_pPDE_HEAT_DATA_INJ->setTREATID(TreatID);
          m_pPDE_HEAT_DATA_INJ->setPLANT(ActPlant);
          m_pPDE_HEAT_DATA_INJ->setDEVICENAME((std::string)InjectLanceData.Device);
          m_pPDE_HEAT_DATA_INJ->setSTARTTIME(Now);

          RetValue = m_pPDE_HEAT_DATA_INJ->insert(); 
        }

        if (RetValue)
        {
          m_pPDE_HEAT_DATA_INJ->commit();
        }
        else
        {
          m_pPDE_HEAT_DATA_INJ->rollback();

          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PDE_HEAT_DATA_INJ", Scope.c_str());
        }
      }// if ( MatCode != DEF::Inv_String && !MatCode.empty() )
    }

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

bool CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnBurnerStart(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();  
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnBurnerStart");
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

    std::string Sender = Event.getSender();

    setpDM_Interface(Sender,DM::EVENT);
    seqStatus seqBurnerStatus         = CIntfData::ToCORBAType(m_pDM_Interface->getStatus(DataKey.c_str(), DATA::BurnerStatus));
    seqGasLanceData SeqGasLanceAmount = CIntfData::ToCORBAType(m_pDM_Interface->getGasLanceData(DataKey.c_str(), DATA::BurnerAmount));

    CStatusHandler BurnerStatusStatusHandler(seqBurnerStatus);

    //assert(length == 3 );
    for ( int i = 0; i < CIntfData::getLength(BurnerStatusStatusHandler.getStatusData(DEF_GEN_STATES::On)); i ++)
    {
      CDateTime Now;
      sStatus Status;
      CIntfData::getAt(Status,BurnerStatusStatusHandler.getStatusData(DEF_GEN_STATES::On),i);

      std::string DeviceName = Status.Device;

      log("DeviceName: " + DeviceName + " started", 1);

      if( !DeviceName.empty() && DeviceName != DEF::Inv_String )
      {
        m_pPDE_HEAT_DATA_BURN->setBURNERNAME(DeviceName);

        if(CIntfData::getLength(SeqGasLanceAmount) > 0)
        {
          for(int j =0; j< CIntfData::getLength(SeqGasLanceAmount); j++)
          {
            sGasLanceData   GasLanceData;
            CIntfData::getAt(GasLanceData,SeqGasLanceAmount,j);

            seqGasData SeqGasData = GasLanceData.LanceData;

            if ( std::string(GasLanceData.Device) == DeviceName )
            {
              double dTotalO2 = 0;
              double dTotalGas = 0;

              for ( long k = 0 ; k < CIntfData::getLength(SeqGasData) ; ++k)
              {
                sGasData GasData;
                CIntfData::getAt(GasData,SeqGasData,k);

                if (std::string(GasData.GasType) == DEF_GCE_BURNER_GASTYPE::O2)
                {
                  dTotalO2 += GasData.GasValue;              
                }
                if(std::string(GasData.GasType) == DEF_GCE_BURNER_GASTYPE::BG)
                {
                  dTotalGas += GasData.GasValue;                  
                }
              }

              m_pPDE_HEAT_DATA_BURN->setO2_CONS(dTotalO2);
              m_pPDE_HEAT_DATA_BURN->setGAS_CONS(dTotalGas);
              break;
            } // if ( std::string(GasLanceData.Device) == DeviceName )
          }
        }//if(CIntfData::getLength(SeqGasLanceAmount) > 0)

        m_pPDE_HEAT_DATA_BURN->setHEATID(HeatID);
        m_pPDE_HEAT_DATA_BURN->setTREATID(TreatID);
        m_pPDE_HEAT_DATA_BURN->setPLANT(ActPlant);
        m_pPDE_HEAT_DATA_BURN->setSTARTTIME(Now);
        RetValue = m_pPDE_HEAT_DATA_BURN->insert();

        if (RetValue)
        {
          m_pPDE_HEAT_DATA_BURN->commit();
        }
        else
        {
          m_pPDE_HEAT_DATA_BURN->rollback();

          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PDE_HEAT_DATA_BURN", Scope.c_str());
        }
      }// if( !DeviceName.empty() && DeviceName != DEF::Inv_String )
    }
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

bool CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnBurnerStop(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();  
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnBurnerStop");
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

    std::string Sender = Event.getSender();

    setpDM_Interface(Sender,DM::EVENT);
    seqStatus seqBurnerStatus         = CIntfData::ToCORBAType(m_pDM_Interface->getStatus      (DataKey.c_str(), DATA::BurnerStatus));
    seqGasLanceData SeqGasLanceAmount = CIntfData::ToCORBAType(m_pDM_Interface->getGasLanceData(DataKey.c_str(), DATA::BurnerAmount));

    CStatusHandler BurnerStatusStatusHandler(seqBurnerStatus);

    for ( int i = 0; i < CIntfData::getLength(BurnerStatusStatusHandler.getStatusData(DEF_GEN_STATES::Off)); i ++)
    {
      CDateTime Now;
      std::string DeviceName = BurnerStatusStatusHandler.getStatusData(DEF_GEN_STATES::Off)[i].Device;

      log("DeviceName: " + DeviceName + " stopped", 1);

      if( !DeviceName.empty() && DeviceName != DEF::Inv_String )
      {
        double dTotalO2 = 0;
        double dTotalGas = 0;

        if(CIntfData::getLength(SeqGasLanceAmount) > 0)
        {
          for(int j =0; j< CIntfData::getLength(SeqGasLanceAmount); j++)
          {
            sGasLanceData   GasLanceData;
            CIntfData::getAt(GasLanceData,SeqGasLanceAmount,j);

            seqGasData SeqGasData = GasLanceData.LanceData;

            if ( std::string(GasLanceData.Device) == DeviceName )
            {
              for ( long k = 0 ; k < CIntfData::getLength(SeqGasData) ; ++k)
              {
                sGasData GasData;
                CIntfData::getAt(GasData,SeqGasData,k);

                if (std::string(GasData.GasType) == DEF_GCE_BURNER_GASTYPE::O2)
                {
                  dTotalO2 += GasData.GasValue;        
                }
                if(std::string(GasData.GasType) == DEF_GCE_BURNER_GASTYPE::BG)
                {
                  dTotalGas += GasData.GasValue;              
                }
              }

              m_pPDE_HEAT_DATA_BURN->setGAS_CONS(dTotalGas);
              m_pPDE_HEAT_DATA_BURN->setO2_CONS(dTotalO2);
              break;
            }
          }// for(int j =0; j< CIntfData::getLength(SeqGasLanceAmount); j++)
        }

        if (m_pPDE_HEAT_DATA_BURN->selectNotStopBurner(HeatID,TreatID,ActPlant,DeviceName))
        {
          m_pPDE_HEAT_DATA_BURN->setENDTIME(Now);

          CDeltaTime DurTime = CDateTime::subTimes(Now, m_pPDE_HEAT_DATA_BURN->getSTARTTIME(1));

          m_pPDE_HEAT_DATA_BURN->setO2_FLOW(dTotalO2/(DurTime.asSeconds()/3600));
          m_pPDE_HEAT_DATA_BURN->setGAS_FLOW(dTotalGas/(DurTime.asSeconds()/3600)); 

          RetValue = m_pPDE_HEAT_DATA_BURN->update();

          if (RetValue)
          {
            m_pPDE_HEAT_DATA_BURN->commit();
          }
          else
          {
            m_pPDE_HEAT_DATA_BURN->rollback();

            cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PDE_HEAT_DATA_BURN", Scope.c_str());
          }
        }// if (m_pPDE_HEAT_DATA_BURN->selectNotStopBurner(HeatID,TreatID,ActPlant,DeviceName))
      }// if( !DeviceName.empty() && DeviceName != DEF::Inv_String )
    }// for ( int i = 0; i < CIntfData::getLength(seqBurnerStatus); i ++)
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

bool CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnManipGasLanceStart(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();  
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnManipGasLanceStart");
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

    std::string Sender = Event.getSender();

    setpDM_Interface(Sender,DM::PRODUCT);
    seqStatus seqGasLanceStatus       = CIntfData::ToCORBAType(m_pDM_Interface->getStatus(ProductID.c_str(), DATA::GasLanceStatus));
    seqGasLanceData SeqGasLanceAmount = CIntfData::ToCORBAType(m_pDM_Interface->getGasLanceData(ProductID.c_str(), DATA::GasLanceAmount));
    CStatusHandler GasLanceStatusStatusHandler(seqGasLanceStatus);

    //assert(length == 3 );
    for ( int i = 0; i < CIntfData::getLength(GasLanceStatusStatusHandler.getStatusData(DEF_GEN_STATES::On)); i ++)
    {
      CDateTime Now;
      sStatus Status;
      CIntfData::getAt(Status,GasLanceStatusStatusHandler.getStatusData(DEF_GEN_STATES::On),i);

      std::string DeviceName = Status.Device;

      log("DeviceName: " + DeviceName + " started", 1);

      if( !DeviceName.empty() && DeviceName != DEF::Inv_String )
      {
        m_pPDE_HEAT_DATA_BURN->setBURNERNAME(DeviceName);

        if(CIntfData::getLength(SeqGasLanceAmount) > 0)
        {
          for(int j =0; j< CIntfData::getLength(SeqGasLanceAmount); j++)
          {
            sGasLanceData   GasLanceData;
            CIntfData::getAt(GasLanceData,SeqGasLanceAmount,j);

            seqGasData SeqGasData = GasLanceData.LanceData;

            if ( std::string(GasLanceData.Device) == DeviceName )
            {
              double dTotalO2 = 0;
              double dTotalGas = 0;

              for ( long k = 0 ; k < CIntfData::getLength(SeqGasData) ; ++k)
              {
                sGasData GasData;
                CIntfData::getAt(GasData,SeqGasData,k);

                if (std::string(GasData.GasType) == DEF_GCE_BURNER_GASTYPE::O2)
                {
                  dTotalO2 += GasData.GasValue;              
                }
								//SARS
                if (std::string(GasData.GasType) == DEF_GCE_BURNER_GASTYPE::BG)
                {
                  dTotalGas += GasData.GasValue;              
                }
              }

              m_pPDE_HEAT_DATA_BURN->setO2_CONS(dTotalO2);
              m_pPDE_HEAT_DATA_BURN->setGAS_CONS(dTotalGas);
              break;
            } // if ( std::string(GasLanceData.Device) == DeviceName )
          }
        }//if(CIntfData::getLength(SeqGasLanceAmount) > 0)

        m_pPDE_HEAT_DATA_BURN->setHEATID(HeatID);
        m_pPDE_HEAT_DATA_BURN->setTREATID(TreatID);
        m_pPDE_HEAT_DATA_BURN->setPLANT(ActPlant);
        m_pPDE_HEAT_DATA_BURN->setSTARTTIME(Now);
        RetValue = m_pPDE_HEAT_DATA_BURN->insert();

        if (RetValue)
        {
          m_pPDE_HEAT_DATA_BURN->commit();
        }
        else
        {
          m_pPDE_HEAT_DATA_BURN->rollback();

          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PDE_HEAT_DATA_BURN", Scope.c_str());
        }
      }// if( !DeviceName.empty() && DeviceName != DEF::Inv_String )
    }
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

bool CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnManipGasLanceStop(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();  
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnManipGasLanceStop");
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

    std::string Sender = Event.getSender();

    setpDM_Interface(Sender,DM::PRODUCT);
    seqStatus seqGasLanceStatus       = CIntfData::ToCORBAType(m_pDM_Interface->getStatus      (ProductID.c_str(), DATA::GasLanceStatus));
    seqGasLanceData SeqGasLanceAmount = CIntfData::ToCORBAType(m_pDM_Interface->getGasLanceData(ProductID.c_str(), DATA::GasLanceAmount));
    seqGasLanceData SeqGasLanceFlow   = CIntfData::ToCORBAType(m_pDM_Interface->getGasLanceData(ProductID.c_str(), DATA::GasLanceFlow));

    CStatusHandler GasLancStatusStatusHandler(seqGasLanceStatus);

    for ( int i = 0; i < CIntfData::getLength(GasLancStatusStatusHandler.getStatusData(DEF_GEN_STATES::Off)); i ++)
    {
      CDateTime Now;
      std::string DeviceName = GasLancStatusStatusHandler.getStatusData(DEF_GEN_STATES::Off)[i].Device;

      log("DeviceName: " + DeviceName + " stopped", 1);

      if( !DeviceName.empty() && DeviceName != DEF::Inv_String )
      {
        double dTotalO2 = 0;
        double dTotalGas = 0;

        if(CIntfData::getLength(SeqGasLanceAmount) > 0)
        {
          for(int j =0; j< CIntfData::getLength(SeqGasLanceAmount); j++)
          {
            sGasLanceData   GasLanceData;
            CIntfData::getAt(GasLanceData,SeqGasLanceAmount,j);

            seqGasData SeqGasData = GasLanceData.LanceData;

            if ( std::string(GasLanceData.Device) == DeviceName )
            {
              for ( long k = 0 ; k < CIntfData::getLength(SeqGasData) ; ++k)
              {
                sGasData GasData;
                CIntfData::getAt(GasData,SeqGasData,k);

                if (std::string(GasData.GasType) == DEF_GCE_BURNER_GASTYPE::O2)
                {
                  dTotalO2 += GasData.GasValue;        
                }
								//SARS
                if (std::string(GasData.GasType) == DEF_GCE_BURNER_GASTYPE::BG)
                {
                  dTotalGas += GasData.GasValue;        
                }
              }

              m_pPDE_HEAT_DATA_BURN->setGAS_CONS(dTotalGas);
              m_pPDE_HEAT_DATA_BURN->setO2_CONS(dTotalO2);
              break;
            }
          }// for(int j =0; j< CIntfData::getLength(SeqGasLanceAmount); j++)
        }

        if (m_pPDE_HEAT_DATA_BURN->selectNotStopBurner(HeatID,TreatID,ActPlant,DeviceName))
        {
          m_pPDE_HEAT_DATA_BURN->setENDTIME(Now);

          CDeltaTime DurTime = CDateTime::subTimes(Now, m_pPDE_HEAT_DATA_BURN->getSTARTTIME(1));

          m_pPDE_HEAT_DATA_BURN->setO2_FLOW(dTotalO2/(DurTime.asSeconds()/3600));
          m_pPDE_HEAT_DATA_BURN->setGAS_FLOW(dTotalGas/(DurTime.asSeconds()/3600)); 

          RetValue = m_pPDE_HEAT_DATA_BURN->update();

          if (RetValue)
          {
            m_pPDE_HEAT_DATA_BURN->commit();
          }
          else
          {
            m_pPDE_HEAT_DATA_BURN->rollback();

            cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PDE_HEAT_DATA_BURN", Scope.c_str());
          }
        }// if (m_pPDE_HEAT_DATA_BURN->selectNotStopBurner(HeatID,TreatID,ActPlant,DeviceName))
      }// if( !DeviceName.empty() && DeviceName != DEF::Inv_String )
    }// for ( int i = 0; i < CIntfData::getLength(seqBurnerStatus); i ++)
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

bool CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnMechanicalSystem(CEventMessage& Event)
{
  bool RetValue = false;

  std::string Message   = Event.getMessage();
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnMechanicalSystem");
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

    setpDM_Interface(Event.getSender(),DM::PLANT);
    double ElecCons     = m_pDM_Interface->getDouble(DEF_PLANT::Furnace, DATA::ElecCons);

    seqGasData SeqGasData; 

    long ActionNo       = CSMC_DBData::unspecLong; 

    if (Message == EAF_EvMsg::evEAFDoorClosed)
    {
      ActionNo = DEF_GC_ACTION_DEF::DoorClosed;
    }
    else if (Message == EAF_EvMsg::evEAFDoorOpened)
    {
      ActionNo = DEF_GC_ACTION_DEF::DoorOpen;
    }
    else if (Message == EAF_EvMsg::evEAFRoofArrivesInUpPosition)
    {
      ActionNo = DEF_GC_ACTION_DEF::RoofUp;
    }
    else if (Message == EAF_EvMsg::evEAFRoofArrivesInDownPosition)
    {
      ActionNo = DEF_GC_ACTION_DEF::RoofDown;
    }
    else if (Message == EAF_EvMsg::evEAFGantrySwungIn)
    {
      ActionNo = DEF_GC_ACTION_DEF::GantrySwungIn;
    }
    else if (Message == EAF_EvMsg::evEAFGantrySwungOut)
    {
      ActionNo = DEF_GC_ACTION_DEF::GantrySwungOut;
    }

    RetValue = handleMechanicalSystem(Event, SeqGasData, ElecCons, ActionNo);
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


