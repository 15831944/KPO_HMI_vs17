// Copyright 2006 SMS - Demag AG
//---------------------------------------------------------------------
#include "CExpInvalidTlg.h"
//---------------------------------------------------------------------
CExpInvalidTlg::CExpInvalidTlg(const std::string& tlg,const std::string& el,const std::string& err):
CBaseExp(tlg,el)
{
	this->ErrorMess = err;
}
//----------------------------------------------------------------------
CExpInvalidTlg::~CExpInvalidTlg()
{
}
//----------------------------------------------------------------------
const std::string& CExpInvalidTlg::getError()
{
	return this->ErrorMess;
}
//----------------------------------------------------------------------
