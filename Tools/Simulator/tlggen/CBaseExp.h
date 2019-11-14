// Copyright 2006 SMS - Demag AG

#ifndef _CBaseExp_H_
#define _CBaseExp_H_
//----------------------------------------------------------
#include <string>
//----------------------------------------------------------
//------------------------------------------------------
// Name:  CBaseExp.h
// Descr: Basisklasse aller Exeption - Klassen     
// Date:
// Autor: Emeljanov Anatolij 
//------------------------------------------------------
class CBaseExp 
{
	public:
		CBaseExp(const std::string& tel,const std::string& el):
		Tlg(tel),Elem(el)
		{
		}
		virtual ~CBaseExp() {}
		const std::string& getTlg() { return Tlg; }
    void setTlg(const std::string& tlg) {this->Tlg = tlg;}
		const std::string& getElem() { return Elem; }
		void setElem(const std::string& elem){this->Elem = elem;}
	protected:
		std::string Tlg;
		std::string Elem;
};

#endif 
