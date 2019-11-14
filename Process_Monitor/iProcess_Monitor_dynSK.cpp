// This file is generated by omniidl (C++ backend) - omniORB_4_2. Do not edit.

#include "iProcess_Monitor_s.hh"

OMNI_USING_NAMESPACE(omni)

static const char* _0RL_dyn_library_version = omniORB_4_2_dyn;

static ::CORBA::TypeCode::_Tracker _0RL_tcTrack(__FILE__);

static const char* _0RL_enumMember_PM_mLOG__[] = { "NOTHING", "ERROR_LEVEL", "WARNING_LEVEL", "INFO_LEVEL", "ELSE_LEVEL" };
static CORBA::TypeCode_ptr _0RL_tc_PM_mLOG__ = CORBA::TypeCode::PR_enum_tc("IDL:PM/LOG_:1.0", "LOG_", _0RL_enumMember_PM_mLOG__, 5, &_0RL_tcTrack);
#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace PM { 
  const ::CORBA::TypeCode_ptr _tc_LOG_ = _0RL_tc_PM_mLOG__;
} 
#else
const ::CORBA::TypeCode_ptr PM::_tc_LOG_ = _0RL_tc_PM_mLOG__;
#endif

static CORBA::TypeCode_ptr _0RL_tc_PM_mLOG = CORBA::TypeCode::PR_alias_tc("IDL:PM/LOG:1.0", "LOG", _0RL_tc_PM_mLOG__, &_0RL_tcTrack);


#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace PM { 
  const ::CORBA::TypeCode_ptr _tc_LOG = _0RL_tc_PM_mLOG;
} 
#else
const ::CORBA::TypeCode_ptr PM::_tc_LOG = _0RL_tc_PM_mLOG;
#endif

static CORBA::TypeCode_ptr _0RL_tc_PM_mseqPlantList = CORBA::TypeCode::PR_alias_tc("IDL:PM/seqPlantList:1.0", "seqPlantList", CORBA::TypeCode::PR_sequence_tc(0, CORBA::TypeCode::PR_string_tc(0, &_0RL_tcTrack), &_0RL_tcTrack), &_0RL_tcTrack);


#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace PM { 
  const ::CORBA::TypeCode_ptr _tc_seqPlantList = _0RL_tc_PM_mseqPlantList;
} 
#else
const ::CORBA::TypeCode_ptr PM::_tc_seqPlantList = _0RL_tc_PM_mseqPlantList;
#endif

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace PM { 
  const ::CORBA::TypeCode_ptr _tc_iProcess_Monitor = CORBA::TypeCode::PR_interface_tc("IDL:PM/iProcess_Monitor:1.0", "iProcess_Monitor", &_0RL_tcTrack);
} 
#else
const ::CORBA::TypeCode_ptr PM::_tc_iProcess_Monitor = CORBA::TypeCode::PR_interface_tc("IDL:PM/iProcess_Monitor:1.0", "iProcess_Monitor", &_0RL_tcTrack);
#endif

static void _0RL_PM_mLOG___marshal_fn(cdrStream& _s, void* _v)
{
  PM::LOG_* _p = (PM::LOG_*)_v;
  *_p >>= _s;
}
static void _0RL_PM_mLOG___unmarshal_fn(cdrStream& _s, void*& _v)
{
  PM::LOG_* _p = (PM::LOG_*)_v;
  *_p <<= _s;
}

void operator<<=(::CORBA::Any& _a, PM::LOG_ _s)
{
  _a.PR_insert(_0RL_tc_PM_mLOG__,
               _0RL_PM_mLOG___marshal_fn,
               &_s);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, PM::LOG_& _s)
{
  return _a.PR_extract(_0RL_tc_PM_mLOG__,
                       _0RL_PM_mLOG___unmarshal_fn,
                       &_s);
}

