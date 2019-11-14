// Copyright 2006 SMS - Demag AG

#ifndef _CInterConfig_H_
#define _CInterConfig_H_

#include "CTimeFormat.h"
#include <string>
#include <map>

//--------------------------------------------
// Name:  CInterConfig.h
// Descr: Mit dieser Klasse werden Schnittstellen konfiguriert  
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
class CInterConfig
{
  public:
	  //! gibt ein Objekt der Klasse CInterConfig zurueck.
    static CInterConfig* getInterConfig(const std::string& name);
	  //! Typ fuer Richtung der Fuellung
	  enum PaddingTyp{Left,Right};
	  //! Typ fuer Handhabung der Telegrammlaenge
	  enum LenTlgIdTyp{Total,Body,User};
	  //! Typ fuer Handhabung der Grenzwerte
	  enum LimitValueTyp{Error,Warning,Accept,SetToMinMax};
    void addTelId(const std::string& telName,const std::string& id);
    void setTelIdInfo(const std::string& TelIdName,const std::string& ElemIdName,
    const std::string& TypId,const std::string& ElemLenName);
    const std::string& getTelIdName();
    void getTelId(const std::string& tel,std::string& val);
	  void getTelName(const std::string& id,std::string& val);
    const std::string& getElemIdName();
    const std::string& getElemLenName();
	  void clearTelId();
	  void setSwapping(bool swop);
	  bool getSwapping() const;
	  void setTreatLenIdMode(LenTlgIdTyp treat);
	  LenTlgIdTyp getTreatLenIdMode();
	  void setPaddingDirection(PaddingTyp Dir);
	  PaddingTyp getPaddingDirection() const;
	  void setPaddingString(const std::string& str);
	  char getPaddingString() const;
	  void setLimitTreatment(LimitValueTyp lim);
	  LimitValueTyp getLimitTreatment();
	  void setLogDelimeter(char del);
	  char getLogDelimeter();
	  void setTime(const std::string& date,const std::string& time);
	  const CTimeFormat& getTimeFormat();
    ~CInterConfig();
  protected:
    CInterConfig();
  private:
		//! Container fuer Objekten der Klasse CInterConfig
    static std::map<std::string,CInterConfig*> InterConfContainer;
		//! Container mit Telegrammnamen(Schluessel) und Telegrammkennungen
    std::map<std::string,std::string> TelId;
		//! der Name eines Rekordelements, das Einstellengen fuer
		//  Handhabung des Telegramms enthaelt(defaultwert "Header")
    std::string TelIdName;
		//! Der Name des Elememnts, dass fuer Telegrammkennung
		//  verantwortlich ist
    std::string ElemIdName;
		//!
    std::string TypId;
		//! Der Name des Elements, dass die Laenge des Telegramms enthaelt.
    std::string ElemLenName;
		//! Dutum- und Zeitformat
    CTimeFormat* LogTimeFormat;
		//! Trennzeichen zwischen Telegrammelements in einem Telegramm - Log - Files
		char DelLog;
		//! Handhabung der Grenzwerte(Error,Warning,Accept,SetToMinMax)
		LimitValueTyp LimitValue;
		//! legt die Richtung des Fuellung(Left, Right) fest.
		PaddingTyp PaddingDir;
		//! Das Fuellzeichen  
		std::string PaddingString;
		//! Flag fuer Reihenfolge von Bytes der 
		//  numerischen Werten
		bool Swapping;
		//! legt die Definition der Laenge des Telegramms(Total,
		//  Body,User) fest.
		LenTlgIdTyp LenTlgId;
		void buildDateTemplate(const std::string& date);
		void buildTimeTemplate(const std::string& time);
		CTimeFormat::DateTyp getDateIdent(char sym);
		CTimeFormat::TimeTyp getTimeIdent(char sym);
};
#endif
