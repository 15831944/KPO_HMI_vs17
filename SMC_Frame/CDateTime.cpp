// Copyright (C) 2004 SMS Demag AG
#include "cCBS_StdLog_Task.h"
#include "CSMC_EventLogFrame.h"
#include "CSMC_EventLogFrameController.h"

#include "cCBS_StdInitBase.h"
#include "CDataConversion.h"

#include <math.h>
#include <time.h>
#include <sys/timeb.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#if defined(WIN32) || defined(_WIN32)
  #include <windows.h>
#endif

#include "CDateTime.h"

CDateTime CDateTime::InvalidDateTime()
{
  CDateTime tm((time_t)0);
  tm.m_DST = false; // to be equal in all seasons
  return tm;
}

sDate CDateTime::InvalidDate()
{
  CDateTime tm((time_t)0);
  tm.m_DST = false; // to be equal in all seasons
  return tm.assDate();
}

//##ModelId=4134373E0244
CDateTime::CDateTime()
{
  // preset date/time to "NOW"

  struct _timeb timeb;    // have a time incl milliseconds
  _ftime (&timeb);        // get it

  struct tm *stm = localtime (&timeb.time);

  // we can not access the configuration for static members of other classes, 
  // because they are initialized before loading the configuration (before main, when loading the object they where compiled into)
  //cCBS_StdInitBase * pCBS_StdInitBase = pCBS_StdInitBase = cCBS_StdInitBase::getInstance();

  //resetTime();            // resetting internal time data

  if (stm) // localtime returns 0 on fault
  {
    m_Year        = stm->tm_year+1900;
    m_Month       = stm->tm_mon +1;
    m_Day         = stm->tm_mday;
    m_Hour        = stm->tm_hour;
    m_Minute      = stm->tm_min;
    m_Second      = stm->tm_sec;
    m_MilliSecond = timeb.millitm;

    m_DST = (stm->tm_isdst>0);   // is <0 if there is no DST (e.g. China), otherwise ==0 or >0.

    m_IsDST_Region = isDST_Region();
    //m_UseDST = m_IsDST_Region;
    //pCBS_StdInitBase->replaceWithEntry("DATABASE","useDST",m_UseDST);
    
    isValidDateTime();
  }
  else
  {
    // should not happen but...
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorHandlingDateTime(sMessage, "CDateTime::CDateTime() - localtime not usable");
  }
}


//the copy constructor
CDateTime::CDateTime(const CDateTime& From)
: CTimeBase(From)
{
  m_DisplayFormat = From.m_DisplayFormat;
  m_DST = From.m_DST; 
  m_IsDST_Region = From.m_IsDST_Region;
}

//the assignment operator
CDateTime& CDateTime::operator=(const CDateTime& Value)
{
  if (this != &Value) 
  {
    CTimeBase::operator=(Value);

    m_DisplayFormat = Value.m_DisplayFormat;
    m_DST = Value.m_DST; 
    m_IsDST_Region = Value.m_IsDST_Region;
  }

  return *this;
}

bool CDateTime::adjDST (CDeltaTime deltaT)
{
  CDateTime Now;
  if( fabs(subTimes(Now,*this).asSeconds()) > fabs(deltaT.asSeconds()) )
  {
    m_DST = !m_DST; // if the difference is to big we change the dst flag
  }
  return false;
}

