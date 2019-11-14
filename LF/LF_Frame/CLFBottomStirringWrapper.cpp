// Copyright (C) 2011 SMS Siemag AG

#include "CIntfData.h"
#include "CIntfLF.h"
#include "cCBS_StdEventLogFrameController.h"
#include "iSMC_DataDefinitions_s.hh"
#include "CStirringDataHandler.h"

#include "CLFModelTask.h"
#include "CLFBottomStirringWrapper.h"

//##ModelId=411247B50146
bool CLFBottomStirringWrapper::doOnStirringEnd(CEventMessage &Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFBottomStirringWrapper::doOnStirringEnd(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try 
  {
    seqStirringData StirringAmount;
    sStirringData   StirringData;
    std::string     GasType;
    double          GasValue = 0.0;

    StirringAmount  = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT)->getStirringData(Event.getProductID().c_str(), DATA::StirringAmount));

    CStirringDataHandler StirringDataHandler(StirringAmount);
    seqGasData StirrAmountGasData = StirringDataHandler.getAccumulatedGasDataSeq(); // equals obsolete DEF_DEVICES::Total

    for (int i = 0; i < CIntfData::getLength(StirrAmountGasData); i++) 
    {
      sGasData GasData;
      CIntfData::getAt(GasData,StirrAmountGasData,i);

      if ( GasData.GasValue > 0 )
      {
        GasType     = GasData.GasType;
        GasValue    = GasData.GasValue;
        pIntfLF->hndlBotStirrEnd(GasType, GasValue);
      }
    }

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFBottomStirringWrapper::doOnStirringEnd()", ""  );    
  }

  return RetValue;
}

//##ModelId=411247C901E8
bool CLFBottomStirringWrapper::doOnStirringStart(CEventMessage &Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFBottomStirringWrapper::doOnStirringStart(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try 
  {
    std::string StirringGasType  = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT)->getString(Event.getProductID().c_str(), DATA::StirringGasType ));

    pIntfLF->hndlBotStirrStart(StirringGasType);

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFBottomStirringWrapper::doOnStirringStart()", ""  );    
  }

  return RetValue;
}

//##ModelId=411A19DE013E
bool CLFBottomStirringWrapper::doOnStirringBypassOff(CEventMessage &Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFBottomStirringWrapper::doOnStirringBypassOff(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try 
  {
    pIntfLF->hndlBotStirrBypassOff();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFBottomStirringWrapper::doOnStirringBypassOff()", ""  );    
  }


  return RetValue;
}

//##ModelId=411A1A6600E0
bool CLFBottomStirringWrapper::doOnStirringBypassOn(CEventMessage &Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();
  
  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFBottomStirringWrapper::doOnStirringBypassOn(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try 
  {
    pIntfLF->hndlBotStirrBypassOn();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFBottomStirringWrapper::doOnStirringBypassOn()", ""  );    
  }

  return RetValue;
}
