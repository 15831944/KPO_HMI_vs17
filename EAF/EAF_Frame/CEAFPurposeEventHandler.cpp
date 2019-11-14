// Copyright (C) 2012 SMS Siemag AG

#include "iEventMessages_s.hh"
#include "CEAFPurposeEventHandler.h"
#include "CEAFModelTask.h"

CEAFPurposeEventHandler::CEAFPurposeEventHandler(CModelTask* pModelTask)
: CEAFEventHandler(pModelTask)
{
	EAFPurposeHandlingWrapper.setpModelTask(pModelTask);
}
bool CEAFPurposeEventHandler::handleEvent( CEventMessage& EventMessage)
{
	bool RetValue = true;

  bool doIt = true; 

  // CEAFPurposeEventHandler might come from L1 or HMI 
  // as product or general information for changes in Production Practice 
  // In case of product event only acceptance will be checked. 
  // In case of plant event without any heat data it is necessary 
  // to check if a product is available. This product info will 
  // be used to set data in event. 


	std::string Message = EventMessage.getMessage();


	// calling respective model wrapper functions ; SITE HF +++  if (checkProductAcceptance(EventMessage) ) 
	/*if (EventMessage.isPlantEvent() || checkProductAcceptance(EventMessage) ) 
	{
		if ( EAF_EvMsg::evEAFHandleUpdatePurpose == Message )
		{       
		  EAFPurposeHandlingWrapper.doOnUpdatePurpose(EventMessage); 
		} 
		else
    {
		  RetValue = false; // The event is not for this handler
    }

	}
	else
  {
    log("CEAFPurposeEventHandler::handleEvent --- event is not plant event ---- " ,3);
		RetValue = false; // The event is not for this product
  }*/


  if ( EAF_EvMsg::evEAFHandleUpdatePurpose == Message ) 
  { 
    if ( !checkProductAcceptance(EventMessage) ) 
	  { 
		  if (EventMessage.isPlantEvent()) 
      { 
        
			  log("Got event as plant event",3); 
        if    (CEAFModelTask::getInstance()->getActProductID() != DEF::Inv_String && 
              !CEAFModelTask::getInstance()->getActHeatID().empty() &&
			        !CEAFModelTask::getInstance()->getActTreatID().empty() && 
				      !CEAFModelTask::getInstance()->getActOrderID().empty() && 
				      !CEAFModelTask::getInstance()->getActProductID().empty() ) 
			  { 
				      log("set product data from wrapper into event",3); 
				      EventMessage.setHeatID(CEAFModelTask::getInstance()->getActHeatID()); 
				      EventMessage.setTreatID(CEAFModelTask::getInstance()->getActTreatID()); 
				      EventMessage.setOrderID(CEAFModelTask::getInstance()->getActOrderID());
				      EventMessage.setProductID(CEAFModelTask::getInstance()->getActProductID()); 
				      EventMessage.setPlantEvent(false); 
			  } 
			  else 
			  { 
			    //Because model results would be without any heat information // don't handle event. 
			    doIt = false; 
			  }

		  } 

	  } 
  	
	  if (doIt) 
	  { 
	    EAFPurposeHandlingWrapper.doOnUpdatePurpose(EventMessage);
	  } 
	  else 
		  RetValue = false; // The event is not for this handler 
  } 
  else
  {
	  RetValue = false; 
  }


	return RetValue;
}
