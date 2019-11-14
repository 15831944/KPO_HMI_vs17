// Copyright 2006 SMS - Demag AG

#ifndef _CTlgElemString_H_
#define _CTlgElemString_H_

#include "CTlgElem.h"
//------------------------------------------------------------------
// NAME : CTlgElemString.h
// DESCR: Mit der Klasse werden String-Werte(Zeichenwerte) verwaltet.
// DATE:
// AUTOR: Emeljanov Anatolij
//-----------------------------------------------------------------

class CTlgElemString : public CTlgElem
{
	public:
		CTlgElemString(const CElemDescription::TransportType transp,const int len,
		const std::string& val="",const std::string& name="");
		CTlgElemString(int index);
		CTlgElemString(const CTlgElemString& Obj);
		virtual ~CTlgElemString();
		virtual CTlgElem* clone() const;
		virtual void getValue(std::string& value) const;
		virtual void setValue(const std::string& val,CInterConfig* interConf);
		virtual void setDefaultValue();
		virtual int serialize(char* buffer,int len,CInterConfig* interConfig);
		virtual int compare(const std::string& val,const std::string& subElemName);
		virtual void getElemAsString(std::string& elem,const std::string& del);
		virtual int decodeElem(char* bytes,int count,CInterConfig* interConfig);
		virtual int getTransBytesCount() const;
	private:
		//! Wert des Telegrammelements
		std::string Value;
    //---Kodierungsmethode
    int serializeAsASCII(char* buffer,int len,CInterConfig* interConfig);
		int serializeAsBinary(char* buffer,int len,CInterConfig* interConfig);
    int serializeAsBinaryL3D(char* buffer,int len,CInterConfig* interConfig);
    int serializeAsBinaryCCSD(char* buffer,int len,CInterConfig* interConfig);
		int serializeAsBinaryRD(char* buffer,int len,CInterConfig* interConfig);
    int serializeAsBinaryRS(char* buffer,int len,CInterConfig* interConfig);
    //---Dekodierungsmethode
    int decodeAsASCII(char* bytes,int count,CInterConfig* interConfig);
    int decodeAsBinary(char* bytes,int count,CInterConfig* interConfig);
    int decodeAsBinaryL3D(char* bytes,int count,CInterConfig* interConfig);
    int decodeAsBinaryCCSD(char* bytes,int count,CInterConfig* interConfig);
		int decodeAsBinaryRD(char* bytes,int count,CInterConfig* interConfig);
    int decodeAsBinaryRS(char* bytes,int count,CInterConfig* interConfig);
};
#endif
