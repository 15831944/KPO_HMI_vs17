// Copyright (C) 2004 SMS Siemag AG
#include <iostream>
#include <sstream>
#include <math.h>

#include "cCBS_StdDB_Task.h"
#include "cCBS_StdInitBase.h"

#include "iData_Provider_s.hh"

#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdFrame_TaskController.h"

#include "CDataConversion.h"

#include "CSMC_EventLogFrameController.h"
#include "CSMC_RuntimeController.h"

#include "CSMC_DBColProfile.h"
#include "CSMC_DBColProfileDate.h"
#include "CSMC_DBColProfileDouble.h"
#include "CSMC_DBColProfileBool.h"
#include "CSMC_DBColProfileString.h"
#include "CSMC_DBColProfileLong.h"

#include "CSMC_DBMetaData.h"
#include "CSMC_DBData.h"


const long CSMC_DBData::unspecLong = DEF::Inv_Long;

const std::string CSMC_DBData::unspecString(DEF::Inv_String);

const double CSMC_DBData::unspecDouble = DEF::Inv_Double;

const CDateTime CSMC_DBData::unspecDate = CDateTime::InvalidDateTime();

const std::string CSMC_DBData::Default("Default");

const std::string CSMC_DBData::CommandUpdate("U");
const std::string CSMC_DBData::CommandInsert("I");


// to be backwards compatible
CSMC_DBData::CSMC_DBData(const std::string &TableName, cCBS_Connection* Connection)
: m_TableName(TableName)
, m_LastRow(0)
, m_ActRow(0)
, m_pStatement(0)
, m_pSelectStatement(0)
, m_pResultSet(0) 
, m_TableExists(true)
, m_pPreparedStatement(0)
{  
  if( Connection )
  {
    try
    {
      // try to find respective connection data at cCBS_StdDB_Task
      cCBS_StdDB_Task* pDB_Task = cCBS_StdDB_Task::getInstance();

      m_pCBS_StdConnection = pDB_Task->getCBS_StdConnection(Connection);

      if (!m_pCBS_StdConnection )
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);

        std::string message = "Can not instantiate DB class in case of NULL pointer to connection for table "+m_TableName;  

        pEventLog->EL_DatabaseConnectionError(sMessage,message.c_str(),"");
        // pEventLog->EL_DatabaseConnectionError(sMessage,message.c_str(),"Terminating program!");
        // exit(EXIT_FAILURE);
      }
      else
      {
        // store respective connection data
        m_Login    = m_pCBS_StdConnection->getLogin();
        m_Password = m_pCBS_StdConnection->getPassword();
        m_Url      = m_pCBS_StdConnection->getUrl();

        // get metadata for the table concerned
        if (!m_TableName.empty())
        {
          try
          {
            if ( !checkMetaData() )
            {
              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              std::string message = "Can not read metedata";  
              pEventLog->EL_DBReadError(sMessage, "", m_TableName.c_str(), message.c_str());
            }
          }
          catch(cCBS_DBExc_ConnectionError &ce) 
          {
            doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::CSMC_DBData(..)");

            // try reading metadata for a second time in case of broken connection
            if ( !checkMetaData() )
            {
              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              std::string message = "Can not read metedata";  
              pEventLog->EL_DBReadError(sMessage, "", m_TableName.c_str(), message.c_str());
            }
          }
        }
        else
        {
          log("ERROR: Empty table name.",1);
        }

        close(); // close all opened cursors

      } // if (!m_pCBS_StdConnection ) else 
    }
    catch(cCBS_DBExc_ConnectionError &ce) 
    {
      doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::CSMC_DBData(..)");
    }
    catch(cCBS_DBExc &e) 
    {
      doOnCBS_DBExc(e,"CSMC_DBData::CSMC_DBData(..)");
    }
    catch(...)
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::CSMC_DBData",m_TableName.c_str());
    }
  }
  else
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);

    std::string message = "Can not instantiate DB class in case of NULL pointer to connection for table "+m_TableName;  

    pEventLog->EL_DatabaseConnectionError(sMessage,message.c_str(),"");
    // pEventLog->EL_DatabaseConnectionError(sMessage,message.c_str(),"Terminating program!");
    // exit(EXIT_FAILURE);
  }

  //reset Last Error variable
  resetLastError();
}

// new constructor
CSMC_DBData::CSMC_DBData(const std::string &TableName)
: m_TableName(TableName)
, m_LastRow(0)
, m_ActRow(0)
, m_pStatement(0)
, m_pSelectStatement(0)
, m_pResultSet(0) 
, m_TableExists(true)
, m_pPreparedStatement(0)
, m_pCBS_StdConnection(0)
{
  cCBS_StdInitBase *pStdInitBase = cCBS_StdInitBase::getInstance();

  try
  {  
    if ( !( pStdInitBase->getEntry("DATABASE", "SMC_DBName", m_Url) &&
            pStdInitBase->getEntry("DATABASE", "SMC_DBUser", m_Login)  &&
            pStdInitBase->getEntry("DATABASE", "SMC_DBPassword", m_Password) ))
    {
      std::cerr << "Can not read SMC database settings from ini-file" << std::endl;

      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(Message,"ini file error","CSMC_FrameTask::setDBConnectionParameter()","cannot read SMC database settings from ini file");
    }
    else
    {
      m_pCBS_StdConnection = cCBS_StdDB_Task::getInstance()->getCBS_StdConnection(m_Url, m_Login, m_Password);

      if( m_pCBS_StdConnection )
      {
        // store respective connection data
        m_Login    = m_pCBS_StdConnection->getLogin();
        m_Password = m_pCBS_StdConnection->getPassword();
        m_Url      = m_pCBS_StdConnection->getUrl();

        // get metadata for the table concerned
        if (!m_TableName.empty())
        {
          try
          {
            if ( !checkMetaData() )
            {
              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              std::string message = "Can not read metedata";  
              pEventLog->EL_DBReadError(sMessage, "", m_TableName.c_str(), message.c_str());
            }
          }
          catch(cCBS_DBExc_ConnectionError &ce) 
          {
            doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::CSMC_DBData(..)");

            // try reading metadata for a second time in case of broken connection
            if ( !checkMetaData() )
            {
              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              std::string message = "Can not read metedata";  
              pEventLog->EL_DBReadError(sMessage, "", m_TableName.c_str(), message.c_str());
            }
          }
        }
        else
        {
          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ExceptionCaught(sMessage,"Table name empty","CSMC_DBData::CSMC_DBData","");
        }

        close(); // close all opened cursors
      }
    }
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(Message,"ini file error","CSMC_FrameTask::setDBConnectionParameter()","cannot read SMC database settings from ini file");
  }

}

CSMC_DBData::CSMC_DBData(const std::string &TableName, cCBS_StdConnection *StdConnection)
: m_TableName(TableName)
, m_LastRow(0)
, m_ActRow(0)
, m_pStatement(0)
, m_pSelectStatement(0)
, m_pResultSet(0) 
, m_TableExists(true)
, m_pPreparedStatement(0)
, m_pCBS_StdConnection(StdConnection)
{  
  if( m_pCBS_StdConnection )
  {
    try
    {
      // store respective connection data
      m_Login    = m_pCBS_StdConnection->getLogin();
      m_Password = m_pCBS_StdConnection->getPassword();
      m_Url      = m_pCBS_StdConnection->getUrl();

      // get metadata for the table concerned
      if (!m_TableName.empty())
      {
        try
        {
          if ( !checkMetaData() )
          {
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            std::string message = "Can not read metedata";  
            pEventLog->EL_DBReadError(sMessage, "", m_TableName.c_str(), message.c_str());
          }
        }
        catch(cCBS_DBExc_ConnectionError &ce) 
        {
          doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::CSMC_DBData(..)");

          // try reading metadata for a second time in case of broken connection
          if ( !checkMetaData() )
          {
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            std::string message = "Can not read metedata";  
            pEventLog->EL_DBReadError(sMessage, "", m_TableName.c_str(), message.c_str());
          }
        }
      }
      else
      {
        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ExceptionCaught(sMessage,"Table name empty","CSMC_DBData::CSMC_DBData","");
      }

      close(); // close all opened cursors
    }
    catch(cCBS_DBExc_ConnectionError &ce) 
    {
      doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::CSMC_DBData(..)");
    }
    catch(cCBS_DBExc &e) 
    {
      doOnCBS_DBExc(e,"CSMC_DBData::CSMC_DBData(..)");
    }
    catch(...)
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::CSMC_DBData",m_TableName.c_str());
    }
  }
  else
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);

    std::string message = "Can not instantiate DB class in case of NULL pointer to connection for table "+m_TableName;  

    pEventLog->EL_DatabaseConnectionError(sMessage,message.c_str(),"");
    // pEventLog->EL_DatabaseConnectionError(sMessage,message.c_str(),"Terminating program!");
    // exit(EXIT_FAILURE);
  }

  //reset Last Error variable
  resetLastError();
}

CSMC_DBData::~CSMC_DBData()
{
  initStatements();

  std::map<std::string,CSMC_DBColProfile*>::iterator it;

  for ( it = m_ColProfileList.begin(); it != m_ColProfileList.end(); ++it)
  {
    if ( it->second )
    {
      delete it->second;
    }
  }

  m_ColProfileList.erase(m_ColProfileList.begin(),m_ColProfileList.end());

}

void CSMC_DBData::setLong(const std::string &ColName, long value)
{
  CSMC_DBColProfileLong *pColProfile = 0;

  // try to find existing ebtry or insert entry
  std::map<std::string,CSMC_DBColProfile*>::iterator it = m_ColProfileList.find(ColName);
  if ( it == m_ColProfileList.end())
  {
    pColProfile = new CSMC_DBColProfileLong(m_TableName,ColName);

    // insert profile into list
    m_ColProfileList.insert( std::pair <std::string,CSMC_DBColProfile*>(ColName,pColProfile));
  }
  else
  {
    // get pointer to existing profile
    pColProfile = static_cast<CSMC_DBColProfileLong*>(it->second);
  }

  if (getTraceLevel() > 3)
  {
    std::stringstream Message;
    Message << "Setting value for " << m_TableName << "-" << ColName << ": " ;
    Message << value ;
    log(Message.str(),4);
  }

  pColProfile->setvalue(value);
  pColProfile->setActive(true);

}

long CSMC_DBData::getLong(const std::string& ColName, long Row)
{
  long RetValue = CSMC_DBData::unspecLong;

  try
  {
    if (m_pResultSet && setRow(Row))
    {
      if ( !isNull(ColName, Row) )
      {
        RetValue = m_pResultSet->getInt(ColName);

        if (getTraceLevel() > 3)
        {
          std::stringstream Message;
          Message << "Database returns " << m_TableName << "-" << ColName << "-" << Row << "->";
          Message << RetValue ;
          log(Message.str(),4);
        }
      }
    }
    else
    {
      if (getTraceLevel() > 1)
      {
        std::stringstream Message;
        Message << "getLong not successful for ColName : " << ColName << " Row : " << Row;
        log(Message.str(),2);
      }
    }
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::getLong(..)");
    RetValue = CSMC_DBData::unspecLong;

  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::getLong(..)");
    RetValue = CSMC_DBData::unspecLong;
  }
  catch(...)
  {
    std::stringstream Message;
    Message << m_TableName << "-" << ColName << "-" << Row ;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::getLong",Message.str().c_str());
    RetValue = CSMC_DBData::unspecLong;
  }
  return RetValue;
}

void CSMC_DBData::setDouble(const std::string &ColName, double value)
{
  CSMC_DBColProfileDouble *pColProfile = 0;

  // try to find existing ebtry or insert entry
  std::map<std::string,CSMC_DBColProfile*>::iterator it = m_ColProfileList.find(ColName);
  if ( it == m_ColProfileList.end())
  {
    pColProfile = new CSMC_DBColProfileDouble(m_TableName,ColName);

    // insert profile into list
    m_ColProfileList.insert( std::pair <std::string,CSMC_DBColProfile*>(ColName,pColProfile));
  }
  else
  {
    // get pointer to existing profile
    pColProfile = static_cast<CSMC_DBColProfileDouble*>(it->second);
  }

  if (getTraceLevel() > 3)
  {
    std::stringstream Message;
    Message << "Setting value for " << m_TableName << "-" << ColName << ": ";
    Message << value ;
    log(Message.str(),4);
  }

  pColProfile->setvalue(value);
  pColProfile->setActive(true);

}

