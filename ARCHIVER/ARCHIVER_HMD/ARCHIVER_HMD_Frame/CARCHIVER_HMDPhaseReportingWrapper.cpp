// Copyright (C) 2007 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_S.hh"
#include "iEventMessages_s.hh"
#include "iDM_Interface_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_DBExc.h"
#include "CSMC_EventLogFrameController.h"
#include "CIntfData.h"

#include "CHeatStatusContainer.h"
#include "CPDH_HM_DATA_PHASE.h"
#include "CGC_PHASE.h"

#include "DEF_GC_PHASE.h"

#include "CARCHIVER_HMDTask.h"
#include "CARCHIVER_HMDPhaseReportingWrapper.h"



CARCHIVER_HMDPhaseReportingWrapper::CARCHIVER_HMDPhaseReportingWrapper() 
: m_pPDH_HM_DATA_PHASE(0)
{
}

CARCHIVER_HMDPhaseReportingWrapper::~CARCHIVER_HMDPhaseReportingWrapper()
{
}

bool CARCHIVER_HMDPhaseReportingWrapper::doOnHeatProductionPhaseReport(CEventMessage &Event)
{
  bool RetValue = false;
  bool bTransSucceed=false;
  
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string OrderID   = Event.getOrderID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  std::string CustHeatID;
  //long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);
  
  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_HMDPhaseReportingWrapper::doOnHeatProductionPhaseReport");
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
    
    CDateTime now;
    std::string ActPhase;
    double Lime_Amount;
    double Magn_Amount;
    double Carb_Amount;
    double Blow_Dur;
    long PhaseNo = 0;
    
    //================ logging ==========================
    // get sender PRODUCT interface and log available data
    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    logInterfaceDataList(m_pDM_Interface,ProductID);
    
    ActPhase = CIntfData::ToStdString(m_pDM_Interface->getString(ProductID.c_str(),DATA::PhaseAct));
    Lime_Amount = m_pDM_Interface->getDouble(ProductID.c_str(),DATA::PhaseLimeAmount);
    if (Lime_Amount == DEF::Inv_Double)
    {
      Lime_Amount = 0;
    }
    Magn_Amount = m_pDM_Interface->getDouble(ProductID.c_str(),DATA::PhaseMagnAmount);
    if (Magn_Amount == DEF::Inv_Double)
    {
      Magn_Amount = 0;
    }
    Carb_Amount = m_pDM_Interface->getDouble(ProductID.c_str(),DATA::PhaseCarbAmount);
    if (Carb_Amount == DEF::Inv_Double)
    {
      Carb_Amount = 0;
    }
    Blow_Dur = m_pDM_Interface->getDouble(ProductID.c_str(),DATA::BlowDur);
    if (Blow_Dur == DEF::Inv_Double)
    {
      Blow_Dur = 0;
    }

    // get senter PLANT interface and log available data
    setpDM_Interface(Event.getSender(),DM::PLANT);
    logInterfaceDataList(m_pDM_Interface,DEF_PLANT::Furnace);

    // JAST
    //if (m_pGC_PHASE->select(ActPlant, ActPhase, CSMC_DBData::unspecLong))
    //{
    //  if (!m_pGC_PHASE->isNull(CGC_PHASE::L1_PHASE_NO, 1))
    //  {
    //    PhaseNo = m_pGC_PHASE->getL1PhaseNo(1);
    //  }
    //  else
    //    log("ERROR: L1_PHASE_NO is not set for this Phase!",0);
    //}
    //else
    //{
    //  log("INFO: Actual phase will be skipped, it is not defined for the actual plant",2);
    //  return true;
    //}

    if (m_pPP_HEAT_PLANT->select(HeatID,TreatID,ActPlant))
    {
      CustHeatID = m_pPP_HEAT_PLANT->getHEATID_CUST_PLAN(1);
      if(m_pPP_HEAT->select(CustHeatID))
      {        
        if(ActPhase == DEF_GC_PHASE::StartMonoLime)
        {
// JAST          m_pPP_HEAT->doHeatAndOrderStatusChange(CustHeatID, ActPlant, DEF_GC_HEAT_STATUS::LimeBlow, CSMC_DBData::unspecString);
        }

        if(ActPhase == DEF_GC_PHASE::StartMonoCarb)
        {
// JAST          m_pPP_HEAT->doHeatAndOrderStatusChange(CustHeatID, ActPlant, DEF_GC_HEAT_STATUS::CarbideBlow, CSMC_DBData::unspecString);
        }

        if(ActPhase == DEF_GC_PHASE::MainPhase)
        {
// JAST          m_pPP_HEAT->doHeatAndOrderStatusChange(CustHeatID, ActPlant, DEF_GC_HEAT_STATUS::MagnesBlow, CSMC_DBData::unspecString);
        }
      }
    }
    if (m_pPDH_HM_DATA_PHASE)
    {
      // update data for the last PHASE
      if (m_pPDH_HM_DATA_PHASE->select_phase(ActPlant,HeatID,TreatID))
      {
        if (m_pPDH_HM_DATA_PHASE->isNull(CPDH_HM_DATA_PHASE::END_TIME,1))
        {
          m_pPDH_HM_DATA_PHASE->setHM_ID(HeatID);
          m_pPDH_HM_DATA_PHASE->setTREATID(TreatID);
          m_pPDH_HM_DATA_PHASE->setPLANT(ActPlant);
          m_pPDH_HM_DATA_PHASE->setDURATION(Blow_Dur);
          m_pPDH_HM_DATA_PHASE->setEND_TIME(now);
          m_pPDH_HM_DATA_PHASE->setCONS_CARBIDE(Carb_Amount);
          m_pPDH_HM_DATA_PHASE->setCONS_LIME(Lime_Amount);
          m_pPDH_HM_DATA_PHASE->setCONS_MG(Magn_Amount);

          if (m_pPDH_HM_DATA_PHASE->update())
            m_pPDH_HM_DATA_PHASE->commit();
          else
            m_pPDH_HM_DATA_PHASE->rollback();
        }
      }

      // insert an antry for a new phase
      if ( ActPhase != DEF_GC_PHASE::Deslagging )
      {
        m_pPDH_HM_DATA_PHASE->setHM_ID(HeatID);
        m_pPDH_HM_DATA_PHASE->setTREATID(TreatID);
        m_pPDH_HM_DATA_PHASE->setPLANT(ActPlant);
        m_pPDH_HM_DATA_PHASE->setSTART_TIME(now);
        m_pPDH_HM_DATA_PHASE->setDURATION(Blow_Dur);
        m_pPDH_HM_DATA_PHASE->setPHASE(ActPhase);
        m_pPDH_HM_DATA_PHASE->setCONS_CARBIDE(0);
        m_pPDH_HM_DATA_PHASE->setCONS_LIME(0);
        m_pPDH_HM_DATA_PHASE->setCONS_MG(0);

        if (m_pPDH_HM_DATA_PHASE->insert())
          m_pPDH_HM_DATA_PHASE->commit();
        else
          m_pPDH_HM_DATA_PHASE->rollback();
      }
      //---------------------------------------------
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

void CARCHIVER_HMDPhaseReportingWrapper::initDBClasses()
{
  CARCHIVER_PhaseReportingWrapper::initDBClasses();

  cCBS_StdConnection *pConnection = getStdConnection();

  m_pPDH_HM_DATA_PHASE  = new CPDH_HM_DATA_PHASE(pConnection);
  m_pGC_PHASE             = new CGC_PHASE(pConnection);
  m_pHeatStatusContainer  = new CHeatStatusContainer(pConnection);
}

void CARCHIVER_HMDPhaseReportingWrapper::deleteDBClasses()
{
  CARCHIVER_PhaseReportingWrapper::deleteDBClasses();

  if (m_pPDH_HM_DATA_PHASE) { delete m_pPDH_HM_DATA_PHASE; m_pPDH_HM_DATA_PHASE = 0;}
  if (m_pGC_PHASE)            { delete m_pGC_PHASE; m_pGC_PHASE = 0;}
  if (m_pHeatStatusContainer) { delete m_pHeatStatusContainer; m_pHeatStatusContainer = 0;} 
}

