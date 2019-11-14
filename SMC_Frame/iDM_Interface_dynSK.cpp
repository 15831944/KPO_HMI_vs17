// This file is generated by omniidl (C++ backend) - omniORB_4_2. Do not edit.

#include "iDM_Interface_s.hh"

OMNI_USING_NAMESPACE(omni)

static const char* _0RL_dyn_library_version = omniORB_4_2_dyn;

static ::CORBA::TypeCode::_Tracker _0RL_tcTrack(__FILE__);

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace DM { 
  const ::CORBA::TypeCode_ptr _tc_iDM_Interface = CORBA::TypeCode::PR_interface_tc("IDL:DM/iDM_Interface:1.0", "iDM_Interface", &_0RL_tcTrack);
} 
#else
const ::CORBA::TypeCode_ptr DM::_tc_iDM_Interface = CORBA::TypeCode::PR_interface_tc("IDL:DM/iDM_Interface:1.0", "iDM_Interface", &_0RL_tcTrack);
#endif

static void _0RL_DM_miDM__Interface_marshal_fn(cdrStream& _s, void* _v)
{
  omniObjRef* _o = (omniObjRef*)_v;
  omniObjRef::_marshal(_o, _s);
}
static void _0RL_DM_miDM__Interface_unmarshal_fn(cdrStream& _s, void*& _v)
{
  omniObjRef* _o = omniObjRef::_unMarshal(DM::iDM_Interface::_PD_repoId, _s);
  _v = _o;
}
static void _0RL_DM_miDM__Interface_destructor_fn(void* _v)
{
  omniObjRef* _o = (omniObjRef*)_v;
  if (_o)
    omni::releaseObjRef(_o);
}

void operator<<=(::CORBA::Any& _a, DM::iDM_Interface_ptr _o)
{
  DM::iDM_Interface_ptr _no = DM::iDM_Interface::_duplicate(_o);
  _a.PR_insert(DM::_tc_iDM_Interface,
               _0RL_DM_miDM__Interface_marshal_fn,
               _0RL_DM_miDM__Interface_destructor_fn,
               _no->_PR_getobj());
}
void operator<<=(::CORBA::Any& _a, DM::iDM_Interface_ptr* _op)
{
  _a.PR_insert(DM::_tc_iDM_Interface,
               _0RL_DM_miDM__Interface_marshal_fn,
               _0RL_DM_miDM__Interface_destructor_fn,
               (*_op)->_PR_getobj());
  *_op = DM::iDM_Interface::_nil();
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, DM::iDM_Interface_ptr& _o)
{
  void* _v;
  if (_a.PR_extract(DM::_tc_iDM_Interface,
                    _0RL_DM_miDM__Interface_unmarshal_fn,
                    _0RL_DM_miDM__Interface_marshal_fn,
                    _0RL_DM_miDM__Interface_destructor_fn,
                    _v)) {
    omniObjRef* _r = (omniObjRef*)_v;
    if (_r)
      _o = (DM::iDM_Interface_ptr)_r->_ptrToObjRef(DM::iDM_Interface::_PD_repoId);
    else
      _o = DM::iDM_Interface::_nil();
    return 1;
  }
  return 0;
}

