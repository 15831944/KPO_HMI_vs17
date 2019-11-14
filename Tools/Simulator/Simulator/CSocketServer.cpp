// Copyright 2006 SMS - Demag AG
//------------------------------------------
#include "stdafx.h"
#include "CSocketServer.h"
#include "CConnectionInfo.h"
#include "CLogWriterWrapper.h"
//------------------------------------------
CSocketServer::CSocketServer():
CSocketConnection(),SocketCon(nullptr),WaitClientThread(nullptr)
{
}
//------------------------------------------
CSocketServer::~CSocketServer()
{
}
//------------------------------------------
int CSocketServer::buildConnection(String^ ipAddr,int port)
{
  int ret = 0;
  String^ mess = nullptr;
  if (ipAddr != nullptr)
  {
    if (port>1023)
    {
      ret=buildRemoutHost(ipAddr,port);
      if(ret == 0)
      { 
        SocketCon = gcnew Socket(AddressFamily::InterNetwork,SocketType::Stream,ProtocolType::Tcp);
        mess = "Server IPEndPoint created";
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        SocketCon->Bind(RemouteHost);
        mess = "Bind of server IPEndPoint";
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        SocketCon->Listen(1);//Allows a queue of 1 connection
        mess = "Places a server socket in a listening state";
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      }
    }
    else
    {
      ret=-2;
      mess = "The port number is lower as 1024";
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    }
  }
  else
  {
    ret = -1;
    mess = "Null pointer of ip parameter";
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  }
  return ret;
}
//------------------------------------------
void CSocketServer::waitingForConnection(long wtime_)
{
  WaitingFlag = true;
  ConnectionTimeOut = wtime_;

  ThreadStart^ ThSt = gcnew ThreadStart(this,&CSocketServer::waiting);
  if(waitConTh != nullptr)
    waitConTh->Abort();
  waitConTh = gcnew Thread(ThSt);
  waitConTh->Start();
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,
                                                            "Start thread for waiting connection",
                                                            __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
}
//------------------------------------------
void CSocketServer::waiting()
{
  WaitingFlag = true;
  Status = CConnectionInfo::ConnectionStatus::Waiting;

  if(ConnectionUpdateEvent != nullptr)
    ConnectionUpdateEvent->Invoke();

  if (SocketCon != nullptr && SocketCon->IsBound)
    SocketTcp = SocketCon->Accept();

  //IsConnected->Invoke(true);
  //EMAL
  if (RecieveUpdateEvent != nullptr)
    RecieveUpdateEvent->Invoke();
  WaitingFlag = false;
  if(ConnectionUpdateEvent != nullptr)
  {
    ConnectionUpdateEvent->Invoke();
  }
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,
                                                          "Server to client connected",
                                                          __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  watchConnection();
}
//------------------------------------------
String^ CSocketServer::getConnTyp()
{
  return "Server";
}
//------------------------------------------
bool CSocketServer::disConnection()
{
  CSocketConnection::disConnection();
  if(SocketCon != nullptr)
  {
    if(waitConTh != nullptr)
      waitConTh->Abort();

    SocketCon->Close();
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,
                                                            "Connection disconnected",
                                                            __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  }
  if(ConnectionUpdateEvent != nullptr)
    ConnectionUpdateEvent->Invoke();
  return true;
}
//------------------------------------------
bool CSocketServer::isConnected()
{
  bool ret=false;

 /*if (SocketCon)
  ret = (SocketCon->Poll(-1,System::Net::Sockets::SelectMode::SelectWrite));*/
 ////if (!ret)
 ////  Status = CConnectionInfo::ConnectionStatus::Disconnected;
 if(SocketTcp != nullptr)
    ret = SocketTcp->Connected;
  return ret;
}