// Copyright 2006 SMS - Demag AG

#ifndef _TimeFormat_H_
#define _TimeFormat_H_

#include <string>

//--------------------------------------------
// Name:  CTimeFormat.h
// Descr: Die Klasse dient als Vorlage fuer Datum- und Zeitformat 
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
class CTimeFormat
{
  public:
		//! Typ fuer Datumformat
		enum DateTyp{tYear,tMon,tDay};
		//! Typ fuer Zeitformat
		enum TimeTyp{tHour,tMin,tSec,tMSec};
		//! Typ fuer Jahrformat(2 oder 4 Zeichen) 
		enum YearFormat{tShort,tLang};
		//! Kennzeichen fuer Jahr,Monat,Tag,Stunde
		//! Minute,Sekunde und Millisekunde
		static const char Year;
    static const char Mon;
    static const char Day;
    static const char Hour;
    static const char Min;
    static const char Sec;
    static const char MSec;
    CTimeFormat();
    ~CTimeFormat();
		//! setzt das Datumformat
		void setDateFormat(CTimeFormat::DateTyp f1,const std::string& d1,CTimeFormat::DateTyp f2,
		const std::string& d2,CTimeFormat::DateTyp f3,CTimeFormat::YearFormat year);
		//! setzt setzt das Zeitformat
		void setTimeFormat(CTimeFormat::TimeTyp t1,const std::string& d1,CTimeFormat::TimeTyp t2,const std::string& d2,
	  CTimeFormat::TimeTyp t3,const std::string& d3,CTimeFormat::TimeTyp t4,int msc);
    //! gibt Datumformat zurueck
	  const std::string& getDateFormat() const;
	  //! gibt Zeitfornat zurueck
	  const std::string& getTimeFormat() const;
	  //! gibt der erste Delimeter von Datumformat zurueck
	  const std::string& getDateDelimeter1() const;
	  //! gibt der zweite Delimeter von Datumformat zurueck
	  const std::string& getDateDelimeter2() const;
	  //! gibt der erste Delimeter von Zeitformat zurueck
	  const std::string& getTimeDelimeter1() const;
	  //! gibt der zweite Delimeter von Zeitformat zurueck
	  const std::string& getTimeDelimeter2() const;
	  //! gibt der dritte Delimeter von Zeitformat zurueck
	  const std::string& getTimeDelimeter3() const;
	  //! geben Position des Jahrs,Momats, ... zurueck
	  //  pos - Position in Formatforlage
	  //  length - Laenge von Jahrs,Monat, ...
	  void getYearFormatPlace(int* pos,int* length) const;
	  void getMonFormatPlace(int* pos,int* length) const;
	  void getDayFormatPlace(int* pos,int* length) const;
	  void getHourFormatPlace(int* pos,int* length) const;
	  void getMinFormatPlace(int* pos,int* length) const;
	  void getSecFormatPlace(int* pos,int* length) const;
  private:
		//! Delimeter fuer Datum
		std::string DateDel1;
    std::string DateDel2;
		//! Delimiter fuer Zeit
    std::string TimeDel1;
    std::string TimeDel2;
    std::string TimeDel3;
		//! Format fuer Datum
    std::string DateTemplate;
		//! Format fuer Zeit
    std::string TimeTemplate;
            
		void addToDateTemplate(DateTyp d,YearFormat year);
		void addToTimeTemplate(TimeTyp t,int count);
		void clearDateFormat();
    void clearTimeFormat();
		void getDateFormatPlace(const char c,int* pos,int* length) const;
		void getTimeFormatPlace(const char c,int* pos,int* length) const;
};
#endif
