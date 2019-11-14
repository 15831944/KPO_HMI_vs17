// Copyright (C) 2004 SMS Demag AG

#include "cCBS_StdLog_Task.h"
#include "CDateTimeFormat.h"
#include <string.h>
#include <iostream>
#include "CDateTime.h"
// static data members
//
//##ModelId=41357EBC00BC
const std::string CDateTimeFormat::m_DefaultFormatString = std::string ("%d-%m-%Y %H:%M:%S.***");
//##ModelId=41370B8C0159
const std::string CDateTimeFormat::m_DefaultDTInputStrings[8] =   // As it comes from the DT Interfaces
{// YYYYMMDDhhmmssxxx
   "______%2d",         // DAY
   "____%2d",           // MONTH
   "%4d",               // YEAR
   "________%2d",       // HOUR
   "__________%2d",     // Minute
   "____________%2d",   // Second
   "______________%3d", // MilliSecond
   ""                   // DST
};
//##ModelId=41370B8C013B
const std::string CDateTimeFormat::m_DefaultInputStrings[8] =    // AS it is displayed everywhere
{ // DD-MM-YYYY HH:MM:SS.mmm
    "%2d",
    "___%2d",
    "______%4d",
    "___________%2d",
    "______________%2d",
    "_________________%2d",
    "____________________%3d",
    ""
};

//##ModelId=41357C710036
std::string CDateTimeFormat::getFormat()  const
{
  std::string returnValue; 

  return returnValue;
}

//##ModelId=41357C8F0061
bool CDateTimeFormat::setFormat( std::string newFormat)
{
	// TODO: Add your specialized code here.
  if (newFormat != std::string (""))    // some format set?
  	m_CurrentFormatString = newFormat;
  else
  {
    m_CurrentFormatString = m_DefaultFormatString;
  }
  return true;
}

//##ModelId=41357DA7008B
std::string CDateTimeFormat::formatATime(time_t timeT, unsigned long milliSeconds) const
{
  std::string returnValue;
  char formattedTime[255];

  struct tm *ptm = localtime (&timeT);
 
  size_t filled = strftime (formattedTime, sizeof(formattedTime), m_CurrentFormatString.c_str(), ptm);

  milliSeconds %= 1000;   // make sure 0<=milliseconds<1000 
  char * pc;
  char mils[4];
  bool done=false;
  while (!done)       // replace _ALL_ "*"'s with fractions of a second
  {
    if   (pc = strstr (formattedTime, "***"))
    {
      sprintf (mils, "%3.3d", milliSeconds);  // replace "***" by "126"
      memcpy (pc, mils, 3);                   // beware of '\0' from sprintf!
    }
    else if (pc = strstr (formattedTime, "**"))
    {
      sprintf (mils, "%2.2d", (long) (0.5+milliSeconds/10.));   // rounded
      memcpy (pc, mils, 2);
    }
    else if (pc = strchr (formattedTime, '*')) 
    {
      sprintf (mils, "%1d", (long) (0.5+milliSeconds/100.));    // rounded
      memcpy (pc, mils, 1);
    }
    else
    {
      done=true;
    }
  }
  returnValue = std::string (formattedTime);
  return returnValue;
}



//##ModelId=41370B8B0387
CDateTimeFormat::CDateTimeFormat()
{
	m_CurrentFormatString = m_DefaultFormatString;

  m_CurrentInputFormat_d = m_DefaultInputStrings[0];   // INPUT FORMAT for DAY
  m_CurrentInputFormat_m = m_DefaultInputStrings[1];   //                  MONTH
  m_CurrentInputFormat_y = m_DefaultInputStrings[2];   //                  YEAR
  m_CurrentInputFormat_h = m_DefaultInputStrings[3];   //                  HOUR
  m_CurrentInputFormat_min = m_DefaultInputStrings[4]; //                  Minute
  m_CurrentInputFormat_s   = m_DefaultInputStrings[5]; //                  Second
  m_CurrentInputFormat_ms  = m_DefaultInputStrings[6]; //                  MilliSecond
  m_CurrentInputFormat_DST = m_DefaultInputStrings[7]; //                  DST

  m_CurrentDTInputFormat_d = m_DefaultDTInputStrings[0];   // INPUT FORMAT for DAY
  m_CurrentDTInputFormat_m = m_DefaultDTInputStrings[1];   //                  MONTH
  m_CurrentDTInputFormat_y = m_DefaultDTInputStrings[2];   //                  YEAR
  m_CurrentDTInputFormat_h = m_DefaultDTInputStrings[3];   //                  HOUR
  m_CurrentDTInputFormat_min = m_DefaultDTInputStrings[4]; //                  Minute
  m_CurrentDTInputFormat_s   = m_DefaultDTInputStrings[5]; //                  Second
  m_CurrentDTInputFormat_ms  = m_DefaultDTInputStrings[6]; //                  MilliSecond
  m_CurrentDTInputFormat_DST = m_DefaultDTInputStrings[7]; //                  DST

}

