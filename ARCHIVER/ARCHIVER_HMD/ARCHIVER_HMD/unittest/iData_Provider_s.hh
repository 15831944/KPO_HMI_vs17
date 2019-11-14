// This file is generated by omniidl (C++ backend)- omniORB_4_0. Do not edit.
#ifndef __iData__Provider_hh__
#define __iData__Provider_hh__

#ifndef USE_omniORB_logStream
#define USE_omniORB_logStream
#endif

#ifndef __CORBA_H_EXTERNAL_GUARD__
#include <omniORB4/CORBA.h>
#endif

#ifndef  USE_core_stub_in_nt_dll
# define USE_core_stub_in_nt_dll_NOT_DEFINED_iData__Provider
#endif
#ifndef  USE_dyn_stub_in_nt_dll
# define USE_dyn_stub_in_nt_dll_NOT_DEFINED_iData__Provider
#endif






#ifdef USE_stub_in_nt_dll
#ifndef USE_core_stub_in_nt_dll
#define USE_core_stub_in_nt_dll
#endif
#ifndef USE_dyn_stub_in_nt_dll
#define USE_dyn_stub_in_nt_dll
#endif
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





_CORBA_MODULE DEF

_CORBA_MODULE_BEG

  _CORBA_MODULE_VAR _core_attr const CORBA::Double Inv_Double;

  _CORBA_MODULE_VARINT const CORBA::Long Inv_Long _init_in_decl_( = -2147483647 );

  _CORBA_MODULE_VAR _core_attr const char * Inv_String;

  _CORBA_MODULE_VAR _core_attr const char * Undefined;

  _CORBA_MODULE_VAR _dyn_attr const CORBA::TypeCode_ptr _tc_seqLong;

  class seqLong_var;

  class seqLong : public _CORBA_Unbounded_Sequence_w_FixSizeElement< CORBA::Long, 4, 4 >  {
  public:
    typedef seqLong_var _var_type;
    inline seqLong() {}
    inline seqLong(const seqLong& _s)
      : _CORBA_Unbounded_Sequence_w_FixSizeElement< CORBA::Long, 4, 4 > (_s) {}

    inline seqLong(_CORBA_ULong _max)
      : _CORBA_Unbounded_Sequence_w_FixSizeElement< CORBA::Long, 4, 4 > (_max) {}
    inline seqLong(_CORBA_ULong _max, _CORBA_ULong _len, CORBA::Long* _val, _CORBA_Boolean _rel=0)
      : _CORBA_Unbounded_Sequence_w_FixSizeElement< CORBA::Long, 4, 4 > (_max, _len, _val, _rel) {}

  

    inline seqLong& operator = (const seqLong& _s) {
      _CORBA_Unbounded_Sequence_w_FixSizeElement< CORBA::Long, 4, 4 > ::operator=(_s);
      return *this;
    }
  };

  class seqLong_out;

  class seqLong_var {
  public:
    inline seqLong_var() : _pd_seq(0) {}
    inline seqLong_var(seqLong* _s) : _pd_seq(_s) {}
    inline seqLong_var(const seqLong_var& _s) {
      if( _s._pd_seq )  _pd_seq = new seqLong(*_s._pd_seq);
      else              _pd_seq = 0;
    }
    inline ~seqLong_var() { if( _pd_seq )  delete _pd_seq; }
      
    inline seqLong_var& operator = (seqLong* _s) {
      if( _pd_seq )  delete _pd_seq;
      _pd_seq = _s;
      return *this;
    }
    inline seqLong_var& operator = (const seqLong_var& _s) {
      if( _s._pd_seq ) {
        if( !_pd_seq )  _pd_seq = new seqLong;
        *_pd_seq = *_s._pd_seq;
      } else if( _pd_seq ) {
        delete _pd_seq;
        _pd_seq = 0;
      }
      return *this;
    }
    inline CORBA::Long& operator [] (_CORBA_ULong _s) {
      return (*_pd_seq)[_s];
    }

  

    inline seqLong* operator -> () { return _pd_seq; }
#if defined(__GNUG__)
    inline operator seqLong& () const { return *_pd_seq; }
#else
    inline operator const seqLong& () const { return *_pd_seq; }
    inline operator seqLong& () { return *_pd_seq; }
#endif
      
    inline const seqLong& in() const { return *_pd_seq; }
    inline seqLong&       inout()    { return *_pd_seq; }
    inline seqLong*&      out() {
      if( _pd_seq ) { delete _pd_seq; _pd_seq = 0; }
      return _pd_seq;
    }
    inline seqLong* _retn() { seqLong* tmp = _pd_seq; _pd_seq = 0; return tmp; }
      
    friend class seqLong_out;
    
  private:
    seqLong* _pd_seq;
  };

  class seqLong_out {
  public:
    inline seqLong_out(seqLong*& _s) : _data(_s) { _data = 0; }
    inline seqLong_out(seqLong_var& _s)
      : _data(_s._pd_seq) { _s = (seqLong*) 0; }
    inline seqLong_out(const seqLong_out& _s) : _data(_s._data) {}
    inline seqLong_out& operator = (const seqLong_out& _s) {
      _data = _s._data;
      return *this;
    }
    inline seqLong_out& operator = (seqLong* _s) {
      _data = _s;
      return *this;
    }
    inline operator seqLong*&()  { return _data; }
    inline seqLong*& ptr()       { return _data; }
    inline seqLong* operator->() { return _data; }

    inline CORBA::Long& operator [] (_CORBA_ULong _i) {
      return (*_data)[_i];
    }

  

    seqLong*& _data;

  private:
    seqLong_out();
    seqLong_out& operator=(const seqLong_var&);
  };

  _CORBA_MODULE_VAR _dyn_attr const CORBA::TypeCode_ptr _tc_seqDouble;

  class seqDouble_var;

  class seqDouble : public _CORBA_Unbounded_Sequence_w_FixSizeElement< CORBA::Double, 8, 8 >  {
  public:
    typedef seqDouble_var _var_type;
    inline seqDouble() {}
    inline seqDouble(const seqDouble& _s)
      : _CORBA_Unbounded_Sequence_w_FixSizeElement< CORBA::Double, 8, 8 > (_s) {}

    inline seqDouble(_CORBA_ULong _max)
      : _CORBA_Unbounded_Sequence_w_FixSizeElement< CORBA::Double, 8, 8 > (_max) {}
    inline seqDouble(_CORBA_ULong _max, _CORBA_ULong _len, CORBA::Double* _val, _CORBA_Boolean _rel=0)
      : _CORBA_Unbounded_Sequence_w_FixSizeElement< CORBA::Double, 8, 8 > (_max, _len, _val, _rel) {}

  

    inline seqDouble& operator = (const seqDouble& _s) {
      _CORBA_Unbounded_Sequence_w_FixSizeElement< CORBA::Double, 8, 8 > ::operator=(_s);
      return *this;
    }
  };

  class seqDouble_out;

  class seqDouble_var {
  public:
    inline seqDouble_var() : _pd_seq(0) {}
    inline seqDouble_var(seqDouble* _s) : _pd_seq(_s) {}
    inline seqDouble_var(const seqDouble_var& _s) {
      if( _s._pd_seq )  _pd_seq = new seqDouble(*_s._pd_seq);
      else              _pd_seq = 0;
    }
    inline ~seqDouble_var() { if( _pd_seq )  delete _pd_seq; }
      
    inline seqDouble_var& operator = (seqDouble* _s) {
      if( _pd_seq )  delete _pd_seq;
      _pd_seq = _s;
      return *this;
    }
    inline seqDouble_var& operator = (const seqDouble_var& _s) {
      if( _s._pd_seq ) {
        if( !_pd_seq )  _pd_seq = new seqDouble;
        *_pd_seq = *_s._pd_seq;
      } else if( _pd_seq ) {
        delete _pd_seq;
        _pd_seq = 0;
      }
      return *this;
    }
    inline CORBA::Double& operator [] (_CORBA_ULong _s) {
      return (*_pd_seq)[_s];
    }

  

    inline seqDouble* operator -> () { return _pd_seq; }
#if defined(__GNUG__)
    inline operator seqDouble& () const { return *_pd_seq; }
#else
    inline operator const seqDouble& () const { return *_pd_seq; }
    inline operator seqDouble& () { return *_pd_seq; }
#endif
      
    inline const seqDouble& in() const { return *_pd_seq; }
    inline seqDouble&       inout()    { return *_pd_seq; }
    inline seqDouble*&      out() {
      if( _pd_seq ) { delete _pd_seq; _pd_seq = 0; }
      return _pd_seq;
    }
    inline seqDouble* _retn() { seqDouble* tmp = _pd_seq; _pd_seq = 0; return tmp; }
      
    friend class seqDouble_out;
    
  private:
    seqDouble* _pd_seq;
  };

  class seqDouble_out {
  public:
    inline seqDouble_out(seqDouble*& _s) : _data(_s) { _data = 0; }
    inline seqDouble_out(seqDouble_var& _s)
      : _data(_s._pd_seq) { _s = (seqDouble*) 0; }
    inline seqDouble_out(const seqDouble_out& _s) : _data(_s._data) {}
    inline seqDouble_out& operator = (const seqDouble_out& _s) {
      _data = _s._data;
      return *this;
    }
    inline seqDouble_out& operator = (seqDouble* _s) {
      _data = _s;
      return *this;
    }
    inline operator seqDouble*&()  { return _data; }
    inline seqDouble*& ptr()       { return _data; }
    inline seqDouble* operator->() { return _data; }

    inline CORBA::Double& operator [] (_CORBA_ULong _i) {
      return (*_data)[_i];
    }

  

    seqDouble*& _data;

  private:
    seqDouble_out();
    seqDouble_out& operator=(const seqDouble_var&);
  };

  _CORBA_MODULE_VAR _dyn_attr const CORBA::TypeCode_ptr _tc_seqBoolean;

  class seqBoolean_var;

  class seqBoolean : public _CORBA_Unbounded_Sequence_Boolean {
  public:
    typedef seqBoolean_var _var_type;
    inline seqBoolean() {}
    inline seqBoolean(const seqBoolean& _s)
      : _CORBA_Unbounded_Sequence_Boolean(_s) {}

    inline seqBoolean(_CORBA_ULong _max)
      : _CORBA_Unbounded_Sequence_Boolean(_max) {}
    inline seqBoolean(_CORBA_ULong _max, _CORBA_ULong _len, CORBA::Boolean* _val, _CORBA_Boolean _rel=0)
      : _CORBA_Unbounded_Sequence_Boolean(_max, _len, _val, _rel) {}

  

    inline seqBoolean& operator = (const seqBoolean& _s) {
      _CORBA_Unbounded_Sequence_Boolean::operator=(_s);
      return *this;
    }
  };

  class seqBoolean_out;

  class seqBoolean_var {
  public:
    inline seqBoolean_var() : _pd_seq(0) {}
    inline seqBoolean_var(seqBoolean* _s) : _pd_seq(_s) {}
    inline seqBoolean_var(const seqBoolean_var& _s) {
      if( _s._pd_seq )  _pd_seq = new seqBoolean(*_s._pd_seq);
      else              _pd_seq = 0;
    }
    inline ~seqBoolean_var() { if( _pd_seq )  delete _pd_seq; }
      
    inline seqBoolean_var& operator = (seqBoolean* _s) {
      if( _pd_seq )  delete _pd_seq;
      _pd_seq = _s;
      return *this;
    }
    inline seqBoolean_var& operator = (const seqBoolean_var& _s) {
      if( _s._pd_seq ) {
        if( !_pd_seq )  _pd_seq = new seqBoolean;
        *_pd_seq = *_s._pd_seq;
      } else if( _pd_seq ) {
        delete _pd_seq;
        _pd_seq = 0;
      }
      return *this;
    }
    inline CORBA::Boolean& operator [] (_CORBA_ULong _s) {
      return (*_pd_seq)[_s];
    }

  

    inline seqBoolean* operator -> () { return _pd_seq; }
#if defined(__GNUG__)
    inline operator seqBoolean& () const { return *_pd_seq; }
#else
    inline operator const seqBoolean& () const { return *_pd_seq; }
    inline operator seqBoolean& () { return *_pd_seq; }
#endif
      
    inline const seqBoolean& in() const { return *_pd_seq; }
    inline seqBoolean&       inout()    { return *_pd_seq; }
    inline seqBoolean*&      out() {
      if( _pd_seq ) { delete _pd_seq; _pd_seq = 0; }
      return _pd_seq;
    }
    inline seqBoolean* _retn() { seqBoolean* tmp = _pd_seq; _pd_seq = 0; return tmp; }
      
    friend class seqBoolean_out;
    
  private:
    seqBoolean* _pd_seq;
  };

  class seqBoolean_out {
  public:
    inline seqBoolean_out(seqBoolean*& _s) : _data(_s) { _data = 0; }
    inline seqBoolean_out(seqBoolean_var& _s)
      : _data(_s._pd_seq) { _s = (seqBoolean*) 0; }
    inline seqBoolean_out(const seqBoolean_out& _s) : _data(_s._data) {}
    inline seqBoolean_out& operator = (const seqBoolean_out& _s) {
      _data = _s._data;
      return *this;
    }
    inline seqBoolean_out& operator = (seqBoolean* _s) {
      _data = _s;
      return *this;
    }
    inline operator seqBoolean*&()  { return _data; }
    inline seqBoolean*& ptr()       { return _data; }
    inline seqBoolean* operator->() { return _data; }

    inline CORBA::Boolean& operator [] (_CORBA_ULong _i) {
      return (*_data)[_i];
    }

  

    seqBoolean*& _data;

  private:
    seqBoolean_out();
    seqBoolean_out& operator=(const seqBoolean_var&);
  };

  _CORBA_MODULE_VAR _dyn_attr const CORBA::TypeCode_ptr _tc_seqString;

  class seqString_var;

  class seqString : public _CORBA_Unbounded_Sequence_String {
  public:
    typedef seqString_var _var_type;
    inline seqString() {}
    inline seqString(const seqString& _s)
      : _CORBA_Unbounded_Sequence_String(_s) {}

    inline seqString(_CORBA_ULong _max)
      : _CORBA_Unbounded_Sequence_String(_max) {}
    inline seqString(_CORBA_ULong _max, _CORBA_ULong _len, char** _val, _CORBA_Boolean _rel=0)
      : _CORBA_Unbounded_Sequence_String(_max, _len, _val, _rel) {}

  

    inline seqString& operator = (const seqString& _s) {
      _CORBA_Unbounded_Sequence_String::operator=(_s);
      return *this;
    }
  };

  class seqString_out;

  class seqString_var {
  public:
    inline seqString_var() : _pd_seq(0) {}
    inline seqString_var(seqString* _s) : _pd_seq(_s) {}
    inline seqString_var(const seqString_var& _s) {
      if( _s._pd_seq )  _pd_seq = new seqString(*_s._pd_seq);
      else              _pd_seq = 0;
    }
    inline ~seqString_var() { if( _pd_seq )  delete _pd_seq; }
      
    inline seqString_var& operator = (seqString* _s) {
      if( _pd_seq )  delete _pd_seq;
      _pd_seq = _s;
      return *this;
    }
    inline seqString_var& operator = (const seqString_var& _s) {
      if( _s._pd_seq ) {
        if( !_pd_seq )  _pd_seq = new seqString;
        *_pd_seq = *_s._pd_seq;
      } else if( _pd_seq ) {
        delete _pd_seq;
        _pd_seq = 0;
      }
      return *this;
    }
    inline _CORBA_String_element operator [] (_CORBA_ULong _s) {
      return (*_pd_seq)[_s];
    }

  

    inline seqString* operator -> () { return _pd_seq; }
#if defined(__GNUG__)
    inline operator seqString& () const { return *_pd_seq; }
#else
    inline operator const seqString& () const { return *_pd_seq; }
    inline operator seqString& () { return *_pd_seq; }
#endif
      
    inline const seqString& in() const { return *_pd_seq; }
    inline seqString&       inout()    { return *_pd_seq; }
    inline seqString*&      out() {
      if( _pd_seq ) { delete _pd_seq; _pd_seq = 0; }
      return _pd_seq;
    }
    inline seqString* _retn() { seqString* tmp = _pd_seq; _pd_seq = 0; return tmp; }
      
    friend class seqString_out;
    
  private:
    seqString* _pd_seq;
  };

  class seqString_out {
  public:
    inline seqString_out(seqString*& _s) : _data(_s) { _data = 0; }
    inline seqString_out(seqString_var& _s)
      : _data(_s._pd_seq) { _s = (seqString*) 0; }
    inline seqString_out(const seqString_out& _s) : _data(_s._data) {}
    inline seqString_out& operator = (const seqString_out& _s) {
      _data = _s._data;
      return *this;
    }
    inline seqString_out& operator = (seqString* _s) {
      _data = _s;
      return *this;
    }
    inline operator seqString*&()  { return _data; }
    inline seqString*& ptr()       { return _data; }
    inline seqString* operator->() { return _data; }

    inline _CORBA_String_element operator [] (_CORBA_ULong _i) {
      return (*_data)[_i];
    }

  

    seqString*& _data;

  private:
    seqString_out();
    seqString_out& operator=(const seqString_var&);
  };

