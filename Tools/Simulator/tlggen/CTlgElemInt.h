// Copyright 2006 SMS - Demag AG

#ifndef _CTlgElemInt_H_
#define _CTlgElemInt_H_

#include "CTlgElem.h"
#include "CExpLimitError.h"

//------------------------------------------------------------------
// NAME : CTlgElemInt.h
// DESCR: Die Klasse verwaltet die Telegrammelemente von Typ Integer.
// DATE:
// AUTOR: Emeljanov Anatolij
//------------------------------------------------------------------
class CTlgElemInt : public CTlgElem
{
	public:
		CTlgElemInt(const CElemDescription::TransportType transp,
					      const int len,int val,const std::string& name="");
		CTlgElemInt(int index);
		CTlgElemInt(const CTlgElemInt& Obj);
		virtual ~CTlgElemInt();
		virtual CTlgElem* clone() const;
		virtual void getValue(std::string& value) const;
		virtual void setValue(const std::string& val,CInterConfig* interConf);
		virtual void setDefaultValue();
		virtual int serialize(char* buffer,int len,CInterConfig* interConfig);
		virtual int compare(const std::string& val,const std::string& subElemName);
		virtual void getElemAsString(std::string& elem,const std::string& del);
		//virtual int getSubElemCount() const;
		//virtual CTlgElem* getSubElem(int index) const; 
		//virtual CTlgElem* getSubElem(const std::string& id) const;
		//virtual void addSubElem(CTlgElem* elem);
		virtual int decodeElem(char* bytes,int count,CInterConfig* interConfig);
		virtual int getTransBytesCount() const;
	private:
		//! Value des Telegrammelements
		int Value;
		int serializeAsASCII(char* buffer,int len,CInterConfig* interConfig);
		int serializeAsBinary(char* buffer,int len,CInterConfig* interConfig);
		int decodeAsASCII(char* buffer,int len,CInterConfig* interConfig);
		int decodeAsBinary(char* buffer,int len,CInterConfig* interConfig);
};
#endif 
