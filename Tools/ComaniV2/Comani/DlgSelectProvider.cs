using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Comani
{
  public partial class DlgSelectProvider : Form
  {
    Dictionary<string, IComaniSource> providerDict;
    public IComaniSource SelectedProvider;
    public DlgSelectProvider(List<IComaniSource> providers)
    {
      //fill Dictionary
      providerDict = new Dictionary<string, IComaniSource>();
      foreach (IComaniSource source in providers)
      {
        providerDict.Add(source.getSourceName(), source);
      }

      InitializeComponent();

      //set listbox items
      foreach (string name in providerDict.Keys)
        listBox1.Items.Add(name);


      //sankar
      if (listBox1.Items.Count > 0)
          listBox1.SelectedIndex = 0;

    }

    private void button1_Click(object sender, EventArgs e)
    {       
      SelectedProvider = providerDict[listBox1.SelectedItem as string];
    }

    private void listBox1_DoubleClick(object sender, EventArgs e)
    {
      SelectedProvider = providerDict[listBox1.SelectedItem as string];
    }




  }
}