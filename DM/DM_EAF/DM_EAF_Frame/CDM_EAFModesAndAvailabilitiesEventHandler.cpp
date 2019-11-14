// Copyright (C) 2004 SMS Demag AG

#include "CDM_EAFTask.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CDM_EAFModesAndAvailabilitiesEventHandler.h"


CDM_EAFModesAndAvailabilitiesEventHandler::CDM_EAFModesAndAvailabilitiesEventHandler()
{
}

CDM_EAFModesAndAvailabilitiesEventHandler::~CDM_EAFModesAndAvailabilitiesEventHandler()
{
}

bool CDM_EAFModesAndAvailabilitiesEventHandler::handleEvent(CEventMessage& evMessage)
{
  //EAF_EvMsg::evEAF

  HANDLE_EVENT(EAFSetComputerMode);
  HANDLE_EVENT_DATA(EAFActivateWallTempCtrl);
  HANDLE_EVENT_DATA(EAFDeactivateWallTempCtrl);

	return false;
}


bool CDM_EAFModesAndAvailabilitiesEventHandler::doEAFSetComputerMode(CEventMessage& Event)
{
  // try to update Event with assigend data (ProductID...)
  if ( checkEventAssignment(Event) )
  {

    // copy data from DH to DM_DataInterface
    if ( copyDataEventData(Event) )
    {
      // update PlantManagerInterface Data
      if (m_pDMTask->getpPlantManager() && 
          m_pDMTask->getpPlantManager()->changeComputerModes(Event) )
      {
        // send event to respective destinations
        dispatchEvent(Event);
      }
    }
  }
  return true;
}

