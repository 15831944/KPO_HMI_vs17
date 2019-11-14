// Copyright 2006 SMS - Demag AG

#ifndef _CTlgElem_H_
#define _CTlgElem_H_

#pragma warning( disable : 4290 )

#include "CElemDescription.h"
#include "CExpUnknowTranspTyp.h"
#include "CExpConvertError.h"
#include "CFormatConverter.h"
#include "CInterConfig.h"
#include <string>

//----------------------------------------------------------
// Name:  CTlgElem
// Descr: Eine abstrakte Basisklasse fuer Telegrammelement.
//        Rein virtuelle Methode dieser Klasse werden in abgeleitete
//        Klassen (CTlgElemInt, CTlgElemDoubl,CTlgElemString, CTlgElemSegment)
//        abhaengig vom Typ des Telegrammelements und Schnittstellekonfiguration
//        definiert.
// Date:
// Autor: Emeljanov Anatolij 
//----------------------------------------------------------
class CTlgElem 
{
  public:
    CTlgElem();
    CTlgElem(const CElemDescription::TransportType transp,
	            const int len,const std::string& name="");
	  CTlgElem(const std::string& name,const long count,const CElemDescription::ElementType elemTyp);
	  CTlgElem(int index);
    virtual ~CTlgElem();
		//! setzt den Wert des Telegrammelements 
		virtual void setValue(const std::string& val,CInterConfig* interConf) throw(CExpConvertError) = 0;
		//! setzt Default - Wert fuer Telegrammelements
		//  Integer -1;
		//  Double -1.0
		//  String " " (Leerzeichen)
		virtual void setDefaultValue()=0;
		//! gibt den Wert des Telegrammelements zurueck. 
		// value - In diesen Parameter wird den Wert des 
		//Telegrammelements geschrieben
		virtual  void getValue(std::string& value) const = 0;
		//! erzeugt eine Kopie des Telegrammelements
    virtual CTlgElem* clone()const = 0;
		//! kodiert den Wert des Elements in Byte - Stream. Gibt die Anzahl 
		// der Bytes von Byte - Stream
		//buffer - enthaelt nach dem Funktionaufruf den kodierte Wert.
		//len - Die Groesse den buffer
		//interConfig - enthaelt Regeln fuer Kodierung des Telegrammelements
		virtual int serialize(char* buffer,int len,CInterConfig* interConfig) throw(CExpUnknownTranspTyp)=0;
		//! dekodiert den Byte - Stream in den Wert des Telegrammelements
		virtual int decodeElem(char* bytes,int len,CInterConfig* interConfig) = 0;
		virtual void getElemAsString(std::string& elem,const std::string& del)=0;
		//! vergleicht den Wert des Telegrammelements mit val. Fuer Segmentelements
		//soll Subelement durch subElemName festgelegt werden
		//Rueckgabewert:
		// 1 - Telegrammelements ist groesser
		// -1 - Telegrammelements ist kleiner
		// 0 - Telegrammelement ist gleich mit val
		virtual int compare(const std::string& val,const std::string& subElemName="") = 0;
    //! fuegt ein Subelement zu dem Element hinzu.
    virtual void addSubElem(CTlgElem* elem);
    //! gibt Anzahl der Subelemente zurueck. 
		virtual int getSubElemCount() const;
    //! geben den Zeiger auf ein Subelement zurueck.
		//id - Identifiziert das Subelement durch Nummer oder Name
    virtual CTlgElem* getSubElem(int id) const; 
    virtual CTlgElem* getSubElem(const std::string& id) const;
		//! gibt den Name des Telegrammelements zurueck
    const std::string&  getNameElem() const;
		//! setzt Kommentare fuer Telegrammelement
		void setComment(const std::string& comment);
		//! gibt Kommentare von Telegrammelement zurueck
		const std::string& getComment() const;
		//! gibt die Laenge des Telegrammelements aus Schnittstellenspezifikationsdatei zurueck
    int getLen() const;
    //! gibt die Anzahl der Bytes, die fuer Kodierung des Elements notwaendig ist, zurueck
    virtual int getTransBytesCount() const;
		void setElemType(const CElemDescription::ElementType& elemType);
		CElemDescription::ElementType getElemType() const;
		void setElemInfo(const std::string& unit,const std::string& factor,const std::string& min,const std::string& max,const std::string& numFmt);
		void getMinMax(std::string& min,std::string& max);
    void getNumFmt(std::string& numFmt);

    std::string getFormattedElemValue(const std::string& ElemValue, const std::string& numFmt);

		void getElemInfo(std::string& unit,std::string& factor,std::string& min,std::string& max) const;
    std::string getTranspTyp() const;
		CElemDescription::TransportType getElemTranspTyp() const;
    int getDescrIndex() const;
  protected:
		//! Nummer des Objekts der Klasse CElemDescription, das die Eigenschaften
		// des Telegrammelements enthaelt.
    int DescrIndex;
		void removeFillChar(std::string& val,CInterConfig* interConfig);
    void longToByteStream(char* buffer,long val,CInterConfig* interConfig);
    long byteStreamToLong(char* buffer,CInterConfig* interConfig);
    void freeElemDescription();
    void swapBytes(char* bytes,int count);
};
#endif
