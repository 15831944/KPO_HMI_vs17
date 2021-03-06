// This file is generated by omniidl (C++ backend)- omniORB_4_0. Do not edit.

#include "iData_Provider_s.hh"
#include <omniORB4/tcDescriptor.h>

OMNI_USING_NAMESPACE(omni)

static const char* _0RL_dyn_library_version = omniORB_4_0;

static CORBA::TypeCode_ptr _0RL_tc_DEF_mseqLong = CORBA::TypeCode::PR_alias_tc("IDL:DEF/seqLong:1.0", "seqLong", CORBA::TypeCode::PR_sequence_tc(0, CORBA::TypeCode::PR_long_tc()));


#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace DEF { 
  const CORBA::TypeCode_ptr _tc_seqLong = _0RL_tc_DEF_mseqLong;
} 
#else
const CORBA::TypeCode_ptr DEF::_tc_seqLong = _0RL_tc_DEF_mseqLong;
#endif

static CORBA::TypeCode_ptr _0RL_tc_DEF_mseqDouble = CORBA::TypeCode::PR_alias_tc("IDL:DEF/seqDouble:1.0", "seqDouble", CORBA::TypeCode::PR_sequence_tc(0, CORBA::TypeCode::PR_double_tc()));


#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace DEF { 
  const CORBA::TypeCode_ptr _tc_seqDouble = _0RL_tc_DEF_mseqDouble;
} 
#else
const CORBA::TypeCode_ptr DEF::_tc_seqDouble = _0RL_tc_DEF_mseqDouble;
#endif

static CORBA::TypeCode_ptr _0RL_tc_DEF_mseqBoolean = CORBA::TypeCode::PR_alias_tc("IDL:DEF/seqBoolean:1.0", "seqBoolean", CORBA::TypeCode::PR_sequence_tc(0, CORBA::TypeCode::PR_boolean_tc()));


#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace DEF { 
  const CORBA::TypeCode_ptr _tc_seqBoolean = _0RL_tc_DEF_mseqBoolean;
} 
#else
const CORBA::TypeCode_ptr DEF::_tc_seqBoolean = _0RL_tc_DEF_mseqBoolean;
#endif

static CORBA::TypeCode_ptr _0RL_tc_DEF_mseqString = CORBA::TypeCode::PR_alias_tc("IDL:DEF/seqString:1.0", "seqString", CORBA::TypeCode::PR_sequence_tc(0, CORBA::TypeCode::PR_string_tc(0)));


#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
namespace DEF { 
  const CORBA::TypeCode_ptr _tc_seqString = _0RL_tc_DEF_mseqString;
} 
#else
const CORBA::TypeCode_ptr DEF::_tc_seqString = _0RL_tc_DEF_mseqString;
#endif

static CORBA::PR_structMember _0RL_structmember_sIntfDataList[] = {
  {"Name", CORBA::TypeCode::PR_string_tc(0)},
  {"Type", CORBA::TypeCode::PR_string_tc(0)}
};

static CORBA::TypeCode_ptr _0RL_tc_sIntfDataList = CORBA::TypeCode::PR_struct_tc("IDL:sIntfDataList:1.0", "sIntfDataList", _0RL_structmember_sIntfDataList, 2);
const CORBA::TypeCode_ptr _tc_sIntfDataList = _0RL_tc_sIntfDataList;






static CORBA::TypeCode_ptr _0RL_tc_seqIntfDataList = CORBA::TypeCode::PR_alias_tc("IDL:seqIntfDataList:1.0", "seqIntfDataList", CORBA::TypeCode::PR_sequence_tc(0, _0RL_tc_sIntfDataList));


const CORBA::TypeCode_ptr _tc_seqIntfDataList = _0RL_tc_seqIntfDataList;

const CORBA::TypeCode_ptr _tc_iData_Provider = CORBA::TypeCode::PR_interface_tc("IDL:iData_Provider:1.0", "iData_Provider");

