// Copyright (C) 1999 - 2004 SMS Demag AG
#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <string>
#include <sstream>

#include "cCBS_StdLog_Task.h"
#include "cCBS_StdInitBase.h"


static char PROJECT_NAME[200];
static char SERVER_NAME[200];
static char IIOP_PORT[200];

//##ModelId=40EBCAAE000A
cCBS_StdInitBase* cCBS_StdInitBase::m_pInstance = 0;

//##ModelId=40EAA09302A8
cCBS_StdInitBase* cCBS_StdInitBase::CreateInstance(const std::string  & procName, const std::string  & iniFileName)
{
  const int MAXFILELEN = 300;
  static char ProcNameBuffer[MAXFILELEN];
  static char FileNameBuffer[MAXFILELEN];
  static char* argv[2] = {ProcNameBuffer, FileNameBuffer};

  if(!m_pInstance)
  {
    if (procName.length() < MAXFILELEN && iniFileName.length() < MAXFILELEN)
    {
      strcpy(ProcNameBuffer, procName.c_str());
      strcpy(FileNameBuffer, iniFileName.c_str());
      const int argc = 2;
      m_pInstance = new cCBS_StdInitBase(argc, argv);
    }
  }
  return m_pInstance;
}

//##ModelId=40EAA09302AF
void cCBS_StdInitBase::DeleteInstance()
{
  // TODO: Add your specialized code here.
}

//##ModelId=40EAA09302B8
bool cCBS_StdInitBase::getEntry(const std::string & Group, const std::string & Element, std::string  &value)
{
  bool RetValue = false;
  std::string IniFileValue;

  try
  {
    if(m_pCBS_ConfigBase->getActGrpEle(Group.c_str(),Element.c_str(),IniFileValue) )
    {
      std::stringstream Message;
      Message << "Found value for ";
      Message << Group;
      Message << ":";
      Message << Element;
      Message << " at ini file. Using value '" ;
      Message << IniFileValue;
      Message << "'" ;
      cCBS_StdLog_Task::getInstance()->log(Message.str(),5);

      value = IniFileValue;
      RetValue = true;
    }
  }
  catch(...)
  {
    std::string Message;
    Message = "Exception caught reading " + Group + ":" + Element + " from ini file.";
    cCBS_StdLog_Task::getInstance()->log(Message, 1);
  }

  return RetValue;
}

//##ModelId=40EAA09302C0
cCBS_StdInitBase::~cCBS_StdInitBase()
{
  delete m_pCBS_ConfigBase;
}

//##ModelId=40EAA09302C3
cCBS_StdInitBase::cCBS_StdInitBase(int argc, char *argv[]   ) : 
m_ProjectName("Project"), 
m_ComponentName("Component"), 
m_TaskName("Task"), 
m_DataBase("Database"), 
m_DBUserName("SMC"), 
m_DBPassWd("SMC"), 
m_ServerName("Server"), 
m_IIOP_Port("17000"), 
m_ChannelName("SMC_EventChannel"), 
m_ServiceName("SMC_EventService"), 
m_pCBS_ConfigBase(0),
m_ConfigName("default")
{
  try
  {
    cCBS_ConfigBase * configBase = cCBS_ConfigBase::getConfigBase();

    if (!configBase)
    {
       m_pCBS_ConfigBase = new cCBS_ConfigBase(argc,argv);
    }
    else
    {
      m_pCBS_ConfigBase = configBase;
    }
    
    // sets all configuration data to initialize server object.
    this->initialize();
  }
  catch(...)
  {
    delete m_pCBS_ConfigBase;
    throw;
  }
}

//##ModelId=40EAA093029E
bool cCBS_StdInitBase::getEntry(const std::string & Group, const std::string & Element, long  & value  )
{
  bool RetValue = false;
  long IniFileValue = 0;

  try
  {
    if(m_pCBS_ConfigBase->getActGrpEle(Group.c_str(),Element.c_str(),IniFileValue) )
    {
      std::stringstream Message;
      Message << "Found value for ";
      Message << Group;
      Message << ":";
      Message << Element;
      Message << " at ini file. Using value '" ;
      Message << IniFileValue;
      Message << "'" ;
      cCBS_StdLog_Task::getInstance()->log(Message.str(),5);

      value = IniFileValue;
      RetValue = true;
    }
  }
  catch(...)
  {
    std::string Message;
    Message = "Exception caught reading " + Group + ":" + Element + " from ini file.";
    cCBS_StdLog_Task::getInstance()->log(Message, 1);
  }

  return RetValue;
}

