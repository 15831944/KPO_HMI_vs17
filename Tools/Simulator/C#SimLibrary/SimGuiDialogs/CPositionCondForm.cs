using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace SimGuiDialogs
{
  public partial class CPositionCondForm : Form
  {
    private List<SimGuiDialogs.CPositionCondPanel> panStack;
    private String[] mTlgNames;
    private Dictionary<String, List<int>> mList;
    public CPositionCondForm(Panel parent)
    {
      InitializeComponent();
      this.TopLevel = false;
      this.Parent = parent;
      this.panStack = new List<CPositionCondPanel>();
      this.mTlgNames = null;
      this.mList = null;
    }

    public void Clear()
    {
      if (panStack == null)
        return;
      panStack.Clear();
      this.Controls.Clear();
      mTlgNames = null;
      this.mList = null;
    }

    public void setTlgNames(String[] names, Dictionary<String, List<int>> list)
    {
      this.Clear();
      this.mTlgNames = names;
      this.mList = list;
      NewPanel();
    }

    private void NewPanel()
    {
      if (mTlgNames == null || mList == null)
        return;

      if (this.panStack.Count > 0)
        this.panStack[panStack.Count - 1].setButAddView(false);

      //CPositionCondPanel tmp = new CPositionCondPanel();
      CPositionCondPanel tmp = new CPositionCondPanel(this.mTlgNames, this.mList);
      tmp.setAddPositionCondPanelDel(new CPositionCondPanel.AddPositionCondPanelTyp(this.NewPanel));
      tmp.setRemovePositionCondPanelDel(new CPositionCondPanel.RemovePositionCondPanelTyp(this.RemovePositionCondPanel));
      this.panStack.Add(tmp);
      this.Controls.Add(tmp);
      tmp.Dock = DockStyle.Top;
      this.Refresh();

      //TabIndex bei allen PanelForm korigieren
      int index = panStack.Count - 1;
      foreach (CPositionCondPanel pan in this.panStack)
        pan.TabIndex = index--;

      //this.Size = new Size(this.Size.Width, this.Size.Height + tmp.Size.Height);
      tmp.Focus();
    }

    private void RemovePositionCondPanel(CPositionCondPanel panel)
    {
      if (panel != null && this.panStack.Count > 1)
      {
        //this.Size = new Size(this.Size.Width, this.Size.Height - panel.Size.Height);
        this.Controls.Remove(panel);
        this.panStack.Remove(panel);
        this.panStack[panStack.Count - 1].setButAddView(true);
        this.panStack[panStack.Count - 1].Focus();
      }
    }

    public List<int> getPositions()
    {
      List<int> tmp = null;
      List<int> ret = new List<int>();
      foreach (CPositionCondPanel p in panStack)
      {
        tmp = p.getPositions();
        if (tmp != null)
        {
          foreach (int i in tmp)
            if (!ret.Contains(i))
              ret.Add(i);
        }
      }
      return ret;
    }
  }
}