//##ModelId=41344A2600AA
CDateTime::CDateTime(CDeltaTime &timeOffset)
{
  *this = CDateTime();    // start with "NOW"
  addTime (timeOffset);   // add/subtract Delta

  isValidDateTime();
}
// Constructs a DateTime and presets with the given date/time string, either with the
// default input format or with the optional user's input format.
//##ModelId=41370B8C03CE
CDateTime::CDateTime (const std::string & dateTimeString, const std::string userInputFormat[])
{
  time_t        timeT         = 0;
  unsigned long milliseconds  = 0;
  struct tm *stm              = 0;

  resetTime();            // resetting internal time data

  //cCBS_StdInitBase * pCBS_StdInitBase = pCBS_StdInitBase = cCBS_StdInitBase::getInstance();

  if ( m_DisplayFormat.getInput (timeT, milliseconds, CDateTimeFormat::StandardFormat, 
                                 dateTimeString, userInputFormat) ) 
  {
    stm = localtime (&timeT);
  }  // Start GEPA 18.6.2005 next else if added
  else if ( m_DisplayFormat.getInput (timeT, milliseconds, CDateTimeFormat::DataTransferFormat, 
                                 dateTimeString, userInputFormat) ) 
  {
    stm = localtime (&timeT);
  }// End GEPA 18.6.2005 next elseif added

  if (stm) // localtime returns 0 on fault
  {
    m_Year        = stm->tm_year+1900;
    m_Month       = stm->tm_mon +1;
    m_Day         = stm->tm_mday;
    m_Hour        = stm->tm_hour;
    m_Minute      = stm->tm_min;
    m_Second      = stm->tm_sec;
    m_MilliSecond = milliseconds;
    m_DST = (stm->tm_isdst>0);   // is <0 if there is no DST (e.g. China), otherwise ==0 or >0.

    m_IsDST_Region = isDST_Region();
    //m_UseDST = m_IsDST_Region;
    //pCBS_StdInitBase->replaceWithEntry("DATABASE","useDST",m_UseDST);
    
    isValidDateTime();
  }
  else
  {
    // should not happen but...
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorHandlingDateTime(sMessage, "CDateTime::CDateTime (const std::string & dateTimeString, const std::string userInputFormat[] - localtime not usable");
  }
}

// This constructor takes a Date String AND a time string and optionally an array for the 
// input Format. If the Format is omitted, the default DT input format is applied.
// 
//##ModelId=41370B8D000F
CDateTime::CDateTime (const std::string & dateString, const std::string & timeString, const std::string userInputFormat[])
{
  time_t        timeT         = 0;
  unsigned long milliseconds  = 0;
  struct tm *stm              = 0;

  //cCBS_StdInitBase * pCBS_StdInitBase = pCBS_StdInitBase = cCBS_StdInitBase::getInstance();

  resetTime();            // resetting internal time data

  if ( m_DisplayFormat.getInput (timeT, milliseconds, CDateTimeFormat::DataTransferFormat, 
                                 dateString+timeString, userInputFormat) ) 
  {
    stm = localtime (&timeT);
  }

  if   (stm) // localtime returns 0 on fault
  {
    m_Year        = stm->tm_year+1900;
    m_Month       = stm->tm_mon +1;
    m_Day         = stm->tm_mday;
    m_Hour        = stm->tm_hour;
    m_Minute      = stm->tm_min;
    m_Second      = stm->tm_sec;
    m_MilliSecond = milliseconds;
    m_DST = (stm->tm_isdst>0);   // is <0 if there is no DST (e.g. China), otherwise ==0 or >0.

    m_IsDST_Region = isDST_Region();
    //m_UseDST = m_IsDST_Region;
    //pCBS_StdInitBase->replaceWithEntry("DATABASE","useDST",m_UseDST);

    isValidDateTime();
  }
  else
  {
    // should not happen but...
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorHandlingDateTime(sMessage, "CDateTime::CDateTime (const std::string & dateString, const std::string & timeString, const std::string userInputFormat[]) - localtime not usable");
  }
}

//##ModelId=4161665300B6
CDateTime::CDateTime (time_t timeT)
{
  m_IsDST_Region = isDST_Region();

  SetTime (timeT);

  isValidDateTime();
}

CDateTime::CDateTime (sDate &DateTime)
{
  m_IsDST_Region = isDST_Region();

  SetTime(DateTime);

  // prevent usage of invalid CDateTime object if CORBA data, e.g. given from external system containg data like "-1"
  if ( !isValidDateTime() )
  {
    SetTime(InvalidDate());
  }
}

//##ModelId=4134374B0062
bool CDateTime::SetTime(const std::string & dateTimeString, const std::string  privateFormat[])
{
  *this = CDateTime (dateTimeString, privateFormat);
  return true;
}

//##ModelId=413437580056
bool CDateTime::SetTime(const sDate &DateTime)
{
  bool retval=true;
  m_Year        = DateTime.year;
  m_Month       = DateTime.month;
  m_Day         = DateTime.day;
  m_Hour        = DateTime.hour;
  m_Minute      = DateTime.minute;
  m_Second      = DateTime.second;
  m_MilliSecond = DateTime.msec;
  m_DST         = DateTime.dstFlag;

  return retval;
}