_CORBA_MODULE_END

struct sIntfDataList {
  typedef _CORBA_ConstrType_Variable_Var<sIntfDataList> _var_type;

  
  CORBA::String_member Name;

  CORBA::String_member Type;



  void operator>>= (cdrStream &) const;
  void operator<<= (cdrStream &);
};

typedef sIntfDataList::_var_type sIntfDataList_var;

typedef _CORBA_ConstrType_Variable_OUT_arg< sIntfDataList,sIntfDataList_var > sIntfDataList_out;

_CORBA_GLOBAL_VAR _dyn_attr const CORBA::TypeCode_ptr _tc_sIntfDataList;

_CORBA_GLOBAL_VAR _dyn_attr const CORBA::TypeCode_ptr _tc_seqIntfDataList;

class seqIntfDataList_var;

class seqIntfDataList : public _CORBA_Unbounded_Sequence< sIntfDataList >  {
public:
  typedef seqIntfDataList_var _var_type;
  inline seqIntfDataList() {}
  inline seqIntfDataList(const seqIntfDataList& _s)
    : _CORBA_Unbounded_Sequence< sIntfDataList > (_s) {}

  inline seqIntfDataList(_CORBA_ULong _max)
    : _CORBA_Unbounded_Sequence< sIntfDataList > (_max) {}
  inline seqIntfDataList(_CORBA_ULong _max, _CORBA_ULong _len, sIntfDataList* _val, _CORBA_Boolean _rel=0)
    : _CORBA_Unbounded_Sequence< sIntfDataList > (_max, _len, _val, _rel) {}



