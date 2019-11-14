// Copyright 2009 SMS - Siemag AG

#ifndef _LogWriter_H_
#define _LogWriter_H_

#include <string>
#include <windows.h>
#include <ostream>
#include <fstream>
//-------------------------------------------
// Name:  CLogWriter.h
// Descr: Diese Klasse erzeugt eine Log-Datei. Der Name der Datei wird immer mithilfe
//        des Zeitstempels generiert. Die Klasse ist nach dem Entwurf "Singleton" gebaut.
//        Die Daten werden direkt im Laufe der Anwendung geschrieben, der Buffer wird
//        nach jedem Zugriff in die Datei übernommen.
// Date:  10.07.09
// Autor: Emeljanov Alexander
//--------------------------------------------

class CLogWriter
{
  public:
		//! Message - Typ
    enum MessTyp{Info,Warning, Error}; 
    //! gibt das Objekt der Klasse zurueck
    static CLogWriter* getLogWriter();
    ~CLogWriter();
		//! legt den Pfad der Datei fest
    void setPath(const std::string& path);
    void setSettings(int size,bool info,bool warning,bool error);
		//! schreibt den String - Wert in die Datei
    void WriteMessage(MessTyp typ,std::string& source,std::string& message);
    void WriteMessage(MessTyp typ,std::string& message,char* file,char* func,long line);
    std::string getPath();
  protected:
    CLogWriter();
  private:
		//! Gibt die Anzahl der erzeugten Dateien an
		int count;
		//! Uberprueft, ob die Datei ihre max. Groesse erreicht hat
		bool checkMaxFileSize();
		//! Erzeugt einen Dateinamen ohne Erweiterung (log) und ohne voll. Pfad
		void createFileName();
		//! Dateipfad ohne Dateiname und ohne Erweiterung
		std::string path;
		//! Dateiname ohne Erweiterung und ohne Count
		std::string fileName;
    //! Dateiname mit Erweiterung und mit Count
		std::string fullFileName;
		//! Zeiger auf Objekt der Klasse
    static CLogWriter* LogWriter;
    //! Zeiger auf Ostream
    std::ofstream* writer;
    //! Gibt die akt. Systemezeit
    SYSTEMTIME now;
    //! 
    CRITICAL_SECTION sec; 
    //! maximale Groesse der Datei
    long maxSize;
    bool error;
    bool info;
    bool warning;
};
#endif