#ifndef __0RL_tcParser_buildDesc_s0_clong__
#define __0RL_tcParser_buildDesc_s0_clong__
static void
_0RL_tcParser_setElementCount_s0_clong(const tcSequenceDesc* _desc, CORBA::ULong _len)
{
  ((_CORBA_Unbounded_Sequence_w_FixSizeElement< CORBA::Long, 4, 4 > *)_desc->opq_seq)->length(_len);
}

static CORBA::ULong
_0RL_tcParser_getElementCount_s0_clong(const tcSequenceDesc* _desc)
{
  return ((_CORBA_Unbounded_Sequence_w_FixSizeElement< CORBA::Long, 4, 4 > *)_desc->opq_seq)->length();
}

static CORBA::Boolean
_0RL_tcParser_getElementDesc_s0_clong(const tcSequenceDesc* _desc, CORBA::ULong _index, tcDescriptor& _newdesc, _CORBA_ULong& _contiguous)
{
  _newdesc.p_streamdata = ((_CORBA_Unbounded_Sequence_w_FixSizeElement< CORBA::Long, 4, 4 > *)_desc->opq_seq)->NP_data();
  _contiguous = ((_CORBA_Unbounded_Sequence_w_FixSizeElement< CORBA::Long, 4, 4 > *)_desc->opq_seq)->length() - _index;


  return 1;
}

static void
_0RL_buildDesc_s0_clong(tcDescriptor &_desc, const _CORBA_Unbounded_Sequence_w_FixSizeElement< CORBA::Long, 4, 4 > & _data)
{
  _desc.p_sequence.opq_seq = (void*) &_data;
  _desc.p_sequence.setElementCount =
    _0RL_tcParser_setElementCount_s0_clong;
  _desc.p_sequence.getElementCount =
    _0RL_tcParser_getElementCount_s0_clong;
  _desc.p_sequence.getElementDesc =
    _0RL_tcParser_getElementDesc_s0_clong;
  }
#endif

void operator <<= (CORBA::Any& _a, const DEF::seqLong& _s)
{
  tcDescriptor tcdesc;
  _0RL_buildDesc_s0_clong(tcdesc, _s);
  _a.PR_packFrom(DEF::_tc_seqLong, &tcdesc);
}

void _0RL_seq_delete_DEF_mseqLong(void* _data)
{
  delete (DEF::seqLong*)_data;
}

CORBA::Boolean operator >>= (const CORBA::Any& _a, DEF::seqLong*& _s_out)
{
  return _a >>= (const DEF::seqLong*&) _s_out;
}

CORBA::Boolean operator >>= (const CORBA::Any& _a, const DEF::seqLong*& _s_out)
{
  _s_out = 0;
  DEF::seqLong* stmp = (DEF::seqLong*) _a.PR_getCachedData();
  if( stmp == 0 ) {
    tcDescriptor tcdesc;
    stmp = new DEF::seqLong;
    _0RL_buildDesc_s0_clong(tcdesc, *stmp);
    if( _a.PR_unpackTo(DEF::_tc_seqLong, &tcdesc)) {
      ((CORBA::Any*)&_a)->PR_setCachedData((void*)stmp, _0RL_seq_delete_DEF_mseqLong);
      _s_out = stmp;
      return 1;
    } else {
      delete (DEF::seqLong *)stmp;
      return 0;
    }
  } else {
    CORBA::TypeCode_var tctmp = _a.type();
    if( tctmp->equivalent(DEF::_tc_seqLong) ) {
      _s_out = stmp;
      return 1;
    } else {
      return 0;
    }
  }
}

#ifndef __0RL_tcParser_buildDesc_s0_cdouble__
#define __0RL_tcParser_buildDesc_s0_cdouble__
static void
_0RL_tcParser_setElementCount_s0_cdouble(const tcSequenceDesc* _desc, CORBA::ULong _len)
{
  ((_CORBA_Unbounded_Sequence_w_FixSizeElement< CORBA::Double, 8, 8 > *)_desc->opq_seq)->length(_len);
}

