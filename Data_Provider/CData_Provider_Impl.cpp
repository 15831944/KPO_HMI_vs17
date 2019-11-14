// Copyright (C) 2004 SMS Demag AG

#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <string>
#include <iostream>
#include "CIntfData.h"
#include "iData_Provider_s.hh"
#include "CData_Provider_Impl.h"


CORBA::Any* CData_Provider_Impl::getAny(const char* Key, const char* Name)
{
  if (! m_Critical_Section.lock("CData_Provider_Impl::getAny"))
  {
    CORBA::Any* t = new CORBA::Any(); 
    return t;
  }

  CORBA::Any *ActAny = 0;

  try
  {
    ActAny = new CORBA::Any(CData_Provider::getAny(Key,Name));
  }
  catch(...)
  {
    std::string Message = "during reading CORBA interface Data of Type Any : ";
    Message += Name;

    EventLogExc(Message, "CData_Provider_Impl::getAny","");

    ActAny = new CORBA::Any();
  }

  m_Critical_Section.unlock("CData_Provider_Impl::getAny");

  return ActAny;

}

void CData_Provider_Impl::setAny(const char* Key, const char* Name, const CORBA::Any& NewAny)
{
  if (! m_Critical_Section.lock("CData_Provider_Impl::setAny"))
  {
    return;
  }

  try
  {
    CORBA::Any ActAny;

    ActAny = NewAny;

    CData_Provider::setAny(Key,Name,ActAny);
  }
  catch(...)
  {
    std::string Message = "during writing CORBA interface Data of Type Any : ";
    Message += Name;

    EventLogExc(Message, "CData_Provider_Impl::setAny", "");

  }

  m_Critical_Section.unlock("CData_Provider_Impl::getAny");
}


void CData_Provider_Impl::setLong(const char* Key, const char* Name, CORBA::Long value)
{
  if (! m_Critical_Section.lock("CData_Provider_Impl::setLong"))
  {
    return;
  }

  try
  {
    CData_Provider::setLong(Key,Name,value);
  }
  catch(...)
  {
    std::string Message = "during writing CORBA interface Data of Type Long : ";
    Message += Name;

    EventLogExc(Message, "CData_Provider_Impl::setLong", "");
  }

  m_Critical_Section.unlock("CData_Provider_Impl::setLong");
}

CORBA::Long CData_Provider_Impl::getLong(const char* Key, const char* Name)
{
  if (! m_Critical_Section.lock("CData_Provider_Impl::getLong"))
  {
    return DEF::Inv_Long;
  }

  long RetValue = DEF::Inv_Long;

  try
  {
    RetValue = CData_Provider::getLong(Key,Name);
  }
  catch(...)
  {
    std::string Message = "during reading CORBA interface Data of Type Long : ";
    Message += Name;

    EventLogExc(Message, "CData_Provider_Impl::getLong", "");
  }

  m_Critical_Section.unlock("CData_Provider_Impl::getLong");

  return RetValue;

}


void CData_Provider_Impl::setString(const char* Key, const char* Name, const char * value)
{
  if (! m_Critical_Section.lock("CData_Provider_Impl::setString"))
  {
    return;
  }

  try
  {
    CData_Provider::setString(Key,Name,value);
  }
  catch(...)
  {
    std::string Message = "during writing CORBA interface Data of Type String : ";
    Message += Name;

    EventLogExc(Message, "CData_Provider_Impl::setString", "");
  }

  m_Critical_Section.unlock("CData_Provider_Impl::setString");
}

char * CData_Provider_Impl::getString(const char* Key, const char* Name)
{
  if (! m_Critical_Section.lock("CData_Provider_Impl::getString"))
  {
    return CORBA::string_dup(DEF::Inv_String);
  }

  std::string RetValue = DEF::Inv_String;
  try
  {
    RetValue = CData_Provider::getString(Key,Name);
  }
  catch(...)
  {
    std::string Message = "during reading CORBA interface Data of Type String : ";
    Message += Name;

    EventLogExc(Message, "CData_Provider_Impl::getString", "");
  }

  m_Critical_Section.unlock("CData_Provider_Impl::getString");

  return CORBA::string_dup(RetValue.c_str());
}

