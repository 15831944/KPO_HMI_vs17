// Copyright 2006 SMS - Demag AG
//------------------------------------------------------------------
#include "CExpUnknownElemTyp.h"
//-------------------------------------------------------------------
CExpUnknownElemTyp::CExpUnknownElemTyp(const std::string& unknowntype,const std::string& tlg,const std::string& el):
CBaseExp(tlg,el)
{
  this->type = unknowntype;
}
//-------------------------------------------------------------------
CExpUnknownElemTyp::~CExpUnknownElemTyp()
{
}
//--------------------------------------------------------------------
const std::string& CExpUnknownElemTyp::getType() const
{
  return this->type;
}
//--------------------------------------------------------------------
