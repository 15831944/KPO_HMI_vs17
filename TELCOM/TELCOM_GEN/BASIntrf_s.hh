// This file is generated by omniidl (C++ backend)- omniORB_4_2. Do not edit.
#ifndef __BASIntrf_hh__
#define __BASIntrf_hh__

#ifndef __CORBA_H_EXTERNAL_GUARD__
#include <omniORB4/CORBA.h>
#endif

#ifndef  USE_stub_in_nt_dll
# define USE_stub_in_nt_dll_NOT_DEFINED_BASIntrf
#endif
#ifndef  USE_core_stub_in_nt_dll
# define USE_core_stub_in_nt_dll_NOT_DEFINED_BASIntrf
#endif
#ifndef  USE_dyn_stub_in_nt_dll
# define USE_dyn_stub_in_nt_dll_NOT_DEFINED_BASIntrf
#endif



#ifndef __corbaidl_hh_EXTERNAL_GUARD__
#define __corbaidl_hh_EXTERNAL_GUARD__
#include <corbaidl_s.hh>
#endif
#ifndef __boxes_hh_EXTERNAL_GUARD__
#define __boxes_hh_EXTERNAL_GUARD__
#include <boxes_s.hh>
#endif



#ifdef USE_stub_in_nt_dll
# ifndef USE_core_stub_in_nt_dll
#  define USE_core_stub_in_nt_dll
# endif
# ifndef USE_dyn_stub_in_nt_dll
#  define USE_dyn_stub_in_nt_dll
# endif
#endif

#ifdef _core_attr
# error "A local CPP macro _core_attr has already been defined."
#else
# ifdef  USE_core_stub_in_nt_dll
#  define _core_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _core_attr
# endif
#endif

#ifdef _dyn_attr
# error "A local CPP macro _dyn_attr has already been defined."
#else
# ifdef  USE_dyn_stub_in_nt_dll
#  define _dyn_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _dyn_attr
# endif
#endif



_CORBA_MODULE IBAS

