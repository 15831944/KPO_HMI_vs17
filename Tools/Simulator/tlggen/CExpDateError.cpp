// Copyright 2006 SMS - Demag AG
//------------------------------------------------------------------
#include "CExpDateError.h"
//-------------------------------------------------------------------
//##ModelId=4404D3B40196
CExpDateError::CExpDateError(const std::string& format,const std::string& date):
CExpBaseTimeError(format)
{
  this->Date = date;
}
//-------------------------------------------------------------------
//##ModelId=4404D3B40199
CExpDateError::~CExpDateError()
{
}
//-------------------------------------------------------------------
//##ModelId=4404D3B4019A
const std::string& CExpDateError::getDate()
{
  return this->Date;
}
//-------------------------------------------------------------------
