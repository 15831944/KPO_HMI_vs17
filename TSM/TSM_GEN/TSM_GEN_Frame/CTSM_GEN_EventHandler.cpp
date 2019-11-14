// Copyright (C) 2004 SMS Demag AG

#include "iEventMessages_s.hh"
#include "CEventMessage.h"
#include "CEventMessageCtrl.h"
#include "CTsmBaseApplication.h"
#include "CTSM_GEN_HeatTrackingAction.h"

#include "CTSM_GEN_EventHandler.h"

// HANDLE_EVENT: In case the message of the actual event is equal to the value of the message
// defined in the IDL, the corresponding method name is constructed and the method is called.
#if defined (HANDLE_EVENT)
#undef HANDLE_EVENT
#endif
#define HANDLE_EVENT(action) if (GEN_EvMsg::ev##action == evMessage.getMessage()) do##action(evMessage);

CTSM_GEN_EventHandler::CTSM_GEN_EventHandler()
: m_pTsmApplication(0)
{
}

void CTSM_GEN_EventHandler::connectToTsmApplication(CTsmBaseApplication * pTsmApp)
{
  m_pTsmApplication = pTsmApp;
}

bool CTSM_GEN_EventHandler::handleEvent(const FRIESEvent& Event)
{
  CEventMessage evMessage(Event);

  try
  {
    // I will only react on messages for TSM
    if (!checkReceiver(evMessage))
      return false;

    // useful to separate output from TSM and DM parts
    log("+++++++++++++ TSM PART START ++++++++++++++++",3);

    // Store original message for further use in the CTSM_GEN_SendEventAction
    CEventMessageCtrl::setEventMessage(evMessage);
    log(evMessage.getContent(), 3);

    //replace current produc id by plant id for the state mashine
    evMessage.setProductID(evMessage.getPlantID());

    if ( !evMessage.getProductID().empty() && m_pTsmApplication->isProductRegistered(evMessage) )
    {
      if ( m_pTsmApplication->isProductEventRegistered(evMessage) )
      {
        // event is sent in CTSM_GEN_SendEventAction::execute
        // restore of original product id is done there as well
        m_pTsmApplication->handleEvent(evMessage);
      }
      else
      {
        // just forward event to all receiver from ini file
        // set in the list of [TSM_GENTask] -> DestinationName
        // but restore original product id first

        evMessage.setProductID(CEventMessageCtrl::getEventMessage().getProductID());
        evMessage.dispatch(m_SenderName, m_DestinationList);
      }
    }
    else if ( evMessage.isPlantEvent() )
    {
      // restore original product id first
      evMessage.setProductID(CEventMessageCtrl::getEventMessage().getProductID());

      if ( m_pTsmApplication->isPlantEventRegistered(evMessage) )
      {
        m_pTsmApplication->doHandlePlantEvent(evMessage);
      }
      else
      {
        // forward the plant events any way to 
        // [TSM_GENTask] -> DestinationName
        evMessage.dispatch(m_SenderName, m_DestinationList);
      }
    }
    else //just forward it
    {
      // restore original product id first
      evMessage.setProductID(CEventMessageCtrl::getEventMessage().getProductID());

      evMessage.dispatch(m_SenderName, m_DestinationList);
    }

    log("+++++++++++++ TSM PART END ++++++++++++++++",3);
  }
  catch(...)
  {
    std::string Msg("ERORR: Exception in handle event: '");
    Msg += evMessage.getMessage();
    log(Msg,0);
  }
	return true;
}
