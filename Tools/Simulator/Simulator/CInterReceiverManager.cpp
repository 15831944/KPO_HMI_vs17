// Copyright 2006 SMS - Demag AG

//------------------------------------------------------------------
#include "stdafx.h"
#include "CInterReceiverManager.h"
#include "CLogWriterWrapper.h"
//-------------------------------------------------------------------
CInterReceiverManager::CInterReceiverManager(CTlgInterfaceWrapper^ InterMap,CInterConnection^ interConSock):
CInterBaseManager(InterMap,interConSock)
{
  TlgContainer = gcnew CTlgContainerWrapper();
  ReceiverThread = nullptr;
  NewTlgEvent = nullptr;
}
//-------------------------------------------------------------------
CTlgContainerWrapper^ CInterReceiverManager::getTlgContainer()
{
  return TlgContainer;
}
//-------------------------------------------------------------------
void CInterReceiverManager::setNewTlgEvent(NewTlgEventTyp^ event)
{
  NewTlgEvent = event;
}

void CInterReceiverManager::setUpdateConnRecInfo(UpdateConnRecInfo^ event)
{
  RecInfo=event;
}
//-------------------------------------------------------------------
void CInterReceiverManager::receiveTlg()
{
  static int count = 0;
  ++count;
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,count.ToString(),
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  
  //endReceive();
  String^ conTyp = InterConn->getConnType();
  int retValue;
  if (conTyp)
  {
    StartRecieveInterEventTyp^ updateRec = gcnew StartRecieveInterEventTyp(this,&CInterReceiverManager::receive);
    InterConn->setRecieveUpdateInterEvent(updateRec);
    if(conTyp->Equals("Server"))
    {
      try
      {
        bool ok = true;
        #if defined __CONSOLE__
          ok = false;
          retValue = 0;
        #endif
        if (ok)
          retValue = InterConn->buildConnAsServer();
       }
      catch (SocketException^ e)
      {
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,e->Message,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
				if (MessageHandler)
          MessageHandler->Invoke(e->Message,2); 
        retValue = -3;
      }
      
      if (retValue>=0)
      {
       InterConn->waitingForConnection();
      }
    }
    else
    {
      if(conTyp->Equals("Client"))
      {
        retValue = InterConn->buildConnAsClient();
        if (retValue >= 0)
          InterConn->waitingForConnection();
      }
    }
    //Aus die Return-Werte reagieren
    if (retValue == -1)   
    {
      String^ Mess;
      Mess = "Undefined IP address(interface <" + InterConn->getInterName() +  ">). Configure first!";
			CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,Mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      if(MessageHandler)
        MessageHandler->Invoke(Mess,2); 
    }
    else if (retValue == -2)
    {
      String^ Mess;
      Mess = "Wrong port number (interface <" + InterConn->getInterName() +  ">). Configure first!";
			CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,Mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      if(MessageHandler)
        MessageHandler->Invoke(Mess,2); 
    }
  }
  else
  {
      String^ Mess;
      Mess = "Undefined connection type for interface <"+ InterConn->getInterName() +  "> (Client/Server). Configure first!";
			CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,Mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      if(MessageHandler)
        MessageHandler->Invoke(Mess,2);
  }
}
//-------------------------------------------------------------------
void CInterReceiverManager::endReceive()
{
  if(ReceiverThread)
  {
    ReceiverThread->Abort();
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,
                                              "Receive thread aborted",
                                              __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  }
  ReceiverThread=nullptr;
}
//-------------------------------------------------------------------
void CInterReceiverManager::receive(String^ inter)
{
  if(InterConn->isConnected())
  {
    ThreadStart^ thStart = gcnew ThreadStart(this,&CInterReceiverManager::receive);
    ReceiverThread = gcnew Thread(thStart);
    ReceiverThread->Start();
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,
                                              "Receive thread started (interface <" + inter + ">).",
                                              __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  }
}
//-------------------------------------------------------------------
void CInterReceiverManager::receive()
{
  CItemWrapper^ tlgWr = gcnew CTlgWrapper();
  int tlgLen;
  int i,count;
  char* tlgIdBuff=nullptr;
  char* tlgBodyBuff=nullptr;
  bool flag = true;
  int flag_mess;
  String^ mess = nullptr;
  CLogWriterWrapper^ LogWriter = CLogWriterWrapper::getLogWriterWrapper();

  //Interface Name
  String^ interName = InterConn->getInterName();
  //Interface Einstellungen
  CInterConfigWrapper^ interWr = gcnew CInterConfigWrapper();
  //
  String^ tlgId = interWr->getTlgIdName(interName);
  String^ elemId = interWr->getElemId(interName);
  
  //In diesem Fall sind die Interface Einstellunge falsch
  if (!tlgId->Equals("") && !elemId->Equals("")) 
  {
    //
    int offset = InterSet->getOffsetElem(tlgId,elemId);
    InterSet->getFlatTlg(tlgWr,tlgId);
    //Index von Id Element bestimmen
    int index = tlgWr->getElemIndex(elemId);
    
    //Wenn Index = oder > 0

   
    //int len=tlgWr->getElemLen(index);
    int len=tlgWr->getSubElemTransBytesCount(index);
    String^ type=tlgWr->getElemTypAsString(index);
    std::string tlgName("");
    String^ tlgNameNet=nullptr;
    int nothing = 0;
      
    while(flag)
    {
      try
      {
        count = 0;
        
        // if not connected
        if(! InterConn->isConnected())
        {
          flag = false;
        } 
        else
        {
          tlgIdBuff=new char[sizeof(char)*(offset+len)];
          count = InterConn->receiveByteStream(tlgIdBuff,offset+len);
        }

        if (count == 0)
        {
          nothing++;
          ReceiverThread->Sleep(200);
          if (nothing > 20)
            InterConn->disConnect();
        }
        else if (count < 0)
        {
          if(MessageHandler)
          {
            MessageHandler->Invoke(InterConn->getStatusMessage(),2);
          }
			    LogWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,InterConn->getStatusMessage(),
                                  __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        }
        else
        {
          ////Log Datei schreibeb : TlgId empfangen
          //mess = tlgIdBuff;
          //mess = String::Concat("Received TlgId : ",mess->Substring(0,count));
          //LogWriter->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,__FILE__,__FUNCTION__,__LINE__,new Diagnostics::StackTrace(true),3);
        }
        
        //Wenn Count > 0, Fallunterscheidung
        if(count == (offset+len))
        {
          //tlgName bestimmen
          if(type->Equals("String"))
          {
            tlgName.assign(tlgIdBuff+offset,len);
            tlgNameNet=CStdConverter::StdStrToString(tlgName);
          }
          else
          {
            if(type->Equals("Integer"))
            {
              bool swapping = interWr->isSwapping(interName);
              char buffer[4]={0,0,0,0};
              int* val=nullptr;
              if(swapping)
              {
                if (len == 2)
                {
                  for (int s=0; s<len; s++)
                    buffer[s] = tlgIdBuff[offset+s];

                  for (int i=0; i<len-1; ++i) 
                  {
                    std::swap(buffer[i], buffer[i+1]);
                    i += 1;
                  }
                  int n = 0;
                  for (int i=0; i<len; ++i)
                  {
                    unsigned char x = buffer[i];
                    n += (x << i*8);
                  }
                  val = &n;
                }
                else
                {
                  int pos = offset+len;;
                  int fac = -1;
                  for(i=0; i<len; i++)
                    buffer[i]=tlgIdBuff[pos+i*fac];

                  val = (int*)buffer;
                }
              }
              else
              {
                for(int i=0; i<len; i++)
                  buffer[i] = tlgIdBuff[offset+i];
                val = (int*)buffer;
              }
              tlgNameNet=interWr->getTlgName(interName,System::Convert::ToString(*val));
            }
            else
            {
            }
          }

          //Tlg Prototyp erzeugen
          tlgWr=InterSet->makeTlg(tlgNameNet);
          tlgLen = tlgWr->getTlgTransBytesCount();
          tlgBodyBuff=new char[sizeof(char)*tlgLen];
          for(i=0;i<(offset+len);i++)
          {
            tlgBodyBuff[i]=tlgIdBuff[i];
          }

          InterConn->receiveByteStream(tlgBodyBuff+(offset+len),tlgLen-(offset+len));
          tlgWr->decodeTlg(tlgBodyBuff,tlgLen);

          //Log Datei schreiben, TlgBody empfangen
          /*mess = tlgBodyBuff;
          mess = String::Concat("Received TlgBody : ",mess);
          LogWriter->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,__FILE__,__FUNCTION__,__LINE__,new Diagnostics::StackTrace(true),3);*/
          
          //Warnung,wenn Laenge und Wert von Element fuer Telegramlaenge nicht uebereinstimmt
          String^ elemLenId = interWr->getElemLenId(interName);
          String^ valLen = tlgWr->getSubElemValue("Header",elemLenId);
          int modiLen=interWr->getLenIdTreatModus(interName);
          int correctLen = -1;
          if(modiLen == 1)
          {
            correctLen=tlgWr->getTlgTransBytesCount();
          }
          else if(modiLen == 2)
          {
            correctLen=tlgWr->getTlgBodyTransBytesCount();
          }

          if((correctLen != -1) && (correctLen != System::Convert::ToInt32(valLen)))
          {
              mess = String::Concat(mess,"Telegram: ",tlgNameNet);
              mess = String::Concat(mess," Time: ",CTimeWrapper::getNowTime());
					    LogWriter->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
              if (MessageHandler)
                MessageHandler->Invoke(mess,1);
              mess = "The Length of telegramm is wrong (wrong value: ";
              mess = String::Concat(mess,valLen," correct value: ",System::Convert::ToString(correctLen));
					    LogWriter->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
              if (MessageHandler)
                MessageHandler->Invoke(mess,1);
          }
          //New Tlg Event
          NewTlgEvent->Invoke(tlgWr);
          mess = tlgWr->getSerialiseTlgAsString("");
          mess = String::Concat("Received Tlg : ",mess);
          LogWriter->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        
          delete  [] tlgBodyBuff;
          tlgBodyBuff=nullptr;
        }// if(count == (offset+len)
        delete [] tlgIdBuff;
        tlgIdBuff=nullptr;
      }
      catch(CExpWrapper^ e)
      {
        CExpWrapper::ErrorTyp err=e->getErrorTyp();
        mess = e->getMessage();
        String^ tmp;
        switch(err)
        {
          case CExpWrapper::ErrorTyp::tUnknowTlg:
          
                InterConn->clearAllStream();
                //mess = String::Concat(mess);
                //flag=false;
                flag_mess=2;
                //tmp = tlgIdBuff;
                tmp = gcnew String(tlgIdBuff);
                //for (int i=0;i<count;i++)
                //  tmp = tmp->Concat(tmp, tlgIdBuff[i]);
                mess=mess->Concat(mess," ",tmp);
                //Error
                //InterConn->disConnect();
                //mess = String::Concat(mess,"\nclosed connection");
                //mess = String::Concat(mess);
                break;
          case CExpWrapper::ErrorTyp::tUnknownTranspTyp:
              flag_mess=1;//Warning
              break;
          case CExpWrapper::ErrorTyp::tDecodeElem:
              flag_mess=2;
              break;
          default:
              flag=false;
              flag_mess=2;
              break;
        }
		    LogWriter->WriteMessage((CLogWriterWrapper::MessTyp)flag_mess,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
		    if(MessageHandler)
        {
          MessageHandler->Invoke(mess,flag_mess);
        }
        if(tlgBodyBuff)
          delete  [] tlgBodyBuff;
        tlgBodyBuff=nullptr;
        if(tlgIdBuff)
            delete [] tlgIdBuff;
        tlgIdBuff=nullptr;

        //tlgName="";
        //tlgNameNet=0;
      }
      catch(...)
      {
        mess = "Unknown exception in InterReceiverManager::receive (<" + interName + ">)";
        LogWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        if(MessageHandler)
          MessageHandler->Invoke(mess,2);
      }
      //delete tlgBodyBuff;
    }//end while
  }
  else
  { 
    mess = "Interface<" + interName + "> configuration is wrong (Id element not defined), configure first!";
    LogWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    if(MessageHandler)
      MessageHandler->Invoke(mess,2);
    //Verbindung schliessen
    InterConn->disConnect();
    mess = "Interface <" + interName + "> connection disconnected";
    LogWriter->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),1);
    if(MessageHandler)
      MessageHandler->Invoke(mess,2);
  }
}
//-------------------------------------------------------------------