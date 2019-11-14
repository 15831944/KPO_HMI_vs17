// Copyright (C) 2011 SMS Siemag AG

#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <sstream>
#include <set>

#include "cCBS_StdLog_Task.h"
#include "cCBS_StdFrame_Component.h"
#include "cCBS_StdInitBase.h"

#include "cCBS_DBExc.h"
#include "cCBS_StdEventLogFrame.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdDB_Task.h"


//##ModelId=40EAA0930203
cCBS_StdDB_Task::~cCBS_StdDB_Task()
{
  freeConnections();
}

//##ModelId=40EAA0930206
cCBS_StdDB_Task::cCBS_StdDB_Task()
{
  log("cCBS_StdDB_Task(): Instantiating task",3);

  log("cCBS_StdDB_Task(): Instantiating cCBS_ODBCDriver()",3);
  m_pODBCDriver = new cCBS_ODBCDriver();

  log("cCBS_StdDB_Task(): Registering Driver cCBS_ODBCDriver()",3);
  m_DriverManager.registerDriver(m_pODBCDriver);
}

//##ModelId=40EAA09301F5
void cCBS_StdDB_Task::ownStartUp()
{
  cCBS_StdFrame_Task::ownStartUp();
}

//##ModelId=40EAA09301F8
void cCBS_StdDB_Task::ownRunDown()
{
  freeConnections();

  cCBS_StdFrame_Task::ownRunDown();
}

//##ModelId=40EAA0930200
bool cCBS_StdDB_Task::initialize()
{
	return cCBS_StdFrame_Task::initialize();
}

//##ModelId=40EAA093020B
cCBS_StdDB_Task * cCBS_StdDB_Task::m_Instance = 0  ;

//##ModelId=40EAA0930208
cCBS_StdDB_Task* cCBS_StdDB_Task::getInstance()
{
	if ( m_Instance == 0 )
	{
		m_Instance = new cCBS_StdDB_Task( );
	}
	return m_Instance;
}

bool cCBS_StdDB_Task::checkConnection( const std::string  & Url,  const std::string  & Login,  const std::string  & Password)
{
  bool RetValue = false;

  std::string Message("cCBS_StdDB_Task::checkConnection() for :");
  Message += Url + " " + Login + " " + Password;
  log(Message,3);

  try
  {
    if ( getConnection(Url,Login,Password) )
    {
      RetValue = true;
    }
  }
  catch(cCBS_DBExc_ConnectionError &e)
  {
    RetValue = false;

    doOnCBS_DBExcConnectionError(e, Url, Login, Password);
  }

  return RetValue;
}


//##ModelId=4117473F03B8
cCBS_Connection* cCBS_StdDB_Task::getConnection( const std::string  & Url,  const std::string  & Login,  const std::string  & Password)
{
  std::string Message("cCBS_StdDB_Task::getConnection() for :");
  Message += Url + " " + Login + " " + Password;
  log(Message,3);

  cCBS_Connection* pCBSConnection = 0;

  try
  {
    cCBS_StdConnection* pStdConnection = findConnection(Url,Login,Password);

    if (!pStdConnection)
    {
      try
      {
        log("Establishing new connection!",3);
        pStdConnection = new cCBS_StdConnection(&m_DriverManager,m_pODBCDriver,Url,Login,Password);
        registerConnection(pStdConnection);
      }
      catch(...)
      {
        pStdConnection = 0;

        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        std::string URL = "Unusable URL " + Url + " " + Login + " " + Password;
        pEventLog->EL_ExceptionCaught(Message,"DB connection failed","cCBS_StdDB_Task::getConnection()",URL.c_str());
      }
    }

    if ( pStdConnection )
    {
      pCBSConnection = pStdConnection->getpCBSConnection();

      if ( !pCBSConnection )
      {
        pStdConnection->establishNewConnection();
        pCBSConnection = pStdConnection->getpCBSConnection();
      }
    }
  }
  catch(cCBS_DBExc_ConnectionError &e)
  {
    pCBSConnection = 0;
    doOnCBS_DBExcConnectionError(e, Url, Login, Password);
  }
  catch(...)
  {
    pCBSConnection = 0;
  }

  // setting working state
  if ( pCBSConnection )
  {
    setWorking(true);
  }
  else  
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    std::string URL = "Used URL " + Url + " " + Login + " " + Password;
    pEventLog->EL_ExceptionCaught(Message,"DB connection not possible","cCBS_StdDB_Task::getConnection()",URL.c_str());

    setWorking(false);
  }
  
  return pCBSConnection;
}

