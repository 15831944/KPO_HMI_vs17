// this is a generated file: do not edit
// use CBSEventLogCodeGenerator to generate it out of excel textfile
#define MAX_MESSAGE_LEN 256 // 255 characters and NULL-Termination!!! DB limit

#include <string>

#include "CSMC_EventLogLF.h"
#include <CBS_Tasks/cCBS_Time.h>

CSMC_EventLogLF::CSMC_EventLogLF(std::string sProcName, std::string sServiceName, std::string sContextName )
: CSMC_EventLogFrame(sProcName,sServiceName,sContextName)
{
}
CSMC_EventLogLF::~CSMC_EventLogLF()
{
}

long CSMC_EventLogLF::EL_SteelAnalysisReceived( const char * SampleID,const char * SampleTime)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Steel analysis data received SampleID:";
  EventLogMessage.messageText2 = "Steel analysis data received SampleID:";
  EventLogMessage.messageText += SampleID;
  EventLogMessage.messageText += " SampleTime:";
  EventLogMessage.messageText += SampleTime;
  EventLogMessage.messageText2 += SampleID;
  EventLogMessage.messageText2 += " SampleTime:";
  EventLogMessage.messageText2 += SampleTime;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13001;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SteelAnalysisReceived( sEventLogMessage &EventLogMessage, const char * SampleID,const char * SampleTime)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13001;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Steel analysis data received SampleID:";
  EventLogMessage.messageText2 = "Steel analysis data received SampleID:";
  EventLogMessage.messageText += SampleID;
  EventLogMessage.messageText += " SampleTime:";
  EventLogMessage.messageText += SampleTime;
  EventLogMessage.messageText2 += SampleID;
  EventLogMessage.messageText2 += " SampleTime:";
  EventLogMessage.messageText2 += SampleTime;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SlagAnalysisReceived( const char * SampleID,const char * SampleTime)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Slag analysis data received SampleID:";
  EventLogMessage.messageText2 = "Slag analysis data received SampleID:";
  EventLogMessage.messageText += SampleID;
  EventLogMessage.messageText += " SampleTime:";
  EventLogMessage.messageText += SampleTime;
  EventLogMessage.messageText2 += SampleID;
  EventLogMessage.messageText2 += " SampleTime:";
  EventLogMessage.messageText2 += SampleTime;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13002;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SlagAnalysisReceived( sEventLogMessage &EventLogMessage, const char * SampleID,const char * SampleTime)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13002;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Slag analysis data received SampleID:";
  EventLogMessage.messageText2 = "Slag analysis data received SampleID:";
  EventLogMessage.messageText += SampleID;
  EventLogMessage.messageText += " SampleTime:";
  EventLogMessage.messageText += SampleTime;
  EventLogMessage.messageText2 += SampleID;
  EventLogMessage.messageText2 += " SampleTime:";
  EventLogMessage.messageText2 += SampleTime;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SteelSampleTaken( const char * SampleID,const char * SampleIDLevel1,const char * SampleLocation)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Steel sample taken SampleID:";
  EventLogMessage.messageText2 = "Steel sample taken SampleID:";
  EventLogMessage.messageText += SampleID;
  EventLogMessage.messageText += " SampleIDL1:";
  EventLogMessage.messageText += SampleIDLevel1;
  EventLogMessage.messageText += "  SampleLocation:";
  EventLogMessage.messageText += SampleLocation;
  EventLogMessage.messageText2 += SampleID;
  EventLogMessage.messageText2 += " SampleIDL1:";
  EventLogMessage.messageText2 += SampleIDLevel1;
  EventLogMessage.messageText2 += "  SampleLocation:";
  EventLogMessage.messageText2 += SampleLocation;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13003;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SteelSampleTaken( sEventLogMessage &EventLogMessage, const char * SampleID,const char * SampleIDLevel1,const char * SampleLocation)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13003;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Steel sample taken SampleID:";
  EventLogMessage.messageText2 = "Steel sample taken SampleID:";
  EventLogMessage.messageText += SampleID;
  EventLogMessage.messageText += " SampleIDL1:";
  EventLogMessage.messageText += SampleIDLevel1;
  EventLogMessage.messageText += "  SampleLocation:";
  EventLogMessage.messageText += SampleLocation;
  EventLogMessage.messageText2 += SampleID;
  EventLogMessage.messageText2 += " SampleIDL1:";
  EventLogMessage.messageText2 += SampleIDLevel1;
  EventLogMessage.messageText2 += "  SampleLocation:";
  EventLogMessage.messageText2 += SampleLocation;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SlagSampleTaken( const char * SampleID,const char * SampleIDLevel1,const char * SampleLocation)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Slag sample taken SampleID:";
  EventLogMessage.messageText2 = "Slag sample taken SampleID:";
  EventLogMessage.messageText += SampleID;
  EventLogMessage.messageText += " SampleIDL1:";
  EventLogMessage.messageText += SampleIDLevel1;
  EventLogMessage.messageText += "  SampleLocation:";
  EventLogMessage.messageText += SampleLocation;
  EventLogMessage.messageText2 += SampleID;
  EventLogMessage.messageText2 += " SampleIDL1:";
  EventLogMessage.messageText2 += SampleIDLevel1;
  EventLogMessage.messageText2 += "  SampleLocation:";
  EventLogMessage.messageText2 += SampleLocation;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13004;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SlagSampleTaken( sEventLogMessage &EventLogMessage, const char * SampleID,const char * SampleIDLevel1,const char * SampleLocation)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13004;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Slag sample taken SampleID:";
  EventLogMessage.messageText2 = "Slag sample taken SampleID:";
  EventLogMessage.messageText += SampleID;
  EventLogMessage.messageText += " SampleIDL1:";
  EventLogMessage.messageText += SampleIDLevel1;
  EventLogMessage.messageText += "  SampleLocation:";
  EventLogMessage.messageText += SampleLocation;
  EventLogMessage.messageText2 += SampleID;
  EventLogMessage.messageText2 += " SampleIDL1:";
  EventLogMessage.messageText2 += SampleIDLevel1;
  EventLogMessage.messageText2 += "  SampleLocation:";
  EventLogMessage.messageText2 += SampleLocation;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangeLiquidAdditionData()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change liquid addition data";
  EventLogMessage.messageText2 = "Change liquid addition data";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13005;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangeLiquidAdditionData( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13005;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change liquid addition data";
  EventLogMessage.messageText2 = "Change liquid addition data";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_RemoveLiquidAdditionData()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Remove Liquid Addition Data received";
  EventLogMessage.messageText2 = "Remove Liquid Addition Data received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13006;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_RemoveLiquidAdditionData( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13006;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Remove Liquid Addition Data received";
  EventLogMessage.messageText2 = "Remove Liquid Addition Data received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_MaterialWeighingReport( int MeasWeight,int WeighingType,const char * LadleID,const char * LadleDeslagged)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Material Weighing Report received MeasWeight:";
  EventLogMessage.messageText2 = "Material Weighing Report received MeasWeight:";
  char mstring0[64];
  sprintf( mstring0,"%d",MeasWeight);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " WeighingType:";
  char mstring1[64];
  sprintf( mstring1,"%d",WeighingType);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " LadleID:";
  EventLogMessage.messageText += LadleID;
  EventLogMessage.messageText += " LadleDeslagged:";
  EventLogMessage.messageText += LadleDeslagged;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " WeighingType:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " LadleID:";
  EventLogMessage.messageText2 += LadleID;
  EventLogMessage.messageText2 += " LadleDeslagged:";
  EventLogMessage.messageText2 += LadleDeslagged;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13007;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_MaterialWeighingReport( sEventLogMessage &EventLogMessage, int MeasWeight,int WeighingType,const char * LadleID,const char * LadleDeslagged)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13007;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Material Weighing Report received MeasWeight:";
  EventLogMessage.messageText2 = "Material Weighing Report received MeasWeight:";
  char mstring0[64];
  sprintf( mstring0,"%d",MeasWeight);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " WeighingType:";
  char mstring1[64];
  sprintf( mstring1,"%d",WeighingType);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " LadleID:";
  EventLogMessage.messageText += LadleID;
  EventLogMessage.messageText += " LadleDeslagged:";
  EventLogMessage.messageText += LadleDeslagged;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " WeighingType:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " LadleID:";
  EventLogMessage.messageText2 += LadleID;
  EventLogMessage.messageText2 += " LadleDeslagged:";
  EventLogMessage.messageText2 += LadleDeslagged;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangePhysicalMatAvailibility( const char * MatCode)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change physical material availability Material:";
  EventLogMessage.messageText2 = "Change physical material availability Material:";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText2 += MatCode;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13008;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangePhysicalMatAvailibility( sEventLogMessage &EventLogMessage, const char * MatCode)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13008;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change physical material availability Material:";
  EventLogMessage.messageText2 = "Change physical material availability Material:";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText2 += MatCode;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_HandleUpdatePurpose()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Update Purpose ";
  EventLogMessage.messageText2 = "Update Purpose ";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13009;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_HandleUpdatePurpose( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13009;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Update Purpose ";
  EventLogMessage.messageText2 = "Update Purpose ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_MatBatchCharged( const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget,int RecipeStatus)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Material batch charged Recipe Name:";
  EventLogMessage.messageText2 = "Material batch charged Recipe Name:";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " Recipe No:";
  char mstring1[64];
  sprintf( mstring1,"%d",RecipeNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Source:";
  EventLogMessage.messageText += RecipeSource;
  EventLogMessage.messageText += " Target:";
  EventLogMessage.messageText += RecipeTarget;
  EventLogMessage.messageText += " Status:";
  char mstring4[64];
  sprintf( mstring4,"%d",RecipeStatus);
  EventLogMessage.messageText += mstring4;
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " Recipe No:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Source:";
  EventLogMessage.messageText2 += RecipeSource;
  EventLogMessage.messageText2 += " Target:";
  EventLogMessage.messageText2 += RecipeTarget;
  EventLogMessage.messageText2 += " Status:";
  EventLogMessage.messageText2 += mstring4;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13010;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_MatBatchCharged( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget,int RecipeStatus)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13010;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Material batch charged Recipe Name:";
  EventLogMessage.messageText2 = "Material batch charged Recipe Name:";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " Recipe No:";
  char mstring1[64];
  sprintf( mstring1,"%d",RecipeNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Source:";
  EventLogMessage.messageText += RecipeSource;
  EventLogMessage.messageText += " Target:";
  EventLogMessage.messageText += RecipeTarget;
  EventLogMessage.messageText += " Status:";
  char mstring4[64];
  sprintf( mstring4,"%d",RecipeStatus);
  EventLogMessage.messageText += mstring4;
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " Recipe No:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Source:";
  EventLogMessage.messageText2 += RecipeSource;
  EventLogMessage.messageText2 += " Target:";
  EventLogMessage.messageText2 += RecipeTarget;
  EventLogMessage.messageText2 += " Status:";
  EventLogMessage.messageText2 += mstring4;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_MatBatchDischarged( const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget,int RecipeStatus)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Material batch discharged Recipe Name:";
  EventLogMessage.messageText2 = "Material batch discharged Recipe Name:";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " Recipe No:";
  char mstring1[64];
  sprintf( mstring1,"%d",RecipeNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Source:";
  EventLogMessage.messageText += RecipeSource;
  EventLogMessage.messageText += " Target:";
  EventLogMessage.messageText += RecipeTarget;
  EventLogMessage.messageText += " Status:";
  char mstring4[64];
  sprintf( mstring4,"%d",RecipeStatus);
  EventLogMessage.messageText += mstring4;
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " Recipe No:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Source:";
  EventLogMessage.messageText2 += RecipeSource;
  EventLogMessage.messageText2 += " Target:";
  EventLogMessage.messageText2 += RecipeTarget;
  EventLogMessage.messageText2 += " Status:";
  EventLogMessage.messageText2 += mstring4;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13011;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_MatBatchDischarged( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget,int RecipeStatus)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13011;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Material batch discharged Recipe Name:";
  EventLogMessage.messageText2 = "Material batch discharged Recipe Name:";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " Recipe No:";
  char mstring1[64];
  sprintf( mstring1,"%d",RecipeNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Source:";
  EventLogMessage.messageText += RecipeSource;
  EventLogMessage.messageText += " Target:";
  EventLogMessage.messageText += RecipeTarget;
  EventLogMessage.messageText += " Status:";
  char mstring4[64];
  sprintf( mstring4,"%d",RecipeStatus);
  EventLogMessage.messageText += mstring4;
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " Recipe No:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Source:";
  EventLogMessage.messageText2 += RecipeSource;
  EventLogMessage.messageText2 += " Target:";
  EventLogMessage.messageText2 += RecipeTarget;
  EventLogMessage.messageText2 += " Status:";
  EventLogMessage.messageText2 += mstring4;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_DisableSourceRecipe( const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Disable Source Recipe Recipe Name:";
  EventLogMessage.messageText2 = "Disable Source Recipe Recipe Name:";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " Recipe No:";
  char mstring1[64];
  sprintf( mstring1,"%d",RecipeNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Source:";
  EventLogMessage.messageText += RecipeSource;
  EventLogMessage.messageText += " Target:";
  EventLogMessage.messageText += RecipeTarget;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " Recipe No:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Source:";
  EventLogMessage.messageText2 += RecipeSource;
  EventLogMessage.messageText2 += " Target:";
  EventLogMessage.messageText2 += RecipeTarget;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13012;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_DisableSourceRecipe( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13012;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Disable Source Recipe Recipe Name:";
  EventLogMessage.messageText2 = "Disable Source Recipe Recipe Name:";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " Recipe No:";
  char mstring1[64];
  sprintf( mstring1,"%d",RecipeNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Source:";
  EventLogMessage.messageText += RecipeSource;
  EventLogMessage.messageText += " Target:";
  EventLogMessage.messageText += RecipeTarget;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " Recipe No:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Source:";
  EventLogMessage.messageText2 += RecipeSource;
  EventLogMessage.messageText2 += " Target:";
  EventLogMessage.messageText2 += RecipeTarget;
  EventLogMessage.messageText2 += " ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_EnableSourceRecipe( const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Enable Source Recipe Recipe Name:";
  EventLogMessage.messageText2 = "Enable Source Recipe Recipe Name:";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " Recipe No:";
  char mstring1[64];
  sprintf( mstring1,"%d",RecipeNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Source:";
  EventLogMessage.messageText += RecipeSource;
  EventLogMessage.messageText += " Target:";
  EventLogMessage.messageText += RecipeTarget;
  EventLogMessage.messageText += "  ";
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " Recipe No:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Source:";
  EventLogMessage.messageText2 += RecipeSource;
  EventLogMessage.messageText2 += " Target:";
  EventLogMessage.messageText2 += RecipeTarget;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13013;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_EnableSourceRecipe( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13013;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Enable Source Recipe Recipe Name:";
  EventLogMessage.messageText2 = "Enable Source Recipe Recipe Name:";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " Recipe No:";
  char mstring1[64];
  sprintf( mstring1,"%d",RecipeNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Source:";
  EventLogMessage.messageText += RecipeSource;
  EventLogMessage.messageText += " Target:";
  EventLogMessage.messageText += RecipeTarget;
  EventLogMessage.messageText += "  ";
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " Recipe No:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Source:";
  EventLogMessage.messageText2 += RecipeSource;
  EventLogMessage.messageText2 += " Target:";
  EventLogMessage.messageText2 += RecipeTarget;
  EventLogMessage.messageText2 += " ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_RecipeMaterialCharged( const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Recipe Material Charged Recipe Name:";
  EventLogMessage.messageText2 = "Recipe Material Charged  Recipe Name:";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " Recipe No:";
  char mstring1[64];
  sprintf( mstring1,"%d",RecipeNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Source:";
  EventLogMessage.messageText += RecipeSource;
  EventLogMessage.messageText += " Target:";
  EventLogMessage.messageText += RecipeTarget;
  EventLogMessage.messageText += "  ";
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " Recipe No:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Source:";
  EventLogMessage.messageText2 += RecipeSource;
  EventLogMessage.messageText2 += " Target:";
  EventLogMessage.messageText2 += RecipeTarget;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13014;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_RecipeMaterialCharged( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13014;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Recipe Material Charged Recipe Name:";
  EventLogMessage.messageText2 = "Recipe Material Charged  Recipe Name:";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " Recipe No:";
  char mstring1[64];
  sprintf( mstring1,"%d",RecipeNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Source:";
  EventLogMessage.messageText += RecipeSource;
  EventLogMessage.messageText += " Target:";
  EventLogMessage.messageText += RecipeTarget;
  EventLogMessage.messageText += "  ";
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " Recipe No:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Source:";
  EventLogMessage.messageText2 += RecipeSource;
  EventLogMessage.messageText2 += " Target:";
  EventLogMessage.messageText2 += RecipeTarget;
  EventLogMessage.messageText2 += " ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_RecipeMaterialDischarged( const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Recipe Material Discharged Recipe Name:";
  EventLogMessage.messageText2 = "Recipe Material Discharged  Recipe Name:";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " Recipe No:";
  char mstring1[64];
  sprintf( mstring1,"%d",RecipeNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Source:";
  EventLogMessage.messageText += RecipeSource;
  EventLogMessage.messageText += " Target:";
  EventLogMessage.messageText += RecipeTarget;
  EventLogMessage.messageText += "  ";
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " Recipe No:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Source:";
  EventLogMessage.messageText2 += RecipeSource;
  EventLogMessage.messageText2 += " Target:";
  EventLogMessage.messageText2 += RecipeTarget;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13015;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_RecipeMaterialDischarged( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13015;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Recipe Material Discharged Recipe Name:";
  EventLogMessage.messageText2 = "Recipe Material Discharged  Recipe Name:";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " Recipe No:";
  char mstring1[64];
  sprintf( mstring1,"%d",RecipeNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Source:";
  EventLogMessage.messageText += RecipeSource;
  EventLogMessage.messageText += " Target:";
  EventLogMessage.messageText += RecipeTarget;
  EventLogMessage.messageText += "  ";
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " Recipe No:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Source:";
  EventLogMessage.messageText2 += RecipeSource;
  EventLogMessage.messageText2 += " Target:";
  EventLogMessage.messageText2 += RecipeTarget;
  EventLogMessage.messageText2 += " ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ModelResultCode()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Model Result Code received";
  EventLogMessage.messageText2 = "Model Result Code received";
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13016;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ModelResultCode( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13016;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Model Result Code received";
  EventLogMessage.messageText2 = "Model Result Code received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ModelResultActualSetPoints()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Model Result Actual Set Points received";
  EventLogMessage.messageText2 = "Model Result Actual Set Points received";
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13017;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ModelResultActualSetPoints( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13017;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Model Result Actual Set Points received";
  EventLogMessage.messageText2 = "Model Result Actual Set Points received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ModelResultRecipeSetPoints()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Model Result Recipe Set Points received";
  EventLogMessage.messageText2 = "Model Result Recipe Set Points received";
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13018;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ModelResultRecipeSetPoints( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13018;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Model Result Recipe Set Points received";
  EventLogMessage.messageText2 = "Model Result Recipe Set Points received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SetComputerMode( const char * LadleTransferCarId,const char * Device,int Status)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Set Computer Mode received LadleTransferCarId:";
  EventLogMessage.messageText2 = "Set Computer Mode received LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " Status ";
  char mstring2[64];
  sprintf( mstring2,"%d",Status);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " Device:";
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " Status ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13019;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SetComputerMode( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * Device,int Status)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13019;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Set Computer Mode received LadleTransferCarId:";
  EventLogMessage.messageText2 = "Set Computer Mode received LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " Status ";
  char mstring2[64];
  sprintf( mstring2,"%d",Status);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " Device:";
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " Status ";
  EventLogMessage.messageText2 += mstring2;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_LiquidSteelCharged()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Liquid Steel Charged received";
  EventLogMessage.messageText2 = "Liquid Steel Charged received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13020;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_LiquidSteelCharged( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13020;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Liquid Steel Charged received";
  EventLogMessage.messageText2 = "Liquid Steel Charged received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_LiqMatHandlReport( const char * MeasWeight,const char * WeighingType,const char * LadleId,const char * LadleDeslagged)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Liquid Material Handling Report received MeasWeight:";
  EventLogMessage.messageText2 = "Liquid Material Handling Report received MeasWeight:";
  EventLogMessage.messageText += MeasWeight;
  EventLogMessage.messageText += " WeighingType:";
  EventLogMessage.messageText += WeighingType;
  EventLogMessage.messageText += " LadleId:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText += " LadleDeslagged:";
  EventLogMessage.messageText += LadleDeslagged;
  EventLogMessage.messageText2 += MeasWeight;
  EventLogMessage.messageText2 += " WeighingType:";
  EventLogMessage.messageText2 += WeighingType;
  EventLogMessage.messageText2 += " LadleId:";
  EventLogMessage.messageText2 += LadleId;
  EventLogMessage.messageText2 += " LadleDeslagged:";
  EventLogMessage.messageText2 += LadleDeslagged;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13021;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_LiqMatHandlReport( sEventLogMessage &EventLogMessage, const char * MeasWeight,const char * WeighingType,const char * LadleId,const char * LadleDeslagged)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13021;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Liquid Material Handling Report received MeasWeight:";
  EventLogMessage.messageText2 = "Liquid Material Handling Report received MeasWeight:";
  EventLogMessage.messageText += MeasWeight;
  EventLogMessage.messageText += " WeighingType:";
  EventLogMessage.messageText += WeighingType;
  EventLogMessage.messageText += " LadleId:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText += " LadleDeslagged:";
  EventLogMessage.messageText += LadleDeslagged;
  EventLogMessage.messageText2 += MeasWeight;
  EventLogMessage.messageText2 += " WeighingType:";
  EventLogMessage.messageText2 += WeighingType;
  EventLogMessage.messageText2 += " LadleId:";
  EventLogMessage.messageText2 += LadleId;
  EventLogMessage.messageText2 += " LadleDeslagged:";
  EventLogMessage.messageText2 += LadleDeslagged;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_WireFeedingStart( const char * WireFeederMatCode,const char * WireFeederLineNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Wire Feeding Start received WireFeederMatCode:";
  EventLogMessage.messageText2 = "Wire Feeding Start received WireFeederMatCode:";
  EventLogMessage.messageText += WireFeederMatCode;
  EventLogMessage.messageText += " WireFeederLineNo:";
  EventLogMessage.messageText += WireFeederLineNo;
  EventLogMessage.messageText2 += WireFeederMatCode;
  EventLogMessage.messageText2 += " WireFeederLineNo:";
  EventLogMessage.messageText2 += WireFeederLineNo;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13022;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_WireFeedingStart( sEventLogMessage &EventLogMessage, const char * WireFeederMatCode,const char * WireFeederLineNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13022;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Wire Feeding Start received WireFeederMatCode:";
  EventLogMessage.messageText2 = "Wire Feeding Start received WireFeederMatCode:";
  EventLogMessage.messageText += WireFeederMatCode;
  EventLogMessage.messageText += " WireFeederLineNo:";
  EventLogMessage.messageText += WireFeederLineNo;
  EventLogMessage.messageText2 += WireFeederMatCode;
  EventLogMessage.messageText2 += " WireFeederLineNo:";
  EventLogMessage.messageText2 += WireFeederLineNo;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_WireFeedingEnd( const char * WireFeederLineNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Wire Feeding End received WireFeederLineNo:";
  EventLogMessage.messageText2 = "Wire Feeding End received WireFeederLineNo:";
  EventLogMessage.messageText += WireFeederLineNo;
  EventLogMessage.messageText2 += WireFeederLineNo;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13023;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_WireFeedingEnd( sEventLogMessage &EventLogMessage, const char * WireFeederLineNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13023;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Wire Feeding End received WireFeederLineNo:";
  EventLogMessage.messageText2 = "Wire Feeding End received WireFeederLineNo:";
  EventLogMessage.messageText += WireFeederLineNo;
  EventLogMessage.messageText2 += WireFeederLineNo;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ElectrodesInOperatingPosition()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Electrodes In Operating Position received";
  EventLogMessage.messageText2 = "Electrodes In Operating Position received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13024;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ElectrodesInOperatingPosition( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13024;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Electrodes In Operating Position received";
  EventLogMessage.messageText2 = "Electrodes In Operating Position received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_FurnaceBreakerOn()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Furnace Breaker On";
  EventLogMessage.messageText2 = "Furnace Breaker On";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13025;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_FurnaceBreakerOn( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13025;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Furnace Breaker On";
  EventLogMessage.messageText2 = "Furnace Breaker On";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_FurnaceBreakerOff()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Furnace Breaker Off";
  EventLogMessage.messageText2 = "Furnace Breaker Off";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13026;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_FurnaceBreakerOff( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13026;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Furnace Breaker Off";
  EventLogMessage.messageText2 = "Furnace Breaker Off";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_PowerOn()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Power On";
  EventLogMessage.messageText2 = "Power On";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13027;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_PowerOn( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13027;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Power On";
  EventLogMessage.messageText2 = "Power On";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_PowerOff()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Power Off";
  EventLogMessage.messageText2 = "Power Off";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13028;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_PowerOff( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13028;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Power Off";
  EventLogMessage.messageText2 = "Power Off";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_TapChangeStart( const char * VoltTapNo,const char * EltrdRegCurve)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Tap Change Start  VoltTapNo:";
  EventLogMessage.messageText2 = "Tap Change Start  VoltTapNo:";
  EventLogMessage.messageText += VoltTapNo;
  EventLogMessage.messageText += " EltrdRegCurve:";
  EventLogMessage.messageText += EltrdRegCurve;
  EventLogMessage.messageText2 += VoltTapNo;
  EventLogMessage.messageText2 += " EltrdRegCurve:";
  EventLogMessage.messageText2 += EltrdRegCurve;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13029;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_TapChangeStart( sEventLogMessage &EventLogMessage, const char * VoltTapNo,const char * EltrdRegCurve)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13029;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Tap Change Start  VoltTapNo:";
  EventLogMessage.messageText2 = "Tap Change Start  VoltTapNo:";
  EventLogMessage.messageText += VoltTapNo;
  EventLogMessage.messageText += " EltrdRegCurve:";
  EventLogMessage.messageText += EltrdRegCurve;
  EventLogMessage.messageText2 += VoltTapNo;
  EventLogMessage.messageText2 += " EltrdRegCurve:";
  EventLogMessage.messageText2 += EltrdRegCurve;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_TapChangeFinished( const char * VoltTapNo,const char * EltrdRegCurve)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Tap Change Finished  VoltTapNo:";
  EventLogMessage.messageText2 = "Tap Change Finished  VoltTapNo:";
  EventLogMessage.messageText += VoltTapNo;
  EventLogMessage.messageText += " EltrdRegCurve:";
  EventLogMessage.messageText += EltrdRegCurve;
  EventLogMessage.messageText2 += VoltTapNo;
  EventLogMessage.messageText2 += " EltrdRegCurve:";
  EventLogMessage.messageText2 += EltrdRegCurve;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13030;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_TapChangeFinished( sEventLogMessage &EventLogMessage, const char * VoltTapNo,const char * EltrdRegCurve)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13030;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Tap Change Finished  VoltTapNo:";
  EventLogMessage.messageText2 = "Tap Change Finished  VoltTapNo:";
  EventLogMessage.messageText += VoltTapNo;
  EventLogMessage.messageText += " EltrdRegCurve:";
  EventLogMessage.messageText += EltrdRegCurve;
  EventLogMessage.messageText2 += VoltTapNo;
  EventLogMessage.messageText2 += " EltrdRegCurve:";
  EventLogMessage.messageText2 += EltrdRegCurve;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_CyclicMeasurementElec( const char * CarNo,const char * VoltTapNo,const char * EltrdRegCurve,const char * ElecCons)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Cyclic Data : Electrical System CarNo:";
  EventLogMessage.messageText2 = "Cyclic Data : Electrical System CarNo:";
  EventLogMessage.messageText += CarNo;
  EventLogMessage.messageText += " VoltTap:";
  EventLogMessage.messageText += VoltTapNo;
  EventLogMessage.messageText += " EltrdRegCurve:";
  EventLogMessage.messageText += EltrdRegCurve;
  EventLogMessage.messageText += " ElecCons:";
  EventLogMessage.messageText += ElecCons;
  EventLogMessage.messageText2 += CarNo;
  EventLogMessage.messageText2 += " VoltTap:";
  EventLogMessage.messageText2 += VoltTapNo;
  EventLogMessage.messageText2 += " EltrdRegCurve:";
  EventLogMessage.messageText2 += EltrdRegCurve;
  EventLogMessage.messageText2 += " ElecCons:";
  EventLogMessage.messageText2 += ElecCons;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13031;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_CyclicMeasurementElec( sEventLogMessage &EventLogMessage, const char * CarNo,const char * VoltTapNo,const char * EltrdRegCurve,const char * ElecCons)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13031;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Cyclic Data : Electrical System CarNo:";
  EventLogMessage.messageText2 = "Cyclic Data : Electrical System CarNo:";
  EventLogMessage.messageText += CarNo;
  EventLogMessage.messageText += " VoltTap:";
  EventLogMessage.messageText += VoltTapNo;
  EventLogMessage.messageText += " EltrdRegCurve:";
  EventLogMessage.messageText += EltrdRegCurve;
  EventLogMessage.messageText += " ElecCons:";
  EventLogMessage.messageText += ElecCons;
  EventLogMessage.messageText2 += CarNo;
  EventLogMessage.messageText2 += " VoltTap:";
  EventLogMessage.messageText2 += VoltTapNo;
  EventLogMessage.messageText2 += " EltrdRegCurve:";
  EventLogMessage.messageText2 += EltrdRegCurve;
  EventLogMessage.messageText2 += " ElecCons:";
  EventLogMessage.messageText2 += ElecCons;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_CyclicMeasurementCool( const char * CarNo,const char * CoolWaterDevice,double InletTemp,double OutletTemp,double WaterFlow)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Cyclic Data : Cooling Water CarNo:";
  EventLogMessage.messageText2 = "Cyclic Data : Cooling Water CarNo:";
  EventLogMessage.messageText += CarNo;
  EventLogMessage.messageText += " Device:";
  EventLogMessage.messageText += CoolWaterDevice;
  EventLogMessage.messageText += " InletTemp:";
  char mstring2[64];
  sprintf( mstring2,"%f",InletTemp);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText += " OutletTemp:";
  char mstring3[64];
  sprintf( mstring3,"%f",OutletTemp);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText += " WaterFlow:";
  char mstring4[64];
  sprintf( mstring4,"%f",WaterFlow);
  EventLogMessage.messageText += mstring4;
  EventLogMessage.messageText2 += CarNo;
  EventLogMessage.messageText2 += " Device:";
  EventLogMessage.messageText2 += CoolWaterDevice;
  EventLogMessage.messageText2 += " InletTemp:";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.messageText2 += " OutletTemp:";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.messageText2 += " WaterFlow:";
  EventLogMessage.messageText2 += mstring4;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13032;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_CyclicMeasurementCool( sEventLogMessage &EventLogMessage, const char * CarNo,const char * CoolWaterDevice,double InletTemp,double OutletTemp,double WaterFlow)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13032;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Cyclic Data : Cooling Water CarNo:";
  EventLogMessage.messageText2 = "Cyclic Data : Cooling Water CarNo:";
  EventLogMessage.messageText += CarNo;
  EventLogMessage.messageText += " Device:";
  EventLogMessage.messageText += CoolWaterDevice;
  EventLogMessage.messageText += " InletTemp:";
  char mstring2[64];
  sprintf( mstring2,"%f",InletTemp);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText += " OutletTemp:";
  char mstring3[64];
  sprintf( mstring3,"%f",OutletTemp);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText += " WaterFlow:";
  char mstring4[64];
  sprintf( mstring4,"%f",WaterFlow);
  EventLogMessage.messageText += mstring4;
  EventLogMessage.messageText2 += CarNo;
  EventLogMessage.messageText2 += " Device:";
  EventLogMessage.messageText2 += CoolWaterDevice;
  EventLogMessage.messageText2 += " InletTemp:";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.messageText2 += " OutletTemp:";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.messageText2 += " WaterFlow:";
  EventLogMessage.messageText2 += mstring4;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_CyclicMeasurementStirring( const char * CarNo,const char * StirringDevice,const char * GasType,double GasValue)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Cyclic Data : Stirring CarNo:";
  EventLogMessage.messageText2 = "Cyclic Data : Stirring CarNo:";
  EventLogMessage.messageText += CarNo;
  EventLogMessage.messageText += " Device. ";
  EventLogMessage.messageText += StirringDevice;
  EventLogMessage.messageText += " GasType:";
  EventLogMessage.messageText += GasType;
  EventLogMessage.messageText += " GasValue:";
  char mstring3[64];
  sprintf( mstring3,"%f",GasValue);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText2 += CarNo;
  EventLogMessage.messageText2 += " Device. ";
  EventLogMessage.messageText2 += StirringDevice;
  EventLogMessage.messageText2 += " GasType:";
  EventLogMessage.messageText2 += GasType;
  EventLogMessage.messageText2 += " GasValue:";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13033;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_CyclicMeasurementStirring( sEventLogMessage &EventLogMessage, const char * CarNo,const char * StirringDevice,const char * GasType,double GasValue)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13033;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Cyclic Data : Stirring CarNo:";
  EventLogMessage.messageText2 = "Cyclic Data : Stirring CarNo:";
  EventLogMessage.messageText += CarNo;
  EventLogMessage.messageText += " Device. ";
  EventLogMessage.messageText += StirringDevice;
  EventLogMessage.messageText += " GasType:";
  EventLogMessage.messageText += GasType;
  EventLogMessage.messageText += " GasValue:";
  char mstring3[64];
  sprintf( mstring3,"%f",GasValue);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText2 += CarNo;
  EventLogMessage.messageText2 += " Device. ";
  EventLogMessage.messageText2 += StirringDevice;
  EventLogMessage.messageText2 += " GasType:";
  EventLogMessage.messageText2 += GasType;
  EventLogMessage.messageText2 += " GasValue:";
  EventLogMessage.messageText2 += mstring3;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_CeloxMeasurement( const char * MeasCarbonConc,const char * MeasAlConc,const char * TempSampleId,const char * MeasTemp,const char * MeasO2Conc)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Celox Measurement  MeasCarbonConc:";
  EventLogMessage.messageText2 = "Celox Measurement  MeasCarbonConc:";
  EventLogMessage.messageText += MeasCarbonConc;
  EventLogMessage.messageText += " MeasAlConc:";
  EventLogMessage.messageText += MeasAlConc;
  EventLogMessage.messageText += " TempSampleId:";
  EventLogMessage.messageText += TempSampleId;
  EventLogMessage.messageText += " MeasTemp:";
  EventLogMessage.messageText += MeasTemp;
  EventLogMessage.messageText += " MeasO2Conc:";
  EventLogMessage.messageText += MeasO2Conc;
  EventLogMessage.messageText2 += MeasCarbonConc;
  EventLogMessage.messageText2 += " MeasAlConc:";
  EventLogMessage.messageText2 += MeasAlConc;
  EventLogMessage.messageText2 += " TempSampleId:";
  EventLogMessage.messageText2 += TempSampleId;
  EventLogMessage.messageText2 += " MeasTemp:";
  EventLogMessage.messageText2 += MeasTemp;
  EventLogMessage.messageText2 += " MeasO2Conc:";
  EventLogMessage.messageText2 += MeasO2Conc;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13034;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_CeloxMeasurement( sEventLogMessage &EventLogMessage, const char * MeasCarbonConc,const char * MeasAlConc,const char * TempSampleId,const char * MeasTemp,const char * MeasO2Conc)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13034;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Celox Measurement  MeasCarbonConc:";
  EventLogMessage.messageText2 = "Celox Measurement  MeasCarbonConc:";
  EventLogMessage.messageText += MeasCarbonConc;
  EventLogMessage.messageText += " MeasAlConc:";
  EventLogMessage.messageText += MeasAlConc;
  EventLogMessage.messageText += " TempSampleId:";
  EventLogMessage.messageText += TempSampleId;
  EventLogMessage.messageText += " MeasTemp:";
  EventLogMessage.messageText += MeasTemp;
  EventLogMessage.messageText += " MeasO2Conc:";
  EventLogMessage.messageText += MeasO2Conc;
  EventLogMessage.messageText2 += MeasCarbonConc;
  EventLogMessage.messageText2 += " MeasAlConc:";
  EventLogMessage.messageText2 += MeasAlConc;
  EventLogMessage.messageText2 += " TempSampleId:";
  EventLogMessage.messageText2 += TempSampleId;
  EventLogMessage.messageText2 += " MeasTemp:";
  EventLogMessage.messageText2 += MeasTemp;
  EventLogMessage.messageText2 += " MeasO2Conc:";
  EventLogMessage.messageText2 += MeasO2Conc;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_TempMeasurement( const char * MeasTemp,const char * TempSampleId,const char * MeasCarbonConc,const char * LadleCarPosition,const char * LadleId)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Temperature Measurement MeasTemp:";
  EventLogMessage.messageText2 = "Temperature Measurement MeasTemp:";
  EventLogMessage.messageText += MeasTemp;
  EventLogMessage.messageText += " TempSampleId:";
  EventLogMessage.messageText += TempSampleId;
  EventLogMessage.messageText += " MeasCarbonConc:";
  EventLogMessage.messageText += MeasCarbonConc;
  EventLogMessage.messageText += " LadleCarPosition:";
  EventLogMessage.messageText += LadleCarPosition;
  EventLogMessage.messageText += " LadleId:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText2 += MeasTemp;
  EventLogMessage.messageText2 += " TempSampleId:";
  EventLogMessage.messageText2 += TempSampleId;
  EventLogMessage.messageText2 += " MeasCarbonConc:";
  EventLogMessage.messageText2 += MeasCarbonConc;
  EventLogMessage.messageText2 += " LadleCarPosition:";
  EventLogMessage.messageText2 += LadleCarPosition;
  EventLogMessage.messageText2 += " LadleId:";
  EventLogMessage.messageText2 += LadleId;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13035;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_TempMeasurement( sEventLogMessage &EventLogMessage, const char * MeasTemp,const char * TempSampleId,const char * MeasCarbonConc,const char * LadleCarPosition,const char * LadleId)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13035;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Temperature Measurement MeasTemp:";
  EventLogMessage.messageText2 = "Temperature Measurement MeasTemp:";
  EventLogMessage.messageText += MeasTemp;
  EventLogMessage.messageText += " TempSampleId:";
  EventLogMessage.messageText += TempSampleId;
  EventLogMessage.messageText += " MeasCarbonConc:";
  EventLogMessage.messageText += MeasCarbonConc;
  EventLogMessage.messageText += " LadleCarPosition:";
  EventLogMessage.messageText += LadleCarPosition;
  EventLogMessage.messageText += " LadleId:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText2 += MeasTemp;
  EventLogMessage.messageText2 += " TempSampleId:";
  EventLogMessage.messageText2 += TempSampleId;
  EventLogMessage.messageText2 += " MeasCarbonConc:";
  EventLogMessage.messageText2 += MeasCarbonConc;
  EventLogMessage.messageText2 += " LadleCarPosition:";
  EventLogMessage.messageText2 += LadleCarPosition;
  EventLogMessage.messageText2 += " LadleId:";
  EventLogMessage.messageText2 += LadleId;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_DeslaggingData( const char * DeslagStartTime,const char * DeslagEndTime,const char * LadleTransferCarId,const char * LadleCarPosition,const char * LadleId)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Deslagging Data  DeslagStartTime:";
  EventLogMessage.messageText2 = "Deslagging Data  DeslagStartTime:";
  EventLogMessage.messageText += DeslagStartTime;
  EventLogMessage.messageText += " DeslagEndTime:";
  EventLogMessage.messageText += DeslagEndTime;
  EventLogMessage.messageText += " LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " LadleCarPosition:";
  EventLogMessage.messageText += LadleCarPosition;
  EventLogMessage.messageText += " LadleId:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText2 += DeslagStartTime;
  EventLogMessage.messageText2 += " DeslagEndTime:";
  EventLogMessage.messageText2 += DeslagEndTime;
  EventLogMessage.messageText2 += " LadleTransferCarId:";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " LadleCarPosition:";
  EventLogMessage.messageText2 += LadleCarPosition;
  EventLogMessage.messageText2 += " LadleId:";
  EventLogMessage.messageText2 += LadleId;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13036;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_DeslaggingData( sEventLogMessage &EventLogMessage, const char * DeslagStartTime,const char * DeslagEndTime,const char * LadleTransferCarId,const char * LadleCarPosition,const char * LadleId)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13036;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Deslagging Data  DeslagStartTime:";
  EventLogMessage.messageText2 = "Deslagging Data  DeslagStartTime:";
  EventLogMessage.messageText += DeslagStartTime;
  EventLogMessage.messageText += " DeslagEndTime:";
  EventLogMessage.messageText += DeslagEndTime;
  EventLogMessage.messageText += " LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " LadleCarPosition:";
  EventLogMessage.messageText += LadleCarPosition;
  EventLogMessage.messageText += " LadleId:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText2 += DeslagStartTime;
  EventLogMessage.messageText2 += " DeslagEndTime:";
  EventLogMessage.messageText2 += DeslagEndTime;
  EventLogMessage.messageText2 += " LadleTransferCarId:";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " LadleCarPosition:";
  EventLogMessage.messageText2 += LadleCarPosition;
  EventLogMessage.messageText2 += " LadleId:";
  EventLogMessage.messageText2 += LadleId;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_RoofArrivesInUpPosition( const char * CarNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Roof Arrives In Up Position CarNo:";
  EventLogMessage.messageText2 = "Roof Arrives In Up Position CarNo:";
  EventLogMessage.messageText += CarNo;
  EventLogMessage.messageText2 += CarNo;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13037;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_RoofArrivesInUpPosition( sEventLogMessage &EventLogMessage, const char * CarNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13037;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Roof Arrives In Up Position CarNo:";
  EventLogMessage.messageText2 = "Roof Arrives In Up Position CarNo:";
  EventLogMessage.messageText += CarNo;
  EventLogMessage.messageText2 += CarNo;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_RoofArrivesInDownPosition( const char * CarNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Roof Arrives In Down Position CarNo:";
  EventLogMessage.messageText2 = "Roof Arrives In Down Position CarNo:";
  EventLogMessage.messageText += CarNo;
  EventLogMessage.messageText2 += CarNo;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13038;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_RoofArrivesInDownPosition( sEventLogMessage &EventLogMessage, const char * CarNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13038;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Roof Arrives In Down Position CarNo:";
  EventLogMessage.messageText2 = "Roof Arrives In Down Position CarNo:";
  EventLogMessage.messageText += CarNo;
  EventLogMessage.messageText2 += CarNo;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_TransferCarPositionChanged( const char * LadleTransferCarId,const char * LadleCarPosition,const char * LadleId)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Transfer Car Position Changed  LadleTransferCarId:";
  EventLogMessage.messageText2 = "Transfer Car Position Changed  LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " LadleCarPosition:";
  EventLogMessage.messageText += LadleCarPosition;
  EventLogMessage.messageText += " LadleId:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " LadleCarPosition:";
  EventLogMessage.messageText2 += LadleCarPosition;
  EventLogMessage.messageText2 += " LadleId:";
  EventLogMessage.messageText2 += LadleId;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13039;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_TransferCarPositionChanged( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * LadleCarPosition,const char * LadleId)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13039;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Transfer Car Position Changed  LadleTransferCarId:";
  EventLogMessage.messageText2 = "Transfer Car Position Changed  LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " LadleCarPosition:";
  EventLogMessage.messageText += LadleCarPosition;
  EventLogMessage.messageText += " LadleId:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " LadleCarPosition:";
  EventLogMessage.messageText2 += LadleCarPosition;
  EventLogMessage.messageText2 += " LadleId:";
  EventLogMessage.messageText2 += LadleId;
  EventLogMessage.messageText2 += " ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_BottomStirringByPassOn( const char * LadleTransferCarId,const char * LadleId,const char * LadlePlugNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Bottom Stirring By Pass On  LadleTransferCarId:";
  EventLogMessage.messageText2 = "Bottom Stirring By Pass On  LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " LadleId:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText += " LadlePlugNo:";
  EventLogMessage.messageText += LadlePlugNo;
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " LadleId:";
  EventLogMessage.messageText2 += LadleId;
  EventLogMessage.messageText2 += " LadlePlugNo:";
  EventLogMessage.messageText2 += LadlePlugNo;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13040;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_BottomStirringByPassOn( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * LadleId,const char * LadlePlugNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13040;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Bottom Stirring By Pass On  LadleTransferCarId:";
  EventLogMessage.messageText2 = "Bottom Stirring By Pass On  LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " LadleId:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText += " LadlePlugNo:";
  EventLogMessage.messageText += LadlePlugNo;
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " LadleId:";
  EventLogMessage.messageText2 += LadleId;
  EventLogMessage.messageText2 += " LadlePlugNo:";
  EventLogMessage.messageText2 += LadlePlugNo;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_BottomStirringByPassOff( const char * LadleTransferCarId,const char * LadleId,const char * LadlePlugNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Bottom Stirring By Pass Off  LadleTransferCarId:";
  EventLogMessage.messageText2 = "Bottom Stirring By Pass Off  LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " LadleId:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText += " LadlePlugNo:";
  EventLogMessage.messageText += LadlePlugNo;
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " LadleId:";
  EventLogMessage.messageText2 += LadleId;
  EventLogMessage.messageText2 += " LadlePlugNo:";
  EventLogMessage.messageText2 += LadlePlugNo;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13041;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_BottomStirringByPassOff( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * LadleId,const char * LadlePlugNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13041;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Bottom Stirring By Pass Off  LadleTransferCarId:";
  EventLogMessage.messageText2 = "Bottom Stirring By Pass Off  LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " LadleId:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText += " LadlePlugNo:";
  EventLogMessage.messageText += LadlePlugNo;
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " LadleId:";
  EventLogMessage.messageText2 += LadleId;
  EventLogMessage.messageText2 += " LadlePlugNo:";
  EventLogMessage.messageText2 += LadlePlugNo;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_BottomStirringByPassOn( const char * LadleTransferCarId,const char * LadlePlugNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Bottom Stirring By Pass On  LadleTransferCarId:";
  EventLogMessage.messageText2 = "Bottom Stirring By Pass On  LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " LadlePlugNo:";
  EventLogMessage.messageText += LadlePlugNo;
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " LadlePlugNo:";
  EventLogMessage.messageText2 += LadlePlugNo;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13042;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_BottomStirringByPassOn( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * LadlePlugNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13042;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Bottom Stirring By Pass On  LadleTransferCarId:";
  EventLogMessage.messageText2 = "Bottom Stirring By Pass On  LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " LadlePlugNo:";
  EventLogMessage.messageText += LadlePlugNo;
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " LadlePlugNo:";
  EventLogMessage.messageText2 += LadlePlugNo;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_BottomStirringByPassOff( const char * LadleTransferCarId,const char * LadlePlugNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Bottom Stirring By Pass Off  LadleTransferCarId:";
  EventLogMessage.messageText2 = "Bottom Stirring By Pass Off  LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " LadlePlugNo:";
  EventLogMessage.messageText += LadlePlugNo;
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " LadlePlugNo:";
  EventLogMessage.messageText2 += LadlePlugNo;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13043;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_BottomStirringByPassOff( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * LadlePlugNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13043;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Bottom Stirring By Pass Off  LadleTransferCarId:";
  EventLogMessage.messageText2 = "Bottom Stirring By Pass Off  LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " LadlePlugNo:";
  EventLogMessage.messageText += LadlePlugNo;
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " LadlePlugNo:";
  EventLogMessage.messageText2 += LadlePlugNo;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_BottomStirringStart( const char * LadleTransferCarId,const char * LadleId,const char * StirrGasType,const char * LadlePlugNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Bottom Stirring Start  LadleTransferCarId:";
  EventLogMessage.messageText2 = "Bottom Stirring Start  LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " LadleId:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText += " StirrGasType:";
  EventLogMessage.messageText += StirrGasType;
  EventLogMessage.messageText += " LadlePlugNo:";
  EventLogMessage.messageText += LadlePlugNo;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " LadleId:";
  EventLogMessage.messageText2 += LadleId;
  EventLogMessage.messageText2 += " StirrGasType:";
  EventLogMessage.messageText2 += StirrGasType;
  EventLogMessage.messageText2 += " LadlePlugNo:";
  EventLogMessage.messageText2 += LadlePlugNo;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13044;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_BottomStirringStart( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * LadleId,const char * StirrGasType,const char * LadlePlugNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13044;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Bottom Stirring Start  LadleTransferCarId:";
  EventLogMessage.messageText2 = "Bottom Stirring Start  LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " LadleId:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText += " StirrGasType:";
  EventLogMessage.messageText += StirrGasType;
  EventLogMessage.messageText += " LadlePlugNo:";
  EventLogMessage.messageText += LadlePlugNo;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " LadleId:";
  EventLogMessage.messageText2 += LadleId;
  EventLogMessage.messageText2 += " StirrGasType:";
  EventLogMessage.messageText2 += StirrGasType;
  EventLogMessage.messageText2 += " LadlePlugNo:";
  EventLogMessage.messageText2 += LadlePlugNo;
  EventLogMessage.messageText2 += " ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_BottomStirringEnd( const char * LadleTransferCarId,const char * LadleId,const char * StirrGasType,const char * LadlePlugNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Bottom Stirring End  LadleTransferCarId:";
  EventLogMessage.messageText2 = "Bottom Stirring End  LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " LadleId:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText += " StirrGasType:";
  EventLogMessage.messageText += StirrGasType;
  EventLogMessage.messageText += " LadlePlugNo:";
  EventLogMessage.messageText += LadlePlugNo;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " LadleId:";
  EventLogMessage.messageText2 += LadleId;
  EventLogMessage.messageText2 += " StirrGasType:";
  EventLogMessage.messageText2 += StirrGasType;
  EventLogMessage.messageText2 += " LadlePlugNo:";
  EventLogMessage.messageText2 += LadlePlugNo;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13045;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_BottomStirringEnd( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * LadleId,const char * StirrGasType,const char * LadlePlugNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13045;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Bottom Stirring End  LadleTransferCarId:";
  EventLogMessage.messageText2 = "Bottom Stirring End  LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " LadleId:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText += " StirrGasType:";
  EventLogMessage.messageText += StirrGasType;
  EventLogMessage.messageText += " LadlePlugNo:";
  EventLogMessage.messageText += LadlePlugNo;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " LadleId:";
  EventLogMessage.messageText2 += LadleId;
  EventLogMessage.messageText2 += " StirrGasType:";
  EventLogMessage.messageText2 += StirrGasType;
  EventLogMessage.messageText2 += " LadlePlugNo:";
  EventLogMessage.messageText2 += LadlePlugNo;
  EventLogMessage.messageText2 += " ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_BottomStirringStart( const char * LadleTransferCarId,const char * StirrGasType,const char * LadlePlugNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Bottom Stirring Start  LadleTransferCarId:";
  EventLogMessage.messageText2 = "Bottom Stirring Start  LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " StirrGasType:";
  EventLogMessage.messageText += StirrGasType;
  EventLogMessage.messageText += " LadlePlugNo:";
  EventLogMessage.messageText += LadlePlugNo;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " StirrGasType:";
  EventLogMessage.messageText2 += StirrGasType;
  EventLogMessage.messageText2 += " LadlePlugNo:";
  EventLogMessage.messageText2 += LadlePlugNo;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13046;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_BottomStirringStart( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * StirrGasType,const char * LadlePlugNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13046;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Bottom Stirring Start  LadleTransferCarId:";
  EventLogMessage.messageText2 = "Bottom Stirring Start  LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " StirrGasType:";
  EventLogMessage.messageText += StirrGasType;
  EventLogMessage.messageText += " LadlePlugNo:";
  EventLogMessage.messageText += LadlePlugNo;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " StirrGasType:";
  EventLogMessage.messageText2 += StirrGasType;
  EventLogMessage.messageText2 += " LadlePlugNo:";
  EventLogMessage.messageText2 += LadlePlugNo;
  EventLogMessage.messageText2 += " ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_BottomStirringEnd( const char * LadleTransferCarId,const char * StirrGasType,const char * LadlePlugNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Bottom Stirring End  LadleTransferCarId:";
  EventLogMessage.messageText2 = "Bottom Stirring End  LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " StirrGasType:";
  EventLogMessage.messageText += StirrGasType;
  EventLogMessage.messageText += " LadlePlugNo:";
  EventLogMessage.messageText += LadlePlugNo;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " StirrGasType:";
  EventLogMessage.messageText2 += StirrGasType;
  EventLogMessage.messageText2 += " LadlePlugNo:";
  EventLogMessage.messageText2 += LadlePlugNo;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13047;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_BottomStirringEnd( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * StirrGasType,const char * LadlePlugNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13047;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Bottom Stirring End  LadleTransferCarId:";
  EventLogMessage.messageText2 = "Bottom Stirring End  LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " StirrGasType:";
  EventLogMessage.messageText += StirrGasType;
  EventLogMessage.messageText += " LadlePlugNo:";
  EventLogMessage.messageText += LadlePlugNo;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " StirrGasType:";
  EventLogMessage.messageText2 += StirrGasType;
  EventLogMessage.messageText2 += " LadlePlugNo:";
  EventLogMessage.messageText2 += LadlePlugNo;
  EventLogMessage.messageText2 += " ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_HMISetUpOfHeat()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "HMI Set Up Of Heat";
  EventLogMessage.messageText2 = "HMI Set Up Of Heat";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13048;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_HMISetUpOfHeat( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13048;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "HMI Set Up Of Heat";
  EventLogMessage.messageText2 = "HMI Set Up Of Heat";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_HMIResetOfHeat()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "HMI Reset Of Heat";
  EventLogMessage.messageText2 = "HMI Reset Of Heat";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13049;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_HMIResetOfHeat( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13049;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "HMI Reset Of Heat";
  EventLogMessage.messageText2 = "HMI Reset Of Heat";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ParameterUpdate( const char * ParaArea,const char * ParaProcPT)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Parameter Update ParaArea:";
  EventLogMessage.messageText2 = "Parameter Update ParaArea:";
  EventLogMessage.messageText += ParaArea;
  EventLogMessage.messageText += "  ParaProcPT:";
  EventLogMessage.messageText += ParaProcPT;
  EventLogMessage.messageText2 += ParaArea;
  EventLogMessage.messageText2 += "  ParaProcPT:";
  EventLogMessage.messageText2 += ParaProcPT;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13050;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ParameterUpdate( sEventLogMessage &EventLogMessage, const char * ParaArea,const char * ParaProcPT)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13050;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Parameter Update ParaArea:";
  EventLogMessage.messageText2 = "Parameter Update ParaArea:";
  EventLogMessage.messageText += ParaArea;
  EventLogMessage.messageText += "  ParaProcPT:";
  EventLogMessage.messageText += ParaProcPT;
  EventLogMessage.messageText2 += ParaArea;
  EventLogMessage.messageText2 += "  ParaProcPT:";
  EventLogMessage.messageText2 += ParaProcPT;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_GenParameterUpdate( const char * ParaArea,const char * ParaProcPT)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "General Parameter Update ParaArea:";
  EventLogMessage.messageText2 = "General Parameter Update ParaArea:";
  EventLogMessage.messageText += ParaArea;
  EventLogMessage.messageText += "  ParaProcPT:";
  EventLogMessage.messageText += ParaProcPT;
  EventLogMessage.messageText2 += ParaArea;
  EventLogMessage.messageText2 += "  ParaProcPT:";
  EventLogMessage.messageText2 += ParaProcPT;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13051;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_GenParameterUpdate( sEventLogMessage &EventLogMessage, const char * ParaArea,const char * ParaProcPT)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13051;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "General Parameter Update ParaArea:";
  EventLogMessage.messageText2 = "General Parameter Update ParaArea:";
  EventLogMessage.messageText += ParaArea;
  EventLogMessage.messageText += "  ParaProcPT:";
  EventLogMessage.messageText += ParaProcPT;
  EventLogMessage.messageText2 += ParaArea;
  EventLogMessage.messageText2 += "  ParaProcPT:";
  EventLogMessage.messageText2 += ParaProcPT;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_HeatAnnouncement( const char * HeatID,const char * TreatID,const char * PlantID,const char * LadleTransferCarId,const char * LadleId)
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
  EventLogMessage.messageText += " Transfercar:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " Ladle:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at Plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.messageText2 += " Transfercar:";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " Ladle:";
  EventLogMessage.messageText2 += LadleId;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13052;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_HeatAnnouncement( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID,const char * LadleTransferCarId,const char * LadleId)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13052;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Heat Announcement of ";
  EventLogMessage.messageText2 = "Heat Announcement of ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at Plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText += " Transfercar:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " Ladle:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at Plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.messageText2 += " Transfercar:";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " Ladle:";
  EventLogMessage.messageText2 += LadleId;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_HeatAnnouncementOffline( const char * HeatID,const char * TreatID,const char * PlantID,const char * LadleTransferCarId,const char * LadleId)
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
  EventLogMessage.messageText += " Transfercar:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " Ladle:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at Plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.messageText2 += " Transfercar:";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " Ladle:";
  EventLogMessage.messageText2 += LadleId;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13053;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_HeatAnnouncementOffline( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID,const char * LadleTransferCarId,const char * LadleId)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13053;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Heat Announcement Offline of ";
  EventLogMessage.messageText2 = "Heat Announcement Offline of ";
  EventLogMessage.messageText += HeatID;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText += TreatID;
  EventLogMessage.messageText += " at Plant ";
  EventLogMessage.messageText += PlantID;
  EventLogMessage.messageText += " Transfercar:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " Ladle:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at Plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.messageText2 += " Transfercar:";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " Ladle:";
  EventLogMessage.messageText2 += LadleId;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_HeatAnnounceStatus( const char * HeatAnnounceStatus,const char * HeatID,const char * TreatID,const char * PlantID)
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
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13054;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_HeatAnnounceStatus( sEventLogMessage &EventLogMessage, const char * HeatAnnounceStatus,const char * HeatID,const char * TreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13054;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
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

long CSMC_EventLogLF::EL_HeatCancellation( const char * HeatID,const char * TreatID,const char * PlantID)
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
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13055;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_HeatCancellation( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13055;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
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

long CSMC_EventLogLF::EL_HeatDeparture( const char * HeatID,const char * TreatID,const char * PlantID)
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
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13056;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_HeatDeparture( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13056;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
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

long CSMC_EventLogLF::EL_HeatStart( const char * HeatID,const char * TreatID,const char * PlantID)
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
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13057;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_HeatStart( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13057;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
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

long CSMC_EventLogLF::EL_HeatEnd( const char * HeatID,const char * TreatID,const char * PlantID)
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
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13058;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_HeatEnd( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13058;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
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

long CSMC_EventLogLF::EL_CleanlinessStirring( const char * PhaseElecAct,const char * PhaseStirrAct)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Cleanliness Stirring PhaseElecAct:";
  EventLogMessage.messageText2 = "Cleanliness Stirring PhaseElecAct:";
  EventLogMessage.messageText += PhaseElecAct;
  EventLogMessage.messageText += " PhaseStirrAct:";
  EventLogMessage.messageText += PhaseStirrAct;
  EventLogMessage.messageText2 += PhaseElecAct;
  EventLogMessage.messageText2 += " PhaseStirrAct:";
  EventLogMessage.messageText2 += PhaseStirrAct;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13059;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_CleanlinessStirring( sEventLogMessage &EventLogMessage, const char * PhaseElecAct,const char * PhaseStirrAct)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13059;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Cleanliness Stirring PhaseElecAct:";
  EventLogMessage.messageText2 = "Cleanliness Stirring PhaseElecAct:";
  EventLogMessage.messageText += PhaseElecAct;
  EventLogMessage.messageText += " PhaseStirrAct:";
  EventLogMessage.messageText += PhaseStirrAct;
  EventLogMessage.messageText2 += PhaseElecAct;
  EventLogMessage.messageText2 += " PhaseStirrAct:";
  EventLogMessage.messageText2 += PhaseStirrAct;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_CoolingStirring( const char * PhaseElecAct,const char * PhaseStirrAct)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Cooling Stirring PhaseElecAct:";
  EventLogMessage.messageText2 = "Cooling Stirring PhaseElecAct:";
  EventLogMessage.messageText += PhaseElecAct;
  EventLogMessage.messageText += " PhaseStirrAct:";
  EventLogMessage.messageText += PhaseStirrAct;
  EventLogMessage.messageText2 += PhaseElecAct;
  EventLogMessage.messageText2 += " PhaseStirrAct:";
  EventLogMessage.messageText2 += PhaseStirrAct;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13060;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_CoolingStirring( sEventLogMessage &EventLogMessage, const char * PhaseElecAct,const char * PhaseStirrAct)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13060;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Cooling Stirring PhaseElecAct:";
  EventLogMessage.messageText2 = "Cooling Stirring PhaseElecAct:";
  EventLogMessage.messageText += PhaseElecAct;
  EventLogMessage.messageText += " PhaseStirrAct:";
  EventLogMessage.messageText += PhaseStirrAct;
  EventLogMessage.messageText2 += PhaseElecAct;
  EventLogMessage.messageText2 += " PhaseStirrAct:";
  EventLogMessage.messageText2 += PhaseStirrAct;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_DelayStatus( const char * DelayPlant,const char * DelayCode,const char * DelayStartDate,const char * DelayEndDate,const char * DelayDescription)
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
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13061;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_DelayStatus( sEventLogMessage &EventLogMessage, const char * DelayPlant,const char * DelayCode,const char * DelayStartDate,const char * DelayEndDate,const char * DelayDescription)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13061;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
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

long CSMC_EventLogLF::EL_FinalHeating( const char * PhaseElecAct,const char * PhaseStirrAct)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Final Heating  PhaseElecAct:";
  EventLogMessage.messageText2 = "Final Heating  PhaseElecAct:";
  EventLogMessage.messageText += PhaseElecAct;
  EventLogMessage.messageText += " PhaseStirrAct:";
  EventLogMessage.messageText += PhaseStirrAct;
  EventLogMessage.messageText2 += PhaseElecAct;
  EventLogMessage.messageText2 += " PhaseStirrAct:";
  EventLogMessage.messageText2 += PhaseStirrAct;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13062;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_FinalHeating( sEventLogMessage &EventLogMessage, const char * PhaseElecAct,const char * PhaseStirrAct)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13062;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Final Heating  PhaseElecAct:";
  EventLogMessage.messageText2 = "Final Heating  PhaseElecAct:";
  EventLogMessage.messageText += PhaseElecAct;
  EventLogMessage.messageText += " PhaseStirrAct:";
  EventLogMessage.messageText += PhaseStirrAct;
  EventLogMessage.messageText2 += PhaseElecAct;
  EventLogMessage.messageText2 += " PhaseStirrAct:";
  EventLogMessage.messageText2 += PhaseStirrAct;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_InitialHeating( const char * PhaseElecAct,const char * PhaseStirrAct)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Initial Heating  PhaseElecAct:";
  EventLogMessage.messageText2 = "Initial Heating  PhaseElecAct:";
  EventLogMessage.messageText += PhaseElecAct;
  EventLogMessage.messageText += " PhaseStirrAct:";
  EventLogMessage.messageText += PhaseStirrAct;
  EventLogMessage.messageText2 += PhaseElecAct;
  EventLogMessage.messageText2 += " PhaseStirrAct:";
  EventLogMessage.messageText2 += PhaseStirrAct;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13063;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_InitialHeating( sEventLogMessage &EventLogMessage, const char * PhaseElecAct,const char * PhaseStirrAct)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13063;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Initial Heating  PhaseElecAct:";
  EventLogMessage.messageText2 = "Initial Heating  PhaseElecAct:";
  EventLogMessage.messageText += PhaseElecAct;
  EventLogMessage.messageText += " PhaseStirrAct:";
  EventLogMessage.messageText += PhaseStirrAct;
  EventLogMessage.messageText2 += PhaseElecAct;
  EventLogMessage.messageText2 += " PhaseStirrAct:";
  EventLogMessage.messageText2 += PhaseStirrAct;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_MainHeating( const char * PhaseElecAct,const char * PhaseStirrAct)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Main Heating  PhaseElecAct:";
  EventLogMessage.messageText2 = "Main Heating  PhaseElecAct:";
  EventLogMessage.messageText += PhaseElecAct;
  EventLogMessage.messageText += " PhaseStirrAct:";
  EventLogMessage.messageText += PhaseStirrAct;
  EventLogMessage.messageText2 += PhaseElecAct;
  EventLogMessage.messageText2 += " PhaseStirrAct:";
  EventLogMessage.messageText2 += PhaseStirrAct;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13064;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_MainHeating( sEventLogMessage &EventLogMessage, const char * PhaseElecAct,const char * PhaseStirrAct)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13064;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Main Heating  PhaseElecAct:";
  EventLogMessage.messageText2 = "Main Heating  PhaseElecAct:";
  EventLogMessage.messageText += PhaseElecAct;
  EventLogMessage.messageText += " PhaseStirrAct:";
  EventLogMessage.messageText += PhaseStirrAct;
  EventLogMessage.messageText2 += PhaseElecAct;
  EventLogMessage.messageText2 += " PhaseStirrAct:";
  EventLogMessage.messageText2 += PhaseStirrAct;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SoftStirring( const char * PhaseElecAct,const char * PhaseStirrAct)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Soft Stirring  PhaseElecAct:";
  EventLogMessage.messageText2 = "Soft Stirring  PhaseElecAct:";
  EventLogMessage.messageText += PhaseElecAct;
  EventLogMessage.messageText += " PhaseStirrAct:";
  EventLogMessage.messageText += PhaseStirrAct;
  EventLogMessage.messageText2 += PhaseElecAct;
  EventLogMessage.messageText2 += " PhaseStirrAct:";
  EventLogMessage.messageText2 += PhaseStirrAct;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13065;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SoftStirring( sEventLogMessage &EventLogMessage, const char * PhaseElecAct,const char * PhaseStirrAct)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13065;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Soft Stirring  PhaseElecAct:";
  EventLogMessage.messageText2 = "Soft Stirring  PhaseElecAct:";
  EventLogMessage.messageText += PhaseElecAct;
  EventLogMessage.messageText += " PhaseStirrAct:";
  EventLogMessage.messageText += PhaseStirrAct;
  EventLogMessage.messageText2 += PhaseElecAct;
  EventLogMessage.messageText2 += " PhaseStirrAct:";
  EventLogMessage.messageText2 += PhaseStirrAct;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_CleanlinessStirring()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Cleanliness Stirring started ";
  EventLogMessage.messageText2 = "Cleanliness Stirring started ";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13066;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_CleanlinessStirring( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13066;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Cleanliness Stirring started ";
  EventLogMessage.messageText2 = "Cleanliness Stirring started ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_CoolingStirring()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Cooling Stirring started";
  EventLogMessage.messageText2 = "Cooling Stirring started";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13067;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_CoolingStirring( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13067;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Cooling Stirring started";
  EventLogMessage.messageText2 = "Cooling Stirring started";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_FinalHeating()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Final Heating started";
  EventLogMessage.messageText2 = "Final Heating started";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13068;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_FinalHeating( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13068;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Final Heating started";
  EventLogMessage.messageText2 = "Final Heating started";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_InitialHeating()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Initial Heating started";
  EventLogMessage.messageText2 = "Initial Heating started";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13069;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_InitialHeating( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13069;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Initial Heating started";
  EventLogMessage.messageText2 = "Initial Heating started";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_MainHeating()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Main Heating started";
  EventLogMessage.messageText2 = "Main Heating started";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13070;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_MainHeating( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13070;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Main Heating started";
  EventLogMessage.messageText2 = "Main Heating started";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SoftStirring()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Soft Stirring started";
  EventLogMessage.messageText2 = "Soft Stirring started";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13071;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SoftStirring( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13071;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Soft Stirring started";
  EventLogMessage.messageText2 = "Soft Stirring started";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_TrimmingMaterialDischarged()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Trimming Material Discharged received";
  EventLogMessage.messageText2 = "Trimming Material Discharged received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13072;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_TrimmingMaterialDischarged( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13072;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Trimming Material Discharged received";
  EventLogMessage.messageText2 = "Trimming Material Discharged received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_AlloyingMaterialDischarged()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Alloying Material Discharged received";
  EventLogMessage.messageText2 = "Alloying Material Discharged received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13073;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_AlloyingMaterialDischarged( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13073;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Alloying Material Discharged received";
  EventLogMessage.messageText2 = "Alloying Material Discharged received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangeAimData( const char * TempAim,const char * TreatEndAim)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Aim Data received TempAim:";
  EventLogMessage.messageText2 = "Change Aim Data received TempAim:";
  EventLogMessage.messageText += TempAim;
  EventLogMessage.messageText += " TreatEndAim:";
  EventLogMessage.messageText += TreatEndAim;
  EventLogMessage.messageText2 += TempAim;
  EventLogMessage.messageText2 += " TreatEndAim:";
  EventLogMessage.messageText2 += TreatEndAim;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13074;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangeAimData( sEventLogMessage &EventLogMessage, const char * TempAim,const char * TreatEndAim)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13074;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Aim Data received TempAim:";
  EventLogMessage.messageText2 = "Change Aim Data received TempAim:";
  EventLogMessage.messageText += TempAim;
  EventLogMessage.messageText += " TreatEndAim:";
  EventLogMessage.messageText += TreatEndAim;
  EventLogMessage.messageText2 += TempAim;
  EventLogMessage.messageText2 += " TreatEndAim:";
  EventLogMessage.messageText2 += TreatEndAim;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangeProdPracPointerElec( const char * ElecPracPt,const char * FlagHeatRelated)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Prod Prac Pointer Elec ElecPracPt:";
  EventLogMessage.messageText2 = "Change Prod Prac Pointer Elec ElecPracPt:";
  EventLogMessage.messageText += ElecPracPt;
  EventLogMessage.messageText += " FlagHeatRelated:";
  EventLogMessage.messageText += FlagHeatRelated;
  EventLogMessage.messageText2 += ElecPracPt;
  EventLogMessage.messageText2 += " FlagHeatRelated:";
  EventLogMessage.messageText2 += FlagHeatRelated;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13075;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangeProdPracPointerElec( sEventLogMessage &EventLogMessage, const char * ElecPracPt,const char * FlagHeatRelated)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13075;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Prod Prac Pointer Elec ElecPracPt:";
  EventLogMessage.messageText2 = "Change Prod Prac Pointer Elec ElecPracPt:";
  EventLogMessage.messageText += ElecPracPt;
  EventLogMessage.messageText += " FlagHeatRelated:";
  EventLogMessage.messageText += FlagHeatRelated;
  EventLogMessage.messageText2 += ElecPracPt;
  EventLogMessage.messageText2 += " FlagHeatRelated:";
  EventLogMessage.messageText2 += FlagHeatRelated;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangeProdPracPointerParameter( const char * ParamPracPt,const char * FlagHeatRelated)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Prod Prac Pointer Parameter ParamPracPt:";
  EventLogMessage.messageText2 = "Change Prod Prac Pointer Parameter ParamPracPt:";
  EventLogMessage.messageText += ParamPracPt;
  EventLogMessage.messageText += " FlagHeatRelated:";
  EventLogMessage.messageText += FlagHeatRelated;
  EventLogMessage.messageText2 += ParamPracPt;
  EventLogMessage.messageText2 += " FlagHeatRelated:";
  EventLogMessage.messageText2 += FlagHeatRelated;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13076;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangeProdPracPointerParameter( sEventLogMessage &EventLogMessage, const char * ParamPracPt,const char * FlagHeatRelated)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13076;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Prod Prac Pointer Parameter ParamPracPt:";
  EventLogMessage.messageText2 = "Change Prod Prac Pointer Parameter ParamPracPt:";
  EventLogMessage.messageText += ParamPracPt;
  EventLogMessage.messageText += " FlagHeatRelated:";
  EventLogMessage.messageText += FlagHeatRelated;
  EventLogMessage.messageText2 += ParamPracPt;
  EventLogMessage.messageText2 += " FlagHeatRelated:";
  EventLogMessage.messageText2 += FlagHeatRelated;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangeProdPracPointerRestriction( const char * RestriPracPt,const char * FlagHeatRelated)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Prod Prac Pointer Restriction RestriPracPt:";
  EventLogMessage.messageText2 = "Change Prod Prac Pointer Restriction RestriPracPt:";
  EventLogMessage.messageText += RestriPracPt;
  EventLogMessage.messageText += " FlagHeatRelated:";
  EventLogMessage.messageText += FlagHeatRelated;
  EventLogMessage.messageText2 += RestriPracPt;
  EventLogMessage.messageText2 += " FlagHeatRelated:";
  EventLogMessage.messageText2 += FlagHeatRelated;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13077;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangeProdPracPointerRestriction( sEventLogMessage &EventLogMessage, const char * RestriPracPt,const char * FlagHeatRelated)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13077;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Prod Prac Pointer Restriction RestriPracPt:";
  EventLogMessage.messageText2 = "Change Prod Prac Pointer Restriction RestriPracPt:";
  EventLogMessage.messageText += RestriPracPt;
  EventLogMessage.messageText += " FlagHeatRelated:";
  EventLogMessage.messageText += FlagHeatRelated;
  EventLogMessage.messageText2 += RestriPracPt;
  EventLogMessage.messageText2 += " FlagHeatRelated:";
  EventLogMessage.messageText2 += FlagHeatRelated;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangeProdPracPointerStirring( const char * StirrPracPt,const char * FlagHeatRelated)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Prod Prac Pointer Stirring StirrPracPt:";
  EventLogMessage.messageText2 = "Change Prod Prac Pointer Stirring StirrPracPt:";
  EventLogMessage.messageText += StirrPracPt;
  EventLogMessage.messageText += " FlagHeatRelated:";
  EventLogMessage.messageText += FlagHeatRelated;
  EventLogMessage.messageText2 += StirrPracPt;
  EventLogMessage.messageText2 += " FlagHeatRelated:";
  EventLogMessage.messageText2 += FlagHeatRelated;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13078;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangeProdPracPointerStirring( sEventLogMessage &EventLogMessage, const char * StirrPracPt,const char * FlagHeatRelated)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13078;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Prod Prac Pointer Stirring StirrPracPt:";
  EventLogMessage.messageText2 = "Change Prod Prac Pointer Stirring StirrPracPt:";
  EventLogMessage.messageText += StirrPracPt;
  EventLogMessage.messageText += " FlagHeatRelated:";
  EventLogMessage.messageText += FlagHeatRelated;
  EventLogMessage.messageText2 += StirrPracPt;
  EventLogMessage.messageText2 += " FlagHeatRelated:";
  EventLogMessage.messageText2 += FlagHeatRelated;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_MaterialHandlingReport( const char * Recipename,const char * RecipeSource,const char * RecipeStatus,const char * matCode,double MatWeight)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Material handling for Recipe ";
  EventLogMessage.messageText2 = "Material handling for Recipe ";
  EventLogMessage.messageText += Recipename;
  EventLogMessage.messageText += " Source ";
  EventLogMessage.messageText += RecipeSource;
  EventLogMessage.messageText += " Status ";
  EventLogMessage.messageText += RecipeStatus;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += matCode;
  EventLogMessage.messageText += " ";
  char mstring4[64];
  sprintf( mstring4,"%.3f",MatWeight);
  EventLogMessage.messageText += mstring4;
  EventLogMessage.messageText += "  ";
  EventLogMessage.messageText2 += Recipename;
  EventLogMessage.messageText2 += " Source ";
  EventLogMessage.messageText2 += RecipeSource;
  EventLogMessage.messageText2 += " Status ";
  EventLogMessage.messageText2 += RecipeStatus;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += matCode;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += mstring4;
  EventLogMessage.messageText2 += "  ";
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13079;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_MaterialHandlingReport( sEventLogMessage &EventLogMessage, const char * Recipename,const char * RecipeSource,const char * RecipeStatus,const char * matCode,double MatWeight)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13079;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Material handling for Recipe ";
  EventLogMessage.messageText2 = "Material handling for Recipe ";
  EventLogMessage.messageText += Recipename;
  EventLogMessage.messageText += " Source ";
  EventLogMessage.messageText += RecipeSource;
  EventLogMessage.messageText += " Status ";
  EventLogMessage.messageText += RecipeStatus;
  EventLogMessage.messageText += " - ";
  EventLogMessage.messageText += matCode;
  EventLogMessage.messageText += " ";
  char mstring4[64];
  sprintf( mstring4,"%.3f",MatWeight);
  EventLogMessage.messageText += mstring4;
  EventLogMessage.messageText += "  ";
  EventLogMessage.messageText2 += Recipename;
  EventLogMessage.messageText2 += " Source ";
  EventLogMessage.messageText2 += RecipeSource;
  EventLogMessage.messageText2 += " Status ";
  EventLogMessage.messageText2 += RecipeStatus;
  EventLogMessage.messageText2 += " - ";
  EventLogMessage.messageText2 += matCode;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += mstring4;
  EventLogMessage.messageText2 += "  ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_MaterialHandlingReportCar( const char * CarNo,const char * LadleId,const char * RecipeName,const char * RecipeTarget)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Material handling for CarNo:";
  EventLogMessage.messageText2 = "Material handling for CarNo:";
  EventLogMessage.messageText += CarNo;
  EventLogMessage.messageText += " Ladle:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText += " Recipe:";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " Target:";
  EventLogMessage.messageText += RecipeTarget;
  EventLogMessage.messageText2 += CarNo;
  EventLogMessage.messageText2 += " Ladle:";
  EventLogMessage.messageText2 += LadleId;
  EventLogMessage.messageText2 += " Recipe:";
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " Target:";
  EventLogMessage.messageText2 += RecipeTarget;
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13080;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_MaterialHandlingReportCar( sEventLogMessage &EventLogMessage, const char * CarNo,const char * LadleId,const char * RecipeName,const char * RecipeTarget)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13080;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Material handling for CarNo:";
  EventLogMessage.messageText2 = "Material handling for CarNo:";
  EventLogMessage.messageText += CarNo;
  EventLogMessage.messageText += " Ladle:";
  EventLogMessage.messageText += LadleId;
  EventLogMessage.messageText += " Recipe:";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " Target:";
  EventLogMessage.messageText += RecipeTarget;
  EventLogMessage.messageText2 += CarNo;
  EventLogMessage.messageText2 += " Ladle:";
  EventLogMessage.messageText2 += LadleId;
  EventLogMessage.messageText2 += " Recipe:";
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " Target:";
  EventLogMessage.messageText2 += RecipeTarget;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_RecipeWeighingComplete()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Recipe Weighing Complete received";
  EventLogMessage.messageText2 = "Recipe Weighing Complete received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13081;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_RecipeWeighingComplete( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13081;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Recipe Weighing Complete received";
  EventLogMessage.messageText2 = "Recipe Weighing Complete received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_RecipeWeighingCompleteUpdate()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Recipe Weighing Complete Update received";
  EventLogMessage.messageText2 = "Recipe Weighing Complete Update received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13082;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_RecipeWeighingCompleteUpdate( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13082;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Recipe Weighing Complete Update received";
  EventLogMessage.messageText2 = "Recipe Weighing Complete Update received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_MinChargeableBinWeightUpdate()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Min Chargeable Bin Weight Update received";
  EventLogMessage.messageText2 = "Min Chargeable Bin Weight Update received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13083;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_MinChargeableBinWeightUpdate( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13083;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Min Chargeable Bin Weight Update received";
  EventLogMessage.messageText2 = "Min Chargeable Bin Weight Update received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ErrorTransferCarIdentification( const char * TransferCarId)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error during identification of TransferCarId ";
  EventLogMessage.messageText2 = "Error during identification of TransferCarId ";
  EventLogMessage.messageText += TransferCarId;
  EventLogMessage.messageText2 += TransferCarId;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13084;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ErrorTransferCarIdentification( sEventLogMessage &EventLogMessage, const char * TransferCarId)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13084;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Error during identification of TransferCarId ";
  EventLogMessage.messageText2 = "Error during identification of TransferCarId ";
  EventLogMessage.messageText += TransferCarId;
  EventLogMessage.messageText2 += TransferCarId;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_NoTransferCarInOperatingPosition()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "No transfer car in operating position";
  EventLogMessage.messageText2 = "No transfer car in operating position";
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13085;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_NoTransferCarInOperatingPosition( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13085;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "No transfer car in operating position";
  EventLogMessage.messageText2 = "No transfer car in operating position";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_TimeTempPrevPlantOutOfRange( const char * StdDurAODTap_LFHeatAnn)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Time Temperature Previuos Plant out of Range. Announcement Time minus ";
  EventLogMessage.messageText2 = "Time Temperature Previuos Plant out of Range. Announcement Time minus ";
  EventLogMessage.messageText += StdDurAODTap_LFHeatAnn;
  EventLogMessage.messageText += " minutes";
  EventLogMessage.messageText2 += StdDurAODTap_LFHeatAnn;
  EventLogMessage.messageText2 += " minutes";
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13086;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_TimeTempPrevPlantOutOfRange( sEventLogMessage &EventLogMessage, const char * StdDurAODTap_LFHeatAnn)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13086;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Time Temperature Previuos Plant out of Range. Announcement Time minus ";
  EventLogMessage.messageText2 = "Time Temperature Previuos Plant out of Range. Announcement Time minus ";
  EventLogMessage.messageText += StdDurAODTap_LFHeatAnn;
  EventLogMessage.messageText += " minutes";
  EventLogMessage.messageText2 += StdDurAODTap_LFHeatAnn;
  EventLogMessage.messageText2 += " minutes";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_TransferCarInOperationPos( const char * LadleTransferCarId)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Transfer Car Moved In Operation Position LadleTransferCarId:";
  EventLogMessage.messageText2 = "Transfer Car Moved In Operation Position LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13087;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_TransferCarInOperationPos( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13087;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Transfer Car Moved In Operation Position LadleTransferCarId:";
  EventLogMessage.messageText2 = "Transfer Car Moved In Operation Position LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_TransferCarOutOfOperationPos( const char * LadleTransferCarId)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Transfer Car Moved Out Of Operation Position LadleTransferCarId:";
  EventLogMessage.messageText2 = "Transfer Car Moved Out Of Operation Position LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13088;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_TransferCarOutOfOperationPos( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13088;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Transfer Car Moved Out Of Operation Position LadleTransferCarId:";
  EventLogMessage.messageText2 = "Transfer Car Moved Out Of Operation Position LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_EquipmentIdentification()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error during identification of plant equipment for Heat";
  EventLogMessage.messageText2 = "Error during identification of plant equipment for Heat";
  EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13089;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_EquipmentIdentification( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_warning;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13089;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Error during identification of plant equipment for Heat";
  EventLogMessage.messageText2 = "Error during identification of plant equipment for Heat";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_GantryInTreatmentPosition( int Position,const char * LadleTransferCarId)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Gantry in treatment position ";
  EventLogMessage.messageText2 = "Gantry in treatment position ";
  char mstring0[64];
  sprintf( mstring0,"%d",Position);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " at LadleTransferCarId ";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " at LadleTransferCarId ";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13090;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_GantryInTreatmentPosition( sEventLogMessage &EventLogMessage, int Position,const char * LadleTransferCarId)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13090;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Gantry in treatment position ";
  EventLogMessage.messageText2 = "Gantry in treatment position ";
  char mstring0[64];
  sprintf( mstring0,"%d",Position);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " at LadleTransferCarId ";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " at LadleTransferCarId ";
  EventLogMessage.messageText2 += LadleTransferCarId;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_GantryOutTreatmentPosition()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Gantry out of treatment position";
  EventLogMessage.messageText2 = "Gantry out of treatment position";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13091;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_GantryOutTreatmentPosition( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13091;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Gantry out of treatment position";
  EventLogMessage.messageText2 = "Gantry out of treatment position";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_GantryInMaintenancePosition()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Gantry in maintenance position";
  EventLogMessage.messageText2 = "Gantry in maintenance position";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13092;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_GantryInMaintenancePosition( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13092;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Gantry in maintenance position";
  EventLogMessage.messageText2 = "Gantry in maintenance position";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SlagCeloxMeasurement( const char * MeasFeOConc,const char * MeasMnOConc)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Slag Celox Measurement  MeasFeOConc:";
  EventLogMessage.messageText2 = "Slag Celox Measurement  MeasFeOConc:";
  EventLogMessage.messageText += MeasFeOConc;
  EventLogMessage.messageText += " MeasMnOConc:";
  EventLogMessage.messageText += MeasMnOConc;
  EventLogMessage.messageText2 += MeasFeOConc;
  EventLogMessage.messageText2 += " MeasMnOConc:";
  EventLogMessage.messageText2 += MeasMnOConc;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13093;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SlagCeloxMeasurement( sEventLogMessage &EventLogMessage, const char * MeasFeOConc,const char * MeasMnOConc)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13093;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Slag Celox Measurement  MeasFeOConc:";
  EventLogMessage.messageText2 = "Slag Celox Measurement  MeasFeOConc:";
  EventLogMessage.messageText += MeasFeOConc;
  EventLogMessage.messageText += " MeasMnOConc:";
  EventLogMessage.messageText += MeasMnOConc;
  EventLogMessage.messageText2 += MeasFeOConc;
  EventLogMessage.messageText2 += " MeasMnOConc:";
  EventLogMessage.messageText2 += MeasMnOConc;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SlagWeightCalculation( int SlagWeight)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Slag weight calculation finished with weight ";
  EventLogMessage.messageText2 = "Slag weight calculation finished with weight ";
  char mstring0[64];
  sprintf( mstring0,"%d",SlagWeight);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13094;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SlagWeightCalculation( sEventLogMessage &EventLogMessage, int SlagWeight)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13094;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Slag weight calculation finished with weight ";
  EventLogMessage.messageText2 = "Slag weight calculation finished with weight ";
  char mstring0[64];
  sprintf( mstring0,"%d",SlagWeight);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText2 += mstring0;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ErrorSlagWeightCalculation()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error on slag weight calculation caused by incomplete analysis information";
  EventLogMessage.messageText2 = "Error on slag weight calculation caused by incomplete analysis information";
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.opAckn = 1;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13095;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ErrorSlagWeightCalculation( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13095;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  if (EventLogMessage.opAckn == 0) EventLogMessage.opAckn = 1;
  EventLogMessage.messageText = "Error on slag weight calculation caused by incomplete analysis information";
  EventLogMessage.messageText2 = "Error on slag weight calculation caused by incomplete analysis information";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_CreateTreatmentID()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Create Treatment ID  ";
  EventLogMessage.messageText2 = "Create Treatment ID  ";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13096;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_CreateTreatmentID( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13096;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Create Treatment ID  ";
  EventLogMessage.messageText2 = "Create Treatment ID  ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_RecipeMaterialDischarged( const char * RecipeName,const char * RecipeNo,const char * RecipeSource,const char * MatCode,const char * MatWeight)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Recipe Material Discharged Recipe Name:";
  EventLogMessage.messageText2 = "Recipe Material Discharged Recipe Name:";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " Recipe No:";
  EventLogMessage.messageText += RecipeNo;
  EventLogMessage.messageText += " Source:";
  EventLogMessage.messageText += RecipeSource;
  EventLogMessage.messageText += " MatCode:";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText += " MatWeight:";
  EventLogMessage.messageText += MatWeight;
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " Recipe No:";
  EventLogMessage.messageText2 += RecipeNo;
  EventLogMessage.messageText2 += " Source:";
  EventLogMessage.messageText2 += RecipeSource;
  EventLogMessage.messageText2 += " MatCode:";
  EventLogMessage.messageText2 += MatCode;
  EventLogMessage.messageText2 += " MatWeight:";
  EventLogMessage.messageText2 += MatWeight;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13097;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_RecipeMaterialDischarged( sEventLogMessage &EventLogMessage, const char * RecipeName,const char * RecipeNo,const char * RecipeSource,const char * MatCode,const char * MatWeight)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13097;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Recipe Material Discharged Recipe Name:";
  EventLogMessage.messageText2 = "Recipe Material Discharged Recipe Name:";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " Recipe No:";
  EventLogMessage.messageText += RecipeNo;
  EventLogMessage.messageText += " Source:";
  EventLogMessage.messageText += RecipeSource;
  EventLogMessage.messageText += " MatCode:";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText += " MatWeight:";
  EventLogMessage.messageText += MatWeight;
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " Recipe No:";
  EventLogMessage.messageText2 += RecipeNo;
  EventLogMessage.messageText2 += " Source:";
  EventLogMessage.messageText2 += RecipeSource;
  EventLogMessage.messageText2 += " MatCode:";
  EventLogMessage.messageText2 += MatCode;
  EventLogMessage.messageText2 += " MatWeight:";
  EventLogMessage.messageText2 += MatWeight;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_TempMeasurement( const char * MeasTemp,int TempSampleNo,const char * LadleCarPosition)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Temperature Measurement MeasTemp:";
  EventLogMessage.messageText2 = "Temperature Measurement MeasTemp:";
  EventLogMessage.messageText += MeasTemp;
  EventLogMessage.messageText += " TempSampleNo:";
  char mstring1[64];
  sprintf( mstring1,"%d",TempSampleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " LadleCarPosition:";
  EventLogMessage.messageText += LadleCarPosition;
  EventLogMessage.messageText2 += MeasTemp;
  EventLogMessage.messageText2 += " TempSampleNo:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " LadleCarPosition:";
  EventLogMessage.messageText2 += LadleCarPosition;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13098;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_TempMeasurement( sEventLogMessage &EventLogMessage, const char * MeasTemp,int TempSampleNo,const char * LadleCarPosition)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13098;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Temperature Measurement MeasTemp:";
  EventLogMessage.messageText2 = "Temperature Measurement MeasTemp:";
  EventLogMessage.messageText += MeasTemp;
  EventLogMessage.messageText += " TempSampleNo:";
  char mstring1[64];
  sprintf( mstring1,"%d",TempSampleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " LadleCarPosition:";
  EventLogMessage.messageText += LadleCarPosition;
  EventLogMessage.messageText2 += MeasTemp;
  EventLogMessage.messageText2 += " TempSampleNo:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " LadleCarPosition:";
  EventLogMessage.messageText2 += LadleCarPosition;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_MaterialHandlingReport( const char * CarNo,const char * Recipename,const char * RecipeSource,const char * RecipeStatus,const char * matCode,double MatWeight)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Material handling at Car : ";
  EventLogMessage.messageText2 = "Material handling at Car : ";
  EventLogMessage.messageText += CarNo;
  EventLogMessage.messageText += " for Recipe : ";
  EventLogMessage.messageText += Recipename;
  EventLogMessage.messageText += " Source : ";
  EventLogMessage.messageText += RecipeSource;
  EventLogMessage.messageText += " Status : ";
  EventLogMessage.messageText += RecipeStatus;
  EventLogMessage.messageText += " Material : ";
  EventLogMessage.messageText += matCode;
  EventLogMessage.messageText += " ";
  char mstring5[64];
  sprintf( mstring5,"%.3f",MatWeight);
  EventLogMessage.messageText += mstring5;
  EventLogMessage.messageText += "  ";
  EventLogMessage.messageText2 += CarNo;
  EventLogMessage.messageText2 += " for Recipe : ";
  EventLogMessage.messageText2 += Recipename;
  EventLogMessage.messageText2 += " Source : ";
  EventLogMessage.messageText2 += RecipeSource;
  EventLogMessage.messageText2 += " Status : ";
  EventLogMessage.messageText2 += RecipeStatus;
  EventLogMessage.messageText2 += " Material : ";
  EventLogMessage.messageText2 += matCode;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += mstring5;
  EventLogMessage.messageText2 += "  ";
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13099;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_MaterialHandlingReport( sEventLogMessage &EventLogMessage, const char * CarNo,const char * Recipename,const char * RecipeSource,const char * RecipeStatus,const char * matCode,double MatWeight)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13099;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Material handling at Car : ";
  EventLogMessage.messageText2 = "Material handling at Car : ";
  EventLogMessage.messageText += CarNo;
  EventLogMessage.messageText += " for Recipe : ";
  EventLogMessage.messageText += Recipename;
  EventLogMessage.messageText += " Source : ";
  EventLogMessage.messageText += RecipeSource;
  EventLogMessage.messageText += " Status : ";
  EventLogMessage.messageText += RecipeStatus;
  EventLogMessage.messageText += " Material : ";
  EventLogMessage.messageText += matCode;
  EventLogMessage.messageText += " ";
  char mstring5[64];
  sprintf( mstring5,"%.3f",MatWeight);
  EventLogMessage.messageText += mstring5;
  EventLogMessage.messageText += "  ";
  EventLogMessage.messageText2 += CarNo;
  EventLogMessage.messageText2 += " for Recipe : ";
  EventLogMessage.messageText2 += Recipename;
  EventLogMessage.messageText2 += " Source : ";
  EventLogMessage.messageText2 += RecipeSource;
  EventLogMessage.messageText2 += " Status : ";
  EventLogMessage.messageText2 += RecipeStatus;
  EventLogMessage.messageText2 += " Material : ";
  EventLogMessage.messageText2 += matCode;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += mstring5;
  EventLogMessage.messageText2 += "  ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangeProdPracPointerElec( const char * ProdPracPointer)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Prod Prac Pointer Electric to ";
  EventLogMessage.messageText2 = "Change Prod Prac Pointer Electric to ";
  EventLogMessage.messageText += ProdPracPointer;
  EventLogMessage.messageText2 += ProdPracPointer;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13100;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangeProdPracPointerElec( sEventLogMessage &EventLogMessage, const char * ProdPracPointer)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13100;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Prod Prac Pointer Electric to ";
  EventLogMessage.messageText2 = "Change Prod Prac Pointer Electric to ";
  EventLogMessage.messageText += ProdPracPointer;
  EventLogMessage.messageText2 += ProdPracPointer;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangeProdPracPointerParameter( const char * ProdPracPointer)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Prod Prac Pointer Parameter to ";
  EventLogMessage.messageText2 = "Change Prod Prac Pointer Parameter to ";
  EventLogMessage.messageText += ProdPracPointer;
  EventLogMessage.messageText2 += ProdPracPointer;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13101;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangeProdPracPointerParameter( sEventLogMessage &EventLogMessage, const char * ProdPracPointer)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13101;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Prod Prac Pointer Parameter to ";
  EventLogMessage.messageText2 = "Change Prod Prac Pointer Parameter to ";
  EventLogMessage.messageText += ProdPracPointer;
  EventLogMessage.messageText2 += ProdPracPointer;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangeProdPracPointerRestriction( const char * ProdPracPointer)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Prod Prac Pointer Restriction to ";
  EventLogMessage.messageText2 = "Change Prod Prac Pointer Restriction to ";
  EventLogMessage.messageText += ProdPracPointer;
  EventLogMessage.messageText2 += ProdPracPointer;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13102;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangeProdPracPointerRestriction( sEventLogMessage &EventLogMessage, const char * ProdPracPointer)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13102;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Prod Prac Pointer Restriction to ";
  EventLogMessage.messageText2 = "Change Prod Prac Pointer Restriction to ";
  EventLogMessage.messageText += ProdPracPointer;
  EventLogMessage.messageText2 += ProdPracPointer;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangeProdPracPointerStirring( const char * ProdPracPointer)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Prod Prac Pointer Stirring to ";
  EventLogMessage.messageText2 = "Change Prod Prac Pointer Stirring to ";
  EventLogMessage.messageText += ProdPracPointer;
  EventLogMessage.messageText2 += ProdPracPointer;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13103;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangeProdPracPointerStirring( sEventLogMessage &EventLogMessage, const char * ProdPracPointer)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13103;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Prod Prac Pointer Stirring to ";
  EventLogMessage.messageText2 = "Change Prod Prac Pointer Stirring to ";
  EventLogMessage.messageText += ProdPracPointer;
  EventLogMessage.messageText2 += ProdPracPointer;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SetComputerModeManual( const char * LadleTransferCarId,const char * Device)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Set Computer Mode received LadleTransferCarId:";
  EventLogMessage.messageText2 = "Set Computer Mode received LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " Status : Manual";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " Device:";
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " Status : Manual";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13104;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SetComputerModeManual( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * Device)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13104;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Set Computer Mode received LadleTransferCarId:";
  EventLogMessage.messageText2 = "Set Computer Mode received LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " Status : Manual";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " Device:";
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " Status : Manual";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SetComputerModeAutomatic( const char * LadleTransferCarId,const char * Device)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Set Computer Mode received LadleTransferCarId:";
  EventLogMessage.messageText2 = "Set Computer Mode received LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " Status : Automatic";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " Device:";
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " Status : Automatic";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13105;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SetComputerModeAutomatic( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * Device)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13105;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Set Computer Mode received LadleTransferCarId:";
  EventLogMessage.messageText2 = "Set Computer Mode received LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " Status : Automatic";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " Device:";
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " Status : Automatic";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SetComputerModeDynamic( const char * LadleTransferCarId,const char * Device)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Set Computer Mode received LadleTransferCarId:";
  EventLogMessage.messageText2 = "Set Computer Mode received LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " Status : Dynamic";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " Device:";
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " Status : Dynamic";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13106;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SetComputerModeDynamic( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * Device)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13106;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Set Computer Mode received LadleTransferCarId:";
  EventLogMessage.messageText2 = "Set Computer Mode received LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " Status : Dynamic";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " Device:";
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " Status : Dynamic";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SetComputerModePattern( const char * LadleTransferCarId,const char * Device)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Set Computer Mode received LadleTransferCarId:";
  EventLogMessage.messageText2 = "Set Computer Mode received LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " Status : Pattern";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " Device:";
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " Status : Pattern";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13107;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_SetComputerModePattern( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * Device)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13107;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Set Computer Mode received LadleTransferCarId:";
  EventLogMessage.messageText2 = "Set Computer Mode received LadleTransferCarId:";
  EventLogMessage.messageText += LadleTransferCarId;
  EventLogMessage.messageText += " Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " Status : Pattern";
  EventLogMessage.messageText2 += LadleTransferCarId;
  EventLogMessage.messageText2 += " Device:";
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " Status : Pattern";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_DesulphurizationStirring( const char * PhaseElecAct,const char * PhaseStirrAct)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Desulphurization Stirring without material addition PhaseElecAct:";
  EventLogMessage.messageText2 = "Desulphurization Stirring without material addition PhaseElecAct:";
  EventLogMessage.messageText += PhaseElecAct;
  EventLogMessage.messageText += " PhaseStirrAct:";
  EventLogMessage.messageText += PhaseStirrAct;
  EventLogMessage.messageText2 += PhaseElecAct;
  EventLogMessage.messageText2 += " PhaseStirrAct:";
  EventLogMessage.messageText2 += PhaseStirrAct;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13108;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_DesulphurizationStirring( sEventLogMessage &EventLogMessage, const char * PhaseElecAct,const char * PhaseStirrAct)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13108;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Desulphurization Stirring without material addition PhaseElecAct:";
  EventLogMessage.messageText2 = "Desulphurization Stirring without material addition PhaseElecAct:";
  EventLogMessage.messageText += PhaseElecAct;
  EventLogMessage.messageText += " PhaseStirrAct:";
  EventLogMessage.messageText += PhaseStirrAct;
  EventLogMessage.messageText2 += PhaseElecAct;
  EventLogMessage.messageText2 += " PhaseStirrAct:";
  EventLogMessage.messageText2 += PhaseStirrAct;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_DesulphurizationStirring()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Desulphurization Stirring without material addition started";
  EventLogMessage.messageText2 = "Desulphurization Stirring without material addition started ";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13109;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_DesulphurizationStirring( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13109;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Desulphurization Stirring without material addition started";
  EventLogMessage.messageText2 = "Desulphurization Stirring without material addition started ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangeAimData( const char * Steelgrade,const char * TempAim,const char * TreatEndAim,const char * AimWeight)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Aim Data received Steelgrade:";
  EventLogMessage.messageText2 = "Change Aim Data received Steelgrade:";
  EventLogMessage.messageText += Steelgrade;
  EventLogMessage.messageText += " TempAim:";
  EventLogMessage.messageText += TempAim;
  EventLogMessage.messageText += " TreatEndAim:";
  EventLogMessage.messageText += TreatEndAim;
  EventLogMessage.messageText += " Weight:";
  EventLogMessage.messageText += AimWeight;
  EventLogMessage.messageText2 += Steelgrade;
  EventLogMessage.messageText2 += " TempAim:";
  EventLogMessage.messageText2 += TempAim;
  EventLogMessage.messageText2 += " TreatEndAim:";
  EventLogMessage.messageText2 += TreatEndAim;
  EventLogMessage.messageText2 += " Weight:";
  EventLogMessage.messageText2 += AimWeight;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 13110;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogLF::EL_ChangeAimData( sEventLogMessage &EventLogMessage, const char * Steelgrade,const char * TempAim,const char * TreatEndAim,const char * AimWeight)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 13110;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::LFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Aim Data received Steelgrade:";
  EventLogMessage.messageText2 = "Change Aim Data received Steelgrade:";
  EventLogMessage.messageText += Steelgrade;
  EventLogMessage.messageText += " TempAim:";
  EventLogMessage.messageText += TempAim;
  EventLogMessage.messageText += " TreatEndAim:";
  EventLogMessage.messageText += TreatEndAim;
  EventLogMessage.messageText += " Weight:";
  EventLogMessage.messageText += AimWeight;
  EventLogMessage.messageText2 += Steelgrade;
  EventLogMessage.messageText2 += " TempAim:";
  EventLogMessage.messageText2 += TempAim;
  EventLogMessage.messageText2 += " TreatEndAim:";
  EventLogMessage.messageText2 += TreatEndAim;
  EventLogMessage.messageText2 += " Weight:";
  EventLogMessage.messageText2 += AimWeight;
  return (lRetValue = sendMessage(EventLogMessage));
}