//##ModelId=41344648026A
bool CDateTime::SetTime(time_t t)
{
  bool retval=true;
  struct tm *stm = localtime (&t);
  if (stm)    // localtime returns NULL if t is before 1970!
  {
    m_Year        = stm->tm_year+1900;
    m_Month       = stm->tm_mon +1;
    m_Day         = stm->tm_mday;
    m_Hour        = stm->tm_hour;
    m_Minute      = stm->tm_min;
    m_Second      = stm->tm_sec;
    m_MilliSecond = 0;
    m_DST         = stm->tm_isdst>0;
  }
  else
  {
    retval = false; // signal fault
  }
  return (retval);
}

//##ModelId=413437FD0373
std::string CDateTime::asString() const
{
  std::string retval = m_DisplayFormat.formatATime(asTime_T(), m_MilliSecond);
  return retval;
}

//##ModelId=416D12500366
std::string CDateTime::toDBString() const
{
  std::stringstream ss;
  ss.fill('0');
  ss << std::setw(4) << m_Year << '-' << std::setw(2) << m_Month << '-' << std::setw(2) << m_Day << ' '
     << std::setw(2) << m_Hour;

  if (m_IsDST_Region)
  {
    if (m_DST)
    {
      ss << 'S';
    }
    else
    {
      ss << 'W';
    }
  }
  else
  {
    // suggest ":" in areas where there is no DST
    ss << ':';
    //if ( m_IsDST_Region
    //  && isAmbiguous())
    //{
    //  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    //  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    //  pEventLog->EL_ErrorHandlingDateTime(sMessage, "Loosing crucial information because of missing DST flag in DB.");
    //}
  }

  ss << std::setw(2) << m_Minute << ":" << std::setw(2) << m_Second << ',' << std::setw(3) << m_MilliSecond;
  return ss.str();
}

//##ModelId=416E8F4602F1
void CDateTime::fromDBString(const std::string &value)
{
  std::istringstream is(value);
  if (value != DEF::Inv_String)
  {
    char c, DST;
    is >> std::setw(4) >>  m_Year  >> std::setw(1) >> c // '-'
      >> std::setw(2) >> m_Month  >> std::setw(1) >> c // '-'
      >> std::setw(2) >> m_Day    >> std::setw(2) >> m_Hour >> std::setw(1) >> DST
      >> std::setw(2) >> m_Minute >> std::setw(1) >> c // ':'
      >> std::setw(2) >> m_Second >> std::setw(1) >> c // ','
      >> std::setw(3) >> m_MilliSecond;

    switch (DST){
      case 'W':
        m_DST = false; break;
      case 'S':
        m_DST = true; break;
      case ':':
        if (!m_IsDST_Region)
        {
          m_DST = false;
        }
        else if (isAmbiguous())
        {
          m_DST = false;
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorHandlingDateTime(sMessage, "The time read from the DB is ambiguous because of missing DST falg.");
        }
        else
        {
          struct tm z1;

          memset(&z1, 0, sizeof(z1));

          z1.tm_sec = m_Second;
          z1.tm_min = m_Minute;    
          z1.tm_hour = m_Hour;     
          z1.tm_mday = m_Day;     
          z1.tm_mon = m_Month - 1;     
          z1.tm_year = m_Year - 1900;     
          z1.tm_isdst = 0;          

          mktime(&z1);

          if (0 < z1.tm_isdst)
          {
            m_DST = true;
          }
          else
          {
            m_DST = false;
          }
        }
        break;
    }
  }//if (value != DEF::Inv_String)
  else
  {
    resetTime();
  }
 }

//##ModelId=4134384102B2
std::string CDateTime::asString(const std::string & Format)
{
  // temporarily set Display Format to Argument Format, then do the formatting
  // and reset to previous display Format. (because of this the methodf is not const)
  std::string tmpFormat = m_DisplayFormat.getFormat();
  m_DisplayFormat.setFormat (Format);
  std::string retval = m_DisplayFormat.formatATime(asTime_T(), m_MilliSecond);
  m_DisplayFormat.setFormat(tmpFormat);

  return retval;
}

