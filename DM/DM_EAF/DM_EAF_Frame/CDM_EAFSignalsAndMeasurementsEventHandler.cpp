// Copyright (C) 2011 SMS Siemag AG

#include "CIntfData.h"

#include "CDM_PlantManagementInterface_Impl.h"
#include "CDM_ProductManagementInterface_Impl.h"

#include "CDM_EAFTask.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CDM_EAFSignalsAndMeasurementsEventHandler.h"
#include "CDM_EAFDBManagerTask.h"


CDM_EAFSignalsAndMeasurementsEventHandler::~CDM_EAFSignalsAndMeasurementsEventHandler()
{
}

CDM_EAFSignalsAndMeasurementsEventHandler::CDM_EAFSignalsAndMeasurementsEventHandler()
{
}

bool CDM_EAFSignalsAndMeasurementsEventHandler::handleEvent(CEventMessage& evMessage)
{
  // handle frequently encountered events first
  HANDLE_EVENT(EAFCyclicMeasurement);
  HANDLE_EVENT(EAFCyclicMeasurementTapLadle);

  // handling burner / oxygen lance signals
  HANDLE_EVENT(EAFBurnerStart);
  HANDLE_EVENT(EAFBurnerStop);

  // handling electrical system signals
  HANDLE_EVENT_PLANT(EAFElectrodesInOperatingPosition);
  HANDLE_EVENT_PLANT(EAFElectrodesOutOperatingPosition);
  HANDLE_EVENT_PLANT(EAFElectrodeRegCurveNum);
  HANDLE_EVENT_PLANT(EAFFurnaceBreakerOn);
  HANDLE_EVENT_PLANT(EAFFurnaceBreakerOff);
  HANDLE_EVENT(EAFPowerOn);
  HANDLE_EVENT(EAFPowerOff);
  HANDLE_EVENT_PLANT(EAFTapChangeStart);
  HANDLE_EVENT_PLANT(EAFTapChangeFinished);

  // handling injection system signals
  HANDLE_EVENT(EAFCarbonInjectStart);
  HANDLE_EVENT(EAFCarbonInjectStop);

  // handling jet module signals
  HANDLE_EVENT_DATA(EAFJetModuleStart);
  HANDLE_EVENT_DATA(EAFJetModuleStop);

  // handling lance manipulator system signals
  HANDLE_EVENT(EAFManipGasLanceStart);
  HANDLE_EVENT(EAFManipGasLanceStop);
  HANDLE_EVENT(EAFManipInjectLanceStart);
  HANDLE_EVENT(EAFManipInjectLanceStop);

  // handling measurement signals
  HANDLE_EVENT_DATA(EAFTempMeasurement);
  HANDLE_EVENT_DATA(EAFCeloxMeasurement);

  // handling mechanical system signals
  HANDLE_EVENT_DATA(EAFDeslaggingStart);
  HANDLE_EVENT_DATA(EAFDeslaggingEnd);
  HANDLE_EVENT(EAFTappingStart);
  HANDLE_EVENT(EAFTappingEnd);

  HANDLE_EVENT_PLANT(EAFDoorClosed);
  HANDLE_EVENT_PLANT(EAFDoorOpened);
  HANDLE_EVENT_PLANT(EAFRoofArrivesInUpPosition);
  HANDLE_EVENT_PLANT(EAFRoofArrivesInDownPosition);
  HANDLE_EVENT_PLANT(EAFGantrySwungIn);
  HANDLE_EVENT_PLANT(EAFGantrySwungOut);

  HANDLE_EVENT(EAFSetTappingMasses);
  HANDLE_EVENT_PRODUCT(EAFSetTappedWeight);


  // handling bin system signals
  HANDLE_EVENT_DATA(EAFBinMatHandlingStart);
  HANDLE_EVENT_DATA(EAFBinMatHandlingStop);

  // handling stirring system signals
  HANDLE_EVENT(EAFBottomStirringStart);
  HANDLE_EVENT(EAFBottomStirringEnd);
  HANDLE_EVENT(EAFLadleStirringStart);
  HANDLE_EVENT(EAFLadleStirringStop);


  return false;
}


