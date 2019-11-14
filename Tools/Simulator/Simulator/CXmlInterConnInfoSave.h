// Copyright 2006 SMS - Demag AG

#ifndef _CXmlInterConnInfoSave_H_
#define _CXmlInterConnInfoSave_H_
//------------------------------------------------------
#include "CInterConnectionListe.h"
//------------------------------------------------------
using namespace System;
using namespace System::Xml;
//------------------------------------------------------
//-------------------------------------------
// Name:   CXmlInterConnInfoSave.h
// Descr:  Schreibt Vebindungskonfiguration in einer 
//         Verbindungskonfigurationsdatei
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
public ref class CXmlInterConnInfoSave
{
    public:
          CXmlInterConnInfoSave(CInterConnectionListe^ liste);
          ~CXmlInterConnInfoSave();
          int saveConnectionInfo(String^ path);
    private:
          void writeElement(String^ elem,String^ val);

          CInterConnectionListe^ InterConnectionListe;
          XmlTextWriter^ Writer;
};


#endif