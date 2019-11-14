// Copyright (C) 2009 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"
#include "iDM_Interface_s.hh"
#include "iEventMessages_s.hh"

#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_DBExc.h"
#include "CSMC_EventLogFrameController.h"
#include "CIntfData.h"
#include "CDataConversion.h"

#include "CPDE_HEAT_DATA_MELT.h"

#include "DEF_GC_HEAT_STATUS.h"
#include "DEF_GC_PP_ORDER_SINGLE_AIMS.h"
#include "DEF_GC_TREATMENTPHASE_DEF.h"

#include "CARCHIVER_EAFTreatmentManagementWrapper.h"

CARCHIVER_EAFTreatmentManagementWrapper::~CARCHIVER_EAFTreatmentManagementWrapper()
{
}


CARCHIVER_EAFTreatmentManagementWrapper::CARCHIVER_EAFTreatmentManagementWrapper()      
{
}

void CARCHIVER_EAFTreatmentManagementWrapper::deleteDBClasses()
{
  CARCHIVER_TreatmentWrapper::deleteDBClasses();

  //if (m_pGT_PARAM)                    {delete m_pGT_PARAM; m_pGT_PARAM = 0;  }
  if (m_pPDE_HEAT_DATA_MELT)          {delete m_pPDE_HEAT_DATA_MELT; m_pPDE_HEAT_DATA_MELT = 0;}
}

void CARCHIVER_EAFTreatmentManagementWrapper::initDBClasses()
{
  CARCHIVER_TreatmentWrapper::initDBClasses();

  cCBS_StdConnection *pConnection = getStdConnection();

  //m_pGT_PARAM                   = new CGT_PARAM(pConnection);
  m_pPDE_HEAT_DATA_MELT         = new CPDE_HEAT_DATA_MELT(pConnection);
}

