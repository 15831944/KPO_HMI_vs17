// This file is generated by omniidl (C++ backend) - omniORB_4_2. Do not edit.

#include "BASIntrf_s.h"

OMNI_USING_NAMESPACE(omni)

static const char* _0RL_dyn_library_version = omniORB_4_2_dyn;

static ::CORBA::TypeCode::_Tracker _0RL_tcTrack(__FILE__);

static CORBA::PR_structMember _0RL_structmember_IBAS_mIBAS__LastResponse[] = {
  {"intName", CORBA::TypeCode::PR_string_tc(0, &_0RL_tcTrack)},
  {"lastTime", CORBA::TypeCode::PR_string_tc(0, &_0RL_tcTrack)},
  {"status", CORBA::TypeCode::PR_boolean_tc()}
};

#ifdef _0RL_tc_IBAS_mIBAS__LastResponse
#  undef _0RL_tc_IBAS_mIBAS__LastResponse
#endif
static CORBA::TypeCode_ptr _0RL_tc_IBAS_mIBAS__LastResponse = CORBA::TypeCode::PR_struct_tc("IDL:IBAS/IBAS_LastResponse:1.0", "IBAS_LastResponse", _0RL_structmember_IBAS_mIBAS__LastResponse, 3, &_0RL_tcTrack);

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace IBAS { 
  const ::CORBA::TypeCode_ptr _tc_IBAS_LastResponse = _0RL_tc_IBAS_mIBAS__LastResponse;
} 
#else
const ::CORBA::TypeCode_ptr IBAS::_tc_IBAS_LastResponse = _0RL_tc_IBAS_mIBAS__LastResponse;
#endif






static CORBA::TypeCode_ptr _0RL_tc_IBAS_mseq__IBAS__LastResponses = CORBA::TypeCode::PR_alias_tc("IDL:IBAS/seq_IBAS_LastResponses:1.0", "seq_IBAS_LastResponses", CORBA::TypeCode::PR_sequence_tc(0, _0RL_tc_IBAS_mIBAS__LastResponse, &_0RL_tcTrack), &_0RL_tcTrack);


#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace IBAS { 
  const ::CORBA::TypeCode_ptr _tc_seq_IBAS_LastResponses = _0RL_tc_IBAS_mseq__IBAS__LastResponses;
} 
#else
const ::CORBA::TypeCode_ptr IBAS::_tc_seq_IBAS_LastResponses = _0RL_tc_IBAS_mseq__IBAS__LastResponses;
#endif


static CORBA::TypeCode_ptr _0RL_tc_IBAS_mEXC__TagNotFound = CORBA::TypeCode::PR_exception_tc("IDL:IBAS/EXC_TagNotFound:1.0", "EXC_TagNotFound", (CORBA::PR_structMember*) 0, 0, &_0RL_tcTrack);
#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace IBAS { 
  const ::CORBA::TypeCode_ptr _tc_EXC_TagNotFound = _0RL_tc_IBAS_mEXC__TagNotFound;
} 
#else
const ::CORBA::TypeCode_ptr IBAS::_tc_EXC_TagNotFound = _0RL_tc_IBAS_mEXC__TagNotFound;
#endif



static CORBA::TypeCode_ptr _0RL_tc_IBAS_mEXC__IncorrectTagType = CORBA::TypeCode::PR_exception_tc("IDL:IBAS/EXC_IncorrectTagType:1.0", "EXC_IncorrectTagType", (CORBA::PR_structMember*) 0, 0, &_0RL_tcTrack);
#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace IBAS { 
  const ::CORBA::TypeCode_ptr _tc_EXC_IncorrectTagType = _0RL_tc_IBAS_mEXC__IncorrectTagType;
} 
#else
const ::CORBA::TypeCode_ptr IBAS::_tc_EXC_IncorrectTagType = _0RL_tc_IBAS_mEXC__IncorrectTagType;
#endif


#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace IBAS { 
  const ::CORBA::TypeCode_ptr _tc_BASIntrf = CORBA::TypeCode::PR_interface_tc("IDL:IBAS/BASIntrf:1.0", "BASIntrf", &_0RL_tcTrack);
} 
#else
const ::CORBA::TypeCode_ptr IBAS::_tc_BASIntrf = CORBA::TypeCode::PR_interface_tc("IDL:IBAS/BASIntrf:1.0", "BASIntrf", &_0RL_tcTrack);
#endif

