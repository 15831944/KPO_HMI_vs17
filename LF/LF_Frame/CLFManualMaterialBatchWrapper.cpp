// Copyright (C) 2011 SMS Siemag AG

#include "CIntfData.h"
#include "CIntfLF.h"
#include "cCBS_StdEventLogFrameController.h"
#include "iSMC_DataDefinitions_s.hh"

#include "CLFModelTask.h"
#include "CLFManualMaterialBatchWrapper.h"

//##ModelId=41669117003A
bool CLFManualMaterialBatchWrapper::doOnMaterialBatchCharged(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFManualMaterialBatchWrapper::doOnMaterialBatchCharged(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }

  try
  {
    string ActToLoc   = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(Event.getDataKey().c_str(), DATA::RecipeTarget));
    seqBatch  Batch   = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getBatch(Event.getDataKey().c_str(), DATA::RecipeContent));
    long      SeqLength;
    long      GetAtValue;
    sBatch    MatData;

    SeqLength = CIntfData::getLength(Batch);
    for (int x = 0; x < SeqLength; x++) 
    {
      GetAtValue    = CIntfData::getAt(MatData, Batch, x);
      string Code   = MatData.MatCode;

      pIntfLF->hndlMatChg(ActToLoc, Code, MatData.Mass);
    }

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFManualMaterialBatchWrapper::doOnMaterialBatchCharged()", "" );    
  }

  return RetValue;
}

//##ModelId=416691170282
bool CLFManualMaterialBatchWrapper::doOnMaterialBatchDischarged(CEventMessage& Event)
{
  bool RetValue = false;
  
  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFManualMaterialBatchWrapper::doOnMaterialBatchDischarged(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try 
  {    
    string ActFromLoc = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(Event.getDataKey().c_str(), DATA::RecipeSource));

    string ActToLoc   = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(Event.getDataKey().c_str(), DATA::RecipeTarget));
    
    pIntfLF->hndlMatDischg(ActFromLoc, ActToLoc);

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "","CLFManualMaterialBatchWrapper::doOnMaterialBatchDischarged()",  ""  );    
  }

  return RetValue;
}