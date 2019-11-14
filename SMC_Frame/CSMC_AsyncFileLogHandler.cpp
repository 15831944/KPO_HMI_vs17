// Copyright (C) 2010 SMS Siemag AG

#include <sstream>
#include "CDateTime.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_LogThread.h"

#include "CSMC_AsyncFileLogHandler.h"



void CSMC_AsyncFileLogHandler::log(const std::string& Message, long Level)
{
  try
  {
    CDateTime ActTime;
    std::stringstream ActMessage;
    ActMessage << ActTime.asString() 
                << " "  
                << Message << "\r\n"; // to avoid further writing to IO add new line to massage

    m_LogThread.setMessage(ActMessage.str().c_str(), ActMessage.str().length()+1);

  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(Message,"Unknown","CSMC_AsyncFileLogHandler::log","Logging Data");
  }
}

long CSMC_AsyncFileLogHandler::getQueueSize()
{
  return m_LogThread.getQueueSize();
}

CSMC_AsyncFileLogHandler::~CSMC_AsyncFileLogHandler()
{
  m_LogThread.stopThread();
}

CSMC_AsyncFileLogHandler::CSMC_AsyncFileLogHandler(const std::string& Filename /* = "" */)
{
  m_Type = cCBS_StdLogHandler::m_AsyncFileType;

  std::string FileDir = cCBS_StdInitBase::getInstance()->getXPACT_SMC_LOG();
  FileDir += cCBS_StdInitBase::getInstance()->m_ServerName + "\\";

  bool Redirect     = false;
	long NameDigits   = 3;
	long DataSetsNum  = 30000;
  long RingFilesNum = 100;
	long DaysNum      = 10;
  // if queue size is reached old message will be deleted
  long DataQueueMaxSize = 500;
  // no limit. flush for each message
  long FlushLimit   = 0;

  // read inifile values for trace logging
  cCBS_StdInitBase::getInstance()->replaceWithEntry("LOG","RedirectStdErr",Redirect);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("LOG","NameDigits",NameDigits);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("LOG","DataSetsNum",DataSetsNum);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("LOG","RingFilesNum",RingFilesNum);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("LOG","DaysNum",DaysNum);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("LOG","DataQueueMaxSize",DataQueueMaxSize);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("LOG","FlushLimit",FlushLimit);


	m_LogThread.setFileDir(FileDir.c_str());

	m_LogThread.setNameDigits(NameDigits);
	m_LogThread.setDataSetsNum(DataSetsNum);
	m_LogThread.setRingFilesNum(RingFilesNum);
	m_LogThread.setDaysNum(DaysNum);
  m_LogThread.setDataQueueMaxSize(DataQueueMaxSize);
  m_LogThread.setFlushLimit(FlushLimit);

	m_LogThread.setFileExt("log");
  m_LogThread.setTimeSeparator("_");

  // Sets the file root name.
  // default filename is server name
  std::string NewFileName = Filename;

  // overwrite if set by contructor argument
  if ( NewFileName.empty() )
  {
    NewFileName = cCBS_StdInitBase::getInstance()->m_ServerName.c_str();
  }

  // sets file to ring and creates first file
  m_LogThread.setFileRootName(NewFileName.c_str());

	m_LogThread.startThread();
	Sleep(50); // for sure start-up

}

