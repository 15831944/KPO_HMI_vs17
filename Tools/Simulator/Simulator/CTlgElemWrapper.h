// Copyright 2006 SMS - Demag AG

#ifndef _CTlgElemWrapper_H_
#define _CTlgElemWrapper_H_

#include "CTlgElem.h"

using namespace System;

public ref class CTlgElemWrapper
{
public: 
  CTlgElemWrapper(void);
  ~CTlgElemWrapper(void);
  void setTlgElem(CTlgElem* elemtlg);
  String^ setValue(String^ value,String^ interName);
  CTlgElem* getTlgElem();
  int getSubElemCount();
  void getMinMax(String^& min,String^& max);
  void getElemInfo(String^& unit,String^& factor,String^& min,String^& max);
  String^ getElemType();
  String^ getElemTransport();
  int getElemLenght();
  CTlgElem* getSubElem(int id);
  CTlgElem* getSubElem(String^ pathOfName);
  String^ getElemName();
  void getElemValue(String^& value);
  String^ getElemDescription();
	CElemDescription::ElementType getElemTypeAsEnum();
  int compare (String^ val, String^ elemName);
  
  protected:
  //! Referenziert ein Objekt der Klasse CTlg
  CTlgElem* ElemTlg;
};
#endif