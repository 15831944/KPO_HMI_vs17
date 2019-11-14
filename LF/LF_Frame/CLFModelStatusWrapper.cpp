// Copyright (C) 2011 SMS Siemag AG

#include "CIntfData.h"
#include "CIntfLF.h"
#include "cCBS_StdEventLogFrameController.h"
#include "iSMC_DataDefinitions_s.hh"

#include "CLFModelTask.h"
#include "CLFModelStatusWrapper.h"

//##ModelId=411A1D2001EF
bool CLFModelStatusWrapper::doOnGetModelStatus(CEventMessage &Event)
{
 bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (pIntfLF && m_pModelTask ) 
  {       
    try
    {
      // TO DO

      RetValue = doModelResult(Event);
    }
    catch (...) 
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "",
        "CLFModelStatusWrapper::doOnGetModelStatus()",        
        "");    
    }
  }
  else
  {
    log("error CLFModelStatusWrapper::doOnGetModelStatus(), (pIntfLF && m_pModelTask ) == false", 1);
  }
  return RetValue;
}

