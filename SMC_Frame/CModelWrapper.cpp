// Copyright (C) 2004 SMS Demag AG

#include "iData_Provider_s.hh"
#include "cCBS_StdLog_Task.h"
#include "CEventMessage.h"
#include "cCBS_StdInitBase.h"

#include "CModelWrapper.h"


//##ModelId=4123A06F0296
CModelWrapper::CModelWrapper()
: m_pModelTask(0)
{
}

//##ModelId=4123A07000E8
CModelWrapper::~CModelWrapper()
{
}

//##ModelId=412CBFDB0051
void CModelWrapper::log(const std::string  & Message, long Level)
{
  if ( Level <= getTraceLevel() )
  {
    cCBS_StdLog_Task::getInstance()->log(Message, Level);
  }
}

//##ModelId=418793FB022A
bool CModelWrapper::dispatchEvent(const std::string & SenderName, const std::string  & DestinationName, CEventMessage &Event)
{
  return Event.dispatch(SenderName,DestinationName);
}

//##ModelId=462758FF0093
bool CModelWrapper::dispatchEvent(const std::string & SenderName, std::vector<std::string>  & DestinationName, CEventMessage &Event)
{
  return Event.dispatch(SenderName,DestinationName);
}



//##ModelId=418791F9038D
long CModelWrapper::setToRange(long value, long Default, long Min, long Max)
{
  long RetValue = value; 

  if ( value == DEF::Inv_Long )
  {
    RetValue = Default;
  }
  else
  {
    if ( value > Max )
    {
      RetValue = Max;
    }
    if ( value < Min )
    {
      RetValue = Min;
    }
  }

  return RetValue;
}

//##ModelId=418792E701F0
double CModelWrapper::setToRange(double value, double Default, double Min, double Max)
{
  double RetValue = value; 

  if ( value == DEF::Inv_Double )
  {
    RetValue = Default;
  }
  else
  {
    if ( value > Max )
    {
      RetValue = Max;
    }
    if ( value < Min )
    {
      RetValue = Min;
    }
  }

  return RetValue;
}

//##ModelId=4187931800C0
std::string CModelWrapper::setToRange(const std::string& value, std::string Default)
{
  std::string RetValue = value; 

  if ( value == DEF::Inv_String )
  {
    RetValue = Default;
  }

  return RetValue;
}

//##ModelId=462758FF0075
void CModelWrapper::setpModelTask(CModelTask* pModelTask)
{
  m_pModelTask = pModelTask;
}

long CModelWrapper::getTraceLevel()
{
  return cCBS_StdLog_Task::getInstance()->getTraceLevel();
}
