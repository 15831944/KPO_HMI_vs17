// Copyright 2006 SMS - Demag AG
//----------------------------------------------------
#include "stdafx.h"
#include "CLogWriterWrapper.h"
#include "CLogWriter.h"
#include "CFormatConverterWrapper.h"
#include "CExpWrapper.h"

#if !defined __CONSOLE__
#include "CAppSetting.h"           
#endif

//-----------------------------------------------------
CLogWriterWrapper::CLogWriterWrapper()
{
  writer = CLogWriter::getLogWriter();
}
//-----------------------------------------------------
CLogWriterWrapper::~CLogWriterWrapper()
{

}
//-----------------------------------------------------
void CLogWriterWrapper::removeNeedlessLogFiles()
{
  #if !defined __CONSOLE__
  //*****************************************************
  CAppSetting^ Sett = CAppSetting::getApp();
  int count;
  String^ path = CStdConverter::StdStrToString(writer->getPath());
  array <String^>^ names  = IO::Directory::GetFiles(path);
  String^ name  = nullptr;

  try
  {
    count= CFormatConverterWrapper::StringToInt(Sett->getMaxCountOfLogFiles());
  }
  catch (CExpWrapper^ e)
  {
    count = 10;
    Sett->setMaxCountOfLogFiles("10");
    String^ mess = "Max count of log file should be a integer data type. Count is setting up to 10";
    WriteMessage(MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  }
  if (count <= 0)
  {
    count = 10;
    Sett->setMaxCountOfLogFiles("10");
    String^ mess = "Max count of log file should be positive. Count is setting up to 10";
    WriteMessage(MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  }
  
	if (names->Length > count)
  {
    Collections::ArrayList^ liste = gcnew Collections::ArrayList();
    int index1 = -1;
    int index2 = -1;
    for (int i=0;i<names->Length;i++)
    {
      index1 = names[i]->IndexOf("Simulator");
      index2 = names[i]->LastIndexOf(".log");
      if ((index1 >= 0) && (index2 >8))
        liste->Add(names[i]);
    }
    //Sortieren
    liste->Sort();

    if (liste->Count > count)
    {
      for (int i=0;i<(liste->Count - count);i++)
      {
        name = safe_cast <String^> (liste[i]);
        try
        {
          IO::File::Delete(name);
          String^ mess = String::Concat("Log file <",path,"> deleted.");
          WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        }
        catch(...)
        {
          String^ mess = String::Concat("Log file <",path,"> can not delete.");
          WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        }
      }
    }
  }
  //*****************************************************
  #endif
}
//-----------------------------------------------------
void CLogWriterWrapper::WriteMessage(MessTyp typ,String^ message,String^ file,String^ function,int line,StackTrace^ stTrace,int stDepth)
{
  std::string str_mes = "";
  std::string str_source = "";
  //Message
  CStdConverter::StringToStdStr(message,str_mes);
  
  //Source
  System::Text::StringBuilder^ source = gcnew System::Text::StringBuilder();
  //String^ source = "";
  if (file)
    source->Append(String::Concat(" FILE: ",file));
  if (function)
    source->Append(String::Concat("; FUNCTION: ",function));
  source->Append(String::Concat("; LINE: ",CFormatConverterWrapper::IntToString(line)));
   //.NET - Output
  if (stTrace && stDepth >= 0)
  {
    Diagnostics::StackFrame^ sf; 
    //StDepth auf Gueltigkeit uberpruefen
    if (stDepth == 0 || stDepth > stTrace->FrameCount)
      stDepth = stTrace->FrameCount;

    source->Append("; .NET Output: ");
    for(int i =0; i< stDepth; i++ )
    {
      sf = stTrace->GetFrame(i);
      source->Append(String::Concat("->",sf->GetMethod()));
    }
    //source = source->Remove(source->Length - 2); 
  }
  CStdConverter::StringToStdStr(source->ToString(),str_source);
  //Write
  writer->WriteMessage((CLogWriter::MessTyp) typ, str_source,str_mes);
}
//-----------------------------------------------------
CLogWriterWrapper^ CLogWriterWrapper::getLogWriterWrapper()
{
  if (LogWriterWrapper == nullptr)
  {
    LogWriterWrapper = gcnew CLogWriterWrapper();
  }
  return LogWriterWrapper;
}
//-----------------------------------------------------
void CLogWriterWrapper::setPath(String^ path)
{
  std::string str_path = "";
  CStdConverter::StringToStdStr(path,str_path);
  writer->setPath(str_path);
}
//-----------------------------------------------------
void CLogWriterWrapper::setSettings(int size,bool info,bool warning,bool error)
{
  if (writer)
  {
    int size_ = size;
    if (size<=0)
      size_ = 20;
    writer->setSettings(size_,info,warning,error);
  }
}
//-----------------------------------------------------
void CLogWriterWrapper::ReadSettingsFromIniFile()
{
  #if !defined __CONSOLE__
  //*****************************************************       
  if (writer)
  {
    CAppSetting^ Sett = CAppSetting::getApp();
    array <String^>^ typs = Sett->getMessageTypsInLogFiles();
    int size;
    bool warning = true;
    bool error = true;
    bool info = true;

    try
    {
      size = CFormatConverterWrapper::StringToInt(Sett->getMaxSizeOfLogFiles());
    }
    catch (CExpWrapper^ e)
    {
      size = 20;
      Sett->setMaxSizeOfLogFiles("20");
      String^ mess = "Max size of log file should be a integer data type. Size is setting up to 20 MB";
      WriteMessage(MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    }
    if (size < 1)
    {
      size = 20;
      Sett->setMaxSizeOfLogFiles("20");
      String^ mess = "Max size of log file should be between 1 and 20 MB. Size is setting up to 20 MB";
      WriteMessage(MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    }

    if (typs[0]->Equals("0"))
      info = false;
    if (typs[1]->Equals("0"))
      warning = false;
    if (typs[2]->Equals("0"))
      error = false;

    setSettings(size,info,warning,error);
  }
  //*****************************************************       
  #endif
}