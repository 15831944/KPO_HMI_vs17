// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CFORMATTEDID_439E9CEF0075_INCLUDED
#define _INC_CFORMATTEDID_439E9CEF0075_INCLUDED

#include <string>
#include <map>
#include <set>
#include <vector>

class CFormattedIDElement;

class CFormattedID 
{
public:

  void fixFormattedIDElement(const std::string& Qualifier, const std::string& Fixed);

  std::string getString(const std::string& ID, const std::string& Default, const std::string& Qualifier) const;

  long getLong(const std::string& ID, const std::string& Default, const std::string& Qualifier) const;

  void addFormattedIDElement(const std::string& Qualifier, const std::string& FixedType = "", const std::string& Fixed = "" , bool Truncate = false);

  bool isValidID(const std::string & ID, std::string & ErrorMessage) const;

  void setFormat(const std::string& value);

  virtual ~CFormattedID();

  CFormattedID();

  CFormattedID(const CFormattedID& FormattedID);

  CFormattedID& operator=(const CFormattedID& FormattedID);

protected:
  virtual void init();

  std::map<std::string,std::string> m_SampleTypeList;

  long m_FormattedIDLength;

  std::string m_Format;

  void generateString(const CFormattedIDElement* pFormattedIDElement, std::string  Value, std::string &ActString, const std::string  FillSign = ""  ) const;

  void generateString(const std::string& Qualifier, std::string  Value, std::string &ActString, const std::string  FillSign = ""  ) const;

  void trimString(std::string &ActString, const std::string& Sign ) const;

  long getLength(const std::string& Qualifier) const;

  std::string getFormat(const std::string& Qualifier) const;

  CFormattedIDElement* getFormattedIDElement(const std::string&  Qualifier);

  const CFormattedIDElement* getFormattedIDElement(const std::string& Qualifier) const;

  void log(const std::string & Message, long Level) const;

  void clear();

private:
  std::set<std::string> m_QualifierList;

  std::vector<CFormattedIDElement*> m_FormattedIDElementList;

};

#endif /* _INC_CFORMATTEDID_439E9CEF0075_INCLUDED */
