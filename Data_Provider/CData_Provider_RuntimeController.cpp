// Copyright (C) 2011 SMS Siemag AG

#include <sstream>

#include "CData_Provider_RuntimeController.h"


//##ModelId=42E759D202B8
CData_Provider_RuntimeController::~CData_Provider_RuntimeController()
{
  logTime("");
}

//##ModelId=42E759D202C2
CData_Provider_RuntimeController::CData_Provider_RuntimeController(CData_Provider* pDataProvider, const std::string& FunctionName, const std::string &Key, const std::string &Name)
: m_pData_Provider(pDataProvider)
, m_FunctionName(FunctionName)
, m_Key(Key)
, m_Name(Name)
{
  cCBS_Time::localTime(m_CreationTime);
}

//##ModelId=42E759D202CC
void CData_Provider_RuntimeController::log(const std::string& Message, long Level)
{
  if ( m_pData_Provider )
  {
	  m_pData_Provider->log(Message,Level);
  }
}



//##ModelId=42E77F380346
void CData_Provider_RuntimeController::logTime(const std::string &Action)
{
  if ( m_pData_Provider && m_pData_Provider->getTraceLevel() >= 3 )
  {
	  // calculate difference time and log
    CBS_LocalTime   Now;
    cCBS_Time::localTime(Now);

    long DiffTime = cCBS_Time::diffTime(Now,m_CreationTime);

    if ( DiffTime > 20 )
    {
      std::stringstream Message;

      Message << "******************************************\n"; 
      Message << m_FunctionName 
              << " " << m_Key 
              << " " << m_Name 
              << " takes " << DiffTime << " msecs ";
      if ( !Action.empty() )
      {
        Message << " until " << Action ;
      }

      Message << "\n******************************************"; 
      log(Message.str(),4);
    }
  }
}

