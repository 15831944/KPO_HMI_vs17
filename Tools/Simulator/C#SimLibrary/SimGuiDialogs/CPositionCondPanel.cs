using System;
using System.ComponentModel;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;

namespace SimGuiDialogs
{
  public partial class CPositionCondPanel : System.Windows.Forms.Panel
  {
    public enum ModeBoxValue { First, Last, All, FromTo, Custom };

    //Deligates
    public delegate void AddPositionCondPanelTyp();
    public delegate void RemovePositionCondPanelTyp(CPositionCondPanel panel);



    public CPositionCondPanel(String[] tlgNames, Dictionary<String, List<int>> list)
    {
      InitializeComponent();
      init(tlgNames);
      this.mList = list;
      mAllList = new List<int>();
      foreach (List<int> l in mList.Values)
        foreach (int ll in l)
          mAllList.Add(ll);
    }

    private Dictionary<String, List<int>> mList;
    private List<int> mAllList;
    private AddPositionCondPanelTyp AddPositionCondPanelDel;
    private RemovePositionCondPanelTyp RemovePositionCondPanelDel;
    private System.Windows.Forms.ComboBox cmbItemsBox;
    private System.Windows.Forms.ComboBox cmbModeBox;
    private System.Windows.Forms.Button butRemove;
    private System.Windows.Forms.Button butAdd;
    private System.Windows.Forms.TextBox txtPosTextBox;
    private System.Windows.Forms.Label labCount;
    private System.Windows.Forms.Panel panFromToView;
    private System.Windows.Forms.NumericUpDown numFrom;
    private System.Windows.Forms.NumericUpDown numTo;

    //private static Regex rx = new Regex(@"(\d*|\d\;|-)*");
    //private static Regex rx = new Regex(@"(([0-9]{1,9})+(,|-)?)*");
    private static Regex rx = new Regex(@"(([0-9]{1,9})+(,)?)*");


    //public CPositionCondPanel(IContainer container)
    //{
    //  container.Add(this);
    //  InitializeComponent();
    //}