cCBS_StdConnection* cCBS_StdDB_Task::getCBS_StdConnection( const std::string  & Url,  const std::string  & Login,  const std::string  & Password)
{
  std::string Message("cCBS_StdDB_Task::getConnection() for :");
  Message += Url + " " + Login + " " + Password;
  log(Message,3);

  cCBS_StdConnection* pStdConnection = 0;

  try
  {
    pStdConnection = findConnection(Url,Login,Password);

    if (!pStdConnection)
    {
      log("Establishing new connection!",3);
      pStdConnection = new cCBS_StdConnection(&m_DriverManager,m_pODBCDriver,Url,Login,Password);
      registerConnection(pStdConnection);
    }

  }
  catch(cCBS_DBExc_ConnectionError &e)
  {
    pStdConnection = 0;
    doOnCBS_DBExcConnectionError(e, Url, Login, Password);
  }

  // setting working state
  if ( !pStdConnection )
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    std::string URL = "Used URL " + Url + " " + Login + " " + Password;
    pEventLog->EL_ExceptionCaught(Message,"DB connection lost","cCBS_StdDB_Task::getCBS_StdConnection()",URL.c_str());

    setWorking(false);
  }


  return pStdConnection;
}

//##ModelId=4117624202E6
cCBS_StdConnection* cCBS_StdDB_Task::findConnection(const std::string  & Url, const std::string  & Login, const std::string  & Password, bool Reconnect /* = false */)
{
  cCBS_StdConnection* pStdConnection = 0;

  std::vector<cCBS_StdConnection*>::iterator it;

  for (it = m_ConnectionList.begin();it != m_ConnectionList.end();it++)
  {
    if ( (*it)->getUrl() == Url &&
         (*it)->getLogin() == Login &&
         (*it)->getPassword() == Password )
    {
      // connection found
      pStdConnection = (*it);
      break;
    }
  }

  if (!pStdConnection)
  {
    std::string Message("cCBS_StdDB_Task::findConnection(): Connection not yet established for :");
    Message += Url + " " + Login + " " + Password;
    log(Message,2);
  }
	
	return pStdConnection;
}

//##ModelId=4117634A00F2
void cCBS_StdDB_Task::registerConnection(cCBS_StdConnection * Connection)
{
  log("cCBS_StdDB_Task::registerConnection() ",3);
  m_ConnectionList.push_back(Connection);
}

//##ModelId=41499C9E01AB
void cCBS_StdDB_Task::log(const std::string & Message, long Level)
{
  cCBS_StdFrame_Task::log(Message, Level);
}

//##ModelId=41AF091D01AA
cCBS_StdConnection* cCBS_StdDB_Task::getCBS_StdConnection(cCBS_Connection* pConnection)
{
  cCBS_StdConnection* pCBS_StdConnection = 0;

  std::vector<cCBS_StdConnection*>::iterator it;

  for (it = m_ConnectionList.begin();it != m_ConnectionList.end();it++)
  {
    if ( (*it)->getpCBSConnection() == pConnection )
    {
      // connection found
      pCBS_StdConnection = (*it);
      break;
    }
  }

  if (!pCBS_StdConnection)
  {
    log("cCBS_StdDB_Task::getCBS_StdConnection(): Connection not yet established!",2);
  }
	
	return pCBS_StdConnection;
}

