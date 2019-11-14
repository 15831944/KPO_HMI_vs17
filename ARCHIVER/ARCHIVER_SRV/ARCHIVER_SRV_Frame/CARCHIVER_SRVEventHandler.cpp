
#include "iEventMessages_s.hh"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"

#include "CSMC_EventLogFrameController.h"
#include "CSMC_RuntimeController.h"

#include "CEventMessage.h"

#include "CARCHIVER_SRVEventHandler.h"

//##ModelId=41DD3EFA02CC
CARCHIVER_SRVEventHandler::CARCHIVER_SRVEventHandler(CARCHIVER_Task *Task)
:CARCHIVER_EventHandler(Task)
{
  this->Wrapper.setTaskAndInitDBClasses(Task);
}

//##ModelId=41DD3EFA02CA
CARCHIVER_SRVEventHandler::~CARCHIVER_SRVEventHandler()
{
}

bool CARCHIVER_SRVEventHandler::handleEvent(const FRIESEvent& Event)
{
  bool RetValue = false;
  try
	{
	  // The default implementation for this operation is that chek the receiver, then invoke the hook operation
	  // doEventHandlingHook
	  CEventMessage Event(Event);

    CSMC_RuntimeController Controller("CARCHIVER_SRVEventHandler::handleEvent");

    std::string Message   = Event.getMessage();

    log("", 3);
    log("----------------------------------- New Event -----------------------------------", 3);
    log(Event, 3 );

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

      log("", 3);
      log("----------------------------------------------------------------------------", 3);

      // send RDY message to eventChannel as reply
      // CEventMessageReady changes sender/receiver and receiver/sender
      //CEventMessageReady EventMessageReady(Event);
      //EventMessageReady.dispatch(EventMessageReady.getSender(),EventMessageReady.getReceiver());

    }
	}
	catch(...)
	{
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"Handling Event",
	    "CARCHIVER_SRVEventHandler::handleEvent","HANDLE_EVENT");
	}
	return RetValue;
}


//##ModelId=42EA38FD023B
bool CARCHIVER_SRVEventHandler::handleEvent(CEventMessage& Event)
{
  bool RetValue = false;
  std::string Message = Event.getMessage();

  // some events which can invocate 'service' method
  if (
		  Message == HMD_EvMsg::evHMDHeatDeparture    ||
      Message == HMD_EvMsg::evHMDHeatAnnouncement ||
      Message == LF_EvMsg::evLFHeatAnnouncement   ||
      Message == LF_EvMsg::evLFHeatDeparture      ||
      Message == EAF_EvMsg::evEAFHeatAnnouncement ||
      Message == EAF_EvMsg::evEAFTappingEnd       ||
      Message == "ownStartUp"                        ) 
  {
    log(Event, 3);
    RetValue = Wrapper.doOnServiceEvent(Event);
  }

  return RetValue;
}