double CSMC_DBData::getDouble(const std::string& ColName, long Row)
{
  double RetValue = CSMC_DBData::unspecDouble;

  try
  {
    if (m_pResultSet && setRow(Row))
    {
      if ( !isNull(ColName, Row) )
      {
        RetValue = m_pResultSet->getDouble(ColName);

        if (getTraceLevel() > 3)
        {
          std::stringstream Message;
          Message << "Database returns " << m_TableName << "-" << ColName << "-" << Row << "->" ;
          Message << RetValue ;
          log(Message.str(),4);
        }
      }
    }
    else
    {
      if (getTraceLevel() > 1)
      {
        std::stringstream Message;
        Message << "getDouble not successful for ColName : " << ColName << " Row : " << Row;
        log(Message.str(),2);
      }
    }

  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::getDouble(..)");
    RetValue = CSMC_DBData::unspecDouble;
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::getDouble(..)");
    RetValue = CSMC_DBData::unspecDouble;
  }
  catch(...)
  {
    std::stringstream Message;
    Message << m_TableName << "-" << ColName << "-" << Row ;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::getDouble",Message.str().c_str());
    RetValue = CSMC_DBData::unspecDouble;
  }
  return RetValue;
}

void CSMC_DBData::setString( const std::string &ColName, const std::string &value)
{
  CSMC_DBColProfileString *pColProfile = 0;

  // try to find existing ebtry or insert entry
  std::map<std::string,CSMC_DBColProfile*>::iterator it = m_ColProfileList.find(ColName);
  if ( it == m_ColProfileList.end())
  {
    pColProfile = new CSMC_DBColProfileString(m_TableName,ColName);

    // insert profile into list
    m_ColProfileList.insert( std::pair <std::string,CSMC_DBColProfile*>(ColName,pColProfile));
  }
  else
  {
    // get pointer to existing profile
    pColProfile = static_cast<CSMC_DBColProfileString*>(it->second);
  }

  if (getTraceLevel() > 3)
  {
    std::stringstream Message;
    Message << "Setting value for " << m_TableName << "-" << ColName << ": " ;
    Message << value ;
    log(Message.str(),4);
  }

  pColProfile->setvalue(std::string(value));
  pColProfile->setActive(true);

}

std::string CSMC_DBData::getString(const std::string &ColName, long Row)
{
  std::string RetValue = CSMC_DBData::unspecString;
  try
  {
    if (m_pResultSet && setRow(Row))
    {
      if ( !isNull(ColName, Row) )
      {
        RetValue = m_pResultSet->getString(ColName);

        if (getTraceLevel() > 3)
        {
          std::stringstream Message;
          Message << "Database returns " << m_TableName << "-" << ColName << "-" << Row << "->" ;
          Message << RetValue ;
          log(Message.str(),4);
        }
      }
    }
    else
    {
      if (getTraceLevel() > 1)
      {
        std::stringstream Message;
        Message << "getString not successful for ColName : " << ColName << " Row : " << Row;
        log(Message.str(),2);
      }
    }
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::getString(..)");
    RetValue = CSMC_DBData::unspecString;
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::getString(..)");
    RetValue = CSMC_DBData::unspecString;
  }
  catch(...)
  {
    std::stringstream Message;
    Message << m_TableName << "-" << ColName << "-" << Row ;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::getString",Message.str().c_str());
    RetValue = CSMC_DBData::unspecString;
  }
  return RetValue;
}

void CSMC_DBData::setBool(const std::string  & ColName, bool value)
{
  CSMC_DBColProfileBool *pColProfile = 0;

  // try to find existing ebtry or insert entry
  std::map<std::string,CSMC_DBColProfile*>::iterator it = m_ColProfileList.find(ColName);
  if ( it == m_ColProfileList.end())
  {
    pColProfile = new CSMC_DBColProfileBool(m_TableName,ColName);

    // insert profile into list
    m_ColProfileList.insert( std::pair <std::string,CSMC_DBColProfile*>(ColName,pColProfile));
  }
  else
  {
    // get pointer to existing profile
    pColProfile = static_cast<CSMC_DBColProfileBool*>(it->second);
  }

  if (getTraceLevel() > 3)
  {
    std::stringstream Message;
    Message << "Setting value for " << m_TableName << "-" << ColName << ": " ;
    Message << value ;
    log(Message.str(),4);
  }

  pColProfile->setvalue(value);
  pColProfile->setActive(true);

}

bool CSMC_DBData::getBool(const std::string& ColName, long Row)
{
  bool RetValue = false;

  try
  {
    if (m_pResultSet && setRow(Row))
    {
      if ( !isNull(ColName, Row) )
      {
        RetValue = m_pResultSet->getBoolean(ColName);

        if (getTraceLevel() > 3)
        {
          std::stringstream Message;
          Message << "Database returns " << m_TableName << "-" << ColName << "-" << Row << "->";
          Message << RetValue ;
          log(Message.str(),4);
        }
      }
    }
    else
    {
      if (getTraceLevel() > 1)
      {
        std::stringstream Message;
        Message << "getBool not successful for ColName : " << ColName << " Row : " << Row;
        log(Message.str(),2);
      }
    }

  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::getBool(..)");
    RetValue = false;
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::getBool(..)");
    RetValue = false;
  }
  catch(...)
  {
    std::stringstream Message;
    Message << m_TableName << "-" << ColName << "-" << Row ;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::getBool",Message.str().c_str());
    RetValue = false;
  }
  return RetValue;
}


void CSMC_DBData::setDate(const std::string& ColName, CDateTime & value)
{
  CSMC_DBColProfileDate *pColProfile = 0;

  // try to find existing ebtry or insert entry
  std::map<std::string,CSMC_DBColProfile*>::iterator it = m_ColProfileList.find(ColName);
  if ( it == m_ColProfileList.end())
  {
    pColProfile = new CSMC_DBColProfileDate(m_TableName,ColName);

    // insert profile into list
    m_ColProfileList.insert( std::pair <std::string,CSMC_DBColProfile*>(ColName,pColProfile));
  }
  else
  {
    // get pointer to existing profile
    pColProfile = static_cast<CSMC_DBColProfileDate*>(it->second);
  }

  pColProfile->setDateTime(value);
  pColProfile->setActive(true);

}

CDateTime CSMC_DBData::getDate(const std::string& ColName, long Row)
{
  CDateTime RetValue = CSMC_DBData::unspecDate;
  try
  {
    if (m_pResultSet && setRow(Row))
    {
      if ( !isNull(ColName, Row) )
      {
        DB_CLASSLIB_DATE const *ptdDate = m_pResultSet->getDate(ColName);
        //KLUW: This is special for the ODBC driver. There is an error with the precision.
        DB_CLASSLIB_DATE D = *ptdDate;
        D.msecond /= 1000000;
        RetValue.SetTime(&D);

        if (getTraceLevel() > 3)
        {
          std::stringstream Message;
          Message << "Database returns " << m_TableName << "-" << ColName << "-" << Row << "->";
          Message << RetValue ;
          log(Message.str(),4);
        }
      }
    }
    else
    {
      if (getTraceLevel() > 1)
      {
        std::stringstream Message;
        Message << "getDate not successful for ColName : " << ColName << " Row : " << Row;
        log(Message.str(),2);
      }
    }
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::getDate(..)");
    RetValue = CSMC_DBData::unspecDate;
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::getDate(..)");
    RetValue = CSMC_DBData::unspecDate;
  }
  catch(...)
  {
    std::stringstream Message;
    Message << m_TableName << "-" << ColName << "-" << Row ;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::getDate",Message.str().c_str());
    RetValue = CSMC_DBData::unspecDate;
  }
  return RetValue;
}

