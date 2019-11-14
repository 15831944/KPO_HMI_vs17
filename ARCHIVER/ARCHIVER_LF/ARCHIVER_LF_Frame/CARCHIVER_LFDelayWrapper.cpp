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

#include "CARCHIVER_LFDelayWrapper.h"



//##ModelId=462F15A903A4
CARCHIVER_LFDelayWrapper::CARCHIVER_LFDelayWrapper()
{
}

//##ModelId=462F15AA029A
CARCHIVER_LFDelayWrapper::~CARCHIVER_LFDelayWrapper()
{
}

//do in DM, remove later
//##ModelId=462F15DB02A7
//bool CARCHIVER_LFDelayWrapper::doOnDelayStatus(CEventMessage& Event)
//{
//  bool RetValue = false;
//
//  std::string ProductID = Event.getProductID();
//  std::string HeatID    = Event.getHeatID();
//  std::string TreatID   = Event.getTreatID();
//  std::string DataKey   = Event.getDataKey();
//
//  // Unified exception handling *******************************************************
//  std::string Scope("CARCHIVER_LFDelayWrapper::doOnDelayStatus");
//  std::stringstream ExceptionMsg;
//  ExceptionMsg << "Handling event: " << Event.getSender()
//    << ", " << ProductID << ", " << HeatID
//    << ", " << TreatID   << ", " << DataKey;
//  //***********************************************************************************
//
//  try
//  {   
//    RetValue = handleDelayStatus(Event);
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

//##ModelId=462F15AC0168
void CARCHIVER_LFDelayWrapper::initDBClasses()
{
  CARCHIVER_DelayWrapper::initDBClasses();

}

//##ModelId=462F15AD0004
void CARCHIVER_LFDelayWrapper::deleteDBClasses()
{
  CARCHIVER_DelayWrapper::deleteDBClasses();

}

