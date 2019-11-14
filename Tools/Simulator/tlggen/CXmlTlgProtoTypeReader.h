// Copyright 2006 SMS - Demag AG

#ifndef _CXmlTlgProtoTypeReader_H_
#define _CXmlTlgProtoTypeReader_H_

//#include "TinyXml.h"
//#include "TinyStr.h"
#include "CTlgBuilder.h"
#include "CTlgProtoTypSet.h"
#include <string>

class TiXmlDocument;
class TiXmlElement;

//------------------------------------------------------------------
// NAME : CXmlTlgPrototypReader.h
// DESCR: Mit dieser Klasse werden Schnittstellenspezifikationsdateien gelesen
//        und Telegrammprototyps gebildet. Die Klasse benutzt Free Ware TinyXml,
//        um Schnittstellenspezifikationsdatei zu parsen(www.sourceforge.net).
// DATE:
// AUTOR: Emeljanov Anatolij
//------------------------------------------------------------------
class CXmlTlgProtoTypeReader
{
	public:
		CXmlTlgProtoTypeReader();
		~CXmlTlgProtoTypeReader();
	  //! liest Schnittstellenspezifikationsdate
		CTlgProtoTypSet * readXmlProtoInterface(const std::string& path);
	  //! gibt Fehlermeldung zurueck.
    const std::string& getErrorMessage() const;
	private:
		//! Container fuer Telegrammsprototyps
		CTlgProtoTypSet* TlgProtoTypSet;
		//! Mit diesem Attribut wird Schnittstellenspezifikationsdatei geparst
		TiXmlDocument* XmlDoc;
		//! Mit diesem Attribut werden Telegramme konstruiert
		CTlgBuilder TlgBuilder;
		//! Enthaelt Fehlermeldung, wenn Einlesen 
		//  einer Schnittstellenspezifikationsdatei fehlschlaegt
		std::string ErrorMessage;
		int readInterfaceDescr(CTlgProtoTypSet* inter);
		bool readComment(TiXmlElement* elem,std::string& comment);
		bool readEncodingRules(TiXmlElement* elem,std::string& traspType,std::string& padding,std::string& paddingStr);
		bool readAllTelegrams(CTlgProtoTypSet* inter);
		bool readOneTelegram(CTlgProtoTypSet* inter,TiXmlElement* elem);
		bool readElement(TiXmlElement* elem);
    //bool readElementRekursiv(TiXmlElement* elem);
		bool readPrimitive(TiXmlElement* elem,std::string& appType,std::string& transpType,std::string& len,
		std::string& unit,std::string& factor,std::string& min,std::string& max,std::string& numFmt);
		bool readUserDefinedTyp(TiXmlElement* elem);
		bool readUserDefinedType(std::string& name);
    bool readRecord(TiXmlElement* elem);
		bool isRecords(TiXmlElement* elem);
		bool isSimple(TiXmlElement* elem);
		TiXmlElement* findType(std::string& name); 
};
#endif
