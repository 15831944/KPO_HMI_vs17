// Copyright (C) 2004 SMS Demag AG

#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif


#include <string>
#include <cfloat>
#include <sstream>

#include "iData_Provider_s.hh"

//##ModelId=40BC445A02BF
#include "CIntfDataDouble.h"



//##ModelId=40BC445A02BF
CIntfDataDouble::~CIntfDataDouble()
{
	// ToDo: Add your specialized code here and/or call the base class
}

//##ModelId=40BC445A02C9
CIntfDataDouble::CIntfDataDouble( CData_Provider * pData_Provider, const std::string &Name, const std::string &Key)
:CIntfData(pData_Provider),m_Data(DEF::Inv_Double)
{
  m_Key = Key;
  m_Name = Name;
  m_Type = CIntfData::Double;
}

//##ModelId=40BC458C014C
double CIntfDataDouble::getData()
{
	return m_Data;
}

//##ModelId=40BC458C032D
void CIntfDataDouble::setData(double value)
{
	m_Data = value;

  try
  {
    m_pData_Provider->Validator.validateDouble(m_Name,m_Key,m_Data);
  }
  catch(...)
  {
    m_pData_Provider->EventLogExc("Unknown exception", m_pData_Provider->getProviderName()+":setData()", "set double");
  }

	return;
}



//##ModelId=40D29EEF00EE
void CIntfDataDouble::showContent(long Level)
{
  std::ostringstream Message;
  Message << "CData_Provider content : " <<  getContent();

  log(Message.str(),Level);
}

//##ModelId=44FE999A021C
std::string CIntfDataDouble::getContent()
{
  std::ostringstream Content;
  Content << m_Key << " " << m_Name << " " << m_Type << " " << m_Data;
  return Content.str();
}
