#ifndef CBASINTRF_IMPL_H
#define CBASINTRF_IMPL_H

// #include "BASIntrf_s.h"
#pragma warning (disable: 4311 4312 4267)
#include "IBAS_S.h"
#pragma warning (default: 4311 4312 4267)

class cStorage;
class cEvtMaker;

class cBASIntrf_Impl : public POA_IBAS::IBASIntrf
{
public:
  cBASIntrf_Impl(void);
  ~cBASIntrf_Impl(void);

  virtual CORBA::Long getFloat(const char* tag, CORBA::Float& val);
  virtual CORBA::Long getString(const char* tag, CORBA::String_out val);
  virtual CORBA::Long getLong(const char* tag, CORBA::Long& val);
  virtual CORBA::Long getFlag(const char* tag, CORBA::Long& val);
  virtual CORBA::Long setFloat(const char* tag, CORBA::Float val);
  virtual CORBA::Long setString(const char* tag, const char* val);
  virtual CORBA::Long setLong(const char* tag, CORBA::Long val);
  virtual CORBA::Long setFlag(const char* tag, CORBA::Long val);

  virtual CORBA::Long forceFloat(const char* tag, CORBA::Float val);
  virtual CORBA::Long forceString(const char* tag, const char* val);
  virtual CORBA::Long forceLong(const char* tag, CORBA::Long val);
  virtual CORBA::Long forceFlag(const char* tag, CORBA::Long val);

  virtual CORBA::Boolean setLock  (const char*  tag, CORBA::Boolean value);
  virtual CORBA::Boolean isLocked (const char*  tag);
  virtual   void         clearAllLocks ();
  virtual CORBA::Boolean  getListOfLockedValues (IBAS::seqLocks_out list);

  // no setAllLocks, that really makes no sense.

  virtual CORBA::Long pulseFlag(const char* tag, CORBA::Long msec);

  virtual void getLastResponses(IBAS::seq_IBAS_LastResponses_out IBAS_LastResponses) ;

  void setLastResponse(CORBA::Long telegramID, const char* lastTime);

  virtual void setTelegram(const IBAS::seqValues & taggedValues);

  // virtual omniObjRef* _do_get_interface();

protected:
  cStorage   *m_storage;
  cEvtMaker  *m_evtMaker;
};



#endif
