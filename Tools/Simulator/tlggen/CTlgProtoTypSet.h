// Copyright 2006 SMS - Demeg AG

#ifndef _CTlgProtoTypSet_H_
#define _CTlgProtoTypSet_H_

#pragma warning( disable : 4290 )

#include "CTlgContainer.h"
#include <map>
#include <string>

class CTlg;
class CExpUnknownTlg;

//------------------------------------------------------------------
// NAME : CTlgProtoTypSet.h
// DESCR: Diese Klasse enthaelt ein Container mit Telegrammprototyps
//        einer Schnittstelle
// DATE:
// AUTOR: Emeljanov Anatolij
//------------------------------------------------------------------
class CTlgProtoTypSet 
{
	public:
	  CTlgProtoTypSet();
		~CTlgProtoTypSet();
		const std::string& getName() const;
		void setName(const std::string& value);
		const std::string& getVersion() const;
		void setVersion(const std::string& value);
		void setComment(const std::string& value);
		const std::string& getComment() const;
		//! fuegt ein Telegrammprototyp zu dem Container hinzu
		void addTlgPrototyp(CTlg* tlg);
		//! gibt die Anzahl von Tellegrammprototyps der Schnittstelle zurueck 
		int getTlgCount() const;
		//! erzeugen eine Kopie von einem Telegrammprototyps 
		CTlg* makeTlg(const std::string& name) throw (CExpUnknownTlg);
		CTlg* makeTlg(int id) throw (CExpUnknownTlg);
		//! geben den Zeiger auf einen Telegrammprototyps im Container zurueck
		CTlg* makeFlatTlg(const std::string& name) throw (CExpUnknownTlg);
    CTlg* makeFlatTlg(int id) throw (CExpUnknownTlg);
	private:
		//! Container mit Telegrammprototyps
    CTlgContainer<std::string> TlgProtoMap;
		//! Name der Schnittstelle
		std::string Name;
		//! Version der Schnittstelle
		std::string Version;
		//! Kommentar zu der Schnittstelle
		std::string Comment;
		void freeTlg();
};
#endif 
