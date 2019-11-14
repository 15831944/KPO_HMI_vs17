// This file is generated by omniidl (C++ backend)- omniORB_4_0. Do not edit.

#include "iDM_Interface_s.hh"
#include <omniORB4/tcDescriptor.h>

OMNI_USING_NAMESPACE(omni)

static const char* _0RL_dyn_library_version = omniORB_4_0;

#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace DM { 
  const CORBA::TypeCode_ptr _tc_iDM_Interface = CORBA::TypeCode::PR_interface_tc("IDL:DM/iDM_Interface:1.0", "iDM_Interface");
} 
#else
const CORBA::TypeCode_ptr DM::_tc_iDM_Interface = CORBA::TypeCode::PR_interface_tc("IDL:DM/iDM_Interface:1.0", "iDM_Interface");
#endif

static void
_0RL_tcParser_setObjectPtr_DM_miDM__Interface(const tcObjrefDesc *_desc, CORBA::Object_ptr _ptr)
{
  DM::iDM_Interface_ptr _p = DM::iDM_Interface::_narrow(_ptr);
  DM::iDM_Interface_ptr* pp = (DM::iDM_Interface_ptr*)_desc->opq_objref;
  if (_desc->opq_release && !CORBA::is_nil(*pp)) CORBA::release(*pp);
  *pp = _p;
  CORBA::release(_ptr);
}

static CORBA::Object_ptr
_0RL_tcParser_getObjectPtr_DM_miDM__Interface(const tcObjrefDesc *_desc)
{
  return (CORBA::Object_ptr) *((DM::iDM_Interface_ptr*)_desc->opq_objref);
}

void _0RL_buildDesc_cDM_miDM__Interface(tcDescriptor& _desc, const _CORBA_ObjRef_tcDesc_arg< DM::_objref_iDM_Interface, DM::iDM_Interface_Helper> & _d)
{
  _desc.p_objref.opq_objref = (void*) &_d._data;
  _desc.p_objref.opq_release = _d._rel;
  _desc.p_objref.setObjectPtr = _0RL_tcParser_setObjectPtr_DM_miDM__Interface;
  _desc.p_objref.getObjectPtr = _0RL_tcParser_getObjectPtr_DM_miDM__Interface;
}

void _0RL_delete_DM_miDM__Interface(void* _data) {
  CORBA::release((DM::iDM_Interface_ptr) _data);
}

void operator<<=(CORBA::Any& _a, DM::iDM_Interface_ptr _s) {
  tcDescriptor tcd;
  _CORBA_ObjRef_tcDesc_arg< DM::_objref_iDM_Interface, DM::iDM_Interface_Helper>  tmp(_s,0);
  _0RL_buildDesc_cDM_miDM__Interface(tcd, tmp);
  _a.PR_packFrom(DM::_tc_iDM_Interface, &tcd);
}

void operator<<=(CORBA::Any& _a, DM::iDM_Interface_ptr* _sp) {
  _a <<= *_sp;
  CORBA::release(*_sp);
  *_sp = DM::iDM_Interface::_nil();
}

CORBA::Boolean operator>>=(const CORBA::Any& _a, DM::iDM_Interface_ptr& _s) {
  DM::iDM_Interface_ptr sp = (DM::iDM_Interface_ptr) _a.PR_getCachedData();
  if (sp == 0) {
    tcDescriptor tcd;
    DM::iDM_Interface_var tmp;
    _0RL_buildDesc_cDM_miDM__Interface(tcd, tmp);
    if( _a.PR_unpackTo(DM::_tc_iDM_Interface, &tcd) ) {
      if (!omniORB::omniORB_27_CompatibleAnyExtraction) {
        ((CORBA::Any*)&_a)->PR_setCachedData((void*)(DM::iDM_Interface_ptr)tmp,_0RL_delete_DM_miDM__Interface);
      }
      _s = tmp._retn();
      return 1;
    } else {
      _s = DM::iDM_Interface::_nil(); return 0;
    }
  }
  else {
    CORBA::TypeCode_var tc = _a.type();
    if (tc->equivalent(DM::_tc_iDM_Interface)) {
    _s = sp; return 1;
    }
    else {
    _s = DM::iDM_Interface::_nil(); return 0;
    }
  }
}
