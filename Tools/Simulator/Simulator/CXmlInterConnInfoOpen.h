// Copyright 2006 SMS - Demag AG

#ifndef _CXmlInterConnInfoOpen_H_
#define _CXmlInterConnInfoOpen_H_
//-------------------------------------------------
#include "CInterConnectionListe.h"
//-------------------------------------------------
using namespace System;
using namespace System::Xml;
//------------------------------------------------
//-------------------------------------------
// Name:   CXmlInterConnInfoOpen.h
// Descr:  Liest Vebindungskonfiguration aus einer 
//         Verbindungskonfigurationsdatei
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
public ref class CXmlInterConnInfoOpen
{
    public:
            CXmlInterConnInfoOpen(CInterConnectionListe^ liste);
            ~CXmlInterConnInfoOpen();

            int readInterConnectionInfo(String^ path);
    private:
            
            void setInterConnInfo(String^ name);
            CConnectionInfo::ConnectionType getConnType(String^ connTypeStr);

            CInterConnectionListe^ InterConnectionListe;
            XmlTextReader^ Reader;
};


#endif