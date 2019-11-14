// Copyright 2006 SMS - Demag AG
#ifndef _CInterConnection_H_
#define _CInterConnection_H_
//--------------------------------------------------------
#include "CSocketConnection.h"
#include "CSocketClient.h"
#include "CSocketServer.h"
#include "CConnectionInfo.h"
//----------------------------------------------------------
using namespace System;

//--------------------------------------------------
public delegate void ConnectionUpdateInterEventTyp(String^ inter);
// EMAL
public delegate void StartRecieveInterEventTyp(String^ inter);


//--------------------------------------------------
//-------------------------------------------
// Name: CInterConnection.h
// Descr: Mit dieser Klasse wird die Verbindung
//        fuer eine Schnittstelle verwaltet
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
public ref class CInterConnection
{
  public: delegate void ReceiveThreadInSenderManagerEventTyp(bool start);  
  public:
    String^ getStatusMessage();
    CInterConnection(String^ inter);
    ~CInterConnection();
    void setInterName(String^ name);
    String^ getInterName();
    void setHostInfo(String^ hostName,String^ ipAddr,int port);
    void getHostInfo(String^& hostName,String^& ipAddr,int* port);
    void setConnectionType(CConnectionInfo::ConnectionType type);
    CConnectionInfo::ConnectionType getConnectionType();
    //! bildet Verbindung als Server
    int buildConnAsServer();
    //! bildet Verbindung als Client
    int buildConnAsClient();
    //! wartet auf Communikationspartner
    void waitingForConnection();
    void setDelConnection(DelIsConnected^ conn);
    bool isConnected();
    bool isWaiting();
    String^ getConnType();
    //! 
    bool disConnect();
    int sendByteStream(unsigned char* bytes,int len);
    int receiveByteStream(char* bytes,int len);
    void setUpdateConEvent(CSocketConnection::updateConnEvent^ event);
    void setReceiveThreadInSenderManagerEvent(ReceiveThreadInSenderManagerEventTyp^ e);
    
    void setConnectionTimeOut(long ctime_);
    long getConnectionTimeOut();

    //----------------------------------------------------------------
    //void setConnectionUpdateEvent(ConnectionUpdateEventTyp* event);
    void addConnectionUpdateInterEvent(ConnectionUpdateInterEventTyp^ event);
    void updateConnection();
    //----------------------------------------------------------------
    void setRecieveUpdateInterEvent (StartRecieveInterEventTyp^ event);
    void updateRecieve();
    //bool reConnect(const bool isServer);
    int getRecieveBufferSize();
    void clearAllStream();
  private:
    //! Message of last status
    String^ StatusMessage;
    //! Name der Schnittstelle
    String^ IdInterface;
    CSocketConnection::updateConnEvent^ UpdateConnEvent;
    //! Socket Verbindung
    CSocketConnection^ m_pSocket;
    //! Verbindungskonfiguration der Schnittstelle
    CConnectionInfo^ m_pConnectionInfo;

    //----------------------------------------------------------------------
    ConnectionUpdateEventTyp^ ConnectionUpdateEvent;
    //! Daelegate Objekt. Wird benutzt bei Aenderungen des Verbindungsstatus
    /*ConnectionUpdateInterEventTyp* ConnectionUpdateInterEvent;*/
    //! Liste von Events um andere Formulare über die Statusänderung zu informieren
    System::Collections::ArrayList^ ConnectionUpdateInterEventList;
    //----------------------------------------------------------------------
    StartRecieveInterEventTyp^ RecieveUpdateInterEvent;
    ReceiveThreadInSenderManagerEventTyp^ ReceiveThreadInSenderManagerEvent;
};

#endif