bool CDM_EAFSignalsAndMeasurementsEventHandler::doEAFCyclicMeasurement(CEventMessage& Event)
{
  log("++++++ CDM_EventHandler::doEAFCyclicMeasurement Start",3);

  bool RetValue = true;

  // try to update Event with assigend data (ProductID...)
  if (m_pDataInterface                && 
      m_pDMTask->getpPlantManager()   && 
      m_pDMTask->getpProductManager())
  {
    copyDataEventData(Event); 

    if ( checkEventAssignment(Event) )
    {
      std::string DataKey = Event.getDataKey();

      std::string MeasurementType = m_pDataInterface->getString(DataKey,DATA::MeasurementType);

      if ( MeasurementType == DEF_CYCLIC_MEASUREMENT_TYPES::CoolingWater )
      {
        log("++++++ CDM_EAFSignalsAndMeasurementsEventHandler::doEAFCyclicMeasurement(DEF_CYCLIC_MEASUREMENT_TYPES:CoolingWater)",4);
        
        // copy data to "plant" at plant management interface
        m_pDMTask->getpPlantManager()->changeCoolingWaterData(Event);
      }
      else if ( MeasurementType == DEF_CYCLIC_MEASUREMENT_TYPES::Electric )
      {
        log("++++++ CDM_EAFSignalsAndMeasurementsEventHandler::doEAFCyclicMeasurement(DEF_CYCLIC_MEASUREMENT_TYPES:Electric)",4);
        // data must be copied to Product manager first
        // data will be accumulated there !
        m_pDMTask->getpProductManager()->changeElectricalData(Event);

        // copy data to "transfer car" at plant management interface
        m_pDMTask->getpPlantManager()->changeElectricalData(Event);

        RetValue = RetValue && CDM_EAFDBManagerTask::getInstance()->getDBManager()->evCyclicMeasurementElectric(Event);
      }
      else if ( MeasurementType == DEF_CYCLIC_MEASUREMENT_TYPES::Stirring )
      {
        log("++++++ CDM_EAFSignalsAndMeasurementsEventHandler::doEAFCyclicMeasurement(DEF_CYCLIC_MEASUREMENT_TYPES:Stirring)",4);
        // data must be copied to Product manager first
        // data will be accumulated there !
        m_pDMTask->getpProductManager()->changeStirringData(Event);

      }
      else if ( MeasurementType == DEF_CYCLIC_MEASUREMENT_TYPES::WasteGas )
      {
        log("++++++ CDM_EAFSignalsAndMeasurementsEventHandler::doEAFCyclicMeasurement(DEF_CYCLIC_MEASUREMENT_TYPES:WasteGas)",4);
        // copy data to respective "transfer car" at plant management interface
        m_pDMTask->getpPlantManager()->changeWasteGasData(Event);
      }
      else if ( MeasurementType == DEF_CYCLIC_MEASUREMENT_TYPES::Burning)
      {
        log("++++++ CDM_EAFSignalsAndMeasurementsEventHandler::doEAFCyclicMeasurement(DEF_CYCLIC_MEASUREMENT_TYPES:Burning)",4);
        // data are Product and Plant related 
        m_pDMTask->getpProductManager()->changeBurningData(Event);
        m_pDMTask->getpProductManager()->changeGasData(Event);

        m_pDMTask->getpPlantManager()->changeBurningData(Event);
        m_pDMTask->getpProductManager()->changeGasData(Event);
      }
      else if ( MeasurementType == DEF_CYCLIC_MEASUREMENT_TYPES::Injection)
      {
        log("++++++ CDM_EAFSignalsAndMeasurementsEventHandler::doEAFCyclicMeasurement(DEF_CYCLIC_MEASUREMENT_TYPES:Injection)",4);
        // data must be copied to Product manager first
        // data will be accumulated there !
        m_pDMTask->getpProductManager()->changeInjectionData(Event);

        // copy data to respective "transfer car" at plant management interface
        m_pDMTask->getpPlantManager()->changeInjectionData(Event);
      }
      else if ( MeasurementType == DEF_CYCLIC_MEASUREMENT_TYPES::MatFeeding)
      {
        log("++++++ CDM_EAFSignalsAndMeasurementsEventHandler::doEAFCyclicMeasurement(DEF_CYCLIC_MEASUREMENT_TYPES:MatFeeding)",4);
        RetValue = m_pDMTask->getpProductManager()->changeMaterialFeedingData(Event);
      }

      if (RetValue)
      {
        // activate cyclic trigger
        RetValue = handleCyclicTriggerCall(Event);

        startCyclicTriggerCalls(Event);
      }
    }// if ( checkEventAssignment(Event) )
  }

  log("++++++ CDM_EventHandler::doEAFCyclicMeasurement End",3);

  return RetValue; // event handled
}

