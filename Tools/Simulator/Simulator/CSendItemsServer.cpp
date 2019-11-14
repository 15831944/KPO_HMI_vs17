#include "stdafx.h"
#include "CSendItemsServer.h"
#include "CLogWriterWrapper.h"

//------------------------------------------
CSendItemsServer::CSendItemsServer()
{
  itemsList       = gcnew Collections::ArrayList();
  MessageHandler  = nullptr;
}
//------------------------------------------
CSendItemsServer::~CSendItemsServer()
{
}
//------------------------------------------
CSendItemsServer^ CSendItemsServer::getSendItemsServer()
{
  if(sendItemsServer == nullptr)
  {
    sendItemsServer = gcnew CSendItemsServer();
  }
  return sendItemsServer; 
}
//------------------------------------------
void CSendItemsServer::addItemtoSend(CInterSenderManager^ inter,CSzenItem^ item,Priority priority)
{

}
//------------------------------------------
void CSendItemsServer::sendCyclicItem(CInterConnection^ inter,CItemWrapper^ item)
{
  int len;
  char* buffer=nullptr; 
  unsigned char* buffer1=nullptr;
  String^ mess = nullptr;
  String^ interName = nullptr;
  
  interName = item->getInterfece();
  buffer = new char[item->getTlgTransBytesCount()*sizeof(char)];
  buffer1 = (unsigned char*)buffer;
  len = item->getSerializeTlg(buffer,item->getTlgTransBytesCount());

  try
  {
    int ret = Send(buffer1,len,inter);

    if(ret <= 0)
    {
      mess = String::Concat("Cyclic telegram ",item->getName()," was not send (");
      mess = String::Concat(mess,"no Connection to Interface ",interName,")");
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage((CLogWriterWrapper::MessTyp)2,mess,
																														__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);  
			if(MessageHandler)
        MessageHandler->Invoke(mess,2);
    }
    else
    {
      mess = "Send Cyclic telegram: ";
      
      mess=String::Concat(mess,item->getSerialiseTlgAsString("|"));
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage((CLogWriterWrapper::MessTyp)0,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      if(MessageHandler)
        MessageHandler->Invoke(mess,0);
    }
    delete [] buffer;


  }
  catch (System::Net::Sockets::SocketException^ e)
  {
    if(MessageHandler)
    {
      mess = e->Message;
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage((CLogWriterWrapper::MessTyp)2,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      MessageHandler->Invoke(mess,2);
    }
  }
}
//------------------------------------------
void CSendItemsServer::sendSzenItem(CInterConnection^ inter,CItemWrapper^ item,bool cyclicItem)
{
  if (!cyclicItem)
  {
    int len;
    char* buffer=nullptr; 
    unsigned char* buffer1=nullptr;
    String^ mess = nullptr;
    String^ interName = nullptr;
    
    interName = item->getInterfece();
    buffer = new char[item->getTlgTransBytesCount()*sizeof(char)];
    buffer1 = (unsigned char*)buffer;
    len = item->getSerializeTlg(buffer,item->getTlgTransBytesCount());

    try
    {
      int ret = Send(buffer1,len,inter);

      if(ret <= 0)
      {
        mess = String::Concat("Telegram ",item->getName()," was not send (");
        mess = String::Concat(mess,"no Connection to Interface ",interName,")");
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage((CLogWriterWrapper::MessTyp)2,mess,
																														  __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);  
			  if(MessageHandler)
          MessageHandler->Invoke(mess,2);
      }
      else
      {
        mess = "Send telegram: ";
        mess=String::Concat(mess,item->getSerialiseTlgAsString("|"));
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage((CLogWriterWrapper::MessTyp)0,mess,
                                                             __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        if(MessageHandler)
          MessageHandler->Invoke(mess,0);
      }
      delete [] buffer;


    }
    catch (System::Net::Sockets::SocketException^ e)
    {
      if(MessageHandler)
      {
        mess = e->Message;
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage((CLogWriterWrapper::MessTyp)2,mess,
                                                             __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        MessageHandler->Invoke(mess,2);
      }
    }
  }
}
//------------------------------------------
void CSendItemsServer::sendSzenItem(CInterSenderManager^ inter,CSzenItem^ item)
{
  if (!item->getIsCyclic())
  {
    int len;
    char* buffer=nullptr; 
    unsigned char* buffer1=nullptr;
    String^ mess = nullptr;
    String^ interName = nullptr;
    
    interName = item->getInterface();
    buffer = new char[item->getTlgTransBytesCount()*sizeof(char)];
    buffer1 = (unsigned char*)buffer;
    len = item->getSerializeTlg(buffer,item->getTlgTransBytesCount());
   

    try
    {
      int ret = Send(buffer1,len,inter->getInterConn());
     
      if(ret <= 0)
      {
        mess = String::Concat("Telegram ",item->getItemName()," was not send.");
        if(MessageHandler)
          MessageHandler->Invoke(mess,2);
        
        mess = String::Concat(mess,"No connection to interface ",interName,")");
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage((CLogWriterWrapper::MessTyp)2,mess,
																																__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      }
      else
      {
        mess = "Send Tel: ";
        mess=String::Concat(mess,item->SerializeTlgAsString());
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage((CLogWriterWrapper::MessTyp)0,mess,
                                                  __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        MessageHandler->Invoke(mess,0);
      }
      delete [] buffer;
    }
    catch (System::Net::Sockets::SocketException^ e)
    {
      mess = String::Concat(e->Message);
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage((CLogWriterWrapper::MessTyp)2,mess,
																																__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
			if(MessageHandler)
        MessageHandler->Invoke(mess,2);
    }
  }
}
//---------------------------------------------------------
void CSendItemsServer::setMessageHandler(MessageHandlerTyp^ handler)
{
  MessageHandler = handler;
}
//---------------------------------------------------------
int CSendItemsServer::Send(unsigned char* buffer, int len,CInterConnection^ interCon )
{
  int ret;
  bool ok=true;
  while(ok)
  {
    //Versuch, den Inter Objekt zu sperren
    if (Threading::Monitor::TryEnter(interCon))
    {
      if (interCon->isConnected())
        ret = interCon->sendByteStream(buffer,len);
      else
        ret = -1;
      //Sperre aufheben
      Threading::Monitor::Exit(interCon);
      ok=false; 
    }
    else
    {
      //Sonst warten
      Threading::Thread::CurrentThread->Sleep(2);
    }
  }
  return ret;
}