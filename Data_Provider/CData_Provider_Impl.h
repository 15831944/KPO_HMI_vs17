// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CINTFDATAPROVIDERIMPL_40B757780217_INCLUDED
#define _INC_CINTFDATAPROVIDERIMPL_40B757780217_INCLUDED

#include "CData_Provider.h"

#include "iData_Provider_s.hh"


//##ModelId=40B757780217
class CData_Provider_Impl 
: public CData_Provider
, public POA_iData_Provider
{
protected:
  
public:
	//##ModelId=42008DCE011D
	//virtual void EventLogExc(const std::string & Message, const std::string& Function, const std::string& Action);

	//##ModelId=415D8D370338
	virtual seqIntfDataList* getIntfDataList(const char* Key);

  virtual seqIntfDataList* getRequestedIntfDataList(const char* Key);

  virtual std::vector<std::string> getIntfKeyList();

	//##ModelId=4149B5D402B8
	virtual void log(const std::string & Message, long Level) = 0;


	//##ModelId=40BC537A02E9
	virtual CORBA::Boolean getBoolean(const char* Key, const char* Name);

	//##ModelId=40BC539200AA
	virtual void setBoolean(const char* Key, const char* Name, CORBA::Boolean value);

	//##ModelId=40BC433B03A3
	virtual void setDouble(const char* Key, const char* Name, CORBA::Double value);

	//##ModelId=40BC434C0158
	virtual CORBA::Double getDouble(const char* Key, const char* Name);



	//##ModelId=40B757CD02F6
  virtual CORBA::Any* getAny(const char* Key, const char* Name);

	//##ModelId=40B75CE30301
  virtual char* getString(const char* Key, const char* Name);

	//##ModelId=40B75CE30383
  virtual void setString(const char* Key, const char* Name, const char* value);


	//##ModelId=40B757CD0300
  virtual void setAny(const char* Key, const char* Name, const CORBA::Any& NewAny);

	//##ModelId=40B757CD0328
  virtual void setLong(const char* Key, const char* Name, CORBA::Long value);

	//##ModelId=40B757CD0332
  virtual CORBA::Long getLong(const char* Key, const char* Name);
  
	//##ModelId=40B757CD033C
	virtual void indicate(const char* Key);

	//##ModelId=40B757CD0346
	virtual long complete(const char * Key, const char * Action);

	//##ModelId=44FE999B01AF
  virtual char * generateDataKey(const char* Value);

	//##ModelId=45F7DD7C0073
	virtual char * getIntfDataType(const char* Key, const char* Name);

  virtual char * CData_Provider_Impl::getProviderName();
};

#endif /* _INC_CINTFDATAPROVIDERIMPL_40B757780217_INCLUDED */
