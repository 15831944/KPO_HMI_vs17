// Copyright 2006 SMS - Demeg AG

#ifndef _CTlgElemFloat_H_
#define _CTlgElemFloat_H_

#include "CTlgElem.h"
#include "CExpLimitError.h"

//------------------------------------------------------------------
// NAME : CTlgElemFloat.h
// DESCR: Mit der Klasse werden Float Werte(Gletkommazahlen mit die
//        Laenge 4 - Bytes) verwaltet.
// DATE:
// AUTOR: Emeljanov Anatolij
//------------------------------------------------------------------
class CTlgElemFloat : public CTlgElem
{
	public:
		CTlgElemFloat(const CElemDescription::TransportType transp,const int len,
					        const float val,const std::string& name);
		CTlgElemFloat(int index);
		CTlgElemFloat(const CTlgElemFloat& Obj);
		virtual ~CTlgElemFloat();
		virtual CTlgElem* clone() const;
		//virtual CTlgElem* getSubElem(int index) const;
		//virtual CTlgElem* getSubElem(const std::string& id) const;
		virtual  void getValue(std::string& value) const;
		virtual void setValue(const std::string& val,CInterConfig* interConf);
		virtual void setDefaultValue();
		//virtual int getSubElemCount() const;
		virtual int serialize(char* buffer,int len,CInterConfig* interConfig);
		virtual int compare(const std::string& val,const std::string& subElemName);
		virtual void getElemAsString(std::string& elem,const std::string& del);
		virtual int getTransBytesCount() const;
		//virtual void addSubElem(CTlgElem* elem);
		virtual int decodeElem(char* bytes,int count,CInterConfig* interConfig);
	private:
		//! Value des Telegrammelements
		float Value;
		int serializeAsASCII(char* buffer,int len,CInterConfig* interConfig);
		int serializeAsBinary(char* buffer,int len,CInterConfig* interConfig);
		int decodeAsASCII(char* buffer,int len,CInterConfig* interConfig);
		int decodeAsBinary(char* buffer,int len,CInterConfig* interConfig);
};
#endif
