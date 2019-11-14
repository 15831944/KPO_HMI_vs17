// Copyright (C) 2006 SMS Demag AG
// 

#include "iEventMessages_s.hh"
#include "CEventMessage.h"
#include "CDH_HMI_Task.h"

#include "CHMI_EAF_EventHandler.h"



//##ModelId=45883018018A
bool CHMI_EAF_EventHandler::handleEvent(CEventMessage& evMessage)
{
  bool RetValue = false;

  std::string Message   = evMessage.getMessage();
  std::string HeatID    = evMessage.getHeatID();
  std::string ProductID = evMessage.getProductID();

  log(evMessage, 3);       

  // events from L2 (DM or TSM)
  // do not forward to DM again !
  // copy data for respective Product !
  if ( Message == HMI_EvMsg::evHMIUpdateDialogueData )
  {
    RetValue = copyDMData(evMessage);
  }
  // this event is sent by Tracker on start up and is never stoped
  else if ( Message == HMI_EvMsg::evHMIUpdatePlantData )
  {
    evMessage.setProductID("");
    RetValue = copyDMData(evMessage);
  }
  else 
  {
    if ( checkTransmitter(evMessage) ) // trasmitterlist set with "HMI" as default 
    {
      if ( Message == EAF_EvMsg::evEAFChangeAimData                    ||
           Message == EAF_EvMsg::evEAFChangeProdPracPointerProcess     ||
           Message == EAF_EvMsg::evEAFChangeProdPracPointerInjection   ||
           Message == EAF_EvMsg::evEAFChangeProdPracPointerOxygen      ||
           Message == EAF_EvMsg::evEAFChangeProdPracPointerBurner      ||
           Message == EAF_EvMsg::evEAFChangeProdPracPointerElec        ||
           Message == EAF_EvMsg::evEAFChangeProdPracPointerParameter   ||
           Message == EAF_EvMsg::evEAFChangeProdPracPointerRestriction ||
           Message == EAF_EvMsg::evEAFChangeProdPracPointerScrapLoading ||
           Message == EAF_EvMsg::evEAFChangeProdPracPointerStirring    ||
           Message == EAF_EvMsg::evEAFChangeProdPracDataProcess        ||
           Message == EAF_EvMsg::evEAFChangeProdPracDataInjection      ||
           Message == EAF_EvMsg::evEAFChangeProdPracDataOxygen         ||
           Message == EAF_EvMsg::evEAFChangeProdPracDataBurner         ||
           Message == EAF_EvMsg::evEAFChangeProdPracDataElec           ||
           Message == EAF_EvMsg::evEAFChangeProdPracDataParameter      ||
           Message == EAF_EvMsg::evEAFChangeProdPracDataRestriction    ||
           Message == EAF_EvMsg::evEAFChangeProdPracDataScrapLoading   ||
           Message == EAF_EvMsg::evEAFChangeProdPracDataStirring       ||
           Message == EAF_EvMsg::evEAFChangeLiquidAdditionData         ||
           Message == EAF_EvMsg::evEAFHandleUpdatePurpose              ||
           Message == EAF_EvMsg::evEAFRestrictionDataUpdate            ||    
           Message == EAF_EvMsg::evEAFParameterUpdate                  ||  
           Message == EAF_EvMsg::evEAFUpdateAimDepartureTime           ||
           Message == EAF_EvMsg::evEAFUpdateAimTemperature             ||  
           Message == EAF_EvMsg::evEAFRecipeWeighingCompleteUpdate     ||  
           Message == EAF_EvMsg::evEAFMinChargeableBinWeightUpdate     ||
           Message == EAF_EvMsg::evEAFUpdatePlantStatus                ||
           Message == EAF_EvMsg::evEAFHeatScheduleUpdate               ||
           Message == EAF_EvMsg::evEAFProductionOrderDataUpdate        )          
      {
        // make event to PlantEvent if no Heat Information is available
        if( HeatID.empty() )
        {
          evMessage.setPlantEvent(true);
          log("Event modified to PlantEvent, on Event: " + Message, 3);
        }
      }

      if( Message == HMI_EvMsg::evHMIHeatScheduleUpdate )
      {
        evMessage.setPlantEvent(true);           
        log("Event modified to PlantEvent, on Event: " + Message, 3);
      }
      else
      {
        changeMissingEventData(evMessage);
      }

      RetValue = dispatchEvent(m_SenderName,"",evMessage);   
    } //if ( checkTransmitter(evMessage) )
  }
  return RetValue;
}

//##ModelId=4588301C013F
CHMI_EAF_EventHandler::CHMI_EAF_EventHandler(std::string& ServerName)
{
  m_SenderName = ServerName;
}

//##ModelId=45883020005E
CHMI_EAF_EventHandler::~CHMI_EAF_EventHandler()
{
}

