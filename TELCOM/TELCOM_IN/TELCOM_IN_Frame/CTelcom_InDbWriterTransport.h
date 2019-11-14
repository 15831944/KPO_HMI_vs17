// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif

#ifndef _CTelcom_InDbWriterTransport_H
#define _CTelcom_InDbWriterTransport_H

#include "CTelcom_DbWriterTransport.h"

/** Configuration parameter (receive timeout [sec]) */
char * const CFG_RECEIVETIMEOUT   = "receiveTimeout";

/** Configuration parameter (poll interval [sec]) */
char * const CFG_POLLINTERVAL     = "pollInterval";

/**
Transport for sending telegrams via database tables.
Telegrams are passed in CSV format.
<br>
Database operations ans telegram conversion are performed by a
Java Component. The JVM is automatically created when <tt>connect</tt> is called.
<br>
*/
class CTelcom_InDbWriterTransport : public CTelcom_DbWriterTransport 
{
public:
  CTelcom_InDbWriterTransport();

  virtual ~CTelcom_InDbWriterTransport();

protected:
  virtual void configure(const std::string& section, bas::Configuration& c);

  /**
  * Confirm the last received telegram by updating/deleting the
  * corresponding records in the communication tables.
  * (For receivers only) Confirm last received message.
  * <br>The default implementation is a NO-OP.
  * <br>This method should be implemented by transport classes which support
  * some kind of 'delayed confirmation' of messages. E.g.
  * queueing systems may allow re-reading the same message
  * several times until the message is explicitly confirmed
  * (i.e. removed from the queue).
  * <br>The receiveLoop calls <code>confirm</code>
  * immediately after the MsgReceiver's <code>onMessage</code> method.
  * The return value returned by onMessage is passed in the parameter
  * <i>ok</i>.
  *
  * @param ok true: Message processed, false: repeat message.
  */
  virtual void confirm(bool ok);

  //** send not allowed */
  virtual void send(const TCMessage & msg);

  /** Not allowed. Calling this will throw an exception. */
  /** Wait for message to arrive in the associated database communication tables.
  * @param msg Message object where received message will be stored.
  * @return length of body of received message in bytes or -1 in case of timeout
  */
  virtual int receive(TCMessage & msg);

  /** connect implementation (from AbstractTransport ) */
  virtual int doConnect();

  /** listen implementation (from AbstractTransport ) */
  virtual int doListen();

  /** disconnect implementation (from AbstractTransport ) */
  virtual int doDisconnect();

public:
  /** Set connection information used by <I>connect</I> and <I>listen</I>.*/
  virtual void setConnectInfo(string info);
	void externalDBConnection(); //sankar
private:
  std::string m_ConnectInfo;

};
#endif //_CTelcom_InDbWriterTransport_H
