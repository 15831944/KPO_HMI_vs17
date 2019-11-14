// Copyright (C) 2004 SMS Demag AG

#include "CDM_LFTask.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CDM_LFModesAndAvailabilitiesEventHandler.h"

CDM_LFModesAndAvailabilitiesEventHandler::CDM_LFModesAndAvailabilitiesEventHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}

CDM_LFModesAndAvailabilitiesEventHandler::~CDM_LFModesAndAvailabilitiesEventHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}

bool CDM_LFModesAndAvailabilitiesEventHandler::handleEvent(CEventMessage& evMessage)
{
  //LF_EvMsg::evLF

  HANDLE_EVENT(LFSetComputerMode);
  HANDLE_EVENT(LFResetComputerModeAvailability);

	return false;
}

bool CDM_LFModesAndAvailabilitiesEventHandler::doLFSetComputerMode(CEventMessage& Event)
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


bool CDM_LFModesAndAvailabilitiesEventHandler::doLFResetComputerModeAvailability(CEventMessage& Event)
{
  // try to update Event with assigend data (ProductID...)
  if ( checkEventAssignment(Event) )
  {
    // update PlantManagerInterface Data
    if (m_pDMTask->getpProductManager() && 
        m_pDMTask->getpProductManager()->changeComputerModeAvailabilities(Event))
    {
      // send event to respective destinations
      dispatchEvent(Event);
    }
  }
	return true;
}