  inline seqIntfDataList& operator = (const seqIntfDataList& _s) {
    _CORBA_Unbounded_Sequence< sIntfDataList > ::operator=(_s);
    return *this;
  }
};

class seqIntfDataList_out;

class seqIntfDataList_var {
public:
  inline seqIntfDataList_var() : _pd_seq(0) {}
  inline seqIntfDataList_var(seqIntfDataList* _s) : _pd_seq(_s) {}
  inline seqIntfDataList_var(const seqIntfDataList_var& _s) {
    if( _s._pd_seq )  _pd_seq = new seqIntfDataList(*_s._pd_seq);
    else              _pd_seq = 0;
  }
  inline ~seqIntfDataList_var() { if( _pd_seq )  delete _pd_seq; }
    
  inline seqIntfDataList_var& operator = (seqIntfDataList* _s) {
    if( _pd_seq )  delete _pd_seq;
    _pd_seq = _s;
    return *this;
  }
  inline seqIntfDataList_var& operator = (const seqIntfDataList_var& _s) {
    if( _s._pd_seq ) {
      if( !_pd_seq )  _pd_seq = new seqIntfDataList;
      *_pd_seq = *_s._pd_seq;
    } else if( _pd_seq ) {
      delete _pd_seq;
      _pd_seq = 0;
    }
    return *this;
  }
  inline sIntfDataList& operator [] (_CORBA_ULong _s) {
    return (*_pd_seq)[_s];
  }



