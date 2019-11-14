// Copyright (C) 2004 SMS Demag AG

#include <sstream>
#include "CDateTime.h"
#include "cCBS_FileRing.h"
#include "cCBS_StdFile.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"

#include "CSMC_FpFile.h"
#include "CSMC_Mutex.h"

#include "CSMC_FileLogHandler.h"



//##ModelId=41FE111D0299
void CSMC_FileLogHandler::log(const std::string& Message, long Level)
{
  // NOTE: Level dependence is not yet implemented in log files
  CSMC_Mutex Mutex("CSMC_FileLogHandler::log");

  try
  {
    if (m_Ring && m_File)
    { 
      // hide ringfile against multiple usage !

      CDateTime ActTime;
      std::stringstream ActMessage;
      ActMessage << ActTime.asString() 
                 << " "  
                 << Message;

      m_File->writeData(ActMessage.str().c_str(),'\r','\n');
//      m_File->writeData("\r\n"); 
      m_File->flush();

      m_File->acceptVisit(m_Ring);
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(Message,"","","Logging Data");
  }
}



//##ModelId=41FE13A403BA
CSMC_FileLogHandler::~CSMC_FileLogHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}

//##ModelId=41FE13A50180
CSMC_FileLogHandler::CSMC_FileLogHandler(const std::string& Filename /* = "" */)
: m_File(0)
, m_Ring(0)
{
  m_Type = cCBS_StdLogHandler::m_FileType;

  std::string FileDir = cCBS_StdInitBase::getInstance()->getXPACT_SMC_LOG();
  FileDir += cCBS_StdInitBase::getInstance()->m_ServerName + "\\";

  bool Redirect     = false;
	long NameDigits   = 3;
	long DataSetsNum  = 10000;
  long RingFilesNum = 100;
	long DaysNum      = 10;

  // read inifile values for trace logging
  cCBS_StdInitBase::getInstance()->replaceWithEntry("LOG","RedirectStdErr",Redirect);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("LOG","NameDigits",NameDigits);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("LOG","DataSetsNum",DataSetsNum);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("LOG","RingFilesNum",RingFilesNum);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("LOG","DaysNum",DaysNum);

  m_Ring = new cCBS_FileRing();
  m_File = new CSMC_FpFile(Redirect);

  m_Ring->setFileDir(FileDir.c_str());

	// Sets the number of digits in the index of the file name
	m_Ring->setNameDigits(NameDigits);
	// Sets the number of datasets that are to be stored in each file
	m_Ring->setDataSetsNum(DataSetsNum);
	// Sets the number of files in the ring buffer
	m_Ring->setRingFilesNum(RingFilesNum);
	// Sets the number of days over which the files are kept
	m_Ring->setDaysNum(DaysNum);

	// Sets the files extension
	m_Ring->setFileExt("log");
	// Sets the files name deliimiters
  m_Ring->setTimeSeparator("_");

  // Sets the file root name.
  // default filename is server name
  std::string NewFileName = Filename;

  // overwrite if set by contructor argument
  if ( NewFileName.empty() )
  {
    NewFileName = cCBS_StdInitBase::getInstance()->m_ServerName.c_str();
  }

  m_Ring->setFileRootName(NewFileName.c_str());

	// Sets the file source pointer into the ring buffer object
	m_Ring->setFile(m_File);

}

