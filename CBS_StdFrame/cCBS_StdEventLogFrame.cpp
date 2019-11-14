// this is a generated file: do not edit
// use CBSEventLogUtility to generate it out of excel textfile

#include "cCBS_StdEventLogFrame_DestCodes.h"
#include "cCBS_StdEventLogFrame.h"
#include <string>
#include <sstream>
#include <CBS_Tasks/cCBS_Time.h>

#define MAX_MESSAGE_LEN 256 // 255 characters and NULL-Termination!!! DB limit


cCBS_StdEventLogFrame::cCBS_StdEventLogFrame(std::string sProcName, std::string sServiceName, std::string sContextName)
: cCBS_StdEventLog(sProcName,sServiceName,sContextName)
{
}


cCBS_StdEventLogFrame::~cCBS_StdEventLogFrame()
{
}


long cCBS_StdEventLogFrame::EL_EventReceived(const char * Sender, const char * Receiver, const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_test;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10001;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Event received ");
  EventLogMessage.messageText2.append("Event received ");
  EventLogMessage.messageText.append(__toString__( Sender));
  EventLogMessage.messageText2.append(__toString__( Sender));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  EventLogMessage.messageText.append(__toString__( Receiver));
  EventLogMessage.messageText2.append(__toString__( Receiver));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  EventLogMessage.messageText.append(__toString__( Message));
  EventLogMessage.messageText2.append(__toString__( Message));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_EventReceived(sEventLogMessage &EventLogMessage, const char * Sender, const char * Receiver, const char * Message)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_test;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10001;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Event received ");
  EventLogMessage.messageText2.append("Event received ");
  EventLogMessage.messageText.append(__toString__( Sender));
  EventLogMessage.messageText2.append(__toString__( Sender));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  EventLogMessage.messageText.append(__toString__( Receiver));
  EventLogMessage.messageText2.append(__toString__( Receiver));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  EventLogMessage.messageText.append(__toString__( Message));
  EventLogMessage.messageText2.append(__toString__( Message));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_EventRejected(const char * Sender, const char * Receiver, const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10002;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Event rejected ");
  EventLogMessage.messageText2.append("Event rejected ");
  EventLogMessage.messageText.append(__toString__( Sender));
  EventLogMessage.messageText2.append(__toString__( Sender));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  EventLogMessage.messageText.append(__toString__( Receiver));
  EventLogMessage.messageText2.append(__toString__( Receiver));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  EventLogMessage.messageText.append(__toString__( Message));
  EventLogMessage.messageText2.append(__toString__( Message));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_EventRejected(sEventLogMessage &EventLogMessage, const char * Sender, const char * Receiver, const char * Message)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_warning;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10002;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Event rejected ");
  EventLogMessage.messageText2.append("Event rejected ");
  EventLogMessage.messageText.append(__toString__( Sender));
  EventLogMessage.messageText2.append(__toString__( Sender));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  EventLogMessage.messageText.append(__toString__( Receiver));
  EventLogMessage.messageText2.append(__toString__( Receiver));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  EventLogMessage.messageText.append(__toString__( Message));
  EventLogMessage.messageText2.append(__toString__( Message));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_EventHandled(const char * Sender, const char * Receiver, const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_test;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10003;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Event handled ");
  EventLogMessage.messageText2.append("Event handled ");
  EventLogMessage.messageText.append(__toString__( Sender));
  EventLogMessage.messageText2.append(__toString__( Sender));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  EventLogMessage.messageText.append(__toString__( Receiver));
  EventLogMessage.messageText2.append(__toString__( Receiver));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  EventLogMessage.messageText.append(__toString__( Message));
  EventLogMessage.messageText2.append(__toString__( Message));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_EventHandled(sEventLogMessage &EventLogMessage, const char * Sender, const char * Receiver, const char * Message)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_test;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10003;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Event handled ");
  EventLogMessage.messageText2.append("Event handled ");
  EventLogMessage.messageText.append(__toString__( Sender));
  EventLogMessage.messageText2.append(__toString__( Sender));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  EventLogMessage.messageText.append(__toString__( Receiver));
  EventLogMessage.messageText2.append(__toString__( Receiver));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  EventLogMessage.messageText.append(__toString__( Message));
  EventLogMessage.messageText2.append(__toString__( Message));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_EventDispatched(const char * Sender, const char * Receiver, const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_test;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10004;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Event dispatched ");
  EventLogMessage.messageText2.append("Event dispatched ");
  EventLogMessage.messageText.append(__toString__( Sender));
  EventLogMessage.messageText2.append(__toString__( Sender));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  EventLogMessage.messageText.append(__toString__( Receiver));
  EventLogMessage.messageText2.append(__toString__( Receiver));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  EventLogMessage.messageText.append(__toString__( Message));
  EventLogMessage.messageText2.append(__toString__( Message));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_EventDispatched(sEventLogMessage &EventLogMessage, const char * Sender, const char * Receiver, const char * Message)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_test;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10004;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Event dispatched ");
  EventLogMessage.messageText2.append("Event dispatched ");
  EventLogMessage.messageText.append(__toString__( Sender));
  EventLogMessage.messageText2.append(__toString__( Sender));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  EventLogMessage.messageText.append(__toString__( Receiver));
  EventLogMessage.messageText2.append(__toString__( Receiver));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  EventLogMessage.messageText.append(__toString__( Message));
  EventLogMessage.messageText2.append(__toString__( Message));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_EventHandlingError(const char * Sender, const char * Receiver, const char * Message, const char * ProductID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_error;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10005;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Event not handled ");
  EventLogMessage.messageText2.append("Event not handled ");
  EventLogMessage.messageText.append(__toString__( Sender));
  EventLogMessage.messageText2.append(__toString__( Sender));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  EventLogMessage.messageText.append(__toString__( Receiver));
  EventLogMessage.messageText2.append(__toString__( Receiver));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  EventLogMessage.messageText.append(__toString__( Message));
  EventLogMessage.messageText2.append(__toString__( Message));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  EventLogMessage.messageText.append(__toString__( ProductID));
  EventLogMessage.messageText2.append(__toString__( ProductID));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_EventHandlingError(sEventLogMessage &EventLogMessage, const char * Sender, const char * Receiver, const char * Message, const char * ProductID)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_error;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10005;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Event not handled ");
  EventLogMessage.messageText2.append("Event not handled ");
  EventLogMessage.messageText.append(__toString__( Sender));
  EventLogMessage.messageText2.append(__toString__( Sender));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  EventLogMessage.messageText.append(__toString__( Receiver));
  EventLogMessage.messageText2.append(__toString__( Receiver));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  EventLogMessage.messageText.append(__toString__( Message));
  EventLogMessage.messageText2.append(__toString__( Message));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  EventLogMessage.messageText.append(__toString__( ProductID));
  EventLogMessage.messageText2.append(__toString__( ProductID));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ErrorUsingFrameTask(const char * TaskName)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_error;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10006;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Error using frame task ");
  EventLogMessage.messageText2.append("Error using frame task ");
  EventLogMessage.messageText.append(__toString__( TaskName));
  EventLogMessage.messageText2.append(__toString__( TaskName));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ErrorUsingFrameTask(sEventLogMessage &EventLogMessage, const char * TaskName)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_error;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10006;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Error using frame task ");
  EventLogMessage.messageText2.append("Error using frame task ");
  EventLogMessage.messageText.append(__toString__( TaskName));
  EventLogMessage.messageText2.append(__toString__( TaskName));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ErrorConnectingEventChannel()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_error;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10007;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Error connecting to event channel");
  EventLogMessage.messageText2.append("Error connecting to event channel");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ErrorConnectingEventChannel(sEventLogMessage &EventLogMessage)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_error;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10007;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Error connecting to event channel");
  EventLogMessage.messageText2.append("Error connecting to event channel");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ReconnectingEventChannel()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_test;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10008;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Re-connecting to event channel");
  EventLogMessage.messageText2.append("Re-connecting to event channel");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ReconnectingEventChannel(sEventLogMessage &EventLogMessage)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_test;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10008;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Re-connecting to event channel");
  EventLogMessage.messageText2.append("Re-connecting to event channel");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ErrorTaskWorkingState()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_error;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10009;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Error at task working state");
  EventLogMessage.messageText2.append("Error at task working state");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ErrorTaskWorkingState(sEventLogMessage &EventLogMessage)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_error;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10009;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Error at task working state");
  EventLogMessage.messageText2.append("Error at task working state");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ErrorTaskRegistration()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_error;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10010;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Error at task registration");
  EventLogMessage.messageText2.append("Error at task registration");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ErrorTaskRegistration(sEventLogMessage &EventLogMessage)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_error;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10010;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Error at task registration");
  EventLogMessage.messageText2.append("Error at task registration");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ExceptionCaught(const char * Exception, const char * Function, const char * Action)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_error;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10011;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Exception ");
  EventLogMessage.messageText2.append("Exception ");
  EventLogMessage.messageText.append(__toString__( Exception));
  EventLogMessage.messageText2.append(__toString__( Exception));
  EventLogMessage.messageText.append(" caught in ");
  EventLogMessage.messageText2.append(" caught in ");
  EventLogMessage.messageText.append(__toString__( Function));
  EventLogMessage.messageText2.append(__toString__( Function));
  EventLogMessage.messageText.append("  ");
  EventLogMessage.messageText2.append("  ");
  EventLogMessage.messageText.append(__toString__( Action));
  EventLogMessage.messageText2.append(__toString__( Action));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ExceptionCaught(sEventLogMessage &EventLogMessage, const char * Exception, const char * Function, const char * Action)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_error;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10011;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Exception ");
  EventLogMessage.messageText2.append("Exception ");
  EventLogMessage.messageText.append(__toString__( Exception));
  EventLogMessage.messageText2.append(__toString__( Exception));
  EventLogMessage.messageText.append(" caught in ");
  EventLogMessage.messageText2.append(" caught in ");
  EventLogMessage.messageText.append(__toString__( Function));
  EventLogMessage.messageText2.append(__toString__( Function));
  EventLogMessage.messageText.append("  ");
  EventLogMessage.messageText2.append("  ");
  EventLogMessage.messageText.append(__toString__( Action));
  EventLogMessage.messageText2.append(__toString__( Action));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ExceptionThrown(const char * Exception, const char * Function, const char * Action)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10012;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Exception ");
  EventLogMessage.messageText2.append("Exception ");
  EventLogMessage.messageText.append(__toString__( Exception));
  EventLogMessage.messageText2.append(__toString__( Exception));
  EventLogMessage.messageText.append(" thrown in ");
  EventLogMessage.messageText2.append(" thrown in ");
  EventLogMessage.messageText.append(__toString__( Function));
  EventLogMessage.messageText2.append(__toString__( Function));
  EventLogMessage.messageText.append("  ");
  EventLogMessage.messageText2.append("  ");
  EventLogMessage.messageText.append(__toString__( Action));
  EventLogMessage.messageText2.append(__toString__( Action));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ExceptionThrown(sEventLogMessage &EventLogMessage, const char * Exception, const char * Function, const char * Action)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_warning;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10012;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Exception ");
  EventLogMessage.messageText2.append("Exception ");
  EventLogMessage.messageText.append(__toString__( Exception));
  EventLogMessage.messageText2.append(__toString__( Exception));
  EventLogMessage.messageText.append(" thrown in ");
  EventLogMessage.messageText2.append(" thrown in ");
  EventLogMessage.messageText.append(__toString__( Function));
  EventLogMessage.messageText2.append(__toString__( Function));
  EventLogMessage.messageText.append("  ");
  EventLogMessage.messageText2.append("  ");
  EventLogMessage.messageText.append(__toString__( Action));
  EventLogMessage.messageText2.append(__toString__( Action));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBWriteError(const char * Col, const char * Table, const char * Description)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_error;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10013;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Error writing data into ");
  EventLogMessage.messageText2.append("Error writing data into ");
  EventLogMessage.messageText.append(__toString__( Col));
  EventLogMessage.messageText2.append(__toString__( Col));
  EventLogMessage.messageText.append(" of ");
  EventLogMessage.messageText2.append(" of ");
  EventLogMessage.messageText.append(__toString__( Table));
  EventLogMessage.messageText2.append(__toString__( Table));
  EventLogMessage.messageText.append(" - ");
  EventLogMessage.messageText2.append(" - ");
  EventLogMessage.messageText.append(__toString__( Description));
  EventLogMessage.messageText2.append(__toString__( Description));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBWriteError(sEventLogMessage &EventLogMessage, const char * Col, const char * Table, const char * Description)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_error;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10013;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Error writing data into ");
  EventLogMessage.messageText2.append("Error writing data into ");
  EventLogMessage.messageText.append(__toString__( Col));
  EventLogMessage.messageText2.append(__toString__( Col));
  EventLogMessage.messageText.append(" of ");
  EventLogMessage.messageText2.append(" of ");
  EventLogMessage.messageText.append(__toString__( Table));
  EventLogMessage.messageText2.append(__toString__( Table));
  EventLogMessage.messageText.append(" - ");
  EventLogMessage.messageText2.append(" - ");
  EventLogMessage.messageText.append(__toString__( Description));
  EventLogMessage.messageText2.append(__toString__( Description));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBWriteInfo(const char * Col, const char * Table, const char * Description)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_test;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10014;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Writing data into ");
  EventLogMessage.messageText2.append("Writing data into ");
  EventLogMessage.messageText.append(__toString__( Col));
  EventLogMessage.messageText2.append(__toString__( Col));
  EventLogMessage.messageText.append(" of ");
  EventLogMessage.messageText2.append(" of ");
  EventLogMessage.messageText.append(__toString__( Table));
  EventLogMessage.messageText2.append(__toString__( Table));
  EventLogMessage.messageText.append(" - ");
  EventLogMessage.messageText2.append(" - ");
  EventLogMessage.messageText.append(__toString__( Description));
  EventLogMessage.messageText2.append(__toString__( Description));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBWriteInfo(sEventLogMessage &EventLogMessage, const char * Col, const char * Table, const char * Description)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_test;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10014;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Writing data into ");
  EventLogMessage.messageText2.append("Writing data into ");
  EventLogMessage.messageText.append(__toString__( Col));
  EventLogMessage.messageText2.append(__toString__( Col));
  EventLogMessage.messageText.append(" of ");
  EventLogMessage.messageText2.append(" of ");
  EventLogMessage.messageText.append(__toString__( Table));
  EventLogMessage.messageText2.append(__toString__( Table));
  EventLogMessage.messageText.append(" - ");
  EventLogMessage.messageText2.append(" - ");
  EventLogMessage.messageText.append(__toString__( Description));
  EventLogMessage.messageText2.append(__toString__( Description));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBReadError(const char * Col, const char * Table, const char * Description)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_error;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10015;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Error reading data from ");
  EventLogMessage.messageText2.append("Error reading data from ");
  EventLogMessage.messageText.append(__toString__( Col));
  EventLogMessage.messageText2.append(__toString__( Col));
  EventLogMessage.messageText.append(" of ");
  EventLogMessage.messageText2.append(" of ");
  EventLogMessage.messageText.append(__toString__( Table));
  EventLogMessage.messageText2.append(__toString__( Table));
  EventLogMessage.messageText.append(" - ");
  EventLogMessage.messageText2.append(" - ");
  EventLogMessage.messageText.append(__toString__( Description));
  EventLogMessage.messageText2.append(__toString__( Description));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBReadError(sEventLogMessage &EventLogMessage, const char * Col, const char * Table, const char * Description)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_error;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10015;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Error reading data from ");
  EventLogMessage.messageText2.append("Error reading data from ");
  EventLogMessage.messageText.append(__toString__( Col));
  EventLogMessage.messageText2.append(__toString__( Col));
  EventLogMessage.messageText.append(" of ");
  EventLogMessage.messageText2.append(" of ");
  EventLogMessage.messageText.append(__toString__( Table));
  EventLogMessage.messageText2.append(__toString__( Table));
  EventLogMessage.messageText.append(" - ");
  EventLogMessage.messageText2.append(" - ");
  EventLogMessage.messageText.append(__toString__( Description));
  EventLogMessage.messageText2.append(__toString__( Description));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBReadInfo(const char * Col, const char * Table, const char * Description)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_test;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10016;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Reading data from ");
  EventLogMessage.messageText2.append("Reading data from ");
  EventLogMessage.messageText.append(__toString__( Col));
  EventLogMessage.messageText2.append(__toString__( Col));
  EventLogMessage.messageText.append(" of ");
  EventLogMessage.messageText2.append(" of ");
  EventLogMessage.messageText.append(__toString__( Table));
  EventLogMessage.messageText2.append(__toString__( Table));
  EventLogMessage.messageText.append(" - ");
  EventLogMessage.messageText2.append(" - ");
  EventLogMessage.messageText.append(__toString__( Description));
  EventLogMessage.messageText2.append(__toString__( Description));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBReadInfo(sEventLogMessage &EventLogMessage, const char * Col, const char * Table, const char * Description)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_test;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10016;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Reading data from ");
  EventLogMessage.messageText2.append("Reading data from ");
  EventLogMessage.messageText.append(__toString__( Col));
  EventLogMessage.messageText2.append(__toString__( Col));
  EventLogMessage.messageText.append(" of ");
  EventLogMessage.messageText2.append(" of ");
  EventLogMessage.messageText.append(__toString__( Table));
  EventLogMessage.messageText2.append(__toString__( Table));
  EventLogMessage.messageText.append(" - ");
  EventLogMessage.messageText2.append(" - ");
  EventLogMessage.messageText.append(__toString__( Description));
  EventLogMessage.messageText2.append(__toString__( Description));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_LogMessage(const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_test;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10017;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append(__toString__( Message));
  EventLogMessage.messageText2.append(__toString__( Message));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_LogMessage(sEventLogMessage &EventLogMessage, const char * Message)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_test;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10017;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append(__toString__( Message));
  EventLogMessage.messageText2.append(__toString__( Message));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ProcessStarted(const char * ProcessName)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_info;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10018;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Process started : ");
  EventLogMessage.messageText2.append("Process started : ");
  EventLogMessage.messageText.append(__toString__( ProcessName));
  EventLogMessage.messageText2.append(__toString__( ProcessName));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ProcessStarted(sEventLogMessage &EventLogMessage, const char * ProcessName)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_info;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10018;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Process started : ");
  EventLogMessage.messageText2.append("Process started : ");
  EventLogMessage.messageText.append(__toString__( ProcessName));
  EventLogMessage.messageText2.append(__toString__( ProcessName));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ProcessStopped(const char * ProcessName)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10019;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Process stopped : ");
  EventLogMessage.messageText2.append("Process stopped : ");
  EventLogMessage.messageText.append(__toString__( ProcessName));
  EventLogMessage.messageText2.append(__toString__( ProcessName));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ProcessStopped(sEventLogMessage &EventLogMessage, const char * ProcessName)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_warning;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10019;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Process stopped : ");
  EventLogMessage.messageText2.append("Process stopped : ");
  EventLogMessage.messageText.append(__toString__( ProcessName));
  EventLogMessage.messageText2.append(__toString__( ProcessName));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ErrorTaskControl(const char * TaskName, const char * ErrorMessage)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_error;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ALL;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10020;
  EventLogMessage.opAckn = 0x1;  // (1)
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Error on task control ");
  EventLogMessage.messageText2.append("Error on task control ");
  EventLogMessage.messageText.append(__toString__( TaskName));
  EventLogMessage.messageText2.append(__toString__( TaskName));
  EventLogMessage.messageText.append(" : ");
  EventLogMessage.messageText2.append(" : ");
  EventLogMessage.messageText.append(__toString__( ErrorMessage));
  EventLogMessage.messageText2.append(__toString__( ErrorMessage));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ErrorTaskControl(sEventLogMessage &EventLogMessage, const char * TaskName, const char * ErrorMessage)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_error;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ALL;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10020;
  if (0 == EventLogMessage.opAckn) EventLogMessage.opAckn = 0x1;  // (1)
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Error on task control ");
  EventLogMessage.messageText2.append("Error on task control ");
  EventLogMessage.messageText.append(__toString__( TaskName));
  EventLogMessage.messageText2.append(__toString__( TaskName));
  EventLogMessage.messageText.append(" : ");
  EventLogMessage.messageText2.append(" : ");
  EventLogMessage.messageText.append(__toString__( ErrorMessage));
  EventLogMessage.messageText2.append(__toString__( ErrorMessage));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ProcessTerminated(const char * TaskName, const char * ErrorMessage)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_error;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ALL;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10021;
  EventLogMessage.opAckn = 0x1;  // (1)
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Terminating process ");
  EventLogMessage.messageText2.append("Terminating process ");
  EventLogMessage.messageText.append(__toString__( TaskName));
  EventLogMessage.messageText2.append(__toString__( TaskName));
  EventLogMessage.messageText.append(" : ");
  EventLogMessage.messageText2.append(" : ");
  EventLogMessage.messageText.append(__toString__( ErrorMessage));
  EventLogMessage.messageText2.append(__toString__( ErrorMessage));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ProcessTerminated(sEventLogMessage &EventLogMessage, const char * TaskName, const char * ErrorMessage)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_error;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ALL;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10021;
  if (0 == EventLogMessage.opAckn) EventLogMessage.opAckn = 0x1;  // (1)
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Terminating process ");
  EventLogMessage.messageText2.append("Terminating process ");
  EventLogMessage.messageText.append(__toString__( TaskName));
  EventLogMessage.messageText2.append(__toString__( TaskName));
  EventLogMessage.messageText.append(" : ");
  EventLogMessage.messageText2.append(" : ");
  EventLogMessage.messageText.append(__toString__( ErrorMessage));
  EventLogMessage.messageText2.append(__toString__( ErrorMessage));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_MemorySize(int MemorySize)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_error;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ALL;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10022;
  EventLogMessage.opAckn = 0x1;  // (1)
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Memory size exceeds critical value : ");
  EventLogMessage.messageText2.append("Memory size exceeds critical value : ");
  EventLogMessage.messageText.append(__toString__( MemorySize));
  EventLogMessage.messageText2.append(__toString__( MemorySize));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_MemorySize(sEventLogMessage &EventLogMessage, int MemorySize)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_error;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ALL;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10022;
  if (0 == EventLogMessage.opAckn) EventLogMessage.opAckn = 0x1;  // (1)
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Memory size exceeds critical value : ");
  EventLogMessage.messageText2.append("Memory size exceeds critical value : ");
  EventLogMessage.messageText.append(__toString__( MemorySize));
  EventLogMessage.messageText2.append(__toString__( MemorySize));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ProcessStatusError(const char * ProcessName, const char * FreeMessage)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_error;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ALL;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10023;
  EventLogMessage.opAckn = 0x1;  // (1)
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Process does not run: ");
  EventLogMessage.messageText2.append("Process does not run: ");
  EventLogMessage.messageText.append(__toString__( ProcessName));
  EventLogMessage.messageText2.append(__toString__( ProcessName));
  EventLogMessage.messageText.append(" : ");
  EventLogMessage.messageText2.append(" : ");
  EventLogMessage.messageText.append(__toString__( FreeMessage));
  EventLogMessage.messageText2.append(__toString__( FreeMessage));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ProcessStatusError(sEventLogMessage &EventLogMessage, const char * ProcessName, const char * FreeMessage)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_error;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ALL;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10023;
  if (0 == EventLogMessage.opAckn) EventLogMessage.opAckn = 0x1;  // (1)
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Process does not run: ");
  EventLogMessage.messageText2.append("Process does not run: ");
  EventLogMessage.messageText.append(__toString__( ProcessName));
  EventLogMessage.messageText2.append(__toString__( ProcessName));
  EventLogMessage.messageText.append(" : ");
  EventLogMessage.messageText2.append(" : ");
  EventLogMessage.messageText.append(__toString__( FreeMessage));
  EventLogMessage.messageText2.append(__toString__( FreeMessage));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_MutexAccessError(const char * MutexName, int ThreadId, const char * Function)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_error;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10024;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Access mutex failed MutexName: ");
  EventLogMessage.messageText2.append("Access mutex failed MutexName: ");
  EventLogMessage.messageText.append(__toString__( MutexName));
  EventLogMessage.messageText2.append(__toString__( MutexName));
  EventLogMessage.messageText.append(" - ThreadId ");
  EventLogMessage.messageText2.append(" - ThreadId ");
  EventLogMessage.messageText.append(__toString__( ThreadId));
  EventLogMessage.messageText2.append(__toString__( ThreadId));
  EventLogMessage.messageText.append(" in ");
  EventLogMessage.messageText2.append(" in ");
  EventLogMessage.messageText.append(__toString__( Function));
  EventLogMessage.messageText2.append(__toString__( Function));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_MutexAccessError(sEventLogMessage &EventLogMessage, const char * MutexName, int ThreadId, const char * Function)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_error;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10024;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Access mutex failed MutexName: ");
  EventLogMessage.messageText2.append("Access mutex failed MutexName: ");
  EventLogMessage.messageText.append(__toString__( MutexName));
  EventLogMessage.messageText2.append(__toString__( MutexName));
  EventLogMessage.messageText.append(" - ThreadId ");
  EventLogMessage.messageText2.append(" - ThreadId ");
  EventLogMessage.messageText.append(__toString__( ThreadId));
  EventLogMessage.messageText2.append(__toString__( ThreadId));
  EventLogMessage.messageText.append(" in ");
  EventLogMessage.messageText2.append(" in ");
  EventLogMessage.messageText.append(__toString__( Function));
  EventLogMessage.messageText2.append(__toString__( Function));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_MutexFreeError(int ThreadId, const char * Function)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_error;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10025;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Deallocate mutex failed ThreadId ");
  EventLogMessage.messageText2.append("Deallocate mutex failed ThreadId ");
  EventLogMessage.messageText.append(__toString__( ThreadId));
  EventLogMessage.messageText2.append(__toString__( ThreadId));
  EventLogMessage.messageText.append(" in ");
  EventLogMessage.messageText2.append(" in ");
  EventLogMessage.messageText.append(__toString__( Function));
  EventLogMessage.messageText2.append(__toString__( Function));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_MutexFreeError(sEventLogMessage &EventLogMessage, int ThreadId, const char * Function)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_error;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10025;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Deallocate mutex failed ThreadId ");
  EventLogMessage.messageText2.append("Deallocate mutex failed ThreadId ");
  EventLogMessage.messageText.append(__toString__( ThreadId));
  EventLogMessage.messageText2.append(__toString__( ThreadId));
  EventLogMessage.messageText.append(" in ");
  EventLogMessage.messageText2.append(" in ");
  EventLogMessage.messageText.append(__toString__( Function));
  EventLogMessage.messageText2.append(__toString__( Function));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBDeleteError(const char * Table, const char * Description)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_error;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10026;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Error deleting data from ");
  EventLogMessage.messageText2.append("Error deleting data from ");
  EventLogMessage.messageText.append(__toString__( Table));
  EventLogMessage.messageText2.append(__toString__( Table));
  EventLogMessage.messageText.append(" - ");
  EventLogMessage.messageText2.append(" - ");
  EventLogMessage.messageText.append(__toString__( Description));
  EventLogMessage.messageText2.append(__toString__( Description));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBDeleteError(sEventLogMessage &EventLogMessage, const char * Table, const char * Description)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_error;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10026;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Error deleting data from ");
  EventLogMessage.messageText2.append("Error deleting data from ");
  EventLogMessage.messageText.append(__toString__( Table));
  EventLogMessage.messageText2.append(__toString__( Table));
  EventLogMessage.messageText.append(" - ");
  EventLogMessage.messageText2.append(" - ");
  EventLogMessage.messageText.append(__toString__( Description));
  EventLogMessage.messageText2.append(__toString__( Description));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBDeleteInfo(const char * Table, const char * Description)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_test;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10027;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Deleting data from ");
  EventLogMessage.messageText2.append("Deleting data from ");
  EventLogMessage.messageText.append(__toString__( Table));
  EventLogMessage.messageText2.append(__toString__( Table));
  EventLogMessage.messageText.append(" - ");
  EventLogMessage.messageText2.append(" - ");
  EventLogMessage.messageText.append(__toString__( Description));
  EventLogMessage.messageText2.append(__toString__( Description));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBDeleteInfo(sEventLogMessage &EventLogMessage, const char * Table, const char * Description)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_test;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10027;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Deleting data from ");
  EventLogMessage.messageText2.append("Deleting data from ");
  EventLogMessage.messageText.append(__toString__( Table));
  EventLogMessage.messageText2.append(__toString__( Table));
  EventLogMessage.messageText.append(" - ");
  EventLogMessage.messageText2.append(" - ");
  EventLogMessage.messageText.append(__toString__( Description));
  EventLogMessage.messageText2.append(__toString__( Description));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBWriteWarning(const char * Col, const char * Table, const char * Description)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10028;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Warning writing data into ");
  EventLogMessage.messageText2.append("Warning writing data into ");
  EventLogMessage.messageText.append(__toString__( Col));
  EventLogMessage.messageText2.append(__toString__( Col));
  EventLogMessage.messageText.append(" of ");
  EventLogMessage.messageText2.append(" of ");
  EventLogMessage.messageText.append(__toString__( Table));
  EventLogMessage.messageText2.append(__toString__( Table));
  EventLogMessage.messageText.append(" - ");
  EventLogMessage.messageText2.append(" - ");
  EventLogMessage.messageText.append(__toString__( Description));
  EventLogMessage.messageText2.append(__toString__( Description));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBWriteWarning(sEventLogMessage &EventLogMessage, const char * Col, const char * Table, const char * Description)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_warning;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10028;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Warning writing data into ");
  EventLogMessage.messageText2.append("Warning writing data into ");
  EventLogMessage.messageText.append(__toString__( Col));
  EventLogMessage.messageText2.append(__toString__( Col));
  EventLogMessage.messageText.append(" of ");
  EventLogMessage.messageText2.append(" of ");
  EventLogMessage.messageText.append(__toString__( Table));
  EventLogMessage.messageText2.append(__toString__( Table));
  EventLogMessage.messageText.append(" - ");
  EventLogMessage.messageText2.append(" - ");
  EventLogMessage.messageText.append(__toString__( Description));
  EventLogMessage.messageText2.append(__toString__( Description));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBReadWarning(const char * Col, const char * Table, const char * Description)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10029;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Warning reading data from ");
  EventLogMessage.messageText2.append("Warning reading data from ");
  EventLogMessage.messageText.append(__toString__( Col));
  EventLogMessage.messageText2.append(__toString__( Col));
  EventLogMessage.messageText.append(" of ");
  EventLogMessage.messageText2.append(" of ");
  EventLogMessage.messageText.append(__toString__( Table));
  EventLogMessage.messageText2.append(__toString__( Table));
  EventLogMessage.messageText.append(" - ");
  EventLogMessage.messageText2.append(" - ");
  EventLogMessage.messageText.append(__toString__( Description));
  EventLogMessage.messageText2.append(__toString__( Description));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBReadWarning(sEventLogMessage &EventLogMessage, const char * Col, const char * Table, const char * Description)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_warning;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10029;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Warning reading data from ");
  EventLogMessage.messageText2.append("Warning reading data from ");
  EventLogMessage.messageText.append(__toString__( Col));
  EventLogMessage.messageText2.append(__toString__( Col));
  EventLogMessage.messageText.append(" of ");
  EventLogMessage.messageText2.append(" of ");
  EventLogMessage.messageText.append(__toString__( Table));
  EventLogMessage.messageText2.append(__toString__( Table));
  EventLogMessage.messageText.append(" - ");
  EventLogMessage.messageText2.append(" - ");
  EventLogMessage.messageText.append(__toString__( Description));
  EventLogMessage.messageText2.append(__toString__( Description));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBDeleteWarning(const char * Table, const char * Description)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10030;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Warning deleting data from ");
  EventLogMessage.messageText2.append("Warning deleting data from ");
  EventLogMessage.messageText.append(__toString__( Table));
  EventLogMessage.messageText2.append(__toString__( Table));
  EventLogMessage.messageText.append(" - ");
  EventLogMessage.messageText2.append(" - ");
  EventLogMessage.messageText.append(__toString__( Description));
  EventLogMessage.messageText2.append(__toString__( Description));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBDeleteWarning(sEventLogMessage &EventLogMessage, const char * Table, const char * Description)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_warning;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10030;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Warning deleting data from ");
  EventLogMessage.messageText2.append("Warning deleting data from ");
  EventLogMessage.messageText.append(__toString__( Table));
  EventLogMessage.messageText2.append(__toString__( Table));
  EventLogMessage.messageText.append(" - ");
  EventLogMessage.messageText2.append(" - ");
  EventLogMessage.messageText.append(__toString__( Description));
  EventLogMessage.messageText2.append(__toString__( Description));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBConnectionError(const char * Function)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_error;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10031;
  EventLogMessage.opAckn = 0x0;  // (0)
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Error on database connection in ");
  EventLogMessage.messageText2.append("Error on database connection in ");
  EventLogMessage.messageText.append(__toString__( Function));
  EventLogMessage.messageText2.append(__toString__( Function));
  EventLogMessage.messageText.append("  %<Action>");
  EventLogMessage.messageText2.append("  %<Action>");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBConnectionError(sEventLogMessage &EventLogMessage, const char * Function)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_error;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10031;
  if (0 == EventLogMessage.opAckn) EventLogMessage.opAckn = 0x0;  // (0)
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Error on database connection in ");
  EventLogMessage.messageText2.append("Error on database connection in ");
  EventLogMessage.messageText.append(__toString__( Function));
  EventLogMessage.messageText2.append(__toString__( Function));
  EventLogMessage.messageText.append("  %<Action>");
  EventLogMessage.messageText2.append("  %<Action>");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBReconnectInfo(const char * Description)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_info;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10032;
  EventLogMessage.opAckn = 0x0;  // (0)
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Reconnected to database - ");
  EventLogMessage.messageText2.append("Reconnected to database - ");
  EventLogMessage.messageText.append(__toString__( Description));
  EventLogMessage.messageText2.append(__toString__( Description));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBReconnectInfo(sEventLogMessage &EventLogMessage, const char * Description)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_info;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10032;
  if (0 == EventLogMessage.opAckn) EventLogMessage.opAckn = 0x0;  // (0)
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Reconnected to database - ");
  EventLogMessage.messageText2.append("Reconnected to database - ");
  EventLogMessage.messageText.append(__toString__( Description));
  EventLogMessage.messageText2.append(__toString__( Description));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_CORBAReconnectInfo(const char * Description)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_info;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10033;
  EventLogMessage.opAckn = 0x0;  // (0)
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Reconnected to servant - ");
  EventLogMessage.messageText2.append("Reconnected to servant - ");
  EventLogMessage.messageText.append(__toString__( Description));
  EventLogMessage.messageText2.append(__toString__( Description));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_CORBAReconnectInfo(sEventLogMessage &EventLogMessage, const char * Description)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_info;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10033;
  if (0 == EventLogMessage.opAckn) EventLogMessage.opAckn = 0x0;  // (0)
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Reconnected to servant - ");
  EventLogMessage.messageText2.append("Reconnected to servant - ");
  EventLogMessage.messageText.append(__toString__( Description));
  EventLogMessage.messageText2.append(__toString__( Description));
  EventLogMessage.messageText.append(" ");
  EventLogMessage.messageText2.append(" ");
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBNullValueError(const char * Tablename, const char * Columns)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_error;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10034;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("NULL values detected at ");
  EventLogMessage.messageText2.append("NULL values detected at ");
  EventLogMessage.messageText.append(__toString__( Tablename));
  EventLogMessage.messageText2.append(__toString__( Tablename));
  EventLogMessage.messageText.append(" for columns ");
  EventLogMessage.messageText2.append(" for columns ");
  EventLogMessage.messageText.append(__toString__( Columns));
  EventLogMessage.messageText2.append(__toString__( Columns));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_DBNullValueError(sEventLogMessage &EventLogMessage, const char * Tablename, const char * Columns)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_error;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10034;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("NULL values detected at ");
  EventLogMessage.messageText2.append("NULL values detected at ");
  EventLogMessage.messageText.append(__toString__( Tablename));
  EventLogMessage.messageText2.append(__toString__( Tablename));
  EventLogMessage.messageText.append(" for columns ");
  EventLogMessage.messageText2.append(" for columns ");
  EventLogMessage.messageText.append(__toString__( Columns));
  EventLogMessage.messageText2.append(__toString__( Columns));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ProcessRunDown(const char * ProcessName)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 10035;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Process running down : ");
  EventLogMessage.messageText2.append("Process running down : ");
  EventLogMessage.messageText.append(__toString__( ProcessName));
  EventLogMessage.messageText2.append(__toString__( ProcessName));
  return (lRetValue = sendMessage(EventLogMessage));
}


long cCBS_StdEventLogFrame::EL_ProcessRunDown(sEventLogMessage &EventLogMessage, const char * ProcessName)
{
  if (c_e_test == EventLogMessage.severity) EventLogMessage.severity = c_e_warning;
  if (0 == EventLogMessage.destination) EventLogMessage.destination = cCBS_StdEventLogFrame_DestCodes::ComputerRoom;
  if (0 == EventLogMessage.trigger) EventLogMessage.trigger = 1;
  if (0 == EventLogMessage.eventId) EventLogMessage.eventId = 10035;
  EventLogMessage.language = 1;

  // Construct normal message texts
  EventLogMessage.messageText.clear();
  EventLogMessage.messageText.append("Process running down : ");
  EventLogMessage.messageText2.append("Process running down : ");
  EventLogMessage.messageText.append(__toString__( ProcessName));
  EventLogMessage.messageText2.append(__toString__( ProcessName));
  return (lRetValue = sendMessage(EventLogMessage));
}


// Template for convertion to std::wstring
template <class T>
std::wstring cCBS_StdEventLogFrame::__toWString__(const T& arg)
{
  std::wstringstream s;
  s << arg;

  return s.str();
}


// Special implementation for std::string
std::wstring cCBS_StdEventLogFrame::__toWString__(const std::string& arg)
{
  #define MAX_WSTRING_LEN 255
  wchar_t result[MAX_WSTRING_LEN];
  mbtowc(result, arg.c_str(), MAX_WSTRING_LEN);
  result[MAX_WSTRING_LEN-1] = 0;
  return result;
}


// Template for convertion to std::string
template <class T>
std::string cCBS_StdEventLogFrame::__toString__(const T& arg)
{
  std::stringstream s;
  s << arg;

  return s.str();
}


// Special implementation for std::string itself
std::string cCBS_StdEventLogFrame::__toString__(const std::string& arg)
{
  return arg;
}


void cCBS_StdEventLogFrame::replaceNewlines( std::string &text )
{
  std::string::size_type NewlinePosition = 0;
  while( true )
  {
    // Search next newline.
    NewlinePosition = text.find( '\n', NewlinePosition );
    if( NewlinePosition == std::string::npos )
    {
      // No further newline found.
      break;
    }

    // Replace newline by " - ".
    text.replace( NewlinePosition, 1, " - " );
  }
}



