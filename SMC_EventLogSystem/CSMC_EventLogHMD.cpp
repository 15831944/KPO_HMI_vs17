// this is a generated file: do not edit
// use CBSEventLogCodeGenerator to generate it out of excel textfile
#define MAX_MESSAGE_LEN 256 // 255 characters and NULL-Termination!!! DB limit

#include <string>

#include "CSMC_EventLogHMD.h"
#include <CBS_Tasks/cCBS_Time.h>

CSMC_EventLogHMD::CSMC_EventLogHMD(std::string sProcName, std::string sServiceName, std::string sContextName )
: CSMC_EventLogFrame(sProcName,sServiceName,sContextName)
{
}
CSMC_EventLogHMD::~CSMC_EventLogHMD()
{
}

long CSMC_EventLogHMD::EL_BathLevelMeasurement( double BachLevel)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Bath Level Measurement: BathLevel ";
  EventLogMessage.messageText2 = "Bath Level Measurement: BathLevel ";
  char mstring0[64];
  sprintf( mstring0,"%f",BachLevel);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16001;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_BathLevelMeasurement( sEventLogMessage &EventLogMessage, double BachLevel)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16001;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Bath Level Measurement: BathLevel ";
  EventLogMessage.messageText2 = "Bath Level Measurement: BathLevel ";
  char mstring0[64];
  sprintf( mstring0,"%f",BachLevel);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText2 += mstring0;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_ChangeAimData()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Aim Data received";
  EventLogMessage.messageText2 = "Change Aim Data received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16002;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_ChangeAimData( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16002;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Aim Data received";
  EventLogMessage.messageText2 = "Change Aim Data received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_ChangeAimDepartureTime( const char * AimDepTime)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Aim Departure Time received AimDepTime ";
  EventLogMessage.messageText2 = "Change Aim Departure Time received AimDepTime ";
  EventLogMessage.messageText += AimDepTime;
  EventLogMessage.messageText2 += AimDepTime;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16003;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_ChangeAimDepartureTime( sEventLogMessage &EventLogMessage, const char * AimDepTime)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16003;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Aim Departure Time received AimDepTime ";
  EventLogMessage.messageText2 = "Change Aim Departure Time received AimDepTime ";
  EventLogMessage.messageText += AimDepTime;
  EventLogMessage.messageText2 += AimDepTime;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_ChangePhysicalMatAvailibility( const char * MatCode)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change physical material availability Material:";
  EventLogMessage.messageText2 = "Change physical material availability Material:";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText2 += MatCode;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16004;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_ChangePhysicalMatAvailibility( sEventLogMessage &EventLogMessage, const char * MatCode)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16004;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change physical material availability Material:";
  EventLogMessage.messageText2 = "Change physical material availability Material:";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText2 += MatCode;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_ComputerModeOff()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Computer Mode Off received";
  EventLogMessage.messageText2 = "Computer Mode Off received";
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16005;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_ComputerModeOff( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16005;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Computer Mode Off received";
  EventLogMessage.messageText2 = "Computer Mode Off received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_ComputerModeOn()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Computer Mode On received";
  EventLogMessage.messageText2 = "Computer Mode On received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16006;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_ComputerModeOn( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16006;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Computer Mode On received";
  EventLogMessage.messageText2 = "Computer Mode On received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_CreateTreatmentID()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Create Treatment ID received";
  EventLogMessage.messageText2 = "Create Treatment ID received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16007;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_CreateTreatmentID( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16007;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Create Treatment ID received";
  EventLogMessage.messageText2 = "Create Treatment ID received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_CyclicMeasurement()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Cyclic Measurement";
  EventLogMessage.messageText2 = "Cyclic Measurement";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16008;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_CyclicMeasurement( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16008;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Cyclic Measurement";
  EventLogMessage.messageText2 = "Cyclic Measurement";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_DelayStatus( const char * DelayPlant,const char * DelayCode,const char * DelayStartDate,const char * DelayEndDate,const char * DelayDescription)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Delay Status  DelayPlant:";
  EventLogMessage.messageText2 = "Delay Status  DelayPlant:";
  EventLogMessage.messageText += DelayPlant;
  EventLogMessage.messageText += " DelayCode:";
  EventLogMessage.messageText += DelayCode;
  EventLogMessage.messageText += " DelayStartDate:";
  EventLogMessage.messageText += DelayStartDate;
  EventLogMessage.messageText += " DelayEndDate:";
  EventLogMessage.messageText += DelayEndDate;
  EventLogMessage.messageText += " DelayDescription:";
  EventLogMessage.messageText += DelayDescription;
  EventLogMessage.messageText2 += DelayPlant;
  EventLogMessage.messageText2 += " DelayCode:";
  EventLogMessage.messageText2 += DelayCode;
  EventLogMessage.messageText2 += " DelayStartDate:";
  EventLogMessage.messageText2 += DelayStartDate;
  EventLogMessage.messageText2 += " DelayEndDate:";
  EventLogMessage.messageText2 += DelayEndDate;
  EventLogMessage.messageText2 += " DelayDescription:";
  EventLogMessage.messageText2 += DelayDescription;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16009;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_DelayStatus( sEventLogMessage &EventLogMessage, const char * DelayPlant,const char * DelayCode,const char * DelayStartDate,const char * DelayEndDate,const char * DelayDescription)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16009;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Delay Status  DelayPlant:";
  EventLogMessage.messageText2 = "Delay Status  DelayPlant:";
  EventLogMessage.messageText += DelayPlant;
  EventLogMessage.messageText += " DelayCode:";
  EventLogMessage.messageText += DelayCode;
  EventLogMessage.messageText += " DelayStartDate:";
  EventLogMessage.messageText += DelayStartDate;
  EventLogMessage.messageText += " DelayEndDate:";
  EventLogMessage.messageText += DelayEndDate;
  EventLogMessage.messageText += " DelayDescription:";
  EventLogMessage.messageText += DelayDescription;
  EventLogMessage.messageText2 += DelayPlant;
  EventLogMessage.messageText2 += " DelayCode:";
  EventLogMessage.messageText2 += DelayCode;
  EventLogMessage.messageText2 += " DelayStartDate:";
  EventLogMessage.messageText2 += DelayStartDate;
  EventLogMessage.messageText2 += " DelayEndDate:";
  EventLogMessage.messageText2 += DelayEndDate;
  EventLogMessage.messageText2 += " DelayDescription:";
  EventLogMessage.messageText2 += DelayDescription;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_DeslaggingEnd( const char * DeslagEndTime)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Deslagging End DeslagEndTime:";
  EventLogMessage.messageText2 = "Deslagging End DeslagEndTime:";
  EventLogMessage.messageText += DeslagEndTime;
  EventLogMessage.messageText2 += DeslagEndTime;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16010;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_DeslaggingEnd( sEventLogMessage &EventLogMessage, const char * DeslagEndTime)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16010;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Deslagging End DeslagEndTime:";
  EventLogMessage.messageText2 = "Deslagging End DeslagEndTime:";
  EventLogMessage.messageText += DeslagEndTime;
  EventLogMessage.messageText2 += DeslagEndTime;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_DeslaggingStart( const char * DeslagStartTime,const char * DeslaggingStatus)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Deslagging Start DeslagStartTime:";
  EventLogMessage.messageText2 = "Deslagging Start DeslagStartTime:";
  EventLogMessage.messageText += DeslagStartTime;
  EventLogMessage.messageText += " DeslaggingStatus:";
  EventLogMessage.messageText += DeslaggingStatus;
  EventLogMessage.messageText2 += DeslagStartTime;
  EventLogMessage.messageText2 += " DeslaggingStatus:";
  EventLogMessage.messageText2 += DeslaggingStatus;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16011;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_DeslaggingStart( sEventLogMessage &EventLogMessage, const char * DeslagStartTime,const char * DeslaggingStatus)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16011;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Deslagging Start DeslagStartTime:";
  EventLogMessage.messageText2 = "Deslagging Start DeslagStartTime:";
  EventLogMessage.messageText += DeslagStartTime;
  EventLogMessage.messageText += " DeslaggingStatus:";
  EventLogMessage.messageText += DeslaggingStatus;
  EventLogMessage.messageText2 += DeslagStartTime;
  EventLogMessage.messageText2 += " DeslaggingStatus:";
  EventLogMessage.messageText2 += DeslaggingStatus;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HandleUpdatePurpose()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Update Purpose ";
  EventLogMessage.messageText2 = "Update Purpose ";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16012;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HandleUpdatePurpose( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16012;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Update Purpose ";
  EventLogMessage.messageText2 = "Update Purpose ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HeatAnnouncement( const char * HeatID,const char * TreatID,const char * PlantID,const char * LadleId)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Heat Announcement of ";
  EventLogMessage.messageText2 = "Heat Announcement of ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at Plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText += " Ladle:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at Plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.messageText2 += " Ladle:";
  EventLogMessage.messageText2 += LadleId;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16013;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HeatAnnouncement( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID,const char * LadleId)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16013;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Heat Announcement of ";
  EventLogMessage.messageText2 = "Heat Announcement of ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at Plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText += " Ladle:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at Plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.messageText2 += " Ladle:";
  EventLogMessage.messageText2 += LadleId;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HeatAnnouncementOffline( const char * HeatID,const char * TreatID,const char * PlantID,const char * LadleId)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Heat Announcement Offline of ";
  EventLogMessage.messageText2 = "Heat Announcement Offline of ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at Plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText += " Ladle:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at Plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.messageText2 += " Ladle:";
  EventLogMessage.messageText2 += LadleId;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16014;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HeatAnnouncementOffline( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID,const char * LadleId)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16014;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Heat Announcement Offline of ";
  EventLogMessage.messageText2 = "Heat Announcement Offline of ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at Plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText += " Ladle:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at Plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.messageText2 += " Ladle:";
  EventLogMessage.messageText2 += LadleId;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HeatAnnounceStatus( const char * HeatAnnounceStatus,const char * HeatID,const char * TreatID,const char * PlantID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Heat Announce Status HeatAnnounceStatus:";
  EventLogMessage.messageText2 = "Heat Announce Status HeatAnnounceStatus:";
  EventLogMessage.messageText += HeatAnnounceStatus;
  EventLogMessage.messageText += " of ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at Plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += HeatAnnounceStatus;
  EventLogMessage.messageText2 += " of ";
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at Plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16015;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HeatAnnounceStatus( sEventLogMessage &EventLogMessage, const char * HeatAnnounceStatus,const char * HeatID,const char * TreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16015;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Heat Announce Status HeatAnnounceStatus:";
  EventLogMessage.messageText2 = "Heat Announce Status HeatAnnounceStatus:";
  EventLogMessage.messageText += HeatAnnounceStatus;
  EventLogMessage.messageText += " of ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at Plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += HeatAnnounceStatus;
  EventLogMessage.messageText2 += " of ";
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at Plant ";
  EventLogMessage.messageText2 += PlantID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HeatCancellation( const char * HeatID,const char * TreatID,const char * PlantID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Heat Cancellation of ";
  EventLogMessage.messageText2 = "Heat Cancellation of ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at Plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at Plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16016;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HeatCancellation( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16016;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Heat Cancellation of ";
  EventLogMessage.messageText2 = "Heat Cancellation of ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at Plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at Plant ";
  EventLogMessage.messageText2 += PlantID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HeatDeparture( const char * HeatID,const char * TreatID,const char * PlantID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Heat Departure of ";
  EventLogMessage.messageText2 = "Heat Departure of ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at Plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at Plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16017;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HeatDeparture( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16017;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Heat Departure of ";
  EventLogMessage.messageText2 = "Heat Departure of ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at Plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at Plant ";
  EventLogMessage.messageText2 += PlantID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HeatStart( const char * HeatID,const char * TreatID,const char * PlantID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Heat Start of ";
  EventLogMessage.messageText2 = "Heat Start of ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at Plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at Plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16018;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HeatStart( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16018;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Heat Start of ";
  EventLogMessage.messageText2 = "Heat Start of ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at Plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at Plant ";
  EventLogMessage.messageText2 += PlantID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HeatEnd( const char * HeatID,const char * TreatID,const char * PlantID)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Heat End of ";
  EventLogMessage.messageText2 = "Heat End of ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at Plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at Plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16019;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HeatEnd( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16019;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Heat End of ";
  EventLogMessage.messageText2 = "Heat End of ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at Plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at Plant ";
  EventLogMessage.messageText2 += PlantID;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HoodInOperationPos()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Enclosure Hood In Operation Position";
  EventLogMessage.messageText2 = "Enclosure Hood In Operation Position";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16020;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HoodInOperationPos( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16020;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Enclosure Hood In Operation Position";
  EventLogMessage.messageText2 = "Enclosure Hood In Operation Position";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HoodOutOfOperationPos()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Enclosure Hood Out Of Operation Position";
  EventLogMessage.messageText2 = "Enclosure Hood Out Of Operation Position";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16021;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HoodOutOfOperationPos( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16021;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Enclosure Hood Out Of Operation Position";
  EventLogMessage.messageText2 = "Enclosure Hood Out Of Operation Position";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HotMetalAnalysisReceived( const char * SampleCode,long SampleCounterL1)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Hot Metal Analysis Data received SampleCode:";
  EventLogMessage.messageText2 = "Hot Metal Analysis Data received SampleCode:";
  EventLogMessage.messageText += SampleCode;
  EventLogMessage.messageText += " SampleCounterL1:";
  char mstring1[64];
  sprintf( mstring1,"%l",SampleCounterL1);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += SampleCode;
  EventLogMessage.messageText2 += " SampleCounterL1:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16022;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HotMetalAnalysisReceived( sEventLogMessage &EventLogMessage, const char * SampleCode,long SampleCounterL1)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16022;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Hot Metal Analysis Data received SampleCode:";
  EventLogMessage.messageText2 = "Hot Metal Analysis Data received SampleCode:";
  EventLogMessage.messageText += SampleCode;
  EventLogMessage.messageText += " SampleCounterL1:";
  char mstring1[64];
  sprintf( mstring1,"%l",SampleCounterL1);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += SampleCode;
  EventLogMessage.messageText2 += " SampleCounterL1:";
  EventLogMessage.messageText2 += mstring1;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HotMetalSampleTaken( const char * SampleCode,long SampleCounterL1,const char * SampleLocation)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Hot Metal Sample Taken SampleCode:";
  EventLogMessage.messageText2 = "Hot Metal Sample Taken SampleCode:";
  EventLogMessage.messageText += SampleCode;
  EventLogMessage.messageText += " SampleCounterL1:";
  char mstring1[64];
  sprintf( mstring1,"%l",SampleCounterL1);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " SampleLocation:";
  EventLogMessage.messageText += SampleLocation;
  EventLogMessage.messageText2 += SampleCode;
  EventLogMessage.messageText2 += " SampleCounterL1:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " SampleLocation:";
  EventLogMessage.messageText2 += SampleLocation;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16023;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_HotMetalSampleTaken( sEventLogMessage &EventLogMessage, const char * SampleCode,long SampleCounterL1,const char * SampleLocation)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16023;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Hot Metal Sample Taken SampleCode:";
  EventLogMessage.messageText2 = "Hot Metal Sample Taken SampleCode:";
  EventLogMessage.messageText += SampleCode;
  EventLogMessage.messageText += " SampleCounterL1:";
  char mstring1[64];
  sprintf( mstring1,"%l",SampleCounterL1);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " SampleLocation:";
  EventLogMessage.messageText += SampleLocation;
  EventLogMessage.messageText2 += SampleCode;
  EventLogMessage.messageText2 += " SampleCounterL1:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " SampleLocation:";
  EventLogMessage.messageText2 += SampleLocation;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_InjectionLanceBlowingStart()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Powder Blowing Start";
  EventLogMessage.messageText2 = "Powder Blowing Start";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16024;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_InjectionLanceBlowingStart( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16024;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Powder Blowing Start";
  EventLogMessage.messageText2 = "Powder Blowing Start";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_InjectionLanceBlowingStop()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Powder Blowing Stop";
  EventLogMessage.messageText2 = "Powder Blowing Stop";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16025;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_InjectionLanceBlowingStop( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16025;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Powder Blowing Stop";
  EventLogMessage.messageText2 = "Powder Blowing Stop";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_LanceInOperationPos( long LanceId)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Lance In Operation Position LanceNo: ";
  EventLogMessage.messageText2 = "Lance In Operation Position LanceNo: ";
  char mstring0[64];
  sprintf( mstring0,"%l",LanceId);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16026;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_LanceInOperationPos( sEventLogMessage &EventLogMessage, long LanceId)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16026;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Lance In Operation Position LanceNo: ";
  EventLogMessage.messageText2 = "Lance In Operation Position LanceNo: ";
  char mstring0[64];
  sprintf( mstring0,"%l",LanceId);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText2 += mstring0;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_LanceOutOfOperationPos( long LanceId)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Lance Out Of Operation Position LanceNo: ";
  EventLogMessage.messageText2 = "Lance Out Of Operation Position LanceNo: ";
  char mstring0[64];
  sprintf( mstring0,"%l",LanceId);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16027;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_LanceOutOfOperationPos( sEventLogMessage &EventLogMessage, long LanceId)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16027;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Lance Out Of Operation Position LanceNo: ";
  EventLogMessage.messageText2 = "Lance Out Of Operation Position LanceNo: ";
  char mstring0[64];
  sprintf( mstring0,"%l",LanceId);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText2 += mstring0;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_ModelResult()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Model Result received";
  EventLogMessage.messageText2 = "Model Result received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16028;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_ModelResult( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16028;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Model Result received";
  EventLogMessage.messageText2 = "Model Result received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_ModelResultCode()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Model Result Code received";
  EventLogMessage.messageText2 = "Model Result Code received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16029;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_ModelResultCode( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16029;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Model Result Code received";
  EventLogMessage.messageText2 = "Model Result Code received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_PhaseMonoInjectionCarbideEnd()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Mono Injection Carbide Phase End received";
  EventLogMessage.messageText2 = "Mono Injection Carbide Phase End received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16030;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_PhaseMonoInjectionCarbideEnd( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16030;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Mono Injection Carbide Phase End received";
  EventLogMessage.messageText2 = "Mono Injection Carbide Phase End received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_PhaseMonoInjectionCarbideStart()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Mono Injection Carbide Phase Start received";
  EventLogMessage.messageText2 = "Mono Injection Carbide Phase Start received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16031;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_PhaseMonoInjectionCarbideStart( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16031;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Mono Injection Carbide Phase Start received";
  EventLogMessage.messageText2 = "Mono Injection Carbide Phase Start received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_PhaseMonoInjectionContinued()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Mono Injection Continued Phase received";
  EventLogMessage.messageText2 = "Mono Injection Continued Phase received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16032;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_PhaseMonoInjectionContinued( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16032;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Mono Injection Continued Phase received";
  EventLogMessage.messageText2 = "Mono Injection Continued Phase received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_PhaseMonoInjectionLimeEnd()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Mono Injection Lime Phase End received";
  EventLogMessage.messageText2 = "Mono Injection Lime Phase End received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16033;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_PhaseMonoInjectionLimeEnd( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16033;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Mono Injection Lime Phase End received";
  EventLogMessage.messageText2 = "Mono Injection Lime Phase End received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_PhaseMonoInjectionLimeStart()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Mono Injection Lime Phase Start received";
  EventLogMessage.messageText2 = "Mono Injection Lime Phase Start received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16034;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_PhaseMonoInjectionLimeStart( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16034;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Mono Injection Lime Phase Start received";
  EventLogMessage.messageText2 = "Mono Injection Lime Phase Start received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_SlagAnalysisReceived( const char * SampleCode,long SampleCounterL1)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Slag analysis data received SampleCode:";
  EventLogMessage.messageText2 = "Slag analysis data received SampleCode:";
  EventLogMessage.messageText += SampleCode;
  EventLogMessage.messageText += " SampleCounterL1:";
  char mstring1[64];
  sprintf( mstring1,"%l",SampleCounterL1);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += SampleCode;
  EventLogMessage.messageText2 += " SampleCounterL1:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16035;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_SlagAnalysisReceived( sEventLogMessage &EventLogMessage, const char * SampleCode,long SampleCounterL1)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16035;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Slag analysis data received SampleCode:";
  EventLogMessage.messageText2 = "Slag analysis data received SampleCode:";
  EventLogMessage.messageText += SampleCode;
  EventLogMessage.messageText += " SampleCounterL1:";
  char mstring1[64];
  sprintf( mstring1,"%l",SampleCounterL1);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += SampleCode;
  EventLogMessage.messageText2 += " SampleCounterL1:";
  EventLogMessage.messageText2 += mstring1;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_SlagSampleTaken( const char * SampleCode,long SampleCounterL1,const char * SampleLocation)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Slag Sample Taken SampleCode:";
  EventLogMessage.messageText2 = "Slag Sample Taken SampleCode:";
  EventLogMessage.messageText += SampleCode;
  EventLogMessage.messageText += " SampleCounterL1:";
  char mstring1[64];
  sprintf( mstring1,"%l",SampleCounterL1);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += "SampleLocation:";
  EventLogMessage.messageText += SampleLocation;
  EventLogMessage.messageText2 += SampleCode;
  EventLogMessage.messageText2 += " SampleCounterL1:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += "SampleLocation:";
  EventLogMessage.messageText2 += SampleLocation;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16036;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_SlagSampleTaken( sEventLogMessage &EventLogMessage, const char * SampleCode,long SampleCounterL1,const char * SampleLocation)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16036;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Slag Sample Taken SampleCode:";
  EventLogMessage.messageText2 = "Slag Sample Taken SampleCode:";
  EventLogMessage.messageText += SampleCode;
  EventLogMessage.messageText += " SampleCounterL1:";
  char mstring1[64];
  sprintf( mstring1,"%l",SampleCounterL1);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += "SampleLocation:";
  EventLogMessage.messageText += SampleLocation;
  EventLogMessage.messageText2 += SampleCode;
  EventLogMessage.messageText2 += " SampleCounterL1:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += "SampleLocation:";
  EventLogMessage.messageText2 += SampleLocation;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_TempMeasurement( double MeasTemp)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Temperature Measurement MeasTemp:";
  EventLogMessage.messageText2 = "Temperature Measurement MeasTemp:";
  char mstring0[64];
  sprintf( mstring0,"%f",MeasTemp);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16037;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_TempMeasurement( sEventLogMessage &EventLogMessage, double MeasTemp)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16037;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Temperature Measurement MeasTemp:";
  EventLogMessage.messageText2 = "Temperature Measurement MeasTemp:";
  char mstring0[64];
  sprintf( mstring0,"%f",MeasTemp);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText2 += mstring0;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_PhaseCoInjectionMagnesiumStart()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Phase CoInjection Magnesium Start";
  EventLogMessage.messageText2 = "Phase CoInjection Magnesium Start";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16038;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_PhaseCoInjectionMagnesiumStart( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16038;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Phase CoInjection Magnesium Start";
  EventLogMessage.messageText2 = "Phase CoInjection Magnesium Start";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_PhaseCoInjectionMagnesiumEnd()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Phase CoInjection Magnesium End";
  EventLogMessage.messageText2 = "Phase CoInjection Magnesium End";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 16039;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogHMD::EL_PhaseCoInjectionMagnesiumEnd( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 16039;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::HMDBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Phase CoInjection Magnesium End";
  EventLogMessage.messageText2 = "Phase CoInjection Magnesium End";
  return (lRetValue = sendMessage(EventLogMessage));
}
