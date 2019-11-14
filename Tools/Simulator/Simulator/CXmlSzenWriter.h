
#ifndef _CXmlSzenWriter_H_
#define  _CXmlSzenWriter_H_

#include "CSzenarium.h"
#include "CSzenItem.h"

using namespace System;
using namespace System::Xml;
//using namespace simulator;

public ref class CXmlSzenWriter
{
    public:
           CXmlSzenWriter();
           ~CXmlSzenWriter();
           void writeSzenarium(String^ path,CSzenarium^ szen);
    private:
           XmlTextWriter^ Writer;
           CSzenarium^ Szen;

           String^ getNameSzen(String^ name);
           void writeTlg(int index);
};


#endif