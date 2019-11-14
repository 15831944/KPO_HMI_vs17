// Copyright 2009 SMS - Siemag AG

#ifndef _CLogWriterWrapper_H_
#define _CLogWriterWrapper_H_

//--------------------------------------------------------
#include "CStdConverter.h"
#include "CLogWriter.h"
//--------------------------------------------------------
#include <string>
//--------------------------------------------------------
//using namespace simulator;
using namespace System;
using namespace Diagnostics;
//--------------------------------------------------------
//-------------------------------------------
// Name:  CLogWriterWrapper.h
// Descr: Wrapper fuer die Klasse CLogWriter.h
// Date:  
// Autor: Emeljanov Alexander 
//--------------------------------------------
public ref class CLogWriterWrapper
{
	public:
    enum class MessTyp {Info,Warning,Error};
    
    static CLogWriterWrapper^ getLogWriterWrapper();
    void setPath(String^ path);
    void WriteMessage(MessTyp typ,String^ message,String^ file,String^ function,int line,StackTrace^ stTrace,int stDepth);
    void setSettings(int size,bool info,bool warning,bool error);
    void removeNeedlessLogFiles();
    void ReadSettingsFromIniFile();
		~CLogWriterWrapper();
  protected:
    CLogWriterWrapper();
	private:
    static CLogWriterWrapper^ LogWriterWrapper=nullptr;
    CLogWriter* writer;
};

//// Vergleichsklasse – Kriterium 'Wohnort'  
//private __gc class DateComparer : IComparer 
//{  
//  public int Compare(Object* x, object* y) 
//  {  
//    // prüfen auf null-Übergabe  
//    if(x == null && y == null) return 0;  
//    if(x == null) return 1;  
//    if(y == null) return –1;  
//    // Typüberprüfung  
//    
//    
//    
//    
//    if(x.GetType() != y.GetType())  
//      throw new ArgumentException("Ungültiger Vergleich");  
//    // Vergleich  
//    return ((Person)x).Wohnort.CompareTo(((Person)y).Wohnort);  
//  }  
//};  

#endif