bool CSMC_DBData::first()
{
  bool RetValue = false;

  try
  {
    if (m_pResultSet)
    {
      if (m_pResultSet->first())
      {
        RetValue = setRow(1);
      }
      else
      {
        if (getTraceLevel() > 3)
        {
          log("No data found with statement: " + m_ActStatement, 4);
        }
      }
    }
    else
    {
      if (getTraceLevel() > 0)
      {
        log("first(): m_pResultSet is invalid", 1);
      }
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::first",m_TableName.c_str());
    RetValue = false;
  }
  return RetValue;
}

bool CSMC_DBData::last()
{
  bool RetValue = false;
  try
  {
    if (m_pResultSet)
    {
      if (m_pResultSet->last())
      {
        RetValue = setRow(m_LastRow);
      }
      else
      {
        if (getTraceLevel() > 1)
        {
          log("set last on result set not successful",2);
        }
      }
    }
    else
    {
      if (getTraceLevel() > 0)
      {
        log("last(): m_pResultSet is invalid", 1);
      }
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::last",m_TableName.c_str());
    RetValue = false;
  }
  return RetValue;
}

bool CSMC_DBData::next()
{
  bool RetValue = false;
  try
  {
    if (m_pResultSet)
    {
      if (m_pResultSet->next())
      {
        RetValue = setRow(m_ActRow + 1);
      }
      else
      {
        if (getTraceLevel() > 0)
        {
          log("set next on result set not successful", 1);
        }
      }
    }
    else
    {
      if (getTraceLevel() > 0)
      {
        log("next(): m_pResultSet is invalid", 1);
      }
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::next",m_TableName.c_str());
    RetValue = false;
  }
  return RetValue;
}

bool CSMC_DBData::prev()
{
  bool RetValue = false;
  try
  {
    if (m_pResultSet && m_pResultSet->prev())
    {
      RetValue = setRow(m_ActRow - 1);
    }
    else
    {
      if (getTraceLevel() > 0)
      {
        log("prev not successful", 1);
      }
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::prev",m_TableName.c_str());
    RetValue = false;
  }
  return RetValue;
}

bool CSMC_DBData::setRow(long Row)
{
  bool RetValue = false;

  // Row = -1 must be handled as default = m_ActRow !

  try
  {
    if (Row <= m_LastRow)
    {
      if(Row > 0)
      {
        m_ActRow = Row;
      }

      if (m_pResultSet && m_ActRow > 0)
      {
        m_pResultSet->absolute(m_ActRow);
        RetValue = true;
      }
    }
    else
    {
      if (getTraceLevel() > 3)
      {
        log("setRow for " + m_TableName + "(" + m_Statement + ") : ROW INDEX OUT OF RANGE",4);
      }
    }
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::setRow(..)");
    RetValue = false;
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::setRow(..)");
    RetValue = false;
  }
  catch(...)
  {
    std::stringstream Message;
    Message << m_TableName << "-" << Row ;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::setRow",Message.str().c_str());
    RetValue = false;
  }
  return RetValue;
}

long CSMC_DBData::getLastRow()
{
  return m_LastRow;
}

void CSMC_DBData::findLastRow()
{
  CSMC_RuntimeController RuntimeController("CSMC_DBData::findLastRow");

  m_LastRow = 0;

  if (m_pResultSet)
  {
    m_pResultSet->beforeFirst();

    while (m_pResultSet->next())
    {
      m_LastRow ++;
    }
  }

  if (getTraceLevel() > 2)
  {
    std::stringstream Message;
    Message << m_TableName << "(" << m_Statement << ")";
    Message << " - Found rows : " << m_LastRow;

    log(Message.str(),3);
  }
}

long CSMC_DBData::getColIndex(const std::string& ColName)
{
  long RetValue = -1;
  try
  {
    if (m_pResultSet)
    {
      RetValue = m_pResultSet->findColumn(ColName);
    }
  }
  catch(...)
  {
    std::stringstream Message;
    Message << m_TableName << "-" << ColName ;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::getColIndex",Message.str().c_str());
    RetValue = -1;
  }
  return RetValue;
}


bool CSMC_DBData::select(const std::string& Statement)
{
  m_Statement = Statement;
  return select();
}

bool CSMC_DBData::select()
{
  CSMC_RuntimeController RuntimeController("CSMC_DBData::select");

  bool RetValue = false;

  try
  {
    if ( getpCBSConnection() && m_TableExists )
    {
      // try to select data
      RetValue = execute_select();
    }
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    // try to reconnect once
    if ( handleConnectionError() )
    {
      try
      {
        // try to select data
        RetValue = execute_select();
      }
      catch(cCBS_DBExc_ConnectionError &ce) 
      {
        doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::select(..)");
        RetValue = false;
      }
      catch(cCBS_DBExc &e) 
      {
        doOnCBS_DBExc(e,"CSMC_DBData::select()");
        RetValue = false;
      }
      catch(...)
      {
        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::select",m_TableName.c_str());
        RetValue = false;
      }
    }
    else
    {
      doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::select()");
      RetValue = false;
    }
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::select()");
    RetValue = false;
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::select",m_TableName.c_str());
    RetValue = false;
  }
  return RetValue;
}

bool CSMC_DBData::readData()
{
  bool RetValue = false;

  if( getpCBSConnection() )
  {
    if(!m_Statement.empty())
    {
      createSelectStatement();

      if (m_pSelectStatement)
      {
        // for exception handling
        m_ActStatement = m_Statement;

        log(m_ActStatement,3);

        cCBS_StdDB_Task::getInstance()->setStateDetails("CSMC_DBData::readData()", m_ActStatement, 4);

        m_pResultSet = m_pSelectStatement->executePtQuery(m_Statement);          
        
        if (m_pResultSet)
        {
          RetValue = true;
        }
        else
        {
          log(m_TableName + " (" + m_Statement + ") ERROR: NO RESULT SET AFTER EXECUTE QUERY!", 1);
        }
      }
      else
      {
        log(m_TableName + " : ERROR ON CREATE SELECT STATEMENT !", 1);
      }
    }
    else
    {
      log(m_TableName + " : ERROR: SQL STATEMENT IS EMPTY!", 1);
    }
  }

  return RetValue;
}

bool CSMC_DBData::update()
{
  CSMC_RuntimeController RuntimeController("CSMC_DBData::update");

  // instantiating task controller
  // will work in RELEASED version only !
  // terminates task AND component, if execution of event will take longer than
  // configured time from [ProcessControl] ControlTime = ...
  cCBS_StdFrame_TaskController TaskController( cCBS_StdDB_Task::getInstance() );

  bool RetValue = false;

  try
  {
    if ( getpCBSConnection() && m_TableExists )
    {
      // try to update data
      RetValue = execute_update();
    }
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    // try to reconnect once
    if ( handleConnectionError() )
    {
      try
      {
        // try to update data
        RetValue = execute_update();
      }
      catch(cCBS_DBExc_ConnectionError &ce) 
      {
        doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::update(..)");
        RetValue = false;
      }
      catch(cCBS_DBExc &e) 
      {
        doOnCBS_DBExc(e,"CSMC_DBData::update()");
        RetValue = false;
      }
      catch(...)
      {
        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::update",m_TableName.c_str());
        RetValue = false;
      }

    }
    else
    {
      doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::update()");
      RetValue = false;
    }
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::update()");
    RetValue = false;
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::update",m_TableName.c_str());
    RetValue = false;
  }

  clearDataList();

  return RetValue;
}

bool CSMC_DBData::deleteRows()
{
  CSMC_RuntimeController RuntimeController("CSMC_DBData::deleteRows");

  // instantiating task controller
  // will work in RELEASED version only !
  // terminates task AND component, if execution of event will take longer than
  // configured time from [ProcessControl] ControlTime = ...
  cCBS_StdFrame_TaskController TaskController( cCBS_StdDB_Task::getInstance() );

  bool RetValue = false;

  try
  {
    if ( getpCBSConnection() && m_TableExists )
    {
      // try to delete data
      RetValue = execute_deleteRows();
    }
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    // try to reconnect once
    if ( handleConnectionError() )
    {
      try
      {
        // try to delete data
        RetValue = execute_deleteRows();
      }
      catch(cCBS_DBExc_ConnectionError &ce) 
      {
        doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::deleteRows(..)");
        RetValue = false;
      }
      catch(cCBS_DBExc &e) 
      {
        doOnCBS_DBExc(e,"CSMC_DBData::deleteRows()");
        RetValue = false;
      }
      catch(...)
      {
        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::deleteRows",m_TableName.c_str());
        RetValue = false;
      }
    }
    else
    {
      doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::deleteRows()");
      RetValue = false;
    }
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::deleteRows()");
    RetValue = false;
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::deleteRows",m_TableName.c_str());
    RetValue = false;
  }
  clearDataList();

  return RetValue;
}

bool CSMC_DBData::insert()
{
  CSMC_RuntimeController RuntimeController("CSMC_DBData::insert");

  // instantiating task controller
  // will work in RELEASED version only !
  // terminates task AND component, if execution of event will take longer than
  // configured time from [ProcessControl] ControlTime = ...
  cCBS_StdFrame_TaskController TaskController( cCBS_StdDB_Task::getInstance() );


  bool RetValue = false;

  try
  {
    if ( getpCBSConnection() && m_TableExists )
    {
      // try to insert data
      RetValue = execute_insert();
    }
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    // try to reconnect once
    if ( handleConnectionError() )
    {
      try
      {
        // try to insert data
        RetValue = execute_insert();
      }
      catch(cCBS_DBExc_ConnectionError &ce) 
      {
        doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::insert(..)");
        RetValue = false;
      }
      catch(cCBS_DBExc &e) 
      {
        doOnCBS_DBExc(e,"CSMC_DBData::insert()");
        RetValue = false;
      }
      catch(...)
      {
        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::insert",m_TableName.c_str());
        RetValue = false;
      }
    }
    else
    {
      doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::insert()");
      RetValue = false;
    }
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::insert()");
    RetValue = false;
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::insert",m_TableName.c_str());
    RetValue = false;
  }

  clearDataList();

  return RetValue;
}

void CSMC_DBData::clearDataList()
{
  std::map<std::string,CSMC_DBColProfile*>::iterator it;

  for ( it = m_ColProfileList.begin(); it != m_ColProfileList.end(); ++it)
  {
    it->second->setActive(false);
  }
}

long CSMC_DBData::getColumnType(const std::string& ColName)
{
  long RetValue = CSMC_DBColProfile::SMC_DB_UndefinedType;

  std::map<std::string,CSMC_DBColProfile*>::iterator it;

  it = m_ColProfileList.find(ColName);

  if ( it != m_ColProfileList.end())
  {
    RetValue = it->second->getType();
  }

  return RetValue;
}


std::vector<std::string> CSMC_DBData::getColumnList()
{
  std::vector<std::string> RetList;
  std::map<std::string,CSMC_DBColProfile*>::iterator it;

  for ( it = m_ColProfileList.begin(); it != m_ColProfileList.end(); ++it)
  {
    RetList.push_back(it->first);
  }

  return RetList;
}

bool CSMC_DBData::findColumn(const std::string& ColName)
{
  bool RetValue = false;

  if ( m_ColProfileList.find(ColName) != m_ColProfileList.end())
  {
    RetValue = true;
  }

  return RetValue;
}

void CSMC_DBData::setColumnsFromTable(CSMC_DBData* pSourceTable, long Row)
{
  std::map<std::string,std::string> ColList;
  if ( pSourceTable )
  {
    std::vector<std::string> ColumnList = pSourceTable->getColumnList();
    std::vector<std::string>::iterator it;
    for (it = ColumnList.begin() ; it != ColumnList.end() ; ++it)
    {
      std::string ColName = *it;

      ColList.insert(std::pair<std::string,std::string>(ColName,ColName));
    }
  }

  setColumnsFromTable(pSourceTable, Row, ColList );
}


void CSMC_DBData::setColumnsFromTable(CSMC_DBData* pSourceTable, long Row, std::map<std::string,std::string> ColumnList )
{
  try
  {
    if ( pSourceTable )
    {
      // get ColumnList from source tabel
      std::map<std::string,std::string>::iterator it;

      for (it = ColumnList.begin() ; it != ColumnList.end() ; ++it)
      {
        std::string ColNameSource = it->first;
        std::string ColNameAim    = it->second;

        // check if column has already been called by set-method
        if ( isActive(ColNameAim) )
        {
          continue;
        }

        // check if column name is available at both tables 
        if ( pSourceTable->findColumn(ColNameSource) && findColumn(ColNameAim) )
        {
          long SMC_DB_TypeSource = pSourceTable->getColumnType(ColNameSource);
          long SMC_DB_TypeAim    = getColumnType(ColNameAim);

          // check if column types are identical 
          if ( SMC_DB_TypeSource == SMC_DB_TypeAim && 
               SMC_DB_TypeSource != CSMC_DBColProfile::SMC_DB_UndefinedType )
          {
            try
            {
              // read data from source table and write to aim table
              switch (SMC_DB_TypeSource)
              {
              case CSMC_DBColProfile::SMC_DB_Bool :
                {
                  setBool(ColNameAim,pSourceTable->getBool(ColNameSource,Row));
                  break;
                }
              case CSMC_DBColProfile::SMC_DB_Date :
                {
                  setDate(ColNameAim,pSourceTable->getDate(ColNameSource,Row));
                  break;
                }
              case CSMC_DBColProfile::SMC_DB_Double :
                {
                  setDouble(ColNameAim,pSourceTable->getDouble(ColNameSource,Row));
                  break;
                }
              case CSMC_DBColProfile::SMC_DB_Long :
                {
                  setLong(ColNameAim,pSourceTable->getLong(ColNameSource,Row));
                  break;
                }
              case CSMC_DBColProfile::SMC_DB_String :
                {
                  setString(ColNameAim,pSourceTable->getString(ColNameSource,Row));
                  break;
                }
              default:  
                {
                  // 
                  break;
                }
              }
            }
            catch(...)
            {
              std::stringstream Message;
              Message << "System cannot set data to column "
                << m_TableName 
                << " "
                << ColNameAim ;

              cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::setRowFromTable",Message.str().c_str());
            }
          }
          else
          {
            if (getTraceLevel() > 0)
            {
              std::stringstream Message;
              Message << "CSMC_DBData::setRowFromTable(...) : ERROR : System cannot set data to column "
                      << m_TableName 
                      << " "
                      << ColNameAim 
                      << " : different column type located !";

              log(Message.str(), 1);
            }
          }
        }
        else
        {
          if (getTraceLevel() > 0)
          {
            std::stringstream Message;
            Message << "CSMC_DBData::setRowFromTable(...) : ERROR : System cannot set data to column "
                    << m_TableName 
                    << " "
                    << ColNameAim 
                    << " : column not found !";

            log(Message.str(), 1);
          }
        }
      }
    }
    else
    {
      log("CSMC_DBData::setRowFromTable(...) : ERROR : pointer to source table not defined ", 1);
    }
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::setRowFromTable()");
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::setRowFromTable()");
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::setRowFromTable","");
  }
}


bool CSMC_DBData::setRowData(const std::string &Type)
{
  bool RetValue = false;
  std::map<std::string,CSMC_DBColProfile*>::iterator it;

  m_PreparedValues.clear();
  short ColIndex = 0;

  for ( it = m_ColProfileList.begin(); it != m_ColProfileList.end(); ++it)
  {
    if (it->second->isActive())
    {
      RetValue = true;
      std::stringstream Value;

      if (Type == CommandInsert)
      {
        // insert <,> before each entry except the first one
        if ( ColIndex > 0 )
        {
          m_PreparedValues += ",";
        }
        ColIndex++;
      }

      long Col = -1;
      if (Type == CommandUpdate)
      {
        Col = getColIndex(it->second->getColName());
      }
      else
      {
        Col = it->second->getCol();
      }

      if ( it->second->getType() == CSMC_DBColProfile::SMC_DB_String && Col >= 0)
      {
        std::string svalue;
        svalue = static_cast<CSMC_DBColProfileString*>(it->second)->getvalue();
        bool isWriteNullValue = static_cast<CSMC_DBColProfileString*>(it->second)->isWriteNullValue();

        if (Type == CommandUpdate && m_pResultSet && m_ActRow > 0 && !isWriteNullValue)
        {
          m_pResultSet->updateString(Col,svalue);
        }
        if (Type == CommandInsert && m_pPreparedStatement && !isWriteNullValue)
        {
          m_pPreparedStatement->setString(Col,svalue);
          m_PreparedValues += it->second->getSQLString();
        }
        Value << svalue;
      }
      else if ( it->second->getType() == CSMC_DBColProfile::SMC_DB_Long && Col >= 0)
      {
        int ivalue = 0;
        ivalue = (int)static_cast<CSMC_DBColProfileLong*>(it->second)->getvalue();
        bool isWriteNullValue = static_cast<CSMC_DBColProfileLong*>(it->second)->isWriteNullValue();

        if (Type == CommandUpdate && m_pResultSet && m_ActRow > 0 && !isWriteNullValue)
        {
          m_pResultSet->updateInt(Col,ivalue);
        }
        if (Type == CommandInsert && m_pPreparedStatement && !isWriteNullValue)
        {
          m_pPreparedStatement->setInt(Col,ivalue);
          m_PreparedValues += it->second->getSQLString();
        }
        Value << ivalue;
      }
      else if ( it->second->getType() == CSMC_DBColProfile::SMC_DB_Double && Col >= 0)
      {
        double dvalue = 0.0;
        dvalue = static_cast<CSMC_DBColProfileDouble*>(it->second)->getvalue();
        bool isWriteNullValue = static_cast<CSMC_DBColProfileDouble*>(it->second)->isWriteNullValue();

        if (Type == CommandUpdate && m_pResultSet && m_ActRow > 0 && !isWriteNullValue)
        {
          m_pResultSet->updateDouble(Col,dvalue);
        }
        if (Type == CommandInsert && m_pPreparedStatement && !isWriteNullValue)
        {
          m_pPreparedStatement->setDouble(Col,dvalue);
          m_PreparedValues += it->second->getSQLString();
        }
        Value << dvalue;
      }
      else if ( it->second->getType() == CSMC_DBColProfile::SMC_DB_Bool && Col >= 0)
      {
        bool bvalue = false;
        bvalue = static_cast<CSMC_DBColProfileBool*>(it->second)->getvalue();
        bool isWriteNullValue = static_cast<CSMC_DBColProfileBool*>(it->second)->isWriteNullValue();

        if (Type == CommandUpdate && m_pResultSet && m_ActRow > 0 && !isWriteNullValue)
        {
          m_pResultSet->updateBoolean(Col,bvalue);
        }
        if (Type == CommandInsert && m_pPreparedStatement && !isWriteNullValue)
        {
          m_pPreparedStatement->setBoolean(Col,bvalue);
          m_PreparedValues += it->second->getSQLString();
        }
        Value << bvalue;
      }
      else if ( it->second->getType() == CSMC_DBColProfile::SMC_DB_Date && Col >= 0)
      {
        DB_CLASSLIB_DATE * datevalue = 0;
        datevalue = static_cast<CSMC_DBColProfileDate*>(it->second)->getDateTime();
        bool isWriteNullValue = static_cast<CSMC_DBColProfileDate*>(it->second)->isWriteNullValue();

        if (Type == CommandUpdate && m_pResultSet && m_ActRow > 0 && !isWriteNullValue)
        {
          m_pResultSet->updateDate(Col,*datevalue);
        }
        if (Type == CommandInsert && m_pPreparedStatement && !isWriteNullValue)
        {
          m_pPreparedStatement->setDate(Col,*datevalue);
          m_PreparedValues += it->second->getSQLString();
        }
        Value << datevalue;
      }


      if (getTraceLevel() > 4)
      {
        std::stringstream Message;
        Message << "setRowData for Row:" << m_ActRow
                << " ColName:" << it->second->getColName()
                << " ColType:" << it->second->getType()
                << " Value:"   << Value.str();
        log(Message.str(),5);
      }

    } // if (it->second->m_isActive)
  } // for ( it = m_ColProfileList.begin(); it != m_ColProfileList.end(); ++it)

  return RetValue;
}

void CSMC_DBData::commit()
{
  CSMC_RuntimeController RuntimeController("CSMC_DBData::commit");

  try
  {
    if( getpCBSConnection() && m_TableExists )
    {
      getpCBSConnection()->commit();

      if (getTraceLevel() > 1)
      {
        std::string Message = "commit performed on ";
        Message += m_TableName;
        log(Message,1);
      }
    }
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::commit()");
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::commit()");
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::commit",m_TableName.c_str());
  }

  // free existing statements before continue, e.g. reading new data
  initStatements();

}

void CSMC_DBData::rollback()
{
  CSMC_RuntimeController RuntimeController("CSMC_DBData::rollBack");

  try
  {
    if( getpCBSConnection() && m_TableExists )
    {
      getpCBSConnection()->rollback();

      if (getTraceLevel() > 2)
      {
        std::string Message = "rollback performed on ";
        Message += m_TableName;
        log(Message,1);
      }
    }
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::rollback()");
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::rollback()");
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::rollback",m_TableName.c_str());
  }

  // free existing statements before continue, e.g. reading new data
  initStatements();

  clearDataList();

}

// adding free clause
// make shure that clause is syntactically correct
// no systax check will be done 
void  CSMC_DBData::addWhereClause(const std::string &value)
{
  if ( !value.empty() && CSMC_DBData::unspecString != value)
  {
    std::string WhereClause = value ;
    m_WhereClauseList.push_back(WhereClause);
  }
}

void  CSMC_DBData::addWhereClause(const std::string &ColName, std::vector<long> &ValueList, const std::string & LogicalOperator /* = "IN" */)
{
  if ( findColumn(ColName ) )
  {
    std::string WhereClause;
    std::vector<long>::iterator it = ValueList.begin();

    if ( it != ValueList.end() && !LogicalOperator.empty() )
    {
      WhereClause += " ( " + m_TableName + "." +  ColName + " " + LogicalOperator + " (";

      do
      {
        WhereClause += CDataConversion::LongToString(*it) ;

        it++;

        // add OR , AND .... if ValueList has still entries
        if (it != ValueList.end())
        {
          WhereClause += ","; 
        }

      }while(it != ValueList.end());

      WhereClause += " ) ) ";

      m_WhereClauseList.push_back(WhereClause);
    } // if ( it != ValueList.end() )
  }
  else
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadError(sMessage,ColName.c_str(),m_TableName.c_str(),"System cannot add where clause, Column unknown !");
  }
}

void  CSMC_DBData::addWhereClause(const std::string &ColName, std::vector<std::string> &ValueList, const std::string & LogicalOperator /* = "IN" */)
{
  if ( findColumn(ColName ) )
  {
    std::string WhereClause;
    std::vector<std::string>::iterator it = ValueList.begin();

    if ( it != ValueList.end() && !LogicalOperator.empty() )
    {
      WhereClause += " ( " + m_TableName + "." +  ColName + " " + LogicalOperator + " (";

      do
      {
        WhereClause += "'" + (*it) + "'" ;

        it++;

        // add OR , AND .... if ValueList has still entries
        if (it != ValueList.end())
        {
          WhereClause += ",";
        }

      }while(it != ValueList.end());

      WhereClause += " ) ) ";

      m_WhereClauseList.push_back(WhereClause);
    } // if ( it != ValueList.end() )
  }
  else
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadError(sMessage,ColName.c_str(),m_TableName.c_str(),"System cannot add where clause, Column unknown !");
  }
}


void  CSMC_DBData::addWhereClause(const std::string &ColName, const std::string &value, const std::string & Operator)
{
  if ( findColumn(ColName ) )
  {
    if ( CSMC_DBData::unspecString != value)
    {
      std::string WhereClause = m_TableName + "." +  ColName + " " + Operator + " '" + value + "'" ;
      m_WhereClauseList.push_back(WhereClause);
    }
  }
  else
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadError(sMessage,ColName.c_str(),m_TableName.c_str(),"System cannot add where clause, Column unknown !");
  }
}

void  CSMC_DBData::addWhereClauseforJoin(const std::string &ColName, const std::string &JoinTable, const std::string &JoinColName, const std::string & Operator)
{
  if ( findColumn(ColName ) )
  {
    if ( CSMC_DBData::unspecString != JoinColName)
    {
      std::string WhereClause = m_TableName + "." + ColName + " " + Operator + " ";
      
      if ( !JoinTable.empty() && JoinTable != CSMC_DBData::unspecString)
      {
        WhereClause += JoinTable + "." ;
      }
      
      WhereClause += JoinColName ;

      m_WhereClauseList.push_back(WhereClause);
    }
  }
  else
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadError(sMessage,ColName.c_str(),m_TableName.c_str(),"System cannot add where clause, Column unknown !");
  }
}

