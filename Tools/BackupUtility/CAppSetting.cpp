
#include "stdafx.h"
#include "CAppSetting.h"
#include "CStdConverter.h"
//--------------------------------------------------
CAppSetting::CAppSetting()
{
}
//--------------------------------------------------
CAppSetting* CAppSetting::getApp()
{
	if(AppSetting == 0)
    {
		AppSetting = new CAppSetting();
    
    String* path = System::Windows::Forms::Application::get_StartupPath();
		String* exeFile = System::Windows::Forms::Application::get_ExecutablePath();
		
    int pos = exeFile->LastIndexOf(S"\\");
		exeFile=exeFile->Substring(pos+1,exeFile->get_Length()-pos-1);
		pos = exeFile->LastIndexOf(S".");
		
    exeFile = String::Concat(exeFile->Substring(0,pos),".ini");
    path = System::String::Concat(path,S"\\",exeFile);

    AppSetting->IniName = path;
    }

	return AppSetting;
}
//--------------------------------------------------
bool CAppSetting::checkIniFile()
{
	return System::IO::File::Exists(IniName);
}
//--------------------------------------------------
String* CAppSetting::getIniFileName()
{
	int pos;
    String* ret = 0;

	pos = IniName->LastIndexOf(S"\\");
	ret = IniName->Substring(pos+1,IniName->get_Length()-pos-1);
	return ret;
}
//--------------------------------------------------
bool CAppSetting::setValue(String* Section , String* KeyName , String* Value)
{
  std::string stdIniName("");
  std::string stdSection("");
  std::string stdKeyName("");
  std::string stdValue("");

  CStdConverter::StringToStdStr(IniName,stdIniName);
  CStdConverter::StringToStdStr(Section,stdSection);
  CStdConverter::StringToStdStr(KeyName,stdKeyName);
  CStdConverter::StringToStdStr(Value,stdValue);

  return CIniFile::SetValue(stdKeyName,stdValue,stdSection,stdIniName);
}

void CAppSetting::createIniFile()
{
  std::string inipathstr("");
  CStdConverter::StringToStdStr(IniName,inipathstr);

	CIniFile::Create(inipathstr);
}

//--------------------------------------------------
String* CAppSetting::getValue(String* Section , String* KeyName)
{
  std::string stdReturn("");

  std::string stdIniName("");
  std::string stdSection("");
  std::string stdKeyName("");

  CStdConverter::StringToStdStr(IniName,stdIniName);
  CStdConverter::StringToStdStr(Section,stdSection);
  CStdConverter::StringToStdStr(KeyName,stdKeyName);

  stdReturn = CIniFile::GetValue(stdKeyName,stdSection,stdIniName);

  return CStdConverter::StdStrToString(stdReturn);
}
//--------------------------------------------------