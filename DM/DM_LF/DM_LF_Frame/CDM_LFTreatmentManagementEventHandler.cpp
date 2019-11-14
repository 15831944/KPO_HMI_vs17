// Copyright (C) 2004 SMS Demag AG

#include "cCBS_StdConnection.h"

#include "CDM_LFTask.h"
#include "CDM_LFTreatmentManagementEventHandler.h"
#include "CDM_ProductManagementInterface_Impl.h"

CDM_LFTreatmentManagementEventHandler::CDM_LFTreatmentManagementEventHandler()
: CDM_TreatmentManagementEventHandler( CDM_LFTask::getInstance() )
{
}

CDM_LFTreatmentManagementEventHandler::~CDM_LFTreatmentManagementEventHandler()
{
}

bool CDM_LFTreatmentManagementEventHandler::handleEvent(CEventMessage& evMessage)
{
  // handle management events
  HANDLE_EVENT(LFHeatAnnouncement);
  HANDLE_EVENT(LFHeatAnnouncementOffline);
  HANDLE_EVENT(LFHeatCancellation);
  HANDLE_EVENT(LFHeatDeparture);
  HANDLE_EVENT(LFHeatStart);
  HANDLE_EVENT(LFHeatEnd);

  HANDLE_EVENT(LFHeatScheduleUpdate);
  HANDLE_EVENT(LFSetUpOfHeat);
  HANDLE_EVENT(LFResetOfHeat);

  // handle treatment changing events
  HANDLE_EVENT(LFChangeAimData);
  HANDLE_EVENT(LFChangeProdPracPointerElec);
  HANDLE_EVENT(LFChangeProdPracPointerParameter);
  HANDLE_EVENT(LFChangeProdPracPointerRestriction);
  HANDLE_EVENT(LFChangeProdPracPointerStirring);
  HANDLE_EVENT(LFLadleDataChanged);
  HANDLE_EVENT(LFProductionOrderChanged);
  HANDLE_EVENT(LFSteelGradeChanged);


  // synchronisation
  HANDLE_EVENT(LFCleanlinessStirring);
  HANDLE_EVENT(LFCooling);
  HANDLE_EVENT(LFDelayStatus);
  HANDLE_EVENT(LFMainHeating);
  HANDLE_EVENT(LFInitialHeating);
  HANDLE_EVENT(LFFinalHeating);

  HANDLE_EVENT(LFCreateTreatmentID);
  HANDLE_EVENT_DATA(LFParameterUpdate);

  HANDLE_EVENT_DATA(LFPlantStatusRequest);
  HANDLE_EVENT_DATA(LFRemoveLiquidSteelData);
  HANDLE_EVENT_DATA(LFChangedMatSetPointsByOperator);
  HANDLE_EVENT_DATA(LFChangeProdPracDataRecipeCtrl);
  HANDLE_EVENT_DATA(LFChangeProdPracDataElec);
  HANDLE_EVENT_DATA(LFChangeProdPracDataRecipe);
  HANDLE_EVENT_DATA(LFChangeProdPracDataStirring);
  HANDLE_EVENT_DATA(LFRestrictionDataUpdate);
  HANDLE_EVENT_DATA(LFGetModelStatus);
  HANDLE_EVENT_DATA(LFMaintenance);
  HANDLE_EVENT_DATA(LFUpdateAimDepartureTime);
  HANDLE_EVENT_DATA(LFUpdateAimTemperature);
  HANDLE_EVENT_DATA(LFSoftStirring);
  HANDLE_EVENT(LFUpdatePlantStatus);
  HANDLE_EVENT_DATA(LFApplicationSystemRestart);
  HANDLE_EVENT_DATA(LFPhaseReport);
  HANDLE_EVENT_DATA(LFProductionReport);
  HANDLE_EVENT_DATA(LFPullElectrodeRequest);
  HANDLE_EVENT_DATA(LFElectrodeHydraulicSystemInhibitRequest);
  HANDLE_EVENT_DATA(LFElectrodeHydraulicSystemReleaseRequest);
  HANDLE_EVENT_DATA(LFLevel1HeatReset);

  return false;
}

