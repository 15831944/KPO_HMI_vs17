// Copyright (C) 2009 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELCOM_CORBAMSGPROCESSOR_45AB5D570281_INCLUDED
#define _INC_CTELCOM_CORBAMSGPROCESSOR_45AB5D570281_INCLUDED

#include "iDH_Telcom_s.hh"
#include "telcom.h"
#include "CBS_CorbaLib\cCBS_CorbaProxy.h"
#include "BASIntrf_s.hh"


class CTelcom_Task;

class CTelcom_CorbaMsgProcessor : public MsgProcessor
{
protected:
	CTelcom_Task* m_pTelcom_Task;

  cCBS_Corba m_CorbaModifiers;
  cCBS_CorbaProxy<IBAS::BASIntrf> m_IBASProxy;
	virtual int processTlg(TCMessage& msg);

private:

	std::string m_ServerName;


	TlgFactory* m_pFactory;

	int forwardMessage(const std::string& TlgType, Tlg& theTlg, DH_Telcom::iDH_Telcom_var pCorbaInf);

	int writeToInterface(const std::string& DataKey, const TlgElem& te, DH_Telcom::iDH_Telcom_var pCorbaInf);

  void writeToIBAS(Tlg& theTlg);

public:
  static long OK;
  static long TlgError;
  static long UnknownTlgError;
  static long CorbaError;
  static long CorbaConnectionError ;
  static long TelcomError;
  static long TAMError;
  static long FactoryError;

	void setpTelcom_Task(CTelcom_Task* value);

	CTelcom_CorbaMsgProcessor();

	void setFactory(TlgFactory* Factory);

	//Here you can read ini file.
	void configure(const std::string& section, Configuration& c);

	CTelcom_CorbaMsgProcessor(CTelcom_Task * Telcom_task);

	virtual ~CTelcom_CorbaMsgProcessor();

};

#endif /* _INC_CTELCOM_CORBAMSGPROCESSOR_45AB5D570281_INCLUDED */