//##ModelId=41343832017A
sDate CDateTime::assDate() const
{
  sDate retval;

  retval.year =(CORBA::UShort)    m_Year;
  retval.month =(CORBA::UShort)   m_Month;
  retval.day = (CORBA::UShort)    m_Day;
  retval.hour = (CORBA::UShort)   m_Hour;
  retval.minute = (CORBA::UShort) m_Minute;
  retval.second =(CORBA::UShort)  m_Second;
  retval.msec = (CORBA::UShort)   m_MilliSecond;
  retval.dstFlag = m_DST;          
  return retval;
}

//##ModelId=413446D4025F
time_t CDateTime::asTime_T() const
{
  struct tm xtm;
  struct tm *stm = &xtm;

  stm->tm_year = m_Year   - 1900;
  stm->tm_mon  = m_Month  - 1;
  stm->tm_mday = m_Day;
  stm->tm_hour = m_Hour;
  stm->tm_min = m_Minute;
  stm->tm_sec = m_Second;

  // in case of using DST mktime() adds 1 hour to actual time (m_Hour)
  // for example where time is read from DB without S/W information.
  //stm->tm_isdst = m_DST ? 1:0;
  stm->tm_isdst = CDateTime().get_DST() ? 1:0;

  time_t retval = mktime (stm);                     // returns -1 on error (date before 1970 or after 2038)
  if (retval == (time_t) (-1))  retval=0;         // avoid desaster
  return retval;
}

//##ModelId=41F763DA02F9
long CDateTime::getWeekNo() const
{
  // *****************************************************************
  // Basically, ISO 8601 states that week #1 of a year is the one
  // containing at least 4 days of the new year (Majority)
  // Furthermore, the week begins on MONDAY.
  // Consequently, Week #1 of each year is the week that contains the
  // 1st Thursday of that year (because Thursday...Sunday is 4 days)
  // I present here an alternate calculation for the case if the
  // week begins on Sunday: then week #1 is the one with the 1st 
  // Wednesday.
  // This code is prepared for an alternate definition of the week
  // begin (namely on Sunday, as it was in Germany before 1976).
  // Calculation method:
  // Estimate date of Thursday this week (on Sundays: previous week) 
  // Remark: this must be Wednesday if week is defined to start on 
  // Sundays
  // Count number of days since 1-Jan, divide by 7 and add 1
  // *****************************************************************

  time_t    t      = asTime_T();
  struct tm *ts    = localtime(&t);

#if !defined (WEEK_BEGINS_ON_SUNDAY)  // i.e., YES because it doesn't
  // On Sunday, hop to previous Thursday (+4-day-7), otherwise hop this week's thursday(+4 day==0).
  ts->tm_mday = ts->tm_mday + 4 - (ts->tm_wday > 0 ? ts->tm_wday : 7);
#else   // just in case... in other countries things might be different
  // This case is simpler because of tm_mday's definition: hop to this week's Wednesday (+3-day)
  ts->tm_mday = ts->tm_mday + 3 - ts->tm_wday;
#endif

  t  = mktime(ts);
  ts = localtime(&t);

  return ts->tm_yday/7 + 1;
}

// returns days since sunday [0...6]
long CDateTime::getDayOfWeek() const
{
  time_t    t      = asTime_T();
  struct tm *ts    = localtime(&t);

  return ts->tm_wday;
}



