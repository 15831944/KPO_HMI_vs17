//-------------------------------------------------------------------------------------------------
//
//                           S M S S i e m a g  A G
//
//                            All Rights Reserved
//
//
// project       : Email Server
// filename      : cEmailServer_Comp.cpp
// originator    : Sankar Sarkar
// department    : SMS Siemag
// creation date : 2010
// description   : CBS component for Email Server
//
//-------------------------------------------------------------------------------------------------

//
//-------------------------------------------------------------------------------------------------
// compile test log levels op to #9
#define _CLOG9

#include <strstream>
#include <cctype>

#include "cEmailServer_Comp.h"
#include "CBS_Clog.h"

using namespace System::Runtime::InteropServices;

cEmailServer_Comp * cEmailServer_Comp::m_comp = NULL;

//-------------------------------------------------------------------------------------------------
// getComponent()
//-------------------------------------------------------------------------------------------------
cEmailServer_Comp * cEmailServer_Comp::getComponent()
{
  if (!cEmailServer_Comp::m_comp)
  {
    cEmailServer_Comp::m_comp = new cEmailServer_Comp();
  }
  return cEmailServer_Comp::m_comp;
}

//-------------------------------------------------------------------------------------------------
// release()
// Destroys the pointer to this component.
//-------------------------------------------------------------------------------------------------
void cEmailServer_Comp::release()
{
  if ( cEmailServer_Comp::m_comp )
  {
    delete cEmailServer_Comp::m_comp;
  }
  cEmailServer_Comp::m_comp = NULL;
}

//-------------------------------------------------------------------------------------------------
// ~cEmailServer_Comp()
//-------------------------------------------------------------------------------------------------
cEmailServer_Comp::~cEmailServer_Comp()
{
  try
  {
    if (m_pEmailServerEventHdlTask)
    {
      delete m_pEmailServerEventHdlTask;
    }

  }
  catch(...)
  {
    CLOG1(<< "Destructor: unknown exception caught!" << std::endl);
  }
}

//-------------------------------------------------------------------------------------------------
// cEmailServer_Comp()
// Constructor. Checks for command line arguments and existance of ini-file.
// In case ini-file is not specified a hard-coded standard name is being used.
//-------------------------------------------------------------------------------------------------
cEmailServer_Comp::cEmailServer_Comp()
{
  m_IniFile = "EmailServer.ini";                              // initialisation value; to be taken if no -config
  std::string l_IniFile = "";                         // is specified for exe

  std::string l_Entry;
  long lIniPos = 1;

  //Access CBS Config Base for INI-file
  long lArgs = cCBS_ConfigBase::getConfigBase()->numCmdLineArgs();

  //find entry -config path\file.ini
  for ( int i=1; i < lArgs; i++)
  {
    cCBS_ConfigBase::getConfigBase()->getCmdLineArg(i, l_Entry);
    if (l_Entry == "-config")  // read argument as passed by application shortcut
    {
      lIniPos = i+1;
      break;
    } //if
    else
    {
      CLOG2(<< "Constructor: 'config' argument missing for this application!" << std::endl);
    }
  } //for

  cCBS_ConfigBase::getConfigBase()->getCmdLineArg(lIniPos, l_IniFile);

  if (l_IniFile.size() >0)
  {
    m_IniFile = l_IniFile;
  }
  else
  {
    CLOG2(<< "Constructor: ini file seems to be empty!" << std::endl);
  }
  
//  m_emails = gcnew cEmailServerCore(); 

  CLOG5(<< "Constructor: finished!" << std::endl);
}

void cEmailServer_Comp::ownStartUp()
{
  cCBS_StdComponent::ownStartUp();

  
}
//-------------------------------------------------------------------------------------------------
// getIniFile()
// Returns a pointer to ini-file name.
//-------------------------------------------------------------------------------------------------
const char * cEmailServer_Comp::getIniFile()
{
  return m_IniFile.c_str();
}
//-------------------------------------------------------------------------------------------------
// createSubtasks()
// Create subtasks of model.
//-------------------------------------------------------------------------------------------------
void cEmailServer_Comp::createSubtasks()
{

  // load parameters from config base
  m_cfb = cCBS_ConfigBase::getConfigBase();
  if (!m_cfb)
  {
    CLOG1("cCLM_Comp::createSubtasks(): ConfigBase not found !" << std::endl);
    return;
  }

  // set task data
  CBS_TaskData taskData;
  taskData.critical     = true;
  taskData.autoRecovery = true;
  taskData.priority     = MCBS::MCBS_PrioNormal;

 
  //Creating Event Receiver Task
  std::string ChannelName;
  std::string ServiceName;
  std::string MailId_HMD;
  std::string MailId_LF;
  std::string MailId_EAF;
  m_cfb->getActGrpEle("EVChannel", "EVChannelServiceName", ServiceName);
  m_cfb->getActGrpEle("EVChannel", "EVChannelName", ChannelName);
  m_cfb->getActGrpEle("MAIL_HMD", "MAILID", MailId_HMD);
  m_cfb->getActGrpEle("MAIL_LF", "MAILID", MailId_LF);
  m_cfb->getActGrpEle("MAIL_EAF", "MAILID", MailId_EAF);
  
  m_pEmailServerEventHdlTask  = new cEmailServerEventHdlTask(ChannelName.c_str(), ServiceName.c_str());   
  m_pEmailServerEventHdlTask ->activate(m_componentPOA, "EmailServer_EventHdlTask");
  addSubtask(m_pEmailServerEventHdlTask->getTaskName(),
    m_pEmailServerEventHdlTask->getReference(),
    taskData);

  CLOG5(<< "Create subtasks: Event Handler Task created..." << std::endl);

}



//-------------------------------------------------------------------------------------------------
// afterSubtaskEnd()
//-------------------------------------------------------------------------------------------------
void cEmailServer_Comp::afterSubtaskEnd()
{
  CLOG6( << "afterSubtaskEnd: going to finish. Shut down ORB connection." << std::endl); // TODO: this ok?
  try
  {
    CBS::shutdown();
//    m_emails->Shutdown();
  }                                             
  catch (...)                                   
  {
    CLOG1(<< "afterSubtaskEnd: error when trying to shutdown ORB connection!" << std::endl);
  }
}

//EMAILS::cParam::EmailParameter * cEmailServer_Comp::ReadConfigParameters(std::string email)
//{
//  if(m_EmailsParameterMap.find(email) != m_EmailsParameterMap.end())
//  {
//    return &m_EmailsParameterMap.find(email)->second;
//  }
//    
//  else
//    return nullptr;
//
//}

String^ cEmailServer_Comp::ConvertString(const char* s)
{
  if(s == 0)
    return nullptr;
  return Marshal::PtrToStringAnsi(IntPtr((void*)s));
}

std::string cEmailServer_Comp::ConvertString(String^ s)
{
  if(s == nullptr)
    return "";
  IntPtr p = Marshal::StringToHGlobalAnsi(s);
  std::string ret((const char*)p.ToPointer());
  Marshal::FreeHGlobal(p);
  return ret;
}