_CORBA_MODULE_BEG

  struct IBAS_LastResponse {
    typedef _CORBA_ConstrType_Variable_Var<IBAS_LastResponse> _var_type;

    
    ::CORBA::String_member intName;

    ::CORBA::String_member lastTime;

    ::CORBA::Boolean status;

  

    void operator>>= (cdrStream &) const;
    void operator<<= (cdrStream &);
  };

  typedef IBAS_LastResponse::_var_type IBAS_LastResponse_var;

  typedef _CORBA_ConstrType_Variable_OUT_arg< IBAS_LastResponse,IBAS_LastResponse_var > IBAS_LastResponse_out;

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_IBAS_LastResponse;

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_seq_IBAS_LastResponses;

  class seq_IBAS_LastResponses_var;

  class seq_IBAS_LastResponses : public _CORBA_Unbounded_Sequence< IBAS_LastResponse >  {
  public:
    typedef seq_IBAS_LastResponses_var _var_type;
    inline seq_IBAS_LastResponses() {}
    inline seq_IBAS_LastResponses(const seq_IBAS_LastResponses& _s)
      : _CORBA_Unbounded_Sequence< IBAS_LastResponse > (_s) {}

    inline seq_IBAS_LastResponses(_CORBA_ULong _max)
      : _CORBA_Unbounded_Sequence< IBAS_LastResponse > (_max) {}
    inline seq_IBAS_LastResponses(_CORBA_ULong _max, _CORBA_ULong _len, IBAS_LastResponse* _val, _CORBA_Boolean _rel=0)
      : _CORBA_Unbounded_Sequence< IBAS_LastResponse > (_max, _len, _val, _rel) {}

  

    inline seq_IBAS_LastResponses& operator = (const seq_IBAS_LastResponses& _s) {
      _CORBA_Unbounded_Sequence< IBAS_LastResponse > ::operator=(_s);
      return *this;
    }
  };

  class seq_IBAS_LastResponses_out;

  class seq_IBAS_LastResponses_var {
  public:
    inline seq_IBAS_LastResponses_var() : _pd_seq(0) {}
    inline seq_IBAS_LastResponses_var(seq_IBAS_LastResponses* _s) : _pd_seq(_s) {}
    inline seq_IBAS_LastResponses_var(const seq_IBAS_LastResponses_var& _s) {
      if (_s._pd_seq)  _pd_seq = new seq_IBAS_LastResponses(*_s._pd_seq);
      else             _pd_seq = 0;
    }
    inline ~seq_IBAS_LastResponses_var() { if (_pd_seq)  delete _pd_seq; }
      
    inline seq_IBAS_LastResponses_var& operator = (seq_IBAS_LastResponses* _s) {
      if (_pd_seq)  delete _pd_seq;
      _pd_seq = _s;
      return *this;
    }
    inline seq_IBAS_LastResponses_var& operator = (const seq_IBAS_LastResponses_var& _s) {
      if (&_s != this) {
        if (_s._pd_seq) {
          if (!_pd_seq)  _pd_seq = new seq_IBAS_LastResponses;
          *_pd_seq = *_s._pd_seq;
        }
        else if (_pd_seq) {
          delete _pd_seq;
          _pd_seq = 0;
        }
      }
      return *this;
    }
    inline IBAS_LastResponse& operator [] (_CORBA_ULong _s) {
      return (*_pd_seq)[_s];
    }

  

    inline seq_IBAS_LastResponses* operator -> () { return _pd_seq; }
    inline const seq_IBAS_LastResponses* operator -> () const { return _pd_seq; }
#if defined(__GNUG__)
    inline operator seq_IBAS_LastResponses& () const { return *_pd_seq; }
#else
    inline operator const seq_IBAS_LastResponses& () const { return *_pd_seq; }
    inline operator seq_IBAS_LastResponses& () { return *_pd_seq; }
#endif
      
    inline const seq_IBAS_LastResponses& in() const { return *_pd_seq; }
    inline seq_IBAS_LastResponses&       inout()    { return *_pd_seq; }
    inline seq_IBAS_LastResponses*&      out() {
      if (_pd_seq) { delete _pd_seq; _pd_seq = 0; }
      return _pd_seq;
    }
    inline seq_IBAS_LastResponses* _retn() { seq_IBAS_LastResponses* tmp = _pd_seq; _pd_seq = 0; return tmp; }
      
    friend class seq_IBAS_LastResponses_out;
    
  private:
    seq_IBAS_LastResponses* _pd_seq;
  };

  class seq_IBAS_LastResponses_out {
  public:
    inline seq_IBAS_LastResponses_out(seq_IBAS_LastResponses*& _s) : _data(_s) { _data = 0; }
    inline seq_IBAS_LastResponses_out(seq_IBAS_LastResponses_var& _s)
      : _data(_s._pd_seq) { _s = (seq_IBAS_LastResponses*) 0; }
    inline seq_IBAS_LastResponses_out(const seq_IBAS_LastResponses_out& _s) : _data(_s._data) {}
    inline seq_IBAS_LastResponses_out& operator = (const seq_IBAS_LastResponses_out& _s) {
      _data = _s._data;
      return *this;
    }
    inline seq_IBAS_LastResponses_out& operator = (seq_IBAS_LastResponses* _s) {
      _data = _s;
      return *this;
    }
    inline operator seq_IBAS_LastResponses*&()  { return _data; }
    inline seq_IBAS_LastResponses*& ptr()       { return _data; }
    inline seq_IBAS_LastResponses* operator->() { return _data; }

    inline IBAS_LastResponse& operator [] (_CORBA_ULong _i) {
      return (*_data)[_i];
    }

  

    seq_IBAS_LastResponses*& _data;

  private:
    seq_IBAS_LastResponses_out();
    seq_IBAS_LastResponses_out& operator=(const seq_IBAS_LastResponses_var&);
  };

  class EXC_TagNotFound : public ::CORBA::UserException {
  public:
    
    

    inline EXC_TagNotFound() {
      pd_insertToAnyFn    = insertToAnyFn;
      pd_insertToAnyFnNCP = insertToAnyFnNCP;
    }
    EXC_TagNotFound(const EXC_TagNotFound&);
    
    EXC_TagNotFound& operator=(const EXC_TagNotFound&);
    virtual ~EXC_TagNotFound();
    virtual void _raise() const;
    static EXC_TagNotFound* _downcast(::CORBA::Exception*);
    static const EXC_TagNotFound* _downcast(const ::CORBA::Exception*);
    static inline EXC_TagNotFound* _narrow(::CORBA::Exception* _e) {
      return _downcast(_e);
    }
    
    inline void operator>>=(cdrStream&) const { }
    inline void operator<<=(cdrStream&) { }

    static _core_attr insertExceptionToAny    insertToAnyFn;
    static _core_attr insertExceptionToAnyNCP insertToAnyFnNCP;

    virtual ::CORBA::Exception* _NP_duplicate() const;

    static _core_attr const char* _PD_repoId;
    static _core_attr const char* _PD_typeId;

  private:
    virtual const char* _NP_typeId() const;
    virtual const char* _NP_repoId(int*) const;
    virtual void _NP_marshal(cdrStream&) const;
  };

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_EXC_TagNotFound;

  class EXC_IncorrectTagType : public ::CORBA::UserException {
  public:
    
    

    inline EXC_IncorrectTagType() {
      pd_insertToAnyFn    = insertToAnyFn;
      pd_insertToAnyFnNCP = insertToAnyFnNCP;
    }
    EXC_IncorrectTagType(const EXC_IncorrectTagType&);
    
    EXC_IncorrectTagType& operator=(const EXC_IncorrectTagType&);
    virtual ~EXC_IncorrectTagType();
    virtual void _raise() const;
    static EXC_IncorrectTagType* _downcast(::CORBA::Exception*);
    static const EXC_IncorrectTagType* _downcast(const ::CORBA::Exception*);
    static inline EXC_IncorrectTagType* _narrow(::CORBA::Exception* _e) {
      return _downcast(_e);
    }
    
    inline void operator>>=(cdrStream&) const { }
    inline void operator<<=(cdrStream&) { }

    static _core_attr insertExceptionToAny    insertToAnyFn;
    static _core_attr insertExceptionToAnyNCP insertToAnyFnNCP;

    virtual ::CORBA::Exception* _NP_duplicate() const;

    static _core_attr const char* _PD_repoId;
    static _core_attr const char* _PD_typeId;

  private:
    virtual const char* _NP_typeId() const;
    virtual const char* _NP_repoId(int*) const;
    virtual void _NP_marshal(cdrStream&) const;
  };

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_EXC_IncorrectTagType;

