// Copyright (C) 2007 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELCOM_OUTPROT_45AC95300022_INCLUDED
#define _INC_CTELCOM_OUTPROT_45AC95300022_INCLUDED

#include "CTelcom_OutMsgTypeTranslator.h"

#include "SProt.h"

//##ModelId=45AC95300022
class CTelcom_OutProt : public SProt
{
public:
	//##ModelId=45AC95CC0045
	CTelcom_OutProt();

	//##ModelId=45AC95CC0225
	virtual ~CTelcom_OutProt();

	//##ModelId=45B4E3F3003E
	void switchConnection();

  std::string getStatisticsAsString();

protected:
	//##ModelId=45AE5F6B03A7
	void onConnectHook();

  void doOnConnectError(ETransport & ex, bool isTimeout);

	//##ModelId=45AE59C1036E
	CTelcom_OutMsgTypeTranslator m_MsgTypeTranlator;

	//Watchdog counter
	//##ModelId=45AE540E0118
	long m_WDCounter;

	//##ModelId=45AE53AE00D5
	virtual void doMakeWatchdog(TCMessage& wdog);

	// to conver number to string
	//##ModelId=45AE53F9017A
	 long translateType(std::string& _t);

   virtual int doHandleTlgError(TC_Exception & e, TCMessage & msg);

};

#endif /* _INC_CTELCOM_OUTPROT_45AC95300022_INCLUDED */
