// Copyright 2006 SMS - Demag AG

#ifndef _CLogFileReader_H_
#define _CLogFileReader_H_

#include "CTlgContainer.h"
#include "CTlgPrototypSet.h"
#include "CTelTime.h"
#include "CTlg.h"
#include "CInterConfig.h"
#include <string>
#include <fstream>

//------------------------------------------------------
// Name:  CLogFileReader.h
// Descr: Mit dieser Klasse werden Telegramm - Log - Files eingelesen     
// Date:
// Autor: Emeljanov Anatolij 
//------------------------------------------------------
class CLogFileReader 
{
  public:
		virtual ~CLogFileReader();
		CLogFileReader();
		//!
		void setTlgProtoTyp(CTlgProtoTypSet* tlgProtoTyp);
		//!
		int readLogFile(const std::string& path,bool const&abort);
		//!
		int getEmptyLinesCount()const;
    //!
		int getWrongLinesCount()const;
		//!
		void setTlgCountTotal(int total);
    //!
    int getTlgCountTotal()const;
    //!
		int getTlgCountInFile()const;
		//!
		CTlg* getFlatTlg(int id);
		//!
		double getTlgTime(int id);
		//!
		std::string getTlgTimeAsString(int id);
		//!
		bool checkTlgProtoTypSet(std::string& path);
		//!
		void addLogFile(CLogFileReader* logReader);
		//!
		CTlgContainer<double>& getTlgContainer();
		//!
		void clearContainer();
    //! Liest bestimmte Telgramme aus Log-File aus, und speichert im Container. 
    int readLogFileToAnalyze(long& last_pos,const std::string& path,bool const& abort);
    //!
    void closeInFile();

  private:
		//! Enthaelt Telegrammprototyps einer Schnittstelle
    CTlgProtoTypSet* TlgProtoTyp;
		//! Mit InFile wird Telegramm - Log - File gelesen
    std::ifstream InFile;
    //! die Anzahl von fehlerhaften Lines in Log - File
		int WrongLineCount;
    //! die Anzahl von leeren Line in Log - File
		int EmptyLineCount;
    //! die Anzahl von Telegramme in Telegramm - Log -File
		int TlgCount;
		//! Container  mit Telegramme aus Telegramm - Log - File
    CTlgContainer<double> TlgContainer;
		//! bildet Datum und Zeit eines Telegramm
    bool createTimeTlg(CTelTime& time,const std::string& line);
		//! erzeugt ein neues Telegramm
    CTlg* createTlg(const std::string& line);
		//! fuellt Twelegramm mit Daten 
		bool loadTlg(CTlg* tlg,const std::string& line);
};
#endif

