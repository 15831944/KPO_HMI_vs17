// Copyright 2006 SMS - Demag AG

//------------------------------------------
#include "stdafx.h"
#include "CSocketClient.h"
#include "CConnectionInfo.h"
#include "CLogWriterWrapper.h"
//-----------------------------------------
using namespace System::Net::Sockets;
//------------------------------------------
//-----------------------------------------
CSocketClient::CSocketClient():
CSocketConnection()
{
}
//-----------------------------------------
CSocketClient::~CSocketClient()
{
}
//-------------------------------------------
int CSocketClient::buildConnection(String^ ipAddr,int port)
{
  int ret = 0;
  String^ mess = nullptr;
  if (ipAddr)
  {
    if (port>1023)
    {
      ret = buildRemoutHost(ipAddr,port);
      if(ret == 0)
      {
        SocketTcp = gcnew Socket(AddressFamily::InterNetwork,SocketType::Stream,ProtocolType::Tcp);
        mess = "Client IPEndPoint created";
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
    ret=-1;
    mess = "Null pointer of ip parameter";
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  }
  return ret;
}
//--------------------------------------------
void CSocketClient::waitingForConnection(long wtime_)
{
  WaitingFlag = true;
  ConnectionTimeOut = wtime_;

  System::Threading::ThreadStart^ ThStart = gcnew System::Threading::ThreadStart(this,&CSocketClient::waiting);
  waitConTh = gcnew System::Threading::Thread(ThStart);
  waitConTh->Start();
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,
                                                            "Start thread for waiting connection",
                                                            __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
}
//--------------------------------------------
String^ CSocketClient::getConnTyp()
{
  return "Client";
}
//--------------------------------------------
void CSocketClient::waiting()
{
  bool flag=true;

  if(SocketTcp != nullptr)
  {
    WaitingFlag = true;
    Status = CConnectionInfo::ConnectionStatus::Waiting;
    if(ConnectionUpdateEvent)
      ConnectionUpdateEvent->Invoke();

    long SleepTime = 0;
    while (flag)
    {
      try
      {
        SocketTcp->Connect(RemouteHost);
        if(isConnected())
        {
          flag = false;
          Status = CConnectionInfo::ConnectionStatus::Connected;
          //EMAL
          if(ConnectionUpdateEvent)
            ConnectionUpdateEvent->Invoke();
          if (RecieveUpdateEvent)
            RecieveUpdateEvent->Invoke();
          CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,
                                                            "Client connected",
                                                            __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        }
        else
        {
          if (ConnectionTimeOut!=0)
          {
            SleepTime ++;
            if (SleepTime >= ConnectionTimeOut)
            {
              flag = false;
              WaitingFlag = false;
            }
          }
          Status = CConnectionInfo::ConnectionStatus::Disconnected;

          System::Threading::Thread::Sleep(1000);
        }
      }
      catch(System::Net::Sockets::SocketException^ e)
      {
        if (ConnectionTimeOut!=0)
        {
          SleepTime ++;
          if (SleepTime >= ConnectionTimeOut)
          {
            flag = false;
            WaitingFlag = false;

            #if defined __CONSOLE__
            Console::WriteLine(e->Message);
            #endif
          }
        }
        Status = CConnectionInfo::ConnectionStatus::Disconnected;
				CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,e->Message,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        if(ConnectionUpdateEvent)
          ConnectionUpdateEvent->Invoke();
        System::Threading::Thread::Sleep(1000);
      }
    }
    if(ConnectionUpdateEvent)
      ConnectionUpdateEvent->Invoke();
    //IsConnected->Invoke(true);
    WaitingFlag = false;
  }
}
//--------------------------------------------
bool CSocketClient::disConnection()
{
  CSocketConnection::disConnection();
  if(ConnectionUpdateEvent)
    ConnectionUpdateEvent->Invoke();
  return true;
}
//--------------------------------------------
bool CSocketClient::isConnected()
{
  bool ret=false;


  /*if (SocketTcp)
    ret = SocketTcp->Poll(5,System::Net::Sockets::SelectMode::SelectWrite);*/
  if(SocketTcp)
    ret = SocketTcp->Connected;
  return ret;
}