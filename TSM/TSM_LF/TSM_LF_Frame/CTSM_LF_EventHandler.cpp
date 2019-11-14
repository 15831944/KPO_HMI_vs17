// Copyright (C) 2004 SMS Demag AG

#include "iEventMessages_s.hh"
#include "cCBS_StdInitBase.h"
#include "CEventMessage.h"
#include "CEventMessageCtrl.h"
#include "CTsmBaseApplication.h"
#include "CTSM_LF_PhaseChangeAction.h"
#include "CTSM_LF_EventHandler.h"
#include "CTSM_LF_Task.h"

// HANDLE_EVENT: In case the message of the actual event is equal to the value of the message
// defined in the IDL, the corresponding method name is constructed and the method is called.
#if defined (HANDLE_EVENT)
#undef HANDLE_EVENT
#endif
#define HANDLE_EVENT(action) if (LF_EvMsg::ev##action == evMessage.getMessage())  do##action(evMessage);

// FORWARD_EVENT: Just forward the event with adjusted sender and receiver name.
#if defined (FORWARD_EVENT)
#undef FORWARD_EVENT
#endif
#define FORWARD_EVENT CEventMessage Fwd(evMessage); Fwd.dispatch(m_SenderName,m_DestinationList);

CTSM_LF_EventHandler::CTSM_LF_EventHandler()
: m_pTsmApplication(0)
{
}

void CTSM_LF_EventHandler::connectToTsmApplication(CTsmBaseApplication * pTsmApp)
{
  m_pTsmApplication = pTsmApp;
}

bool CTSM_LF_EventHandler::handleEvent(const FRIESEvent& Event)
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

    // in case of multiple plants, event sender could be like DM_LF_1
    // TSM Rule sets does only know DM_LF
    // change event.SenderName before sending event to TSM kernel
    CTSM_LF_Task::getInstance()->changeEventTransmitterName(evMessage);

    std::string RDY = ".RDY";
    // discard ".RDY" events if no rule defined.
    if (evMessage.getMessage().rfind(RDY) != std::string::npos)
    {
      if (!m_pTsmApplication->isProductEventRegistered(evMessage))
      {
        std::string Message;
        Message  = "Discard event : " + evMessage.getMessage();
        log(Message, 3);
        log("+++++++++++++ TSM END ++++++++++++++++",3);
        return true;
      }
    }

    // As long as DH_HMI is used the event evHMIUpdatePlantData 
    // must be sent from tracker to HD_HMI to inform 
    // about plant status, independent of any heat. 
    // The product id in this event is CYCL_LF_1/2
    // Status of this product is not necessary to be known.
    if ( evMessage.getProductID().find("CYCL_") == std::string::npos)
    {
  	  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      std::string State = m_pTsmApplication->getProductStatus(evMessage) + " for product " + evMessage.getProductID();
      pEventLog->EL_TrackingState(sMessage,State.c_str());
    }

    // Store original message for further use in the CTSM_LF_SendEventAction
    CEventMessageCtrl::setEventMessage(evMessage);

    log(evMessage.getContent(), 3);

    if (evMessage.isPlantEvent())
    {
      // Handle plant related event messages
      // General events like ReloadTSM are realized in the base applictaion
      // HANDLE_EVENT(CleanZombies);
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
        HANDLE_EVENT(LFHeatAnnouncementOffline);
        HANDLE_EVENT(LFHeatAnnouncement);
        HANDLE_EVENT(LFHeatCancellation);
        HANDLE_EVENT(LFTsmCreateProduct);
        HANDLE_EVENT(LFResetOfHeat);
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

    return true;
  }
  catch(...)
  {
    return false;
  }
  return true;
}

