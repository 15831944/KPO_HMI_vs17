// Copyright (C) 2007 SMS Demag AG

#include "cCBS_StdEventLogFrameController.h"

#include "CTelcom_TcpipTransport.h"
#include "cCBS_StdLog_Task.h"



//##ModelId=45ABB08401C1
CTelcom_TcpipTransport::CTelcom_TcpipTransport()
{
	// ToDo: Add your specialized code here and/or call the base class
}

//##ModelId=45ABB084038D
CTelcom_TcpipTransport::~CTelcom_TcpipTransport()
{
	// ToDo: Add your specialized code here and/or call the base class
}

//##ModelId=45ABB08E002D
void CTelcom_TcpipTransport::switchConnection()
{
  string newConnectInfo;

  if (getConnectInfo() == m_ConnectInfo1)
  {
    newConnectInfo = m_ConnectInfo2;
  }
  else
  {
    newConnectInfo = m_ConnectInfo1;
  }
  setConnectInfo(newConnectInfo);

  std::string Message;
  Message = "TcpipTransport: Change to " + getConnectInfo();
  cCBS_StdLog_Task::getInstance()->log(Message,3);
}

//##ModelId=45ABB08E004B
void CTelcom_TcpipTransport::configure(const std::string& section, bas::Configuration& c)
{
  // execute the configuration of the base class:
  TcpipTransport::configure(section, c);

  // record the current connect info string:
  m_ConnectInfo1 = getConnectInfo();

  // now evaluate additional
  // configuration parameters 'host2' and 'service2':
  c.setSection(section);
  std::string host2, service2;
  host2 = c.gets("host2", "");
  service2 = c.gets("service2", "");
  if (host2.length()>0)
      m_ConnectInfo2 = host2+":"+service2;

  // safe temporary
  std::string t = section;

  c.setSection("SMS_Definition");
  BigEndPlatf = c.getbool("BigEndian");
  isRedundancy = c.getbool("isRedundancy", false);
  // restore
  c.setSection(t);
}

void CTelcom_TcpipTransport::setConnectInfo(string info)
{
  TcpipTransport::setConnectInfo(info);
}

int CTelcom_TcpipTransport::receive(TCMessage & msg)
{
  int RetValue = 0;

  try
  {
    RetValue = TcpipTransport::receive(msg);
  }
  catch(ETransport &e)
  {
    std::string Action;
    Action = "Reading Telegram data for : ";
    Action += msg.getType();

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, e.what(), "CTelcom_TcpipTransport::receive(TCMessage& msg)",Action.c_str());

    throw e;
  }
  catch(...)
  {
    std::string Action;
    Action = "Reading Telegram data for : ";
    Action += msg.getType();

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "Unknown exception", "CTelcom_TcpipTransport::receive(TCMessage& msg)",Action.c_str());

    throw;
  }

  return RetValue;

}