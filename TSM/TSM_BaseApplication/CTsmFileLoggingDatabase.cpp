// Copyright (C) 2004 SMS Demag AG

#include "cCBS_StdInitBase.h"
#include "CDateTime.h"
#include "CTsmFileLoggingDatabase.h"



CTsmFileLoggingDatabase::CTsmFileLoggingDatabase()
: m_fileDbName(getFileDbName())
{
  m_fstream.open(m_fileDbName.c_str(), std::ios::out | std::ios::trunc);
  if (!m_fstream.is_open())
  {
    std::cerr << "Unable to open file " << m_fileDbName << std::endl;
  }
}

CTsmFileLoggingDatabase::CTsmFileLoggingDatabase(std::string TaskName)
: m_fileDbName(getFileDbName(TaskName))
{
  m_fstream.open(m_fileDbName.c_str(), std::ios::out | std::ios::trunc);
  if (!m_fstream.is_open())
  {
    std::cerr << "Unable to open file " << m_fileDbName << std::endl;
  }
}


CTsmFileLoggingDatabase::~CTsmFileLoggingDatabase()
{
  if (m_fstream.is_open())
  {
    m_fstream.close();
  }
}

void CTsmFileLoggingDatabase::protocolPlantStateTransition(const CEventID & eventID, const CProcessStatusID & currentPlantState, const CProcessStatusID & nextPlantState)
{
  if (m_fstream.is_open())
  {
    CDateTime ActTime;
    m_fstream << ActTime.asString() << " Plant state transition from <" 
              << currentPlantState  << "> to <"
              << nextPlantState     << "> on event <"
              << eventID            << ">"
              << std::endl;
  }
  else
  {
    std::cerr << "Unable to write into file " << m_fileDbName << std::endl;
  }
}

void CTsmFileLoggingDatabase::protocolProductStateTransition(const CObjectID & productID, const CEventID & eventID, const CProcessStatusID & currentProductState, const CProcessStatusID & currentPlantState, const CProcessStatusID & newProductState)
{
  if (m_fstream.is_open())
  {
    CDateTime ActTime;
    m_fstream << ActTime.asString()  << "Product state transition from <" 
              << currentProductState << "> to <"
              << newProductState     << "> on event <"
              << eventID             << "> for product <" 
              << productID           << "> on plant state <" 
              << currentPlantState   << ">"
              << std::endl;
  }
  else
  {
    std::cerr << "Unable to write into file " << m_fileDbName << std::endl;
  }

}

std::string CTsmFileLoggingDatabase::getFileDbName()
{
  cCBS_StdInitBase *pInitBase = cCBS_StdInitBase::getInstance();
  std::string dataBaseName;
  cCBS_StdInitBase::getInstance()->replaceWithEntry("PATH", "TsmFileDataBaseName", dataBaseName);
  return pInitBase->getXPACT_SMC_LOG() + dataBaseName;
}

std::string CTsmFileLoggingDatabase::getFileDbName(const std::string& TaskName)
{
  cCBS_StdInitBase *pInitBase = cCBS_StdInitBase::getInstance();
  
  std::string dataBaseName;
  cCBS_StdInitBase::getInstance()->replaceWithEntry("PATH", "TsmFileDataBaseName", dataBaseName);

  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName, "TsmFileDataBaseName", dataBaseName);
  
  return pInitBase->getXPACT_SMC_LOG() + dataBaseName;
}

void CTsmFileLoggingDatabase::addScheduleItem(const CObjectID & eventPointID, const CObjectID & productID, bool isCheckIn)
{
	// ToDo: Add your specialized code here
	
	static_cast<void>(0);
}

