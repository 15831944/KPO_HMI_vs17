// Copyright (C) 2011 SMS Siemag AG

#include "cCBS_StdInitBase.h"
#include "CSMC_EventLogFrameController.h"

#include "cCBS_StdLog_Task.h"
#include "CTelegram_DataProfile.h"


//##ModelId=426E3B1302BD
CTelegram_DataProfile::~CTelegram_DataProfile()
{
	// ToDo: Add your specialized code here and/or call the base class
}

//##ModelId=426E3B1400A4
CTelegram_DataProfile::CTelegram_DataProfile(const std::string& TelegramID)
: m_TelegramID(TelegramID)
, m_IntervalShortTerm(1)        // inner check interal in seconds
, m_MaxTelegramsShortTerm(10)   // max no of telegram accepted in inner check interal
, m_ActTelegramsShortTerm(0)
, m_IntervalLongTerm(10)        // outer check interal in seconds
, m_MaxTelegramsLongTerm(50)    // max no of telegram accepted in outer check interal
, m_ActTelegramsLongTerm(0)
, m_hasShortTermError(false)
, m_hasLongTermError(false)

{
  CDateTime Now;
  m_StartOfLastIntervalShortTerm = Now;
  m_StartOfLastIntervalLongTerm = Now;

  // accepted will be per default 
  // 10 telegramms in 1 second or 50 telegramms in 10 seconds

  // first preset general values by inifile entries
                                                                                                                                                                                                                                                                                                                                                                                       
  cCBS_StdInitBase::getInstance()->replaceWithEntry("TELEGRAMFREQUENCY", TelegramID, m_MaxTelegramsShortTerm);

}

//##ModelId=426F8E9102C4
bool CTelegram_DataProfile::check()
{
  bool RetValue = true;

  // calculate time difference between "now" and StartOfLastInterval
  CDateTime Now;
  CDeltaTime DeltaTimeShortTerm = CDateTime::subTimes(Now,m_StartOfLastIntervalShortTerm);
  CDeltaTime DeltaTimeLongTerm = CDateTime::subTimes(Now,m_StartOfLastIntervalLongTerm);

  double IntervalShortTerm = DeltaTimeShortTerm.asSeconds();
  double IntervalLongTerm = DeltaTimeLongTerm.asSeconds();

  m_ActTelegramsShortTerm++;
  m_ActTelegramsLongTerm++;
  
  // new IntervalShortTerm starts here if m_IntervalShortTerm has elapsed
  if ( IntervalShortTerm > m_IntervalShortTerm )            
  {
    m_StartOfLastIntervalShortTerm = Now;
    m_ActTelegramsShortTerm        = 0;
    m_hasShortTermError            = false;
  }
  else
  {
    if ( m_ActTelegramsShortTerm > m_MaxTelegramsShortTerm ) // entering critical amount of telegrams per IntervalShortTerm !
    {
      RetValue = false;
      
      if ( !m_hasShortTermError ) // to switch eeventlog only once per interval
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorTelegramFrequency(sMessage,m_TelegramID.c_str(),m_ActTelegramsShortTerm,m_IntervalShortTerm);
      }

      m_hasShortTermError = true;

    }
  }

  // new IntervalLongTerm starts here if m_IntervalLongTerm has elapsed
  if ( IntervalLongTerm > m_IntervalLongTerm )            
  {
    m_StartOfLastIntervalLongTerm = Now;
    m_ActTelegramsLongTerm        = 0;
    m_hasLongTermError            = false;
  }
  else
  {
    if ( m_ActTelegramsLongTerm > m_MaxTelegramsLongTerm ) // entering critical amount of telegrams per IntervalLongTerm !
    {
      RetValue = false;

      if ( !m_hasLongTermError ) // to switch eeventlog only once per interval
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorTelegramFrequency(sMessage,m_TelegramID.c_str(),m_ActTelegramsLongTerm,m_IntervalLongTerm);
      }

      m_hasLongTermError = true;


    }
  }

  return RetValue;
}

//##ModelId=426F9886008F
void CTelegram_DataProfile::log(const std::string& Message, long Level)
{
  cCBS_StdLog_Task::getInstance()->log(Message, Level);
}
