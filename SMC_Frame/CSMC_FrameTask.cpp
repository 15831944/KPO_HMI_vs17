// Copyright (C) 2004 SMS Demag AG

#include "cCBS_StdConnection.h"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdDB_Task.h"

#include "cCBS_StdEventLogFrameController.h"

#include "CSMC_FrameTask.h"


std::string CSMC_FrameTask::EVENT("EVENT");

std::string CSMC_FrameTask::PLANT("PLANT");

std::string CSMC_FrameTask::PRODUCT("PRODUCT");

CSMC_FrameTask::CSMC_FrameTask() 
{
}


CSMC_FrameTask::~CSMC_FrameTask()
{
}

cCBS_StdConnection* CSMC_FrameTask::getStdConnection()
{
  cCBS_StdConnection* pStdConnection = 0;

  try
  {
    pStdConnection = cCBS_StdDB_Task::getInstance()->getCBS_StdConnection(m_DBName,m_DBUser, m_DBPassword);
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(Message,"DB connection error","CSMC_FrameTask::getStdConnection()","unknown connection / URL");
  }
  
	return pStdConnection;
}

void CSMC_FrameTask::handleDBConnectionError()
{
  setDBConnectionParameter();

  checkDBConnection();
}

bool CSMC_FrameTask::initialize()
{
  bool RetCode = cCBS_StdFrame_Task::initialize();

  RetCode = RetCode && setDBConnectionParameter();

  RetCode = RetCode && checkDBConnection();

  if ( !RetCode )
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(Message,"initialize failed","CSMC_FrameTask::initialize()","terminating programm");

    // to guaranty EL_ExceptionCaught to be sent to CBS service
    Sleep(3000);

    // terminate programm in case of starting up without getting connection to database
    exit(EXIT_FAILURE);
  }


  return RetCode;
}

void CSMC_FrameTask::log(const std::string& Message, long Level)
{
	cCBS_StdFrame_Task::log(Message, Level);
}

bool CSMC_FrameTask::setDBConnectionParameter()
{
  bool RetValue = false;

  cCBS_StdInitBase *pStdInitBase = cCBS_StdInitBase::getInstance();

  try
  {  
    if ( !( pStdInitBase->getEntry("DATABASE", "SMC_DBName", m_DBName) &&
            pStdInitBase->getEntry("DATABASE", "SMC_DBUser", m_DBUser)  &&
            pStdInitBase->getEntry("DATABASE", "SMC_DBPassword", m_DBPassword) ))
    {
      std::cerr << "Can not read SMC database settings from ini-file" << std::endl;

      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(Message,"ini file error","CSMC_FrameTask::setDBConnectionParameter()","cannot read SMC database settings from ini file");
    }
    else
    {
      RetValue = true;
    }
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(Message,"ini file error","CSMC_FrameTask::setDBConnectionParameter()","cannot read SMC database settings from ini file");
  }

  return RetValue;
}

bool CSMC_FrameTask::checkDBConnection()
{
  bool RetValue = cCBS_StdDB_Task::getInstance()->checkConnection(m_DBName, m_DBUser, m_DBPassword);

  if ( !RetValue )
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(Message,"DB connection check failed","CSMC_FrameTask::checkDBConnection()","Can not establish database connection");
  }

  return RetValue;
}