// Copyright 2006 SMS - Demag AG
#ifndef _CExpInvalidTlg_H_
#define _CExpInvalidTlg_H_

#include "CBaseExp.h"

//------------------------------------------------------
// Name:  CExpInvalidTlg.h
// Descr: Mit dieser Klasse werden Fehlern, die waehrend
//        der Bildung eines Telegramms entstehen, behandelt.
// Date:
// Autor: Emeljanov Anatolij 
//------------------------------------------------------

class CExpInvalidTlg : public CBaseExp
{
	public:
		CExpInvalidTlg(const std::string& tlg,const std::string& el,const std::string& err);
		~CExpInvalidTlg();
		const std::string& getError();
	private:
		std::string ErrorMess;
};
#endif
