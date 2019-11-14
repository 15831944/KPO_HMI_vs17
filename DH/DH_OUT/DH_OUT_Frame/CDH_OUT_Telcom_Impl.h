// Copyright (C) 2006 SMS Demag AG Germany

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDH_OUT_TELCOM_IMPL_4586DDA9004C_INCLUDED
#define _INC_CDH_OUT_TELCOM_IMPL_4586DDA9004C_INCLUDED

#include "CSMC_DataProvider_Impl.h"
#include "iDH_Telcom_s.hh"

//##ModelId=4586DDA9004C
class CDH_OUT_Telcom_Impl 
: public CSMC_DataProvider_Impl
, public POA_DH_Telcom::iDH_Telcom
{
public:
	//##ModelId=4582D8E20205
	virtual long onComplete(const std::string & Key, const std::string & Action);

	//##ModelId=4582D964034C
	CDH_OUT_Telcom_Impl();

	//##ModelId=4582D965016D
	virtual ~CDH_OUT_Telcom_Impl();

};

#endif /* _INC_CDH_OUT_TELCOM_IMPL_4586DDA9004C_INCLUDED */
