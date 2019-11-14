// Copyright (C) 2012 SMS Siemag AG

#include "CSMC_DBColProfile.h"
#include "cCBS_StdInitBase.h"

bool CSMC_DBColProfile::m_ShowPrecisionTestLogs = true;
bool CSMC_DBColProfile::m_IniFileAlreadyRead = false;

CSMC_DBColProfile::~CSMC_DBColProfile()
{
}

CSMC_DBColProfile::CSMC_DBColProfile(const std::string  & TableName,  SMC_DB_Type Type, const std::string  & ColName, long ColSize)
: m_TableName(TableName)
, m_ColName(ColName)
, m_Type(Type)
, m_ColSize(ColSize)
, m_isActive(false)
, m_writeNullValue(false)
{
  if (!m_IniFileAlreadyRead)
  {
    m_IniFileAlreadyRead = true;
    cCBS_StdInitBase * pCBS_StdInitBase = cCBS_StdInitBase::getInstance();
    pCBS_StdInitBase->replaceWithEntry("TESTLOG", "ShowPrecisionTestLogs", m_ShowPrecisionTestLogs);
  }
}

bool CSMC_DBColProfile::isWriteNullValue()
{
  return m_writeNullValue;
}