static CORBA::ULong
_0RL_tcParser_getElementCount_s0_cdouble(const tcSequenceDesc* _desc)
{
  return ((_CORBA_Unbounded_Sequence_w_FixSizeElement< CORBA::Double, 8, 8 > *)_desc->opq_seq)->length();
}

static CORBA::Boolean
_0RL_tcParser_getElementDesc_s0_cdouble(const tcSequenceDesc* _desc, CORBA::ULong _index, tcDescriptor& _newdesc, _CORBA_ULong& _contiguous)
{
  _newdesc.p_streamdata = ((_CORBA_Unbounded_Sequence_w_FixSizeElement< CORBA::Double, 8, 8 > *)_desc->opq_seq)->NP_data();
  _contiguous = ((_CORBA_Unbounded_Sequence_w_FixSizeElement< CORBA::Double, 8, 8 > *)_desc->opq_seq)->length() - _index;


  return 1;
}

static void
_0RL_buildDesc_s0_cdouble(tcDescriptor &_desc, const _CORBA_Unbounded_Sequence_w_FixSizeElement< CORBA::Double, 8, 8 > & _data)
{
  _desc.p_sequence.opq_seq = (void*) &_data;
  _desc.p_sequence.setElementCount =
    _0RL_tcParser_setElementCount_s0_cdouble;
  _desc.p_sequence.getElementCount =
    _0RL_tcParser_getElementCount_s0_cdouble;
  _desc.p_sequence.getElementDesc =
    _0RL_tcParser_getElementDesc_s0_cdouble;
  }
#endif

void operator <<= (CORBA::Any& _a, const DEF::seqDouble& _s)
{
  tcDescriptor tcdesc;
  _0RL_buildDesc_s0_cdouble(tcdesc, _s);
  _a.PR_packFrom(DEF::_tc_seqDouble, &tcdesc);
}

void _0RL_seq_delete_DEF_mseqDouble(void* _data)
{
  delete (DEF::seqDouble*)_data;
}

CORBA::Boolean operator >>= (const CORBA::Any& _a, DEF::seqDouble*& _s_out)
{
  return _a >>= (const DEF::seqDouble*&) _s_out;
}

CORBA::Boolean operator >>= (const CORBA::Any& _a, const DEF::seqDouble*& _s_out)
{
  _s_out = 0;
  DEF::seqDouble* stmp = (DEF::seqDouble*) _a.PR_getCachedData();
  if( stmp == 0 ) {
    tcDescriptor tcdesc;
    stmp = new DEF::seqDouble;
    _0RL_buildDesc_s0_cdouble(tcdesc, *stmp);
    if( _a.PR_unpackTo(DEF::_tc_seqDouble, &tcdesc)) {
      ((CORBA::Any*)&_a)->PR_setCachedData((void*)stmp, _0RL_seq_delete_DEF_mseqDouble);
      _s_out = stmp;
      return 1;
    } else {
      delete (DEF::seqDouble *)stmp;
      return 0;
    }
  } else {
    CORBA::TypeCode_var tctmp = _a.type();
    if( tctmp->equivalent(DEF::_tc_seqDouble) ) {
      _s_out = stmp;
      return 1;
    } else {
      return 0;
    }
  }
}

#ifndef __0RL_tcParser_buildDesc_s0_cboolean__
#define __0RL_tcParser_buildDesc_s0_cboolean__
static void
_0RL_tcParser_setElementCount_s0_cboolean(const tcSequenceDesc* _desc, CORBA::ULong _len)
{
  ((_CORBA_Unbounded_Sequence_Boolean*)_desc->opq_seq)->length(_len);
}

static CORBA::ULong
_0RL_tcParser_getElementCount_s0_cboolean(const tcSequenceDesc* _desc)
{
  return ((_CORBA_Unbounded_Sequence_Boolean*)_desc->opq_seq)->length();
}

