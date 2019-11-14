// Copyright (C) 2011 SMS Siemag AG

#include "CStirringDataHandler.h"
#include "CDM_EAFTask.h"
#include "CDM_EAFDBManagerTask.h"

#include "DEF_GC_PLANT.h"
#include "DEF_GC_STIRR_GAS_TYPE.h"
#include "DEF_GCE_BURNER_GASTYPE.h"

#include "cCBS_StdConnection.h"
#include "CGasLanceDataHandler.h"

#include "CDM_EAFTreatmentManagementEventHandler.h"


CDM_EAFTreatmentManagementEventHandler::CDM_EAFTreatmentManagementEventHandler()
: CDM_TreatmentManagementEventHandler( CDM_EAFTask::getInstance() )
{
}

CDM_EAFTreatmentManagementEventHandler::~CDM_EAFTreatmentManagementEventHandler()
{
}

bool CDM_EAFTreatmentManagementEventHandler::handleEvent(CEventMessage& evMessage)
{
  HANDLE_EVENT(EAFHeatAnnouncement);
  HANDLE_EVENT(EAFAutoHeatAnnouncement);
  HANDLE_EVENT(EAFHeatCancellation);
  HANDLE_EVENT(EAFHeatDeparture);
  HANDLE_EVENT(EAFHeatStart);
  HANDLE_EVENT(EAFHeatEnd);
  HANDLE_EVENT(EAFDelayStatus);
  HANDLE_EVENT(EAFBasketRequest);
  HANDLE_EVENT(EAFBasketHotMetalInfomationRequest);
  HANDLE_EVENT(EAFPhaseReport);
  HANDLE_EVENT(EAFHeatScheduleUpdate);
  HANDLE_EVENT(EAFCreateTreatmentID);
  HANDLE_EVENT_DATA(EAFParameterUpdate);

  HANDLE_EVENT(EAFChangeAimData);
  HANDLE_EVENT(EAFSteelGradeChanged);
  HANDLE_EVENT(EAFChangeHotHeelData);

  HANDLE_EVENT(EAFTapLadleData);
  HANDLE_EVENT(EAFChangeTapLadleData);

  HANDLE_EVENT(EAFChangeProdPracPointerProcess);
  HANDLE_EVENT(EAFChangeProdPracPointerInjection);
  HANDLE_EVENT(EAFChangeProdPracPointerOxygen);
  HANDLE_EVENT(EAFChangeProdPracPointerBurner);
  //not used any more HANDLE_EVENT(EAFChangeProdPracPointerElec);
  HANDLE_EVENT(EAFChangeProdPracPointerParameter);
  HANDLE_EVENT(EAFChangeProdPracPointerRestriction);
  HANDLE_EVENT(EAFChangeProdPracPointerScrapLoading);
  //HANDLE_EVENT(EAFChangeProdPracPointerStirring);
  
  // ProdPracData stored by HMI
  HANDLE_EVENT_DATA(EAFChangeProdPracDataProcess);
  HANDLE_EVENT_DATA(EAFChangeProdPracDataInjection);
  HANDLE_EVENT_DATA(EAFChangeProdPracDataOxygen);
  HANDLE_EVENT_DATA(EAFChangeProdPracDataBurner);
  //not used any more HANDLE_EVENT_DATA(EAFChangeProdPracDataElec);
  HANDLE_EVENT_DATA(EAFChangeProdPracDataParameter);
  HANDLE_EVENT_DATA(EAFChangeProdPracDataRestriction);
  HANDLE_EVENT_DATA(EAFChangeProdPracDataScrapLoading);
  HANDLE_EVENT_DATA(EAFChangeProdPracDataStirring);
  HANDLE_EVENT_DATA(EAFChangeProdPracDataRecipeCTRL);
  HANDLE_EVENT_DATA(EAFChangeProdPracManipGasLance);
  
  HANDLE_EVENT(EAFProductionOrderChanged);

  HANDLE_EVENT(EAFChangeThermalStatus);
  HANDLE_EVENT(EAFChangeTreatmentMode);

  HANDLE_EVENT_PRODUCT(EAFUpdateAimDepartureTime);
  HANDLE_EVENT_PRODUCT(EAFUpdateAimTemperature);

  HANDLE_EVENT(EAFOrderScrap);
  HANDLE_EVENT_DATA(EAFMaintenance);
  HANDLE_EVENT_DATA(EAFGetModelStatus);
  HANDLE_EVENT(EAFSetUpOfHeat); 
  HANDLE_EVENT_DATA(EAFMinChargeableBinWeightUpdate);
  HANDLE_EVENT(EAFUpdatePlantStatus);
  HANDLE_EVENT_DATA(EAFApplicationSystemRestart);
  HANDLE_EVENT_DATA(EAFProductionReport);
  HANDLE_EVENT_DATA(EAFPullElectrodeRequest);

  HANDLE_EVENT_DATA(EAFElectrodeHydraulicSystemInhibitRequest);
  HANDLE_EVENT_DATA(EAFElectrodeHydraulicSystemReleaseRequest);

  HANDLE_EVENT(EAFManipInjectLanceAvail);  
  HANDLE_EVENT(EAFBurnerGasAvail);  


  HANDLE_EVENT_PLANT(EAFManipGasLanceAvail);

  HANDLE_EVENT_PLANT(EAFOxygenLanceInhibit);
  HANDLE_EVENT_PLANT(EAFOxygenLanceRelease);


  HANDLE_EVENT_PLANT(EAFLevel1HeatReset);

  return false;
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFSetUpOfHeat(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evSetupOfHeat(Event))
  {
    if (checkEventAssignment(Event))
    {
      RetValue = dispatchEvent( Event );
    }
  }
  return RetValue;
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFHeatAnnouncement(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if (CDM_EAFTask::getInstance()->getpPlantManager()->checkAssignement(Event))
  {
    if ( CDM_EAFDBManagerTask::getInstance()->getDBManager()->evHeatAnnouncement(Event,false) )
    {
      RetValue = doHeatAnnouncement( Event );

      if ( RetValue )
      {
        CDM_EAFDBManagerTask::getInstance()->getStdConnection()->commit();
      }
      else
      {
        CDM_EAFDBManagerTask::getInstance()->getStdConnection()->rollback();
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

  return RetValue;
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFAutoHeatAnnouncement(CEventMessage& Event)
{
  bool RetValue = false;

  CEventMessage NewEvent;

  // set internal CORBA data to handle heta announcement like to be initiatet by HMI
  // getting CEventMessage NewEvent back by reference !
  if ( CDM_EAFDBManagerTask::getInstance()->getDBManager()->evAutoHeatAnnouncement(NewEvent) )
  {
    // will now be called at "Tapping End"

    // clean internal buffer for previous product
    //m_pDMTask->getpPlantManager()->deassignProduct(Event.getProductID());
    //m_pDMTask->getpProductManager()->changeAssignedModel(Event.getProductID(),"");
    //CDM_EventHandler::removeAllCyclicTriggerCalls(Event.getProductID());

    RetValue = CDM_EAFDBManagerTask::getInstance()->getDBManager()->evHeatAnnouncement(NewEvent,false) ;

    RetValue = RetValue && doHeatAnnouncement( NewEvent );
  }


  if ( RetValue )
  {
    CDM_EAFDBManagerTask::getInstance()->getStdConnection()->commit();
  }
  else
  {
    CDM_EAFDBManagerTask::getInstance()->getStdConnection()->rollback();
  }

  return RetValue;
}


bool CDM_EAFTreatmentManagementEventHandler::doEAFHeatCancellation(CEventMessage& Event)
{
  bool RetValue = false;
  if ( checkEventAssignment(Event) )
  {
    copyDataEventData(Event);

    if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evCancelHeat(Event))
    {
      RetValue = doHeatCancellation( Event );
    }
  }
  return RetValue;
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFHeatDeparture(CEventMessage& Event)
{
  bool RetValue = false;
  if ( checkEventAssignment(Event) )
  {
    copyDataEventData(Event); 

    if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evHeatDeparture(Event))
    {
      RetValue = doHeatDeparture( Event );
    }


		//SARS : AutoDelay - JSW does not need this
		/*bool isDelay;
    if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->AutomaticlyFillRelativeDelays(Event,true,isDelay))
    {
			if(isDelay)
			{
				Event.setMessage(EAF_EvMsg::evEAFDelayStatus);
				if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evDelayStatus(Event))
				{
					dispatchEvent(Event);
				}
			}
    }*/


  }
  return RetValue;
}



bool CDM_EAFTreatmentManagementEventHandler::doEAFHeatStart(CEventMessage& Event)
{
  bool RetValue = false;
  if ( checkEventAssignment(Event) )
  {
    copyDataEventData(Event); 

    if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evHeatStart(Event))
    {
      RetValue = doHeatStart ( Event );
    }
  }
  
  return RetValue;
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFHeatEnd(CEventMessage& Event)
{
  bool RetValue = false;
  if ( checkEventAssignment(Event) )
  {
    copyDataEventData(Event); 

    if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evHeatEnd(Event))
    {
      RetValue = doHeatEnd ( Event );
    }
  }
  
  return RetValue;
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFBasketRequest(CEventMessage& Event)
{
  dispatchEvent(Event);
  return true;
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFBasketHotMetalInfomationRequest(CEventMessage& Event)
{
  if ( checkEventAssignment(Event) )
  {
    dispatchEvent(Event);
  }
  return true;
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFPhaseReport(CEventMessage& Event)
{

  std::string dataKey = Event.getDataKey();
  seqPhaseDataReport seqPhaseData = CIntfData::ToCORBAType(m_pDataInterface->getPhaseDataReport(dataKey.c_str(),DATA::PhaseDataReport));
  if(seqPhaseData.length() > 0 )
  {
    seqPhaseData[0].GasCons = getGasCons4PhaseReport(Event);
    m_pDataInterface->setPhaseDataReport(dataKey.c_str(),DATA::PhaseDataReport,seqPhaseData);
  }

  // try to update Event with assigend data (ProductID...)

  if ( checkEventAssignment(Event) )
  {
    if ( copyProductEventData(Event))
    {
      // send event to respective destinations
      dispatchEvent(Event);

    }
  }
  return true;
}

double CDM_EAFTreatmentManagementEventHandler::getLastBurnerO2Cons(const std::string& dataKey, const std::string& Plant)
{
  seqGasLanceData GasLanceData = CIntfData::ToCORBAType(m_pPlantManagementInterface->getGasLanceData(Plant.c_str(),DATA::BurnerAmount));

  CGasLanceDataHandler GasLanceDataHandler(GasLanceData);

  double GasValue = GasLanceDataHandler.getGasValue(DEF_DEVICES::Burner, DEF_GCE_BURNER_GASTYPE::O2);

  return GasValue;
}

double CDM_EAFTreatmentManagementEventHandler::getLastBurnerBGCons(const std::string& dataKey, const std::string& Plant)
{
  seqGasLanceData GasLanceData = CIntfData::ToCORBAType(m_pPlantManagementInterface->getGasLanceData(Plant.c_str(),DATA::BurnerAmount));

  CGasLanceDataHandler GasLanceDataHandler(GasLanceData);

  double GasValue = GasLanceDataHandler.getGasValue(DEF_DEVICES::Burner, DEF_GCE_BURNER_GASTYPE::BG);

  return GasValue;
}


double CDM_EAFTreatmentManagementEventHandler::getLastLanceO2Cons(const std::string& dataKey, const std::string& Plant)
{
  seqGasLanceData GasLanceData = CIntfData::ToCORBAType(m_pPlantManagementInterface->getGasLanceData(Plant.c_str(),DATA::GasLanceAmount));

  CGasLanceDataHandler GasLanceDataHandler(GasLanceData);

  double GasValue = GasLanceDataHandler.getGasValue(DEF_DEVICES::TopLance, DEF_GAS::O2);

  return GasValue;
}

double  CDM_EAFTreatmentManagementEventHandler::getLastLanceN2Cons(const std::string& dataKey, const std::string& Plant)
{
  seqGasLanceData GasLanceData = CIntfData::ToCORBAType(m_pPlantManagementInterface->getGasLanceData(Plant.c_str(),DATA::GasLanceAmount));

  CGasLanceDataHandler GasLanceDataHandler(GasLanceData);

  double GasValue = GasLanceDataHandler.getGasValue(DEF_DEVICES::TopLance, DEF_GAS::N2);

  return GasValue;
}

double  CDM_EAFTreatmentManagementEventHandler::getLastStirrArCons(const std::string& dataKey, const std::string& Plant)
{
  seqStirringData StirringAmount = CIntfData::ToCORBAType(m_pPlantManagementInterface->getStirringData(Plant.c_str(),DATA::StirringAmount));

  CStirringDataHandler StirringDataHandler(StirringAmount);

  double Cons = StirringDataHandler.getAccumulatedGasValue(DEF_GC_STIRR_GAS_TYPE::Ar);

  return Cons ;
}

double  CDM_EAFTreatmentManagementEventHandler::getLastStirrN2Cons(const std::string& dataKey, const std::string& Plant)
{
  seqStirringData StirringAmount = CIntfData::ToCORBAType(m_pPlantManagementInterface->getStirringData(Plant.c_str(),DATA::StirringAmount));

  CStirringDataHandler StirringDataHandler(StirringAmount);

  double Cons = StirringDataHandler.getAccumulatedGasValue(DEF_GC_STIRR_GAS_TYPE::N2);

  return Cons ;
}


seqDeviceGasData CDM_EAFTreatmentManagementEventHandler::getGasCons4PhaseReport(CEventMessage& Event)
{
  std::string Plant = m_pDMTask->getPlantFromEventMessage(Event);

  double o2BurnerCons = getLastBurnerO2Cons(Event.getDataKey(), Plant.c_str()) ;
  double bgBurnerCons = getLastBurnerBGCons(Event.getDataKey(), Plant.c_str()) ;
  double o2LanceCons  = getLastLanceO2Cons(Event.getDataKey(), Plant.c_str()) ;
  double n2LanceCons  = getLastLanceN2Cons(Event.getDataKey(), Plant.c_str()) ;
  double arStirrCons  = getLastStirrArCons(Event.getDataKey(), Plant.c_str()) ;
  double n2StrrrCons  = getLastStirrN2Cons(Event.getDataKey(), Plant.c_str()) ;

  sGasData o2BurnerGasData;
  sGasData bgBurnerGasData;
  sGasData o2LanceGasData;
  sGasData n2LanceGasData;
  sGasData arStirrGasData;
  sGasData n2StirrGasData;

  o2BurnerGasData.GasType =  DEF_GCE_BURNER_GASTYPE::O2.c_str();
  o2BurnerGasData.GasValue = o2BurnerCons;

  bgBurnerGasData.GasType =  DEF_GCE_BURNER_GASTYPE::BG.c_str();
  bgBurnerGasData.GasValue = bgBurnerCons;

  o2LanceGasData.GasType =  DEF_GCE_BURNER_GASTYPE::O2.c_str();
  o2LanceGasData.GasValue = o2LanceCons;

  n2LanceGasData.GasType =  DEF_GCE_BURNER_GASTYPE::N2.c_str();
  n2LanceGasData.GasValue = n2LanceCons;

  arStirrGasData.GasType =  DEF_GC_STIRR_GAS_TYPE::Ar.c_str();
  arStirrGasData.GasValue = arStirrCons;

  n2StirrGasData.GasType =  DEF_GC_STIRR_GAS_TYPE::N2.c_str();
  n2StirrGasData.GasValue = n2StrrrCons;

  seqGasData seqBurnerGasData;
  seqGasData seqLanceGasData;
  seqGasData seqStirrGasData;

  CIntfData::insert(seqBurnerGasData, o2BurnerGasData);
  CIntfData::insert(seqBurnerGasData, bgBurnerGasData);

  CIntfData::insert(seqLanceGasData, o2LanceGasData);
  CIntfData::insert(seqLanceGasData, n2LanceGasData);

  CIntfData::insert(seqStirrGasData, arStirrGasData);
  CIntfData::insert(seqStirrGasData, n2StirrGasData);

  sDeviceGasData burnerDeviceGasData;
  sDeviceGasData lanceDeviceGasData;
  sDeviceGasData stirrDeviceGasData;

  burnerDeviceGasData.GasData = seqBurnerGasData;
  burnerDeviceGasData.Device = DEF_DEVICES::Burner;
  lanceDeviceGasData.GasData = seqLanceGasData;
  lanceDeviceGasData.Device = DEF_DEVICES::TopLance;
  stirrDeviceGasData.GasData = seqStirrGasData;
  stirrDeviceGasData.Device =  DEF_DEVICES::TopLance;// todo device is not mapped to gas type, no device name for stirring ,change later

  seqDeviceGasData deviceDeviceArray;

  CIntfData::insert(deviceDeviceArray, burnerDeviceGasData);
  CIntfData::insert(deviceDeviceArray, lanceDeviceGasData);
  CIntfData::insert(deviceDeviceArray, stirrDeviceGasData);

  return deviceDeviceArray;

}

bool CDM_EAFTreatmentManagementEventHandler::doEAFHeatScheduleUpdate(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if ( checkEventAssignment(Event) )
  {
    // we have to set PlantId, it is used for further selection for scrap handling
    if ( Event.getPlantID().empty() )
    {
      std::string PlantId = DEF_GC_PLANT::EAF_1;

      cCBS_StdInitBase::getInstance()->replaceWithEntry("PLANT","PlantId",PlantId);

      Event.setPlantID(PlantId);
    }


    if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evHeatScheduleUpdate(Event))
    {
      RetValue = dispatchEvent(Event);
    }
  }

  return true;
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFCreateTreatmentID(CEventMessage& Event)
{
  doCreateTreatmentID(Event);
  return true;
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFTapLadleData(CEventMessage& Event)
{
  return doEAFChangeTapLadleData(Event);
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFChangeTapLadleData(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if ( checkEventAssignment(Event) )
  {
    if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evChangeTapLadleData(Event))
    {
      m_pDMTask->getpPlantManager()->changeTappingData(Event);

      RetValue = dispatchEvent(Event);
    }
  }

  return true;
}


bool CDM_EAFTreatmentManagementEventHandler::sendAdditionalEvents(CEventMessage& Event)
{
  return CDM_EventHandler::sendAdditionalEvents(Event);
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFManipInjectLanceAvail(CEventMessage& Event)
{
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << Event.getProductID() << ", " << Event.getHeatID()
    << ", " << Event.getTreatID() << ", " << Event.getDataKey();
  try
  {
    // try to update Event with assigend data (ProductID...)
    if ( checkEventAssignment(Event) )
    {
      if (m_pDataInterface)
      {
        if ( copyDataEventData(Event) )
        {
          // copy Plant relevant data from Event interface
          if (m_pDMTask->getpPlantManager()) 
          {
            m_pDMTask->getpPlantManager()->changeInjectionData(Event);
          }

          // copy Product relevant data from Event interface
          if (m_pDMTask->getpProductManager()) 
          {
            m_pDMTask->getpProductManager()->changeInjectionData(Event);
          }

          dispatchEvent(Event);

        } // if ( copyDataEventData(Event) )
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      "CDM_EAFTreatmentManagementEventHandler::doEAFManipInjectLanceAvail()",
      ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      "CDM_EAFTreatmentManagementEventHandler::doEAFManipInjectLanceAvail()",
      ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDM_EAFTreatmentManagementEventHandler::doEAFManipInjectLanceAvail()",
      ExceptionMsg.str().c_str());
  }
  return true;
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFBurnerGasAvail(CEventMessage& Event)
{
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << Event.getProductID() << ", " << Event.getHeatID()
    << ", " << Event.getTreatID() << ", " << Event.getDataKey();
  try
  {
    // try to update Event with assigend data (ProductID...)
    if ( checkEventAssignment(Event) )
    {
      if (m_pDataInterface)
      {
        if ( copyDataEventData(Event) )
        {
          // copy Plant relevant data from Event interface
          if (m_pDMTask->getpPlantManager()) 
          {
            m_pDMTask->getpPlantManager()->changeBurningData(Event);
          }

          // copy Product relevant data from Event interface
          if (m_pDMTask->getpProductManager()) 
          {
            m_pDMTask->getpProductManager()->changeBurningData(Event);
          }

          dispatchEvent(Event);

        } // if ( copyDataEventData(Event) )
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      "CDM_EAFTreatmentManagementEventHandler::doEAFBurnerGasAvail()",
      ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      "CDM_EAFTreatmentManagementEventHandler::doEAFBurnerGasAvail()",
      ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDM_EAFTreatmentManagementEventHandler::doEAFBurnerGasAvail()",
      ExceptionMsg.str().c_str());
  }
  return true;
}


bool CDM_EAFTreatmentManagementEventHandler::doEAFDelayStatus(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evDelayStatus(Event))
  {
    RetValue = dispatchEvent(Event);
  }

  return RetValue;  
}


bool CDM_EAFTreatmentManagementEventHandler::doEAFChangeProdPracPointerInjection(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evChangeProdPracPointerInjection(Event))
  {
    if (checkEventAssignment(Event))
    {
      RetValue = dispatchEvent(Event);
    }
  }
  return RetValue;  
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFChangeProdPracPointerOxygen(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evChangeProdPracPointerOxygen(Event))
  {
    if (checkEventAssignment(Event))
    {
      RetValue = dispatchEvent(Event);
    }
  }
  return RetValue;  
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFChangeProdPracPointerParameter(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evChangeProdPracPointerParameter(Event))
  {
    if (checkEventAssignment(Event))
    {
      RetValue = dispatchEvent(Event);
    }
  }
  return RetValue;  
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFChangeProdPracPointerBurner(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evChangeProdPracDataBurner(Event))
  {
    if (checkEventAssignment(Event))
    {
      RetValue = dispatchEvent(Event);
    }
  }
  return RetValue;  
}


bool CDM_EAFTreatmentManagementEventHandler::doEAFChangeProdPracPointerProcess(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evChangeProdPracPointerProcess(Event))
  {
    if (checkEventAssignment(Event))
    {
      RetValue = dispatchEvent(Event);
    }
  }
  return RetValue;  
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFChangeProdPracPointerRestriction(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evChangeProdPracPointerRestriction(Event))
  {
    if (checkEventAssignment(Event))
    {
      RetValue = dispatchEvent(Event);
    }
  }
  return RetValue;  
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFChangeProdPracPointerScrapLoading(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evChangeProdPracPointerScrapLoading(Event))
  {
    if (checkEventAssignment(Event))
    {
      RetValue = dispatchEvent(Event);
    }
  }
  return RetValue;  
}


bool CDM_EAFTreatmentManagementEventHandler::doEAFChangeAimData(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evChangeAimData(Event))
  {
    if (checkEventAssignment(Event))
    {
      RetValue = dispatchEvent(Event);
    }
  }
  return RetValue;
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFChangeHotHeelData(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evChangeHotHeelData(Event))
  {
    if (checkEventAssignment(Event))
    {
      RetValue = dispatchEvent(Event);
    }
  }
  return RetValue;
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFChangeThermalStatus(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  //change furnace status before sending event
  CDM_EAFTask::getInstance()->getpPlantManager()->changePlantInformation(Event) ;

  if (checkEventAssignment(Event))
  {
    if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evChangeThermalStatus(Event))
    {
      RetValue = dispatchEvent(Event);
    }
  }

  return true;
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFProductionOrderChanged(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evProductionOrderChanged(Event))
  {
    if (checkEventAssignment(Event))
    {
      RetValue = dispatchEvent(Event);
    }
  }

  return true;
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFSteelGradeChanged(CEventMessage& Event)
{
  bool RetValue = false;

  if (copyDataEventData(Event))
  {
    if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evSteelGradeChanged(Event))
    {
      if (checkEventAssignment(Event))
      {
        RetValue = dispatchEvent(Event);
      }
    }
  }

  return true;
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFChangeTreatmentMode(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evChangeTreatmentMode(Event))
  {
    if (checkEventAssignment(Event))
    {
      RetValue = dispatchEvent(Event);
    }
  }
  return true;
}

bool CDM_EAFTreatmentManagementEventHandler::doOnUnknownProduct(CEventMessage& Event)
{
  // send event to tsm to add product and be able to pass all product events
  CEventMessage NewEvent(Event);

  NewEvent.setMessage(EAF_EvMsg::evEAFTsmCreateProduct);

  return dispatchEvent(NewEvent);;
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFOrderScrap(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evOrderScrap(Event))
  {
    if (checkEventAssignment(Event))
    {
      RetValue = dispatchEvent(Event);
    }

  }
  return true;
}

bool CDM_EAFTreatmentManagementEventHandler::doEAFUpdatePlantStatus(CEventMessage& Event)
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