void  CSMC_DBData::addWhereClauseforNULL(const std::string& ColName, bool isNULL)
{
  if ( findColumn(ColName ) )
  {
    if ( isNULL )
    {
      std::string WhereClause = m_TableName + "." +  ColName + " is NULL" ;
      m_WhereClauseList.push_back(WhereClause);
    }
    else
    {
      std::string WhereClause = m_TableName + "." +  ColName + " is NOT NULL" ;
      m_WhereClauseList.push_back(WhereClause);
    }
  }
  else
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadError(sMessage,ColName.c_str(),m_TableName.c_str(),"System cannot add where clause, Column unknown !");
  }
}

void  CSMC_DBData::addWhereClause(const std::string &ColName, long value, const std::string & Operator)
{
  if ( findColumn(ColName ) )
  {
    if ( CSMC_DBData::unspecLong != value)
    {
      std::stringstream strValue;
      strValue << value ;
      std::string WhereClause = m_TableName + "." +  ColName + " " + Operator + " " + strValue.str();
      m_WhereClauseList.push_back(WhereClause);
    }
  }
  else
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadError(sMessage,ColName.c_str(),m_TableName.c_str(),"System cannot add where clause, Column unknown !");
  }
}

void CSMC_DBData::addWhereClause(const std::string& ColName, double value, const std::string & Operator)
{
  if ( findColumn(ColName ) )
  {
    if ( CSMC_DBData::unspecDouble != value)
    {
      std::stringstream strValue;
      strValue << value ;
      std::string WhereClause = m_TableName + "." +  ColName + " " + Operator + " " + strValue.str();
      m_WhereClauseList.push_back(WhereClause);
    }
  }
  else
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadError(sMessage,ColName.c_str(),m_TableName.c_str(),"System cannot add where clause, Column unknown !");
  }
}

// method uses simple DBString format from CDateTime
void CSMC_DBData::addWhereClause(const std::string& ColName, const CDateTime& value, const std::string & Operator)
{
  if ( findColumn(ColName ) )
  {
    if ( !(CSMC_DBData::unspecDate == value))
    {
      std::string WhereClause = m_TableName + "." +  ColName + " " + Operator + " '" + value.toDBString() +"'";
      m_WhereClauseList.push_back(WhereClause);
    }
  }
  else
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadError(sMessage,ColName.c_str(),m_TableName.c_str(),"System cannot add where clause, Column unknown !");
  }
}

void CSMC_DBData::addWhereClauseforDate(const std::string& ColName, const CDateTime& value, const std::string & Operator)
{
  CDateTime _value(value);
  if ( findColumn(ColName ) )
  {
    if ( !(CSMC_DBData::unspecDate == value))
    {
      std::string WhereClause= m_TableName + "." +  ColName + " " + Operator + " '" + _value.asString("%Y-%m-%d %H:%M:%S") +"'";
      m_WhereClauseList.push_back(WhereClause);
    }
  }
  else
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadError(sMessage,ColName.c_str(),m_TableName.c_str(),"System cannot add where clause, Column unknown !");
  }
}

void CSMC_DBData::addWhereClauseforTimestamp(const std::string& ColName, const CDateTime& value, const std::string & Operator)
{
  CDateTime _value(value);
  if ( findColumn(ColName ) )
  {
    if ( !(CSMC_DBData::unspecDate == value))
    {
      std::string WhereClause = m_TableName + "." +  ColName + " " + Operator + " '" + _value.asString("%Y-%m-%d %H:%M:%S.***") +"'";
      m_WhereClauseList.push_back(WhereClause);
    }
  }
  else
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadError(sMessage,ColName.c_str(),m_TableName.c_str(),"System cannot add where clause, Column unknown !");
  }
}

