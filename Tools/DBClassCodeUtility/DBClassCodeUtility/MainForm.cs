using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Xml;
using System.IO;
using System.Xml.XPath;
using System.Text;
using Microsoft.Win32;
using Wrapper;

namespace DBClassCodeUtility
{
  /// <summary>
  /// Summary description for Form1.
  /// </summary>
  ///    
  struct sActInfo
  {
    public string Service;
    public string tabPageIndex;
    public int selectedItemsCount;
  };

  public class MainForm : System.Windows.Forms.Form
  {
    private System.Windows.Forms.MainMenu mainMenu1;
    private System.Windows.Forms.Panel panelTables;
    private System.Windows.Forms.TabControl tabControlConnections;
    private System.Windows.Forms.Splitter splitter1;
    private System.Windows.Forms.Label labelUser;
    private System.Windows.Forms.TextBox textBoxUser;
    private System.Windows.Forms.Label labelPassword;
    private System.Windows.Forms.TextBox textBoxPassword;
    private System.Windows.Forms.Panel panelConnection;
    private System.Windows.Forms.Button buttonConnect;
    private System.Windows.Forms.Label labelServices;
    private System.Windows.Forms.ComboBox comboBoxServices;
    private CConnections Connections;
    private System.Windows.Forms.Control allCreatedControls;
    private System.Windows.Forms.MenuItem menuItemOpen;
    private System.Windows.Forms.MenuItem menuItemClose;
    private System.Data.Odbc.OdbcConnection conn ;
    
    private System.Windows.Forms.TabControl tabControlTable;
    private System.Windows.Forms.Panel TabControlPanel;
    private System.Windows.Forms.TabPage tabPageData;
    private IContainer components;
    private System.Windows.Forms.TabPage tabPageDetails;
    private System.Windows.Forms.DataGrid GridTableDetails;
    private System.Windows.Forms.MenuItem menuItem_EDIT;
    private System.Windows.Forms.RadioButton radioButton_GEN_CLASS;
    private System.Windows.Forms.RadioButton radioButton_GEN_DEF;
    private System.Windows.Forms.MenuItem menuItem_DataBase;
    private System.Windows.Forms.TabPage tabPage_Check;
    private System.Windows.Forms.GroupBox groupBox_options;
    private System.Windows.Forms.TextBox textBoxDB;
    private System.Windows.Forms.TextBox textBoxDir;
    private System.Windows.Forms.Label labelProcessBar;
    private System.Windows.Forms.Button buttonCheckCancel;
    private System.Windows.Forms.Label label_CDB;
    private System.Windows.Forms.Label label_WD;
    private System.Windows.Forms.Button buttonCheck;
    private System.Windows.Forms.Button buttonCheckInfo; 
    
    private System.Windows.Forms.MenuItem menuItem_Settings;
    private System.Windows.Forms.Label label_report;
    private System.Windows.Forms.Button button_wd;
    private System.Windows.Forms.CheckBox checkBox1;
    private System.Windows.Forms.CheckBox checkBox2;
    private System.Windows.Forms.CheckBox checkBox3;
    private System.Windows.Forms.CheckBox checkBox4;
    private System.Windows.Forms.Button button1;
    private System.Windows.Forms.Button button2;
    private System.Windows.Forms.Button button3;
    private System.Windows.Forms.Button button4;
    private System.Windows.Forms.GroupBox groupBox_option;
    private System.Windows.Forms.CheckBox checkBox5;
    private System.Windows.Forms.Button button5;    
    private System.Windows.Forms.TabPage tabPage_Generated;
    private System.Windows.Forms.Button buttonGenerate;
    private System.Windows.Forms.Button buttonGenCancle;
    private System.Windows.Forms.Label labelGenReportOut;
    private System.Windows.Forms.Label label_GenReport;
    private System.Windows.Forms.GroupBox groupBox_Gen;
    private System.Windows.Forms.Panel panelCheck;
    private System.Windows.Forms.Button buttonGenXmlFile;
    private System.Windows.Forms.Button buttonGenSelectAll;
    private System.Windows.Forms.ListBox listBoxGenReportOut;
    private System.Windows.Forms.Label labelWDPath;
    private System.Windows.Forms.Label labelDBSERVICE;
    private System.Windows.Forms.Label labelDBUSER;
    private System.Windows.Forms.Label label_DBUser;
    private System.Windows.Forms.Label label_WDPath;
    private System.Windows.Forms.Label label_DBService;
    private System.Windows.Forms.GroupBox groupBoxInfo;
    private System.Windows.Forms.ContextMenu contextMenuListB;
    private System.Windows.Forms.MenuItem menuItemOpenFile;
    private System.Windows.Forms.MenuItem menuItemUpdate;
    private System.Windows.Forms.CheckBox checkBoxWDFiles;

    private ListBox ListCPPClasses;
    private string methodSummary = null;
    private string sReportText = null;
    private string sGenReport = null;
    private bool IsDBTable = true;


    public DataSet TableDescriptionDataSet;
    public DataSet CompareDescriptionDataSet;
    string XMLDirCompare1 = "";
    string XMLDirCompare2 = "";
    private int count = 0;
    private int notExisting = 0;
    private ArrayList flagArr;
    private BackgroundWorker backgroundWorkerCheck;
    private ProgressBar progressBarCheck;
    private BackgroundWorker backgroundWorkerGen;
    private MenuItem menuItem1;
    private MenuItem menuItemDBClassCodeUtility;
    private MenuItem menuItemClassCodeUtility;
    private MenuItem menuItemCompareData;
    private ProgressBar progressBarGen;

