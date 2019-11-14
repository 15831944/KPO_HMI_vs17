// Copyright (C) 2004 SMS Demag AG

#include <iostream>
#include "iSMC_DataDefinitions_s.hh"

#include "CDM_StatusHandler.h"



std::map<std::string,long> &  CDM_StatusHandler::getStatusList()
{
  return m_StatusList;
}



void CDM_StatusHandler::addStatus(const std::string& StatusName, long Status)
{
  m_StatusList.insert( std::pair<std::string,long>(StatusName,Status));
}

void CDM_StatusHandler::setStatus(const std::string& StatusName, long Status)
{
  std::map<std::string,long>::iterator it;

  it = m_StatusList.find(StatusName);
  if ( it != m_StatusList.end() )
  {
    it->second = Status;
  }
  else
  {
    addStatus(StatusName, Status);
  }

}

long CDM_StatusHandler::getStatus(const std::string& StatusName)
{
  long RetValue = DEF::Inv_Long;

  std::map<std::string,long>::iterator it;

  it = m_StatusList.find(StatusName);
  if ( it != m_StatusList.end() )
  {
    RetValue = it->second;
  }

	return RetValue;
}

bool CDM_StatusHandler::isStatusChanged(const std::string& StatusName, long value)
{
  bool isChanged = false;

  std::map<std::string,long>::iterator it;
  it = m_StatusList.find(StatusName);
  if ( it != m_StatusList.end() )
  {
    //compare and update status if it has changed
    long st = it->second;
    if (st != value)
    {
      isChanged = true;
      it->second = value;
    }
  }
  else
  {
    // new status also means a change
    addStatus(StatusName, value);
    isChanged = true;
  }

  return isChanged;
}
