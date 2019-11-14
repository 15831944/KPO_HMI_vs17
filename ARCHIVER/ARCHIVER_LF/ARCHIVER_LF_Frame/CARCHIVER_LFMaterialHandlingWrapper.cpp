// Copyright (C) 2007 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"
#include "iEventMessages_s.hh"
#include "iDM_Interface_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_DBExc.h"

#include "CIntfData.h"
#include "CSMC_EventLogFrameController.h"

#include "CDateTime.h"
#include "CDataConversion.h"
#include "CStirringDataHandler.h"

#include "CPDL_HEAT_DATA.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_STIRR_GAS_TYPE.h"

#include "CARCHIVER_LFMaterialHandlingWrapper.h"


//##ModelId=462E05C502E3
CARCHIVER_LFMaterialHandlingWrapper::CARCHIVER_LFMaterialHandlingWrapper()
{
}

//##ModelId=462E05C60173
CARCHIVER_LFMaterialHandlingWrapper::~CARCHIVER_LFMaterialHandlingWrapper()
{
  deleteDBClasses();
}

//##ModelId=462F05BD019C
bool CARCHIVER_LFMaterialHandlingWrapper::doOnMaterialHandlingReport(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_LFMaterialHandlingWrapper::doOnMaterialHandlingReport");
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

    //get info from PRODUCTION_MANAGEMENT_INTERFACE
    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    seqStirringData StirringAmount = CIntfData::ToCORBAType(m_pDM_Interface->getStirringData(ProductID.c_str(),DATA::StirringAmount));

    double ElecCons                = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::ElecCons);

    CStirringDataHandler StirringDataHandler(StirringAmount);
    seqGasData SeqGasData = StirringDataHandler.getAccumulatedGasDataSeq(); // equals obsolete DEF_DEVICES::Total

    long TreatmentPosition = DEF_GC_TRETMENTPOSITION::TransferCar1;

	  if( m_pPDL_HEAT_DATA->select( HeatID,TreatID,ActPlant ) )
	  {
	    TreatmentPosition = m_pPDL_HEAT_DATA->getCARNO(1);
    }

    sMetTimeStamp TimeStamp;
    TimeStamp.O2_Moment   = DEF::Inv_Double;
    TimeStamp.Ar_Moment   = DEF::Inv_Double;
    TimeStamp.N2_Moment   = DEF::Inv_Double;
    TimeStamp.Elec_Moment = CDataConversion::SetInvalidToDefault(ElecCons,DEF::Inv_Double);

    //set corresponding gas moment. valid gas types O2,Ar,N2
    for (long i = 0 ; i < CIntfData::getLength(SeqGasData) ; ++i)
    {
      sGasData theGasData;
      CIntfData::getAt(theGasData,&SeqGasData,i);

      if (std::string(theGasData.GasType) == DEF_GC_STIRR_GAS_TYPE::Ar)
      {
        TimeStamp.Ar_Moment = theGasData.GasValue;
      }
      else if (std::string(theGasData.GasType) == DEF_GC_STIRR_GAS_TYPE::N2)
      {
        TimeStamp.N2_Moment = theGasData.GasValue;
      }
    }

    RetValue = handleMaterialHandlingReport(Event, TimeStamp, TreatmentPosition);
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

//##ModelId=462F05A5003A
bool CARCHIVER_LFMaterialHandlingWrapper::doOnLiqMatHandlingReport(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  //std::string PlantID   = Event.getPlantID();
  //std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  //long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);
  //std::string ProdOrderID = Event.getOrderID();

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_LFMaterialHandlingWrapper::doOnLiqMatHandlingReport");
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

    RetValue = handleLiqMatHandlingReport(Event);

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

//bool CARCHIVER_LFMaterialHandlingWrapper::doOnhandleUpdatePurpose(CEventMessage& Event)
//{
//  bool RetValue = false;
//
//  std::string ProductID = Event.getProductID();
//  std::string HeatID    = Event.getHeatID();
//  std::string TreatID   = Event.getTreatID();
//  std::string DataKey   = Event.getDataKey();
//
//  // Unified exception handling *******************************************************
//  std::string Scope("CARCHIVER_LFMaterialHandlingWrapper::doOnhandleUpdatePurpose");
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
//    setpDM_Interface(Event.getSender(),DM::EVENT);
//
//    seqMaterials sqMat;
//    sqMat = CIntfData::ToCORBAType(m_pDM_Interface->getMaterials(DataKey.c_str(),DATA::MinBinWeight));
//    bool isAllmat = m_pDM_Interface->getBoolean(DataKey.c_str(), DATA::AllMaterials);
//
//    RetValue = handleMinChargeableBinWeightUpdate(Event,sqMat);
//    RetValue = RetValue&&handleUpdatePurpose(Event,sqMat,isAllmat);
//    return RetValue;
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

//##ModelId=462E05C80338
void CARCHIVER_LFMaterialHandlingWrapper::initDBClasses()
{
  CARCHIVER_MaterialHandlingWrapper::initDBClasses();

  cCBS_StdConnection *pConnection = getStdConnection();

  m_pPDL_HEAT_DATA   = new CPDL_HEAT_DATA(pConnection); 
  //m_pPDL_Wire_Add    = new CPDL_WIRE_ADD(pConnection);
}


//##ModelId=462E05C90183
void CARCHIVER_LFMaterialHandlingWrapper::deleteDBClasses()
{
  CARCHIVER_MaterialHandlingWrapper::deleteDBClasses();

  if(m_pPDL_HEAT_DATA) {delete m_pPDL_HEAT_DATA;m_pPDL_HEAT_DATA = 0;}

  //if (m_pPDL_Wire_Add)    { delete m_pPDL_Wire_Add; m_pPDL_Wire_Add = 0; } 
}