//##ModelId=41343853002D
bool CDateTime::addTime(CDeltaTime & deltaT)
{
  // add Y,m,d,h,min,s,ms. Let OS correct for e.g. 31-Feb...
  
  bool retval=true;   // assume success

  m_Year        += deltaT.m_Year        ;
  m_Month       += deltaT.m_Month       ;
  m_Day         += deltaT.m_Day         ;
  m_Hour        += deltaT.m_Hour        ;
  m_Minute      += deltaT.m_Minute      ;
  m_Second      += deltaT.m_Second      ;
  
  long millitm = m_MilliSecond + deltaT.m_MilliSecond ;

                                      // ------------ nSecs = X in all cases ----------------------------------
  if   (millitm > 1000)               //  1001                      1999                    2000
  {                                   // t should be t+X+1.001s     t+X+1.999s              t+X+2.000s
    long int dms = millitm/1000;      //  1                         1                       2  
    millitm %=1000;                   //  1                         999                     0
    m_Second +=dms;                   // X+1                        X+1                     X+2
  }                                   // total t=t+X+1s+1ms OK      t=t+X+1s+999ms OK       t=t+2s+0ms OK
                                      //
  else if (millitm <0)                // e.g. -------------- nSecs=X in all 3 cases ------------------------ 
  {                                   // -2400                      -1                      -1000           -999
                                      // t should be  t+X-2.400s    t+X-0.001 s             t+X -1.000 s    t+X-0.999 s
    long dms = (millitm-999)/1000;    // -3                         -1                      -1              -1
    millitm += (1000*dms);            // +600                       +999                    0               +1
    m_Second +=dms;                   // X-3                        X-1                     X-1             X-1
  }                                   // total: t=t+X-3s+600ms      t+X-2s+999ms            t+X-1s 0ms      t+X-1s+1ms

  m_MilliSecond = millitm;   // set normalized value
  struct tm  xtm;
  struct tm *stm = &xtm;

  stm->tm_year = m_Year   - 1900;
  stm->tm_mon  = m_Month  - 1;
  stm->tm_mday = m_Day;
  stm->tm_hour = m_Hour;
  stm->tm_min = m_Minute;
  stm->tm_sec = m_Second;
  stm->tm_isdst = m_DST ? 1:0;

  if   ( mktime (stm) != (time_t) (-1))  // mktime returns (time_t) -1 on error
  {
    m_Year        = stm->tm_year+1900;
    m_Month       = stm->tm_mon +1;
    m_Day         = stm->tm_mday;
    m_Hour        = stm->tm_hour;
    m_Minute      = stm->tm_min;
    m_Second      = stm->tm_sec;
    m_DST         = (stm->tm_isdst>0);
  }
  else
  {
    retval=false;
  }
  return retval;
}

//##ModelId=4134472200D0
bool CDateTime::addTime(long nSeconds, long nMilliSeconds)
{
  // create a Delta Time from arguments and do the calculation with that.
  return addTime (CDeltaTime(nSeconds,nMilliSeconds));
}

//##ModelId=4134AF2801C7
bool CDateTime::addTime (double dSeconds)
{
  long lSeconds = (long) dSeconds;   // cuts off fractionaal part
  long milliSeconds =1000 * (long) (dSeconds-lSeconds);

  return addTime (lSeconds, milliSeconds);
}
//##ModelId=41343F8802A8
CDeltaTime CDateTime::subTimes(const CDateTime & T1, const CDateTime & T2)
{
  CDeltaTime dT( long (T1.asTime_T()-T2.asTime_T()) );
 
  dT.m_MilliSecond = T1.m_MilliSecond -  T2.m_MilliSecond ;   // can be <0, but OK.
  return dT;
}

//##ModelId=4134391A01B8
bool CDateTime::setDisplayFormat(const std::string & newFormat)
{
  return m_DisplayFormat.setFormat(newFormat);
}

//##ModelId=413439E1023E
CDateTime::~CDateTime()
{
}

//##ModelId=41345DBF00A4
CDateTime CDateTime::addTimes(const CDateTime & T, const CDeltaTime & dT)
{
  CDateTime result(T);      // start with a straight copy, then add deltas and normalize

  result.m_Year        += dT.m_Year;       
  result.m_Month       += dT.m_Month;      
  result.m_Day         += dT.m_Day   ;     
  result.m_Hour        += dT.m_Hour   ;    
  result.m_Minute      += dT.m_Minute  ;   
  result.m_Second      += dT.m_Second   ;  
  result.m_MilliSecond += dT.m_MilliSecond;

  result.addTime(0,0);      // not null operation: will correct range of minutes and hours and such

  return result;
}

//##ModelId=41345E2903C7
CDateTime CDateTime::addTimes(const CDeltaTime & dT, const CDateTime & T)
{
  return addTimes (T,dT);
}

//##ModelId=415A6689022A
bool CDateTime::operator <<(const std::string& dateTime)
{
 return SetTime(dateTime);
}

//##ModelId=415A63AB012B
bool CDateTime::operator <<(time_t t)
{
  return SetTime(t);
}

//##ModelId=415A66BF0065
bool CDateTime::operator <<(sDate &dateTime)
{
 return SetTime(dateTime);
}

// flush contents into an OStream using standard or preset formatting
std::ostream & operator<< (std::ostream &os,  CDateTime &dateTime)
{
  os << dateTime.asString();
  return os;
}

