// Meltshop.h
#include "IBASConnection.h"

#pragma once

using namespace System;
using namespace System::Collections::Generic;


namespace Meltshop {

  public ref class MeltshopPlugin : public Comani::IComaniSource
  {
  public:
    MeltshopPlugin();
    virtual Comani::Telegram^ createTelegram(LibTelcom::TelegramDefinition^ definition);
    virtual bool configureSource();
    virtual String^ getSourceName();
  private:
    String^ contextName;
    Dictionary<String^, IBASConnection^>^ connDict;
  };
}
