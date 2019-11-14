// Copyright 2008 SMS - Demag AG
#include "StdAfx.h"
#include "CTimeWrapper.h"
#include "CFormatConverterWrapper.h"
#include "CMessageWrite.h"
#include "CSendSzenario.h"
#include "CSendItemsServer.h"
#include "CLogWriterWrapper.h"

#using <mscorlib.dll>

CSendSzenario::CSendSzenario(String^ szenFile, System::Collections::ArrayList^ modelList,
                             CInterConnection^ interCon,Thread^ th)
{
  scen1 = nullptr;
	scen2 = nullptr;
	//Szenarium = szen;
  InterCon = interCon;
  MainThread = th;
	this->szenFile=szenFile;
	this->modelList=modelList;
	szenFileThread=nullptr;
	//SzenArrayList = gcnew System::Collections::ArrayList();
  firstSend=true;
  isAllSended = false;
}
//---------------------------------------------------------
void CSendSzenario::updateConnStatus(String^ inter)
{
  static int count = 1;
  
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,
                                            count.ToString(),__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  ++count;
  
  if (!isAllSended)
  {
    if(InterCon->isConnected())
    {
      isAllSended=true; 
      sendTelegramms(); 
      InterCon->disConnect();
    }
    if (MainThread->ThreadState == System::Threading::ThreadState::Suspended)
    {
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,
                                                "Wake main thread!",__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      MainThread->Resume();
    }
  } 
}
//--------------------------------------------------------
void CSendSzenario::readSzenFile(void)
{
  System::Threading::ThreadStart^ start = gcnew System::Threading::ThreadStart(this,&CSendSzenario::readSzenarioFileWithThread);
	szenFileThread = gcnew Thread(start);
	szenFileThread->Start();
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,
                                                        "Read szenario thread started!",__FILE__,__FUNCTION__,__LINE__,
                                                        gcnew Diagnostics::StackTrace(true),3);
}
//---------------------------------------------------------
//Liest 
void CSendSzenario::readSzenarioFileWithThread()
{
	String^ mess = nullptr;
  CLogWriterWrapper^ logWriter = CLogWriterWrapper::getLogWriterWrapper();
  int countTelegrammsTotal = 0;
  
  String^ line = nullptr;
	String^ delStr = " ";
	array <Char>^ delChar = delStr->ToCharArray();
	array <String^>^ items = nullptr;
	
  int diffTime = 0;

	String^ name=nullptr;
	double rel = 0;
	double t0;
  double d0=-1.0;
  
	bool firstSzenarium = true;
	//2 Szenario Obketen erzeugen
	/*scen1 = gcnew CSzenarium();
	scen2 = gcnew CSzenarium();*/
	
  try
  {
		mess = String::Concat("read of ",szenFile);
    logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    Console::WriteLine(mess);
    
    System::IO::StreamReader^ sr = gcnew System::IO::StreamReader(this->szenFile);
    Console::WriteLine();
    Console::WriteLine("Telegramms readed : ");
    Console::WriteLine("\n\n===================================================\n");

    CSzenarium::MessageScenarioDelTyp^ del = gcnew CSzenarium::MessageScenarioDelTyp(&CMessageWrite::writeMessage);

    //Name, Rel aus dem Szeanrio - Datei auslesen
		line = sr->ReadLine();
		items = line->Split(delChar);
		if(items->Length == 2)
			name = items[1];
		else
			name = "Unknow";
		line = sr->ReadLine();
		items = line->Split(delChar);
		if(items->Length == 2)
			rel = CFormatConverterWrapper::StringToDouble(items[1]);
		else
			rel = 1.0;
		line = sr->ReadLine();
		items = line->Split(delChar);
		if(items->Length == 2)
			t0 = CFormatConverterWrapper::StringToDouble(items[1]);
		else
			t0 = 0.0;

		bool ok = true;
    int partCount = 1;
		
    do
		{
			scen = gcnew CSzenarium();
			scen->setMessScenDel(del);
      //Console::WriteLine(String::Concat("Szenario Part ",System::Convert::ToString(partCount++)," : "));
      

      ////wenn 1.te Szenarium
      //if (partCount==1)
      //{
      //  ok = scen->readScenarioFromFileInPart(sr,modelList,1000,t0,name,rel,szenFile,d0,0);
      //}
      //else
      //{
      //  ok = scen->readScenarioFromFileInPart(sr,modelList,1000,t0,name,rel,szenFile,d0,diffTime);
      //}
      //


			ok = scen->readScenarioFromFileInPart(sr,modelList,50,t0,name,rel,szenFile,d0,0);

      countTelegrammsTotal+=scen->getSzenItemCount();

      //Ausgabe 
      mess = String::Concat(countTelegrammsTotal.ToString()," telegrams of szenario readed");
      logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      CMessageWrite::writeProgress(countTelegrammsTotal);
      
      ////Differenz im Szenarium berechnen
      //diffTime = (scen->getSzenItem(scen->getSzenItemCount())->getTime()) - (scen->getSzenItem(1)->getTime());
      ////Differenz mit Relation multiplizieren
      //diffTime*=rel;

			bool ok2 = true;
			do
			{
				if ((partCount % 2) == 0)
				{
					if (scen2)
					{
						System::Threading::Thread::CurrentThread->Sleep(1);
					}
					else
					{
						scen2 = scen;
						ok2 = false;
					}
				}
				else
				{
					if (scen1)
					{
						System::Threading::Thread::CurrentThread->Sleep(1);
					}
					else
					{
						scen1 = scen;
						ok2 = false;
					}
				}
			}
			while (ok2);
		
			partCount++;

     
      
      //-------

      /*Console::WriteLine();
			for (int i=1;i<=partCount-1;i++)
      {
        Console::Write(".");
      }*/
      //Warten, um die CPU - Vollauslastung zu vermeiden
      //System::Threading::Thread::get_CurrentThread()->Sleep(1);
      
		}
		while (ok);	

    sr->Close();
    mess = String::Concat(System::Convert::ToString(partCount-1)," " "parts of scenario was readed.");
    logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    CMessageWrite::writeMessage(mess);
    
    mess = String::Concat(countTelegrammsTotal.ToString()," tellegrams accepted.");
    logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    CMessageWrite::writeMessage(mess);
  }
  catch (Exception^ e)
  {
    mess = String::Concat("The file ",szenFile," could not be read:");
    logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    CMessageWrite::writeMessage(mess);
    logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,e->Message,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    CMessageWrite::writeMessage(e->Message);
  }
  /*szenFileThread->Abort();*/
}
//-----------------------------------------------------
void CSendSzenario::sendTelegramms()
{
  bool ok = true;
  CSzenItem^ item;
  int count;
  char* buffer;
  double delay;
  DateTime ActuelTime;
  DateTime StartTime;
  System::TimeSpan sendDelay;
  int sendDelayAsMili;
	bool firstSzenarium = true;
	int sendCount = 1;

  CSzenarium^ Szenarium=nullptr;
  
	do
  {
		//Wenn kein Szenarium abgeschickt wurde	
		if (firstSzenarium)
		{
			bool ok2 = true;
			do
			{
				if (scen1)
				{
						firstSzenarium = false;
						ok2=false;
						/*Console::WriteLine("Erste Tellegramm ist da");
						Console::ReadLine();*/
				}
				else
				{
					System::Threading::Thread::CurrentThread->Sleep(1);
				}
			}//end while
			while (ok2);
		}

		//gerade
		if ((sendCount % 2) == 0)
		{
			if (scen2)
			{
				Szenarium = scen2;
			}
			else
			{
				ok = false;
			}
		}
    //ungerade
		else
		{
			if (scen1)
			{
				Szenarium = scen1;
			}
			else
			{
				ok = false;
			}
		}
		
		if (ok)
		{
			count = Szenarium->getSzenItemCount();
    
			/*Console::WriteLine(String::Concat("Count : ",count.ToString()));*/
	    
			item = nullptr;
			/*count = 0;*/
			buffer = nullptr;
			
			StartTime = DateTime::Now;
			
			for(int i=1;i<=count;i++)
			{
				ActuelTime = DateTime::Now;
				item = Szenarium->getSzenItem(i);
				/*buffer = new char[item->getTlgTransBytesCount()*sizeof(char)];
				len = item->getSerializeTlg(buffer,item->getTlgTransBytesCount());*/
				delay = item->getDelay();
				if(InterCon->isConnected())
				{
					sendDelay = ActuelTime - StartTime;
					sendDelayAsMili = (int)(delay*1000 - sendDelay.TotalMilliseconds);
					if( sendDelayAsMili > 0)
						System::Threading::Thread::CurrentThread->Sleep(sendDelayAsMili); 
					
          CSendItemsServer::getSendItemsServer()->sendSzenItem(InterCon,item->getTlgWrapper(),false);
          //InterCon->sendByteStream((unsigned char*)buffer,len);
				}
				delete buffer;
			}
			firstSend = false;

			if ((sendCount % 2) == 0)
				scen2 = nullptr;
			else
				scen1 = nullptr;

			Szenarium = nullptr;

			sendCount++;

      count=0;
	
			//	else
			//    {
			//		if (firstSend)
			//      {
			//        System::Threading::Monitor::Exit(SzenArrayList);
			//        System::Threading::Thread::get_CurrentThread()->Sleep(1);
			//      }
			//      else
			//      {
			//        System::Threading::Monitor::Exit(SzenArrayList);
			//        ok = false;
			//        CMessageWrite::writeMessage("All parts of szenario was send!");
			//      }
			//    }
				//}
				//else
			//  {
				//	//Wenn ArrayListe mit Szenario besetzt ist, warten.
			//    System::Threading::Thread::get_CurrentThread()->Sleep(1);
			//  }
		}
  }
  while (ok);
}