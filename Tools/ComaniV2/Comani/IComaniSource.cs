using System;
using System.Collections.Generic;
using System.Text;
using LibTelcom;

namespace Comani
{
  public interface IComaniSource
  {
    Telegram createTelegram(TelegramDefinition definition);
    string getSourceName();
    bool configureSource();
  }
}
