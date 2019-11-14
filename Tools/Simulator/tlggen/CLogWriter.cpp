// Copyright 2009 SMS - Siemag AG

//-----------------------------------------------
#include "CLogWriter.h"
#include <fstream>
#include "CFormatConverter.h"
#include <windows.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/stat.h>

//-----------------------------------------------
void CLogWriter::setSettings(int size,bool info,bool warning,bool error)
{
  this->maxSize = size*1048576;
  this->error = error;
  this->info = info;
  this->warning = warning;
}
//-----------------------------------------------
bool CLogWriter::checkMaxFileSize()
{
	struct stat buf; 
	stat(fullFileName.c_str(),&buf); 
	long size = buf.st_size;

	if (size>this->maxSize)
		return true;

	return false;
}
//-----------------------------------------------
void CLogWriter::createFileName()
{ 
  count++;
  GetLocalTime(&now);
  std::string date = CFormatConverter::IntToString(now.wDay) + "_" + CFormatConverter::IntToString(now.wMonth) 
					            + "_" + CFormatConverter::IntToString(now.wYear);
  std::string std_time = CFormatConverter::IntToString(now.wHour) + "_" + CFormatConverter::IntToString(now.wMinute) +
                          "_" + CFormatConverter::IntToString(now.wSecond);
  
  if (count < 2)
  {
    fileName="Simulator_" + date + "_" + std_time;
    fullFileName = path + fileName + ".log";
  }
  else
    fullFileName =path + fileName + "("+CFormatConverter::IntToString(count)+").log";
}
//-----------------------------------------------
CLogWriter::CLogWriter()
{
  maxSize = 20971520;
  error = true;
  info = true;
  warning = true;
  count = 0;
	writer = 0;
  InitializeCriticalSection(&sec);
}
//-----------------------------------------------
CLogWriter::~CLogWriter()
{
  DeleteCriticalSection(&sec);
  writer->close();
  delete writer;
	writer = 0;
}
//-----------------------------------------------
CLogWriter* CLogWriter::getLogWriter()
{
  if(LogWriter == 0)
  {
    LogWriter = new CLogWriter(); 
  }
  return LogWriter;
}
//-----------------------------------------------
void CLogWriter::setPath(const std::string& path)
{
	this->path=path;
	this->createFileName();
	writer = new std::ofstream(fullFileName.c_str());
}
//-----------------------------------------------
void CLogWriter::WriteMessage(MessTyp typ,std::string& message,char* file,char* func,long line)
{
  std::string file_std = file;
  file_std = file_std.erase(0,file_std.find_last_of("\\")+1);  
  std::string func_std = func;
  func_std = func_std.erase(0,func_std.find_last_of("::")+1);  
  std::string source = "FILE: " + file_std + "; FUNCTION: " + func_std + "; LINE: " + CFormatConverter::LongToString(line); 
  WriteMessage(typ,source,message);
}
//-----------------------------------------------
void CLogWriter::WriteMessage(MessTyp typ,std::string& source,std::string& message)
{
  bool ok = false;  
  if ((typ == Error && error) || (typ == Info && info) || (typ == Warning && warning))
    ok = true;

  //Wenn Ofstream Objekt erzeugt wurde
  if (writer && ok)
  {
    GetLocalTime(&now);
    //Zeitstempel
    std::string date = CFormatConverter::IntToString(now.wDay)+ "-" + CFormatConverter::IntToString(now.wMonth) 
                  + "-" + CFormatConverter::IntToString(now.wYear);
    std::string std_time = CFormatConverter::IntToString(now.wHour) + ":" + CFormatConverter::IntToString(now.wMinute)
                      + ":" + CFormatConverter::IntToString(now.wSecond) + "." + CFormatConverter::IntToString(now.wMilliseconds);
    
    //INFO,WARNING,ERROR
    std::string std_typ;
    if (typ == Error)
      std_typ = "E";
    else if (typ == Warning)
      std_typ = "W";
    else if (typ == Info)
      std_typ = "I";
    else
      std_typ = "O";
    
    // Request ownership of the critical section.
    EnterCriticalSection(&sec);
    //Schreiben in die Datei
    (*writer) << date + " " + std_time + "\t" + std_typ + " : " + message + "; " + source <<std::endl;
    //Puffer leeren
    (*writer).flush();
		//Ueberpruefen, ob die Max. Groesse der Datei erreicht wurde.
		if (checkMaxFileSize())
		{
			(*writer).close();
      createFileName();
			writer = new std::ofstream(fullFileName.c_str());
		}
	
    // Release ownership of the critical section.
    LeaveCriticalSection(&sec);
  }
}
//-----------------------------------------------
std::string CLogWriter::getPath()
{
  return path;
}
//-----------------------------------------------
CLogWriter* CLogWriter::LogWriter = 0; 
//-----------------------------------------------
