// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif


#include <string>
#include <iostream>

//##ModelId=40B6F5FD019A
#include "CIntfData.h"
//##ModelId=40B6F5FD019A
#include "CData_Provider.h"


//##ModelId=40B6F5FD019A
const std::string& CIntfData::getName()
{
  return m_Name;
}



//##ModelId=40B6FFBF0279
void CIntfData::log(const std::string & Message, long Level)
{
	if ( m_pData_Provider && m_pData_Provider->getTraceLevel() >= Level )
  {
    m_pData_Provider->log(Message,Level);
  }
}


//##ModelId=40B74F2901AE
CIntfData::~CIntfData()
{
	// ToDo: Add your specialized code here and/or call the base class
}



//##ModelId=40BF22590165
 const std::string &  CIntfData::getType() 
{
	return m_Type;
}



//##ModelId=40D29EAD02D4
void CIntfData::showContent(long Level)
{
  // TODO: Add your specialized code here.
}



//##ModelId=414957C40121
CIntfData::CIntfData(CData_Provider* pData_Provider)
: m_pData_Provider(pData_Provider)
, m_isUpdated(true)
, m_isRequested(false)
{
}



//##ModelId=415D878E0231
std::string CIntfData::String("String");

//##ModelId=415D878E0259
std::string CIntfData::Long("Long");

//##ModelId=415D878E0277
std::string CIntfData::Double("Double");

//##ModelId=415D878E029F
std::string CIntfData::Bool("Bool");

//##ModelId=415D878E02C8
std::string CIntfData::Any("Any");


//##ModelId=44FE999B001F
std::string CIntfData::getContent()
{
  return std::string("");
}


//##ModelId=44FE999A0371
void CIntfData::setUpdated(bool value)
{
  m_isUpdated = value;
}

//##ModelId=44FE999A03A3
bool CIntfData::isUpdated()
{
  return m_isUpdated;
}

void CIntfData::setRequested(bool value)
{
  m_isRequested = value;
}

bool CIntfData::isRequested()
{
  return m_isRequested;
}
