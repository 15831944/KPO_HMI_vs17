// This is the main project file for VC++ application project 
// generated using an Application Wizard.

//-----------------------------------------------------------------
#include "stdafx.h"
#include "CTlgInterfaceWrapper.h"
#include "CInterConfigWrapper.h"
#include "CInterConnection.h"
#include "CXmlInterConnInfoOpen.h"
#include "CSzenarium.h"
#include "CInterSenderManager.h"
#include "CRecieveSzenario.h"
#include "CInterReceiverManager.h"
#include "CFormatConverterWrapper.h"
#include "CSendSzenario.h"
#include "CMessageWrite.h"
#include "CLogWriterWrapper.h"

#undef CreateDirectory

#using <mscorlib.dll>

using namespace System;
using namespace System::Collections;
using namespace System::Threading;

//-----------------------------------------------------------------
void writeHelp();
//-----------------------------------------------------------------

int _tmain(int argc,char** argv)
{
  bool isReciever = true;
  String^ mess = nullptr;
	CLogWriterWrapper^ logWriter = CLogWriterWrapper::getLogWriterWrapper();
  CSendSzenario^ sendScen=nullptr; 
  CTlgInterfaceWrapper^ model = nullptr; //fuer read Schnittstellenspezifikationsdatei
  CInterConfigWrapper^ confWr = nullptr; //fuer read Schnittstellenkonfigurationsdatei
  CInterConnectionListe^ conList = nullptr;

  int retVal = 0;
  int count,i,countReceive,countSender;
  String^ interFile = nullptr;
  String^ interConFile = nullptr;
  String^ interSockConFile = nullptr;
  String^ directoryPath = nullptr;
  String^ scenFile = nullptr;
  String^ val1 = nullptr;
  String^ val2 = nullptr;
  String^ errorStr=nullptr;
  ArrayList^ modelList = nullptr;
  //Parameter Counter
  countSender = 4*2+1;
  countReceive = 3*2+1;

  try
  {
    //Die Paramter, welche in der Console uebergeben wurden, aus dem String  - Array auslesen
    //Anhand der Parameter wird festgelegt, ob's Sender oder Reciever ist.
    if(argc == countSender || argc == countReceive)
    {
      count = argc;
      //init von Pfaede
      std::string str1;
      std::string str2;
      for(i=1;i<count-1;i=i+2)
      {
        str1 = (argv[i]); 
        str2 = (argv[i+1]); 
        val1 = CStdConverter::StdStrToString(str1);
        val2 = CStdConverter::StdStrToString(str2);
        
        
        //val1 = System::Convert::ToString (argv[i]);
        //val2 = System::Convert::ToString(argv[i+1]);
        if(val1->Equals("-inter"))
        {
            interFile = val2;
        }
        else if(val1->Equals("-config"))
        {
            interConFile = val2;
        }
        else if(val1->Equals("-con"))
        {
            interSockConFile = val2;
        }
        else if(val1->Equals("-scen"))
        {
            scenFile = val2;
            isReciever=false;
        }
        else if(val1->Equals("-dir"))
        {
          directoryPath = val2;
        }
      }
      //Pfad fuer LogWriter festlegen und entsprechende Ordner erzeugen
      String^ pathStartApp = pathStartApp=System::Reflection::Assembly::GetExecutingAssembly()->GetName()->CodeBase;
      // " file:///" entfernen
      pathStartApp=pathStartApp->Remove(0,8);
      //Slash Zeichen durch Backslash erstzen
      pathStartApp=pathStartApp->Replace("/","\\");
      pathStartApp=pathStartApp->Substring(0,pathStartApp->LastIndexOf("\\")+1);
      pathStartApp=String::Concat(pathStartApp,"Log\\");
      try
      {
        IO::Directory::CreateDirectory(pathStartApp);
        CLogWriterWrapper::getLogWriterWrapper()->setPath(pathStartApp);
      }
      catch (Exception^ ex)
      {
        logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,ex->Message,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      }
      //Wenn's Reciever ist, dann Ordner "Sim_Console" für Log Dateien erzeugen
      if (isReciever)
      {
        if (!directoryPath)
        {
          //plus Sim_Console
          directoryPath = String::Concat(pathStartApp,"Sim_Console\\"); 
        }
        //Ordner Sim_Console erzeugen, falls nicht vorhanden
        try
        {
          System::IO::Directory::CreateDirectory(directoryPath);
        }
        catch (System::Exception^ ex)
        {
          mess = String::Concat(directoryPath," : ",ex->Message);
          logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
          Console::WriteLine(mess);
          directoryPath=nullptr;
        }
      }

        //---lesen die Schnittstellenspezifikationsdatei
        Console::WriteLine(String::Concat("read of ",interFile));
        model = gcnew CTlgInterfaceWrapper();
        model->loadFromFile(interFile,false);
        errorStr = model->getErrorMessage();


      if(errorStr == nullptr)
      {
        //---lesen die Schnittstellenconfigurationsdatei
        Console::WriteLine(String::Concat("read of ",interConFile));
        confWr = gcnew CInterConfigWrapper();
        try
        {
          confWr->readInterConfigurationFile(model->getInterfaceName(),interConFile);
        }
        catch (Xml::XmlException^ e)
        {
          mess = String::Concat("Read of interface configuration failed. Error : ",e->Message);
          logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
          return 1;
        }

        //---lesen Socket - Verbindungsinfo
        Console::WriteLine(String::Concat("read of ",interSockConFile));
        conList = gcnew CInterConnectionListe();
        CInterConnection^ interCon = gcnew CInterConnection(model->getInterfaceName());
        conList->addInterface(interCon);
        CXmlInterConnInfoOpen^ xmlConReader = gcnew CXmlInterConnInfoOpen(conList);
        try
        {
          xmlConReader->readInterConnectionInfo(interSockConFile);
        }
        catch (...)
        {
          mess = "Read of connection file failed!";
          logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
          return 1;
        }
        
        //Wenn Sender 
        if (!isReciever)
        {
          //---erstellen Schnittstellen Manager
          CInterSenderManager^ interMan = gcnew CInterSenderManager(model,interCon);
          modelList = gcnew ArrayList();
          modelList->Add(interMan);

				  //Console::ReadLine(); Debug
  				
				  //---Aufbau der Socket - Verbindung         
          sendScen = gcnew CSendSzenario(scenFile,modelList,interCon,Thread::CurrentThread);
          
          //Szenario File mit Thraed auslesen
				  sendScen->readSzenFile();

				  ConnectionUpdateInterEventTyp^ updateSendConn = gcnew ConnectionUpdateInterEventTyp(sendScen,&CSendSzenario::updateConnStatus);
          interCon->addConnectionUpdateInterEvent(updateSendConn);
          //String * bla = Console::ReadLine();
          
          //Wenn die Verdindung erfolgreich aufgebaut wurde. 
          if(conList->buildConnection(1) == 0)
          {
            //"WaitingForConnection" wartet auf die Verbinung
            //Am Anfang ist der Status Waiting
            conList->getInterfaceAt(1)->waitingForConnection();
            
            //Hilfsvariable
            int counter = 0;
            //Return Wert zuerst auf 1 setzen, bedeutet "Fehler"
            retVal = 1;

            //While Schleife, schaut nacht, ob Status Connected ist, wenn nicht
            //wird eine Weile gewartet, das ganze wird solange wiederholt, bis's connected
            // ist oder counter > als 100 ist.
            while ((! conList->getInterfaceAt(1)->isConnected()) && (counter <= 100))
            {
              if (conList->getInterfaceAt(1)->isWaiting())
              {
                //es wird gewartet
                System::Threading::Thread::CurrentThread->Sleep(20);
              }
              else
              {
                counter = 100;
                mess = "Waiting for connection thread closed!";
                logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,__FILE__,__FUNCTION__,__LINE__,
                                        gcnew Diagnostics::StackTrace(true),3);
              }
              counter++;
            } // end while

              //Wenn connectet ist, dann return 0
              //MainThraed ins Status Suspend schicken
              if (conList->getInterfaceAt(1)->isConnected())
              {
                retVal = 0;
                mess = "Good luck!!!";
                CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,__FILE__,__FUNCTION__,__LINE__,
                                                          gcnew Diagnostics::StackTrace(true),3);
                Console::WriteLine(mess);
                System::Threading::Thread::CurrentThread->Suspend();
              }
          }
          else
          {
            mess = "Build connection failed!";
            Console::WriteLine(mess);
            CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,
                                                    gcnew Diagnostics::StackTrace(true),3);
          }
        }
        
        //Wenn Reciever
        else
        {
          //---erstellen Schnittstellen Manager
          CInterReceiverManager^ interMan = gcnew CInterReceiverManager(model,interCon);
          modelList = gcnew ArrayList();
          modelList->Add(interMan);

          CTlgContainerWrapper^ tlgCon = interMan->getTlgContainer();
          int tlgCount = 0;   
          int tlgCountTemp = 0;

          CRecieveSzenario^ recieveScen = gcnew CRecieveSzenario(interMan,interCon,Thread::CurrentThread,directoryPath);

          NewTlgEventTyp^ newTlgEvent = gcnew NewTlgEventTyp(recieveScen,&CRecieveSzenario::showNewTelegram);
          interMan->setNewTlgEvent(newTlgEvent);
          /*UpdateConnRecInfo* updateConnRecInfoEvent = gcnew UpdateConnRecInfo(recieveScen,&CRecieveSzenario::updateConnStatus);
          interMan->setUpdateConnRecInfo(updateConnRecInfoEvent);*/

          // //---Aufbau der Socket - Verbindung
          //ConnectionUpdateInterEventTyp* updateSendConn = gcnew ConnectionUpdateInterEventTyp(recieveScen,&CRecieveSzenario::updateConnStatus);
          //interCon->addConnectionUpdateInterEvent(updateSendConn);
   
          if(conList->buildConnection(1)==0)
          {
            mess = "Good luck!!!";
            logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
            Console::WriteLine(mess);
            recieveScen->updateConnStatus(" ");
					  System::Threading::Thread::CurrentThread->Sleep(4000);

            while (true)
            {
						  System::Threading::Thread::CurrentThread->Sleep(50);
              if (!interMan->isConnected() && !interMan->isWaiting())
						  {
							  mess = "Connection closed!";
                logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
                Console::WriteLine(mess);
							  System::Threading::Thread::CurrentThread->Sleep(2000);
							  break;
						  }
            } // end while

            retVal = 1;
          }
          else
          {
            mess = "Build connection failed!";
            logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
            Console::WriteLine(mess);   
          }
        }
      }
      else
      {
        //error
        String^ mess = String::Concat("Read of interface failed. Error : ",errorStr);
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,
                                                  gcnew Diagnostics::StackTrace(true),3);
        retVal = 1;

      }
    }
    else
    {
      writeHelp();
    }
  }
  catch (System::Exception^ e)
  {
    Console::WriteLine(String::Concat(e->Message,interFile));
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,e->Message,__FILE__,__FUNCTION__,__LINE__,
                                                  gcnew Diagnostics::StackTrace(true),3);
    return -1;
  }
  return retVal;
}
//--------------------------------------------------------------------------------
void writeHelp()
{
    String^ mess = nullptr;
    Console::WriteLine("=============================================");
    Console::WriteLine("       WRONG ARGUMENTS!                      ");
    Console::WriteLine("=============================================");
    Console::WriteLine("format (Sender,with -scen parameter) :");
    Console::WriteLine("-inter param1 -config param2 -con param3 -scen param4");
    Console::WriteLine("");
    Console::WriteLine(" param1 :  name of interface file (*.XML)");
    Console::WriteLine(" param2 :  name of interface configuration file (*.icnf)");
    Console::WriteLine(" param3 :  name of connection configuration file (*.ici)");
    Console::WriteLine(" param4 :  name of scenario file (*.szn)");
    Console::WriteLine("");
    Console::WriteLine("=============================================");
    Console::WriteLine("format (Reciever, without -scen parameter) :");
    Console::WriteLine("-inter param1 -config param2 -con param3 [-dir param4]");
    Console::WriteLine("");
    Console::WriteLine(" param1 :  name of interface file (*.XML)");
    Console::WriteLine(" param2 :  name of interface configuration file (*.icnf)");
    Console::WriteLine(" param3 :  name of connection configuration file (*.ici)");
    Console::WriteLine(" param4 :  directory for telegram log - file (optional)");
    Console::WriteLine("");
    Console::WriteLine("=============================================");
    Console::WriteLine(" return codes: 0 - OK");
    Console::WriteLine("               1 - ERROR");
    Console::WriteLine("=============================================");
}
//--------------------------------------------------------------------------------