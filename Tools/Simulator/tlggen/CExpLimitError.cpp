// Copyright 2006 SMS - Demag AG
//------------------------------------------------------
#include "CExpLimitError.h"
//------------------------------------------------------
CExpLimitError::CExpLimitError(CInterConfig::LimitValueTyp lim,const std::string& min,
							   const std::string& max,const std::string& val,const std::string& tlg,const std::string& el):
CBaseExp(tlg,el)
{
	LimitTyp=lim;
	Min=min;
	Max=max;
	Value=val;
}
//------------------------------------------------------
CExpLimitError::~CExpLimitError()
{
}
//------------------------------------------------------
const CInterConfig::LimitValueTyp& CExpLimitError::getLimitValueTyp()
{
	return this->LimitTyp;
}
//------------------------------------------------------
const std::string& CExpLimitError::getMin()
{
	return this->Min;
}
//-------------------------------------------------------
const std::string& CExpLimitError::getMax()
{
	return this->Max;
}
//------------------------------------------------------
const std::string& CExpLimitError::getValue()
{
	return this->Value;
}
//------------------------------------------------------