bool cCBS_StdInitBase::getEntry(const std::string & Group, const std::string & Element, long long & value  )
{
  bool RetValue = false;
  std::string IniFileValue;

  try
  {
    if(m_pCBS_ConfigBase->getActGrpEle(Group.c_str(),Element.c_str(),IniFileValue) )
    {
      std::stringstream Message;
      Message << "Found value for ";
      Message << Group;
      Message << ":";
      Message << Element;
      Message << " at ini file. Using value '" ;
      Message << IniFileValue;
      Message << "'" ;
      cCBS_StdLog_Task::getInstance()->log(Message.str(),5);

      long long temp_convert = 0;
      std::stringstream stream;		
      stream << IniFileValue;

      if ( ( stream >> temp_convert ) )
      {
        value = temp_convert;
        RetValue = true;
      }
    }
  }
  catch(...)
  {
    std::string Message;
    Message = "Exception caught reading " + Group + ":" + Element + " from ini file.";
    cCBS_StdLog_Task::getInstance()->log(Message, 1);
  }

  return RetValue;
}


//##ModelId=40EAA09302A6
void cCBS_StdInitBase::initialize()
{

  if (m_pCBS_ConfigBase)
  {
    m_pCBS_ConfigBase->getActCfgName(m_ConfigName);
  }

  replaceWithEntry("PROJECT","Name",m_ProjectName);
  strcpy(PROJECT_NAME, m_ProjectName.c_str());

  replaceWithEntry("CORBA","ServerName",m_ServerName);
  strcpy(SERVER_NAME, m_ServerName.c_str());

  m_TaskName = m_ServerName + "Task";
  
  replaceWithEntry("DATABASE","DBName",m_DataBase);
  
  replaceWithEntry("DATABASE","DBUser",m_DBUserName);
  
  replaceWithEntry("DATABASE","DBPassword",m_DBPassWd);
  
  
  replaceWithEntry("CORBA","IiopPort",m_IIOP_Port);
  strcpy(IIOP_PORT, m_IIOP_Port.c_str());

  replaceWithEntry("EventService","EvChannelName",m_ChannelName);
  
  replaceWithEntry("EventService","EvServiceName",m_ServiceName);

  char *res;
  if ( (res = getenv("X-Pact")) != NULL)
  {
      m_XPACT_SMC = res;
      if (m_XPACT_SMC[m_XPACT_SMC.length()-1] != '/')
        m_XPACT_SMC += '/';
  }
  else
  {
    m_XPACT_SMC.clear();
    cCBS_StdLog_Task::getInstance()->log("Environment variable X-Pact not set.", 1);
  }

  if ( (res = getenv("X-Pact_RT")) != NULL)
  {
      m_XPACT_SMC_RT = res;
      if (m_XPACT_SMC_RT[m_XPACT_SMC_RT.length()-1] != '/')
        m_XPACT_SMC_RT += '/';

      m_XPACT_SMC_LOG = m_XPACT_SMC_RT + "log" + '/'; 
  }
  else
  {
    m_XPACT_SMC_LOG.clear();
    m_XPACT_SMC_RT.clear();
    cCBS_StdLog_Task::getInstance()->log("Environment variable X-Pact_RT not set.", 1);
  }

  this->setArgForEventChannel();
}

//##ModelId=40EAA09302B2
cCBS_StdInitBase* cCBS_StdInitBase::getInstance()
{
  if(!m_pInstance)
  {
    CreateInstance();
  }
  return m_pInstance;
}

//##ModelId=40EAA09302C9
void cCBS_StdInitBase::setArgForEventChannel()
{
  m_ArgcForEventConsumer = 0;
  m_ArgcForEventSender = 0;

  char** act_argv_Consumer = new char*[0];
  char** act_argv_Sender = new char*[0];

  m_ArgvForEventConsumer = act_argv_Consumer;
  m_ArgvForEventSender   = act_argv_Sender;

}


//##ModelId=434CD3370002
bool cCBS_StdInitBase::replaceWithEntry(const std::string& Group, const std::string& Element, std::vector<std::string>& value)
{
  bool RetValue = true;
  // remark incoming value
  std::vector<std::string> ActValue = value;
  std::vector<std::string> IniValue;
  std::vector<std::string> NewValue;

  if (!getEntryList(Group, Element, IniValue) || IniValue.empty() )
  {
    NewValue = ActValue;
    RetValue = false;
  }
  else
  {
    NewValue = IniValue;
  }

  value = NewValue;

  return RetValue;
}

