// Copyright (C) 2011 SMS Siemag AG

#include "iEventMessages_s.hh"
#include "CLFPurposeEventHandler.h"

CLFPurposeEventHandler::CLFPurposeEventHandler(CModelTask* pModelTask)
: CLFEventHandler(pModelTask)
{
  LFPurposeHandlingWrapper.setpModelTask(pModelTask);
}
bool CLFPurposeEventHandler::handleEvent( CEventMessage& EventMessage)
{
  log("++++++ CLFPurposeEventHandler::handleEvent",3);

  bool RetValue = true;
  bool doIt = true;

  // LFHandleUpdatePurpose might come from L1 or HMI 
  // as product or general information for changes in Production Practice
  // In case of product event only acceptance will be checked.
  // In case of plant event without any heat data it is necessary 
  // to check if a product is available. This product info will
  // be used to set data in event.
  std::string Message = EventMessage.getMessage();

  if ( LF_EvMsg::evLFHandleUpdatePurpose == Message )
  {
    if ( !checkProductAcceptance(EventMessage) )
    {
      if (EventMessage.isPlantEvent())
      {
        log("Got event as plant event",3);
        if ( CLFModelTask::getInstance()->getActProductID() != DEF::Inv_String && 
            !CLFModelTask::getInstance()->getActHeatID().empty() &&
            !CLFModelTask::getInstance()->getActTreatID().empty() &&
            !CLFModelTask::getInstance()->getActOrderID().empty() &&
            !CLFModelTask::getInstance()->getActProductID().empty() )
        {
          log("set product data from wrapper into event",3);

          EventMessage.setHeatID(CLFModelTask::getInstance()->getActHeatID());
          EventMessage.setTreatID(CLFModelTask::getInstance()->getActTreatID());
          EventMessage.setOrderID(CLFModelTask::getInstance()->getActOrderID());
          EventMessage.setProductID(CLFModelTask::getInstance()->getActProductID());
          EventMessage.setPlantEvent(false);
        }
        else
        {
          //Because model results would be without any heat information
          // don't handle event.
          doIt = false;
        }
      }//if (EventMessage.isPlantEvent())
    }//if ( !checkProductAcceptance(EventMessage) )
    if (doIt)
    {
      LFPurposeHandlingWrapper.doOnUpdatePurpose(EventMessage);
    } 
    else
      RetValue = false; // The event is not for this handler
  }
  else
    RetValue = false; // The event is not for this product

  return RetValue;
}

