// Copyright 2006 SMS - Demag AG

//--------------------------------------------------------------------
#ifndef _CFormatConverte_H_
#define _CFormatConverte_H_

#pragma warning( disable : 4290 )

#include "CExpConvertError.h"
#include <string>

//--------------------------------------------------------------------
// Name:  CTlgElem
// Descr: Konvertiert ein Wert von einem Datentyp nach andere Datentyp.
//        Wenn Konvertierung fehlschlaegt, wird eine Exception von Typ
//        CExpConvertError geworfen.
// Date:
// Autor: Emeljanov Anatolij 
//---------------------------------------------------------------------

class CFormatConverter
{
	public:
		static long StringToLong(const std::string& val) throw(CExpConvertError);
		static int StringToInt(const std::string& val) throw(CExpConvertError);
    static unsigned short int StringToShortInt(const std::string& val) throw (CExpConvertError);
    static int StringToInt(const std::string& val,int len) throw (CExpConvertError);
		static double StringToDouble(const std::string& val) throw(CExpConvertError);
		static float StringToFloat(const std::string& val) throw (CExpConvertError);
    static std::string IntToString(const int val);
		static std::string LongToString(const long val);
    static std::string DoublToString(const double val);
    static std::string FloatToString(const float val);
		static void CheckDelimeter(std::string& val);
};
#endif