static CORBA::Boolean
_0RL_tcParser_getElementDesc_s0_cboolean(const tcSequenceDesc* _desc, CORBA::ULong _index, tcDescriptor& _newdesc, _CORBA_ULong& _contiguous)
{
  _newdesc.p_streamdata = ((_CORBA_Unbounded_Sequence_Boolean*)_desc->opq_seq)->NP_data();
  _contiguous = ((_CORBA_Unbounded_Sequence_Boolean*)_desc->opq_seq)->length() - _index;


  return 1;
}

static void
_0RL_buildDesc_s0_cboolean(tcDescriptor &_desc, const _CORBA_Unbounded_Sequence_Boolean& _data)
{
  _desc.p_sequence.opq_seq = (void*) &_data;
  _desc.p_sequence.setElementCount =
    _0RL_tcParser_setElementCount_s0_cboolean;
  _desc.p_sequence.getElementCount =
    _0RL_tcParser_getElementCount_s0_cboolean;
  _desc.p_sequence.getElementDesc =
    _0RL_tcParser_getElementDesc_s0_cboolean;
  }
#endif

void operator <<= (CORBA::Any& _a, const DEF::seqBoolean& _s)
{
  tcDescriptor tcdesc;
  _0RL_buildDesc_s0_cboolean(tcdesc, _s);
  _a.PR_packFrom(DEF::_tc_seqBoolean, &tcdesc);
}

void _0RL_seq_delete_DEF_mseqBoolean(void* _data)
{
  delete (DEF::seqBoolean*)_data;
}

CORBA::Boolean operator >>= (const CORBA::Any& _a, DEF::seqBoolean*& _s_out)
{
  return _a >>= (const DEF::seqBoolean*&) _s_out;
}

CORBA::Boolean operator >>= (const CORBA::Any& _a, const DEF::seqBoolean*& _s_out)
{
  _s_out = 0;
  DEF::seqBoolean* stmp = (DEF::seqBoolean*) _a.PR_getCachedData();
  if( stmp == 0 ) {
    tcDescriptor tcdesc;
    stmp = new DEF::seqBoolean;
    _0RL_buildDesc_s0_cboolean(tcdesc, *stmp);
    if( _a.PR_unpackTo(DEF::_tc_seqBoolean, &tcdesc)) {
      ((CORBA::Any*)&_a)->PR_setCachedData((void*)stmp, _0RL_seq_delete_DEF_mseqBoolean);
      _s_out = stmp;
      return 1;
    } else {
      delete (DEF::seqBoolean *)stmp;
      return 0;
    }
  } else {
    CORBA::TypeCode_var tctmp = _a.type();
    if( tctmp->equivalent(DEF::_tc_seqBoolean) ) {
      _s_out = stmp;
      return 1;
    } else {
      return 0;
    }
  }
}

#ifndef __0RL_tcParser_buildDesc_s0_cstring__
#define __0RL_tcParser_buildDesc_s0_cstring__
static void
_0RL_tcParser_setElementCount_s0_cstring(const tcSequenceDesc* _desc, CORBA::ULong _len)
{
  ((_CORBA_Unbounded_Sequence_String*)_desc->opq_seq)->length(_len);
}

static CORBA::ULong
_0RL_tcParser_getElementCount_s0_cstring(const tcSequenceDesc* _desc)
{
  return ((_CORBA_Unbounded_Sequence_String*)_desc->opq_seq)->length();
}

static CORBA::Boolean
_0RL_tcParser_getElementDesc_s0_cstring(const tcSequenceDesc* _desc, CORBA::ULong _index, tcDescriptor& _newdesc, _CORBA_ULong& _contiguous)
{
  _0RL_buildDesc_cstring(_newdesc, (*((_CORBA_Unbounded_Sequence_String*)_desc->opq_seq))[_index]);


  return 1;
}