bool CDM_LFTreatmentManagementEventHandler::doLFHeatAnnouncement(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if (CDM_LFTask::getInstance()->getpPlantManager()->checkAssignement(Event))
  {
    if (CDM_LFDBManagerTask::getInstance()->getDBManager()->evHeatAnnouncement(Event,false))
    {
      RetValue = doHeatAnnouncement( Event );

      if ( RetValue )
      {
        CDM_LFDBManagerTask::getInstance()->getStdConnection()->commit();
      }
      else
      {
        CDM_LFDBManagerTask::getInstance()->getStdConnection()->rollback();
      }
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_HeatAnnouncementError(sMessage,Event.getHeatID().c_str(),Event.getTreatID().c_str(),Event.getPlantID().c_str());
    }
  }
  else
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_HeatAnnouncementError(sMessage,Event.getHeatID().c_str(),Event.getTreatID().c_str(),Event.getPlantID().c_str());
  }

  return true;
}

bool CDM_LFTreatmentManagementEventHandler::doLFHeatAnnouncementOffline(CEventMessage& Event)
{
  return doHeatAnnouncementOffline( Event ); 
}


bool CDM_LFTreatmentManagementEventHandler::doLFHeatCancellation(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_LFDBManagerTask::getInstance()->getDBManager()->evCancelHeat(Event))
  {
    RetValue = doHeatCancellation( Event );
  }

  return true;
}

bool CDM_LFTreatmentManagementEventHandler::doLFHeatDeparture(CEventMessage& Event)
{
  bool RetValue = false;

  if (copyDataEventData(Event))
  {
    if (checkEventAssignment(Event))
    {
      if(CDM_LFDBManagerTask::getInstance()->getDBManager()->evHeatDeparture(Event))
      {
        RetValue = doHeatDeparture( Event );
      }
    }

		//SARS : AutoDelay
		bool isDelay;
    if(CDM_LFDBManagerTask::getInstance()->getDBManager()->AutomaticlyFillRelativeDelays(Event,true,isDelay))
    {
			if(isDelay)
			{
				Event.setMessage(LF_EvMsg::evLFDelayStatus);
				if(CDM_LFDBManagerTask::getInstance()->getDBManager()->evDelayStatus(Event))
				{
					dispatchEvent(Event);
				}
			}
    }

  }
  return true;
}

bool CDM_LFTreatmentManagementEventHandler::doLFHeatStart(CEventMessage& Event)
{
  bool RetValue = false;
  if ( checkEventAssignment(Event) )
  {
    copyDataEventData(Event); 

    if(CDM_LFDBManagerTask::getInstance()->getDBManager()->evHeatStart(Event))
    {
      RetValue = doHeatStart ( Event );
    }
  }
  
  return true;
}

bool CDM_LFTreatmentManagementEventHandler::doLFHeatEnd(CEventMessage& Event)
{
  bool RetValue = false;
  if ( checkEventAssignment(Event) )
  {
    copyDataEventData(Event); 

    if(CDM_LFDBManagerTask::getInstance()->getDBManager()->evHeatEnd(Event))
    {
      RetValue = doHeatEnd ( Event ); // SARS : doHeatStart ( Event );
    }
  }
  
  return true;
}

bool CDM_LFTreatmentManagementEventHandler::doLFHeatScheduleUpdate(CEventMessage& Event)
{
  // try to update Event with assigend data (ProductID...)
  if ( checkEventAssignment(Event) )
  {
    if ( copyDataEventData(Event) )
    {
      // send event to respective destinations
      dispatchEvent(Event);
    }
  }
  return true;
}

bool CDM_LFTreatmentManagementEventHandler::doLFCreateTreatmentID(CEventMessage& Event)
{
  doCreateTreatmentID(Event);
  return true;
}

bool CDM_LFTreatmentManagementEventHandler::doLFSetUpOfHeat(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_LFDBManagerTask::getInstance()->getDBManager()->evSetupOfHeat(Event))
  {
    if (checkEventAssignment(Event))
    {
      RetValue = dispatchEvent( Event );
    }
  }
  return true;
}

