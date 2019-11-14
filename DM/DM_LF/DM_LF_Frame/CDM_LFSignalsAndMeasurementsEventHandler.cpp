// Copyright (C) 2004 SMS Demag AG

#include "CIntfData.h"

#include "cCBS_StdEventLogFrameController.h"
#include "CDM_PlantManagementInterface_Impl.h"
#include "CDM_ProductManagementInterface_Impl.h"
#include "CDM_LFTask.h"
#include "CDM_LFSignalsAndMeasurementsEventHandler.h"

CDM_LFSignalsAndMeasurementsEventHandler::~CDM_LFSignalsAndMeasurementsEventHandler()
{
}

CDM_LFSignalsAndMeasurementsEventHandler::CDM_LFSignalsAndMeasurementsEventHandler()
{
}

bool CDM_LFSignalsAndMeasurementsEventHandler::handleEvent(CEventMessage& evMessage)
{

  //LF_EvMsg::evLF

  // electrical system signals
  HANDLE_EVENT_PLANT(LFElectrodesInOperatingPosition);
  HANDLE_EVENT_PLANT(LFElectrodesOutOperatingPosition);
  HANDLE_EVENT_PLANT(LFFurnaceBreakerOn);
  HANDLE_EVENT_PLANT(LFFurnaceBreakerOff);
  HANDLE_EVENT(LFPowerOn);
  HANDLE_EVENT(LFPowerOff);
  HANDLE_EVENT(LFTapChangeStart);
  HANDLE_EVENT(LFTapChangeFinished);
  HANDLE_EVENT(LFImpCurveChanged);

  // handling measurement signals
  HANDLE_EVENT(LFCyclicMeasurement); 
  HANDLE_EVENT_DATA(LFTempMeasurement);
  HANDLE_EVENT_DATA(LFCeloxMeasurement);
  HANDLE_EVENT_DATA(LFTemperatureSampleRequest);

  // handling mechanical system signals
  HANDLE_EVENT_DATA(LFDeslaggingData);
  HANDLE_EVENT(LFRoofArrivesInUpPosition);
  HANDLE_EVENT(LFRoofArrivesInDownPosition);
  HANDLE_EVENT(LFGantrySwungIn);
  HANDLE_EVENT(LFGantrySwungOut);

  HANDLE_EVENT(LFTransferCarPositionChanged);

  // handling stirring system signals
  HANDLE_EVENT(LFBottomStirringByPassOn);
  HANDLE_EVENT(LFBottomStirringByPassOff);
  HANDLE_EVENT(LFBottomStirringStart);
  HANDLE_EVENT(LFBottomStirringEnd);
  HANDLE_EVENT(LFEmergencyLanceStirringStart);
  HANDLE_EVENT(LFEmergencyLanceStirringEnd);

	return false;
}

bool CDM_LFSignalsAndMeasurementsEventHandler::doLFTapChangeStart(CEventMessage& Event)
{
  // copy data from DH to DM_DataInterface
  if ( copyDataEventData(Event) )
  {
    // try to update Event with assigend data (ProductID...)
    if ( checkEventAssignment(Event) )
    {
      if (m_pDMTask->getpPlantManager() )
      {
        // update PlantManagerInterface Data for TransferCar
        m_pDMTask->getpPlantManager()->changeElectricalData(Event);

        // send event to respective destinations
        dispatchEvent(Event);

      }
    }
  }
  return true;
}

bool CDM_LFSignalsAndMeasurementsEventHandler::doLFTapChangeFinished(CEventMessage& Event)
{
  // copy data from DH to DM_DataInterface
  if ( copyDataEventData(Event) )
  {
    // try to update Event with assigend data (ProductID...)
    if ( checkEventAssignment(Event) )
    {
      if (m_pDMTask->getpPlantManager() )
      {
        // update PlantManagerInterface Data for TransferCar
        m_pDMTask->getpPlantManager()->changeElectricalData(Event);

        // send event to respective destinations
        dispatchEvent(Event);

      }
    }
  }
  return true;
}

bool CDM_LFSignalsAndMeasurementsEventHandler::doLFImpCurveChanged(CEventMessage& Event)
{
  // copy data from DH to DM_DataInterface
  if ( copyDataEventData(Event) )
  {
    // try to update Event with assigend data (ProductID...)
    if ( checkEventAssignment(Event) )
    {
      if (m_pDMTask->getpPlantManager() )
      {
        // update PlantManagerInterface Data for TransferCar
        m_pDMTask->getpPlantManager()->changeElectricalData(Event);

        // send event to respective destinations
        dispatchEvent(Event);

      }
    }
  }
  return true;
}

