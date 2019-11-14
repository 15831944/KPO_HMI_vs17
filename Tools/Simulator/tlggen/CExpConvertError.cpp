// Copyright 2006 SMS - Demag AG
#include "CExpConvertError.h"

//--------------------------------------------------------------------------------
//##ModelId=4404D3B401A7
CExpConvertError::CExpConvertError(const std::string& val,const std::string& type):
CBaseExp("","")
{
	this->val = val;
	this->type = type;
}
//--------------------------------------------------------------------------------
//##ModelId=4404D3B401B8
const std::string& CExpConvertError::getValue()
{
	return this->val;
}
//--------------------------------------------------------------------------------
//##ModelId=4404D3B401B9
const std::string& CExpConvertError::getType()
{
	return this->type;
}
//--------------------------------------------------------------------------------
//##ModelId=4404D3B401B7
CExpConvertError::~CExpConvertError()
{
}
//--------------------------------------------------------------------------------
