// Copyright 2006 SMS - Demag AG

#ifndef _CStdConverter_H_
#define _CStdConverter_H_
//-----------------------------------------
#include <string>
//----------------------------------------
using namespace System;
//----------------------------------------
//-------------------------------------------
// Name:  CStdConverter.h
// Descr: Konvert Datentyps zwischen .NET  und C++ Standard
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------  

 public ref class CStdConverter
{
	public:
        static  void StringToStdStr(String^ netval,std::string& stdval);
        static String^ StdStrToString(const std::string& stdval);
        static void FormatString(String^& str,int num);     
};

#endif
