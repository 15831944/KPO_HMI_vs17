// Copyright (C) 2006 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDH_IN_INTERFACE_IMPL_4582D78B0070_INCLUDED
#define _INC_CDH_IN_INTERFACE_IMPL_4582D78B0070_INCLUDED

#include "CSMC_DataProvider_Impl.h"
#include "iDH_Interface_s.hh"

//##ModelId=4582D78B0070
class CDH_IN_Interface_Impl 
: public CSMC_DataProvider_Impl
, public POA_DH::iDH_Interface
{
public:
	//##ModelId=4582D84D01AF
	CDH_IN_Interface_Impl();

	//##ModelId=4582D84E002A
	virtual ~CDH_IN_Interface_Impl();

};

#endif /* _INC_CDH_IN_INTERFACE_IMPL_4582D78B0070_INCLUDED */
