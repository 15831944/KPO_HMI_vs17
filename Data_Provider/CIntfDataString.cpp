// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif


#include <string>
#include <iostream>
#include <sstream>
 
#include "iData_Provider_s.hh"

//##ModelId=40B740D200EC
#include "CIntfDataString.h"



//##ModelId=40B740D200EC
std::string  CIntfDataString::getData()
{
	return m_Data;
}

//##ModelId=40B740D200F6
void CIntfDataString::setData(const std::string& value)
{
	m_Data = value;
  
  try
  {
    m_pData_Provider->Validator.validateString(m_Name,m_Key,m_Data);
  }
  catch(...)
  {
    m_pData_Provider->EventLogExc("Unknown exception", m_pData_Provider->getProviderName()+":setData(std::string& value)", "set string");
  }

	return;
}

//##ModelId=40B740D20100
CIntfDataString::~CIntfDataString()
{
}

//##ModelId=40B740D2010A
CIntfDataString::CIntfDataString( CData_Provider * pData_Provider, const std::string &Name, const std::string &Key)
:CIntfData(pData_Provider),m_Data(DEF::Inv_String)
{
  m_Key = Key;
  m_Name = Name;
  m_Type = CIntfData::String;
}



//##ModelId=40D29EFA0003
void CIntfDataString::showContent(long Level)
{
  std::ostringstream Message;
  Message << "CData_Provider content : " << getContent();

  log(Message.str(),Level);
}

//##ModelId=44FE999A00BE
std::string CIntfDataString::getContent()
{
  std::ostringstream Content;
  Content << m_Key << " " << m_Name << " " << m_Type << " " << m_Data;
  return Content.str();
}
