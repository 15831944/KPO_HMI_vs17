// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELEGRAM_ADAPTER_40F7CBD100BB_INCLUDED
#define _INC_CTELEGRAM_ADAPTER_40F7CBD100BB_INCLUDED


#include <string>
#include <vector>
using namespace std;

#include "cCBS_StdEvent_Task.h"
#include "CSMC_DataProvider_Impl.h"
#include "CTelegram_DataProfile.h"

class CTelegram_Handler;

//////////////////////////////////////////////////
//
//This class is an adapter, access to telegram handler. The 
//telegram handler must be registered. Also provide this 
//class an incoming (source) and outgoing (target) interfaces 
//to map data in data handler. The method log() allows 
//logging of messages. Depends on direction of mapped data 
//the interfaces must be set correctly.
//
//////////////////////////////////////////////////
class CTelegram_Adapter 
{
public:
	bool doOnComplete(const std::string& Key, const std::string& TlgName);

	cCBS_StdFrame_Task* m_pTask;

	void log(const std::string& message, long Level);

	std::string m_SenderName;

	std::string m_DestinationName;

  std::vector<std::string> m_DestinationList;

	cCBS_StdEvent_Task* m_pEvent_Task;

	CSMC_DataProvider_Impl* m_pIntf_IN;

	CSMC_DataProvider_Impl* m_pIntf_OUT;

	CTelegram_Adapter(CSMC_DataProvider_Impl *pIntf_IN, CSMC_DataProvider_Impl *pIntf_OUT, cCBS_StdFrame_Task *pTask);

	virtual ~CTelegram_Adapter();

	bool registerHandler(CTelegram_Handler* NewHandler);

private:

	vector<CTelegram_Handler*> m_Telegram_Handler_List;

  void addTelegram_DataProfile(const std::string& TelegramID);

  bool checkTelegramFrequence(const std::string& TelegramID);
  map<std::string,CTelegram_DataProfile*> m_Telegram_DataProfile_List;

};

#endif /* _INC_CTELEGRAM_ADAPTER_40F7CBD100BB_INCLUDED */
