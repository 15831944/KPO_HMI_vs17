#ifndef _cCBS_StdEventLogFrame_h_
#define _cCBS_StdEventLogFrame_h_

#include "cCBS_StdEventLog.h"


class cCBS_StdEventLogFrame: public cCBS_StdEventLog
{
public:
  cCBS_StdEventLogFrame(std::string sProcName = "", std::string sServiceName = "", std::string sContextName = "");
  virtual ~cCBS_StdEventLogFrame();

  long EL_EventReceived(const char * Sender, const char * Receiver, const char * Message);
  long EL_EventReceived(sEventLogMessage &EventLogMessage, const char * Sender, const char * Receiver, const char * Message);
  long EL_EventRejected(const char * Sender, const char * Receiver, const char * Message);
  long EL_EventRejected(sEventLogMessage &EventLogMessage, const char * Sender, const char * Receiver, const char * Message);
  long EL_EventHandled(const char * Sender, const char * Receiver, const char * Message);
  long EL_EventHandled(sEventLogMessage &EventLogMessage, const char * Sender, const char * Receiver, const char * Message);
  long EL_EventDispatched(const char * Sender, const char * Receiver, const char * Message);
  long EL_EventDispatched(sEventLogMessage &EventLogMessage, const char * Sender, const char * Receiver, const char * Message);
  long EL_EventHandlingError(const char * Sender, const char * Receiver, const char * Message, const char * ProductID);
  long EL_EventHandlingError(sEventLogMessage &EventLogMessage, const char * Sender, const char * Receiver, const char * Message, const char * ProductID);
  long EL_ErrorUsingFrameTask(const char * TaskName);
  long EL_ErrorUsingFrameTask(sEventLogMessage &EventLogMessage, const char * TaskName);
  long EL_ErrorConnectingEventChannel();
  long EL_ErrorConnectingEventChannel(sEventLogMessage &EventLogMessage);
  long EL_ReconnectingEventChannel();
  long EL_ReconnectingEventChannel(sEventLogMessage &EventLogMessage);
  long EL_ErrorTaskWorkingState();
  long EL_ErrorTaskWorkingState(sEventLogMessage &EventLogMessage);
  long EL_ErrorTaskRegistration();
  long EL_ErrorTaskRegistration(sEventLogMessage &EventLogMessage);
  long EL_ExceptionCaught(const char * Exception, const char * Function, const char * Action);
  long EL_ExceptionCaught(sEventLogMessage &EventLogMessage, const char * Exception, const char * Function, const char * Action);
  long EL_ExceptionThrown(const char * Exception, const char * Function, const char * Action);
  long EL_ExceptionThrown(sEventLogMessage &EventLogMessage, const char * Exception, const char * Function, const char * Action);
  long EL_DBWriteError(const char * Col, const char * Table, const char * Description);
  long EL_DBWriteError(sEventLogMessage &EventLogMessage, const char * Col, const char * Table, const char * Description);
  long EL_DBWriteInfo(const char * Col, const char * Table, const char * Description);
  long EL_DBWriteInfo(sEventLogMessage &EventLogMessage, const char * Col, const char * Table, const char * Description);
  long EL_DBReadError(const char * Col, const char * Table, const char * Description);
  long EL_DBReadError(sEventLogMessage &EventLogMessage, const char * Col, const char * Table, const char * Description);
  long EL_DBReadInfo(const char * Col, const char * Table, const char * Description);
  long EL_DBReadInfo(sEventLogMessage &EventLogMessage, const char * Col, const char * Table, const char * Description);
  long EL_LogMessage(const char * Message);
  long EL_LogMessage(sEventLogMessage &EventLogMessage, const char * Message);
  long EL_ProcessStarted(const char * ProcessName);
  long EL_ProcessStarted(sEventLogMessage &EventLogMessage, const char * ProcessName);
  long EL_ProcessStopped(const char * ProcessName);
  long EL_ProcessStopped(sEventLogMessage &EventLogMessage, const char * ProcessName);
  long EL_ErrorTaskControl(const char * TaskName, const char * ErrorMessage);
  long EL_ErrorTaskControl(sEventLogMessage &EventLogMessage, const char * TaskName, const char * ErrorMessage);
  long EL_ProcessTerminated(const char * TaskName, const char * ErrorMessage);
  long EL_ProcessTerminated(sEventLogMessage &EventLogMessage, const char * TaskName, const char * ErrorMessage);
  long EL_MemorySize(int MemorySize);
  long EL_MemorySize(sEventLogMessage &EventLogMessage, int MemorySize);
  long EL_ProcessStatusError(const char * ProcessName, const char * FreeMessage);
  long EL_ProcessStatusError(sEventLogMessage &EventLogMessage, const char * ProcessName, const char * FreeMessage);
  long EL_MutexAccessError(const char * MutexName, int ThreadId, const char * Function);
  long EL_MutexAccessError(sEventLogMessage &EventLogMessage, const char * MutexName, int ThreadId, const char * Function);
  long EL_MutexFreeError(int ThreadId, const char * Function);
  long EL_MutexFreeError(sEventLogMessage &EventLogMessage, int ThreadId, const char * Function);
  long EL_DBDeleteError(const char * Table, const char * Description);
  long EL_DBDeleteError(sEventLogMessage &EventLogMessage, const char * Table, const char * Description);
  long EL_DBDeleteInfo(const char * Table, const char * Description);
  long EL_DBDeleteInfo(sEventLogMessage &EventLogMessage, const char * Table, const char * Description);
  long EL_DBWriteWarning(const char * Col, const char * Table, const char * Description);
  long EL_DBWriteWarning(sEventLogMessage &EventLogMessage, const char * Col, const char * Table, const char * Description);
  long EL_DBReadWarning(const char * Col, const char * Table, const char * Description);
  long EL_DBReadWarning(sEventLogMessage &EventLogMessage, const char * Col, const char * Table, const char * Description);
  long EL_DBDeleteWarning(const char * Table, const char * Description);
  long EL_DBDeleteWarning(sEventLogMessage &EventLogMessage, const char * Table, const char * Description);
  long EL_DBConnectionError(const char * Function);
  long EL_DBConnectionError(sEventLogMessage &EventLogMessage, const char * Function);
  long EL_DBReconnectInfo(const char * Description);
  long EL_DBReconnectInfo(sEventLogMessage &EventLogMessage, const char * Description);
  long EL_CORBAReconnectInfo(const char * Description);
  long EL_CORBAReconnectInfo(sEventLogMessage &EventLogMessage, const char * Description);
  long EL_DBNullValueError(const char * Tablename, const char * Columns);
  long EL_DBNullValueError(sEventLogMessage &EventLogMessage, const char * Tablename, const char * Columns);
  long EL_ProcessRunDown(const char * ProcessName);
  long EL_ProcessRunDown(sEventLogMessage &EventLogMessage, const char * ProcessName);
protected:
  template <class T>
  static std::wstring __toWString__(const T& arg);
  static std::wstring __toWString__(const std::string& arg);
  template <class T>
  static std::string __toString__(const T& arg);
  static std::string __toString__(const std::string& arg);

  static void replaceNewlines( std::string &text );

protected:
  long lRetValue;
};

#endif