bool CDM_EAFSignalsAndMeasurementsEventHandler::doEAFSetTappingMasses(CEventMessage& Event)
{
  bool ReturnValue = false;

  try
  {
    if ( checkEventAssignment(Event) )
    {
      if (copyDataEventData(Event))
      {
        if (m_pDMTask->getpProductManager()) 
        {
          ReturnValue = m_pDMTask->getpProductManager()->changeTappingData(Event);
          ReturnValue = ReturnValue &&  dispatchEvent(Event);
        }        
      }
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDM_EventHandler::doProductEvent()",
      "");
  }
  return ReturnValue;
}

bool CDM_EAFSignalsAndMeasurementsEventHandler::doEAFBottomStirringStart(CEventMessage& Event)
{
  doEAFStirring(Event);
  return true; // event handled
}

bool CDM_EAFSignalsAndMeasurementsEventHandler::doEAFBottomStirringEnd(CEventMessage& Event)
{
  doEAFStirring(Event);
  return true; // event handled
}


bool CDM_EAFSignalsAndMeasurementsEventHandler::doEAFLadleStirringStart(CEventMessage& Event)
{
  bool RetValue = false;

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << Event.getHeatID()
    << ", " << Event.getTreatID() << ", " << Event.getDataKey();

  try
  {
    // copy Plant relevant data from Event interface
    if (copyDataEventData(Event))
    {
      if (m_pDMTask->getpPlantManager()) 
      {
        m_pDMTask->getpPlantManager()->changeStirringData(Event);
      }

      if (checkEventAssignment(Event)) // to find ProductID
      {
        if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evLadleStirringStart(Event))
        {
          dispatchEvent(Event);
        }
      }
    } // if ( copyDataEventData(Event) )
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      "CDM_EAFSignalsAndMeasurementsEventHandler::doEAFLadleStirringStart()",
      ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      "CDM_EAFSignalsAndMeasurementsEventHandler::doEAFLadleStirringStart()",
      ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDM_EAFSignalsAndMeasurementsEventHandler::doEAFLadleStirringStart()",
      ExceptionMsg.str().c_str());
  }

  return true; // event handled
}

bool CDM_EAFSignalsAndMeasurementsEventHandler::doEAFLadleStirringStop(CEventMessage& Event)
{
  bool RetValue = false;

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << Event.getHeatID()
    << ", " << Event.getTreatID() << ", " << Event.getDataKey();

  try
  {
    // copy Plant relevant data from Event interface
    if ( copyDataEventData(Event) )
    {
      if (m_pDMTask->getpPlantManager()) 
      {
        m_pDMTask->getpPlantManager()->changeStirringData(Event);
      }

      // find related product
      if ( checkEventAssignment(Event) )
      {
        if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evLadleStirringStop(Event))
        {
          dispatchEvent(Event);
        }
      }
    } // if ( copyDataEventData(Event) )
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      "CDM_EAFSignalsAndMeasurementsEventHandler::doEAFLadleStirringStop()",
      ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      "CDM_EAFSignalsAndMeasurementsEventHandler::doEAFLadleStirringStop()",
      ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDM_EAFSignalsAndMeasurementsEventHandler::doEAFLadleStirringStop()",
      ExceptionMsg.str().c_str());
  }

  return true; // event handled
}

