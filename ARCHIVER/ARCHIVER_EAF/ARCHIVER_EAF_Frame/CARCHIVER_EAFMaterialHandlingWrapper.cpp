// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"
#include "iEventMessages_s.hh"
#include "iDM_Interface_s.hh"

#include "cCBS_DBExc.h"
#include "cCBS_StdEventLogFrameController.h"

#include "CStirringDataHandler.h"
#include "CIntfData.h"
#include "CEventMessage.h"
#include "CDataConversion.h"

#include "DEF_GC_HEAT_STATUS.h"

#include "CARCHIVER_EAFMaterialHandlingWrapper.h"

#include "DEF_GC_STIRR_GAS_TYPE.h"

CARCHIVER_EAFMaterialHandlingWrapper::CARCHIVER_EAFMaterialHandlingWrapper()
{
}

CARCHIVER_EAFMaterialHandlingWrapper::~CARCHIVER_EAFMaterialHandlingWrapper()
{
  deleteDBClasses(); 
}

void CARCHIVER_EAFMaterialHandlingWrapper::deleteDBClasses()
{
  CARCHIVER_MaterialHandlingWrapper::deleteDBClasses();
}

void CARCHIVER_EAFMaterialHandlingWrapper::initDBClasses()
{
  CARCHIVER_MaterialHandlingWrapper::initDBClasses();
}

bool CARCHIVER_EAFMaterialHandlingWrapper::doOnMaterialHandlingReport(CEventMessage& Event)
{
  bool RetValue = false;
  std::string ProductID = Event.getProductID();

  setpDM_Interface(Event.getSender(),DM::PRODUCT);
  seqStirringData StirringAmount = CIntfData::ToCORBAType(m_pDM_Interface->getStirringData(ProductID.c_str(),DATA::StirringAmount));

  double ElecCons                = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::ElecCons);
  long TreatmentPosition         = m_pDM_Interface->getLong(ProductID.c_str(), DATA::TreatmentPosition);

  CStirringDataHandler StirringDataHandler(StirringAmount);
  seqGasData SeqGasData = StirringDataHandler.getAccumulatedGasDataSeq(); // equals obsolete DEF_DEVICES::Total

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

  RetValue = handleMaterialHandlingReport(Event,TimeStamp, TreatmentPosition);
  return RetValue;
}

bool CARCHIVER_EAFMaterialHandlingWrapper::doOnLiqMatHandlingReport(CEventMessage& Event)
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
  std::string CustHeatID;

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_GENMaterialHandlingReport::doOnLiqMatHandlingReport");
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

bool CARCHIVER_EAFMaterialHandlingWrapper::UpdateLadleData(double RemNettWgt,double GrossWgt,double RemSteelWgt,double RemSlagWgt,long ScullMass,long Location,long Deslaged)
{
  bool RetValue = false;

  // columns removed foem table
  // m_pPD_LADLE->setGROSSWEIGHT(GrossWgt);
  m_pPD_LADLE->setSCULLMASS(ScullMass);
  m_pPD_LADLE->setDESLAGGED(Deslaged);
  if (Location != DEF::Inv_Long)
    m_pPD_LADLE->setLADLEPOSID(Location);

  RetValue = m_pPD_LADLE->update();
  if (RetValue)
    m_pPD_LADLE->commit();
  else
    m_pPD_LADLE->rollback();

  return RetValue;
}

bool CARCHIVER_EAFMaterialHandlingWrapper::doBasketDischarge(CEventMessage& Event)
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
  std::string Scope("CARCHIVER_EAFMaterialHandlingWrapper::doBasketDischarge");
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

    if (Message == EAF_EvMsg::evEAFRoofArrivesInUpPosition)
    {
      handleBasketDischargeStart(Event, "", SeqGasData, ElecCons);
    }
    else if (Message == EAF_EvMsg::evEAFRoofArrivesInDownPosition)
    {
      handleBasketDischarged(Event, "", SeqGasData, ElecCons);
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

