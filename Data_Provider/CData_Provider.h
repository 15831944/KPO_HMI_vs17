// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CINTFDATAPROVIDER_407BE8E50310_INCLUDED
#define _INC_CINTFDATAPROVIDER_407BE8E50310_INCLUDED

#include <string>
#include <map>
#include <set>

#include "corba.h"

#include "CIntfDataBuffer.h"
#include "CIntfDataValidator.h"
#include "CData_Provider_Critical_Section.h"

class CIntfDataSequence;
class CIntfDataLong;

class CIntfDataDouble;
class CIntfData;

class CIntfDataRuleSet;

//class providing dynamic data storage
class CData_Provider 
{
  friend class CIntfDataString;
  friend class CIntfDataLong;
  friend class CIntfDataDouble;
  friend class CIntfDataAny;
  friend class CIntfDataBoolean;

public:
  bool isKey(const std::string& Key);

  std::string getProviderName();

  virtual void EventLogValidationFailure(const std::string& Message) = 0;

  void setProviderName(std::string& value);

  virtual void EventLogExc(const std::string & Message, const std::string& Function, const std::string& Action) = 0;

  //Return Key of DataBuffer element with respectve Index, 
  //Index 0 = first element
  std::string getKey(long Index);

  //Return number of DataBuffer elements
  long getSize();

  //Set DataBUffer element with respective Key as "persistent"
  void setPersistence(const std::string& Key, bool Value);
  bool getPersistence(const std::string& Key);

  //Log content of actual DataBuffer element.
  void showContent(const std::string& Key, long Level);

  virtual void log(const std::string & Message, long Level);

  //calling doComplete method
  long complete(const std::string & Key, const std::string & Action);

  CData_Provider();

  //Set maximum Buffer size. In case of size reached, 
  //oldest DataBuffer element will be deleted (if not "persistent").
  void setBufferSize(long value);

  // delete data at this key. Key is not deleted
  bool deleteData(const std::string & Key, const std::string & Name = "");

  virtual void onDeleteDataKey(const std::string& Key);
  virtual long getTraceLevel() = 0;

protected:

  std::set<std::string> m_EvaluationList;
  std::string m_ProviderName;
  CIntfDataBuffer IntfDataBuffer;
  CIntfDataValidator  Validator;
  CData_Provider_Critical_Section m_Critical_Section;

  // moved from public
  std::string  getIntfDataType(const std::string& Key, const std::string& Name);
  std::map<std::string,std::string> getIntfDataTypeList(const std::string& Key);
  std::map<std::string,std::string> getRequestedIntfDataTypeList(const std::string& Key);

  virtual void onNewData();
  virtual void EventLogReadFailure(const std::string& Message) = 0;

  //Genrate automatic data key from internal Counter of DataBuffer
  std::string  generateDataKey(const std::string& Value);
  bool isUpdated(const std::string& Key,const std::string& Name);

  virtual void beforeDataAccess(const std::string & Key,const std::string & Name);
  virtual void afterDataAccess(const std::string& Key,const std::string& Name);

  //Inserting DataBummer element with respective Key, 
  //calling virtual OnIndicate method
  void indicate(const std::string & Key);
  virtual void onIndicate(const std::string & Key);

  //Calling setting isCompleted attribute to DataBuffer, 
  //calling virtual OnComplete method
  long doComplete(const std::string & Key, const std::string & Action);
  virtual long onComplete(const std::string & Key,const std::string & Action);

  virtual bool isLoggingOn();

  //Return List of Interface data for respective Key
  std::vector<CIntfData*>  getIntfDataList(const std::string& Key);
  std::set<std::string> getIntfReqList(const std::string& Key);

  std::vector<std::string> getIntfKeyList();

  CORBA::Any getAny(const std::string& Key, const std::string &Name);
  //calling virtual OnNewData method
  void setAny(const std::string& Key, const std::string& Name, CORBA::Any &NewAny);

  long getLong(const std::string & Key, const std::string & Name);
  //calling virtual OnNewData method
  void setLong(const std::string & Key, const std::string & Name, long value);

  std::string getString(const std::string & Key, const std::string & Name);
  //calling virtual OnNewData method
  void setString(const std::string & Key, const std::string & Name, const std::string & value);

  double getDouble(const std::string & Key, const std::string & Name);
  //calling virtual OnNewData method
  void setDouble(const std::string & Key, const std::string & Name, double value);

  CORBA::Boolean getBoolean(const std::string & Key, const std::string & Name);
  //calling virtual OnNewData method
  void setBoolean(const std::string & Key, const std::string & Name, CORBA::Boolean value);

private:
  std::string m_SubKey;
  // moved from public
  void logEvaluated(const std::string& Message, const std::string& Name);
};

#endif /* _INC_CINTFDATAPROVIDER_407BE8E50310_INCLUDED */
