// Copyright (C) 2005 SMS Demag AG Germany

#include "cCBS_StdInitBase.h"
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdDB_Task.h"

#include "CTraceLogCleaner_Controller.h"
#include "CTraceLogCleaner_Task.h"

#include "io.h"   //satk 25-05-2018



CTraceLogCleaner_Task* CTraceLogCleaner_Task::m_Instance = 0;


CTraceLogCleaner_Task::CTraceLogCleaner_Task()
{
}

CTraceLogCleaner_Task::~CTraceLogCleaner_Task()
{
}

 CTraceLogCleaner_Task* CTraceLogCleaner_Task::getInstance() 
{
	if ( m_Instance == 0 )
	{
		m_Instance = new CTraceLogCleaner_Task( );
	}

	return m_Instance;

}


void CTraceLogCleaner_Task::log(const std::string& Message, long Level)
{
  cCBS_StdLog_Task::getInstance()->log(Message, Level);
}

bool CTraceLogCleaner_Task::initialize()
{
  bool ret = cCBS_StdFrame_Task::initialize();

  std::vector<std::string> PathNames;
  std::vector<std::string> DirectoryNames;
  std::vector<std::string>::iterator itPathNames;
  std::vector<std::string>::iterator itSubDirs;

  if ( !cCBS_StdInitBase::getInstance()->getEntryList("CONTROLPATH","PathNames",PathNames) )
  {
    std::string PathName = cCBS_StdInitBase::getInstance()->getXPACT_SMC_LOG();

    // we expect PathName without final '/' 
    if (PathName[PathName.length()-1] == '/')
    {
      PathName = PathName.substr(0,PathName.length()-1);
    }

    PathNames.push_back( PathName );
  }

  // one CTraceLogCleaner_Controller per directory of each path
  for ( itPathNames = PathNames.begin(); itPathNames != PathNames.end(); ++itPathNames)
  {
    std::string PathName = (*itPathNames);

    std::vector<std::string> SubDirs = getSubDirs(PathName);

    if ( SubDirs.size() > 0 )
    {
      for ( itSubDirs = SubDirs.begin(); itSubDirs != SubDirs.end(); ++itSubDirs)
      {
        std::string SubDir = (*itSubDirs);
        CTraceLogCleaner_Controller *pTraceLogCleaner_Controller = new CTraceLogCleaner_Controller(PathName,SubDir);
        m_TraceLogCleaner_ControllerList.push_back(pTraceLogCleaner_Controller);
      }
    }
    else
    {
      CTraceLogCleaner_Controller *pTraceLogCleaner_Controller = new CTraceLogCleaner_Controller(PathName,"");
      m_TraceLogCleaner_ControllerList.push_back(pTraceLogCleaner_Controller);
    }
  }

  return ret;
}

std::vector<std::string> CTraceLogCleaner_Task::getSubDirs(const std::string& PathName)
{
  std::vector<std::string> SubDirs;

  struct _finddata_t c_file;
  intptr_t hFile;

  // Find subdirectories
  std::string FindDir = PathName + "/*" ;
  if ( (hFile = _findfirst( FindDir.c_str(), &c_file )) != -1L )
  {
    do
    {
      std::string DirName = c_file.name;

      // is this probably an directory ?
      if ( DirName.find('.') == std::string::npos )
      {
        SubDirs.push_back(DirName);
      }
    } while ( _findnext(hFile, &c_file) == 0 );

   _findclose( hFile );

  } 

  return SubDirs;
}


