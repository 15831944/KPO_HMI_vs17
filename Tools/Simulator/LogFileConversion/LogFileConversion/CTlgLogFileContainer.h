#ifndef _CTlgLogFileContainer_H_
#define _CTlgLogFileContainer_H_

#include "CInterAssignment.h"

using namespace System;
using namespace System::Collections;

ref class CTlgLogFileContainer
{
  public:
    CTlgLogFileContainer();
    ~CTlgLogFileContainer();
    void readLogFile(String^ path,CInterAssignment^ interAss);
    void writeLogFile(String^ path);
    int getTlgCount();
    String^ getTlgAsString(int index);
    String^ getDestTlgName(int index);
  private:
    String^ Path;
    ArrayList^ TlgLogFileContainer;

    String^ getTlgName(String^ line);
    String^ getTlgBody(String^ line);
};
#endif