// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfEAF.h"

#include "CIntfData.h"
#include "CEAFModelTask.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CEAFFeedingMaterialHandlingWrapper.h"

//##ModelId=41112916038A
bool CEAFFeedingMaterialHandlingWrapper::doOnBinMaterialHandlingStart( CEventMessage &Event )
{
	bool RetValue = false;

// mrut 2013-11-06 #if defined EAF_DYNAMIC_FEEDING
#if defined (EAF_PATTERN_FEEDING) || defined (EAF_DYNAMIC_FEEDING)

	CIntfEAF *pIntfEAF = getpModelIntf();

	if (!pIntfEAF) return false;
	try 
	{
		  seqBatch *Batch   = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getBatch(
												 Event.getDataKey().c_str(), DATA::MatFeedingData);
		  long      GetAtValue;
		  sBatch    MatData;

		  for (int x = 0; x < CIntfData::getLength(*Batch); x++) 
		  {
			  GetAtValue    = CIntfData::getAt(MatData, Batch, x);
			  string sCode   = MatData.MatCode;

			  pIntfEAF->hndlFeedingStart(sCode);
	  }

	  // Sequence Diagram: get model results / Call Sequence
	  RetValue = doModelResult(Event);
	}
	catch (...) 
	{
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
	  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
	  pEventLog->EL_ExceptionCaught(sMessage, "","CEAFFeedingMaterialHandlingWrapper::doOnBinMaterialHandlingStart()",	""  );    
	} 

#endif

	return RetValue;
}

//##ModelId=4111295903AF
bool CEAFFeedingMaterialHandlingWrapper::doOnBinMaterialHandlingStop( CEventMessage &Event )
{
	bool RetValue = false;

// mrut 2013-11-06 #if defined EAF_DYNAMIC_FEEDING
#if defined (EAF_PATTERN_FEEDING) || defined (EAF_DYNAMIC_FEEDING)

	CIntfEAF *pIntfEAF = getpModelIntf();

	if (!pIntfEAF) return false;
	try 
	{
		seqBatch *Batch   = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getBatch(
											 Event.getDataKey().c_str(), DATA::MatFeedingData);
		long      GetAtValue;
		sBatch    MatData;

		for (int x = 0; x < CIntfData::getLength(*Batch); x++) 
		{
			GetAtValue    = CIntfData::getAt(MatData, Batch, x);
			string sCode   = MatData.MatCode;

			pIntfEAF->hndlFeedingStop(sCode);
		}

		// Sequence Diagram: get model results / Call Sequence
		RetValue = doModelResult(Event);
	}
	catch (...) 
	{
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
	  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
	  pEventLog->EL_ExceptionCaught(sMessage, "", "CEAFFeedingMaterialHandlingWrapper::doOnBinMaterialHandlingStop()",	""  );    
	} 

#endif

	return RetValue;
}

