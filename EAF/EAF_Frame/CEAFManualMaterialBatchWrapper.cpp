// Copyright (C) 2004 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfEAF.h"

#include "CEAFManualMaterialBatchWrapper.h"
#include "CIntfData.h"


//##ModelId=4152969701E8
bool CEAFManualMaterialBatchWrapper::doOnMaterialBatchCharged( CEventMessage &Event )
{
	bool RetValue = false;
	CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !m_pModelTask) 
  {
    log("error CEAFManualMaterialBatchWrapper::doOnMaterialBatchCharged(), ( pIntfEAF && m_pModelTask) == false", 1);
    return RetValue;
  }

	try
	{
			string ActToLoc   = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(Event.getDataKey().c_str(), DATA::RecipeTarget));
			seqBatch  Batch   = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getBatch(Event.getDataKey().c_str(), DATA::RecipeContent));
			long      SeqLength;
			long      GetAtValue;
			sBatch    MatData;

      pIntfEAF->indicateMatChg();

			SeqLength = CIntfData::getLength(Batch);
			for (int x = 0; x < SeqLength; x++) 
			{
				GetAtValue    = CIntfData::getAt(MatData, Batch, x);
				string Code   = MatData.MatCode;

				pIntfEAF->hndlMatChg(ActToLoc, Code, MatData.Mass);
			}

			pIntfEAF->hndlEvent();
			RetValue = doModelResult(Event);
	}
	catch (...)
	{
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
	  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
	  pEventLog->EL_ExceptionCaught(sMessage, "", "CEAFManualMaterialBatchWrapper::doOnMaterialBatchCharged()", ""  );    
	}

	return RetValue;
}

//##ModelId=415296980110
bool CEAFManualMaterialBatchWrapper::doOnMaterialBatchDischarged( CEventMessage &Event )
{
	bool RetValue = false;
	CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !m_pModelTask) 
  {
    log("error CEAFManualMaterialBatchWrapper::doOnMaterialBatchDischarged(), ( pIntfEAF && m_pModelTask) == false", 1);
    return RetValue;
  }

	try 
	{    

		string ActFromLoc = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(Event.getDataKey().c_str(), DATA::RecipeSource));

		string ActToLoc   = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(Event.getDataKey().c_str(), DATA::RecipeTarget));

		pIntfEAF->hndlMatDischg(ActFromLoc, ActToLoc);

		// Sequence Diagram: get model results / Call Sequence
		RetValue = doModelResult(Event);
	}
	catch (...) 
	{
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
	  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
	  pEventLog->EL_ExceptionCaught(sMessage, "","CEAFManualMaterialBatchWrapper::doOnMaterialBatchDischarged()", ""  );    
	}

	return RetValue;
	
}