std::string CSMC_DBData::getWhereStatement()
{
  std::string WhereStatement;

  if ( !m_WhereClauseList.empty() )
  {
    WhereStatement = " WHERE (";
    std::vector<std::string>::iterator it;
    for ( it = m_WhereClauseList.begin(); it != m_WhereClauseList.end(); ++ it)
    {
      WhereStatement += (*it);

      if ( (*it) != m_WhereClauseList.back())
      {
        WhereStatement += " AND ";
      }
    }
    WhereStatement += ") ";
  }

  return WhereStatement; 
}

std::string CSMC_DBData::getCopyByInsertStatement(CSMC_DBData* pSourceTable)
{
  std::string CopyStatement;

  try
  {
    if ( pSourceTable )
    {
      // statement like 
      // "INSERT INTO Table ( Col1, Col2, Col3) ( select Col1, Col2, Col3  from SourceTable WHERE Col1 = 'bla' AND Col4 = 'xyz');
      // as used for copying data from PD_xxx to HD_xxx
      // or 
      // "INSERT INTO Table ( Col1, Col2, Col3) ( select 'bla', Col2, Col3  from SourceTable WHERE Col4 = 'xyz' );
      // as used for copying data from GT_xxx to HD_xxx
      // 
      // |-------- InsertStatement -----------| |-------------------- SelectStatement --------------------------|
      // |-------------------------------------- CopyStatement --------------------------------------------------|


      // using column list from SourceTable
      std::map<std::string, std::string> CopyColumnList;
      std::vector<std::string> ColumnList = pSourceTable->getColumnList();
      std::vector<std::string>::iterator it;

      // if column has been presetted by setXXX method
      // insert pair of columnname and value
      std::map<std::string,CSMC_DBColProfile*>::iterator itColProfile;
      for ( itColProfile = m_ColProfileList.begin(); itColProfile != m_ColProfileList.end(); ++itColProfile)
      {
        if ( itColProfile->second->isActive())
        {
          CopyColumnList.insert( std::pair<std::string,std::string>(itColProfile->second->getColName(),itColProfile->second->getSQLString()) );
        }
      }

      // now use all columns that are available at source table
      for (it = ColumnList.begin() ; it != ColumnList.end() ; ++it)
      {
        std::string Column = (*it);

        // check if column is also avialable in aim table 
        if ( findColumn(Column) )
        {
          // insert pair of columnname and columnname
          if ( CopyColumnList.find(Column) == CopyColumnList.end() )
          { 
            CopyColumnList.insert( std::pair<std::string,std::string>(Column,Column) );
          }
        }
        else
        {
          // do not send eventlog if source table is "GT-table" that contains PLANTNO column
          if ( pSourceTable->m_TableName.substr(0,2) == "GT" && Column == "PLANTNO" )
          {
            continue;
          }

          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_DBWriteError(sMessage,Column.c_str(),m_TableName.c_str(), (pSourceTable->m_TableName + ": Table structures not equal").c_str());
        }
      } // for (it = ColumnList.begin() ; it != ColumnList.end() ; ++it)

      // build CopyStatement
      std::string InsertStatement = "insert into " + m_TableName + "(";
      std::string SelectStatement = " ( select ";

      std::map<std::string,std::string>::iterator itCopy;
      for (itCopy = CopyColumnList.begin() ; itCopy != CopyColumnList.end() ; ++itCopy)
      {
        InsertStatement += itCopy->first + " ," ;    // may contain 'HEATID' 
        SelectStatement += itCopy->second + " ," ;   // may contain 'HEATID' or e.g. '4711' 
      }

      // cut off last ","
      InsertStatement = InsertStatement.substr(0,InsertStatement.find_last_of(','));
      SelectStatement = SelectStatement.substr(0,SelectStatement.find_last_of(','));

      InsertStatement += ")";
      SelectStatement += " from " + pSourceTable->getTableName() + " " + pSourceTable->getWhereStatement() + " )" ;

      CopyStatement = InsertStatement + SelectStatement + ";";
    }
    else
    {
      log("CSMC_DBData::getCopyByInsertStatement(...) : ERROR : pointer to source table not defined ", 1);
    }
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::getCopyByInsertStatement()");
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::getCopyByInsertStatement()");
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::getCopyByInsertStatement","");
  }

  return CopyStatement; 
}

std::string CSMC_DBData::getCopyByUpdateStatement(CSMC_DBData* pSourceTable)
{
  std::string CopyStatement;

  try
  {
    if ( pSourceTable )
    {
      // statement like 
      // "UPDATE Table set (Col1, Col2, Col3) = (select Col1, Col2, Col3 from SourceTable WHERE SourceTable.Col1 = 'bla') where Table.Col1 = 'bla' ;
      // |-------- UpdateStatement ---------|   |-------------------- SelectStatement ----------------------------------| |--- UpdateClause -------|
      // |----------------------------------------------------- CopyStatement ---------------------------------------------------------------------|


      // using column list from SourceTable
      std::map<std::string, std::string> CopyColumnList;
      std::vector<std::string> ColumnList = pSourceTable->getColumnList();
      std::vector<std::string>::iterator it;

      // if column has been presetted by setXXX method
      // insert pair of columnname and value
      std::map<std::string,CSMC_DBColProfile*>::iterator itColProfile;
      for ( itColProfile = m_ColProfileList.begin(); itColProfile != m_ColProfileList.end(); ++itColProfile)
      {
        if ( itColProfile->second->isActive())
        {
          CopyColumnList.insert( std::pair<std::string,std::string>(itColProfile->second->getColName(),itColProfile->second->getSQLString()) );
        }
      }

      // now use all columns that are available at source table
      for (it = ColumnList.begin() ; it != ColumnList.end() ; ++it)
      {
        std::string Column = (*it);

        // check if column is also avialable in aim table 
        if ( findColumn(Column) )
        {
          // insert pair of columnname and columnname
          if ( CopyColumnList.find(Column) == CopyColumnList.end() )
          { 
            CopyColumnList.insert( std::pair<std::string,std::string>(Column,Column) );
          }
        }
        else
        {
          // do not send eventlog if source table is "GT-table" that contains PLANTNO column
          if ( pSourceTable->m_TableName.substr(0,2) == "GT" && Column == "PLANTNO" )
          {
            continue;
          }

          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_DBWriteError(sMessage,Column.c_str(),m_TableName.c_str(), (pSourceTable->m_TableName + ": Table structures not equal").c_str());
        }
      } // for (it = ColumnList.begin() ; it != ColumnList.end() ; ++it)

      // build CopyStatement
      std::string UpdateStatement = "update " + m_TableName + " set (";
      std::string SelectStatement = " ( select ";

      std::map<std::string,std::string>::iterator itCopy;
      for (itCopy = CopyColumnList.begin() ; itCopy != CopyColumnList.end() ; ++itCopy)
      {
        UpdateStatement += itCopy->first + " ," ;    // may contain 'HEATID' 
        SelectStatement += itCopy->second + " ," ;   // may contain 'HEATID'
      }

      // cut off last ","
      UpdateStatement = UpdateStatement.substr(0,UpdateStatement.find_last_of(','));
      SelectStatement = SelectStatement.substr(0,SelectStatement.find_last_of(','));

      UpdateStatement += ")";
      SelectStatement += " from " + pSourceTable->getTableName() + " " + pSourceTable->getWhereStatement() + " )" ;

      CopyStatement = UpdateStatement + " = " + SelectStatement + getWhereStatement() + ";";
    }
    else
    {
      log("CSMC_DBData::getCopyByUpdateStatement(...) : ERROR : pointer to source table not defined ", 1);
    }
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::getCopyByUpdateStatement()");
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::getCopyByUpdateStatement()");
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::getCopyByUpdateStatement","");
  }

  return CopyStatement; 
}

void CSMC_DBData::cleanWhereStatement()
{
  m_WhereClauseList.clear();
}

void CSMC_DBData::log(const std::string& Message, long Level)
{
  if (getTraceLevel() >= Level)
  {
    cCBS_StdDB_Task::getInstance()->log(Message, Level);
  }
}

void CSMC_DBData::initStatements()
{
  CSMC_RuntimeController RuntimeController("CSMC_DBData::initStatements");
  
  try
  {
    if( getpCBSConnection() )
    {
      if (m_pSelectStatement)
      {
        getpCBSConnection()->freeStatement(m_pSelectStatement);
      }

      if (m_pStatement)
      {
        getpCBSConnection()->freeStatement(m_pStatement);
      }
    }  
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::initStatements()");
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::initStatements()");
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::initStatements",m_TableName.c_str());
  }

  m_pSelectStatement = 0;
  m_pStatement = 0;
  m_pResultSet = 0;

}

void CSMC_DBData::createStatement()
{
  CSMC_RuntimeController RuntimeController("CSMC_DBData::createStatement");
  try
  {
    initStatements();

    if( getpCBSConnection() )
    {
      m_pStatement = getpCBSConnection()->createPtStatement();
    }
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::createStatements()");
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::createStatements()");
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::createStatment",m_TableName.c_str());
  }
}

void CSMC_DBData::createSelectStatement()
{
  CSMC_RuntimeController RuntimeController("CSMC_DBData::createSelectStatement");

  try
  {
    initStatements();

    if( getpCBSConnection() )
    {
      m_pSelectStatement = getpCBSConnection()->createPtStatement();
    }
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::createSelectStatement()");
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::createSelectStatement()");
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::createSelectStatment",m_TableName.c_str());
  }
}

bool CSMC_DBData::isNull(const std::string& ColName, long Row)
{
  bool RetValue = true;

  try
  {
    if (m_pResultSet)
    {
      // using default (-1) for actual Row or set RowIndex
      if ( Row < 0 || setRow(Row) )
      {
        RetValue = m_pResultSet->isNull( getColIndex(ColName) );

        if (RetValue) // isNull returned true !!
        {
          if (getTraceLevel() > 3)
          {
            std::stringstream Message;
            Message << "Database returns NULL for " << m_TableName << "-" << ColName << "-" << Row ;
            log(Message.str(),4);
          }
        }
      }
    }
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::isNull()");
    RetValue = false;
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::isNull()");
    RetValue = false;
  }
  catch(...)
  {
    std::stringstream Message;
    Message << m_TableName << "-" << ColName << "-" << Row ;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::isNull",Message.str().c_str());
    RetValue = false;
  }

  return RetValue;
}

bool CSMC_DBData::createInsertStatement()
{
  bool RetValue = false;

  if ( !m_ColProfileList.empty() )
  {
    RetValue = true;
    long ColIndex = 0;
    std::string ValueList;
    std::string ColList;
    std::string InsertStatement;

    std::map<std::string,CSMC_DBColProfile*>::iterator it;
    for ( it = m_ColProfileList.begin(); it != m_ColProfileList.end(); ++it)
    {
      if ( it->second->isActive())
      {
        // insert <,> before each entry except the first one
        if ( ColIndex > 0 ) 
        {
          ColList += ",";
          ValueList += ",";
        }
        // set ColIndex to active entry
        it->second->setCol(ColIndex);

        // add respective values to ColList and ValueList for INSERT statement
        ColList += it->second->getColName();
        ValueList += it->second->getSQLString();

        ++ColIndex; // increase ColIndex counter in case of active entry only

      }
    }

    InsertStatement = "insert into " + m_TableName;
    InsertStatement += " (" + ColList + ") ";
    InsertStatement += " values ";
    InsertStatement += " (" + ValueList + ") ";
    InsertStatement += ";" ;

    m_Statement = InsertStatement;

    initStatements();

    createStatement();
  }
  else
  {
    log("Error at CSMC_DBData::createInsertStatement() - Size of m_ColProfileList is <= 0 !", 2);
    setLastError("NO_COLUMNS_TO_BE_INSERTED", 0, m_TableName);
  }

  return RetValue;
}

