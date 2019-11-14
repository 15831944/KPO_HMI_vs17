// Copyright (C) 2009 SMS Siemag

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdEvent_Task.h"

#include "CSMC_RuntimeController.h"
#include "CEventMessageReady.h"
#include "CARCHIVER_Task.h"

#include "CARCHIVER_EventHandler.h"


CARCHIVER_EventHandler::~CARCHIVER_EventHandler()
{
}

CARCHIVER_EventHandler::CARCHIVER_EventHandler(CARCHIVER_Task *Task)
: m_pARCHIVER_Task(Task)
{
  // set communcation values for task
  setpTask(Task);
}


bool CARCHIVER_EventHandler::handleEvent(const FRIESEvent& Event)
{
  bool RetValue = false;
  try
  {
    // The default implementation for this operation is that chek the receiver, then invoke the hook operation
    // doEventHandlingHook
    CEventMessage Event(Event);

    if (checkReceiver(Event)) // inserted for usage at offline system
    {
      CSMC_RuntimeController Controller("CARCHIVER_EventHandler::handleEvent");

      cCBS_StdEvent_Task::getInstance()->setStateDetails("Actual Event Message", Event.getContent(), 0);

      std::string Message   = Event.getMessage();

      log("",3);
      log("----------------------------------- New Event -----------------------------------",3);
      log( Event,3 );

      // set static value
      m_ActEvent = Event;

      // Invokes on the actual event handling hook.
      // The actual event handling would be performed here, so this pure virtual hook operation
      // must be implement before instantiation
      RetValue = handleEvent(Event);

      if (RetValue)
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_EventHandled(sMessage,Event.getSender().c_str(),Event.getReceiver().c_str(),Message.c_str());

        log("",3);
        log("----------------------------------------------------------------------------",3);

        // send RDY message to eventChannel as reply
        // CEventMessageReady changes sender/receiver and receiver/sender
        CEventMessageReady EventMessageReady(Event);
        EventMessageReady.dispatch(EventMessageReady.getSender(),EventMessageReady.getReceiver());
      }
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"Handling Event",
      "CARCHIVER_EventHandler::handleEvent","HANDLE_EVENT");
  }
  return RetValue;
}

bool CARCHIVER_EventHandler::dispatchEvent(CEventMessage& Event)
{
  bool RetValue = false;
  try
  {
    // already set by CEventHandler class
    /*
    // Sends the event Event to corresponding destinations.
    if ( m_pTask )
    {
      std::string TaskName = m_pTask->getTaskName();
      cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"SenderName",m_SenderName);
    }
    */

    RetValue = CEventHandler::dispatchEvent(m_SenderName,CEventMessage::getDestinationList(m_SenderName),Event);

  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"Handling Event",
      "CDM_EventHandler::handleEvent","HANDLE_EVENT");
  }
  return RetValue;
}
