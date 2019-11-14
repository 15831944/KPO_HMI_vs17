// Copyright (C) 2011 SMS Siemag AG

#include "iEventMessages_s.hh"
#include "CLFTreatmentManagerEventHandler.h"


//##ModelId=462767AA030B
CLFTreatmentManagerEventHandler::CLFTreatmentManagerEventHandler(CModelTask* pModelTask)
: CLFEventHandler(pModelTask)
{
  LFTreatmentManagerDataWrapper.setpModelTask(pModelTask);
}


//##ModelId=4118B972029C
bool CLFTreatmentManagerEventHandler::handleEvent( CEventMessage& EventMessage)
{
  bool RetValue = true;
  
  std::string Message = EventMessage.getMessage();

  // check DM model assignment in case of following events
  if ( Message == LF_EvMsg::evLFHeatAnnouncement || 
       Message == LF_EvMsg::evLFHeatCancellation || 
       Message == LF_EvMsg::evLFHeatDeparture )  
  {
    checkAnnouncement(EventMessage,false);
  }
  else if ( Message == LF_EvMsg::evLFHeatAnnouncementOffline  )  // will be handled like announcement !
  {
    checkAnnouncement(EventMessage,true);
  }

  // calling respective model wrapper functions
  if ( checkProductAcceptance(EventMessage) )
  {
    if ( Message == LF_EvMsg::evLFHeatAnnouncement || 
         Message == LF_EvMsg::evLFHeatAnnouncementOffline  )  // will be handled like announcement !
    { 
      LFTreatmentManagerDataWrapper.doOnHandleHeatAnnouncement(EventMessage);      
    } 
    else if (LF_EvMsg::evLFHeatCancellation == Message) 
    { 
      LFTreatmentManagerDataWrapper.doOnHeatCancellation(EventMessage);      
    } 
    else if (LF_EvMsg::evLFHeatDeparture == Message) 
    { 
      LFTreatmentManagerDataWrapper.doOnHeatDeparture(EventMessage);      
    } 
    else if (LF_EvMsg::evLFHeatStart == Message) 
    { 
      LFTreatmentManagerDataWrapper.doOnHeatStart(EventMessage);      
    } 
    else if (LF_EvMsg::evLFChangeAimData == Message) 
    { 
      LFTreatmentManagerDataWrapper.doOnChangeAimData(EventMessage);      
    }
    else if (LF_EvMsg::evLFSteelGradeChanged == Message) 
    { 
      LFTreatmentManagerDataWrapper.doOnChangeAimData(EventMessage);      
    }
    else if (LF_EvMsg::evLFUpdateAimDepartureTime == Message)  
    { 
      LFTreatmentManagerDataWrapper.doOnUpdateAimDepartureTime(EventMessage);      
    } 
    else if (LF_EvMsg::evLFUpdateAimTemperature == Message) 
    { 
      LFTreatmentManagerDataWrapper.doOnUpdateAimTemperature(EventMessage);      
    } 
    else if (LF_EvMsg::evLFLadleDataChanged== Message) 
    { 
      LFTreatmentManagerDataWrapper.doOnLadleDataChanged(EventMessage);      
    }
    else if (LF_EvMsg::evLFChangeProdPracPointerElec == Message) 
    { 
      LFTreatmentManagerDataWrapper.doOnChangeProdPracElectric(EventMessage);      
    } 
    else if (LF_EvMsg::evLFChangeProdPracPointerStirring == Message) 
    { 
      LFTreatmentManagerDataWrapper.doOnChangeProdPracStirring(EventMessage);      
    } 
    else if (LF_EvMsg::evLFChangeProdPracPointerRestriction == Message) 
    { 
      LFTreatmentManagerDataWrapper.doOnChangeProdPracRestriction(EventMessage);      
    } 
    else if (LF_EvMsg::evLFChangeProdPracPointerParameter == Message) 
    { 
      LFTreatmentManagerDataWrapper.doOnChangeProdPracParameter(EventMessage);      
    } 
    else if ((LF_EvMsg::evLFFinalHeating == Message)
      ||(LF_EvMsg::evLFInitialHeating == Message)
      ||(LF_EvMsg::evLFMainHeating == Message)
      ||(LF_EvMsg::evLFSoftStirring == Message)
      ||(LF_EvMsg::evLFCooling == Message)
      ||(LF_EvMsg::evLFCleanlinessStirring == Message))
    { 
      LFTreatmentManagerDataWrapper.doOnSwitchEvent(EventMessage);      
    } 
    else
      RetValue = false; // The event is not for this handler
  }
  else
    RetValue = false; // The event is not for this product

  return RetValue;
}