//##ModelId=40F53EA1017E
bool cCBS_StdInitBase::replaceWithEntry(const std::string & Group, const std::string & Element, std::string  & value)
{
  bool RetValue = true;
  // remark incoming value
  std::string ActValue = value;
  std::string IniValue;
  std::string NewValue;

  if (!getEntry(Group, Element, IniValue) || IniValue.empty() )
  {
    NewValue = ActValue;
    RetValue = false;
  }
  else
  {
    NewValue = IniValue;
  }

  value = NewValue;

  return RetValue;
}

//##ModelId=410E53A2018C
bool cCBS_StdInitBase::replaceWithEntry(const std::string & Group, const std::string & Element, long  & value)
{
  bool RetValue = true;
  int ActValue = value;

  if (!getEntry(Group, Element, value) )
  {
    value = ActValue;
    RetValue = false;
  }

  if ( !RetValue )
  {
    std::string Message;
    Message = "Error reading " + Group + ":" + Element + " from ini file.";
    cCBS_StdLog_Task::getInstance()->log(Message,5);
  }

  return RetValue;
}

bool cCBS_StdInitBase::replaceWithEntry(const std::string & Group, const std::string & Element, long long & value)
{
  bool RetValue = true;
  long long ActValue = value;

  if (!getEntry(Group, Element, value) )
  {
    value = ActValue;
    RetValue = false;
  }

  if ( !RetValue )
  {
    std::string Message;
    Message = "Error reading " + Group + ":" + Element + " from ini file.";
    cCBS_StdLog_Task::getInstance()->log(Message,5);
  }

  return RetValue;
}


//##ModelId=410E54EA0332
bool cCBS_StdInitBase::getEntry(const std::string & Group, const std::string & Element, double  & value  )
{
  bool RetValue = false;
  double IniFileValue = 0.0;

  try
  {
    if(m_pCBS_ConfigBase->getActGrpEle(Group.c_str(),Element.c_str(),IniFileValue) )
    {
      std::stringstream Message;
      Message << "Found value for ";
      Message << Group;
      Message << ":";
      Message << Element;
      Message << " at ini file. Using value '" ;
      Message << IniFileValue;
      Message << "'" ;
      cCBS_StdLog_Task::getInstance()->log(Message.str(),5);

      value = IniFileValue;
      RetValue = true;
    }
  }
  catch(...)
  {
    std::string Message;
    Message = "Exception caught reading " + Group + ":" + Element + " from ini file.";
    cCBS_StdLog_Task::getInstance()->log(Message, 1);
  }

  return RetValue;
}

//##ModelId=410E55070355
bool cCBS_StdInitBase::replaceWithEntry(const std::string & Group, const std::string & Element, double  & value)
{
  bool RetValue = true;
  double ActValue = value;

  if (!getEntry(Group, Element, value))
  {
    value = ActValue;
    RetValue = false;
  }

  if ( !RetValue )
  {
    std::string Message;
    Message = "Error reading " + Group + ":" + Element + " from ini file.";
    cCBS_StdLog_Task::getInstance()->log(Message,5);
  }

  return RetValue;
}

//##ModelId=410E60700070
bool cCBS_StdInitBase::getEntry(const std::string & Group, const std::string & Element, bool  & value)
{
  bool RetValue = false;
  int IniFileValue = 0;

  try
  {
    if(m_pCBS_ConfigBase->getActGrpEle(Group.c_str(),Element.c_str(),IniFileValue) )
    {
      std::stringstream Message;
      Message << "Found value for ";
      Message << Group;
      Message << ":";
      Message << Element;
      Message << " at ini file. Using value '" ;
      Message << IniFileValue;
      Message << "'" ;
      cCBS_StdLog_Task::getInstance()->log(Message.str(),5);
      RetValue = true;

      if (IniFileValue != 0)
      {
        value = true;
      }
      else
      {
        value = false;
      }
    }
  }
  catch(...)
  {
    std::string Message;
    Message = "Exception caught reading " + Group + ":" + Element + " from ini file.";
    cCBS_StdLog_Task::getInstance()->log(Message, 1);
  }

  return RetValue;
}

//##ModelId=410E6079018C
bool cCBS_StdInitBase::replaceWithEntry(const std::string & Group, const std::string & Element, bool  & value)
{
  bool RetValue = true;
  bool ActValue = value;

  if (!getEntry(Group, Element, value))
  {
    value = ActValue;
    RetValue = false;
  }

  if ( !RetValue )
  {
    std::string Message;
    Message = "Error reading " + Group + ":" + Element + " from ini file.";
    cCBS_StdLog_Task::getInstance()->log(Message,5);
  }

  return RetValue;
}

//##ModelId=411B3E8403B3
const std::string& cCBS_StdInitBase::getXPACT_SMC() const
{
  return m_XPACT_SMC;
}

//##ModelId=411B3E850308
const std::string& cCBS_StdInitBase::getXPACT_SMC_LOG() const
{
  return m_XPACT_SMC_LOG;
}

