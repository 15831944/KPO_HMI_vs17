// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfEAF.h"

#include "CEAFCeloxMeasurementWrapper.h"

//##ModelId=4158056903C1
bool CEAFCeloxMeasurementWrapper::doOnCeloxMeasurement( CEventMessage &Event )
{
	bool RetValue = false;

	CIntfEAF *pIntfEAF = getpModelIntf();
	if (!pIntfEAF )return false;
	
	try
	{
		double Temp     = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getDouble(
								 Event.getDataKey().c_str(), DATA::MeasTemp);
		double ActyO2   = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getDouble(
								 Event.getDataKey().c_str(), DATA::MeasO2Conc);
		double ActyC    = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getDouble(
								 Event.getDataKey().c_str(), DATA::MeasCarbonConc);

		pIntfEAF->hndlCeloxMeas(Temp, ActyO2, ActyC, true);

		// Sequence Diagram: get model results / Call Sequence
		RetValue = doModelResult(Event);
	}
	catch (...) 
	{
		cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
		sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
		pEventLog->EL_ExceptionCaught(sMessage, "", "CEAFMaterialInjectionWrapper::doOnCeloxMeasurement()", "" );          
	}


	return RetValue;
}

