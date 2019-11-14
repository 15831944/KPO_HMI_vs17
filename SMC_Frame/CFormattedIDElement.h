// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CFORMATTEDIDELEMENT_439E9CFA0180_INCLUDED
#define _INC_CFORMATTEDIDELEMENT_439E9CFA0180_INCLUDED

#include <string>

class CFormattedIDElement 
{
public:
  bool getTruncate() const;

  void setTruncate(bool value);

  static const std::string Alpha;

  static const std::string Numeric;

  void setLength(long value);

  void setPos(long value);

  const std::string& getFixed() const;

  void setFixed(std::string& value);

  const std::string& getFixedType() const;

  void setFixedType(std::string& value);

  void setQualifier(std::string& value);

  const long getLength() const;

  const long getPos() const;

  std::string getFormat() const;

  const std::string& getQualifier() const;

  CFormattedIDElement(std::string Qualifier, long Length = 0, long Pos = 0);

  CFormattedIDElement(const CFormattedIDElement& FormattedIDElement);

  CFormattedIDElement& operator=(const CFormattedIDElement& FormattedIDElement);

  bool isUsed() const;

  void setTruncateLeft(bool Value);

  bool getTruncateLeft() const;

private:
  bool m_Truncate;

  //indicates whether we should cut the left part or the other
  bool m_TruncateLeft;

  std::string m_Fixed;

  std::string m_FixedType;

  std::string m_Qualifier;

  long m_Length;

  long m_Pos;

};

#endif /* _INC_CFORMATTEDIDELEMENT_439E9CFA0180_INCLUDED */
