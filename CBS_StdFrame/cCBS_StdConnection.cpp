// Copyright (C) 1999 - 2004 SMS Demag AG

//##ModelId=4117630B002C
#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "cCBS_StdEventLogFrameController.h"

#include "cCBS_StdDB_Task.h"
#include "cCBS_StdConnection.h"



//##ModelId=4117630B002C
 std::string& cCBS_StdConnection::getLogin()
{
	return m_Login;
}

//##ModelId=411763170069
 std::string& cCBS_StdConnection::getUrl()
{
	return m_Url;
}

//##ModelId=4117631D03D9
 std::string& cCBS_StdConnection::getPassword()
{
	return m_Password;

}



//##ModelId=41177009007C
cCBS_StdConnection::cCBS_StdConnection(cCBS_DriverManager * DriverManager, cCBS_ODBCDriver  * Driver, const std::string  & Url, const std::string  & Login, const std::string &Password)
: m_pDriverManager(DriverManager)
, m_pODBCDriver(Driver)
, m_Url(Url)
, m_Login(Login)
, m_Password(Password)
, m_pCBSConnection(0)
{
  establishNewConnection();
}

void cCBS_StdConnection::revokeConnection()
{
  try
  {
    if (m_pDriverManager && m_pCBSConnection)
    {
  	  m_pDriverManager->freeConnection(m_pCBSConnection);
    }
  }
  catch(cCBS_DBExc& e)
  {
    std::string msg = e.getText();
    size_t pos = 0;

    while((pos = msg.find('\n')) != std::string::npos) 
    {
      msg.replace(pos,1,"");
    }

    std::stringstream ErrorCode;
    ErrorCode << e.getExcCode();

	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,msg.c_str(),"cCBS_StdConnection::revokeConnection()()",ErrorCode.str().c_str());
  }
  catch(...)
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","cCBS_StdConnection::revokeConnection()()","");
  }

  m_pCBSConnection = 0;

}


bool cCBS_StdConnection::establishNewConnection()
{
  bool RetValue = false;

  try
  {
    revokeConnection();

    std::string Message("cCBS_StdConnection::establishNewConnection() for :");
    Message += m_Url + " " + m_Login + " " + m_Password;
    log(Message,3);
  
    if (m_pDriverManager && m_pODBCDriver)
    {

      // Url could be of content
      // DriverName@DBName or DBName
      // CBS DriverManager is expecting DriverName@DBName style !

      std::string CombinedUrl = m_Url;
      std::string DriverName  = m_pODBCDriver->getName();

      if ( m_Url.find(DriverName) == std::string::npos ) // DriverName not found !
      {
        CombinedUrl = DriverName + "@" + m_Url;         
      }

      std::string Message("Using Url : ");

      Message += CombinedUrl;

      log(Message,3);


      m_pCBSConnection = &m_pDriverManager->getConnection(CombinedUrl, m_Login, m_Password); 

      log("Setting auto-commit to FALSE",3);

      if (m_pCBSConnection)
      {
        RetValue = true;

        m_pCBSConnection->setAutoCommit(false);

        cCBS_StdDB_Task::getInstance()->setWorking(true);
        cCBS_StdDB_Task::getInstance()->setStateDetails(CombinedUrl + "-" + m_Login + "-" + m_Password, "connection established", 0);
      }
      else
      {
        cCBS_StdDB_Task::getInstance()->setWorking(false);
        cCBS_StdDB_Task::getInstance()->setStateDetails(CombinedUrl + "-" + m_Login + "-" + m_Password, "connection lost", 0);
      }
    }
  }
  catch(cCBS_DBExc& e)
  {
    std::string msg = e.getText();
    size_t pos = 0;

    while((pos = msg.find('\n')) != std::string::npos) 
    {
      msg.replace(pos,1,"");
    }

    std::stringstream ErrorCode;
    ErrorCode << e.getExcCode();

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,msg.c_str(),"cCBS_StdConnection::establishNewConnection",ErrorCode.str().c_str());

    RetValue = false;

    cCBS_StdDB_Task::getInstance()->setWorking(false);
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","cCBS_StdConnection::establishNewConnection","");

    RetValue = false;

    cCBS_StdDB_Task::getInstance()->setWorking(false);
  }

  if ( !RetValue )
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBConnectionError(sMessage,"cCBS_StdConnection::establishNewConnection()");
  }

  return RetValue;
}



//##ModelId=411771EC027E
cCBS_Connection* cCBS_StdConnection::getpCBSConnection()
{
  return m_pCBSConnection;
}

void cCBS_StdConnection::rollback()
{
  try
  {
    log("Performimg rollback on Database", 3);

    m_pCBSConnection->rollback();

    log("Rollback performed on Database", 3);
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","cCBS_StdConnection::rollback()","");
  }
}

void cCBS_StdConnection::commit()
{
  try
  {
    log("Performimg commit on Database", 3);
    
    m_pCBSConnection->commit();
    
    log("Commit performed on Database", 3);
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","cCBS_StdConnection::commit()","");
  }
}


//##ModelId=411892B50024
cCBS_StdConnection::~cCBS_StdConnection()
{
  if (m_pDriverManager && m_pCBSConnection)
  {
  	m_pDriverManager->freeConnection(*m_pCBSConnection);
  }
}



//##ModelId=411895FC0322
void cCBS_StdConnection::log(const std::string & Message, long Level)
{
  cCBS_StdDB_Task::getInstance()->log(Message, Level);
}


bool cCBS_StdConnection::reconnect()
{
  bool RetValue = false;

  std::string Message("cCBS_StdConnection::reconnect() for :");
  Message += m_Url + " " + m_Login + " " + m_Password;
  log(Message,3);
  
  if (m_pDriverManager && m_pODBCDriver)
  {
    if ( !m_pCBSConnection )
    {
      RetValue = establishNewConnection();
    }
    else
    {
      RetValue = m_pDriverManager->reconnect(m_pCBSConnection);
    }
  }

  if ( RetValue )
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReconnectInfo(sMessage, "");
  }

  return RetValue;
}