    public MainForm()
    {
      try
      {
        //
        // Required for Windows Form Designer support
        //
        InitializeComponent();
        
        this.Text = CData.Instance.getVersionOfDBClassCodeUtility();
       
        Connections = new CConnections();
        allCreatedControls = new Control();
        
        TableDescriptionDataSet = new DataSet("TableDescription");
      }
      catch(System.Security.SecurityException ex)
      {
        MessageBox.Show(ex.StackTrace + " : \r\n\r\n" + ex.Message);
      }
    }

    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    protected override void Dispose( bool disposing )
    {
      if( disposing )
      {
        if (components != null) 
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
      this.components = new System.ComponentModel.Container();
      System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
      this.panelTables = new System.Windows.Forms.Panel();
      this.tabControlConnections = new System.Windows.Forms.TabControl();
      this.mainMenu1 = new System.Windows.Forms.MainMenu(this.components);
      this.menuItem_DataBase = new System.Windows.Forms.MenuItem();
      this.menuItemOpen = new System.Windows.Forms.MenuItem();
      this.menuItemUpdate = new System.Windows.Forms.MenuItem();
      this.menuItemClose = new System.Windows.Forms.MenuItem();
      this.menuItem_EDIT = new System.Windows.Forms.MenuItem();
      this.menuItem_Settings = new System.Windows.Forms.MenuItem();
      this.menuItem1 = new System.Windows.Forms.MenuItem();
      this.menuItemDBClassCodeUtility = new System.Windows.Forms.MenuItem();
      this.menuItemClassCodeUtility = new System.Windows.Forms.MenuItem();
      this.splitter1 = new System.Windows.Forms.Splitter();
      this.panelConnection = new System.Windows.Forms.Panel();
      this.comboBoxServices = new System.Windows.Forms.ComboBox();
      this.buttonConnect = new System.Windows.Forms.Button();
      this.labelServices = new System.Windows.Forms.Label();
      this.textBoxPassword = new System.Windows.Forms.TextBox();
      this.labelPassword = new System.Windows.Forms.Label();
      this.textBoxUser = new System.Windows.Forms.TextBox();
      this.labelUser = new System.Windows.Forms.Label();
      this.panelCheck = new System.Windows.Forms.Panel();
      this.buttonCheck = new System.Windows.Forms.Button();
      this.buttonCheckInfo = new System.Windows.Forms.Button();
      this.buttonCheckCancel = new System.Windows.Forms.Button();
      this.radioButton_GEN_CLASS = new System.Windows.Forms.RadioButton();
      this.radioButton_GEN_DEF = new System.Windows.Forms.RadioButton();
      this.conn = new System.Data.Odbc.OdbcConnection();
      this.tabControlTable = new System.Windows.Forms.TabControl();
      this.tabPageDetails = new System.Windows.Forms.TabPage();
      this.GridTableDetails = new System.Windows.Forms.DataGrid();
      this.tabPageData = new System.Windows.Forms.TabPage();
      this.tabPage_Check = new System.Windows.Forms.TabPage();
      this.groupBox_options = new System.Windows.Forms.GroupBox();
      this.progressBarCheck = new System.Windows.Forms.ProgressBar();
      this.groupBox_option = new System.Windows.Forms.GroupBox();
      this.button4 = new System.Windows.Forms.Button();
      this.button3 = new System.Windows.Forms.Button();
      this.button2 = new System.Windows.Forms.Button();
      this.button1 = new System.Windows.Forms.Button();
      this.checkBox2 = new System.Windows.Forms.CheckBox();
      this.checkBox1 = new System.Windows.Forms.CheckBox();
      this.checkBox3 = new System.Windows.Forms.CheckBox();
      this.checkBox4 = new System.Windows.Forms.CheckBox();
      this.checkBox5 = new System.Windows.Forms.CheckBox();
      this.button5 = new System.Windows.Forms.Button();
      this.button_wd = new System.Windows.Forms.Button();
      this.label_report = new System.Windows.Forms.Label();
      this.label_CDB = new System.Windows.Forms.Label();
      this.textBoxDB = new System.Windows.Forms.TextBox();
      this.label_WD = new System.Windows.Forms.Label();
      this.textBoxDir = new System.Windows.Forms.TextBox();
      this.labelProcessBar = new System.Windows.Forms.Label();
      this.tabPage_Generated = new System.Windows.Forms.TabPage();
      this.progressBarGen = new System.Windows.Forms.ProgressBar();
      this.groupBoxInfo = new System.Windows.Forms.GroupBox();
      this.labelDBUSER = new System.Windows.Forms.Label();
      this.labelWDPath = new System.Windows.Forms.Label();
      this.labelDBSERVICE = new System.Windows.Forms.Label();
      this.label_DBService = new System.Windows.Forms.Label();
      this.label_DBUser = new System.Windows.Forms.Label();
      this.label_WDPath = new System.Windows.Forms.Label();
      this.listBoxGenReportOut = new System.Windows.Forms.ListBox();
      this.groupBox_Gen = new System.Windows.Forms.GroupBox();
      this.buttonGenSelectAll = new System.Windows.Forms.Button();
      this.buttonGenerate = new System.Windows.Forms.Button();
      this.buttonGenCancle = new System.Windows.Forms.Button();
      this.buttonGenXmlFile = new System.Windows.Forms.Button();
      this.checkBoxWDFiles = new System.Windows.Forms.CheckBox();
      this.label_GenReport = new System.Windows.Forms.Label();
      this.labelGenReportOut = new System.Windows.Forms.Label();
      this.TabControlPanel = new System.Windows.Forms.Panel();
      this.contextMenuListB = new System.Windows.Forms.ContextMenu();
      this.menuItemOpenFile = new System.Windows.Forms.MenuItem();
      this.menuItemCompareData = new System.Windows.Forms.MenuItem();
      this.backgroundWorkerCheck = new System.ComponentModel.BackgroundWorker();
      this.backgroundWorkerGen = new System.ComponentModel.BackgroundWorker();
      this.panelTables.SuspendLayout();
      this.panelConnection.SuspendLayout();
      this.panelCheck.SuspendLayout();
      this.tabControlTable.SuspendLayout();
      this.tabPageDetails.SuspendLayout();
      ((System.ComponentModel.ISupportInitialize)(this.GridTableDetails)).BeginInit();
      this.tabPage_Check.SuspendLayout();
      this.groupBox_options.SuspendLayout();
      this.groupBox_option.SuspendLayout();
      this.tabPage_Generated.SuspendLayout();
      this.groupBoxInfo.SuspendLayout();
      this.groupBox_Gen.SuspendLayout();
      this.TabControlPanel.SuspendLayout();
      this.SuspendLayout();
      // 
      // panelTables
      // 
      this.panelTables.Controls.Add(this.tabControlConnections);
      this.panelTables.Dock = System.Windows.Forms.DockStyle.Left;
      this.panelTables.Location = new System.Drawing.Point(0, 0);
      this.panelTables.Name = "panelTables";
      this.panelTables.Size = new System.Drawing.Size(208, 497);
      this.panelTables.TabIndex = 0;
      // 
      // tabControlConnections
      // 
      this.tabControlConnections.Dock = System.Windows.Forms.DockStyle.Fill;
      this.tabControlConnections.Location = new System.Drawing.Point(0, 0);
      this.tabControlConnections.Name = "tabControlConnections";
      this.tabControlConnections.SelectedIndex = 0;
      this.tabControlConnections.Size = new System.Drawing.Size(208, 497);
      this.tabControlConnections.TabIndex = 3;
      this.tabControlConnections.SelectedIndexChanged += new System.EventHandler(this.tabControlConnections_SelectedIndexChanged);
      // 
      // mainMenu1
      // 
      this.mainMenu1.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.menuItem_DataBase,
            this.menuItem_EDIT});
      // 
      // menuItem_DataBase
      // 
      this.menuItem_DataBase.Index = 0;
      this.menuItem_DataBase.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.menuItemOpen,
            this.menuItemUpdate,
            this.menuItemClose});
      this.menuItem_DataBase.Text = "DataBase";
      // 
      // menuItemOpen
      // 
      this.menuItemOpen.Index = 0;
      this.menuItemOpen.Text = "Connect";
      this.menuItemOpen.Click += new System.EventHandler(this.menuItemOpenClick);
      // 
      // menuItemUpdate
      // 
      this.menuItemUpdate.Enabled = false;
      this.menuItemUpdate.Index = 1;
      this.menuItemUpdate.Shortcut = System.Windows.Forms.Shortcut.F5;
      this.menuItemUpdate.Text = "Update";
      this.menuItemUpdate.Click += new System.EventHandler(this.menuItemUpdate_Click);
      // 
      // menuItemClose
      // 
      this.menuItemClose.Enabled = false;
      this.menuItemClose.Index = 2;
      this.menuItemClose.Shortcut = System.Windows.Forms.Shortcut.AltF4;
      this.menuItemClose.Text = "Close";
      this.menuItemClose.Click += new System.EventHandler(this.menuItemCloseClick);
      // 
      // menuItem_EDIT
      // 
      this.menuItem_EDIT.Index = 1;
      this.menuItem_EDIT.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.menuItem_Settings,
            this.menuItem1});
      this.menuItem_EDIT.Text = "Tools";
      // 
      // menuItem_Settings
      // 
      this.menuItem_Settings.Index = 0;
      this.menuItem_Settings.Text = "Settings...";
      this.menuItem_Settings.Click += new System.EventHandler(this.menuItemTool_Click);
      // 
      // menuItem1
      // 
      this.menuItem1.Index = 1;
      this.menuItem1.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.menuItemDBClassCodeUtility,
            this.menuItemClassCodeUtility});
      this.menuItem1.Text = "Toggle Mode";
      // 
      // menuItemDBClassCodeUtility
      // 
      this.menuItemDBClassCodeUtility.Checked = true;
      this.menuItemDBClassCodeUtility.Index = 0;
      this.menuItemDBClassCodeUtility.Text = "DBClassCodeUtility";
      this.menuItemDBClassCodeUtility.Click += new System.EventHandler(this.menuItemDBClassCodeUtility_Click);
      // 
      // menuItemClassCodeUtility
      // 
      this.menuItemClassCodeUtility.Index = 1;
      this.menuItemClassCodeUtility.Text = "ClassCodeUtility";
      this.menuItemClassCodeUtility.Click += new System.EventHandler(this.menuItemClassCodeUtility_Click);
      // 
      // splitter1
      // 
      this.splitter1.Location = new System.Drawing.Point(208, 0);
      this.splitter1.Name = "splitter1";
      this.splitter1.Size = new System.Drawing.Size(3, 497);
      this.splitter1.TabIndex = 0;
      this.splitter1.TabStop = false;
      // 
      // panelConnection
      // 
      this.panelConnection.Controls.Add(this.comboBoxServices);
      this.panelConnection.Controls.Add(this.buttonConnect);
      this.panelConnection.Controls.Add(this.labelServices);
      this.panelConnection.Controls.Add(this.textBoxPassword);
      this.panelConnection.Controls.Add(this.labelPassword);
      this.panelConnection.Controls.Add(this.textBoxUser);
      this.panelConnection.Controls.Add(this.labelUser);
      this.panelConnection.Dock = System.Windows.Forms.DockStyle.Top;
      this.panelConnection.Location = new System.Drawing.Point(211, 0);
      this.panelConnection.Name = "panelConnection";
      this.panelConnection.Size = new System.Drawing.Size(621, 40);
      this.panelConnection.TabIndex = 1;
      this.panelConnection.Visible = false;
      // 
      // comboBoxServices
      // 
      this.comboBoxServices.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
      this.comboBoxServices.Location = new System.Drawing.Point(440, 9);
      this.comboBoxServices.Name = "comboBoxServices";
      this.comboBoxServices.Size = new System.Drawing.Size(80, 21);
      this.comboBoxServices.TabIndex = 6;
      this.comboBoxServices.Text = "Service";
      this.comboBoxServices.SelectedIndexChanged += new System.EventHandler(this.comboBoxServices_SelectedIndexChanged);
      this.comboBoxServices.TextChanged += new System.EventHandler(this.service_TextChanged);
      // 
      // buttonConnect
      // 
      this.buttonConnect.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
      this.buttonConnect.Location = new System.Drawing.Point(536, 8);
      this.buttonConnect.Name = "buttonConnect";
      this.buttonConnect.Size = new System.Drawing.Size(75, 23);
      this.buttonConnect.TabIndex = 7;
      this.buttonConnect.Text = "Connect";
      this.buttonConnect.Click += new System.EventHandler(this.connectClick);
      // 
      // labelServices
      // 
      this.labelServices.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
      this.labelServices.Location = new System.Drawing.Point(392, 12);
      this.labelServices.Name = "labelServices";
      this.labelServices.Size = new System.Drawing.Size(48, 17);
      this.labelServices.TabIndex = 4;
      this.labelServices.Text = "Service";
      // 
      // textBoxPassword
      // 
      this.textBoxPassword.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
      this.textBoxPassword.Location = new System.Drawing.Point(307, 9);
      this.textBoxPassword.Name = "textBoxPassword";
      this.textBoxPassword.Size = new System.Drawing.Size(69, 20);
      this.textBoxPassword.TabIndex = 3;
      this.textBoxPassword.TextChanged += new System.EventHandler(this.password_TextChanged);
      this.textBoxPassword.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBoxPassword_KeyDown);
      // 
      // labelPassword
      // 
      this.labelPassword.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
      this.labelPassword.Location = new System.Drawing.Point(250, 12);
      this.labelPassword.Name = "labelPassword";
      this.labelPassword.Size = new System.Drawing.Size(56, 18);
      this.labelPassword.TabIndex = 2;
      this.labelPassword.Text = "Password";
      // 
      // textBoxUser
      // 
      this.textBoxUser.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
      this.textBoxUser.Location = new System.Drawing.Point(160, 9);
      this.textBoxUser.Name = "textBoxUser";
      this.textBoxUser.Size = new System.Drawing.Size(80, 20);
      this.textBoxUser.TabIndex = 1;
      this.textBoxUser.TextChanged += new System.EventHandler(this.user_TextChanged);
      // 
      // labelUser
      // 
      this.labelUser.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
      this.labelUser.Location = new System.Drawing.Point(123, 12);
      this.labelUser.Name = "labelUser";
      this.labelUser.Size = new System.Drawing.Size(31, 16);
      this.labelUser.TabIndex = 0;
      this.labelUser.Text = "User";
      // 
      // panelCheck
      // 
      this.panelCheck.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
      this.panelCheck.Controls.Add(this.buttonCheck);
      this.panelCheck.Controls.Add(this.buttonCheckInfo);
      this.panelCheck.Controls.Add(this.buttonCheckCancel);
      this.panelCheck.Dock = System.Windows.Forms.DockStyle.Bottom;
      this.panelCheck.Location = new System.Drawing.Point(211, 457);
      this.panelCheck.Name = "panelCheck";
      this.panelCheck.Size = new System.Drawing.Size(621, 40);
      this.panelCheck.TabIndex = 4;
      this.panelCheck.Visible = false;
      // 
      // buttonCheck
      // 
      this.buttonCheck.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
      this.buttonCheck.Enabled = false;
      this.buttonCheck.Location = new System.Drawing.Point(520, 8);
      this.buttonCheck.Name = "buttonCheck";
      this.buttonCheck.Size = new System.Drawing.Size(96, 23);
      this.buttonCheck.TabIndex = 4;
      this.buttonCheck.Text = "Check";
      this.buttonCheck.Click += new System.EventHandler(this.buttonCheck_Click);
      // 
      // buttonCheckInfo
      // 
      this.buttonCheckInfo.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
      this.buttonCheckInfo.Enabled = false;
      this.buttonCheckInfo.Location = new System.Drawing.Point(424, 8);
      this.buttonCheckInfo.Name = "buttonCheckInfo";
      this.buttonCheckInfo.Size = new System.Drawing.Size(88, 23);
      this.buttonCheckInfo.TabIndex = 12;
      this.buttonCheckInfo.Text = "Info";
      this.buttonCheckInfo.Click += new System.EventHandler(this.buttonCheckInfo_Click);
      // 
      // buttonCheckCancel
      // 
      this.buttonCheckCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
      this.buttonCheckCancel.Enabled = false;
      this.buttonCheckCancel.Location = new System.Drawing.Point(320, 8);
      this.buttonCheckCancel.Name = "buttonCheckCancel";
      this.buttonCheckCancel.Size = new System.Drawing.Size(96, 23);
      this.buttonCheckCancel.TabIndex = 1;
      this.buttonCheckCancel.Text = "Cancel";
      this.buttonCheckCancel.Click += new System.EventHandler(this.buttonCheckCancel_Click);
      // 
      // radioButton_GEN_CLASS
      // 
      this.radioButton_GEN_CLASS.Location = new System.Drawing.Point(16, 24);
      this.radioButton_GEN_CLASS.Name = "radioButton_GEN_CLASS";
      this.radioButton_GEN_CLASS.Size = new System.Drawing.Size(104, 24);
      this.radioButton_GEN_CLASS.TabIndex = 8;
      this.radioButton_GEN_CLASS.TabStop = true;
      this.radioButton_GEN_CLASS.Text = "Class_from_DB";
      this.radioButton_GEN_CLASS.CheckedChanged += new System.EventHandler(this.radioButton_GEN_CLASS_CheckedChanged);
      // 
      // radioButton_GEN_DEF
      // 
      this.radioButton_GEN_DEF.Location = new System.Drawing.Point(16, 56);
      this.radioButton_GEN_DEF.Name = "radioButton_GEN_DEF";
      this.radioButton_GEN_DEF.Size = new System.Drawing.Size(104, 24);
      this.radioButton_GEN_DEF.TabIndex = 7;
      this.radioButton_GEN_DEF.Text = "Defintion_Class";
      this.radioButton_GEN_DEF.CheckedChanged += new System.EventHandler(this.radioButton_GEN_DEF_CheckedChanged);
      // 
      // tabControlTable
      // 
      this.tabControlTable.Controls.Add(this.tabPageDetails);
      this.tabControlTable.Controls.Add(this.tabPageData);
      this.tabControlTable.Controls.Add(this.tabPage_Check);
      this.tabControlTable.Controls.Add(this.tabPage_Generated);
      this.tabControlTable.Dock = System.Windows.Forms.DockStyle.Fill;
      this.tabControlTable.Location = new System.Drawing.Point(0, 0);
      this.tabControlTable.Name = "tabControlTable";
      this.tabControlTable.SelectedIndex = 0;
      this.tabControlTable.Size = new System.Drawing.Size(621, 417);
      this.tabControlTable.TabIndex = 5;
      this.tabControlTable.Visible = false;
      this.tabControlTable.Click += new System.EventHandler(this.tabControlTable_Click);
      this.tabControlTable.SelectedIndexChanged += new System.EventHandler(this.tabControlTable_SelectedIndexChanged);
      // 
      // tabPageDetails
      // 
      this.tabPageDetails.Controls.Add(this.GridTableDetails);
      this.tabPageDetails.Location = new System.Drawing.Point(4, 22);
      this.tabPageDetails.Name = "tabPageDetails";
      this.tabPageDetails.Size = new System.Drawing.Size(613, 391);
      this.tabPageDetails.TabIndex = 0;
      this.tabPageDetails.Text = "Details";
      this.tabPageDetails.UseVisualStyleBackColor = true;
      // 
      // GridTableDetails
      // 
      this.GridTableDetails.BackgroundColor = System.Drawing.SystemColors.ActiveCaptionText;
      this.GridTableDetails.CaptionBackColor = System.Drawing.SystemColors.Control;
      this.GridTableDetails.DataMember = "";
      this.GridTableDetails.Dock = System.Windows.Forms.DockStyle.Fill;
      this.GridTableDetails.HeaderForeColor = System.Drawing.SystemColors.ControlText;
      this.GridTableDetails.Location = new System.Drawing.Point(0, 0);
      this.GridTableDetails.Name = "GridTableDetails";
      this.GridTableDetails.ReadOnly = true;
      this.GridTableDetails.Size = new System.Drawing.Size(613, 391);
      this.GridTableDetails.TabIndex = 0;
      this.GridTableDetails.Visible = false;
      // 
      // tabPageData
      // 
      this.tabPageData.Location = new System.Drawing.Point(4, 22);
      this.tabPageData.Name = "tabPageData";
      this.tabPageData.Size = new System.Drawing.Size(613, 391);
      this.tabPageData.TabIndex = 1;
      this.tabPageData.Text = "Data";
      this.tabPageData.UseVisualStyleBackColor = true;
      // 
      // tabPage_Check
      // 
      this.tabPage_Check.Controls.Add(this.groupBox_options);
      this.tabPage_Check.Location = new System.Drawing.Point(4, 22);
      this.tabPage_Check.Name = "tabPage_Check";
      this.tabPage_Check.Size = new System.Drawing.Size(613, 391);
      this.tabPage_Check.TabIndex = 2;
      this.tabPage_Check.Text = "Check";
      this.tabPage_Check.UseVisualStyleBackColor = true;
      // 
      // groupBox_options
      // 
      this.groupBox_options.Controls.Add(this.progressBarCheck);
      this.groupBox_options.Controls.Add(this.groupBox_option);
      this.groupBox_options.Controls.Add(this.button_wd);
      this.groupBox_options.Controls.Add(this.label_report);
      this.groupBox_options.Controls.Add(this.label_CDB);
      this.groupBox_options.Controls.Add(this.textBoxDB);
      this.groupBox_options.Controls.Add(this.label_WD);
      this.groupBox_options.Controls.Add(this.textBoxDir);
      this.groupBox_options.Controls.Add(this.labelProcessBar);
      this.groupBox_options.Dock = System.Windows.Forms.DockStyle.Fill;
      this.groupBox_options.Location = new System.Drawing.Point(0, 0);
      this.groupBox_options.Name = "groupBox_options";
      this.groupBox_options.Size = new System.Drawing.Size(613, 391);
      this.groupBox_options.TabIndex = 11;
      this.groupBox_options.TabStop = false;
      // 
      // progressBarCheck
      // 
      this.progressBarCheck.Location = new System.Drawing.Point(244, 178);
      this.progressBarCheck.Name = "progressBarCheck";
      this.progressBarCheck.Size = new System.Drawing.Size(100, 23);
      this.progressBarCheck.TabIndex = 20;
      // 
      // groupBox_option
      // 
      this.groupBox_option.Controls.Add(this.button4);
      this.groupBox_option.Controls.Add(this.button3);
      this.groupBox_option.Controls.Add(this.button2);
      this.groupBox_option.Controls.Add(this.button1);
      this.groupBox_option.Controls.Add(this.checkBox2);
      this.groupBox_option.Controls.Add(this.checkBox1);
      this.groupBox_option.Controls.Add(this.checkBox3);
      this.groupBox_option.Controls.Add(this.checkBox4);
      this.groupBox_option.Controls.Add(this.checkBox5);
      this.groupBox_option.Controls.Add(this.button5);
      this.groupBox_option.Location = new System.Drawing.Point(8, 12);
      this.groupBox_option.Name = "groupBox_option";
      this.groupBox_option.Size = new System.Drawing.Size(336, 164);
      this.groupBox_option.TabIndex = 19;
      this.groupBox_option.TabStop = false;
      this.groupBox_option.Text = "OPTIONS";
      // 
      // button4
      // 
      this.button4.BackColor = System.Drawing.Color.RosyBrown;
      this.button4.Enabled = false;
      this.button4.ForeColor = System.Drawing.SystemColors.ControlText;
      this.button4.Location = new System.Drawing.Point(8, 144);
      this.button4.Name = "button4";
      this.button4.Size = new System.Drawing.Size(6, 6);
      this.button4.TabIndex = 21;
      this.button4.UseVisualStyleBackColor = false;
      // 
      // button3
      // 
      this.button3.BackColor = System.Drawing.Color.RosyBrown;
      this.button3.Enabled = false;
      this.button3.ForeColor = System.Drawing.SystemColors.ControlText;
      this.button3.Location = new System.Drawing.Point(8, 114);
      this.button3.Name = "button3";
      this.button3.Size = new System.Drawing.Size(6, 6);
      this.button3.TabIndex = 20;
      this.button3.UseVisualStyleBackColor = false;
      // 
      // button2
      // 
      this.button2.BackColor = System.Drawing.Color.RosyBrown;
      this.button2.Enabled = false;
      this.button2.ForeColor = System.Drawing.SystemColors.ControlText;
      this.button2.Location = new System.Drawing.Point(9, 84);
      this.button2.Name = "button2";
      this.button2.Size = new System.Drawing.Size(6, 6);
      this.button2.TabIndex = 19;
      this.button2.UseVisualStyleBackColor = false;
      // 
      // button1
      // 
      this.button1.BackColor = System.Drawing.Color.RosyBrown;
      this.button1.Enabled = false;
      this.button1.ForeColor = System.Drawing.SystemColors.ControlText;
      this.button1.Location = new System.Drawing.Point(9, 54);
      this.button1.Name = "button1";
      this.button1.Size = new System.Drawing.Size(6, 6);
      this.button1.TabIndex = 18;
      this.button1.UseVisualStyleBackColor = false;
      // 
      // checkBox2
      // 
      this.checkBox2.Location = new System.Drawing.Point(24, 74);
      this.checkBox2.Name = "checkBox2";
      this.checkBox2.Size = new System.Drawing.Size(304, 24);
      this.checkBox2.TabIndex = 15;
      this.checkBox2.Text = "Are there table columns without get / set method";
      this.checkBox2.CheckedChanged += new System.EventHandler(this.checkBoxGroup_CheckedChanged);
      // 
      // checkBox1
      // 
      this.checkBox1.Location = new System.Drawing.Point(24, 41);
      this.checkBox1.Name = "checkBox1";
      this.checkBox1.Size = new System.Drawing.Size(304, 32);
      this.checkBox1.TabIndex = 14;
      this.checkBox1.Text = "Are there tables without classes";
      this.checkBox1.CheckedChanged += new System.EventHandler(this.checkBoxGroup_CheckedChanged);
      // 
      // checkBox3
      // 
      this.checkBox3.Location = new System.Drawing.Point(24, 104);
      this.checkBox3.Name = "checkBox3";
      this.checkBox3.Size = new System.Drawing.Size(304, 24);
      this.checkBox3.TabIndex = 16;
      this.checkBox3.Text = "Are there get/set methods without table columns";
      this.checkBox3.CheckedChanged += new System.EventHandler(this.checkBoxGroup_CheckedChanged);
      // 
      // checkBox4
      // 
      this.checkBox4.Location = new System.Drawing.Point(24, 136);
      this.checkBox4.Name = "checkBox4";
      this.checkBox4.Size = new System.Drawing.Size(304, 24);
      this.checkBox4.TabIndex = 17;
      this.checkBox4.Text = "Are there select methods, which do not exist in the table";
      this.checkBox4.CheckedChanged += new System.EventHandler(this.checkBoxGroup_CheckedChanged);
      // 
      // checkBox5
      // 
      this.checkBox5.Location = new System.Drawing.Point(24, 16);
      this.checkBox5.Name = "checkBox5";
      this.checkBox5.Size = new System.Drawing.Size(304, 24);
      this.checkBox5.TabIndex = 20;
      this.checkBox5.Text = "Are there classes without table";
      this.checkBox5.CheckedChanged += new System.EventHandler(this.checkBoxGroup_CheckedChanged);
      // 
      // button5
      // 
      this.button5.BackColor = System.Drawing.Color.RosyBrown;
      this.button5.Enabled = false;
      this.button5.ForeColor = System.Drawing.SystemColors.ControlText;
      this.button5.Location = new System.Drawing.Point(9, 24);
      this.button5.Name = "button5";
      this.button5.Size = new System.Drawing.Size(6, 6);
      this.button5.TabIndex = 22;
      this.button5.UseVisualStyleBackColor = false;
      // 
      // button_wd
      // 
      this.button_wd.Location = new System.Drawing.Point(322, 360);
      this.button_wd.Name = "button_wd";
      this.button_wd.Size = new System.Drawing.Size(22, 20);
      this.button_wd.TabIndex = 13;
      this.button_wd.Text = "...";
      this.button_wd.Click += new System.EventHandler(this.button_wd_Click);
      // 
      // label_report
      // 
      this.label_report.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold);
      this.label_report.Location = new System.Drawing.Point(8, 185);
      this.label_report.Name = "label_report";
      this.label_report.Size = new System.Drawing.Size(168, 24);
      this.label_report.TabIndex = 11;
      this.label_report.Text = "Report Output";
      // 
      // label_CDB
      // 
      this.label_CDB.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.label_CDB.Location = new System.Drawing.Point(8, 304);
      this.label_CDB.Name = "label_CDB";
      this.label_CDB.Size = new System.Drawing.Size(144, 16);
      this.label_CDB.TabIndex = 5;
      this.label_CDB.Text = "Connectet DataBase";
      // 
      // textBoxDB
      // 
      this.textBoxDB.Location = new System.Drawing.Point(8, 320);
      this.textBoxDB.Name = "textBoxDB";
      this.textBoxDB.ReadOnly = true;
      this.textBoxDB.Size = new System.Drawing.Size(336, 20);
      this.textBoxDB.TabIndex = 4;
      this.textBoxDB.Text = "hier soll DataBase Quelle stehen";
      // 
      // label_WD
      // 
      this.label_WD.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.label_WD.Location = new System.Drawing.Point(8, 344);
      this.label_WD.Name = "label_WD";
      this.label_WD.Size = new System.Drawing.Size(120, 16);
      this.label_WD.TabIndex = 7;
      this.label_WD.Text = "Working Directory";
      // 
      // textBoxDir
      // 
      this.textBoxDir.Location = new System.Drawing.Point(8, 360);
      this.textBoxDir.Name = "textBoxDir";
      this.textBoxDir.ReadOnly = true;
      this.textBoxDir.Size = new System.Drawing.Size(320, 20);
      this.textBoxDir.TabIndex = 6;
      this.textBoxDir.Text = "hier soll der Pfadname stehen";
      // 
      // labelProcessBar
      // 
      this.labelProcessBar.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
      this.labelProcessBar.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F);
      this.labelProcessBar.Location = new System.Drawing.Point(8, 209);
      this.labelProcessBar.Name = "labelProcessBar";
      this.labelProcessBar.Size = new System.Drawing.Size(336, 88);
      this.labelProcessBar.TabIndex = 0;
      // 
      // tabPage_Generated
      // 
      this.tabPage_Generated.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
      this.tabPage_Generated.Controls.Add(this.progressBarGen);
      this.tabPage_Generated.Controls.Add(this.groupBoxInfo);
      this.tabPage_Generated.Controls.Add(this.listBoxGenReportOut);
      this.tabPage_Generated.Controls.Add(this.groupBox_Gen);
      this.tabPage_Generated.Controls.Add(this.label_GenReport);
      this.tabPage_Generated.Controls.Add(this.labelGenReportOut);
      this.tabPage_Generated.Location = new System.Drawing.Point(4, 22);
      this.tabPage_Generated.Name = "tabPage_Generated";
      this.tabPage_Generated.Size = new System.Drawing.Size(613, 391);
      this.tabPage_Generated.TabIndex = 3;
      this.tabPage_Generated.Text = "Generate";
      this.tabPage_Generated.UseVisualStyleBackColor = true;
      // 
      // progressBarGen
      // 
      this.progressBarGen.Location = new System.Drawing.Point(500, 19);
      this.progressBarGen.Name = "progressBarGen";
      this.progressBarGen.Size = new System.Drawing.Size(100, 23);
      this.progressBarGen.TabIndex = 25;
      // 
      // groupBoxInfo
      // 
      this.groupBoxInfo.Controls.Add(this.labelDBUSER);
      this.groupBoxInfo.Controls.Add(this.labelWDPath);
      this.groupBoxInfo.Controls.Add(this.labelDBSERVICE);
      this.groupBoxInfo.Controls.Add(this.label_DBService);
      this.groupBoxInfo.Controls.Add(this.label_DBUser);
      this.groupBoxInfo.Controls.Add(this.label_WDPath);
      this.groupBoxInfo.Location = new System.Drawing.Point(16, 181);
      this.groupBoxInfo.Name = "groupBoxInfo";
      this.groupBoxInfo.Size = new System.Drawing.Size(240, 184);
      this.groupBoxInfo.TabIndex = 24;
      this.groupBoxInfo.TabStop = false;
      this.groupBoxInfo.Text = "Information";
      // 
      // labelDBUSER
      // 
      this.labelDBUSER.Location = new System.Drawing.Point(56, 48);
      this.labelDBUSER.Name = "labelDBUSER";
      this.labelDBUSER.Size = new System.Drawing.Size(176, 16);
      this.labelDBUSER.TabIndex = 13;
      this.labelDBUSER.Text = "UserName";
      // 
      // labelWDPath
      // 
      this.labelWDPath.Location = new System.Drawing.Point(56, 72);
      this.labelWDPath.Name = "labelWDPath";
      this.labelWDPath.Size = new System.Drawing.Size(176, 96);
      this.labelWDPath.TabIndex = 20;
      this.labelWDPath.Text = "Working Directory";
      // 
      // labelDBSERVICE
      // 
      this.labelDBSERVICE.Location = new System.Drawing.Point(56, 24);
      this.labelDBSERVICE.Name = "labelDBSERVICE";
      this.labelDBSERVICE.Size = new System.Drawing.Size(176, 16);
      this.labelDBSERVICE.TabIndex = 15;
      this.labelDBSERVICE.Text = "ServiceName";
      // 
      // label_DBService
      // 
      this.label_DBService.Location = new System.Drawing.Point(8, 24);
      this.label_DBService.Name = "label_DBService";
      this.label_DBService.Size = new System.Drawing.Size(80, 16);
      this.label_DBService.TabIndex = 23;
      this.label_DBService.Text = "Service :";
      // 
      // label_DBUser
      // 
      this.label_DBUser.Location = new System.Drawing.Point(8, 48);
      this.label_DBUser.Name = "label_DBUser";
      this.label_DBUser.Size = new System.Drawing.Size(90, 16);
      this.label_DBUser.TabIndex = 22;
      this.label_DBUser.Text = "User      :";
      // 
      // label_WDPath
      // 
      this.label_WDPath.Location = new System.Drawing.Point(8, 72);
      this.label_WDPath.Name = "label_WDPath";
      this.label_WDPath.Size = new System.Drawing.Size(90, 16);
      this.label_WDPath.TabIndex = 21;
      this.label_WDPath.Text = "WD       :";
      // 
      // listBoxGenReportOut
      // 
      this.listBoxGenReportOut.BackColor = System.Drawing.SystemColors.Menu;
      this.listBoxGenReportOut.HorizontalScrollbar = true;
      this.listBoxGenReportOut.Location = new System.Drawing.Point(264, 101);
      this.listBoxGenReportOut.Name = "listBoxGenReportOut";
      this.listBoxGenReportOut.SelectionMode = System.Windows.Forms.SelectionMode.None;
      this.listBoxGenReportOut.Size = new System.Drawing.Size(336, 264);
      this.listBoxGenReportOut.TabIndex = 19;
      // 
      // groupBox_Gen
      // 
      this.groupBox_Gen.Controls.Add(this.buttonGenSelectAll);
      this.groupBox_Gen.Controls.Add(this.buttonGenerate);
      this.groupBox_Gen.Controls.Add(this.radioButton_GEN_CLASS);
      this.groupBox_Gen.Controls.Add(this.radioButton_GEN_DEF);
      this.groupBox_Gen.Controls.Add(this.buttonGenCancle);
      this.groupBox_Gen.Controls.Add(this.buttonGenXmlFile);
      this.groupBox_Gen.Controls.Add(this.checkBoxWDFiles);
      this.groupBox_Gen.Location = new System.Drawing.Point(14, 16);
      this.groupBox_Gen.Name = "groupBox_Gen";
      this.groupBox_Gen.Size = new System.Drawing.Size(240, 152);
      this.groupBox_Gen.TabIndex = 14;
      this.groupBox_Gen.TabStop = false;
      this.groupBox_Gen.Text = "Options";
      // 
      // buttonGenSelectAll
      // 
      this.buttonGenSelectAll.Location = new System.Drawing.Point(112, 96);
      this.buttonGenSelectAll.Name = "buttonGenSelectAll";
      this.buttonGenSelectAll.Size = new System.Drawing.Size(96, 23);
      this.buttonGenSelectAll.TabIndex = 20;
      this.buttonGenSelectAll.Text = "SelectAll";
      this.buttonGenSelectAll.Click += new System.EventHandler(this.buttonGenSelectAll_Click);
      // 
      // buttonGenerate
      // 
      this.buttonGenerate.Location = new System.Drawing.Point(8, 96);
      this.buttonGenerate.Name = "buttonGenerate";
      this.buttonGenerate.Size = new System.Drawing.Size(96, 23);
      this.buttonGenerate.TabIndex = 9;
      this.buttonGenerate.Text = "Generate";
      this.buttonGenerate.Click += new System.EventHandler(this.buttonGenerate_Click);
      // 
      // buttonGenCancle
      // 
      this.buttonGenCancle.Enabled = false;
      this.buttonGenCancle.Location = new System.Drawing.Point(8, 120);
      this.buttonGenCancle.Name = "buttonGenCancle";
      this.buttonGenCancle.Size = new System.Drawing.Size(96, 23);
      this.buttonGenCancle.TabIndex = 6;
      this.buttonGenCancle.Text = "Cancel";
      this.buttonGenCancle.Click += new System.EventHandler(this.buttonGenCancle_Click);
      // 
      // buttonGenXmlFile
      // 
      this.buttonGenXmlFile.Enabled = false;
      this.buttonGenXmlFile.Location = new System.Drawing.Point(112, 120);
      this.buttonGenXmlFile.Name = "buttonGenXmlFile";
      this.buttonGenXmlFile.Size = new System.Drawing.Size(96, 23);
      this.buttonGenXmlFile.TabIndex = 19;
      this.buttonGenXmlFile.Text = "XML File";
      this.buttonGenXmlFile.Click += new System.EventHandler(this.buttonGenXmlFile_Click);
      // 
      // checkBoxWDFiles
      // 
      this.checkBoxWDFiles.Location = new System.Drawing.Point(216, 96);
      this.checkBoxWDFiles.Name = "checkBoxWDFiles";
      this.checkBoxWDFiles.Size = new System.Drawing.Size(16, 24);
      this.checkBoxWDFiles.TabIndex = 21;
      this.checkBoxWDFiles.CheckedChanged += new System.EventHandler(this.checkBoxWDFiles_CheckedChanged);
      // 
      // label_GenReport
      // 
      this.label_GenReport.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold);
      this.label_GenReport.Location = new System.Drawing.Point(264, 19);
      this.label_GenReport.Name = "label_GenReport";
      this.label_GenReport.Size = new System.Drawing.Size(336, 24);
      this.label_GenReport.TabIndex = 12;
      this.label_GenReport.Text = "Report";
      // 
      // labelGenReportOut
      // 
      this.labelGenReportOut.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
      this.labelGenReportOut.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F);
      this.labelGenReportOut.Location = new System.Drawing.Point(264, 47);
      this.labelGenReportOut.Name = "labelGenReportOut";
      this.labelGenReportOut.Size = new System.Drawing.Size(336, 50);
      this.labelGenReportOut.TabIndex = 7;
      // 
      // TabControlPanel
      // 
      this.TabControlPanel.AutoScroll = true;
      this.TabControlPanel.Controls.Add(this.tabControlTable);
      this.TabControlPanel.Dock = System.Windows.Forms.DockStyle.Fill;
      this.TabControlPanel.Location = new System.Drawing.Point(211, 40);
      this.TabControlPanel.Name = "TabControlPanel";
      this.TabControlPanel.Size = new System.Drawing.Size(621, 417);
      this.TabControlPanel.TabIndex = 6;
      // 
      // contextMenuListB
      // 
      this.contextMenuListB.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.menuItemOpenFile,
            this.menuItemCompareData});
      // 
      // menuItemOpenFile
      // 
      this.menuItemOpenFile.Index = 0;
      this.menuItemOpenFile.Text = "Open File";
      this.menuItemOpenFile.Click += new System.EventHandler(this.menuItemOpenFile_Click);
      // 
      // menuItemCompareData
      // 
      this.menuItemCompareData.Index = 1;
      this.menuItemCompareData.Text = "Compare Data";
      this.menuItemCompareData.Click += new System.EventHandler(this.menuItemCompareData_Click);
      // 
      // backgroundWorkerCheck
      // 
      this.backgroundWorkerCheck.WorkerReportsProgress = true;
      this.backgroundWorkerCheck.WorkerSupportsCancellation = true;
      this.backgroundWorkerCheck.DoWork += new System.ComponentModel.DoWorkEventHandler(this.backgroundWorkerCheck_DoWork);
      this.backgroundWorkerCheck.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(this.backgroundWorkerCheck_RunWorkerCompleted);
      this.backgroundWorkerCheck.ProgressChanged += new System.ComponentModel.ProgressChangedEventHandler(this.backgroundWorkerCheck_ProgressChanged);
      // 
      // backgroundWorkerGen
      // 
      this.backgroundWorkerGen.WorkerReportsProgress = true;
      this.backgroundWorkerGen.WorkerSupportsCancellation = true;
      this.backgroundWorkerGen.DoWork += new System.ComponentModel.DoWorkEventHandler(this.backgroundWorkerGen_DoWork);
      this.backgroundWorkerGen.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(this.backgroundWorkerGen_RunWorkerCompleted);
      this.backgroundWorkerGen.ProgressChanged += new System.ComponentModel.ProgressChangedEventHandler(this.backgroundWorkerGen_ProgressChanged);
      // 
      // MainForm
      // 
      this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
      this.ClientSize = new System.Drawing.Size(832, 497);
      this.Controls.Add(this.TabControlPanel);
      this.Controls.Add(this.panelCheck);
      this.Controls.Add(this.panelConnection);
      this.Controls.Add(this.splitter1);
      this.Controls.Add(this.panelTables);
      this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
      this.Menu = this.mainMenu1;
      this.Name = "MainForm";
      this.Text = "DBClassCodeUtility";
      this.Load += new System.EventHandler(this.readServices);
      this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MainForm_FormClosed);
      this.Closing += new System.ComponentModel.CancelEventHandler(this.MainForm_Closing);
      this.panelTables.ResumeLayout(false);
      this.panelConnection.ResumeLayout(false);
      this.panelConnection.PerformLayout();
      this.panelCheck.ResumeLayout(false);
      this.tabControlTable.ResumeLayout(false);
      this.tabPageDetails.ResumeLayout(false);
      ((System.ComponentModel.ISupportInitialize)(this.GridTableDetails)).EndInit();
      this.tabPage_Check.ResumeLayout(false);
      this.groupBox_options.ResumeLayout(false);
      this.groupBox_options.PerformLayout();
      this.groupBox_option.ResumeLayout(false);
      this.tabPage_Generated.ResumeLayout(false);
      this.groupBoxInfo.ResumeLayout(false);
      this.groupBox_Gen.ResumeLayout(false);
      this.TabControlPanel.ResumeLayout(false);
      this.ResumeLayout(false);

    }
    #endregion

    /// <summary>
    /// The main entry point for the application.
    /// </summary>
    /// 
    [STAThread]
    static void Main() 
    {
      Application.Run(new MainForm());
    }


    private void menuItemOpenClick(object sender, System.EventArgs e)
    {
      panelConnection.Visible = true; // make Connection panel visible
      string service;
      
      // read User Settings
      int index = 0;
      if( (index=comboBoxServices.Items.IndexOf(CData.Instance.ReadSetting("UserSettings", "SelectedDataBase"))) != -1 )
      {
        service = comboBoxServices.Items[index].ToString();
        comboBoxServices.Text = service;
      }
      else
        service = comboBoxServices.Text;

      textBoxUser.Text = Connections.getUserAuthentication(service);
      textBoxPassword.Text = Connections.getPasswordAuthentication(service);

      if(textBoxUser.Text.Length != 0 && textBoxPassword.Text.Length != 0 && comboBoxServices.Text.Length != 0)
        buttonConnect.Enabled = true; // Enable button "Connect"
      else
        buttonConnect.Enabled = false; // button "Connect" by default Disabled
    }


    private void readServices(object sender, System.EventArgs e)
    {
      RegistryKey reg;
      RegistryKey Services;

      try
      {
        reg = Registry.LocalMachine;
        Services = reg.OpenSubKey("SOFTWARE\\ODBC\\ODBC.INI\\ODBC Data Sources");

        // Request all values from the "ODBC Data Sources" key
        string [] valueNames = Services.GetValueNames();

        // Enumerate the values
        for (int i = 0; i < valueNames.Length; i++)
        {
          string serv = valueNames[i];
          comboBoxServices.Items.Add(serv);
        }
        //comboBoxServices.SelectedIndex = 0;
      }
      catch(Exception ex)
      {
        MessageBox.Show(ex.StackTrace + " : \r\n\r\n"  + ex.Message);
      }
      comboBoxServices.EndUpdate();

      string ServiceName = comboBoxServices.Items[0].ToString();
          
      CData.Instance.makeIniFile(Environment.CurrentDirectory, ServiceName);

      // Set the User Settings
      if(CData.Instance.ReadSetting("UserSettings", "Gen").Equals("GEN_DEF"))
        this.radioButton_GEN_DEF.Checked = true;
      else if(CData.Instance.ReadSetting("UserSettings", "Gen").Equals("GEN_CLASS"))
        this.radioButton_GEN_CLASS.Checked = true;

      if(!CData.Instance.ReadSetting("UserSettings", "WorkingDirectory").Equals(""))
        CData.Instance.setWorkingDirectory(CData.Instance.ReadSetting("UserSettings", "WorkingDirectory"));

      // reduce click for user
      this.menuItemOpen.PerformClick();
    }
    

    private void connectClick(object sender, System.EventArgs e)
    {
      string ServiceName;
      Cursor = Cursors.WaitCursor;
      
      if (comboBoxServices.SelectedIndex != -1)
      {
        ServiceName = comboBoxServices.SelectedItem.ToString();
      }
      else
      {
        ServiceName = comboBoxServices.Text;
      }
      
      // Set selected user setting
      CData.Instance.WriteSetting("UserSettings","SelectedDataBase", ServiceName);

      if (Connections.makeConnection(textBoxUser.Text, textBoxPassword.Text, ServiceName,tabControlConnections.Controls.Count.ToString()))
      {
        panelConnection.Visible = false;
        tabControlConnections.ShowToolTips = true;

        ListCPPClasses = new ListBox();
        ListCPPClasses.SelectedIndexChanged += new System.EventHandler(this.tableSelect);
        ListCPPClasses.MouseDown += new System.Windows.Forms.MouseEventHandler(this.ListB_MouseDown);
        ListCPPClasses.ContextMenu = this.contextMenuListB;

        ListCPPClasses.HorizontalScrollbar = true;
        //ListCPPClasses.ItemHeight = 80;
        ListCPPClasses.Dock = DockStyle.Fill;

        RefreshListBoxCPPClasses(ServiceName, tabControlConnections.Controls.Count.ToString());

        loadToTabControl(ListCPPClasses, ServiceName, textBoxPassword.Text);

        menuItemClose.Enabled = true;
        menuItemUpdate.Enabled = true;

        TableDescriptionDataSet.Tables.Clear();
        ListCPPClasses.SetSelected(0, true);
      }

      Cursor = Cursors.Default;
    }

    private bool RefreshListBoxCPPClasses(string ServiceName, string tabPageIndex)
    {
      bool ReturnValue = true;
  
      if (ListCPPClasses != null )
      {
        int SelectedIndex = ListCPPClasses.SelectedIndex;

        ListCPPClasses.Items.Clear();

        System.Data.Odbc.OdbcConnection conn = new System.Data.Odbc.OdbcConnection();
        CTableAnalyser TableAnalyser         = new CTableAnalyser();
        ArrayList TabNames                   = new ArrayList();

        //get connection with identification "service + extention"
        if (Connections.getConnection(ServiceName, ref conn, tabPageIndex))
        {
          bool IsWildCardFilterOn = true;
          if (CData.Instance.ReadSetting("UserSettings", "WildCardFilter") == "no")
          {
            IsWildCardFilterOn = false;
          }
          else
          {
            IsWildCardFilterOn = true;
          }

          // read tablenames from DB
          if (TableAnalyser.readTables(TabNames, ref conn, IsWildCardFilterOn))
          {
            System.Collections.IEnumerator Enumerator = TabNames.GetEnumerator();
            while (Enumerator.MoveNext())
            {
              ListCPPClasses.Items.Add(Enumerator.Current.ToString());
            }
          }
        }// if (Connections.getConnection(ServiceName, ref conn, tabControlConnections.Controls.Count.ToString()))
        else
        {
          ReturnValue = false;
        }

        if (SelectedIndex >= 0 && SelectedIndex <= ListCPPClasses.Items.Count-1)
        {
          ListCPPClasses.SetSelected(SelectedIndex, true);    
        }  
      }
      else
      {
        ReturnValue = false;
      }

      return ReturnValue;
    }

    private void loadToTabControl(ListBox listBox, string TabPageText, string ToolTipText)
    {
      System.Windows.Forms.TabPage tabPage = new System.Windows.Forms.TabPage(); ;
      tabPage.Tag = tabControlConnections.Controls.Count;
      tabPage.Text = TabPageText;
      tabPage.ToolTipText = ToolTipText;

      tabPage.Size = new System.Drawing.Size(256, 214);
      tabPage.TabIndex = 0;

      tabPage.Controls.Add(listBox);
      tabControlConnections.Controls.Add(tabPage);
      tabControlConnections.SelectedIndex = (int)tabPage.Tag;  
    }

    private void menuItemCloseClick(object sender, System.EventArgs e)
    {
      string ConnectionToClose = tabControlConnections.SelectedTab.Text;
      Connections.closeConnection(ConnectionToClose, tabControlConnections.SelectedTab.Tag.ToString());
      tabControlConnections.Controls.Remove(tabControlConnections.SelectedTab);
      if (tabControlConnections.Controls.Count == 0)
      {
        GridTableDetails.DataSource = null ;
        GridTableDetails.CaptionText = "";
        GridTableDetails.Visible = false;
        menuItemClose.Enabled = false;
        menuItemUpdate.Enabled = false;
        tabControlTable.Visible = false;
      }

      if(tabControlConnections.TabCount == 0)
      {
        panelCheck.Visible = false; 
      }

      Cursor = Cursors.Default;
    }

    private void user_TextChanged(object sender, System.EventArgs e)
    {
      if(textBoxUser.Text.Length != 0 && textBoxPassword.Text.Length != 0 && comboBoxServices.Text.Length != 0)
        buttonConnect.Enabled = true; // Enable button "Connect"
    }

    private void password_TextChanged(object sender, System.EventArgs e)
    {
      if(textBoxUser.Text.Length != 0 && textBoxPassword.Text.Length != 0 && comboBoxServices.Text.Length != 0)
        buttonConnect.Enabled = true; // Enable button "Connect"
    }

    private void service_TextChanged(object sender, System.EventArgs e)
    {
      if(textBoxUser.Text.Length != 0 && textBoxPassword.Text.Length != 0 && comboBoxServices.Text.Length != 0)
        buttonConnect.Enabled = true; // Enable button "Connect"
    }

    // table details and content
    private bool loadTable(string tableName, string service, string tabPageIndex, bool readData)
    {
      bool RetValue = true;

      if (readData)
      {
        if (!TableDescriptionDataSet.Tables.Contains(tableName + "DATA"))
        {
          System.Data.Odbc.OdbcConnection conn = new System.Data.Odbc.OdbcConnection();

          if (Connections.getConnection(service, ref conn, tabPageIndex))
          {
            // table for content
            DataTable TableData = new DataTable(tableName + "DATA");// Table that contains the Data
            CTableAnalyser reader = new CTableAnalyser();
            reader.readTableContent(tableName, ref TableData, conn);
            TableDescriptionDataSet.Tables.Add(TableData);
            RetValue = true;
          }
          else
          {
            RetValue = false;
          }

          conn.Close();
        }
        else
          if (TableDescriptionDataSet.Tables.Contains(tableName + "DATA"))
            RetValue = true;
      }

      if (!TableDescriptionDataSet.Tables.Contains(tableName)) // to avoid additional select
      {
        DataTable TableDesc = new DataTable(tableName);// Table that describe the Table with name "TableName"

        if (IsDBTable)
        {
          System.Data.Odbc.OdbcConnection conn = new System.Data.Odbc.OdbcConnection();

          if (Connections.getConnection(service, ref conn, tabPageIndex))
          {
            CTableAnalyser reader = new CTableAnalyser();

            if (CData.Instance.ReadSetting("UserSettings", "WildCardFilter") == "no")
            {
              // table for details
              reader.readTableDetails(tableName, ref TableDesc, conn, false);
            }
            else
            {
              // table for details
              reader.readTableDetails(tableName, ref TableDesc, conn, true);
            }
          }
          else 
          {
            RetValue = false;
          }

          conn.Close();
        }
        TableDescriptionDataSet.Tables.Add(TableDesc);
        RetValue = RetValue && true;
      }
      else
      {
        if (TableDescriptionDataSet.Tables.Contains(tableName))
          RetValue = RetValue && true;
      }

      return RetValue;
    }

    // table comments
    private string getTableComment(string tableName, string service, string tabPageIndex)
    {
      string RetValue = "";

      //System.Data.Odbc.OdbcConnection conn = new System.Data.Odbc.OdbcConnection();

      //if (Connections.getConnection(service, ref conn, tabPageIndex))
      //{    
      //}
      //else
      //{
      //}

      //conn.Close();

      return RetValue;
    }

    private void tableSelect(object sender, System.EventArgs e)
    {
      if(ListCPPClasses.SelectedItems.Count >= 1)
      {
        if (IsDBTable)
        {
          string TableName = ListCPPClasses.SelectedItem.ToString();
          string Service = tabControlConnections.SelectedTab.Text;
          string tabPageIndex = tabControlConnections.SelectedIndex.ToString();

          if (tabControlTable.SelectedIndex == 1) // read data
          {
            if (!loadTable(TableName, Service, tabPageIndex, true))
              return;
          }
          else if (!loadTable(TableName, Service, tabPageIndex, false))
            return;
          {
            GridTableDetails.CaptionText = TableName;

            // if Details-Page "0" selected 
            if (tabControlTable.SelectedIndex == 0)
            {
              GridTableDetails.DataSource = TableDescriptionDataSet.Tables[TableName];
              //GridTableDetails.SetDataBinding(TableDescriptionDataSet, TableName);
              GridTableDetails.Refresh();
              newWidth(TableDescriptionDataSet, TableName, 0);

              if (tabControlTable.TabPages[0].Controls.Count == 0)
                tabControlTable.TabPages[0].Controls.Add(GridTableDetails);
            }
            //if Data-Page "1" selected or tabPage_Generate "3"
            else if (tabControlTable.SelectedIndex == 1 || tabControlTable.SelectedIndex == 3)
            {
              Cursor = Cursors.WaitCursor;
              GridTableDetails.DataSource = TableDescriptionDataSet.Tables[TableName + "DATA"];
              GridTableDetails.Refresh();
              Cursor = Cursors.Default;

              if (tabControlTable.TabPages[1].Controls.Count == 0)
                tabControlTable.TabPages[1].Controls.Add(GridTableDetails);

              labelDBUSER.Text = Connections.getDBName();
              labelDBSERVICE.Text = Connections.getDBService();
              labelWDPath.Text = CData.Instance.getWorkingDirectory();

              if (ListCPPClasses.SelectedIndices.Count != 0)
              {
                buttonGenerate.Enabled = true;
                labelGenReportOut.Text = "Status: Ready" + " \n\r";

                if (ListCPPClasses.SelectedItems.Count == 1)
                {
                  labelGenReportOut.Text += "Table number " + (ListCPPClasses.SelectedIndex + 1);
                }
                else if (ListCPPClasses.SelectedItems.Count >= 1)
                {
                  labelGenReportOut.Text += (ListCPPClasses.SelectedItems.Count) + " table(s) selected";
                }

              }
              else
              {
                labelGenReportOut.Text = "Status: Make your selection" + " \n\r";
                buttonGenerate.Enabled = false;
              }

              buttonGenXmlFile.Enabled = false;
            }
            //tabPage_Check
            else if (tabControlTable.SelectedIndex == 2)
            {
              button1.BackColor = Color.RosyBrown;
              button2.BackColor = Color.RosyBrown;
              button3.BackColor = Color.RosyBrown;
              button4.BackColor = Color.RosyBrown;
              button5.BackColor = Color.RosyBrown;
              buttonCheckInfo.Enabled = false;

              if (ListCPPClasses.SelectedIndices.Count != 0 && checkBox1.Checked || checkBox2.Checked ||
                checkBox3.Checked || checkBox4.Checked || checkBox5.Checked)
              {
                buttonCheck.Enabled = true;
                labelProcessBar.Text = "Status: Ready" + " \n\r";
              }
              else
              {
                labelProcessBar.Text = "Status: Make your selection " + " \n\r";
                buttonCheck.Enabled = false;
              }

              if (ListCPPClasses.SelectedItems.Count == 1)
              {
                labelProcessBar.Text += "Table number " + (ListCPPClasses.SelectedIndex + 1);
              }

              textBoxDir.Text = CData.Instance.getWorkingDirectory();
              textBoxDB.Text = Connections.getDBService();
            }

            GridTableDetails.Visible = true;
            tabControlTable.Visible = true;

          }// if (Connections.getConnection(...))
        }
        else if (menuItemClassCodeUtility.Checked)
        {
          //tabPage_Generate "3"
          if (tabControlTable.SelectedIndex == 0)
          {
            labelDBUSER.Text = "";
            labelDBSERVICE.Text = "";
            labelWDPath.Text = CData.Instance.getWorkingDirectory();

            if (ListCPPClasses.SelectedIndices.Count != 0)
            {
              buttonGenerate.Enabled = true;
              labelGenReportOut.Text = "Status: Ready" + " \n\r";

              if (ListCPPClasses.SelectedItems.Count == 1)
              {
                labelGenReportOut.Text += "File number " + (ListCPPClasses.SelectedIndex + 1);
              }
              else if (ListCPPClasses.SelectedItems.Count >= 1)
              {
                labelGenReportOut.Text += (ListCPPClasses.SelectedItems.Count) + " table(s) selected";
              }

            }
            else
            {
              labelGenReportOut.Text = "Status: Make your selection" + " \n\r";
              buttonGenerate.Enabled = false;
            }

            buttonGenXmlFile.Enabled = false;
          }
        }
      }
    }// private void tableSelect(object sender, System.EventArgs e


    private void tabControlConnections_SelectedIndexChanged(object sender, System.EventArgs e)
    {
      if(tabControlConnections.Controls.Count != 0)
      {
        ListCPPClasses = (ListBox)tabControlConnections.SelectedTab.Controls[0];
        buttonCheck.Enabled = false;

        //Load table to grid if database connection changes
        if (ListCPPClasses.SelectedItems.Count != 0)
        {
          //void tableSelect()
          TableDescriptionDataSet.Tables.Clear();
          ListCPPClasses.SetSelected(ListCPPClasses.SelectedIndex,true);         
        }
      }
    }

    private void tabControlTable_SelectedIndexChanged(object sender, System.EventArgs e)
    {

      int topIndex = ListCPPClasses.TopIndex;

      if (IsDBTable && tabControlConnections.SelectedTab != null)
      {
        ListCPPClasses = (ListBox)tabControlConnections.SelectedTab.Controls[0];

        //Load table to grid for right tabpage
        if (ListCPPClasses.SelectedItems.Count != 0)
        {
          //void tableSelect()
          ListCPPClasses.SetSelected(ListCPPClasses.SelectedIndex, true);
          ListCPPClasses.TopIndex = topIndex;
          ListCPPClasses.SetSelected(ListCPPClasses.SelectedIndex, true);
        }
      }

    }//tabControlTable_SelectedIndexChanged

    void newWidth(DataSet ds, string TableName, int ColumnIndex)
    {
      int maxlength = 0;
      int rows_count = ds.Tables[TableName].Rows.Count; 
      string str = "";
      int length = 0;

      Graphics g = this.GridTableDetails.CreateGraphics();

      // Take width one balnk space to add to the new width to the Column   
      int offset = Convert.ToInt32(Math.Ceiling(g.MeasureString(" ", this.GridTableDetails.Font).Width));

      for (int i=0; i < rows_count; ++i)
      {
        str =  ds.Tables[TableName].Rows[i][ColumnIndex].ToString();

        // Get the width of Current Field String according to the Font
        length = Convert.ToInt32(Math.Ceiling(g.MeasureString(str, this.GridTableDetails.Font).Width));
        if (length  > maxlength)                
        {
          maxlength = length;
        }
      }// End of For Loop

      maxlength += offset;

      // Create new Table Style
      DataGridTableStyle ts = new DataGridTableStyle();
      ts.MappingName = TableName;
      this.GridTableDetails.TableStyles.Clear();
      this.GridTableDetails.TableStyles.Add(ts);

      // Assign New Width to DataGrid column
      this.GridTableDetails.TableStyles[TableName].GridColumnStyles[0].Width = maxlength;
    }

    private void comboBoxServices_SelectedIndexChanged(object sender, System.EventArgs e)
    {
      string service = ((ComboBox)sender).Text;

      string User = Connections.getUserAuthentication(service);
      string Password = Connections.getPasswordAuthentication(service);

      if( User.Length != 0 && Password.Length != 0 )
      {
        textBoxUser.Text = User;
        textBoxPassword.Text = Password;       
      }
     
      if(textBoxUser.Text.Length != 0 && textBoxPassword.Text.Length != 0 && comboBoxServices.Text.Length != 0)
      {       
        buttonConnect.Enabled = true; // Enable button "Connect"
      }
      else
      {
        buttonConnect.Enabled = false; // Disable button "Connect"
      }
    }

    // Are there classes in the working directory with no table (flagArr.Contains(4))
    private void SearchForTables()
    {
      string sFileName = null;
      int classCount = 0;
      int classNotExisting = 0;

      ArrayList files = CData.Instance.getTablesInPath(true);
      
      methodSummary += "--------------------------------------------------------------------" + "\n\r\n\r";
      methodSummary += "These files have no table: \n\r\n\r";

      for ( int ii = 0 ; ii < files.Count; ii++)
      {
        //sFileName = files[ii.].Name.Substring(1);

        sFileName = files[ii].ToString();
           
        if(!ListCPPClasses.Items.Contains(sFileName))
        {
          classNotExisting++;
          methodSummary += "\t " +  sFileName + ".cpp/h \n\r\n\r";
          button5.BackColor = Color.MediumSeaGreen;
        }
        else
        {
          classCount++;
          //methodSummary += sFileName + "\t\t\t YES (table) \n\r\n\r";
        }
      }// for ( int ai = 0 ; ai < fileInfo.Length; ai++)
      methodSummary += "--------------------------------------------------------------------" + "\n\r\n\r";

      methodSummary = methodSummary.Insert(0, ((classCount+classNotExisting) + " files have been inspected \n\r\n\r" 
        +(classCount) + " files exist as table \n\r\n\r" 
        + classNotExisting + " files have no table \n\r\n\r"));
        
      labelProcessBar.Text = "Status: Finished" + " \n\r" +
        (classNotExisting+classCount) + " file(s) are/were monitored and of these " + classNotExisting + " not existing as table"; 
        
      //for enabling the info button 
      count = classCount;
      notExisting= classNotExisting;  
    }

    // Are there tables without class (flagArr.Contains(0))
    private void SearchForClasses(string Filename)
    {
      // Setzt den Filename für die Pfadangabe wieder auf WorkingDirectory
      string PathName = CData.Instance.getWorkingDirectory();
      PathName += "\\C";
      PathName += Filename;

      if((!File.Exists(PathName + ".h")) && (!File.Exists(PathName + ".cpp")) )
      {
        // first
        if( notExisting == 0 )
        {
          methodSummary += "--------------------------------------------------------------------" + "\n\r\n\r";
          methodSummary += "These tables have no files: \n\r\n\r";
        }

        methodSummary += "\t " + Filename + "\n\r";
        methodSummary += "\n\r";

        notExisting++;
      }
      else
      {
        button1.BackColor = Color.MediumSeaGreen;
        count++;
      }
    }

    private void buttonCheck_Click(object sender, System.EventArgs e)
    {
      string FileNameChecker = @CData.Instance.getWorkingDirectory() + "\\DBClassCodeUtility.txt";
      //Prüft ob es die Datei DBClassCodeUtility.txt gibt

      long SelectedIndex = tabControlTable.SelectedIndex;

      if(!File.Exists(FileNameChecker))
      {
        StreamWriter file = File.CreateText((FileNameChecker));
        file.Close();
      }
      else
      {
        FileStream  file = File.Create((FileNameChecker));
        file.Close();
      }
      
      button1.BackColor = Color.RosyBrown;
      button2.BackColor = Color.RosyBrown;
      button3.BackColor = Color.RosyBrown;
      button4.BackColor = Color.RosyBrown;
      button5.BackColor = Color.RosyBrown;
      
      flagArr = new  ArrayList();
      
      methodSummary = "";
      methodSummary += "\n\r\n\r";

      Cursor = Cursors.WaitCursor;

      // Are there tables without class
      if(checkBox1.Checked == true)
        flagArr.Add(0);

      // Are there table columns without get / set method
      if(checkBox2.Checked == true)
        flagArr.Add(1);

      // Are there get/set methods without table columns
      if(checkBox3.Checked == true)
        flagArr.Add(2);

      // Are there select methods, which do not exist in the table
      if(checkBox4.Checked == true)
        flagArr.Add(3);

      // Are there classes in the working directory with no table
      if(checkBox5.Checked == true)
        flagArr.Add(4);

      if (!flagArr.Count.Equals(0))
      {
        buttonCheck.Enabled = false;
        buttonCheckInfo.Enabled = false;
        buttonCheckCancel.Enabled = true;

        labelProcessBar.Text = "Please Wait ... \r\n";

        sActInfo local;
        local.Service            = tabControlConnections.SelectedTab.Text.ToString(); 
        local.tabPageIndex       = tabControlConnections.SelectedIndex.ToString();
        local.selectedItemsCount = ListCPPClasses.SelectedItems.Count;

        backgroundWorkerCheck.RunWorkerAsync(local);
      }

      Cursor = Cursors.Default;   
    }//private void buttonCheck_Click(object sender, System.EventArgs e)

    private void buttonGenerate_Click(object sender, System.EventArgs e)
    {
      listBoxGenReportOut.Items.Clear();

      buttonGenXmlFile.Enabled = false;
      buttonGenerate.Enabled = false;
      buttonGenCancle.Enabled = true;
      buttonGenSelectAll.Enabled = false;
      
      labelGenReportOut.Text = "Please Wait ... \r\n";

      sActInfo local;
      local.Service            = tabControlConnections.SelectedTab.Text.ToString();
      local.tabPageIndex       = tabControlConnections.SelectedIndex.ToString();
      local.selectedItemsCount = ListCPPClasses.SelectedItems.Count;

      backgroundWorkerGen.RunWorkerAsync(local);
    }// private void buttonGenerate_Click(object sender, System.EventArgs e)
    
    private void menuItemTool_Click(object sender, System.EventArgs e)
    {
      Settings setting = new Settings();
      setting.ShowDialog();
      textBoxDir.Text = CData.Instance.getWorkingDirectory();
      labelWDPath.Text = CData.Instance.getWorkingDirectory();

      if (menuItemClassCodeUtility.Checked)
      {
        ArrayList files = CData.Instance.getTablesInPath(false);
        ListCPPClasses.Items.Clear();

        foreach (string file in files)
        {
          ListCPPClasses.Items.Add(file);
        }
      }
      else
      {

        if (tabControlConnections.SelectedTab != null)
        {
          RefreshListBoxCPPClasses(tabControlConnections.SelectedTab.Text, tabControlConnections.SelectedIndex.ToString());

          menuItemUpdate_Click(new object(), new EventArgs());
        }
      }
    }

    private void radioButton_GEN_CLASS_CheckedChanged(object sender, System.EventArgs e)
    {
      CData.Instance.WriteSetting("UserSettings","Gen", "GEN_CLASS");
    }

    private void radioButton_GEN_DEF_CheckedChanged(object sender, System.EventArgs e)
    {
      CData.Instance.WriteSetting("UserSettings","Gen", "GEN_DEF");
    }

    private void tabControlTable_Click(object sender, System.EventArgs e)
    {
      // tabPage_Check
      if( tabControlTable.SelectedIndex == 2 )
      {
        panelCheck.Visible = true;
        buttonCheckCancel.Enabled = false;

        ListCPPClasses.SelectionMode = SelectionMode.MultiExtended;

        if (backgroundWorkerCheck.IsBusy)
          backgroundWorkerCheck.CancelAsync();

        progressBarCheck.Value = 0;
      }
      //tabPage_Generate
      else if (tabControlTable.SelectedIndex == 3)
      {
        panelCheck.Visible = false;
        buttonGenCancle.Enabled = false;
        buttonGenXmlFile.Enabled = false;

        ListCPPClasses.SelectionMode = SelectionMode.MultiExtended;

        if (backgroundWorkerGen.IsBusy)
          backgroundWorkerGen.CancelAsync();

        progressBarGen.Value = 0;
      }
      else
      {
        panelCheck.Visible = false; 

        ListCPPClasses.SelectionMode = SelectionMode.One;

        TableDescriptionDataSet.Tables.Clear();
     
        if(ListCPPClasses.SelectedItems.Count > 1)
        {  
          ListCPPClasses.ClearSelected();
          ListCPPClasses.SetSelected(0,true);
        }
      }
    }

    private void buttonGenCancle_Click(object sender, System.EventArgs e)
    {
      // Disable the Cancel button.
      backgroundWorkerGen.CancelAsync();

      // Disable the Cancel button.
      buttonGenCancle.Enabled = false;
      buttonGenerate.Enabled = true;  
    }

    private void buttonCheckCancel_Click(object sender, System.EventArgs e)
    {
      // Disable the Cancel button.
      backgroundWorkerCheck.CancelAsync();

      buttonCheckCancel.Enabled = false;
      buttonCheck.Enabled = true;
    }

    private void buttonCheckInfo_Click(object sender, System.EventArgs e)
    {
      buttonCheckInfo.Enabled = false;
      int count = 0;

      #region WriteOutAndShowSummary    
      try
      {
        StreamReader readChecker =  File.OpenText((@CData.Instance.getWorkingDirectory() + "\\DBClassCodeUtility.txt"));
        readChecker.Close();
        StreamWriter methodChecker =  File.CreateText((@CData.Instance.getWorkingDirectory() + "\\DBClassCodeUtility.txt"));
        methodChecker.WriteLine(methodSummary);
        methodChecker.Close();    
        System.Diagnostics.Process process = System.Diagnostics.Process.Start((@CData.Instance.getWorkingDirectory() + "\\DBClassCodeUtility.txt"));
        
        // wait for start process 
        while(!process.Responding)
        {      
          count++;        
        }
      }
      catch(IOException ioex)
      {
        MessageBox.Show(ioex.StackTrace + " : \r\n\r\n"  + ioex.Message);
      }
      catch(Exception ex)
      {
        MessageBox.Show(ex.StackTrace + " : \r\n\r\n"  + ex.Message);
        MessageBox.Show(ex.StackTrace + " : \r\n\r\n"  + ex.GetType().ToString());
      }
      //if(process.Exist)process.Kill();   
      #endregion
      buttonCheckInfo.Enabled = true;
    }

  
    private void button_wd_Click(object sender, System.EventArgs e)
    {
      Settings setting = new Settings();
      setting.ShowDialog();
      textBoxDir.Text = CData.Instance.getWorkingDirectory();
      labelWDPath.Text = CData.Instance.getWorkingDirectory();
    }

    private void checkBoxGroup_CheckedChanged(object sender, System.EventArgs e)
    {
      if (ListCPPClasses.SelectedIndices.Count != 0 &&  checkBox1.Checked || checkBox2.Checked ||
        checkBox3.Checked || checkBox4.Checked || checkBox5.Checked)
      {
        buttonCheck.Enabled = true;
        labelProcessBar.Text = "Status: Ready" + " \n\r";
      }
      else
      {
        buttonCheck.Enabled = false;
        labelProcessBar.Text = "Status: Make your selection" + " \n\r";
      }

      button1.BackColor = Color.RosyBrown;
      button2.BackColor = Color.RosyBrown;
      button3.BackColor = Color.RosyBrown;
      button4.BackColor = Color.RosyBrown;
      button5.BackColor = Color.RosyBrown;
    }

    private void MainForm_Closing(object sender, System.ComponentModel.CancelEventArgs e)
    {
      if (backgroundWorkerCheck.IsBusy)
        backgroundWorkerCheck.CancelAsync();

      if (backgroundWorkerGen.IsBusy)
        backgroundWorkerGen.CancelAsync();
    }

    private void textBoxPassword_KeyDown(object sender, System.Windows.Forms.KeyEventArgs e)
    {
      // If the ENTER key is pressed, make a connect,
      if ( e.KeyValue == 13 )
      {
        buttonConnect.PerformClick(); 
      }
    }

    private void buttonGenXmlFile_Click(object sender, System.EventArgs e)
    {
      string FileName = CData.Instance.getWorkingDirectory() + "\\DB_TABLE.xml";
      
      try
      {
        System.Diagnostics.Process process = System.Diagnostics.Process.Start(@FileName); 
      }
      catch (Exception ex)
      {
        MessageBox.Show(ex.StackTrace + " : \r\n\r\n"  + ex.Message,
          "Exception for " + FileName, MessageBoxButtons.OK, MessageBoxIcon.Error);  
      }
    }

    private void buttonGenSelectAll_Click(object sender, System.EventArgs e)
    {
      if (checkBoxWDFiles.Checked)
      {
        ListCPPClasses.ClearSelected();
        ArrayList files = CData.Instance.getTablesInPath(true);

        if (files.Count.Equals(0))
        {
          MessageBox.Show("no file in this context",
            "Please note: ", MessageBoxButtons.OK, MessageBoxIcon.None);
 
          checkBoxWDFiles.Checked = false;          
        }
        else
        {
          int index = -1;
          for ( int ii = 0 ; ii < files.Count; ii++)
          {   
            index = ListCPPClasses.Items.IndexOf(files[ii].ToString());

            if( index != -1 )
            {
              ListCPPClasses.SetSelected(index,true);
            }
          }        
        }
      }  
      else
      {
        // Loop through and select items to the ListBox.
        for (int x = 0; x <= ListCPPClasses.Items.Count-1; x++)
        {
          ListCPPClasses.SetSelected(x,true);
        } 
      }
    }
   
    private void ListB_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
    {      
      // Update the mouse path with the mouse information
      Point mouseDownLocation = new Point(e.X, e.Y);

      switch (e.Button) 
      {
        case MouseButtons.Right:
        {       
          int TableIndex = ListCPPClasses.IndexFromPoint(mouseDownLocation);

          if ( TableIndex >= 0 && TableIndex <= ListCPPClasses.Items.Count)
          {            
            ListCPPClasses.SelectedIndex = TableIndex;
          }          
          break;
        }
        default:
          break;
      }      
    }

    private void menuItemCompareData_Click(object sender, EventArgs e)
    {
      string CurrentDirectory = System.Environment.CurrentDirectory;
      string TableName = ListCPPClasses.SelectedItem.ToString();
      string Service = tabControlConnections.SelectedTab.Text;
      string tabPageIndex = tabControlConnections.SelectedIndex.ToString();

      if (loadTable(TableName, Service, tabPageIndex, true) )
      {
        CompareDescriptionDataSet = new DataSet("CompareDescription");

        CompareDescriptionDataSet = TableDescriptionDataSet;

        string expression;
        expression = "PK like '%PK%'";

        // Use the Select method to find all rows matching the filter.
        DataRow[] foundRows = CompareDescriptionDataSet.Tables[TableName].Select(expression);

        expression = "";

        // Print column 0 of each returned row.
        for (int i = 0; i < foundRows.Length; i++)
        { 
          if (i > 0 )
          {
            expression += ", ";
          }
          expression += foundRows[i][0] + " ASC";
        }

        if (menuItemCompareData.Text == "Compare Data with")
        {
          XMLDirCompare1 = CurrentDirectory + "\\Compare1" + Service + ".xml";

          DataView view = CompareDescriptionDataSet.Tables[TableName + "DATA"].DefaultView;

          view.Sort = expression;
          view.ToTable().WriteXml(@XMLDirCompare1);
          
          System.Diagnostics.Process.Start("C:\\Program Files\\WinMerge\\WinMergeU.exe", XMLDirCompare1 + " " + XMLDirCompare2);
          menuItemCompareData.Text = "Compare Data";
        }
        else
        {
          XMLDirCompare2 = CurrentDirectory + "\\Compare2" + Service + ".xml";

          DataView view = CompareDescriptionDataSet.Tables[TableName + "DATA"].DefaultView;

          view.Sort = expression;
          view.ToTable().WriteXml(@XMLDirCompare2);

          menuItemCompareData.Text = "Compare Data with";
        }    
      }     
    }

    private void menuItemOpenFile_Click(object sender, System.EventArgs e)
    {
      string TableName = ListCPPClasses.SelectedItem.ToString();
      string FileName = CData.Instance.getWorkingDirectory() + "\\C" + TableName + ".cpp";
      
      try
      {
        if ( File.Exists(FileName) )
        {
          System.Diagnostics.Process process = System.Diagnostics.Process.Start(@FileName);   
        }
        else
        {
          MessageBox.Show(TableName + " has no file in this context !",
            "File does not exists", MessageBoxButtons.OK, MessageBoxIcon.Warning);      
        }
      }
      catch (Exception ex)
      {
        MessageBox.Show(ex.StackTrace + " : \r\n\r\n"  + ex.Message,
          "Exception for " + TableName, MessageBoxButtons.OK, MessageBoxIcon.Error);  
      }
    }

    private void menuItemUpdate_Click(object sender, System.EventArgs e)
    {
      if (ListCPPClasses != null)
      {
        TableDescriptionDataSet.Tables.Clear();

        ListCPPClasses.SetSelected(ListCPPClasses.SelectedIndex, true);
      }
    }

    private void checkBoxWDFiles_CheckedChanged(object sender, System.EventArgs e)
    {
      if (((CheckBox)sender).Checked)
      {
        buttonGenSelectAll.Text = "Select WD files";
      }
      else      
      buttonGenSelectAll.Text = "Select all";
    }

    private void backgroundWorkerCheck_DoWork(object sender, DoWorkEventArgs e)
    {
      try
      {
        //if (InvokeRequired)
        //{
        //  // Using the InvokeRequired property of the control.
        //  this.Invoke(new System.ComponentModel.DoWorkEventHandler(backgroundWorkerCheck_DoWork), new object[] { sender, e });
        //  return;
        //}

        count = 0;
        notExisting = 0;

        sActInfo local = (sActInfo)e.Argument;

        string Service         = local.Service;
        string tabPageIndex    = local.tabPageIndex;
        int selectedItemsCount = local.selectedItemsCount;
 
        if (!flagArr.Contains(4))
          methodSummary += "--------------------------------------------------------------------" + "\n\r\n\r";

        if (flagArr.Contains(4))
        {
          //SearchForTables();

          string sFileName = null;
          int classCount = 0;
          int classNotExisting = 0;

          ArrayList files = CData.Instance.getTablesInPath(true);

          methodSummary += "--------------------------------------------------------------------" + "\n\r\n\r";
          methodSummary += "These files have no table: \n\r\n\r";

          for (int ii = 0; ii < files.Count; ii++)
          {
            //sFileName = files[ii.].Name.Substring(1);

            sFileName = files[ii].ToString();

            if (!ListCPPClasses.Items.Contains(sFileName))
            {
              classNotExisting++;
              methodSummary += "\t " + sFileName + ".cpp/h \n\r\n\r";
              button5.BackColor = Color.MediumSeaGreen;

              int progress = ((ii+1) * 100 / files.Count);
              backgroundWorkerCheck.ReportProgress(progress);
            }
            else
            {
              classCount++;
              //methodSummary += sFileName + "\t\t\t YES (table) \n\r\n\r";
            }
          }// for ( int ai = 0 ; ai < fileInfo.Length; ai++)
          methodSummary += "--------------------------------------------------------------------" + "\n\r\n\r";

          methodSummary = methodSummary.Insert(0, ((classCount + classNotExisting) + " files have been inspected \n\r\n\r"
            + (classCount) + " files exist as table \n\r\n\r"
            + classNotExisting + " files have no table \n\r\n\r"));

          sReportText = "Status: Finished" + " \n\r" +
            (classNotExisting + classCount) + " file(s) are/were monitored and of these " + classNotExisting + " not existing as table";

          //for enabling the info button 
          count = classCount;
          notExisting = classNotExisting;
        }// if(flagArr.Contains(4))


        if (flagArr.Contains(0) || flagArr.Contains(1) || flagArr.Contains(2) || flagArr.Contains(3))
        {
          count = 0;
          notExisting = 0;

          for (int i = 0; i <= selectedItemsCount - 1; i++)
          {
            // following user abort
            if (backgroundWorkerCheck.CancellationPending)
            {
              if (count != 0)
              {
                if (flagArr.Contains(0))
                {
                  methodSummary = methodSummary.Insert(0,
                    (ListCPPClasses.SelectedItems.Count + " tables have been inspected \n\r\n\r"
                    + (ListCPPClasses.SelectedItems.Count - notExisting) + " tables exist as a class in the current directory \n\r\n\r"
                    + notExisting.ToString() + " tables are not in the current directory \n\r\n\r"));
                }
              }// if (count != 0)

              break;
            }

            string TableName = ListCPPClasses.SelectedItems[i].ToString();
            string PathName = CData.Instance.getWorkingDirectory() + "\\C" + TableName;

            if (flagArr.Contains(0))
            {
              SearchForClasses(TableName);
            }// if(flagArr.Contains(0))

            if (flagArr.Contains(1) || flagArr.Contains(2) || flagArr.Contains(3))
            {
              if ((File.Exists(PathName + ".h")) && (File.Exists(PathName + ".cpp")))
              {
                count++;

                if (!TableDescriptionDataSet.Tables.Contains(TableName))
                {
                  loadTable(TableName, Service, tabPageIndex, false);
                }

                CCodePreprocessor preProc = new CCodePreprocessor(TableDescriptionDataSet.Tables[TableName], PathName, true, "");

                if (flagArr.Contains(1))
                {
                  // Are there table columns without get / set method

                  // missing
                  foreach (XmlNode methods in CData.Instance.getGeneratedMethodsToMerge((int)CData.MethodType.MISSING))
                  {
                    button2.BackColor = Color.MediumSeaGreen;

                    methodSummary += "In Class C" + ListCPPClasses.SelectedItems[i].ToString() + "\n\r\n\r";
                    methodSummary += "\n\r";

                    methodSummary += " are missing these get/set methods from the table \n\r\n\r";
                    methodSummary += "\n\r";
                    methodSummary += methods.Attributes.GetNamedItem("NAME").InnerText + "\n\r\n\r";
                  }
                }

                if (flagArr.Contains(2) || flagArr.Contains(3))
                {
                  XmlNodeList personalMethods, missingMethods;
                  personalMethods = CData.Instance.getPersonalMethods();
                  missingMethods = CData.Instance.getGeneratedMethodsToMerge((int)CData.MethodType.OLD);

                  int PMcount = personalMethods.Count;
                  int MMcount = missingMethods.Count;

                  //missingMethods.Item(MMcount).AppendChild(missingMethods.Item(0));

                  if (!missingMethods.Count.Equals(0))
                  {
                    string methode = null;
                    if (flagArr.Contains(2)) methode = "get/set";
                    if (flagArr.Contains(3)) methode = "select";
                    if (flagArr.Contains(3) && flagArr.Contains(2)) methode = "select/get/set";

                    foreach (XmlNode methods in missingMethods)
                    {
                      if (methods.Attributes.GetNamedItem("NAME").InnerText.Equals("select") && flagArr.Contains(3))
                      {
                        button4.BackColor = Color.MediumSeaGreen;
                        methodSummary += "\t -----------------------------------------------------------------\n\r\n\r ";
                        methodSummary += "\t The following " + methode + " are different to the generated class " + methods.Attributes.GetNamedItem("CLASS").InnerText + "\n\r\n\r";
                        methodSummary += "\n\r";

                        //search the String !noTableColumn for extra information
                        if (methods.Attributes.GetNamedItem("COLUMNEXISTS").InnerText.Equals("NO"))
                        {
                          string MethodSigManual = "";
                          string MethodSigDataBase = "";
                          if (methods.Attributes.GetNamedItem("LINESAVE").InnerText.Equals("YES"))
                          {
                            MethodSigManual = "\t " + methods.Attributes.GetNamedItem("SIGNATURE").InnerText;
                            if (methods.ChildNodes.Count > 0)
                            {
                              for (int arg = 0; arg < methods.ChildNodes.Count; arg++)//if more as on argument
                              {
                                MethodSigDataBase += "\t" + methods.ChildNodes[arg].Attributes["ARG_TYPE"].InnerText + " ";
                                MethodSigDataBase += methods.ChildNodes[arg].Attributes["NAME"].InnerText;
                                if (arg < methods.ChildNodes.Count - 1)
                                  MethodSigDataBase += ", ";
                              }
                              MethodSigDataBase += ")";

                              methodSummary += "\t Manual or Old select method is different to the select method in DataBase \r\n";
                              methodSummary += "\t Manu/Old " + MethodSigManual + "\r\n";
                              methodSummary += "\t DataBase " + MethodSigDataBase + "\r\n";
                            }
                            else if (methods.ChildNodes.Count == 0)
                            {
                              methodSummary += "\t Manual or Old select method is found \r\n";
                              methodSummary += "\t Manu/Old " + MethodSigManual + "\r\n";
                              methodSummary += "\t column has no PK !!!! \r\n";
                            }
                          }
                        } // if( methods.Attributes.GetNamedItem("COLUMNEXISTS").InnerText.Equals("NO") ) 
                        else
                        {
                          methodSummary += "\t " + methods.Attributes.GetNamedItem("NAME").InnerText + "\n\r\n\r";

                          //search the String !body for extra information
                          if (methods.Attributes.GetNamedItem("BODYIDENTICAL").InnerText.Equals("NO"))
                          {
                            methodSummary += "\t The method body has a different content in comparison to the generated class \n\r\n\r ";
                          }
                        }

                        methodSummary += "\t -----------------------------------------------------------------\n\r\n\r ";
                      }// if(((ArrayList)missingMethods[index+1]).Contains("select") && flagArr.Contains(3))

                      if (methods.Attributes.GetNamedItem("NAME").InnerText.Equals("select") && flagArr.Contains(2))
                      {
                        button3.BackColor = Color.MediumSeaGreen;

                        methodSummary += "\t -----------------------------------------------------------------\n\r\n\r ";

                        methodSummary += "The following " + methode + " are different to the generated class \n\r\n\r";
                        methodSummary += "\n\r";

                        methodSummary += "\t " + methods.Attributes.GetNamedItem("NAME").InnerText + "\n\r\n\r";

                        //search the String !noTableColumn for extra information
                        if (methods.Attributes.GetNamedItem("COLUMNEXISTS").InnerText.Equals("NO"))
                        {
                          methodSummary += "\t The method has no table column \n\r\n\r";
                        }
                        else
                        {
                          methodSummary += "\t The signature of this method is different. \n\r\n\r";
                        }

                        //search the String !body for extra information
                        if (methods.Attributes.GetNamedItem("BODYIDENTICAL").InnerText.Equals("NO"))
                        {
                          string body = methods.Attributes.GetNamedItem("BODY").InnerText.ToString();
                          body = body.Replace("\n", "");
                          body = body.Replace("\t", "");
                          body = body.Replace("\r", "");
                          methodSummary += "\t The method body has a different content in comparison to the generated class " + methods.Attributes.GetNamedItem("CLASS").InnerText + "\n\r\n\r";
                        }
                        methodSummary += "\t -----------------------------------------------------------------\n\r\n\r ";
                      }
                    }// for
                  }//if(!missingMethods.Count.Equals(0))
                }// if(flagArr.Contains(2)

              }// if( (File.Exists(PathName + ".h")) && (File.Exists(PathName + ".cpp")) )
              else
              {
                notExisting++;
                continue;
              }
            }

            if (flagArr.Contains(0) || flagArr.Contains(1) || flagArr.Contains(2) || flagArr.Contains(3))
            {
              sReportText = "Status: At work" + " \n\r" +
                "From " + (selectedItemsCount) + " table(s) are/were monitored " + (count + notExisting);
            }

            int progress = ((i+1) * 100 / selectedItemsCount);
            backgroundWorkerCheck.ReportProgress(progress);

          }//  for(int i = 0; i<=ListCPPClasses.SelectedItems.Count-1; i++)
        }// if(flagArr.Contains(0) || flagArr.Contains(1)|| flagArr.Contains(2) || flagArr.Contains(3))

        if ((count + notExisting) != 0)
        {
          if (flagArr.Contains(0))
          {
            methodSummary = methodSummary.Insert(0, (selectedItemsCount + " tables have been inspected \n\r\n\r"
              + (selectedItemsCount - notExisting) + " tables exist as a class in the current directory \n\r\n\r"
              + notExisting.ToString() + " tables are not in the current directory \n\r\n\r"));
          }
        }

        if (flagArr.Contains(0) || flagArr.Contains(1) || flagArr.Contains(2) || flagArr.Contains(3))
        {
          sReportText = "Status: Finished" + " \n\r" +
            "From " + (selectedItemsCount) + " table(s) are/were monitored " + (count + notExisting) + " \n\r"
            + (selectedItemsCount - notExisting) + " tables exist in the current directory";
        }
      }
      catch (ArgumentOutOfRangeException aore)
      {
        MessageBox.Show(aore.StackTrace
          + " State: " + backgroundWorkerCheck.WorkerReportsProgress.ToString()
          + " Error: " + aore.Message,
          "Exception" + aore.InnerException, MessageBoxButtons.OK, MessageBoxIcon.Error);
      }
      catch (Exception ex)
      {
        MessageBox.Show(ex.StackTrace
          + " State: " + backgroundWorkerCheck.WorkerReportsProgress.ToString()
          + " Error: " + ex.Message,
          "Exception" + ex.InnerException, MessageBoxButtons.OK, MessageBoxIcon.Error);
      }
    }

    private void backgroundWorkerCheck_ProgressChanged(object sender, ProgressChangedEventArgs e)
    {
      progressBarCheck.Value = e.ProgressPercentage;

      labelProcessBar.Text = sReportText;
    }

    private void backgroundWorkerCheck_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
    {
      if ((count + notExisting) != 0)
      {
        buttonCheckInfo.Enabled = true;
      } //if((count+notExisting) != 0)
      else
      {
        buttonCheckInfo.Enabled = false;
      }

      labelProcessBar.Text = sReportText;

      buttonCheck.Enabled = true;
      buttonCheckCancel.Enabled = false;
    }

    private void backgroundWorkerGen_DoWork(object sender, DoWorkEventArgs e)
    {
      try
      {
        //if (InvokeRequired)
        //{
        //  // Using the InvokeRequired property of the control.
        //  this.Invoke(new System.ComponentModel.DoWorkEventHandler(backgroundWorkerGen_DoWork), new object[] { sender, e });
        //  return;
        //}

        sActInfo local = (sActInfo)e.Argument;

        string Service         = local.Service;
        string tabPageIndex    = local.tabPageIndex;
        int selectedItemsCount = local.selectedItemsCount;

        string workingDirectory = CData.Instance.getWorkingDirectory();

        bool IsAutomatic = false;

        if (radioButton_GEN_CLASS.Checked == true)
        {
          DialogResult result = MessageBox.Show("Merge and checkout files automatically ?",
                                               "Question", MessageBoxButtons.YesNo, MessageBoxIcon.Question);

          if (result == DialogResult.Yes)
          {
            IsAutomatic = true;
            CData.Instance.WriteSetting("UserSettings", "ManualMethodAutomaticGeneration", "yes");
          }
          else
          {
            CData.Instance.WriteSetting("UserSettings", "ManualMethodAutomaticGeneration", "no");
          }
        }

        DateTime StartZeit = DateTime.Now;

        if (workingDirectory != null)
        {
          System.Environment.CurrentDirectory = workingDirectory;

          DialogResult dr = DialogResult.OK;

          for (int i = 0; i <= selectedItemsCount - 1; i++)
          {
            string TableName = ListCPPClasses.SelectedItems[i].ToString();
            string Filename = workingDirectory + "\\C" + TableName;

            if (radioButton_GEN_DEF.Checked == true)
            {
              if (loadTable(TableName, Service, tabPageIndex, true))
              {
                // save table content for def generation
                CData.Instance.setTableContent(TableDescriptionDataSet.Tables[TableName + "DATA"]);
              }
              else
              {
                throw new NullReferenceException("Main::GenClassList: can not load table " + TableName);
              }

              #region DB_COMMENTS
              ArrayList comments = new ArrayList();

              CData.Instance.setComments(comments);
              #endregion

              DefBox frm = new DefBox(TableDescriptionDataSet.Tables[TableName], Filename);
              dr = frm.ShowDialog();

              sGenReport = TableName + " \r\n";

            } // if(radioButton_GEN_DEF.Checked == true )
            else if (radioButton_GEN_CLASS.Checked == true)
            {

              if (!loadTable(TableName, Service, tabPageIndex, false))
              {
                throw new NullReferenceException("Main::GenClassList: can not load table " + TableName);
              }

              string sTableComment = getTableComment(TableName, Service, tabPageIndex);

              CCodePreprocessor preProc = new CCodePreprocessor(TableDescriptionDataSet.Tables[TableName], Filename, IsDBTable, sTableComment);
              // Check the Table, if it exist and if there is a difference.If yes show it

              // add personal methods + insert and delete generated methods + merge different body content
              if (preProc.getFileExists() && CData.Instance.getNewXmlDocument() != null && !CData.Instance.getPersonalMethods().Count.Equals(0))
              {
                sGenReport = TableName + " merge/different \r\n";

                if (IsAutomatic)
                {
                  XmlDocument newDoc             = CData.Instance.getNewXmlDocument();
                  XmlElement  root               = newDoc.DocumentElement;
                  XmlNodeList PersonalMethodList = root.SelectNodes("/class/METHOD[@GENERATEDBY='MANUAL']");

                  foreach (XmlNode methods in PersonalMethodList)
                  {
                    methods.Attributes.GetNamedItem("GENERATE").InnerText = "YES"; 
                  }

                  #region ShowNewXmlFile
                  StreamWriter xr = File.CreateText("DB_TABLE.xml");
                  xr.WriteLine(newDoc.InnerXml);
                  xr.Close();
                  #endregion

                  CCodeWriter writer = new CCodeWriter();
                  writer.writeCode(TableName, newDoc);
                }
                else
                {
                  Checkbox frm = new Checkbox(TableName, Filename, CData.Instance.getMethodSummary());
                  dr = frm.ShowDialog();
                }
              }
              // insert and delete generated methods or merge different body content
              else if (preProc.getFileExists() && (CData.Instance.getNewXmlDocument() != null && !CData.Instance.getGeneratedMethodsToMerge((int)CData.MethodType.BOTH).Count.Equals(0)
                || !CData.Instance.getDifferentGeneratedMethods().Count.Equals(0)))
              {
                sGenReport = TableName + " is different \r\n";

                CCodeWriter writer = new CCodeWriter();
                writer.writeCode(TableName, CData.Instance.getNewXmlDocument());
              }
              // file not exits, make new file   
              else if (!preProc.getFileExists())
              {
                sGenReport = TableName + " is new \r\n";

                // set working dir for reset
                CData.Instance.resetTablesInPath();

                CCodeWriter writer = new CCodeWriter();
                writer.writeCode(TableName, CData.Instance.getXmlDocument());
              }
              else
              {
                sGenReport = TableName + " is identical \r\n";
              }
            }// else if( radioButton_GEN_CLASS.Checked == true )

            //if (dr == DialogResult.OK)
            //{
            //  MessageBox.Show("Generation complete",
            //    "INFO", MessageBoxButtons.OK, MessageBoxIcon.Information);
            //}
            if (dr == DialogResult.Abort)
            {
              MessageBox.Show("Generation aborted",
                "INFO", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);

              break;
            }
            else if (dr == DialogResult.Cancel)
            {
              MessageBox.Show("Generation canceled",
                "INFO", MessageBoxButtons.OK, MessageBoxIcon.Information);

              break;
            }

            int progress = ((i + 1) * 100 / selectedItemsCount);
            backgroundWorkerGen.ReportProgress(progress);

            sReportText = "Please Wait ... \r\n";
            sReportText += "Status: At work : " + progress + "% \n\r"
              + (i + 1) + " of " + (selectedItemsCount) + " table(s) are/were proceeded  \r\n";
         
            count = i + 1;

            //following user abort
            if (backgroundWorkerGen.CancellationPending)
            {
              break;
            }
          }// for(int i = 0; i<=selectedItemsCount-1 ; i++)

        }// if( data.getWorkingDirectory() != null )
        else MessageBox.Show("Please specify the path in the menu \"Edit/Settings\" ");


        DateTime EndZeit = DateTime.Now;
        TimeSpan totalTimeSpan = (EndZeit - StartZeit);

        string sTotalTime = totalTimeSpan.Hours.ToString().PadLeft(2, '0') + ":" + totalTimeSpan.Minutes.ToString().PadLeft(2, '0') + ":" + totalTimeSpan.Seconds.ToString().PadLeft(2, '0');

        sReportText = "Status: Finished " + sTotalTime + " hh:mm:ss \n\r" + (count) + " table(s) is/are proceeded \n\r";
      }
      catch (ArgumentOutOfRangeException aore)
      {
        MessageBox.Show(aore.StackTrace
          + " State: " + backgroundWorkerGen.WorkerReportsProgress.ToString()
          + " Error: " + aore.Message,
          "Exception" + aore.InnerException, MessageBoxButtons.OK, MessageBoxIcon.Error);
      }
      catch (Exception ex)
      {
        MessageBox.Show(ex.StackTrace
          + " State: " + backgroundWorkerGen.WorkerReportsProgress.ToString()
          + " Error: " + ex.Message,
          "Exception" + ex.InnerException, MessageBoxButtons.OK, MessageBoxIcon.Error);
      }
    }

    private void backgroundWorkerGen_ProgressChanged(object sender, ProgressChangedEventArgs e)
    {
      progressBarGen.Value = e.ProgressPercentage;

      int itemsPerPage = (int)(listBoxGenReportOut.Height / listBoxGenReportOut.ItemHeight);
      listBoxGenReportOut.TopIndex = listBoxGenReportOut.Items.Count - itemsPerPage;

      listBoxGenReportOut.Items.Add(sGenReport);
      labelGenReportOut.Text = sReportText;
    }

    private void backgroundWorkerGen_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
    {
      labelGenReportOut.Text = sReportText;

      buttonGenXmlFile.Enabled = true;
      buttonGenerate.Enabled = true;
      buttonGenCancle.Enabled = false;
      buttonGenSelectAll.Enabled = true;
    }

    private void menuItemClassCodeUtility_Click(object sender, EventArgs e)
    {
      ArrayList files = CData.Instance.getTablesInPath(false);

      if (files.Count != 0)
      {
        menuItemClassCodeUtility.Checked = true;
        menuItemDBClassCodeUtility.Checked = false;
        IsDBTable = false;

        ListCPPClasses = null;

        while (tabControlConnections.Controls.Count > 0)
        {
          string ConnectionToClose = tabControlConnections.SelectedTab.Text;
          Connections.closeConnection(ConnectionToClose, tabControlConnections.SelectedTab.Tag.ToString());
          tabControlConnections.Controls.Remove(tabControlConnections.SelectedTab);

          if (tabControlConnections.Controls.Count == 0)
          {
            GridTableDetails.DataSource = null;
            GridTableDetails.CaptionText = "";
            GridTableDetails.Visible = false;
            menuItemClose.Enabled = false;
            menuItemUpdate.Enabled = false;
            tabControlTable.Visible = false;
          }

          if (tabControlConnections.TabCount == 0)
          {
            panelCheck.Visible = false;
          }

          Cursor = Cursors.Default;
        }

        ListCPPClasses = new ListBox();

        ListCPPClasses.SelectedIndexChanged += new System.EventHandler(this.tableSelect);
        ListCPPClasses.MouseDown += new System.Windows.Forms.MouseEventHandler(this.ListB_MouseDown);
        ListCPPClasses.ContextMenu = this.contextMenuListB;

        ListCPPClasses.HorizontalScrollbar = true;
        //ListCPPClasses.ItemHeight = 80;
        ListCPPClasses.Dock = DockStyle.Fill;

        foreach (string file in files)
        {
          ListCPPClasses.Items.Add(file);
        }

        loadToTabControl(ListCPPClasses, "WD FILES", "CPP FILES");

        menuItemOpen.Enabled = false;
        panelConnection.Visible = false;

        tabControlTable.Controls.Clear();

        this.tabControlTable.Controls.Add(this.tabPage_Generated);

        tabControlTable.Visible = true;

        ListCPPClasses.SetSelected(0, true);

        ListCPPClasses.SelectionMode = SelectionMode.MultiExtended;

        if (backgroundWorkerGen.IsBusy)
          backgroundWorkerGen.CancelAsync();

        progressBarGen.Value = 0;
      }
      else
      {
        MessageBox.Show("Invalid path! note: use Settings menu for browse to other path",
          "No CPP files found", MessageBoxButtons.OK, MessageBoxIcon.Error);
      }
    }

    private void menuItemDBClassCodeUtility_Click(object sender, EventArgs e)
    {
      menuItemClassCodeUtility.Checked = false;
      menuItemDBClassCodeUtility.Checked = true;
      IsDBTable = true;

      ListCPPClasses = null;

      while (tabControlConnections.Controls.Count > 0)
      {
        string ConnectionToClose = tabControlConnections.SelectedTab.Text;
        Connections.closeConnection(ConnectionToClose, tabControlConnections.SelectedTab.Tag.ToString());
        tabControlConnections.Controls.Remove(tabControlConnections.SelectedTab);

        if (tabControlConnections.Controls.Count == 0)
        {
          GridTableDetails.DataSource = null;
          GridTableDetails.CaptionText = "";
          GridTableDetails.Visible = false;
          menuItemClose.Enabled = false;
          menuItemUpdate.Enabled = false;
          tabControlTable.Visible = false;
        }

        if (tabControlConnections.TabCount == 0)
        {
          panelCheck.Visible = false;
        }

        Cursor = Cursors.Default;
      }

      menuItemOpen.Enabled = true;
      panelConnection.Visible = true;

      tabControlTable.Controls.Clear();

      this.tabControlTable.Controls.Add(this.tabPageDetails);
      this.tabControlTable.Controls.Add(this.tabPageData);
      this.tabControlTable.Controls.Add(this.tabPage_Check);
      this.tabControlTable.Controls.Add(this.tabPage_Generated);
    }

    private void MainForm_FormClosed(object sender, FormClosedEventArgs e)
    {
      string CurrentDirectory = System.Environment.CurrentDirectory;
      //find files in the current directory an delete them
      foreach (string fileName in System.IO.Directory.GetFiles(CurrentDirectory))
      {
        try
        {
          if (fileName.EndsWith(".xml"))
          {
            System.IO.File.Delete(fileName);
          }
        }
        catch
        {
          //Some files produce an exception if they cannot be deleted
          //throw Exception ex; 
        }
      }


    }
  }// public class MainForm
}// namespace DBClassCodeUtility
