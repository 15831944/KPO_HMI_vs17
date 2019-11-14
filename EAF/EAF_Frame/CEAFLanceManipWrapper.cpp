// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfEAF.h"

#include "CEAFLanceManipWrapper.h"
#include "CGCE_INJECTION_TYPE.h"


//##ModelId=41122602015B
bool CEAFLanceManipWrapper::doOnManipGasLanceStart( CEventMessage &Event )
{
  bool RetValue = false;

  if (!m_pModelTask) 
  {
    log("error CEAFLanceManipWrapper::doOnManipGasLanceStart(), (m_pModelTask) == false", 1);
    return false;
  }

   #if defined (EAF_GAS_LANCES)

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) return false;
  try
  {
    
    long lanceNo     = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getLong(Event.getDataKey().c_str(), DATA::LanceId);

    pIntfEAF->hndlManipGasLanceStart(lanceNo);

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFLanceManipWrapper::doOnManipGasLanceStart()",   ""  );          
  }
  
  #endif


  return RetValue;
}

//##ModelId=4112261D0081
bool CEAFLanceManipWrapper::doOnManipGasLanceStop( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) return false;
  
  if (!m_pModelTask) 
  {
    log("error CEAFLanceManipWrapper::doOnManipGasLanceStop(), (m_pModelTask) == false", 1);
    return false;
  }

   #if defined (EAF_GAS_LANCES)
  try
  {
    long lanceNo     = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getLong(Event.getDataKey().c_str(), DATA::LanceId);

    pIntfEAF->hndlManipGasLanceStop(lanceNo);

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFLanceManipWrapper::doOnManipGasLanceStop()",  ""  );          
  }
  
  #endif


  return RetValue;
}

//##ModelId=4112263D01B7
bool CEAFLanceManipWrapper::doOnManipInjLanceStart( CEventMessage &Event )
{
  bool RetValue = false;

  #if defined (EAF_INJECTION_LANCES) 

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) return false;

  try
  {
    std::string  InjectType         = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(Event.getProductID().c_str(), DATA::InjectType ));

    // find purpose code for current injection type
    std::string RelatedPurpCode = m_pGCE_INJECTION_TYPE->getPurposeCodeByInjType(InjectType);

    if ( RelatedPurpCode != CSMC_DBData::unspecString ) 
    {
      pIntfEAF->hndlManipInjectLanceStart(RelatedPurpCode);

      // Sequence Diagram: get model results / Call Sequence
      RetValue = doModelResult(Event);
    }
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFLanceManipWrapper::doOnManipInjLanceStart()",  ""  );          
  }
  #endif

  return RetValue;
}

//##ModelId=4112265700C7
bool CEAFLanceManipWrapper::doOnManipInjLanceStop( CEventMessage &Event )
{
  bool RetValue = false;

  #if defined (EAF_INJECTION_LANCES) 

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) return false;
  
  try
  {
    std::string  InjectType         = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(Event.getProductID().c_str(), DATA::InjectType ));

    // find purpose code for current injection type
    std::string RelatedPurpCode = m_pGCE_INJECTION_TYPE->getPurposeCodeByInjType(InjectType);

    if ( RelatedPurpCode != CSMC_DBData::unspecString ) 
    {
      pIntfEAF->hndlManipInjectLanceStop(RelatedPurpCode);

      // Sequence Diagram: get model results / Call Sequence
      RetValue = doModelResult(Event);
    }
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFLanceManipWrapper::doOnManipInjLanceStop()",   ""   );          
  }
  #endif

  return RetValue;
}