//##ModelId=48A53B9203A7
void cCBS_StdDB_Task::freeConnection(const std::string  & Url,  const std::string  & Login,  const std::string  & Password)
{
  std::vector<cCBS_StdConnection*>::iterator it;

  try
  {

    // find respective connection, free this and remove from m_ConnectionList !
    for (it = m_ConnectionList.begin();it != m_ConnectionList.end();it++)
    {
      if ( (*it)->getUrl() == Url &&
          (*it)->getLogin() == Login &&
          (*it)->getPassword() == Password )
      {
        // connection found
        m_DriverManager.freeConnection((*it)->getpCBSConnection());
        delete (*it);

        m_ConnectionList.erase(it);
        break;
      }
    }
  }
  catch(...)
  {
    log("Exception at m_ConnectionList handling : cCBS_StdDB_Task::freeConnection(...) ",1);
  }
}


//##ModelId=42A7FAFF01B1
void cCBS_StdDB_Task::freeConnections()
{
  std::vector<cCBS_StdConnection*>::iterator it;

  for (it = m_ConnectionList.begin();it != m_ConnectionList.end();it++)
  {
    std::string Message("cCBS_StdDB_Task::freeConnection() for :");
    Message += (*it)->getUrl() + " " + (*it)->getLogin() + " " + (*it)->getPassword();
    log(Message,3);

    m_DriverManager.freeConnection((*it)->getpCBSConnection());

    delete (*it);
  }

  m_ConnectionList.erase(m_ConnectionList.begin(),m_ConnectionList.end());
}

//##ModelId=436F556B014A
void cCBS_StdDB_Task::doOnCBS_DBExcConnectionError(cCBS_DBExc &ex, const std::string &url, const std::string &user, const std::string &passwd)
{
  std::string msg = ex.getText();
  size_t pos = 0;

  while((pos = msg.find('\n')) != std::string::npos) 
  {
    msg.replace(pos,1,"");
  }

  std::stringstream  connectString;
  connectString << "for " << user << "/" << passwd << "@" << url;
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ExceptionCaught(sMessage,"", msg.c_str(), connectString.str().c_str());
}


