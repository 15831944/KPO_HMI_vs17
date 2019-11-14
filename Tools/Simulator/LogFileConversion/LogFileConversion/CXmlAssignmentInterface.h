#ifndef _CXmlAssignmentInterface_H_
#define _CXmlAssignmentInterface_H_

#include "CInterAssignment.h"
#include "CTlgAssignment.h"

using namespace System;
using namespace System::Xml;

public ref class CXmlAssignmentInterface
{
  public:
    CXmlAssignmentInterface();
    ~CXmlAssignmentInterface();
    void setAssignmentCofigFileForRead(String^ path);
    void readAssignmentCofigFile(CInterAssignment^ interAss);
    void getAssignmentInterfaces(String^& sourceName,String^& destName);
    int writeAssignmentInterface(String^ path,CInterAssignment^ interAss);
  private:
    String^ SourceName;
    String^ DestinationName;
    String^ Path;
    //XmlTextReader^ xmlReader;
};
#endif
