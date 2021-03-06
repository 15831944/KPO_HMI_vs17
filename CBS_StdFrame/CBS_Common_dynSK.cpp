// This file is generated by omniidl (C++ backend) - omniORB_4_2. Do not edit.

#include "CBS_Common_s.hh"

OMNI_USING_NAMESPACE(omni)

static const char* _0RL_dyn_library_version = omniORB_4_2_dyn;

static ::CORBA::TypeCode::_Tracker _0RL_tcTrack(__FILE__);

static CORBA::TypeCode_ptr _0RL_tc_CBS__OctetSequence = CORBA::TypeCode::PR_alias_tc("IDL:CBS_OctetSequence:1.0", "CBS_OctetSequence", CORBA::TypeCode::PR_sequence_tc(0, CORBA::TypeCode::PR_octet_tc(), &_0RL_tcTrack), &_0RL_tcTrack);


const CORBA::TypeCode_ptr _tc_CBS_OctetSequence = _0RL_tc_CBS__OctetSequence;

static CORBA::TypeCode_ptr _0RL_tc_CBS__StringSequence = CORBA::TypeCode::PR_alias_tc("IDL:CBS_StringSequence:1.0", "CBS_StringSequence", CORBA::TypeCode::PR_sequence_tc(0, CORBA::TypeCode::PR_string_tc(0, &_0RL_tcTrack), &_0RL_tcTrack), &_0RL_tcTrack);


const CORBA::TypeCode_ptr _tc_CBS_StringSequence = _0RL_tc_CBS__StringSequence;

static CORBA::TypeCode_ptr _0RL_tc_CBS__AnySeq = CORBA::TypeCode::PR_alias_tc("IDL:CBS_AnySeq:1.0", "CBS_AnySeq", CORBA::TypeCode::PR_sequence_tc(0, CORBA::TypeCode::PR_any_tc(), &_0RL_tcTrack), &_0RL_tcTrack);


const CORBA::TypeCode_ptr _tc_CBS_AnySeq = _0RL_tc_CBS__AnySeq;

const CORBA::TypeCode_ptr _tc_iCBS_OctetTransfer = CORBA::TypeCode::PR_interface_tc("IDL:iCBS_OctetTransfer:1.0", "iCBS_OctetTransfer", &_0RL_tcTrack);

static CORBA::PR_structMember _0RL_structmember_MCBS_mCBS__LocalTime[] = {
  {"year", CORBA::TypeCode::PR_ushort_tc()},
  {"month", CORBA::TypeCode::PR_ushort_tc()},
  {"day", CORBA::TypeCode::PR_ushort_tc()},
  {"hour", CORBA::TypeCode::PR_ushort_tc()},
  {"minute", CORBA::TypeCode::PR_ushort_tc()},
  {"second", CORBA::TypeCode::PR_ushort_tc()},
  {"msec", CORBA::TypeCode::PR_ushort_tc()},
  {"dstFlag", CORBA::TypeCode::PR_boolean_tc()}
};

#ifdef _0RL_tc_MCBS_mCBS__LocalTime
#  undef _0RL_tc_MCBS_mCBS__LocalTime
#endif
static CORBA::TypeCode_ptr _0RL_tc_MCBS_mCBS__LocalTime = CORBA::TypeCode::PR_struct_tc("IDL:MCBS/CBS_LocalTime:1.0", "CBS_LocalTime", _0RL_structmember_MCBS_mCBS__LocalTime, 8, &_0RL_tcTrack);

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace MCBS { 
  const ::CORBA::TypeCode_ptr _tc_CBS_LocalTime = _0RL_tc_MCBS_mCBS__LocalTime;
} 
#else
const ::CORBA::TypeCode_ptr MCBS::_tc_CBS_LocalTime = _0RL_tc_MCBS_mCBS__LocalTime;
#endif


