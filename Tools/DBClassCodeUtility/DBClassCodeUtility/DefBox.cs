using System;
using System.IO;
using System.Data;
using System.Xml;
using System.Xml.XPath;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace DBClassCodeUtility
{
	/// <summary>
	/// Summary description for DefBox.
	/// </summary>
  public class DefBox : System.Windows.Forms.Form
  {
    private System.Windows.Forms.Button button_DefGenerate;
    private System.Windows.Forms.Button button_Cancel;
    private System.Windows.Forms.Button button_Info;
    /// <summary>
    /// Required designer variable.
    /// </summary>
    private System.ComponentModel.Container components = null;
    private System.Windows.Forms.DataGrid dataGridDef;
    private System.Windows.Forms.DataGridTableStyle dataGridTableStyle_COLUM;
    
    string Filename;
    private int m_detailIndex = 0;
    private int m_dataIndex = 0;
    
    DataTable Desc_Table;
    private System.Windows.Forms.Panel panel1;
    DataGrid dataGrid1;
 

    public DefBox(DataTable Desc_Table, string Filename)
    {
      //
      // Required for Windows Form Designer support
      //

      //Constructor 
      InitializeComponent();

      button_Info.Enabled= false;

      this.Width = 550;
      // advice.Text = "From which column shall be a definition interfaces generated";
      this.Filename = Filename;
      this.Desc_Table = Desc_Table;
      FileInfo f = new FileInfo(this.Filename);

      this.Text = "Defbox for " + f.Name.ToString();
      
      DataTable userTable = new DataTable("DefTable");

      // neue Spalten hinzufügen:
      userTable.Columns.Add(newColumForDataTable("ColName", true, typeof(System.String)));
      userTable.Columns.Add(newColumForDataTable("Type", true, typeof(System.String)));
      userTable.Columns.Add(newColumForDataTable("Name", false, typeof(bool)));
      userTable.Columns.Add(newColumForDataTable("Value", false, typeof(bool)));

      // neue Datensätze
      DataRow dr;
      for (int index = 0; index<=this.Desc_Table.Rows.Count-1; index++)
      {
        dr = userTable.NewRow();
        dr["ColName"] = Desc_Table.Rows[index]["COLUMN_NAME"].ToString();
                           
        dr["Type"] = getColType(Desc_Table.Rows[index]["DATA_TYPE"].ToString(), Desc_Table.Rows[index]["DATA_LENGTH"].ToString(),
          Desc_Table.Rows[index]["DATA_SCALE"].ToString()); // type of column
        
        dr["Name"] = false;
        dr["Value"] = false;

        userTable.Rows.Add(dr);
      }
     
      // DataSet-Objekt
      DataSet dataSet = new DataSet();
      dataSet.Tables.Add(userTable);

      // DataGrid-Objekt und füge das DataSet-Objekt hinzu
      dataGrid1 = new DataGrid();
      dataGrid1.SetDataBinding(dataSet, "DefTable"); 

      // Zuletzt setze ich das DataGrid als DataSource des DataGridView's:
      dataGridDef.DataSource = userTable;

      newWidth(dataSet, "DefTable", 0);
      //dataGridDef.Size = dataGrid1.Size;

      // add to dataGridDef
      //BindToDataSet(userTable);
    }

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
      System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(DefBox));
      this.button_DefGenerate = new System.Windows.Forms.Button();
      this.button_Cancel = new System.Windows.Forms.Button();
      this.button_Info = new System.Windows.Forms.Button();
      this.dataGridDef = new System.Windows.Forms.DataGrid();
      this.dataGridTableStyle_COLUM = new System.Windows.Forms.DataGridTableStyle();
      this.panel1 = new System.Windows.Forms.Panel();
      ((System.ComponentModel.ISupportInitialize)(this.dataGridDef)).BeginInit();
      this.panel1.SuspendLayout();
      this.SuspendLayout();
      // 
      // button_DefGenerate
      // 
      this.button_DefGenerate.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
      this.button_DefGenerate.Location = new System.Drawing.Point(352, 394);
      this.button_DefGenerate.Name = "button_DefGenerate";
      this.button_DefGenerate.Size = new System.Drawing.Size(75, 24);
      this.button_DefGenerate.TabIndex = 12;
      this.button_DefGenerate.Text = "Generate";
      this.button_DefGenerate.Click += new System.EventHandler(this.button_DefGenerate_Click);
      // 
      // button_Cancel
      // 
      this.button_Cancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
      this.button_Cancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.button_Cancel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F);
      this.button_Cancel.Location = new System.Drawing.Point(440, 394);
      this.button_Cancel.Name = "button_Cancel";
      this.button_Cancel.Size = new System.Drawing.Size(75, 24);
      this.button_Cancel.TabIndex = 13;
      this.button_Cancel.Text = "Cancel";
      this.button_Cancel.Click += new System.EventHandler(this.button_Cancel_Click);
      // 
      // button_Info
      // 
      this.button_Info.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
      this.button_Info.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.button_Info.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F);
      this.button_Info.Location = new System.Drawing.Point(528, 394);
      this.button_Info.Name = "button_Info";
      this.button_Info.Size = new System.Drawing.Size(75, 24);
      this.button_Info.TabIndex = 14;
      this.button_Info.Text = "Info";
      // 
      // dataGridDef
      // 
      this.dataGridDef.BackgroundColor = System.Drawing.SystemColors.ActiveCaptionText;
      this.dataGridDef.CaptionBackColor = System.Drawing.SystemColors.ControlLight;
      this.dataGridDef.DataMember = "";
      this.dataGridDef.Dock = System.Windows.Forms.DockStyle.Fill;
      this.dataGridDef.HeaderForeColor = System.Drawing.SystemColors.ControlText;
      this.dataGridDef.Location = new System.Drawing.Point(0, 0);
      this.dataGridDef.Name = "dataGridDef";
      this.dataGridDef.Size = new System.Drawing.Size(616, 384);
      this.dataGridDef.TabIndex = 16;
      this.dataGridDef.TableStyles.AddRange(new System.Windows.Forms.DataGridTableStyle[] {
            this.dataGridTableStyle_COLUM});
      this.dataGridDef.CurrentCellChanged += new System.EventHandler(this.dataGridDef_CurrentCellChanged);
      // 
      // dataGridTableStyle_COLUM
      // 
      this.dataGridTableStyle_COLUM.DataGrid = this.dataGridDef;
      this.dataGridTableStyle_COLUM.HeaderForeColor = System.Drawing.SystemColors.ControlText;
      // 
      // panel1
      // 
      this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                  | System.Windows.Forms.AnchorStyles.Right)));
      this.panel1.Controls.Add(this.dataGridDef);
      this.panel1.Location = new System.Drawing.Point(0, 0);
      this.panel1.Name = "panel1";
      this.panel1.Size = new System.Drawing.Size(616, 384);
      this.panel1.TabIndex = 17;
      // 
      // DefBox
      // 
      this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
      this.ClientSize = new System.Drawing.Size(616, 431);
      this.Controls.Add(this.panel1);
      this.Controls.Add(this.button_Cancel);
      this.Controls.Add(this.button_Info);
      this.Controls.Add(this.button_DefGenerate);
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
      this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
      this.Name = "DefBox";
      this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
      this.Text = "DefBox";
      ((System.ComponentModel.ISupportInitialize)(this.dataGridDef)).EndInit();
      this.panel1.ResumeLayout(false);
      this.ResumeLayout(false);

    }
    #endregion

    private void button_DefGenerate_Click(object sender, System.EventArgs e)
    {
      try
      {
        int firstCount = 0;
        int secondCount = 0;

        String firstColName = "";
        String secondColName = "";
        //String Value = 

        for (int index = 0; index < GetDataSetFromDataSource().Tables["DefTable"].Rows.Count; index++)
        {
          // Name
          if (typeof(bool) == GetTypeFromRow(index, 2))
          {
            bool Ischecked = (bool)GetDataSetFromDataSource().Tables["DefTable"].Rows[index].ItemArray.GetValue(2);

            if (Ischecked)
            {
              // to avoid misktakes when compling code, note only strings are allowed for names
              if (typeof(string) == GetDataSetFromDataSource().Tables["DefTable"].Rows[index].ItemArray.GetValue(0).GetType())
              {
                m_detailIndex = index;
                firstColName = GetDataSetFromDataSource().Tables["DefTable"].Rows[index].ItemArray.GetValue(0).ToString();
                firstCount++;
              }
            }
          }

          // Value
          if (typeof(bool) == GetTypeFromRow(index, 3))
          {
            bool Ischecked = (bool)GetDataSetFromDataSource().Tables["DefTable"].Rows[index].ItemArray.GetValue(3);

            if (Ischecked)
            {
              m_dataIndex = index;
              secondColName = GetDataSetFromDataSource().Tables["DefTable"].Rows[index].ItemArray.GetValue(0).ToString();
              secondCount++;
            }
          }
        }

        // exor condition
        if (firstCount == 1 && secondCount == 1)
        {
          XmlDocument defDoc = new XmlDocument();

          CCodePreprocessor pre = new CCodePreprocessor();
          defDoc = pre.createDefClass(Desc_Table, m_detailIndex, m_dataIndex);

          FileInfo f = new FileInfo(this.Filename);
          string Filename = f.Name.ToString();
          Filename = Filename.Remove(0, 1);

          System.Environment.CurrentDirectory = CData.Instance.getWorkingDirectory();

          CCodeWriter writer = new CCodeWriter();
          writer.writeDefCode(Filename, defDoc);

          this.DialogResult = System.Windows.Forms.DialogResult.OK;

          this.Close();
        }
        else
        {
          MessageBox.Show("Generate_Click : for each checkbox row only one is allowed to selecet",
            "Error on check box", MessageBoxButtons.OK, MessageBoxIcon.Error);     
        }
      }
      catch (Exception ex)
      {
        this.DialogResult = System.Windows.Forms.DialogResult.Abort;

        MessageBox.Show(ex.StackTrace + " : \r\n\r\n"
          + ex.Message,
          "Error: " + ex.ToString(), MessageBoxButtons.OK, MessageBoxIcon.Error);     
      }   
    }//private void button_DefGenerate_Click(object sender, System.EventArgs e)

    private System.Type GetTypeFromRow(int row, int index)
    {
      return GetDataSetFromDataSource().Tables["DefTable"].Rows[row].ItemArray.GetValue(index).GetType();   
    }

    // add to dataGridDef
    private void BindToDataSet(DataTable userTable)
    {
      dataGridDef.DataSource = userTable;
      dataGridDef.Refresh();
    }

    private DataSet GetDataSetFromDataSource()
    {
      // Create a DataSet variable, and set it to the DataSource.
      DataSet myDataSet;
      myDataSet = (DataSet) dataGrid1.DataSource;
      return myDataSet;
    }

    private DataTable GetDataSetFromDataSource2()
    {
      // Create a DataSet variable, and set it to the DataSource.
      DataTable myDataSet;
      myDataSet = (DataTable) dataGrid1.DataSource;
      return myDataSet;
    }  
  
    private DataColumn newColumForDataTable(string ColumnName, bool ReadOnly, System.Type type)
    {
      
      DataColumn column = new DataColumn();
      column.DataType = type;
      column.ColumnName = ColumnName;
      column.ReadOnly = ReadOnly;
      return column;
    }

    // return column type
    private string getColType(string dbType, string dbLength, string dbScale)
    {
      if(dbType == "VARCHAR2")
      {
        if(dbLength == "23") return "CDateTime";
        else return "string";
      }
      else if(dbType == "NUMBER")
      {
        if(dbScale == "0") return "long";
        else return "double";
      }
      else if(dbType != "")
        return dbType;
      else return "unknown";
    }// End of getColType

    void newWidth(DataSet ds, string TableName, int ColumnIndex)
    {
      int maxlength = 0;
      int rows_count = ds.Tables[TableName].Rows.Count; 
      string str = "";
      int length = 0;

      Graphics g = dataGridDef.CreateGraphics();

      // Take width one balnk space to add to the new width to the Column   
      int offset = Convert.ToInt32(Math.Ceiling(g.MeasureString(" ", dataGridDef.Font).Width));

      for (int i=0; i < rows_count; ++i)
      {
        str =  ds.Tables[TableName].Rows[i][ColumnIndex].ToString();

        // Get the width of Current Field String according to the Font
        length = Convert.ToInt32(Math.Ceiling(g.MeasureString(str, dataGridDef.Font).Width));
        if (length  > maxlength)                
        {
          maxlength = length;
        }
      }// End of For Loop

      maxlength += offset;

      // Create new Table Style
      DataGridTableStyle ts = new DataGridTableStyle();
      ts.MappingName = TableName;
      dataGridDef.TableStyles.Clear();
      dataGridDef.TableStyles.Add(ts);

      // Assign New Width to DataGrid column
      dataGridDef.TableStyles[TableName].GridColumnStyles[0].Width = maxlength;
      //dataGridDef.Size = new System.Drawing.Size(maxlength+270, rows_count*45);
    }

    private void dataGridDef_CurrentCellChanged(object sender, System.EventArgs e)
    {
      int ColIndex = ((DataGrid)sender).CurrentCell.ColumnNumber;
      int RowIndex = ((DataGrid)sender).CurrentCell.RowNumber; 
      //only one is allowed to Select
        
      // doesnt work!!
      //GetDataSetFromDataSource().Tables["DefTable"].Rows[m_dataIndex].ItemArray.SetValue(true, 3);
      
      for(int index = 0; index < GetDataSetFromDataSource().Tables["DefTable"].Rows.Count; index++)
      {
        if ( ColIndex == 2 ) 
          GetDataSetFromDataSource().Tables["DefTable"].Rows[index]["Name"] = false; 
        else if ( ColIndex == 3 )
          GetDataSetFromDataSource().Tables["DefTable"].Rows[index]["Value"] = false;        
      }  

      GetDataSetFromDataSource().Tables["DefTable"].Rows[RowIndex][ColIndex] = true;

      BindToDataSet(GetDataSetFromDataSource().Tables["DefTable"]);
    }

    private void button_Cancel_Click(object sender, System.EventArgs e)
    {
      this.Close();
    }// private void dataGridDef_CurrentCellChanged(object sender, System.EventArgs e)

  }
}
