// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif

#ifndef _CTELCOM_OUTDBWRITERTRANSPORT_H
#define _CTELCOM_OUTDBWRITERTRANSPORT_H

#include "CTelcom_DbWriterTransport.h"

/**
Transport for sending telegrams via database tables.
Telegrams are passed in CSV format.
<br>
Database operations ans telegram conversion are performed by a
Java Component. The JVM is automatically created when <tt>connect</tt> is called.
<br>
*/
class CTelcom_OutDbWriterTransport : public CTelcom_DbWriterTransport 
{
public:
  CTelcom_OutDbWriterTransport();

  virtual ~CTelcom_OutDbWriterTransport();

  virtual void configure(const std::string& section, bas::Configuration& c);

protected:
  /** Send specified telegram by writing into the associated database tables. */
  virtual void send(const TCMessage & msg);

  /** connect implementation (from AbstractTransport ) */
  virtual int doConnect();

  /** listen implementation (from AbstractTransport ) */
  virtual int doListen();

  /** disconnect implementation (from AbstractTransport ) */
  virtual int doDisconnect();

public:
  /** Set connection information used by <I>connect</I> and <I>listen</I>.*/
  virtual void setConnectInfo(string info);

private:
  std::string m_ConnectInfo;

};
#endif //_CTELCOM_OUTDBWRITERTRANSPORT_H