const std::string& cCBS_StdInitBase::getXPACT_SMC_RT() const
{
  return m_XPACT_SMC_RT;
}


//##ModelId=4124ECF600F8
 std::string& cCBS_StdInitBase::getConfigName()
{
	return m_ConfigName;
}

//##ModelId=412F1C8203C2
bool cCBS_StdInitBase::getEntryList(const std::string& Group, const std::string& Element, std::vector<std:: string> & List)
{
  bool RetValue = false;
  std::string value;

  if ( getEntry(Group,Element,value) )
  {
    std::string ActString;

    if (!value.empty() )
    {
      RetValue = true;
      std::string ActValue = value;

      while (!ActValue.empty())
      {
        std::string ActSubstr = ActValue;

        std::basic_string <char>::size_type pos = ActValue.find(",");

        if ( std::string::npos != pos )
        {
          ActSubstr = ActValue.substr(0,pos );
          ActValue = ActValue.substr(pos+1,ActValue.length());
        }
        else
        {
          ActValue.erase();
        }

        if ( ActSubstr.length() > 0 )
        {
          ActSubstr = Trim(ActSubstr," ");
        }

        List.push_back(ActSubstr);        
      }
    }
  }

	return RetValue;
}

bool cCBS_StdInitBase::getAtEntryList(const std::string& Group, const std::string& Element, long Position, std::string& Value)
{
  bool RetValue = false;

  std::vector<std::string> List;

  if ( getEntryList(Group, Element, List) )
  {
    if ( (long)List.size() >= Position )
    {
      Value = List.at(Position - 1);
      RetValue = true;
    }
  }

	return RetValue;
}

bool cCBS_StdInitBase::isValueOfList(const std::string& Group, const std::string& ListName, const std::string& Value)
{
  bool RetValue = false;

  std::vector<std::string> List;

  if ( getEntryList(Group, ListName, List) )
  {
    std::vector<std::string>::iterator it;

    for ( it = List.begin(); it != List.end(); ++it )
    {
      std::string Element = (*it);

      if ( Element == Value )
      {
        RetValue = true;
        break;
      }
    }
  }

  return RetValue;
}

bool cCBS_StdInitBase::getValueOfListEntry(const std::string& Group, const std::string& ListName, const std::string& Entry, std::string& Value)
{
  bool RetValue = false;

  std::vector<std::string> List;

  if ( getEntryList(Group, ListName, List) )
  {
    std::vector<std::string>::iterator it;

    for ( it = List.begin(); it != List.end(); ++it )
    {
      std::string Element = (*it);

      // entry found in list and entry has an element with value
      if ( Element == Entry && getEntry(Group, Element, Value) )
      {
        RetValue = true;
        break;
      }
    }
  }

	return RetValue;
}

bool cCBS_StdInitBase::getValueOfListEntry(const std::string& Group, const std::string& ListName, const std::string& Entry, long& Value)
{
  bool RetValue = false;

  std::vector<std::string> List;

  if ( getEntryList(Group, ListName, List) )
  {
    std::vector<std::string>::iterator it;

    for ( it = List.begin(); it != List.end(); ++it )
    {
      std::string Element = (*it);

      // entry found in list and entry has an element with value
      if ( Element == Entry && getEntry(Group, Element, Value) )
      {
        RetValue = true;
        break;
      }
    }
  }

	return RetValue;
}




//##ModelId=45ACF218010A
int cCBS_StdInitBase::numCmdLineArgs()
{
  int ArgNum = 0;

  if (m_pCBS_ConfigBase)
    ArgNum = m_pCBS_ConfigBase->numCmdLineArgs();

  return ArgNum;
}

//##ModelId=45ACF218011E
bool cCBS_StdInitBase::getCmdLineArgs(std::vector<std::string>& Arguments)
{
  bool ret = false;
  
  ret = m_pCBS_ConfigBase->getCmdLineArgs(Arguments);

  return ret;
}

std::string cCBS_StdInitBase::Trim(const std::string& Value, const std::string& Sign)
{
  std::string RetValue;

  if ( Value.length() > 0 )
  {
    RetValue = Value;

    std::string::size_type pos = RetValue.find_last_not_of(Sign);
    if ( pos != std::string::npos )
    {
      RetValue.erase(pos + 1);
      pos = RetValue.find_first_not_of(Sign);

      if ( pos != std::string::npos )
      {
        RetValue.erase(0, pos);
      }
    }
    else
    {
      // delete all 'Signs'
      RetValue.erase(RetValue.begin(), RetValue.end());
    }
  }

  return RetValue;
}