bool CDM_LFSignalsAndMeasurementsEventHandler::doLFCyclicMeasurement(CEventMessage& Event)
{
    // copy all data into the event data corba interface
  if ( m_pDataInterface               && 
       m_pDMTask->getpPlantManager()  && 
       m_pDMTask->getpProductManager() )
  {
    if ( copyDataEventData(Event) )
    {
      if ( checkEventAssignment(Event) )
      {
        std::string DataKey = Event.getDataKey();
        std::string ProductID = Event.getProductID();

        // which kind of MeasurementType has been received here ?
        std::string MeasurementType = m_pDataInterface->getString(DataKey,DATA::MeasurementType);

        //CDM_LFEventLogHandlerSignalsAndMeasurements::EventLog need MeasurementType for logging
        m_pProductManagementInterface->setString(ProductID.c_str(),DATA::MeasurementType,MeasurementType);

        if ( MeasurementType == DEF_CYCLIC_MEASUREMENT_TYPES::CoolingWater ) // data are not heat / product related !!!
        {
          // copy data to "plant" at plant management interface
          m_pDMTask->getpPlantManager()->changeCoolingWaterData(Event);
        }
        else if ( MeasurementType == DEF_CYCLIC_MEASUREMENT_TYPES::Electric ) 
        {
          // data must be copied to Product manager first
          // data will be accumulated there !
          m_pDMTask->getpProductManager()->changeElectricalData(Event);

          // copy data to "transfer car" at plant management interface
          m_pDMTask->getpPlantManager()->changeElectricalData(Event);

          CDM_LFDBManagerTask::getInstance()->getDBManager()->evCyclicMeasurementElectric(Event);
   
        }
        else if ( MeasurementType == DEF_CYCLIC_MEASUREMENT_TYPES::Stirring ) 
        {
          // data must be copied to Product manager first
          // data will be accumulated there !
          m_pDMTask->getpProductManager()->changeStirringData(Event);

          // copy data to respective "transfer car" at plant management interface
          m_pDMTask->getpPlantManager()->changeStirringData(Event);
        }
        
        // activate cyclic trigger
        handleCyclicTriggerCall(Event);

        startCyclicTriggerCalls(Event);
      }
    } // if ( copyDataEventData(Event) )
  } // if ( m_pDataInterface               && 

  return true;
}

bool CDM_LFSignalsAndMeasurementsEventHandler::doLFStirring(CEventMessage& Event)
{
  // try to update Event with assigend data (ProductID...)
    // copy data from DH to DM_DataInterface
  if ( copyDataEventData(Event) )
  {
    if ( checkEventAssignment(Event) )
    {
      if (m_pDMTask->getpProductManager() && 
          m_pDMTask->getpPlantManager() )
      {
        // update ProductManagerInterface Data
        m_pDMTask->getpProductManager()->changeStirringData(Event);
  
        // update PlantManagerInterface Data for TransferCar
        m_pDMTask->getpPlantManager()->changeStirringData(Event);

        // send event to respective destinations
        dispatchEvent(Event);

      }
    }
  }

  return true;
}

bool CDM_LFSignalsAndMeasurementsEventHandler::doLFBottomStirringByPassOn(CEventMessage& Event)
{
	doLFStirring(Event);
  return true;
}

bool CDM_LFSignalsAndMeasurementsEventHandler::doLFBottomStirringByPassOff(CEventMessage& Event)
{
	doLFStirring(Event);
  return true;
}

bool CDM_LFSignalsAndMeasurementsEventHandler::doLFBottomStirringStart(CEventMessage& Event)
{
	doLFStirring(Event);
  return true;
}

bool CDM_LFSignalsAndMeasurementsEventHandler::doLFBottomStirringEnd(CEventMessage& Event)
{
	doLFStirring(Event);
  return true;
}

bool CDM_LFSignalsAndMeasurementsEventHandler::doLFTransferCarPositionChanged(CEventMessage& Event)
{
  // TransferCarPositionChanged event could occour without ProductID !!
  // therefor first the Plantinformation will be set !!!

  // copy data from DH to DM_DataInterface
  if ( copyDataEventData(Event) )
  {
    // update PlantManagerInterface Data for TransferCar
    if (m_pDMTask->getpProductManager() && 
        m_pDMTask->getpPlantManager() )
    {
      m_pDMTask->getpPlantManager()->changePlantInformation(Event);

      // set cooling water data to 0 if transfercar is out of operating position !
      m_pDMTask->getpPlantManager()->changeCoolingWaterData(Event);
    }
  }

  // try to find releated ProductID and assign it to event
  if ( checkEventAssignment(Event) )
  {
    // send event to respective destinations
    dispatchEvent(Event);
  }
  return true;
}


bool CDM_LFSignalsAndMeasurementsEventHandler::doLFPowerOn(CEventMessage& Event)
{
  // copy data from DH to DM_DataInterface
  if ( copyDataEventData(Event) )
  {
    // try to find releated ProductID and assign it to event
    if ( checkEventAssignment(Event) )
    {
      // update Product data for ElecCons, PowerOnDur, PowerOffDur
      if (m_pDMTask->getpPlantManager() )
      {
        m_pDMTask->getpPlantManager()->changeElectricalData(Event);
      }

      // update Product data for ElecCons, PowerOnDur, PowerOffDur
      if (m_pDMTask->getpProductManager() )
      {
        m_pDMTask->getpProductManager()->changeElectricalData(Event);
      }

	    //record in action table
      CDM_LFDBManagerTask::getInstance()->getDBManager()->evPowerOn(Event);

      // now copy data to plant interface

      // send event to respective destinations
      dispatchEvent(Event);
    }
  }

  return true;
}

