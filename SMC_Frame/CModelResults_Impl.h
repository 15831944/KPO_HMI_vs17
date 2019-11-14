// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CMODELRESULTS_IMPL_454A1F0B02BE_INCLUDED
#define _INC_CMODELRESULTS_IMPL_454A1F0B02BE_INCLUDED

#include "iModelResults_s.hh"

#include "CSMC_DataProvider_Impl.h"

//##ModelId=454A1F0B02BE
class CModelResults_Impl 
: public CSMC_DataProvider_Impl
, public iModelResults
, public POA_iModelResults
{
public:
  CModelResults_Impl();

  virtual ~CModelResults_Impl();
};

#endif /* _INC_CMODELRESULTS_IMPL_454A1F0B02BE_INCLUDED */
