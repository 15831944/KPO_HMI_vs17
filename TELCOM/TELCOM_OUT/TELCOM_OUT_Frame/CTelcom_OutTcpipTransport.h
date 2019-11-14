// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELCOM_OUTTCPIPTRANSPORT_45AB55D30135_INCLUDED
#define _INC_CTELCOM_OUTTCPIPTRANSPORT_45AB55D30135_INCLUDED

#include "CTelcom_TcpipTransport.h"

class CTelcom_OutTask;

class CTelcom_OutTcpipTransport : public CTelcom_TcpipTransport
{
  friend class CTelcom_OutProt;
public:
	CTelcom_OutTcpipTransport();

	virtual ~CTelcom_OutTcpipTransport();
  
  //overwrite switch connection to allow control of the out interface from the in interface
  void switchConnection();

protected:
	int doDisconnect();

	//Check on DH_XX_L1_IN which CPU is active and 
	// depends on this info set ConnectInfo
	bool checkAndSetRightConnection();

	//First check appropriate connection if more than one 
	//(redundant CPUs) connection available.
	int doConnect();

	//First check appropriate connection if more than one 
	//(redundant CPUs) connection available.
	int doListen();

  virtual void configure(const std::string& section, bas::Configuration& c);

  bool isConnectionControlledByIn;

  /** Send a message. (from AbstractTransport) */
  virtual void send(const TCMessage & msg);
};

#endif /* _INC_CTELCOM_OUTTCPIPTRANSPORT_45AB55D30135_INCLUDED */
