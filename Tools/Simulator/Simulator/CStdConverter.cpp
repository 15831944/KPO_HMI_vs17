// Copyright 2006 SMS - Demag AG
#include "stdafx.h"
#include "CStdConverter.h"
//------------------------------------------------
using namespace System::Runtime::InteropServices;
//------------------------------------------------
void CStdConverter::StringToStdStr(String^ netval,std::string& stdval)
{
  const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(netval)).ToPointer();
  stdval = chars;
  Marshal::FreeHGlobal(System::IntPtr((void*)chars));
}
//-------------------------------------------------
String^ CStdConverter::StdStrToString(const std::string& stdval)
{
  //if(!stdval.empty())
  return Marshal::PtrToStringAnsi(System::IntPtr((void*)stdval.c_str()));
  //else
  //return " ";
}
//-------------------------------------------------
void CStdConverter::FormatString(String^& str,int num)
{
  //std::string s_str("bbb");
  //s_str.clear();
  if(str)
  {
    int pos=-1;
    int len;
    pos=str->IndexOf(",");
    if(pos == -1)
    {
      pos=str->IndexOf(".");
    }
    if(pos != -1)
    {
      len=str->Length;
      if(pos+1+num < len)
      {
        str=str->Substring(0,pos+1+num);
      }
    }
  }
}
//-------------------------------------------------
