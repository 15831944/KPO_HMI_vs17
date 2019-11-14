// Copyright (C) 2008 SMS Demag AG

#include "CIntfData.h"

#include "CInjectDataHandler.h"

CInjectDataHandler::~CInjectDataHandler()
{
}

CInjectDataHandler::CInjectDataHandler()
{
	m_InjectData.length(0);
}

CInjectDataHandler::CInjectDataHandler(seqInjectData& InjectData)
{
	fill(InjectData);
}

void CInjectDataHandler::fill(seqInjectData& InjectData)
{
	m_InjectData = InjectData;
}

seqInjectData& CInjectDataHandler::getInjectData()
{
  return m_InjectData;
}

void CInjectDataHandler::update(seqInjectData& InjectData)
{
  for ( long i = 0 ; i < CIntfData::getLength(InjectData) ; ++i )
  {
    sInjectData InjectDataStruct;
    CIntfData::getAt(InjectDataStruct,InjectData,i);

    update(InjectDataStruct);
  }
}

void CInjectDataHandler::update(sInjectData& InjectData)
{
  // try to find existing device of InjectData
  if ( isInjectType((std::string)InjectData.InjectType))
  {
    for ( long i = 0 ; i < CIntfData::getLength(m_InjectData) ; ++i )
    {
      sInjectData InjectDataStruct;
      CIntfData::getAt(InjectDataStruct,m_InjectData,i);

      // find position of new InjectData at m_InjectData
      if ((std::string)InjectDataStruct.InjectType == (std::string)InjectData.InjectType)
      {
        CIntfData::setAt(m_InjectData,InjectData,i);
      }
    }
  }
  else
  {
    insertInjectData(InjectData);
  }
}

bool CInjectDataHandler::isInjectType(const std::string& InjectType)
{
	return isInjectType(m_InjectData,InjectType);
}

bool CInjectDataHandler::isInjectType(seqInjectData& InjectData, const std::string& InjectType)
{
  bool RetValue = false;

  for ( long i = 0 ; i < CIntfData::getLength(InjectData) ; ++i )
  {
    sInjectData InjectDataStruct;

    CIntfData::getAt(InjectDataStruct,InjectData,i);

    if ( (std::string)InjectDataStruct.InjectType == InjectType )
    {
      RetValue = true;
      break;
    }
  }
	return RetValue;
}

sInjectData CInjectDataHandler::findInjectData(seqInjectData& InjectData, const std::string& InjectType)
{
  sInjectData RetValue;

  for ( long i = 0 ; i < CIntfData::getLength(InjectData) ; ++i )
  {
    sInjectData InjectDataStruct;

    CIntfData::getAt(InjectDataStruct,InjectData,i);

    if ( (std::string)InjectDataStruct.InjectType == InjectType )
    {
      RetValue = InjectDataStruct;
      break;
    }
  }

	return RetValue;
}

sInjectData CInjectDataHandler::findInjectData(const std::string& InjectType)
{
	return findInjectData(m_InjectData,InjectType);
}

void CInjectDataHandler::insertInjectData(sInjectData& InjectData)
{
  CIntfData::insert(m_InjectData,InjectData);
}

void CInjectDataHandler::updateInjectMatValue(const std::string& InjectType, double InjectMatValue)
{
  sInjectData theInjectData;
  if (!isInjectType(InjectType))
  {
    theInjectData.InjectType = InjectType.c_str();
    theInjectData.InjectMatValue = InjectMatValue;
    CIntfData::insert(m_InjectData,theInjectData);
  }
  else
  {
    for ( long i = 0 ; i < CIntfData::getLength(m_InjectData) ; ++i )
    {
      CIntfData::getAt(theInjectData,m_InjectData,i);

      // find position of new InjectData at m_InjectData
      if ( (std::string)theInjectData.InjectType == InjectType )
      {
        theInjectData.InjectMatValue = InjectMatValue;
      } // if ( (std::string)InjectData.InjectType == InjectType )
      CIntfData::setAt(m_InjectData,theInjectData,i);
    } // for ( long i = 0 ; i < CIntfData::getLength(m_InjectData) ; ++i )
  }
}

void CInjectDataHandler::updateInjectMatCode(const std::string& InjectType, const std::string& InjectMatCode)
{
  sInjectData theInjectData;

  if ( !isInjectType(InjectType) )
  {
    theInjectData.InjectType = InjectType.c_str();
    theInjectData.InjectMatCode = InjectMatCode.c_str();
    CIntfData::insert(m_InjectData,theInjectData);
  }
  else
  {
    for ( long i = 0 ; i < CIntfData::getLength(m_InjectData) ; ++i )
    {
      CIntfData::getAt(theInjectData,m_InjectData,i);

      // find position of new InjectData at m_InjectData
      if ( (std::string)theInjectData.InjectType == InjectType )
      {
        theInjectData.InjectMatCode = InjectMatCode.c_str();
      }
      CIntfData::setAt(m_InjectData,theInjectData,i);
    }
  }
}

double CInjectDataHandler::getInjectMatValue(const std::string& InjectType)
{
  double InjectMatValue = DEF::Inv_Double;
  sInjectData theInjectData;

  for (long i = 0; i < CIntfData::getLength(m_InjectData); i++)
  {
    CIntfData::getAt(theInjectData,m_InjectData,i);
    if ( (std::string)theInjectData.InjectType == InjectType)
    {
      InjectMatValue = theInjectData.InjectMatValue;
      break;
    }
  }
  return InjectMatValue;
}

std::string CInjectDataHandler::getInjectMatCode(const std::string& InjectType)
{
  std::string InjectMatCode = DEF::Inv_String;
  sInjectData theInjectData;

  for (long i = 0; i < CIntfData::getLength(m_InjectData); i++)
  {
    CIntfData::getAt(theInjectData,m_InjectData,i);
    if ( (std::string)theInjectData.InjectType == InjectType)
    {
      InjectMatCode = theInjectData.InjectMatCode;
      break;
    }
  }
  return InjectMatCode;
}

void CInjectDataHandler::diff(seqInjectData& InjectData)
{
  for ( long i = 0 ; i < CIntfData::getLength(InjectData) ; ++i )
  {
    sInjectData InjectDataStruct;
    CIntfData::getAt(InjectDataStruct,InjectData,i);
    std::string InjectType = InjectDataStruct.InjectType;

    if (this->isInjectType(InjectType))
    {
      double Diff = max(0, (this->getInjectMatValue(InjectType) - InjectDataStruct.InjectMatValue));
      this->updateInjectMatValue(InjectType, Diff);
    }
    else
    {
      // insert a new device
      this->updateInjectMatValue(InjectType, InjectDataStruct.InjectMatValue);
    }
  }
}

void CInjectDataHandler::add(seqInjectData& InjectData)
{
  for ( long i = 0 ; i < CIntfData::getLength(InjectData) ; ++i )
  {
    sInjectData InjectDataStruct;
    CIntfData::getAt(InjectDataStruct,InjectData,i);
    std::string InjectType = InjectDataStruct.InjectType;

    if (isInjectType(InjectType))
    {
      double Sum = getInjectMatValue(InjectType) + InjectDataStruct.InjectMatValue;
      updateInjectMatValue(InjectType, Sum);
    }
    else
    {
      // insert a new device
      updateInjectMatValue(InjectType, InjectDataStruct.InjectMatValue);
    }
  }
}
