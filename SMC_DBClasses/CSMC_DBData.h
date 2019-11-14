// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_DBDATA_414EEE0801A3_INCLUDED
#define _INC_CSMC_DBDATA_414EEE0801A3_INCLUDED

#include <string>
#include <vector>
#include <map>
#include <set>


#include "cCBS_DBExc.h"
#include "cCBS_Connection.h"
#include "cCBS_StdConnection.h"
#include "cCBS_Statement.h"
#include "CDateTime.h"

#include "cCBS_ResultSet.h"

class CSMC_DBColProfile;

class CSMC_DBMetaData;

//Class providing CBS DB Classes functionality.
class CSMC_DBData 
{
protected:

  virtual void doOnConstruct();
  virtual void doOnDestruct();

  cCBS_Connection* getpCBSConnection();

  bool m_TableExists;

  cCBS_StdConnection* m_pCBS_StdConnection;

  //TableName. Should be set during construction of derived 
  //class.
  std::string m_TableName;

  cCBS_PreparedStatement* m_pPreparedStatement;

  //Statement (Select Statement). Should be set on 
  //construction of derived classes.
  std::string m_Statement;

  long m_LastRow;

  std::string m_ActStatement;

  void initStatements();

  //Last SQL Error which occured
  cCBS_ODBC_DBError m_lastError;

  // return trace of cCBS_StdDB_Task
  long getTraceLevel();

  //used for update and insert
  cCBS_Statement* m_pStatement;

  cCBS_Statement* m_pSelectStatement;

  cCBS_ResultSet * m_pResultSet;

  bool execute_prepared_insert();

  std::string m_PreparedStatement;

public:
  bool insertPrepared();
  
  // method calls respective getxxx method for Row from pSourceTable and calls setxxx methods from actual table
  // for each column which name is equal in both tables
  void setColumnsFromTable(CSMC_DBData* pSourceTable, long Row);

  // method calls respective getxxx method for Row from pSourceTable and calls setxxx methods from actual table
  // for each pair of columns which defined at ColumnList map of content <SOURCE_COLUMN , AIM_COLUMN>
  void setColumnsFromTable(CSMC_DBData* pSourceTable, long Row, std::map<std::string,std::string> ColumnList);

  //Setting Row of respective ResultRet to Index.
  bool setRow(long Row);

  void doOnCBS_DBExc_ConnectionError(cCBS_DBExc_ConnectionError& ex, const std::string& Action = "");

  void doOnCBS_DBExc_ConnectionError(cCBS_DBExc& ex, const std::string& Action = "");

  bool getMetaData(const std::string& TableName);

  std::string getTableName();

  void doOnCBS_DBExc(cCBS_DBExc& ex, const std::string& Action = "");

  bool handleConnectionError();

  bool isNull(const std::string& ColName, long Row = -1);

  void log(const std::string& Message, long Level);

  //Rollback actions on Connection and free respective 
  //statements.
  void rollback();

  static const long unspecLong;

  static const std::string unspecString;

  static const double unspecDouble;

  static const CDateTime unspecDate;

  static const std::string Default;

  //Setting value for ColName of date type. Inserting 
  //DBColProfile into DataList.
  void setDate(const std::string& ColName, CDateTime & value);

  //Returning value from table ColName of type CDateTime 
  //and respective Row
  CDateTime getDate(const std::string& ColName, long Row);

  void cleanWhereStatement();

  //Returns where Statement like WHERE ( PLANT = 'AOD' AND 
  //HEATNO = 1 ) according to Where clauses form 
  //WhereClauseList beeing added by addWhereClause method
  std::string getWhereStatement();

  std::string getCopyByInsertStatement(CSMC_DBData* pSourceTable);
  std::string getCopyByUpdateStatement(CSMC_DBData* pSourceTable);

  // adding free clause
  // make shure that clause is syntactically correct
  // no systax check will be done 
  void  addWhereClause(const std::string &value);

  void  addWhereClause(const std::string &ColName, const std::string &value , const std::string & Operator = "=");
  void  addWhereClause(const std::string &ColName, std::vector<std::string> &ValueList, const std::string & LogicalOperator = "IN" );

  void  addWhereClause(const std::string &ColName,  long value , const std::string & Operator = "=");
  void  addWhereClause(const std::string &ColName, std::vector<long> &ValueList, const std::string & LogicalOperator = "IN");

  void addWhereClause(const std::string& ColName, double value , const std::string & Operator = "=");

  // method uses simple DBString format from CDateTime
  void addWhereClause(const std::string& ColName, const CDateTime& value, const std::string & Operator = "=");

  void addWhereClauseforJoin(const std::string &ColName, const std::string &JoinTable, const std::string &JoinColName, const std::string & Operator = "=" );

  void addWhereClauseforNULL(const std::string& ColName, bool isNULL = true);


  //This methos is in principal equal to 
  //addWhereClauseforTimestamp, but we need a different 
  //time format without milli seconds.
  void addWhereClauseforDate(const std::string& ColName, const CDateTime& value = CSMC_DBData::unspecDate, const std::string & Operator = "=");

  //This methos is in principal equal to 
  //addWhereClauseforDate, but we need a different time 
  //format with milli seconds.
  void addWhereClauseforTimestamp(const std::string& ColName, const CDateTime& value = CSMC_DBData::unspecDate, const std::string & Operator = "=");