bool CDM_LFTreatmentManagementEventHandler::doLFResetOfHeat(CEventMessage& Event)
{
  return dispatchEvent( Event );
}

bool CDM_LFTreatmentManagementEventHandler::sendAdditionalEvents(CEventMessage& Event)
{
  return CDM_EventHandler::sendAdditionalEvents(Event);
}

bool CDM_LFTreatmentManagementEventHandler::doLFFinalHeating(CEventMessage& Event)
{
  return doOnHeating(Event);
}

bool CDM_LFTreatmentManagementEventHandler::doLFCleanStirring(CEventMessage& Event)
{
  //Insert Action to PD_ACTION
  CDM_LFDBManagerTask::getInstance()->getDBManager()->evCleaninessStirringReceived(Event);

  //do data copy
  return doDataEvent(Event);
}

bool CDM_LFTreatmentManagementEventHandler::doLFInitialHeating(CEventMessage& Event)
{
  return doOnHeating(Event);
}

bool CDM_LFTreatmentManagementEventHandler::doLFMainHeating(CEventMessage& Event)
{
  return doOnHeating(Event);
}

bool CDM_LFTreatmentManagementEventHandler::doLFTemperatureHold(CEventMessage& Event)
{
  return doOnHeating(Event);
}

bool CDM_LFTreatmentManagementEventHandler::doLFCleanlinessStirring(CEventMessage& Event)
{
  bool RetValue = false;

  if(CDM_LFDBManagerTask::getInstance()->getDBManager()->evCleaninessStirringReceived(Event))
  {
    RetValue = doOnHeating(Event);
  }
  return true;
}

bool CDM_LFTreatmentManagementEventHandler::doLFCooling(CEventMessage& Event)
{
  return doOnHeating(Event);
}

bool CDM_LFTreatmentManagementEventHandler::doLFDelayStatus(CEventMessage& Event)
{
  bool RetValue = false;

  if ( copyDataEventData(Event) )
  {
    if ( CDM_LFDBManagerTask::getInstance()->getDBManager()->evDelayStatus(Event) )
    {
      RetValue = dispatchEvent(Event);
    }
  }

  return true;  
}

bool CDM_LFTreatmentManagementEventHandler::doLFChangeProdPracPointerStirring(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_LFDBManagerTask::getInstance()->getDBManager()->evChangeProdPracPointerStirring(Event))
  {
    if (checkEventAssignment(Event))
    {
      RetValue = dispatchEvent(Event);
    }
  }
  return true;
}

bool CDM_LFTreatmentManagementEventHandler::doLFChangeProdPracPointerRestriction(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_LFDBManagerTask::getInstance()->getDBManager()->evChangeProdPracPointerRestriction(Event))
  {
    if (checkEventAssignment(Event))
    {
      RetValue = dispatchEvent(Event);
    }
  }
  return true;
}

bool CDM_LFTreatmentManagementEventHandler::doLFChangeProdPracPointerElec(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_LFDBManagerTask::getInstance()->getDBManager()->evChangeProdPracPointerElec(Event))
  {
    if (checkEventAssignment(Event))
    {
      RetValue = dispatchEvent(Event);
    }
  }
  return true;
}

