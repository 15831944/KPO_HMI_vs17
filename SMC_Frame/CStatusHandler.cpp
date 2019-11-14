// Copyright (C) 2004 SMS Demag AG

#include <sstream>
#include <fstream>

#include "iData_Provider_s.hh"

#include "cCBS_StdInitBase.h"
#include "CIntfData.h"

#include "CSMC_EventLogFrameController.h"
#include "CDataConversion.h"

#include "CStatusHandlerValidator.h"
#include "CStatusHandler.h"



CStatusHandler::~CStatusHandler()
{
  m_StatusList.clear();
}

CStatusHandler::CStatusHandler()
{
  loadRules();
}

CStatusHandler::CStatusHandler(seqStatus& StatusData)
{
  loadRules();

  fill(StatusData); 
}

void CStatusHandler::fill(seqStatus& StatusData)
{
  update(StatusData);
}

void CStatusHandler::update(seqStatus& StatusData)
{
  for ( long i = 0 ; i < CIntfData::getLength(StatusData) ; ++i )
  {
    sStatus Status;
    CIntfData::getAt(Status,StatusData,i);

    update(Status);
  }
}


void CStatusHandler::update(sStatus Status)
{
  // try to find existing device of StirringData
  if ( isStatus( std::string(Status.Device), std::string(Status.StatusName) ) )
  {
    setStatus(std::string(Status.Device),std::string(Status.StatusName),Status.Status);
  }
  else
  {
    addStatus(std::string(Status.Device),std::string(Status.StatusName),Status.Status);
  }
}

void CStatusHandler::update(const std::string& Device, const std::string& StatusName, long Status)
{
  // try to find existing device of StirringData
  if ( isStatus( std::string(Device), std::string(StatusName) ) )
  {
    setStatus(std::string(Device),std::string(StatusName),Status);
  }
  else
  {
    addStatus(std::string(Device),std::string(StatusName),Status);
  }
}



void CStatusHandler::updateValue(std::vector<std::string> IDList, const std::string& StatusName, long Value)
{
  std::vector<std::string>::iterator it;

  for ( it = IDList.begin() ; it != IDList.end() ; ++it)
  {
    sStatus Status;
    Status.Device     = (*it).c_str();
    Status.StatusName = StatusName.c_str();
    Status.Status     = Value;

    update(Status);
  }
}


seqStatus CStatusHandler::getStatusData()
{
  seqStatus StatusData;

  std::map<std::string, std::map<std::string, long> >::iterator it;

  for ( it = m_StatusList.begin(); it != m_StatusList.end(); ++it )
  {
    sStatus Status;
    Status.Device     = it->first.c_str();

    std::map<std::string, long>::iterator itData;
    std::map<std::string, long> Data = it->second;

    for ( itData = Data.begin(); itData != Data.end(); ++itData )
    {
      Status.StatusName = itData->first.c_str();
      Status.Status     = itData->second;

      CIntfData::insert(StatusData,Status);
    }
  }
  return StatusData;
}

seqStatus CStatusHandler::getStatusData(long Status)
{
  seqStatus StatusData;

  std::map<std::string, std::map<std::string, long> >::iterator it;

  for ( it = m_StatusList.begin(); it != m_StatusList.end(); ++it )
  {
    sStatus structStatus;
    structStatus.Device     = it->first.c_str();

    std::map<std::string, long>::iterator itData;
    std::map<std::string, long> Data = it->second;

    for ( itData = Data.begin(); itData != Data.end(); ++itData )
    {
      if ( Status == itData->second )
      {
        structStatus.StatusName = itData->first.c_str();
        structStatus.Status     = itData->second;

        CIntfData::insert(StatusData,structStatus);
      }
    }
  }
  return StatusData;
}

std::vector<std::string> CStatusHandler::getIDList(const std::string& StatusName, long Value)
{
  std::vector<std::string> IDList;

  std::map<std::string, std::map<std::string, long> >::iterator it;

  for ( it = m_StatusList.begin(); it != m_StatusList.end(); ++it )
  {
    std::map<std::string, long>::iterator itData;
    std::map<std::string, long> Data = it->second;

    for ( itData = Data.begin(); itData != Data.end(); ++itData )
    {
      if ( StatusName == itData->first && 
           Value      == itData->second )
      {
        IDList.push_back(it->first);
      }
    }
  }

  return IDList;
}


