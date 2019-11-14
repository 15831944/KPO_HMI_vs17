// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfEAF.h"

#include "CIntfData.h"
#include "CEAFModelTask.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CEAFInjectionMaterialHandlingWrapper.h"



//##ModelId=4111283C01EC
bool CEAFInjectionMaterialHandlingWrapper::doOnDolomiticLimeInjStart( CEventMessage &Event )
{
	bool RetValue = false;

	CIntfEAF *pIntfEAF = getpModelIntf();

	if (!pIntfEAF) return false;
	try 
	{
    //pIntfEAF->hndlDoloLimeInjctStart(""); // MatCode : const char* 

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
	}
	catch (...) 
	{
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
	  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
	  pEventLog->EL_ExceptionCaught(sMessage, "","CEAFInjectionMaterialHandlingWrapper::doOnDolomiticLimeInjStart()", "" );    
	} 


	return RetValue;
}

//##ModelId=4111287D022C
bool CEAFInjectionMaterialHandlingWrapper::doOnDolomiticLimeInjStop( CEventMessage &Event )
{
	bool RetValue = false;

	CIntfEAF *pIntfEAF = getpModelIntf();
	if (!pIntfEAF) return false;

	try 
	{
    //pIntfEAF->hndlDoloLimeInjctStop("", 0); // MatCode, Masse 

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
	}
	catch (...) 
	{
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
	  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
	  pEventLog->EL_ExceptionCaught(sMessage, "","CEAFInjectionMaterialHandlingWrapper::doOnDolomiticLimeInjStop()",""  );    
	} 


  return RetValue;
}

