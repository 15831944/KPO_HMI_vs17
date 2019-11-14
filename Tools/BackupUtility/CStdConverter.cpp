
#include "stdafx.h"
#include "CStdConverter.h"


using namespace System::Runtime::InteropServices;

//------------------------------------------------
void CStdConverter::StringToStdStr(String* netval,std::string& stdval)
{
    const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(netval)).ToPointer();
    stdval = chars;
    Marshal::FreeHGlobal(System::IntPtr((void*)chars));
}
//-------------------------------------------------
String* CStdConverter::StdStrToString(const std::string& stdval)
{
  return Marshal::PtrToStringAnsi(System::IntPtr((void*)stdval.c_str()));
}
//-------------------------------------------------