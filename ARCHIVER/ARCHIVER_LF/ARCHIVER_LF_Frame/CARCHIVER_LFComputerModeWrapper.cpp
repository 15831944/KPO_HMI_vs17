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

#include "CARCHIVER_LFTask.h"
#include "CARCHIVER_LFComputerModeWrapper.h"
#include "DEF_GC_PLANT_DEF.h"


//##ModelId=462E2BE203E0
CARCHIVER_LFComputerModeWrapper::CARCHIVER_LFComputerModeWrapper() 
{
}

//##ModelId=462E2BE30266
CARCHIVER_LFComputerModeWrapper::~CARCHIVER_LFComputerModeWrapper()
{
  deleteDBClasses();
}

//##ModelId=462E2C4E022E
bool CARCHIVER_LFComputerModeWrapper::doOnSetComputerMode(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string Sender    = Event.getSender();
  std::string PlantID   = Event.getPlantID();
  //std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  //long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_LFComputerModeWrapper::doOnSetComputerMode");
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

    //------------------------------------------------------
    setpDM_Interface(Event.getSender(),DM::PLANT);

    seqComputerModes SeqComputerModes;
    SeqComputerModes = CIntfData::ToCORBAType(m_pDM_Interface->getComputerModes(DataKey.c_str(), DATA::ComputerModes));

    long CarNo = 0;
        
    if (DataKey == DEF_PLANT::TransferCar1)
      CarNo = 1;
    else if (DataKey == DEF_PLANT::TransferCar2)
      CarNo = 2;

    // Do included use case
    RetValue = handleSetComputerMode(Event, SeqComputerModes, CarNo);

    //------------------------------------------------------
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

//##ModelId=462E2BE501C7
void CARCHIVER_LFComputerModeWrapper::initDBClasses()
{
  CARCHIVER_ComputerModeWrapper::initDBClasses();
}

//##ModelId=462E2BE60042
void CARCHIVER_LFComputerModeWrapper::deleteDBClasses()
{
  CARCHIVER_ComputerModeWrapper::deleteDBClasses();
}

