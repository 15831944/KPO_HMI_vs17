// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif

#ifndef _CTELCOM_ORAADAPTERAPP_H_
#define _CTELCOM_ORAADAPTERAPP_H_

#include "OraAdapterApp.h"

/** Base class for ORACLE based adapter process.
*/

class CTelcom_OraAdapterApp: public OraAdapterApp
{
public:
 /**
  * Construct an application object.
  * @param name unique application name; also used as the ORACLE session identifier.
  * @param ver  optinal version number
  */
  CTelcom_OraAdapterApp(const string& name="", const string& ver="");

  virtual ~CTelcom_OraAdapterApp();
  
  // IProtCallback implementation:
  virtual void reconfigure();

  virtual std::string getDbConnectStr();
  
protected:
  virtual void doDefineOptions(bas::CliCmdLine &cl);
  virtual void doProcessCmdLine(const bas::CliCmdLine &cl);
  virtual void doConfigure(bas::Configuration &cfg);
  virtual void doInit();
  virtual void doRun();
  virtual void doFinish();
};

#endif // CTELCOM_ORAADAPTERAPP_H_
