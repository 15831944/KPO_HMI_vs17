
#ifndef _CXmlCyclicTlgReader_H_
#define _CXmlCyclicTlgReader_H_

#include "CSzenarium.h"
#include "CSzenItem.h"
#include "CTlgWrapper.h"
#include "CSzenarium.h"
#include "CItemWrapper.h"
#include "CCyclicElemTable.h"

using namespace System;
using namespace System::Xml;
using namespace System::Collections::Generic;

public ref class CXmlCyclicTlgReader
{
  public: delegate void MessageXmlCyclicReaderDelTyp(String^ mes,int typ);
  public:
    CXmlCyclicTlgReader();
    ~CXmlCyclicTlgReader();
    void readCyclicItems(String^ path,List<CTlgInterfaceWrapper^>^ interCon);
    void setMessageXmlCyclicReaderDelTyp(MessageXmlCyclicReaderDelTyp^ typ);
    CCyclicElemTable^ readItemAllElem(CItemWrapper^ item);
  private:
    XmlTextReader^ Reader;
    MessageXmlCyclicReaderDelTyp^ MessageXmlCyclicReaderDel;
    //ArrayList^ PrototypTlgSet;

};

#endif