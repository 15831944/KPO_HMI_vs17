// Copyright 2006 SMS - Demag AG

#ifndef _CTelTime_H_
#define _CTelTime_H_

#include "CTimeFormat.h"
#include "CFormatConverter.h"
#include "CExpTimeError.h"
#include "CExpDateError.h"

//-------------------------------------------
// Name:  CTelTime.h
// Descr: repraesentiert die Zeit fuer Telegramme      
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
class CTelTime
{
  public:
    CTelTime();
    ~CTelTime();
		//! setzt die Zeit
    void setTime(const double t);
		//! gibt die Zeit zurueck
    double getTimeAsDouble() const;
		//! geben Datum und Zeit als Zeichenfolge zurueck
		std::string getDateAsString() const;
		std::string getTimeAsString() const;
		void setDateFormat(CTimeFormat::DateTyp f1,const std::string& d1,CTimeFormat::DateTyp f2,
		const std::string& d2,CTimeFormat::DateTyp f3,CTimeFormat::YearFormat year);
		void setTimeFormat(CTimeFormat::TimeTyp t1,const std::string& d1,CTimeFormat::TimeTyp t2,const std::string& d2,
		CTimeFormat::TimeTyp t3,const std::string& d3,CTimeFormat::TimeTyp t4,int msc);
		const std::string& getDateFormat() const;
		const std::string& getTimeFormat() const;
		//! setzt die Zeit
		void setTime(const std::string& date,const std::string& time) throw(CExpDateError,CExpTimeError);
		//! berechnet die Zeitdifferenz
    double getDiffTimeAsSecond(CTelTime* t);
		void setTimeFormat(const CTimeFormat& format);
		const CTimeFormat& getTimeFormat();
  private:
		//! Die Zeit des Telegramms.Das Nachkommaanteil steht
		//  fuer Millisekunden
    double TlgTime;
		//!	Format fuer Datum und Zeit
    CTimeFormat TimeFormat;
		std::string getDateFormatString() const;
		std::string getTimeFormatString() const;
		void setDate(const std::string& date,struct tm* tm_t);
		void setTime(const std::string& time,struct tm* tm_t);
    bool checkDateFormat(const std::string& date);
    bool checkTimeFormat(const std::string& time);
};
#endif
