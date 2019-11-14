using System;
using System.ComponentModel;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Windows.Forms;

namespace SimGuiDialogs
{
  public partial class CMultiFilterPanel : System.Windows.Forms.Panel
  {
    //Deligates
    public delegate void AddFilterPanelTyp ();
    public delegate void RemoveFilterPanelTyp (CMultiFilterPanel panel);
    
    //Members
    private Button butAdd;
    private Button butRemove;
    private TextBox txtFilterBox;
    private AddFilterPanelTyp AddFilterPanelDel;
    private RemoveFilterPanelTyp RemoveFilterPanelDel;
    
    public CMultiFilterPanel()
    {
      InitializeComponent();
      initView();
    }
    private void initView()
    {
      this.butAdd = new Button();
      this.butRemove = new Button();
      this.txtFilterBox = new TextBox();

      this.butAdd.Height = 20;
      this.butAdd.Width = 55;
      this.butAdd.Text = "Add";
      this.butAdd.Dock = DockStyle.Right;
      this.butRemove.Height = 20;
      this.butRemove.Width = 55;
      this.butRemove.Text = "Remove";
      this.butRemove.Dock = DockStyle.Right;
      this.txtFilterBox.Height = 20;
      this.txtFilterBox.Dock = DockStyle.Fill;
      this.txtFilterBox.Text = "*";

      this.Controls.Add(this.butRemove);
      this.Controls.Add(this.butAdd);
      this.Controls.Add(this.txtFilterBox);

      //Events
      this.butAdd.Click += new System.EventHandler(this.butAdd_Click);
      this.butRemove.Click += new System.EventHandler(this.butRemove_Click);

      this.Height = 20;
      this.Dock = DockStyle.Top;

      this.AddFilterPanelDel = null;
      this.RemoveFilterPanelDel = null;
    }
    //Event - Methodes
    private void butAdd_Click(object sender, EventArgs e)
    {
      if (this.AddFilterPanelDel != null)
        this.AddFilterPanelDel.Invoke();
    }
    private void butRemove_Click(object sender, EventArgs e)
    {
      if (this.RemoveFilterPanelDel != null)
        this.RemoveFilterPanelDel.Invoke(this);
    }
    //Set - Methodes
    public void setAddFilterPanelDel(AddFilterPanelTyp del)
    {
      this.AddFilterPanelDel = del;
    }
    public void setRemoveFilterPanelDel(RemoveFilterPanelTyp del)
    {
      this.RemoveFilterPanelDel = del;
    }
    public void setButAddView(bool value)
    {
      this.butAdd.Visible = value;
    }
    public String FilterText
    {
      get
      {
        if (this.txtFilterBox.Text == null)
          return "*";
        return this.txtFilterBox.Text;
      }
      set
      {
        if (value != null)
          this.txtFilterBox.Text = value;
        else
          this.txtFilterBox.Text = "*";
      }
    }

    //public CMultiFilterPanel()
    //{
    //  container.Add(this);

    //  InitializeComponent();
    //}
  }
}
