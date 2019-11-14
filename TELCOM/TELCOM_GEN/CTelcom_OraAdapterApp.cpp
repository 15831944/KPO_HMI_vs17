// Copyright (C) 2011 SMS Siemag AG

#include "CTelcom_OraAdapterApp.h"
#include "cCBS_StdLog_Task.h"


CTelcom_OraAdapterApp::CTelcom_OraAdapterApp(const string& name, const string& ver)
: OraAdapterApp(name, ver)
{
	std::string Message;
  Message = "CTelcom_OraAdapterApp::CTelcom_OraAdapterApp(const string& name, const string& ver)";
  Message += " Name = " + name + "; TelcomVersion = " + ver + ";" ;
  cCBS_StdLog_Task::getInstance()->log(Message,1);
}

CTelcom_OraAdapterApp::~CTelcom_OraAdapterApp()
{
	// ToDo: Add your specialized code here and/or call the base class
}

void CTelcom_OraAdapterApp::reconfigure()
{
  std::string Message;
  Message = "CTelcom_OraAdapterApp::reconfigure()";

  OraAdapterApp::reconfigure();

  cCBS_StdLog_Task::getInstance()->log(Message,3);
}

std::string CTelcom_OraAdapterApp::getDbConnectStr()
{
  std::string RetValue = "";

  bas::OraSession& oraSession = OraAdapterApp::getSession();

  RetValue = oraSession.getUser() + "@" +  oraSession.getInstance();

  return RetValue;
}

void CTelcom_OraAdapterApp::doDefineOptions(bas::CliCmdLine &cl)
{ 
  std::string Message;
  Message = "CTelcom_OraAdapterApp::doDefineOptions(bas::CliCmdLine &cl)";

  OraAdapterApp::doDefineOptions(cl);
  
  std::string db_con_str = cl.getItem("db_con_str");

  cCBS_StdLog_Task::getInstance()->log(Message,3);
}

void CTelcom_OraAdapterApp::doProcessCmdLine(const bas::CliCmdLine &cl)
{
  std::string Message;
  Message = "CTelcom_OraAdapterApp::doProcessCmdLine(bas::CliCmdLine &cl)";

  OraAdapterApp::doProcessCmdLine(cl);

  std::string db_con_str = cl.getItem("db_con_str");
  
  cCBS_StdLog_Task::getInstance()->log(Message,3);
}

void CTelcom_OraAdapterApp::doConfigure(bas::Configuration &cfg)
{
  OraAdapterApp::doConfigure(cfg);

  cfg.setSection("SMS_Transport");

  std::string strTransportProtocol = cfg.gets("transportProtocol");

  std::string Message;
  Message = "CTelcom_OraAdapterApp::doConfigure(bas::Configuration &cfg)";
  Message += " DataBase [" + getDbConnectStr() + "]";

  cCBS_StdLog_Task::getInstance()->log(Message,3);
}

void CTelcom_OraAdapterApp::doInit()
{
  std::string Message;
  Message = "CTelcom_OraAdapterApp::doInit()";

  bas::OraSession& oraSession = OraAdapterApp::getSession();

  struct sqlca& SqlHandle = oraSession.getSQLCAHandle();

  int sqlCode = SqlHandle.sqlcode;

  std::string strSqlMessage = std::string(SqlHandle.sqlerrm.sqlerrmc);

  if ( !strSqlMessage.empty() )
  {
    Message += " SqlMessage = " + strSqlMessage + "; ";

    //ORA-01403: no data found
    //ORA-00942: table or view does not exist
    //Telcom OraApp required general tables (e.g tc_process)
    //..\packages\telcom_EAI\telcom\lib\plsql\transport
    //load.sql
    cCBS_StdLog_Task::getInstance()->log(Message,3);
  }
	
  OraAdapterApp::doInit();

  Message += " DataBase [" + getDbConnectStr() + "] is";

  if ( oraSession.isConnected() )
  {
    Message += " connected";
  }
  else
  {
    Message += " not connected";
  }

  cCBS_StdLog_Task::getInstance()->log(Message,3);
}

void CTelcom_OraAdapterApp::doRun()
{
  // run the application
  OraAdapterApp::doRun();
}

void CTelcom_OraAdapterApp::doFinish()
{
  std::string Message;
  Message = "CTelcom_OraAdapterApp::doFinish()";

  OraAdapterApp::doFinish();

  Message += " DataBase [" + getDbConnectStr() + "] is";

  if ( OraAdapterApp::getSession().isConnected() )
  {
    Message += " connected";
  }
  else
  {
    Message += " not connected";
  }

  cCBS_StdLog_Task::getInstance()->log(Message,3);
}