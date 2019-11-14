// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <string>

//##ModelId=40B6F10803E4
#include "CIntfDataAny.h"

namespace localHere_cIntfDataAny
{
  struct EqualTypeCodes 
  {
            EqualTypeCodes(
                CORBA::TypeCode_ptr tc
            ): _ptr(tc) {}
    bool    operator()(CORBA::TypeCode_ptr rhs) const {
                return _ptr->equal(rhs);
            }
    CORBA::TypeCode_ptr _ptr;
  };
  void indent (int)
  {
    // at the time being, it's a dummy
  }
}
using namespace localHere_cIntfDataAny;

//##ModelId=40B6F10803E4
CORBA::Any& CIntfDataAny::getData()
{
	return m_pData;
}

//##ModelId=40B6F1090006
void CIntfDataAny::setData(CORBA::Any& value)
{
  m_pData = value;

  try
  {
    m_pData_Provider->Validator.validateAny(m_Name,m_Key,m_pData);
  }
  catch(...)
  {
    m_pData_Provider->EventLogExc("Unknown exception", m_pData_Provider->getProviderName()+":setData", "set sequence");
  }

	return;
}

//##ModelId=40B6F1090010
CIntfDataAny::CIntfDataAny( CData_Provider* pData_Provider, const std::string &Name, const std::string &Key)
:CIntfData(pData_Provider)
{
  m_Key     = Key;
  m_Name    = Name;
  m_Type    = CIntfData::Any;
  m_Indent  = 0;
  // Get a Factory for DynAny
  CORBA::Object_var dynObj = cCBS_ORB::getORB()->resolve_initial_references("DynAnyFactory");
  m_DynAnyFact             = DynamicAny::DynAnyFactory::_narrow(dynObj);
}

//##ModelId=40B6F1090012
CIntfDataAny::~CIntfDataAny()
{
}



//##ModelId=412C5A6B00DD
void CIntfDataAny::showContent(long Level)
{
	std::ostringstream Message;
  Message << "CData_Provider content : " << m_Key << " " << m_Name << " " << m_Type << " ";

  Message << getContent();

  log(Message.str(),Level);

}


//##ModelId=426CEACC0221
std::string CIntfDataAny::getContent()
{
  return CIntfData::getContent(m_pData,m_DynAnyFact);
}

