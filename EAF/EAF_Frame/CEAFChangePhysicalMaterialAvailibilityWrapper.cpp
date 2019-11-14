// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfEAF.h"

#include "CEAFChangePhysicalMaterialAvailibilityWrapper.h"

//##ModelId=429F1E93009D
bool CEAFChangePhysicalMaterialAvailibilityWrapper::doOnChangedPhysicalMatAvail( CEventMessage &Event )
{
	bool RetValue = false;

	CIntfEAF *pIntfEAF = getpModelIntf();

	if (!m_pModelTask) 
	{
		log("error CEAFChangePhysicalMaterialAvailibilityWrapper::doOnChangedPhysicalMatAvail(), (m_pModelTask) == false", 1);
		return false;
	}
	if (!pIntfEAF ) {
		log("error CEAFChangePhysicalMaterialAvailibilityWrapper::doOnChangedPhysicalMatAvail(), (pIntfEAF && m_pModelTask) == false", 1);
		return false;
	}

	try 
	{
		// Sequence Diagram: handle change of physical material availibility / Call Sequence	
		string ActMatCode     = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(
								 Event.getDataKey().c_str(), DATA::MatCode));

		pIntfEAF->hndlUpdateAvailMat(ActMatCode);

		// Sequence Diagram: get model results / Call Sequence
		RetValue = doModelResult(Event);
	}
	catch (...) 
	{
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
	  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
	  pEventLog->EL_ExceptionCaught(sMessage, "",  "CEAFChangePhysicalMaterialAvailibilityWrapper::doOnChangedPhysicalMatAvail() ", "" );    
	}

	return RetValue;
}

