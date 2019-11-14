// Copyright (C) 2011 SMS Siemag AG

#include "basApp.h"
#include "CTelcom_InDbWriterTransport.h"
// Interface zu JAVA
#include "JIF.h"
#include "TCMessage.h"
#include "TCTrace.h"

#include "cCBS_StdLog_Task.h"

#define READERCLASS "com/psibt/dbengine2/content/DBReader"

//sankar
#include "cCBS_StdDB_Task.h" 
#include "cbs.h"
#include "CCBS_StdInitBase.h" 
#include "CTelcom_InTask.h"

bool ExternalDatabaseConnection = true;
cCBS_StdConnection* pStdConnection ;
cCBS_Connection* pCBSConnection;
std::string External_DBName = "";
std::string External_DBUser = "";
std::string External_DBPassword = "";

CTelcom_InDbWriterTransport::CTelcom_InDbWriterTransport()
: CTelcom_DbWriterTransport()
{
	// ToDo: Add your specialized code here and/or call the base class
  javaclass = READERCLASS;
  myclassname = "CTelcom_InDbWriterTransport";


  //sankar
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EXTERNAL_DATABASE","DBName",External_DBName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EXTERNAL_DATABASE","DBUser",External_DBUser);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EXTERNAL_DATABASE","DBPassword",External_DBPassword);

}

CTelcom_InDbWriterTransport::~CTelcom_InDbWriterTransport()
{
	// ToDo: Add your specialized code here and/or call the base class
}

void CTelcom_InDbWriterTransport::configure(const std::string & section, bas::Configuration & c)
{
  // execute the configuration of the base class:
  CTelcom_DbWriterTransport::configure(section, c);

  // record the current connect info string:
  m_ConnectInfo = getConnectInfo();

  addJavaParam(c, CFG_RECEIVETIMEOUT);
  addJavaParam(c, CFG_POLLINTERVAL);

  //CTelcom_OutTask::getInstance()->setWorking(true);
}

void CTelcom_InDbWriterTransport::send(const TCMessage & msg)
{
  BASASSERT2(false, "CTelcom_InDbWriterTransport::send not allowed");
}

void CTelcom_InDbWriterTransport::confirm(bool ok)
{
  if (traceLevel>0) 
  {
    TCTrace<<"("<<myclassname<<") "<<"confirm("<<ok<<")"<<bas::endlog;
  }

  if (!ok)
  {
    return;
  }

  string dummy = callJava(javaclass, "confirm");
}

int CTelcom_InDbWriterTransport::receive(TCMessage & msg)
{
  {if (traceLevel>0) TCTrace<<"("<<myclassname<<") "<<"receive"<<bas::endlog;};

  string msgbody;
  string msgtype;
  JIF&   jif = JIF::instance();

  const char* param = "";

  //msgtype = jif.callMethod(READERCLASS, "receive", param);
  msgtype = callJava(javaclass, "receive", param);
  if (msgtype.size() == 0)
    return -1; // timeout

  // fetch tlg body from java:
  msgbody = callJava(javaclass, "getTlgBody");

  msg.clear();
  msgtype = bas::Txt::trim(msgtype);
  msg.setType(msgtype);
  //msg.setSender read frpm rprot setting;
  msg.setSendTime(bas::Time::now());

  TCMessage &msgHeader = msg;
  msgHeader.setType("Head");

  msg.setHeader(msgHeader);

  int RetValueLen = msgbody.size();
  msg.writeBuf(msgbody.c_str(), RetValueLen); 

  std::string Message;

  Message = "CTelcom_InDbWriterTransport:receive(const TCMessage & msg)";

  cCBS_StdLog_Task::getInstance()->log(Message,3);

  return RetValueLen;
}

