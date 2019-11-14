// Copyright 2006 SMS - Demag AG
//-----------------------------------------------------------------
#include "CExpUnknowTranspTyp.h"
//--------------------------------------------------------------------
CExpUnknownTranspTyp::CExpUnknownTranspTyp(const std::string& trans,const std::string& tlg,const std::string& el):
CBaseExp(tlg,el)
{
  this->TranspTyp = trans;
}
//--------------------------------------------------------------------
CExpUnknownTranspTyp::~CExpUnknownTranspTyp()
{
}
//-------------------------------------------------------------------
const std::string& CExpUnknownTranspTyp::getTranspTyp() const
{
  return this->TranspTyp;
}
//-------------------------------------------------------------