static void
_0RL_buildDesc_s0_cstring(tcDescriptor &_desc, const _CORBA_Unbounded_Sequence_String& _data)
{
  _desc.p_sequence.opq_seq = (void*) &_data;
  _desc.p_sequence.setElementCount =
    _0RL_tcParser_setElementCount_s0_cstring;
  _desc.p_sequence.getElementCount =
    _0RL_tcParser_getElementCount_s0_cstring;
  _desc.p_sequence.getElementDesc =
    _0RL_tcParser_getElementDesc_s0_cstring;
  }
#endif

void operator <<= (CORBA::Any& _a, const DEF::seqString& _s)
{
  tcDescriptor tcdesc;
  _0RL_buildDesc_s0_cstring(tcdesc, _s);
  _a.PR_packFrom(DEF::_tc_seqString, &tcdesc);
}

void _0RL_seq_delete_DEF_mseqString(void* _data)
{
  delete (DEF::seqString*)_data;
}

CORBA::Boolean operator >>= (const CORBA::Any& _a, DEF::seqString*& _s_out)
{
  return _a >>= (const DEF::seqString*&) _s_out;
}

CORBA::Boolean operator >>= (const CORBA::Any& _a, const DEF::seqString*& _s_out)
{
  _s_out = 0;
  DEF::seqString* stmp = (DEF::seqString*) _a.PR_getCachedData();
  if( stmp == 0 ) {
    tcDescriptor tcdesc;
    stmp = new DEF::seqString;
    _0RL_buildDesc_s0_cstring(tcdesc, *stmp);
    if( _a.PR_unpackTo(DEF::_tc_seqString, &tcdesc)) {
      ((CORBA::Any*)&_a)->PR_setCachedData((void*)stmp, _0RL_seq_delete_DEF_mseqString);
      _s_out = stmp;
      return 1;
    } else {
      delete (DEF::seqString *)stmp;
      return 0;
    }
  } else {
    CORBA::TypeCode_var tctmp = _a.type();
    if( tctmp->equivalent(DEF::_tc_seqString) ) {
      _s_out = stmp;
      return 1;
    } else {
      return 0;
    }
  }
}

void _0RL_delete_sIntfDataList(void* _data) {
  sIntfDataList* _0RL_t = (sIntfDataList*) _data;
  delete _0RL_t;
}

static CORBA::Boolean
_0RL_tcParser_getMemberDesc_sIntfDataList(const tcStructDesc *_desc, CORBA::ULong _index, tcDescriptor &_newdesc){
  switch (_index) {
  case 0:
    _0RL_buildDesc_cstring(_newdesc, ((sIntfDataList*)_desc->opq_struct)->Name);
    return 1;
  case 1:
    _0RL_buildDesc_cstring(_newdesc, ((sIntfDataList*)_desc->opq_struct)->Type);
    return 1;

  default:
    return 0;
  };
}
static CORBA::ULong

_0RL_tcParser_getMemberCount_sIntfDataList(const tcStructDesc *_desc)
{
  return 2;
}

void _0RL_buildDesc_csIntfDataList(tcDescriptor &_desc, const sIntfDataList& _data)
{
  _desc.p_struct.getMemberDesc = _0RL_tcParser_getMemberDesc_sIntfDataList;
  _desc.p_struct.getMemberCount = _0RL_tcParser_getMemberCount_sIntfDataList;
  _desc.p_struct.opq_struct = (void *)&_data;
}



void operator<<=(CORBA::Any& _a, const sIntfDataList& _s) {
  tcDescriptor _0RL_tcdesc;
  _0RL_buildDesc_csIntfDataList(_0RL_tcdesc, _s);
  _a.PR_packFrom(_0RL_tc_sIntfDataList, &_0RL_tcdesc);
}
 
void operator<<=(CORBA::Any& _a, sIntfDataList* _sp) {
  tcDescriptor _0RL_tcdesc;
  _0RL_buildDesc_csIntfDataList(_0RL_tcdesc, *_sp);
  _a.PR_packFrom(_0RL_tc_sIntfDataList, &_0RL_tcdesc);
  delete _sp;
}

