// Copyright 2006 SMS - Demag AG
#ifndef _CInterSenderManager_H_
#define _CInterSenderManager_H_

//-------------------------------------------------------------
#include "CInterBaseManager.h"
#include "CTlgLogFileReaderWrapper.h"
//-------------------------------------------------------------
//-------------------------------------------
// Name: CInterSenderManager.h
// Descr: Realisiert das Verwalten einer Schnittstelle in
//        Senderrichtung
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
public ref class CInterSenderManager : public CInterBaseManager
{
	public:
		CInterSenderManager(CTlgInterfaceWrapper^ InterMap,CInterConnection^ interConSock);
		//! prueft, ob angegebene Telegramm - Log -File zu der
		//  Schnittstelle passt
    bool checkInterface(String^ path);
    String^ getInterfaceName();
		//! Liest ein Telegramm - Log - File
		int loadLogFile(String^ path,const bool &abort);
		CTlgLogFileReaderWrapper^ getLogFileContainer();
		//! verschieckt Daten ueber Socket - Verbindung 
		int sendBytes(unsigned char* bytes,int len);
		//!	loescht Telegramme in Cintainer fuer Tellegramm - Log - File
		void clearLogFile();
    //!
    bool isLogFileLoad();
    //!
    CInterConnection^ getInterConn (void);
    //!
    int getTlgCount();
  private:
		//! Container mit Telegrammen aus einem Telegramm - Log -File
    CTlgLogFileReaderWrapper^ LogFileReader;
    //!
    Threading::Thread^ RecThr;
    //!
    void InvokeReceiveThread(bool start);
    void receive();

};

#endif