// Copyright (C) 2009 SMS Demag AG

#include "iEventMessages_s.hh"
#include "cCBS_StdInitBase.h"
#include "CEventMessage.h"
#include "CEventMessageCtrl.h"
#include "CTsmBaseApplication.h"
#include "CTSM_HMD_PhaseChangeAction.h"
#include "CTSM_HMD_EventHandler.h"
#include "CTSM_HMD_Task.h"

// HANDLE_EVENT: In case the message of the actual event is equal to the value of the message
// defined in the IDL, the corresponding method name is constructed and the method is called.
#if defined (HANDLE_EVENT)
#undef HANDLE_EVENT
#endif
#define HANDLE_EVENT(action) if (HMD_EvMsg::ev##action == evMessage.getMessage())  do##action(evMessage);

// FORWARD_EVENT: Just forward the event with adjusted sender and receiver name.
#if defined (FORWARD_EVENT)
#undef FORWARD_EVENT
#endif
#define FORWARD_EVENT CEventMessage Fwd(evMessage); Fwd.dispatch(m_SenderName,m_DestinationList);

//##ModelId=45A21E8E0088
CTSM_HMD_EventHandler::CTSM_HMD_EventHandler()
: m_pTsmApplication(0)
{
}

//##ModelId=45A21E8E0092
void CTSM_HMD_EventHandler::connectToTsmApplication(CTsmBaseApplication * pTsmApp)
{
  m_pTsmApplication = pTsmApp;
}

//##ModelId=45A21E8E00BA
bool CTSM_HMD_EventHandler::handleEvent(const FRIESEvent& Event)
{
  CEventMessage evMessage(Event);

  try
  {
    // I will only react on messages for TSM
    if (m_ReceiverName != evMessage.getReceiver())
      return true;

    // useful to separate output fro TSM and DM parts
    log("+++++++++++++ TSM PART START ++++++++++++++++",3);

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

    // Store original message for further use in the CTSM_LF_SendEventAction
    CEventMessageCtrl::setEventMessage(evMessage);

    log(evMessage.getContent(),3);

		//sankar
    //std::string relatedProdID = evMessage.getRelatedProductID();
    //if (!relatedProdID.empty())
    //{
    //  std::string prodID = evMessage.getProductID();
    //  evMessage.setRelatedProductID(prodID);
    //  evMessage.setProductID(relatedProdID);
    //}

    // in case of multiple plants, event sender could be like DM_HMD_1
    // TSM Rule sets does only know DM_HMD
    // change event.SenderName before sending event to TSM kernel
    CTSM_HMD_Task::getInstance()->changeEventTransmitterName(evMessage);

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
        HANDLE_EVENT(HMDHeatAnnouncementOffline);
        HANDLE_EVENT(HMDHeatAnnouncement);
        HANDLE_EVENT(HMDHeatCancellation);
        HANDLE_EVENT(HMDSetUpOfHeat);
        HANDLE_EVENT(HMDResetOfHeat);
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

//##ModelId=46D28CE40182
bool CTSM_HMD_EventHandler::doHMDSetUpOfHeat(CEventMessage & evMessage)
{
  return m_pTsmApplication->doAddProduct(evMessage);
}

//##ModelId=46D28CE40196
bool CTSM_HMD_EventHandler::doHMDResetOfHeat(CEventMessage & evMessage)
{
  if (m_pTsmApplication->isProductRegistered(evMessage))
  {
    m_pTsmApplication->doHandleProductEvent(evMessage);
    return m_pTsmApplication->doRemoveProduct(evMessage);
  }
  return true;
}

//##ModelId=45A21E8E00E2
bool CTSM_HMD_EventHandler::doHMDHeatAnnouncement(CEventMessage & evMessage)
{
  return m_pTsmApplication->doAddProduct(evMessage);
}

//##ModelId=45A21E8E0100
bool CTSM_HMD_EventHandler::doHMDHeatAnnouncementOffline(CEventMessage & evMessage)
{
  return m_pTsmApplication->doAddProduct(evMessage);
}

//##ModelId=45A21E8E0151
bool CTSM_HMD_EventHandler::doHMDHeatCancellation(CEventMessage & evMessage)
{
  if (m_pTsmApplication->isProductRegistered(evMessage))
  {
    m_pTsmApplication->doHandleProductEvent(evMessage);
    return m_pTsmApplication->doRemoveProduct(evMessage);
  }
  return true;
}

bool CTSM_HMD_EventHandler::doGenRemoveTrackedProduct(CEventMessage & evMessage)
{
  return m_pTsmApplication->doRemoveProduct(evMessage);
}

//##ModelId=45A21E8E0074
void CTSM_HMD_EventHandler::handlePhaseTrackingEvents(CEventMessage& evMessage)
{
  try
  {
    bool RetValue = false;
    std::string msg = evMessage.getMessage();

    if (msg == HMD_EvMsg::evHMDHeatAnnouncement ||
        msg == HMD_EvMsg::evHMDHeatCancellation ||
        msg == HMD_EvMsg::evHMDHotMetalSampleTaken ||
        msg == HMD_EvMsg::evHMDTempMeasurement )
    {

      // Create a new unique product for the phase tracking
      std::string ProductID = evMessage.getProductID();
      std::string extProductID = CEventMessage::getExtendedProductID(ProductID, CTSM_HMD_PhaseChangeAction::ProductIdExtension);

      CEventMessage newEvent = evMessage;
      newEvent.setProductID(extProductID);
      newEvent.setSender("TSM_HMD");

      if (msg == HMD_EvMsg::evHMDHeatAnnouncement)
      {
        CEventMessage ev = newEvent;
        ev.setMessage("HMD_CREATE_PHASETRACKER");
        m_pTsmApplication->doAddProduct(ev);
        m_pTsmApplication->doHandleProductEvent(ev);
      }

      if (m_pTsmApplication->isProductRegistered(newEvent))
      {
        // Forward the significant Event to the phase tracker
        m_pTsmApplication->doHandleProductEvent(newEvent);

        if (msg == HMD_EvMsg::evHMDHeatCancellation
         || msg == GEN_EvMsg::evGenRemoveTrackedProduct)
        {
          CTSM_HMD_PhaseChangeAction::PreviousStates.erase(extProductID);
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

