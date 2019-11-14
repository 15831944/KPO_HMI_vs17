
#ifndef _CAppSetting_H_
#define _CAppSetting_H_

//-------------------------------------------------------------
#include "IniFile.h" 
//--------------------------------------------------------------
using namespace System;
//-------------------------------------------------------------
__gc class CAppSetting
{
	public:
				static CAppSetting* getApp();
				bool checkIniFile();
				void createIniFile();

        String* getIniFileName();

        bool setValue(String* Section , String* KeyName , String* Value);
        String* getValue(String* Section , String* KeyName);

        String* IniName;

	protected:
				CAppSetting();

	private:
				static CAppSetting* AppSetting=0;
};


#endif