std::string cCBS_StdDB_Task::cCBS_StdDB_TaskControlThread::getStateDetails()
{
  std::string StateDetails = m_pTask->getTaskName();

  StateDetails = StateDetails + "::ControlThread::getStateDetails()" + "\n";

  cCBS_Connection*  pCBS_Connection = 0;
  cCBS_Statement*   pCBS_Statement  = 0;
  cCBS_StdDB_Task*  CBS_StdDB_Task = dynamic_cast<cCBS_StdDB_Task*>(m_pTask);

  try
  {
    // Statement to find locked table or rows
    std::string SQLStatement;
    SQLStatement  = "SELECT l.inst_id,SUBSTR(L.ORACLE_USERNAME,1,8) ORA_USER, SUBSTR(L.SESSION_ID,1,3) SID,";
    SQLStatement += "S.serial# as SERIALNO,";
    SQLStatement += "SUBSTR(O.OWNER||'.'||O.OBJECT_NAME,1,40) OBJECT, P.SPID OS_PID,";
    SQLStatement += "DECODE(L.LOCKED_MODE, 0,'NONE',";
    SQLStatement += "1,'NULL',";
    SQLStatement += "2,'ROW SHARE',";
    SQLStatement += "3,'ROW EXCLUSIVE',";
    SQLStatement += "4,'SHARE',";
    SQLStatement += "5,'SHARE ROW EXCLUSIVE',";
    SQLStatement += "6,'EXCLUSIVE',";
    SQLStatement += "NULL) LOCKED_MODE ";
    SQLStatement += "FROM sys.GV_$LOCKED_OBJECT L, DBA_OBJECTS O, sys.GV_$SESSION S, sys.GV_$PROCESS P ";
    SQLStatement += "WHERE L.OBJECT_ID = O.OBJECT_ID ";
    SQLStatement += "and l.inst_id = s.inst_id ";
    SQLStatement += "AND L.SESSION_ID = S.SID ";
    SQLStatement += "and s.inst_id = p.inst_id ";
    SQLStatement += "AND S.PADDR = P.ADDR(+) ";
    SQLStatement += "order by l.inst_id;";

    // staement to SID details
    std::string SQL_SID;
    SQL_SID = "select STATUS, PROCESS, PROGRAM, LOGON_TIME, MACHINE from v$session where SID = '";

    std::set<long> SIDS;
    std::set<long>::iterator it_sids;

    if ( CBS_StdDB_Task != 0 )
    {
      pCBS_Connection = CBS_StdDB_Task->m_DriverManager.getPtConnection(m_URL, m_DBUser, m_DBPassword);
    }
    else
    {
      StateDetails += " dynamic_cast<cCBS_StdDB_Task*> failed.";
    }

    if ( pCBS_Connection != 0 )
    {
      pCBS_Statement = pCBS_Connection->createPtStatement();
      if ( pCBS_Statement != 0 )
      {
        try
        {
          long rows = 0;                // to count the found rows
          std::stringstream ResultSID;  // to collect query result for SQL_SID
          std::stringstream Result;     // to collect query result for SQLStatement

          cCBS_ResultSet *ptRS = pCBS_Statement->executePtQuery(SQLStatement);
          if ( ptRS )
          {
            ptRS->setTruncateChar(" ");
            ptRS->beforeFirst();
            while ( ptRS->next() )
            {
              SIDS.insert(ptRS->getInt("SID"));

              Result << "SID "          << ptRS->getInt("SID") << " | ";
              Result << "INST_ID "      << ptRS->getInt("INST_ID") << " | ";
              Result << "ORA_USER "     << ptRS->getString("ORA_USER") << " | ";
              Result << "SERIALNO "     << ptRS->getInt("SERIALNO") << " | ";
              Result << "OBJECT "       << ptRS->getString("OBJECT") << " | ";
              Result << "OS_PID "       << ptRS->getInt("OS_PID") << " | ";
              Result << "LOCKED_MODE "  << ptRS->getString("LOCKED_MODE") << " |";
              Result << "\n";

              rows++;
            }
            StateDetails += Result.str();
          }

          if ( rows == 0 )
          {
            StateDetails += " No result for statement : " + SQLStatement;
          }
          else
          {
            StateDetails += "*** Second part ***\n";

            it_sids = SIDS.begin();

            while ( it_sids != SIDS.end() )
            {
              pCBS_Connection->freeStatement(pCBS_Statement);
              pCBS_Statement = pCBS_Connection->createPtStatement();
              if ( pCBS_Statement != 0 )
              {
                std::stringstream Statement;
                Statement << SQL_SID << *it_sids << "';";

                cCBS_ResultSet *ptRS = pCBS_Statement->executePtQuery(Statement.str());
                if ( ptRS )
                {
                  ptRS->setTruncateChar(" ");
                  ptRS->beforeFirst();
                  while ( ptRS->next() )
                  {
                    ResultSID << "SID "         << *it_sids << " |";
                    ResultSID << "STATUS "      << ptRS->getString("STATUS") << " | ";
                    ResultSID << "PROCESS "     << ptRS->getString("PROCESS")<< " | ";
                    ResultSID << "PROGRAM "        << ptRS->getString("PROGRAM")<< " | ";
                    DB_CLASSLIB_DATE const *LOGON_TIME = ptRS->getDate("LOGON_TIME");
                    ResultSID << "LOGON_TIME "  << LOGON_TIME->day<<"."<<LOGON_TIME->month<<"."<<LOGON_TIME->year<<" "<<LOGON_TIME->hour<<":"<<LOGON_TIME->minute<<":"<<LOGON_TIME->second << " | ";
                    ResultSID << "MACHINE "     << ptRS->getString("MACHINE")<< " |";
                    ResultSID << "\n";
                  }//while ( ptRS->next() )
                }//if ( ptRS )

                //StateDetails += ResultSID.str();
                //ResultSID.str() = "";
              }
              else
              {
                StateDetails += " 2nd. pCBS_Connection->createPtStatement failed";
              }

              it_sids++;
            }

            StateDetails += ResultSID.str();

          }
        }
        catch(cCBS_DBExc& e)
        {
          StateDetails += "cCBS_DBExc caught: " + e.getText();
        }
        catch(...)
        {
          StateDetails += "Exception caught";
        }

        // free the statement
        pCBS_Connection->freeStatement(pCBS_Statement);

        CBS_StdDB_Task->m_DriverManager.freeConnection(pCBS_Connection);
      }
      else
      {
        StateDetails += " 1. pCBS_Connection->createPtStatement failed";
      }
    }
    else
    {
      StateDetails += " No connection to the data base: " + m_URL + " " + m_DBUser + " " + m_DBPassword;
    }
  }
  catch(cCBS_DBExc& e)
  {
    StateDetails += "cCBS_DBExc caught: " + e.getText();
  }
  catch(...)
  {
    StateDetails += " Exception ...";
  }

  if ( CBS_StdDB_Task != 0 )
  {
    if ( pCBS_Connection  != 0 )
    {
      CBS_StdDB_Task->m_DriverManager.freeConnection(pCBS_Connection);
    }
  } 

	return StateDetails;
}

