// Copyright (C) 2004 SMS Demag AG

#include <sstream>

#include "cCBS_StdLog_Task.h"

#include "CSMC_RuntimeController.h"


//##ModelId=42E7439E0305
CSMC_RuntimeController::~CSMC_RuntimeController()
{
  logTime("");
}

//##ModelId=42E7439F00CD
CSMC_RuntimeController::CSMC_RuntimeController(const std::string& FunctionName)
: m_FunctionName(FunctionName)
{
  cCBS_Time::localTime(m_CreationTime);
}



//##ModelId=42E744A5017C
void CSMC_RuntimeController::log(const std::string& Message, long Level)
{
  cCBS_StdLog_Task::getInstance()->log(Message,Level);
}



//##ModelId=42E7819B02A1
void CSMC_RuntimeController::logTime(const std::string& Action)
{
  long LogLevel = 3;
  if (cCBS_StdLog_Task::getInstance()->getTraceLevel() >= LogLevel)
  {
	  // calculate difference time and log
    CBS_LocalTime   Now;
    cCBS_Time::localTime(Now);

    long DiffTime = cCBS_Time::diffTime(Now,m_CreationTime);

    if ( DiffTime > 50 )
    {
      std::stringstream Message;

      Message << "*********  "
              << m_FunctionName 
              << " takes " << DiffTime << " msecs ";

      if ( !Action.empty() )
      {
        Message << " until " << Action ;
      }

      Message << "  *********";
      log(Message.str(),LogLevel);
    }
  }
}

