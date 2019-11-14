// Copyright 2006 SMS - Demag AG
#ifndef _CExpTlgLenError_H_
#define _CExpTlgLenError_H_

#include "CBaseExp.h"
#include "CInterConfig.h"
//--------------------------------------------------------
// Name:  CExpTlgLenError.h
// Descr: Exception dieser Klasse wird geworfen, wenn die Lange
//        des Telegramms falsch ist
// Date:
// Autor: Emeljanov Anatolij 
//------------------------------------------------------
class CExpTlgLenError : public CBaseExp
{
	public:
		CExpTlgLenError(CInterConfig::LenTlgIdTyp lenTyp,const std::string& val,const std::string& tlg,const std::string& el);
		virtual ~CExpTlgLenError();
		const CInterConfig::LenTlgIdTyp& getLenTlgIdTyp();
		const std::string& getValue();
	private:
		CInterConfig::LenTlgIdTyp LenTyp;
		std::string Value;
};
#endif