bool CStatusHandler::isStatusChanged(const std::string& ID, const std::string& StatusName, bool Value)
{
  bool RetValue = false;
  
  if ( Value )
  {
    RetValue = isStatusChanged(ID, StatusName, DEF_GEN_STATES::On);
  }
  else
  {
    RetValue = isStatusChanged(ID, StatusName, DEF_GEN_STATES::Off);
  }

  return RetValue;
}



bool CStatusHandler::isStatusChanged(const std::string& ID, const std::string& StatusName, long Value)
{
  bool RetValue = false;

  if ( isStatus(ID,StatusName) )
  {
    long ActStatus = getStatus(ID,StatusName);

    if ( ActStatus != Value )
    {
      if ( ! m_Validator.validateTransition(StatusName, ActStatus, Value ) )
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorStateTransition(sMessage, StatusName.c_str(), CDataConversion::LongToString(ActStatus).c_str(), CDataConversion::LongToString(Value).c_str() );
      }

      RetValue = true;
      setStatus(ID,StatusName,Value);
    }
  }
  else
  {
    RetValue = true;
    addStatus(ID,StatusName,Value);
  }

  return RetValue;
}

void CStatusHandler::removeID(const std::string& ID)
{
  std::map<std::string, std::map<std::string, long> >::iterator it;

  it = m_StatusList.find(ID);

  if ( it != m_StatusList.end() )
  {
    m_StatusList.erase(it);
  }
}

void CStatusHandler::addStatus(const std::string& ID, const std::string& StatusName, long Value)
{
  std::map<std::string,long> Status;
  std::map<std::string, std::map<std::string, long> >::iterator it;

  it = m_StatusList.find(ID);

  if ( it != m_StatusList.end() )
  {
    Status = it->second;
    Status.insert(std::pair<std::string,long>(StatusName,Value));
    it->second = Status;
  }
  else
  {
    Status.insert(std::pair<std::string,long>(StatusName,Value));
    m_StatusList.insert( std::pair <std::string, std::map< std::string, long > > (ID, Status));
  }

}

bool CStatusHandler::isStatus(const std::string& ID, const std::string& StatusName)
{
  bool RetValue = false;

  std::map<std::string, std::map<std::string, long> >::iterator it;

  it = m_StatusList.find(ID);

  if ( it != m_StatusList.end() )
  {
    std::map<std::string, long> Status = it->second;
    std::map<std::string, long>::iterator itStatus;

    itStatus = Status.find(StatusName);
    if ( itStatus != Status.end() )
    {
      RetValue = true;
    }    
  }

  return RetValue;
}

long CStatusHandler::getStatus(const std::string& ID, const std::string& StatusName  )
{
  long RetValue = DEF::Inv_Long;

  std::map<std::string, std::map<std::string, long> >::iterator it;

  it = m_StatusList.find(ID);

  if ( it != m_StatusList.end() )
  {
    std::map<std::string, long> Status = it->second;
    std::map<std::string, long>::iterator itStatus;

    itStatus = Status.find(StatusName);
    if ( itStatus != Status.end() )
    {
      RetValue = itStatus->second;
    }    
  }

  return RetValue;
}

void CStatusHandler::setStatus(const std::string& ID, const std::string& StatusName, long Value)
{
  std::map<std::string, std::map<std::string, long> >::iterator it;

  it = m_StatusList.find(ID);

  if ( it != m_StatusList.end() )
  {
    std::map<std::string, long> Status = it->second;
    std::map<std::string, long>::iterator itStatus;

    itStatus = Status.find(StatusName);
    if ( itStatus != Status.end() )
    {
      itStatus->second = Value;
      it->second = Status;
    }    
  }
}

//set start time of status start
bool CStatusHandler::setStartTime(seqStatus& SeqStatus, const std::string& DeviceName, const std::string& StatusName, sDate Value)
{
  bool RetValue = false;

  long SeqLength = CIntfData::getLength(SeqStatus);
  sStatus Status;

  for (long pos = 0; pos < SeqLength; pos++ )
  {
    if (CIntfData::getAt(Status, SeqStatus, pos))
    {
      if ( DeviceName == std::string(Status.Device) && 
           StatusName == std::string(Status.StatusName))
      {
        Status.StartTime = Value;
        CIntfData::setAt(SeqStatus, Status, pos);

        RetValue = true;
        break;
      }
    }
  }
  if (!RetValue)
  {
    Status.Device     = DeviceName.c_str();
    Status.StatusName = StatusName.c_str();
    Status.StartTime  = Value;

    CIntfData::insert(SeqStatus, Status);

    RetValue = true;
  }
  return RetValue;
}