int CTelcom_InDbWriterTransport::doConnect()
{
  std::string Message;
  Message = "CTelcom_InDbWriterTransport::doConnect()";

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

int CTelcom_InDbWriterTransport::doListen()
{
  int ReturnValue = DbWriterTransport::doListen();

  CTelcom_DbWriterTransport::setConnectInfo(m_ConnectInfo);

  std::string Message;
  Message = "CTelcom_InDbWriterTransport::doListen()";
  cCBS_StdLog_Task::getInstance()->log(Message,3);

  return ReturnValue;
}

int CTelcom_InDbWriterTransport::doDisconnect()
{
  int ReturnValue = DbWriterTransport::doDisconnect();

  if (ReturnValue == -1)
  {
    cCBS_StdLog_Task::getInstance()->log("CTelcom_InDbWriterTransport::doDisconnect: Dis-Connection timeout.",3);
  }
  else
  {
    cCBS_StdLog_Task::getInstance()->log("CTelcom_InDbWriterTransport::doDisconnect: Dis-Connected!",3);
  }

	
  //sankar
	CBS::shutdown();
	//externalDBConnection();

  return ReturnValue;
}

void CTelcom_InDbWriterTransport::setConnectInfo(string info)
{
  std::string Message;
  Message = "CTelcom_InDbWriterTransport::setConnectInfo(string info)";

  if ( !info.empty() &&  m_ConnectInfo != info)
  {
    m_ConnectInfo = info;
    DbWriterTransport::setConnectInfo(info);
    Message = "CTelcom_InDbWriterTransport::setConnectInfo: Change to " + info;
  }
  else
  {
    Message += "CTelcom_InDbWriterTransport::setConnectInfo: Value equal to previous value " + info;
  }
  
  cCBS_StdLog_Task::getInstance()->log(Message,3);
}

void CTelcom_InDbWriterTransport::externalDBConnection()
{
	/*CTelcom_InTask::getInstance()->getTask()->setWorking(false); *///ffra 31102018
	cCBS_Statement* selectStatement = 0;
	try
  {  
		cCBS_StdDB_Task* pDB_Task = cCBS_StdDB_Task::getInstance();
		if(pDB_Task)
		{
			pStdConnection = pDB_Task->getCBS_StdConnection(External_DBName,External_DBUser,External_DBPassword);		
			pCBSConnection = pStdConnection->getpCBSConnection();

			if(pCBSConnection)
				selectStatement = pCBSConnection->createPtStatement();
			else
			{
				cCBS_StdDB_Task::getInstance()->freeConnections();
				ExternalDatabaseConnection = false;
				return;
			}
		
			std::string sql =  "select count(*) from dual ;" ;
			selectStatement = pCBSConnection->createPtStatement();
			if(selectStatement->executePtQuery(sql))
			{
				if(ExternalDatabaseConnection == false)
				{
					CBS::shutdown();
				}
				ExternalDatabaseConnection = true;
			}
			
		} //if(pDB_Task...

	}
	catch(cCBS_DBExc_ConnectionError &cExc) 
  {
		cCBS_StdLog_Task::getInstance()->log("--- externalDBConnection: external database connection error.. ---",3);
		ExternalDatabaseConnection = false;
    try
    {
			cCBS_StdLog_Task::getInstance()->log("--- externalDBConnection: RECONNECT.. ---",3);
      pStdConnection->reconnect();
      pCBSConnection = pStdConnection->getpCBSConnection();
    }
    catch (...)
    {
       cCBS_StdLog_Task::getInstance()->log("--- externalDBConnection: pStdConnection->reconnect....database connection problem ---",3);
    }
		if   (selectStatement)  {pCBSConnection->freeStatement(selectStatement);  selectStatement=0;}
  }

  catch (cCBS_DBExc &e)
  {
		cCBS_StdLog_Task::getInstance()->log("--- externalDBConnection: Unexpected exception caught.. ---",3);
		if   (selectStatement)  {pCBSConnection->freeStatement(selectStatement);  selectStatement=0;}
  }
  catch (...)
  {
     cCBS_StdLog_Task::getInstance()->log("--- externalDBConnection: Unexpected exception caught.. ---",3);
     if   (selectStatement)  {pCBSConnection->freeStatement(selectStatement);  selectStatement=0;}
  }

}
