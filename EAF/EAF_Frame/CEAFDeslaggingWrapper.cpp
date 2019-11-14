// Copyright (C) 2004 SMS Demag AG

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfEAF.h"

#include "CEAFDeslaggingWrapper.h"


//##ModelId=4112390E005D
bool CEAFDeslaggingWrapper::doOnDeslaggingStart( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF) 
  {
    log("error CEAFDeslaggingWrapper::doOnDeslaggingStart(), (pIntfEAF) == false", 1);
    return false;
  }
  try 
  {
    pIntfEAF->hndlDeslagStart();   

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFDeslaggingWrapper::doOnDeslaggingStart()",   ""   );    
  }

  return RetValue;
}

//##ModelId=411239200387
bool CEAFDeslaggingWrapper::doOnDeslaggingEnd( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) return false;
  
  try 
  {
    pIntfEAF->hndlDeslagStop();   

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFDeslaggingWrapper::doOnDeslaggingEnd()",   ""  );    
  }

  return RetValue;
}