//get end time of status end
sDate CStatusHandler::getStartTime(seqStatus& SeqStatus, const std::string& DeviceName, const std::string& StatusName)
{
  sDate RetValue = CDateTime::InvalidDate();

  long SeqLength = CIntfData::getLength(SeqStatus);
  sStatus Status;

  for (long pos = 0; pos < SeqLength; pos++ )
  {
    if (CIntfData::getAt(Status, SeqStatus, pos))
    {
      if ( DeviceName == std::string(Status.Device) && 
           StatusName == std::string(Status.StatusName))
      {
        RetValue = Status.StartTime;
        break;
      }
    }
  }
  return RetValue;
}

//set end time of status end
bool CStatusHandler::setEndTime(seqStatus& SeqStatus, const std::string& DeviceName, const std::string& StatusName, sDate Value)
{
  bool RetValue = false;

  long SeqLength = CIntfData::getLength(SeqStatus);
  sStatus Status;

  for (long pos = 0; pos < SeqLength; pos++ )
  {
    if (CIntfData::getAt(Status, SeqStatus, pos))
    {
      if ( DeviceName == std::string(Status.Device) && 
           StatusName == std::string(Status.StatusName))
      {
        Status.EndTime = Value;
        CIntfData::setAt(SeqStatus, Status, pos);

        RetValue = true;
        break;
      }
    }
  }
  if (!RetValue)
  {
    Status.Device     = DeviceName.c_str();
    Status.StatusName = StatusName.c_str();
    Status.EndTime    = Value;

    CIntfData::insert(SeqStatus, Status);

    RetValue = true;
  }
  return RetValue;
}

//get end time of status end
sDate CStatusHandler::getEndTime(seqStatus& SeqStatus, const std::string& DeviceName, const std::string& StatusName)
{
  sDate RetValue = CDateTime::InvalidDate();

  long SeqLength = CIntfData::getLength(SeqStatus);
  sStatus Status;

  for (long pos = 0; pos < SeqLength; pos++ )
  {
    if (CIntfData::getAt(Status, SeqStatus, pos))
    {
      if ( DeviceName == std::string(Status.Device) && 
           StatusName == std::string(Status.StatusName))
      {
        RetValue = Status.EndTime;
        break;
      }
    }
  }
  return RetValue;
}

bool CStatusHandler::setDeviceStatus(seqStatus& SeqStatus, const std::string& DeviceName, const std::string& StatusName, bool Value)
{
  bool RetValue = false;
  
  if ( Value )
  {
    RetValue = setDeviceStatus(SeqStatus, DeviceName, StatusName, DEF_GEN_STATES::On);
  }
  else
  {
    RetValue = setDeviceStatus(SeqStatus, DeviceName, StatusName, DEF_GEN_STATES::Off);
  }

  return RetValue;

}

bool CStatusHandler::setDeviceStatus(seqStatus& SeqStatus, const std::string& DeviceName, const std::string& StatusName, long Value)
{
  bool RetValue = false;

  long SeqLength = CIntfData::getLength(SeqStatus);
  sStatus Status;

  for (long pos = 0; pos < SeqLength; pos++ )
  {
    if (CIntfData::getAt(Status, SeqStatus, pos))
    {
      if ( DeviceName == std::string(Status.Device) && 
           StatusName == std::string(Status.StatusName))
      {
        Status.Status     = Value;
        Status.StatusName = StatusName.c_str();

        CIntfData::setAt(SeqStatus, Status, pos);

        RetValue = true;
        break;
      }
    }
  }
  if (!RetValue)
  {
    Status.Device     = DeviceName.c_str();
    Status.StatusName = StatusName.c_str();
    Status.Status     = Value;

    CIntfData::insert(SeqStatus, Status);

    RetValue = true;
  }
  return RetValue;
}



long CStatusHandler::getDeviceStatus(seqStatus& SeqStatus, const std::string& DeviceName, const std::string& StatusName)
{
  long RetStatus = DEF_GEN_STATES::Undefined;

  long SeqLength = CIntfData::getLength(SeqStatus);
  sStatus Status;

  for (long pos = 0; pos < SeqLength; pos++ )
  {
    if (CIntfData::getAt(Status, SeqStatus, pos))
    {
      if ( DeviceName == std::string(Status.Device) && 
           StatusName == std::string(Status.StatusName))
      {
        RetStatus = Status.Status;
        break;
      }
    }
  }

  return RetStatus;
}