bool CDM_EAFSignalsAndMeasurementsEventHandler::doEAFTappingStart(CEventMessage& Event)
{
  bool RetValue = false;

  // copy data from DH to DM_DataInterface
  if ( copyDataEventData(Event) )
  {
    if ( checkEventAssignment(Event) )
    {
      if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evTappingStart(Event))
      {
        RetValue = doEAFTapping(Event);
      }


		//SARS : AutoDelay
		bool isDelay;
    if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->LastPowerOffToTapStartDelays(Event,true,isDelay))
    {
			if(isDelay)
			{
				Event.setMessage(EAF_EvMsg::evEAFDelayStatus);
				if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evDelayStatus(Event))
				{
					dispatchEvent(Event);
				}
			}
    }

		//SARS : AutoDelay
		//bool isDelay;
    if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->ExtraPowerOnDelays(Event,true,isDelay))
    {
			if(isDelay)
			{
				Event.setMessage(EAF_EvMsg::evEAFDelayStatus);
				if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evDelayStatus(Event))
				{
					dispatchEvent(Event);
				}
			}
    }
		


    }
  }


  return true; // event handled
}

bool CDM_EAFSignalsAndMeasurementsEventHandler::doEAFTappingEnd(CEventMessage& Event)
{
  bool RetValue = false;

  // copy data from DH to DM_DataInterface
  if ( copyDataEventData(Event) )
  {
    if ( checkEventAssignment(Event) )
    {
      if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evTappingEnd(Event))
      {
        RetValue = doEAFTapping(Event);
      }

      if ( RetValue )
      {
        if (m_pDMTask->getpProductManager()) 
        {
          m_pDMTask->getpProductManager()->changeProductInformation(Event);
          m_pDMTask->getpProductManager()->changeAssignedModel(Event, "");
        }
        if (m_pDMTask->getpPlantManager()) 
        {
          m_pDMTask->getpPlantManager()->changePlantInformation(Event);
        }

        // now defined at TSM
        // CEventMessage NewEvent(Event);
        // NewEvent.setMessage(EAF_EvMsg::evEAFAutoHeatAnnouncement);
        // NewEvent.dispatch("Tracking_EAF_1","Tracking_EAF_1");
      }


		//SARS : AutoDelay
		bool isDelay;
    if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->TapStartToTapEndDelays(Event,true,isDelay))
    {
			if(isDelay)
			{
				Event.setMessage(EAF_EvMsg::evEAFDelayStatus);
				if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evDelayStatus(Event))
				{
					dispatchEvent(Event);
				}
			}
    }





    }
  }

  return true; // event handled
}

bool CDM_EAFSignalsAndMeasurementsEventHandler::doEAFTapping(CEventMessage& Event)
{
  bool RetValue = true;
  // try to update Event with assigend data (ProductID...)
  if ( checkEventAssignment(Event) )
  {
    // set tapping start/end time
    if ( m_pDMTask->getpPlantManager() )
    {
      RetValue = m_pDMTask->getpProductManager()->changeTappingData(Event);
    }

    if (m_pDMTask->getpProductManager())
    {
      RetValue = m_pDMTask->getpProductManager()->changeProductInformation(Event);
    }

    // send event to respective destinations
    RetValue = dispatchEvent(Event);
  }

  return RetValue; // event handled
}


bool CDM_EAFSignalsAndMeasurementsEventHandler::doEAFStirring(CEventMessage& Event)
{
  // try to update Event with assigend data (ProductID...)
  if ( checkEventAssignment(Event) )
  {
    // copy data from DH to DM_DataInterface
    if ( copyDataEventData(Event) )
    {
      // update ProductManagerInterface Data
      if (m_pDMTask->getpProductManager() )
      {
        m_pDMTask->getpProductManager()->changeStirringData(Event);

        // send event to respective destinations
        dispatchEvent(Event);
      }
    }
  }
  return true; // event handled
}

bool CDM_EAFSignalsAndMeasurementsEventHandler::doEAFBurnerStart(CEventMessage& Event)
{
  doEAFBurner(Event);

  return true; // event handled
}

