// This file is generated by omniidl (C++ backend)- omniORB_4_2. Do not edit.

#include "iProcess_Monitor_s.hh"
#include <omniORB4/IOP_S.h>
#include <omniORB4/IOP_C.h>
#include <omniORB4/callDescriptor.h>
#include <omniORB4/callHandle.h>
#include <omniORB4/objTracker.h>


OMNI_USING_NAMESPACE(omni)

static const char* _0RL_library_version = omniORB_4_2;



#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage othewise.
namespace PM { 
  extern const char * HeatID = "HeatID";
} 
#else
const char * PM::HeatID = "HeatID";
#endif

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage othewise.
namespace PM { 
  extern const char * TreatID = "TreatID";
} 
#else
const char * PM::TreatID = "TreatID";
#endif

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage othewise.
namespace PM { 
  extern const char * CustHeatID = "CustHeatID";
} 
#else
const char * PM::CustHeatID = "CustHeatID";
#endif

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage othewise.
namespace PM { 
  extern const char * CustTreatID = "CustTreatID";
} 
#else
const char * PM::CustTreatID = "CustTreatID";
#endif

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage othewise.
namespace PM { 
  extern const char * OrderId = "OrderId";
} 
#else
const char * PM::OrderId = "OrderId";
#endif

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage othewise.
namespace PM { 
  extern const char * PlantID = "PlantID";
} 
#else
const char * PM::PlantID = "PlantID";
#endif

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage othewise.
namespace PM { 
  extern const char * ActModel = "ActModel";
} 
#else
const char * PM::ActModel = "ActModel";
#endif

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage othewise.
namespace PM { 
  extern const char * Destination = "Destination";
} 
#else
const char * PM::Destination = "Destination";
#endif

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage othewise.
namespace PM { 
  extern const char * Sender = "Sender";
} 
#else
const char * PM::Sender = "Sender";
#endif

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage othewise.
namespace PM { 
  extern const char * PlantUnit = "PlantUnit";
} 
#else
const char * PM::PlantUnit = "PlantUnit";
#endif

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage othewise.
namespace PM { 
  extern const char * PlantNo = "PlantNo";
} 
#else
const char * PM::PlantNo = "PlantNo";
#endif

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage othewise.
namespace PM { 
  extern const char * NotValidValue = "NotAvailable";
} 
#else
const char * PM::NotValidValue = "NotAvailable";
#endif

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage othewise.
namespace PM { 
  extern const char * TelegramName = "TelegramName";
} 
#else
const char * PM::TelegramName = "TelegramName";
#endif

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage othewise.
namespace PM { 
  extern const char * ProductID = "ProductID";
} 
#else
const char * PM::ProductID = "ProductID";
#endif

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage othewise.
namespace PM { 
  extern const char * PlantList = "PlantList";
} 
#else
const char * PM::PlantList = "PlantList";
#endif

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage othewise.
namespace PM { 
  extern const char * Monitor = "Monitor";
} 
#else
const char * PM::Monitor = "Monitor";
#endif

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage othewise.
namespace PM { 
  extern const char * Control = "Control";
} 
#else
const char * PM::Control = "Control";
#endif

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage othewise.
namespace PM { 
  extern const char * ErrorsMax = "ErrorsMax";
} 
#else
const char * PM::ErrorsMax = "ErrorsMax";
#endif

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage othewise.
namespace PM { 
  extern const char * ErrorCount = "ErrorCount";
} 
#else
const char * PM::ErrorCount = "ErrorCount";
#endif

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage othewise.
namespace PM { 
  extern const char * Tracking = "Tracking";
} 
#else
const char * PM::Tracking = "Tracking";
#endif

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage othewise.
namespace PM { 
  extern const char * EventTracking = "EventTracking";
} 
#else
const char * PM::EventTracking = "EventTracking";
#endif

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage othewise.
namespace PM { 
  extern const char * EventIsSent = "EventIsSent";
} 
#else
const char * PM::EventIsSent = "EventIsSent";
#endif

PM::iProcess_Monitor_ptr PM::iProcess_Monitor_Helper::_nil() {
  return ::PM::iProcess_Monitor::_nil();
}

::CORBA::Boolean PM::iProcess_Monitor_Helper::is_nil(::PM::iProcess_Monitor_ptr p) {
  return ::CORBA::is_nil(p);

}

void PM::iProcess_Monitor_Helper::release(::PM::iProcess_Monitor_ptr p) {
  ::CORBA::release(p);
}

void PM::iProcess_Monitor_Helper::marshalObjRef(::PM::iProcess_Monitor_ptr obj, cdrStream& s) {
  ::PM::iProcess_Monitor::_marshalObjRef(obj, s);
}

PM::iProcess_Monitor_ptr PM::iProcess_Monitor_Helper::unmarshalObjRef(cdrStream& s) {
  return ::PM::iProcess_Monitor::_unmarshalObjRef(s);
}

void PM::iProcess_Monitor_Helper::duplicate(::PM::iProcess_Monitor_ptr obj) {
  if (obj && !obj->_NP_is_nil())  omni::duplicateObjRef(obj);
}

