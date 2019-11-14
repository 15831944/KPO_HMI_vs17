// Copyright 2006 SMS - Demag AG

#ifndef _CTimeWrapper_H_
#define _CTimeWrapper_H_

//------------------------------------------------
#include "CTelTime.h"
//------------------------------------------------

//------------------------------------------------
using namespace System;
//-------------------------------------------------
//-------------------------------------------
// Name:  CTlgTimeWrapper.h
// Descr: Wrapper fuer die Klasse CTelTime
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
public ref class CTimeWrapper
{
	public:
			CTimeWrapper();
			~CTimeWrapper();
			CTimeWrapper^ clone();
			void setTime(CTelTime* tm);
			void setDate(String^ date);
			void setTime(String^ time);
			bool isGreater(CTimeWrapper^ tm);
			CTelTime* getTime();
			double getDifferenzTimeAsSecond(CTimeWrapper^ tm);
            static String^ getNowTime();
						static String^ getNowDate();
						static String^ getNowDateAndTimeForFilePath();
	private:
		CTelTime* Time;
    

};



#endif
