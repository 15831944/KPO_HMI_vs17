// Copyright (C) 2004 SMS Demag AG

#include "CFormattedIDElement.h"

CFormattedIDElement::CFormattedIDElement(std::string Qualifier, long Length, long Pos)
: m_Qualifier(Qualifier)
, m_Length(Length)
, m_Pos(Pos)
, m_TruncateLeft(false)
, m_Truncate(false)
, m_Fixed("")
, m_FixedType("")
{
}

CFormattedIDElement::CFormattedIDElement(const CFormattedIDElement& FormattedIDElement)
: m_Qualifier(FormattedIDElement.m_Qualifier)
, m_Length(FormattedIDElement.m_Length)
, m_Pos(FormattedIDElement.m_Pos)
, m_TruncateLeft(FormattedIDElement.m_TruncateLeft)
, m_Truncate(FormattedIDElement.m_Truncate)
, m_Fixed(FormattedIDElement.m_Fixed)
, m_FixedType(FormattedIDElement.m_FixedType)
{
}

CFormattedIDElement& CFormattedIDElement::operator=(const CFormattedIDElement& FormattedIDElement)
{
  //check for self-assignment
  if (this == &FormattedIDElement)
    return *this;

  m_Qualifier = FormattedIDElement.m_Qualifier;
  m_Length = FormattedIDElement.m_Length;
  m_Pos = FormattedIDElement.m_Pos;
  m_TruncateLeft = FormattedIDElement.m_TruncateLeft;
  m_Truncate = FormattedIDElement.m_Truncate;
  m_Fixed = FormattedIDElement.m_Fixed;
  m_FixedType = FormattedIDElement.m_FixedType;

  return *this;
}

const long CFormattedIDElement::getLength() const
{
  return m_Length;
}

const long CFormattedIDElement::getPos() const
{
  return m_Pos;
}

const std::string& CFormattedIDElement::getQualifier() const
{
  return m_Qualifier;
}


const std::string CFormattedIDElement::Numeric("Numeric");

void CFormattedIDElement::setLength(long value)
{
  m_Length = value;
  return;
}

void CFormattedIDElement::setPos(long value)
{
  m_Pos = value;
  return;
}

const std::string& CFormattedIDElement::getFixed() const
{
  return m_Fixed;
}

void CFormattedIDElement::setFixed(std::string& value)
{
  m_Fixed = value;
  return;
}

const std::string& CFormattedIDElement::getFixedType() const
{
  return m_FixedType;
}

void CFormattedIDElement::setFixedType(std::string& value)
{
  m_FixedType = value;
  return;
}

void CFormattedIDElement::setQualifier(std::string& value)
{
  m_Qualifier = value;
  return;
}



const std::string CFormattedIDElement::Alpha("Alpha");



std::string CFormattedIDElement::getFormat() const
{
  std::string Format;

  for ( int i = 0 ; i < m_Length ; ++i)
  {
    Format.insert(i,m_Qualifier);
  }

  return Format;
}

bool CFormattedIDElement::isUsed() const
{
  bool RetValue = false;

  if ( m_Pos >= 0 && m_Length > 0 )
  {
    RetValue = true;
  }

  return RetValue;
}


bool CFormattedIDElement::getTruncate() const
{
  return m_Truncate;

}

void CFormattedIDElement::setTruncate(bool value)
{
  m_Truncate = value;
  return;

}

void CFormattedIDElement::setTruncateLeft(bool Value)
{
  m_TruncateLeft = Value;
}

bool CFormattedIDElement::getTruncateLeft() const
{
  return m_TruncateLeft;
}
