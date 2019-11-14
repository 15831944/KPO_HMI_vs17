// Copyright (C) 2006 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDH_HMI_INTERFACE_IMPL_458672E201AC_INCLUDED
#define _INC_CDH_HMI_INTERFACE_IMPL_458672E201AC_INCLUDED

#include "CSMC_DataProvider_Impl.h"
#include "iDH_Interface_s.hh"

class CDH_HMI_Interface_Impl 
: public CSMC_DataProvider_Impl
, public POA_DH::iDH_Interface
{
protected:
  void beforeDataAccess(const std::string & Key,const std::string & Name);

};

#endif /* _INC_CDH_HMI_INTERFACE_IMPL_458672E201AC_INCLUDED */
