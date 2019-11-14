

#ifndef _CStdConverter_H_
#define _CStdConverter_H_

#include <string>

using namespace System;


__gc class CStdConverter
{
	public:
		static void StringToStdStr(String* netval,std::string& stdval);
    static String* StdStrToString(const std::string& stdval);
};


#endif
