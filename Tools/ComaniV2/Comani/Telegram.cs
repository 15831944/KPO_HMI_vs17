using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using LibTelcom;

namespace Comani
{
  public partial class Telegram : UserControl
  {
    protected TelegramDefinition telegramDef;
    protected Dictionary<string, IValueControl> itemControls;
    protected Dictionary<string, LibTelcom.TelegramItem> itemDefs;
    protected ISourceConnection dataSource;

    public Telegram(TelegramDefinition def, ref ISourceConnection source)
    {
      InitializeComponent();
      dataSource = source;
      telegramDef = def;
      itemControls = new Dictionary<string, IValueControl>();
      itemDefs = new Dictionary<string, LibTelcom.TelegramItem>();
      groupBox1.Text = def.TelegramName + " (" + def.Description + ")";

      foreach (LibTelcom.TelegramItem item in def.TelegramItems)
      {
        addItem(item);
      }
    }
    protected virtual void addItem(LibTelcom.TelegramItem item)
    {
      if (item.Count == 1)
        addItem(item.Name, item);
      else
      {
        for (int i = 0; i < item.Count; i++)
          addItem(item.Name + "[" + i.ToString() + "]", item);
      }
    }
    protected virtual void addItemLabel(int rowNo, string text, string description)
    {
      Label l = new Label();
      l.Text = text;
      toolTip1.SetToolTip(l, description);
      tableLayoutPanel1.Controls.Add(l, 0, rowNo);
    }
    protected virtual void addItemControl(int rowNo, Control c)
    {
      tableLayoutPanel1.Controls.Add(c, 1, rowNo);
    }
    protected virtual void addUnitLabel(int rowNo, string unit)
    {
      Label l = new Label();
      l.Text = unit;
      tableLayoutPanel1.Controls.Add(l, 0, rowNo);
    }
    protected virtual void addItem(string name, LibTelcom.TelegramItem item)
    {
      tableLayoutPanel1.RowCount++;      
      int rowNo = tableLayoutPanel1.RowCount - 2;
      addItemLabel(rowNo, name, item.Comment);
      TextValueControl val = new TextValueControl();
      addItemControl(rowNo, val);
      if (item is LibTelcom.PrimitiveItem)
        addUnitLabel(rowNo, (item as LibTelcom.PrimitiveItem).Unit);
      itemControls.Add(name, val);
      itemDefs.Add(name, item);
    }

    public virtual void refresh()
    {
      foreach (string item in itemDefs.Keys)
      {
        if (itemDefs[item] is LibTelcom.PrimitiveItem)
        {
          LibTelcom.PrimitiveItem pi = itemDefs[item] as LibTelcom.PrimitiveItem;
          object val = dataSource.readValue(item, pi.DataType);
          itemControls[item].setValue(val);
        }
      }
    }

    private void button1_Click(object sender, EventArgs e)
    {
      tableLayoutPanel1.ColumnStyles[1].Width = 0;
      refresh();
    }

    private void toolStripButton2_Click(object sender, EventArgs e)
    {
      timer1.Enabled = !(timer1.Enabled);
      if (timer1.Enabled)
        toolStripButton2.Image = Comani.Properties.Resources.StopRefresh;
      else
        toolStripButton2.Image = Comani.Properties.Resources.StartRefresh;
    }

    private void timer1_Tick(object sender, EventArgs e)
    {
      refresh();
    }
  }
}
