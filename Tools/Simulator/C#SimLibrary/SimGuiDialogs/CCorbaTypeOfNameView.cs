using System;
using System.ComponentModel;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Windows.Forms;

namespace SimGuiDialogs
{
  public partial class CCorbaTypeOfNameView : System.Windows.Forms.Panel
  {
    private Label labDataTypeView;
    private Label labValueView;
    private RichTextBox rtValueBox;
    
    public CCorbaTypeOfNameView()
    {
      InitializeComponent();
      init();
    }

    public CCorbaTypeOfNameView(IContainer container)
    {
      container.Add(this);
      InitializeComponent();
      init();
    }

    private void init()
    {
      Panel tmpPanelTop = new Panel();
      tmpPanelTop.Size = new System.Drawing.Size(10, 50);
      tmpPanelTop.Dock = DockStyle.Top;
      tmpPanelTop.BorderStyle = BorderStyle.FixedSingle;
      //
      //DataType
      Label tmp = new Label();
      tmp.Location = new System.Drawing.Point(0, 0);
      //tmp.Size = System.Drawing.Size(30, 50);
      tmp.Text = "Data Type: ";
      tmpPanelTop.Controls.Add(tmp);
      //
      labDataTypeView = new Label();
      labDataTypeView.Location = new System.Drawing.Point(100, 0);
      labDataTypeView.Text = "none";
      tmpPanelTop.Controls.Add(labDataTypeView);
      //
      //Value
      //tmp = new Label();
      //tmp.Location = new System.Drawing.Point(0, 30);
      //tmp.Text = "Value: ";
      //this.Controls.Add(tmp);
      //   
      Panel tmpPanelMiddle = new Panel();
      tmpPanelMiddle.Dock = DockStyle.Fill;
      //
      rtValueBox = new RichTextBox();
      rtValueBox.Location = new System.Drawing.Point(100, 30);
      rtValueBox.Dock = DockStyle.Fill;
      rtValueBox.ReadOnly = true;
      rtValueBox.WordWrap = false;
      rtValueBox.ScrollBars = RichTextBoxScrollBars.ForcedBoth;
      tmpPanelMiddle.Controls.Add(rtValueBox);
      //
      //labValueView = new Label();
      //labValueView.Text = "none";
      //labValueView.Location = new System.Drawing.Point(100, 30);
      //this.Controls.Add(labValueView);
      this.Controls.Add(tmpPanelMiddle);
      this.Controls.Add(tmpPanelTop);
    }

    public void Clear()
    {
      //labValueView.Text = "";
      labDataTypeView.Text = "";
      rtValueBox.Clear();
    }

    public void setValues(String DataType, String Value)
    {
      if (DataType == null || Value == null)
        return;

      rtValueBox.Text = Value;
      labDataTypeView.Text = DataType;
    }
  }
}
