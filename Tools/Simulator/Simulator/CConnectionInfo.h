// Copyright 2006 SMS - Demag AG
#ifndef _CConnectionInfo_H_
#define _CConnectionInfo_H_

//-------------------------------------
using namespace System;
//-------------------------------------------
// Name: CConnectionInfo.h
// Descr: Diese Klasse enthaelt Verbindungskonfiguration
//        von Schnittstellen
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
public ref class CConnectionInfo
{
public:
  CConnectionInfo();
  ~CConnectionInfo();

  enum class ConnectionType{None,Server,Client};
  value struct ConnectionStatus
  {
    static String^ Waiting      = "Waiting";
    static String^ Connected    = "Connected";
    static String^ Disconnected = "Disconnected";
    static String^ Ready        = "Ready for receiving";
  };

  void setPort(int port);
  void setIpAddresse(String^ ipAddr);
  void setHostName(String^ hostName);
  void setConnectionType(ConnectionType type);
  void setConnectionTimeOut(long ctime_);
  long getConnectionTimeOut();
  int getPort();
  String^ getIpAddresse();
  String^ getHostName();
  ConnectionType getConnectionType();

private:
  //! Nummer des Ports
  int Port;
  //! IP - Adresse
  String^ IpAddr;
  //! Name des Hosts
  String^ HostName;
  //! Typ der Verbindung(Server, Client)
  ConnectionType Type;
  //! Wartezeit in Sekunden bevor der Verbindungsaubau 
  //! unterbrochen wird wenn keine Verbindung 
  long ConnnectionTimeOut;

};
#endif