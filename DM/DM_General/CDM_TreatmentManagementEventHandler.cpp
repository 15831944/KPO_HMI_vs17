// Copyright (C) 2004 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"

#include "CSMC_DataProvider_Impl.h"
#include "CDM_ProductManagementInterface_Impl.h"

#include "cCBS_StdEventLogFrameController.h"
#include "CDM_EventHandler.h"
#include "CDM_Task.h"

#include "CEventMessage.h"

#include "CDM_TreatmentManagementEventHandler.h"

bool CDM_TreatmentManagementEventHandler::doHeatAnnouncementOffline(CEventMessage& Event)
{
  return doHeatAnnouncement(Event);
}

bool CDM_TreatmentManagementEventHandler::doHeatAnnouncement(CEventMessage& Event)
{	
  bool RetValue = true;

  try
  {
    log ("++++++ CDM_TreatmentManagementEventHandler::doHeatAnnouncement",3);

    // First registers the product with the Product Manager when a HEAT_ANNOUCEMENT
    // or respective event is coming in.
    if (m_pDMTask->getpProductManager() && 
        m_pDMTask->getpPlantManager()) 
    {
      m_pDMTask->getpProductManager()->registerProduct(Event);

      // Checks the validity of the event received.
      if ( checkEventAssignment(Event) )
      {
        std::string ProductID = Event.getProductID();
        std::string HeatID = Event.getHeatID();
        std::string TreatID = Event.getTreatID();
        std::vector<std::string> ProductList;
        std::vector<std::string>::iterator it;

        // preset product data with incoming event data like
        // Date, Plant location or HeatPreparation value
        m_pDMTask->getpProductManager()->changeProductInformation(Event);

        // first checking product data against database to deassign heats from tracker 
        // that are no longer in production
        ProductList = m_pDMTask->getpPlantManager()->getProductsOutOfProduction(Event);
        for ( it = ProductList.begin() ; it != ProductList.end() ; ++it)
        {
          m_pDMTask->getpPlantManager()->deassignProduct(*it);
          m_pDMTask->getpProductManager()->changeAssignedModel(*it,"");
          CDM_EventHandler::removeAllCyclicTriggerCalls(*it);
        }

        // remove cyclic triggers for actual heat to be shure that old triggers for identical heat will be removed
        CDM_EventHandler::removeAllCyclicTriggerCalls(Event);

        // Assigns the product to an idle Model process, because we might have multiple instances 
        // running simultaneously, so find one of them as the assigned target. 
        m_pDMTask->getpPlantManager()->assignProduct(Event);

        // changing plant information / resettig Plant data
        m_pDMTask->getpPlantManager()->changePlantInformation(Event);

        // first checks product data against database to deassign heats from tracker 
        // that are no longer in production
        // set Model ID of Plant Manager for Product
        m_pDMTask->getpProductManager()->changeAssignedModel(Event, m_pDMTask->getpPlantManager()->getAssignedModel(ProductID));

        // send event to corresponding receivers or destinations. 
        dispatchEvent(Event);

        startCyclicTriggerCalls(Event);
      }
    }
    else
    {
      log("PlantManager or ProductManager not available",1);
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,
      m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID(),m_pDMTask->getExternalHeatID(Event.getProductID()));
    pEventLog->EL_ExceptionCaught(sMessage,"","CDM_TreatmentManagementEventHandler::doHeatAnnouncement","");
  }

  return RetValue;

}

bool CDM_TreatmentManagementEventHandler::doHeatCancellation(CEventMessage& Event)
{
  try
  {
    //check if event could be assigned to product
    if ( checkEventAssignment(Event) )
    {
      m_pDMTask->log("INFO: CDM_TreatmentManagementEventHandler::doHeatCancellation!",2);

      std::string ProductID = Event.getProductID();
      std::string HeatID = Event.getHeatID();
      std::string TreatID = Event.getTreatID();

      // Deassign the product from the plant manager. 
      if (m_pDMTask->getpPlantManager())
      { 
        // definetely deassign product and release transfer car
        m_pDMTask->getpPlantManager()->changePlantInformation( Event );
      }

      // Decouples the product from a particular model instance, i.e.,LF_1 or LF_2
      if (m_pDMTask->getpProductManager()) 
      {
        m_pDMTask->getpProductManager()->changeAssignedModel(Event, "");
        m_pDMTask->getpProductManager()->changeOrderData(Event, "");
        m_pDMTask->getpProductManager()->changeProductInformation(Event);
      }

      // send event to corresponding receivers or destinations. 
      bool RetValue = dispatchEvent(Event);

      // sendAdditionalEvents called at "afterDispatchEvent"

      // remove existing cyclic trigger calls
      CDM_EventHandler::removeAllCyclicTriggerCalls(Event);
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,
      m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID(),m_pDMTask->getExternalHeatID(Event.getProductID()));
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDM_TreatmentManagementEventHandler::doHeatCancellation",
      "");
  }
  return true;
}

