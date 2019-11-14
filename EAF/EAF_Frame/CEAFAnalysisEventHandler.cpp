// Copyright (C) 2004 SMS Demag AG

#include "iEventMessages_s.hh"
#include "CEAFAnalysisEventHandler.h"

//##ModelId=467645DF00F8
CEAFAnalysisEventHandler::CEAFAnalysisEventHandler(CModelTask* pModelTask)
: CEAFEventHandler(pModelTask)
{
  EAFAnalysisHandlingWrapper.setpModelTask(pModelTask);
}

//##ModelId=414711A301B2
bool CEAFAnalysisEventHandler::handleEvent( CEventMessage& EventMessage)
{
  bool RetValue = true;
  std::string Message = EventMessage.getMessage();

	if ( !checkProductAcceptance(EventMessage) ) 
	{
		return false;		
	}


	if ( EAF_EvMsg::evEAFSlagAnalysisReceived == Message )
	{ 
		EAFAnalysisHandlingWrapper.doOnSlagAnalysisReceived(EventMessage);		
	} 
	else if (EAF_EvMsg::evEAFSteelAnalysisReceived == Message) 
	{ 
		EAFAnalysisHandlingWrapper.doOnSteelAnalysisReceived(EventMessage);		
	} 
	else if (EAF_EvMsg::evEAFSlagSampleTaken == Message) 
	{ 
		EAFAnalysisHandlingWrapper.doOnSlagSampleTaken(EventMessage);		
	} 
	else if (EAF_EvMsg::evEAFSteelSampleTaken == Message) 
	{ 
		EAFAnalysisHandlingWrapper.doOnSteelSampleTaken(EventMessage);			
	} 
	else
  {
		RetValue = false; 
  }

	return RetValue;
}
