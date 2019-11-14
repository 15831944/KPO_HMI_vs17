// Copyright (C) 2006 SMS Demag AG
// 

#include "iEventMessages_s.hh"
#include "cCBS_StdInitBase.h"
#include "CEventMessage.h"
#include "CDH_HMI_Task.h"

#include "CHMI_GEN_EventHandler.h"



//##ModelId=45882F8402D2
bool CHMI_GEN_EventHandler::handleEvent(CEventMessage& evMessage)
{
  bool RetValue = true;
  std::string Message = evMessage.getMessage();
  std::string HeatID    = evMessage.getHeatID();
  std::string ProductID = evMessage.getProductID();

  if ( HMI_EvMsg::evHMIProductionOrderDataUpdate == Message  ||
       HMI_EvMsg::evHMIHeatScheduleUpdate        == Message  ||
       HMI_EvMsg::evHMISetUpOfHeat               == Message  ||
       HMI_EvMsg::evHMIResetOfHeat               == Message  ||
       HMI_EvMsg::evHMISteelGradeDataUpdate      == Message  ||
       HMI_EvMsg::evHMIRequestPlanningData       == Message 
     )
  {
    log(evMessage, 3);       

    // make event to PlantEvent if no Heat / product Information are available
    if( HeatID.empty() )
    {
      evMessage.setPlantEvent(true);
      log("Event modified to PlantEvent, on Event: " + Message, 3);
    }

    dispatchEvent(m_SenderName,"",evMessage);
  }
  else if   (HMI_EvMsg::evHMIRequestHeatSchedule == Message)
  {
    // If HMI Operator requests Heat Schedule, we need to request three Heat Schedules, one for each plant.

    log(evMessage, 3);       

    // make event to PlantEvent if no Heat / product Information are available
    if( HeatID.empty() )
    {
      evMessage.setPlantEvent(true);
      log("Event modified to PlantEvent, on Event: " + Message, 3);
    }

    evMessage.setPlantID("EAF_1");
    dispatchEvent(m_SenderName,"",evMessage);

    evMessage.setPlantID("AOD_1");
    dispatchEvent(m_SenderName,"",evMessage);

    evMessage.setPlantID("LF_1");
    dispatchEvent(m_SenderName,"",evMessage);

  }
  else
  {
    RetValue = false; // The event is for this handler, but the handler doesn't have a do-method
  }
 
  return RetValue;    
}

//##ModelId=45882FAA01B6
CHMI_GEN_EventHandler::CHMI_GEN_EventHandler(std::string& ServerName)
{
  m_SenderName = ServerName;
}

//##ModelId=45882FAE021F
CHMI_GEN_EventHandler::~CHMI_GEN_EventHandler()
{
}