CORBA::Boolean operator>>=(const CORBA::Any& _a, sIntfDataList*& _sp) {
  return _a >>= (const sIntfDataList*&) _sp;
}

CORBA::Boolean operator>>=(const CORBA::Any& _a, const sIntfDataList*& _sp) {
  _sp = (sIntfDataList *) _a.PR_getCachedData();
  if (_sp == 0) {
    tcDescriptor _0RL_tcdesc;
    _sp = new sIntfDataList;
    _0RL_buildDesc_csIntfDataList(_0RL_tcdesc, *_sp);
    if (_a.PR_unpackTo(_0RL_tc_sIntfDataList, &_0RL_tcdesc)) {
      ((CORBA::Any *)&_a)->PR_setCachedData((void*)_sp, _0RL_delete_sIntfDataList);
      return 1;
    } else {
      delete (sIntfDataList *)_sp; _sp = 0;
      return 0;
    }
  } else {
    CORBA::TypeCode_var _0RL_tctmp = _a.type();
    if (_0RL_tctmp->equivalent(_0RL_tc_sIntfDataList)) return 1;
    _sp = 0;
    return 0;
  }
}
#ifndef __0RL_tcParser_buildDesc_s0_csIntfDataList__
#define __0RL_tcParser_buildDesc_s0_csIntfDataList__
static void
_0RL_tcParser_setElementCount_s0_csIntfDataList(const tcSequenceDesc* _desc, CORBA::ULong _len)
{
  ((_CORBA_Unbounded_Sequence< sIntfDataList > *)_desc->opq_seq)->length(_len);
}

static CORBA::ULong
_0RL_tcParser_getElementCount_s0_csIntfDataList(const tcSequenceDesc* _desc)
{
  return ((_CORBA_Unbounded_Sequence< sIntfDataList > *)_desc->opq_seq)->length();
}

static CORBA::Boolean
_0RL_tcParser_getElementDesc_s0_csIntfDataList(const tcSequenceDesc* _desc, CORBA::ULong _index, tcDescriptor& _newdesc, _CORBA_ULong& _contiguous)
{
  _0RL_buildDesc_csIntfDataList(_newdesc, (*((_CORBA_Unbounded_Sequence< sIntfDataList > *)_desc->opq_seq))[_index]);


  return 1;
}

static void
_0RL_buildDesc_s0_csIntfDataList(tcDescriptor &_desc, const _CORBA_Unbounded_Sequence< sIntfDataList > & _data)
{
  _desc.p_sequence.opq_seq = (void*) &_data;
  _desc.p_sequence.setElementCount =
    _0RL_tcParser_setElementCount_s0_csIntfDataList;
  _desc.p_sequence.getElementCount =
    _0RL_tcParser_getElementCount_s0_csIntfDataList;
  _desc.p_sequence.getElementDesc =
    _0RL_tcParser_getElementDesc_s0_csIntfDataList;
  }
#endif

void operator <<= (CORBA::Any& _a, const seqIntfDataList& _s)
{
  tcDescriptor tcdesc;
  _0RL_buildDesc_s0_csIntfDataList(tcdesc, _s);
  _a.PR_packFrom(_tc_seqIntfDataList, &tcdesc);
}

void _0RL_seq_delete_seqIntfDataList(void* _data)
{
  delete (seqIntfDataList*)_data;
}

CORBA::Boolean operator >>= (const CORBA::Any& _a, seqIntfDataList*& _s_out)
{
  return _a >>= (const seqIntfDataList*&) _s_out;
}

