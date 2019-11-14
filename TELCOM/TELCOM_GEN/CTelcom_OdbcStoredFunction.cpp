#pragma warning(disable:4786)

#include <iostream>
#include <sstream>
#include <string>

using namespace std;



#include "CTelcom_OdbcStoredFunction.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_DBExc.h"

CTelcom_OdbcStoredFunction::CTelcom_OdbcStoredFunction()
{
}

CTelcom_OdbcStoredFunction::~CTelcom_OdbcStoredFunction()
{
  try
  {
    freeAllHandles();
  }
  catch (cCBS_DBExc &e)
	{
    // forward the error correction code to the main controller 
    throw (e);
	}
}

// Free handles and disconnect
bool CTelcom_OdbcStoredFunction::freeAllHandles()
{
  SQLRETURN  retcode = -1;
  // End the connection 
  try
  {
    if (m_hstmt) 
    { 
      retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
      if(!DiagnosticSQLRetCode(retcode))
      {
        throw (cCBS_DBExc("CTelcom_OdbcStoredFunction::freeAllHandles(): could not free Statement handle"));
      }
      m_hstmt = NULL;
    }
    if(!ODBCDisconnect())
    {
      throw (cCBS_DBExc("CTelcom_OdbcStoredFunction::freeAllHandles(): could not disconnet from database"));
    } 
    if (m_hdbc) 
    { 
      retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hdbc);
      if(!DiagnosticSQLRetCode(retcode))
      {
        throw (cCBS_DBExc("CTelcom_OdbcStoredFunction::freeAllHandles(): could not free connection handle"));
      }
      m_hdbc = NULL; 
    }
    if (m_henv) 
    { 
      retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_henv);
      if(!DiagnosticSQLRetCode(retcode))
      {
        throw (cCBS_DBExc("CTelcom_OdbcStoredFunction::freeAllHandles(): could not free environment handle"));
      }
      m_henv = NULL;
    }
    std::cout << "Connection to the database has been successfully separated!" << std::endl;  
    return true;
  }
  catch (cCBS_DBExc &e)
	{
    throw (e);
	}
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_LogMessage(Message, "CTelcom_OdbcStoredFunction::freeAllHandles(): could not free environment handle");
    return false;
  }
}

// Represents a connection to a data source
bool CTelcom_OdbcStoredFunction::ODBCConnection()
{
  bool ReValue = false; 
  std::string DBName = "";
  std::string DBUser = "";
  std::string DBPassword = "";
  SQLRETURN  retcode = -1;

  // Initialize the environment, connection, statement handles
  m_henv = NULL;
  m_hdbc = NULL;
  m_hstmt = NULL;
  
  cCBS_StdInitBase *pStdInitBase = cCBS_StdInitBase::getInstance();

  if( !( pStdInitBase->getEntry("SMS_Transport", "service", DBName) &&
          pStdInitBase->getEntry("SMS_Transport", "user", DBUser)  &&
          pStdInitBase->getEntry("SMS_Transport", "password", DBPassword) ) )
  {
    std::cerr << "Can not read SMC database settings from ini-file" << std::endl;
  }

  try
  {
    /* Allocate an environment handle */
    retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_henv);
    
    /* We want ODBC 3 support */
    retcode = SQLSetEnvAttr(m_henv, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);;
    
    /* Allocate a connection handle */
    retcode = SQLAllocHandle(SQL_HANDLE_DBC, m_henv, &m_hdbc); 
    
    /* Connect to the DSN mydsn */
    retcode = SQLConnect(m_hdbc, (SQLCHAR*)DBName.c_str(),SQL_NTS,(SQLCHAR*)DBUser.c_str(), SQL_NTS, (SQLCHAR*)DBPassword.c_str(), SQL_NTS);
    
    if (DiagnosticSQLRetCode(retcode))
    {
      std::cout << "Connection successful!" << std::endl;
    }
    else
    {
      throw (cCBS_DBExc("CTelcom_OdbcStoredFunction::ODBCConnection(): could not connect to database!"));
    }

    /* Allocate a statement handle */
    retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);    
    if (DiagnosticSQLRetCode(retcode))
    {
      std::cout << "connected to : " << DBName << ", " << DBUser << ", " << DBPassword << std::endl;

      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_LogMessage(Message, "CTelcom_OdbcStoredFunction::ODBCConnection: IS SUCCESSFUL" );
      ReValue = true;     
    }
    else
    {
      throw (cCBS_DBExc("CTelcom_OdbcStoredFunction::ODBCConnection(): could not allocate a statement handle!"));   
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_LogMessage(Message, "CTelcom_OdbcStoredFunction::ODBCConnection(): could not allocate a statement handle!");    
  }

  return ReValue;
}