static void _0RL_PM_mseqPlantList_marshal_fn(cdrStream& _s, void* _v)
{
  PM::seqPlantList* _p = (PM::seqPlantList*)_v;
  *_p >>= _s;
}
static void _0RL_PM_mseqPlantList_unmarshal_fn(cdrStream& _s, void*& _v)
{
  PM::seqPlantList* _p = new PM::seqPlantList;
  *_p <<= _s;
  _v = _p;
}
static void _0RL_PM_mseqPlantList_destructor_fn(void* _v)
{
  PM::seqPlantList* _p = (PM::seqPlantList*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const PM::seqPlantList& _s)
{
  PM::seqPlantList* _p = new PM::seqPlantList(_s);
  _a.PR_insert(_0RL_tc_PM_mseqPlantList,
               _0RL_PM_mseqPlantList_marshal_fn,
               _0RL_PM_mseqPlantList_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, PM::seqPlantList* _sp)
{
  _a.PR_insert(_0RL_tc_PM_mseqPlantList,
               _0RL_PM_mseqPlantList_marshal_fn,
               _0RL_PM_mseqPlantList_destructor_fn,
               _sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, PM::seqPlantList*& _sp)
{
  return _a >>= (const PM::seqPlantList*&) _sp;
}
::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const PM::seqPlantList*& _sp)
{
  void* _v;
  if (_a.PR_extract(_0RL_tc_PM_mseqPlantList,
                    _0RL_PM_mseqPlantList_unmarshal_fn,
                    _0RL_PM_mseqPlantList_marshal_fn,
                    _0RL_PM_mseqPlantList_destructor_fn,
                    _v)) {
    _sp = (const PM::seqPlantList*)_v;
    return 1;
  }
  return 0;
}

static void _0RL_PM_miProcess__Monitor_marshal_fn(cdrStream& _s, void* _v)
{
  omniObjRef* _o = (omniObjRef*)_v;
  omniObjRef::_marshal(_o, _s);
}
static void _0RL_PM_miProcess__Monitor_unmarshal_fn(cdrStream& _s, void*& _v)
{
  omniObjRef* _o = omniObjRef::_unMarshal(PM::iProcess_Monitor::_PD_repoId, _s);
  _v = _o;
}
static void _0RL_PM_miProcess__Monitor_destructor_fn(void* _v)
{
  omniObjRef* _o = (omniObjRef*)_v;
  if (_o)
    omni::releaseObjRef(_o);
}

void operator<<=(::CORBA::Any& _a, PM::iProcess_Monitor_ptr _o)
{
  PM::iProcess_Monitor_ptr _no = PM::iProcess_Monitor::_duplicate(_o);
  _a.PR_insert(PM::_tc_iProcess_Monitor,
               _0RL_PM_miProcess__Monitor_marshal_fn,
               _0RL_PM_miProcess__Monitor_destructor_fn,
               _no->_PR_getobj());
}
void operator<<=(::CORBA::Any& _a, PM::iProcess_Monitor_ptr* _op)
{
  _a.PR_insert(PM::_tc_iProcess_Monitor,
               _0RL_PM_miProcess__Monitor_marshal_fn,
               _0RL_PM_miProcess__Monitor_destructor_fn,
               (*_op)->_PR_getobj());
  *_op = PM::iProcess_Monitor::_nil();
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, PM::iProcess_Monitor_ptr& _o)
{
  void* _v;
  if (_a.PR_extract(PM::_tc_iProcess_Monitor,
                    _0RL_PM_miProcess__Monitor_unmarshal_fn,
                    _0RL_PM_miProcess__Monitor_marshal_fn,
                    _0RL_PM_miProcess__Monitor_destructor_fn,
                    _v)) {
    omniObjRef* _r = (omniObjRef*)_v;
    if (_r)
      _o = (PM::iProcess_Monitor_ptr)_r->_ptrToObjRef(PM::iProcess_Monitor::_PD_repoId);
    else
      _o = PM::iProcess_Monitor::_nil();
    return 1;
  }
  return 0;
}