namespace LocalHere
{
  int skipc (const char* c)
  {
    int ii=0;
    while (*c != '%') {c++;ii++;}
    return ii;
  }

}


//##ModelId=41370B8B03A5
CDateTimeFormat::~CDateTimeFormat()
{
	// TODO: Add your specialized code here.
}


//##ModelId=41370B8B03B0
bool CDateTimeFormat::getInput (time_t &timeT, 
                                unsigned long &milliSeconds, 
                                FormatTypes ft, 
                                const std::string &inputDateTime,
                                const std::string userFormat[],
                                const std::string userFormatDST)
{
  bool retval=true;   // assume success

  struct tm xtm;

  if   (ft == DataTransferFormat && (0 ==userFormat) )
  {
    if   (m_CurrentDTInputFormat_d != "" 
      && EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(m_CurrentDTInputFormat_d.c_str())
      , m_CurrentDTInputFormat_d.c_str()+LocalHere::skipc(m_CurrentDTInputFormat_d.c_str())
                       , &xtm.tm_mday))
    {
      retval=false;
      xtm.tm_mday=0;
    }
    if   (m_CurrentDTInputFormat_m != "" 
      && EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(m_CurrentDTInputFormat_m.c_str())
                     , m_CurrentDTInputFormat_m.c_str()+LocalHere::skipc(m_CurrentDTInputFormat_m.c_str())
                     , &xtm.tm_mon))
    {
      retval=false;
      xtm.tm_mon=0;
    }
    else
      xtm.tm_mon -=1;  // tm_mon starts at 0, real months start at 1!

    if   (m_CurrentDTInputFormat_y != "" 
      && EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(m_CurrentDTInputFormat_y.c_str()),
      m_CurrentDTInputFormat_y.c_str()+LocalHere::skipc(m_CurrentDTInputFormat_y.c_str()), &xtm.tm_year))
    {
      retval=false;
      xtm.tm_year=0;
    }
    else
    { // read was OK. 
      if   (xtm.tm_year >=100)
        xtm.tm_year = xtm.tm_year-1900;
      else if (xtm.tm_year < 70)
        xtm.tm_year += 100;         // year 0...69 means 2000...2069, 70...99 is 1970...1999 !
    }

    if   (m_CurrentDTInputFormat_h != "" 
      && EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(m_CurrentDTInputFormat_h.c_str()), 
        m_CurrentDTInputFormat_h.c_str()+LocalHere::skipc(m_CurrentDTInputFormat_h.c_str()), &xtm.tm_hour))
    {
      retval=false;
      xtm.tm_hour=0;
    }
    if   (m_CurrentDTInputFormat_min != "" 
      && EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(m_CurrentDTInputFormat_min.c_str()), 
        m_CurrentDTInputFormat_min.c_str()+LocalHere::skipc(m_CurrentDTInputFormat_min.c_str()), &xtm.tm_min))
    {
      retval=false;
      xtm.tm_min=0;
    }
    if   (m_CurrentDTInputFormat_s != "")  // Seconds may be omitted.
    {
      if  (EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(m_CurrentDTInputFormat_s.c_str()), 
          m_CurrentDTInputFormat_s.c_str()+LocalHere::skipc(m_CurrentDTInputFormat_s.c_str()), &xtm.tm_sec))
      {
        retval=false;
        xtm.tm_sec=0;
      }
    }
    else
    {
      xtm.tm_sec = 0;   // provide 0 as default
    }
    long lv_milliseconds=0;
    if   (m_CurrentDTInputFormat_ms != "")
    {
      if   (EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(m_CurrentDTInputFormat_ms.c_str()),
        m_CurrentDTInputFormat_ms.c_str()+LocalHere::skipc(m_CurrentDTInputFormat_ms.c_str()), &lv_milliseconds))
      {
        retval=false;
      }
    }
    else
    {
      lv_milliseconds=0;        // provide 0 as default
    }

    // From the MSDN Libary:
    // tm_isdst is a required field. If not set, its value is undefined and the return value from mktime is unpredictable
    if   (m_CurrentDTInputFormat_DST != "")  // if DST is in the string
    {
      if  (EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(m_CurrentDTInputFormat_DST.c_str()), 
          m_CurrentDTInputFormat_DST.c_str()+LocalHere::skipc(m_CurrentDTInputFormat_DST.c_str()), &xtm.tm_isdst))
      {
        // A value less than zero to have the C run-time library code compute whether standard time or daylight savings time is in effect. 
        // The C run-time library assumes the United States' rules for implementing the calculation of Daylight Saving Time.
        retval=false;
        //xtm.tm_isdst = -1;
        xtm.tm_isdst = CDateTime().get_DST() ? 1 : 0; //use DST of now
      }
    }
    else
    {  
      // A value less than zero to have the C run-time library code compute whether standard time or daylight savings time is in effect. 
      // The C run-time library assumes the United States' rules for implementing the calculation of Daylight Saving Time.
      //xtm.tm_isdst = -1;
      xtm.tm_isdst = CDateTime().get_DST() ? 1 : 0; //use DST of now
    }

    if   (retval)   // input read OK ?
    {
      time_t theTime = mktime(&xtm);
      if   (theTime != (time_t)(-1))
      {
        timeT = theTime;
        milliSeconds = lv_milliseconds;
      }
      else
      {
        retval=false;
      }
    }
  }
  else if (ft == StandardFormat && (0 == userFormat) )  // no User Format and Standard Format selected
  {
    if   (m_CurrentInputFormat_d != "" 
      && EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(m_CurrentInputFormat_d.c_str())
      , m_CurrentInputFormat_d.c_str()+LocalHere::skipc(m_CurrentInputFormat_d.c_str())
                       , &xtm.tm_mday))
    {
      retval=false;
      xtm.tm_mday=0;
    }
    if   (m_CurrentInputFormat_m != "" 
      && EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(m_CurrentInputFormat_m.c_str())
                     , m_CurrentInputFormat_m.c_str()+LocalHere::skipc(m_CurrentInputFormat_m.c_str())
                     , &xtm.tm_mon))
    {
      retval=false;
      xtm.tm_mon=0;
    }
    else
      xtm.tm_mon -=1;  // tm_mon starts at 0, real months start at 1!

    if   (m_CurrentInputFormat_y != "" 
      && EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(m_CurrentInputFormat_y.c_str()),
      m_CurrentInputFormat_y.c_str()+LocalHere::skipc(m_CurrentInputFormat_y.c_str()), &xtm.tm_year))
    {
      retval=false;
      xtm.tm_year=0;
    }
    else
    { // read was OK. 
      if   (xtm.tm_year >=100)
        xtm.tm_year = xtm.tm_year-1900;
      else if (xtm.tm_year < 70)
        xtm.tm_year += 100;         // year 0...69 means 2000...2069, 70...99 is 1970...1999 !
    }

    if   (m_CurrentInputFormat_h != "" 
      && EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(m_CurrentInputFormat_h.c_str()), 
        m_CurrentInputFormat_h.c_str()+LocalHere::skipc(m_CurrentInputFormat_h.c_str()), &xtm.tm_hour))
    {
      retval=false;
      xtm.tm_hour=0;
    }
    if   (m_CurrentInputFormat_min != "" 
      && EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(m_CurrentInputFormat_min.c_str()), 
        m_CurrentInputFormat_min.c_str()+LocalHere::skipc(m_CurrentInputFormat_min.c_str()), &xtm.tm_min))
    {
      retval=false;
      xtm.tm_min=0;
    }
    if   (m_CurrentInputFormat_s != "")  // Seconds may be omitted.
    {
      if  (EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(m_CurrentInputFormat_s.c_str()), 
          m_CurrentInputFormat_s.c_str()+LocalHere::skipc(m_CurrentInputFormat_s.c_str()), &xtm.tm_sec))
      {
        retval=false;
        xtm.tm_sec=0;
      }
    }
    else
    {
      xtm.tm_sec = 0;   // provide 0 as default
    }
    long lv_milliseconds=0;
    if   (m_CurrentInputFormat_ms != "")
    {
      if   (EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(m_CurrentInputFormat_ms.c_str()),
        m_CurrentInputFormat_ms.c_str()+LocalHere::skipc(m_CurrentInputFormat_ms.c_str()), &lv_milliseconds))
      {
        retval=false;
      }
    }
    else
    {
      lv_milliseconds=0;        // provide 0 as default
    }

    // From the MSDN Libary:
    // tm_isdst is a required field. If not set, its value is undefined and the return value from mktime is unpredictable
    if   (m_CurrentInputFormat_DST != "")  // if DST is in the string
    {
      if  (EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(m_CurrentInputFormat_DST.c_str()), 
          m_CurrentInputFormat_DST.c_str()+LocalHere::skipc(m_CurrentInputFormat_DST.c_str()), &xtm.tm_isdst))
      {
        // A value less than zero to have the C run-time library code compute whether standard time or daylight savings time is in effect. 
        // The C run-time library assumes the United States' rules for implementing the calculation of Daylight Saving Time.
        retval=false;
        //xtm.tm_isdst = -1;
        xtm.tm_isdst = CDateTime().get_DST() ? 1 : 0; //use DST of now
      }
    }
    else
    {  
      // A value less than zero to have the C run-time library code compute whether standard time or daylight savings time is in effect. 
      // The C run-time library assumes the United States' rules for implementing the calculation of Daylight Saving Time.
      //xtm.tm_isdst = -1;
      xtm.tm_isdst = CDateTime().get_DST() ? 1 : 0; //use DST of now
    }

    if   (retval)   // input read OK ?
    {
      time_t theTime = mktime(&xtm);
      if   (theTime != (time_t)(-1))
      {
        timeT = theTime;
        milliSeconds = lv_milliseconds;
      }
      else
      {
        retval=false;
      }
    }
  }
  else if ( 0 != userFormat )
  {
    if   (userFormat[0] != "" 
      && EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(userFormat[0].c_str())
      , userFormat[0].c_str()+LocalHere::skipc(userFormat[0].c_str())
                       , &xtm.tm_mday))
    {
      retval=false;
      xtm.tm_mday=0;
    }
    if   (userFormat[1] != "" 
      && EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(userFormat[1].c_str())
                      , userFormat[1].c_str()+LocalHere::skipc(userFormat[1].c_str())
                     , &xtm.tm_mon))
    {
      retval=false;
      xtm.tm_mon=0;
    }
    else
      xtm.tm_mon -=1;  // tm_mon starts at 0, real months start at 1!

    if   (userFormat[2] != "" 
      && EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(userFormat[2].c_str()),
      userFormat[2].c_str()+LocalHere::skipc(userFormat[2].c_str()), &xtm.tm_year))
    {
      retval=false;
      xtm.tm_year=0;
    }
    else
    { // read was OK. 
      if   (xtm.tm_year >=100)
        xtm.tm_year = xtm.tm_year-1900;
      else if (xtm.tm_year < 70)
        xtm.tm_year += 100;         // year 0...69 means 2000...2069, 70...99 is 1970...1999 !
    }

    if   (userFormat[3] != "" 
      && EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(userFormat[3].c_str()), 
        userFormat[3].c_str()+LocalHere::skipc(userFormat[3].c_str()), &xtm.tm_hour))
    {
      retval=false;
      xtm.tm_hour=0;
    }
    if   (userFormat[4] != "" 
      && EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(userFormat[4].c_str()), 
        userFormat[4].c_str()+LocalHere::skipc(userFormat[4].c_str()), &xtm.tm_min))
    {
      retval=false;
      xtm.tm_min=0;
    }
    if   (userFormat[5] != "")  // Seconds may be omitted.
    {
      if  (EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(userFormat[5].c_str()), 
          userFormat[5].c_str()+LocalHere::skipc(userFormat[5].c_str()), &xtm.tm_sec))
      {
        retval=false;
        xtm.tm_sec=0;
      }
    }
    else
    {
      xtm.tm_sec = 0;   // provide 0 as default
    }
    long lv_milliseconds=0;
    if   (userFormat[6] != "")
    {
      if   (EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(userFormat[6].c_str()),
        userFormat[6].c_str()+LocalHere::skipc(userFormat[6].c_str()), &lv_milliseconds))
      {
        retval=false;
      }
    }
    else
    {
      lv_milliseconds=0;        // provide 0 as default
    }

    // From the MSDN Libary:
    // tm_isdst is a required field. If not set, its value is undefined and the return value from mktime is unpredictable
    if   (userFormatDST != "")  
    {
      if  (EOF == sscanf (inputDateTime.c_str()+LocalHere::skipc(userFormatDST.c_str()), 
          userFormatDST.c_str()+LocalHere::skipc(userFormatDST.c_str()), &xtm.tm_isdst))
      {
        // A value less than zero to have the C run-time library code compute whether standard time or daylight savings time is in effect. 
        // The C run-time library assumes the United States' rules for implementing the calculation of Daylight Saving Time.
        retval=false;
        //xtm.tm_isdst = -1;
        xtm.tm_isdst = CDateTime().get_DST() ? 1 : 0; //use DST of now
      }
    }
    else
    {  
      // A value less than zero to have the C run-time library code compute whether standard time or daylight savings time is in effect. 
      // The C run-time library assumes the United States' rules for implementing the calculation of Daylight Saving Time.
      //xtm.tm_isdst = -1;
      xtm.tm_isdst = CDateTime().get_DST() ? 1 : 0; //use DST of now
    }

    if   (retval)   // input read OK ?
    {
      time_t theTime = mktime(&xtm);
      if   (theTime != (time_t)(-1))
      {
        timeT = theTime;
        milliSeconds = lv_milliseconds;
      }
      else
      {
        retval=false;
      }
    }
  }
  else 
  {
    // invalid ft and no user Format
    cCBS_StdLog_Task::getInstance()->log("Fatal Error! Creation of DateTime failed by invalid format specification.", 1);
    exit (EXIT_FAILURE);
  }

  return retval;

}