void cCBS_StdDB_Task::doOnComponentStartup()
{
	// ToDo: Add your specialized code here or after the call to base class
	cCBS_StdFrame_Task::doOnComponentStartup();
}

cCBS_StdDB_Task::cCBS_StdDB_TaskControlThread::cCBS_StdDB_TaskControlThread(cCBS_StdDB_Task* pTask , long ControlTime)
: cCBS_StdFrame_TaskControlThread(pTask, ControlTime)
{
}

void cCBS_StdDB_Task::runControlThread()
{
  // if time > 0 is set in ini file, control is active
  long ControlTime        = -1;
  std::string ODBC_Name   = "l2smc";
  std::string URL         = "ODBC_Driver@";
  std::string DBUser      = "l2smc";
  std::string DBPassword  = "l2smc";

  cCBS_StdInitBase::getInstance()->replaceWithEntry("DATABASE", "SMC_DBName", ODBC_Name);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("DATABASE", "SMC_DBUser", DBUser);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("DATABASE", "SMC_DBPassword", DBPassword);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("ProcessControl","ControlTime",ControlTime);

  // append odbc name to URL
  URL += ODBC_Name;

  // overwrite with task specific entries 
  std::string TaskName = getTaskName();
  cCBS_StdInitBase::getInstance()->replaceWithEntry(getTaskName(),"ControlTime",ControlTime);

  if ( ControlTime > 0 && !m_pControlThread )
  {
    std::stringstream Message;

    Message << "Starting control thread for Task " 
            << TaskName 
            << " using control time " 
            << ControlTime 
            << " (msecs) ";
    
    log(Message.str(),3);

    m_pControlThread = new cCBS_StdDB_Task::cCBS_StdDB_TaskControlThread(this,ControlTime);
    m_pControlThread->setFreeOnTerminate(true);
    dynamic_cast<cCBS_StdDB_TaskControlThread*>(m_pControlThread)->m_DBUser = DBUser;
    dynamic_cast<cCBS_StdDB_TaskControlThread*>(m_pControlThread)->m_DBPassword = DBPassword;
    dynamic_cast<cCBS_StdDB_TaskControlThread*>(m_pControlThread)->m_URL = URL;
    m_pControlThread->run();
  }
}
