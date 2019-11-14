// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfEAF.h"

#include "CEAFTappingLadleWrapper.h"

bool CEAFTappingLadleWrapper::doOnLadleStirringStart( CEventMessage &Event )
{
  bool RetValue = false;
 
  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) return false;
  
  try 
  {
    std::string GasType = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT)->getString(Event.getProductID().c_str(), DATA::StirringGasType ));

    pIntfEAF->hndlLadleStirrStart(GasType);

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFTappingLadleWrapper::doOnLadleStirringStart()",   ""  );    
  }
  

  return RetValue;
}

bool CEAFTappingLadleWrapper::doOnLadleStirringStop( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) return false;
  
  try 
  {
    pIntfEAF->hndlLadleStirrEnd();   

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFTappingLadleWrapper::doOnLadleStirringStop()",  "" );    
  }
  
  return RetValue;
}

bool CEAFTappingLadleWrapper::doOnFurnaceBottomStirringStart( CEventMessage &Event )
{
  bool RetValue = false;

#if defined (EAF_BOTTOM_STIRRING)
 
  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) return false;
  
  try 
  {
    std::string GasType = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT)->getString(Event.getProductID().c_str(), DATA::StirringGasType ));

    pIntfEAF->hndlFurnBottomStirringStart(GasType); 

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFTappingLadleWrapper::doOnFurnaceBottomStirringStart()",   ""  );    
  }

#endif  

  return RetValue;
}


bool CEAFTappingLadleWrapper::doOnFurnaceBottomStirringStop( CEventMessage &Event )
{
  bool RetValue = false;

#if defined (EAF_BOTTOM_STIRRING)

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) return false;
  
  try 
  {
    pIntfEAF->hndlFurnBottomStirringEnd();   

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFTappingLadleWrapper::doOnFurnaceBottomStirringStop()",  "" );    
  }
#endif

  return RetValue;
}