#ifndef __IBAS_mBASIntrf__
#define __IBAS_mBASIntrf__
  class BASIntrf;
  class _objref_BASIntrf;
  class _impl_BASIntrf;
  
  typedef _objref_BASIntrf* BASIntrf_ptr;
  typedef BASIntrf_ptr BASIntrfRef;

  class BASIntrf_Helper {
  public:
    typedef BASIntrf_ptr _ptr_type;

    static _ptr_type _nil();
    static _CORBA_Boolean is_nil(_ptr_type);
    static void release(_ptr_type);
    static void duplicate(_ptr_type);
    static void marshalObjRef(_ptr_type, cdrStream&);
    static _ptr_type unmarshalObjRef(cdrStream&);
  };

  typedef _CORBA_ObjRef_Var<_objref_BASIntrf, BASIntrf_Helper> BASIntrf_var;
  typedef _CORBA_ObjRef_OUT_arg<_objref_BASIntrf,BASIntrf_Helper > BASIntrf_out;

#endif

  // interface BASIntrf
  class BASIntrf {
  public:
    // Declarations for this interface type.
    typedef BASIntrf_ptr _ptr_type;
    typedef BASIntrf_var _var_type;

    static _ptr_type _duplicate(_ptr_type);
    static _ptr_type _narrow(::CORBA::Object_ptr);
    static _ptr_type _unchecked_narrow(::CORBA::Object_ptr);
    
    static _ptr_type _nil();

    static inline void _marshalObjRef(_ptr_type, cdrStream&);

    static inline _ptr_type _unmarshalObjRef(cdrStream& s) {
      omniObjRef* o = omniObjRef::_unMarshal(_PD_repoId,s);
      if (o)
        return (_ptr_type) o->_ptrToObjRef(_PD_repoId);
      else
        return _nil();
    }

    static inline _ptr_type _fromObjRef(omniObjRef* o) {
      if (o)
        return (_ptr_type) o->_ptrToObjRef(_PD_repoId);
      else
        return _nil();
    }

    static _core_attr const char* _PD_repoId;

    // Other IDL defined within this scope.
    
  };

  class _objref_BASIntrf :
    public virtual ::CORBA::Object,
    public virtual omniObjRef
  {
  public:
    // IDL operations
    ::CORBA::Long getFloat(const char* tag, ::CORBA::Float& val);
    ::CORBA::Long getString(const char* tag, ::CORBA::String_out val);
    ::CORBA::Long getLong(const char* tag, ::CORBA::Long& val);
    ::CORBA::Long getFlag(const char* tag, ::CORBA::Long& val);
    ::CORBA::Long setFloat(const char* tag, ::CORBA::Float val);
    ::CORBA::Long setString(const char* tag, const char* val);
    ::CORBA::Long setLong(const char* tag, ::CORBA::Long val);
    ::CORBA::Long setFlag(const char* tag, ::CORBA::Long val);
    ::CORBA::Long pulseFlag(const char* tag, ::CORBA::Long msec);
    void getLastResponses(::IBAS::seq_IBAS_LastResponses_out IBAS_LastResponses);

    // Constructors
    inline _objref_BASIntrf()  { _PR_setobj(0); }  // nil
    _objref_BASIntrf(omniIOR*, omniIdentity*);

  protected:
    virtual ~_objref_BASIntrf();

    
  private:
    virtual void* _ptrToObjRef(const char*);

    _objref_BASIntrf(const _objref_BASIntrf&);
    _objref_BASIntrf& operator = (const _objref_BASIntrf&);
    // not implemented

    friend class BASIntrf;
  };

  class _pof_BASIntrf : public _OMNI_NS(proxyObjectFactory) {
  public:
    inline _pof_BASIntrf() : _OMNI_NS(proxyObjectFactory)(BASIntrf::_PD_repoId) {}
    virtual ~_pof_BASIntrf();

    virtual omniObjRef* newObjRef(omniIOR*,omniIdentity*);
    virtual _CORBA_Boolean is_a(const char*) const;
  };

  class _impl_BASIntrf :
    public virtual omniServant
  {
  public:
    virtual ~_impl_BASIntrf();

    virtual ::CORBA::Long getFloat(const char* tag, ::CORBA::Float& val) = 0;
    virtual ::CORBA::Long getString(const char* tag, ::CORBA::String_out val) = 0;
    virtual ::CORBA::Long getLong(const char* tag, ::CORBA::Long& val) = 0;
    virtual ::CORBA::Long getFlag(const char* tag, ::CORBA::Long& val) = 0;
    virtual ::CORBA::Long setFloat(const char* tag, ::CORBA::Float val) = 0;
    virtual ::CORBA::Long setString(const char* tag, const char* val) = 0;
    virtual ::CORBA::Long setLong(const char* tag, ::CORBA::Long val) = 0;
    virtual ::CORBA::Long setFlag(const char* tag, ::CORBA::Long val) = 0;
    virtual ::CORBA::Long pulseFlag(const char* tag, ::CORBA::Long msec) = 0;
    virtual void getLastResponses(::IBAS::seq_IBAS_LastResponses_out IBAS_LastResponses) = 0;
    
  public:  // Really protected, workaround for xlC
    virtual _CORBA_Boolean _dispatch(omniCallHandle&);

  private:
    virtual void* _ptrToInterface(const char*);
    virtual const char* _mostDerivedRepoId();
    
  };


  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_BASIntrf;

