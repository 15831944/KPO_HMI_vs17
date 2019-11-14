// Copyright 2006 SMS - Demag AG
#ifndef _CSocketClient_H_
#define _CSocketClient_H_
//----------------------------------------------------
#include "CSocketConnection.h"
//-----------------------------------------------------
// Name:  CSocketServer.h
// Descr: Mit dieser Klasse wird Socket Verbindung als Client
//        aufgebaut
// Date:
// Autor: Emeljanov Anatolij 
//------------------------------------------------------
public ref class CSocketClient : public CSocketConnection
{
	public:
			CSocketClient();
			~CSocketClient();
			virtual int buildConnection(String^ ipAddr,int port) override;
			virtual void waitingForConnection(long wtime_) override;
			virtual String^ getConnTyp() override;
			virtual bool disConnection() override;
      virtual bool isConnected() override;
	private:
		   void waiting();
};
#endif