  inline seqIntfDataList* operator -> () { return _pd_seq; }
#if defined(__GNUG__)
  inline operator seqIntfDataList& () const { return *_pd_seq; }
#else
  inline operator const seqIntfDataList& () const { return *_pd_seq; }
  inline operator seqIntfDataList& () { return *_pd_seq; }
#endif
    
  inline const seqIntfDataList& in() const { return *_pd_seq; }
  inline seqIntfDataList&       inout()    { return *_pd_seq; }
  inline seqIntfDataList*&      out() {
    if( _pd_seq ) { delete _pd_seq; _pd_seq = 0; }
    return _pd_seq;
  }
  inline seqIntfDataList* _retn() { seqIntfDataList* tmp = _pd_seq; _pd_seq = 0; return tmp; }
    
  friend class seqIntfDataList_out;
  
private:
  seqIntfDataList* _pd_seq;
};

class seqIntfDataList_out {
public:
  inline seqIntfDataList_out(seqIntfDataList*& _s) : _data(_s) { _data = 0; }
  inline seqIntfDataList_out(seqIntfDataList_var& _s)
    : _data(_s._pd_seq) { _s = (seqIntfDataList*) 0; }
  inline seqIntfDataList_out(const seqIntfDataList_out& _s) : _data(_s._data) {}
  inline seqIntfDataList_out& operator = (const seqIntfDataList_out& _s) {
    _data = _s._data;
    return *this;
  }
  inline seqIntfDataList_out& operator = (seqIntfDataList* _s) {
    _data = _s;
    return *this;
  }
  inline operator seqIntfDataList*&()  { return _data; }
  inline seqIntfDataList*& ptr()       { return _data; }
  inline seqIntfDataList* operator->() { return _data; }