//##ModelId=415970C60196
bool CDateTime::SetTime(DB_CLASSLIB_DATE const *pDateTime)
{
  m_Year        = pDateTime->year;
  m_Month       = pDateTime->month;
  m_Day         = pDateTime->day;
  m_Hour        = pDateTime->hour;
  m_Minute      = pDateTime->minute;
  m_Second      = pDateTime->second;
  m_MilliSecond = pDateTime->msecond;
 
  // Construct daylight saving from original time values
  CDateTime tmp = *this;
  tmp.addTime(0,0);
  m_DST = tmp.get_DST();
  return this->addTime(0,0);   // normalization
}

//##ModelId=416D103C00BE
bool CDateTime::get_DST()const
{
  return m_DST;
}

//##ModelId=415A7535019C
DB_CLASSLIB_DATE CDateTime::asDB_CLASSLIB_DATE() const
{
  DB_CLASSLIB_DATE D;

  D.year    = (short int)m_Year;
  D.month   = (short int)m_Month;
  D.day     = (short int)m_Day;
  D.hour    = (short int)m_Hour;
  D.minute  = (short int)m_Minute;
  D.second  = (short int)m_Second;
  D.msecond = (int)m_MilliSecond;
  return D;
}

//##ModelId=416168DF0311
bool CDateTime::operator!=(const CDateTime& rhs) const
{
  return !operator ==(rhs);
}

//##ModelId=416168E30123
bool CDateTime::operator==(const CDateTime& rhs) const
{
  // Normalization is wrong on this place
  // because this operation modifys the time
  // dependent on system dst.
  // It is not possible to to compare winter times
  // in summer
  //CDateTime d(rhs);
  //d.addTime(0,0);   // normalization
  //return CTimeBase::operator ==(d) && m_DST == d.m_DST;
  return CTimeBase::operator ==(rhs) && m_DST == rhs.m_DST;
}

bool CDateTime::operator>=(const CDateTime& rhs) const
{
  return operator > (rhs) || operator == (rhs);
}

bool CDateTime::operator<=(const CDateTime& rhs) const
{
  return operator < (rhs) || operator == (rhs);
}

bool CDateTime::operator>(const CDateTime& rhs) const
{
  return asTime_T() > rhs.asTime_T();
}

bool CDateTime::operator<(const CDateTime& rhs) const
{
  return asTime_T() < rhs.asTime_T();
}




//##ModelId=44FE9C3000A5
void CDateTime::resetTime()
{
  // reset internal time structure
  SetTime ((time_t)0);
}

// Create me from data as received (CORBA Any)
// Any consists of DEF::seqLong with lenght of 8 !
CDateTime::CDateTime(CORBA::Any seqAny)
{
  // preset internal time first !
  resetTime();

  //is DST region?
  m_IsDST_Region = isDST_Region();

  // extract seqLong from any frist 
  DEF::seqLong *TimeSeq;
  if (seqAny >>= TimeSeq)
  {
    if (TimeSeq->length() == 8)
    {
      m_Year        = (*TimeSeq)[0]; // year
      m_Month       = (*TimeSeq)[1];
      m_Day         = (*TimeSeq)[2];
      m_Hour        = (*TimeSeq)[3];
      m_Minute      = (*TimeSeq)[4];
      m_Second      = (*TimeSeq)[5];
      m_MilliSecond = (*TimeSeq)[6];
      m_DST         = ((*TimeSeq)[7] == 1 ) ? true:false;

      // prevent usage of invalid CDateTime object if CORBA data, e.g. given from external system containg data like "-1"
      if ( !isValidDateTime() )
      {
        SetTime(InvalidDate());
      }
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingDateTime(sMessage, "CDateTime::CDateTime(CORBA::Any seqAny) - wrong sequence lenght of CORBA::Any");
    }
  }
 
}

