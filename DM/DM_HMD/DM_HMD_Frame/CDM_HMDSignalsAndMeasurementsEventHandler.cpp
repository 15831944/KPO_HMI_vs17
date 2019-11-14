// Copyright (C) 2007 SMS Demag AG

#include "CIntfData.h"
#include "CDM_HMDTask.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CDM_HMDSignalsAndMeasurementsEventHandler.h"

CDM_HMDSignalsAndMeasurementsEventHandler::~CDM_HMDSignalsAndMeasurementsEventHandler()
{
}

CDM_HMDSignalsAndMeasurementsEventHandler::CDM_HMDSignalsAndMeasurementsEventHandler()
{
}

bool CDM_HMDSignalsAndMeasurementsEventHandler::handleEvent(CEventMessage& evMessage)
{
	HANDLE_EVENT(HMDCyclicMeasurement);
  HANDLE_EVENT(HMDTempMeasurement);
  HANDLE_EVENT(HMDPhasePreparation); // Preparation

  HANDLE_EVENT(HMDPhaseMonoInjectionLimeStart);   // StartMonoLime or 
  HANDLE_EVENT(HMDPhaseMonoInjectionCarbideStart);//StartMonoCarb

  HANDLE_EVENT(HMDPhaseMonoInjectionContinued);  // MainPhase

  HANDLE_EVENT(HMDPhaseMonoInjectionLimeEnd);    //EndLime or
  HANDLE_EVENT(HMDPhaseMonoInjectionCarbideEnd); //EndCaride

	HANDLE_EVENT(HMDPhaseCoInjectionMagnesiumStart);   //Start Magnesium
  HANDLE_EVENT(HMDPhaseCoInjectionMagnesiumEnd); // End Magnesium

  HANDLE_EVENT(HMDPhaseDeslagging); // Deslagging
  //============================================================


  HANDLE_EVENT_DATA(HMDDeslaggingStart);
	HANDLE_EVENT_DATA(HMDDeslaggingEnd);
	HANDLE_EVENT_DATA(HMDParameterUpdate);
	HANDLE_EVENT_DATA(HMDChangeTreatmentType);
  HANDLE_EVENT_DATA(HMDGetModelStatus);
  HANDLE_EVENT_DATA(HMDRequestMatAvail);

	// copy received data direct to plant interface under
  // DEF_PLANT::Furnace key and send event
	HANDLE_EVENT_PLANT(HMDBathLevelMeasurement);


	return false;
}

bool CDM_HMDSignalsAndMeasurementsEventHandler::doHMDCyclicMeasurement(CEventMessage& Event)
{
	m_pDataInterface->showContent(Event.getDataKey(),2);
  // copy all data into the event data corba interface
  if ( m_pDataInterface && 
       copyDataEventData(Event) && 
       m_pDMTask->getpPlantManager() && 
       m_pDMTask->getpProductManager() )
  {
    if ( checkEventAssignment(Event) )
    {
      m_pDMTask->getpPlantManager()->changeInjectionData(Event);
      m_pDMTask->getpProductManager()->changeInjectionData(Event); 

      // activate cyclic trigger
      CDM_EventHandler::handleCyclicTriggerCall(Event);			
    }
  }
  return true;
}

bool CDM_HMDSignalsAndMeasurementsEventHandler::doHMDLanceBlowing(CEventMessage &Event)
{
  // method for future use
  // try to update Event with assigend data (ProductID...)
  if ( checkEventAssignment(Event) )
  {
    // copy data from DH to DM_DataInterface
    if ( copyDataEventData(Event) )
    {
      if (m_pDMTask->getpPlantManager() && 
          m_pDMTask->getpProductManager())
      {
        m_pDMTask->getpPlantManager()->changeBlowingData(Event);
        m_pDMTask->getpProductManager()->changeBlowingData(Event);
      }
      // send event to respective destinations
      dispatchEvent(Event);
    }
  }
  return true;
}

bool CDM_HMDSignalsAndMeasurementsEventHandler::doHMDPhasePreparation(CEventMessage &Event)
{
  return doHMDPhaseDataChange(Event);
}

bool CDM_HMDSignalsAndMeasurementsEventHandler::doHMDPhaseMonoInjectionLimeStart(CEventMessage &Event)
{
  return doHMDPhaseDataChange(Event);
}

bool CDM_HMDSignalsAndMeasurementsEventHandler::doHMDPhaseMonoInjectionCarbideStart(CEventMessage &Event)
{
  return doHMDPhaseDataChange(Event);
}

bool CDM_HMDSignalsAndMeasurementsEventHandler::doHMDPhaseMonoInjectionContinued(CEventMessage &Event)
{
  return doHMDPhaseDataChange(Event);
}

bool CDM_HMDSignalsAndMeasurementsEventHandler::doHMDPhaseMonoInjectionLimeEnd(CEventMessage &Event)
{
  return doHMDPhaseDataChange(Event);
}

bool CDM_HMDSignalsAndMeasurementsEventHandler::doHMDPhaseMonoInjectionCarbideEnd(CEventMessage &Event)
{
  return doHMDPhaseDataChange(Event);
}

bool CDM_HMDSignalsAndMeasurementsEventHandler::doHMDPhaseCoInjectionMagnesiumStart(CEventMessage &Event)
{
  return doHMDPhaseDataChange(Event);
}

bool CDM_HMDSignalsAndMeasurementsEventHandler::doHMDPhaseCoInjectionMagnesiumEnd(CEventMessage &Event)
{
  return doHMDPhaseDataChange(Event);
}


bool CDM_HMDSignalsAndMeasurementsEventHandler::doHMDPhaseDeslagging(CEventMessage &Event)
{
  return doHMDPhaseDataChange(Event);
}

bool CDM_HMDSignalsAndMeasurementsEventHandler::doHMDPhaseDataChange(CEventMessage &Event)
{
  // try to update Event with assigend data (ProductID...)
  if ( checkEventAssignment(Event) )
  {
    // copy data from DH to DM_DataInterface
    if ( copyDataEventData(Event) )
    {
      if (m_pDMTask->getpProductManager())
      {
        m_pDMTask->getpProductManager()->changeInjectionData(Event);
      }
      // send event to respective destinations
      dispatchEvent(Event);

			CDM_HMDDBManagerTask::getInstance()->getDBManager()->doPhaseDataChange(Event);
    }
  }
  return true;
}

bool CDM_HMDSignalsAndMeasurementsEventHandler::doHMDTempMeasurement(CEventMessage& Event)
{
  return doHMDMeasurement(Event);
}

bool CDM_HMDSignalsAndMeasurementsEventHandler::doHMDCeloxMeasurement(CEventMessage& Event)
{
  return doHMDMeasurement(Event);
}

bool CDM_HMDSignalsAndMeasurementsEventHandler::doHMDMeasurement(CEventMessage& Event)
{
  //// copy data from DH to DM_DataInterface


  bool RetValue = false;
  copyDataEventData(Event);

  if(CDM_HMDDBManagerTask::getInstance()->getDBManager()->evTempMeasurement(Event))
  
  if (checkEventAssignment(Event))
    RetValue = dispatchEvent( Event );

  return RetValue;

}
