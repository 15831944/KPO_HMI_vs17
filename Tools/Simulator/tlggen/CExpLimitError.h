// Copyright 2006 SMS - Demag AG
#ifndef _CExpLimitError_H_
#define _CExpLimitError_H_
//-------------------------------------------
#include "CBaseExp.h"
#include "CInterConfig.h"
//-------------------------------------------
//------------------------------------------------------
// Name:  CExpLimitError.h
// Descr: Exception dieser Klasse wird ausgeloest, wenn der 
//        Wert eines Telegrammelements ausserhalb des definierten
//        Grenzbereich liegt.
// Date:
// Autor: Emeljanov Anatolij 
//------------------------------------------------------
class CExpLimitError : public CBaseExp
{
	public:
		CExpLimitError(CInterConfig::LimitValueTyp lim,const std::string& min,const std::string& max,
		const std::string& val,const std::string& tlg,const std::string& el);
		virtual ~CExpLimitError();

		const CInterConfig::LimitValueTyp& getLimitValueTyp();
		const std::string& getMin();
		const std::string& getMax();
		const std::string& getValue(); 
	private:
		//! Definition der Handhabung der Grenzwerten
		CInterConfig::LimitValueTyp LimitTyp;
		//! minimale Granze
		std::string Min;
		//! maximale Grenze
		std::string Max;
		//! Wert des Telegrammelements
		std::string Value;
};
#endif