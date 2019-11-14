// Copyright 2006 SMS - Demag AG

#ifndef _CExpBaseTimeError_H_
#define _CExpBaseTimeError_H_

//-----------------------------------------------------
#include <string>
//------------------------------------------------------
// Name:  CExpBaseTimeError.h
// Descr: Basisklasse fuer CExpDateError und CExpTimeError     
// Date:
// Autor: Emeljanov Anatolij 
//------------------------------------------------------
class CExpBaseTimeError
{
  public:
    CExpBaseTimeError(const std::string& Format);
    virtual ~CExpBaseTimeError();
    const std::string& getFormat();
  private:
    std::string Format;
};

#endif
