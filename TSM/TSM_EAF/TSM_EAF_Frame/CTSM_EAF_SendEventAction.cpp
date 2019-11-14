// Copyright (C) 2004 SMS Demag AG

#include "CDelayedTriggerCall.h"
#include "CTrackingObject.h"
#include "CEventMessageCtrl.h"
#include "cCBS_StdInitBase.h"
#include "CTSM_EAF_SendEventAction.h"
#include "CTSM_EAF_Task.h"

void CTSM_EAF_SendEventAction::execute(CTrackingObject* pObjectForAction)
{
  // Check if pointer is existing
  if (!pObjectForAction)
		return;

  std::string productID = CEventMessage::getOriginalProductID(pObjectForAction->getObjectID());
  
  CEventMessage actualMessage = CEventMessageCtrl::getEventMessage();

  m_eventMessage.setProductID(productID);

  // copy all other entries from the incoming event
  m_eventMessage.setPlantID(actualMessage.getPlantID());
  m_eventMessage.setHeatID(actualMessage.getHeatID());
  m_eventMessage.setTreatID(actualMessage.getTreatID());
  m_eventMessage.setOrderID(actualMessage.getOrderID());
  m_eventMessage.setDataKey(actualMessage.getDataKey());
  m_eventMessage.setPlantEvent(actualMessage.isPlantEvent());

  if (m_delay > 0)
  {
    CDelayedTriggerCall(m_eventMessage, 1000*m_delay);
  }
  else
  {
    // Call event directly using the application
    std::string SenderName = m_eventMessage.getSender();
    std::string TaskName   = CTSM_EAF_Task::getInstance()->getTaskName();

    cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage","SenderName",SenderName);
    cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"SenderName",SenderName);

    // fixing, seems that ->this object will be used further on!
    // in this case Receiver beeing set at dispatch method are still stored at m_eventMessage member

    CEventMessage theMessage(m_eventMessage);

    std::vector<std::string> EventReceiverNames;

    CTSM_Task::getEventReceiverNames(EventReceiverNames,theMessage.getReceiver());

    theMessage.dispatch(SenderName,EventReceiverNames);
  }
}

CTSM_EAF_SendEventAction::CTSM_EAF_SendEventAction(const std::string& eventSender, const std::string& eventReceiver, const std::string& eventMessage, bool isPlantEvent, long delay)
:m_eventMessage(eventSender, eventReceiver, eventMessage, "", "", isPlantEvent)
, m_delay(delay)
{
}

