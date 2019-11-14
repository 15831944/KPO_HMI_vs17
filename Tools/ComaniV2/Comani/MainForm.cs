using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Reflection;
using LibTelcom;

namespace Comani
{
  public partial class MainForm : Form
  {
    List<IComaniSource> providers;
    public MainForm()
    {
      providers = new List<IComaniSource>();
      InitializeComponent();
      loadProvider("Meltshop.dll", "Meltshop.MeltshopPlugin");
    }

    private void loadProvider(string fileName, string className)
    {
      System.Runtime.Remoting.ObjectHandle handle = Activator.CreateInstanceFrom(fileName, className);
      IComaniSource newProvider = handle.Unwrap() as IComaniSource;
      providers.Add(newProvider);
    }

    private void closeToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.Close();
    }

    private void btnLoadConfig_Click(object sender, EventArgs e)
    {
      OpenFileDialog dlgDefFile = new OpenFileDialog();
      dlgDefFile.Title = "choose Telegram definition file";
      dlgDefFile.Filter = "Telegram Definitions|*.xml";
      if (dlgDefFile.ShowDialog() == DialogResult.OK)
      {
        TelegramDefinitionReader reader = new LibTelcom.TelegramDefinitionReader(dlgDefFile.FileName);
        List<TelegramDefinition> definitions =  reader.getTelegramDefinitions();
        TreeNode node = treeView1.Nodes.Add(System.IO.Path.GetFileName(dlgDefFile.FileName));
        foreach (TelegramDefinition def in definitions)
        {
          TreeNode tlgNode = node.Nodes.Add(def.TelegramName + "  (" + def.Description + ")");
          tlgNode.Tag = def;
        }
      }
    }

    private void showTelegram(TelegramDefinition def)
    {
      DlgSelectProvider dlgProviders = new DlgSelectProvider(providers);
      if (dlgProviders.ShowDialog() == DialogResult.OK)
      {
          // sankar
          if (dlgProviders.SelectedProvider == null)
          {
              MessageBox.Show("Please select the item from the list");
              return;
          }

        if (dlgProviders.SelectedProvider.configureSource())
        {
          Telegram tlg = dlgProviders.SelectedProvider.createTelegram(def);
          flowLayoutPanel1.Controls.Add(tlg);
        }
      }
    }

    private void treeView1_NodeMouseDoubleClick(object sender, TreeNodeMouseClickEventArgs e)
    {
      showTelegram(e.Node.Tag as TelegramDefinition);
    }
  }
}