bool CDM_LFSignalsAndMeasurementsEventHandler::doLFPowerOff(CEventMessage& Event)
{
  // copy data from DH to DM_DataInterface
  if ( copyDataEventData(Event) )
  {
    // try to find releated ProductID and assign it to event
    if ( checkEventAssignment(Event) )
    {
      // update Product data for ElecCons, PowerOnDur, PowerOffDur
      if (m_pDMTask->getpPlantManager() )
      {
        m_pDMTask->getpPlantManager()->changeElectricalData(Event);
      }

      // update PlantManagerInterface Data for TransferCar
      if (m_pDMTask->getpProductManager() )
      {
        m_pDMTask->getpProductManager()->changeElectricalData(Event);
      }

	    //record in action table
      CDM_LFDBManagerTask::getInstance()->getDBManager()->evPowerOff(Event);

      // send event to respective destinations
      dispatchEvent(Event);
    }
  }

  return true;
}

bool CDM_LFSignalsAndMeasurementsEventHandler::doLFEmergencyLanceStirringStart(CEventMessage& Event)
{
  // copy data from DH to DM_DataInterface
  if ( copyDataEventData(Event) )
  {
    // try to find releated ProductID and assign it to event
    if ( checkEventAssignment(Event) )
    {
      // update PlantManagerInterface Data for TransferCar
      if (m_pDMTask->getpProductManager() )
      {
        m_pDMTask->getpProductManager()->changeStirringData(Event);
      }

      // send event to respective destinations
      dispatchEvent(Event);
    }
  }

  return true;
}

bool CDM_LFSignalsAndMeasurementsEventHandler::doLFEmergencyLanceStirringEnd(CEventMessage& Event)
{
  // copy data from DH to DM_DataInterface
  if ( copyDataEventData(Event) )
  {
    // try to find releated ProductID and assign it to event
    if ( checkEventAssignment(Event) )
    {
      // update PlantManagerInterface Data for TransferCar
      if (m_pDMTask->getpProductManager() )
      {
        m_pDMTask->getpProductManager()->changeStirringData(Event);
      }

      // send event to respective destinations
      dispatchEvent(Event);
    }
  }

  return true;
}

bool CDM_LFSignalsAndMeasurementsEventHandler::doLFRoofArrivesInDownPosition(CEventMessage& Event)
{
  // copy data from DH to DM_DataInterface
  if ( copyDataEventData(Event) )
  {
    // try to find releated ProductID and assign it to event
    if (! checkEventAssignment(Event) )
    {
      log("WARNING: equipment tracking without related product.",2);
    }

    // update PlantManagerInterface Data for TransferCar
    if (m_pDMTask->getpPlantManager() )
    {
      m_pDMTask->getpPlantManager()->changePlantInformation(Event);
    }

    // send event to respective destinations
    dispatchEvent(Event);
  }

  return true;
}

bool CDM_LFSignalsAndMeasurementsEventHandler::doLFRoofArrivesInUpPosition(CEventMessage& Event)
{
  // copy data from DH to DM_DataInterface
  if ( copyDataEventData(Event) )
  {
    // try to find releated ProductID and assign it to event
    if (! checkEventAssignment(Event) )
    {
      log("WARNING: equipment tracking without related product.",2);
    }

    // update PlantManagerInterface Data for TransferCar
    if (m_pDMTask->getpPlantManager() )
    {
      m_pDMTask->getpPlantManager()->changePlantInformation(Event);
    }

    // send event to respective destinations
    dispatchEvent(Event);
  }

  return true;
}

bool CDM_LFSignalsAndMeasurementsEventHandler::doLFGantrySwungIn(CEventMessage& Event)
{
  // copy data from DH to DM_DataInterface
  if ( copyDataEventData(Event) )
  {
    // try to find releated ProductID and assign it to event
    if (! checkEventAssignment(Event) )
    {
      log("WARNING: equipment tracking without related product.",2);
    }

    // update PlantManagerInterface Data 
    if (m_pDMTask->getpPlantManager() )
    {
      m_pDMTask->getpPlantManager()->changePlantInformation(Event);
    }

    // send event to respective destinations
    dispatchEvent(Event);
  }

  return true;
}

bool CDM_LFSignalsAndMeasurementsEventHandler::doLFGantrySwungOut(CEventMessage& Event)
{
  // copy data from DH to DM_DataInterface
  if ( copyDataEventData(Event) )
  {
    // try to find releated ProductID and assign it to event
    if (! checkEventAssignment(Event) )
    {
      log("WARNING: equipment tracking without related product.",2);
    }

    // update PlantManagerInterface Data 
    if (m_pDMTask->getpPlantManager() )
    {
      m_pDMTask->getpPlantManager()->changePlantInformation(Event);
    }

    // send event to respective destinations
    dispatchEvent(Event);
  }

  return true;
}
