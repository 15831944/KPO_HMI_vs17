// this is a generated file: do not edit
// use CBSEventLogCodeGenerator to generate it out of excel textfile
#define MAX_MESSAGE_LEN 256 // 255 characters and NULL-Termination!!! DB limit

#include <string>

#include "CSMC_EventLogFrame.h"
#include <CBS_Tasks/cCBS_Time.h>

CSMC_EventLogFrame::CSMC_EventLogFrame(std::string sProcName, std::string sServiceName, std::string sContextName )
: cCBS_StdEventLogFrame(sProcName,sServiceName,sContextName)
{
}
CSMC_EventLogFrame::~CSMC_EventLogFrame()
{
}

long CSMC_EventLogFrame::EL_Analysis( const char * Elem1,double AnlVal1,const char * Elem2,double AnlVal2,const char * Elem3,double AnlVal3,const char * Elem4,double AnlVal4,const char * Elem5,double AnlVale5)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "";
  EventLogMessage.messageText2 = "";
  EventLogMessage.messageText += Elem1;
  EventLogMessage.messageText += ": ";
  char mstring1[64];
  sprintf( mstring1,"%f",AnlVal1);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem2;
  EventLogMessage.messageText += ": ";
  char mstring3[64];
  sprintf( mstring3,"%f",AnlVal2);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem3;
  EventLogMessage.messageText += ": ";
  char mstring5[64];
  sprintf( mstring5,"%f",AnlVal3);
  EventLogMessage.messageText += mstring5;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem4;
  EventLogMessage.messageText += ": ";
  char mstring7[64];
  sprintf( mstring7,"%f",AnlVal4);
  EventLogMessage.messageText += mstring7;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem5;
  EventLogMessage.messageText += ": ";
  char mstring9[64];
  sprintf( mstring9,"%f",AnlVale5);
  EventLogMessage.messageText += mstring9;
  EventLogMessage.messageText2 += Elem1;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem2;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem3;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring5;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem4;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring7;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem5;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring9;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11001;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_Analysis( sEventLogMessage &EventLogMessage, const char * Elem1,double AnlVal1,const char * Elem2,double AnlVal2,const char * Elem3,double AnlVal3,const char * Elem4,double AnlVal4,const char * Elem5,double AnlVale5)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11001;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "";
  EventLogMessage.messageText2 = "";
  EventLogMessage.messageText += Elem1;
  EventLogMessage.messageText += ": ";
  char mstring1[64];
  sprintf( mstring1,"%f",AnlVal1);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem2;
  EventLogMessage.messageText += ": ";
  char mstring3[64];
  sprintf( mstring3,"%f",AnlVal2);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem3;
  EventLogMessage.messageText += ": ";
  char mstring5[64];
  sprintf( mstring5,"%f",AnlVal3);
  EventLogMessage.messageText += mstring5;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem4;
  EventLogMessage.messageText += ": ";
  char mstring7[64];
  sprintf( mstring7,"%f",AnlVal4);
  EventLogMessage.messageText += mstring7;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem5;
  EventLogMessage.messageText += ": ";
  char mstring9[64];
  sprintf( mstring9,"%f",AnlVale5);
  EventLogMessage.messageText += mstring9;
  EventLogMessage.messageText2 += Elem1;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem2;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem3;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring5;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem4;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring7;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem5;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring9;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_DatabaseConnectionError( const char * Decription,const char * Action)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Connecting to Database failed ";
  EventLogMessage.messageText2 = "Connecting to Database failed ";
  EventLogMessage.messageText += Decription;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Action;
  EventLogMessage.messageText2 += Decription;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Action;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11002;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_DatabaseConnectionError( sEventLogMessage &EventLogMessage, const char * Decription,const char * Action)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11002;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Connecting to Database failed ";
  EventLogMessage.messageText2 = "Connecting to Database failed ";
  EventLogMessage.messageText += Decription;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Action;
  EventLogMessage.messageText2 += Decription;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Action;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_DatabaseReconnect( const char * table,const char * user,const char * pwd,const char * url)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Re-connecting to Database for ";
  EventLogMessage.messageText2 = "Re-connecting to Database for ";
  EventLogMessage.messageText += table;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += user;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += pwd;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += url;
  EventLogMessage.messageText2 += table;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += user;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += pwd;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += url;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11003;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_DatabaseReconnect( sEventLogMessage &EventLogMessage, const char * table,const char * user,const char * pwd,const char * url)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11003;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Re-connecting to Database for ";
  EventLogMessage.messageText2 = "Re-connecting to Database for ";
  EventLogMessage.messageText += table;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += user;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += pwd;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += url;
  EventLogMessage.messageText2 += table;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += user;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += pwd;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += url;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_DataProviderReadError( const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "System can not provide data for ";
  EventLogMessage.messageText2 = "System can not provide data for ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += Message;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11004;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_DataProviderReadError( sEventLogMessage &EventLogMessage, const char * Message)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11004;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "System can not provide data for ";
  EventLogMessage.messageText2 = "System can not provide data for ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += Message;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_DataProviderValidation( const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Invalid data detected ";
  EventLogMessage.messageText2 = "Invalid data detected ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += Message;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11005;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_DataProviderValidation( sEventLogMessage &EventLogMessage, const char * Message)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11005;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Invalid data detected ";
  EventLogMessage.messageText2 = "Invalid data detected ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += Message;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorConnectingProxy( const char * ProxyName,const char * Description)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error connecting to proxy for ";
  EventLogMessage.messageText2 = "Error connecting to proxy for ";
  EventLogMessage.messageText += ProxyName;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Description;
  EventLogMessage.messageText2 += ProxyName;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Description;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11006;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorConnectingProxy( sEventLogMessage &EventLogMessage, const char * ProxyName,const char * Description)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11006;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error connecting to proxy for ";
  EventLogMessage.messageText2 = "Error connecting to proxy for ";
  EventLogMessage.messageText += ProxyName;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Description;
  EventLogMessage.messageText2 += ProxyName;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Description;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorDetectingHeat( const char * HeatID,const char * TreatID,const char * EventMessage)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "System can not detect Heat ";
  EventLogMessage.messageText2 = "System can not detect Heat ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " for Event ";
  EventLogMessage.messageText += EventMessage;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " for Event ";
  EventLogMessage.messageText2 += EventMessage;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11007;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorDetectingHeat( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * EventMessage)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11007;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "System can not detect Heat ";
  EventLogMessage.messageText2 = "System can not detect Heat ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " for Event ";
  EventLogMessage.messageText += EventMessage;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " for Event ";
  EventLogMessage.messageText2 += EventMessage;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorDetectingProxy( const char * ProxyName,const char * Description)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error detecting proxy for ";
  EventLogMessage.messageText2 = "Error detecting proxy for ";
  EventLogMessage.messageText += ProxyName;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Description;
  EventLogMessage.messageText2 += ProxyName;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Description;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11008;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorDetectingProxy( sEventLogMessage &EventLogMessage, const char * ProxyName,const char * Description)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11008;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error detecting proxy for ";
  EventLogMessage.messageText2 = "Error detecting proxy for ";
  EventLogMessage.messageText += ProxyName;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Description;
  EventLogMessage.messageText2 += ProxyName;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Description;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingBatch( const char * Name,const char * Description)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error handling batch ";
  EventLogMessage.messageText2 = "Error handling batch ";
  EventLogMessage.messageText += Name;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Description;
  EventLogMessage.messageText2 += Name;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Description;
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11009;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingBatch( sEventLogMessage &EventLogMessage, const char * Name,const char * Description)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11009;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error handling batch ";
  EventLogMessage.messageText2 = "Error handling batch ";
  EventLogMessage.messageText += Name;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Description;
  EventLogMessage.messageText2 += Name;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Description;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingDateTime()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error handling Date or Time Information";
  EventLogMessage.messageText2 = "Error handling Date or Time Information";
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11010;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingDateTime( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11010;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error handling Date or Time Information";
  EventLogMessage.messageText2 = "Error handling Date or Time Information";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingRecipe( const char * RecipeName,const char * DefaultRecipeName)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "System cannot handle recipe ";
  EventLogMessage.messageText2 = "System cannot handle recipe ";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " using default ";
  EventLogMessage.messageText += DefaultRecipeName;
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " using default ";
  EventLogMessage.messageText2 += DefaultRecipeName;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11011;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingRecipe( sEventLogMessage &EventLogMessage, const char * RecipeName,const char * DefaultRecipeName)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11011;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "System cannot handle recipe ";
  EventLogMessage.messageText2 = "System cannot handle recipe ";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " using default ";
  EventLogMessage.messageText += DefaultRecipeName;
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " using default ";
  EventLogMessage.messageText2 += DefaultRecipeName;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingSample( const char * HeatID,const char * TreatID,const char * PlantID,const char * SampleId)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "System cannot handle sample ";
  EventLogMessage.messageText2 = "System cannot handle sample ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText += " - Sample ";
  EventLogMessage.messageText += SampleId;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.messageText2 += " - Sample ";
  EventLogMessage.messageText2 += SampleId;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11012;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingSample( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID,const char * SampleId)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11012;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "System cannot handle sample ";
  EventLogMessage.messageText2 = "System cannot handle sample ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText += " - Sample ";
  EventLogMessage.messageText += SampleId;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.messageText2 += " - Sample ";
  EventLogMessage.messageText2 += SampleId;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorProcessingData( const char * Function,const char * Params)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "";
  EventLogMessage.messageText2 = "";
  EventLogMessage.messageText += Function;
  EventLogMessage.messageText += " not successful with ";
  EventLogMessage.messageText += Params;
  EventLogMessage.messageText2 += Function;
  EventLogMessage.messageText2 += " not successful with ";
  EventLogMessage.messageText2 += Params;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11013;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorProcessingData( sEventLogMessage &EventLogMessage, const char * Function,const char * Params)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11013;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "";
  EventLogMessage.messageText2 = "";
  EventLogMessage.messageText += Function;
  EventLogMessage.messageText += " not successful with ";
  EventLogMessage.messageText += Params;
  EventLogMessage.messageText2 += Function;
  EventLogMessage.messageText2 += " not successful with ";
  EventLogMessage.messageText2 += Params;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorRegisterProxy( const char * ListName,const char * Description)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error registering proxies for ";
  EventLogMessage.messageText2 = "Error registering proxies for ";
  EventLogMessage.messageText += ListName;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Description;
  EventLogMessage.messageText2 += ListName;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Description;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11014;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorRegisterProxy( sEventLogMessage &EventLogMessage, const char * ListName,const char * Description)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11014;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error registering proxies for ";
  EventLogMessage.messageText2 = "Error registering proxies for ";
  EventLogMessage.messageText += ListName;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Description;
  EventLogMessage.messageText2 += ListName;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Description;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorSearchingData( const char * SearchKey,const char * TableName)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Data for ";
  EventLogMessage.messageText2 = "Data for ";
  EventLogMessage.messageText += SearchKey;
  EventLogMessage.messageText += " not found in ";
  EventLogMessage.messageText += TableName;
  EventLogMessage.messageText2 += SearchKey;
  EventLogMessage.messageText2 += " not found in ";
  EventLogMessage.messageText2 += TableName;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11015;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorSearchingData( sEventLogMessage &EventLogMessage, const char * SearchKey,const char * TableName)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11015;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Data for ";
  EventLogMessage.messageText2 = "Data for ";
  EventLogMessage.messageText += SearchKey;
  EventLogMessage.messageText += " not found in ";
  EventLogMessage.messageText += TableName;
  EventLogMessage.messageText2 += SearchKey;
  EventLogMessage.messageText2 += " not found in ";
  EventLogMessage.messageText2 += TableName;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_EventChannelMessage( const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Event channel ";
  EventLogMessage.messageText2 = "Event channel ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += Message;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11016;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_EventChannelMessage( sEventLogMessage &EventLogMessage, const char * Message)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11016;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Event channel ";
  EventLogMessage.messageText2 = "Event channel ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += Message;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_EventSuccessfullyExecuted( const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Event successfully executed ";
  EventLogMessage.messageText2 = "Event successfully executed ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += Message;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11017;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_EventSuccessfullyExecuted( sEventLogMessage &EventLogMessage, const char * Message)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11017;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Event successfully executed ";
  EventLogMessage.messageText2 = "Event successfully executed ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += Message;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatAnnoucementAdditional( const char * HeatID,const char * TreatID,const char * PlantID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "System can not handle additional heat announcement for heat ";
  EventLogMessage.messageText2 = "System can not handle additional heat announcement for heat ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11018;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatAnnoucementAdditional( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11018;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "System can not handle additional heat announcement for heat ";
  EventLogMessage.messageText2 = "System can not handle additional heat announcement for heat ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += PlantID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatAnnouncementRepeated( const char * HeatID,const char * TreatID,const char * PlantID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "System can not handle repeated heat announcement for heat ";
  EventLogMessage.messageText2 = "System can not handle repeated heat announcement for heat ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11019;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatAnnouncementRepeated( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11019;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "System can not handle repeated heat announcement for heat ";
  EventLogMessage.messageText2 = "System can not handle repeated heat announcement for heat ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += PlantID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatAnnouncementError( const char * HeatID,const char * TreatID,const char * PlantID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "System can not handle heat announcement for heat ";
  EventLogMessage.messageText2 = "System can not handle heat announcement for heat ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11020;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatAnnouncementError( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11020;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "System can not handle heat announcement for heat ";
  EventLogMessage.messageText2 = "System can not handle heat announcement for heat ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += PlantID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InconsistentDataReceived( const char * DataDescription,const char * EventMessage)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Inconsisten Data ";
  EventLogMessage.messageText2 = "Inconsisten Data ";
  EventLogMessage.messageText += DataDescription;
  EventLogMessage.messageText += " found for Event ";
  EventLogMessage.messageText += EventMessage;
  EventLogMessage.messageText2 += DataDescription;
  EventLogMessage.messageText2 += " found for Event ";
  EventLogMessage.messageText2 += EventMessage;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11021;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InconsistentDataReceived( sEventLogMessage &EventLogMessage, const char * DataDescription,const char * EventMessage)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11021;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Inconsisten Data ";
  EventLogMessage.messageText2 = "Inconsisten Data ";
  EventLogMessage.messageText += DataDescription;
  EventLogMessage.messageText += " found for Event ";
  EventLogMessage.messageText += EventMessage;
  EventLogMessage.messageText2 += DataDescription;
  EventLogMessage.messageText2 += " found for Event ";
  EventLogMessage.messageText2 += EventMessage;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_LiquidAdditionCharged( int LiqAddnNo,double Weight)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Liquid Addition no ";
  EventLogMessage.messageText2 = "Liquid Addition no ";
  char mstring0[64];
  sprintf( mstring0,"%d",LiqAddnNo);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " charged with weight ";
  char mstring1[64];
  sprintf( mstring1,"%f",Weight);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " charged with weight ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11022;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_LiquidAdditionCharged( sEventLogMessage &EventLogMessage, int LiqAddnNo,double Weight)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11022;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Liquid Addition no ";
  EventLogMessage.messageText2 = "Liquid Addition no ";
  char mstring0[64];
  sprintf( mstring0,"%d",LiqAddnNo);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " charged with weight ";
  char mstring1[64];
  sprintf( mstring1,"%f",Weight);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " charged with weight ";
  EventLogMessage.messageText2 += mstring1;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_LiquidAdditionNotFound()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "No uncharged Liquid Addition found in the Database";
  EventLogMessage.messageText2 = "No uncharged Liquid Addition found in the Database";
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11023;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_LiquidAdditionNotFound( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11023;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "No uncharged Liquid Addition found in the Database";
  EventLogMessage.messageText2 = "No uncharged Liquid Addition found in the Database";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ModelAvailable( const char * ProcessName)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Model available at process ";
  EventLogMessage.messageText2 = "Model available at process ";
  EventLogMessage.messageText += ProcessName;
  EventLogMessage.messageText2 += ProcessName;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11024;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ModelAvailable( sEventLogMessage &EventLogMessage, const char * ProcessName)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11024;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Model available at process ";
  EventLogMessage.messageText2 = "Model available at process ";
  EventLogMessage.messageText += ProcessName;
  EventLogMessage.messageText2 += ProcessName;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ProcessAvailable( const char * ProcessName,const char * Usage)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Process ";
  EventLogMessage.messageText2 = "Process ";
  EventLogMessage.messageText += ProcessName;
  EventLogMessage.messageText += " available for ";
  EventLogMessage.messageText += Usage;
  EventLogMessage.messageText2 += ProcessName;
  EventLogMessage.messageText2 += " available for ";
  EventLogMessage.messageText2 += Usage;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11025;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ProcessAvailable( sEventLogMessage &EventLogMessage, const char * ProcessName,const char * Usage)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11025;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Process ";
  EventLogMessage.messageText2 = "Process ";
  EventLogMessage.messageText += ProcessName;
  EventLogMessage.messageText += " available for ";
  EventLogMessage.messageText += Usage;
  EventLogMessage.messageText2 += ProcessName;
  EventLogMessage.messageText2 += " available for ";
  EventLogMessage.messageText2 += Usage;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatAssignedToModel( const char * HeatID,const char * TreatID,const char * ModelName)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Heat ";
  EventLogMessage.messageText2 = "Heat ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " assigned to Model ";
  EventLogMessage.messageText += ModelName;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " assigned to Model ";
  EventLogMessage.messageText2 += ModelName;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11026;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatAssignedToModel( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * ModelName)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11026;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Heat ";
  EventLogMessage.messageText2 = "Heat ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " assigned to Model ";
  EventLogMessage.messageText += ModelName;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " assigned to Model ";
  EventLogMessage.messageText2 += ModelName;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatDeassignedFromModel( const char * HeatID,const char * TreatID,const char * ModelName)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Heat ";
  EventLogMessage.messageText2 = "Heat ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " deassigned from Model ";
  EventLogMessage.messageText += ModelName;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " deassigned from Model ";
  EventLogMessage.messageText2 += ModelName;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11027;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatDeassignedFromModel( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * ModelName)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11027;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Heat ";
  EventLogMessage.messageText2 = "Heat ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " deassigned from Model ";
  EventLogMessage.messageText += ModelName;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " deassigned from Model ";
  EventLogMessage.messageText2 += ModelName;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_StateTransition( const char * KindOfTransition,const char * prevState,const char * newState,const char * product,const char * event)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "";
  EventLogMessage.messageText2 = "";
  EventLogMessage.messageText += KindOfTransition;
  EventLogMessage.messageText += " transition from ";
  EventLogMessage.messageText += prevState;
  EventLogMessage.messageText += " to ";
  EventLogMessage.messageText += newState;
  EventLogMessage.messageText += " detected for product ";
  EventLogMessage.messageText += product;
  EventLogMessage.messageText += " on event ";
  EventLogMessage.messageText += event;
  EventLogMessage.messageText2 += KindOfTransition;
  EventLogMessage.messageText2 += " transition from ";
  EventLogMessage.messageText2 += prevState;
  EventLogMessage.messageText2 += " to ";
  EventLogMessage.messageText2 += newState;
  EventLogMessage.messageText2 += " detected for product ";
  EventLogMessage.messageText2 += product;
  EventLogMessage.messageText2 += " on event ";
  EventLogMessage.messageText2 += event;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11028;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_StateTransition( sEventLogMessage &EventLogMessage, const char * KindOfTransition,const char * prevState,const char * newState,const char * product,const char * event)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11028;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "";
  EventLogMessage.messageText2 = "";
  EventLogMessage.messageText += KindOfTransition;
  EventLogMessage.messageText += " transition from ";
  EventLogMessage.messageText += prevState;
  EventLogMessage.messageText += " to ";
  EventLogMessage.messageText += newState;
  EventLogMessage.messageText += " detected for product ";
  EventLogMessage.messageText += product;
  EventLogMessage.messageText += " on event ";
  EventLogMessage.messageText += event;
  EventLogMessage.messageText2 += KindOfTransition;
  EventLogMessage.messageText2 += " transition from ";
  EventLogMessage.messageText2 += prevState;
  EventLogMessage.messageText2 += " to ";
  EventLogMessage.messageText2 += newState;
  EventLogMessage.messageText2 += " detected for product ";
  EventLogMessage.messageText2 += product;
  EventLogMessage.messageText2 += " on event ";
  EventLogMessage.messageText2 += event;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_SteelWeightComp( double HDWeight,double HHWeight)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Steel weight from HEATDATA ";
  EventLogMessage.messageText2 = "Steel weight from HEATDATA ";
  char mstring0[64];
  sprintf( mstring0,"%f",HDWeight);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " - from HOTHEEL ";
  char mstring1[64];
  sprintf( mstring1,"%f",HHWeight);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " - from HOTHEEL ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11029;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_SteelWeightComp( sEventLogMessage &EventLogMessage, double HDWeight,double HHWeight)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11029;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Steel weight from HEATDATA ";
  EventLogMessage.messageText2 = "Steel weight from HEATDATA ";
  char mstring0[64];
  sprintf( mstring0,"%f",HDWeight);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " - from HOTHEEL ";
  char mstring1[64];
  sprintf( mstring1,"%f",HHWeight);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " - from HOTHEEL ";
  EventLogMessage.messageText2 += mstring1;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_UnspecificEventReceived()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Receiving event with unspecific Heat data";
  EventLogMessage.messageText2 = "Receiving event with unspecific Heat data";
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11030;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_UnspecificEventReceived( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11030;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Receiving event with unspecific Heat data";
  EventLogMessage.messageText2 = "Receiving event with unspecific Heat data";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_UseOfProdPracPt( const char * Type,int ProdPrac,const char * ColumnName)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Production Practice ";
  EventLogMessage.messageText2 = "Production Practice ";
  EventLogMessage.messageText += Type;
  EventLogMessage.messageText += " Pointer value ";
  char mstring1[64];
  sprintf( mstring1,"%d",ProdPrac);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " used from ";
  EventLogMessage.messageText += ColumnName;
  EventLogMessage.messageText2 += Type;
  EventLogMessage.messageText2 += " Pointer value ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " used from ";
  EventLogMessage.messageText2 += ColumnName;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11031;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_UseOfProdPracPt( sEventLogMessage &EventLogMessage, const char * Type,int ProdPrac,const char * ColumnName)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11031;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Production Practice ";
  EventLogMessage.messageText2 = "Production Practice ";
  EventLogMessage.messageText += Type;
  EventLogMessage.messageText += " Pointer value ";
  char mstring1[64];
  sprintf( mstring1,"%d",ProdPrac);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " used from ";
  EventLogMessage.messageText += ColumnName;
  EventLogMessage.messageText2 += Type;
  EventLogMessage.messageText2 += " Pointer value ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " used from ";
  EventLogMessage.messageText2 += ColumnName;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ViolationColPrecision( const char * TableName,const char * Col,const char * Old,const char * New)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Column precision violation for ";
  EventLogMessage.messageText2 = "Column precision violation for ";
  EventLogMessage.messageText += TableName;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Col;
  EventLogMessage.messageText += " value ";
  EventLogMessage.messageText += Old;
  EventLogMessage.messageText += " truncated to ";
  EventLogMessage.messageText += New;
  EventLogMessage.messageText2 += TableName;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Col;
  EventLogMessage.messageText2 += " value ";
  EventLogMessage.messageText2 += Old;
  EventLogMessage.messageText2 += " truncated to ";
  EventLogMessage.messageText2 += New;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11032;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ViolationColPrecision( sEventLogMessage &EventLogMessage, const char * TableName,const char * Col,const char * Old,const char * New)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11032;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Column precision violation for ";
  EventLogMessage.messageText2 = "Column precision violation for ";
  EventLogMessage.messageText += TableName;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Col;
  EventLogMessage.messageText += " value ";
  EventLogMessage.messageText += Old;
  EventLogMessage.messageText += " truncated to ";
  EventLogMessage.messageText += New;
  EventLogMessage.messageText2 += TableName;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Col;
  EventLogMessage.messageText2 += " value ";
  EventLogMessage.messageText2 += Old;
  EventLogMessage.messageText2 += " truncated to ";
  EventLogMessage.messageText2 += New;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorTelegramFrequency( const char * TelegramName,int Amount,int Seconds)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "System cannot handle telegram ";
  EventLogMessage.messageText2 = "System cannot handle telegram ";
  EventLogMessage.messageText += TelegramName;
  EventLogMessage.messageText += " reciving ";
  char mstring1[64];
  sprintf( mstring1,"%d",Amount);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " times in ";
  char mstring2[64];
  sprintf( mstring2,"%d",Seconds);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += TelegramName;
  EventLogMessage.messageText2 += " reciving ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " times in ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11033;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorTelegramFrequency( sEventLogMessage &EventLogMessage, const char * TelegramName,int Amount,int Seconds)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11033;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "System cannot handle telegram ";
  EventLogMessage.messageText2 = "System cannot handle telegram ";
  EventLogMessage.messageText += TelegramName;
  EventLogMessage.messageText += " reciving ";
  char mstring1[64];
  sprintf( mstring1,"%d",Amount);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " times in ";
  char mstring2[64];
  sprintf( mstring2,"%d",Seconds);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += TelegramName;
  EventLogMessage.messageText2 += " reciving ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " times in ";
  EventLogMessage.messageText2 += mstring2;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidMaterialCode( const char * MaterialCode)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Invalid material code received: ";
  EventLogMessage.messageText2 = "Invalid material code received: ";
  EventLogMessage.messageText += MaterialCode;
  EventLogMessage.messageText2 += MaterialCode;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11034;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidMaterialCode( sEventLogMessage &EventLogMessage, const char * MaterialCode)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11034;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Invalid material code received: ";
  EventLogMessage.messageText2 = "Invalid material code received: ";
  EventLogMessage.messageText += MaterialCode;
  EventLogMessage.messageText2 += MaterialCode;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_TerminatingCyclicTrigger( const char * Event,const char * HeatID,const char * TreatID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Terminating cyclic trigger ";
  EventLogMessage.messageText2 = "Terminating cyclic trigger ";
  EventLogMessage.messageText += Event;
  EventLogMessage.messageText += " for Heat ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText2 += Event;
  EventLogMessage.messageText2 += " for Heat ";
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11035;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_TerminatingCyclicTrigger( sEventLogMessage &EventLogMessage, const char * Event,const char * HeatID,const char * TreatID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11035;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Terminating cyclic trigger ";
  EventLogMessage.messageText2 = "Terminating cyclic trigger ";
  EventLogMessage.messageText += Event;
  EventLogMessage.messageText += " for Heat ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText2 += Event;
  EventLogMessage.messageText2 += " for Heat ";
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHeatDataConversion( const char * HeatID,const char * TreatID,const char * Plant)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error on heat data conversion for HeatID ";
  EventLogMessage.messageText2 = "Error on heat data conversion for HeatID ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " - TreatID ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " -  Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " - TreatID ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " -  Plant ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11036;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHeatDataConversion( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * Plant)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11036;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error on heat data conversion for HeatID ";
  EventLogMessage.messageText2 = "Error on heat data conversion for HeatID ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " - TreatID ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " -  Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " - TreatID ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " -  Plant ";
  EventLogMessage.messageText2 += Plant;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHeatDataConversion( const char * HeatID,const char * TreatID,const char * Plant,const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error on heat data conversion for HeatID ";
  EventLogMessage.messageText2 = "Error on heat data conversion for HeatID ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " - TreatID ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " -  Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " - TreatID ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " -  Plant ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += Message;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11037;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHeatDataConversion( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * Plant,const char * Message)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11037;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error on heat data conversion for HeatID ";
  EventLogMessage.messageText2 = "Error on heat data conversion for HeatID ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " - TreatID ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " -  Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " - TreatID ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " -  Plant ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += Message;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorPlantDataConversion( const char * Plant,int PlantNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error on plant data conversion for Plant ";
  EventLogMessage.messageText2 = "Error on plant data conversion for Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText += " - PlantNo ";
  char mstring1[64];
  sprintf( mstring1,"%d",PlantNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.messageText2 += " - PlantNo ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11038;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorPlantDataConversion( sEventLogMessage &EventLogMessage, const char * Plant,int PlantNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11038;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error on plant data conversion for Plant ";
  EventLogMessage.messageText2 = "Error on plant data conversion for Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText += " - PlantNo ";
  char mstring1[64];
  sprintf( mstring1,"%d",PlantNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.messageText2 += " - PlantNo ";
  EventLogMessage.messageText2 += mstring1;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorPlantDataConversion( const char * Plant)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error on plant data conversion for Plant ";
  EventLogMessage.messageText2 = "Error on plant data conversion for Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11039;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorPlantDataConversion( sEventLogMessage &EventLogMessage, const char * Plant)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11039;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error on plant data conversion for Plant ";
  EventLogMessage.messageText2 = "Error on plant data conversion for Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText2 += Plant;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorPlantDataConversion( int PlantNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error on plant data conversion for PlantNo ";
  EventLogMessage.messageText2 = "Error on plant data conversion for PlantNo ";
  char mstring0[64];
  sprintf( mstring0,"%d",PlantNo);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11040;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorPlantDataConversion( sEventLogMessage &EventLogMessage, int PlantNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11040;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error on plant data conversion for PlantNo ";
  EventLogMessage.messageText2 = "Error on plant data conversion for PlantNo ";
  char mstring0[64];
  sprintf( mstring0,"%d",PlantNo);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText2 += mstring0;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorFormattedIdHandling( const char * Type,const char * ErrorMessage)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error handling formatted data for ";
  EventLogMessage.messageText2 = "Error handling formatted data for ";
  EventLogMessage.messageText += Type;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += ErrorMessage;
  EventLogMessage.messageText2 += Type;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += ErrorMessage;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11041;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorFormattedIdHandling( sEventLogMessage &EventLogMessage, const char * Type,const char * ErrorMessage)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11041;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error handling formatted data for ";
  EventLogMessage.messageText2 = "Error handling formatted data for ";
  EventLogMessage.messageText += Type;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += ErrorMessage;
  EventLogMessage.messageText2 += Type;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += ErrorMessage;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HandlingTelegramData( const char * Telegram)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Handling telegram data for ";
  EventLogMessage.messageText2 = "Handling telegram data for ";
  EventLogMessage.messageText += Telegram;
  EventLogMessage.messageText2 += Telegram;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11042;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HandlingTelegramData( sEventLogMessage &EventLogMessage, const char * Telegram)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11042;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Handling telegram data for ";
  EventLogMessage.messageText2 = "Handling telegram data for ";
  EventLogMessage.messageText += Telegram;
  EventLogMessage.messageText2 += Telegram;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_NoProdPracPtAssigned( const char * Type,const char * HeatID,const char * TreatID,const char * PlantID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "No production practice pointer type ";
  EventLogMessage.messageText2 = "No production practice pointer type ";
  EventLogMessage.messageText += Type;
  EventLogMessage.messageText += " assigned to heat ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += Type;
  EventLogMessage.messageText2 += " assigned to heat ";
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11043;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_NoProdPracPtAssigned( sEventLogMessage &EventLogMessage, const char * Type,const char * HeatID,const char * TreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11043;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "No production practice pointer type ";
  EventLogMessage.messageText2 = "No production practice pointer type ";
  EventLogMessage.messageText += Type;
  EventLogMessage.messageText += " assigned to heat ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += Type;
  EventLogMessage.messageText2 += " assigned to heat ";
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += PlantID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_LostTelegramInQueue( const char * ProcessName,const char * TelegramName)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Queue is full. ProcessName ";
  EventLogMessage.messageText2 = "Queue is full. ProcessName ";
  EventLogMessage.messageText += ProcessName;
  EventLogMessage.messageText += " TelegramName ";
  EventLogMessage.messageText += TelegramName;
  EventLogMessage.messageText2 += ProcessName;
  EventLogMessage.messageText2 += " TelegramName ";
  EventLogMessage.messageText2 += TelegramName;
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11044;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_LostTelegramInQueue( sEventLogMessage &EventLogMessage, const char * ProcessName,const char * TelegramName)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11044;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Queue is full. ProcessName ";
  EventLogMessage.messageText2 = "Queue is full. ProcessName ";
  EventLogMessage.messageText += ProcessName;
  EventLogMessage.messageText += " TelegramName ";
  EventLogMessage.messageText += TelegramName;
  EventLogMessage.messageText2 += ProcessName;
  EventLogMessage.messageText2 += " TelegramName ";
  EventLogMessage.messageText2 += TelegramName;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_LostConnection( const char * ProcessName)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Lost Connection ProcessName: ";
  EventLogMessage.messageText2 = "Lost Connection ProcessName: ";
  EventLogMessage.messageText += ProcessName;
  EventLogMessage.messageText2 += ProcessName;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11045;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_LostConnection( sEventLogMessage &EventLogMessage, const char * ProcessName)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11045;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Lost Connection ProcessName: ";
  EventLogMessage.messageText2 = "Lost Connection ProcessName: ";
  EventLogMessage.messageText += ProcessName;
  EventLogMessage.messageText2 += ProcessName;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_PredictionCalculationError( const char * CustHeatID,const char * CustTreatID,const char * PlantID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Prediction calculation on announcement for heat ";
  EventLogMessage.messageText2 = "Prediction calculation on announcement for heat ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText += " was not successful";
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.messageText2 += " was not successful";
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11046;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_PredictionCalculationError( sEventLogMessage &EventLogMessage, const char * CustHeatID,const char * CustTreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11046;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Prediction calculation on announcement for heat ";
  EventLogMessage.messageText2 = "Prediction calculation on announcement for heat ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText += " was not successful";
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.messageText2 += " was not successful";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_MaterialCodeUndefined( const char * MatCode)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Material code ";
  EventLogMessage.messageText2 = "Material code ";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText += " not defined in data base";
  EventLogMessage.messageText2 += MatCode;
  EventLogMessage.messageText2 += " not defined in data base";
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11047;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_MaterialCodeUndefined( sEventLogMessage &EventLogMessage, const char * MatCode)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11047;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Material code ";
  EventLogMessage.messageText2 = "Material code ";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText += " not defined in data base";
  EventLogMessage.messageText2 += MatCode;
  EventLogMessage.messageText2 += " not defined in data base";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatNotInProduction( const char * CustHeatID,const char * CustTreatID,const char * PlantID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Receiving data for finished heat ";
  EventLogMessage.messageText2 = "Receiving data for finished heat ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11048;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatNotInProduction( sEventLogMessage &EventLogMessage, const char * CustHeatID,const char * CustTreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11048;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Receiving data for finished heat ";
  EventLogMessage.messageText2 = "Receiving data for finished heat ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += PlantID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatAlreadyInProduction( const char * CustHeatID,const char * CustTreatID,const char * PlantID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Receiving data for heat already in production ";
  EventLogMessage.messageText2 = "Receiving data for heat already in production ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11049;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatAlreadyInProduction( sEventLogMessage &EventLogMessage, const char * CustHeatID,const char * CustTreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11049;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Receiving data for heat already in production ";
  EventLogMessage.messageText2 = "Receiving data for heat already in production ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += PlantID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatStatusChanged( const char * HeatID,const char * TreatID,const char * Plant,const char * NewStatus)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Heat status has been changed HeatID ";
  EventLogMessage.messageText2 = "Heat status has been changed HeatID ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " - TreatID ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " -  Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText += " New status ";
  char mstring3[64];
  sprintf( mstring3,"%s ",NewStatus);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " - TreatID ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " -  Plant ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.messageText2 += " New status ";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11050;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatStatusChanged( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * Plant,const char * NewStatus)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11050;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Heat status has been changed HeatID ";
  EventLogMessage.messageText2 = "Heat status has been changed HeatID ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " - TreatID ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " -  Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText += " New status ";
  char mstring3[64];
  sprintf( mstring3,"%s ",NewStatus);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " - TreatID ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " -  Plant ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.messageText2 += " New status ";
  EventLogMessage.messageText2 += mstring3;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidTemperature( const char * CustHeatID,double Temperature)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Invalid temperature HeatID ";
  EventLogMessage.messageText2 = "Invalid temperature HeatID ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " Temperature ";
  char mstring1[64];
  sprintf( mstring1,"%f",Temperature);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " Temperature ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11051;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidTemperature( sEventLogMessage &EventLogMessage, const char * CustHeatID,double Temperature)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11051;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Invalid temperature HeatID ";
  EventLogMessage.messageText2 = "Invalid temperature HeatID ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " Temperature ";
  char mstring1[64];
  sprintf( mstring1,"%f",Temperature);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " Temperature ";
  EventLogMessage.messageText2 += mstring1;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_LiquidMaterialReport( const char * Ladle,const char * WgtType,double Weight)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Liquid material report received Ladle ";
  EventLogMessage.messageText2 = "Liquid material report received Ladle ";
  EventLogMessage.messageText += Ladle;
  EventLogMessage.messageText += " WgtType ";
  EventLogMessage.messageText += WgtType;
  EventLogMessage.messageText += " Weight ";
  char mstring2[64];
  sprintf( mstring2,"%f",Weight);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += Ladle;
  EventLogMessage.messageText2 += " WgtType ";
  EventLogMessage.messageText2 += WgtType;
  EventLogMessage.messageText2 += " Weight ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11052;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_LiquidMaterialReport( sEventLogMessage &EventLogMessage, const char * Ladle,const char * WgtType,double Weight)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11052;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Liquid material report received Ladle ";
  EventLogMessage.messageText2 = "Liquid material report received Ladle ";
  EventLogMessage.messageText += Ladle;
  EventLogMessage.messageText += " WgtType ";
  EventLogMessage.messageText += WgtType;
  EventLogMessage.messageText += " Weight ";
  char mstring2[64];
  sprintf( mstring2,"%f",Weight);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += Ladle;
  EventLogMessage.messageText2 += " WgtType ";
  EventLogMessage.messageText2 += WgtType;
  EventLogMessage.messageText2 += " Weight ";
  EventLogMessage.messageText2 += mstring2;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_SteelGradeUpdate( const char * CustHeatID,const char * CustTreatID,const char * GradeBefore,const char * GradeAfter,const char * OrderBefore,const char * OrderAfter)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Steel grade update. HeatID ";
  EventLogMessage.messageText2 = "Steel grade update. HeatID ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " TreatID ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " GradeBefore ";
  EventLogMessage.messageText += GradeBefore;
  EventLogMessage.messageText += " GradeAfter ";
  EventLogMessage.messageText += GradeAfter;
  EventLogMessage.messageText += " OrderBefore ";
  EventLogMessage.messageText += OrderBefore;
  EventLogMessage.messageText += " OrderAfter ";
  EventLogMessage.messageText += OrderAfter;
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " TreatID ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " GradeBefore ";
  EventLogMessage.messageText2 += GradeBefore;
  EventLogMessage.messageText2 += " GradeAfter ";
  EventLogMessage.messageText2 += GradeAfter;
  EventLogMessage.messageText2 += " OrderBefore ";
  EventLogMessage.messageText2 += OrderBefore;
  EventLogMessage.messageText2 += " OrderAfter ";
  EventLogMessage.messageText2 += OrderAfter;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11053;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_SteelGradeUpdate( sEventLogMessage &EventLogMessage, const char * CustHeatID,const char * CustTreatID,const char * GradeBefore,const char * GradeAfter,const char * OrderBefore,const char * OrderAfter)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11053;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Steel grade update. HeatID ";
  EventLogMessage.messageText2 = "Steel grade update. HeatID ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " TreatID ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " GradeBefore ";
  EventLogMessage.messageText += GradeBefore;
  EventLogMessage.messageText += " GradeAfter ";
  EventLogMessage.messageText += GradeAfter;
  EventLogMessage.messageText += " OrderBefore ";
  EventLogMessage.messageText += OrderBefore;
  EventLogMessage.messageText += " OrderAfter ";
  EventLogMessage.messageText += OrderAfter;
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " TreatID ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " GradeBefore ";
  EventLogMessage.messageText2 += GradeBefore;
  EventLogMessage.messageText2 += " GradeAfter ";
  EventLogMessage.messageText2 += GradeAfter;
  EventLogMessage.messageText2 += " OrderBefore ";
  EventLogMessage.messageText2 += OrderBefore;
  EventLogMessage.messageText2 += " OrderAfter ";
  EventLogMessage.messageText2 += OrderAfter;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_OrderChanged( const char * CustHeatID,const char * CustTreatID,const char * Plant,const char * OrderAfter)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Production Order Changed. HeatID ";
  EventLogMessage.messageText2 = "Production Order Changed. HeatID ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " TreatID ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText += " new Order ";
  EventLogMessage.messageText += OrderAfter;
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " TreatID ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.messageText2 += " new Order ";
  EventLogMessage.messageText2 += OrderAfter;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11054;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_OrderChanged( sEventLogMessage &EventLogMessage, const char * CustHeatID,const char * CustTreatID,const char * Plant,const char * OrderAfter)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11054;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Production Order Changed. HeatID ";
  EventLogMessage.messageText2 = "Production Order Changed. HeatID ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " TreatID ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText += " new Order ";
  EventLogMessage.messageText += OrderAfter;
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " TreatID ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.messageText2 += " new Order ";
  EventLogMessage.messageText2 += OrderAfter;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_SteelGradeChanged( const char * CustHeatID,const char * CustTreatID,const char * Plant,const char * GradeAfter)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Steel grade changed. HeatID ";
  EventLogMessage.messageText2 = "Steel grade changed. HeatID ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " TreatID ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += "  at plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText += " new Steel Grade ";
  EventLogMessage.messageText += GradeAfter;
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " TreatID ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += "  at plant ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.messageText2 += " new Steel Grade ";
  EventLogMessage.messageText2 += GradeAfter;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11055;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_SteelGradeChanged( sEventLogMessage &EventLogMessage, const char * CustHeatID,const char * CustTreatID,const char * Plant,const char * GradeAfter)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11055;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Steel grade changed. HeatID ";
  EventLogMessage.messageText2 = "Steel grade changed. HeatID ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " TreatID ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += "  at plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText += " new Steel Grade ";
  EventLogMessage.messageText += GradeAfter;
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " TreatID ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += "  at plant ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.messageText2 += " new Steel Grade ";
  EventLogMessage.messageText2 += GradeAfter;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ProdPracChanged( const char * Grade,const char * Type,int Number,const char * CustHeatID,const char * CustTreatID,const char * Plant)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Using new production practice pointer of Steel Grade ";
  EventLogMessage.messageText2 = "Using new production practice pointer of Steel Grade ";
  EventLogMessage.messageText += Grade;
  EventLogMessage.messageText += " Type ";
  EventLogMessage.messageText += Type;
  EventLogMessage.messageText += " Number ";
  char mstring2[64];
  sprintf( mstring2,"%d ",Number);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText += " for HeatID ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " TreatID ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText2 += Grade;
  EventLogMessage.messageText2 += " Type ";
  EventLogMessage.messageText2 += Type;
  EventLogMessage.messageText2 += " Number ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.messageText2 += " for HeatID ";
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " TreatID ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11056;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ProdPracChanged( sEventLogMessage &EventLogMessage, const char * Grade,const char * Type,int Number,const char * CustHeatID,const char * CustTreatID,const char * Plant)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11056;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Using new production practice pointer of Steel Grade ";
  EventLogMessage.messageText2 = "Using new production practice pointer of Steel Grade ";
  EventLogMessage.messageText += Grade;
  EventLogMessage.messageText += " Type ";
  EventLogMessage.messageText += Type;
  EventLogMessage.messageText += " Number ";
  char mstring2[64];
  sprintf( mstring2,"%d ",Number);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText += " for HeatID ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " TreatID ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText2 += Grade;
  EventLogMessage.messageText2 += " Type ";
  EventLogMessage.messageText2 += Type;
  EventLogMessage.messageText2 += " Number ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.messageText2 += " for HeatID ";
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " TreatID ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += Plant;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ProdPracNotDefined( const char * Grade)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Production practice pointer not defined for Steel Grade ";
  EventLogMessage.messageText2 = "Production practice pointer not defined for Steel Grade ";
  EventLogMessage.messageText += Grade;
  EventLogMessage.messageText2 += Grade;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11057;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ProdPracNotDefined( sEventLogMessage &EventLogMessage, const char * Grade)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11057;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Production practice pointer not defined for Steel Grade ";
  EventLogMessage.messageText2 = "Production practice pointer not defined for Steel Grade ";
  EventLogMessage.messageText += Grade;
  EventLogMessage.messageText2 += Grade;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_NoChangeOfProdPrac()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "No change of production practice pointer after blow";
  EventLogMessage.messageText2 = "No change of production practice pointer after blow";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11058;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_NoChangeOfProdPrac( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11058;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "No change of production practice pointer after blow";
  EventLogMessage.messageText2 = "No change of production practice pointer after blow";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHeatStatusChange( const char * HeatID,const char * TreatID,const char * Plant,const char * NewStatus)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error on heat status change for HeatID ";
  EventLogMessage.messageText2 = "Error on heat status change for HeatID ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " - TreatID ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " -  Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText += " - status ";
  char mstring3[64];
  sprintf( mstring3,"%s ",NewStatus);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " - TreatID ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " -  Plant ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.messageText2 += " - status ";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11059;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHeatStatusChange( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * Plant,const char * NewStatus)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11059;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error on heat status change for HeatID ";
  EventLogMessage.messageText2 = "Error on heat status change for HeatID ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " - TreatID ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " -  Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText += " - status ";
  char mstring3[64];
  sprintf( mstring3,"%s ",NewStatus);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " - TreatID ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " -  Plant ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.messageText2 += " - status ";
  EventLogMessage.messageText2 += mstring3;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingAnalysis( const char * HeatID,const char * TreatID,const char * Plant,const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error on analysis handling for HeatID ";
  EventLogMessage.messageText2 = "Error on analysis handling for HeatID ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " - TreatID ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " -  Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " - TreatID ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " -  Plant ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += Message;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11060;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingAnalysis( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * Plant,const char * Message)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11060;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error on analysis handling for HeatID ";
  EventLogMessage.messageText2 = "Error on analysis handling for HeatID ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " - TreatID ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " -  Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " - TreatID ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " -  Plant ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += Message;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HandlingNotUsableAnalysis( const char * HeatID,const char * TreatID,const char * Plant,const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Handling not usable analysis for HeatID ";
  EventLogMessage.messageText2 = "Handling not usable analysis for HeatID ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " - TreatID ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " -  Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " - TreatID ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " -  Plant ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += Message;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11061;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HandlingNotUsableAnalysis( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * Plant,const char * Message)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11061;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Handling not usable analysis for HeatID ";
  EventLogMessage.messageText2 = "Handling not usable analysis for HeatID ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " - TreatID ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " -  Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " - TreatID ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " -  Plant ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += Message;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_UsingDefaultSample( const char * SampleId,const char * DefaultSampleId)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Sample ";
  EventLogMessage.messageText2 = "Sample ";
  EventLogMessage.messageText += SampleId;
  EventLogMessage.messageText += " not usable, using default sample ";
  EventLogMessage.messageText += DefaultSampleId;
  EventLogMessage.messageText2 += SampleId;
  EventLogMessage.messageText2 += " not usable, using default sample ";
  EventLogMessage.messageText2 += DefaultSampleId;
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11062;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_UsingDefaultSample( sEventLogMessage &EventLogMessage, const char * SampleId,const char * DefaultSampleId)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11062;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Sample ";
  EventLogMessage.messageText2 = "Sample ";
  EventLogMessage.messageText += SampleId;
  EventLogMessage.messageText += " not usable, using default sample ";
  EventLogMessage.messageText += DefaultSampleId;
  EventLogMessage.messageText2 += SampleId;
  EventLogMessage.messageText2 += " not usable, using default sample ";
  EventLogMessage.messageText2 += DefaultSampleId;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ModelNotAvailable( const char * ProcessName,const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Model not available at process ";
  EventLogMessage.messageText2 = "Model not available at process ";
  EventLogMessage.messageText += ProcessName;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += ProcessName;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Message;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11063;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ModelNotAvailable( sEventLogMessage &EventLogMessage, const char * ProcessName,const char * Message)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11063;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Model not available at process ";
  EventLogMessage.messageText2 = "Model not available at process ";
  EventLogMessage.messageText += ProcessName;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += ProcessName;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Message;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidTlgData( const char * TlgName,const char * Element,const char * Value)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Invalid data. Telegram: ";
  EventLogMessage.messageText2 = "Invalid data. Telegram: ";
  EventLogMessage.messageText += TlgName;
  EventLogMessage.messageText += " Element: ";
  EventLogMessage.messageText += Element;
  EventLogMessage.messageText += " Value: ";
  EventLogMessage.messageText += Value;
  EventLogMessage.messageText2 += TlgName;
  EventLogMessage.messageText2 += " Element: ";
  EventLogMessage.messageText2 += Element;
  EventLogMessage.messageText2 += " Value: ";
  EventLogMessage.messageText2 += Value;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11064;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidTlgData( sEventLogMessage &EventLogMessage, const char * TlgName,const char * Element,const char * Value)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11064;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Invalid data. Telegram: ";
  EventLogMessage.messageText2 = "Invalid data. Telegram: ";
  EventLogMessage.messageText += TlgName;
  EventLogMessage.messageText += " Element: ";
  EventLogMessage.messageText += Element;
  EventLogMessage.messageText += " Value: ";
  EventLogMessage.messageText += Value;
  EventLogMessage.messageText2 += TlgName;
  EventLogMessage.messageText2 += " Element: ";
  EventLogMessage.messageText2 += Element;
  EventLogMessage.messageText2 += " Value: ";
  EventLogMessage.messageText2 += Value;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidTlgData( const char * TlgName,const char * Element,int Value)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Invalid data. Telegram: ";
  EventLogMessage.messageText2 = "Invalid data. Telegram: ";
  EventLogMessage.messageText += TlgName;
  EventLogMessage.messageText += " Element: ";
  EventLogMessage.messageText += Element;
  EventLogMessage.messageText += " Value: ";
  char mstring2[64];
  sprintf( mstring2,"%d",Value);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += TlgName;
  EventLogMessage.messageText2 += " Element: ";
  EventLogMessage.messageText2 += Element;
  EventLogMessage.messageText2 += " Value: ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11065;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidTlgData( sEventLogMessage &EventLogMessage, const char * TlgName,const char * Element,int Value)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11065;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Invalid data. Telegram: ";
  EventLogMessage.messageText2 = "Invalid data. Telegram: ";
  EventLogMessage.messageText += TlgName;
  EventLogMessage.messageText += " Element: ";
  EventLogMessage.messageText += Element;
  EventLogMessage.messageText += " Value: ";
  char mstring2[64];
  sprintf( mstring2,"%d",Value);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += TlgName;
  EventLogMessage.messageText2 += " Element: ";
  EventLogMessage.messageText2 += Element;
  EventLogMessage.messageText2 += " Value: ";
  EventLogMessage.messageText2 += mstring2;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidTlgData( const char * TlgName,const char * Element,int Value,int Min,int Max)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Invalid data. Telegram: ";
  EventLogMessage.messageText2 = "Invalid data. Telegram: ";
  EventLogMessage.messageText += TlgName;
  EventLogMessage.messageText += " Element: ";
  EventLogMessage.messageText += Element;
  EventLogMessage.messageText += " Value: ";
  char mstring2[64];
  sprintf( mstring2,"%d",Value);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText += " out of Range ";
  char mstring3[64];
  sprintf( mstring3,"%d",Min);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText += " … ";
  char mstring4[64];
  sprintf( mstring4,"%d",Max);
  EventLogMessage.messageText += mstring4;
  EventLogMessage.messageText2 += TlgName;
  EventLogMessage.messageText2 += " Element: ";
  EventLogMessage.messageText2 += Element;
  EventLogMessage.messageText2 += " Value: ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.messageText2 += " out of Range ";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.messageText2 += " … ";
  EventLogMessage.messageText2 += mstring4;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11066;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidTlgData( sEventLogMessage &EventLogMessage, const char * TlgName,const char * Element,int Value,int Min,int Max)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11066;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Invalid data. Telegram: ";
  EventLogMessage.messageText2 = "Invalid data. Telegram: ";
  EventLogMessage.messageText += TlgName;
  EventLogMessage.messageText += " Element: ";
  EventLogMessage.messageText += Element;
  EventLogMessage.messageText += " Value: ";
  char mstring2[64];
  sprintf( mstring2,"%d",Value);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText += " out of Range ";
  char mstring3[64];
  sprintf( mstring3,"%d",Min);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText += " … ";
  char mstring4[64];
  sprintf( mstring4,"%d",Max);
  EventLogMessage.messageText += mstring4;
  EventLogMessage.messageText2 += TlgName;
  EventLogMessage.messageText2 += " Element: ";
  EventLogMessage.messageText2 += Element;
  EventLogMessage.messageText2 += " Value: ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.messageText2 += " out of Range ";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.messageText2 += " … ";
  EventLogMessage.messageText2 += mstring4;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidTlgData( const char * TlgName,const char * Element,double Value,double Min,double Max)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Invalid data. Telegram: ";
  EventLogMessage.messageText2 = "Invalid data. Telegram: ";
  EventLogMessage.messageText += TlgName;
  EventLogMessage.messageText += " Element: ";
  EventLogMessage.messageText += Element;
  EventLogMessage.messageText += " Value: ";
  char mstring2[64];
  sprintf( mstring2,"%f",Value);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText += " out of Range ";
  char mstring3[64];
  sprintf( mstring3,"%f",Min);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText += " … ";
  char mstring4[64];
  sprintf( mstring4,"%f",Max);
  EventLogMessage.messageText += mstring4;
  EventLogMessage.messageText2 += TlgName;
  EventLogMessage.messageText2 += " Element: ";
  EventLogMessage.messageText2 += Element;
  EventLogMessage.messageText2 += " Value: ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.messageText2 += " out of Range ";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.messageText2 += " … ";
  EventLogMessage.messageText2 += mstring4;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11067;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidTlgData( sEventLogMessage &EventLogMessage, const char * TlgName,const char * Element,double Value,double Min,double Max)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11067;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Invalid data. Telegram: ";
  EventLogMessage.messageText2 = "Invalid data. Telegram: ";
  EventLogMessage.messageText += TlgName;
  EventLogMessage.messageText += " Element: ";
  EventLogMessage.messageText += Element;
  EventLogMessage.messageText += " Value: ";
  char mstring2[64];
  sprintf( mstring2,"%f",Value);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText += " out of Range ";
  char mstring3[64];
  sprintf( mstring3,"%f",Min);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText += " … ";
  char mstring4[64];
  sprintf( mstring4,"%f",Max);
  EventLogMessage.messageText += mstring4;
  EventLogMessage.messageText2 += TlgName;
  EventLogMessage.messageText2 += " Element: ";
  EventLogMessage.messageText2 += Element;
  EventLogMessage.messageText2 += " Value: ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.messageText2 += " out of Range ";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.messageText2 += " … ";
  EventLogMessage.messageText2 += mstring4;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorReceivingModelResult( const char * HeatID,const char * TreatID,const char * PlantID,const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error receiving Model Results for ";
  EventLogMessage.messageText2 = "Error receiving Model Results for ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText += "  - ";
  char mstring3[64];
  sprintf( mstring3,"%",Message);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.messageText2 += "  - ";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11068;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorReceivingModelResult( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID,const char * Message)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11068;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error receiving Model Results for ";
  EventLogMessage.messageText2 = "Error receiving Model Results for ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText += "  - ";
  char mstring3[64];
  sprintf( mstring3,"%",Message);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.messageText2 += "  - ";
  EventLogMessage.messageText2 += mstring3;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingTelegram( const char * TlgName,const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error handling telegram ";
  EventLogMessage.messageText2 = "Error handling telegram ";
  EventLogMessage.messageText += TlgName;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += TlgName;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += Message;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11069;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingTelegram( sEventLogMessage &EventLogMessage, const char * TlgName,const char * Message)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11069;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error handling telegram ";
  EventLogMessage.messageText2 = "Error handling telegram ";
  EventLogMessage.messageText += TlgName;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += TlgName;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += Message;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_MaterialAvailabilityChanged( int Available,const char * MatCode,const char * Source)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Material availability changed to ";
  EventLogMessage.messageText2 = "Material availability changed to ";
  char mstring0[64];
  sprintf( mstring0,"%d",Available);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " for Material ";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText += " at ";
  EventLogMessage.messageText += Source;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " for Material ";
  EventLogMessage.messageText2 += MatCode;
  EventLogMessage.messageText2 += " at ";
  EventLogMessage.messageText2 += Source;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11070;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_MaterialAvailabilityChanged( sEventLogMessage &EventLogMessage, int Available,const char * MatCode,const char * Source)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11070;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Material availability changed to ";
  EventLogMessage.messageText2 = "Material availability changed to ";
  char mstring0[64];
  sprintf( mstring0,"%d",Available);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " for Material ";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText += " at ";
  EventLogMessage.messageText += Source;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " for Material ";
  EventLogMessage.messageText2 += MatCode;
  EventLogMessage.messageText2 += " at ";
  EventLogMessage.messageText2 += Source;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_MaterialAvailabilityUnused()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Material availability data from Level 1 not used";
  EventLogMessage.messageText2 = "Material availability data from Level 1 not used";
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11071;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_MaterialAvailabilityUnused( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11071;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Material availability data from Level 1 not used";
  EventLogMessage.messageText2 = "Material availability data from Level 1 not used";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorPointerHandling( const char * Function,const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error on internal pointer handling ";
  EventLogMessage.messageText2 = "Error on internal pointer handling ";
  EventLogMessage.messageText += Function;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += Function;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Message;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11072;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorPointerHandling( sEventLogMessage &EventLogMessage, const char * Function,const char * Message)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11072;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error on internal pointer handling ";
  EventLogMessage.messageText2 = "Error on internal pointer handling ";
  EventLogMessage.messageText += Function;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += Function;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Message;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorMessage( const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "General Error ";
  EventLogMessage.messageText2 = "General Error ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += Message;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11073;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorMessage( sEventLogMessage &EventLogMessage, const char * Message)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11073;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "General Error ";
  EventLogMessage.messageText2 = "General Error ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += Message;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_TelegramHandled( const char * Telegram,const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Telegram handled ";
  EventLogMessage.messageText2 = "Telegram handled ";
  EventLogMessage.messageText += Telegram;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += Telegram;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Message;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11074;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_TelegramHandled( sEventLogMessage &EventLogMessage, const char * Telegram,const char * Message)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11074;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Telegram handled ";
  EventLogMessage.messageText2 = "Telegram handled ";
  EventLogMessage.messageText += Telegram;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += Telegram;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Message;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatDetected( const char * HeatID,const char * TreatID,const char * EventMessage)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Heat detected ";
  EventLogMessage.messageText2 = "Heat detected ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " for Event ";
  EventLogMessage.messageText += EventMessage;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " for Event ";
  EventLogMessage.messageText2 += EventMessage;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11075;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatDetected( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * EventMessage)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11075;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Heat detected ";
  EventLogMessage.messageText2 = "Heat detected ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " for Event ";
  EventLogMessage.messageText += EventMessage;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " for Event ";
  EventLogMessage.messageText2 += EventMessage;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorMultipleHeatAssignment()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Heat assigned to multiple models";
  EventLogMessage.messageText2 = "Heat assigned to multiple models";
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11076;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorMultipleHeatAssignment( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11076;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Heat assigned to multiple models";
  EventLogMessage.messageText2 = "Heat assigned to multiple models";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_MeasurementRejected( const char * MeasType,double MeasValue)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Measurement rejected ";
  EventLogMessage.messageText2 = "Measurement rejected ";
  EventLogMessage.messageText += MeasType;
  EventLogMessage.messageText += " with value ";
  char mstring1[64];
  sprintf( mstring1,"%f",MeasValue);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += MeasType;
  EventLogMessage.messageText2 += " with value ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.opAckn = 1;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 11077;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_MeasurementRejected( sEventLogMessage &EventLogMessage, const char * MeasType,double MeasValue)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11077;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  if (EventLogMessage.opAckn == 0) EventLogMessage.opAckn = 1;
  EventLogMessage.messageText = "Measurement rejected ";
  EventLogMessage.messageText2 = "Measurement rejected ";
  EventLogMessage.messageText += MeasType;
  EventLogMessage.messageText += " with value ";
  char mstring1[64];
  sprintf( mstring1,"%f",MeasValue);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += MeasType;
  EventLogMessage.messageText2 += " with value ";
  EventLogMessage.messageText2 += mstring1;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_LadleAssignmentPlanningData( const char * LadleType,int LadleNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Ladle assignment by Planning Data using ";
  EventLogMessage.messageText2 = "Ladle assignment by Planning Data using ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11078;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_LadleAssignmentPlanningData( sEventLogMessage &EventLogMessage, const char * LadleType,int LadleNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11078;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Ladle assignment by Planning Data using ";
  EventLogMessage.messageText2 = "Ladle assignment by Planning Data using ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += mstring1;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_LadleAssignmentPretreatmentData( const char * LadleType,int LadleNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Ladle assignment by Pretreatment Data using ";
  EventLogMessage.messageText2 = "Ladle assignment by Pretreatment Data using ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11079;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_LadleAssignmentPretreatmentData( sEventLogMessage &EventLogMessage, const char * LadleType,int LadleNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11079;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Ladle assignment by Pretreatment Data using ";
  EventLogMessage.messageText2 = "Ladle assignment by Pretreatment Data using ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += mstring1;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorSteelGradePractice( const char * PracticeName,const char * SteelGradeCode)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "No practice ";
  EventLogMessage.messageText2 = "No practice ";
  EventLogMessage.messageText += PracticeName;
  EventLogMessage.messageText += " defined for steel grade ";
  EventLogMessage.messageText += SteelGradeCode;
  EventLogMessage.messageText2 += PracticeName;
  EventLogMessage.messageText2 += " defined for steel grade ";
  EventLogMessage.messageText2 += SteelGradeCode;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.opAckn = 1;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 11080;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorSteelGradePractice( sEventLogMessage &EventLogMessage, const char * PracticeName,const char * SteelGradeCode)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11080;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  if (EventLogMessage.opAckn == 0) EventLogMessage.opAckn = 1;
  EventLogMessage.messageText = "No practice ";
  EventLogMessage.messageText2 = "No practice ";
  EventLogMessage.messageText += PracticeName;
  EventLogMessage.messageText += " defined for steel grade ";
  EventLogMessage.messageText += SteelGradeCode;
  EventLogMessage.messageText2 += PracticeName;
  EventLogMessage.messageText2 += " defined for steel grade ";
  EventLogMessage.messageText2 += SteelGradeCode;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ResettingData( const char * Data,const char * HeatID,const char * TreatID,const char * Plant)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Resetting ";
  EventLogMessage.messageText2 = "Resetting ";
  EventLogMessage.messageText += Data;
  EventLogMessage.messageText += " for HeatID ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " - TreatID ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " -  Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText2 += Data;
  EventLogMessage.messageText2 += " for HeatID ";
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " - TreatID ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " -  Plant ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11081;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ResettingData( sEventLogMessage &EventLogMessage, const char * Data,const char * HeatID,const char * TreatID,const char * Plant)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11081;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Resetting ";
  EventLogMessage.messageText2 = "Resetting ";
  EventLogMessage.messageText += Data;
  EventLogMessage.messageText += " for HeatID ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " - TreatID ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " -  Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText2 += Data;
  EventLogMessage.messageText2 += " for HeatID ";
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " - TreatID ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " -  Plant ";
  EventLogMessage.messageText2 += Plant;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_RejectingRecipe( const char * RecipeName,const char * HeatID,const char * TreatID,const char * Plant)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Rejecting recipe ";
  EventLogMessage.messageText2 = "Rejecting recipe ";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " for HeatID ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " - TreatID ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " -  Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " for HeatID ";
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " - TreatID ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " -  Plant ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11082;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_RejectingRecipe( sEventLogMessage &EventLogMessage, const char * RecipeName,const char * HeatID,const char * TreatID,const char * Plant)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11082;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Rejecting recipe ";
  EventLogMessage.messageText2 = "Rejecting recipe ";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " for HeatID ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " - TreatID ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " -  Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " for HeatID ";
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " - TreatID ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " -  Plant ";
  EventLogMessage.messageText2 += Plant;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_TrackingState( const char * ActState)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Actual tracking state is ";
  EventLogMessage.messageText2 = "Actual tracking state is ";
  EventLogMessage.messageText += ActState;
  EventLogMessage.messageText2 += ActState;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11083;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_TrackingState( sEventLogMessage &EventLogMessage, const char * ActState)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11083;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Actual tracking state is ";
  EventLogMessage.messageText2 = "Actual tracking state is ";
  EventLogMessage.messageText += ActState;
  EventLogMessage.messageText2 += ActState;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorStateTransition( const char * StatusName,const char * ActStatus,const char * NewStatus)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error on state transition for status ";
  EventLogMessage.messageText2 = "Error on state transition for status ";
  EventLogMessage.messageText += StatusName;
  EventLogMessage.messageText += " Status ";
  EventLogMessage.messageText += ActStatus;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += NewStatus;
  EventLogMessage.messageText2 += StatusName;
  EventLogMessage.messageText2 += " Status ";
  EventLogMessage.messageText2 += ActStatus;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += NewStatus;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11084;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorStateTransition( sEventLogMessage &EventLogMessage, const char * StatusName,const char * ActStatus,const char * NewStatus)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11084;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error on state transition for status ";
  EventLogMessage.messageText2 = "Error on state transition for status ";
  EventLogMessage.messageText += StatusName;
  EventLogMessage.messageText += " Status ";
  EventLogMessage.messageText += ActStatus;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += NewStatus;
  EventLogMessage.messageText2 += StatusName;
  EventLogMessage.messageText2 += " Status ";
  EventLogMessage.messageText2 += ActStatus;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += NewStatus;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatScheduleUpdate( const char * CustHeatID,const char * CustTreatID,const char * OrderID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Heat schedule update for heat ";
  EventLogMessage.messageText2 = "Heat schedule update for heat ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " at order ";
  EventLogMessage.messageText += OrderID;
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " at order ";
  EventLogMessage.messageText2 += OrderID;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.opAckn = 1;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11085;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatScheduleUpdate( sEventLogMessage &EventLogMessage, const char * CustHeatID,const char * CustTreatID,const char * OrderID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11085;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  if (EventLogMessage.opAckn == 0) EventLogMessage.opAckn = 1;
  EventLogMessage.messageText = "Heat schedule update for heat ";
  EventLogMessage.messageText2 = "Heat schedule update for heat ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " at order ";
  EventLogMessage.messageText += OrderID;
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " at order ";
  EventLogMessage.messageText2 += OrderID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorOrderData( const char * OrderID,const char * CustHeatID,const char * CustTreatID,const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error on handling order data for ";
  EventLogMessage.messageText2 = "Error on handling order data for ";
  EventLogMessage.messageText += OrderID;
  EventLogMessage.messageText += " with ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += "  - ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += OrderID;
  EventLogMessage.messageText2 += " with ";
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += "  - ";
  EventLogMessage.messageText2 += Message;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11086;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorOrderData( sEventLogMessage &EventLogMessage, const char * OrderID,const char * CustHeatID,const char * CustTreatID,const char * Message)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11086;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error on handling order data for ";
  EventLogMessage.messageText2 = "Error on handling order data for ";
  EventLogMessage.messageText += OrderID;
  EventLogMessage.messageText += " with ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += "  - ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += OrderID;
  EventLogMessage.messageText2 += " with ";
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += "  - ";
  EventLogMessage.messageText2 += Message;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHeatAlreadyInProduction( const char * CustHeatID,const char * CustTreatID,const char * PlantID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Receiving data for heat already in production ";
  EventLogMessage.messageText2 = "Receiving data for heat already in production ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11087;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHeatAlreadyInProduction( sEventLogMessage &EventLogMessage, const char * CustHeatID,const char * CustTreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11087;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Receiving data for heat already in production ";
  EventLogMessage.messageText2 = "Receiving data for heat already in production ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += PlantID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_OrderData( const char * OrderID,const char * CustHeatID,const char * CustTreatID,const char * Plant)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Production Order handled for ";
  EventLogMessage.messageText2 = "Production Order handled for ";
  EventLogMessage.messageText += OrderID;
  EventLogMessage.messageText += " with HeatID ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " TreatID ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText2 += OrderID;
  EventLogMessage.messageText2 += " with HeatID ";
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " TreatID ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11088;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_OrderData( sEventLogMessage &EventLogMessage, const char * OrderID,const char * CustHeatID,const char * CustTreatID,const char * Plant)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11088;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Production Order handled for ";
  EventLogMessage.messageText2 = "Production Order handled for ";
  EventLogMessage.messageText += OrderID;
  EventLogMessage.messageText += " with HeatID ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " TreatID ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText2 += OrderID;
  EventLogMessage.messageText2 += " with HeatID ";
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " TreatID ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += Plant;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatScheduleUpdate( const char * CustHeatID,const char * CustTreatID,const char * OrderID,const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Heat schedule update for heat ";
  EventLogMessage.messageText2 = "Heat schedule update for heat ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " at order ";
  EventLogMessage.messageText += OrderID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " at order ";
  EventLogMessage.messageText2 += OrderID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Message;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.opAckn = 1;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11089;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatScheduleUpdate( sEventLogMessage &EventLogMessage, const char * CustHeatID,const char * CustTreatID,const char * OrderID,const char * Message)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11089;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  if (EventLogMessage.opAckn == 0) EventLogMessage.opAckn = 1;
  EventLogMessage.messageText = "Heat schedule update for heat ";
  EventLogMessage.messageText2 = "Heat schedule update for heat ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " at order ";
  EventLogMessage.messageText += OrderID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " at order ";
  EventLogMessage.messageText2 += OrderID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Message;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorUnknownHeatStart( const char * HeatID,const char * TreatmentPos)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error on heat start with unknown heat ";
  EventLogMessage.messageText2 = "Error on heat start with unknown heat ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " at ";
  EventLogMessage.messageText += TreatmentPos;
  EventLogMessage.messageText += " - announce heat on level 2 and re-start heat on level 1";
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " at ";
  EventLogMessage.messageText2 += TreatmentPos;
  EventLogMessage.messageText2 += " - announce heat on level 2 and re-start heat on level 1";
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.opAckn = 1;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11090;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorUnknownHeatStart( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatmentPos)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11090;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  if (EventLogMessage.opAckn == 0) EventLogMessage.opAckn = 1;
  EventLogMessage.messageText = "Error on heat start with unknown heat ";
  EventLogMessage.messageText2 = "Error on heat start with unknown heat ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " at ";
  EventLogMessage.messageText += TreatmentPos;
  EventLogMessage.messageText += " - announce heat on level 2 and re-start heat on level 1";
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " at ";
  EventLogMessage.messageText2 += TreatmentPos;
  EventLogMessage.messageText2 += " - announce heat on level 2 and re-start heat on level 1";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_Analysis( const char * Elem1,double AnlVal1,const char * Elem2,double AnlVal2,const char * Elem3,double AnlVal3,const char * Elem4,double AnlVal4,const char * Elem5,double AnlVale5,const char * Elem6,double AnlVale6,const char * Elem7,double AnlVale7)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "";
  EventLogMessage.messageText2 = "";
  EventLogMessage.messageText += Elem1;
  EventLogMessage.messageText += ": ";
  char mstring1[64];
  sprintf( mstring1,"%f",AnlVal1);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem2;
  EventLogMessage.messageText += ": ";
  char mstring3[64];
  sprintf( mstring3,"%f",AnlVal2);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem3;
  EventLogMessage.messageText += ": ";
  char mstring5[64];
  sprintf( mstring5,"%f",AnlVal3);
  EventLogMessage.messageText += mstring5;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem4;
  EventLogMessage.messageText += ": ";
  char mstring7[64];
  sprintf( mstring7,"%f",AnlVal4);
  EventLogMessage.messageText += mstring7;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem5;
  EventLogMessage.messageText += ": ";
  char mstring9[64];
  sprintf( mstring9,"%f",AnlVale5);
  EventLogMessage.messageText += mstring9;
  EventLogMessage.messageText += "  ";
  EventLogMessage.messageText += Elem6;
  EventLogMessage.messageText += ": ";
  char mstring11[64];
  sprintf( mstring11,"%f",AnlVale6);
  EventLogMessage.messageText += mstring11;
  EventLogMessage.messageText += "  ";
  EventLogMessage.messageText += Elem7;
  EventLogMessage.messageText += ": ";
  char mstring13[64];
  sprintf( mstring13,"%f",AnlVale7);
  EventLogMessage.messageText += mstring13;
  EventLogMessage.messageText2 += Elem1;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem2;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem3;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring5;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem4;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring7;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem5;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring9;
  EventLogMessage.messageText2 += "  ";
  EventLogMessage.messageText2 += Elem6;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring11;
  EventLogMessage.messageText2 += "  ";
  EventLogMessage.messageText2 += Elem7;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring13;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11091;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_Analysis( sEventLogMessage &EventLogMessage, const char * Elem1,double AnlVal1,const char * Elem2,double AnlVal2,const char * Elem3,double AnlVal3,const char * Elem4,double AnlVal4,const char * Elem5,double AnlVale5,const char * Elem6,double AnlVale6,const char * Elem7,double AnlVale7)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11091;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "";
  EventLogMessage.messageText2 = "";
  EventLogMessage.messageText += Elem1;
  EventLogMessage.messageText += ": ";
  char mstring1[64];
  sprintf( mstring1,"%f",AnlVal1);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem2;
  EventLogMessage.messageText += ": ";
  char mstring3[64];
  sprintf( mstring3,"%f",AnlVal2);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem3;
  EventLogMessage.messageText += ": ";
  char mstring5[64];
  sprintf( mstring5,"%f",AnlVal3);
  EventLogMessage.messageText += mstring5;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem4;
  EventLogMessage.messageText += ": ";
  char mstring7[64];
  sprintf( mstring7,"%f",AnlVal4);
  EventLogMessage.messageText += mstring7;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem5;
  EventLogMessage.messageText += ": ";
  char mstring9[64];
  sprintf( mstring9,"%f",AnlVale5);
  EventLogMessage.messageText += mstring9;
  EventLogMessage.messageText += "  ";
  EventLogMessage.messageText += Elem6;
  EventLogMessage.messageText += ": ";
  char mstring11[64];
  sprintf( mstring11,"%f",AnlVale6);
  EventLogMessage.messageText += mstring11;
  EventLogMessage.messageText += "  ";
  EventLogMessage.messageText += Elem7;
  EventLogMessage.messageText += ": ";
  char mstring13[64];
  sprintf( mstring13,"%f",AnlVale7);
  EventLogMessage.messageText += mstring13;
  EventLogMessage.messageText2 += Elem1;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem2;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem3;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring5;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem4;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring7;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem5;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring9;
  EventLogMessage.messageText2 += "  ";
  EventLogMessage.messageText2 += Elem6;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring11;
  EventLogMessage.messageText2 += "  ";
  EventLogMessage.messageText2 += Elem7;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring13;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InitialHeatPropertyChanged( const char * Type,const char * CurrentValue,const char * NewValue)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Initial heat property ";
  EventLogMessage.messageText2 = "Initial heat property ";
  EventLogMessage.messageText += Type;
  EventLogMessage.messageText += " changed : Current ";
  EventLogMessage.messageText += CurrentValue;
  EventLogMessage.messageText += " New ";
  EventLogMessage.messageText += NewValue;
  EventLogMessage.messageText2 += Type;
  EventLogMessage.messageText2 += " changed : Current ";
  EventLogMessage.messageText2 += CurrentValue;
  EventLogMessage.messageText2 += " New ";
  EventLogMessage.messageText2 += NewValue;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11092;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InitialHeatPropertyChanged( sEventLogMessage &EventLogMessage, const char * Type,const char * CurrentValue,const char * NewValue)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11092;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Initial heat property ";
  EventLogMessage.messageText2 = "Initial heat property ";
  EventLogMessage.messageText += Type;
  EventLogMessage.messageText += " changed : Current ";
  EventLogMessage.messageText += CurrentValue;
  EventLogMessage.messageText += " New ";
  EventLogMessage.messageText += NewValue;
  EventLogMessage.messageText2 += Type;
  EventLogMessage.messageText2 += " changed : Current ";
  EventLogMessage.messageText2 += CurrentValue;
  EventLogMessage.messageText2 += " New ";
  EventLogMessage.messageText2 += NewValue;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_UserNotFound( const char * PlantID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "No user found, who is currently responsible for ";
  EventLogMessage.messageText2 = "No user found, who is currently responsible for ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11093;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_UserNotFound( sEventLogMessage &EventLogMessage, const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11093;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "No user found, who is currently responsible for ";
  EventLogMessage.messageText2 = "No user found, who is currently responsible for ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += PlantID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_AddedProduct( const char * ProductID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Product added. ProductId ";
  EventLogMessage.messageText2 = "Product added. ProductId ";
  EventLogMessage.messageText += ProductID;
  EventLogMessage.messageText2 += ProductID;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11094;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_AddedProduct( sEventLogMessage &EventLogMessage, const char * ProductID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11094;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Product added. ProductId ";
  EventLogMessage.messageText2 = "Product added. ProductId ";
  EventLogMessage.messageText += ProductID;
  EventLogMessage.messageText2 += ProductID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_RecipeConversion( int L1RecNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Recipe conversion L1No: ";
  EventLogMessage.messageText2 = "Recipe conversion L1No: ";
  char mstring0[64];
  sprintf( mstring0,"%d",L1RecNo);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11095;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_RecipeConversion( sEventLogMessage &EventLogMessage, int L1RecNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11095;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Recipe conversion L1No: ";
  EventLogMessage.messageText2 = "Recipe conversion L1No: ";
  char mstring0[64];
  sprintf( mstring0,"%d",L1RecNo);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText2 += mstring0;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_RecipeConversion( const char * RecipeName,int RecipeNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Recipe conversion. RecipeName: ";
  EventLogMessage.messageText2 = "Recipe conversion. RecipeName: ";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " RecipeNo: ";
  char mstring1[64];
  sprintf( mstring1,"%d",RecipeNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " RecipeNo: ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11096;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_RecipeConversion( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11096;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Recipe conversion. RecipeName: ";
  EventLogMessage.messageText2 = "Recipe conversion. RecipeName: ";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " RecipeNo: ";
  char mstring1[64];
  sprintf( mstring1,"%d",RecipeNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " RecipeNo: ";
  EventLogMessage.messageText2 += mstring1;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_LogMessageLost( int Size)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Queue of size ";
  EventLogMessage.messageText2 = "Queue of size ";
  char mstring0[64];
  sprintf( mstring0,"%d",Size);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " is full. Message lost";
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " is full. Message lost";
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11097;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_LogMessageLost( sEventLogMessage &EventLogMessage, int Size)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11097;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Queue of size ";
  EventLogMessage.messageText2 = "Queue of size ";
  char mstring0[64];
  sprintf( mstring0,"%d",Size);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " is full. Message lost";
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " is full. Message lost";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorWrongHeatingModeStarted( int L1HeatingMode,int L2HeatingMode)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "L1 started Heating Mode ";
  EventLogMessage.messageText2 = "L1 started Heating Mode ";
  char mstring0[64];
  sprintf( mstring0,"%d",L1HeatingMode);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += ", but L2 announced Heating Mode ";
  char mstring1[64];
  sprintf( mstring1,"%d",L2HeatingMode);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += "! Computer Mode ist not allowed";
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += ", but L2 announced Heating Mode ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += "! Computer Mode ist not allowed";
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11098;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorWrongHeatingModeStarted( sEventLogMessage &EventLogMessage, int L1HeatingMode,int L2HeatingMode)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11098;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "L1 started Heating Mode ";
  EventLogMessage.messageText2 = "L1 started Heating Mode ";
  char mstring0[64];
  sprintf( mstring0,"%d",L1HeatingMode);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += ", but L2 announced Heating Mode ";
  char mstring1[64];
  sprintf( mstring1,"%d",L2HeatingMode);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += "! Computer Mode ist not allowed";
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += ", but L2 announced Heating Mode ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += "! Computer Mode ist not allowed";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_StatusNotChanged( const char * PlantID,const char * StatusName,int Status)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Status not changed. Plant: ";
  EventLogMessage.messageText2 = "Status not changed. Plant: ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText += " Status Name: ";
  EventLogMessage.messageText += StatusName;
  EventLogMessage.messageText += " Status: ";
  char mstring2[64];
  sprintf( mstring2,"%d",Status);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.messageText2 += " Status Name: ";
  EventLogMessage.messageText2 += StatusName;
  EventLogMessage.messageText2 += " Status: ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11099;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_StatusNotChanged( sEventLogMessage &EventLogMessage, const char * PlantID,const char * StatusName,int Status)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11099;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Status not changed. Plant: ";
  EventLogMessage.messageText2 = "Status not changed. Plant: ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText += " Status Name: ";
  EventLogMessage.messageText += StatusName;
  EventLogMessage.messageText += " Status: ";
  char mstring2[64];
  sprintf( mstring2,"%d",Status);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.messageText2 += " Status Name: ";
  EventLogMessage.messageText2 += StatusName;
  EventLogMessage.messageText2 += " Status: ";
  EventLogMessage.messageText2 += mstring2;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingLadleData( const char * LadleType,int LadleNo,const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error handling data for ladle ";
  EventLogMessage.messageText2 = "Error handling data for ladle ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Message;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11100;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingLadleData( sEventLogMessage &EventLogMessage, const char * LadleType,int LadleNo,const char * Message)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11100;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error handling data for ladle ";
  EventLogMessage.messageText2 = "Error handling data for ladle ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Message;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ChangeEquipmentThermalStatus( const char * EquipmentName,const char * ThermStatus)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Thermal status of ";
  EventLogMessage.messageText2 = "Thermal status of ";
  EventLogMessage.messageText += EquipmentName;
  EventLogMessage.messageText += " changed to ";
  EventLogMessage.messageText += ThermStatus;
  EventLogMessage.messageText2 += EquipmentName;
  EventLogMessage.messageText2 += " changed to ";
  EventLogMessage.messageText2 += ThermStatus;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11101;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ChangeEquipmentThermalStatus( sEventLogMessage &EventLogMessage, const char * EquipmentName,const char * ThermStatus)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11101;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Thermal status of ";
  EventLogMessage.messageText2 = "Thermal status of ";
  EventLogMessage.messageText += EquipmentName;
  EventLogMessage.messageText += " changed to ";
  EventLogMessage.messageText += ThermStatus;
  EventLogMessage.messageText2 += EquipmentName;
  EventLogMessage.messageText2 += " changed to ";
  EventLogMessage.messageText2 += ThermStatus;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatAnnouncementModelError( const char * HeatID,const char * TreatID,const char * PlantID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Heat could'n be announced at model ";
  EventLogMessage.messageText2 = "Heat could'n be announced at model ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11102;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatAnnouncementModelError( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11102;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Heat could'n be announced at model ";
  EventLogMessage.messageText2 = "Heat could'n be announced at model ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at plant ";
  EventLogMessage.messageText2 += PlantID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorUnknownLadleReceived( const char * LadleType,const char * LadleNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "LadleType = ";
  EventLogMessage.messageText2 = "LadleType = ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " LadleNo = ";
  EventLogMessage.messageText += LadleNo;
  EventLogMessage.messageText += " is not defined! Handling is not possible!";
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " LadleNo = ";
  EventLogMessage.messageText2 += LadleNo;
  EventLogMessage.messageText2 += " is not defined! Handling is not possible!";
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11103;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorUnknownLadleReceived( sEventLogMessage &EventLogMessage, const char * LadleType,const char * LadleNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11103;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "LadleType = ";
  EventLogMessage.messageText2 = "LadleType = ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " LadleNo = ";
  EventLogMessage.messageText += LadleNo;
  EventLogMessage.messageText += " is not defined! Handling is not possible!";
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " LadleNo = ";
  EventLogMessage.messageText2 += LadleNo;
  EventLogMessage.messageText2 += " is not defined! Handling is not possible!";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorUnknownScrapContainerNoReceived( const char * ContainerNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "ScrapContainer No ";
  EventLogMessage.messageText2 = "ScrapContainer No ";
  EventLogMessage.messageText += ContainerNo;
  EventLogMessage.messageText += " is not defined! Handling is not possible!";
  EventLogMessage.messageText2 += ContainerNo;
  EventLogMessage.messageText2 += " is not defined! Handling is not possible!";
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11104;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorUnknownScrapContainerNoReceived( sEventLogMessage &EventLogMessage, const char * ContainerNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11104;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "ScrapContainer No ";
  EventLogMessage.messageText2 = "ScrapContainer No ";
  EventLogMessage.messageText += ContainerNo;
  EventLogMessage.messageText += " is not defined! Handling is not possible!";
  EventLogMessage.messageText2 += ContainerNo;
  EventLogMessage.messageText2 += " is not defined! Handling is not possible!";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingCyclicData( const char * Measurement,const char * Function,const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error handling cyclic data for ";
  EventLogMessage.messageText2 = "Error handling cyclic data for ";
  EventLogMessage.messageText += Measurement;
  EventLogMessage.messageText += " at function ";
  EventLogMessage.messageText += Function;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += Measurement;
  EventLogMessage.messageText2 += " at function ";
  EventLogMessage.messageText2 += Function;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += Message;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11105;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingCyclicData( sEventLogMessage &EventLogMessage, const char * Measurement,const char * Function,const char * Message)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11105;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error handling cyclic data for ";
  EventLogMessage.messageText2 = "Error handling cyclic data for ";
  EventLogMessage.messageText += Measurement;
  EventLogMessage.messageText += " at function ";
  EventLogMessage.messageText += Function;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += Measurement;
  EventLogMessage.messageText2 += " at function ";
  EventLogMessage.messageText2 += Function;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += Message;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidTlgDataToDefault( const char * TlgName,const char * Element,int Value,int Min,int Max,int Default)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Invalid data. Telegram: ";
  EventLogMessage.messageText2 = "Invalid data. Telegram: ";
  EventLogMessage.messageText += TlgName;
  EventLogMessage.messageText += " Element: ";
  EventLogMessage.messageText += Element;
  EventLogMessage.messageText += " Value: ";
  char mstring2[64];
  sprintf( mstring2,"%d",Value);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText += " out of Range min: ";
  char mstring3[64];
  sprintf( mstring3,"%d",Min);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText += "  max: ";
  char mstring4[64];
  sprintf( mstring4,"%d",Max);
  EventLogMessage.messageText += mstring4;
  EventLogMessage.messageText += " using defaullt ";
  char mstring5[64];
  sprintf( mstring5,"%d",Default);
  EventLogMessage.messageText += mstring5;
  EventLogMessage.messageText2 += TlgName;
  EventLogMessage.messageText2 += " Element: ";
  EventLogMessage.messageText2 += Element;
  EventLogMessage.messageText2 += " Value: ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.messageText2 += " out of Range min: ";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.messageText2 += "  max: ";
  EventLogMessage.messageText2 += mstring4;
  EventLogMessage.messageText2 += " using defaullt ";
  EventLogMessage.messageText2 += mstring5;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11106;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidTlgDataToDefault( sEventLogMessage &EventLogMessage, const char * TlgName,const char * Element,int Value,int Min,int Max,int Default)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11106;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Invalid data. Telegram: ";
  EventLogMessage.messageText2 = "Invalid data. Telegram: ";
  EventLogMessage.messageText += TlgName;
  EventLogMessage.messageText += " Element: ";
  EventLogMessage.messageText += Element;
  EventLogMessage.messageText += " Value: ";
  char mstring2[64];
  sprintf( mstring2,"%d",Value);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText += " out of Range min: ";
  char mstring3[64];
  sprintf( mstring3,"%d",Min);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText += "  max: ";
  char mstring4[64];
  sprintf( mstring4,"%d",Max);
  EventLogMessage.messageText += mstring4;
  EventLogMessage.messageText += " using defaullt ";
  char mstring5[64];
  sprintf( mstring5,"%d",Default);
  EventLogMessage.messageText += mstring5;
  EventLogMessage.messageText2 += TlgName;
  EventLogMessage.messageText2 += " Element: ";
  EventLogMessage.messageText2 += Element;
  EventLogMessage.messageText2 += " Value: ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.messageText2 += " out of Range min: ";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.messageText2 += "  max: ";
  EventLogMessage.messageText2 += mstring4;
  EventLogMessage.messageText2 += " using defaullt ";
  EventLogMessage.messageText2 += mstring5;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidTlgDataToDefault( const char * TlgName,const char * Element,double Value,double Min,double Max,double Default)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Invalid data. Telegram: ";
  EventLogMessage.messageText2 = "Invalid data. Telegram: ";
  EventLogMessage.messageText += TlgName;
  EventLogMessage.messageText += " Element: ";
  EventLogMessage.messageText += Element;
  EventLogMessage.messageText += " Value: ";
  char mstring2[64];
  sprintf( mstring2,"%f",Value);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText += " out of Range min: ";
  char mstring3[64];
  sprintf( mstring3,"%f",Min);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText += " max: ";
  char mstring4[64];
  sprintf( mstring4,"%f",Max);
  EventLogMessage.messageText += mstring4;
  EventLogMessage.messageText += " using default ";
  char mstring5[64];
  sprintf( mstring5,"%f",Default);
  EventLogMessage.messageText += mstring5;
  EventLogMessage.messageText2 += TlgName;
  EventLogMessage.messageText2 += " Element: ";
  EventLogMessage.messageText2 += Element;
  EventLogMessage.messageText2 += " Value: ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.messageText2 += " out of Range min: ";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.messageText2 += " max: ";
  EventLogMessage.messageText2 += mstring4;
  EventLogMessage.messageText2 += " using default ";
  EventLogMessage.messageText2 += mstring5;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11107;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidTlgDataToDefault( sEventLogMessage &EventLogMessage, const char * TlgName,const char * Element,double Value,double Min,double Max,double Default)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11107;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Invalid data. Telegram: ";
  EventLogMessage.messageText2 = "Invalid data. Telegram: ";
  EventLogMessage.messageText += TlgName;
  EventLogMessage.messageText += " Element: ";
  EventLogMessage.messageText += Element;
  EventLogMessage.messageText += " Value: ";
  char mstring2[64];
  sprintf( mstring2,"%f",Value);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText += " out of Range min: ";
  char mstring3[64];
  sprintf( mstring3,"%f",Min);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText += " max: ";
  char mstring4[64];
  sprintf( mstring4,"%f",Max);
  EventLogMessage.messageText += mstring4;
  EventLogMessage.messageText += " using default ";
  char mstring5[64];
  sprintf( mstring5,"%f",Default);
  EventLogMessage.messageText += mstring5;
  EventLogMessage.messageText2 += TlgName;
  EventLogMessage.messageText2 += " Element: ";
  EventLogMessage.messageText2 += Element;
  EventLogMessage.messageText2 += " Value: ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.messageText2 += " out of Range min: ";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.messageText2 += " max: ";
  EventLogMessage.messageText2 += mstring4;
  EventLogMessage.messageText2 += " using default ";
  EventLogMessage.messageText2 += mstring5;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingScrapContainerData( const char * ContainerType,int ScrapContainerNo,const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error handling data for ScrapContainer ";
  EventLogMessage.messageText2 = "Error handling data for ScrapContainer ";
  EventLogMessage.messageText += ContainerType;
  EventLogMessage.messageText += " ";
  char mstring1[64];
  sprintf( mstring1,"%d",ScrapContainerNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += ContainerType;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Message;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11108;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingScrapContainerData( sEventLogMessage &EventLogMessage, const char * ContainerType,int ScrapContainerNo,const char * Message)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11108;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error handling data for ScrapContainer ";
  EventLogMessage.messageText2 = "Error handling data for ScrapContainer ";
  EventLogMessage.messageText += ContainerType;
  EventLogMessage.messageText += " ";
  char mstring1[64];
  sprintf( mstring1,"%d",ScrapContainerNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += ContainerType;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Message;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_Analysis( const char * Elem1,const char * AnlVal1,const char * Elem2,const char * AnlVal2,const char * Elem3,const char * AnlVal3,const char * Elem4,const char * AnlVal4,const char * Elem5,const char * AnlVale5)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "";
  EventLogMessage.messageText2 = "";
  EventLogMessage.messageText += Elem1;
  EventLogMessage.messageText += ": ";
  EventLogMessage.messageText += AnlVal1;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem2;
  EventLogMessage.messageText += ": ";
  EventLogMessage.messageText += AnlVal2;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem3;
  EventLogMessage.messageText += ": ";
  EventLogMessage.messageText += AnlVal3;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem4;
  EventLogMessage.messageText += ": ";
  EventLogMessage.messageText += AnlVal4;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem5;
  EventLogMessage.messageText += ": ";
  EventLogMessage.messageText += AnlVale5;
  EventLogMessage.messageText2 += Elem1;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += AnlVal1;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem2;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += AnlVal2;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem3;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += AnlVal3;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem4;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += AnlVal4;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem5;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += AnlVale5;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11109;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_Analysis( sEventLogMessage &EventLogMessage, const char * Elem1,const char * AnlVal1,const char * Elem2,const char * AnlVal2,const char * Elem3,const char * AnlVal3,const char * Elem4,const char * AnlVal4,const char * Elem5,const char * AnlVale5)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11109;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "";
  EventLogMessage.messageText2 = "";
  EventLogMessage.messageText += Elem1;
  EventLogMessage.messageText += ": ";
  EventLogMessage.messageText += AnlVal1;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem2;
  EventLogMessage.messageText += ": ";
  EventLogMessage.messageText += AnlVal2;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem3;
  EventLogMessage.messageText += ": ";
  EventLogMessage.messageText += AnlVal3;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem4;
  EventLogMessage.messageText += ": ";
  EventLogMessage.messageText += AnlVal4;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem5;
  EventLogMessage.messageText += ": ";
  EventLogMessage.messageText += AnlVale5;
  EventLogMessage.messageText2 += Elem1;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += AnlVal1;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem2;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += AnlVal2;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem3;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += AnlVal3;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem4;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += AnlVal4;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem5;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += AnlVale5;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_SteelGradeChanged( const char * NewSteelGrade)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Steel grade changed to new Steel Grade ";
  EventLogMessage.messageText2 = "Steel grade changed to new Steel Grade ";
  EventLogMessage.messageText += NewSteelGrade;
  EventLogMessage.messageText2 += NewSteelGrade;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11110;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_SteelGradeChanged( sEventLogMessage &EventLogMessage, const char * NewSteelGrade)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11110;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Steel grade changed to new Steel Grade ";
  EventLogMessage.messageText2 = "Steel grade changed to new Steel Grade ";
  EventLogMessage.messageText += NewSteelGrade;
  EventLogMessage.messageText2 += NewSteelGrade;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingDateTime( const char * Description)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error handling Date or Time Information ";
  EventLogMessage.messageText2 = "Error handling Date or Time Information ";
  EventLogMessage.messageText += Description;
  EventLogMessage.messageText2 += Description;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11111;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingDateTime( sEventLogMessage &EventLogMessage, const char * Description)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11111;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error handling Date or Time Information ";
  EventLogMessage.messageText2 = "Error handling Date or Time Information ";
  EventLogMessage.messageText += Description;
  EventLogMessage.messageText2 += Description;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_LostTelegramInQueue( const char * ConnectString,const char * ProcessName,const char * TelegramName)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Telegram processing delay in ";
  EventLogMessage.messageText2 = "Telegram processing delay in ";
  EventLogMessage.messageText += ConnectString;
  EventLogMessage.messageText += ". Process name ";
  EventLogMessage.messageText += ProcessName;
  EventLogMessage.messageText += " lost telegram name ";
  EventLogMessage.messageText += TelegramName;
  EventLogMessage.messageText2 += ConnectString;
  EventLogMessage.messageText2 += ". Process name ";
  EventLogMessage.messageText2 += ProcessName;
  EventLogMessage.messageText2 += " lost telegram name ";
  EventLogMessage.messageText2 += TelegramName;
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11112;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_LostTelegramInQueue( sEventLogMessage &EventLogMessage, const char * ConnectString,const char * ProcessName,const char * TelegramName)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11112;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Telegram processing delay in ";
  EventLogMessage.messageText2 = "Telegram processing delay in ";
  EventLogMessage.messageText += ConnectString;
  EventLogMessage.messageText += ". Process name ";
  EventLogMessage.messageText += ProcessName;
  EventLogMessage.messageText += " lost telegram name ";
  EventLogMessage.messageText += TelegramName;
  EventLogMessage.messageText2 += ConnectString;
  EventLogMessage.messageText2 += ". Process name ";
  EventLogMessage.messageText2 += ProcessName;
  EventLogMessage.messageText2 += " lost telegram name ";
  EventLogMessage.messageText2 += TelegramName;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatNotInProduction( const char * CustHeatID,const char * CustTreatID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Receiving data for finished heat ";
  EventLogMessage.messageText2 = "Receiving data for finished heat ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11113;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatNotInProduction( sEventLogMessage &EventLogMessage, const char * CustHeatID,const char * CustTreatID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11113;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Receiving data for finished heat ";
  EventLogMessage.messageText2 = "Receiving data for finished heat ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += CustTreatID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ScrapContainerDischargedError( int ContainerInSeq,int ContainerNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error handling scrap discharged. ContainerInSeq:";
  EventLogMessage.messageText2 = "Error handling scrap discharged. ContainerInSeq:";
  char mstring0[64];
  sprintf( mstring0,"%d",ContainerInSeq);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " ContainerNo: ";
  char mstring1[64];
  sprintf( mstring1,"%d",ContainerNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " ContainerNo: ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11114;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ScrapContainerDischargedError( sEventLogMessage &EventLogMessage, int ContainerInSeq,int ContainerNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11114;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error handling scrap discharged. ContainerInSeq:";
  EventLogMessage.messageText2 = "Error handling scrap discharged. ContainerInSeq:";
  char mstring0[64];
  sprintf( mstring0,"%d",ContainerInSeq);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " ContainerNo: ";
  char mstring1[64];
  sprintf( mstring1,"%d",ContainerNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " ContainerNo: ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHeatingModeHeatAlreadyStarted( const char * CustHeatID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Heating mode could not be changed, heat ";
  EventLogMessage.messageText2 = "Heating mode could not be changed, heat ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " is already started";
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " is already started";
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11115;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHeatingModeHeatAlreadyStarted( sEventLogMessage &EventLogMessage, const char * CustHeatID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11115;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Heating mode could not be changed, heat ";
  EventLogMessage.messageText2 = "Heating mode could not be changed, heat ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " is already started";
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " is already started";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidLadle( const char * LadleType,int LadleNo,const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Not valid ladle: ";
  EventLogMessage.messageText2 = "Not valid ladle: ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Message;
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11116;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidLadle( sEventLogMessage &EventLogMessage, const char * LadleType,int LadleNo,const char * Message)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11116;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Not valid ladle: ";
  EventLogMessage.messageText2 = "Not valid ladle: ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Message;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidProductionOrder( const char * OrderId,const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Not valid production order ";
  EventLogMessage.messageText2 = "Not valid production order ";
  EventLogMessage.messageText += OrderId;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += OrderId;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Message;
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11117;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidProductionOrder( sEventLogMessage &EventLogMessage, const char * OrderId,const char * Message)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11117;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Not valid production order ";
  EventLogMessage.messageText2 = "Not valid production order ";
  EventLogMessage.messageText += OrderId;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += OrderId;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Message;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HMAnalysisAssignmentError( const char * HMLadleID,int SampleRef)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Hot metal analysis for ladle ";
  EventLogMessage.messageText2 = "Hot metal analysis for ladle ";
  EventLogMessage.messageText += HMLadleID;
  EventLogMessage.messageText += " could not be assigned to any hot metal. SampleRef ";
  char mstring1[64];
  sprintf( mstring1,"%d",SampleRef);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += HMLadleID;
  EventLogMessage.messageText2 += " could not be assigned to any hot metal. SampleRef ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.opAckn = 1;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 11118;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HMAnalysisAssignmentError( sEventLogMessage &EventLogMessage, const char * HMLadleID,int SampleRef)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11118;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  if (EventLogMessage.opAckn == 0) EventLogMessage.opAckn = 1;
  EventLogMessage.messageText = "Hot metal analysis for ladle ";
  EventLogMessage.messageText2 = "Hot metal analysis for ladle ";
  EventLogMessage.messageText += HMLadleID;
  EventLogMessage.messageText += " could not be assigned to any hot metal. SampleRef ";
  char mstring1[64];
  sprintf( mstring1,"%d",SampleRef);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += HMLadleID;
  EventLogMessage.messageText2 += " could not be assigned to any hot metal. SampleRef ";
  EventLogMessage.messageText2 += mstring1;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HotMetalAnalysisReceived( const char * HotMetalID,const char * Elem1,double AnlVal1,const char * Elem2,double AnlVal2,const char * Elem3,double AnlVal3,const char * Elem4,double AnlVal4,const char * Elem5,double AnlVale5,const char * Elem6,double AnlVale6,const char * Elem7,double AnlVale7)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Hot metal analysis received HotMetalID: ";
  EventLogMessage.messageText2 = "Hot metal analysis received HotMetalID: ";
  EventLogMessage.messageText += HotMetalID;
  EventLogMessage.messageText += " Elements ";
  EventLogMessage.messageText += Elem1;
  EventLogMessage.messageText += ": ";
  char mstring2[64];
  sprintf( mstring2,"%f",AnlVal1);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem2;
  EventLogMessage.messageText += ": ";
  char mstring4[64];
  sprintf( mstring4,"%f",AnlVal2);
  EventLogMessage.messageText += mstring4;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem3;
  EventLogMessage.messageText += ": ";
  char mstring6[64];
  sprintf( mstring6,"%f",AnlVal3);
  EventLogMessage.messageText += mstring6;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem4;
  EventLogMessage.messageText += ": ";
  char mstring8[64];
  sprintf( mstring8,"%f",AnlVal4);
  EventLogMessage.messageText += mstring8;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem5;
  EventLogMessage.messageText += ": ";
  char mstring10[64];
  sprintf( mstring10,"%f",AnlVale5);
  EventLogMessage.messageText += mstring10;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem6;
  EventLogMessage.messageText += ": ";
  char mstring12[64];
  sprintf( mstring12,"%f",AnlVale6);
  EventLogMessage.messageText += mstring12;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem7;
  EventLogMessage.messageText += ": ";
  char mstring14[64];
  sprintf( mstring14,"%f",AnlVale7);
  EventLogMessage.messageText += mstring14;
  EventLogMessage.messageText2 += HotMetalID;
  EventLogMessage.messageText2 += " Elements ";
  EventLogMessage.messageText2 += Elem1;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem2;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring4;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem3;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring6;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem4;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring8;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem5;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring10;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem6;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring12;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem7;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring14;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11119;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HotMetalAnalysisReceived( sEventLogMessage &EventLogMessage, const char * HotMetalID,const char * Elem1,double AnlVal1,const char * Elem2,double AnlVal2,const char * Elem3,double AnlVal3,const char * Elem4,double AnlVal4,const char * Elem5,double AnlVale5,const char * Elem6,double AnlVale6,const char * Elem7,double AnlVale7)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11119;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Hot metal analysis received HotMetalID: ";
  EventLogMessage.messageText2 = "Hot metal analysis received HotMetalID: ";
  EventLogMessage.messageText += HotMetalID;
  EventLogMessage.messageText += " Elements ";
  EventLogMessage.messageText += Elem1;
  EventLogMessage.messageText += ": ";
  char mstring2[64];
  sprintf( mstring2,"%f",AnlVal1);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem2;
  EventLogMessage.messageText += ": ";
  char mstring4[64];
  sprintf( mstring4,"%f",AnlVal2);
  EventLogMessage.messageText += mstring4;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem3;
  EventLogMessage.messageText += ": ";
  char mstring6[64];
  sprintf( mstring6,"%f",AnlVal3);
  EventLogMessage.messageText += mstring6;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem4;
  EventLogMessage.messageText += ": ";
  char mstring8[64];
  sprintf( mstring8,"%f",AnlVal4);
  EventLogMessage.messageText += mstring8;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem5;
  EventLogMessage.messageText += ": ";
  char mstring10[64];
  sprintf( mstring10,"%f",AnlVale5);
  EventLogMessage.messageText += mstring10;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem6;
  EventLogMessage.messageText += ": ";
  char mstring12[64];
  sprintf( mstring12,"%f",AnlVale6);
  EventLogMessage.messageText += mstring12;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += Elem7;
  EventLogMessage.messageText += ": ";
  char mstring14[64];
  sprintf( mstring14,"%f",AnlVale7);
  EventLogMessage.messageText += mstring14;
  EventLogMessage.messageText2 += HotMetalID;
  EventLogMessage.messageText2 += " Elements ";
  EventLogMessage.messageText2 += Elem1;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem2;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring4;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem3;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring6;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem4;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring8;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem5;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring10;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem6;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring12;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += Elem7;
  EventLogMessage.messageText2 += ": ";
  EventLogMessage.messageText2 += mstring14;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidHotMetalId( const char * HotMetalID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Invalid hot metal ID: ";
  EventLogMessage.messageText2 = "Invalid hot metal ID: ";
  EventLogMessage.messageText += HotMetalID;
  EventLogMessage.messageText2 += HotMetalID;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11120;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidHotMetalId( sEventLogMessage &EventLogMessage, const char * HotMetalID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11120;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Invalid hot metal ID: ";
  EventLogMessage.messageText2 = "Invalid hot metal ID: ";
  EventLogMessage.messageText += HotMetalID;
  EventLogMessage.messageText2 += HotMetalID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HotMetalTemperatureReceived( const char * HotMetalID,double MeasTemp)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Hot metal temperature received HotMetalID: ";
  EventLogMessage.messageText2 = "Hot metal temperature received HotMetalID: ";
  EventLogMessage.messageText += HotMetalID;
  EventLogMessage.messageText += " Temperature: ";
  char mstring1[64];
  sprintf( mstring1,"%f",MeasTemp);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += HotMetalID;
  EventLogMessage.messageText2 += " Temperature: ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11121;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HotMetalTemperatureReceived( sEventLogMessage &EventLogMessage, const char * HotMetalID,double MeasTemp)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11121;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Hot metal temperature received HotMetalID: ";
  EventLogMessage.messageText2 = "Hot metal temperature received HotMetalID: ";
  EventLogMessage.messageText += HotMetalID;
  EventLogMessage.messageText += " Temperature: ";
  char mstring1[64];
  sprintf( mstring1,"%f",MeasTemp);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += HotMetalID;
  EventLogMessage.messageText2 += " Temperature: ";
  EventLogMessage.messageText2 += mstring1;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HMTemperatureAssignmentError( const char * HMLadleID,int SampleRef)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Hot metal temperature for ladle ";
  EventLogMessage.messageText2 = "Hot metal temperature for ladle ";
  EventLogMessage.messageText += HMLadleID;
  EventLogMessage.messageText += " could not be assigned to any hot metal. SampleRef ";
  char mstring1[64];
  sprintf( mstring1,"%d",SampleRef);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += HMLadleID;
  EventLogMessage.messageText2 += " could not be assigned to any hot metal. SampleRef ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.opAckn = 1;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 11122;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HMTemperatureAssignmentError( sEventLogMessage &EventLogMessage, const char * HMLadleID,int SampleRef)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11122;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  if (EventLogMessage.opAckn == 0) EventLogMessage.opAckn = 1;
  EventLogMessage.messageText = "Hot metal temperature for ladle ";
  EventLogMessage.messageText2 = "Hot metal temperature for ladle ";
  EventLogMessage.messageText += HMLadleID;
  EventLogMessage.messageText += " could not be assigned to any hot metal. SampleRef ";
  char mstring1[64];
  sprintf( mstring1,"%d",SampleRef);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += HMLadleID;
  EventLogMessage.messageText2 += " could not be assigned to any hot metal. SampleRef ";
  EventLogMessage.messageText2 += mstring1;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidTlgDataToDefault( const char * TlgName,const char * Element,const char * Value,const char * Default)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Invalid data. Telegram: ";
  EventLogMessage.messageText2 = "Invalid data. Telegram: ";
  EventLogMessage.messageText += TlgName;
  EventLogMessage.messageText += " Element: ";
  EventLogMessage.messageText += Element;
  EventLogMessage.messageText += " Value: ";
  EventLogMessage.messageText += Value;
  EventLogMessage.messageText += " using defaullt ";
  EventLogMessage.messageText += Default;
  EventLogMessage.messageText2 += TlgName;
  EventLogMessage.messageText2 += " Element: ";
  EventLogMessage.messageText2 += Element;
  EventLogMessage.messageText2 += " Value: ";
  EventLogMessage.messageText2 += Value;
  EventLogMessage.messageText2 += " using defaullt ";
  EventLogMessage.messageText2 += Default;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11123;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_InvalidTlgDataToDefault( sEventLogMessage &EventLogMessage, const char * TlgName,const char * Element,const char * Value,const char * Default)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11123;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Invalid data. Telegram: ";
  EventLogMessage.messageText2 = "Invalid data. Telegram: ";
  EventLogMessage.messageText += TlgName;
  EventLogMessage.messageText += " Element: ";
  EventLogMessage.messageText += Element;
  EventLogMessage.messageText += " Value: ";
  EventLogMessage.messageText += Value;
  EventLogMessage.messageText += " using defaullt ";
  EventLogMessage.messageText += Default;
  EventLogMessage.messageText2 += TlgName;
  EventLogMessage.messageText2 += " Element: ";
  EventLogMessage.messageText2 += Element;
  EventLogMessage.messageText2 += " Value: ";
  EventLogMessage.messageText2 += Value;
  EventLogMessage.messageText2 += " using defaullt ";
  EventLogMessage.messageText2 += Default;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ProdOrderNew( const char * OrderID,const char * UserCode)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "New production order received. Production order ID ";
  EventLogMessage.messageText2 = "New production order received. Production order ID ";
  char mstring0[64];
  sprintf( mstring0,"%s ",OrderID);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " User code ";
  EventLogMessage.messageText += UserCode;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " User code ";
  EventLogMessage.messageText2 += UserCode;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11124;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ProdOrderNew( sEventLogMessage &EventLogMessage, const char * OrderID,const char * UserCode)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11124;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "New production order received. Production order ID ";
  EventLogMessage.messageText2 = "New production order received. Production order ID ";
  char mstring0[64];
  sprintf( mstring0,"%s ",OrderID);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " User code ";
  EventLogMessage.messageText += UserCode;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " User code ";
  EventLogMessage.messageText2 += UserCode;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ProdOrderUpdate( const char * OrderID,const char * UserCode)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Update of production order data. Production order ID ";
  EventLogMessage.messageText2 = "Update of production order data. Production order ID ";
  char mstring0[64];
  sprintf( mstring0,"%s ",OrderID);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " User code ";
  EventLogMessage.messageText += UserCode;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " User code ";
  EventLogMessage.messageText2 += UserCode;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11125;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ProdOrderUpdate( sEventLogMessage &EventLogMessage, const char * OrderID,const char * UserCode)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11125;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Update of production order data. Production order ID ";
  EventLogMessage.messageText2 = "Update of production order data. Production order ID ";
  char mstring0[64];
  sprintf( mstring0,"%s ",OrderID);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " User code ";
  EventLogMessage.messageText += UserCode;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " User code ";
  EventLogMessage.messageText2 += UserCode;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ProdOrderDelete( const char * OrderID,const char * UserCode)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Planed production order deleted. Production order ID ";
  EventLogMessage.messageText2 = "Planed production order deleted. Production order ID ";
  char mstring0[64];
  sprintf( mstring0,"%s ",OrderID);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " User code ";
  EventLogMessage.messageText += UserCode;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " User code ";
  EventLogMessage.messageText2 += UserCode;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11126;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ProdOrderDelete( sEventLogMessage &EventLogMessage, const char * OrderID,const char * UserCode)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11126;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Planed production order deleted. Production order ID ";
  EventLogMessage.messageText2 = "Planed production order deleted. Production order ID ";
  char mstring0[64];
  sprintf( mstring0,"%s ",OrderID);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " User code ";
  EventLogMessage.messageText += UserCode;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " User code ";
  EventLogMessage.messageText2 += UserCode;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ProdOrderAlreadyExists( const char * OrderID,const char * UserCode)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Save new production order not posible. Production order ID ";
  EventLogMessage.messageText2 = "Save new production order not posible. Production order ID ";
  char mstring0[64];
  sprintf( mstring0,"%s ",OrderID);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " is already defined  User code ";
  EventLogMessage.messageText += UserCode;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " is already defined  User code ";
  EventLogMessage.messageText2 += UserCode;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11127;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ProdOrderAlreadyExists( sEventLogMessage &EventLogMessage, const char * OrderID,const char * UserCode)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11127;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Save new production order not posible. Production order ID ";
  EventLogMessage.messageText2 = "Save new production order not posible. Production order ID ";
  char mstring0[64];
  sprintf( mstring0,"%s ",OrderID);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " is already defined  User code ";
  EventLogMessage.messageText += UserCode;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " is already defined  User code ";
  EventLogMessage.messageText2 += UserCode;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ProdOrderDeleteError( const char * OrderID,const char * UserCode)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Deletion of production order in production is not possible. Production order ID ";
  EventLogMessage.messageText2 = "Deletion of production order in production is not possible. Production order ID ";
  char mstring0[64];
  sprintf( mstring0,"%s ",OrderID);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " User code ";
  EventLogMessage.messageText += UserCode;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " User code ";
  EventLogMessage.messageText2 += UserCode;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11128;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ProdOrderDeleteError( sEventLogMessage &EventLogMessage, const char * OrderID,const char * UserCode)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11128;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Deletion of production order in production is not possible. Production order ID ";
  EventLogMessage.messageText2 = "Deletion of production order in production is not possible. Production order ID ";
  char mstring0[64];
  sprintf( mstring0,"%s ",OrderID);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " User code ";
  EventLogMessage.messageText += UserCode;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " User code ";
  EventLogMessage.messageText2 += UserCode;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ProdOrderUpdateError( const char * OrderID,const char * UserCode)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Production order data update not possible. Production order ID ";
  EventLogMessage.messageText2 = "Production order data update not possible. Production order ID ";
  char mstring0[64];
  sprintf( mstring0,"%s ",OrderID);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " User code ";
  EventLogMessage.messageText += UserCode;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " User code ";
  EventLogMessage.messageText2 += UserCode;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11129;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ProdOrderUpdateError( sEventLogMessage &EventLogMessage, const char * OrderID,const char * UserCode)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11129;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Production order data update not possible. Production order ID ";
  EventLogMessage.messageText2 = "Production order data update not possible. Production order ID ";
  char mstring0[64];
  sprintf( mstring0,"%s ",OrderID);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " User code ";
  EventLogMessage.messageText += UserCode;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " User code ";
  EventLogMessage.messageText2 += UserCode;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_SteelGradeNew( const char * SteelGradeCode,const char * UserCode)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "New steel grade received. Steel grade code ";
  EventLogMessage.messageText2 = "New steel grade received. Steel grade code ";
  char mstring0[64];
  sprintf( mstring0,"%s ",SteelGradeCode);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " User code ";
  EventLogMessage.messageText += UserCode;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " User code ";
  EventLogMessage.messageText2 += UserCode;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11130;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_SteelGradeNew( sEventLogMessage &EventLogMessage, const char * SteelGradeCode,const char * UserCode)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11130;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "New steel grade received. Steel grade code ";
  EventLogMessage.messageText2 = "New steel grade received. Steel grade code ";
  char mstring0[64];
  sprintf( mstring0,"%s ",SteelGradeCode);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " User code ";
  EventLogMessage.messageText += UserCode;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " User code ";
  EventLogMessage.messageText2 += UserCode;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_SteelGradeUpdate( const char * SteelGradeCode,const char * UserCode)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Steel grade data update. Steel grade code ";
  EventLogMessage.messageText2 = "Steel grade data update. Steel grade code ";
  char mstring0[64];
  sprintf( mstring0,"%s ",SteelGradeCode);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " User code ";
  EventLogMessage.messageText += UserCode;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " User code ";
  EventLogMessage.messageText2 += UserCode;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11131;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_SteelGradeUpdate( sEventLogMessage &EventLogMessage, const char * SteelGradeCode,const char * UserCode)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11131;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Steel grade data update. Steel grade code ";
  EventLogMessage.messageText2 = "Steel grade data update. Steel grade code ";
  char mstring0[64];
  sprintf( mstring0,"%s ",SteelGradeCode);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " User code ";
  EventLogMessage.messageText += UserCode;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " User code ";
  EventLogMessage.messageText2 += UserCode;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_SteelGradeDelete( const char * SteelGradeCode,const char * UserCode)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Steel grade deleted. Steel grade code ";
  EventLogMessage.messageText2 = "Steel grade deleted. Steel grade code ";
  char mstring0[64];
  sprintf( mstring0,"%s ",SteelGradeCode);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " User code ";
  EventLogMessage.messageText += UserCode;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " User code ";
  EventLogMessage.messageText2 += UserCode;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11132;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_SteelGradeDelete( sEventLogMessage &EventLogMessage, const char * SteelGradeCode,const char * UserCode)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11132;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Steel grade deleted. Steel grade code ";
  EventLogMessage.messageText2 = "Steel grade deleted. Steel grade code ";
  char mstring0[64];
  sprintf( mstring0,"%s ",SteelGradeCode);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " User code ";
  EventLogMessage.messageText += UserCode;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " User code ";
  EventLogMessage.messageText2 += UserCode;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatDelete( const char * CustHeatID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Heat ";
  EventLogMessage.messageText2 = "Heat ";
  char mstring0[64];
  sprintf( mstring0,"%s ",CustHeatID);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " was successfully deleted.";
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " was successfully deleted.";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11133;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatDelete( sEventLogMessage &EventLogMessage, const char * CustHeatID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11133;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Heat ";
  EventLogMessage.messageText2 = "Heat ";
  char mstring0[64];
  sprintf( mstring0,"%s ",CustHeatID);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " was successfully deleted.";
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " was successfully deleted.";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatDeleteError( const char * CustHeatID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Deletion of Heat ";
  EventLogMessage.messageText2 = "Deletion of Heat ";
  char mstring0[64];
  sprintf( mstring0,"%s ",CustHeatID);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " in production is not possible.";
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " in production is not possible.";
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11134;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HeatDeleteError( sEventLogMessage &EventLogMessage, const char * CustHeatID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11134;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Deletion of Heat ";
  EventLogMessage.messageText2 = "Deletion of Heat ";
  char mstring0[64];
  sprintf( mstring0,"%s ",CustHeatID);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " in production is not possible.";
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " in production is not possible.";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HandleHeatReport( const char * ReportReceiver,const char * CustHeatID,const char * CustTreatID,const char * Plant)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Handle heat report to ";
  EventLogMessage.messageText2 = "Handle heat report to ";
  EventLogMessage.messageText += ReportReceiver;
  EventLogMessage.messageText += " Heat ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " Treat ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText2 += ReportReceiver;
  EventLogMessage.messageText2 += " Heat ";
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " Treat ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " Plant ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11135;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HandleHeatReport( sEventLogMessage &EventLogMessage, const char * ReportReceiver,const char * CustHeatID,const char * CustTreatID,const char * Plant)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11135;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Handle heat report to ";
  EventLogMessage.messageText2 = "Handle heat report to ";
  EventLogMessage.messageText += ReportReceiver;
  EventLogMessage.messageText += " Heat ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " Treat ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText2 += ReportReceiver;
  EventLogMessage.messageText2 += " Heat ";
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " Treat ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " Plant ";
  EventLogMessage.messageText2 += Plant;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HandleHeatReportError( const char * ReportReceiver,const char * CustHeatID,const char * CustTreatID,const char * Plant,const char * Reason)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error handle heat report to ";
  EventLogMessage.messageText2 = "Error handle heat report to ";
  EventLogMessage.messageText += ReportReceiver;
  EventLogMessage.messageText += " Heat ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " Treat ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText += " Reason ";
  EventLogMessage.messageText += Reason;
  EventLogMessage.messageText2 += ReportReceiver;
  EventLogMessage.messageText2 += " Heat ";
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " Treat ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " Plant ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.messageText2 += " Reason ";
  EventLogMessage.messageText2 += Reason;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11136;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HandleHeatReportError( sEventLogMessage &EventLogMessage, const char * ReportReceiver,const char * CustHeatID,const char * CustTreatID,const char * Plant,const char * Reason)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11136;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error handle heat report to ";
  EventLogMessage.messageText2 = "Error handle heat report to ";
  EventLogMessage.messageText += ReportReceiver;
  EventLogMessage.messageText += " Heat ";
  EventLogMessage.messageText += CustHeatID;
  EventLogMessage.messageText += " Treat ";
  EventLogMessage.messageText += CustTreatID;
  EventLogMessage.messageText += " Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText += " Reason ";
  EventLogMessage.messageText += Reason;
  EventLogMessage.messageText2 += ReportReceiver;
  EventLogMessage.messageText2 += " Heat ";
  EventLogMessage.messageText2 += CustHeatID;
  EventLogMessage.messageText2 += " Treat ";
  EventLogMessage.messageText2 += CustTreatID;
  EventLogMessage.messageText2 += " Plant ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.messageText2 += " Reason ";
  EventLogMessage.messageText2 += Reason;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ApplicationSystemRestart()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Application System Restart received";
  EventLogMessage.messageText2 = "Application System Restart received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.opAckn = 1;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11137;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ApplicationSystemRestart( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11137;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  if (EventLogMessage.opAckn == 0) EventLogMessage.opAckn = 1;
  EventLogMessage.messageText = "Application System Restart received";
  EventLogMessage.messageText2 = "Application System Restart received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HandleHMIOperatorAcknowledge( const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "";
  EventLogMessage.messageText2 = "";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += Message;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.opAckn = 1;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11138;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HandleHMIOperatorAcknowledge( sEventLogMessage &EventLogMessage, const char * Message)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11138;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  if (EventLogMessage.opAckn == 0) EventLogMessage.opAckn = 1;
  EventLogMessage.messageText = "";
  EventLogMessage.messageText2 = "";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += Message;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ConnectionError( const char * ProcessName,const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Connection Error on ProcessName: ";
  EventLogMessage.messageText2 = "Connection Error on ProcessName: ";
  EventLogMessage.messageText += ProcessName;
  EventLogMessage.messageText += " to ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += ProcessName;
  EventLogMessage.messageText2 += " to ";
  EventLogMessage.messageText2 += Message;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11139;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ConnectionError( sEventLogMessage &EventLogMessage, const char * ProcessName,const char * Message)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11139;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Connection Error on ProcessName: ";
  EventLogMessage.messageText2 = "Connection Error on ProcessName: ";
  EventLogMessage.messageText += ProcessName;
  EventLogMessage.messageText += " to ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += ProcessName;
  EventLogMessage.messageText2 += " to ";
  EventLogMessage.messageText2 += Message;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingRecipe( const char * RecipeName,int RecipeNo,const char * Message)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "System cannot handle recipe ";
  EventLogMessage.messageText2 = "System cannot handle recipe ";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " with no. ";
  char mstring1[64];
  sprintf( mstring1,"%d",RecipeNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " with no. ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += Message;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11140;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingRecipe( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo,const char * Message)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11140;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "System cannot handle recipe ";
  EventLogMessage.messageText2 = "System cannot handle recipe ";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " with no. ";
  char mstring1[64];
  sprintf( mstring1,"%d",RecipeNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += Message;
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " with no. ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += Message;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HandleRestriction( const char * Source,const char * RecipeName,const char * Purpose)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Restriction found for source ";
  EventLogMessage.messageText2 = "Restriction found for source ";
  EventLogMessage.messageText += Source;
  EventLogMessage.messageText += " and Recipe ";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " for Purpose ";
  EventLogMessage.messageText += Purpose;
  EventLogMessage.messageText2 += Source;
  EventLogMessage.messageText2 += " and Recipe ";
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " for Purpose ";
  EventLogMessage.messageText2 += Purpose;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11141;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HandleRestriction( sEventLogMessage &EventLogMessage, const char * Source,const char * RecipeName,const char * Purpose)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11141;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Restriction found for source ";
  EventLogMessage.messageText2 = "Restriction found for source ";
  EventLogMessage.messageText += Source;
  EventLogMessage.messageText += " and Recipe ";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " for Purpose ";
  EventLogMessage.messageText += Purpose;
  EventLogMessage.messageText2 += Source;
  EventLogMessage.messageText2 += " and Recipe ";
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " for Purpose ";
  EventLogMessage.messageText2 += Purpose;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HandleGeneratedSampleId( const char * SampleId)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Sample Id generated ";
  EventLogMessage.messageText2 = "Sample Id generated ";
  EventLogMessage.messageText += SampleId;
  EventLogMessage.messageText2 += SampleId;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11142;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HandleGeneratedSampleId( sEventLogMessage &EventLogMessage, const char * SampleId)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11142;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Sample Id generated ";
  EventLogMessage.messageText2 = "Sample Id generated ";
  EventLogMessage.messageText += SampleId;
  EventLogMessage.messageText2 += SampleId;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HandleSubmittedSampleId( const char * SampleId)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Sample Id submitted ";
  EventLogMessage.messageText2 = "Sample Id submitted ";
  EventLogMessage.messageText += SampleId;
  EventLogMessage.messageText2 += SampleId;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11143;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_HandleSubmittedSampleId( sEventLogMessage &EventLogMessage, const char * SampleId)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11143;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Sample Id submitted ";
  EventLogMessage.messageText2 = "Sample Id submitted ";
  EventLogMessage.messageText += SampleId;
  EventLogMessage.messageText2 += SampleId;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingRestriction( const char * RestrictionName,const char * Plant,int Practice,int TreatModeNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "System cannot find restriction ";
  EventLogMessage.messageText2 = "System cannot find restriction ";
  EventLogMessage.messageText += RestrictionName;
  EventLogMessage.messageText += " for ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText += " with practice ";
  char mstring2[64];
  sprintf( mstring2,"%d",Practice);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText += " and treatmentmode ";
  char mstring3[64];
  sprintf( mstring3,"%d",TreatModeNo);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText2 += RestrictionName;
  EventLogMessage.messageText2 += " for ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.messageText2 += " with practice ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.messageText2 += " and treatmentmode ";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11144;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorHandlingRestriction( sEventLogMessage &EventLogMessage, const char * RestrictionName,const char * Plant,int Practice,int TreatModeNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11144;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "System cannot find restriction ";
  EventLogMessage.messageText2 = "System cannot find restriction ";
  EventLogMessage.messageText += RestrictionName;
  EventLogMessage.messageText += " for ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText += " with practice ";
  char mstring2[64];
  sprintf( mstring2,"%d",Practice);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText += " and treatmentmode ";
  char mstring3[64];
  sprintf( mstring3,"%d",TreatModeNo);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText2 += RestrictionName;
  EventLogMessage.messageText2 += " for ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.messageText2 += " with practice ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.messageText2 += " and treatmentmode ";
  EventLogMessage.messageText2 += mstring3;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorLadleIdGeneration( const char * Function,const char * LadleType,int LadleNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error on ladle id generation at ";
  EventLogMessage.messageText2 = "Error on ladle id generation at ";
  EventLogMessage.messageText += Function;
  EventLogMessage.messageText += " for type ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " and number ";
  char mstring2[64];
  sprintf( mstring2,"%d",LadleNo);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += Function;
  EventLogMessage.messageText2 += " for type ";
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " and number ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11145;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorLadleIdGeneration( sEventLogMessage &EventLogMessage, const char * Function,const char * LadleType,int LadleNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11145;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error on ladle id generation at ";
  EventLogMessage.messageText2 = "Error on ladle id generation at ";
  EventLogMessage.messageText += Function;
  EventLogMessage.messageText += " for type ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " and number ";
  char mstring2[64];
  sprintf( mstring2,"%d",LadleNo);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += Function;
  EventLogMessage.messageText2 += " for type ";
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " and number ";
  EventLogMessage.messageText2 += mstring2;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorLadleIdGeneration( const char * Function,const char * LadleId)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error on ladle id generation at ";
  EventLogMessage.messageText2 = "Error on ladle id generation at ";
  EventLogMessage.messageText += Function;
  EventLogMessage.messageText += " for ladle id ";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText2 += Function;
  EventLogMessage.messageText2 += " for ladle id ";
  EventLogMessage.messageText2 += LadleId;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11146;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorLadleIdGeneration( sEventLogMessage &EventLogMessage, const char * Function,const char * LadleId)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11146;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error on ladle id generation at ";
  EventLogMessage.messageText2 = "Error on ladle id generation at ";
  EventLogMessage.messageText += Function;
  EventLogMessage.messageText += " for ladle id ";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText2 += Function;
  EventLogMessage.messageText2 += " for ladle id ";
  EventLogMessage.messageText2 += LadleId;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_CreatePretreatmentData( const char * HeatID,const char * TreatID,const char * Plant)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "New pretreatment data created for Heat ";
  EventLogMessage.messageText2 = "New pretreatment data created for Heat ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " Treat ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " Treat ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " Plant ";
  EventLogMessage.messageText2 += Plant;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11147;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_CreatePretreatmentData( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * Plant)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11147;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "New pretreatment data created for Heat ";
  EventLogMessage.messageText2 = "New pretreatment data created for Heat ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " Treat ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " Plant ";
  EventLogMessage.messageText += Plant;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " Treat ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " Plant ";
  EventLogMessage.messageText2 += Plant;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ProcessMonitorSwitchOffCompMode( const char * PRODUCT,const char * PLANT)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "The process monitor switched off the computer mode for ";
  EventLogMessage.messageText2 = "The process monitor switched off the computer mode for ";
  EventLogMessage.messageText += PRODUCT;
  EventLogMessage.messageText += " at ";
  EventLogMessage.messageText += PLANT;
  EventLogMessage.messageText += "!";
  EventLogMessage.messageText2 += PRODUCT;
  EventLogMessage.messageText2 += " at ";
  EventLogMessage.messageText2 += PLANT;
  EventLogMessage.messageText2 += "!";
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.opAckn = 1;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 11148;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ProcessMonitorSwitchOffCompMode( sEventLogMessage &EventLogMessage, const char * PRODUCT,const char * PLANT)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11148;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  if (EventLogMessage.opAckn == 0) EventLogMessage.opAckn = 1;
  EventLogMessage.messageText = "The process monitor switched off the computer mode for ";
  EventLogMessage.messageText2 = "The process monitor switched off the computer mode for ";
  EventLogMessage.messageText += PRODUCT;
  EventLogMessage.messageText += " at ";
  EventLogMessage.messageText += PLANT;
  EventLogMessage.messageText += "!";
  EventLogMessage.messageText2 += PRODUCT;
  EventLogMessage.messageText2 += " at ";
  EventLogMessage.messageText2 += PLANT;
  EventLogMessage.messageText2 += "!";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_RecipeConversion( int OldRecipeNo,int NewRecipeNo,const char * Recipe)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "RecipeNo changed from ";
  EventLogMessage.messageText2 = "RecipeNo changed from ";
  char mstring0[64];
  sprintf( mstring0,"%d",OldRecipeNo);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " to ";
  char mstring1[64];
  sprintf( mstring1,"%d",NewRecipeNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " for recipe ";
  EventLogMessage.messageText += Recipe;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " to ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " for recipe ";
  EventLogMessage.messageText2 += Recipe;
  EventLogMessage.messageText2 += ".";
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11149;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_RecipeConversion( sEventLogMessage &EventLogMessage, int OldRecipeNo,int NewRecipeNo,const char * Recipe)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11149;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "RecipeNo changed from ";
  EventLogMessage.messageText2 = "RecipeNo changed from ";
  char mstring0[64];
  sprintf( mstring0,"%d",OldRecipeNo);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " to ";
  char mstring1[64];
  sprintf( mstring1,"%d",NewRecipeNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " for recipe ";
  EventLogMessage.messageText += Recipe;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " to ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " for recipe ";
  EventLogMessage.messageText2 += Recipe;
  EventLogMessage.messageText2 += ".";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_MaterialCodeDefinitionInserted( const char * MatCode)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Inserted new material code definition for ";
  EventLogMessage.messageText2 = "Inserted new material code definition for ";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText2 += MatCode;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11150;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_MaterialCodeDefinitionInserted( sEventLogMessage &EventLogMessage, const char * MatCode)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11150;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Inserted new material code definition for ";
  EventLogMessage.messageText2 = "Inserted new material code definition for ";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText2 += MatCode;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_MaterialCodeDefinitionAltered( const char * MatCode)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Altered material code definition for ";
  EventLogMessage.messageText2 = "Altered material code definition for ";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText2 += MatCode;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11151;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_MaterialCodeDefinitionAltered( sEventLogMessage &EventLogMessage, const char * MatCode)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11151;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Altered material code definition for ";
  EventLogMessage.messageText2 = "Altered material code definition for ";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText2 += MatCode;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_MaterialCodeDefinitionDeleted( const char * MatCode)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Deleted material code definition for ";
  EventLogMessage.messageText2 = "Deleted material code definition for ";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText2 += MatCode;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11152;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_MaterialCodeDefinitionDeleted( sEventLogMessage &EventLogMessage, const char * MatCode)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11152;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Deleted material code definition for ";
  EventLogMessage.messageText2 = "Deleted material code definition for ";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText2 += MatCode;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_RecipeWithoutMaterials( const char * RecipeName,int RecipeNo,int RecipeStatus)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "No materials received for recipe ";
  EventLogMessage.messageText2 = "No materials received for recipe ";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += "  ";
  char mstring1[64];
  sprintf( mstring1,"%d",RecipeNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " with status ";
  char mstring2[64];
  sprintf( mstring2,"%d",RecipeStatus);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += "  ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " with status ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11153;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_RecipeWithoutMaterials( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo,int RecipeStatus)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11153;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "No materials received for recipe ";
  EventLogMessage.messageText2 = "No materials received for recipe ";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += "  ";
  char mstring1[64];
  sprintf( mstring1,"%d",RecipeNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " with status ";
  char mstring2[64];
  sprintf( mstring2,"%d",RecipeStatus);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += "  ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " with status ";
  EventLogMessage.messageText2 += mstring2;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_CreateHotMetalCounter( int HMCounter,const char * HMLadleID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "New hot metal counter ";
  EventLogMessage.messageText2 = "New hot metal counter ";
  char mstring0[64];
  sprintf( mstring0,"%d",HMCounter);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " created for lalde ";
  EventLogMessage.messageText += HMLadleID;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " created for lalde ";
  EventLogMessage.messageText2 += HMLadleID;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11154;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_CreateHotMetalCounter( sEventLogMessage &EventLogMessage, int HMCounter,const char * HMLadleID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11154;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "New hot metal counter ";
  EventLogMessage.messageText2 = "New hot metal counter ";
  char mstring0[64];
  sprintf( mstring0,"%d",HMCounter);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " created for lalde ";
  EventLogMessage.messageText += HMLadleID;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " created for lalde ";
  EventLogMessage.messageText2 += HMLadleID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_EmptyHotMetalLadleDischarged( const char * HMLadleID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Discharge empty hot metal ladle ";
  EventLogMessage.messageText2 = "Discharge empty hot metal ladle ";
  EventLogMessage.messageText += HMLadleID;
  EventLogMessage.messageText2 += HMLadleID;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 11155;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_EmptyHotMetalLadleDischarged( sEventLogMessage &EventLogMessage, const char * HMLadleID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11155;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Discharge empty hot metal ladle ";
  EventLogMessage.messageText2 = "Discharge empty hot metal ladle ";
  EventLogMessage.messageText += HMLadleID;
  EventLogMessage.messageText2 += HMLadleID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_EmptyPurpose( const char * PURP_CODE,int UNITGROUPNO)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Purpose ";
  EventLogMessage.messageText2 = "Purpose ";
  EventLogMessage.messageText += PURP_CODE;
  EventLogMessage.messageText += " for UnitGroupNo ";
  char mstring1[64];
  sprintf( mstring1,"%d",UNITGROUPNO);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " contains no any materials";
  EventLogMessage.messageText2 += PURP_CODE;
  EventLogMessage.messageText2 += " for UnitGroupNo ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " contains no any materials";
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11156;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_EmptyPurpose( sEventLogMessage &EventLogMessage, const char * PURP_CODE,int UNITGROUPNO)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11156;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Purpose ";
  EventLogMessage.messageText2 = "Purpose ";
  EventLogMessage.messageText += PURP_CODE;
  EventLogMessage.messageText += " for UnitGroupNo ";
  char mstring1[64];
  sprintf( mstring1,"%d",UNITGROUPNO);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " contains no any materials";
  EventLogMessage.messageText2 += PURP_CODE;
  EventLogMessage.messageText2 += " for UnitGroupNo ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " contains no any materials";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorEquipmentIdentification( const char * EQUIP_TYPE_PARENT,const char * STRUCT_SUB_ID_PARENT,const char * EQUIP_TYPE,const char * STRUCT_SUB_ID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error for identification of equipment for Parenttype ";
  EventLogMessage.messageText2 = "Error for identification of equipment for Parenttype ";
  EventLogMessage.messageText += EQUIP_TYPE_PARENT;
  EventLogMessage.messageText += " ParentId ";
  EventLogMessage.messageText += STRUCT_SUB_ID_PARENT;
  EventLogMessage.messageText += " and Subtype ";
  EventLogMessage.messageText += EQUIP_TYPE;
  EventLogMessage.messageText += " and SubId ";
  EventLogMessage.messageText += STRUCT_SUB_ID;
  EventLogMessage.messageText2 += EQUIP_TYPE_PARENT;
  EventLogMessage.messageText2 += " ParentId ";
  EventLogMessage.messageText2 += STRUCT_SUB_ID_PARENT;
  EventLogMessage.messageText2 += " and Subtype ";
  EventLogMessage.messageText2 += EQUIP_TYPE;
  EventLogMessage.messageText2 += " and SubId ";
  EventLogMessage.messageText2 += STRUCT_SUB_ID;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11157;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorEquipmentIdentification( sEventLogMessage &EventLogMessage, const char * EQUIP_TYPE_PARENT,const char * STRUCT_SUB_ID_PARENT,const char * EQUIP_TYPE,const char * STRUCT_SUB_ID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11157;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error for identification of equipment for Parenttype ";
  EventLogMessage.messageText2 = "Error for identification of equipment for Parenttype ";
  EventLogMessage.messageText += EQUIP_TYPE_PARENT;
  EventLogMessage.messageText += " ParentId ";
  EventLogMessage.messageText += STRUCT_SUB_ID_PARENT;
  EventLogMessage.messageText += " and Subtype ";
  EventLogMessage.messageText += EQUIP_TYPE;
  EventLogMessage.messageText += " and SubId ";
  EventLogMessage.messageText += STRUCT_SUB_ID;
  EventLogMessage.messageText2 += EQUIP_TYPE_PARENT;
  EventLogMessage.messageText2 += " ParentId ";
  EventLogMessage.messageText2 += STRUCT_SUB_ID_PARENT;
  EventLogMessage.messageText2 += " and Subtype ";
  EventLogMessage.messageText2 += EQUIP_TYPE;
  EventLogMessage.messageText2 += " and SubId ";
  EventLogMessage.messageText2 += STRUCT_SUB_ID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorEquipmentIdentification( const char * EQUIP_TYPE,const char * STRUCT_SUB_ID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error for identification of equipment for Type ";
  EventLogMessage.messageText2 = "Error for identification of equipment for Type ";
  EventLogMessage.messageText += EQUIP_TYPE;
  EventLogMessage.messageText += " and Id ";
  EventLogMessage.messageText += STRUCT_SUB_ID;
  EventLogMessage.messageText2 += EQUIP_TYPE;
  EventLogMessage.messageText2 += " and Id ";
  EventLogMessage.messageText2 += STRUCT_SUB_ID;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11158;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorEquipmentIdentification( sEventLogMessage &EventLogMessage, const char * EQUIP_TYPE,const char * STRUCT_SUB_ID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11158;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error for identification of equipment for Type ";
  EventLogMessage.messageText2 = "Error for identification of equipment for Type ";
  EventLogMessage.messageText += EQUIP_TYPE;
  EventLogMessage.messageText += " and Id ";
  EventLogMessage.messageText += STRUCT_SUB_ID;
  EventLogMessage.messageText2 += EQUIP_TYPE;
  EventLogMessage.messageText2 += " and Id ";
  EventLogMessage.messageText2 += STRUCT_SUB_ID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorEquipmentTypeIdentification( const char * EQUIP_TYPE,const char * ID,const char * PARENT_ID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error for identification of equipment for Type ";
  EventLogMessage.messageText2 = "Error for identification of equipment for Type ";
  EventLogMessage.messageText += EQUIP_TYPE;
  EventLogMessage.messageText += " and Id ";
  EventLogMessage.messageText += ID;
  EventLogMessage.messageText += " and ParentId ";
  EventLogMessage.messageText += PARENT_ID;
  EventLogMessage.messageText2 += EQUIP_TYPE;
  EventLogMessage.messageText2 += " and Id ";
  EventLogMessage.messageText2 += ID;
  EventLogMessage.messageText2 += " and ParentId ";
  EventLogMessage.messageText2 += PARENT_ID;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11159;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorEquipmentTypeIdentification( sEventLogMessage &EventLogMessage, const char * EQUIP_TYPE,const char * ID,const char * PARENT_ID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11159;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error for identification of equipment for Type ";
  EventLogMessage.messageText2 = "Error for identification of equipment for Type ";
  EventLogMessage.messageText += EQUIP_TYPE;
  EventLogMessage.messageText += " and Id ";
  EventLogMessage.messageText += ID;
  EventLogMessage.messageText += " and ParentId ";
  EventLogMessage.messageText += PARENT_ID;
  EventLogMessage.messageText2 += EQUIP_TYPE;
  EventLogMessage.messageText2 += " and Id ";
  EventLogMessage.messageText2 += ID;
  EventLogMessage.messageText2 += " and ParentId ";
  EventLogMessage.messageText2 += PARENT_ID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorEquipmentTypeIdentification( const char * EQUIP_TYPE,const char * ID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error for identification of equipment for Type ";
  EventLogMessage.messageText2 = "Error for identification of equipment for Type ";
  EventLogMessage.messageText += EQUIP_TYPE;
  EventLogMessage.messageText += " and Id ";
  EventLogMessage.messageText += ID;
  EventLogMessage.messageText2 += EQUIP_TYPE;
  EventLogMessage.messageText2 += " and Id ";
  EventLogMessage.messageText2 += ID;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11160;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorEquipmentTypeIdentification( sEventLogMessage &EventLogMessage, const char * EQUIP_TYPE,const char * ID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11160;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error for identification of equipment for Type ";
  EventLogMessage.messageText2 = "Error for identification of equipment for Type ";
  EventLogMessage.messageText += EQUIP_TYPE;
  EventLogMessage.messageText += " and Id ";
  EventLogMessage.messageText += ID;
  EventLogMessage.messageText2 += EQUIP_TYPE;
  EventLogMessage.messageText2 += " and Id ";
  EventLogMessage.messageText2 += ID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorEquipmentMountIdentification( const char * EQUIP_TYPE,const char * ID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error for identification of mounted equipment for Type ";
  EventLogMessage.messageText2 = "Error for identification of mounted equipment for Type ";
  EventLogMessage.messageText += EQUIP_TYPE;
  EventLogMessage.messageText += " and Id ";
  EventLogMessage.messageText += ID;
  EventLogMessage.messageText2 += EQUIP_TYPE;
  EventLogMessage.messageText2 += " and Id ";
  EventLogMessage.messageText2 += ID;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11161;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ErrorEquipmentMountIdentification( sEventLogMessage &EventLogMessage, const char * EQUIP_TYPE,const char * ID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11161;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Error for identification of mounted equipment for Type ";
  EventLogMessage.messageText2 = "Error for identification of mounted equipment for Type ";
  EventLogMessage.messageText += EQUIP_TYPE;
  EventLogMessage.messageText += " and Id ";
  EventLogMessage.messageText += ID;
  EventLogMessage.messageText2 += EQUIP_TYPE;
  EventLogMessage.messageText2 += " and Id ";
  EventLogMessage.messageText2 += ID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_NextHeatNotReadyForAnnounce()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Next heat not ready for announcement.";
  EventLogMessage.messageText2 = "Next heat not ready for announcement.";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11162;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_NextHeatNotReadyForAnnounce( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11162;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Next heat not ready for announcement.";
  EventLogMessage.messageText2 = "Next heat not ready for announcement.";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_NoHeatForAutoAnnounce()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "No heats in heat schedule for auto announcement.";
  EventLogMessage.messageText2 = "No heats in heat schedule for auto announcement.";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11163;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_NoHeatForAutoAnnounce( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11163;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "No heats in heat schedule for auto announcement.";
  EventLogMessage.messageText2 = "No heats in heat schedule for auto announcement.";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_UseDefaultLadle( const char * LadleType,int LadleNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "No ladle available. Using default ladle ";
  EventLogMessage.messageText2 = "No ladle available. Using default ladle ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11164;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_UseDefaultLadle( sEventLogMessage &EventLogMessage, const char * LadleType,int LadleNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11164;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "No ladle available. Using default ladle ";
  EventLogMessage.messageText2 = "No ladle available. Using default ladle ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += mstring1;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ScrapContainerDataUpdate( const char * ContainerType,int ContainerNo,const char * MaterialData)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "New scrap container data ";
  EventLogMessage.messageText2 = "New scrap container data ";
  EventLogMessage.messageText += ContainerType;
  EventLogMessage.messageText += " ";
  char mstring1[64];
  sprintf( mstring1,"%d",ContainerNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Materials ";
  EventLogMessage.messageText += MaterialData;
  EventLogMessage.messageText2 += ContainerType;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Materials ";
  EventLogMessage.messageText2 += MaterialData;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11165;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ScrapContainerDataUpdate( sEventLogMessage &EventLogMessage, const char * ContainerType,int ContainerNo,const char * MaterialData)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11165;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "New scrap container data ";
  EventLogMessage.messageText2 = "New scrap container data ";
  EventLogMessage.messageText += ContainerType;
  EventLogMessage.messageText += " ";
  char mstring1[64];
  sprintf( mstring1,"%d",ContainerNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Materials ";
  EventLogMessage.messageText += MaterialData;
  EventLogMessage.messageText2 += ContainerType;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Materials ";
  EventLogMessage.messageText2 += MaterialData;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ChangeLadleData( const char * PrevLadleType,int PrevLadleNo,const char * ActLadleType,int ActLadleNo,int Content)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change ladle data from prev ladle ";
  EventLogMessage.messageText2 = "Change ladle data from prev ladle ";
  EventLogMessage.messageText += PrevLadleType;
  EventLogMessage.messageText += "";
  char mstring1[64];
  sprintf( mstring1,"%d",PrevLadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " to act ladle ";
  EventLogMessage.messageText += ActLadleType;
  EventLogMessage.messageText += "";
  char mstring3[64];
  sprintf( mstring3,"%d",ActLadleNo);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText += " with content: ";
  char mstring4[64];
  sprintf( mstring4,"%d",Content);
  EventLogMessage.messageText += mstring4;
  EventLogMessage.messageText2 += PrevLadleType;
  EventLogMessage.messageText2 += "";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " to act ladle ";
  EventLogMessage.messageText2 += ActLadleType;
  EventLogMessage.messageText2 += "";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.messageText2 += " with content: ";
  EventLogMessage.messageText2 += mstring4;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11166;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_ChangeLadleData( sEventLogMessage &EventLogMessage, const char * PrevLadleType,int PrevLadleNo,const char * ActLadleType,int ActLadleNo,int Content)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11166;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Change ladle data from prev ladle ";
  EventLogMessage.messageText2 = "Change ladle data from prev ladle ";
  EventLogMessage.messageText += PrevLadleType;
  EventLogMessage.messageText += "";
  char mstring1[64];
  sprintf( mstring1,"%d",PrevLadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " to act ladle ";
  EventLogMessage.messageText += ActLadleType;
  EventLogMessage.messageText += "";
  char mstring3[64];
  sprintf( mstring3,"%d",ActLadleNo);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText += " with content: ";
  char mstring4[64];
  sprintf( mstring4,"%d",Content);
  EventLogMessage.messageText += mstring4;
  EventLogMessage.messageText2 += PrevLadleType;
  EventLogMessage.messageText2 += "";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " to act ladle ";
  EventLogMessage.messageText2 += ActLadleType;
  EventLogMessage.messageText2 += "";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.messageText2 += " with content: ";
  EventLogMessage.messageText2 += mstring4;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_RecipeConversionFailure( int L1RecNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Recipe conversion failed for L1No: ";
  EventLogMessage.messageText2 = "Recipe conversion failed for L1No: ";
  char mstring0[64];
  sprintf( mstring0,"%d",L1RecNo);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11167;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_RecipeConversionFailure( sEventLogMessage &EventLogMessage, int L1RecNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11167;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Recipe conversion failed for L1No: ";
  EventLogMessage.messageText2 = "Recipe conversion failed for L1No: ";
  char mstring0[64];
  sprintf( mstring0,"%d",L1RecNo);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText2 += mstring0;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_RecipeConversionFailure( const char * RecipeName,int RecipeNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Recipe conversion failed for RecipeName: ";
  EventLogMessage.messageText2 = "Recipe conversion failed for RecipeName: ";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " RecipeNo: ";
  char mstring1[64];
  sprintf( mstring1,"%d",RecipeNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " RecipeNo: ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11168;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_RecipeConversionFailure( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11168;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Recipe conversion failed for RecipeName: ";
  EventLogMessage.messageText2 = "Recipe conversion failed for RecipeName: ";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " RecipeNo: ";
  char mstring1[64];
  sprintf( mstring1,"%d",RecipeNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " RecipeNo: ";
  EventLogMessage.messageText2 += mstring1;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_UnknownAnalysisElement( const char * ElemName,double AnlVal)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Unknown element ";
  EventLogMessage.messageText2 = "Unknown element ";
  EventLogMessage.messageText += ElemName;
  EventLogMessage.messageText += " with concentration ";
  char mstring1[64];
  sprintf( mstring1,"%f",AnlVal);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " found in analysis";
  EventLogMessage.messageText2 += ElemName;
  EventLogMessage.messageText2 += " with concentration ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " found in analysis";
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11169;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_UnknownAnalysisElement( sEventLogMessage &EventLogMessage, const char * ElemName,double AnlVal)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11169;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::AllBotLines;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Unknown element ";
  EventLogMessage.messageText2 = "Unknown element ";
  EventLogMessage.messageText += ElemName;
  EventLogMessage.messageText += " with concentration ";
  char mstring1[64];
  sprintf( mstring1,"%f",AnlVal);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " found in analysis";
  EventLogMessage.messageText2 += ElemName;
  EventLogMessage.messageText2 += " with concentration ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " found in analysis";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_MinChargeableWeightViolated( const char * RecipeName,const char * MatCode,double Weight,double MinWeight)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Minimal chargeable weight viloted for recipe ";
  EventLogMessage.messageText2 = "Minimal chargeable weight viloted for recipe ";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " and material ";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText += " with weight ";
  char mstring2[64];
  sprintf( mstring2,"%f",Weight);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText += " for minmal weight ";
  char mstring3[64];
  sprintf( mstring3,"%f",MinWeight);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " and material ";
  EventLogMessage.messageText2 += MatCode;
  EventLogMessage.messageText2 += " with weight ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.messageText2 += " for minmal weight ";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 0;
  EventLogMessage.eventId = 11170;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogFrame::EL_MinChargeableWeightViolated( sEventLogMessage &EventLogMessage, const char * RecipeName,const char * MatCode,double Weight,double MinWeight)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 11170;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 0;
  EventLogMessage.messageText = "Minimal chargeable weight viloted for recipe ";
  EventLogMessage.messageText2 = "Minimal chargeable weight viloted for recipe ";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " and material ";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText += " with weight ";
  char mstring2[64];
  sprintf( mstring2,"%f",Weight);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText += " for minmal weight ";
  char mstring3[64];
  sprintf( mstring3,"%f",MinWeight);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " and material ";
  EventLogMessage.messageText2 += MatCode;
  EventLogMessage.messageText2 += " with weight ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.messageText2 += " for minmal weight ";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.messageText2 += " ";
  return (lRetValue = sendMessage(EventLogMessage));
}
