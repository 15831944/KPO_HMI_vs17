// Copyright (C) 2004 SMS Demag AG

#include "iEventMessages_s.hh"
#include "CHMDTreatmentManagerEventHandler.h"

CHMDTreatmentManagerEventHandler::CHMDTreatmentManagerEventHandler(CModelTask* pModelTask)
: CHMDEventHandler(pModelTask)
{
  HMDTreatmentManagerDataWrapper.setpModelTask(pModelTask);
  HMDTreatmentManagerDataWrapper.initDBClasses();
}


//##ModelId=412331B3034F
bool CHMDTreatmentManagerEventHandler::handleEvent( CEventMessage& EventMessage)
{
  bool RetValue = true;
  std::string Message = EventMessage.getMessage();

  // sub system is checked in CEventHandler
  // check DM in case of Heat Announcement
  if ( HMD_EvMsg::evHMDHeatAnnouncement == Message )
  {
    checkAnnouncement(EventMessage,false);
  }

  if ( checkProductAcceptance(EventMessage) )
  {
    if ( HMD_EvMsg::evHMDHeatAnnouncement == Message )
    {
      
      HMDTreatmentManagerDataWrapper.doOnHandleHeatAnnouncement(EventMessage, -1.0);
    }

    if ( HMD_EvMsg::evHMDChangeAimData == Message )
    {
      
      HMDTreatmentManagerDataWrapper.doOnChangeAimData(EventMessage);
    }

    else if ( HMD_EvMsg::evHMDHeatDeparture == Message  )  
    {
      
      HMDTreatmentManagerDataWrapper.doOnHeatDeparture(EventMessage);      
    }
	else if( HMD_EvMsg::evHMDHotMetalAnalysisReceived          == Message)
    { 
      //HMDTreatmentManagerDataWrapper.doOnAnalysisReceived(EventMessage);      //sankar not required because it is static model
    } 
	else if( HMD_EvMsg::evHMDTempMeasurement         == Message)
    { 
      //HMDTreatmentManagerDataWrapper.doOnTempMeasurement(EventMessage);      //sankar not required because it is static model
    } 

    else
      RetValue = false; // The event is not for this handler
  }
  else
    RetValue = false; // The event is not for this product

  return RetValue;
}
