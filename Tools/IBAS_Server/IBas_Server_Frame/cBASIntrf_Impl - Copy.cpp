#include "cbasintrf_impl.h"
#include "IBAS_S.h"
#define _CLOG9
#include "CBS_Utilities\CBS_Clog.h"

#include <map>
#include <string>
// some CBS Includes to make compiler happy (need only cCBS_StdEventSenderTask but that requires more)


#include "cCBS_StdTask.h"
#include "cCBS_EvChannelSender.h"
#include "cCBS_StdEventSenderTask.h"
//#include "iStdEventData_s.h"
#include "cCBS_StdEventSenderTask.h"


#include "cMutex.h"
#include "cStorage.h"
// not necessary for meltshop
//#include "cEvtMaker.h"

#define OK		1
#define ERROR	0


cBASIntrf_Impl::cBASIntrf_Impl(void)
{
  m_storage  = cStorage::instance();
  //m_evtMaker = new cEvtMaker;
}

cBASIntrf_Impl::~cBASIntrf_Impl(void)
{
}



CORBA::Long cBASIntrf_Impl::getFloat(const char* tag, CORBA::Float& val)
{
  cMutex Mutex; 
  long funcVal = ERROR;          // assume failure

  bool WITHOUTEXCEPTION = false;  // i.e. retrieve may throw.
  float retVal;

  if   (m_storage->retrieve  (tag, retVal, WITHOUTEXCEPTION))
  {
    // retrieve was OK
    val=retVal;
    funcVal = OK;
  }
  else
  {
    // retrieve was not OK but no exception. Dont touch user's val variable.
  }

  return funcVal;
}
CORBA::Long cBASIntrf_Impl::getString(const char* tag, CORBA::String_out val)
{
  long funcVal = ERROR;   // assume failure
  cMutex Mutex; 
  bool WITHOUTEXCEPTION=false;  // i.e. retrieve may throw.
  std::string retVal;
  if   (m_storage->retrieve  (tag, retVal, WITHOUTEXCEPTION))
  {
    // retrieve was OK. Caller will take ownership of *val,
    // so we need to invoke string_dup
    val=CORBA::string_dup (retVal.c_str());
    funcVal = OK;
  }
  else
  {
    // retrieve was not OK but no exception. Dont touch user's val variable.
  }

  return funcVal;
}
CORBA::Long cBASIntrf_Impl::getLong(const char* tag, CORBA::Long& val)
{
  long funcVal = ERROR;   // assume failure
  cMutex Mutex; 
  bool WITHOUTEXCEPTION=false;  // i.e. retrieve may throw.
  long retVal;
  if   (m_storage->retrieve  (tag, retVal, WITHOUTEXCEPTION))
  {
    // retrieve was OK
    val=retVal;
    funcVal = OK;
  }
  else
  {
    // retrieve was not OK but no exception. Dont touch user's val variable.
  }

  return funcVal;
}
CORBA::Long cBASIntrf_Impl::getFlag(const char* tag, CORBA::Long& val)
{
  return getLong (tag, val);
}
CORBA::Long cBASIntrf_Impl::setFloat(const char* tag, CORBA::Float val)
{
  cMutex Mutex; 
  m_storage->store(tag,val);
  return OK;
}
CORBA::Long cBASIntrf_Impl::forceFloat(const char* tag, CORBA::Float val)
{
  cMutex Mutex; 
  m_storage->store(tag,val, true, true);
  return OK;
}
CORBA::Long cBASIntrf_Impl::setString(const char* tag, const char* val)
{
  cMutex Mutex; 
  m_storage->store (tag, val);
  return OK;
}
CORBA::Long cBASIntrf_Impl::forceString(const char* tag, const char* val)
{
  cMutex Mutex; 
  m_storage->store (tag, val, true, true);
  return OK;
}
CORBA::Long cBASIntrf_Impl::setLong(const char* tag, CORBA::Long newValue)
{
  cMutex Mutex; 
  long oldValue;
  bool WITHOUTEXCEPTION=true;
  
  // just make sure we dont throw events when tracking prepares a set point
  // (only when setting value with tag "fb.something" 
  //if   (tag[0] == 'f' 
  //  &&  tag[1] == 'b' 
  //  &&  tag[2] == '.' 
  //  && ! m_storage ->isLocked (tag)
  //  &&  m_storage->retrieve  (tag, oldValue, WITHOUTEXCEPTION))
  //    m_evtMaker->checkAndSend (tag, oldValue, newValue);
  m_storage->store (tag, newValue);
  return OK;
}
CORBA::Long cBASIntrf_Impl::forceLong(const char* tag, CORBA::Long newValue)
{
  cMutex Mutex; 
  long oldValue;
  bool WITHOUTEXCEPTION=true;
  
  // just make sure we dont throw events when tracking prepares a set point
  // (only when setting value with tag "fb.something" 

  if   (tag[0] == 'f' 
    &&  tag[1] == 'b' 
    &&  tag[2] == '.' 
    &&  m_storage->retrieve  (tag, oldValue, WITHOUTEXCEPTION))
  {
      //m_evtMaker->checkAndSend (tag, oldValue, newValue);
  }
  m_storage->store (tag, newValue, true, true);
  return OK;
}
CORBA::Long cBASIntrf_Impl::setFlag(const char* tag, CORBA::Long val)
{
  // Flag is just another word for Long...
  return setLong(tag,val);
}
CORBA::Long cBASIntrf_Impl::forceFlag(const char* tag, CORBA::Long val)
{
  // Flag is just another word for Long...
  return forceLong(tag,val);
}
CORBA::Long cBASIntrf_Impl::pulseFlag(const char* tag, CORBA::Long msec)
{
  cMutex Mutex; 
  return OK;
}


