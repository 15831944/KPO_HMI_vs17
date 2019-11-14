#pragma once
// Copyright 2006 SMS - Demag AG
//-------------------------------------------
// Name:  CXmlCyclicTlgWriter.h
// Descr: Schreibt alle benoetigte Konfiguration  
//        in eine XML - Datei
// Date:  21.11.08
// Autor: Emeljanov Alexander 
//--------------------------------------------

#ifndef _CXmlCyclicTlgWriter_H_
#define  _CXmlCyclicTlgWriter_H_

#include "CItemWrapper.h"
#include "CCyclicElemTable.h"

using namespace System;
using namespace System::Xml;

public ref class CXmlCyclicTlgWriter
{
public:
	CXmlCyclicTlgWriter(void);
	~CXmlCyclicTlgWriter(void);
	void writeCyclicItems(String^ path);
private:
	XmlTextWriter^ Writer;

  void writeItem(CItemWrapper^ item,CCyclicElemTable^ elemTable);
};
#endif