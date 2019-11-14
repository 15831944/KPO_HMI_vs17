// Copyright 2006 SMS - Demag AG
#ifndef _CExpUnknownElemTyp_H_
#define _CExpUnknownElemTyp_H_

#include "CBaseExp.h"

#include <string>
//------------------------------------------------------
// Name:  CExpTlgLenError.h
// Descr: Exception dieser Klasse wird geworfen, wenn die Lange
//        des Telegramms falsch ist
// Date:
// Autor: Emeljanov Anatolij 
//------------------------------------------------------
class CExpUnknownElemTyp : public CBaseExp
{
  public:
    CExpUnknownElemTyp(const std::string& unknowntype,const std::string& tlg,const std::string& el);
    ~CExpUnknownElemTyp();
    const std::string& getType() const;
  private:
		std::string type;
};
#endif