CORBA::Boolean cBASIntrf_Impl::setLock  (const char*  tag, CORBA::Boolean value)
{
  return m_storage->setLock  (std::string (tag), value);
}
CORBA::Boolean cBASIntrf_Impl::isLocked (const char*  tag)
{
  return m_storage->isLocked  (std::string (tag));
}

void  cBASIntrf_Impl::clearAllLocks ()
{
  m_storage->setAllLocks (false);
}

CORBA::Boolean cBASIntrf_Impl::getListOfLockedValues (IBAS::seqLocks_out list)
{
  bool retval = false;
  IBAS::seqLocks_var returnList = new IBAS::seqLocks;
  std::vector<std::string>   LockList;

  if   (retval = m_storage->getListOfLockedValues (LockList))
  {
    size_t length = LockList.size();
    returnList->length(static_cast<CORBA::ULong> (length));
    long ii=0;
    for (std::vector<std::string>::iterator it=LockList.begin(); it != LockList.end(); ++it)
    {
      returnList[ii++]   = CORBA::string_dup ((*it).c_str()) ;
    }
  }
  // In any case, even if the sequence is empty, pass back the sequence.
  list = returnList._retn();
  return retval;
}



void cBASIntrf_Impl::setTelegram(const IBAS::seqValues& taggedValues)
{

  cMutex Mutex;    // avoid conflict

  try
  {
    long l = taggedValues.length() ;
    for (long ii=0; ii<l; ii++)
    {
//      std::string tag = taggedValues[ii].Tag;
      const char *ctag = taggedValues[ii].Tag;
      IBAS::u_Data Data = taggedValues[ii].Data;

      switch (Data._d())
      {
      case IBAS::e_kindLong :
        setLong (ctag, Data.LongVal());
        break;
      case IBAS::e_kindFloat :
        setFloat (ctag, static_cast<CORBA::Float>(Data.FloatVal()));
        break;
      case IBAS::e_kindString :
        setString (ctag, Data.StringVal());
        break;
      default:
        break;
      }

    }
    // now send accumulated EC Events.
    //m_evtMaker->sendAccumulatedEvents ();
  }
  catch (...)
  {
  }
}



void cBASIntrf_Impl::getLastResponses(IBAS::seq_IBAS_LastResponses_out IBAS_LastResponses)
{return ;}

void cBASIntrf_Impl::setLastResponse(CORBA::Long telegramID, const char* lastTime)
{return ;}

//omniObjRef* _do_get_interface(){}