    //Event - Methodes
    private void butAdd_Click(object sender, EventArgs e)
    {
      if (this.AddPositionCondPanelDel != null)
        this.AddPositionCondPanelDel.Invoke();
    }
    private void butRemove_Click(object sender, EventArgs e)
    {
      if (this.RemovePositionCondPanelDel != null)
        this.RemovePositionCondPanelDel.Invoke(this);
    }
    //Set - Methodes
    public void setAddPositionCondPanelDel(AddPositionCondPanelTyp del)
    {
      this.AddPositionCondPanelDel = del;
    }
    public void setRemovePositionCondPanelDel(RemovePositionCondPanelTyp del)
    {
      this.RemovePositionCondPanelDel = del;
    }
    public void setButAddView(bool value)
    {
      this.butAdd.Visible = value;
    }
    private void init(String[] tlgNames)
    {
      this.Height = 20;
      //
      this.cmbItemsBox = new System.Windows.Forms.ComboBox();
      this.cmbModeBox = new System.Windows.Forms.ComboBox();
      this.butRemove = new System.Windows.Forms.Button();
      this.butAdd = new System.Windows.Forms.Button();
      this.txtPosTextBox = new System.Windows.Forms.TextBox();
      this.labCount = new System.Windows.Forms.Label();
      // labCount;
      this.labCount.Dock = System.Windows.Forms.DockStyle.Left;
      this.labCount.AutoSize = false;
      this.labCount.Width = 50;
      this.labCount.Text = "";
      this.labCount.Name = "labCount";
      this.labCount.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
      // txtPosTextBox
      this.txtPosTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
      this.txtPosTextBox.Name = "txtPosTextBox";
      this.txtPosTextBox.Visible = false;
      // cmbModeBox
      this.cmbModeBox.Dock = System.Windows.Forms.DockStyle.Left;
      this.cmbModeBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
      this.cmbModeBox.Items.AddRange(new object[] {
            "First",
            "Last",
            "All",
            "From .. To ..",
            "Custom ..."});
      this.cmbModeBox.Name = "cmbModeBox";
      this.cmbModeBox.Size = new System.Drawing.Size(100, 20);
      this.cmbModeBox.SelectedIndexChanged += new System.EventHandler(this.cmbModeBox_SelectedIndexChanged);
      this.cmbModeBox.Enabled = false;

      // cmbItemsBox
      this.cmbItemsBox.Dock = System.Windows.Forms.DockStyle.Left;
      this.cmbItemsBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
      this.cmbItemsBox.FormattingEnabled = true;
      this.cmbItemsBox.Name = "cmbItemsBox";
      this.cmbItemsBox.Size = new System.Drawing.Size(100, 20);
      //this.cmbItemsBox.Items.AddRange(tlgNames);
      this.cmbItemsBox.Items.Add("All Tlg's");
      foreach (String s in tlgNames)
        this.cmbItemsBox.Items.Add(s);
      this.cmbItemsBox.SelectedIndexChanged += new System.EventHandler(this.cmbItemsBox_SelectedIndexChanged);
      // butRemove
      this.butRemove.Dock = System.Windows.Forms.DockStyle.Right;
      this.butRemove.Name = "butRemove";
      this.butRemove.Size = new System.Drawing.Size(55, 20);
      this.butRemove.Text = "Remove";
      // butAdd
      this.butAdd.Dock = System.Windows.Forms.DockStyle.Right;
      this.butAdd.Name = "butAdd";
      this.butAdd.Size = new System.Drawing.Size(55, 20);
      this.butAdd.Text = "Add";


      //Events
      this.butAdd.Click += new System.EventHandler(this.butAdd_Click);
      this.butRemove.Click += new System.EventHandler(this.butRemove_Click);


      //Panel From To
      this.panFromToView = new Panel();
      this.numFrom = new NumericUpDown();
      this.numTo = new NumericUpDown();

      this.panFromToView.Dock = System.Windows.Forms.DockStyle.Fill;
      this.panFromToView.Visible = false;

      numTo.Dock = System.Windows.Forms.DockStyle.Left;
      numTo.Minimum = 2;
      numTo.Width = 70;
      this.panFromToView.Controls.Add(numTo);

      Label tmpLab = new Label();
      tmpLab.Text = "To:";
      tmpLab.Width = 20;
      tmpLab.Dock = System.Windows.Forms.DockStyle.Left;
      this.panFromToView.Controls.Add(tmpLab);

      numFrom.Dock = System.Windows.Forms.DockStyle.Left;
      numFrom.Minimum = 1;
      numFrom.Width = 70;
      this.panFromToView.Controls.Add(numFrom);

      tmpLab = new Label();
      tmpLab.Text = "From:";
      tmpLab.Width = 35;
      tmpLab.Dock = System.Windows.Forms.DockStyle.Left;
      this.panFromToView.Controls.Add(tmpLab);

      this.Controls.Add(this.panFromToView);
      this.Controls.Add(this.txtPosTextBox);
      this.Controls.Add(this.cmbModeBox);
      this.Controls.Add(this.butRemove);
      this.Controls.Add(this.cmbItemsBox);
      this.Controls.Add(this.labCount);
      this.Controls.Add(this.butAdd);
    }

    private void cmbItemsBox_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (cmbItemsBox.SelectedIndex < 0)
      {
        cmbModeBox.Enabled = false;
        labCount.Enabled = false;
        cmbModeBox.SelectedIndex = 0;
      }

      labCount.Enabled = true;

      //if (this.mList.ContainsKey((String)cmbItemsBox.SelectedItem))
      //  this.labCount.Text = this.mList[(String)cmbItemsBox.SelectedItem].Count.ToString();
      //else
      //  this.labCount.Text = "0";

      cmbModeBox.Enabled = true;
      cmbModeBox.SelectedIndex = 0;
      this.txtPosTextBox.Text = "";
      cmbModeBox_SelectedIndexChanged(null, null);
    }