static void _0RL_CBS__OctetSequence_marshal_fn(cdrStream& _s, void* _v)
{
  CBS_OctetSequence* _p = (CBS_OctetSequence*)_v;
  *_p >>= _s;
}
static void _0RL_CBS__OctetSequence_unmarshal_fn(cdrStream& _s, void*& _v)
{
  CBS_OctetSequence* _p = new CBS_OctetSequence;
  *_p <<= _s;
  _v = _p;
}
static void _0RL_CBS__OctetSequence_destructor_fn(void* _v)
{
  CBS_OctetSequence* _p = (CBS_OctetSequence*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const CBS_OctetSequence& _s)
{
  CBS_OctetSequence* _p = new CBS_OctetSequence(_s);
  _a.PR_insert(_0RL_tc_CBS__OctetSequence,
               _0RL_CBS__OctetSequence_marshal_fn,
               _0RL_CBS__OctetSequence_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, CBS_OctetSequence* _sp)
{
  _a.PR_insert(_0RL_tc_CBS__OctetSequence,
               _0RL_CBS__OctetSequence_marshal_fn,
               _0RL_CBS__OctetSequence_destructor_fn,
               _sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, CBS_OctetSequence*& _sp)
{
  return _a >>= (const CBS_OctetSequence*&) _sp;
}
::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const CBS_OctetSequence*& _sp)
{
  void* _v;
  if (_a.PR_extract(_0RL_tc_CBS__OctetSequence,
                    _0RL_CBS__OctetSequence_unmarshal_fn,
                    _0RL_CBS__OctetSequence_marshal_fn,
                    _0RL_CBS__OctetSequence_destructor_fn,
                    _v)) {
    _sp = (const CBS_OctetSequence*)_v;
    return 1;
  }
  return 0;
}

static void _0RL_CBS__StringSequence_marshal_fn(cdrStream& _s, void* _v)
{
  CBS_StringSequence* _p = (CBS_StringSequence*)_v;
  *_p >>= _s;
}
static void _0RL_CBS__StringSequence_unmarshal_fn(cdrStream& _s, void*& _v)
{
  CBS_StringSequence* _p = new CBS_StringSequence;
  *_p <<= _s;
  _v = _p;
}
static void _0RL_CBS__StringSequence_destructor_fn(void* _v)
{
  CBS_StringSequence* _p = (CBS_StringSequence*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const CBS_StringSequence& _s)
{
  CBS_StringSequence* _p = new CBS_StringSequence(_s);
  _a.PR_insert(_0RL_tc_CBS__StringSequence,
               _0RL_CBS__StringSequence_marshal_fn,
               _0RL_CBS__StringSequence_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, CBS_StringSequence* _sp)
{
  _a.PR_insert(_0RL_tc_CBS__StringSequence,
               _0RL_CBS__StringSequence_marshal_fn,
               _0RL_CBS__StringSequence_destructor_fn,
               _sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, CBS_StringSequence*& _sp)
{
  return _a >>= (const CBS_StringSequence*&) _sp;
}
::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const CBS_StringSequence*& _sp)
{
  void* _v;
  if (_a.PR_extract(_0RL_tc_CBS__StringSequence,
                    _0RL_CBS__StringSequence_unmarshal_fn,
                    _0RL_CBS__StringSequence_marshal_fn,
                    _0RL_CBS__StringSequence_destructor_fn,
                    _v)) {
    _sp = (const CBS_StringSequence*)_v;
    return 1;
  }
  return 0;
}

static void _0RL_CBS__AnySeq_marshal_fn(cdrStream& _s, void* _v)
{
  CBS_AnySeq* _p = (CBS_AnySeq*)_v;
  *_p >>= _s;
}
static void _0RL_CBS__AnySeq_unmarshal_fn(cdrStream& _s, void*& _v)
{
  CBS_AnySeq* _p = new CBS_AnySeq;
  *_p <<= _s;
  _v = _p;
}
static void _0RL_CBS__AnySeq_destructor_fn(void* _v)
{
  CBS_AnySeq* _p = (CBS_AnySeq*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const CBS_AnySeq& _s)
{
  CBS_AnySeq* _p = new CBS_AnySeq(_s);
  _a.PR_insert(_0RL_tc_CBS__AnySeq,
               _0RL_CBS__AnySeq_marshal_fn,
               _0RL_CBS__AnySeq_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, CBS_AnySeq* _sp)
{
  _a.PR_insert(_0RL_tc_CBS__AnySeq,
               _0RL_CBS__AnySeq_marshal_fn,
               _0RL_CBS__AnySeq_destructor_fn,
               _sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, CBS_AnySeq*& _sp)
{
  return _a >>= (const CBS_AnySeq*&) _sp;
}
::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const CBS_AnySeq*& _sp)
{
  void* _v;
  if (_a.PR_extract(_0RL_tc_CBS__AnySeq,
                    _0RL_CBS__AnySeq_unmarshal_fn,
                    _0RL_CBS__AnySeq_marshal_fn,
                    _0RL_CBS__AnySeq_destructor_fn,
                    _v)) {
    _sp = (const CBS_AnySeq*)_v;
    return 1;
  }
  return 0;
}

static void _0RL_iCBS__OctetTransfer_marshal_fn(cdrStream& _s, void* _v)
{
  omniObjRef* _o = (omniObjRef*)_v;
  omniObjRef::_marshal(_o, _s);
}
static void _0RL_iCBS__OctetTransfer_unmarshal_fn(cdrStream& _s, void*& _v)
{
  omniObjRef* _o = omniObjRef::_unMarshal(iCBS_OctetTransfer::_PD_repoId, _s);
  _v = _o;
}
static void _0RL_iCBS__OctetTransfer_destructor_fn(void* _v)
{
  omniObjRef* _o = (omniObjRef*)_v;
  if (_o)
    omni::releaseObjRef(_o);
}

void operator<<=(::CORBA::Any& _a, iCBS_OctetTransfer_ptr _o)
{
  iCBS_OctetTransfer_ptr _no = iCBS_OctetTransfer::_duplicate(_o);
  _a.PR_insert(_tc_iCBS_OctetTransfer,
               _0RL_iCBS__OctetTransfer_marshal_fn,
               _0RL_iCBS__OctetTransfer_destructor_fn,
               _no->_PR_getobj());
}
void operator<<=(::CORBA::Any& _a, iCBS_OctetTransfer_ptr* _op)
{
  _a.PR_insert(_tc_iCBS_OctetTransfer,
               _0RL_iCBS__OctetTransfer_marshal_fn,
               _0RL_iCBS__OctetTransfer_destructor_fn,
               (*_op)->_PR_getobj());
  *_op = iCBS_OctetTransfer::_nil();
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, iCBS_OctetTransfer_ptr& _o)
{
  void* _v;
  if (_a.PR_extract(_tc_iCBS_OctetTransfer,
                    _0RL_iCBS__OctetTransfer_unmarshal_fn,
                    _0RL_iCBS__OctetTransfer_marshal_fn,
                    _0RL_iCBS__OctetTransfer_destructor_fn,
                    _v)) {
    omniObjRef* _r = (omniObjRef*)_v;
    if (_r)
      _o = (iCBS_OctetTransfer_ptr)_r->_ptrToObjRef(iCBS_OctetTransfer::_PD_repoId);
    else
      _o = iCBS_OctetTransfer::_nil();
    return 1;
  }
  return 0;
}

static void _0RL_MCBS_mCBS__LocalTime_marshal_fn(cdrStream& _s, void* _v)
{
  MCBS::CBS_LocalTime* _p = (MCBS::CBS_LocalTime*)_v;
  *_p >>= _s;
}
static void _0RL_MCBS_mCBS__LocalTime_unmarshal_fn(cdrStream& _s, void*& _v)
{
  MCBS::CBS_LocalTime* _p = new MCBS::CBS_LocalTime;
  *_p <<= _s;
  _v = _p;
}
static void _0RL_MCBS_mCBS__LocalTime_destructor_fn(void* _v)
{
  MCBS::CBS_LocalTime* _p = (MCBS::CBS_LocalTime*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const MCBS::CBS_LocalTime& _s)
{
  MCBS::CBS_LocalTime* _p = new MCBS::CBS_LocalTime(_s);
  _a.PR_insert(_0RL_tc_MCBS_mCBS__LocalTime,
               _0RL_MCBS_mCBS__LocalTime_marshal_fn,
               _0RL_MCBS_mCBS__LocalTime_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, MCBS::CBS_LocalTime* _sp)
{
  _a.PR_insert(_0RL_tc_MCBS_mCBS__LocalTime,
               _0RL_MCBS_mCBS__LocalTime_marshal_fn,
               _0RL_MCBS_mCBS__LocalTime_destructor_fn,
               _sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, MCBS::CBS_LocalTime*& _sp)
{
  return _a >>= (const MCBS::CBS_LocalTime*&) _sp;
}
::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const MCBS::CBS_LocalTime*& _sp)
{
  void* _v;
  if (_a.PR_extract(_0RL_tc_MCBS_mCBS__LocalTime,
                    _0RL_MCBS_mCBS__LocalTime_unmarshal_fn,
                    _0RL_MCBS_mCBS__LocalTime_marshal_fn,
                    _0RL_MCBS_mCBS__LocalTime_destructor_fn,
                    _v)) {
    _sp = (const MCBS::CBS_LocalTime*)_v;
    return 1;
  }
  return 0;
}

