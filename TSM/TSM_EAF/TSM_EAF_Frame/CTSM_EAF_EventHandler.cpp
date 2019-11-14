// Copyright (C) 2004 SMS Demag AG

#include "iEventMessages_s.hh"
#include "cCBS_StdInitBase.h"
#include "CEventMessage.h"
#include "CEventMessageCtrl.h"
#include "CTsmBaseApplication.h"
#include "CTSM_EAF_PhaseChangeAction.h"
#include "CTSM_EAF_EventHandler.h"
#include "CTSM_EAF_Task.h"

// HANDLE_EVENT: In case the message of the actual event is equal to the value of the message
// defined in the IDL, the corresponding method name is constructed and the method is called.
#if defined (HANDLE_EVENT)
#undef HANDLE_EVENT
#endif
#define HANDLE_EVENT(action) if (EAF_EvMsg::ev##action == evMessage.getMessage()) do##action(evMessage);

// FORWARD_EVENT: Just forward the event with adjusted sender and receiver name.
#if defined (FORWARD_EVENT)
#undef FORWARD_EVENT
#endif
#define FORWARD_EVENT CEventMessage Fwd(evMessage); Fwd.dispatch(m_SenderName,m_DestinationList);

CTSM_EAF_EventHandler::CTSM_EAF_EventHandler()
: m_pTsmApplication(0)
{
}

void CTSM_EAF_EventHandler::connectToTsmApplication(CTsmBaseApplication * pTsmApp)
{
  m_pTsmApplication = pTsmApp;
}

bool CTSM_EAF_EventHandler::handleEvent(const FRIESEvent& Event)
{
  CEventMessage evMessage(Event);
  cCBS_StdEvent_Task::getInstance()->setStateDetails("Actual Event Message", evMessage.getContent(), 0);

  try
  {
    // I will only react on messages for TSM
    if (!checkReceiver(evMessage))
      return false;

    // useful to separate output fro TSM and DM parts
    log("+++++++++++++ TSM PART START ++++++++++++++++",3);

    std::string RDY = ".RDY";
    // discard ".RDY" events if no rule defined.
    if (evMessage.getMessage().rfind(RDY) != std::string::npos)
    {
      // check first for tracked product
      if (!m_pTsmApplication->isProductEventRegistered(evMessage))
      {
        // maybe in phase tracker this event is used
        // if not than discard. isProductEventRegistered for phase product
        if (! handlePhaseTrackingEvents(evMessage))
        {
          std::string Message;
          Message  = "Discard event : " + evMessage.getContent();
          log(Message, 4);
        }
        log("+++++++++++++ TSM END ++++++++++++++++",3);
        return true;
      }
    }

   	CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    std::string State = m_pTsmApplication->getProductStatus(evMessage) + " for product " + evMessage.getProductID();
    pEventLog->EL_TrackingState(sMessage,State.c_str());


    // Store original message for further use in the CTSM_EAF_SendEventAction
    CEventMessageCtrl::setEventMessage(evMessage);

    log(evMessage.getContent(), 3);

    // in case of multiple plants, event sender could be like DM_EAF_1
    // TSM Rule sets does only know DM_EAF
    // change event.SenderName before sending event to TSM kernel
    CTSM_EAF_Task::getInstance()->changeEventTransmitterName(evMessage);

    if (evMessage.isPlantEvent())
    {
      // Handle plant related event messages
      if ( m_pTsmApplication->isPlantEventRegistered(evMessage) )
      {
        m_pTsmApplication->handleEvent(evMessage);
      }
      else
      {
        // Only forward the event in case no special rule was defined
        FORWARD_EVENT;
      }
    }
    else
    {
      // NOTE: The order is important for the functionality.
      // call phase tracker, will create and remove additional tracking products 
      handlePhaseTrackingEvents(evMessage); 

      std::stringstream CombinedMessage;
      CombinedMessage << "INFO: Try to find rule for " << evMessage.getSender()+"$"+evMessage.getMessage();
      log(CombinedMessage.str(),3);

      // first handle special events 
      try
      {
        HANDLE_EVENT(EAFHeatAnnouncementOffline);
        HANDLE_EVENT(EAFHeatAnnouncement);
        HANDLE_EVENT(EAFHeatCancellation);
        HANDLE_EVENT(EAFResetOfHeat);
        HANDLE_EVENT(EAFTsmCreateProduct);
        if (evMessage.getMessage() == GEN_EvMsg::evGenRemoveTrackedProduct)
          doGenRemoveTrackedProduct(evMessage);

        //*********
        // Event will be sent if product is registered.
        // A product will be added at announcement or after SetUpOfHeat.
        // SetUpOfHeat is created by DM Component.
        //*********
        if (m_pTsmApplication->isProductRegistered(evMessage))
        {
          if (m_pTsmApplication->isProductEventRegistered(evMessage))
          {
            m_pTsmApplication->handleEvent(evMessage);
          }
          else
          {
            FORWARD_EVENT;
          }
        }
      }
      catch(...)
      {
        std::string Msg("ERORR: Exception in handle event: '");
        Msg += evMessage.getMessage() + "', it will be sent anyway!";
        log(Msg,1);
        FORWARD_EVENT;
      }
    }

    log("+++++++++++++ TSM PART END ++++++++++++++++",3);
  }
  catch(...)
  {
    return false;
  }
	return true;
}

