#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTelcom_OdbcStoredFunction_3C73CF6D01A4_INCLUDED
#define _INC_CTelcom_OdbcStoredFunction_3C73CF6D01A4_INCLUDED


#include <windows.h>
#include <sql.h>
#include<sqltypes.h>
#include<sqlext.h>

////////////////////////////////////////////////////////////
//
// This class is used to communicate with specialized
// oracle stored functions that have in and out parameter.
// Configuration is done via  ini files.
// 
// Configuration for this is in ini
//
// [SMS_OracleTransport]
// service=xe
// user=isdemir
// password=isdemir
////////////////////////////////////////////////////////////

class CTelcom_OdbcStoredFunction 
{
protected: 
  SQLHENV m_henv;  
  SQLHDBC m_hdbc;
  SQLHSTMT m_hstmt; 

public: 
  // Constructor of CTelcom_OdbcStoredFunction
  CTelcom_OdbcStoredFunction();

  ~CTelcom_OdbcStoredFunction();

  // Establishing a connection by passing the database name, user name and password
  bool ODBCConnection();

  // Free handles and disconnect
  bool freeAllHandles();

  void testConnection(SQLUSMALLINT Column=2);

  // true = Msg will not be read again and the next one can be processed
  bool set_Bstat(bool MessageProcessed = false);

  // This method calls the stored function 'Bericht' in the Oracle database
  int getBerichtFromDB(std::string p_poort, double p_timeout, 
                        std::string * r_sender, std::string * r_transmission,
                        std::string * r_typeReport, std::string * r_timezone, 
                        std::string * r_destination, std::string * r_messageContent);

  // This method calls the stored function 'Bericht_raw' in the Oracle database
  bool setBerichtInDB(std::string sender, std::string transmission, 
                      std::string typeReport, std::string timezone,
                      std::string messageContent, long nr, 
                      std::string lastSender, std::string currentSender);

  // This method calls the stored function 'Send.Bericht' in the Oracle database
  bool CTelcom_OdbcStoredFunction::sendBerichtToCorusDB(std::string sender, std::string typeReport, std::string messageContent);

protected:
  bool ODBCDisconnect();


private: 
  // SQLRETURN value can be obtained by calling DiagnosticSQLRetCode
  bool DiagnosticSQLRetCode(SQLRETURN retcode);

};

#endif /* _INC_CTelcom_OdbcStoredFunction_3C73CF6D01A4_INCLUDED */