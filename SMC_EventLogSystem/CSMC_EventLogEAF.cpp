// this is a generated file: do not edit
// use CBSEventLogCodeGenerator to generate it out of excel textfile
#define MAX_MESSAGE_LEN 256 // 255 characters and NULL-Termination!!! DB limit

#include <string>

#include "CSMC_EventLogEAF.h"
#include <CBS_Tasks/cCBS_Time.h>

CSMC_EventLogEAF::CSMC_EventLogEAF(std::string sProcName, std::string sServiceName, std::string sContextName )
: CSMC_EventLogFrame(sProcName,sServiceName,sContextName)
{
}
CSMC_EventLogEAF::~CSMC_EventLogEAF()
{
}

long CSMC_EventLogEAF::EL_SteelAnalysisReceived( const char * SampleID,const char * SampleTime)
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
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14001;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_SteelAnalysisReceived( sEventLogMessage &EventLogMessage, const char * SampleID,const char * SampleTime)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14001;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
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

long CSMC_EventLogEAF::EL_SlagAnalysisReceived( const char * SampleID,const char * SampleTime)
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
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14002;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_SlagAnalysisReceived( sEventLogMessage &EventLogMessage, const char * SampleID,const char * SampleTime)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14002;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
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

long CSMC_EventLogEAF::EL_SteelSampleTaken( const char * SampleID,const char * SampleIDLevel1,const char * SampleLocation)
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
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14003;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_SteelSampleTaken( sEventLogMessage &EventLogMessage, const char * SampleID,const char * SampleIDLevel1,const char * SampleLocation)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14003;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
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

long CSMC_EventLogEAF::EL_SlagSampleTaken( const char * SampleID,const char * SampleIDLevel1,const char * SampleLocation)
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
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14004;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_SlagSampleTaken( sEventLogMessage &EventLogMessage, const char * SampleID,const char * SampleIDLevel1,const char * SampleLocation)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14004;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
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