    private void cmbModeBox_SelectedIndexChanged(object sender, EventArgs e)
    {
      //this.txtPosTextBox.Enabled = false;
      //Anzahl der Telegrammen im Containar bezogen aus den selektierten Wert im ItemComboxbox
      int total = 0;
      //Wenn All
      if (cmbItemsBox.SelectedIndex == 0)
        total = this.mAllList.Count;
      else if (this.mList.ContainsKey((String)cmbItemsBox.SelectedItem))
        total = this.mList[(String)cmbItemsBox.SelectedItem].Count;
      else
        total = -1;

      if (total > 0)
      {
        //Custom
        if (cmbModeBox.SelectedIndex == (int)ModeBoxValue.Custom)
        {
          this.txtPosTextBox.Visible = true;
          this.panFromToView.Visible = false;
          //this.txtPosTextBox.Enabled = true;
          this.labCount.Text = "";
          this.labCount.Text = "../" + total.ToString();
        }
        else if (cmbModeBox.SelectedIndex == (int)ModeBoxValue.FromTo)
        {
          this.numTo.Maximum = total;
          this.numTo.Value = total;
          this.txtPosTextBox.Visible = false;
          this.panFromToView.Visible = true;
          //this.txtPosTextBox.Enabled = true;
          this.labCount.Text = "";
        }
        //First,Last
        else
        {
          if (cmbModeBox.SelectedIndex == (int)ModeBoxValue.First || cmbModeBox.SelectedIndex == (int)ModeBoxValue.Last)
            this.labCount.Text = "1/" + total.ToString();
          else if (cmbModeBox.SelectedIndex == (int)ModeBoxValue.All) //All
            this.labCount.Text = total.ToString() + "/" + total.ToString();
          else
            this.labCount.Text = "0";

          this.txtPosTextBox.Visible = false;
          this.panFromToView.Visible = false;
        }
      }
      else
      {
        this.labCount.Text = "0";
        this.txtPosTextBox.Visible = false;
        this.panFromToView.Visible = false;
      }


      //int width = System.Windows.Forms.TextRenderer.MeasureText(this.labCount.Text, this.labCount.Font).Width;
      //if (width > panCountMaxWidth)
      //{
      //  panCountMaxWidth = width;

      //}
    }

    //private List<int> match(String text)
    //{
    //  if (text == null)
    //    return null;

    //  List<int> ret = new List<int>();
    //  int semiIndex = 0;
    //  int minusIndex = 0;
    //  int preminus;
    //  int postminus;
    //  String subStr = null;
    //  String posStr = rx.Match(text).Value;

    //  System.Windows.Forms.MessageBox.Show(null, posStr,
    //                "",
    //                MessageBoxButtons.OK,
    //                MessageBoxIcon.Information);




    //  while (posStr.Length > 0)
    //  {
    //    semiIndex = posStr.IndexOf(",");
    //    minusIndex = posStr.IndexOf("-");

    //    //Nur die Zahlen
    //    if (semiIndex < 0 && minusIndex < 0)
    //    {
    //      if (posStr.Length > 0)
    //        ret.Add((int)Convert.ToDecimal(posStr));
    //      break;
    //    }
    //    else if ((minusIndex < 0 && semiIndex > 0) || (semiIndex < minusIndex))
    //    {
    //      subStr = posStr.Substring(0, semiIndex);
    //      posStr = posStr.Remove(0, semiIndex+1);


    //      System.Windows.Forms.MessageBox.Show(null, subStr,
    //                          "",
    //                          MessageBoxButtons.OK,
    //                          MessageBoxIcon.Information);



    //      if (subStr.Length > 0)
    //        ret.Add((int)Convert.ToDecimal(subStr));
    //    }
    //    else
    //    {




    //    }
    //  }

    //  return ret;
    //}