// disconnect
bool CTelcom_OdbcStoredFunction::ODBCDisconnect()
{ 
  SQLRETURN  retcode = -1;
  try
  {
    if (m_hdbc)
	  {
		  retcode = SQLDisconnect(m_hdbc);
		  if(DiagnosticSQLRetCode(retcode))
		  {
        return true;
		  }
	  } // if (m_hdbc)
    return false;
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_LogMessage(Message, "CTelcom_OdbcStoredFunction::ODBCDisconnect(): could not disconnect to database!" );
    throw (cCBS_DBExc("CTelcom_OdbcStoredFunction::ODBCDisconnect(): could not disconnect to database!"));
  }
}


void CTelcom_OdbcStoredFunction::testConnection(SQLUSMALLINT Column)
{
  SQLRETURN  retcode = -1;
  char* stmt = "SELECT * from BERICHT;";
  int row = 0;

  try
  {
    retcode = SQLExecDirect(m_hstmt, (SQLCHAR*)stmt, SQL_NTS); 

    //Retrieve data from row set.
    //retcode = SQLBindCol(m_hstmt, 1, SQL_C_LONG, (SQLPOINTER) &lEmpID, sizeof(long), &indicator1);

    //Initialize the database connection
    while(SQL_SUCCEEDED(retcode = SQLFetch(m_hstmt)))
    {
      SQLLEN indicator;
      char buf[512];
      /* retrieve column data as a std::string */    
      retcode = SQLGetData(m_hstmt, Column, SQL_C_CHAR, buf, sizeof(buf), &indicator);
      if (SQL_SUCCEEDED(retcode)) 
      {
        /* Handle null columns */
        if (indicator == SQL_NULL_DATA) 
          strcpy(buf, "NULL");

	      printf("TEST SUCCEEDED Column %u : %s", Column, buf);
      }
      else
      {
        throw (cCBS_DBExc("CTelcom_OdbcStoredFunction::testConnection(SQLUSMALLINT Column): TEST FAILED!"));
      }
    } // while(SQL_SUCCEEDED(retcode = SQLFetch(m_hstmt)))
  }
  catch (cCBS_DBExc &e)
	{
    throw (e);
	}
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_LogMessage(Message, "CTelcom_OdbcStoredFunction::testConnection(SQLUSMALLINT Column): TEST FAILED!");
  }
}

// This method calls the stored function in the Oracle database 
// true = read next Msg
bool CTelcom_OdbcStoredFunction::set_Bstat(bool MessageProcessed)
{
  std::string MessageStat = "N";
  
  // J = okay , E = error
  if(MessageProcessed)
  {
      MessageStat = "J";
  }
  else
  {
      MessageStat = "E";
  }
  
  SQLRETURN  retcode = -1;
  
  SQLCHAR res[2]  = "";
  SQLINTEGER Num1IndOrLen = -1;

  std::string Statement = "{call GET.Bstat('"+ MessageStat + "')}";

  try
  {
    retcode = SQLPrepare(m_hstmt,(SQLCHAR*)Statement.c_str(), SQL_NTS);

    retcode = SQLExecute(m_hstmt);
      
    if (DiagnosticSQLRetCode(retcode))
    {
      return true;
    } // if (DiagnosticSQLRetCode(retcode))
    else
    {
      throw (cCBS_DBExc("CTelcom_OdbcStoredFunction::getBerichtFromDB(): could not execute SQL !")); 
    }
  }
  catch (cCBS_DBExc &e)
	{
    throw (e);
	}
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_LogMessage(Message, "CTelcom_OdbcStoredFunction::getBerichtFromDB(): could not execute SQL !");
    return false;
  }
}


