// Copyright (C) 2007 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"
#include "iEventMessages_s.hh"
#include "iDM_Interface_s.hh"

#include "CIntfData.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_EventLogFrameController.h"
#include "cCBS_DBExc.h"
#include "CDateTime.h"
#include "CDataConversion.h"
#include  "CEventMessage.h"
#include "CARCHIVER_LFAnalysisDataWrapper.h"
#include "DEF_GC_HEAT_STATUS.h"
#include "CPDL_Heat_Data.h"
#include "DEF_GC_PLANT_DEF.h"

//##ModelId=462EFAE20213
CARCHIVER_LFAnalysisDataWrapper::CARCHIVER_LFAnalysisDataWrapper()
{
}


//##ModelId=462EFAE300D3
CARCHIVER_LFAnalysisDataWrapper::~CARCHIVER_LFAnalysisDataWrapper()
{
  deleteDBClasses();
}


//##ModelId=462EFB0D004C
bool CARCHIVER_LFAnalysisDataWrapper::doOnSampleTaken(CEventMessage& Event )
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string ProdOrderID = Event.getOrderID();

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_LFAnalysisDataWrapper::doOnSampleTaken");
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

    long TreatmentPosition = DEF_GC_TRETMENTPOSITION::TransferCar1;

    if( m_pPDL_HEAT_DATA->select( HeatID,TreatID,ActPlant ) )
    {
       TreatmentPosition = m_pPDL_HEAT_DATA->getCARNO(1);
    }

    RetValue = writeSample(Event,TreatmentPosition);


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

//do in DM, remove later
//##ModelId=462EFB2E02BC
//bool CARCHIVER_LFAnalysisDataWrapper::doOnAnalysisReceived(CEventMessage& Event, bool Steel)
//{
//  bool RetValue = false;
//
//  std::string ProductID = Event.getProductID();
//  std::string HeatID    = Event.getHeatID();
//  std::string TreatID   = Event.getTreatID();
//  std::string DataKey   = Event.getDataKey();
//  std::string PlantID   = Event.getPlantID();
//  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
//  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);
//  std::string ProdOrderID = Event.getOrderID();
//
//  // Unified exception handling *******************************************************
//  std::string Scope("CARCHIVER_LFAnalysisDataWrapper::doOnAnalysisReceived");
//  std::stringstream ExceptionMsg;
//  ExceptionMsg << "Handling event: " << Event.getSender()
//    << ", " << ProductID << ", " << HeatID
//    << ", " << TreatID   << ", " << DataKey;
//  //***********************************************************************************
//
//  try
//  {
//    if (!checkDBConnection())
//    {
//      handleDBConnectionError();
//      if (!checkDBConnection()) return false;
//    }
//
//    seqAnalysisData  SeqAnalysisData;
//
//    // collect data from event data interface
//    setpDM_Interface(Event.getSender(),DM::EVENT);
//
//    if (Steel)
//      SeqAnalysisData = CIntfData::ToCORBAType(m_pDM_Interface->getAnalysisData(DataKey.c_str(),DATA::SteelMeasAnalysis));
//    else
//      SeqAnalysisData = CIntfData::ToCORBAType(m_pDM_Interface->getAnalysisData(DataKey.c_str(),DATA::SlagMeasAnalysis));
//
//
//    // write into PD_ANL_ENTRY, PD_LADLE_ANL, update sampleid and sampleno in PD_LADLE_DATA
//    RetValue = writeAnalysis(Event, SeqAnalysisData);
//
//
//  }
//  catch (cCBS_DBExc &e)
//  {
//    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
//    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
//    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
//      Scope.c_str(), ExceptionMsg.str().c_str()); 
//    RetValue = false;
//    handleDBConnectionError();
//  }
//  catch(CORBA::SystemException& sExc) 
//  {
//    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
//    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
//    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
//      Scope.c_str(), ExceptionMsg.str().c_str());
//    RetValue = false;
//  }
//  catch(CORBA::Exception& cExc) 
//  {
//    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
//    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
//    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
//      Scope.c_str(), ExceptionMsg.str().c_str());
//    RetValue = false;
//  }
//  catch(...)
//  {
//    std::string Msg("Unknown exception:");
//    Msg += ExceptionMsg.str();
//    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
//    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
//    pEventLog->EL_ExceptionCaught(sMessage, "",
//      Scope.c_str(), Msg.c_str()); 
//    RetValue = false;
//  }
//  return RetValue;
//}

//##ModelId=462EFAE403B6
void CARCHIVER_LFAnalysisDataWrapper::initDBClasses()
{
  CARCHIVER_AnalysisDataWrapper::initDBClasses();

  cCBS_StdConnection *pConnection = getStdConnection();

  m_pPDL_HEAT_DATA = new CPDL_HEAT_DATA(pConnection);

}

//##ModelId=462EFAE501F2
void CARCHIVER_LFAnalysisDataWrapper::deleteDBClasses()
{
  CARCHIVER_AnalysisDataWrapper::deleteDBClasses();
  if (m_pPDL_HEAT_DATA ) {delete m_pPDL_HEAT_DATA; m_pPDL_HEAT_DATA = 0;}

}

