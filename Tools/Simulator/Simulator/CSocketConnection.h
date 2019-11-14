// Copyright 2006 SMS - Demag AG
#ifndef _CSocketConnection_H
#define _CSocketConnection_H

#pragma warning( disable : 4570 )

//---------------------------------------------------------
using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
//-----------------------------------------------------------
public delegate void DelIsConnected(bool status);
public delegate void DelTreatmentRecConn(int index);
//------------------------------------------------------------
public delegate void ConnectionUpdateEventTyp();
// EMAL
public delegate void RecieveUpdateEventTyp();
//------------------------------------------------------------
//-------------------------------------------
// Name: CConnectionInfo.h
// Descr: Basisklasse fuer die Klasse CSocketserver,CSocketClient
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
public ref class CSocketConnection
{
  public:
    CSocketConnection();
    ~CSocketConnection();

    virtual String^ getStatus();
    delegate void updateConnEvent(String^ interName,int status);
    void setUpdateConnEvent(updateConnEvent^ event);
    //! richtet ein Socket ein
    virtual int buildConnection(String^ ipAddr,int port)=0;
    //! Mit dieser Methode wird auf Kommunikationspartner gewartet
    virtual void waitingForConnection(long wtime_)=0;
    //! gibt den Typ der Verbindung zurueck
    virtual String^ getConnTyp()=0;
    //! true, wenn Verbindung hergestellt ist
    virtual bool isConnected()=0;
    //! true, wenn auf Kommunikationspartner gewartet wird
    bool isWaiting();
    //! send Daten ueber Verbindung
    int sendByteStream(unsigned char* bytes,int len);
    //! empfaengt Daten ueber Verbindung
    int receiveByteStream(char* buffer,int len);
    virtual bool disConnection();
    void setDelConnected(DelIsConnected^ conn);
    //------------------------------------------
    void setConnectionUpdateEvent(ConnectionUpdateEventTyp^ event);
    //------------------------------------------
    // EMAL
    void setRecieveUpdateEvent(RecieveUpdateEventTyp^ event);
    //
    bool getSocketBlockingState();
    //
    void setSocketBlockingState(bool state);
    //
    //void CheckConnection(bool &ret);
    //
    int getRecieveBufferSize();
    //
    void clearAllStream();
  protected:
    //! Connection status of socket
    String^ Status;
    //! Socker fuer Datenuebertragung
    Socket^ SocketTcp;
    IPEndPoint^ RemouteHost;
    //! Thread fuer Warten auf Kommunikationspartner
    System::Threading::Thread^ waitConTh;
    //! Timer zum Ueberpruefen der Verfuegbarkeit des Kommunikationspartner
    System::Threading::Timer^ watchConTimer;
    //! wird auf true gesetzt, wenn auf Kommunikationspartner
    //  gewartet wird
    bool WaitingFlag;
    //! Waiting time if no connection before abort
    long ConnectionTimeOut;
    int buildRemoutHost(String^ ipAddr,int port);
    void watchConnection();
    void checkConnection(System::Object^ obj);
    updateConnEvent^ connEvent;
    DelIsConnected^ IsConnected;
    //--------------------------------------------------
    ConnectionUpdateEventTyp^  ConnectionUpdateEvent;
    //--------------------------------------------------
    // EMAL
    RecieveUpdateEventTyp^ RecieveUpdateEvent;
};

#endif
