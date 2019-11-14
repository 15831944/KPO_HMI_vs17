// Copyright (C) 2004 SMS Demag AG

#define GEN_EvMsg
#include "CDM_GENTask.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CDM_GENModesAndAvailabilitiesEventHandler.h"

CDM_GENModesAndAvailabilitiesEventHandler::CDM_GENModesAndAvailabilitiesEventHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}

CDM_GENModesAndAvailabilitiesEventHandler::~CDM_GENModesAndAvailabilitiesEventHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}

bool CDM_GENModesAndAvailabilitiesEventHandler::handleEvent(CEventMessage& evMessage)
{
	return false;
}



bool CDM_GENModesAndAvailabilitiesEventHandler::doGENSetComputerModeBlowingOn(CEventMessage& Event)
{
  doGENSetComputerMode(Event);
	return true;
}

bool CDM_GENModesAndAvailabilitiesEventHandler::doGENSetComputerModeBlowingOff(CEventMessage& Event)
{
  doGENSetComputerMode(Event);
	return true;
}

bool CDM_GENModesAndAvailabilitiesEventHandler::doGENSetComputerModeMatHandlingOn(CEventMessage& Event)
{
  doGENSetComputerMode(Event);
	return true;
}

bool CDM_GENModesAndAvailabilitiesEventHandler::doGENSetComputerModeMatHandlingOff(CEventMessage& Event)
{
  doGENSetComputerMode(Event);
	return true;
}

bool CDM_GENModesAndAvailabilitiesEventHandler::doGENSetComputerMode(CEventMessage& Event)
{
  // try to update Event with assigend data (ProductID...)
  if ( checkEventAssignment(Event) )
  {
    if ( copyDataEventData(Event) )//we need to copy the data exactly once, so anyone who handles our event can read the data from us
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
}//bool CDM_GENModesAndAvailabilitiesEventHandler::doGENSetComputerMode(CEventMessage& Event)

bool CDM_GENModesAndAvailabilitiesEventHandler::doGENSetGasAvailability(CEventMessage& Event)
{
	doGENSetAvailabilities(Event);
	return true;
}

bool CDM_GENModesAndAvailabilitiesEventHandler::doGENSetTopLanceAvailability(CEventMessage& Event)
{
	doGENSetAvailabilities(Event);
	return true;
}

bool CDM_GENModesAndAvailabilitiesEventHandler::doGENSetTuyeresAvailability(CEventMessage& Event)
{
	doGENSetAvailabilities(Event);
	return true;
}

bool CDM_GENModesAndAvailabilitiesEventHandler::doGENSetAvailabilities(CEventMessage& Event)
{
/*
  // try to update Event with assigend data (ProductID...)
  if ( checkEventAssignment(Event) )
  {
    // copy data from DH to DM_DataInterface
    if ( copyDataEventData(Event, "",DEF_PLANT::Furnace) )
    {
      // update PlantManagerInterface Data
      if (m_pDMTask->getpPlantManager() && 
          m_pDMTask->getpPlantManager()->changeAvailabilities(Event) )
      {
        // send event to respective destinations
        dispatchEvent(Event);
      }
    }
  }
*/
  return true;
}
