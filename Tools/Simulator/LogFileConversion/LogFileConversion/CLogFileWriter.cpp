
#include "stdafx.h"
#include "CLogFileWriter.h"
//-----------------------------------------------------
using namespace System;
using namespace System::Windows::Forms;
//-----------------------------------------------------
CLogFileWriter::CLogFileWriter()
{
    int pos;
    String^ path;
    path = Application::ExecutablePath;
    pos=path->LastIndexOf(".");
    path = String::Concat(path->Substring(0,pos+1),"log");
       
    System::IO::File::Delete(path);
    Writer = gcnew System::IO::StreamWriter(path);
}
//-----------------------------------------------------
CLogFileWriter::~CLogFileWriter()
{
}
//-----------------------------------------------------
CLogFileWriter^ CLogFileWriter::getLogFileWriter()
{
  if(LogFileWriter == nullptr)
  {
    LogFileWriter = gcnew CLogFileWriter();
  }
  return LogFileWriter;
}
//-----------------------------------------------------
void CLogFileWriter::writeMessage(String^ mess)
{
    Writer->WriteLine(mess);
    //System::IO::StreamWriter* sw = new System::IO::StreamWriter(path);
}
//-----------------------------------------------------