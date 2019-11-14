// Copyright 2006 SMS - Demag AG

#ifndef _CInterConnectionListe_H_
#define _CInterConnectionListe_H_
//----------------------------------------------------------------
#include "CInterConnection.h"
#include "CSocketConnection.h"
#include "CConnectionInfo.h"
//------------------------------------------------------------------
using namespace System;
using namespace System::Collections;
//-------------------------------------------
// Name: CConnectionInfo.h
// Descr: Diese Klasse enthaelt ein Container mit Objekte
//        der Klasse CInterConnection
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------

public ref class CInterConnectionListe
{
  public:

    delegate void ChangeConnectionEvent(String^ interName, int status);

    CInterConnectionListe();
    ~CInterConnectionListe();
    void setActiveInterface(int number);
    int getActiveInterface();
    void addInterface(String^ interName);
    void addInterface(CInterConnection^ inter);
    int getInterfaceCount();
    String^ getInterfaceName(int id);
    CInterConnection^ getInterfaceAt(int index);

    void addObserver(ChangeConnectionEvent^ event);
    void setHostInfo(int index,String^ hostName,String^ ipAddr,int port);
    void getHostInfo(int index,String^& hostName,String^& ipAddr,int* port);

    int buildConnection(int index);
    void setDelConnection(DelIsConnected^ conn);
    bool isConnected(int index);
    bool isWaiting(int index);
    String^ getConnType(int index);
    bool disConnect(int index);
    void disConnectAll();
    int sendByteStream(unsigned char* bytes,int len,int index);
    int receiveByteStream(char* bytes,int len,int index);
    void setDirection(String^ dir);
    String^ getDirection();
    int getInterNummber(String^ name);
    void removeInerface(String^ inter);
    //------------------------------------------------------------------
    void setConnectionUpdateInterEvent(ConnectionUpdateInterEventTyp^ event,String^ inter);
    //------------------------------------------------------------------
  private:
    int ActiveInterface;
    ArrayList^ InterConnectionListe;
    void notifyToObserver(String^ interName,int status);
    String^ Dir;
    ArrayList^ ConEventListe;
    DelIsConnected^ IsConnectedEvent;
};


#endif
