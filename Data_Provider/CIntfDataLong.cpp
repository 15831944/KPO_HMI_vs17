// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif


#include <string>
#include <sstream>

#include "iData_Provider_s.hh"

//##ModelId=40B6F651030D
#include "CIntfDataLong.h"



//##ModelId=40B6F651030D
long CIntfDataLong::getData()
{
	return m_Data;
}

//##ModelId=40B6F6510317
void CIntfDataLong::setData(long value)
{
	m_Data = value;

  try
  {
    m_pData_Provider->Validator.validateLong(m_Name,m_Key,m_Data);
  }
  catch(...)
  {
    m_pData_Provider->EventLogExc("Unknown exception", m_pData_Provider->getProviderName()+":setData", "set long");
  }

	return;
}



//##ModelId=40B72F290130
CIntfDataLong::~CIntfDataLong()
{
}

//##ModelId=40B72F2A03DB
CIntfDataLong::CIntfDataLong( CData_Provider * pData_Provider, const std::string &Name, const std::string &Key)
:CIntfData(pData_Provider),m_Data(DEF::Inv_Long)
{
  m_Key = Key;
  m_Name = Name;
  m_Type = CIntfData::Long;
}




//##ModelId=40D29EBF00C7
void CIntfDataLong::showContent(long Level)
{
  std::ostringstream Message;
  Message << "CData_Provider content : " << getContent();

  log(Message.str(),Level);
}

//##ModelId=44FE999A0172
std::string CIntfDataLong::getContent()
{
  std::ostringstream Content;
  Content << m_Key << " " << m_Name << " " << m_Type << " " << m_Data;
  return Content.str();
}