bool CTSM_LF_EventHandler::doLFTsmCreateProduct(CEventMessage & evMessage)
{
  bool RetValue = m_pTsmApplication->doAddProduct(evMessage);

  // coding is obsolete if respective state transition is designed in TSM rule set
  CEventMessage NewEventMessage(evMessage);
  std::string NewProductID = NewEventMessage.getProductID() + ":HEAT_IS_ANNOUNCED";
  NewEventMessage.setProductID(NewProductID);

  RetValue = RetValue && m_pTsmApplication->doSetProductState(NewEventMessage);

  return RetValue;
}

bool CTSM_LF_EventHandler::doLFResetOfHeat(CEventMessage & evMessage)
{
  if (m_pTsmApplication->isProductRegistered(evMessage))
  {
    m_pTsmApplication->doHandleProductEvent(evMessage);
    return m_pTsmApplication->doRemoveProduct(evMessage);
  }
  return true;
}

bool CTSM_LF_EventHandler::doLFHeatAnnouncement(CEventMessage & evMessage)
{
  return m_pTsmApplication->doAddProduct(evMessage);
}

bool CTSM_LF_EventHandler::doLFHeatAnnouncementOffline(CEventMessage & evMessage)
{
  return m_pTsmApplication->doAddProduct(evMessage);
}

bool CTSM_LF_EventHandler::doLFHeatCancellation(CEventMessage & evMessage)
{
  if (m_pTsmApplication->isProductRegistered(evMessage))
  {
    m_pTsmApplication->doHandleProductEvent(evMessage);
    return m_pTsmApplication->doRemoveProduct(evMessage);
  }
  return true;
}

bool CTSM_LF_EventHandler::doGenRemoveTrackedProduct(CEventMessage & evMessage)
{
  return m_pTsmApplication->doRemoveProduct(evMessage);
}

void CTSM_LF_EventHandler::handlePhaseTrackingEvents(CEventMessage& evMessage)
{
  try
  {
    bool RetValue = false;
    std::string msg = evMessage.getMessage();

    if (msg == LF_EvMsg::evLFHeatAnnouncement ||
        msg == LF_EvMsg::evLFHeatCancellation ||
        msg == LF_EvMsg::evLFHeatDeparture ||
        msg == LF_EvMsg::evLFCleanlinessStirring ||
        msg == LF_EvMsg::evLFInitialHeating ||
        msg == LF_EvMsg::evLFPowerOn ||
        msg == LF_EvMsg::evLFMainHeating || 
        msg == LF_EvMsg::evLFSteelSampleTaken ||
        msg == LF_EvMsg::evLFAlloyingMaterialDischarged ||
        msg == LF_EvMsg::evLFTempMeasurement ||
        msg == LF_EvMsg::evLFCeloxMeasurement ||
        msg == GEN_EvMsg::evGenRemoveTrackedProduct)
    {

      // Create a new unique product for the phase tracking
      std::string ProductID = evMessage.getProductID();
      std::string extProductID = CEventMessage::getExtendedProductID(ProductID, CTSM_LF_PhaseChangeAction::ProductIdExtension);

      CEventMessage newEvent = evMessage;
      newEvent.setProductID(extProductID);
      newEvent.setSender("TSM_LF");

      if (msg == LF_EvMsg::evLFHeatAnnouncement)
      {
        CEventMessage ev = newEvent;
        ev.setMessage("LF_CREATE_PHASETRACKER");
        m_pTsmApplication->doAddProduct(ev);
        m_pTsmApplication->doHandleProductEvent(ev);
      }

      if (m_pTsmApplication->isProductRegistered(newEvent))
      {
        // Forward the significant Event to the phase tracker
        m_pTsmApplication->doHandleProductEvent(newEvent);

        if (msg == LF_EvMsg::evLFHeatCancellation
         || msg == GEN_EvMsg::evGenRemoveTrackedProduct)
        {
          CTSM_LF_PhaseChangeAction::PreviousStates.erase(extProductID);
          m_pTsmApplication->doRemoveProduct(newEvent);
        }
      }
    }
  }
  catch(...)
  {
    log("Exception during handlePhaseTrackingEvents !",3);
  }
}

