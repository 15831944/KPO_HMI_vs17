using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace SimGuiDialogs
{
  public partial class CMultiFilterForm : Form
  {
    private List<SimGuiDialogs.CMultiFilterPanel> panStack;
    public CMultiFilterForm(Panel parent,String[] regExp)
    {
      InitializeComponent();
      this.TopLevel = false;
      this.Parent = parent;
      this.Dock = DockStyle.Fill;
      this.panStack = new List<CMultiFilterPanel>();
      //this.Size = new Size(this.Size.Width,1);
      //this.Size.Height(1); ;
      if (regExp == null)
        this.NewPanel();
      else
        ReadLastRegExp(regExp);

    }

    private void ReadLastRegExp(String[] regExp)
    {
      foreach (String reg in regExp)
      {
        this.NewPanel();
        this.panStack[this.panStack.Count-1].FilterText = reg;
      }
    }

    private void NewPanel()
    {
      if (this.panStack.Count > 0)
        this.panStack[panStack.Count-1].setButAddView(false);
      
      CMultiFilterPanel tmp = new CMultiFilterPanel();
      tmp.setAddFilterPanelDel(new CMultiFilterPanel.AddFilterPanelTyp(this.NewPanel));
      tmp.setRemoveFilterPanelDel(new CMultiFilterPanel.RemoveFilterPanelTyp(this.RemoveFilterPanel));
      this.panStack.Add(tmp);
      this.Controls.Add(tmp);
      tmp.Dock = DockStyle.Top;
      this.Refresh();

      //TabIndex bei allen PanelForm korigieren
      int index = panStack.Count - 1;
      foreach (CMultiFilterPanel pan in this.panStack)
        pan.TabIndex = index--;

      //this.Size = new Size(this.Size.Width, this.Size.Height + tmp.Size.Height);
      tmp.Focus();
    }

    private void RemoveFilterPanel(CMultiFilterPanel panel)
    {
      if (panel!= null && this.panStack.Count > 1)
      {
        //this.Size = new Size(this.Size.Width, this.Size.Height - panel.Size.Height);
        this.Controls.Remove(panel);
        this.panStack.Remove(panel);
        this.panStack[panStack.Count - 1].setButAddView(true);
        this.panStack[panStack.Count - 1].Focus();

      }
    }

    public String[] getRegExAsString()
    {
      String[] ret = new String[this.panStack.Count];
      int index = 0;
      foreach (CMultiFilterPanel pan in this.panStack)
      {
        ret[index++] = pan.FilterText;
      }
      return ret;
    }

    public void Clear()
    {
      if (panStack == null)
        return;
      this.panStack.Clear();
      this.Controls.Clear();
      NewPanel();
    }

    private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {

    }
  }
}