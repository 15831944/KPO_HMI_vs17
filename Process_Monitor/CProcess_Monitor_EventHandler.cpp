// Copyright (C) 2009 SMS Demag AG Germany

#include "iEventMessages_s.hh"
#include "iProcess_Monitor_s.hh"
//#include "cCBS_StdInitBase.h"
#include "CEventMessage.h"

#include "CProcess_Monitor_TelcomIntf_Impl.h"
#include "CProcess_Monitor_EventHandler.h"

bool CProcess_Monitor_EventHandler::handleEvent(const FRIESEvent& Event)
{
  bool RetValue = true;
	CEventMessage ActEvent(Event);

  std::string ActMessage = ActEvent.getMessage();

  if (ActMessage == AOD_EvMsg::evAODHeatAnnouncement ||
      ActMessage == BOF_EvMsg::evBOFHeatAnnouncement ||
      ActMessage == LF_EvMsg::evLFHeatAnnouncement ||
      ActMessage == EAF_EvMsg::evEAFHeatAnnouncement ||
      ActMessage == LTS_EvMsg::evLTSHeatAnnouncement 
     )
  {
    log (ActEvent, PM::INFO_LEVEL);
    
    enable(ActEvent);
  }
  if (ActMessage == AOD_EvMsg::evAODHeatDeparture ||
      ActMessage == AOD_EvMsg::evAODHeatCancellation ||
      ActMessage == BOF_EvMsg::evBOFTappingEnd ||
      ActMessage == LF_EvMsg::evLFHeatDeparture ||
      ActMessage == EAF_EvMsg::evEAFTappingEnd ||
      ActMessage == EAF_EvMsg::evEAFHeatCancellation ||
      ActMessage == LTS_EvMsg::evLTSHeatDeparture ||
      ActMessage == BOF_EvMsg::evBOFHeatCancellation ||
      ActMessage == LF_EvMsg::evLFHeatCancellation ||
      ActMessage == LTS_EvMsg::evLTSHeatCancellation 
     )
  {
    log(ActEvent, PM::INFO_LEVEL);

    disable(ActEvent);
  }
  else
    RetValue = false; // The event is not for this handler

  return RetValue;
}

CProcess_Monitor_EventHandler::~CProcess_Monitor_EventHandler()
{
}

CProcess_Monitor_EventHandler::CProcess_Monitor_EventHandler(CProcess_Monitor_Task* _task)
:m_pProcMonTask(_task)
{
}

bool CProcess_Monitor_EventHandler::enable(CEventMessage& Event)
{
  bool RetValue = false;
  std::string PlantID = Event.getPlantID();
  std::string ProductID = Event.getProductID();

  log("CProcess_Monitor_EventHandler::enable()", PM::INFO_LEVEL);

  if (m_pProcMonTask && m_pProcMonTask->getTelcom_Interface())
  {
    // check if plant id is supported
    if (m_pProcMonTask->getTelcom_Interface()->isPlantId(PlantID))
    {
      std::string ActProduct = m_pProcMonTask->getTelcom_Interface()->getString(PlantID, PM::ProductID);
      if (ActProduct == DEF::Inv_String)
        ActProduct.clear();


      if ( !ProductID.empty() &&
          ProductID != DEF::Inv_String )
      {
        // stop control task first
        if ( m_pProcMonTask->getTelcom_Interface()->getBoolean(PlantID, PM::Control) )
        {
          log("Disable control for Plant->Product " + PlantID + "->" + ActProduct, PM::WARNING_LEVEL);
        }
        m_pProcMonTask->getTelcom_Interface()->setBoolean(PlantID, PM::Control, false);

        // set received product data
        m_pProcMonTask->getTelcom_Interface()->setString(PlantID, PM::ProductID, Event.getProductID());
        m_pProcMonTask->getTelcom_Interface()->setString(PlantID, PM::HeatID, Event.getHeatID());
        m_pProcMonTask->getTelcom_Interface()->setString(PlantID, PM::TreatID, Event.getTreatID());
        m_pProcMonTask->getTelcom_Interface()->setString(PlantID, PM::OrderId, Event.getOrderID());
        // reset counter
        m_pProcMonTask->getTelcom_Interface()->setLong(PlantID, PM::ErrorCount, 0);

        m_pProcMonTask->getTelcom_Interface()->initProcesses(PlantID);

        // get respective model from tracker
        DM::iDM_Interface_var& pDM = m_pProcMonTask->getpDM_Interface(Event.getSender(), DM::PRODUCT);
        if (pDM)
        {
          std::string CustHeatID = CIntfData::ToStdString(pDM->getString(ProductID.c_str(), PM::CustHeatID));
          if (CustHeatID == DEF::Inv_String)
            CustHeatID.clear();

          std::string CustTreatID = CIntfData::ToStdString(pDM->getString(ProductID.c_str(), PM::CustTreatID));
          if (CustTreatID == DEF::Inv_String)
            CustTreatID.clear();

          m_pProcMonTask->getTelcom_Interface()->setString(PlantID, PM::CustHeatID, CustHeatID);
          m_pProcMonTask->getTelcom_Interface()->setString(PlantID, PM::CustTreatID, CustTreatID);

          std::string ActModel = CIntfData::ToStdString(pDM->getString(ProductID.c_str(), PM::ActModel));
          if (ActModel != DEF::Inv_String &&
              !ActModel.empty())
          {
            log("Add act model :" + ActModel, PM::INFO_LEVEL);
            m_pProcMonTask->getTelcom_Interface()->addProcess(PlantID, ActModel);
          }
          else
            log("No model is added to monitor list", PM::WARNING_LEVEL);

          if (!CustHeatID.empty() && !CustTreatID.empty())
          {
            std::string Message = "Enable control " + PlantID + "->" + ProductID;
            log(Message, PM::INFO_LEVEL);
            m_pProcMonTask->getTelcom_Interface()->setBoolean(PlantID, PM::Control, true);
            m_pProcMonTask->setWorking(true);
            m_pProcMonTask->setStateDetails("Last enabled monitoring: Plant->Heat (product) " + 
                                             PlantID + "->" + CustHeatID + " (" + ProductID + ")");
            RetValue = true;
          }
          else
          {
            log("No CustHeatID or CustTreatID available. Cannot start monitor "+PlantID+"->"+ProductID, PM::ERROR_LEVEL);
          }
        }
        else
        {
          log("Data Manager not reachable. Cannot start monitor "+PlantID+"->"+ProductID, PM::ERROR_LEVEL);
        }
      }
      else
        log("Unspecified Product Received: " + ProductID, PM::ERROR_LEVEL);
    }
    else
      log("Received plantid is not supported : " + PlantID + ". See ini file [Monitor] PlantID=", PM::WARNING_LEVEL);
  }
  return RetValue;
}

