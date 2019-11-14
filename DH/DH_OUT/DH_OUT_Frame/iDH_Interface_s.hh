// This file is generated by omniidl (C++ backend)- omniORB_4_2. Do not edit.
#ifndef __iDH__Interface_hh__
#define __iDH__Interface_hh__

#ifndef __CORBA_H_EXTERNAL_GUARD__
#include <omniORB4/CORBA.h>
#endif

#ifndef  USE_stub_in_nt_dll
# define USE_stub_in_nt_dll_NOT_DEFINED_iDH__Interface
#endif
#ifndef  USE_core_stub_in_nt_dll
# define USE_core_stub_in_nt_dll_NOT_DEFINED_iDH__Interface
#endif
#ifndef  USE_dyn_stub_in_nt_dll
# define USE_dyn_stub_in_nt_dll_NOT_DEFINED_iDH__Interface
#endif



#ifndef __iData__Provider_hh_EXTERNAL_GUARD__
#define __iData__Provider_hh_EXTERNAL_GUARD__
#include <iData_Provider_s.hh>
#endif
#ifndef __CBS__Common_hh_EXTERNAL_GUARD__
#define __CBS__Common_hh_EXTERNAL_GUARD__
#include <CBS_Common_s.hh>
#endif
#ifndef __iSMC__DataProvider_hh_EXTERNAL_GUARD__
#define __iSMC__DataProvider_hh_EXTERNAL_GUARD__
#include <iSMC_DataProvider_s.hh>
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



_CORBA_MODULE DH

_CORBA_MODULE_BEG

#ifndef __DH_miDH__Interface__
#define __DH_miDH__Interface__
  class iDH_Interface;
  class _objref_iDH_Interface;
  class _impl_iDH_Interface;
  
  typedef _objref_iDH_Interface* iDH_Interface_ptr;
  typedef iDH_Interface_ptr iDH_InterfaceRef;

  class iDH_Interface_Helper {
  public:
    typedef iDH_Interface_ptr _ptr_type;

    static _ptr_type _nil();
    static _CORBA_Boolean is_nil(_ptr_type);
    static void release(_ptr_type);
    static void duplicate(_ptr_type);
    static void marshalObjRef(_ptr_type, cdrStream&);
    static _ptr_type unmarshalObjRef(cdrStream&);
  };

  typedef _CORBA_ObjRef_Var<_objref_iDH_Interface, iDH_Interface_Helper> iDH_Interface_var;
  typedef _CORBA_ObjRef_OUT_arg<_objref_iDH_Interface,iDH_Interface_Helper > iDH_Interface_out;

#endif

  // interface iDH_Interface
  class iDH_Interface {
  public:
    // Declarations for this interface type.
    typedef iDH_Interface_ptr _ptr_type;
    typedef iDH_Interface_var _var_type;

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

  class _objref_iDH_Interface :
    public virtual _objref_iSMC_DataProvider
  {
  public:
    // IDL operations
    

    // Constructors
    inline _objref_iDH_Interface()  { _PR_setobj(0); }  // nil
    _objref_iDH_Interface(omniIOR*, omniIdentity*);

  protected:
    virtual ~_objref_iDH_Interface();

    
  private:
    virtual void* _ptrToObjRef(const char*);

    _objref_iDH_Interface(const _objref_iDH_Interface&);
    _objref_iDH_Interface& operator = (const _objref_iDH_Interface&);
    // not implemented

    friend class iDH_Interface;
  };

  class _pof_iDH_Interface : public _OMNI_NS(proxyObjectFactory) {
  public:
    inline _pof_iDH_Interface() : _OMNI_NS(proxyObjectFactory)(iDH_Interface::_PD_repoId) {}
    virtual ~_pof_iDH_Interface();

    virtual omniObjRef* newObjRef(omniIOR*,omniIdentity*);
    virtual _CORBA_Boolean is_a(const char*) const;
  };

  class _impl_iDH_Interface :
    public virtual _impl_iSMC_DataProvider
  {
  public:
    virtual ~_impl_iDH_Interface();

    
    
  public:  // Really protected, workaround for xlC
    virtual _CORBA_Boolean _dispatch(omniCallHandle&);

  private:
    virtual void* _ptrToInterface(const char*);
    virtual const char* _mostDerivedRepoId();
    
  };


  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_iDH_Interface;

_CORBA_MODULE_END



_CORBA_MODULE POA_DH
_CORBA_MODULE_BEG

  class iDH_Interface :
    public virtual DH::_impl_iDH_Interface,
    public virtual POA_iSMC_DataProvider
  {
  public:
    virtual ~iDH_Interface();

    inline ::DH::iDH_Interface_ptr _this() {
      return (::DH::iDH_Interface_ptr) _do_this(::DH::iDH_Interface::_PD_repoId);
    }
  };

_CORBA_MODULE_END



_CORBA_MODULE OBV_DH
_CORBA_MODULE_BEG

_CORBA_MODULE_END





#undef _core_attr
#undef _dyn_attr

void operator<<=(::CORBA::Any& _a, DH::iDH_Interface_ptr _s);
void operator<<=(::CORBA::Any& _a, DH::iDH_Interface_ptr* _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, DH::iDH_Interface_ptr& _s);



inline void
DH::iDH_Interface::_marshalObjRef(::DH::iDH_Interface_ptr obj, cdrStream& s) {
  omniObjRef::_marshal(obj->_PR_getobj(),s);
}



#ifdef   USE_stub_in_nt_dll_NOT_DEFINED_iDH__Interface
# undef  USE_stub_in_nt_dll
# undef  USE_stub_in_nt_dll_NOT_DEFINED_iDH__Interface
#endif
#ifdef   USE_core_stub_in_nt_dll_NOT_DEFINED_iDH__Interface
# undef  USE_core_stub_in_nt_dll
# undef  USE_core_stub_in_nt_dll_NOT_DEFINED_iDH__Interface
#endif
#ifdef   USE_dyn_stub_in_nt_dll_NOT_DEFINED_iDH__Interface
# undef  USE_dyn_stub_in_nt_dll
# undef  USE_dyn_stub_in_nt_dll_NOT_DEFINED_iDH__Interface
#endif

#endif  // __iDH__Interface_hh__

