// Copyright 2006 SMS - Demag AG

//-------------------------------------------------------------
#include "stdafx.h"
#include "CInterConnection.h"
#include "CLogWriterWrapper.h"
//---------------------------------------------------------------
CInterConnection::CInterConnection(String^ inter):
m_pSocket(nullptr)
{
  m_pConnectionInfo = gcnew CConnectionInfo();
  IdInterface = inter;
  ConnectionUpdateEvent = nullptr;
  ReceiveThreadInSenderManagerEvent = nullptr;
  /*ConnectionUpdateInterEvent = 0;*/
  StatusMessage = "";
  ConnectionUpdateInterEventList = gcnew System::Collections::ArrayList();
}
//---------------------------------------------------------------
CInterConnection::~CInterConnection()
{
}
//----------------------------------------------------------------
void CInterConnection::setReceiveThreadInSenderManagerEvent(ReceiveThreadInSenderManagerEventTyp^ e)
{
  ReceiveThreadInSenderManagerEvent = e;
}
//----------------------------------------------------------------
void CInterConnection::setInterName(String^ name)
{
  this->IdInterface = name;
}
//----------------------------------------------------------------
String^ CInterConnection::getInterName()
{
  return this->IdInterface;
}
//----------------------------------------------------------------
void CInterConnection::setHostInfo(String^ hostName,String^ ipAddr,int port)
{
  m_pConnectionInfo->setHostName(hostName);
  m_pConnectionInfo->setIpAddresse(ipAddr);
  m_pConnectionInfo->setPort(port);
}
//----------------------------------------------------------------
void  CInterConnection::getHostInfo(String^& hostName,String^& ipAddr,int* port)
{
  hostName=m_pConnectionInfo->getHostName();
  ipAddr=m_pConnectionInfo->getIpAddresse();
  (*port) = m_pConnectionInfo->getPort();
}
//----------------------------------------------------------------
int CInterConnection::buildConnAsServer()
{
  int ret=0;
  //try
  //{
  m_pSocket = gcnew CSocketServer();
  ConnectionUpdateEventTyp^ upConn = gcnew ConnectionUpdateEventTyp(this,&CInterConnection::updateConnection);
  m_pSocket->setConnectionUpdateEvent(upConn);
  //EMAL
  RecieveUpdateEventTyp^ upRec = gcnew RecieveUpdateEventTyp(this,&CInterConnection::updateRecieve);
  m_pSocket->setRecieveUpdateEvent(upRec);
  
  //m_pSocket->setUpdateConnEvent(UpdateConnEvent);
  ret = m_pSocket->buildConnection(m_pConnectionInfo->getIpAddresse(),m_pConnectionInfo->getPort());
 



  if (ReceiveThreadInSenderManagerEvent && ret==0)
    ReceiveThreadInSenderManagerEvent->Invoke(true);
  //}
  //catch (ObjectDisposedException* e) 
  //{
  //  ret = -1;
  //  StatusMessage = e->Message;
  //}
  //catch (SocketException* e) 
  //{
  //  StatusMessage = e->Message;
  //  ret = 2;
  //}
  //catch(Exception* e)
  //{
  //  StatusMessage = e->Message;
  //  ret = -1;
  //}
  return ret;
}
//----------------------------------------------------------------
int CInterConnection::buildConnAsClient()
{
  int ret=0;

  m_pSocket = gcnew CSocketClient();
  ConnectionUpdateEventTyp^ upConn = gcnew ConnectionUpdateEventTyp(this,&CInterConnection::updateConnection);
  m_pSocket->setConnectionUpdateEvent(upConn);
  //EMAL
  RecieveUpdateEventTyp^ upRec = gcnew RecieveUpdateEventTyp(this,&CInterConnection::updateRecieve);
  m_pSocket->setRecieveUpdateEvent(upRec);
  ret = m_pSocket->buildConnection(m_pConnectionInfo->getIpAddresse(),m_pConnectionInfo->getPort());
  if (ReceiveThreadInSenderManagerEvent && ret==0)
    ReceiveThreadInSenderManagerEvent->Invoke(true);
  /* catch (ObjectDisposedException* e) 
  {
    ret = -1;
    StatusMessage = e->Message;
  }
  catch (SocketException* e) 
  {
    StatusMessage = e->Message;
    ret = 2;
  }
  catch(Exception* e)
  {
    StatusMessage = e->Message;
    ret = 3;
  }*/

  return ret;
}
//----------------------------------------------------------------
void CInterConnection::waitingForConnection()
{
  m_pSocket->waitingForConnection(m_pConnectionInfo->getConnectionTimeOut());
}
//----------------------------------------------------------------
void CInterConnection::setDelConnection(DelIsConnected^ conn)
{
  m_pSocket->setDelConnected(conn);
}
//----------------------------------------------------------------
bool CInterConnection::isConnected()
{
 // if(Sender != 0)
  //{ 
   // bool flag;
   // flag=Sender->isConnected();
 // }
  //if(Receiver != 0)
  //{
    // bool flag;
    //flag=Receiver->isConnected();
 // }

  if(m_pSocket != nullptr)
    return m_pSocket->isConnected();
  else
    return false;

  //if(m_pSocket != 0)
  //{
  //  bool ret;
  //  m_pSocket->CheckConnection(ret);
  //  return ret;
  //}
  //else
  //  return false;
}
//----------------------------------------------------------------
bool CInterConnection::isWaiting()
{
  if(m_pSocket != nullptr)
    return m_pSocket->isWaiting();
  else
    return false;
}
//----------------------------------------------------------------
String^ CInterConnection::getConnType()
{   
  //if(m_pSocket != 0)
  //  return m_pSocket->getConnTyp();
  //else
  //  return "";
  String^ ret = nullptr;
  CConnectionInfo::ConnectionType typeConn = m_pConnectionInfo->getConnectionType();
  if(typeConn == CConnectionInfo::ConnectionType::Client)
  {
    ret = "Client"; 
  }
  else
  {
    if(typeConn == CConnectionInfo::ConnectionType::Server)
      ret = "Server";
  }
  return ret;
}
//----------------------------------------------------------------
bool CInterConnection::disConnect()
{
  if(m_pSocket != nullptr)
  {
    m_pSocket->disConnection();
    if (ReceiveThreadInSenderManagerEvent)
      ReceiveThreadInSenderManagerEvent->Invoke(false);
    StatusMessage = "DisConnect was called!";
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,
                                              StatusMessage,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    updateConnection();
  }
  return true;
}
//----------------------------------------------------------------
int CInterConnection::sendByteStream(unsigned char* bytes,int len)
{ 
  int ret = -1;
  if(m_pSocket != nullptr)
  {
    // This is how you can determine whether a socket is still connected.
    bool blockingState = m_pSocket->getSocketBlockingState();

    try
    {
      ret=m_pSocket->sendByteStream(bytes,len);
    }
    catch (System::Net::Sockets::SocketException^ e ) 
    {
      m_pSocket->setSocketBlockingState(blockingState);
      m_pSocket->disConnection();
      throw e;
    }
  }
  return ret;
}
//----------------------------------------------------------------
int CInterConnection::receiveByteStream(char* bytes,int len)
{
  int ret = -1;
  //  String * x;

  try
  {
    if(m_pSocket != nullptr)
    {
      ret = m_pSocket->receiveByteStream(bytes,len);
    }
  }
  catch (ObjectDisposedException^ e) 
  {
    StatusMessage = e->Message;
    m_pSocket->disConnection();
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,
                                              StatusMessage,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    updateConnection();
  }
  catch (SocketException^ e) 
  {
    StatusMessage = e->Message;
    m_pSocket->disConnection();
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,
                                              StatusMessage,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    updateConnection();
  }
  catch (ArgumentOutOfRangeException^ e) 
  {
    StatusMessage = e->Message;
    m_pSocket->disConnection();
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,
                                              StatusMessage,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    updateConnection();
  }
  return ret;
}
//----------------------------------------------------------------
void CInterConnection::clearAllStream()
{
  try
  {
    if(m_pSocket != nullptr)
    {
      m_pSocket->clearAllStream();
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,
                                                "Socketbuffer emptied",
                                                __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    }
  }
  catch (ObjectDisposedException^ e) 
  {
    StatusMessage = e->Message;
    m_pSocket->disConnection();
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,
                                              StatusMessage,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    updateConnection();
  }
  catch (SocketException^ e) 
  {
    StatusMessage = e->Message;
    m_pSocket->disConnection();
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,
                                              StatusMessage,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    updateConnection();
  }
  catch (ArgumentOutOfRangeException^ e) 
  {
    StatusMessage = e->Message;
    m_pSocket->disConnection();
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,
                                              StatusMessage,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    updateConnection();
  }
}
//----------------------------------------------------------------
void CInterConnection::setConnectionType(CConnectionInfo::ConnectionType type)
{
  m_pConnectionInfo->setConnectionType(type);
}
//----------------------------------------------------------------
CConnectionInfo::ConnectionType CInterConnection::getConnectionType()
{
  return m_pConnectionInfo->getConnectionType();
}
//---------------------------------------------------------------
void CInterConnection::setUpdateConEvent(CSocketConnection::updateConnEvent^ event)
{
  this->UpdateConnEvent = event;
  //m_pSocket->setUpdateConnEvent(event);
}
//---------------------------------------------------------------
//void CInterConnection::setConnectionUpdateEvent(ConnectionUpdateEventTyp* event)
//{
  //  ConnectionUpdateEvent = event;
