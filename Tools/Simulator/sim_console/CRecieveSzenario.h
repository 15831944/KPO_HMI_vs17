// Copyright 2008 SMS - Demag AG
#ifndef _CRecieveSzenario_H_
#define _CRecieveSzenario_H_

#include "stdafx.h"
#include "CTlgInterfaceWrapper.h"
#include "CInterConfigWrapper.h"
#include "CInterConnection.h"
#include "CXmlInterConnInfoOpen.h"
#include "CSzenarium.h"
#include "CInterSenderManager.h"
#include "CItemWrapper.h"
#include "CInterReceiverManager.h"
//-----------------------------------------------------------------
#using <mscorlib.dll>
//-------------------------------------------
// Name:  CRecieveSzenario.h
// Descr: Reciever Szenario fuer die Sim - Konsole
// Date:
// Autor: Emeljanov Alexander 
//--------------------------------------------
using namespace System;
using namespace System::Collections;
using namespace System::Threading;
//--------------------------------------------
public ref class CRecieveSzenario
{
public:
  /*void CRecieveScenario(CSzenarium^ szen,CInterConnection^ interCon,Thread^ th);*/
  void updateConnStatus();
  void updateConnStatus(String^ inter);
  void showNewTelegram(CItemWrapper^ tlg);
  CRecieveSzenario(CInterReceiverManager^ interMan,CInterConnection^ interCon,Thread^ th,String^ directoryPath);
  ~CRecieveSzenario(void);

private:
  CInterReceiverManager^ InterMan;
  CInterConnection^ InterCon;
	String^ LogFilePath;
	System::IO::StreamWriter^ TlgWriter;
  Thread^ MainThread;
  bool isReceiveTlg;

  void recieveTelegramms();
};
#endif