  inline sIntfDataList& operator [] (_CORBA_ULong _i) {
    return (*_data)[_i];
  }



  seqIntfDataList*& _data;

private:
  seqIntfDataList_out();
  seqIntfDataList_out& operator=(const seqIntfDataList_var&);
};

#ifndef __iData__Provider__
#define __iData__Provider__

class iData_Provider;
class _objref_iData_Provider;
class _impl_iData_Provider;

typedef _objref_iData_Provider* iData_Provider_ptr;
typedef iData_Provider_ptr iData_ProviderRef;

class iData_Provider_Helper {
public:
  typedef iData_Provider_ptr _ptr_type;

  static _ptr_type _nil();
  static _CORBA_Boolean is_nil(_ptr_type);
  static void release(_ptr_type);
  static void duplicate(_ptr_type);
  static void marshalObjRef(_ptr_type, cdrStream&);
  static _ptr_type unmarshalObjRef(cdrStream&);
};

typedef _CORBA_ObjRef_Var<_objref_iData_Provider, iData_Provider_Helper> iData_Provider_var;
typedef _CORBA_ObjRef_OUT_arg<_objref_iData_Provider,iData_Provider_Helper > iData_Provider_out;

#endif

class iData_Provider {
public:
  // Declarations for this interface type.
  typedef iData_Provider_ptr _ptr_type;
  typedef iData_Provider_var _var_type;

