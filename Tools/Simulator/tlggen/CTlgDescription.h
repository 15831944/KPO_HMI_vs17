// Copyright 2006 SMS - Demag AG

#ifndef _CTlgDescription_H_
#define _CTlgDescription_H_

#include <string>
#include <vector>
#include <map>

//------------------------------------------
// Name:  CTlgElem
// Descr: Mit dieser Klasse werden Eigenschaften 
//        der Telegramme festgelegt
// Date:
// Autor: Emeljanov Anatolij 
//-------------------------------------------
class CTlgDescription 
{
	public:
		const std::string &  getNameTlg() const;
		void setNameTlg(const std::string& name);
		long getLenTlg() const;
		void setLenTlg(long len);
		const std::string &  getDescrTlg() const;
    void setDescrTlg(const std::string& descr);
    void setDirection(const std::string& dir);
    const std::string& getDirection() const;
		void setInterfaceName(const std::string& name);
		const std::string& getInterfaceName()const;
		static CTlgDescription* getTlgDescriptionInztanz(int id);
		static int createTlgDescription();
		static void reserveTlgDescription(int id);
		static void releaseTlgDescription(int id);
    //test - funktion
    static void writeTlgDescr(const std::string& path);
  protected:
		CTlgDescription();
	private:
		//! Container fuer Objekten der Klasse CElemDescription
		static std::map<int,CTlgDescription*> TlgDescrMap;
		//! Container enthaelt die Anzahl Referenzen auf Objekten   
    static std::map<int,int> ObjReferenzMap;
    //! Container enthaelt die freie Integer Keys  
    static std::vector<int> FreeKeyList;
    //! Name des Telegramms
		std::string Name;
		//! Laenge des Telegramms
		long Len;
		//! Kommentar zum Telegramm
		std::string Description;
		//! Richtung(Senden,Empfangen)
    std::string Direction;
		//! Name der Schnittstelle
		std::string Interface;
};
#endif
