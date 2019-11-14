// Copyright (C) 2011 SMS Siemag AG

#include "CIntfData.h"
#include "CIntfLF.h"
#include "cCBS_StdEventLogFrameController.h"
#include "iSMC_DataDefinitions_s.hh"

#include "CLFTemperaturMeasurementWrapper.h"
#include "CLFModelTask.h"

//##ModelId=41665D960141
bool CLFTemperaturMeasurementWrapper::doOnTempMeasurement(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFTemperaturMeasurementWrapper::doOnTempMeasurement(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try
  {
    double ActTemp = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getDouble(Event.getDataKey().c_str(), DATA::MeasTemp);

    std::stringstream Message ;

    if (ActTemp <= 0.0 || ActTemp == DEF::Inv_Double)
    {
      Message << "ERROR: invalid Temperature: " << ActTemp << ", it will be ignored!";
      log(Message.str(),1);
    }
    else
    {
      Message << "Set pIntfLF->hndlTempMeas " << ActTemp;
      log(Message.str(),3);
      pIntfLF->hndlTempMeas(ActTemp, true); 
      RetValue = doModelResult(Event);
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "","CLFTemperaturMeasurement_Wrapper::doOnTempMeasurement()","");    
  }

  return RetValue;
}