// Copyright (C) 2004 SMS Demag AG

#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif


#include <string>
#include <sstream>

//##ModelId=40BC54EF006E
#include "CIntfDataBoolean.h"



//##ModelId=40BC54EF006E
CIntfDataBoolean::CIntfDataBoolean( CData_Provider * pData_Provider, const std::string &Name, const std::string &Key)
:CIntfData(pData_Provider),m_Data(false)
{
  m_Key = Key;
  m_Name = Name;
  m_Type = CIntfData::Bool;
}

//##ModelId=40BC5510000A
CIntfDataBoolean::~CIntfDataBoolean()
{
	// ToDo: Add your specialized code here and/or call the base class
}

//##ModelId=40BC551200AD
bool CIntfDataBoolean::getData()
{
	return m_Data;
}

//##ModelId=40BC55120252
void CIntfDataBoolean::setData(bool value)
{
	m_Data = value;
	return;
}



//##ModelId=40D29EEA029F
void CIntfDataBoolean::showContent(long Level)
{
  std::ostringstream Message;
  Message << "CData_Provider content : " << getContent();

  log(Message.str(),Level);
}

//##ModelId=44FE999A02D0
std::string CIntfDataBoolean::getContent()
{
  std::ostringstream Content;
  Content << m_Key << " " << m_Name << " " << m_Type << " " << m_Data;
  return Content.str();
}
