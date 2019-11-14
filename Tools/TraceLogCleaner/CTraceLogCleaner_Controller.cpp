// Copyright (C) 2005 SMS Demag AG Germany
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <direct.h>
#include <time.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "cCBS_StdMutex.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdEventLogFrameController.h"

#include "CDateTime.h"

#include "CTraceLogCleaner_Task.h"
#include "CTraceLogCleaner_Controller.h"


CTraceLogCleaner_Controller::CTraceLogCleaner_Controller(const std::string& ControlPath, const std::string& ControlDirectory)
: m_ControlPath(ControlPath)
, m_ControlDirectory(ControlDirectory)
{
  m_pCleaner_Thread = new CTraceLogCleaner_Controller::cCTraceLogCleaner_Thread(ControlPath,ControlDirectory);
  m_pCleaner_Thread->setFreeOnTerminate(true);
  m_pCleaner_Thread->run();
}

CTraceLogCleaner_Controller::~CTraceLogCleaner_Controller()
{
}

void CTraceLogCleaner_Controller::log(const std::string& Message, long Level)
{
  cCBS_StdLog_Task::getInstance()->log(Message, Level);
}

// ******************************************************************
// ******************************************************************
// Thread handling
// ******************************************************************
// ******************************************************************

CTraceLogCleaner_Controller::cCTraceLogCleaner_Thread::cCTraceLogCleaner_Thread(const std::string& ControlPath, const std::string& ControlDirectory)
: m_ControlTime(60000)
, m_ControlPath(ControlPath)
, m_ControlDirectory(ControlDirectory)
, m_ZipFiles(false)
, m_ZipPerDay(false)
{
  if ( !ControlPath.empty() )
  {
    m_FullPathName = ControlPath ; 
  }

  if ( !ControlDirectory.empty() )
  {
    if (m_FullPathName[m_FullPathName.length()-1] != '/')
    {
      m_FullPathName = m_FullPathName + "/";  // this works for windows only !
    }
    
    m_FullPathName = m_FullPathName + ControlDirectory;
  }

  // we expect m_FullPathName without final '/' 
  if (m_FullPathName[m_FullPathName.length()-1] == '/')
  {
    m_FullPathName = m_FullPathName.substr(0,m_FullPathName.length()-1);
  }

  m_FileExtensions.push_back("*");
  m_NoOfFiles     = 20;     // size of Files vector for No of files to be deleteed/zipped at one control cycle
  m_FileLifeTime  = 168;    // this is one week in hours

  // default is a subdirectory "log_backup" at XPACT_SMC
  m_Xpact_Smc     = cCBS_StdInitBase::getInstance()->getXPACT_SMC();

  // we extend m_ZipDirectory with final '/' if required
  if (m_Xpact_Smc[m_Xpact_Smc.length()-1] != '/')
  {
    m_Xpact_Smc = m_Xpact_Smc + "/";
  }

  m_ZipDirectory = m_Xpact_Smc + "log_backup";

  cCBS_StdInitBase::getInstance()->replaceWithEntry("CONTROLPATH","ControlTime",m_ControlTime);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("CONTROLPATH","FileLifeTime",m_FileLifeTime);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("CONTROLPATH","NoOfFiles",m_NoOfFiles);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("CONTROLPATH","FileExtensions",m_FileExtensions);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("CONTROLPATH","ZipFiles",m_ZipFiles);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("CONTROLPATH","ZipPerDay",m_ZipPerDay);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("CONTROLPATH","ZipDirectory",m_ZipDirectory);

  cCBS_StdInitBase::getInstance()->replaceWithEntry(ControlPath,"ControlTime",m_ControlTime);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(ControlPath,"FileLifeTime",m_FileLifeTime);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(ControlPath,"NoOfFiles",m_NoOfFiles);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(ControlPath,"FileExtensions",m_FileExtensions);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(ControlPath,"ZipFiles",m_ZipFiles);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(ControlPath,"ZipPerDay",m_ZipPerDay);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(ControlPath,"ZipDirectory",m_ZipDirectory);

  cCBS_StdInitBase::getInstance()->replaceWithEntry(ControlDirectory,"ControlTime",m_ControlTime);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(ControlDirectory,"FileLifeTime",m_FileLifeTime);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(ControlDirectory,"NoOfFiles",m_NoOfFiles);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(ControlDirectory,"FileExtensions",m_FileExtensions);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(ControlDirectory,"ZipFiles",m_ZipFiles);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(ControlDirectory,"ZipPerDay",m_ZipPerDay);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(ControlDirectory,"ZipDirectory",m_ZipDirectory);

  cCBS_StdInitBase::getInstance()->replaceWithEntry(m_FullPathName,"ControlTime",m_ControlTime);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(m_FullPathName,"FileLifeTime",m_FileLifeTime);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(m_FullPathName,"NoOfFiles",m_NoOfFiles);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(m_FullPathName,"FileExtensions",m_FileExtensions);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(m_FullPathName,"ZipFiles",m_ZipFiles);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(m_FullPathName,"ZipPerDay",m_ZipPerDay);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(m_FullPathName,"ZipDirectory",m_ZipDirectory);

  cCBS_StdLog_Task::getInstance()->log(" create zip directory " + m_ZipDirectory, 1);
  if ( m_ZipFiles )
  {
    // create zip directory
    try
    {
      //std::string Command = "md \"" + m_ZipDirectory + "\"";
      //system(Command.c_str());

      //if(n==0) // mkdir succeeded
      int n = _mkdir(m_ZipDirectory.c_str());

      if( errno != 17 && n != 0 ) // 17 = EEXIST File exists
      {
        //http://msdn.microsoft.com/de-de/library/t3ayayh1(v=VS.80).aspx
        cCBS_StdLog_Task::getInstance()->log("mkdir failed !!!!! ErrorNo = " + errno, 1);
      }

    }
    catch(...)
    {
      ;
    }
  }
}

