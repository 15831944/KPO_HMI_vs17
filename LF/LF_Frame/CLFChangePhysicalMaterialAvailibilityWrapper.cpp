// Copyright (C) 2011 SMS Siemag AG

#include "CIntfLF.h"
#include "CLFModelTask.h"
#include "iSMC_DataDefinitions_s.hh"
#include "cCBS_StdEventLogFrameController.h"
#include "CLFChangePhysicalMaterialAvailibilityWrapper.h"


//##ModelId=4166902303D5
bool CLFChangePhysicalMaterialAvailibilityWrapper::doOnChangedPhysicalMatAvail(CEventMessage& Event)
{
  bool RetValue = false;
  
  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFChangePhysicalMaterialAvailibilityWrapper::doOnChangedPhysicalMatAvail(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try 
  {
    string ActMatCode = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(Event.getDataKey().c_str(), DATA::MatCode));

    pIntfLF->hndlUpdateAvailMat(ActMatCode);

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "","CLFChangePhysicalMaterialAvailibilityWrapper::doOnChangedPhysicalMatAvail() ", "" );    
  }

  return RetValue;
}

