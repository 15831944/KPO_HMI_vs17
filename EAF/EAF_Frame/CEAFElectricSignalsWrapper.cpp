// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfEAF.h"

#include "CEAFElectricSignalsWrapper.h"


//##ModelId=41121E110340
bool CEAFElectricSignalsWrapper::doOnRegCurvNumChange( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF )
  {
    log("error CEAFElectricSignalsWrapper::doOnRegCurvNumChange(), (pIntfEAF) == false", 1);
    return false;
  }
  
  try
  {
    long EltrdRegCurve    = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getLong(
                               Event.getDataKey().c_str(), DATA::ElectrodRegCurve);

    pIntfEAF->hndlNewEltrdReguCurve(EltrdRegCurve);

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFElectricSignalsWrapper::doOnRegCurvNumChange()",     ""  );          
  }


  return RetValue;
}

//##ModelId=41121F2F03D1
bool CEAFElectricSignalsWrapper::doOnActivWallTempContr( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) return false;
  
  try
  {
    pIntfEAF->actvWallTempCtrl();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFElectricSignalsWrapper::doOnActivWallTempContr()",      ""   );          
  }
  

  return RetValue;
}

//##ModelId=41121F910117
bool CEAFElectricSignalsWrapper::doOnDeactivVallTempContr( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF )return false;
  
  try
  {
    pIntfEAF->deactvWallTempCtrl();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFElectricSignalsWrapper::doOnDeactivVallTempContr()",   ""  );          
  }
  
  return RetValue;
}



//##ModelId=4158273E0307
bool CEAFElectricSignalsWrapper::doOnElectrodInOperationPos( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!m_pModelTask) 
  {
    log("error CEAFElectricSignalsWrapper::doOnElectrodInOperationPosd(), (m_pModelTask) == false", 1);
    return false;
  }
  if (!pIntfEAF ) return false;
  
  try
  {
    pIntfEAF->hndlElectrodesInOpPos();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFElectricSignalsWrapper::doOnElectrodInOperationPos()",    ""  );          
  }


  return RetValue;
}

bool CEAFElectricSignalsWrapper::doOnElectrodOutOperationPos( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!m_pModelTask) 
  {
    log("error CEAFElectricSignalsWrapper::doOnElectrodOutOperationPos(), (m_pModelTask) == false", 1);
    return false;
  }
  if (!pIntfEAF ) return false;

  log("doOnElectrodOutOperationPos() - for test", 1);

  try
  {
    pIntfEAF->hndlElectrodeLifted();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFElectricSignalsWrapper::doOnElectrodOutOperationPos()",    ""  );          
  }


  return RetValue;
}

//##ModelId=4158273F021A
bool CEAFElectricSignalsWrapper::doOnElectrodLifted( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!m_pModelTask) 
  {
    log("error CEAFElectricSignalsWrapper::doOnElectrodLifted(), (m_pModelTask) == false", 1);
    return false;
  }
  if (!pIntfEAF ) return false;
  
  try
  {
    pIntfEAF->hndlElectrodeLifted();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFElectricSignalsWrapper::doOnElectrodLifted()",  ""  );          
  }
  

  return RetValue;
}

//##ModelId=415827400370
bool CEAFElectricSignalsWrapper::doOnFurnBreakerOn( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) return false;
  
  try
  {
    pIntfEAF->hndlFurnBrkrOn();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFElectricSignalsWrapper::doOnFurnBreakerOn()",    ""   );          
  }


  return RetValue;
}

//##ModelId=41582741012D
bool CEAFElectricSignalsWrapper::doOnPowerOff( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) return false;

  try
  {
    pIntfEAF->hndlPowerOff();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFElectricSignalsWrapper::doOnPowerOff()",   ""   );          
  }
  

  return RetValue;
}

//##ModelId=41582741030D
bool CEAFElectricSignalsWrapper::doOnPowerOn( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) return false;
  
  try
  {
    pIntfEAF->hndlPowerOn();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFElectricSignalsWrapper::doOnPowerOn()",   ""   );          
  }
  

  return RetValue;
}

//##ModelId=41582742014A
bool CEAFElectricSignalsWrapper::doOnTapChangeFinished( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) return false;
  
  try
  {
    long NewVoltTapNo     = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PLANT)->getLong(DEF_PLANT::Furnace, DATA::VoltTapNo);

    pIntfEAF->hndlTapChgEnd(NewVoltTapNo);

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFElectricSignalsWrapper::doOnTapChangeFinished()",  ""  );          
  }
  

  return RetValue;
}

//##ModelId=4158274203A6
bool CEAFElectricSignalsWrapper::doOnTapChangeStart( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) return false;
  
  try
  {
    pIntfEAF->hndlTapChgStart();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFElectricSignalsWrapper::doOnTapChangeStart()",    ""   );          
  }
  

  return RetValue;
}

//##ModelId=41582743034C
bool CEAFElectricSignalsWrapper::doOnFurnBreakerOff( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) return false;
  
  try
  {
    double MeasConsElec    = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getLong(
                               Event.getDataKey().c_str(), DATA::ElecCons); //DATA::ElecCons
    
    pIntfEAF->hndlFurnBrkrOff(MeasConsElec);

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFElectricSignalsWrapper::doOnFurnBreakerOff()",    ""   );          
  }
  

  return RetValue;
}

