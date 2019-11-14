// Copyright (C) 2004 SMS Demag AG, Germany 

#include "CSMC_EventLogFrameController.h"

#include "CSMC_DBTableBase.h"



//##ModelId=41D9305A037D
CSMC_DBTableBase::CSMC_DBTableBase(cCBS_StdConnection* Connection)
: m_pStdConnection(Connection)
, m_pSMC_DBData(0)
{
}

//##ModelId=41D9305C0004
CSMC_DBTableBase::~CSMC_DBTableBase()
{
}


void CSMC_DBTableBase::setColumnsFromTable(CSMC_DBData* pSourceTable, long Row)
{
  if (m_pSMC_DBData)
  {
    m_pSMC_DBData->setColumnsFromTable(pSourceTable, Row);
  }
}

bool CSMC_DBTableBase::insert()
{
  bool RetValue = false;

  if (m_pSMC_DBData)
  {
    RetValue = m_pSMC_DBData->insert();
  }

  return RetValue;
}

void CSMC_DBTableBase::commit()
{
  if (m_pSMC_DBData)
  {
    m_pSMC_DBData->commit();
  }
}

bool CSMC_DBTableBase::deleteRows()
{
  bool RetValue = false;

  if (m_pSMC_DBData)
  {
    RetValue = m_pSMC_DBData->deleteRows();
  }

  return RetValue;
}

std::string CSMC_DBTableBase::getString(const std::string& ColName, long Row)
{
  std::string RetValue = CSMC_DBData::unspecString;

  if (m_pSMC_DBData)
  {
    RetValue = m_pSMC_DBData->getString(ColName, Row);
  }

  return RetValue;
}


long CSMC_DBTableBase::getLong(const std::string& ColName, long Row)
{
  long RetValue = CSMC_DBData::unspecLong;

  if (m_pSMC_DBData)
  {
    RetValue = m_pSMC_DBData->getLong(ColName, Row);
  }

  return RetValue;
}

double CSMC_DBTableBase::getDouble(const std::string& ColName, long Row)
{
  double RetValue = CSMC_DBData::unspecDouble;

  if (m_pSMC_DBData)
  {
    RetValue = m_pSMC_DBData->getDouble(ColName, Row);
  }

  return RetValue;
}

bool CSMC_DBTableBase::getBool(const std::string& ColName, long Row)
{
  bool RetValue = false;

  if (m_pSMC_DBData)
  {
    RetValue = m_pSMC_DBData->deleteRows();
  }

  return RetValue;
}
void CSMC_DBTableBase::setBool(const std::string &ColName, bool value)
{
  if (m_pSMC_DBData)
  {
    m_pSMC_DBData->setBool( ColName, value);
  }
}
void CSMC_DBTableBase::setDouble(const std::string  & ColName, double value)
{
  if (m_pSMC_DBData)
  {
    m_pSMC_DBData->setDouble( ColName, value);
  }
}
void CSMC_DBTableBase::setString( const std::string  & ColName, const std::string &value)
{
  if (m_pSMC_DBData)
  {
    m_pSMC_DBData->setString( ColName, value);
  }
}
void CSMC_DBTableBase::setLong( const std::string &ColName, long value)
{
  if (m_pSMC_DBData)
  {
    m_pSMC_DBData->setLong( ColName, value);
  }
}

bool CSMC_DBTableBase::first()
{
  bool RetValue = false;

  if (m_pSMC_DBData)
  {
    RetValue = m_pSMC_DBData->first();
  }

  return RetValue;
}
bool CSMC_DBTableBase::last()
{
  bool RetValue = false;

  if (m_pSMC_DBData)
  {
    RetValue = m_pSMC_DBData->last();
  }

  return RetValue;
}
bool CSMC_DBTableBase::next()
{
  bool RetValue = false;

  if (m_pSMC_DBData)
  {
    RetValue = m_pSMC_DBData->next();
  }

  return RetValue;
}
bool CSMC_DBTableBase::prev()
{
  bool RetValue = false;

  if (m_pSMC_DBData)
  {
    RetValue = m_pSMC_DBData->prev();
  }

  return RetValue;
}

long CSMC_DBTableBase::getLastRow()
{
  long RetValue = CSMC_DBData::unspecLong;

  if (m_pSMC_DBData)
  {
    RetValue = m_pSMC_DBData->getLastRow();
  }

  return RetValue;

}
