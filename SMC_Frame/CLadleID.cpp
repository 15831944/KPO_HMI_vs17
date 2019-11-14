// Copyright (C) 2004 SMS Demag AG

#include "CSMC_EventLogFrameController.h"

#include "CDataConversion.h"
#include "CSMC_DBData.h"
#include "DEF_GC_LADLE_TYPE.h"

#include "CLadleID.h"


CLadleID::~CLadleID()
{
}

CLadleID::CLadleID()
{
}

std::string CLadleID::generateLadleID(const std::string &LadleType, long LadleNo, bool ForceEventLog /* = false */ )
{
  std::string ID = LadleType + CDataConversion::LongToString(LadleNo);

  if ( LadleType == DEF::Inv_String             || 
       LadleType == CSMC_DBData::unspecString   ||
       LadleNo   == DEF::Inv_Long               || 
       LadleNo   == CSMC_DBData::unspecLong )
  {
    if ( ForceEventLog )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorLadleIdGeneration(Message, "CLadleID::generateLadleID", LadleType.c_str(), LadleNo);
    }

    ID = DEF::Inv_String;
  }

  return ID;
}

std::string CLadleID::getLadleType(const std::string &LadleID)
{
  std::string LadleType = DEF::Inv_String;

  if ( LadleID.size() >= 2 )
  {
    // check for valid format like T1, P23, H222
    LadleType = LadleID.substr(0,1);
  }

  // we do not have Connectionm here, test ladle types seperately
  if ( LadleType != DEF_GC_LADLE_TYPE::FeCrLadle     && 
       LadleType != DEF_GC_LADLE_TYPE::HotMetalLadle && 
       LadleType != DEF_GC_LADLE_TYPE::PreMetalLadle && 
       LadleType != DEF_GC_LADLE_TYPE::TeemingLadle )
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorLadleIdGeneration(Message,"CLadleID::getLadleType",LadleID.c_str());

    LadleType = DEF::Inv_String;
  }

  return LadleType;
}

long CLadleID::getLadleNo(const std::string &LadleID)
{
  long LadleNo          = DEF::Inv_Long;
  std::string LadleType = DEF::Inv_String;

  if ( LadleID.size() >= 2 )
  {
    LadleNo = CDataConversion::StringToLong(LadleID.substr(1,LadleID.length()), DEF::Inv_Long ) ;

    LadleType = getLadleType(LadleID);
  }

  if ( LadleType == DEF::Inv_String ||
       LadleNo   == DEF::Inv_Long )
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorLadleIdGeneration(Message,"CLadleID::getLadleNo",LadleID.c_str());

    LadleNo = DEF::Inv_Long;    
  }

  return LadleNo;
}

bool CLadleID::isValid(const std::string &LadleID)
{
  bool RetValue = false;

  std::string LadleType = getLadleType(LadleID);
  long        LadleNo   = getLadleNo(LadleID);

  if ( LadleType != DEF::Inv_String &&
       LadleNo   != DEF::Inv_Long )
  {
    RetValue = true;
  }

  return RetValue;
}

bool CLadleID::checkLadleIDWithDefaultType(const std::string &DefaultLadleType, std::string &LadleID)
{
  bool RetValue = false;

  if ( isValid(LadleID) )
  {
    RetValue = true;
  }
  else
  {
    if ( isValid(DefaultLadleType + LadleID) )
    {
      LadleID   = DefaultLadleType + LadleID;
      RetValue  = true;
    }
  }

  return RetValue;
}

