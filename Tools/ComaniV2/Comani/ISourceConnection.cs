using System;
using System.Collections.Generic;
using System.Text;

namespace Comani
{
  public interface ISourceConnection
  {
    object readValue(string itemName, LibTelcom.TelcomDataType dataType);
  }
}
