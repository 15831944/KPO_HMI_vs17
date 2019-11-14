// Copyright (C) 2004 SMS Demag AG

#include "CEventMessage.h"
#include "CDelayedTriggerCall.h"
#include "CTrackingObject.h"
#include "cCBS_StdInitBase.h"

#include "CTSM_Task.h"
#include "CTsmSendEventAction.h"

void CTsmSendEventAction::execute(CTrackingObject* pObjectForAction)
{
  // Check if pointer is existing
  if (!pObjectForAction)
		return;

  // Regular case: Trigger is sent over event channel (with or without delay)
  m_eventMessage.setProductID(pObjectForAction->getObjectID());

  // Call event directly using the application
  std::string SenderName = m_eventMessage.getSender();

  cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage","SenderName",SenderName);


  // fixing, seems that ->this object will be used further on!
  // in this case Receiver beeing set at dispatch method are still stored at m_eventMessage member
  CEventMessage theMessage(m_eventMessage);
  theMessage.setSender(SenderName);

  // get list of possible receivers from ini file NAMECONVERSION
  std::vector<std::string> EventReceiverNames;
  CTSM_Task::getEventReceiverNames(EventReceiverNames,theMessage.getReceiver());

  // if several receivers will be detected by ini file, create one delayed trigger for each receiver !
  if (m_delay > 0)
  {
    std::vector<std::string>::iterator it;

    for ( it = EventReceiverNames.begin() ; it != EventReceiverNames.end() ; ++it )
    {
      theMessage.setReceiver(*it);
      CDelayedTriggerCall(theMessage, 1000*m_delay);
    }
  }
  else
  {
    theMessage.dispatch(SenderName,EventReceiverNames);
  }

}

CTsmSendEventAction::CTsmSendEventAction(const std::string& eventSender, const std::string& eventReceiver, const std::string& eventMessage, bool isPlantEvent, long delay)
:m_eventMessage(eventSender, eventReceiver, eventMessage, "", "", isPlantEvent)
, m_delay(delay)
{
}

