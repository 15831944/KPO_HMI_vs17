// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif

#ifndef _CTELCOM_DBWRITERTRANSPORT_H
#define _CTELCOM_DBWRITERTRANSPORT_H

#include "DbWriterTransport.h"

/**
Transport for sending telegrams via database tables.
Telegrams are passed in CSV format.
<br>
Database operations ans telegram conversion are performed by a
Java Component. The JVM is automatically created when <tt>connect</tt> is called.
<br>
*/
class CTelcom_DbWriterTransport : public DbWriterTransport 
{
public:
  CTelcom_DbWriterTransport();

  virtual ~CTelcom_DbWriterTransport();

protected:
  /** Send specified telegram by writing into the associated database tables. */
  virtual void send(const TCMessage & msg) ;

  /** 'Configurable' implementation. */
  virtual void configure(const std::string& section, bas::Configuration& c);

};
#endif //_CTELCOM_DBWRITERTRANSPORT_H
