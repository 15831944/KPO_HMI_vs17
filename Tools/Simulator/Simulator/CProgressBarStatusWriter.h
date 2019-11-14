// Copyright 2007 SMS - Demag AG
#ifndef _CProgressBarStatusWriter_H_
#define _CProgressBarStatusWriter_H_
//--------------------------------------------------------
#include "CProgressInfoByFileLogRead.h"
#include "CProgressBarViewForm.h"
#include "CStdConverter.h"
#include <windows.h>
//--------------------------------------------------------
#include <string>
//--------------------------------------------------------
using namespace simulator;
using namespace System;


//-------------------------------------------
// Name:  CMessageWriter.h
// Descr: WrapperKlasse
// Date:  
// Autor: Emeljanov Alexander  
//--------------------------------------------
public ref class CProgressBarStatusWriter
{
	public:
    CProgressBarStatusWriter (CProgressBarViewForm^ view);
		~CProgressBarStatusWriter();
		void startWrite();
		void endWrite();
    /*long getData();*/
	private:
    System::Threading::Thread^ TimerWriter;
    void write();
   CProgressBarViewForm^ ProgressBarView;
   CProgressInfoByFileLogRead* InfoByFileLogRead;

};
#endif