bool CSMC_DBData::createUpdateStatement()
{
  bool RetValue = false;

  if ( !m_ColProfileList.empty() )
  {
    long ColIndex = 0;
    std::string ValueList;
    std::string ColList;
    std::string UpdateStatement;
    std::map<std::string,CSMC_DBColProfile*>::iterator it;

    UpdateStatement = "update " + m_TableName;
    UpdateStatement += " set " ;  // Uli: was " set ("

    for ( it = m_ColProfileList.begin(); it != m_ColProfileList.end(); ++it)
    {
      if ( it->second->isActive())
      {
        // returning true only if active field has been detected
        // otherwise statment looks like 
        // update Table set where Field = value;
        //                 * <- sql error here
        RetValue = true;

        // insert <,> before each entry except the first one
        if ( ColIndex > 0 ) 
        {
          UpdateStatement += ",";
        }

        UpdateStatement += it->second->getColName();
        UpdateStatement += "=";
        UpdateStatement += it->second->getSQLString();

        ++ColIndex; // increase ColIndex counter in case of active entry only

      }
    }

    UpdateStatement += " "; // Uli: this was ") ";

    UpdateStatement += getWhereStatement();
    UpdateStatement += ";" ;

    m_Statement = UpdateStatement;
    createStatement();

  }
  else
  {
    log("Error at CSMC_DBData::createUpdateStatement() - Size of m_ColProfileList is <= 0 !", 2);
    setLastError("NO_COLUMNS_TO_BE_UPDATED", 0, m_TableName);
  }

  return RetValue;
}

//part of error handling, make sure there are no recursive calls
//this function will set the statements and the result set to zero
bool CSMC_DBData::handleConnectionError()
{
  bool RetValue = false;

  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_DatabaseConnectionError(sMessage,"","CSMC_DBData::handleConnectionError()");

  try
  {
    // the standard connection will check if a CBS connection is established
    // depending on that it will create a new CBS connection or invoke its
    // reconnect method
    RetValue = m_pCBS_StdConnection->reconnect();


    // do not call init statements due to possible recursive method call !
    if (m_pSelectStatement)
    {
      if ( getpCBSConnection() )
      {
        getpCBSConnection()->freeStatement(m_pSelectStatement);
      }
    }

    if (m_pPreparedStatement)
    {
      if ( getpCBSConnection() )
      {
        getpCBSConnection()->freeStatement(m_pPreparedStatement);
      }
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();  
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",std::string("CSMC_DBData::handleConnectionError for " + m_TableName).c_str(),"free connections");

    RetValue = false;
  }

  //ensure that the pointers are set to zero even when we caught something
  m_pSelectStatement = 0;
  m_pResultSet = 0;
  m_pPreparedStatement = 0;

  return RetValue;
}

void CSMC_DBData::doOnCBS_DBExc(cCBS_DBExc& ex, const std::string& Action)
{
  long NumOfErr = ex.m_SQLErrors.size(); // number of ORA Errors

  //set data base errors  
  if ( !ex.m_SQLErrors.empty() )
  {
    m_lastError = *ex.m_SQLErrors.front();
  }
  else
  {
    setLastError("UNKNOWN_ERROR", 0, m_ActStatement); 
  }
  
  // Exception with NumOfErr = 0 means i.e. No Rows satisfy the Where Clause by Update
  if ( NumOfErr > 0 ) // handle only real errors
  {
    std::string msg = ex.getText();
    size_t pos = 0;
    while((pos = msg.find('\n')) != std::string::npos) 
    {
      msg.replace(pos,1,"");
    }

    msg += " ErrorCode ";
    msg += ex.m_errorcode;

    //another workaround CBS-deficite not giving oracle error code 3114 on db-connection error, which prevented further reconnection-attempts.
    // error code 3114 is not returned in ex.m_errorcode, but only as part of ex.getText()
    if ( ex.getText().find("ORA-03114") != std::string::npos ||  // not connected
         ex.getText().find("ORA-01012") != std::string::npos ||  // not logged on
         ex.getText().find("ORA-00028") != std::string::npos )   // session killed
    {
      doOnCBS_DBExc_ConnectionError(ex, Action);
    }
    else
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,msg.c_str(),Action.c_str(), m_ActStatement.c_str());
    }
  }
}


bool CSMC_DBData::getMetaData(const std::string& TableName)
{

  bool RetValue = false;

  try
  {
    // *************************************************************************************
    // clean up m_ColProfileList to erase existing entries in case of re-calling getMetaData
    // *************************************************************************************
    std::map<std::string,CSMC_DBColProfile*>::iterator it;

    for ( it = m_ColProfileList.begin(); it != m_ColProfileList.end(); ++it)
    {
      if ( it->second )
      {
        delete it->second;
      }
    }

    m_ColProfileList.erase(m_ColProfileList.begin(),m_ColProfileList.end());

    // *********************
    // fill m_ColProfileList
    // *********************
    long i = 0;

    cleanWhereStatement();

    m_Statement = "SELECT * FROM ";
    m_Statement += TableName;
    m_Statement += " WHERE ROWNUM <= 1;";

    if( getpCBSConnection() )
    {
      createSelectStatement();

      if(m_pSelectStatement)
      {
        // for exception handling
        m_ActStatement = m_Statement;

        CSMC_DBMetaData * pMetaDataResultSet = 0 ;
        pMetaDataResultSet = static_cast<CSMC_DBMetaData *>(m_pSelectStatement->executePtQuery(m_Statement)); 

        std::vector<cCBS_ODBCColDescr> ColDescriList;
        std::vector<cCBS_ODBCColDescr>::iterator it;

        ColDescriList = pMetaDataResultSet->getColumnDescrList();

        for ( it = ColDescriList.begin(),i = 0; it != ColDescriList.end() ; ++it, ++ i ) 
        {
          std::string ColName = ColDescriList.at(i).sName;

          long ColType    = ColDescriList.at(i).iSqlCType;
          long ColSize    = ColDescriList.at(i).iSqlSize;
          long ColScale   = ColDescriList.at(i).iScale;

          // use only interger part to nesseccary truncatation of values
          // scale = 0 for SQL_C_CHAR columns
          ColSize = max(ColSize - ColScale,-1);

          // ColType return SQL_C_DOUBLE in case of definition NUMBER(5)
          if ( ColType == SQL_C_LONG || 
             ( ColType == SQL_C_DOUBLE && ColScale == 0 ) )
          {
            CSMC_DBColProfileLong *pColProfile = new CSMC_DBColProfileLong(TableName,ColName,ColSize);
            m_ColProfileList.insert( std::pair <std::string,CSMC_DBColProfile*>(ColName,pColProfile));
          }
          else if (ColType == SQL_C_CHAR)
          {
            CSMC_DBColProfileString *pColProfile = new CSMC_DBColProfileString(TableName,ColName,ColSize);
            m_ColProfileList.insert( std::pair <std::string,CSMC_DBColProfile*>(ColName,pColProfile));
          }
          else if (ColType == SQL_C_DOUBLE)
          {
            CSMC_DBColProfileDouble *pColProfile = new CSMC_DBColProfileDouble(TableName,ColName,ColSize);
            m_ColProfileList.insert( std::pair <std::string,CSMC_DBColProfile*>(ColName,pColProfile));
          }
        }

        RetValue = true;

      } // if(m_pSelectStatement)
    } // if(getpCBSConnection())

    m_Statement.erase();
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::getMetaData()");
    RetValue = false;
  }
  catch(cCBS_DBExc_TableNotExists &te) 
  {
    m_TableExists = false;

    doOnCBS_DBExc(te,"CSMC_DBData::getMetaData()");
    RetValue = false;
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::getMetaData()");
    RetValue = false;
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::getMetaData",m_TableName.c_str());
    RetValue = false;
  }

  // free existing statements before continue, e.g. reading new data
  initStatements();

  return RetValue;
}

std::string CSMC_DBData::getTableName()
{
  return m_TableName;
}


bool CSMC_DBData::execute_select()
{
  bool RetValue = false;

  checkMetaData();

  // execute selection in case a ResultSet was successfully created
  if(readData())
  {
    // set row counter
    findLastRow();
    // set row position
    RetValue = first();
  }

  return RetValue;
}

bool CSMC_DBData::execute_insert()
{
  bool RetValue = false;

  checkMetaData();

  createInsertStatement();

  if (m_pStatement)
  {
    m_ActStatement = m_Statement;

    log(m_ActStatement,2);

    cCBS_StdDB_Task::getInstance()->setStateDetails("CSMC_DBData::execute_insert()", m_ActStatement, 4);

    m_pStatement->execute(m_Statement);

    RetValue = true;
  }

  return RetValue;
}

bool CSMC_DBData::execute_deleteRows()
{
  bool RetValue = false;

  checkMetaData();

  if ( CDataConversion::Trim(getWhereStatement()).empty() )
  {
    if (getTraceLevel() > 0)
    {
      log(m_TableName + "(" + m_Statement + ") Unable to DELETE rows, WHERE clause not defined!", 2);
    }
  }
  else
  {
    // Don' t use m_pStatement because createStatement() destroys existing statements and result
    // sets. This will not work if iterating over a result set and try to delete some rows.
    cCBS_Statement* pStatement = getpCBSConnection()->createPtStatement();

    std::string Statement = "Delete from " + m_TableName + getWhereStatement() + ";";

    if (pStatement)
    {
      try
      {
        // for exception handling
        m_ActStatement = Statement;

        log(m_ActStatement,1);

        cCBS_StdDB_Task::getInstance()->setStateDetails("CSMC_DBData::execute_deleteRows()", m_ActStatement, 4);

        // Deletion on wrong columns leads to an exception.
        // Free the statement to avoid open cursors.
        pStatement->execute(Statement);

        getpCBSConnection()->freeStatement(pStatement);
        pStatement = 0;

        RetValue = true;
      }
      catch(cCBS_DBExc_NoRowAffected& e)
      {
        RetValue = true;
        log("No rows deleted, where clause returned empty set." + e.getExcCode(),4);
        if (pStatement)
        {
          getpCBSConnection()->freeStatement(pStatement);
          pStatement = 0;
        } 
      }
      catch(cCBS_DBExc &e) 
      {
        // Exception with ex.m_SQLErrors.empty() means 
        // no Rows selected by Where Clause -> this is not a real excpetion
        if ( e.m_SQLErrors.empty() )
        {
          if (pStatement)
          {
            getpCBSConnection()->freeStatement(pStatement);
            pStatement = 0;
          }  

          RetValue = true; //the state of the DB is as expected the rows do not exist
        }//if ( e.m_SQLErrors.empty() )
        else
        {
          if (pStatement)
          {
            getpCBSConnection()->freeStatement(pStatement);
            pStatement = 0;
          }  

          throw e;
        }
      }
    }
  }

  return RetValue;

}

bool CSMC_DBData::execute_update()
{
  bool RetValue = false;

  checkMetaData();

  if ( CDataConversion::Trim(getWhereStatement()).empty() )
  {
    if (getTraceLevel() > 0)
    {
      log(m_TableName + "(" + m_Statement + ") Unable to UPDATE row, WHERE clause not defined!", 2);
    }
  }
  else
  {
    if (createUpdateStatement()) // WHERE clause will be added within createUpdateStatement()
    {
      if (m_pStatement)
      {
        try
        {
          // for exception handling
          m_ActStatement = m_Statement;

          log(m_ActStatement,2);

          cCBS_StdDB_Task::getInstance()->setStateDetails("CSMC_DBData::execute_update()", m_ActStatement, 4);

          m_pStatement->execute(m_Statement);

          RetValue = true;
        }
        catch(cCBS_DBExc_NoRowAffected& e)
        {
          RetValue = true;
          log("No rows updated, where clause returned empty set." + e.getExcCode(),4);
          //setLastError("NO_DATA_FOUND", 1403, m_ActStatement);
        }
        catch(cCBS_DBExc &e) 
        {
          // Exception with ex.m_SQLErrors.empty() means 
          // no Rows selected by Where Clause -> this is not a real excpetion
          if ( e.m_SQLErrors.empty() )
          {
            RetValue = true;
            log("No rows updated, where clause returned empty set.",4);
            //setLastError("NO_DATA_FOUND", 1403, m_ActStatement);
          }
          else
          {
            if (m_pStatement)
            {
              getpCBSConnection()->freeStatement(m_pStatement);
              m_pStatement = 0;
            }  

            throw e;
          }
        }
      }
    }
  }

  return RetValue;
}

