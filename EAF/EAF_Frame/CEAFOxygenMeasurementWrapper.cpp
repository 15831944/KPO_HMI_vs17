// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfEAF.h"

#include "CEAFOxygenMeasurementWrapper.h"

//##ModelId=41123803012A
bool CEAFOxygenMeasurementWrapper::doOnOxygenMeusurement( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) return false;
  
  try
  {
    double ConcO2   = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getDouble(
                               Event.getDataKey().c_str(), DATA::MeasO2Conc);

    pIntfEAF->hndlOxygenMeas(ConcO2);

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFOxygenMeasurementWrapper::doOnOxygenMeusurement()",  ""  );          
  }
  

  return RetValue;
}

