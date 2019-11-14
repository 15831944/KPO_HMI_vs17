using System;
using System.Collections;

namespace DBClassCodeUtility
{
  public class MethodComparer : IComparer
  {
    ArrayList mrs = CData.Instance.getMethodRuleSet();

    // Calls CaseInsensitiveComparer.Compare with the parameters
    int IComparer.Compare(Object x, Object y)
    {
      if (mrs.Count > 0)
      {
        int index = 0;
        foreach (string s in mrs)
        {
          int found = 0;
          index++;
          // ruleset for manual methods
          if ( x.ToString().Contains(s) )
          {
            x = x.ToString().Insert(0, "AAA" + index.ToString());
            found++;
          }
          if ( y.ToString().Contains(s) )
          {
            y = y.ToString().Insert(0, "AAA" + index.ToString());
            found++;
          }
          if ( found == 2 )
          {
            break;
          }
        }
      }

      int retValue = (new CaseInsensitiveComparer()).Compare(x, y);
      return (retValue);
    }
  }
}