// Create me from data as received via DT (8 integers)
//##ModelId=44FE9C3000A6
CDateTime::CDateTime (long year, long month,  long day, 
                      long hour, long minute, long second, long millisec, long isDST)
{
  //////////////////////////////////////////////////////////////////////////////
  // This is due to a design flow in Data Transfer. They send 8 integers
  // (from year down to summer/wintertime flag ), not taking into account that something like
  // DST exists. We use a heuristics to decide whether or not the given
  // date/time is in Summer or Winter.
  //////////////////////////////////////////////////////////////////////////////

  // SET INTERNALS TO ARGUMENT VALUES
  m_Year        = year;
  m_Month       = month;
  m_Day         = day;
  m_Hour        = hour;
  m_Minute      = minute;
  m_Second      = second;
  m_MilliSecond = millisec ;
  m_DST         = (isDST == 1) ? true:false;
  
  // Utilize that mktime corrects input struct tm.

  struct tm xtm;
  struct tm *stm = &xtm;

  stm->tm_year = m_Year   - 1900;
  stm->tm_mon  = m_Month  - 1;
  stm->tm_mday = m_Day;
  stm->tm_hour = m_Hour;
  stm->tm_min = m_Minute;
  stm->tm_sec = m_Second;

  stm->tm_isdst = m_DST ? 1:0; 

  // following call to mktime() can apply corrections to DST flag and/or time string.
  // 
  if  ( mktime (stm) >=0)
  {
    m_Year        = stm->tm_year + 1900;
    m_Month       = stm->tm_mon + 1;
    m_Day         = stm->tm_mday;
    m_Hour        = stm->tm_hour;
    m_Minute      = stm->tm_min;
    m_Second      = stm->tm_sec;
    m_DST         = (stm->tm_isdst == 1) ? true:false;

    isValidDateTime();
  }
  else
  {
    // nothing to do, input date/time probably wrong,
    // result will not be better.
    ;            // shyce
  }

  //need to set the indication wether or not we are in a DST region
  m_IsDST_Region = isDST_Region();
}


//##ModelId=44FE9C3000CD
std::string CDateTime::asSMString ()
{
  char *format;
  if   (m_DST )                         // DST in effect
    format = "%Y-%m-%d %HS%M:%S.***";   
  else                                  // DST not in effect
    format = "%Y-%m-%d %HW%M:%S.***";   

 return asString (format);

}

CORBA::Any CDateTime::asCORBAAny()
{
  DEF::seqLong lDateTime;
  lDateTime.length(8);
  lDateTime[0] = m_Year;
  lDateTime[1] = m_Month;
  lDateTime[2] = m_Day;
  lDateTime[3] = m_Hour;
  lDateTime[4] = m_Minute;
  lDateTime[5] = m_Second;
  lDateTime[6] = m_MilliSecond;
  lDateTime[7] = m_DST;

  CORBA::Any anyDateTime;
  anyDateTime <<=  lDateTime;
  return anyDateTime;	
};

void CDateTime::fromCORBAAny(CORBA::Any anyTime)
{
  DEF::seqLong  *slongdatetime;
  long  ldatetime[8];
  if ( (anyTime >>= slongdatetime) )
  {
    if (slongdatetime->length() == 8)
    {
      for ( int i = 0; i < 8; i++ )
      {
        ldatetime[i] = (*slongdatetime)[i];
      }
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingDateTime(sMessage, "void CDateTime::fromCORBAAny(CORBA::Any anyTime) - wrong sequence lenght of CORBA::Any");
    }
  }

  m_Year        = ldatetime[0];
  m_Month       = ldatetime[1];
  m_Day         = ldatetime[2];
  m_Hour        = ldatetime[3];
  m_Minute      = ldatetime[4];
  m_Second      = ldatetime[5];
  m_MilliSecond = ldatetime[6];
  m_DST         = (ldatetime[7] == 1) ? true:false;
}

void CDateTime::UTCtoLocalTime(long TimeZone /* = 0 */)
{
  // **********************************
  // regard timezone and DST 
  // DST is between the last sunday of march, 2:00h and the last sunday of october, 3:00 

  CDateTime ActTime(asTime_T());  // copy actual time info
  CDateTime BeginDST(asTime_T()); // copy actual time info
  CDateTime EndDST(asTime_T());   // copy actual time info

  BeginDST.setMonth(3);
  BeginDST.setDay( BeginDST.getLastDayOfWeek(0) );
  BeginDST.setHour(2);
  BeginDST.setMinute(0);
  BeginDST.setSecond(0);
  BeginDST.setMilliSecond(0);

  cCBS_StdLog_Task::getInstance()->log("DST starts at "+ BeginDST.asString(), 4);

  EndDST.setMonth(10);
  EndDST.setDay( EndDST.getLastDayOfWeek(0) );
  EndDST.setHour(3);
  EndDST.setMinute(0);
  EndDST.setSecond(0);
  EndDST.setMilliSecond(0);

  cCBS_StdLog_Task::getInstance()->log("DST ends at "+ EndDST.asString(), 4);

  if ( BeginDST <= ActTime && ActTime <= EndDST )
  {
    cCBS_StdLog_Task::getInstance()->log("Actual time is DST with "+ ActTime.asString(), 4);

    addTime(3600.);
  }

  addTime(TimeZone * 3600);

  return;
}

