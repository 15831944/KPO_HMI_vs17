#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTelcom_OracleTransport_4370B1A202C3_INCLUDED
#define _INC_CTelcom_OracleTransport_4370B1A202C3_INCLUDED

//#include <fstream>
//#include <iostream>
#include <map>
#include "telcom.h"
#include "transport.h"
#include "CTelcom_OdbcStoredFunction.h"

//////////////////////////////////////////////////
//
// This class is used to communicate
// connects to the database and can communicate with stored functions 
// 
// Configuration for this is in ini
// see: configure
//
//////////////////////////////////////////////////
class CTelcom_OracleTransport : public AbstractTransport
{
public:

	CTelcom_OracleTransport();

  void setHeaderTlgType(std::string headName);

	void setFactory(TlgFactory* Factory);

	virtual ~CTelcom_OracleTransport();


protected:

  long m_TraceLevel;

  //To create tlgs
  TlgFactory* m_pFactory;

  virtual void configure(const std::string & section, bas::Configuration & c);

  virtual int doConnect();

  virtual int  receive(TCMessage & msg);

  virtual void send(const TCMessage & msg);

  virtual int doDisconnect();

  virtual int doListen();

  std::string m_ConnectInfo;

  //Connection retry interval.
  int m_retryInterval;

  bool finishedProcessing;

  bool showContent(Tlg& tlg, const std::string & MessageType, long level);

  CTelcom_OdbcStoredFunction* m_pStoredFunction;

private:

  bool logTelegram(const TlgElem& te, const std::string & MessageType);

  std::string anlUser;

  std::string anlPassword;

  std::string anlService;

protected:
  
  std::string m_LocalMsgFormat;

  std::string m_RemoteMsgFormat;

};

#endif /* _INC_CTelcom_OracleTransport_4370B1A202C3_INCLUDED */