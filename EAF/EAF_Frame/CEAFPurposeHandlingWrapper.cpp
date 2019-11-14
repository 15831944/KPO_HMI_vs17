// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfEAF.h"

#include "CEAFPurposeHandlingWrapper.h"
#include "CIntfData.h"

//##ModelId=415431FA0316
bool CEAFPurposeHandlingWrapper::doOnUpdatePurpose( CEventMessage &Event )
{
	bool RetValue = false;

	CIntfEAF *pIntfEAF = getpModelIntf();
	if (!pIntfEAF ) return false;

	if (!m_pModelTask) 
	{
		log("error CEAFPurposeHandlingWrapper::doOnUpdatePurpose(), (m_pModelTask) == false", 1);
		return false;
	}

	try
	{
		seqStringList Purposes = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getStringList(
											 Event.getDataKey().c_str(), DATA::UpdatedPurpose));

    std::string PurposeName;

		for (long x = 0; x < CIntfData::getLength(Purposes); x++) 
		{
			CIntfData::getAt(PurposeName, Purposes, x);
			pIntfEAF->hndlUpdatePurpose(PurposeName);
    }

		// Sequence Diagram: get model results / Call Sequence
		RetValue = doModelResult(Event);
	}
	catch (...) 
	{
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
	  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
	  pEventLog->EL_ExceptionCaught(sMessage, "", "CEAFPurposeHandlingWrapper::doOnUpdatePurpose",  "" );          
	}

	return RetValue;
}

