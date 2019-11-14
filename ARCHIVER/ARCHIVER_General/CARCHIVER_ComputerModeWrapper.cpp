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
#include "CEventMessage.h"

#include "CARCHIVER_Task.h"
#include "CARCHIVER_ComputerModeWrapper.h"


//##ModelId=45E533B00385
CARCHIVER_ComputerModeWrapper::CARCHIVER_ComputerModeWrapper()
{
}

//##ModelId=45E533B1026E
CARCHIVER_ComputerModeWrapper::~CARCHIVER_ComputerModeWrapper()
{
  deleteDBClasses();
}

//##ModelId=4666840202EC
bool CARCHIVER_ComputerModeWrapper::handleSetComputerMode(CEventMessage& Event, seqComputerModes& SeqComputerModes, long CarNo)
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
  std::string Scope("CARCHIVER_MaterialHandlingWrapper::handleMaterialHandlingReport");
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

    RetValue = m_pPD_COMP_DATA->writeStatus(HeatID, TreatID, ActPlant,SeqComputerModes);
    
	if(!RetValue)
    {
      log("ERROR: failed to write computer modes into PD_COMP_DATA",1);
    }
  }
  catch (cCBS_DBExc &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Scope.c_str(), ExceptionMsg.str().c_str()); 
    RetValue = false;
    handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(), Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(), Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(...)
  {
    std::string Msg("Unknown exception:");
    Msg += ExceptionMsg.str();
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "", Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}

//##ModelId=45E533B201CF
void CARCHIVER_ComputerModeWrapper::initDBClasses()
{
  cCBS_StdConnection *pConnection = getStdConnection();

  m_pPD_COMP_DATA       = new CPD_COMP_DATA(pConnection);
  m_pGC_Plant_Container = new CGC_Plant_Container(pConnection);
}

//##ModelId=45E533B30068
void CARCHIVER_ComputerModeWrapper::deleteDBClasses()
{
  if (m_pPD_COMP_DATA) { delete m_pPD_COMP_DATA; m_pPD_COMP_DATA = 0; }
  if (m_pGC_Plant_Container) { delete m_pGC_Plant_Container; m_pGC_Plant_Container = 0; }
}