//}
//---------------------------------------------------------------
void CInterConnection::addConnectionUpdateInterEvent(ConnectionUpdateInterEventTyp^ event)
{
  //ConnectionUpdateInterEvent = event;
  //-----EMAL-----
  if (!ConnectionUpdateInterEventList->Contains(event))
    ConnectionUpdateInterEventList->Add(event);
}
// EMAL ----
void CInterConnection::setRecieveUpdateInterEvent (StartRecieveInterEventTyp^ event)
{
  RecieveUpdateInterEvent = event;
}

// EMAL ----
void CInterConnection::updateRecieve()
{
  if(RecieveUpdateInterEvent)
    RecieveUpdateInterEvent->Invoke(IdInterface);
}
//---------------------------------------------------------------
void CInterConnection::updateConnection()
{
  /*if(ConnectionUpdateInterEvent)
    ConnectionUpdateInterEvent->Invoke(IdInterface);*/
   //call invoke of all in container
  ConnectionUpdateInterEventTyp^ event=nullptr;
  for (int i=0;i<ConnectionUpdateInterEventList->Count;i++)
  {
		event = safe_cast <ConnectionUpdateInterEventTyp^> (ConnectionUpdateInterEventList[i]);
    if(event != nullptr && IdInterface != nullptr)
      event->Invoke(IdInterface);
  }
}
//---------------------------------------------------------------

String^ CInterConnection::getStatusMessage()
{
  return StatusMessage;
}
//------------------------------------------------------------------
void CInterConnection::setConnectionTimeOut(long ctime_)
{
   m_pConnectionInfo->setConnectionTimeOut(ctime_);
}
//-----------------------------------------------------------------
long CInterConnection::getConnectionTimeOut()
{
  return m_pConnectionInfo->getConnectionTimeOut();
}
//-----------------------------------------------------------------
//bool CInterConnection::reConnect(const bool isServer)
//{
//  /*bool ret = true;
//  int index;
//  if (disConnect())
//  {
//    if(isServer)
//      index = buildConnAsServer();
//    else
//      index = buildConnAsClient();
//    
//    if (index!=0)
//      ret=false;
//  }
//  else
//    ret = false;*/
//  
//  return false;
//}
//---------------------------------------------------------------------
int CInterConnection::getRecieveBufferSize()
{
  return m_pSocket->getRecieveBufferSize();
}