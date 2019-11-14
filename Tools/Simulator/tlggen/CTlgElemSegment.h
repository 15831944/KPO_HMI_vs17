// Copyright 2006 SMS - Demag AG

#ifndef _CTlgElemSegment_H_
#define _CTlgElemSegment_H_

#include "CTlgElem.h"
#include <vector>
#include <string>

//------------------------------------------------------------------
// NAME : CTlgElemSegment.h
// DESCR: Mit der Klasse werden Rekords und Listen Elementen verwaltet.
// DATE:
// AUTOR: Emeljanov Anatolij
//------------------------------------------------------------------
class CTlgElemSegment : public CTlgElem
{
	public:
		CTlgElemSegment(const CElemDescription::TransportType transp,const CElemDescription::ElementType elemType,const std::string& name="");
		CTlgElemSegment(const std::string& name,CElemDescription::ElementType elemType,const long count = 0);
		CTlgElemSegment(const CTlgElemSegment& Obj);
		CTlgElemSegment(int index);
		virtual ~CTlgElemSegment();
		virtual CTlgElem* clone() const;
		virtual  void getValue(std::string& value) const;
		virtual void setValue(const std::string& val,CInterConfig* interConf);
		virtual void setDefaultValue();
		virtual int serialize(char* buffer,int len,CInterConfig* interConfig);
		virtual int compare(const std::string& val,const std::string& subElemName);
		virtual void getElemAsString(std::string& elem,const std::string& del);
		virtual int getSubElemCount() const;
		virtual CTlgElem* getSubElem(int index) const;
		virtual CTlgElem* getSubElem(const std::string& id) const;
		virtual void addSubElem(CTlgElem* elem);
		virtual int decodeElem(char* bytes,int count,CInterConfig* interConfig);
    virtual int getTransBytesCount() const;
	private:
		// Container fuer Subelemente
		std::vector<CTlgElem*> ElemVector;		
};
#endif
