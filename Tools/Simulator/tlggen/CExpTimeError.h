// Copyright 2006 SMS - Demag AG
#ifndef _CExpTimeError_H_
#define _CExpTimeError_H_

#include "CExpBaseTimeError.h" 
#include <string>
//------------------------------------------------------
// Name:  CExpTimeError.h
// Descr: Exception dieser Klasse wird geworfen, wenn
//        Zeitformatfehler auftretten
// Date:
// Autor: Emeljanov Anatolij 
//------------------------------------------------------
class CExpTimeError : public CExpBaseTimeError
{
  public:
    CExpTimeError(const std::string& format,const std::string& time);
    ~CExpTimeError();
    const std::string& getTime();
  private:
    std::string Time;
};
#endif