_CORBA_MODULE_END



_CORBA_MODULE POA_IBAS
_CORBA_MODULE_BEG

  class BASIntrf :
    public virtual IBAS::_impl_BASIntrf,
    public virtual ::PortableServer::ServantBase
  {
  public:
    virtual ~BASIntrf();

    inline ::IBAS::BASIntrf_ptr _this() {
      return (::IBAS::BASIntrf_ptr) _do_this(::IBAS::BASIntrf::_PD_repoId);
    }
  };

_CORBA_MODULE_END



_CORBA_MODULE OBV_IBAS
_CORBA_MODULE_BEG

_CORBA_MODULE_END





#undef _core_attr
#undef _dyn_attr

extern void operator<<=(::CORBA::Any& _a, const IBAS::IBAS_LastResponse& _s);
extern void operator<<=(::CORBA::Any& _a, IBAS::IBAS_LastResponse* _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, IBAS::IBAS_LastResponse*& _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const IBAS::IBAS_LastResponse*& _sp);

void operator<<=(::CORBA::Any& _a, const IBAS::seq_IBAS_LastResponses& _s);
void operator<<=(::CORBA::Any& _a, IBAS::seq_IBAS_LastResponses* _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, IBAS::seq_IBAS_LastResponses*& _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const IBAS::seq_IBAS_LastResponses*& _sp);

void operator<<=(::CORBA::Any& _a, const IBAS::EXC_TagNotFound& _s);
void operator<<=(::CORBA::Any& _a, const IBAS::EXC_TagNotFound* _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const IBAS::EXC_TagNotFound*& _sp);

void operator<<=(::CORBA::Any& _a, const IBAS::EXC_IncorrectTagType& _s);
void operator<<=(::CORBA::Any& _a, const IBAS::EXC_IncorrectTagType* _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const IBAS::EXC_IncorrectTagType*& _sp);

void operator<<=(::CORBA::Any& _a, IBAS::BASIntrf_ptr _s);
void operator<<=(::CORBA::Any& _a, IBAS::BASIntrf_ptr* _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, IBAS::BASIntrf_ptr& _s);



inline void
IBAS::BASIntrf::_marshalObjRef(::IBAS::BASIntrf_ptr obj, cdrStream& s) {
  omniObjRef::_marshal(obj->_PR_getobj(),s);
}



#ifdef   USE_stub_in_nt_dll_NOT_DEFINED_BASIntrf
# undef  USE_stub_in_nt_dll
# undef  USE_stub_in_nt_dll_NOT_DEFINED_BASIntrf
#endif
#ifdef   USE_core_stub_in_nt_dll_NOT_DEFINED_BASIntrf
# undef  USE_core_stub_in_nt_dll
# undef  USE_core_stub_in_nt_dll_NOT_DEFINED_BASIntrf
#endif
#ifdef   USE_dyn_stub_in_nt_dll_NOT_DEFINED_BASIntrf
# undef  USE_dyn_stub_in_nt_dll
# undef  USE_dyn_stub_in_nt_dll_NOT_DEFINED_BASIntrf
#endif

#endif  // __BASIntrf_hh__