CTraceLogCleaner_Controller::cCTraceLogCleaner_Thread::~cCTraceLogCleaner_Thread()
{
}

//Virtual work method. Sleeps for the specified ControlTime and checks status 
//will run down task and component in case of errors
void CTraceLogCleaner_Controller::cCTraceLogCleaner_Thread::work()
{
  try
  {
    while( !getTerminateThread() )
    {
      cCBS_StdLog_Task::getInstance()->log("  ", 1);
      cCBS_StdLog_Task::getInstance()->log(" Start control cycle for " + m_ControlDirectory, 1);

      performWorkingStep();
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CTraceLogCleaner_Controller::cCTraceLogCleaner_Thread::work()","performing Working Step");
  }
}


void CTraceLogCleaner_Controller::cCTraceLogCleaner_Thread::terminate()
{
  forceTerminate();
}


void CTraceLogCleaner_Controller::cCTraceLogCleaner_Thread::performWorkingStep()
{
  try
  {
    if ( !getTerminateThread() )
    {
      // only remove valid file names !
      if ( !m_FullPathName.empty() && m_FileExtensions.size() > 0 )
      {
        m_FileList.erase(m_FileList.begin(),m_FileList.end());

        setFileList(m_FullPathName);

        removeFiles(m_FileList);
      }
    }

    sleep(m_ControlTime);

  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CCyclicedTriggerCall::CCyclicTrig::performWorkingStep()","");
  }
}

//***********************************
// this functiomn is MSVS specific !
//***********************************

void CTraceLogCleaner_Controller::cCTraceLogCleaner_Thread::setFileList(const std::string& FullPath)
{
  cCBS_StdMutex Mutex("setFileList");

  std::vector<std::string>::iterator it;

  std::cout << "getting file list from directory " << FullPath <<  std::endl;

  for ( it = m_FileExtensions.begin(); it != m_FileExtensions.end() ; ++it)
  {
    struct _finddata_t c_file;
    intptr_t hFile;

    std::string Extension = (*it);

    if ( Extension != "*" )
    {
      Extension = Extension + "*";
    }

    std::cout << "looking for files with extension " << Extension <<  std::endl;

    // Find subdirectories
    std::string FindDir = FullPath + "/*" ;
    if ( (hFile = _findfirst( FindDir.c_str(), &c_file )) != -1L )
    {
      do
      {
        std::string DirName = c_file.name;

        // is this probably an directory ?
        if ( DirName.find('.') == std::string::npos )
        {
          std::string SubDir = FullPath + "/" + DirName;

          setFileList(SubDir);
        }
      } while ( _findnext(hFile, &c_file) == 0 );

     _findclose( hFile );

    } 


    // Find files
    std::string FindName = FullPath + "/*." + Extension;

    if ( (hFile = _findfirst( FindName.c_str(), &c_file )) != -1L )
    {
      do
      {
        std::string FileName = c_file.name;

        time_t time_write = c_file.time_write;

        CDateTime WriteDate(time_write);
        CDateTime Now;

        CDeltaTime DiffTime = CDateTime::subTimes(Now,WriteDate);

        // compare LifeTime in hours with age of file

        double Diff = DiffTime.asSeconds() / 3600. ;

        if ( Diff > m_FileLifeTime )
        {
          std::string FullFileName = FullPath + "/" + FileName;

          m_FileList.push_back(FullFileName);

          // limit files to be removed in one control cycle, default set to 20
          // 0 indicates "all files"
          if ( m_NoOfFiles > 0 && (long)m_FileList.size() >= m_NoOfFiles )
          {
            break;
          }
        }
      } while ( _findnext(hFile, &c_file) == 0 );

     _findclose( hFile );

    } 
  }

}

//***********************************
// this functiomn is MSVS specific !
//***********************************
bool CTraceLogCleaner_Controller::cCTraceLogCleaner_Thread::removeFiles(std::vector<std::string> FileList)
{ 
  bool RetValue = false;

  std::cout << "removing files from directory " << m_FullPathName <<  std::endl;

  // prepare zipping
  // program will create one zip file per Dir and write zip files into Dir

  std::string ZipProgramName = "zip.exe";
  std::string ZipProgramArguments ;

  cCBS_StdInitBase::getInstance()->replaceWithEntry("ZIPPROGRAM","ProgramName",ZipProgramName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("ZIPPROGRAM","ProgramArguments",ZipProgramArguments);


  if ( m_ZipFiles )
  {
    cCBS_StdMutex Mutex("ZipFileName");

    // prepare zip file name for zip command
    std::stringstream Zip;

    CDateTime FileDate;
    FileDate.addTime( -1 * m_FileLifeTime * 3600);

    Zip.fill('0');

    if ( m_ZipPerDay )
    {
      Zip << m_ZipDirectory 
          << "/" 
          << m_ControlDirectory 
          << "_" 
          << std::setw(4)
          << FileDate.getYear() 
          << "_" 
          << std::setw(2)
          << FileDate.getMonth() 
          << "_" 
          << std::setw(2)
          << FileDate.getDay() 
          << ".zip";
    }
    else
    {
      Zip << m_ZipDirectory 
          << "/" 
          << m_ControlDirectory 
          << "_" 
          << std::setw(4)
          << FileDate.getYear() 
          << "_week_" 
          << std::setw(2)
          << FileDate.getWeekNo() 
          << ".zip";
    }

    m_ZipFileName = Zip.str();
  }

  for ( m_FileListIterator = m_FileList.begin(); m_FileListIterator != m_FileList.end() ; ++m_FileListIterator)
  {
    if ( m_ZipFiles )
    {
      cCBS_StdMutex Mutex("zipFiles" + m_FullPathName);

      try
      {
        //std::string Command = "start/MIN zip " + ZipFileName + " \"" + FileName + "\"";
        std::string Command = ZipProgramName + " " + ZipProgramArguments + " " + m_ZipFileName + " \"" + (*m_FileListIterator) + "\"";
        system(Command.c_str());

        cCBS_StdLog_Task::getInstance()->log(" File " + (*m_FileListIterator) + " zipped to archive " + m_ZipFileName, 1);
      }
      catch(...)
      {
        ;
      }
    }
 
    {
      cCBS_StdMutex Mutex("removeFiles");

      if( remove( (*m_FileListIterator).c_str() ) == 0 )
      {
        cCBS_StdLog_Task::getInstance()->log(" File " + (*m_FileListIterator) + " deleted", 1);
        RetValue = true;
      }
    }
  }

  return RetValue;
}