// Copyright 2006 SMS - Demeg AG
#ifndef _TlgBuilder_H_
#define _TlgBuilder_H_

#include "CTlg.h"
#include "CTlgElem.h"
#include "CElemDescription.h"
#include <string>

class CExpUnknownElemTyp;
class CExpUnknownTranspTyp;

//------------------------------------------------------------------
// NAME : CTlgBuilder.h
// DESCR: Mit dieser Klasse werden Telegrammprototyps gebildet
// DATE:
// AUTOR: Emeljanov Anatolij
//------------------------------------------------------------------
class CTlgBuilder
{
	public:
		CTlgBuilder();
		~CTlgBuilder();
		//! erzeugt ein neues Telegramm
		void makeTlg(const std::string& name,const long len,const std::string& dir);
		//! gibt gebildetes Telegramm zurueck
		CTlg* getTlg();
		//! setzt ein Kommentar zum Telegrammelement
		void setElemComment(const std::string& comment);
		//! erzeugt ein neues Listenelement
		void makeArrayElement(const std::string& name,long count);
		//! setzt Eigenschaften zum Listenelement
		//void setArrayAttribute(const std::string& elemType,const std::string& transpType,long elemLen) throw (CExpUnknownElemTyp,CExpUnknownTranspTyp);
		//! endet Bildung des Listenelements
		void endArray();
		//! erzeugt ein einfaches Telegrammelement
		void makeSimpleElement(const std::string& name,const std::string& elemType,long elemLen);
		void setSimpleElemAttribute();
		//! endet Bildung eines einfachen Telegrammelements
		void endSimpleElement();
		//! erzeugt ein neues Rekordselement
		void makeRecords(const std::string& name);
		//! endet Bildung des Rekordselement
		void endRecordsElement();
		//! setzt Eigenschaften eines Telegrammelements
		void setElemInfo(const std::string& transp,const std::string& unit,const std::string& factor,
                     const std::string& min,const std::string& max,const std::string& numFmt);
		//! setzt Description zum Telegramm
		void setTlgDescr(const std::string& DescrStr);
		void setTlgInterName(const std::string& name);
	private:
		CElemDescription::ElementType stringToElemType(const std::string& str,int len);
		CElemDescription::TransportType stringToTranspType(const std::string& str);
		CTlgElem* createElement(CElemDescription::ElementType type,int index,int len);
		void addTlgElem();
		std::string getActElemName();
		//! Name der Schnittstelle
		std::string name;
		//! zu bildene Telegramm
		CTlg* Tlg;
		std::vector<CTlgElem*> ElemVect;
		//CTlgElem* Elem;
		//CTlgElem* ContextElem;
		//! zu bildene einfaches Telegrammelement
		//CTlgElem* TlgElem;
		//! zu bildene Rekordelement 
		//CTlgElem* RecordElem;
		//! zu bildene Listenelement
		//CTlgElem* ArrayElem;
};
#endif