void CData_Provider_Impl::indicate(const char* Key)
{
  if (! m_Critical_Section.lock("CData_Provider_Impl::indicate"))
  {
    return;
  }

  try
  {
    CData_Provider::indicate(Key);
  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider_Impl::indicate", "");
  }

  m_Critical_Section.unlock("CData_Provider_Impl::indicate");

}

long CData_Provider_Impl::complete(const char * Key, const char * Action)
{
  long RetValue = DEF::Inv_Long;

  if (! m_Critical_Section.lock("CData_Provider_Impl::complete"))
  {
    return RetValue;
  }

  try
  {
    RetValue = CData_Provider::doComplete(Key,Action);
  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider_Impl::complete", "");
  }

  m_Critical_Section.unlock("CData_Provider_Impl::complete");

  return RetValue;

}





void CData_Provider_Impl::setDouble(const char* Key, const char* Name, CORBA::Double value)
{
  if (! m_Critical_Section.lock("CData_Provider_Impl::setDouble"))
  {
    return;
  }

  try
  {
    CData_Provider::setDouble(Key,Name,value);
  }
  catch(...)
  {
    std::string Message = "during writing CORBA interface Data of Type Double : ";
    Message += Name;

    EventLogExc(Message, "CData_Provider_Impl::setDouble", "");
  }

  m_Critical_Section.unlock("CData_Provider_Impl::setDouble");

}

CORBA::Double CData_Provider_Impl::getDouble(const char* Key, const char* Name)
{
  if (! m_Critical_Section.lock("CData_Provider_Impl::getDouble"))
  {
    return DEF::Inv_Double;
  }

  double RetValue = DEF::Inv_Double;

  try
  {
    RetValue = CData_Provider::getDouble(Key,Name);
  }
  catch(...)
  {
    std::string Message = "during reading CORBA interface Data of Type Double : ";
    Message += Name;

    EventLogExc(Message, "CData_Provider_Impl::getDouble", "");
  }

  m_Critical_Section.unlock("CData_Provider_Impl::getDouble");

  return RetValue;
}



CORBA::Boolean CData_Provider_Impl::getBoolean(const char* Key, const char* Name)
{
  if (! m_Critical_Section.lock("CData_Provider_Impl::getBoolean"))
  {
    return false;
  }

  bool RetValue = false;

  try
  {
    RetValue = CData_Provider::getBoolean(Key,Name);
  }
  catch(...)
  {
    std::string Message = "during reading CORBA interface Data of Type Boolean : ";
    Message += Name;

    EventLogExc(Message, "CData_Provider_Impl::getBoolean", "");
  }

  m_Critical_Section.unlock("CData_Provider_Impl::getBoolean");

  return RetValue;
}

void CData_Provider_Impl::setBoolean(const char* Key, const char* Name, CORBA::Boolean value)
{
  if (! m_Critical_Section.lock("CData_Provider_Impl::setBoolean"))
  {
    return;
  }

  try
  {
    CData_Provider::setBoolean(Key,Name,value);
  }
  catch(...)
  {
    std::string Message = "during writing CORBA interface Data of Type Boolean : ";
    Message += Name;
   
    EventLogExc(Message, "CData_Provider_Impl::setBoolean", "");
  }

  m_Critical_Section.unlock("CData_Provider_Impl::setBoolean");

}

seqIntfDataList* CData_Provider_Impl::getIntfDataList(const char* Key)
{
  if (! m_Critical_Section.lock("CData_Provider_Impl::getIntfDataList"))
  {
    return new seqIntfDataList();
  }

  seqIntfDataList* ret = new seqIntfDataList();

  try
  {
    std::map<std::string,std::string> IntfDataNameList = getIntfDataTypeList(Key);
    std::map<std::string,std::string>::iterator it;

    if ( !IntfDataNameList.empty() )
    {
      for ( it = IntfDataNameList.begin(); it != IntfDataNameList.end() ; ++ it )
      {
        sIntfDataList IntfDataList;
        IntfDataList.Name = it->first.c_str();
        IntfDataList.Type = it->second.c_str();

        CIntfData::insert(*ret,IntfDataList);
      }
    }
    else
    {
      ret->length(0);
    }
  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider_Impl::getIntfDataList", "");
  }

  m_Critical_Section.unlock("CData_Provider_Impl::getIntfDataList");

  return ret;	

}

