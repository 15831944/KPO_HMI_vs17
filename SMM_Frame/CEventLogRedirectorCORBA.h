// Copyright (C) 1999 - 2000 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEVENTLOGREDIRECTORCORBA_45F567E9029A_INCLUDED
#define _INC_CEVENTLOGREDIRECTORCORNA_45F567E9029A_INCLUDED

#include "CEventLogRedirector.h"
#include "CSMM_ModelTask.h"

class cCBS_StdEventLogFrame;


class CEventLogRedirectorCORBA 
: public CEventLogRedirector
{
public:
  CEventLogRedirectorCORBA(CSMM_ModelTask * pModelTask);

  virtual ~CEventLogRedirectorCORBA();

  virtual void handleMessage(int id, int severity, const std::string& m1, const std::string& m2, const std::string& m3, const std::string& file, long line, const std::string& out, const std::string& OutPutSpec, const std::string& FreeText, long Destination, int opAckn);

  virtual void handleMessage(int id, int severity, const std::string& m1, const std::wstring& m2, const std::string& m3, const std::string& file, long line, const std::string& out, const std::string& OutPutSpec, const std::string& FreeText, long Destination, int opAckn);

  virtual void handleMessage(int id, int severity, const std::string& m1, const std::string& m2, const std::string& m3, const std::string& file, long line, const std::string& out, const std::string& OutPutSpec, const std::string& FreeText, long Destination);

  virtual void handleMessage(int id, int severity, const std::string& m1, const std::wstring& m2, const std::string& m3, const std::string& file, long line, const std::string& out, const std::string& OutPutSpec, const std::string& FreeText, long Destination);


private:
  cCBS_StdEventLogFrame *m_pEventLog;

  CSMM_ModelTask * m_pModelTask;

  // to be independent of old style of event logs and event log server v1
  // original definition was in errorlog.h from CBS
  enum {E_TEST=0, E_INFO=8,E_WARNING=16, E_ERROR=24, E_FATAL_ERROR=40};

};

#endif /* _INC_CEVENTLOGREDIRECTORCORBA_45F567E9029A_INCLUDED */
