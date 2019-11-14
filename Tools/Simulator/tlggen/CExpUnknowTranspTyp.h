// Copyright 2006 SMS - Demag AG

#ifndef _CExpUnknowTranspTyp_H_
#define _CExpUnknowTranspTyp_H_

#include "CBaseExp.h"

//------------------------------------------------------
// Name:  CExpUnknownTranspTyp.h
// Descr: Exception dieser Klasse wird geworfen, wenn Taransporttyp
//        eines Telegrammelement nicht bekannt ist.
// Date:
// Autor: Emeljanov Anatolij 
//------------------------------------------------------
class CExpUnknownTranspTyp : public CBaseExp
{
  public:
    CExpUnknownTranspTyp(const std::string& trans,const std::string& tlg,const std::string& el);
    ~CExpUnknownTranspTyp();
    const std::string& getTranspTyp() const;
  private:
    std::string TranspTyp;
};
#endif
