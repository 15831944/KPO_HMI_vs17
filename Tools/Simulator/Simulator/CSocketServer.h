// Copyright 2006 SMS - Demag AG
#ifndef _CSocketServer_H_
#define _CSocketServer_H_
//-----------------------------------------------------
#include "CSocketConnection.h"
//-----------------------------------------------------
using namespace System::Threading;
//-----------------------------------------------------
//-----------------------------------------------------
// Name:  CSocketServer.h
// Descr: Mit dieser Klasse wird Socket Verbindung als Server
//        aufgebaut
// Date:
// Autor: Emeljanov Anatolij 
//------------------------------------------------------
public ref class CSocketServer : public CSocketConnection
{
	public:
			CSocketServer();
			~CSocketServer();
			virtual int buildConnection(String^ ipAddr,int port) override;
			virtual void waitingForConnection(long wtime_) override;
			virtual String^ getConnTyp() override;
			virtual bool disConnection() override;
      virtual bool isConnected() override;
	private:
			void waiting();
		  Socket^ SocketCon;
			Thread^ WaitClientThread;
};


#endif
