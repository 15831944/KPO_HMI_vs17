// Copyright 2006 SMS - Demag AG
//--------------------------------------------------------
#include "CExpTlgLenError.h"
//--------------------------------------------------------
CExpTlgLenError::CExpTlgLenError(CInterConfig::LenTlgIdTyp lenTyp,const std::string& val,const std::string& tlg,const std::string& el):
CBaseExp(tlg,el)
{
	this->LenTyp = lenTyp;
	this->Value = val;
}
//--------------------------------------------------------
CExpTlgLenError:: ~CExpTlgLenError()
{
}
//--------------------------------------------------------
const CInterConfig::LenTlgIdTyp& CExpTlgLenError::getLenTlgIdTyp()
{
	return this->LenTyp;
}
//--------------------------------------------------------
const std::string& CExpTlgLenError::getValue()
{
	return this->Value;
}
//--------------------------------------------------------