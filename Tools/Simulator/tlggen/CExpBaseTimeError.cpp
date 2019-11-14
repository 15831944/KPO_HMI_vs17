// Copyright 2006 SMS - Demag AG

#include "CExpBaseTimeError.h"

//-----------------------------------------------------------
CExpBaseTimeError::CExpBaseTimeError(const std::string& format):
Format(format)
{
}
//-----------------------------------------------------------
CExpBaseTimeError::~CExpBaseTimeError()
{
}
//-----------------------------------------------------------
const std::string& CExpBaseTimeError::getFormat()
{
    return this->Format;
}
//-----------------------------------------------------------