void CStatusHandler::loadRules()
{
  try
  {
    cCBS_StdInitBase *pInitBase = cCBS_StdInitBase::getInstance();
    
    std::string StatusHandlerRuleSet;

    pInitBase->replaceWithEntry("PATH", "StatusHandlerRuleSet", StatusHandlerRuleSet);

    if (!StatusHandlerRuleSet.empty())
    {
      StatusHandlerRuleSet =  pInitBase->getXPACT_SMC() + StatusHandlerRuleSet;

      std::ifstream in(StatusHandlerRuleSet.c_str());
      std::string lineBuffer;

      // read line of RuleSet file
      // structure must be like 
      // [ELECTRIC]
      // 0 -> 1 // POWER_OFF  -> POWER_ON 
      // 1 -> 0 // POWER_ON   -> POWER_OFF

      std::string Key; // block name

      while (getline(in, lineBuffer))
	    {
        std::string Comp;
        long State      = DEF::Inv_Long;
        long Transition = DEF::Inv_Long;

        std::istringstream istr(lineBuffer);

        // processing empty and comment lines
        if(lineBuffer.empty() || lineBuffer.substr(0,2) == "//")
        {
          continue;
        }

        // processing [Block], will be used as "key" later on
        if(lineBuffer.substr(0,1) == "[")
        {
          // key is value inbetween "[" and "]"
          if( istr >> Key )
          {
            Key = Key.substr(1,Key.length()-2);
          }
          else
          {
            Key.erase();
          }
        }

        // processing rules
        if( istr >> State >> Comp >> Transition)
        {
          if ( State      != DEF::Inv_Long && 
               Transition != DEF::Inv_Long )
          {
            m_Validator.loadRule(Key,State,Transition);
          }
        }
      }

      in.close();
    }
  }
  catch(...)
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CStatusHandler::loadRules()", "");
  }
}


void CStatusHandler::addStatus(std::string& ID, seqGasAvail& SeqGasAvail)
{
  bool RetVal = false;

  long L1 = SeqGasAvail.length();
  for ( long l = 0; l < L1; l++ )
  {
    addStatus(ID, std::string(SeqGasAvail[l].GasType), SeqGasAvail[l].GasAvail);
  }
}

long CStatusHandler::getMaxStatus(seqStatus& SeqStatus, const std::string& DeviceName, const std::string& StatusName)
{
  long MaxStatus = -1;

  long SeqLength = CIntfData::getLength(SeqStatus);
  sStatus Status;

  for (long pos = 0; pos < SeqLength; pos++ )
  {
    if (CIntfData::getAt(Status, SeqStatus, pos))
    {
      if ( !DeviceName.empty() && !StatusName.empty() &&
           DeviceName == std::string(Status.Device) && 
           StatusName == std::string(Status.StatusName))
      {
        MaxStatus = max(MaxStatus, Status.Status);
      }
      else if ( !DeviceName.empty() && StatusName.empty() &&
                DeviceName == std::string(Status.Device))
      {
        MaxStatus = max(MaxStatus, Status.Status);
      }
      else if ( DeviceName.empty() && !StatusName.empty() &&
                StatusName == std::string(Status.StatusName))
      {
        MaxStatus = max(MaxStatus, Status.Status);
      }
      else
      {
        MaxStatus = max(MaxStatus, Status.Status);
      }
    }
  }

  return MaxStatus;
}

long CStatusHandler::getMinStatus(seqStatus& SeqStatus, const std::string& DeviceName, const std::string& StatusName)
{
  long MinStatus = 999999;

  long SeqLength = CIntfData::getLength(SeqStatus);
  sStatus Status;

  for (long pos = 0; pos < SeqLength; pos++ )
  {
    if (CIntfData::getAt(Status, SeqStatus, pos))
    {
      if ( !DeviceName.empty() && !StatusName.empty() &&
           DeviceName == std::string(Status.Device) && 
           StatusName == std::string(Status.StatusName))
      {
        MinStatus = min(MinStatus, Status.Status);
      }
      else if ( !DeviceName.empty() && StatusName.empty() &&
                DeviceName == std::string(Status.Device))
      {
        MinStatus = min(MinStatus, Status.Status);
      }
      else if ( DeviceName.empty() && !StatusName.empty() &&
                StatusName == std::string(Status.StatusName))
      {
        MinStatus = min(MinStatus, Status.Status);
      }
      else
      {
        MinStatus = min(MinStatus, Status.Status);
      }
    }
  }

  return MinStatus;
}

