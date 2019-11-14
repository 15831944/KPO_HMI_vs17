// Copyright (C) 2007 SMS Demag AG

#include "CDM_HMDTask.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CDM_HMDModesAndAvailabilitiesEventHandler.h"

//##ModelId=45139A72009F
bool CDM_HMDModesAndAvailabilitiesEventHandler::handleEvent(CEventMessage& evMessage)
{
  HANDLE_EVENT(HMDSetComputerModeOn);
  HANDLE_EVENT(HMDSetComputerModeOff);

  //materials in bins
  HANDLE_EVENT_DATA(HMDMaterialAvailability);
	return false;
}

//##ModelId=45139A7200AC
bool CDM_HMDModesAndAvailabilitiesEventHandler::doHMDSetComputerModeOn(CEventMessage& Event)
{
  return doHMDSetComputerMode(Event);
}

//##ModelId=45139A7200AE
bool CDM_HMDModesAndAvailabilitiesEventHandler::doHMDSetComputerModeOff(CEventMessage& Event)
{
  return doHMDSetComputerMode(Event);
}

//##ModelId=45139A7200AA
bool CDM_HMDModesAndAvailabilitiesEventHandler::doHMDSetComputerMode(CEventMessage& Event)
{
  // copy data from DH to DM_DataInterface
  if ( copyDataEventData(Event) )
  {
    // update PlantManagerInterface Data
    if (m_pDMTask->getpPlantManager())
    {
      m_pDMTask->getpPlantManager()->changeComputerModes(Event);
      // send event to respective destinations

      Event.setDataKey(DEF_PLANT::Furnace);

      dispatchEvent(Event);
    }
  }
	return true;
}

//##ModelId=45139A72009C
CDM_HMDModesAndAvailabilitiesEventHandler::CDM_HMDModesAndAvailabilitiesEventHandler()
{
}

//##ModelId=45139A72009D
CDM_HMDModesAndAvailabilitiesEventHandler::~CDM_HMDModesAndAvailabilitiesEventHandler()
{
}