bool CDM_TreatmentManagementEventHandler::doHeatDeparture(CEventMessage& Event)
{
  try
  {
    //check if event could be assigned to product
    if ( checkEventAssignment(Event) )
    {
      if (m_pDMTask->getpPlantManager())
      {
        m_pDMTask->getpPlantManager()->changePlantInformation(Event);

        if (m_pDMTask->getpProductManager()) 
        {
          m_pDMTask->getpProductManager()->changeProductInformation(Event);
          m_pDMTask->getpProductManager()->changeAssignedModel(Event, "");
        }

        // send event to corresponding receivers or destinations. 
        bool RetValue = dispatchEvent(Event);

        // sendAdditionalEvents called at "afterDispatchEvent"

        // remove existing cyclic trigger calls
        CDM_EventHandler::removeAllCyclicTriggerCalls(Event);
      }
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,
      m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID(),m_pDMTask->getExternalHeatID(Event.getProductID()));
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDM_TreatmentManagementEventHandler::doHeatDeparture",
      "");
  }
  return true;
}

bool CDM_TreatmentManagementEventHandler::doHeatStart(CEventMessage& Event)
{
  try
  {
    //check if event could be assigned to product
    if ( checkEventAssignment(Event) )
    {
      // copy all data releated for this event to Event Interface
      // some of this data will be overwritten with more actual values later on

      copyDataEventData(Event);

      if ( m_pDMTask->getpProductManager() )
      {
        m_pDMTask->getpProductManager()->changeProductInformation(Event);
      }

      if ( m_pDMTask->getpPlantManager() )
      {
        m_pDMTask->getpPlantManager()->changePlantInformation(Event);
      }

      dispatchEvent(Event);
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,
      m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID(),m_pDMTask->getExternalHeatID(Event.getProductID()));
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDM_TreatmentManagementEventHandler::doHeatStart",
      "");
  }
  return true;
}

bool CDM_TreatmentManagementEventHandler::doHeatEnd(CEventMessage& Event)
{
  try
  {
    //check if event could be assigned to product
    if ( checkEventAssignment(Event) )
    {
      if (m_pDMTask->getpPlantManager())
      {
        m_pDMTask->getpPlantManager()->changePlantInformation(Event);
      }

      if (m_pDMTask->getpProductManager())
      {
        m_pDMTask->getpProductManager()->changeProductInformation(Event);
        m_pDMTask->getpProductManager()->changeAssignedModel(Event, "");
      }

      // send event to corresponding receivers or destinations. 
      bool RetValue = dispatchEvent(Event);

      // sendAdditionalEvents called at "afterDispatchEvent"
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,
      m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID(),m_pDMTask->getExternalHeatID(Event.getProductID()));
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDM_TreatmentManagementEventHandler::doHeatEnd",
      "");

  }
  return true;
}

CDM_TreatmentManagementEventHandler::CDM_TreatmentManagementEventHandler(CDM_Task* pDMTask)
:CDM_EventHandler( pDMTask )
{
}

CDM_TreatmentManagementEventHandler::~CDM_TreatmentManagementEventHandler()
{
}

bool CDM_TreatmentManagementEventHandler::doCreateTreatmentID(CEventMessage& Event)
{
  try
  {
    //check if event could be assigned to product
    if ( checkEventAssignment(Event) )
    {
      // copy all data releated for this event to Event Interface
      // some of this data will be overwritten with more actual values later on
      copyDataEventData(Event);

      if (m_pDMTask->getpProductManager()) 
      {
        m_pDMTask->getpProductManager()->changeProductInformation(Event);
      }

      dispatchEvent(Event);
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,
      m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID(),m_pDMTask->getExternalHeatID(Event.getProductID()));
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDM_TreatmentManagementEventHandler::doCreateTreatmentID",
      "");
  }
  return true;
}

bool CDM_TreatmentManagementEventHandler::doProductionOrderChanged(CEventMessage& Event)
{
  try
  {
    //check if event could be assigned to product
    if ( checkEventAssignment(Event) )
    {
      if ( m_pDMTask != 0 )
      {
        if ( m_pDMTask->getpProductManager() )
        {
          std::string NewOrderID = m_pDMTask->getpDataInterface()->getString(Event.getDataKey(),DATA::OrderId);
          if ( NewOrderID != DEF::Inv_String )
          {
            if ( m_pDMTask->getpProductManager()->changeOrderData(Event, NewOrderID) )
            {
              std::string ProductId   = Event.getProductID();
              std::string PlantId     = Event.getPlantID();
              std::string CustHeatId  = m_pDMTask->getpProductManagementInterface()->getString(ProductId, DATA::CustHeatID);
              std::string CustTreatId = m_pDMTask->getpProductManagementInterface()->getString(ProductId, DATA::CustTreatID);

              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__, __LINE__, m_pDMTask->getProcessState(ProductId), ProductId, CustHeatId);
              pEventLog->EL_OrderChanged(sMessage, CustHeatId.c_str(), CustTreatId.c_str(), PlantId.c_str(), NewOrderID.c_str());

              Event.setOrderID(NewOrderID);
              dispatchEvent(Event);
            }
          }
        }
        else
        {
          log("doProductionOrderChanged: Invalid order received",1);
        }
      }
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,
      m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID(),m_pDMTask->getExternalHeatID(Event.getProductID()));
    pEventLog->EL_ExceptionCaught(sMessage, "Unknown", "CDM_TreatmentManagementEventHandler::doProductionOrderChanged", "");
  }

  return true;
}
