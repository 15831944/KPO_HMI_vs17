// Copyright 2006 SMS - Demag AG

#ifndef _CInterBaseManager_H_
#define _CInterBaseManager_H_
//---------------------------------------------
#include "CTlgInterfaceWrapper.h"
#include "CInterConnection.h"
#include "CItemWrapper.h"
//---------------------------------------------
using namespace System;
//-------------------------------------------
//-------------------------------------------
// Name: CInterBaseManager.h
// Descr: Basisklasse fuer Klasse CInterSenderManager
//        CInterReceiverManager
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
public delegate void MessageHandlerSendRecTyp(String^ mess, int flag);
//--------------------------------------------
public ref class CInterBaseManager
{
	public:
		CInterBaseManager(CTlgInterfaceWrapper^ InterMap,CInterConnection^ interConSock);
    String^ getInterfaceDescr();
    String^ getInterfaceVersion();
		String^ getInterfaceName();
		//! gibt die Konfiguration der Verbindung zurueck
		void getHostInfo(String^& host,String^& ip,int* port);
		CTlgInterfaceWrapper^ getInterProtoSet();
    //! erzeigt ein neues Telegramm
		CItemWrapper^ makeTlg(String^ name);
		//! true, wenn die Verbindung in Zustand Connected
     bool isConnected();
		//! true, wenn die Verbindung in Zustand Waiting
		bool isWaiting();
		//! Typ der Verbindung(Server, Client)
    String^ getConnectionTyp();
    void setMessageHandler(MessageHandlerSendRecTyp^ handler);
	protected:
		//! Enthaelt Telegrammprototyps einer Schnittstelle
		CTlgInterfaceWrapper^ InterSet;
		//! Mit diesem Attribut wird Socket - Verbindung aufgebaut
		CInterConnection^ InterConn;
    MessageHandlerSendRecTyp^ MessageHandler;
};
#endif
