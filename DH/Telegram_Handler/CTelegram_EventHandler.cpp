// Copyright (C) 2011 SMS Siemag AG

#include "cCBS_StdEventLogFrameController.h"
#include "CTelegram_EventHandler.h"


bool CTelegram_EventHandler::dispatchEvent(const std::string& SenderName, const std::string & DestinationName, CEventMessage& Event)
{
  bool RetValue = false;

  std::string ActSenderName      = SenderName;
  if (ActSenderName.empty())
  {
    ActSenderName = Event.getSender();
  }

  std::string ActDestinationName      = DestinationName;
  if (ActDestinationName.empty())
  {
    ActDestinationName = Event.getReceiver();
  }
    
  try
  {
    // try to find entries at inifile
    ActSenderName = CEventMessage::getSenderName(ActSenderName);

    std::vector<std::string> DestinationList = CEventMessage::getDestinationList(ActDestinationName);

    RetValue = Event.dispatch(ActSenderName,DestinationList);
  }
  catch(...)
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CTelegram_Handler::dispatchEvent()",
                                         "");
  }
  return RetValue;
}


