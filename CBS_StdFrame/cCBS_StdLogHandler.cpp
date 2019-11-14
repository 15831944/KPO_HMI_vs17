// Copyright (C) 2011 SMS Siemag AG

#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "cCBS_StdLogHandler.h"

cCBS_StdLogHandler::cCBS_StdLogHandler()
{
}

cCBS_StdLogHandler::~cCBS_StdLogHandler()
{
}

long cCBS_StdLogHandler::m_FileType = 1;

long cCBS_StdLogHandler::m_EventLogType = 2;

long cCBS_StdLogHandler::m_DisplayType = 0;

long cCBS_StdLogHandler::m_AsyncFileType = 3;

std::string cCBS_StdLogHandler::getType()
{
  std::string LogHandlerType;
  if ( m_Type == m_AsyncFileType )
  {
    LogHandlerType = "AsyncFile";
  }
  else if ( m_Type == m_FileType )
  {
    LogHandlerType = "File";
  }
  else if ( m_Type == m_EventLogType )
  {
    LogHandlerType = "EventLog";
  }
  else if ( m_Type == m_DisplayType)
  {
    LogHandlerType = "Display";
  }
  return LogHandlerType;
};
