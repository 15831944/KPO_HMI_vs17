// Copyright 2006 SMS - Demag AG
//-------------------------------------------
#include "CExpUnknownTlg.h"
//--------------------------------------------
CExpUnknownTlg::CExpUnknownTlg(const std::string& name,const std::string& line):
CBaseExp(name,"")
{
  this->Line = line;
}
//----------------------------------------------
CExpUnknownTlg::~CExpUnknownTlg()
{
}
//----------------------------------------------
const std::string& CExpUnknownTlg::getLine()
{
  return this->Line;
}
//----------------------------------------------
