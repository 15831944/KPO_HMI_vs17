// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfEAF.h"

#include "CEAFModelTask.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CEAFOxygenSideLancesWrapper.h"

//##ModelId=41122A9B01C3
bool CEAFOxygenSideLancesWrapper::doOnOxygenSideLanceStart( CEventMessage &Event )
{
  bool RetValue = false;

#if defined(EAF_BURNER)     

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF) return false;
  
  try
  {
		long lanceNo     = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getLong(Event.getDataKey().c_str(), DATA::LanceId);

    pIntfEAF->hndlOxySideLanceStart(lanceNo);  // LanceNo

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFOxygenSideLancesWrapper::doOnOxygenSideLanceStart()",    ""  );          
  }

#endif

  return RetValue;
}

//##ModelId=41122AB6005C
bool CEAFOxygenSideLancesWrapper::doOnOxygenSideLanceStop( CEventMessage &Event )
{
  bool RetValue = false;

#if defined(EAF_BURNER)     

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF) return false;
  
  try
  {
		long lanceNo     = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getLong(Event.getDataKey().c_str(), DATA::LanceId);

    pIntfEAF->hndlOxySideLanceStop(lanceNo);  // LanceNo

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFOxygenSideLancesWrapper::doOnOxygenSideLanceStop()",    ""    );          
  }

#endif

  return RetValue;
}