static void _0RL_IBAS_mIBAS__LastResponse_marshal_fn(cdrStream& _s, void* _v)
{
  IBAS::IBAS_LastResponse* _p = (IBAS::IBAS_LastResponse*)_v;
  *_p >>= _s;
}
static void _0RL_IBAS_mIBAS__LastResponse_unmarshal_fn(cdrStream& _s, void*& _v)
{
  IBAS::IBAS_LastResponse* _p = new IBAS::IBAS_LastResponse;
  *_p <<= _s;
  _v = _p;
}
static void _0RL_IBAS_mIBAS__LastResponse_destructor_fn(void* _v)
{
  IBAS::IBAS_LastResponse* _p = (IBAS::IBAS_LastResponse*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const IBAS::IBAS_LastResponse& _s)
{
  IBAS::IBAS_LastResponse* _p = new IBAS::IBAS_LastResponse(_s);
  _a.PR_insert(_0RL_tc_IBAS_mIBAS__LastResponse,
               _0RL_IBAS_mIBAS__LastResponse_marshal_fn,
               _0RL_IBAS_mIBAS__LastResponse_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, IBAS::IBAS_LastResponse* _sp)
{
  _a.PR_insert(_0RL_tc_IBAS_mIBAS__LastResponse,
               _0RL_IBAS_mIBAS__LastResponse_marshal_fn,
               _0RL_IBAS_mIBAS__LastResponse_destructor_fn,
               _sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, IBAS::IBAS_LastResponse*& _sp)
{
  return _a >>= (const IBAS::IBAS_LastResponse*&) _sp;
}
::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const IBAS::IBAS_LastResponse*& _sp)
{
  void* _v;
  if (_a.PR_extract(_0RL_tc_IBAS_mIBAS__LastResponse,
                    _0RL_IBAS_mIBAS__LastResponse_unmarshal_fn,
                    _0RL_IBAS_mIBAS__LastResponse_marshal_fn,
                    _0RL_IBAS_mIBAS__LastResponse_destructor_fn,
                    _v)) {
    _sp = (const IBAS::IBAS_LastResponse*)_v;
    return 1;
  }
  return 0;
}

static void _0RL_IBAS_mseq__IBAS__LastResponses_marshal_fn(cdrStream& _s, void* _v)
{
  IBAS::seq_IBAS_LastResponses* _p = (IBAS::seq_IBAS_LastResponses*)_v;
  *_p >>= _s;
}
static void _0RL_IBAS_mseq__IBAS__LastResponses_unmarshal_fn(cdrStream& _s, void*& _v)
{
  IBAS::seq_IBAS_LastResponses* _p = new IBAS::seq_IBAS_LastResponses;
  *_p <<= _s;
  _v = _p;
}
static void _0RL_IBAS_mseq__IBAS__LastResponses_destructor_fn(void* _v)
{
  IBAS::seq_IBAS_LastResponses* _p = (IBAS::seq_IBAS_LastResponses*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const IBAS::seq_IBAS_LastResponses& _s)
{
  IBAS::seq_IBAS_LastResponses* _p = new IBAS::seq_IBAS_LastResponses(_s);
  _a.PR_insert(_0RL_tc_IBAS_mseq__IBAS__LastResponses,
               _0RL_IBAS_mseq__IBAS__LastResponses_marshal_fn,
               _0RL_IBAS_mseq__IBAS__LastResponses_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, IBAS::seq_IBAS_LastResponses* _sp)
{
  _a.PR_insert(_0RL_tc_IBAS_mseq__IBAS__LastResponses,
               _0RL_IBAS_mseq__IBAS__LastResponses_marshal_fn,
               _0RL_IBAS_mseq__IBAS__LastResponses_destructor_fn,
               _sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, IBAS::seq_IBAS_LastResponses*& _sp)
{
  return _a >>= (const IBAS::seq_IBAS_LastResponses*&) _sp;
}
::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const IBAS::seq_IBAS_LastResponses*& _sp)
{
  void* _v;
  if (_a.PR_extract(_0RL_tc_IBAS_mseq__IBAS__LastResponses,
                    _0RL_IBAS_mseq__IBAS__LastResponses_unmarshal_fn,
                    _0RL_IBAS_mseq__IBAS__LastResponses_marshal_fn,
                    _0RL_IBAS_mseq__IBAS__LastResponses_destructor_fn,
                    _v)) {
    _sp = (const IBAS::seq_IBAS_LastResponses*)_v;
    return 1;
  }
  return 0;
}


static void _0RL_IBAS_mEXC__TagNotFound_marshal_fn(cdrStream& _s, void* _v)
{
  const IBAS::EXC_TagNotFound* _p = (const IBAS::EXC_TagNotFound*)_v;
  *_p >>= _s;
}
static void _0RL_IBAS_mEXC__TagNotFound_unmarshal_fn(cdrStream& _s, void*& _v)
{
  IBAS::EXC_TagNotFound* _p = new IBAS::EXC_TagNotFound;
  *_p <<= _s;
  _v = _p;
}
static void _0RL_IBAS_mEXC__TagNotFound_destructor_fn(void* _v)
{
  IBAS::EXC_TagNotFound* _p = (IBAS::EXC_TagNotFound*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const IBAS::EXC_TagNotFound& _s)
{
  IBAS::EXC_TagNotFound* _p = new IBAS::EXC_TagNotFound(_s);
  _a.PR_insert(_0RL_tc_IBAS_mEXC__TagNotFound,
               _0RL_IBAS_mEXC__TagNotFound_marshal_fn,
               _0RL_IBAS_mEXC__TagNotFound_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, const IBAS::EXC_TagNotFound* _sp)
{
  _a.PR_insert(_0RL_tc_IBAS_mEXC__TagNotFound,
               _0RL_IBAS_mEXC__TagNotFound_marshal_fn,
               _0RL_IBAS_mEXC__TagNotFound_destructor_fn,
               (IBAS::EXC_TagNotFound*)_sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const IBAS::EXC_TagNotFound*& _sp)
{
  void* _v;
  if (_a.PR_extract(_0RL_tc_IBAS_mEXC__TagNotFound,
                    _0RL_IBAS_mEXC__TagNotFound_unmarshal_fn,
                    _0RL_IBAS_mEXC__TagNotFound_marshal_fn,
                    _0RL_IBAS_mEXC__TagNotFound_destructor_fn,
                    _v)) {
    _sp = (const IBAS::EXC_TagNotFound*)_v;
    return 1;
  }
  return 0;
}

static void _0RL_insertToAny__cIBAS_mEXC__TagNotFound(::CORBA::Any& _a, const ::CORBA::Exception& _e) {
  const IBAS::EXC_TagNotFound & _ex = (const IBAS::EXC_TagNotFound &) _e;
  operator<<=(_a,_ex);
}

static void _0RL_insertToAnyNCP__cIBAS_mEXC__TagNotFound (::CORBA::Any& _a, const ::CORBA::Exception* _e) {
  const IBAS::EXC_TagNotFound* _ex = (const IBAS::EXC_TagNotFound*) _e;
  operator<<=(_a,_ex);
}

class _0RL_insertToAny_Singleton__cIBAS_mEXC__TagNotFound {
public:
  _0RL_insertToAny_Singleton__cIBAS_mEXC__TagNotFound() {
    IBAS::EXC_TagNotFound::insertToAnyFn = _0RL_insertToAny__cIBAS_mEXC__TagNotFound;
    IBAS::EXC_TagNotFound::insertToAnyFnNCP = _0RL_insertToAnyNCP__cIBAS_mEXC__TagNotFound;
  }
};
static _0RL_insertToAny_Singleton__cIBAS_mEXC__TagNotFound _0RL_insertToAny_Singleton__cIBAS_mEXC__TagNotFound_;


static void _0RL_IBAS_mEXC__IncorrectTagType_marshal_fn(cdrStream& _s, void* _v)
{
  const IBAS::EXC_IncorrectTagType* _p = (const IBAS::EXC_IncorrectTagType*)_v;
  *_p >>= _s;
}
static void _0RL_IBAS_mEXC__IncorrectTagType_unmarshal_fn(cdrStream& _s, void*& _v)
{
  IBAS::EXC_IncorrectTagType* _p = new IBAS::EXC_IncorrectTagType;
  *_p <<= _s;
  _v = _p;
}
static void _0RL_IBAS_mEXC__IncorrectTagType_destructor_fn(void* _v)
{
  IBAS::EXC_IncorrectTagType* _p = (IBAS::EXC_IncorrectTagType*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const IBAS::EXC_IncorrectTagType& _s)
{
  IBAS::EXC_IncorrectTagType* _p = new IBAS::EXC_IncorrectTagType(_s);
  _a.PR_insert(_0RL_tc_IBAS_mEXC__IncorrectTagType,
               _0RL_IBAS_mEXC__IncorrectTagType_marshal_fn,
               _0RL_IBAS_mEXC__IncorrectTagType_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, const IBAS::EXC_IncorrectTagType* _sp)
{
  _a.PR_insert(_0RL_tc_IBAS_mEXC__IncorrectTagType,
               _0RL_IBAS_mEXC__IncorrectTagType_marshal_fn,
               _0RL_IBAS_mEXC__IncorrectTagType_destructor_fn,
               (IBAS::EXC_IncorrectTagType*)_sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const IBAS::EXC_IncorrectTagType*& _sp)
{
  void* _v;
  if (_a.PR_extract(_0RL_tc_IBAS_mEXC__IncorrectTagType,
                    _0RL_IBAS_mEXC__IncorrectTagType_unmarshal_fn,
                    _0RL_IBAS_mEXC__IncorrectTagType_marshal_fn,
                    _0RL_IBAS_mEXC__IncorrectTagType_destructor_fn,
                    _v)) {
    _sp = (const IBAS::EXC_IncorrectTagType*)_v;
    return 1;
  }
  return 0;
}

static void _0RL_insertToAny__cIBAS_mEXC__IncorrectTagType(::CORBA::Any& _a, const ::CORBA::Exception& _e) {
  const IBAS::EXC_IncorrectTagType & _ex = (const IBAS::EXC_IncorrectTagType &) _e;
  operator<<=(_a,_ex);
}

static void _0RL_insertToAnyNCP__cIBAS_mEXC__IncorrectTagType (::CORBA::Any& _a, const ::CORBA::Exception* _e) {
  const IBAS::EXC_IncorrectTagType* _ex = (const IBAS::EXC_IncorrectTagType*) _e;
  operator<<=(_a,_ex);
}

class _0RL_insertToAny_Singleton__cIBAS_mEXC__IncorrectTagType {
public:
  _0RL_insertToAny_Singleton__cIBAS_mEXC__IncorrectTagType() {
    IBAS::EXC_IncorrectTagType::insertToAnyFn = _0RL_insertToAny__cIBAS_mEXC__IncorrectTagType;
    IBAS::EXC_IncorrectTagType::insertToAnyFnNCP = _0RL_insertToAnyNCP__cIBAS_mEXC__IncorrectTagType;
  }
};
static _0RL_insertToAny_Singleton__cIBAS_mEXC__IncorrectTagType _0RL_insertToAny_Singleton__cIBAS_mEXC__IncorrectTagType_;

static void _0RL_IBAS_mBASIntrf_marshal_fn(cdrStream& _s, void* _v)
{
  omniObjRef* _o = (omniObjRef*)_v;
  omniObjRef::_marshal(_o, _s);
}
static void _0RL_IBAS_mBASIntrf_unmarshal_fn(cdrStream& _s, void*& _v)
{
  omniObjRef* _o = omniObjRef::_unMarshal(IBAS::BASIntrf::_PD_repoId, _s);
  _v = _o;
}
static void _0RL_IBAS_mBASIntrf_destructor_fn(void* _v)
{
  omniObjRef* _o = (omniObjRef*)_v;
  if (_o)
    omni::releaseObjRef(_o);
}

void operator<<=(::CORBA::Any& _a, IBAS::BASIntrf_ptr _o)
{
  IBAS::BASIntrf_ptr _no = IBAS::BASIntrf::_duplicate(_o);
  _a.PR_insert(IBAS::_tc_BASIntrf,
               _0RL_IBAS_mBASIntrf_marshal_fn,
               _0RL_IBAS_mBASIntrf_destructor_fn,
               _no->_PR_getobj());
}
void operator<<=(::CORBA::Any& _a, IBAS::BASIntrf_ptr* _op)
{
  _a.PR_insert(IBAS::_tc_BASIntrf,
               _0RL_IBAS_mBASIntrf_marshal_fn,
               _0RL_IBAS_mBASIntrf_destructor_fn,
               (*_op)->_PR_getobj());
  *_op = IBAS::BASIntrf::_nil();
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, IBAS::BASIntrf_ptr& _o)
{
  void* _v;
  if (_a.PR_extract(IBAS::_tc_BASIntrf,
                    _0RL_IBAS_mBASIntrf_unmarshal_fn,
                    _0RL_IBAS_mBASIntrf_marshal_fn,
                    _0RL_IBAS_mBASIntrf_destructor_fn,
                    _v)) {
    omniObjRef* _r = (omniObjRef*)_v;
    if (_r)
      _o = (IBAS::BASIntrf_ptr)_r->_ptrToObjRef(IBAS::BASIntrf::_PD_repoId);
    else
      _o = IBAS::BASIntrf::_nil();
    return 1;
  }
  return 0;
}