// This method calls the stored function in the Oracle database
int CTelcom_OdbcStoredFunction::getBerichtFromDB(std::string p_poort, double p_timeout, 
                                             std::string * r_sender, std::string * r_transmission,
                                             std::string * r_typeReport, std::string * r_timezone, 
                                             std::string * r_destination, std::string * r_messageContent)
{
  int retValue = -1;
  SQLRETURN  retcode = -1;
  
  SQLINTEGER res = 0;
  SQLLEN resInd = -1;

  // dutch varibles:
  SQLCHAR p_zender[20]  = "";
  SQLLEN Num3IndOrLen = -1;
    
  SQLCHAR p_dt_verzending[200] = "";
  SQLLEN Num4IndOrLen = -1;

  SQLCHAR p_type_bericht[200]  = "";
  SQLLEN Num5IndOrLen = -1;

  SQLCHAR p_tijdzone[2]  = "";
  SQLLEN Num6IndOrLen = -1;

  SQLCHAR p_bestemming[200]  = "";
  SQLLEN Num7IndOrLen = -1;

  SQLCHAR p_inhoud[4001]  = "";
  SQLLEN Num8IndOrLen = -1;

  ostringstream sp_timeout;
  sp_timeout << p_timeout;

  std::string Statement = "{? = call GET.Bericht('"+ p_poort +"','" + sp_timeout.str() + "',?,?,?,?,?,?)}";

  try
  {
    retcode = SQLPrepare(m_hstmt,(SQLCHAR*)Statement.c_str(), SQL_NTS);

    retcode = SQLBindParameter(m_hstmt,1, SQL_PARAM_OUTPUT, SQL_C_LONG,SQL_INTEGER,0, 0,
			    &res, sizeof res, &resInd);

    retcode = SQLBindParameter(m_hstmt,2, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR,0, 0,
 			    &p_zender, sizeof p_zender, &Num3IndOrLen);

    retcode = SQLBindParameter(m_hstmt,3, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_DATE,0, 0,
 			    &p_dt_verzending, sizeof p_dt_verzending, &Num4IndOrLen);

    retcode = SQLBindParameter(m_hstmt,4, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR,0, 0,
 			    &p_type_bericht,sizeof p_type_bericht, &Num5IndOrLen);

    retcode = SQLBindParameter(m_hstmt,5, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_CHAR,0, 0,
 			    &p_tijdzone,sizeof p_tijdzone, &Num6IndOrLen);

    retcode = SQLBindParameter(m_hstmt,6, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR,0, 0,
 			    &p_bestemming,sizeof p_bestemming, &Num7IndOrLen);

    retcode = SQLBindParameter(m_hstmt,7, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR,0, 0,
 			    &p_inhoud,sizeof p_inhoud, &Num8IndOrLen);

    retcode = SQLExecute(m_hstmt);
      
    if (DiagnosticSQLRetCode(retcode))
    {      
      *r_sender = (char*) p_zender;
      *r_transmission = (char*) p_dt_verzending;
      *r_typeReport = (char*) p_type_bericht;
      *r_timezone = (char*) p_tijdzone;
      *r_destination = (char*) p_bestemming;
      *r_messageContent = (char*) p_inhoud;

      retValue = (int) res;   
    } // if (DiagnosticSQLRetCode(retcode))
    else
    {
      throw (cCBS_DBExc("CTelcom_OdbcStoredFunction::getBerichtFromDB(): could not execute SQL !")); 
    }

    return retValue;
  }
  catch (cCBS_DBExc &e)
	{
    throw (e);
	}
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_LogMessage(Message, "CTelcom_OdbcStoredFunction::getBerichtFromDB(): could not execute SQL !");
  }
}

