// This file is generated by omniidl (C++ backend) - omniORB_4_2. Do not edit.

#include "iDH_Telcom_s.hh"

OMNI_USING_NAMESPACE(omni)

static const char* _0RL_dyn_library_version = omniORB_4_2_dyn;

static ::CORBA::TypeCode::_Tracker _0RL_tcTrack(__FILE__);

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace DH_Telcom { 
  const ::CORBA::TypeCode_ptr _tc_iDH_Telcom = CORBA::TypeCode::PR_interface_tc("IDL:DH_Telcom/iDH_Telcom:1.0", "iDH_Telcom", &_0RL_tcTrack);
} 
#else
const ::CORBA::TypeCode_ptr DH_Telcom::_tc_iDH_Telcom = CORBA::TypeCode::PR_interface_tc("IDL:DH_Telcom/iDH_Telcom:1.0", "iDH_Telcom", &_0RL_tcTrack);
#endif

static void _0RL_DH__Telcom_miDH__Telcom_marshal_fn(cdrStream& _s, void* _v)
{
  omniObjRef* _o = (omniObjRef*)_v;
  omniObjRef::_marshal(_o, _s);
}
static void _0RL_DH__Telcom_miDH__Telcom_unmarshal_fn(cdrStream& _s, void*& _v)
{
  omniObjRef* _o = omniObjRef::_unMarshal(DH_Telcom::iDH_Telcom::_PD_repoId, _s);
  _v = _o;
}
static void _0RL_DH__Telcom_miDH__Telcom_destructor_fn(void* _v)
{
  omniObjRef* _o = (omniObjRef*)_v;
  if (_o)
    omni::releaseObjRef(_o);
}

void operator<<=(::CORBA::Any& _a, DH_Telcom::iDH_Telcom_ptr _o)
{
  DH_Telcom::iDH_Telcom_ptr _no = DH_Telcom::iDH_Telcom::_duplicate(_o);
  _a.PR_insert(DH_Telcom::_tc_iDH_Telcom,
               _0RL_DH__Telcom_miDH__Telcom_marshal_fn,
               _0RL_DH__Telcom_miDH__Telcom_destructor_fn,
               _no->_PR_getobj());
}
void operator<<=(::CORBA::Any& _a, DH_Telcom::iDH_Telcom_ptr* _op)
{
  _a.PR_insert(DH_Telcom::_tc_iDH_Telcom,
               _0RL_DH__Telcom_miDH__Telcom_marshal_fn,
               _0RL_DH__Telcom_miDH__Telcom_destructor_fn,
               (*_op)->_PR_getobj());
  *_op = DH_Telcom::iDH_Telcom::_nil();
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, DH_Telcom::iDH_Telcom_ptr& _o)
{
  void* _v;
  if (_a.PR_extract(DH_Telcom::_tc_iDH_Telcom,
                    _0RL_DH__Telcom_miDH__Telcom_unmarshal_fn,
                    _0RL_DH__Telcom_miDH__Telcom_marshal_fn,
                    _0RL_DH__Telcom_miDH__Telcom_destructor_fn,
                    _v)) {
    omniObjRef* _r = (omniObjRef*)_v;
    if (_r)
      _o = (DH_Telcom::iDH_Telcom_ptr)_r->_ptrToObjRef(DH_Telcom::iDH_Telcom::_PD_repoId);
    else
      _o = DH_Telcom::iDH_Telcom::_nil();
    return 1;
  }
  return 0;
}