  static _ptr_type _duplicate(_ptr_type);
  static _ptr_type _narrow(CORBA::Object_ptr);
  static _ptr_type _unchecked_narrow(CORBA::Object_ptr);
  static _ptr_type _nil();

  static inline void _marshalObjRef(_ptr_type, cdrStream&);

  static inline _ptr_type _unmarshalObjRef(cdrStream& s) {
    omniObjRef* o = omniObjRef::_unMarshal(_PD_repoId,s);
    if (o)
      return (_ptr_type) o->_ptrToObjRef(_PD_repoId);
    else
      return _nil();
  }

  static _core_attr const char* _PD_repoId;

  // Other IDL defined within this scope.
  
};

class _objref_iData_Provider :
  public virtual CORBA::Object, public virtual omniObjRef
{
public:
  CORBA::Any* getAny(const char* Key, const char* Name);
  void setAny(const char* Key, const char* Name, const CORBA::Any& NewAny);
  CORBA::Long getLong(const char* Key, const char* Name);
  void setLong(const char* Key, const char* Name, CORBA::Long value);
  void setDouble(const char* Key, const char* Name, CORBA::Double value);
  CORBA::Double getDouble(const char* Key, const char* Name);
  char* getString(const char* Key, const char* Name);
  void setString(const char* Key, const char* Name, const char* value);
  void setBoolean(const char* Key, const char* Name, CORBA::Boolean value);
  CORBA::Boolean getBoolean(const char* Key, const char* Name);
  void indicate(const char* Key);
  void complete(const char* Key, const char* Action);
  seqIntfDataList* getIntfDataList(const char* Key);
  seqIntfDataList* getRequestedIntfDataList(const char* Key);
  char* generateDataKey(const char* Value);
  char* getIntfDataType(const char* Key, const char* Name);

  inline _objref_iData_Provider()  { _PR_setobj(0); }  // nil
  _objref_iData_Provider(omniIOR*, omniIdentity*);

protected:
  virtual ~_objref_iData_Provider();

  
private:
  virtual void* _ptrToObjRef(const char*);

  _objref_iData_Provider(const _objref_iData_Provider&);
  _objref_iData_Provider& operator = (const _objref_iData_Provider&);
  // not implemented

  friend class iData_Provider;
};

