// Copyright 2008 SMS - Demag AG
#include "StdAfx.h"
#include "CRecieveSzenario.h"
#include "CTimeWrapper.h"
#include "CFormatConverterWrapper.h"
#using <mscorlib.dll>

//----------------------------------------------------
CRecieveSzenario::CRecieveSzenario(CInterReceiverManager^ interMan,CInterConnection^ interCon,Thread^ th,String^ directoryPath)
{
	InterMan=interMan;
  InterCon = interCon;
  MainThread = th;
  isReceiveTlg=false;
  TlgWriter = nullptr;
	//System::Environment::GetEnvironmentVariable(S"XPACT_SMS_LOS")
  
  if (directoryPath)
  {
    LogFilePath = System::String::Concat(directoryPath,
		  "SimRec_",CTimeWrapper::getNowDateAndTimeForFilePath(),".log");
	  try
	  {
		  if (LogFilePath)
			  TlgWriter = gcnew System::IO::StreamWriter (LogFilePath);        
	  }
	  catch (System::IO::DirectoryNotFoundException^ e)
	  {
		  Console::WriteLine(e->Message);
		  Console::WriteLine("Es werden keine Telegramme in Log Datei gespeichert.");
    }
	}
  else
     Console::WriteLine("Es werden keine Telegramme in Log Datei gespeichert.");
}
//----------------------------------------------------
CRecieveSzenario::~CRecieveSzenario(void)
{
  //if (TlgWriter)
  //  TlgWriter->Close();
}
//----------------------------------------------------
//void CRecieveSzenario::closeLogFile()
//{
//	TlgWriter->Close();
//}
//----------------------------------------------------
void CRecieveSzenario::recieveTelegramms()
{

  //InterCon->receiveByteStream(

}
//----------------------------------------------------
void CRecieveSzenario::updateConnStatus()
{

}
//----------------------------------------------------
void CRecieveSzenario::updateConnStatus(String^ inter)
{
  if(!isReceiveTlg)
  {
    InterMan->receiveTlg();
    isReceiveTlg=true;
  }
}
//----------------------------------------------------
void CRecieveSzenario::showNewTelegram(CItemWrapper^ tlg)
{
  String^ body = nullptr;
  String^ name = tlg->getName();
  
  String^ time = CTimeWrapper::getNowTime();
  body = tlg->getSerialiseTlgAsString("|");
  String^ output = System::String::Concat(time," ",name," ",body);
  Console::WriteLine(System::String::Concat(output));

	if (TlgWriter)
	{
    TlgWriter->WriteLine(String::Concat(CTimeWrapper::getNowDate()," ",output,"  Comment: ",tlg->getTlgDescr()));
		TlgWriter->Flush();
	}

}
////----------------------------------------------------
//CRecieveSzenario::CRecieveScenario(CSzenarium^ szen,CInterConnection^ interCon,Thread^ th)
//{
//
//}