// get e.g. last sunday in october, DayOfWeek according to tm struct 0 = Sunday
long CDateTime::getLastDayOfWeek(long DayOfWeek)
{
  CDateTime ActDate(asTime_T()); // copy actual time info

  long LastDayOfWeek = 1;

  ActDate.setDay(1);

  do 
  {
    if ( ActDate.getDayOfWeek() == DayOfWeek )
    {
      LastDayOfWeek = max(LastDayOfWeek,ActDate.getDay());
    }

    ActDate.addTime(24 * 60 * 60 , 0 );

  }
  while ( ActDate.getMonth() == getMonth() );

  return LastDayOfWeek;
}

CDeltaTime CDateTime::subTime(const CDateTime& RefTime)
{
  CDeltaTime dT( long (this->asTime_T()-RefTime.asTime_T()) );
 
  dT.m_MilliSecond = this->m_MilliSecond -  RefTime.m_MilliSecond ;   // can be <0, but OK.
  return dT;
}

bool CDateTime::isValidDateTime()
{
  bool RetValue = true;

  if ( getYear()    < 1970 ||   getYear()   > 2999  ||
       getMonth()   < 1    ||   getMonth()  > 12    ||
       getDay()     < 0    ||   getDay()    > 31    ||
       getHour()    < 0    ||   getHour()   > 24    ||
       getMinute()  < 0    ||   getMinute() > 59    ||
       getSecond()  < 0    ||   getSecond() > 59    )
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorHandlingDateTime(sMessage, "bool CDateTime::isValidDateTime() - date out of valid range (1970 - 2999)");

    RetValue = false;
  }

  return RetValue;
}

bool CDateTime::isAmbiguous() const
{
  bool RetValue = false;

  struct tm z1;
  struct tm z2;

  memset(&z1, 0, sizeof(z1));
  memset(&z2, 0, sizeof(z2));

  z1.tm_sec = m_Second;
  z1.tm_min = m_Minute;    
  z1.tm_hour = m_Hour;     
  z1.tm_mday = m_Day;     
  z1.tm_mon = m_Month - 1;     
  z1.tm_year = m_Year - 1900;     
  z1.tm_isdst = 0;     

  z2.tm_sec = m_Second;
  z2.tm_min = m_Minute;    
  z2.tm_hour = m_Hour;     
  z2.tm_mday = m_Day;     
  z2.tm_mon = m_Month - 1;     
  z2.tm_year = m_Year - 1900;     
  z2.tm_isdst = 1;  


  mktime(&z1); 
  mktime(&z2); 

  if ( 0 == z1.tm_isdst
    && 1 == z2.tm_isdst )
  {
    RetValue = true;
  }

  return RetValue;
}//bool CDateTime::isAmbiguous() const

bool CDateTime::isDST_Region() const
{
  bool RetValue = true;

  //at the moment only an implementation for windows is available
#if defined(WIN32) || defined(_WIN32)
  TIME_ZONE_INFORMATION tzinfo;
  DWORD dwRet;

  dwRet = GetTimeZoneInformation(&tzinfo);

  if ( TIME_ZONE_ID_DAYLIGHT == dwRet )
  {
    RetValue = true;
  }
  else if (TIME_ZONE_ID_STANDARD == dwRet )
  {
    //check if there is date for the switch
    if (0 == tzinfo.DaylightDate.wMonth) //month == zero means no DST in this region
    {
      RetValue = false;
    }
    else
    {
      RetValue = true;
    }
  }
  else if (TIME_ZONE_ID_INVALID == dwRet)
  {
    RetValue = false;

    std::string Description = "bool CDateTime::isDST_Region() - error retrieving time zone information";
    Description += CDataConversion::LongToString(GetLastError());
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorHandlingDateTime(sMessage, Description.c_str() );
  }
  else
  {
    RetValue = false;
  }
#endif  

  return RetValue;
}//bool CDateTime::isDST_Region() const