bool CProcess_Monitor_EventHandler::disable(CEventMessage& Event)
{
  bool RetValue = false;
  std::string PlantID = Event.getPlantID();
  std::string ProductID = Event.getProductID();

  log("CProcess_Monitor_EventHandler::disable()", PM::INFO_LEVEL);

  if (m_pProcMonTask && m_pProcMonTask->getTelcom_Interface())
  {
    if (m_pProcMonTask->getTelcom_Interface()->isPlantId(PlantID))
    {
      std::string ActProduct = m_pProcMonTask->getTelcom_Interface()->getString(PlantID, PM::ProductID);

      if ( !ProductID.empty() &&
          ProductID != DEF::Inv_String )
      {
        if (ActProduct == ProductID) // to be shure that disable is done once only 
        {
          // disable last
          std::string Message = "Disable control for Plant->Product " + PlantID + "->" + ActProduct;
          log(Message, PM::WARNING_LEVEL);
          m_pProcMonTask->getTelcom_Interface()->setBoolean(PlantID, PM::Control, false);
          std::string CustHeatID = m_pProcMonTask->getTelcom_Interface()->getString(PlantID, PM::CustHeatID);

          log("Remove processes for plant: " + PlantID, PM::INFO_LEVEL);
          m_pProcMonTask->getTelcom_Interface()->resetProcesses(PlantID);

          m_pProcMonTask->setStateDetails("Last stopped monitoring: Plant->Heat (product) " + 
                                           PlantID + "->" + CustHeatID + " (" + ProductID + ")");

          // now set working state false if nothing has to be monitored
          bool WorkState = false;
          std::map< std::string, std::set<std::string> > MonitorList;
          std::map< std::string, std::set<std::string> >::const_iterator itMonitorList;
          MonitorList = m_pProcMonTask->getTelcom_Interface()->getMonitorList();
          for (itMonitorList = MonitorList.begin(); itMonitorList != MonitorList.end(); itMonitorList ++)
          {
            std::string ActPlantID = itMonitorList->first;

            WorkState = WorkState || m_pProcMonTask->getTelcom_Interface()->getBoolean(ActPlantID, PM::Control);
          }
          if ( WorkState == false )
          {
            //not yet viable to reset status m_pProcMonTask->setWorking(WorkState);
            m_pProcMonTask->setStateDetails("No monitoring for any plant currently active. Waiting for next heat announcement.");
          }

          RetValue = true;
        }
      }
      else
        log("Unspecified Product Received: " + ProductID, PM::ERROR_LEVEL);
    }
    else
      log("Received plantid is not supported : " + PlantID + ". See ini file [Monitor] PlantID=", PM::WARNING_LEVEL);
  }
  return RetValue;
}

bool CProcess_Monitor_EventHandler::doOnEventHandlingError(const FRIESEvent& Event)
{
  bool RetValue = true;

  // This method is called if event is accepted but not handled
  // Monitor accepts all events from tracking but handle only two.

  //try
  //{
  //  CEventMessage EventMessage(Event);

  //  std::stringstream Message;

  //  Message << "Event not handled! "
  //          <<  EventMessage.getSender()    << " -> "
  //          <<  EventMessage.getReceiver()  << " "
  //          <<  EventMessage.getMessage()   << " for ProductID : "
  //          <<  EventMessage.getProductID();

  //  log(Message.str());
  //}
  //catch(...)
  //{
  //  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  //  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  //  pEventLog->EL_ExceptionCaught(sMessage,"","CEventHandler::doOnEventHandlingError()","Handling event error");
  //}

  return RetValue;

}
