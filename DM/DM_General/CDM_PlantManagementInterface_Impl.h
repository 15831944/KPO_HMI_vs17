// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_PLANTMANAGEMENTINTERFACE_IMPL_416A96F600FB_INCLUDED
#define _INC_CDM_PLANTMANAGEMENTINTERFACE_IMPL_416A96F600FB_INCLUDED

#include "iDM_Interface_s.hh"
#include "iEventData_s.hh"

#include "CSMC_DataProvider_Impl.h"

class CDM_PlantManagementInterface_Impl 
  : public CSMC_DataProvider_Impl
  , public POA_DM::iDM_Interface
{
public:
  virtual ::CORBA::Boolean setProductFromTreatmentPos(const char* TreatmentPosition, ::sEventData_out EventData);
};

#endif /* _INC_CDM_PLANTMANAGEMENTINTERFACE_IMPL_416A96F600FB_INCLUDED */
