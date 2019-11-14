// Copyright 2006 SMS - Demag AG
#ifndef _CExpUnknownTlg_H_
#define _CExpUnknownTlg_H_

#include "CBaseExp.h"
#include <string>

//------------------------------------------------------
// Name:  CExpUnknownTlg.h
// Descr: Exception dieser Klasse wird geworfen, wenn das nachfragende
//        Telegramm bei der Schnittstelle nicht bekannt ist
// Date:
// Autor: Emeljanov Anatolij 
//------------------------------------------------------
class CExpUnknownTlg : public CBaseExp
{
  public:
    CExpUnknownTlg(const std::string& tlg,const std::string& line);
    ~CExpUnknownTlg();
    const std::string& getLine();
  private:
    std::string Line;
};
#endif 
