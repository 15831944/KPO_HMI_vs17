#ifndef _CTlgItemContainer_H_
#define _CTlgItemContainer_H_

#include "CTlgAssignment.h"
#include "CTlgWrapper.h"

using namespace System;
using namespace System::Collections;

ref class CTlgItemContainer
{
  public:
    CTlgItemContainer(String^ tlgBody,CTlgAssignment^ tlgAss,CTlgWrapper^ wrSource,CTlgWrapper^ wrDest);
    ~CTlgItemContainer();
    String^ getTlgLine();
    String^ getDestTlgName();
  private:
    String^ TlgName;
    String^ DestTlgName;
    ArrayList^ ItemList;

    void intiTlgItem(String^ tlgBody,CTlgAssignment^ tlgAss,CTlgWrapper^ wrDest,CTlgWrapper^ wrSource);
    array <String^>^ tlgBodyParser(String^ line);
};
#endif