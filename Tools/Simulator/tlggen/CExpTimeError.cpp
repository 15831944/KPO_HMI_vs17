// Copyright 2006 SMS - Demag AG
//---------------------------------------------------------------------
#include "CExpTimeError.h"
//----------------------------------------------------------------------
CExpTimeError::CExpTimeError(const std::string& format,const std::string& time):
CExpBaseTimeError(format)
{
  this->Time = time;
}
//----------------------------------------------------------------------
CExpTimeError::~CExpTimeError()
{
}
//----------------------------------------------------------------------
const std::string& CExpTimeError::getTime()
{
  return this->Time;
}
//----------------------------------------------------------------------