bool CARCHIVER_EAFTreatmentManagementWrapper::doOnHeatStart(CEventMessage& Event)
{
  bool RetValue = true ;
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);


  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_EAFTreatmentManagementWrapper::doOnHeatStart");
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

    RetValue = RetValue && handleHeatStart(Event);

    //update PD_PlantStatus
    if(m_pPD_PLANTSTATUS->select(ActPlant,ActPlantNo,CSMC_DBData::unspecLong))
    {
      m_pPD_PLANTSTATUS->setTREATMENTSTART(Now);

      RetValue = RetValue && m_pPD_PLANTSTATUS->update();

      if(RetValue)
        m_pPD_PLANTSTATUS->commit();
      else 
        m_pPD_PLANTSTATUS->rollback();
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



bool CARCHIVER_EAFTreatmentManagementWrapper::doOnTappingStart(CEventMessage& Event)
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
  std::string Scope("CARCHIVER_EAFTreatmentManagementWrapper::doOnTappingStart");
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

    handleTappingStart(Event);

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


bool CARCHIVER_EAFTreatmentManagementWrapper::doPhaseReport(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string Sender    = Event.getSender();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);


  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_EAFTreatmentManagementWrapper::doPhaseReport");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  try
  {
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }

    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    CDateTime HeatAnnounceTime  ( m_pDM_Interface->getDate  (ProductID.c_str(), DATA::HeatAnnounceTime));
    double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatAnnounceTime);
    double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatStartTime);

    seqPhaseDataReport seqPhaseData = CIntfData::ToCORBAType(m_pDM_Interface->getPhaseDataReport(ProductID.c_str(),DATA::PhaseDataReport));

    double ElecCons             = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::ElecCons);
    std::string PhaseAct        = m_pDM_Interface->getString(ProductID.c_str(), DATA::PhaseTracker);
    long PhaseNoAct             = m_pDM_Interface->getLong(ProductID.c_str(), DATA::PhaseNoTracker);

    /********************************************************/

    // check and convert data 
    PhaseAct = CDataConversion::SetInvalidToDefault(PhaseAct,DEF_GC_TREATMENTPHASE_DEF::Preparation);

    std::string Phase = PhaseAct;

    if ( PhaseNoAct > 0 )
    {
      Phase += " " + CDataConversion::LongToString(PhaseNoAct); 
    }

    //if(seqPhaseData.length() > 0 )
    //{
    //  sPhaseDataReport sPhaseDataReportData;
    //  CIntfData::getAt(sPhaseDataReportData,seqPhaseData,0);

    //  Phase      = sPhaseDataReportData.PhaseName;
    //  PhaseNoAct = sPhaseDataReportData.PhaseNo;

    //  m_pPDE_HEAT_DATA_MELT->savePhaseDataReport(HeatID,TreatID,ActPlant,sPhaseDataReportData);
    //}

    if ( m_pPDE_HEAT_DATA_MELT )
    {
      if ( m_pPDE_HEAT_DATA_MELT->writeDataOnPhaseEnd(HeatID, TreatID, ActPlant, CSMC_DBData::unspecString, ElecCons) )
      {
        m_pPDE_HEAT_DATA_MELT->writeDataOnPhaseStart(HeatID, TreatID, ActPlant, Phase, ElecCons);
      }
    }

    //If Phase = Meltdown Bakset1 then fill PreparationEnd in pd_action time = meltdownstart time
    //also fill PreparationStart in pd_action time = last TappingEnd time

    if(Phase == "MeltBskNo:" && PhaseNoAct == 1)
    {
      if(!m_pPD_ACTION->select(HeatID,TreatID,ActPlant,DEF_GC_ACTION_DEF::PreparationEnd,CSMC_DBData::unspecDate))
      {
        CDateTime now;

        double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatAnnounceTime);
        double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatStartTime);   
        std::string ActionName;
        if (m_pPD_ACTION->isActionDefined(DEF_GC_ACTION_DEF::PreparationEnd))
        {
          ActionName = m_pPD_ACTION->getActionDefName(DEF_GC_ACTION_DEF::PreparationEnd);
        }
        else
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorSearchingData(sMessage,"ACTIONNO","GC_ACTION_DEF");
        }
        m_pPD_ACTION->m_Row.ACTIONNAME                = ActionName;
        m_pPD_ACTION->m_Row.ACTIONUNIT                = "min";
        m_pPD_ACTION->m_Row.ACTIONVALUE               = "0";
        m_pPD_ACTION->m_Row.ACTIONSTATUS              = 1;
        m_pPD_ACTION->m_Row.DURSINCEHEATANNOUNCEMENT  = DurSinceHeatAnnounce;
        m_pPD_ACTION->m_Row.DURSINCESTARTOFHEAT       = DurSinceHeatStart;
        m_pPD_ACTION->m_Row.N2_MOMENT                 = 0;
        m_pPD_ACTION->m_Row.AR_MOMENT                 = 0;
        m_pPD_ACTION->m_Row.O2_MOMENT                 = 0;
        m_pPD_ACTION->m_Row.ELECEGY                   = 0;

        m_pPD_ACTION->write(HeatID, TreatID, ActPlant, DEF_GC_ACTION_DEF::PreparationEnd, true);
      }

      if(!m_pPD_ACTION->select(HeatID,TreatID,ActPlant,DEF_GC_ACTION_DEF::PreparationStart,CSMC_DBData::unspecDate))
      {
        CDateTime dLastEndTime = m_pPD_ACTION->GetLastEventRevTime(HeatID,TreatID,ActPlant,DEF_GC_ACTION_DEF::TappingEnd);

        m_pPD_ACTION->setHEATID(HeatID);
        m_pPD_ACTION->setTREATID(TreatID);
        m_pPD_ACTION->setPLANT(ActPlant);
        m_pPD_ACTION->setREVTIME(dLastEndTime);

        std::string ActionName;

        if(m_pPD_ACTION->isActionDefined(DEF_GC_ACTION_DEF::PreparationStart))
        {
          ActionName = m_pPD_ACTION->getActionDefName(DEF_GC_ACTION_DEF::PreparationStart);

        }
        else
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorSearchingData(sMessage,"ACTIONNO","GC_ACTION_DEF");
        }

        m_pPD_ACTION->setACTIONNO(DEF_GC_ACTION_DEF::PreparationStart);
        m_pPD_ACTION->setACTIONNAME(ActionName);
        m_pPD_ACTION->setACTIONUNIT("min");
        m_pPD_ACTION->setACTIONVALUE("0");
        m_pPD_ACTION->setACTIONSTATUS(1);
        m_pPD_ACTION->setDURSINCEHEATANNOUNCEMENT(0);
        m_pPD_ACTION->setDURSINCESTARTOFHEAT(0);
        m_pPD_ACTION->setN2_MOMENT(0);
        m_pPD_ACTION->setAR_MOMENT(0);
        m_pPD_ACTION->setO2_MOMENT(0);
        m_pPD_ACTION->setELECEGY(0);
        RetValue = m_pPD_ACTION->insert();
        if(RetValue)
          m_pPD_ACTION->commit();
        else
          m_pPD_ACTION->rollback();
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