class _pof_iData_Provider : public _OMNI_NS(proxyObjectFactory) {
public:
  inline _pof_iData_Provider() : _OMNI_NS(proxyObjectFactory)(iData_Provider::_PD_repoId) {}
  virtual ~_pof_iData_Provider();

  virtual omniObjRef* newObjRef(omniIOR*,omniIdentity*);
  virtual _CORBA_Boolean is_a(const char*) const;
};

class _impl_iData_Provider :
  public virtual omniServant
{
public:
  virtual ~_impl_iData_Provider();

  virtual CORBA::Any* getAny(const char* Key, const char* Name) = 0;
  virtual void setAny(const char* Key, const char* Name, const CORBA::Any& NewAny) = 0;
  virtual CORBA::Long getLong(const char* Key, const char* Name) = 0;
  virtual void setLong(const char* Key, const char* Name, CORBA::Long value) = 0;
  virtual void setDouble(const char* Key, const char* Name, CORBA::Double value) = 0;
  virtual CORBA::Double getDouble(const char* Key, const char* Name) = 0;
  virtual char* getString(const char* Key, const char* Name) = 0;
  virtual void setString(const char* Key, const char* Name, const char* value) = 0;
  virtual void setBoolean(const char* Key, const char* Name, CORBA::Boolean value) = 0;
  virtual CORBA::Boolean getBoolean(const char* Key, const char* Name) = 0;
  virtual void indicate(const char* Key) = 0;
  virtual void complete(const char* Key, const char* Action) = 0;
  virtual seqIntfDataList* getIntfDataList(const char* Key) = 0;
  virtual seqIntfDataList* getRequestedIntfDataList(const char* Key) = 0;
  virtual char* generateDataKey(const char* Value) = 0;
  virtual char* getIntfDataType(const char* Key, const char* Name) = 0;
  
public:  // Really protected, workaround for xlC
  virtual _CORBA_Boolean _dispatch(omniCallHandle&);

private:
  virtual void* _ptrToInterface(const char*);
  virtual const char* _mostDerivedRepoId();
};


_CORBA_GLOBAL_VAR _dyn_attr const CORBA::TypeCode_ptr _tc_iData_Provider;



_CORBA_MODULE POA_DEF
_CORBA_MODULE_BEG

_CORBA_MODULE_END

