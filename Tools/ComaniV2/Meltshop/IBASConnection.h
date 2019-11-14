#pragma once
#include "BasIntrf_s.h"
#include "CBS_CorbaLib\cCBS_CorbaProxy.h"

using namespace System;
using namespace LibTelcom;

namespace Meltshop
{

  ref class IBASConnection : Comani::ISourceConnection
  {
  public:
    IBASConnection(void);
    virtual Object^ readValue(String^ itemName, LibTelcom::TelcomDataType type);
    void initialize(String^ context, String^ intrfName, String^ plantName);
  private:
    std::string* m_PlantName;
    IBAS::BASIntrf_ptr m_BASIntrf;
  };
}