// This method calls the stored function in the Oracle database for sending a CORUS Message
bool CTelcom_OdbcStoredFunction::setBerichtInDB(std::string sender, std::string transmission, 
                                                std::string typeReport, std::string timezone,
                                                std::string messageContent, long nr,
                                                std::string lastSender, std::string currentSender)
{
  SQLRETURN  retcode = -1;
  
  SQLINTEGER res = 0;
  SQLLEN resInd = -1;

  //SQLCHAR dt_verzending[200] = "";
  //strcpy(reinterpret_cast<char*>(dt_verzending), p_dt_verzending.c_str()); 
  //SQLINTEGER Num1IndOrLen = -1;

  ostringstream ssnr;
  ssnr << nr;

  std::string Statement = "{? = call Func_Bericht_raw('" + sender + "',TO_DATE ('"
                                                    + transmission.c_str() + "', 'yyyy-mm-dd HH24:MI:SS'),'" 
                                                    + typeReport + "','" 
                                                    + timezone + "','" 
                                                    + messageContent + "','" 
                                                    + ssnr.str() + "','" 
                                                    + lastSender + "','" 
                                                    + currentSender + "')}";

  try
  {
    retcode = SQLPrepare(m_hstmt,(SQLCHAR*)Statement.c_str(), SQL_NTS);
    
    retcode = SQLBindParameter(m_hstmt,1, SQL_PARAM_OUTPUT, SQL_C_LONG,SQL_INTEGER,0, 0,
			    &res, sizeof res, &resInd);

    //retcode = SQLBindParameter(m_hstmt,2, SQL_PARAM_INPUT, SQL_DATE, SQL_C_CHAR ,0, 0,
 			//    &dt_verzending, sizeof dt_verzending, &Num1IndOrLen);

    retcode = SQLExecute(m_hstmt);

    // std::cout << res << std::endl;

    if (DiagnosticSQLRetCode(retcode))
    {
      std::cout << "Telcom_OdbcStoredFunction::setBerichtInDB: " << typeReport << " send to " << sender << " over ODBC"<<std::endl;
      return true;
    } // if (DiagnosticSQLRetCode(retcode))
    else
    {
      throw (cCBS_DBExc("CTelcom_OdbcStoredFunction::getBericht_rawFromDB(): could not execute SQL for typ !"));
    }
  }
  catch (cCBS_DBExc &e)
	{
    // forward the error correction code to the main controller 
    throw (e);
	}
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_LogMessage(Message, "CTelcom_OdbcStoredFunction::getBericht_rawFromDB(): could not execute SQL !");
    return false;
  }
}

// This method calls the stored function in the Oracle database for sending a CORUS Message
bool CTelcom_OdbcStoredFunction::sendBerichtToCorusDB(std::string sender, std::string typeReport, std::string messageContent)
{
  SQLRETURN  retcode = -1;
  
  SQLINTEGER res = 0;
  SQLLEN resInd = -1;

  //SQLCHAR dt_verzending[200] = "";
  //strcpy(reinterpret_cast<char*>(dt_verzending), p_dt_verzending.c_str()); 
  //SQLINTEGER Num1IndOrLen = -1;

  //ostringstream ssnr;
  //ssnr << nr;

  // first argument, BerichtNr default Null
  std::string Statement = "{? = call SEND.Bericht('','"                                                   
                                  + typeReport + "','" 
                                  + messageContent + "')}";

  try
  {
    retcode = SQLPrepare(m_hstmt,(SQLCHAR*)Statement.c_str(), SQL_NTS);
    
    retcode = SQLBindParameter(m_hstmt,1, SQL_PARAM_OUTPUT, SQL_C_LONG,SQL_INTEGER,0, 0,
			    &res, sizeof res, &resInd);

    //retcode = SQLBindParameter(m_hstmt,2, SQL_PARAM_INPUT, SQL_DATE, SQL_C_CHAR ,0, 0,
 			//    &dt_verzending, sizeof dt_verzending, &Num1IndOrLen);

    retcode = SQLExecute(m_hstmt);

    // std::cout << res << std::endl;

    if (DiagnosticSQLRetCode(retcode))
    {
      std::cout << "Telcom_OdbcStoredFunction::setBerichtInDB: " << typeReport << " send to " << sender << " over ODBC"<<std::endl;
      return true;
    } // if (DiagnosticSQLRetCode(retcode))
    else
    {
      throw (cCBS_DBExc("CTelcom_OdbcStoredFunction::sendBerichtToCorusDB(): could not execute SQL !"));
    }
  }
  catch (cCBS_DBExc &e)
	{
    // forward the error correction code to the main controller 
    throw (e);
	}
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_LogMessage(Message, "CTelcom_OdbcStoredFunction::getBericht_rawFromDB(): could not execute SQL !");
    return false;
  }
}