bool CDM_LFTreatmentManagementEventHandler::doLFChangeAimData(CEventMessage& Event)
{
  bool RetValue = false;

  if ( copyDataEventData(Event) )
  {
    bool DispatchIt = checkEventAssignment(Event);

    // First change of aim data
    if(CDM_LFDBManagerTask::getInstance()->getDBManager()->evChangeAimData(Event))
    {
      if ( DispatchIt )
      {
        dispatchEvent(Event);
      }
    }
    //If any production practice pointer has been changed, then correlated event will be sent.
    if ( CDM_LFDBManagerTask::getInstance()->getDBManager()->evChangeProdPracPointerElec(Event) )
    {
      if ( DispatchIt )
      {
        CEventMessage PPEvent(Event);
        PPEvent.setMessage(LF_EvMsg::evLFChangeProdPracPointerElec);
        dispatchEvent(PPEvent);
      }
    }
    if ( CDM_LFDBManagerTask::getInstance()->getDBManager()->evChangeProdPracPointerParameter(Event) )
    {
      if ( DispatchIt )
      {
        CEventMessage PPEvent(Event);
        PPEvent.setMessage(LF_EvMsg::evLFChangeProdPracPointerParameter);
        dispatchEvent(PPEvent);
      }
    }
    if ( CDM_LFDBManagerTask::getInstance()->getDBManager()->evChangeProdPracPointerRestriction(Event) )
    {
      if ( DispatchIt )
      {
        CEventMessage PPEvent(Event);
        PPEvent.setMessage(LF_EvMsg::evLFChangeProdPracPointerRestriction);
        dispatchEvent(PPEvent);
      }
    }
    if ( CDM_LFDBManagerTask::getInstance()->getDBManager()->evChangeProdPracPointerStirring(Event) )
    {
      if ( DispatchIt )
      {
        CEventMessage PPEvent(Event);
        PPEvent.setMessage(LF_EvMsg::evLFChangeProdPracPointerStirring);
        dispatchEvent(PPEvent);
      }
    }
  }
  return true;
}

bool CDM_LFTreatmentManagementEventHandler::doLFChangeProdPracPointerParameter(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_LFDBManagerTask::getInstance()->getDBManager()->evChangeProdPracPointerParameter(Event))
  {
    if (checkEventAssignment(Event))
    {
      RetValue = dispatchEvent(Event);
    }
  }
  return true;
}

bool CDM_LFTreatmentManagementEventHandler::doLFProductionOrderChanged(CEventMessage& Event)
{
  bool RetValue = false;

  if ( copyDataEventData(Event) )
  {
    if ( CDM_LFDBManagerTask::getInstance()->getDBManager()->evProductionOrderChanged(Event) )
    {
      // send event and show log
      doProductionOrderChanged(Event);
    }
  }

  return true;
}


bool CDM_LFTreatmentManagementEventHandler::doLFLadleDataChanged(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_LFDBManagerTask::getInstance()->getDBManager()->evChangeTapLadleData(Event))
  {
    // fill missing event data
    if ( checkEventAssignment(Event) )
    {
      RetValue = dispatchEvent(Event);
    }
  }
  return true;
}

bool CDM_LFTreatmentManagementEventHandler::doOnHeating(CEventMessage& Event)
{
  // copy all data into the event data corba interface
  if ( copyDataEventData(Event) )
  {
    // try to update Event with assigend data (ProductID...)
    if ( checkEventAssignment(Event) )
    {
      m_pDMTask->getpProductManager()->changeHeatingData(Event);
      m_pDMTask->getpProductManager()->changeElectricalData(Event);

      // send event to respective destinations
      dispatchEvent(Event);
    }
  }
  return true;

}

bool CDM_LFTreatmentManagementEventHandler::doOnUnknownProduct(CEventMessage& Event)
{
  // send event to tsm to add product and be able to pass all product events
  CEventMessage NewEvent(Event);

  NewEvent.setMessage(LF_EvMsg::evLFTsmCreateProduct);

  return dispatchEvent(NewEvent);
}

bool CDM_LFTreatmentManagementEventHandler::doLFSteelGradeChanged(CEventMessage& Event)
{
  bool RetValue = false;

  if ( copyDataEventData(Event) )
  {
    if ( CDM_LFDBManagerTask::getInstance()->getDBManager()->evLFSteelGradeChanged(Event) )
    {
      if (checkEventAssignment(Event))
      {
        RetValue = dispatchEvent(Event);
      }
    }
  }

  return true;
}

bool CDM_LFTreatmentManagementEventHandler::doLFUpdatePlantStatus(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if (checkEventAssignment(Event))
  {
    if (m_pDMTask->getpPlantManager()) 
    {
      m_pDMTask->getpPlantManager()->changeElectricalData(Event);
    }

    RetValue = dispatchEvent(Event);
  }

  return true;
}
