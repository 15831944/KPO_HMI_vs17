// Copyright 2006 SMS - Demag AG
#ifndef _CExpConvertError_H_
#define _CExpConvertError_H_
//-------------------------------------------
#include <string>
//-------------------------------------------
#include "CBaseExp.h"
//------------------------------------------------------
// Name:  CExpBaseTimeError.h
// Descr: Diese Exception - Klasse wirde benutzt, wenn 
//        Konvertierung eines Wertes zu einem Datentyp fehlschlaegt
// Date:
// Autor: Emeljanov Anatolij 
//------------------------------------------------------
//##ModelId=4404D3B401A5
class CExpConvertError : public CBaseExp
{
	public:
	  //##ModelId=4404D3B401A7
	  CExpConvertError(const std::string& val,const std::string& type);
	  //##ModelId=4404D3B401B7
	  ~CExpConvertError();
	  //##ModelId=4404D3B401B8
	  const std::string& getValue();
	  //##ModelId=4404D3B401B9
	  const std::string& getType();
	private:
		//! fehlerhafte Wert
	  //##ModelId=441B250E0109
		std::string val;
		//! Typ, in dem den Wert konvertiert werden musste.
	  //##ModelId=441B250502EE
		std::string type;
};
#endif