class POA_iData_Provider :
  public virtual _impl_iData_Provider,
  public virtual PortableServer::ServantBase
{
public:
  virtual ~POA_iData_Provider();

  inline ::iData_Provider_ptr _this() {
    return (::iData_Provider_ptr) _do_this(::iData_Provider::_PD_repoId);
  }
};





#undef _core_attr
#undef _dyn_attr

extern void operator <<= (CORBA::Any& _a, const DEF::seqLong& _s);
inline void operator <<= (CORBA::Any& _a, DEF::seqLong* _sp) {
  _a <<= *_sp;
  delete _sp;
}
extern _CORBA_Boolean operator >>= (const CORBA::Any& _a, DEF::seqLong*& _sp);
extern _CORBA_Boolean operator >>= (const CORBA::Any& _a, const DEF::seqLong*& _sp);

extern void operator <<= (CORBA::Any& _a, const DEF::seqDouble& _s);
inline void operator <<= (CORBA::Any& _a, DEF::seqDouble* _sp) {
  _a <<= *_sp;
  delete _sp;
}
extern _CORBA_Boolean operator >>= (const CORBA::Any& _a, DEF::seqDouble*& _sp);
extern _CORBA_Boolean operator >>= (const CORBA::Any& _a, const DEF::seqDouble*& _sp);

extern void operator <<= (CORBA::Any& _a, const DEF::seqBoolean& _s);
inline void operator <<= (CORBA::Any& _a, DEF::seqBoolean* _sp) {
  _a <<= *_sp;
  delete _sp;
}
extern _CORBA_Boolean operator >>= (const CORBA::Any& _a, DEF::seqBoolean*& _sp);
extern _CORBA_Boolean operator >>= (const CORBA::Any& _a, const DEF::seqBoolean*& _sp);

extern void operator <<= (CORBA::Any& _a, const DEF::seqString& _s);
inline void operator <<= (CORBA::Any& _a, DEF::seqString* _sp) {
  _a <<= *_sp;
  delete _sp;
}
extern _CORBA_Boolean operator >>= (const CORBA::Any& _a, DEF::seqString*& _sp);
extern _CORBA_Boolean operator >>= (const CORBA::Any& _a, const DEF::seqString*& _sp);

extern void operator<<=(CORBA::Any& _a, const sIntfDataList& _s);
extern void operator<<=(CORBA::Any& _a, sIntfDataList* _sp);
extern CORBA::Boolean operator>>=(const CORBA::Any& _a, sIntfDataList*& _sp);
extern CORBA::Boolean operator>>=(const CORBA::Any& _a, const sIntfDataList*& _sp);

extern void operator <<= (CORBA::Any& _a, const seqIntfDataList& _s);
inline void operator <<= (CORBA::Any& _a, seqIntfDataList* _sp) {
  _a <<= *_sp;
  delete _sp;
}
extern _CORBA_Boolean operator >>= (const CORBA::Any& _a, seqIntfDataList*& _sp);
extern _CORBA_Boolean operator >>= (const CORBA::Any& _a, const seqIntfDataList*& _sp);

void operator<<=(CORBA::Any& _a, iData_Provider_ptr _s);
void operator<<=(CORBA::Any& _a, iData_Provider_ptr* _s);
CORBA::Boolean operator>>=(const CORBA::Any& _a, iData_Provider_ptr& _s);



inline void
iData_Provider::_marshalObjRef(::iData_Provider_ptr obj, cdrStream& s) {
  omniObjRef::_marshal(obj->_PR_getobj(),s);
}




#ifdef   USE_core_stub_in_nt_dll_NOT_DEFINED_iData__Provider
# undef  USE_core_stub_in_nt_dll
# undef  USE_core_stub_in_nt_dll_NOT_DEFINED_iData__Provider
#endif
#ifdef   USE_dyn_stub_in_nt_dll_NOT_DEFINED_iData__Provider
# undef  USE_dyn_stub_in_nt_dll
# undef  USE_dyn_stub_in_nt_dll_NOT_DEFINED_iData__Provider
#endif

#endif  // __iData__Provider_hh__

