// Copyright (C) 2007 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_S.hh"
#include "iEventMessages_s.hh"
#include "iDM_Interface_s.hh"

#include "CIntfData.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_DBExc.h"
#include "cCBS_StdCORBA_Task.h"
#include "CSMC_EventLogFrameController.h"
#include "CEventMessage.h"
#include "CDateTime.h"
#include"CDataConversion.h"

#include "CARCHIVER_LFTask.h"

#include "CPDL_HEAT_DATA.h"
#include "CPDL_CYCL_MEAS_DATA.h"
#include "CEquipmentData.h"
#include "CPD_PRETREATDATA.h"
#include "CPD_HEAT_DATA_LIQADD.h"
#include "CGC_PHASE.h"
#include "CPD_PHASE_RES.h"
#include "CGC_LADLE_PARTS.h"
#include "CGC_LADLE_DEF.h"
#include "CHD_GRADE.h"
#include "CHDL_CYCL_MEAS_DATA.h"
#include "CHDL_HEAT_DATA.h"
#include "CHDL_PP_STIRR.h"
#include "CHDL_PP_STIRR_SPEC.h"
#include "CGC_HEAT_STATUS.h" 
#include "CPD_PLANTSTATUS.h"
#include "CPDL_HEAT_DATA_MELT.h"

#include "DEF_GC_PLANT_DEF.h"

#include "CARCHIVER_LFTreatmentWrapper.h"



//##ModelId=462E23FB016F
CARCHIVER_LFTreatmentWrapper::CARCHIVER_LFTreatmentWrapper() 
: m_pEquipmentData(0)
, m_pPDL_HEAT_DATA(0)
, m_pPDL_CYCL_MEAS_DATA(0)
, m_pHDL_HEAT_DATA(0)
{
}

//##ModelId=462E23FB03B4
CARCHIVER_LFTreatmentWrapper::~CARCHIVER_LFTreatmentWrapper()
{
}