bool CDM_EAFSignalsAndMeasurementsEventHandler::doEAFBurnerStop(CEventMessage& Event)
{
  doEAFBurner(Event);

  return true; // event handled
}

bool CDM_EAFSignalsAndMeasurementsEventHandler::doEAFManipGasLanceStart(CEventMessage& Event)
{
  doEAFManipGasLance(Event);

  return true; // event handled
}

bool CDM_EAFSignalsAndMeasurementsEventHandler::doEAFManipGasLanceStop(CEventMessage& Event)
{
  doEAFManipGasLance(Event);

  return true; // event handled
}

bool CDM_EAFSignalsAndMeasurementsEventHandler::doEAFManipInjectLanceStart(CEventMessage& Event)
{
  doOnManipInjectLance(Event);

  return true; // event handled
}
bool CDM_EAFSignalsAndMeasurementsEventHandler::doEAFManipInjectLanceStop(CEventMessage& Event)
{
  doOnManipInjectLance(Event);

  return true; // event handled
}

bool CDM_EAFSignalsAndMeasurementsEventHandler::doOnManipInjectLance(CEventMessage& Event)
{
  // try to update Event with assigend data (ProductID...)
  if ( checkEventAssignment(Event) )
  {
    // copy all data into the event data corba interface
    if ( copyDataEventData(Event) && 
         m_pDMTask->getpProductManager() && 
         m_pDMTask->getpPlantManager() )
    {
      m_pDMTask->getpPlantManager()->changeInjectionData(Event);

      m_pDMTask->getpProductManager()->changeInjectionData(Event);

      // send event to respective destinations
      dispatchEvent(Event);
    }
  }
  return true;
}


bool CDM_EAFSignalsAndMeasurementsEventHandler::doEAFPowerOn(CEventMessage& Event)
{
  bool RetValue = doOnHeating(Event);

  RetValue = RetValue && CDM_EAFDBManagerTask::getInstance()->getDBManager()->evPowerOn(Event);

		//SARS : AutoDelay
		bool isDelay;
    if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->LastTapEndToPowerOnDelays(Event,true,isDelay))
    {
			if(isDelay)
			{
				Event.setMessage(EAF_EvMsg::evEAFDelayStatus);
				if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evDelayStatus(Event))
				{
					dispatchEvent(Event);
					return RetValue; 
				}
			}
    }

		//SARS : AutoDelay
    if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->PowerOffToPowerOnDelays(Event,true,isDelay))
    {
			if(isDelay)
			{
				Event.setMessage(EAF_EvMsg::evEAFDelayStatus);
				if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evDelayStatus(Event))
				{
					dispatchEvent(Event);
				}
			}
    }

  return RetValue; // event handled
}

bool CDM_EAFSignalsAndMeasurementsEventHandler::doEAFPowerOff(CEventMessage& Event)
{
  bool RetValue = doOnHeating(Event);

  RetValue = RetValue && CDM_EAFDBManagerTask::getInstance()->getDBManager()->evPowerOff(Event);

  return RetValue; // event handled
}

bool CDM_EAFSignalsAndMeasurementsEventHandler::doOnHeating(CEventMessage& Event)
{
  // try to update Event with assigend data (ProductID...)
  if ( checkEventAssignment(Event) )
  {
    // copy all data into the event data corba interface
    if ( copyPlantEventData(Event)         && 
      m_pDMTask->getpProductManager()  )
    {
      m_pDMTask->getpProductManager()->changeHeatingData(Event);
      m_pDMTask->getpProductManager()->changeElectricalData(Event);

      // send event to respective destinations
      dispatchEvent(Event);
    }
  }
  return true;
}

