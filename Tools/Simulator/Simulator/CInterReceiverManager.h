// Copyright 2006 SMS - Demag AG
#ifndef _CInterReceiverManager_H_
#define _CInterReceiverManager_H_

//----------------------------------------------------
#include "CInterBaseManager.h"
#include "CTlgContainerWrapper.h"
#include "CTlgDecoderWrapper.h"
#include "CInterConfigWrapper.h"
#include "CExpWrapper.h"
//----------------------------------------------------
using namespace System::Threading;
//----------------------------------------------------
public delegate void NewTlgEventTyp(CItemWrapper^ tlg);
//----------------------------------------------------
public delegate void UpdateConnRecInfo();
//-------------------------------------------
// Name: CInterReceiverManager.h
// Descr: Realisiert das Verwalten einer Schnittstelle in
//        Empfangrichtung
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
public ref class CInterReceiverManager : public CInterBaseManager
{
	public:
			CInterReceiverManager(CTlgInterfaceWrapper^ InterMap,CInterConnection^ interConSock);
			CTlgContainerWrapper^ getTlgContainer();
			void setNewTlgEvent(NewTlgEventTyp^ event);
      void setUpdateConnRecInfo(UpdateConnRecInfo^ event);
			//! Mit dieser Methode werden Telegramme empfangen
            void receiveTlg();
	private:
			//! Container fuer Empfangene Telegramme
			CTlgContainerWrapper^ TlgContainer;
			//! Thread, in dem die Telegramme empfangen werden
			Thread^ ReceiverThread;
			//! ein Delegate - Objekt, fuer Benachrichtigung,
			//  wenn ein Telegramm empfangen wird
			NewTlgEventTyp^ NewTlgEvent;
      UpdateConnRecInfo^ RecInfo;
			//! Mit dieser Methode wird Empfang beendet
      void endReceive();
			void receive();
			void receive(String^ inter);
};



#endif