bool CSMC_DBData::execute_update_fail_on_no_row()
{
  bool RetValue = false;

  checkMetaData();

  if ( CDataConversion::Trim(getWhereStatement()).empty() )
  {
    if (getTraceLevel() > 0)
    {
      log(m_TableName + "(" + m_Statement + ") Unable to UPDATE row, WHERE clause not defined!", 2);
    }
  }
  else
  {
    if (createUpdateStatement()) // WHERE clause will be added within createUpdateStatement()
    {
      if (m_pStatement)
      {
        try
        {
          // for exception handling
          m_ActStatement = m_Statement;

          log(m_ActStatement,1);

          cCBS_StdDB_Task::getInstance()->setStateDetails("CSMC_DBData::execute_update_fail_on_no_row()", m_ActStatement, 1);

          m_pStatement->execute(m_Statement);

          RetValue = true;
        }
        catch(cCBS_DBExc_NoRowAffected& e)
        {
          RetValue = false;
          log("No rows updated, where clause returned empty set." + e.getExcCode(),4);
          setLastError("NO_DATA_FOUND", 1403, m_ActStatement);
        }
        catch(cCBS_DBExc &e) 
        {
          // Exception with ex.m_SQLErrors.empty() means 
          // no Rows selected by Where Clause -> this is not a real excpetion
          if ( e.m_SQLErrors.empty() )
          {
            RetValue = false;
            log("No rows updated, where clause returned empty set.",4);
            setLastError("NO_DATA_FOUND", 1403, m_ActStatement);
          }
          else
          {
            if (m_pStatement)
            {
              getpCBSConnection()->freeStatement(m_pStatement);
              m_pStatement = 0;
            }  

            throw e;
          }
        }
      }
    }
  }

  return RetValue;
}


void CSMC_DBData::doOnCBS_DBExc_ConnectionError(cCBS_DBExc_ConnectionError& ex, const std::string& Action)
{
  cCBS_DBExc CBS_DBExc(ex);

  doOnCBS_DBExc_ConnectionError(CBS_DBExc, Action);
}

void CSMC_DBData::doOnCBS_DBExc_ConnectionError(cCBS_DBExc& ex, const std::string& Action)
{
  long NumOfErr = ex.m_SQLErrors.size(); // number of ORA Errors

  //set data base errors  
  if ( !ex.m_SQLErrors.empty() )
  {
    m_lastError = *ex.m_SQLErrors.front();
  }
  else
  {
    setLastError("UNKNOWN_ERROR", 0, m_ActStatement); 
  }

  // Exception with NumOfErr = 0 means i.e. No Rows satisfy the Where Clause by Update
  if ( NumOfErr > 0 ) // handle only real errors
  {
    std::string msg = ex.getText();
    size_t pos = 0;
    while((pos = msg.find('\n')) != std::string::npos) 
    {
      msg.replace(pos,1,"");
    }

    msg += " ErrorCode ";
    msg += ex.m_errorcode;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, msg.c_str(), Action.c_str(), m_ActStatement.c_str());
  }

  handleConnectionError();

}


// closing actual statements
void CSMC_DBData::close()
{
  initStatements();
}

bool CSMC_DBData::isActive(const std::string &ColName)
{
  bool RetValue = false;

  // try to find existing entry or insert entry
  std::map<std::string,CSMC_DBColProfile*>::iterator it = m_ColProfileList.find(ColName);
  if ( it != m_ColProfileList.end())
  {
    if ( it->second->isActive())
    {
      RetValue = true;
    }
  }

  return RetValue;

}

long CSMC_DBData::getTraceLevel()
{
  return cCBS_StdDB_Task::getInstance()->getTraceLevel();
}

cCBS_Connection* CSMC_DBData::getpCBSConnection()
{
  cCBS_Connection* pCBS_Connection = 0;

  if ( m_pCBS_StdConnection )
  {
    pCBS_Connection = m_pCBS_StdConnection->getpCBSConnection();

    if ( !pCBS_Connection )
    {
      m_pCBS_StdConnection->reconnect();

      pCBS_Connection = m_pCBS_StdConnection->getpCBSConnection();
    }
  }

  return pCBS_Connection;
}

bool CSMC_DBData::copyByInsert(CSMC_DBData* pSourceTable)
{
  CSMC_RuntimeController RuntimeController("CSMC_DBData::copyByInsert(CSMC_DBData* pSourceTable)");

  // instantiating task controller
  // will work in RELEASED version only !
  // terminates task AND component, if execution of event will take longer than
  // configured time from [ProcessControl] ControlTime = ...
  cCBS_StdFrame_TaskController TaskController( cCBS_StdDB_Task::getInstance() );

  bool RetValue = false;

  try
  {
    if ( getpCBSConnection() )
    {
      // try to copy data
      RetValue = execute_copyByInsert(pSourceTable);
    }
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    // try to reconnect once
    if ( handleConnectionError() )
    {
      try
      {
        // try to copy data
        RetValue = execute_copyByInsert(pSourceTable);
      }
      catch(cCBS_DBExc_ConnectionError &ce) 
      {
        doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::copyByInsert(..)");
        RetValue = false;
      }
      catch(cCBS_DBExc &e) 
      {
        doOnCBS_DBExc(e,"CSMC_DBData::copyByInsert()");
        RetValue = false;
      }
      catch(...)
      {
        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::copyByInsert",m_TableName.c_str());
        RetValue = false;
      }
    }
    else
    {
      doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::copyByInsert(CSMC_DBData* pSourceTable)");
      RetValue = false;
    }
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::copyByInsert(CSMC_DBData* pSourceTable)");
    RetValue = false;
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::copyByInsert(CSMC_DBData* pSourceTable)",m_TableName.c_str());
    RetValue = false;
  }

  return RetValue;
}

bool CSMC_DBData::copyByUpdate(CSMC_DBData* pSourceTable)
{
  CSMC_RuntimeController RuntimeController("CSMC_DBData::copyByUpdate(CSMC_DBData* pSourceTable)");

  // instantiating task controller
  // will work in RELEASED version only !
  // terminates task AND component, if execution of event will take longer than
  // configured time from [ProcessControl] ControlTime = ...
  cCBS_StdFrame_TaskController TaskController( cCBS_StdDB_Task::getInstance() );

  bool RetValue = false;

  try
  {
    if ( getpCBSConnection() )
    {
      // try to copy data
      RetValue = execute_copyByUpdate(pSourceTable);
    }
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    // try to reconnect once
    if ( handleConnectionError() )
    {
      try
      {
        // try to copy data
        RetValue = execute_copyByUpdate(pSourceTable);
      }
      catch(cCBS_DBExc_ConnectionError &ce) 
      {
        doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::copyByUpdate(..)");
        RetValue = false;
      }
      catch(cCBS_DBExc &e) 
      {
        doOnCBS_DBExc(e,"CSMC_DBData::copyByUpdate()");
        RetValue = false;
      }
      catch(...)
      {
        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::copyByUpdate",m_TableName.c_str());
        RetValue = false;
      }

    }
    else
    {
      doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::copyByUpdate(CSMC_DBData* pSourceTable)");
      RetValue = false;
    }
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::copyByUpdate(CSMC_DBData* pSourceTable)");
    RetValue = false;
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::copyByUpdate(CSMC_DBData* pSourceTable)",m_TableName.c_str());
    RetValue = false;
  }

  return RetValue;
}


bool CSMC_DBData::execute_copyByInsert(CSMC_DBData* pSourceTable)
{
  bool result = true;

  checkMetaData();

  try
  {
    m_Statement = getCopyByInsertStatement(pSourceTable);

    // for exception handling output
    m_ActStatement = m_Statement;

    initStatements();

    m_pStatement = getpCBSConnection()->createPtStatement();

    if (m_pStatement)
    {
      log(m_ActStatement,2);

      cCBS_StdDB_Task::getInstance()->setStateDetails("CSMC_DBData::execute_copyByInsert()", m_ActStatement, 4);

      m_pStatement->execute(m_Statement);    
      
      getpCBSConnection()->freeStatement(m_pStatement);
      m_pStatement = 0;
    }		
  }
  catch(cCBS_DBExc &e) 
  {
    if (m_pStatement)
    {
      getpCBSConnection()->freeStatement(m_pStatement);
      m_pStatement = 0;
    }  

    throw e;
  }

  return result;
}

bool CSMC_DBData::execute_copyByUpdate(CSMC_DBData* pSourceTable)
{
  bool result = true;

  checkMetaData();

  try
  {
    m_Statement = getCopyByUpdateStatement(pSourceTable);

    // for exception handling output
    m_ActStatement = m_Statement;

    initStatements();

    m_pStatement = getpCBSConnection()->createPtStatement();

    if (m_pStatement)
    {
      log(m_ActStatement,2);

      cCBS_StdDB_Task::getInstance()->setStateDetails("CSMC_DBData::execute_copyByUpdate()", m_ActStatement, 4);

      m_pStatement->execute(m_Statement);    

      getpCBSConnection()->freeStatement(m_pStatement);
      m_pStatement = 0;
    }		
  }
  catch(cCBS_DBExc_NoRowAffected& e)
  {
    result = true;
    log("No rows updated, where clause returned empty set." + e.getExcCode(),4);
    if (m_pStatement)
    {
      getpCBSConnection()->freeStatement(m_pStatement);
      m_pStatement = 0;
    } 
  }
  catch(cCBS_DBExc &e) 
  {
    if (m_pStatement)
    {
      getpCBSConnection()->freeStatement(m_pStatement);
      m_pStatement = 0;
    }  

    throw e;
  }

  return result;
}


// move to "insert row" and insert new dataset into used ResultSet
// data must be selected before and new PKs must be presetted by calling "set" methods
bool CSMC_DBData::copy()
{
  CSMC_RuntimeController RuntimeController("CSMC_DBData::copy");

  // instantiating task controller
  // will work in RELEASED version only !
  // terminates task AND component, if execution of event will take longer than
  // configured time from [ProcessControl] ControlTime = ...
  cCBS_StdFrame_TaskController TaskController( cCBS_StdDB_Task::getInstance() );

  bool RetValue = false;

  try
  {
    if ( getpCBSConnection() )
    {
      // try to copy data
      RetValue = execute_copy();
    }
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    // try to reconnect once
    if ( handleConnectionError() )
    {
      try
      {
        // try to copy data
        RetValue = execute_copy();
      }
      catch(cCBS_DBExc_ConnectionError &ce) 
      {
        doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::copy(..)");
        RetValue = false;
      }
      catch(cCBS_DBExc &e) 
      {
        doOnCBS_DBExc(e,"CSMC_DBData::copy()");
        RetValue = false;
      }
      catch(...)
      {
        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::copy",m_TableName.c_str());
        RetValue = false;
      }
    }
    else
    {
      doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::copy()");
      RetValue = false;
    }
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::copy()");
    RetValue = false;
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::copy",m_TableName.c_str());
    RetValue = false;
  }

  clearDataList();

  return RetValue;
}

bool CSMC_DBData::execute_copy()
{
  bool RetValue = false;

  checkMetaData();

  try
  {
    if ( m_pResultSet && first() ) 
    {
      if ( !m_ColProfileList.empty() )
      {
        m_pResultSet->moveToInsertRow();

        if ( setRowData(CommandUpdate) )
        {
          cCBS_StdDB_Task::getInstance()->setStateDetails("CSMC_DBData::execute_copy()", m_ActStatement, 4);

          m_pResultSet->insertRow();

          RetValue = true;
        }
      }
      else
      {
        log("CSMC_DBData::execute_copy() - no data presetted by calling set methods",2);
      }
    }
    else
    {
      log("CSMC_DBData::execute_copy() - no data selected ",2);
    }
  }
  catch(cCBS_DBExc &e) 
  {
    throw e;
  }

  return RetValue;
}

bool CSMC_DBData::updateOrInsert()
{
  CSMC_RuntimeController RuntimeController("CSMC_DBData::updateOrInsert");

  // instantiating task controller
  // will work in RELEASED version only !
  // terminates task AND component, if execution of event will take longer than
  // configured time from [ProcessControl] ControlTime = ...
  cCBS_StdFrame_TaskController TaskController( cCBS_StdDB_Task::getInstance() );

  bool RetValue = false;

  try
  {
    if ( getpCBSConnection() && m_TableExists )
    {
      // try to update data
      if ( !execute_update_fail_on_no_row() )
      {
        RetValue = execute_insert();
      }
      else
        RetValue = true;
    }
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    // try to reconnect once
    if ( handleConnectionError() )
    {
      try
      {
        if ( !execute_update() )
        {
          RetValue = execute_insert();
        }
        else
          RetValue = true;
      }
      catch(cCBS_DBExc_ConnectionError &ce) 
      {
        doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::updateOrInsert(..)");
        RetValue = false;
      }
      catch(cCBS_DBExc &e) 
      {
        doOnCBS_DBExc(e,"CSMC_DBData::updateOrInsert()");
        RetValue = false;
      }
      catch(...)
      {
        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::updateOrInsert",m_TableName.c_str());
        RetValue = false;
      }
    }
    else
    {
      doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::updateOrInsert()");
      RetValue = false;
    }
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::updateOrInsert()");
    RetValue = false;
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::updateOrInsert",m_TableName.c_str());
    RetValue = false;
  }

  clearDataList();

  return RetValue;
}


