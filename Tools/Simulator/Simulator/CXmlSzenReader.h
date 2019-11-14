
#ifndef _CXmlSzenReader_H_
#define _CXmlSzenReader_H_

#include "CSzenarium.h"
#include "CSzenItem.h"
#include "CTlgWrapper.h"
//#include "CBaseTlgFactoryWrapper.h"
#include  "CInterBaseManager.h"

using namespace System;
using namespace System::Xml;

public ref class CXmlSzenReader
{
  public:
    CXmlSzenReader();
    ~CXmlSzenReader();
    CSzenarium^ loadSzenarium(String^ path,ArrayList^ protoInterSet);
  private:
    XmlTextReader^ Reader;
    CSzenarium^ Szen;
    ArrayList^ PrototypTlgSet;
    //!!!CBaseTlgFactoryWrapper* TlgFactory;
    void createSzen();
    void addTelegram();
    String^ getTlgId(String^ line);

    CItemWrapper^ createTlg(String^ name);
};

#endif