//##ModelId=462F85900378
bool CARCHIVER_LFTreatmentWrapper::doOnHeatStart(CEventMessage& Event)
{
  bool RetValue = true;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string Sender    = Event.getSender();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);


  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_LFTreatmentWrapper::doOnHeatStart");
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

    //update PD_PlantStatus LadleNO,LadleType, TreantmentStartTime etc.
    setpDM_Interface(Sender,DM::EVENT);    

    long LadleNo = m_pDM_Interface->getLong(DataKey.c_str(), DATA::LadleNo);
    std::string LadleType = CIntfData::ToStdString(m_pDM_Interface->getString(DataKey.c_str(), DATA::LadleType));

    CDateTime   Now;
    long row = 0;

    RetValue = RetValue && handleHeatStart(Event);//Handle general operation of  heat start.

    long nCarNo = 1;
    if( m_pPDL_HEAT_DATA->select( HeatID,TreatID,ActPlant ) )
    {
      nCarNo = m_pPDL_HEAT_DATA->getCARNO(1) ;
    }

    //update PD_PlantStatus 
    if( m_pPD_PLANTSTATUS->select(ActPlant,ActPlantNo,nCarNo) )
    {
    //  m_pPD_PLANTSTATUS->setHEATID(HeatID);  //  U153: done by CPD_PLANTSTATUS::doHeatStart
    //  m_pPD_PLANTSTATUS->setTREATID(TreatID);

    //  if ( m_pGC_LADLE_DEF->isValidLadle(LadleNo, LadleType) )
    //  {
    //    m_pPD_PLANTSTATUS->setLADLENO(LadleNo);
    //    m_pPD_PLANTSTATUS->setLADLETYPE(LadleType);
    //  }

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

//##ModelId=462F85910008
bool CARCHIVER_LFTreatmentWrapper::doOnHeatAnnounceStatus(CEventMessage& Event)
{
  // TODO: Add your specialized code here.
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string Sender    = Event.getSender();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);  

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_LFSignalsAndMeasurementWrapper::doOnHeatAnnounceStatus");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Sender
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

    RetValue = handleHeatAnnounceStatus(Event,CSMC_DBData::unspecDouble);

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

//##ModelId=462F85910094
bool CARCHIVER_LFTreatmentWrapper::doOnUpdateAimDepartureTime(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string Sender    = Event.getSender();

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_LFTreatmentWrapper::doOnUpdateAimDepartureTime");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Sender
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

    setpDM_Interface(Sender,DM::EVENT);
    CDateTime depTime ;
    depTime.SetTime(m_pDM_Interface->getDate(DataKey.c_str(),DATA::TreatEndAim));

    // update PD_HEATDATA
    RetValue = handleUpdateAimDepartureTime(Event,depTime);

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

//##ModelId=462F859100EE
bool CARCHIVER_LFTreatmentWrapper::doOnUpdateAimTemperature(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string Sender    = Event.getSender();

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_LFTreatmentWrapper::doOnUpdateAimTemperature");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Sender
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

    setpDM_Interface(Sender,DM::EVENT);
    // update PD_HEATDATA
    RetValue = handleUpdateAimTemperature(Event,m_pDM_Interface->getDouble(DataKey.c_str(),DATA::TempAim));
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

bool CARCHIVER_LFTreatmentWrapper::doPhaseReport(CEventMessage& Event)
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
  std::string Scope("CARCHIVER_LFTreatmentManagementWrapper::doPhaseReport");
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

    //seqPhaseDataReport seqL1PhaseData = CIntfData::ToCORBAType(m_pDM_Interface->getPhaseDataReport(ProductID.c_str(),DATA::PhaseDataReport));

    double ElecCons             = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::ElecCons);
    std::string PhaseAct        = m_pDM_Interface->getString(ProductID.c_str(), DATA::PhaseProcess);
    long PhaseNoAct             = m_pDM_Interface->getLong(ProductID.c_str(),   DATA::PhaseNoProcess);

    /********************************************************/

    // check and convert data 
    PhaseAct = CDataConversion::SetInvalidToDefault(PhaseAct,DEF_LF_PHASES::HeatingInitial);

    std::string Phase = PhaseAct;

    if ( PhaseNoAct > 0 )
    {
      Phase += " " + CDataConversion::LongToString(PhaseNoAct); 
    }

    if ( m_pPDL_HEAT_DATA_MELT )
    {
      if ( m_pPDL_HEAT_DATA_MELT->writeDataOnPhaseEnd(HeatID, TreatID, ActPlant, CSMC_DBData::unspecString, ElecCons) )
      {
        m_pPDL_HEAT_DATA_MELT->writeDataOnPhaseStart(HeatID, TreatID, ActPlant, Phase, ElecCons);
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

//##ModelId=462E23FF0023
void CARCHIVER_LFTreatmentWrapper::initDBClasses()
{
  CARCHIVER_TreatmentWrapper::initDBClasses();

  cCBS_StdConnection *pConnection = getStdConnection();

  m_pPDL_CYCL_MEAS_DATA     = new CPDL_CYCL_MEAS_DATA(pConnection);
  m_pEquipmentData          = new CEquipmentData(pConnection);
  m_pPD_PRETREATDATA        = new CPD_PRETREATDATA(pConnection);
  m_pPD_HEAT_DATA_LIQADD    = new CPD_HEAT_DATA_LIQADD(pConnection);
  m_pPDL_HEAT_DATA          = new CPDL_HEAT_DATA(pConnection);
  m_pGC_PHASE               = new CGC_PHASE(pConnection);
  m_pPD_PHASE_RES           = new CPD_PHASE_RES(pConnection); 
  m_pGC_LADLE_PARTS         = new CGC_LADLE_PARTS(pConnection);
  m_pGC_LADLE_DEF           = new CGC_LADLE_DEF(pConnection);
  m_pHD_GRADE               = new CHD_GRADE(pConnection);
  m_pHDL_CYCL_MEAS_DATA     = new CHDL_CYCL_MEAS_DATA(pConnection);
  m_pHDL_HEAT_DATA          = new CHDL_HEAT_DATA(pConnection);
  m_pHDL_PP_STIRR           = new CHDL_PP_STIRR(pConnection);
  m_pHDL_PP_STIRR_SPEC      = new CHDL_PP_STIRR_SPEC(pConnection);
  m_pCGC_HEAT_STAT          = new CGC_HEAT_STATUS(pConnection);
  m_pPD_PLANTSTATUS         = new CPD_PLANTSTATUS(pConnection);
  m_pPDL_HEAT_DATA_MELT     = new CPDL_HEAT_DATA_MELT(pConnection);

}


//##ModelId=462E23FF02A2
void CARCHIVER_LFTreatmentWrapper::deleteDBClasses()
{
  CARCHIVER_TreatmentWrapper::deleteDBClasses();
  if (m_pEquipmentData) { delete m_pEquipmentData; m_pEquipmentData = 0;}
  if (m_pPDL_HEAT_DATA) { delete m_pPDL_HEAT_DATA; m_pPDL_HEAT_DATA = 0;}
  if (m_pPDL_CYCL_MEAS_DATA) { delete m_pPDL_CYCL_MEAS_DATA; m_pPDL_CYCL_MEAS_DATA= 0;}
  if (m_pPD_PRETREATDATA) {delete m_pPD_PRETREATDATA ; m_pPD_PRETREATDATA = 0;}
  if (m_pPD_HEAT_DATA_LIQADD) {delete m_pPD_HEAT_DATA_LIQADD;m_pPD_HEAT_DATA_LIQADD = 0;}
  if (m_pGC_PHASE) {delete m_pGC_PHASE;m_pGC_PHASE = 0;}
  if (m_pPD_PHASE_RES) {delete m_pPD_PHASE_RES;m_pPD_PHASE_RES = 0;}  
  if (m_pGC_LADLE_PARTS) {delete m_pGC_LADLE_PARTS;m_pGC_LADLE_PARTS = 0;}
  if (m_pGC_LADLE_DEF) {delete m_pGC_LADLE_DEF;m_pGC_LADLE_DEF = 0;}
  if (m_pHD_GRADE) {delete m_pHD_GRADE;m_pHD_GRADE = 0;}
  if (m_pHDL_CYCL_MEAS_DATA) {delete m_pHDL_CYCL_MEAS_DATA;m_pHDL_CYCL_MEAS_DATA = 0;}
  if (m_pHDL_HEAT_DATA) {delete m_pHDL_HEAT_DATA;m_pHDL_HEAT_DATA = 0;}
  if (m_pHDL_PP_STIRR) {delete m_pHDL_PP_STIRR;m_pHDL_PP_STIRR = 0;}
  if (m_pHDL_PP_STIRR_SPEC) {delete m_pHDL_PP_STIRR_SPEC;m_pHDL_PP_STIRR_SPEC = 0;}
  if (m_pCGC_HEAT_STAT) {delete m_pCGC_HEAT_STAT;m_pCGC_HEAT_STAT = 0;}
  if (m_pPD_PLANTSTATUS) {delete m_pPD_PLANTSTATUS; m_pPD_PLANTSTATUS = 0;}
  if (m_pPDL_HEAT_DATA_MELT) {delete m_pPDL_HEAT_DATA_MELT; m_pPDL_HEAT_DATA_MELT = 0;}
}