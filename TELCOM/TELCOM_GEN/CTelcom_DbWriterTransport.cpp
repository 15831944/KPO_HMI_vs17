// Copyright (C) 2011 SMS Siemag AG

#include "CTelcom_DbWriterTransport.h"

#include "TCMessage.h"

#include "CSMC_EventLogFrameController.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdLog_Task.h"

CTelcom_DbWriterTransport::CTelcom_DbWriterTransport()
: DbWriterTransport()
{
	// ToDo: Add your specialized code here and/or call the base class
}

CTelcom_DbWriterTransport::~CTelcom_DbWriterTransport()
{
	// ToDo: Add your specialized code here and/or call the base class
}

void CTelcom_DbWriterTransport::configure(const std::string& section, bas::Configuration& c)
{
  // execute the configuration of the base class:
  DbWriterTransport::configure(section, c);
}

void CTelcom_DbWriterTransport::send(const TCMessage & msg)
{
  std::string Function = "CTelcom_DbWriterTransport::send(const TCMessage & msg)";

  try
  {
    std::string Message = "";
    Message += "  Msg type is "      + msg.getType();
    Message += ", Msg BufString is " + msg.getBufString();

    DbWriterTransport::send(msg);

    //Message += ", Msg BufFormat is " + msg.getBufFormat();
    //Message += ", Msg ErrorInfo is " + msg.getErrorInfo();
    
    cCBS_StdLog_Task::getInstance()->log(Message,3);
  }
  catch(...)
  {
    //std::string test = e.what();
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, msg.getBufString().c_str(), Function.c_str(), msg.getErrorInfo().c_str());
  }
}