// SQLRETURN value can be obtained by calling DiagnosticSQLRetCode 
bool CTelcom_OdbcStoredFunction::DiagnosticSQLRetCode(SQLRETURN retcode)
{ 
  switch (retcode)
  {
    case SQL_SUCCESS:
    {
      //std::cout << "SQL_SUCCESS" << std::endl;
      return true;
    }

    case SQL_SUCCESS_WITH_INFO:
    {
      std::cout << "The function completed successfully but with possible non-fatal errors" << std::endl;
      return false;
    }

    case SQL_NO_DATA:
    {
      std::cout << "No Data..." << std::endl;
      throw (cCBS_DBExc("CTelcom_OdbcStoredFunction::DiagnosticSQLRetCode: SQL_NO_DATA"));
    }

    case SQL_STILL_EXECUTING:
    {
      std::cout << "SQL_STILL_EXECUTING" << std::endl;
      throw (cCBS_DBExc("CTelcom_OdbcStoredFunction::DiagnosticSQLRetCode: SQL_STILL_EXECUTING"));
    }

    case SQL_NEED_DATA:
    {
      std::cout << "SQL_NEED_DATA" << std::endl;
      throw (cCBS_DBExc("CTelcom_OdbcStoredFunction::DiagnosticSQLRetCode: TSQL_NEED_DATA"));
    }

    case SQL_INVALID_HANDLE:
    {
      std::cout << "The handle passed to the function is invalid." << std::endl;
      throw (cCBS_DBExc("CTelcom_OdbcStoredFunction::DiagnosticSQLRetCode: The handle passed to the function is invalid.")); 
    }
    case SQL_ERROR:
    {
      SQLRETURN  rc = -1;
      SQLCHAR     buffer[SQL_MAX_MESSAGE_LENGTH + 1];
      SQLCHAR     sqlstate[SQL_SQLSTATE_SIZE + 1];
      SQLINTEGER  sqlcode;
      SQLSMALLINT length;

      rc = SQLError(m_henv, m_hdbc, m_hstmt, sqlstate, &sqlcode, buffer, SQL_MAX_MESSAGE_LENGTH + 1, &length);  
      
      if( SQL_SUCCEEDED(rc) )
      {
        std::cout << std::endl << " **** SQL_ERROR ***** " << std::endl << std::endl;
        std::cout << "SQLSTATE: " << sqlstate <<std::endl;
        std::cout << "Native Error Code: " << sqlcode << std::endl;
        std::cout << buffer << std::endl;

        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_LogMessage(Message, "CTelcom_OdbcStoredFunction::DiagnosticSQLRetCode: SQL_ERROR" );

        //ODBCConnection(); // frag if fehlt sqlcode auswerten

        //{
        //  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        //  sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        //  pEventLog->EL_LogMessage(Message, "CTelcom_OdbcStoredFunction::DiagnosticSQLRetCode: TRY TO RECONNECT" );
        //}
      }
      else
      {
        throw (cCBS_DBExc("CTelcom_OdbcStoredFunction::DiagnosticSQLRetCode: unknown SQL_ERROR")); 
      }   
      return false;
    }
    default:
    {
      std::cout << "No status was found" << std::endl;
    }
  }

  return false;
}