bool CDM_EAFSignalsAndMeasurementsEventHandler::doEAFManipGasLance(CEventMessage& Event)
{
  // try to update Event with assigend data (ProductID...)
  if ( checkEventAssignment(Event) )
  {
    // copy data from DH to DM_DataInterface
    if ( copyDataEventData(Event) )
    {
      // update ProductManagerInterface Data
      if (m_pDMTask->getpPlantManager() && 
        m_pDMTask->getpProductManager()  )
      {
        m_pDMTask->getpProductManager()->changeGasData(Event);
        //m_pDMTask->getpProductManager()->changeGasLanceData(Event);

        // send event to respective destinations
        dispatchEvent(Event);
      }
    }
  }
  return true;
}

bool CDM_EAFSignalsAndMeasurementsEventHandler::doEAFCarbonInjectStart(CEventMessage& Event)
{
  // try to update Event with assigend data (ProductID...)
  if ( checkEventAssignment(Event) )
  {
    // copy data from DH to DM_DataInterface
    if ( copyDataEventData(Event) )
    {
      // update ProductManagerInterface Data
      if (m_pDMTask->getpPlantManager() && 
        m_pDMTask->getpProductManager()  )
      {
        m_pDMTask->getpPlantManager()->changeInjectionData(Event);

        m_pDMTask->getpProductManager()->changeInjectionData(Event);

        // send event to respective destinations
        dispatchEvent(Event);
      }
    }
  }
  return true;
}

bool CDM_EAFSignalsAndMeasurementsEventHandler::doEAFCarbonInjectStop(CEventMessage& Event)
{
  // try to update Event with assigend data (ProductID...)
  if ( checkEventAssignment(Event) )
  {
    // copy data from DH to DM_DataInterface
    if ( copyDataEventData(Event) )
    {
      // update ProductManagerInterface Data
      if (m_pDMTask->getpPlantManager() && 
        m_pDMTask->getpProductManager()  )
      {
        m_pDMTask->getpPlantManager()->changeInjectionData(Event);

        m_pDMTask->getpProductManager()->changeInjectionData(Event);

        // send event to respective destinations
        dispatchEvent(Event);
      }
    }
  }
  return true;
}

bool CDM_EAFSignalsAndMeasurementsEventHandler::doEAFBurner(CEventMessage& Event)
{
  // try to update Event with assigend data (ProductID...)
  if ( checkEventAssignment(Event) )
  {
    // copy data from DH to DM_DataInterface
    if ( copyDataEventData(Event) )
    {
      // update ProductManagerInterface Data
      if (m_pDMTask->getpPlantManager() && 
          m_pDMTask->getpProductManager()  )
      {
        // data are Product and Plant related 
        m_pDMTask->getpProductManager()->changeBurningData(Event);

        m_pDMTask->getpPlantManager()->changeBurningData(Event);

        // send event to respective destinations
        dispatchEvent(Event);
      }
    }
  }
  return true; // event handled
}

// cyclic event for ladle stirring
bool CDM_EAFSignalsAndMeasurementsEventHandler::doEAFCyclicMeasurementTapLadle(CEventMessage& Event)
{
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << Event.getHeatID()
    << ", " << Event.getTreatID() << ", " << Event.getDataKey();

  try
  {
      // try to update Event with assigend data (ProductID...)
    if (m_pDataInterface                && 
        m_pDMTask->getpPlantManager()   && 
        m_pDMTask->getpProductManager())
    {
      // copy data from DH to DM_DataInterface
      copyDataEventData(Event); 

      if ( checkEventAssignment(Event) )
      {
        // copy Plant relevant data from Event interface
        m_pDMTask->getpPlantManager()->changeStirringData(Event);

        //copy Product relevant data from Event interface
        m_pDMTask->getpProductManager()->changeStirringData(Event);

        // activate cyclic trigger
        handleCyclicTriggerCall(Event);

        startCyclicTriggerCalls(Event);
      }
    }
  } // try block
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      "CDM_EAFSignalsAndMeasurementsEventHandler::doEAFCyclicMeasurementTapLadle()",
      ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      "CDM_EAFSignalsAndMeasurementsEventHandler::doEAFCyclicMeasurementTapLadle()",
      ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDM_EAFSignalsAndMeasurementsEventHandler::doEAFCyclicMeasurementTapLadle()",
      ExceptionMsg.str().c_str());
  }
  return true; // event handled
}


