// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfEAF.h"

#include "CEAFRoofPositionWrapper.h"

//##ModelId=41121C7D0105
bool CEAFRoofPositionWrapper::doOnDoorOpened( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF )return false;
  try
  {
    pIntfEAF->hndlDoorOpen();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFRoofPositionWrapper::doOnDoorOpened()",       ""    );          
  }

  return RetValue;
}

//##ModelId=41121C9302EA
bool CEAFRoofPositionWrapper::doOnDoorClosed( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF  ) return false;
  
  try
  {
    pIntfEAF->hndlDoorClosed();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CEAFRoofPositionWrapper::doOnDoorClosed()",    ""   );          
  }
  

  return RetValue;
}



//##ModelId=4158192C01F9
bool CEAFRoofPositionWrapper::doOnGantrySwungIn( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) return false;
  
  try
  {
    pIntfEAF->hndlGantryPosIn();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFRoofPositionWrapper::doOnGantrySwungIn()",      ""   );          
  }
  

  return RetValue;
}

//##ModelId=4158192D00A6
bool CEAFRoofPositionWrapper::doOnGantrySwungOut( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) return false;
  
  try
  {
    pIntfEAF->hndlGantryPosOut();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFRoofPositionWrapper::doOnGantrySwungOut()",    ""  );          
  }
  

  return RetValue;
}

//##ModelId=4158192D0289
bool CEAFRoofPositionWrapper::doOnRoofInDownPos( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) return false;
  
  try
  {
    pIntfEAF->hndlRoofPosDown();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFRoofPositionWrapper::doOnRoofInDownPos()",    ""   );          
  }
  

  return RetValue;
}

//##ModelId=4158192E00DC
bool CEAFRoofPositionWrapper::doOnRoofInUpPos( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) return false;
  
  try
  {
    pIntfEAF->hndlRoofPosUp();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFRoofPositionWrapper::doOnRoofInUpPos()",     ""   );          
  }
  

  return RetValue;
}

