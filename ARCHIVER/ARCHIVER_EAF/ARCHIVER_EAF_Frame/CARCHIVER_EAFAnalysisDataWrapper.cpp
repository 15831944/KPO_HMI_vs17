// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_S.hh"
#include "iEventMessages_s.hh"
#include "iDM_Interface_s.hh"

#include "CIntfData.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_DBExc.h"
#include "CEventMessage.h"
#include "CDateTime.h"
#include "CARCHIVER_EAFAnalysisDataWrapper.h"
#include "DEF_GC_PLANT_DEF.h"

//##ModelId=41DAAC9B00C9
CARCHIVER_EAFAnalysisDataWrapper::CARCHIVER_EAFAnalysisDataWrapper()
{
}

//##ModelId=41DAAC9B0318
CARCHIVER_EAFAnalysisDataWrapper::~CARCHIVER_EAFAnalysisDataWrapper()
{
  deleteDBClasses();
}

bool CARCHIVER_EAFAnalysisDataWrapper::doOnSampleTaken(CEventMessage& Event, bool Steel)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string Sender    = Event.getSender();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string ProdOrderID = Event.getOrderID();

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_EAFSignalsAndMeasurementWrapper::doOnSampleTaken");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************

  setpDM_Interface(Sender,DM::PRODUCT);
  long TreatmentPosition = m_pDM_Interface->getLong(ProductID.c_str(), DATA::TreatmentPosition);

  try
  {
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }

    writeSample(Event, TreatmentPosition);
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
//##ModelId=41DAAC9801FB
void CARCHIVER_EAFAnalysisDataWrapper::deleteDBClasses()
{
  CARCHIVER_AnalysisDataWrapper::deleteDBClasses();

}

//##ModelId=41DAAC9901D5
void CARCHIVER_EAFAnalysisDataWrapper::initDBClasses()
{
  CARCHIVER_AnalysisDataWrapper::initDBClasses();
}