long CSMC_EventLogEAF::EL_ChangeLiquidAdditionData()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change liquid addition data";
  EventLogMessage.messageText2 = "Change liquid addition data";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14005;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeLiquidAdditionData( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14005;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change liquid addition data";
  EventLogMessage.messageText2 = "Change liquid addition data";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_RemoveLiquidAdditionData()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Remove liquid addition data";
  EventLogMessage.messageText2 = "Remove liquid addition data";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14006;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_RemoveLiquidAdditionData( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14006;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Remove liquid addition data";
  EventLogMessage.messageText2 = "Remove liquid addition data";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_MaterialWeighingReport( int MeasWeight,int WeighingType,const char * LadelID,const char * LadelDeslagged)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Material handling report : Actual weight:";
  EventLogMessage.messageText2 = "Material handling report : Actual weight:";
  char mstring0[64];
  sprintf( mstring0,"%d",MeasWeight);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += "  Weighing type:";
  char mstring1[64];
  sprintf( mstring1,"%d",WeighingType);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Ladel:";
  EventLogMessage.messageText += LadelID;
  EventLogMessage.messageText += " Ladle deslagged:";
  EventLogMessage.messageText += LadelDeslagged;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += "  Weighing type:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Ladel:";
  EventLogMessage.messageText2 += LadelID;
  EventLogMessage.messageText2 += " Ladle deslagged:";
  EventLogMessage.messageText2 += LadelDeslagged;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14007;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_MaterialWeighingReport( sEventLogMessage &EventLogMessage, int MeasWeight,int WeighingType,const char * LadelID,const char * LadelDeslagged)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14007;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Material handling report : Actual weight:";
  EventLogMessage.messageText2 = "Material handling report : Actual weight:";
  char mstring0[64];
  sprintf( mstring0,"%d",MeasWeight);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += "  Weighing type:";
  char mstring1[64];
  sprintf( mstring1,"%d",WeighingType);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Ladel:";
  EventLogMessage.messageText += LadelID;
  EventLogMessage.messageText += " Ladle deslagged:";
  EventLogMessage.messageText += LadelDeslagged;
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += "  Weighing type:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Ladel:";
  EventLogMessage.messageText2 += LadelID;
  EventLogMessage.messageText2 += " Ladle deslagged:";
  EventLogMessage.messageText2 += LadelDeslagged;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangePhysicalMatAvailibility( const char * MatCode)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change physical material availability Material:";
  EventLogMessage.messageText2 = "Change physical material availability Material:";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText2 += MatCode;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14008;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangePhysicalMatAvailibility( sEventLogMessage &EventLogMessage, const char * MatCode)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14008;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change physical material availability Material:";
  EventLogMessage.messageText2 = "Change physical material availability Material:";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText2 += MatCode;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HandleUpdatePurpose()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Update Purpose ";
  EventLogMessage.messageText2 = "Update Purpose ";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14009;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HandleUpdatePurpose( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14009;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Update Purpose ";
  EventLogMessage.messageText2 = "Update Purpose ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_MatBatchCharged( const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget,int RecipeStatus)
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
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14010;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_MatBatchCharged( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget,int RecipeStatus)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14010;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
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

long CSMC_EventLogEAF::EL_MatBatchDischarged( const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget,int RecipeStatus)
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
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14011;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_MatBatchDischarged( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget,int RecipeStatus)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14011;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
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

long CSMC_EventLogEAF::EL_DisableSourceRecipe( const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget)
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
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14012;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_DisableSourceRecipe( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14012;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
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

long CSMC_EventLogEAF::EL_EnableSourceRecipe( const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget)
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
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14013;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_EnableSourceRecipe( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14013;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
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

long CSMC_EventLogEAF::EL_RecipeMaterialCharged( const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget)
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
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14014;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_RecipeMaterialCharged( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14014;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
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

long CSMC_EventLogEAF::EL_RecipeMaterialDischarged( const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget)
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
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14015;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_RecipeMaterialDischarged( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14015;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
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

long CSMC_EventLogEAF::EL_ModelResultCode()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Model Result Code received";
  EventLogMessage.messageText2 = "Model Result Code received";
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14016;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ModelResultCode( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14016;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Model Result Code received";
  EventLogMessage.messageText2 = "Model Result Code received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ModelResultActualSetPoints()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Model Result Actual Set Points received";
  EventLogMessage.messageText2 = "Model Result Actual Set Points received";
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14017;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ModelResultActualSetPoints( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14017;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Model Result Actual Set Points received";
  EventLogMessage.messageText2 = "Model Result Actual Set Points received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ModelResultRecipeSetPoints()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Model Result Recipe Set Points received";
  EventLogMessage.messageText2 = "Model Result Recipe Set Points received";
  EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14018;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ModelResultRecipeSetPoints( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_test;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14018;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::ComputerRoom;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Model Result Recipe Set Points received";
  EventLogMessage.messageText2 = "Model Result Recipe Set Points received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_LadleStirringStart()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Ladle Stirring Start received";
  EventLogMessage.messageText2 = "Ladle Stirring Start received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14019;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_LadleStirringStart( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14019;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Ladle Stirring Start received";
  EventLogMessage.messageText2 = "Ladle Stirring Start received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_LadleStirringStop()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Ladle Stirring Stop received";
  EventLogMessage.messageText2 = "Ladle Stirring Stop received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14020;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_LadleStirringStop( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14020;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Ladle Stirring Stop received";
  EventLogMessage.messageText2 = "Ladle Stirring Stop received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_BurnerStart()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Burner Start received";
  EventLogMessage.messageText2 = "Burner Start received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14021;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_BurnerStart( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14021;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Burner Start received";
  EventLogMessage.messageText2 = "Burner Start received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_BurnerStop()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Burner Stop received";
  EventLogMessage.messageText2 = "Burner Stop received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14022;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_BurnerStop( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14022;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Burner Stop received";
  EventLogMessage.messageText2 = "Burner Stop received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_OxygenSideLanceStart()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Oxygen Side Lance Start received";
  EventLogMessage.messageText2 = "Oxygen Side Lance Start received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14023;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_OxygenSideLanceStart( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14023;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Oxygen Side Lance Start received";
  EventLogMessage.messageText2 = "Oxygen Side Lance Start received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_OxygenSideLanceStop()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Oxygen Side Lance Stop received";
  EventLogMessage.messageText2 = "Oxygen Side Lance Stop received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14024;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_OxygenSideLanceStop( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14024;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Oxygen Side Lance Stop received";
  EventLogMessage.messageText2 = "Oxygen Side Lance Stop received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ElectrodesInOperatingPosition()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Electrodes In Operating Position";
  EventLogMessage.messageText2 = "Electrodes In Operating Position";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14025;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ElectrodesInOperatingPosition( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14025;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Electrodes In Operating Position";
  EventLogMessage.messageText2 = "Electrodes In Operating Position";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ElectrodesOutOfOperatingPosition()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Electrodes out of operating position";
  EventLogMessage.messageText2 = "Electrodes out of operating position";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14026;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ElectrodesOutOfOperatingPosition( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14026;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Electrodes out of operating position";
  EventLogMessage.messageText2 = "Electrodes out of operating position";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_FurnaceBreakerOn()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Furnace Breaker On";
  EventLogMessage.messageText2 = "Furnace Breaker On";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14027;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_FurnaceBreakerOn( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14027;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Furnace Breaker On";
  EventLogMessage.messageText2 = "Furnace Breaker On";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_FurnaceBreakerOff()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Furnace Breaker Off";
  EventLogMessage.messageText2 = "Furnace Breaker Off";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14028;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_FurnaceBreakerOff( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14028;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Furnace Breaker Off";
  EventLogMessage.messageText2 = "Furnace Breaker Off";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_PowerOn()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Power On";
  EventLogMessage.messageText2 = "Power On";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14029;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_PowerOn( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14029;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Power On";
  EventLogMessage.messageText2 = "Power On";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_PowerOff()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Power Off";
  EventLogMessage.messageText2 = "Power Off";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14030;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_PowerOff( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14030;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Power Off";
  EventLogMessage.messageText2 = "Power Off";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_TapChangeStart( const char * VoltTapNo,const char * EltrdRegCurve,const char * FurnTapChangOn)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Tap Change Start received VoltTapNo:";
  EventLogMessage.messageText2 = "Tap Change Start received VoltTapNo:";
  EventLogMessage.messageText += VoltTapNo;
  EventLogMessage.messageText += " EltrdRegCurve:";
  EventLogMessage.messageText += EltrdRegCurve;
  EventLogMessage.messageText += " FurnTapChangOn:";
  EventLogMessage.messageText += FurnTapChangOn;
  EventLogMessage.messageText2 += VoltTapNo;
  EventLogMessage.messageText2 += " EltrdRegCurve:";
  EventLogMessage.messageText2 += EltrdRegCurve;
  EventLogMessage.messageText2 += " FurnTapChangOn:";
  EventLogMessage.messageText2 += FurnTapChangOn;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14031;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_TapChangeStart( sEventLogMessage &EventLogMessage, const char * VoltTapNo,const char * EltrdRegCurve,const char * FurnTapChangOn)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14031;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Tap Change Start received VoltTapNo:";
  EventLogMessage.messageText2 = "Tap Change Start received VoltTapNo:";
  EventLogMessage.messageText += VoltTapNo;
  EventLogMessage.messageText += " EltrdRegCurve:";
  EventLogMessage.messageText += EltrdRegCurve;
  EventLogMessage.messageText += " FurnTapChangOn:";
  EventLogMessage.messageText += FurnTapChangOn;
  EventLogMessage.messageText2 += VoltTapNo;
  EventLogMessage.messageText2 += " EltrdRegCurve:";
  EventLogMessage.messageText2 += EltrdRegCurve;
  EventLogMessage.messageText2 += " FurnTapChangOn:";
  EventLogMessage.messageText2 += FurnTapChangOn;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_TapChangeFinished( const char * VoltTapNo,const char * EltrdRegCurve,const char * FurnTapChangOn)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Tap Change Finished received VoltTapNo:";
  EventLogMessage.messageText2 = "Tap Change Finished received VoltTapNo:";
  EventLogMessage.messageText += VoltTapNo;
  EventLogMessage.messageText += " EltrdRegCurve:";
  EventLogMessage.messageText += EltrdRegCurve;
  EventLogMessage.messageText += " FurnTapChangOn:";
  EventLogMessage.messageText += FurnTapChangOn;
  EventLogMessage.messageText2 += VoltTapNo;
  EventLogMessage.messageText2 += " EltrdRegCurve:";
  EventLogMessage.messageText2 += EltrdRegCurve;
  EventLogMessage.messageText2 += " FurnTapChangOn:";
  EventLogMessage.messageText2 += FurnTapChangOn;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14032;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_TapChangeFinished( sEventLogMessage &EventLogMessage, const char * VoltTapNo,const char * EltrdRegCurve,const char * FurnTapChangOn)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14032;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Tap Change Finished received VoltTapNo:";
  EventLogMessage.messageText2 = "Tap Change Finished received VoltTapNo:";
  EventLogMessage.messageText += VoltTapNo;
  EventLogMessage.messageText += " EltrdRegCurve:";
  EventLogMessage.messageText += EltrdRegCurve;
  EventLogMessage.messageText += " FurnTapChangOn:";
  EventLogMessage.messageText += FurnTapChangOn;
  EventLogMessage.messageText2 += VoltTapNo;
  EventLogMessage.messageText2 += " EltrdRegCurve:";
  EventLogMessage.messageText2 += EltrdRegCurve;
  EventLogMessage.messageText2 += " FurnTapChangOn:";
  EventLogMessage.messageText2 += FurnTapChangOn;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ElectrodeRegCurveNum()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Electrode Reguration Curve Number received ";
  EventLogMessage.messageText2 = "Electrode Reguration Curve Number received ";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14033;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ElectrodeRegCurveNum( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14033;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Electrode Reguration Curve Number received ";
  EventLogMessage.messageText2 = "Electrode Reguration Curve Number received ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ManipGasLanceStart( const char * EAFGasLanceNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Manipulation Gas Lance Start received EAFGasLanceNo:";
  EventLogMessage.messageText2 = "Manipulation Gas Lance Start received EAFGasLanceNo:";
  EventLogMessage.messageText += EAFGasLanceNo;
  EventLogMessage.messageText2 += EAFGasLanceNo;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14034;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ManipGasLanceStart( sEventLogMessage &EventLogMessage, const char * EAFGasLanceNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14034;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Manipulation Gas Lance Start received EAFGasLanceNo:";
  EventLogMessage.messageText2 = "Manipulation Gas Lance Start received EAFGasLanceNo:";
  EventLogMessage.messageText += EAFGasLanceNo;
  EventLogMessage.messageText2 += EAFGasLanceNo;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ManipGasLanceStop( const char * EAFGasLanceNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Manipulation Gas Lance Stop received EAFGasLanceNo:";
  EventLogMessage.messageText2 = "Manipulation Gas Lance Stop received EAFGasLanceNo:";
  EventLogMessage.messageText += EAFGasLanceNo;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += EAFGasLanceNo;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14035;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ManipGasLanceStop( sEventLogMessage &EventLogMessage, const char * EAFGasLanceNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14035;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Manipulation Gas Lance Stop received EAFGasLanceNo:";
  EventLogMessage.messageText2 = "Manipulation Gas Lance Stop received EAFGasLanceNo:";
  EventLogMessage.messageText += EAFGasLanceNo;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += EAFGasLanceNo;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ManipGasLanceStop( const char * Device,const char * GasType,double GasValue)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Manipulation Gas Lance Stop received Device:";
  EventLogMessage.messageText2 = "Manipulation Gas Lance Stop received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " GasType:";
  EventLogMessage.messageText += GasType;
  EventLogMessage.messageText += " GasValue:";
  char mstring2[64];
  sprintf( mstring2,"%f",GasValue);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " GasType:";
  EventLogMessage.messageText2 += GasType;
  EventLogMessage.messageText2 += " GasValue:";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14036;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ManipGasLanceStop( sEventLogMessage &EventLogMessage, const char * Device,const char * GasType,double GasValue)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14036;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Manipulation Gas Lance Stop received Device:";
  EventLogMessage.messageText2 = "Manipulation Gas Lance Stop received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " GasType:";
  EventLogMessage.messageText += GasType;
  EventLogMessage.messageText += " GasValue:";
  char mstring2[64];
  sprintf( mstring2,"%f",GasValue);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " GasType:";
  EventLogMessage.messageText2 += GasType;
  EventLogMessage.messageText2 += " GasValue:";
  EventLogMessage.messageText2 += mstring2;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ManipInjectLanceStart( const char * Device,double MatNumber,const char * LanceMatCode)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Manipulation Injection Lance Start received Device:";
  EventLogMessage.messageText2 = "Manipulation Injection Lance Start received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " MatNumber:";
  char mstring1[64];
  sprintf( mstring1,"%f",MatNumber);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " LanceMatCode:";
  EventLogMessage.messageText += LanceMatCode;
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " MatNumber:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " LanceMatCode:";
  EventLogMessage.messageText2 += LanceMatCode;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14037;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ManipInjectLanceStart( sEventLogMessage &EventLogMessage, const char * Device,double MatNumber,const char * LanceMatCode)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14037;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Manipulation Injection Lance Start received Device:";
  EventLogMessage.messageText2 = "Manipulation Injection Lance Start received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " MatNumber:";
  char mstring1[64];
  sprintf( mstring1,"%f",MatNumber);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " LanceMatCode:";
  EventLogMessage.messageText += LanceMatCode;
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " MatNumber:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " LanceMatCode:";
  EventLogMessage.messageText2 += LanceMatCode;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ManipInjectLanceStop( const char * Device,double MatNumber,double LanceVal)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Manipulation Injection Lance Stop received Device:";
  EventLogMessage.messageText2 = "Manipulation Injection Lance Stop received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " MatNumber:";
  char mstring1[64];
  sprintf( mstring1,"%f",MatNumber);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " LanceVal:";
  char mstring2[64];
  sprintf( mstring2,"%f",LanceVal);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " MatNumber:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " LanceVal:";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14038;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ManipInjectLanceStop( sEventLogMessage &EventLogMessage, const char * Device,double MatNumber,double LanceVal)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14038;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Manipulation Injection Lance Stop received Device:";
  EventLogMessage.messageText2 = "Manipulation Injection Lance Stop received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " MatNumber:";
  char mstring1[64];
  sprintf( mstring1,"%f",MatNumber);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " LanceVal:";
  char mstring2[64];
  sprintf( mstring2,"%f",LanceVal);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " MatNumber:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " LanceVal:";
  EventLogMessage.messageText2 += mstring2;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ManipInjectLanceStop( const char * Device,double MatNumber,const char * LanceMatCode)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Manipulation Injection Lance Stop received Device:";
  EventLogMessage.messageText2 = "Manipulation Injection Lance Stop received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " MatNumber:";
  char mstring1[64];
  sprintf( mstring1,"%f",MatNumber);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " LanceMatCode:";
  EventLogMessage.messageText += LanceMatCode;
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " MatNumber:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " LanceMatCode:";
  EventLogMessage.messageText2 += LanceMatCode;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14039;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ManipInjectLanceStop( sEventLogMessage &EventLogMessage, const char * Device,double MatNumber,const char * LanceMatCode)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14039;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Manipulation Injection Lance Stop received Device:";
  EventLogMessage.messageText2 = "Manipulation Injection Lance Stop received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " MatNumber:";
  char mstring1[64];
  sprintf( mstring1,"%f",MatNumber);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " LanceMatCode:";
  EventLogMessage.messageText += LanceMatCode;
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " MatNumber:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " LanceMatCode:";
  EventLogMessage.messageText2 += LanceMatCode;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_CeloxMeasurement()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Celox Measurement received";
  EventLogMessage.messageText2 = "Celox Measurement received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14040;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_CeloxMeasurement( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14040;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Celox Measurement received";
  EventLogMessage.messageText2 = "Celox Measurement received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_TempMeasurement( const char * MeasTemp,const char * MeasO2Conc)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Temp Measurement received MeasTemp:";
  EventLogMessage.messageText2 = "Temp Measurement received MeasTemp:";
  EventLogMessage.messageText += MeasTemp;
  EventLogMessage.messageText += " MeasO2Conc:";
  EventLogMessage.messageText += MeasO2Conc;
  EventLogMessage.messageText2 += MeasTemp;
  EventLogMessage.messageText2 += " MeasO2Conc:";
  EventLogMessage.messageText2 += MeasO2Conc;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14041;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_TempMeasurement( sEventLogMessage &EventLogMessage, const char * MeasTemp,const char * MeasO2Conc)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14041;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Temp Measurement received MeasTemp:";
  EventLogMessage.messageText2 = "Temp Measurement received MeasTemp:";
  EventLogMessage.messageText += MeasTemp;
  EventLogMessage.messageText += " MeasO2Conc:";
  EventLogMessage.messageText += MeasO2Conc;
  EventLogMessage.messageText2 += MeasTemp;
  EventLogMessage.messageText2 += " MeasO2Conc:";
  EventLogMessage.messageText2 += MeasO2Conc;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_OxygenMeasurement()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Oxygen Measurement received";
  EventLogMessage.messageText2 = "Oxygen Measurement received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14042;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_OxygenMeasurement( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14042;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Oxygen Measurement received";
  EventLogMessage.messageText2 = "Oxygen Measurement received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_DeslaggingStart()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Deslagging Start received";
  EventLogMessage.messageText2 = "Deslagging Start received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14043;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_DeslaggingStart( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14043;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Deslagging Start received";
  EventLogMessage.messageText2 = "Deslagging Start received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_DeslaggingEnd()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Deslagging End received";
  EventLogMessage.messageText2 = "Deslagging End received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14044;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_DeslaggingEnd( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14044;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Deslagging End received";
  EventLogMessage.messageText2 = "Deslagging End received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_DoorOpened( const char * SlagDoorOpen)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Door Opened received SlagDoorOpen:";
  EventLogMessage.messageText2 = "Door Opened received SlagDoorOpen:";
  EventLogMessage.messageText += SlagDoorOpen;
  EventLogMessage.messageText2 += SlagDoorOpen;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14045;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_DoorOpened( sEventLogMessage &EventLogMessage, const char * SlagDoorOpen)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14045;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Door Opened received SlagDoorOpen:";
  EventLogMessage.messageText2 = "Door Opened received SlagDoorOpen:";
  EventLogMessage.messageText += SlagDoorOpen;
  EventLogMessage.messageText2 += SlagDoorOpen;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_DoorClosed( const char * SlagDoorOpen)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Door Closed received SlagDoorOpen:";
  EventLogMessage.messageText2 = "Door Closed received SlagDoorOpen:";
  EventLogMessage.messageText += SlagDoorOpen;
  EventLogMessage.messageText2 += SlagDoorOpen;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14046;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_DoorClosed( sEventLogMessage &EventLogMessage, const char * SlagDoorOpen)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14046;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Door Closed received SlagDoorOpen:";
  EventLogMessage.messageText2 = "Door Closed received SlagDoorOpen:";
  EventLogMessage.messageText += SlagDoorOpen;
  EventLogMessage.messageText2 += SlagDoorOpen;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_RoofArrivesInUpPosition( const char * RoofPosUp)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Roof Arrives In Up Position received RoofPosUp:";
  EventLogMessage.messageText2 = "Roof Arrives In Up Position received RoofPosUp:";
  EventLogMessage.messageText += RoofPosUp;
  EventLogMessage.messageText2 += RoofPosUp;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14047;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_RoofArrivesInUpPosition( sEventLogMessage &EventLogMessage, const char * RoofPosUp)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14047;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Roof Arrives In Up Position received RoofPosUp:";
  EventLogMessage.messageText2 = "Roof Arrives In Up Position received RoofPosUp:";
  EventLogMessage.messageText += RoofPosUp;
  EventLogMessage.messageText2 += RoofPosUp;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_RoofArrivesInDownPosition( const char * RoofPosUp)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Roof Arrives In Down Position received RoofPosUp:";
  EventLogMessage.messageText2 = "Roof Arrives In Down Position received RoofPosUp:";
  EventLogMessage.messageText += RoofPosUp;
  EventLogMessage.messageText2 += RoofPosUp;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14048;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_RoofArrivesInDownPosition( sEventLogMessage &EventLogMessage, const char * RoofPosUp)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14048;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Roof Arrives In Down Position received RoofPosUp:";
  EventLogMessage.messageText2 = "Roof Arrives In Down Position received RoofPosUp:";
  EventLogMessage.messageText += RoofPosUp;
  EventLogMessage.messageText2 += RoofPosUp;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_GantrySwungIn( const char * GantryPosIn)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Gantry Swung In received GantryPosIn:";
  EventLogMessage.messageText2 = "Gantry Swung In received GantryPosIn:";
  EventLogMessage.messageText += GantryPosIn;
  EventLogMessage.messageText2 += GantryPosIn;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14049;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_GantrySwungIn( sEventLogMessage &EventLogMessage, const char * GantryPosIn)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14049;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Gantry Swung In received GantryPosIn:";
  EventLogMessage.messageText2 = "Gantry Swung In received GantryPosIn:";
  EventLogMessage.messageText += GantryPosIn;
  EventLogMessage.messageText2 += GantryPosIn;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_GantrySwungOut( const char * GantryPosIn)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Gantry Swung Out received GantryPosIn:";
  EventLogMessage.messageText2 = "Gantry Swung Out received GantryPosIn:";
  EventLogMessage.messageText += GantryPosIn;
  EventLogMessage.messageText2 += GantryPosIn;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14050;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_GantrySwungOut( sEventLogMessage &EventLogMessage, const char * GantryPosIn)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14050;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Gantry Swung Out received GantryPosIn:";
  EventLogMessage.messageText2 = "Gantry Swung Out received GantryPosIn:";
  EventLogMessage.messageText += GantryPosIn;
  EventLogMessage.messageText2 += GantryPosIn;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_SetTappingMasses( const char * TappingMass)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Set Tapping Masses received TappingMass:";
  EventLogMessage.messageText2 = "Set Tapping Masses received TappingMass:";
  EventLogMessage.messageText += TappingMass;
  EventLogMessage.messageText2 += TappingMass;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14051;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_SetTappingMasses( sEventLogMessage &EventLogMessage, const char * TappingMass)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14051;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Set Tapping Masses received TappingMass:";
  EventLogMessage.messageText2 = "Set Tapping Masses received TappingMass:";
  EventLogMessage.messageText += TappingMass;
  EventLogMessage.messageText2 += TappingMass;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_TappingStart()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Tapping Start received";
  EventLogMessage.messageText2 = "Tapping Start received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14052;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_TappingStart( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14052;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Tapping Start received";
  EventLogMessage.messageText2 = "Tapping Start received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_TappingEnd()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Tapping End received";
  EventLogMessage.messageText2 = "Tapping End received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14053;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_TappingEnd( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14053;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Tapping End received";
  EventLogMessage.messageText2 = "Tapping End received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HeatAnnouncement( const char * HeatID,const char * TreatID,const char * PlantID)
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
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at Plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14054;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HeatAnnouncement( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14054;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Heat Announcement of ";
  EventLogMessage.messageText2 = "Heat Announcement of ";
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

long CSMC_EventLogEAF::EL_HeatAnnouncementOffline( const char * HeatID,const char * TreatID,const char * PlantID)
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
  EventLogMessage.messageText2 += HeatID;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.messageText2 += TreatID;
  EventLogMessage.messageText2 += " at Plant ";
  EventLogMessage.messageText2 += PlantID;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14055;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HeatAnnouncementOffline( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14055;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Heat Announcement Offline of ";
  EventLogMessage.messageText2 = "Heat Announcement Offline of ";
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

long CSMC_EventLogEAF::EL_HeatAnnounceStatus( const char * HeatAnnounceStatus,const char * HeatID,const char * TreatID,const char * PlantID)
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
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14056;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HeatAnnounceStatus( sEventLogMessage &EventLogMessage, const char * HeatAnnounceStatus,const char * HeatID,const char * TreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14056;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
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

long CSMC_EventLogEAF::EL_HeatCancellation( const char * HeatID,const char * TreatID,const char * PlantID)
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
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14057;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HeatCancellation( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14057;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
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

long CSMC_EventLogEAF::EL_HeatDeparture( const char * HeatID,const char * TreatID,const char * PlantID)
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
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14058;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HeatDeparture( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14058;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
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

long CSMC_EventLogEAF::EL_HeatStart( const char * HeatID,const char * TreatID,const char * PlantID)
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
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14059;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HeatStart( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14059;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
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

long CSMC_EventLogEAF::EL_HeatEnd( const char * HeatID,const char * TreatID,const char * PlantID)
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
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14060;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HeatEnd( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14060;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
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

long CSMC_EventLogEAF::EL_ChangeAimData( const char * Steelgrade,const char * TempAim,const char * TreatEndAim,const char * AimWeight)
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
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14061;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeAimData( sEventLogMessage &EventLogMessage, const char * Steelgrade,const char * TempAim,const char * TreatEndAim,const char * AimWeight)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14061;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
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

long CSMC_EventLogEAF::EL_ChangeHotHeelData()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Hot Heel Data received";
  EventLogMessage.messageText2 = "Change Hot Heel Data received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14062;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeHotHeelData( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14062;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Hot Heel Data received";
  EventLogMessage.messageText2 = "Change Hot Heel Data received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeTapLadleData( const char * TapLadleId,const char * TapLadleStatus)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Tap Ladle Data received TapLadleId:";
  EventLogMessage.messageText2 = "Change Tap Ladle Data received TapLadleId:";
  EventLogMessage.messageText += TapLadleId;
  EventLogMessage.messageText += " TapLadleStatus:";
  EventLogMessage.messageText += TapLadleStatus;
  EventLogMessage.messageText2 += TapLadleId;
  EventLogMessage.messageText2 += " TapLadleStatus:";
  EventLogMessage.messageText2 += TapLadleStatus;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14063;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeTapLadleData( sEventLogMessage &EventLogMessage, const char * TapLadleId,const char * TapLadleStatus)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14063;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Tap Ladle Data received TapLadleId:";
  EventLogMessage.messageText2 = "Change Tap Ladle Data received TapLadleId:";
  EventLogMessage.messageText += TapLadleId;
  EventLogMessage.messageText += " TapLadleStatus:";
  EventLogMessage.messageText += TapLadleStatus;
  EventLogMessage.messageText2 += TapLadleId;
  EventLogMessage.messageText2 += " TapLadleStatus:";
  EventLogMessage.messageText2 += TapLadleStatus;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerElec( const char * EAFPracElecPT,const char * FlagHeatRelated)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Production Practice Pointer Electric received EAFPracElecPT:";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Electric received EAFPracElecPT:";
  EventLogMessage.messageText += EAFPracElecPT;
  EventLogMessage.messageText += " FlagHeatRelated:";
  EventLogMessage.messageText += FlagHeatRelated;
  EventLogMessage.messageText2 += EAFPracElecPT;
  EventLogMessage.messageText2 += " FlagHeatRelated:";
  EventLogMessage.messageText2 += FlagHeatRelated;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14064;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerElec( sEventLogMessage &EventLogMessage, const char * EAFPracElecPT,const char * FlagHeatRelated)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14064;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Production Practice Pointer Electric received EAFPracElecPT:";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Electric received EAFPracElecPT:";
  EventLogMessage.messageText += EAFPracElecPT;
  EventLogMessage.messageText += " FlagHeatRelated:";
  EventLogMessage.messageText += FlagHeatRelated;
  EventLogMessage.messageText2 += EAFPracElecPT;
  EventLogMessage.messageText2 += " FlagHeatRelated:";
  EventLogMessage.messageText2 += FlagHeatRelated;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerInjection( const char * EAFPracInjectPT,const char * FlagHeatRelated)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Production Practice Pointer Injection received EAFPracInjectPT:";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Injection received EAFPracInjectPT:";
  EventLogMessage.messageText += EAFPracInjectPT;
  EventLogMessage.messageText += " FlagHeatRelated:";
  EventLogMessage.messageText += FlagHeatRelated;
  EventLogMessage.messageText2 += EAFPracInjectPT;
  EventLogMessage.messageText2 += " FlagHeatRelated:";
  EventLogMessage.messageText2 += FlagHeatRelated;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14065;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerInjection( sEventLogMessage &EventLogMessage, const char * EAFPracInjectPT,const char * FlagHeatRelated)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14065;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Production Practice Pointer Injection received EAFPracInjectPT:";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Injection received EAFPracInjectPT:";
  EventLogMessage.messageText += EAFPracInjectPT;
  EventLogMessage.messageText += " FlagHeatRelated:";
  EventLogMessage.messageText += FlagHeatRelated;
  EventLogMessage.messageText2 += EAFPracInjectPT;
  EventLogMessage.messageText2 += " FlagHeatRelated:";
  EventLogMessage.messageText2 += FlagHeatRelated;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracDataBurnerOxygen( const char * EAFPracBurnerPT,const char * FlagHeatRelated)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Production Practice Pointer Burner Oxygen received EAFPracBurnerPT:";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Burner Oxygen received EAFPracBurnerPT:";
  EventLogMessage.messageText += EAFPracBurnerPT;
  EventLogMessage.messageText += " FlagHeatRelated:";
  char mstring1[64];
  sprintf( mstring1,"%",FlagHeatRelated);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += EAFPracBurnerPT;
  EventLogMessage.messageText2 += " FlagHeatRelated:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.eventId = 14066;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracDataBurnerOxygen( sEventLogMessage &EventLogMessage, const char * EAFPracBurnerPT,const char * FlagHeatRelated)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14066;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.messageText = "Change Production Practice Pointer Burner Oxygen received EAFPracBurnerPT:";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Burner Oxygen received EAFPracBurnerPT:";
  EventLogMessage.messageText += EAFPracBurnerPT;
  EventLogMessage.messageText += " FlagHeatRelated:";
  char mstring1[64];
  sprintf( mstring1,"%",FlagHeatRelated);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += EAFPracBurnerPT;
  EventLogMessage.messageText2 += " FlagHeatRelated:";
  EventLogMessage.messageText2 += mstring1;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerOxygen( const char * EAFPracLancePT,const char * FlagHeatRelated)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Production Practice Pointer Oxygen received EAFPracLancePT:";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Oxygen received EAFPracLancePT:";
  EventLogMessage.messageText += EAFPracLancePT;
  EventLogMessage.messageText += " FlagHeatRelated:";
  char mstring1[64];
  sprintf( mstring1,"%",FlagHeatRelated);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += EAFPracLancePT;
  EventLogMessage.messageText2 += " FlagHeatRelated:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14067;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerOxygen( sEventLogMessage &EventLogMessage, const char * EAFPracLancePT,const char * FlagHeatRelated)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14067;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Production Practice Pointer Oxygen received EAFPracLancePT:";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Oxygen received EAFPracLancePT:";
  EventLogMessage.messageText += EAFPracLancePT;
  EventLogMessage.messageText += " FlagHeatRelated:";
  char mstring1[64];
  sprintf( mstring1,"%",FlagHeatRelated);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += EAFPracLancePT;
  EventLogMessage.messageText2 += " FlagHeatRelated:";
  EventLogMessage.messageText2 += mstring1;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerParameter( const char * ParaPracPT,const char * FlagHeatRelated)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Production Practice Pointer Parameter received ParaPracPT:";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Parameter received ParaPracPT:";
  EventLogMessage.messageText += ParaPracPT;
  EventLogMessage.messageText += " FlagHeatRelated:";
  EventLogMessage.messageText += FlagHeatRelated;
  EventLogMessage.messageText2 += ParaPracPT;
  EventLogMessage.messageText2 += " FlagHeatRelated:";
  EventLogMessage.messageText2 += FlagHeatRelated;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14068;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerParameter( sEventLogMessage &EventLogMessage, const char * ParaPracPT,const char * FlagHeatRelated)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14068;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Production Practice Pointer Parameter received ParaPracPT:";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Parameter received ParaPracPT:";
  EventLogMessage.messageText += ParaPracPT;
  EventLogMessage.messageText += " FlagHeatRelated:";
  EventLogMessage.messageText += FlagHeatRelated;
  EventLogMessage.messageText2 += ParaPracPT;
  EventLogMessage.messageText2 += " FlagHeatRelated:";
  EventLogMessage.messageText2 += FlagHeatRelated;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerRestriction( const char * RestriPracPt,const char * FlagHeatRelated)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Production Practice Pointer Restriction received RestriPracPt:";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Restriction received RestriPracPt:";
  EventLogMessage.messageText += RestriPracPt;
  EventLogMessage.messageText += " FlagHeatRelated:";
  EventLogMessage.messageText += FlagHeatRelated;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += RestriPracPt;
  EventLogMessage.messageText2 += " FlagHeatRelated:";
  EventLogMessage.messageText2 += FlagHeatRelated;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14069;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerRestriction( sEventLogMessage &EventLogMessage, const char * RestriPracPt,const char * FlagHeatRelated)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14069;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Production Practice Pointer Restriction received RestriPracPt:";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Restriction received RestriPracPt:";
  EventLogMessage.messageText += RestriPracPt;
  EventLogMessage.messageText += " FlagHeatRelated:";
  EventLogMessage.messageText += FlagHeatRelated;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += RestriPracPt;
  EventLogMessage.messageText2 += " FlagHeatRelated:";
  EventLogMessage.messageText2 += FlagHeatRelated;
  EventLogMessage.messageText2 += " ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_CreateTreatmentID()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Create Treatment ID received ";
  EventLogMessage.messageText2 = "Create Treatment ID received ";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14070;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_CreateTreatmentID( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14070;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Create Treatment ID received ";
  EventLogMessage.messageText2 = "Create Treatment ID received ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_DelayStatus( const char * DelayPlant,const char * DelayCode,const char * DelayStartDate,const char * DelayEndDate,const char * DelayDescription)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Delay Status received DelayPlant:";
  EventLogMessage.messageText2 = "Delay Status received DelayPlant:";
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
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14071;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_DelayStatus( sEventLogMessage &EventLogMessage, const char * DelayPlant,const char * DelayCode,const char * DelayStartDate,const char * DelayEndDate,const char * DelayDescription)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14071;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Delay Status received DelayPlant:";
  EventLogMessage.messageText2 = "Delay Status received DelayPlant:";
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

long CSMC_EventLogEAF::EL_HeatScheduleUpdate()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Heat Schedule Update received";
  EventLogMessage.messageText2 = "Heat Schedule Update received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14072;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HeatScheduleUpdate( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14072;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Heat Schedule Update received";
  EventLogMessage.messageText2 = "Heat Schedule Update received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_SetComputerMode( const char * Device,int Status)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Set Computer Mode received Device:";
  EventLogMessage.messageText2 = "Set Computer Mode received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " Status ";
  char mstring1[64];
  sprintf( mstring1,"%d",Status);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " Status ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14073;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_SetComputerMode( sEventLogMessage &EventLogMessage, const char * Device,int Status)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14073;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Set Computer Mode received Device:";
  EventLogMessage.messageText2 = "Set Computer Mode received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " Status ";
  char mstring1[64];
  sprintf( mstring1,"%d",Status);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " Status ";
  EventLogMessage.messageText2 += mstring1;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ActivateWallTempCtrl()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Activate Wall Temperatur Control received";
  EventLogMessage.messageText2 = "Activate Wall Temperatur Control received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14074;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ActivateWallTempCtrl( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14074;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Activate Wall Temperatur Control received";
  EventLogMessage.messageText2 = "Activate Wall Temperatur Control received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_DeactivateWallTempCtrl()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Deactivate Wall Temperatur Control received";
  EventLogMessage.messageText2 = "Deactivate Wall Temperatur Control received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14075;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_DeactivateWallTempCtrl( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14075;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Deactivate Wall Temperatur Control received";
  EventLogMessage.messageText2 = "Deactivate Wall Temperatur Control received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HandleScrapContainerDischarged( const char * ContainerNo,const char * ContainerInSeq,const char * LastScrapContainer)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Handle ScrapContainer Discharged received ContainerNo:";
  EventLogMessage.messageText2 = "Handle ScrapContainer Discharged received ContainerNo:";
  EventLogMessage.messageText += ContainerNo;
  EventLogMessage.messageText += " ContainerInSeq:";
  EventLogMessage.messageText += ContainerInSeq;
  EventLogMessage.messageText += " LastScrapContainer:";
  EventLogMessage.messageText += LastScrapContainer;
  EventLogMessage.messageText2 += ContainerNo;
  EventLogMessage.messageText2 += " ContainerInSeq:";
  EventLogMessage.messageText2 += ContainerInSeq;
  EventLogMessage.messageText2 += " LastScrapContainer:";
  EventLogMessage.messageText2 += LastScrapContainer;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14076;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HandleScrapContainerDischarged( sEventLogMessage &EventLogMessage, const char * ContainerNo,const char * ContainerInSeq,const char * LastScrapContainer)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14076;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Handle ScrapContainer Discharged received ContainerNo:";
  EventLogMessage.messageText2 = "Handle ScrapContainer Discharged received ContainerNo:";
  EventLogMessage.messageText += ContainerNo;
  EventLogMessage.messageText += " ContainerInSeq:";
  EventLogMessage.messageText += ContainerInSeq;
  EventLogMessage.messageText += " LastScrapContainer:";
  EventLogMessage.messageText += LastScrapContainer;
  EventLogMessage.messageText2 += ContainerNo;
  EventLogMessage.messageText2 += " ContainerInSeq:";
  EventLogMessage.messageText2 += ContainerInSeq;
  EventLogMessage.messageText2 += " LastScrapContainer:";
  EventLogMessage.messageText2 += LastScrapContainer;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_MaterialHandlingReport( const char * RecipeName,const char * RecipeSource,const char * RecipeStatus,const char * RecipeNo,const char * RecipeTarget)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Material Handling Report received RecipeName:";
  EventLogMessage.messageText2 = "Material Handling Report received RecipeName:";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " RecipeSource:";
  EventLogMessage.messageText += RecipeSource;
  EventLogMessage.messageText += " RecipeStatus:";
  EventLogMessage.messageText += RecipeStatus;
  EventLogMessage.messageText += " RecipeNo:";
  EventLogMessage.messageText += RecipeNo;
  EventLogMessage.messageText += " RecipeTarget:";
  EventLogMessage.messageText += RecipeTarget;
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " RecipeSource:";
  EventLogMessage.messageText2 += RecipeSource;
  EventLogMessage.messageText2 += " RecipeStatus:";
  EventLogMessage.messageText2 += RecipeStatus;
  EventLogMessage.messageText2 += " RecipeNo:";
  EventLogMessage.messageText2 += RecipeNo;
  EventLogMessage.messageText2 += " RecipeTarget:";
  EventLogMessage.messageText2 += RecipeTarget;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14077;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_MaterialHandlingReport( sEventLogMessage &EventLogMessage, const char * RecipeName,const char * RecipeSource,const char * RecipeStatus,const char * RecipeNo,const char * RecipeTarget)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14077;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Material Handling Report received RecipeName:";
  EventLogMessage.messageText2 = "Material Handling Report received RecipeName:";
  EventLogMessage.messageText += RecipeName;
  EventLogMessage.messageText += " RecipeSource:";
  EventLogMessage.messageText += RecipeSource;
  EventLogMessage.messageText += " RecipeStatus:";
  EventLogMessage.messageText += RecipeStatus;
  EventLogMessage.messageText += " RecipeNo:";
  EventLogMessage.messageText += RecipeNo;
  EventLogMessage.messageText += " RecipeTarget:";
  EventLogMessage.messageText += RecipeTarget;
  EventLogMessage.messageText2 += RecipeName;
  EventLogMessage.messageText2 += " RecipeSource:";
  EventLogMessage.messageText2 += RecipeSource;
  EventLogMessage.messageText2 += " RecipeStatus:";
  EventLogMessage.messageText2 += RecipeStatus;
  EventLogMessage.messageText2 += " RecipeNo:";
  EventLogMessage.messageText2 += RecipeNo;
  EventLogMessage.messageText2 += " RecipeTarget:";
  EventLogMessage.messageText2 += RecipeTarget;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_MaterialHandlingReport( const char * MatCode,double Mass)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Material Handling Report received MatCode:";
  EventLogMessage.messageText2 = "Material Handling Report received MatCode:";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText += " Mass:";
  char mstring1[64];
  sprintf( mstring1,"%f",Mass);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += MatCode;
  EventLogMessage.messageText2 += " Mass:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14078;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_MaterialHandlingReport( sEventLogMessage &EventLogMessage, const char * MatCode,double Mass)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14078;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Material Handling Report received MatCode:";
  EventLogMessage.messageText2 = "Material Handling Report received MatCode:";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText += " Mass:";
  char mstring1[64];
  sprintf( mstring1,"%f",Mass);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += MatCode;
  EventLogMessage.messageText2 += " Mass:";
  EventLogMessage.messageText2 += mstring1;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HandleSetScrapContainerData( const char * ContainerNo,const char * ContainerInSeq,const char * LastScrapContainer)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Handle Set ScrapContainer Data received ContainerNo:";
  EventLogMessage.messageText2 = "Handle Set ScrapContainer Data received ContainerNo:";
  EventLogMessage.messageText += ContainerNo;
  EventLogMessage.messageText += " ContainerInSeq:";
  EventLogMessage.messageText += ContainerInSeq;
  EventLogMessage.messageText += " LastScrapContainer:";
  EventLogMessage.messageText += LastScrapContainer;
  EventLogMessage.messageText2 += ContainerNo;
  EventLogMessage.messageText2 += " ContainerInSeq:";
  EventLogMessage.messageText2 += ContainerInSeq;
  EventLogMessage.messageText2 += " LastScrapContainer:";
  EventLogMessage.messageText2 += LastScrapContainer;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14079;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HandleSetScrapContainerData( sEventLogMessage &EventLogMessage, const char * ContainerNo,const char * ContainerInSeq,const char * LastScrapContainer)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14079;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Handle Set ScrapContainer Data received ContainerNo:";
  EventLogMessage.messageText2 = "Handle Set ScrapContainer Data received ContainerNo:";
  EventLogMessage.messageText += ContainerNo;
  EventLogMessage.messageText += " ContainerInSeq:";
  EventLogMessage.messageText += ContainerInSeq;
  EventLogMessage.messageText += " LastScrapContainer:";
  EventLogMessage.messageText += LastScrapContainer;
  EventLogMessage.messageText2 += ContainerNo;
  EventLogMessage.messageText2 += " ContainerInSeq:";
  EventLogMessage.messageText2 += ContainerInSeq;
  EventLogMessage.messageText2 += " LastScrapContainer:";
  EventLogMessage.messageText2 += LastScrapContainer;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_LiquidAdditionCharged()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Liquid Addition Charged received";
  EventLogMessage.messageText2 = "Liquid Addition Charged received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14080;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_LiquidAdditionCharged( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14080;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Liquid Addition Charged received";
  EventLogMessage.messageText2 = "Liquid Addition Charged received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_LiqMatHandlReport( const char * MeasWeight,const char * WeighingType,const char * LadleId,const char * LadleDeslagged)
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
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14081;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_LiqMatHandlReport( sEventLogMessage &EventLogMessage, const char * MeasWeight,const char * WeighingType,const char * LadleId,const char * LadleDeslagged)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14081;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
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

long CSMC_EventLogEAF::EL_MinChargeableBinWeightUpdate()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Min Chargeable Bin Weight Update received";
  EventLogMessage.messageText2 = "Min Chargeable Bin Weight Update received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14082;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_MinChargeableBinWeightUpdate( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14082;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Min Chargeable Bin Weight Update received";
  EventLogMessage.messageText2 = "Min Chargeable Bin Weight Update received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ParameterUpdate( const char * ParamName,const char * ParamValue)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Parameter Update received ParamName:";
  EventLogMessage.messageText2 = "Parameter Update received ParamName:";
  EventLogMessage.messageText += ParamName;
  EventLogMessage.messageText += " ParamValue:";
  EventLogMessage.messageText += ParamValue;
  EventLogMessage.messageText2 += ParamName;
  EventLogMessage.messageText2 += " ParamValue:";
  EventLogMessage.messageText2 += ParamValue;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14083;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ParameterUpdate( sEventLogMessage &EventLogMessage, const char * ParamName,const char * ParamValue)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14083;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Parameter Update received ParamName:";
  EventLogMessage.messageText2 = "Parameter Update received ParamName:";
  EventLogMessage.messageText += ParamName;
  EventLogMessage.messageText += " ParamValue:";
  EventLogMessage.messageText += ParamValue;
  EventLogMessage.messageText2 += ParamName;
  EventLogMessage.messageText2 += " ParamValue:";
  EventLogMessage.messageText2 += ParamValue;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_MatFeedingStart()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Material Feeding Start received";
  EventLogMessage.messageText2 = "Material Feeding Start received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14084;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_MatFeedingStart( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14084;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Material Feeding Start received";
  EventLogMessage.messageText2 = "Material Feeding Start received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_MatFeedingStop()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Material Feeding Stop received";
  EventLogMessage.messageText2 = "Material Feeding Stop received";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14085;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_MatFeedingStop( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14085;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Material Feeding Stop received";
  EventLogMessage.messageText2 = "Material Feeding Stop received";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ScrapContainerDischargedError( int ContainerInSeq,int ContainerNo)
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
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14086;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ScrapContainerDischargedError( sEventLogMessage &EventLogMessage, int ContainerInSeq,int ContainerNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14086;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
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

long CSMC_EventLogEAF::EL_ScrapContainerAssignmentError( int ContainerInSeq,int ContainerNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error handling ScrapContainer assignment. ContainerInSeq:";
  EventLogMessage.messageText2 = "Error handling ScrapContainer assignment. ContainerInSeq:";
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
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14087;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ScrapContainerAssignmentError( sEventLogMessage &EventLogMessage, int ContainerInSeq,int ContainerNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14087;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Error handling ScrapContainer assignment. ContainerInSeq:";
  EventLogMessage.messageText2 = "Error handling ScrapContainer assignment. ContainerInSeq:";
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

long CSMC_EventLogEAF::EL_ScrapContainerRemoveError( int ContainerInSeq,int ContainerNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error handling remove ScrapContainer. ContainerInSeq:";
  EventLogMessage.messageText2 = "Error handling remove ScrapContainer. ContainerInSeq:";
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
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14088;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ScrapContainerRemoveError( sEventLogMessage &EventLogMessage, int ContainerInSeq,int ContainerNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14088;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Error handling remove ScrapContainer. ContainerInSeq:";
  EventLogMessage.messageText2 = "Error handling remove ScrapContainer. ContainerInSeq:";
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

long CSMC_EventLogEAF::EL_HandleScrapContainerRemove( int ContainerInSeq,int ContainerNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Remove ScrapContainer. ContainerInSeq:";
  EventLogMessage.messageText2 = "Remove ScrapContainer. ContainerInSeq:";
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
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14089;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HandleScrapContainerRemove( sEventLogMessage &EventLogMessage, int ContainerInSeq,int ContainerNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14089;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Remove ScrapContainer. ContainerInSeq:";
  EventLogMessage.messageText2 = "Remove ScrapContainer. ContainerInSeq:";
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

long CSMC_EventLogEAF::EL_HotMetalAssignment( const char * LadleType,int LadleNo,int ChargeSeq)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Hot metal assignment. LadleType: ";
  EventLogMessage.messageText2 = "Hot metal assignment. LadleType: ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " LadleNo: ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Charging SequenceNo: ";
  char mstring2[64];
  sprintf( mstring2,"%d",ChargeSeq);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " LadleNo: ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Charging SequenceNo: ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14090;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HotMetalAssignment( sEventLogMessage &EventLogMessage, const char * LadleType,int LadleNo,int ChargeSeq)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14090;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Hot metal assignment. LadleType: ";
  EventLogMessage.messageText2 = "Hot metal assignment. LadleType: ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " LadleNo: ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Charging SequenceNo: ";
  char mstring2[64];
  sprintf( mstring2,"%d",ChargeSeq);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " LadleNo: ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Charging SequenceNo: ";
  EventLogMessage.messageText2 += mstring2;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HotMetalAssignmentError( const char * LadleType,int LadleNo,int ChargeSeq)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error handling hot metal assignment. LadleType: ";
  EventLogMessage.messageText2 = "Error handling hot metal assignment. LadleType: ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " LadleNo: ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Charging SequenceNo: ";
  char mstring2[64];
  sprintf( mstring2,"%d",ChargeSeq);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " LadleNo: ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Charging SequenceNo: ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14091;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HotMetalAssignmentError( sEventLogMessage &EventLogMessage, const char * LadleType,int LadleNo,int ChargeSeq)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14091;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Error handling hot metal assignment. LadleType: ";
  EventLogMessage.messageText2 = "Error handling hot metal assignment. LadleType: ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " LadleNo: ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Charging SequenceNo: ";
  char mstring2[64];
  sprintf( mstring2,"%d",ChargeSeq);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " LadleNo: ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Charging SequenceNo: ";
  EventLogMessage.messageText2 += mstring2;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HotMetalDischarged( const char * LadleType,int LadleNo,int ChargeSeq,double Weight)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Hot metal discharged. LadleType: ";
  EventLogMessage.messageText2 = "Hot metal discharged. LadleType: ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " LadleNo: ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Charging SequenceNo: ";
  char mstring2[64];
  sprintf( mstring2,"%d",ChargeSeq);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText += " Weight: ";
  char mstring3[64];
  sprintf( mstring3,"%f",Weight);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " LadleNo: ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Charging SequenceNo: ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.messageText2 += " Weight: ";
  EventLogMessage.messageText2 += mstring3;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14092;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HotMetalDischarged( sEventLogMessage &EventLogMessage, const char * LadleType,int LadleNo,int ChargeSeq,double Weight)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14092;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Hot metal discharged. LadleType: ";
  EventLogMessage.messageText2 = "Hot metal discharged. LadleType: ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " LadleNo: ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Charging SequenceNo: ";
  char mstring2[64];
  sprintf( mstring2,"%d",ChargeSeq);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText += " Weight: ";
  char mstring3[64];
  sprintf( mstring3,"%f",Weight);
  EventLogMessage.messageText += mstring3;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " LadleNo: ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Charging SequenceNo: ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.messageText2 += " Weight: ";
  EventLogMessage.messageText2 += mstring3;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HotMetalDischargedError( const char * LadleType,int LadleNo,int ChargeSeq)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error handling hot metal discharged. LadleType: ";
  EventLogMessage.messageText2 = "Error handling hot metal discharged. LadleType: ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " LadleNo: ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Charging SequenceNo: ";
  char mstring2[64];
  sprintf( mstring2,"%d",ChargeSeq);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " LadleNo: ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Charging SequenceNo: ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14093;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HotMetalDischargedError( sEventLogMessage &EventLogMessage, const char * LadleType,int LadleNo,int ChargeSeq)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14093;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Error handling hot metal discharged. LadleType: ";
  EventLogMessage.messageText2 = "Error handling hot metal discharged. LadleType: ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " LadleNo: ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Charging SequenceNo: ";
  char mstring2[64];
  sprintf( mstring2,"%d",ChargeSeq);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " LadleNo: ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Charging SequenceNo: ";
  EventLogMessage.messageText2 += mstring2;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HotMetalData( const char * LadleType,int LadleNo,int ChargeSeq)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Hot metal data update. LadleType: ";
  EventLogMessage.messageText2 = "Hot metal data update. LadleType: ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " LadleNo: ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Charging SequenceNo: ";
  char mstring2[64];
  sprintf( mstring2,"%d",ChargeSeq);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " LadleNo: ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Charging SequenceNo: ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14094;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HotMetalData( sEventLogMessage &EventLogMessage, const char * LadleType,int LadleNo,int ChargeSeq)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14094;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Hot metal data update. LadleType: ";
  EventLogMessage.messageText2 = "Hot metal data update. LadleType: ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " LadleNo: ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Charging SequenceNo: ";
  char mstring2[64];
  sprintf( mstring2,"%d",ChargeSeq);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " LadleNo: ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Charging SequenceNo: ";
  EventLogMessage.messageText2 += mstring2;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HotMetalDataError( const char * LadleType,int LadleNo,int ChargeSeq)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error handling hot metal data update. LadleType: ";
  EventLogMessage.messageText2 = "Error handling hot metal data update. LadleType: ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " LadleNo: ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Charging SequenceNo: ";
  char mstring2[64];
  sprintf( mstring2,"%d",ChargeSeq);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " LadleNo: ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Charging SequenceNo: ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14095;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HotMetalDataError( sEventLogMessage &EventLogMessage, const char * LadleType,int LadleNo,int ChargeSeq)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14095;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Error handling hot metal data update. LadleType: ";
  EventLogMessage.messageText2 = "Error handling hot metal data update. LadleType: ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " LadleNo: ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Charging SequenceNo: ";
  char mstring2[64];
  sprintf( mstring2,"%d",ChargeSeq);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " LadleNo: ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Charging SequenceNo: ";
  EventLogMessage.messageText2 += mstring2;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HotMetalRemove( const char * LadleType,int LadleNo,int ChargeSeq)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Hot metal removed. LadleType: ";
  EventLogMessage.messageText2 = "Hot metal removed. LadleType: ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " LadleNo: ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Charging SequenceNo: ";
  char mstring2[64];
  sprintf( mstring2,"%d",ChargeSeq);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " LadleNo: ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Charging SequenceNo: ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14096;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HotMetalRemove( sEventLogMessage &EventLogMessage, const char * LadleType,int LadleNo,int ChargeSeq)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14096;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Hot metal removed. LadleType: ";
  EventLogMessage.messageText2 = "Hot metal removed. LadleType: ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " LadleNo: ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Charging SequenceNo: ";
  char mstring2[64];
  sprintf( mstring2,"%d",ChargeSeq);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " LadleNo: ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Charging SequenceNo: ";
  EventLogMessage.messageText2 += mstring2;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HotMetalRemoveError( const char * LadleType,int LadleNo,int ChargeSeq)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error remove hot metal. LadleType: ";
  EventLogMessage.messageText2 = "Error remove hot metal. LadleType: ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " LadleNo: ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Charging SequenceNo: ";
  char mstring2[64];
  sprintf( mstring2,"%d",ChargeSeq);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " LadleNo: ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Charging SequenceNo: ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14097;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HotMetalRemoveError( sEventLogMessage &EventLogMessage, const char * LadleType,int LadleNo,int ChargeSeq)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14097;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Error remove hot metal. LadleType: ";
  EventLogMessage.messageText2 = "Error remove hot metal. LadleType: ";
  EventLogMessage.messageText += LadleType;
  EventLogMessage.messageText += " LadleNo: ";
  char mstring1[64];
  sprintf( mstring1,"%d",LadleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " Charging SequenceNo: ";
  char mstring2[64];
  sprintf( mstring2,"%d",ChargeSeq);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += LadleType;
  EventLogMessage.messageText2 += " LadleNo: ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " Charging SequenceNo: ";
  EventLogMessage.messageText2 += mstring2;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ScrapContainerSetDataError( int ContainerInSeq,int ContainerNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error to store ScrapContainer data. ContainerInSeq:";
  EventLogMessage.messageText2 = "Error to store ScrapContainer data. ContainerInSeq:";
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
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14098;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ScrapContainerSetDataError( sEventLogMessage &EventLogMessage, int ContainerInSeq,int ContainerNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14098;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Error to store ScrapContainer data. ContainerInSeq:";
  EventLogMessage.messageText2 = "Error to store ScrapContainer data. ContainerInSeq:";
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

long CSMC_EventLogEAF::EL_HandleSetScrapContainerData( int ContainerInSeq,int ContainerNo)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Handle set ScrapContainer data. ContainerInSeq:";
  EventLogMessage.messageText2 = "Hadle set ScrapContainer data. ContainerInSeq:";
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
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14099;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HandleSetScrapContainerData( sEventLogMessage &EventLogMessage, int ContainerInSeq,int ContainerNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14099;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Handle set ScrapContainer data. ContainerInSeq:";
  EventLogMessage.messageText2 = "Hadle set ScrapContainer data. ContainerInSeq:";
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

long CSMC_EventLogEAF::EL_TapChangeStart( const char * ReactTapNo,const char * VoltTapNo,const char * EltrdRegCurve,const char * FurnTapChangOn)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Tap Change Start received  ReactTapNo:";
  EventLogMessage.messageText2 = "Tap Change Start received  ReactTapNo:";
  EventLogMessage.messageText += ReactTapNo;
  EventLogMessage.messageText += "  VoltTapNo:";
  EventLogMessage.messageText += VoltTapNo;
  EventLogMessage.messageText += " EltrdRegCurve:";
  EventLogMessage.messageText += EltrdRegCurve;
  EventLogMessage.messageText += " FurnTapChangOn:";
  EventLogMessage.messageText += FurnTapChangOn;
  EventLogMessage.messageText2 += ReactTapNo;
  EventLogMessage.messageText2 += "  VoltTapNo:";
  EventLogMessage.messageText2 += VoltTapNo;
  EventLogMessage.messageText2 += " EltrdRegCurve:";
  EventLogMessage.messageText2 += EltrdRegCurve;
  EventLogMessage.messageText2 += " FurnTapChangOn:";
  EventLogMessage.messageText2 += FurnTapChangOn;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14100;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_TapChangeStart( sEventLogMessage &EventLogMessage, const char * ReactTapNo,const char * VoltTapNo,const char * EltrdRegCurve,const char * FurnTapChangOn)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14100;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Tap Change Start received  ReactTapNo:";
  EventLogMessage.messageText2 = "Tap Change Start received  ReactTapNo:";
  EventLogMessage.messageText += ReactTapNo;
  EventLogMessage.messageText += "  VoltTapNo:";
  EventLogMessage.messageText += VoltTapNo;
  EventLogMessage.messageText += " EltrdRegCurve:";
  EventLogMessage.messageText += EltrdRegCurve;
  EventLogMessage.messageText += " FurnTapChangOn:";
  EventLogMessage.messageText += FurnTapChangOn;
  EventLogMessage.messageText2 += ReactTapNo;
  EventLogMessage.messageText2 += "  VoltTapNo:";
  EventLogMessage.messageText2 += VoltTapNo;
  EventLogMessage.messageText2 += " EltrdRegCurve:";
  EventLogMessage.messageText2 += EltrdRegCurve;
  EventLogMessage.messageText2 += " FurnTapChangOn:";
  EventLogMessage.messageText2 += FurnTapChangOn;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_TapChangeFinished( const char * ReactTapNo,const char * VoltTapNo,const char * EltrdRegCurve,const char * FurnTapChangOn)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Tap Change Finished received ReactTapNo:";
  EventLogMessage.messageText2 = "Tap Change Finished received ReactTapNo:";
  EventLogMessage.messageText += ReactTapNo;
  EventLogMessage.messageText += " VoltTapNo:";
  EventLogMessage.messageText += VoltTapNo;
  EventLogMessage.messageText += " EltrdRegCurve:";
  EventLogMessage.messageText += EltrdRegCurve;
  EventLogMessage.messageText += " FurnTapChangOn:";
  EventLogMessage.messageText += FurnTapChangOn;
  EventLogMessage.messageText2 += ReactTapNo;
  EventLogMessage.messageText2 += " VoltTapNo:";
  EventLogMessage.messageText2 += VoltTapNo;
  EventLogMessage.messageText2 += " EltrdRegCurve:";
  EventLogMessage.messageText2 += EltrdRegCurve;
  EventLogMessage.messageText2 += " FurnTapChangOn:";
  EventLogMessage.messageText2 += FurnTapChangOn;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14101;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_TapChangeFinished( sEventLogMessage &EventLogMessage, const char * ReactTapNo,const char * VoltTapNo,const char * EltrdRegCurve,const char * FurnTapChangOn)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14101;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Tap Change Finished received ReactTapNo:";
  EventLogMessage.messageText2 = "Tap Change Finished received ReactTapNo:";
  EventLogMessage.messageText += ReactTapNo;
  EventLogMessage.messageText += " VoltTapNo:";
  EventLogMessage.messageText += VoltTapNo;
  EventLogMessage.messageText += " EltrdRegCurve:";
  EventLogMessage.messageText += EltrdRegCurve;
  EventLogMessage.messageText += " FurnTapChangOn:";
  EventLogMessage.messageText += FurnTapChangOn;
  EventLogMessage.messageText2 += ReactTapNo;
  EventLogMessage.messageText2 += " VoltTapNo:";
  EventLogMessage.messageText2 += VoltTapNo;
  EventLogMessage.messageText2 += " EltrdRegCurve:";
  EventLogMessage.messageText2 += EltrdRegCurve;
  EventLogMessage.messageText2 += " FurnTapChangOn:";
  EventLogMessage.messageText2 += FurnTapChangOn;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HandleScrapOrder( const char * OrderID,int ContainerInSeq,const char * ContainerType)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Handle scrap for order ";
  EventLogMessage.messageText2 = "Handle scrap for order ";
  EventLogMessage.messageText += OrderID;
  EventLogMessage.messageText += " - ContainerInSeq:";
  char mstring1[64];
  sprintf( mstring1,"%d",ContainerInSeq);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " - ContainerType: ";
  EventLogMessage.messageText += ContainerType;
  EventLogMessage.messageText += " -";
  EventLogMessage.messageText2 += OrderID;
  EventLogMessage.messageText2 += " - ContainerInSeq:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " - ContainerType ";
  EventLogMessage.messageText2 += ContainerType;
  EventLogMessage.messageText2 += " -";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14102;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_HandleScrapOrder( sEventLogMessage &EventLogMessage, const char * OrderID,int ContainerInSeq,const char * ContainerType)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14102;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Handle scrap for order ";
  EventLogMessage.messageText2 = "Handle scrap for order ";
  EventLogMessage.messageText += OrderID;
  EventLogMessage.messageText += " - ContainerInSeq:";
  char mstring1[64];
  sprintf( mstring1,"%d",ContainerInSeq);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " - ContainerType: ";
  EventLogMessage.messageText += ContainerType;
  EventLogMessage.messageText += " -";
  EventLogMessage.messageText2 += OrderID;
  EventLogMessage.messageText2 += " - ContainerInSeq:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " - ContainerType ";
  EventLogMessage.messageText2 += ContainerType;
  EventLogMessage.messageText2 += " -";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_TempMeasurement( const char * MeasTemp,int TempSampleNo)
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
  EventLogMessage.messageText2 += MeasTemp;
  EventLogMessage.messageText2 += " TempSampleNo:";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14103;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_TempMeasurement( sEventLogMessage &EventLogMessage, const char * MeasTemp,int TempSampleNo)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14103;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Temperature Measurement MeasTemp:";
  EventLogMessage.messageText2 = "Temperature Measurement MeasTemp:";
  EventLogMessage.messageText += MeasTemp;
  EventLogMessage.messageText += " TempSampleNo:";
  char mstring1[64];
  sprintf( mstring1,"%d",TempSampleNo);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText2 += MeasTemp;
  EventLogMessage.messageText2 += " TempSampleNo:";
  EventLogMessage.messageText2 += mstring1;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ManipInjectLanceStart( const char * Device,const char * MatCode)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Manipulation Injection Lance Start received Device:";
  EventLogMessage.messageText2 = "Manipulation Injection Lance Start received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " MatCode:";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " MatCode:";
  EventLogMessage.messageText2 += MatCode;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14104;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ManipInjectLanceStart( sEventLogMessage &EventLogMessage, const char * Device,const char * MatCode)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14104;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Manipulation Injection Lance Start received Device:";
  EventLogMessage.messageText2 = "Manipulation Injection Lance Start received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " MatCode:";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " MatCode:";
  EventLogMessage.messageText2 += MatCode;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ManipInjectLanceStop( const char * Device,const char * MatCode,double Value)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Manipulation Injection Lance Stop received Device:";
  EventLogMessage.messageText2 = "Manipulation Injection Lance Stop received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " MatCode:";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText += " Value:";
  char mstring2[64];
  sprintf( mstring2,"%f",Value);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " MatCode:";
  EventLogMessage.messageText2 += MatCode;
  EventLogMessage.messageText2 += " Value:";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14105;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ManipInjectLanceStop( sEventLogMessage &EventLogMessage, const char * Device,const char * MatCode,double Value)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14105;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Manipulation Injection Lance Stop received Device:";
  EventLogMessage.messageText2 = "Manipulation Injection Lance Stop received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " MatCode:";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText += " Value:";
  char mstring2[64];
  sprintf( mstring2,"%f",Value);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " MatCode:";
  EventLogMessage.messageText2 += MatCode;
  EventLogMessage.messageText2 += " Value:";
  EventLogMessage.messageText2 += mstring2;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_InjectionStart( const char * Device,const char * MatCode)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Injection Start received Device:";
  EventLogMessage.messageText2 = "Injection Start received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " MatCode:";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " MatCode:";
  EventLogMessage.messageText2 += MatCode;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14106;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_InjectionStart( sEventLogMessage &EventLogMessage, const char * Device,const char * MatCode)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14106;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Injection Start received Device:";
  EventLogMessage.messageText2 = "Injection Start received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " MatCode:";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " MatCode:";
  EventLogMessage.messageText2 += MatCode;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_InjectionStop( const char * Device,const char * MatCode,double Value)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Injection Stop received Device:";
  EventLogMessage.messageText2 = "Injection Stop received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " MatCode:";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText += " Value:";
  char mstring2[64];
  sprintf( mstring2,"%f",Value);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " MatCode:";
  EventLogMessage.messageText2 += MatCode;
  EventLogMessage.messageText2 += " Value:";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14107;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_InjectionStop( sEventLogMessage &EventLogMessage, const char * Device,const char * MatCode,double Value)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14107;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Injection Stop received Device:";
  EventLogMessage.messageText2 = "Injection Stop received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " MatCode:";
  EventLogMessage.messageText += MatCode;
  EventLogMessage.messageText += " Value:";
  char mstring2[64];
  sprintf( mstring2,"%f",Value);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " MatCode:";
  EventLogMessage.messageText2 += MatCode;
  EventLogMessage.messageText2 += " Value:";
  EventLogMessage.messageText2 += mstring2;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ScrapContainerOrderError( int ContainerNo,int ContainerInSeqReq,int ScrapContainertInSeqAct)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Error handling scrap ScrapContainer sequence for ScrapContainer: ";
  EventLogMessage.messageText2 = "Error handling scrap ScrapContainer sequence for ScrapContainer: ";
  char mstring0[64];
  sprintf( mstring0,"%d",ContainerNo);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " - requested sequence ";
  char mstring1[64];
  sprintf( mstring1,"%d",ContainerInSeqReq);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " - actual sequence ";
  char mstring2[64];
  sprintf( mstring2,"%d",ScrapContainertInSeqAct);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " - requested sequence ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " - actual sequence ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14108;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ScrapContainerOrderError( sEventLogMessage &EventLogMessage, int ContainerNo,int ContainerInSeqReq,int ScrapContainertInSeqAct)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14108;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Error handling scrap ScrapContainer sequence for ScrapContainer: ";
  EventLogMessage.messageText2 = "Error handling scrap ScrapContainer sequence for ScrapContainer: ";
  char mstring0[64];
  sprintf( mstring0,"%d",ContainerNo);
  EventLogMessage.messageText += mstring0;
  EventLogMessage.messageText += " - requested sequence ";
  char mstring1[64];
  sprintf( mstring1,"%d",ContainerInSeqReq);
  EventLogMessage.messageText += mstring1;
  EventLogMessage.messageText += " - actual sequence ";
  char mstring2[64];
  sprintf( mstring2,"%d",ScrapContainertInSeqAct);
  EventLogMessage.messageText += mstring2;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += mstring0;
  EventLogMessage.messageText2 += " - requested sequence ";
  EventLogMessage.messageText2 += mstring1;
  EventLogMessage.messageText2 += " - actual sequence ";
  EventLogMessage.messageText2 += mstring2;
  EventLogMessage.messageText2 += " ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerElec( const char * ProdPracPointer)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Production Practice Pointer Electric received to ";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Electric received to ";
  EventLogMessage.messageText += ProdPracPointer;
  EventLogMessage.messageText2 += ProdPracPointer;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14109;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerElec( sEventLogMessage &EventLogMessage, const char * ProdPracPointer)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14109;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Production Practice Pointer Electric received to ";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Electric received to ";
  EventLogMessage.messageText += ProdPracPointer;
  EventLogMessage.messageText2 += ProdPracPointer;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerInjection( const char * ProdPracPointer)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Production Practice Pointer Injection received to ";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Injection received to ";
  EventLogMessage.messageText += ProdPracPointer;
  EventLogMessage.messageText2 += ProdPracPointer;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14110;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerInjection( sEventLogMessage &EventLogMessage, const char * ProdPracPointer)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14110;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Production Practice Pointer Injection received to ";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Injection received to ";
  EventLogMessage.messageText += ProdPracPointer;
  EventLogMessage.messageText2 += ProdPracPointer;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracDataBurnerOxygen( const char * ProdPracPointer)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Production Practice Pointer Burner Oxygen received to ";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Burner Oxygen received to ";
  EventLogMessage.messageText += ProdPracPointer;
  EventLogMessage.messageText2 += ProdPracPointer;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14111;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracDataBurnerOxygen( sEventLogMessage &EventLogMessage, const char * ProdPracPointer)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14111;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Production Practice Pointer Burner Oxygen received to ";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Burner Oxygen received to ";
  EventLogMessage.messageText += ProdPracPointer;
  EventLogMessage.messageText2 += ProdPracPointer;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerOxygen( const char * ProdPracPointer)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Production Practice Pointer Oxygen received to ";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Oxygen received to ";
  EventLogMessage.messageText += ProdPracPointer;
  EventLogMessage.messageText2 += ProdPracPointer;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14112;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerOxygen( sEventLogMessage &EventLogMessage, const char * ProdPracPointer)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14112;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Production Practice Pointer Oxygen received to ";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Oxygen received to ";
  EventLogMessage.messageText += ProdPracPointer;
  EventLogMessage.messageText2 += ProdPracPointer;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerParameter( const char * ProdPracPointer)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Production Practice Pointer Parameter received to ";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Parameter received to ";
  EventLogMessage.messageText += ProdPracPointer;
  EventLogMessage.messageText2 += ProdPracPointer;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14113;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerParameter( sEventLogMessage &EventLogMessage, const char * ProdPracPointer)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14113;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Production Practice Pointer Parameter received to ";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Parameter received to ";
  EventLogMessage.messageText += ProdPracPointer;
  EventLogMessage.messageText2 += ProdPracPointer;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerRestriction( const char * ProdPracPointer)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Production Practice Pointer Restriction received to ";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Restriction received to ";
  EventLogMessage.messageText += ProdPracPointer;
  EventLogMessage.messageText2 += ProdPracPointer;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14114;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerRestriction( sEventLogMessage &EventLogMessage, const char * ProdPracPointer)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14114;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Production Practice Pointer Restriction received to ";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Restriction received to ";
  EventLogMessage.messageText += ProdPracPointer;
  EventLogMessage.messageText2 += ProdPracPointer;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_SetComputerModeManual( const char * Device)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Set Computer Mode received Device:";
  EventLogMessage.messageText2 = "Set Computer Mode received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " Status : Manual";
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " Status : Manual";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14115;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_SetComputerModeManual( sEventLogMessage &EventLogMessage, const char * Device)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14115;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Set Computer Mode received Device:";
  EventLogMessage.messageText2 = "Set Computer Mode received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " Status : Manual";
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " Status : Manual";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_SetComputerModeAutomatic( const char * Device)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Set Computer Mode received Device:";
  EventLogMessage.messageText2 = "Set Computer Mode received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " Status : Automatic";
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " Status : Automatic";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14116;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_SetComputerModeAutomatic( sEventLogMessage &EventLogMessage, const char * Device)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14116;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Set Computer Mode received Device:";
  EventLogMessage.messageText2 = "Set Computer Mode received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " Status : Automatic";
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " Status : Automatic";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_SetComputerModeDynamic( const char * Device)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Set Computer Mode received Device:";
  EventLogMessage.messageText2 = "Set Computer Mode received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " Status : Dynamic";
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " Status : Dynamic";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14117;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_SetComputerModeDynamic( sEventLogMessage &EventLogMessage, const char * Device)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14117;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Set Computer Mode received Device:";
  EventLogMessage.messageText2 = "Set Computer Mode received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " Status : Dynamic";
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " Status : Dynamic";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_SetComputerModePattern( const char * Device)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Set Computer Mode received Device:";
  EventLogMessage.messageText2 = "Set Computer Mode received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " Status : Pattern";
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " Status : Pattern";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14118;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_SetComputerModePattern( sEventLogMessage &EventLogMessage, const char * Device)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14118;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Set Computer Mode received Device:";
  EventLogMessage.messageText2 = "Set Computer Mode received Device:";
  EventLogMessage.messageText += Device;
  EventLogMessage.messageText += " Status : Pattern";
  EventLogMessage.messageText2 += Device;
  EventLogMessage.messageText2 += " Status : Pattern";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_FlameProfileUnused()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Flame profile data from Level 1 not used";
  EventLogMessage.messageText2 = "Flame profile data from Level 1 not used";
  EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14119;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_FlameProfileUnused( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_error;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14119;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Flame profile data from Level 1 not used";
  EventLogMessage.messageText2 = "Flame profile data from Level 1 not used";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_DoorOpened()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Door Opened";
  EventLogMessage.messageText2 = "Door Opened";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14120;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_DoorOpened( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14120;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Door Opened";
  EventLogMessage.messageText2 = "Door Opened";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_DoorClosed()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Door Closed";
  EventLogMessage.messageText2 = "Door Closed";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14121;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_DoorClosed( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14121;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Door Closed";
  EventLogMessage.messageText2 = "Door Closed";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_RoofArrivesInUpPosition()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Roof Arrives In Up Position";
  EventLogMessage.messageText2 = "Roof Arrives In Up Position";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14122;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_RoofArrivesInUpPosition( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14122;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Roof Arrives In Up Position";
  EventLogMessage.messageText2 = "Roof Arrives In Up Position";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_RoofArrivesInDownPosition()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Roof Arrives In Down Position";
  EventLogMessage.messageText2 = "Roof Arrives In Down Position";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14123;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_RoofArrivesInDownPosition( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14123;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Roof Arrives In Down Position";
  EventLogMessage.messageText2 = "Roof Arrives In Down Position";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_GantrySwungIn()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Gantry Swung In";
  EventLogMessage.messageText2 = "Gantry Swung In";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14124;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_GantrySwungIn( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14124;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Gantry Swung In";
  EventLogMessage.messageText2 = "Gantry Swung In";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_GantrySwungOut()
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Gantry Swung Out";
  EventLogMessage.messageText2 = "Gantry Swung Out";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14125;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_GantrySwungOut( sEventLogMessage &EventLogMessage )
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14125;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Gantry Swung Out";
  EventLogMessage.messageText2 = "Gantry Swung Out";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerPlantRestriction( const char * RestriPracPt,const char * FlagHeatRelated)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Production Practice Pointer Plant Restriction received RestriPracPt:";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Plant Restriction received RestriPracPt:";
  EventLogMessage.messageText += RestriPracPt;
  EventLogMessage.messageText += " FlagHeatRelated:";
  EventLogMessage.messageText += FlagHeatRelated;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += RestriPracPt;
  EventLogMessage.messageText2 += " FlagHeatRelated:";
  EventLogMessage.messageText2 += FlagHeatRelated;
  EventLogMessage.messageText2 += " ";
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14126;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerPlantRestriction( sEventLogMessage &EventLogMessage, const char * RestriPracPt,const char * FlagHeatRelated)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14126;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Production Practice Pointer Plant Restriction received RestriPracPt:";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Plant Restriction received RestriPracPt:";
  EventLogMessage.messageText += RestriPracPt;
  EventLogMessage.messageText += " FlagHeatRelated:";
  EventLogMessage.messageText += FlagHeatRelated;
  EventLogMessage.messageText += " ";
  EventLogMessage.messageText2 += RestriPracPt;
  EventLogMessage.messageText2 += " FlagHeatRelated:";
  EventLogMessage.messageText2 += FlagHeatRelated;
  EventLogMessage.messageText2 += " ";
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerPlantRestriction( const char * ProdPracPointer)
{
  sEventLogMessage EventLogMessage;
  cCBS_Time::localTime(EventLogMessage.applDateTime);
  EventLogMessage.messageText = "Change Production Practice Pointer Plant Restriction received to ";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Plant Restriction received to ";
  EventLogMessage.messageText += ProdPracPointer;
  EventLogMessage.messageText2 += ProdPracPointer;
  EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  EventLogMessage.trigger = 1;
  EventLogMessage.eventId = 14127;
  return (lRetValue = sendMessage(EventLogMessage));
}

long CSMC_EventLogEAF::EL_ChangeProdPracPointerPlantRestriction( sEventLogMessage &EventLogMessage, const char * ProdPracPointer)
{
  if (EventLogMessage.severity == c_e_test) EventLogMessage.severity = c_e_info;
  EventLogMessage.language = 1;
  if (EventLogMessage.eventId == 0) EventLogMessage.eventId = 14127;
  if (EventLogMessage.destination == 0) EventLogMessage.destination = CSMC_DestCodes::EAFBotLine;
  if (EventLogMessage.trigger != true) EventLogMessage.trigger = 1;
  EventLogMessage.messageText = "Change Production Practice Pointer Plant Restriction received to ";
  EventLogMessage.messageText2 = "Change Production Practice Pointer Plant Restriction received to ";
  EventLogMessage.messageText += ProdPracPointer;
  EventLogMessage.messageText2 += ProdPracPointer;
  return (lRetValue = sendMessage(EventLogMessage));
}
