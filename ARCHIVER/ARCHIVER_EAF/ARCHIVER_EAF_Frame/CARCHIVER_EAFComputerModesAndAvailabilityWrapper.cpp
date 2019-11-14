// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_S.hh"
#include "iEventMessages_s.hh"
#include "iDM_Interface_s.hh"

#include "CIntfData.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_DBExc.h"
#include "cCBS_StdCORBA_Task.h"
#include "CEventMessage.h"
#include "CARCHIVER_EAFComputerModesAndAvailabilityWrapper.h"
#include "DEF_GC_PLANT_DEF.h"

//##ModelId=41DAB08B02E5
CARCHIVER_EAFComputerModesAndAvailabilityWrapper::~CARCHIVER_EAFComputerModesAndAvailabilityWrapper()
{
  deleteDBClasses();
}

//##ModelId=41DAB08B03AF
CARCHIVER_EAFComputerModesAndAvailabilityWrapper::CARCHIVER_EAFComputerModesAndAvailabilityWrapper()
{
}

//##ModelId=41DAB460015F
bool CARCHIVER_EAFComputerModesAndAvailabilityWrapper::doOnSetComputerMode(CEventMessage& Event)
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
  std::string Scope("CARCHIVER_EAFComputerModesAndAvailabilityWrapper::doOnSetComputerMode");
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

    seqComputerModes SeqComputerModes;
    setpDM_Interface(Event.getSender(),DM::PLANT);
    SeqComputerModes = CIntfData::ToCORBAType(m_pDM_Interface->getComputerModes(DEF_PLANT::Furnace,DATA::ComputerModes));

    // Do included use case
    RetValue = handleSetComputerMode(Event, SeqComputerModes);

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

//##ModelId=41DAB08A0077
void CARCHIVER_EAFComputerModesAndAvailabilityWrapper::deleteDBClasses()
{
  CARCHIVER_ComputerModeWrapper::deleteDBClasses();
}

//##ModelId=41DAB08A01C2
void CARCHIVER_EAFComputerModesAndAvailabilityWrapper::initDBClasses()
{
  CARCHIVER_ComputerModeWrapper::initDBClasses();
}