seqIntfDataList* CData_Provider_Impl::getRequestedIntfDataList(const char* Key)
{
  if (! m_Critical_Section.lock("CData_Provider_Impl::getRequestedIntfDataList"))
  {
    seqIntfDataList* t = new seqIntfDataList();
    return t;
  }

  seqIntfDataList* ret = 0;

  try
  {
    ret = new seqIntfDataList();

    std::map<std::string,std::string> IntfDataNameList = getRequestedIntfDataTypeList(Key);
    std::map<std::string,std::string>::iterator it;

    if ( !IntfDataNameList.empty() )
    {
      for ( it = IntfDataNameList.begin(); it != IntfDataNameList.end() ; ++ it )
      {
        sIntfDataList IntfDataList;
        IntfDataList.Name = it->first.c_str();
        IntfDataList.Type = it->second.c_str();

        CIntfData::insert(*ret,IntfDataList);
      }
    }
    else
    {
      ret->length(0);
    }
  }
  catch(...)
  {
    EventLogExc("Unknown exception","CData_Provider_Impl::getRequestedIntfDataList","");
  }

  m_Critical_Section.unlock("CData_Provider_Impl::getRequestedIntfDataList");

  return ret;	

}

std::vector<std::string> CData_Provider_Impl::getIntfKeyList()
{
  std::vector<std::string> IntfKeyList;

  if (! m_Critical_Section.lock("CData_Provider_Impl::getIntfKeyList"))
  {
    return IntfKeyList;
  }

  try
  {
    IntfKeyList = getIntfKeyList();
  }
  catch(...)
  {
    EventLogExc("Unknown exception","CData_Provider_Impl::getIntfKeyList","");
  }

  m_Critical_Section.unlock("CData_Provider_Impl::getIntfKeyList");

  return IntfKeyList;	

}


char * CData_Provider_Impl::generateDataKey(const char* Value)
{
  if (! m_Critical_Section.lock("CData_Provider_Impl::generateDataKey"))
  {
    return CORBA::string_dup(DEF::Inv_String);
  }

  std::string RetValue = DEF::Inv_String;
  try
  {
    RetValue = CData_Provider::generateDataKey(Value);
  }
  catch(...)
  {
    std::string Message = "Unknown exception during generating DataKey ";
    EventLogExc(Message, "CData_Provider_Impl::generateDataKey", "");
  }

  m_Critical_Section.unlock("CData_Provider_Impl::generateDataKey");

  return CORBA::string_dup(RetValue.c_str());
}

char * CData_Provider_Impl::getIntfDataType(const char* Key, const char* Name)
{
  if (! m_Critical_Section.lock("CData_Provider_Impl::getIntfDataType"))
  {
    return CORBA::string_dup(DEF::Inv_String);
  }

  std::string RetValue = DEF::Inv_String;
  try
  {
    RetValue = CData_Provider::getIntfDataType(Key, Name);
  }
  catch(...)
  {
    std::string Message = "Unknown exception during getting DataType ";
    EventLogExc(Message, "CData_Provider_Impl::getIntfDataType", "");
  }

  m_Critical_Section.unlock("CData_Provider_Impl::getIntfDataType");

  return CORBA::string_dup(RetValue.c_str());
}

char * CData_Provider_Impl::getProviderName()
{
  if (! m_Critical_Section.lock("CData_Provider_Impl::getProviderName"))
  {
    return CORBA::string_dup(DEF::Inv_String);
  }

  std::string RetValue = DEF::Inv_String;
  try
  {
    RetValue = CData_Provider::getProviderName();
  }
  catch(...)
  {
    std::string Message = "Unknown exception during getting ProviderName ";
    EventLogExc(Message, "CData_Provider_Impl::getProviderName", "");
  }

  m_Critical_Section.unlock("CData_Provider_Impl::getProviderName");

  return CORBA::string_dup(RetValue.c_str());
}