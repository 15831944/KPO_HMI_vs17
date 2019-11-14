// Copyright (C) 2011 SMS Siemag AG

#include "CIntfData.h"
#include "CIntfLF.h"
#include "cCBS_StdEventLogFrameController.h"
#include "iSMC_DataDefinitions_s.hh"

#include "CLFModelTask.h"
#include "CLFPurposeHandlingWrapper.h"

//##ModelId=41655D6800A9
bool CLFPurposeHandlingWrapper::doOnUpdatePurpose(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (pIntfLF && m_pModelTask ) 
  {
    try
    {
      seqStringList Purposes = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getStringList(
                                             Event.getDataKey().c_str(), DATA::UpdatedPurpose));
      std::string PurposeName;

	    for (int x = 0; x < CIntfData::getLength(Purposes); x++) 
      {
        CIntfData::getAt(PurposeName, Purposes, x);
        pIntfLF->hndlUpdatePurpose(PurposeName);
      }

      // Sequence Diagram: get model results / Call Sequence
      RetValue = doModelResult(Event);
    }
    catch (...) 
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "",
        "CLFPurposeHandlingWrapper::doOnUpdatePurpose",
        ""
      );          
    }
  }
  else
  {
    log("error CLFPurposeHandlingWrapper::doOnUpdatePurpose(), (pIntfLF && m_pModelTask) == false", 1);
  }

  return RetValue;
}

