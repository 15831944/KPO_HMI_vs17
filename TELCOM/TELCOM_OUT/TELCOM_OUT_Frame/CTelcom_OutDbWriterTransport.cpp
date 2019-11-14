// Copyright (C) 2011 SMS Siemag AG

#include "CTelcom_OutDbWriterTransport.h"
#include "TCMessage.h"
#include "cCBS_StdLog_Task.h"

CTelcom_OutDbWriterTransport::CTelcom_OutDbWriterTransport()
: CTelcom_DbWriterTransport()
{
	// ToDo: Add your specialized code here and/or call the base class
}

CTelcom_OutDbWriterTransport::~CTelcom_OutDbWriterTransport()
{
	// ToDo: Add your specialized code here and/or call the base class
}

void CTelcom_OutDbWriterTransport::configure(const std::string & section, bas::Configuration & c)
{
  // execute the configuration of the base class:
  CTelcom_DbWriterTransport::configure(section, c);

  // record the current connect info string:
  m_ConnectInfo = getConnectInfo();

  //CTelcom_OutTask::getInstance()->setWorking(true);
}

void CTelcom_OutDbWriterTransport::send(const TCMessage & msg)
{
  std::string Message;
  Message = "CTelcom_OutDbWriterTransport:send(const TCMessage & msg)";

  CTelcom_DbWriterTransport::send(msg);
 
  cCBS_StdLog_Task::getInstance()->log(Message,3);
}

int CTelcom_OutDbWriterTransport::doConnect()
{
  std::string Message;
  Message = "CTelcom_OutDbWriterTransport::doConnect()";

  int ReturnValue = DbWriterTransport::doConnect();

  if ( ReturnValue == 0 )
  {
    CTelcom_DbWriterTransport::setConnectInfo(m_ConnectInfo);
  }
  else
  {
    Message += " failed";
  }
  
  cCBS_StdLog_Task::getInstance()->log(Message,3);

  return ReturnValue;
}

int CTelcom_OutDbWriterTransport::doListen()
{
  int ReturnValue = DbWriterTransport::doListen();

  CTelcom_DbWriterTransport::setConnectInfo(m_ConnectInfo);

  std::string Message;
  Message = "CTelcom_OutDbWriterTransport::doListen()";
  cCBS_StdLog_Task::getInstance()->log(Message,3);

  return ReturnValue;
}

int CTelcom_OutDbWriterTransport::doDisconnect()
{
  int ReturnValue = DbWriterTransport::doDisconnect();

  if (ReturnValue == -1)
  {
    cCBS_StdLog_Task::getInstance()->log("CTelcom_OutDbWriterTransport::doDisconnect: Dis-Connection timeout.", 1);
  }
  else
  {
    cCBS_StdLog_Task::getInstance()->log("CTelcom_OutDbWriterTransport::doDisconnect: Dis-Connected!", 1);
  }

  return ReturnValue;
}

void CTelcom_OutDbWriterTransport::setConnectInfo(string info)
{
  std::string Message;
  Message = "CTelcom_OutDbWriterTransport::setConnectInfo(string info)";

  if ( !info.empty() &&  m_ConnectInfo != info)
  {
    m_ConnectInfo = info;
    DbWriterTransport::setConnectInfo(info);
    Message = "CTelcom_OutDbWriterTransport::setConnectInfo: Change to " + info;
  }
  else
  {
    Message += "CTelcom_OutDbWriterTransport::setConnectInfo: Value equal to previous value " + info;
  }
  
  cCBS_StdLog_Task::getInstance()->log(Message,3);
}