PM::iProcess_Monitor_ptr
PM::iProcess_Monitor::_duplicate(::PM::iProcess_Monitor_ptr obj)
{
  if (obj && !obj->_NP_is_nil())  omni::duplicateObjRef(obj);
  return obj;
}

PM::iProcess_Monitor_ptr
PM::iProcess_Monitor::_narrow(::CORBA::Object_ptr obj)
{
  if (!obj || obj->_NP_is_nil() || obj->_NP_is_pseudo()) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_realNarrow(_PD_repoId);
  return e ? e : _nil();
}


PM::iProcess_Monitor_ptr
PM::iProcess_Monitor::_unchecked_narrow(::CORBA::Object_ptr obj)
{
  if (!obj || obj->_NP_is_nil() || obj->_NP_is_pseudo()) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_uncheckedNarrow(_PD_repoId);
  return e ? e : _nil();
}

PM::iProcess_Monitor_ptr
PM::iProcess_Monitor::_nil()
{
#ifdef OMNI_UNLOADABLE_STUBS
  static _objref_iProcess_Monitor _the_nil_obj;
  return &_the_nil_obj;
#else
  static _objref_iProcess_Monitor* _the_nil_ptr = 0;
  if (!_the_nil_ptr) {
    omni::nilRefLock().lock();
    if (!_the_nil_ptr) {
      _the_nil_ptr = new _objref_iProcess_Monitor;
      registerNilCorbaObject(_the_nil_ptr);
    }
    omni::nilRefLock().unlock();
  }
  return _the_nil_ptr;
#endif
}

const char* PM::iProcess_Monitor::_PD_repoId = "IDL:PM/iProcess_Monitor:1.0";


PM::_objref_iProcess_Monitor::~_objref_iProcess_Monitor() {
  
}


PM::_objref_iProcess_Monitor::_objref_iProcess_Monitor(omniIOR* ior, omniIdentity* id) :
   omniObjRef(::PM::iProcess_Monitor::_PD_repoId, ior, id, 1),
   _objref_iData_Provider(ior, id)
   
{
  _PR_setobj(this);
}

void*
PM::_objref_iProcess_Monitor::_ptrToObjRef(const char* id)
{
  if (id == ::PM::iProcess_Monitor::_PD_repoId)
    return (::PM::iProcess_Monitor_ptr) this;
  if (id == ::iData_Provider::_PD_repoId)
    return (::iData_Provider_ptr) this;


  if (id == ::CORBA::Object::_PD_repoId)
    return (::CORBA::Object_ptr) this;

  if (omni::strMatch(id, ::PM::iProcess_Monitor::_PD_repoId))
    return (::PM::iProcess_Monitor_ptr) this;
  if (omni::strMatch(id, ::iData_Provider::_PD_repoId))
    return (::iData_Provider_ptr) this;


  if (omni::strMatch(id, ::CORBA::Object::_PD_repoId))
    return (::CORBA::Object_ptr) this;

  return 0;
}

PM::_pof_iProcess_Monitor::~_pof_iProcess_Monitor() {}


omniObjRef*
PM::_pof_iProcess_Monitor::newObjRef(omniIOR* ior, omniIdentity* id)
{
  return new ::PM::_objref_iProcess_Monitor(ior, id);
}


::CORBA::Boolean
PM::_pof_iProcess_Monitor::is_a(const char* id) const
{
  if (omni::ptrStrMatch(id, ::PM::iProcess_Monitor::_PD_repoId))
    return 1;
  if (omni::ptrStrMatch(id, iData_Provider::_PD_repoId))
    return 1;


  return 0;
}

const PM::_pof_iProcess_Monitor _the_pof_PM_miProcess__Monitor;

PM::_impl_iProcess_Monitor::~_impl_iProcess_Monitor() {}


::CORBA::Boolean
PM::_impl_iProcess_Monitor::_dispatch(omniCallHandle& _handle)
{
  

  
#ifndef _MSC_VER
  if (_impl_iData_Provider::_dispatch(_handle)) {
    return 1;
  }
#else
  // Work-around for incorrect MSVC code generation.
  if (((_impl_iData_Provider*)this)->
      _impl_iData_Provider::_dispatch(_handle)) {
    return 1;
  }
#endif


  return 0;
}

void*
PM::_impl_iProcess_Monitor::_ptrToInterface(const char* id)
{
  if (id == ::PM::iProcess_Monitor::_PD_repoId)
    return (::PM::_impl_iProcess_Monitor*) this;
  if (id == ::iData_Provider::_PD_repoId)
    return (::_impl_iData_Provider*) this;


  if (id == ::CORBA::Object::_PD_repoId)
    return (void*) 1;

  if (omni::strMatch(id, ::PM::iProcess_Monitor::_PD_repoId))
    return (::PM::_impl_iProcess_Monitor*) this;
  if (omni::strMatch(id, ::iData_Provider::_PD_repoId))
    return (::_impl_iData_Provider*) this;


  if (omni::strMatch(id, ::CORBA::Object::_PD_repoId))
    return (void*) 1;
  return 0;
}

const char*
PM::_impl_iProcess_Monitor::_mostDerivedRepoId()
{
  return ::PM::iProcess_Monitor::_PD_repoId;
}

POA_PM::iProcess_Monitor::~iProcess_Monitor() {}

