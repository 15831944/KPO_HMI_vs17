// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfEAF.h"

#include "CEAFTemperaturMeasurementWrapper.h"

//##ModelId=41580195034A
bool CEAFTemperaturMeasurementWrapper::doOnTempMeasurement( CEventMessage &Event )
{
  bool RetValue = false;
  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!m_pModelTask) 
  {
    log("error CEAFTemperaturMeasurementWrapper::doOnTempMeasurement(), (m_pModelTask) == false", 1);
    return false;
  }

  if (!pIntfEAF) return false;
 
  try
  {
    double ActTemp     = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getDouble(
	                                      Event.getDataKey().c_str(), DATA::MeasTemp);

    pIntfEAF->hndlTempMeas(ActTemp); 

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CEAFTemperaturMeasurementWrapper::doOnTempMeasurement",   ""  );          
  }
 

  return RetValue;
}