bool CTSM_EAF_EventHandler::doEAFResetOfHeat(CEventMessage & evMessage)
{
  if (m_pTsmApplication->isProductRegistered(evMessage))
  {
    m_pTsmApplication->doHandleProductEvent(evMessage);
    return m_pTsmApplication->doRemoveProduct(evMessage);
  }
  return true;
}

bool CTSM_EAF_EventHandler::doEAFHeatAnnouncement(CEventMessage & evMessage)
{
  return m_pTsmApplication->doAddProduct(evMessage);
}

bool CTSM_EAF_EventHandler::doEAFHeatAnnouncementOffline(CEventMessage & evMessage)
{
  return m_pTsmApplication->doAddProduct(evMessage);
}

bool CTSM_EAF_EventHandler::doEAFHeatCancellation(CEventMessage & evMessage)
{
  if (m_pTsmApplication->isProductRegistered(evMessage))
  {
    m_pTsmApplication->doHandleProductEvent(evMessage);
    return m_pTsmApplication->doRemoveProduct(evMessage);
  }
  return true;
}

bool CTSM_EAF_EventHandler::doEAFTsmCreateProduct(CEventMessage & evMessage)
{
  bool RetValue = m_pTsmApplication->doAddProduct(evMessage);

  // coding is obsolete if respective state transition is designed in TSM rule set
  CEventMessage NewEventMessage(evMessage);
  std::string NewProductID = NewEventMessage.getProductID() + ":HEAT_IS_ANNOUNCED";
  NewEventMessage.setProductID(NewProductID);

  RetValue = RetValue && m_pTsmApplication->doSetProductState(NewEventMessage);

  return RetValue;
}

bool CTSM_EAF_EventHandler::doGenRemoveTrackedProduct(CEventMessage & evMessage)
{
  if (m_pTsmApplication->isProductRegistered(evMessage))
  {
    return m_pTsmApplication->doRemoveProduct(evMessage);
  }
  return true;
}

bool CTSM_EAF_EventHandler::handlePhaseTrackingEvents(CEventMessage& evMessage)
{
  bool RetValue = false;
  try
  {
    std::string msg = evMessage.getMessage();

    if (msg == EAF_EvMsg::evEAFHeatAnnouncement||
        msg == EAF_EvMsg::evEAFHandleBasketDischarged ||
        msg == EAF_EvMsg::evEAFLiquidAdditionCharged ||
        msg == EAF_EvMsg::evEAFEstimatedEnergyReached ||
        msg == EAF_EvMsg::evEAFPowerOn  ||
        msg == EAF_EvMsg::evEAFPowerOff ||
        msg == EAF_EvMsg::evEAFRoofArrivesInDownPosition ||
        msg == EAF_EvMsg::evEAFFurnaceBreakerOn  ||
        msg == EAF_EvMsg::evEAFFurnaceBreakerOff ||
        msg == EAF_EvMsg::evEAFTempMeasurement ||
        msg == EAF_EvMsg::evEAFCeloxMeasurement ||
        msg == EAF_EvMsg::evEAFTappingStart ||
        msg == EAF_EvMsg::evEAFTappingEnd ||
        msg == EAF_EvMsg::evEAFHeatCancellation||
        msg == EAF_EvMsg::evEAFHeatDeparture
       )
    {

      // Create a new unique product for the phase tracking
      std::string ProductID = evMessage.getProductID();
      std::string extProductID = CEventMessage::getExtendedProductID(ProductID, CTSM_EAF_PhaseChangeAction::ProductIdExtension);
      CEventMessage newEvent = evMessage;
      newEvent.setProductID(extProductID);
      newEvent.setSender("TSM_EAF");
      if (msg == EAF_EvMsg::evEAFHeatAnnouncement)
      {
        CEventMessage ev = newEvent;
        ev.setMessage("EAF_CREATE_PHASETRACKER");
        m_pTsmApplication->doAddProduct(ev);
        m_pTsmApplication->doHandleProductEvent(ev);
      }

      if (m_pTsmApplication->isProductRegistered(newEvent))
      {
        RetValue = true;
        // Forward the significant Event to the phase tracker
        m_pTsmApplication->doHandleProductEvent(newEvent);

        if (msg == EAF_EvMsg::evEAFHeatCancellation || 
            msg == GEN_EvMsg::evGenRemoveTrackedProduct)
        {
          CTSM_EAF_PhaseChangeAction::PreviousStates.erase(ProductID);
          m_pTsmApplication->doRemoveProduct(newEvent);
        }
      }
    }
    else
    {
      std::string Message;
      Message  = "handlePhaseTrackingEvents discard event " + evMessage.getMessage();
      log(Message, 2);
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"Unknown","CTSM_EAF_EventHandler::handlePhaseTrackingEvents","");
  }

  return RetValue;
}

