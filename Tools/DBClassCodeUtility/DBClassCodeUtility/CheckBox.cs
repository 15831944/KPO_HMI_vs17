using System;
using System.IO;
using System.Data;
using System.Drawing;
using System.Xml;
using System.Xml.XPath;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace DBClassCodeUtility
{
  /// <summary>
  /// Summary description for Form1.
  /// </summary>
  public class Checkbox : System.Windows.Forms.Form
  {   
    private System.Windows.Forms.Button Generate;
    private System.Windows.Forms.Button details;
    private System.Windows.Forms.MainMenu mainMenu1;
    private System.Windows.Forms.Button cancel;
    private System.Windows.Forms.Panel panel3;
    private System.Windows.Forms.Label advice;
    private System.Windows.Forms.Label label_body;   
    /// <summary>
    /// Required designer variable.
    /// </summary>
    private System.ComponentModel.Container components = null;

    string TableName;
    string Filename= null;
    string methodSummary;
    
    XmlNodeList PersonalMethodList;
    private System.Windows.Forms.CheckedListBox checkedListBox1;
    XmlDocument newDoc;

    public Checkbox(string TableName, string Filename, string methodSummary)
    {
      //
      InitializeComponent();
      //  
      this.TableName = TableName;
      
      this.newDoc = CData.Instance.getNewXmlDocument();
      this.Filename = Filename;
      this.methodSummary = methodSummary;
      FileInfo f = new FileInfo(this.Filename);
//      CData.Instance.setWorkingDirectory(f.DirectoryName);

      this.Text = "Checkbox for " + f.Name.ToString(); 

      this.advice.Text = "There was a difference to the database found." 
        + "\n\r" + "Selected methods will be added.";
                 
      label_body.Text = "Information:\n\r\n\r" + "First: Please click the info button for more details!"
        + "\n\r" + "Second: make your selection and generate" 
        + "\n\r\n\r" + "Note: If methods were not identified," 
        +     "\n\r"  + "you find a backup file in the working directory. As a *.bak.";

      //Select and display the value of all the PERSONAL attributes.
      XmlElement root = newDoc.DocumentElement;
      PersonalMethodList = root.SelectNodes("/class/METHOD[@GENERATEDBY='MANUAL']");
   
      if( PersonalMethodList.Count.Equals(0) )
      {
        checkedListBox1.Visible =false;
        Generate.Visible = false;
      }
      else
      {
        int count = 0;
        foreach (XmlNode methods in PersonalMethodList)
        {
          this.checkedListBox1.Items.Add(methods.Attributes.GetNamedItem("SIGNATURE").InnerText);
          methods.Attributes.GetNamedItem("INDEX").InnerText = count.ToString();

          this.checkedListBox1.SetItemChecked(count, true);
          count++;
        }

        //      Since then, but the scroll bars in the checkedListBox are also still visible
        //      So checkedListBox need to be bigger than all the items are displayed.
        //      int intItemsCount=Math.Max(this.checkedListBox1.Items.Count,this.checkedListBox2.Items.Count);
        //      if(intItemsCount <= 5) intItemsCount = intItemsCount + 8; 
        //      int intListBoxSize=intItemsCount*this.checkedListBox1.ItemHeight+4;
        //      this.checkedListBox1.Height=intListBoxSize;
        //      this.checkedListBox2.Height=intListBoxSize;
      }
    }// end Constructor
 
    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    protected override void Dispose( bool disposing )
    {
      if( disposing )
      {
        if(components != null)
        {
          components.Dispose();
        }
      }
      base.Dispose( disposing );
    }
    
    #region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
      System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(Checkbox));
      this.Generate = new System.Windows.Forms.Button();
      this.details = new System.Windows.Forms.Button();
      this.mainMenu1 = new System.Windows.Forms.MainMenu();
      this.cancel = new System.Windows.Forms.Button();
      this.panel3 = new System.Windows.Forms.Panel();
      this.label_body = new System.Windows.Forms.Label();
      this.advice = new System.Windows.Forms.Label();
      this.checkedListBox1 = new System.Windows.Forms.CheckedListBox();
      this.panel3.SuspendLayout();
      this.SuspendLayout();
      // 
      // Generate
      // 
      this.Generate.DialogResult = System.Windows.Forms.DialogResult.OK;
      this.Generate.Location = new System.Drawing.Point(416, 6);
      this.Generate.Name = "Generate";
      this.Generate.Size = new System.Drawing.Size(80, 20);
      this.Generate.TabIndex = 5;
      this.Generate.Text = "Generate";
      this.Generate.Click += new System.EventHandler(this.button_Merge_Click);
      // 
      // details
      // 
      this.details.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.details.Enabled = false;
      this.details.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F);
      this.details.Location = new System.Drawing.Point(576, 6);
      this.details.Name = "details";
      this.details.Size = new System.Drawing.Size(80, 20);
      this.details.TabIndex = 10;
      this.details.Text = "Info";
      this.details.Click += new System.EventHandler(this.details_Click);
      // 
      // cancel
      // 
      this.cancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.cancel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F);
      this.cancel.Location = new System.Drawing.Point(496, 6);
      this.cancel.Name = "cancel";
      this.cancel.Size = new System.Drawing.Size(80, 20);
      this.cancel.TabIndex = 6;
      this.cancel.Text = "Cancel";
      this.cancel.Click += new System.EventHandler(this.cancel_Click);
      // 
      // panel3
      // 
      this.panel3.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
        | System.Windows.Forms.AnchorStyles.Right)));
      this.panel3.Controls.Add(this.cancel);
      this.panel3.Controls.Add(this.Generate);
      this.panel3.Controls.Add(this.details);
      this.panel3.Location = new System.Drawing.Point(0, 424);
      this.panel3.Name = "panel3";
      this.panel3.Size = new System.Drawing.Size(664, 32);
      this.panel3.TabIndex = 13;
      // 
      // label_body
      // 
      this.label_body.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
        | System.Windows.Forms.AnchorStyles.Right)));
      this.label_body.Location = new System.Drawing.Point(0, 280);
      this.label_body.Name = "label_body";
      this.label_body.Size = new System.Drawing.Size(664, 144);
      this.label_body.TabIndex = 15;
      this.label_body.Text = "Information:";
      // 
      // advice
      // 
      this.advice.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
        | System.Windows.Forms.AnchorStyles.Right)));
      this.advice.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
      this.advice.Location = new System.Drawing.Point(0, 0);
      this.advice.Name = "advice";
      this.advice.Size = new System.Drawing.Size(664, 56);
      this.advice.TabIndex = 8;
      this.advice.Text = "advice";
      // 
      // checkedListBox1
      // 
      this.checkedListBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
        | System.Windows.Forms.AnchorStyles.Left) 
        | System.Windows.Forms.AnchorStyles.Right)));
      this.checkedListBox1.CheckOnClick = true;
      this.checkedListBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F);
      this.checkedListBox1.HorizontalScrollbar = true;
      this.checkedListBox1.ImeMode = System.Windows.Forms.ImeMode.NoControl;
      this.checkedListBox1.Location = new System.Drawing.Point(0, 56);
      this.checkedListBox1.Name = "checkedListBox1";
      this.checkedListBox1.Size = new System.Drawing.Size(664, 220);
      this.checkedListBox1.TabIndex = 14;
      this.checkedListBox1.SelectedIndexChanged += new System.EventHandler(this.checkedListBox1_SelectedIndexChanged);
      // 
      // Checkbox
      // 
      this.AutoScaleBaseSize = new System.Drawing.Size(7, 16);
      this.ClientSize = new System.Drawing.Size(664, 453);
      this.Controls.Add(this.panel3);
      this.Controls.Add(this.advice);
      this.Controls.Add(this.checkedListBox1);
      this.Controls.Add(this.label_body);
      this.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F);
      this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
      this.Menu = this.mainMenu1;
      this.Name = "Checkbox";
      this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
      this.Text = "Checkbox";
      this.Closing += new System.ComponentModel.CancelEventHandler(this.Checkbox_Closing);
      this.panel3.ResumeLayout(false);
      this.ResumeLayout(false);

    }
    #endregion

    // merge files
    private void button_Merge_Click(object sender, System.EventArgs e)
    {      
      int selectedIndex=0;
      
      for(int index=0; index<=checkedListBox1.CheckedIndices.Count-1; index++)  
      {
        selectedIndex = (int)checkedListBox1.CheckedIndices[index];

        PersonalMethodList[selectedIndex].Attributes.GetNamedItem("GENERATE").InnerText = "YES"; 
      }

      #region ShowNewXmlFile
      StreamWriter xr =  File.CreateText("DB_TABLE.xml");
      xr.WriteLine(this.newDoc.InnerXml);
      xr.Close();    
      #endregion

      #region MakeCppAndHeader
      // if method are cheched, missing or old
      if( !CData.Instance.getPersonalMethodsToGenerate().Equals(0) || !CData.Instance.getGeneratedMethodsToMerge((int)CData.MethodType.BOTH).Equals(0))
      {
        System.Environment.CurrentDirectory = CData.Instance.getWorkingDirectory();
        CCodeWriter writer = new CCodeWriter();
        writer.writeCode(this.TableName, this.newDoc);
      }
      #endregion

      this.Close();
    }

    private void cancel_Click(object sender, System.EventArgs e)
    {
      this.Close();
    }

    private void details_Click(object sender, System.EventArgs e)
    {
      // frag
//      if (CData.Instance.getMissingColumn() != null)
//      {
//        this.methodSummary += "Es fehlen folgende get/set Methoden \n\r\n\r";
//        this.methodSummary += CData.Instance.getMissingColumn() + "\n\r\n\r ";
//        this.methodSummary += "\n\r\n\r";
//      }
     
      #region WriteOutAndShowSummary
      StreamReader readChecker =  File.OpenText((@CData.Instance.getWorkingDirectory() + "\\DBClassCodeUtility.txt"));
      readChecker.Close();
      StreamWriter methodChecker =  File.CreateText((@CData.Instance.getWorkingDirectory() + "\\DBClassCodeUtility.txt"));
      methodChecker.WriteLine(this.Filename);
      methodChecker.WriteLine(this.methodSummary);
      methodChecker.Close();    
      System.Diagnostics.Process process = System.Diagnostics.Process.Start((@CData.Instance.getWorkingDirectory() + "\\DBClassCodeUtility.txt"));
      //if(process.Exist)process.Kill();
      #endregion
    }

    private void Checkbox_Closing(object sender, System.ComponentModel.CancelEventArgs e)
    {
      CData.Instance.setNewSummary(null);
    }

    private void checkedListBox1_SelectedIndexChanged(object sender, System.EventArgs e)
    {
//      int Selected = ((CheckedListBox)sender).SelectedIndex;
//
//      if(details.Enabled == false)
//      {
//        // for definition select only one
//        if(checkedListBox1.CheckedItems.Count >= 1 )
//        {
//
//          foreach(int indexChecked in checkedListBox1.CheckedIndices)
//            checkedListBox1.SetItemChecked(indexChecked, false);
//
//          checkedListBox1.SetItemChecked(Selected, true);
//        }
//      }
//      else 
//      {
//        if(checkedListBox1.CheckedItems.Count >= 1 )
//        {
//          if( PersonalMethodList[Selected].Attributes.GetNamedItem("COLUMNEXISTS").InnerText.Equals("NO") )  
//          {
//            string body = PersonalMethodList[Selected].Attributes.GetNamedItem("BODY").InnerText;
//            label_body.Text = "Information:\n\r\n\r" + "- "+ PersonalMethodList[Selected].Attributes.GetNamedItem("NAME").InnerText
//              + " - \n\r" + "This method can be add to your document.";
//          }
//          else
//          {
//            label_body.Text = "Information:\n\r\n\r" + "This method can be add to your document"; 
//          }
//        }//if(checkedListBox1.CheckedItems.Count >= 1 )
//        else 
//        {
//          label_body.Text = "Information:\n\r\n\r" + "First: Please click the info button for more details!"
//            + "\n\r" + "Second: make your selection and generate" 
//            + "\n\r\n\r" + "Note: If methods were not identified," 
//            +     "\n\r"  + "you find a backup file in the working directory. As a *.bak.";  
//        }   
//      }
    }// private void checkedListBox1_SelectedIndexChanged(object sender, System.EventArgs e)

  }//  public class Checkbox : System.Windows.Forms.Form
}// namespace DBClassCodeUtility