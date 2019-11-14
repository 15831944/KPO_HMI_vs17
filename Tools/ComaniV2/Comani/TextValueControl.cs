using System;
using System.ComponentModel;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;

namespace Comani
{
  public partial class TextValueControl : TextBox, IValueControl
  {
    public TextValueControl()
    {
      InitializeComponent();
    }

    public TextValueControl(IContainer container)
    {
      container.Add(this);

      InitializeComponent();
    }

    #region IValueControl Members

    public void setValue(object value)
    {
      Text = value.ToString();
    }

    #endregion
  }
}
