// Copyright 2006 SMS - Demag AG

//-----------------------------------------------
#ifndef _CElemDescription_H_
#define _CElemDescription_H_
//------------------------------------------------
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
//------------------------------------------------
// Name:  CElemDescription.h
// Descr: Mit dieser Klasse werden Eigenschaften von 
//		    Telegrammelementen festgelegt.	
// Date:
// Autor: Emeljanov Anatolij
//------------------------------------------------
class CElemDescription 
{
	public:
	  //! Transporttyp fuer Telegrammelemente
	  enum TransportType 
	  {
		  ascii,
		  binary,
      binaryL3D,
      binaryCCSD,
		  binaryRD,
      binaryRS,
		  unknow
	  };
	  //! Applicationtyp fuer Telegrammelemente 	  
	  enum ElementType 
	  {
		  tInteger,
		  tShortInteger,
		  tDouble,
		  tFloat,
		  tString,
		  tArray,
		  tRecord,
		  tUnknow,	
		  tSegment
	  };
		void setNameElem(const std::string& name);
		const std::string &  getNameElem() const;
		void setElemLen(const int len);
		int getElemLen() const;
		void setElemDescr(const std::string& descr);
		const std::string &  getElemDescr() const;
		void setMaxElem(const std::string& max);
		const std::string &  getMaxElem() const;
		void setMinElem(const std::string& min);
		const std::string &  getMinElem() const;

		void setNumFmtElem(const std::string& numFmt);
		const std::string &  getNumFmtElem() const;

		void setUnitElem(const std::string& unit);
		const std::string &  getUnitElem() const;
		void setFactorElem(const std::string& factor);
		const std::string &  getFactorElem() const;
		void setTtranspTypeElem(const CElemDescription::TransportType& transType);
		CElemDescription::TransportType getTranspTypeElem() const;
		void setElemType(const CElemDescription::ElementType& elemType);
		CElemDescription::ElementType getElemType() const;
    void setElemCount(const long count);
		long getElemCount() const;
    std::string getTransTypAsString();

		//! erzeugt ein neues Objekt der Klasse CElemDescription
		// Rueckgabewert ist die Nummer des Objekt in ElemDescrMap 
		static int createDescription();
		//! Gibt Objekt der Klasse CElemDescription, das unter der
		// Nummer id in ElemDescrMap abgelegt ist, zurueck.
		static CElemDescription* getDescriptionInztanz(int id);
		//! Erhoeht entsprechende Wert in ObjReferenzMap um 1
		static void reserveElemDescription(int id);
		//! Erniedrigt entsprechende Wert in ObjReferenzMap um 1
		static void releaseElemDescription(int id);
		
		//test
		static void writeElemDescr(const std::string& path);
	protected:
		CElemDescription();          

	private:
		//! Container fuer Objekten der Klasse CElemDescription
		static std::map<int,CElemDescription*> ElemDescrMap;
		//! Container enthaelt die Anzahl Referenzen auf Objekten   
    static std::map<int,int> ObjReferenzMap;
    //! Container enthaelt die freie Integer Keys  
    static std::vector<int> FreeKeyList;
		//! Name des Elements
		std::string Name;
		//! Laenge des elements
		int Len;
		//! Kommentar zu dem Element
		std::string Description;
		//! Grenzwerte fuer das Element
		std::string Max;
		std::string Min;
    std::string NumFmt;
		//! Einheit des Elements
		std::string Unit;
		//! Faktor fuer Multiplizieren vor dem Senden 
		// des Elements
		std::string Factor;
		//! Transporttyp des Elements
		TransportType Transport;
		//! Applicationtyp des Elements
		ElementType ElemType;
    
		long Count;
};
#endif 