  //Commiting actions on Connection and free respective 
  //statements.
  void commit();

  //Method performing data selection of respective Table.
  bool select();

  //Method performing data selection of respective Table 
  //for given Statement.
  bool select(const std::string& Statement);

  //Method performing data update of respective Table 
  //regarding fields of DataList..
  bool update();

  bool deleteRows();

  //Method performing data insertion of respective Table 
  //regarding fields of DataList..
  bool insert();

  //Returning value from table ColName of type long and 
  //respective Row
  long getLong(const std::string& ColName, long Row);

  //Returning value from table ColName of type double and 
  //respective Row
  double getDouble(const std::string& ColName, long Row);

  //Returning value from table ColName of type bool and 
  //respective Row
  bool getBool(const std::string& ColName, long Row);

  //Setting value for ColName of type bool. Inserting 
  //DBColProfile into DataList.
  void setBool(const std::string &ColName, bool value);

  //Setting value for ColName of type double. Inserting 
  //DBColProfile into DataList.
  void setDouble(const std::string  & ColName, double value);

  //Setting value for ColName of type string. Inserting 
  //DBColProfile into DataList.
  void setString( const std::string  & ColName, const std::string &value);

  //Setting value for ColName of type long. Inserting 
  //DBColProfile into DataList.
  void setLong( const std::string &ColName, long value);

  //Setting Row to respective postion.
  bool first();

  //Setting Row to respective postion.
  bool last();

  //Setting Row to respective postion.
  bool next();

  //Setting Row to respective postion.
  bool prev();

  virtual ~CSMC_DBData();

protected:
  //Base class for database handling. Valid argument 
  //"Connection" neccessary !
  CSMC_DBData(const std::string &TableName, cCBS_StdConnection *StdConnection );

  // to be backwards compatible
  CSMC_DBData(const std::string &TableName, cCBS_Connection* Connection);

    // new constructor
  CSMC_DBData(const std::string &TableName);

  std::vector<std::string> getColumnList();

public:
  //Returning value from table ColName of type string and 
  //respective Row
  std::string getString(const std::string  & ColName, long Row);

  //Returning total number of rows.
  long getLastRow();

  // closing actual statements
  void close();

  bool updateOrInsert();
  void setPreparedStatement();

  bool copy();

  // Creates a copy statement based on source table to copy data from 
  // source table to destination table. 
  // Before calling this function where statement in the 
  // source table has to be set by calling pSourceTable.addWhereClause(...)
  // and columns in destination table which are not in source table like HEATID, TREATID, PLANT
  // have to be set by using set-functions (setHEATID(HEATID))
  bool copyByInsert(CSMC_DBData* pSourceTable);

  // Creates an update statement based on source table to update data 
  // in destination table. 
  // Before calling this function where statement in the 
  // source AND destination table has to be set by calling 
  // pSourceTable.addWhereClause(...)
  bool copyByUpdate(CSMC_DBData* pSourceTable);

  bool executeSQL(const std::string &pSQL);

  void resetLastError();

  void logLastError(long Level);
 
  cCBS_ODBC_DBError getLastError();

  void setLastError(const std::string &pMsgText, int pErrCode, const std::string &pSQLState);

  std::string getActStatement();
private:

  bool isActive(const std::string &ColName);

  bool execute_copy();
  bool execute_copyByInsert(CSMC_DBData* pSourceTable);
  bool execute_copyByUpdate(CSMC_DBData* pSourceTable);

  bool execute_update();

  bool execute_update_fail_on_no_row();

  bool execute_select();

  bool execute_insert();

  bool execute_deleteRows();

  //Base class handling CBS DB Classes functionalities 
  //providing comfortable DB access in derived classes.
  long m_ActRow;

  std::string m_Url;

  std::string m_Password;

  std::string m_Login;

  bool createUpdateStatement();

  bool  createInsertStatement();

  void createStatement();

  void createSelectStatement();

  void createPreparedStatement(const std::string& Statement);

  std::vector<std::string> m_WhereClauseList;
  std::map<std::string, std::string> m_CopyColumnList;

  long getColIndex(const std::string& ColName);

  //Setting Field of respective Statement regarding 
  //DBColProfile data of DataList members.
  bool setRowData(const std::string &Type);

  void clearDataList();

  long getColumnType(const std::string& ColName);
  bool findColumn(const std::string& ColName);

  //List representing DBCOlProfile objects being inserted 
  //by respective set methods (setString...)
  std::map<std::string,CSMC_DBColProfile*>  m_ColProfileList;

  //Performing select statement and fill ResultSet.
  //returns true if ResultSet was successfully created
  bool readData();
  void findLastRow();

  bool checkMetaData();

  static const std::string CommandUpdate;
  static const std::string CommandInsert;

  // for logging of set values for prepared statement
  std::string m_PreparedValues;

  //the copy constructor and the assignment operator should be private as we normally would not want to make a copy
  CSMC_DBData(const CSMC_DBData& From);
  CSMC_DBData& operator=(const CSMC_DBData& Value);
};

#endif /* _INC_CSMC_DBDATA_414EEE0801A3_INCLUDED */