void CSMC_DBData::createPreparedStatement(const std::string& Statement)
{
  CSMC_RuntimeController RuntimeController("CSMC_DBData::createPreparedStatement");

  try
  {
    if( getpCBSConnection() )
    {
      if (m_pPreparedStatement)
      {
        getpCBSConnection()->freeStatement(m_pPreparedStatement);
        m_pPreparedStatement = 0;
      }

      m_pPreparedStatement = getpCBSConnection()->preparePtStatement(Statement);
    }
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::createPreparedStatement()");
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::createPreparedStatement()");
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::createPreparedStatement",m_TableName.c_str());
  }
}

// This function must be called BEFORE writing the data in a loop (model results)
// by using function insertPrepared()
void CSMC_DBData::setPreparedStatement()
{
  if ( !m_ColProfileList.empty() )
  {
    long ColIndex = 0;
    std::string ValueList;
    std::string ColList;
    std::string PrepInsertStat;
    std::map<std::string,CSMC_DBColProfile*>::iterator it;

    for ( it = m_ColProfileList.begin(); it != m_ColProfileList.end(); ++it)
    {
      if ( it->second->isActive())
      {
        // insert <,> before each entry except the first one
        if ( ColIndex > 0 ) 
        {
          ColList += ",";
          ValueList += ",";
        }
        // set ColIndex to active entry
        it->second->setCol(ColIndex);

        // add respective values to ColList and ValueList for INSERT statement
        ColList += it->second->getColName();
        ValueList += "?";

        ++ColIndex; // increase ColIndex counter in case of active entry only
      }
    }

    PrepInsertStat = "insert into " + m_TableName;
    PrepInsertStat += " (" + ColList + ") ";
    PrepInsertStat += " values ";
    PrepInsertStat += " (" + ValueList + ") ";

    /** JOGE is not tested yet

    // init m_pPreparedStatement
    // if statement is not initialized or previous statement 
    // is different to actual
    if (!m_pPreparedStatement ||
         m_PreparedStatement != PrepInsertStat)
    {
      if ( getTraceLevel() > 3 )
      {
        if ( m_pPreparedStatement )//old cursor but new statement
        {
          log("Prepared Statement before is different to actual. Renew prepared statement.",4);
          log("Statement before: " + m_PreparedStatement, 4);
          log("Statement actual: " + PrepInsertStat, 4);
        }
      }
      createPreparedStatement(PrepInsertStat);
      m_PreparedStatement = PrepInsertStat;
    }
    **/

    createPreparedStatement(PrepInsertStat);
    m_PreparedStatement = PrepInsertStat;
  }
  else
  {
    log("Error at CSMC_DBData::setPreparedStatement() - size of ColProfileList <= 0 !", 2);
  }
}

// This function has to be used when data are written in a loop (model results).
// Call setPreparedStatement() before.
bool CSMC_DBData::insertPrepared()
{
  CSMC_RuntimeController RuntimeController("CSMC_DBData::insertPrepared");

  // instantiating task controller
  // will work in RELEASED version only !
  // terminates task AND component, if execution of event will take longer than
  // configured time from [ProcessControl] ControlTime = ...
  cCBS_StdFrame_TaskController TaskController( cCBS_StdDB_Task::getInstance() );

  bool RetValue = false;

  try
  {
    if ( getpCBSConnection() && m_TableExists )
    {
      // try to insert data
      RetValue = execute_prepared_insert();
    }
  }
  catch(cCBS_DBExc_ConnectionError &ce) 
  {
    // try to reconnect once
    if ( handleConnectionError() )
    {
      try
      {
        // try to insert data
        RetValue = execute_prepared_insert();
      }
      catch(cCBS_DBExc_ConnectionError &ce) 
      {
        doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::insertPrepared(..)");
        RetValue = false;
      }
      catch(cCBS_DBExc &e) 
      {
        doOnCBS_DBExc(e,"CSMC_DBData::insertPrepared()");
        RetValue = false;
      }
      catch(...)
      {
        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::insertPrepared",m_TableName.c_str());
        RetValue = false;
      }
    }
    else
    {
      doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::insertPrepared()");
      RetValue = false;
    }
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e,"CSMC_DBData::insertPrepared()");
    RetValue = false;
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_DBData::insertPrepared",m_TableName.c_str());
    RetValue = false;
  }

  clearDataList();

  return RetValue;
}

bool CSMC_DBData::execute_prepared_insert()
{
  bool RetValue = false;

  checkMetaData();

  if (m_pPreparedStatement)
  {
    if (m_PreparedStatement.empty())
    {
      if (getTraceLevel() > 0)
      {
        log(m_TableName + " Unable to insert. Prepared statement not defined!", 2);
      }
    }
    else
    {
      if (setRowData(CommandInsert/*I*/))
      {
        m_ActStatement = m_PreparedStatement + m_PreparedValues;
        // for exception handling output
        log(m_ActStatement,3);

        cCBS_StdDB_Task::getInstance()->setStateDetails("CSMC_DBData::execute_prepared_insert()", m_ActStatement,4);

        m_pPreparedStatement->executeUpdate();

        RetValue = true;
      }
    }
  }

  return RetValue;
}

void CSMC_DBData::doOnConstruct()
{
  // to be implemented at derived classes
}
void CSMC_DBData::doOnDestruct()
{
  // to be implemented at derived classes
}

//Execute std::string as SQL and catch SQL Errors in case of occuriance
bool CSMC_DBData::executeSQL(const std::string &pSQL)
{
  bool result = true;
  try
  {
    checkMetaData();

    std::string::size_type indexCh = pSQL.find_last_of(";");
    m_Statement = indexCh !=  std::string::npos ? pSQL : pSQL + ";";
    initStatements();

    if( getpCBSConnection() )
    {
      m_pStatement = getpCBSConnection()->createPtStatement();

      if (m_pStatement)
      {
        m_ActStatement = m_Statement; // for exception handling

        log(m_ActStatement,3);

        cCBS_StdDB_Task::getInstance()->setStateDetails("CSMC_DBData::executeSQL()", m_ActStatement, 4);

        m_pStatement->execute(m_Statement);    

        getpCBSConnection()->freeStatement(m_pStatement);
        m_pStatement = 0;
      }
    }
  }
  catch(cCBS_DBExc_NoRowAffected& e)
  {
    result = true;

    if (getpCBSConnection() && m_pStatement)
    {
      getpCBSConnection()->freeStatement(m_pStatement);
      m_pStatement = 0;
    }
    log("No rows updated/deleted because where clause returned empty set." + e.getExcCode(),4);
  }
  catch(cCBS_DBExc &e) 
  {
    doOnCBS_DBExc(e, "CSMC_DBData::executeSQ");

    result = false;

    if (getpCBSConnection() && m_pStatement)
    {
      getpCBSConnection()->freeStatement(m_pStatement);
      m_pStatement = 0;
    }  
  }

  return result;
}

//Return Last SQL Error structure
cCBS_ODBC_DBError CSMC_DBData::getLastError()
{
  return m_lastError; 
}

//set Last Error
void CSMC_DBData::setLastError(const std::string &pMsgText, int pErrCode, const std::string &pSQLState)
{
  log("++++++ CSMC_DBData::setLastError",3);
  log("Error: " + pMsgText + ", ErrorCode: " + CDataConversion::LongToString(pErrCode) + ", SQL: " + pSQLState,5);

  m_lastError.m_MessageText = pMsgText;
  m_lastError.m_NativeErrorCode = pErrCode;
  m_lastError.m_SQLState = pSQLState;
}

//reset Last Error structure
void CSMC_DBData::resetLastError()
{
  m_lastError.m_MessageText = "";
  m_lastError.m_NativeErrorCode = -1;
  m_lastError.m_SQLState = "";
}

void CSMC_DBData::logLastError(long Level)
{
  if ( m_lastError.m_MessageText.size() > 0 )
  {
    if (getTraceLevel() >= Level)
    {
      std::stringstream Message;
      Message << "Error on database handling occured : "
              << m_lastError.m_MessageText 
              << " - " 
              << m_lastError.m_NativeErrorCode 
              << " - " 
              << m_lastError.m_SQLState;

      log(Message.str(), Level);
    }
  }
}


std::string CSMC_DBData::getActStatement()
{
  return m_ActStatement;
}

bool CSMC_DBData::checkMetaData()
{
  bool RetValue = true;

  if (m_ColProfileList.empty())
  {
    RetValue = getMetaData(m_TableName);
  }

  return RetValue;
}

CSMC_DBData::CSMC_DBData(const CSMC_DBData& From)
: m_TableExists(From.m_TableExists)
, m_pCBS_StdConnection(From.m_pCBS_StdConnection)
, m_TableName(From.m_TableName)
, m_LastRow(0)
, m_ActRow(0)
, m_Statement("")
, m_ActStatement("")
, m_PreparedStatement("")
, m_Url(From.m_Url)
, m_Password(From.m_Password)
, m_Login(From.m_Login)
, m_PreparedValues("")
, m_pPreparedStatement(0)
, m_pSelectStatement(0)
, m_pStatement(0)
, m_pResultSet(0)
{
  resetLastError();

  m_WhereClauseList.clear();
  m_CopyColumnList.clear();
  m_ColProfileList.clear();

  //fill meta data
  if (!m_TableName.empty())
  {
    try
    {
      if ( !checkMetaData() )
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        std::string message = "Can not read metedata";  
        pEventLog->EL_DBReadError(sMessage, "", m_TableName.c_str(), message.c_str());
      }
    }
    catch(cCBS_DBExc_ConnectionError &ce) 
    {
      doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::CSMC_DBData(..)");

      // try reading metadata for a second time in case of broken connection
      if ( !checkMetaData() )
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        std::string message = "Can not read metedata";  
        pEventLog->EL_DBReadError(sMessage, "", m_TableName.c_str(), message.c_str());
      }
    }
  }

  close();
}

CSMC_DBData& CSMC_DBData::operator=(const CSMC_DBData& Value)
{
  if (this != &Value) 
  {
    //first free all statements
    close();

    m_TableExists = Value.m_TableExists;
    m_pCBS_StdConnection = Value.m_pCBS_StdConnection; // we point to the same cbs std connection
    m_TableName = Value.m_TableName;

    m_LastRow = 0;
    m_ActRow = 0;

    m_Statement = "";
    m_ActStatement = "";

    m_PreparedStatement = "";
    
    resetLastError();

    std::string m_Url = Value.m_Url;
    std::string m_Password = Value.m_Password;
    std::string m_Login = Value.m_Login;

    m_WhereClauseList.clear();
    m_CopyColumnList.clear();
    m_ColProfileList.clear();
    m_PreparedValues = "";

    //ownership of the original statements and result set remains with the original object
    m_pPreparedStatement = 0;
    m_pSelectStatement = 0;
    m_pStatement = 0;
    m_pResultSet = 0;

    //fill meta data
    if (!m_TableName.empty())
    {
      try
      {
        if ( !checkMetaData() )
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          std::string message = "Can not read metedata";  
          pEventLog->EL_DBReadError(sMessage, "", m_TableName.c_str(), message.c_str());
        }
      }
      catch(cCBS_DBExc_ConnectionError &ce) 
      {
        doOnCBS_DBExc_ConnectionError(ce,"CSMC_DBData::operator=");

        // try reading metadata for a second time in case of broken connection
        if ( !checkMetaData() )
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          std::string message = "Can not read metedata";  
          pEventLog->EL_DBReadError(sMessage, "", m_TableName.c_str(), message.c_str());
        }
      }
    }

    close();
  }

  return *this;
}