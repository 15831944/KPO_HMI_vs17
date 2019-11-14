// Copyright 2006 SMS - Demag AG

#ifndef _CMessageWriter_H_
#define _CMessageWriter_H_

//--------------------------------------------------------
#include "CMessageStack.h"
#include "CMessageForm.h"
#include "CStdConverter.h"
//--------------------------------------------------------
#include <string>
//--------------------------------------------------------
using namespace simulator;
using namespace System;
//--------------------------------------------------------
//-------------------------------------------
// Name:  CMessageWriter.h
// Descr: Wrapper fuer die Klasse CMessageStack.h
// Date:  
// Autor: Emeljanov Anatolij 
//--------------------------------------------
public ref class CMessageWriter
{
	public:
			CMessageWriter(CMessageForm^ txtBx);
			~CMessageWriter();
			void startWrite();
			void endWrite();
	private:
			CMessageForm^ TextBox;
			System::Threading::Thread^ TimerWriter;

			void write();
};
#endif