    private List<int> MatchCustom(String text)
    {
      if (text == null)
        return null;

      List<int> ret = new List<int>();
      int commaIndex = 0;
      String posStr = rx.Match(text).Value;
      String subStr = null;

      System.Windows.Forms.MessageBox.Show(null, text + "\n\n\n" + posStr,
                          "",
                          MessageBoxButtons.OK,
                          MessageBoxIcon.Information);
      
      while (posStr.Length > 0)
      {
        commaIndex = posStr.IndexOf(",");
        if (commaIndex >= 0)
        {
          subStr = posStr.Substring(0, commaIndex);
          posStr = posStr.Remove(0, commaIndex + 1);

          if (subStr.Length > 0)
            ret.Add((int)Convert.ToDecimal(subStr));

        } //Nur die Zahlen
        else
        {
          if (posStr.Length > 0)
            ret.Add((int)Convert.ToDecimal(posStr));
          break;
        }
      }
      
      return ret;
    }

    public List<int> getPositions()
    {
      if (cmbItemsBox.SelectedIndex < 0)
        return null;


      List<int> ret = new List<int>();
      //Wenn Alle Telegramme
      if (cmbItemsBox.SelectedIndex == 0)
      {
        //All
        if (cmbModeBox.SelectedIndex == (int)ModeBoxValue.All)
        {
          return this.mAllList;
        }
        //First
        if (cmbModeBox.SelectedIndex == (int)ModeBoxValue.First)
        {
          ret.Add(this.mAllList[0]);
          return ret;
        }
        //Last
        if (cmbModeBox.SelectedIndex == (int)ModeBoxValue.Last)
        {
          ret.Add(this.mAllList[this.mAllList.Count-1]);
          return ret;
        }
        //FromTo
        if (cmbModeBox.SelectedIndex == (int)ModeBoxValue.FromTo)
        {
          if (this.numFrom.Value > this.numTo.Value)
            return null;

          for (int i = (int)this.numFrom.Value; i <= (int)this.numTo.Value; i++)
            ret.Add(i);
          return ret;
        }
        //Custom
        if (cmbModeBox.SelectedIndex == (int)ModeBoxValue.Custom)
        {
          ret = this.MatchCustom(this.txtPosTextBox.Text);
          if (ret.Count <= 0)
            return null;

          for (int i = 0; i < ret.Count; i++)
            if (!this.mAllList.Contains(ret[i]))
              ret.RemoveAt(i);

          return ret;
        }
      } //Ausgewaehltes Telegramm
      else
      {
        if ((!this.mList.ContainsKey((String)cmbItemsBox.SelectedItem)) || (this.mList[(String)cmbItemsBox.SelectedItem].Count == 0))
          return null;

        //All
        if (cmbModeBox.SelectedIndex == (int)ModeBoxValue.All)
        {
          return this.mList[(String)cmbItemsBox.SelectedItem];
        }
        //First
        if (cmbModeBox.SelectedIndex == (int)ModeBoxValue.First)
        {
          ret.Add(this.mList[(String)cmbItemsBox.SelectedItem][0]);
          return ret;
        }
        //Last
        if (cmbModeBox.SelectedIndex == (int)ModeBoxValue.Last)
        {
          ret.Add(this.mList[(String)cmbItemsBox.SelectedItem][this.mList[(String)cmbItemsBox.SelectedItem].Count - 1]);
          return ret;
        }
        //FromTo
        if (cmbModeBox.SelectedIndex == (int)ModeBoxValue.FromTo)
        {
          if (this.numFrom.Value > this.numTo.Value)
            return null;

          for (int i = (int)this.numFrom.Value; i <= (int)this.numTo.Value; i++)
            ret.Add(this.mList[(String)cmbItemsBox.SelectedItem][i - 1]);

          return ret;
        }
        //Custom
        if (cmbModeBox.SelectedIndex == (int)ModeBoxValue.Custom)
        {

          List<int> tmp = this.mList[(String)cmbItemsBox.SelectedItem];
          List<int> tmpMatch = this.MatchCustom(this.txtPosTextBox.Text);

          if (tmpMatch.Count <= 0)
            return null;

          for (int i = 0; i < tmpMatch.Count; i++)
            if (tmpMatch[i] <= tmp.Count && (!ret.Contains(tmp[i])))
              ret.Add(tmp[i]);

          String mess = "";
          foreach (int i in ret)
            mess += i + ",";
                      
          return ret;
        }
      }
      return null;
    }
  }
}
