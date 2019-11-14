// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfEAF.h"

#include "cCBS_StdEventLogFrameController.h"
#include "CEAFJetModuleWrapper.h"



//##ModelId=4112253B0129
bool CEAFJetModuleWrapper::doOnJetModuleStart( CEventMessage &Event )
{
  bool RetValue = false;

#if defined EAF_JET_MODULES

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF) 
  {
    log("error CEAFJetModuleWrapper::doOnJetModuleStart(), (pIntfEAF) == false", 1);
    return false;
  }
  
  try
  {
    pIntfEAF->hndlJetModuleStart(0); 

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFJetModuleWrapper::doOnJetModuleStart()",   ""  );          
  }
#endif
  return RetValue;
}

//##ModelId=41122551023C
bool CEAFJetModuleWrapper::doOnJetModuleStop( CEventMessage &Event )
{
  bool RetValue = false;

#ifdef EAF_JET_MODULES

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF) 
  {
    log("error CEAFJetModuleWrapper::doOnJetModuleStop(), (pIntfEAF) == false", 1);
    return false;
  }
  
  try
  {
    pIntfEAF->hndlJetModuleStop(0); 

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFJetModuleWrapper::doOnJetModuleStop()",    ""   );          
  }

#endif

  return RetValue;
}

