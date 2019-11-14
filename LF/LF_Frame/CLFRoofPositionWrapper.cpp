// Copyright (C) 2011 SMS Siemag AG

#include "CIntfData.h"
#include "CIntfLF.h"
#include "cCBS_StdEventLogFrameController.h"
#include "iSMC_DataDefinitions_s.hh"

#include "CLFRoofPositionWrapper.h"

//##ModelId=41665DED0159
bool CLFRoofPositionWrapper::doOnGantrySwungIn(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFRoofPositionWrapper::doOnGantrySwungIn(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try
  {
    pIntfLF->hndlGantryPosIn();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFRoofPositionWrapper::doOnGantrySwungIn()", ""  );    
  }

  return RetValue;
}

//##ModelId=41665DED038A
bool CLFRoofPositionWrapper::doOnGantrySwungOut(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFRoofPositionWrapper::doOnGantrySwungOut(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try
  {
    pIntfLF->hndlGantryPosOut();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFRoofPositionWrapper::doOnGantrySwungOut()", ""  );    
  }

  return RetValue;
}

//##ModelId=41665DEE01B4
bool CLFRoofPositionWrapper::doOnRoofInDownPos(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFRoofPositionWrapper::doOnRoofInDownPos(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try
  {
    pIntfLF->hndlRoofPosDown();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFRoofPositionWrapper::doOnRoofInDownPos()", ""  );    
  }


  return RetValue;
}

//##ModelId=41665DEF000A
bool CLFRoofPositionWrapper::doOnRoofInUpPos(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFRoofPositionWrapper::doOnRoofInUpPos(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try
  {
    pIntfLF->hndlRoofPosUp();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFRoofPositionWrapper::doOnRoofInUpPos()", ""  );    
  }

  return RetValue;
}