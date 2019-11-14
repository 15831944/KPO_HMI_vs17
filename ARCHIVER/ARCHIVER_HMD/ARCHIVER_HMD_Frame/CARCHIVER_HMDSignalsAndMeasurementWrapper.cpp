// Copyright (C) 2007 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_S.hh"
#include "cCBS_StdConnection.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_DBExc.h"
#include "CSMC_EventLogFrameController.h"
#include "CIntfData.h"

#include "CPDH_HM_DATA.h"
#include "CPD_PLANTSTATUS_PLANT.h"
#include "CPP_HEAT_PLANT.h"
#include "CPDH_CYCL_MEAS_DATA.h"
#include "CGT_MAT_PURP.h"
#include "CGT_PURP.h"

#include "DEF_GT_PURP.h"
#include "DEF_GC_PLANTSTATUS.h"


#include "CARCHIVER_HMDTask.h"
#include "CARCHIVER_HMDSignalsAndMeasurementWrapper.h"

CARCHIVER_HMDSignalsAndMeasurementWrapper::CARCHIVER_HMDSignalsAndMeasurementWrapper()
: m_pPDH_Cycl_Meas_Data(0)	
, m_pPDH_HM_DATA(0)
, m_pPD_PLANTSTATUS_PLANT(0)
{
  // for cyclic codes
  m_PurpList.insert(DEF_GT_PURP::Carbide);
  m_PurpList.insert(DEF_GT_PURP::Lime);
  m_PurpList.insert(DEF_GT_PURP::Magnesium);
}

CARCHIVER_HMDSignalsAndMeasurementWrapper::~CARCHIVER_HMDSignalsAndMeasurementWrapper()
{
}

