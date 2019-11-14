// Copyright 2006 SMS - Demag AG
#include "stdafx.h"
#include "CSocketConnection.h"
#include "CConnectionInfo.h"
#include "CLogWriterWrapper.h"
//----------------------------------------------
CSocketConnection::CSocketConnection():
SocketTcp(nullptr),RemouteHost(nullptr),IsConnected(nullptr), WaitingFlag(false),waitConTh(nullptr)
{
}
//----------------------------------------------
CSocketConnection::~CSocketConnection()
{
}
//---------------------------------------------
int CSocketConnection::buildRemoutHost(String^ ipAddr,int port)
{
  int ret = 0;
  int count=0;
  int i=0;
  bool flag;
  System::Net::IPHostEntry^ hostEntry=System::Net::Dns::GetHostByAddress(ipAddr);
	count = hostEntry->AddressList->Length;
  i=0;
  flag=true;
  while((flag) && (i<count))
  {
    if((hostEntry->AddressList[i]->ToString())->Equals(ipAddr))
    {
      flag=false;
    }
    else
    i++;
  }
  if(i>=count)
  {
    ret = 1;
  }
  else
  {
    RemouteHost = gcnew IPEndPoint(hostEntry->AddressList[i],port);
  }
  return ret;
}
//----------------------------------------------
//bool CSocketConnection::isConnected()
//{
//  bool ret=false;
//
//  if (SocketTcp)
//    ret = SocketTcp->Poll(5,System::Net::Sockets::SelectMode::SelectWrite);
//  /*if(SocketTcp)
//    ret = SocketTcp->get_Connected();*/
//  return ret;
//}

//----------------------------------------------
//void CSocketConnection::CheckConnection(bool &ret)
//{
//  if (SocketTcp != 0)
//  {
//    bool state = SocketTcp->Blocking;
//    try
//    {
//      //Verbindung testen
//      Byte tmp[] = new Byte[1];
//      SocketTcp->Blocking = false;
//      SocketTcp->Send( tmp, 0, static_cast<SocketFlags>(0) );
//
//      ret = true;
//    }
//    catch (System::Net::Sockets::SocketException* e) 
//    {
//      ret = false;
//      SocketTcp->Blocking = state;
//    }
//    catch ( ... )
//    {
//      ret = false;
//    }
//  }
//  else
//    ret = false;
//}

//----------------------------------------------
bool CSocketConnection::getSocketBlockingState()
{
  return SocketTcp->Blocking;
}
//----------------------------------------------
void CSocketConnection::setSocketBlockingState(bool state)
{
  SocketTcp->Blocking = state;
}
void CSocketConnection::setDelConnected(DelIsConnected^ conn)
{
  this->IsConnected = conn;
}
//---------------------------------------------

//----------------------------------------------
int CSocketConnection::sendByteStream(unsigned char* bytes,int len)
{
  int ret=-1;
  if(SocketTcp != nullptr)
  {
    //Verbindung testen
    array <Byte>^ tmp = gcnew array<Byte>(1);
    SocketTcp->Blocking = false;
    SocketTcp->Send( tmp,0,SocketFlags::None);
    //
    array <Byte>^ byteStream = gcnew array <Byte>(len);
    for(int i=0;i<len;i++)
      byteStream[i] = bytes[i];

    ret=SocketTcp->Send(byteStream,0,len,SocketFlags::None);
  }
  return ret;
}
//----------------------------------------------
int CSocketConnection::receiveByteStream(char* buffer,int len)
{
  int ret=-1;
  if(SocketTcp != nullptr)
  {
    if (isConnected())
    {
      array <Byte>^ byteStream = gcnew array <Byte>(len);
      ret=SocketTcp->Receive(byteStream,0,len,SocketFlags::None);
      for(int i=0;i<ret;i++)
        buffer[i]=byteStream[i];
    }  
  }
  return ret;
}
//----------------------------------------------
void CSocketConnection::clearAllStream()
{
  if(SocketTcp != nullptr)
  {
    if (isConnected())
    {
      array <Byte>^ byteStream = gcnew array <Byte>(8192);
      SocketTcp->Receive(byteStream,0,8192,SocketFlags::None);
      delete byteStream;
    }
  }
}
//----------------------------------------------
int CSocketConnection::getRecieveBufferSize()
{
  return SocketTcp->ReceiveBufferSize;
}
//----------------------------------------------
bool CSocketConnection::disConnection()
{
  bool ret=true;

  if(SocketTcp != nullptr)
  {
    if(SocketTcp->Connected)
    {
      SocketTcp->Shutdown(SocketShutdown::Both);
      SocketTcp->Close();
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,
                                                            "Connection disconnected",
                                                            __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      //ConnectionUpdateEvent->Invoke();
    }
    else
    {
      if(WaitingFlag)
      {
        if(waitConTh != nullptr)
        {
          waitConTh->Abort();
          SocketTcp->Close();
          CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,
                                                    "Waiting thread aborted",
                                                    __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
          //ConnectionUpdateEvent->Invoke();
        }
      }
    }
  }
  WaitingFlag = false;
  Status = CConnectionInfo::ConnectionStatus::Disconnected;
  if(watchConTimer)
  {
		//watchConTimer->Dispose();
    delete watchConTimer;
    watchConTimer=nullptr;
  }
  return ret;
}
//----------------------------------------------
bool CSocketConnection::isWaiting()
{
  return this->WaitingFlag;
}
//----------------------------------------------
void CSocketConnection::setUpdateConnEvent(updateConnEvent^ event)
{
  this->connEvent = event;
}
//----------------------------------------------
void CSocketConnection::setRecieveUpdateEvent(RecieveUpdateEventTyp^ event)
{
  this->RecieveUpdateEvent = event;
}
//----------------------------------------------
void CSocketConnection::setConnectionUpdateEvent(ConnectionUpdateEventTyp^ event)
{
  this->ConnectionUpdateEvent = event;
}
//----------------------------------------------
void CSocketConnection::watchConnection()
{
  System::Threading::TimerCallback^ timerDel = gcnew System::Threading::TimerCallback(this,&CSocketConnection::checkConnection);
  watchConTimer = gcnew System::Threading::Timer(timerDel,nullptr,1000,10000);
}
//----------------------------------------------
void CSocketConnection::checkConnection(System::Object^ obj)
{
  //int count;
  //Socket* liste[] = new Socket*[1];
  //liste[0]=SocketTcp;

  //bool test = SocketTcp->Poll(10,System::Net::Sockets::SelectMode::SelectWrite);
  if(SocketTcp!=nullptr && !SocketTcp->Connected)
  {
    //watchConTimer->Dispose(nullptr);
    delete watchConTimer;
    watchConTimer=nullptr;
    if(ConnectionUpdateEvent)
      ConnectionUpdateEvent->Invoke();
  }
}
//----------------------------------------------
String^ CSocketConnection::getStatus()
{
  return Status;
}