// Copyright 2008 SMS - Demag AG
#ifndef _CSendSzenario_H_
#define _CSendSzenario_H_

#include "stdafx.h"
#include "CInterConnection.h"
#include "CSzenarium.h"

#using <mscorlib.dll>

//-------------------------------------------
// Name:  CSendSzenario.h
// Descr: Send Szenario fuer die Sim - Konsole
// Date:
// Autor: Emeljanov Alexander 
//--------------------------------------------
//using namespace System;
//using namespace System::Collections;
//using namespace System::Threading;
//--------------------------------------------
ref class CSendSzenario
{
  public:
      CSendSzenario(String^ szenFile, System::Collections::ArrayList^ modelList,
                             CInterConnection^ interCon,Thread^ th);
      //Liest 
			void readSzenFile(void);
      void updateConnStatus(String^ inter);
     
  private:
			CSzenarium^ scen1;
			CSzenarium^ scen2;
			//System::Collections::ArrayList^ SzenArrayList;
			System::Collections::ArrayList^ modelList;
			CSzenarium^ scen;
			String^ szenFile;
			CInterConnection^ InterCon;
      Thread^ MainThread;
			Thread^ szenFileThread;
			bool firstSend;
      bool isAllSended;

      void readSzenarioFileWithThread();
      void sendTelegramms();
};
#endif