bool CARCHIVER_HMDSignalsAndMeasurementWrapper::doOnCyclicMeasurement(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string Sender    = Event.getSender();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_HMDSignalsAndMeasurementWrapper::doOnCyclicMeasurement");
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

    log("Begin HMD Cyclical Measured Data ",3);
    
    setpDM_Interface(Sender,DM::PRODUCT);
    double durSA = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatAnnounceTime);
    double durSS = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatStartTime);
    double AmountMagn    = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::MagnAmount);
    double AmountLime    = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::LimeAmount);
    double AmountCarb    = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::CarbAmount);

		setpDM_Interface(Sender,DM::EVENT);
	  double FlowN2      =  m_pDM_Interface->getDouble(DataKey.c_str(), DATA::PowderFlow); 
	  double ConsN2      = m_pDM_Interface->getDouble(DataKey.c_str(), DATA::PowderConsumption); 
	  double PressN2      = m_pDM_Interface->getDouble(DataKey.c_str(), DATA::N2Press);
	  long LancePos      = m_pDM_Interface->getLong(DataKey.c_str(), DATA::LancePos);
		
    setpDM_Interface(Sender,DM::PLANT);

    long BlowType        = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::HMDBlowType);
    double FlowMagn      = m_pDM_Interface->getDouble(DEF_PLANT::Furnace, DATA::HMDBlowingRateMg);
    double FlowLime      = m_pDM_Interface->getDouble(DEF_PLANT::Furnace, DATA::HMDBlowingRateLime);
    double FlowCarb      = m_pDM_Interface->getDouble(DEF_PLANT::Furnace, DATA::HMDBlowingRateCarbide);

    CDateTime now;

    if ( m_pPDH_HM_DATA->select(HeatID, TreatID, ActPlant) )
    {
      m_pPDH_Cycl_Meas_Data->setHM_ID(HeatID);
      m_pPDH_Cycl_Meas_Data->setTREATID(TreatID);
      m_pPDH_Cycl_Meas_Data->setPLANT(ActPlant);

      m_pPDH_Cycl_Meas_Data->setREVTIME(now);
      m_pPDH_Cycl_Meas_Data->setDURSINCEHEATANNOUNCE(durSA);
      m_pPDH_Cycl_Meas_Data->setDURSINCESTARTOFHEAT(durSS);

      m_pPDH_Cycl_Meas_Data->setFLOW_LIME(FlowLime);
      m_pPDH_Cycl_Meas_Data->setFLOW_MG(FlowMagn);
      m_pPDH_Cycl_Meas_Data->setFLOW_CARBIDE(FlowCarb);

      m_pPDH_Cycl_Meas_Data->setCONS_LIME(AmountLime);
      m_pPDH_Cycl_Meas_Data->setCONS_MG(AmountMagn);
      m_pPDH_Cycl_Meas_Data->setCONS_CARBIDE(AmountCarb);
      
      m_pPDH_Cycl_Meas_Data->setTREATTYPE(BlowType);

      m_pPDH_Cycl_Meas_Data->setGAS_FLOW_N2(FlowN2);
      m_pPDH_Cycl_Meas_Data->setGAS_PRESSURE_N2(PressN2);
      m_pPDH_Cycl_Meas_Data->setCONS_N2(ConsN2);
      m_pPDH_Cycl_Meas_Data->setLANCEPOS(LancePos);

      if (m_pPDH_Cycl_Meas_Data->insert())
      {
        RetValue = true;
        m_pPDH_Cycl_Meas_Data->commit();
      }
      else
     {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBWriteError(sMessage, "" , "PDH_CYCL_MEAS_DATA", "insert failure");
        m_pPDH_Cycl_Meas_Data->rollback();
        RetValue = false;
     }
      
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBReadError(sMessage,"HM_ID - TREATID - PLANT","PDH_HM_DATA","");
    }

	
	  RetValue = RetValue && m_pPD_PLANTSTATUS_PLANT->updateStatus(ActPlant, ActPlantNo, 1, 2,  DEF_GC_PLANTSTATUS::LIME, CDataConversion::LongToString((long)AmountLime), false, m_lastError);
	  RetValue = RetValue && m_pPD_PLANTSTATUS_PLANT->updateStatus(ActPlant, ActPlantNo, 1, 2,  DEF_GC_PLANTSTATUS::MG, CDataConversion::LongToString((long)AmountMagn), false, m_lastError);
	  RetValue = RetValue && m_pPD_PLANTSTATUS_PLANT->updateStatus(ActPlant, ActPlantNo, 1, 2,  DEF_GC_PLANTSTATUS::CARBIDE, CDataConversion::LongToString((long)AmountCarb), false, m_lastError);

		if (RetValue)
			m_pPD_PLANTSTATUS_PLANT->commit();
		else
		{
			m_pPD_PLANTSTATUS_PLANT->rollback();
		}

    log("End HMD Cyclical Measured Data ",3);

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

void CARCHIVER_HMDSignalsAndMeasurementWrapper::initDBClasses()
{
  CARCHIVER_SignalsAndMeasurementWrapper::initDBClasses();

  cCBS_StdConnection *pConnection = getStdConnection();

  m_pPDH_Cycl_Meas_Data    = new CPDH_CYCL_MEAS_DATA(pConnection);
  m_pPDH_HM_DATA           = new CPDH_HM_DATA(pConnection);
	m_pPD_PLANTSTATUS_PLANT  = new CPD_PLANTSTATUS_PLANT(pConnection);
}

void CARCHIVER_HMDSignalsAndMeasurementWrapper::deleteDBClasses()
{
  CARCHIVER_SignalsAndMeasurementWrapper::deleteDBClasses();

  if (m_pPDH_Cycl_Meas_Data)      { delete m_pPDH_Cycl_Meas_Data; m_pPDH_Cycl_Meas_Data = 0; } 
  if (m_pPDH_HM_DATA)             { delete m_pPDH_HM_DATA; m_pPDH_HM_DATA = 0; } 
  if (m_pPD_PLANTSTATUS_PLANT)    { delete m_pPD_PLANTSTATUS_PLANT; m_pPD_PLANTSTATUS_PLANT = 0; } 
}