CORBA::Boolean operator >>= (const CORBA::Any& _a, const seqIntfDataList*& _s_out)
{
  _s_out = 0;
  seqIntfDataList* stmp = (seqIntfDataList*) _a.PR_getCachedData();
  if( stmp == 0 ) {
    tcDescriptor tcdesc;
    stmp = new seqIntfDataList;
    _0RL_buildDesc_s0_csIntfDataList(tcdesc, *stmp);
    if( _a.PR_unpackTo(_tc_seqIntfDataList, &tcdesc)) {
      ((CORBA::Any*)&_a)->PR_setCachedData((void*)stmp, _0RL_seq_delete_seqIntfDataList);
      _s_out = stmp;
      return 1;
    } else {
      delete (seqIntfDataList *)stmp;
      return 0;
    }
  } else {
    CORBA::TypeCode_var tctmp = _a.type();
    if( tctmp->equivalent(_tc_seqIntfDataList) ) {
      _s_out = stmp;
      return 1;
    } else {
      return 0;
    }
  }
}

static void
_0RL_tcParser_setObjectPtr_iData__Provider(const tcObjrefDesc *_desc, CORBA::Object_ptr _ptr)
{
  iData_Provider_ptr _p = iData_Provider::_narrow(_ptr);
  iData_Provider_ptr* pp = (iData_Provider_ptr*)_desc->opq_objref;
  if (_desc->opq_release && !CORBA::is_nil(*pp)) CORBA::release(*pp);
  *pp = _p;
  CORBA::release(_ptr);
}

static CORBA::Object_ptr
_0RL_tcParser_getObjectPtr_iData__Provider(const tcObjrefDesc *_desc)
{
  return (CORBA::Object_ptr) *((iData_Provider_ptr*)_desc->opq_objref);
}

void _0RL_buildDesc_ciData__Provider(tcDescriptor& _desc, const _CORBA_ObjRef_tcDesc_arg< _objref_iData_Provider, iData_Provider_Helper> & _d)
{
  _desc.p_objref.opq_objref = (void*) &_d._data;
  _desc.p_objref.opq_release = _d._rel;
  _desc.p_objref.setObjectPtr = _0RL_tcParser_setObjectPtr_iData__Provider;
  _desc.p_objref.getObjectPtr = _0RL_tcParser_getObjectPtr_iData__Provider;
}

void _0RL_delete_iData__Provider(void* _data) {
  CORBA::release((iData_Provider_ptr) _data);
}

void operator<<=(CORBA::Any& _a, iData_Provider_ptr _s) {
  tcDescriptor tcd;
  _CORBA_ObjRef_tcDesc_arg< _objref_iData_Provider, iData_Provider_Helper>  tmp(_s,0);
  _0RL_buildDesc_ciData__Provider(tcd, tmp);
  _a.PR_packFrom(_tc_iData_Provider, &tcd);
}

void operator<<=(CORBA::Any& _a, iData_Provider_ptr* _sp) {
  _a <<= *_sp;
  CORBA::release(*_sp);
  *_sp = iData_Provider::_nil();
}

CORBA::Boolean operator>>=(const CORBA::Any& _a, iData_Provider_ptr& _s) {
  iData_Provider_ptr sp = (iData_Provider_ptr) _a.PR_getCachedData();
  if (sp == 0) {
    tcDescriptor tcd;
    iData_Provider_var tmp;
    _0RL_buildDesc_ciData__Provider(tcd, tmp);
    if( _a.PR_unpackTo(_tc_iData_Provider, &tcd) ) {
      if (!omniORB::omniORB_27_CompatibleAnyExtraction) {
        ((CORBA::Any*)&_a)->PR_setCachedData((void*)(iData_Provider_ptr)tmp,_0RL_delete_iData__Provider);
      }
      _s = tmp._retn();
      return 1;
    } else {
      _s = iData_Provider::_nil(); return 0;
    }
  }
  else {
    CORBA::TypeCode_var tc = _a.type();
    if (tc->equivalent(_tc_iData_Provider)) {
    _s = sp; return 1;
    }
    else {
    _s = iData_Provider::_nil(); return 0;
    }
  }
}

