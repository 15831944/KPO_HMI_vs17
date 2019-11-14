// Copyright (C) 2011 SMS Siemag AG

#include "CIntfData.h"
#include "CIntfLF.h"
#include "cCBS_StdEventLogFrameController.h"
#include "iSMC_DataDefinitions_s.hh"

#include "CLFElectricSignalsWrapper.h"

//##ModelId=41665E4E0003
bool CLFElectricSignalsWrapper::doOnElectrodInOperationPos(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFElectricSignalsWrapper::doOnElectrodInOperationPos(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }

  try
  {
    long ElecPos = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getLong(Event.getDataKey().c_str(), DATA::ElecPosUp);

    if (ElecPos == DEF_GEN_STATES::No || ElecPos == DEF::Inv_Long)
      pIntfLF->hndlElectrodesInOpPos();
    else
      pIntfLF->hndlElectrodeLifted();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFElectricSignalsWrapper::doOnElectrodInOperationPos()", ""  );    
  }


  return RetValue;
}

bool CLFElectricSignalsWrapper::doOnElectrodOutOperationPos(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFElectricSignalsWrapper::doOnElectrodOutOperationPos(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try
  {
    pIntfLF->hndlElectrodeLifted();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFElectricSignalsWrapper::doOnElectrodOutOperationPos()", ""  );    
  }

  return RetValue;
}

//##ModelId=41665E4E02F2
bool CLFElectricSignalsWrapper::doOnElectrodLifted(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();
    
  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFElectricSignalsWrapper::doOnElectrodLifted(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }

  try
  {
    pIntfLF->hndlElectrodeLifted();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFElectricSignalsWrapper::doOnElectrodLifted()", ""  );    
  }

  return RetValue;
}

//##ModelId=41665E4F0113
bool CLFElectricSignalsWrapper::doOnFurnBreakerOff(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFElectricSignalsWrapper::doOnFurnBreakerOff(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try
  {
    //double ElecCons = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getDouble(Event.getDataKey().c_str(), DATA::ElecCons );
    double ElecCons = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT)->getDouble(Event.getProductID().c_str(), DATA::ElecCons );

    pIntfLF->hndlFurnBrkrOff(ElecCons);

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFElectricSignalsWrapper::doOnFurnBreakerOff()", ""  );    
  }

  return RetValue;
}

//##ModelId=41665E4F031E
bool CLFElectricSignalsWrapper::doOnFurnBreakerOn(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFElectricSignalsWrapper::doOnFurnBreakerOn(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try
  {
    pIntfLF->hndlFurnBrkrOn();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFElectricSignalsWrapper::doOnFurnBreakerOff()", ""  );    
  }

  return RetValue;
}

//##ModelId=41665E50010D
bool CLFElectricSignalsWrapper::doOnPowerOff(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFElectricSignalsWrapper::doOnPowerOff(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try
  {
    pIntfLF->hndlPowerOff();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFElectricSignalsWrapper::doOnPowerOff()", ""  );    
  }

  return RetValue;
}

//##ModelId=41665E5002A8
bool CLFElectricSignalsWrapper::doOnPowerOn(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFElectricSignalsWrapper::doOnPowerOn(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try
  {
    pIntfLF->hndlPowerOn();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFElectricSignalsWrapper::doOnPowerOn()", ""  );    
  }

  return RetValue;
}

//##ModelId=41665E5100A0
bool CLFElectricSignalsWrapper::doOnTapChangeFinished(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();
  
  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFElectricSignalsWrapper::doOnTapChangeFinished(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try
  {
    std::stringstream tmp;
    tmp << "Tap Change Finished: "<< endl;
    long VoltTap  = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PLANT)->getLong(Event.getDataKey().c_str(), DATA::VoltTapNo );
     
    if (VoltTap==DEF::Inv_Long)
    {
      tmp << "Event Interface VoltTap is invalid " << VoltTap << endl;
      VoltTap  = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT)->getLong(Event.getProductID().c_str(), DATA::VoltTapNo );        
    }
    if (VoltTap==DEF::Inv_Long)
    {
      tmp << "Product Interface VoltTap is invalid " << VoltTap << endl;
      VoltTap = 0;
      tmp << "Use Tap " << VoltTap << endl;
    }
    tmp << "Tap " << VoltTap;
    log (tmp.str(),1);
    pIntfLF->hndlTapChgEnd(VoltTap);


    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFElectricSignalsWrapper::doOnTapChangeFinished()", ""  );    
  }

  return RetValue;
}

//##ModelId=41665E51024F
bool CLFElectricSignalsWrapper::doOnTapChangeStart(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFElectricSignalsWrapper::doOnTapChangeStart(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try
  {
    pIntfLF->hndlTapChgStart();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFElectricSignalsWrapper::doOnTapChangeStart()", ""  );    
  }

  return RetValue;
}

