// Copyright 2006 SMS - Demag AG

#ifndef _CTlgElemDoubl_H_
#define _CTlgElemDoubl_H_

#include "CTlgElem.h"
#include "CExpLimitError.h"

//------------------------------------------------------------------
// NAME : CTlgElemDouble.h
// DESCR: Mit der Klasse werden Dauble Werte(Gletkommazahlen mit die
//        Laenge 8 - Bytes) verwaltet.
// DATE:
// AUTOR: Emeljanov Anatolij
//------------------------------------------------------------------
class CTlgElemDoubl : public CTlgElem
{
	public:
		CTlgElemDoubl(const CElemDescription::TransportType transp,const int len,
					        const double val,const std::string& name);
		CTlgElemDoubl(int index);
		CTlgElemDoubl(const CTlgElemDoubl& Obj);
		virtual ~CTlgElemDoubl();
		virtual CTlgElem* clone() const;
		//virtual CTlgElem* getSubElem(int index) const;
		//virtual CTlgElem* getSubElem(const std::string& id) const;
		virtual void getValue(std::string& value)const;
		virtual void setValue(const std::string& val,CInterConfig* interConf);
		virtual void setDefaultValue();
		virtual int serialize(char* buffer,int len,CInterConfig* interConfig);
		virtual int compare(const std::string& val,const std::string& subElemName);
		virtual void getElemAsString(std::string& elem,const std::string& del);
		//virtual int getSubElemCount() const;
		//virtual void addSubElem(CTlgElem* elem);
		virtual int decodeElem(char* bytes,int count,CInterConfig* interConfig);
		virtual int getTransBytesCount() const;
	private:
		//! Value des Telegrammelements
		double Value;
		int serializeAsASCII(char* buffer,int len,CInterConfig* interConfig);
		int serializeAsBinary(char* buffer,int len,CInterConfig* interConfig);
		int decodeAsASCII(char* buffer,int len,CInterConfig* interConfig);
		int decodeAsBinary(char* buffer,int len,CInterConfig* interConfig);
};
#endif
