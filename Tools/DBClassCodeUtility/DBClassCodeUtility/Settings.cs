using System;
using System.Collections;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;

namespace DBClassCodeUtility
{
  /// <summary>
  /// Summary description for Settings.
  /// </summary>
  public class Settings : System.Windows.Forms.Form
  {
    private System.Windows.Forms.Button button_FindDir;
    private System.Windows.Forms.TextBox textBox_path;
    private System.Windows.Forms.Label labelWorkingDir;
    private System.Windows.Forms.Button buttonOK;
    private Button buttonCancel;
    private TreeView treeViewSettings;
    private TabControl tabControl;
    private TabPage tabPageGeneral;
    private Label labelTapGeneral;
    private TabPage tabPageSortControl;
    private Label labelTapSortControl;
    private CheckBox checkBoxSortControllManualMethodSort;
    private GroupBox groupBoxFilter;
    private CheckBox checkBoxDisableUserWildCard;
    protected TextBox textBoxDescription;
    private Label labelTapGeneralVersion;
    private TabPage tabPageGenerate;
    private Label labelGenerate;
    private Label labelGen;
    private Label labelRuleSet;
    private ListBox listBoxRuleSet;
    private ContextMenuStrip contextMenuRuleSet;
    private ToolStripMenuItem newToolStripMenuItem;
    private ToolStripMenuItem deleteToolStripMenuItem;
    private ToolStripMenuItem moveToolStripMenuItem;
    private ToolStripMenuItem upToolStripMenuItem;
    private ToolStripMenuItem downToolStripMenuItem;
    private TextBox textBoxNewRuleSetValue;
    private Button buttonAdd;
    private IContainer components;
    private TabPage tabPageReleaseNotes;
    private RichTextBox richTextBoxReleaseNotes;
    private string sTextBoxNewRuleSetValue;

    public Settings()
    {
      //
      // Required for Windows Form Designer support
      //
      InitializeComponent();

      sTextBoxNewRuleSetValue = "Enter RuleSet Value";

      if (!CData.Instance.ReadSetting("UserSettings", "WorkingDirectory").Equals(""))
      {
        CData.Instance.setWorkingDirectory(CData.Instance.ReadSetting("UserSettings", "WorkingDirectory"));
      }
      //listBoxRuleSet.ContextMenuStrip = this.contextMenuRuleSet;
      labelTapGeneralVersion.Text = "Version " + CData.Instance.getVersionOfDBClassCodeUtility();    
      treeViewSettings.ExpandAll();
      treeViewSettings.SelectedNode = this.treeViewSettings.Nodes[0].Nodes[0];
      treeViewSettings.SelectedNode.Checked = true;
      //
      // TODO: Add any constructor code after InitializeComponent call
      //
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
      this.components = new System.ComponentModel.Container();
      System.Windows.Forms.TreeNode treeNode1 = new System.Windows.Forms.TreeNode("General");
      System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("SortControl");
      System.Windows.Forms.TreeNode treeNode3 = new System.Windows.Forms.TreeNode("Generate", new System.Windows.Forms.TreeNode[] {
            treeNode2});
      System.Windows.Forms.TreeNode treeNode4 = new System.Windows.Forms.TreeNode("ReleaseNotes");
      System.Windows.Forms.TreeNode treeNode5 = new System.Windows.Forms.TreeNode("Environment", new System.Windows.Forms.TreeNode[] {
            treeNode1,
            treeNode3,
            treeNode4});
      System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Settings));
      this.button_FindDir = new System.Windows.Forms.Button();
      this.textBox_path = new System.Windows.Forms.TextBox();
      this.labelWorkingDir = new System.Windows.Forms.Label();
      this.buttonOK = new System.Windows.Forms.Button();
      this.buttonCancel = new System.Windows.Forms.Button();
      this.treeViewSettings = new System.Windows.Forms.TreeView();
      this.tabControl = new System.Windows.Forms.TabControl();
      this.tabPageGeneral = new System.Windows.Forms.TabPage();
      this.labelTapGeneralVersion = new System.Windows.Forms.Label();
      this.groupBoxFilter = new System.Windows.Forms.GroupBox();
      this.checkBoxDisableUserWildCard = new System.Windows.Forms.CheckBox();
      this.labelTapGeneral = new System.Windows.Forms.Label();
      this.tabPageGenerate = new System.Windows.Forms.TabPage();
      this.labelGen = new System.Windows.Forms.Label();
      this.labelGenerate = new System.Windows.Forms.Label();
      this.tabPageSortControl = new System.Windows.Forms.TabPage();
      this.buttonAdd = new System.Windows.Forms.Button();
      this.textBoxNewRuleSetValue = new System.Windows.Forms.TextBox();
      this.contextMenuRuleSet = new System.Windows.Forms.ContextMenuStrip(this.components);
      this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.deleteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.moveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.upToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.downToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.labelRuleSet = new System.Windows.Forms.Label();
      this.listBoxRuleSet = new System.Windows.Forms.ListBox();
      this.checkBoxSortControllManualMethodSort = new System.Windows.Forms.CheckBox();
      this.labelTapSortControl = new System.Windows.Forms.Label();
      this.tabPageReleaseNotes = new System.Windows.Forms.TabPage();
      this.textBoxDescription = new System.Windows.Forms.TextBox();
      this.richTextBoxReleaseNotes = new System.Windows.Forms.RichTextBox();
      this.tabControl.SuspendLayout();
      this.tabPageGeneral.SuspendLayout();
      this.groupBoxFilter.SuspendLayout();
      this.tabPageGenerate.SuspendLayout();
      this.tabPageSortControl.SuspendLayout();
      this.contextMenuRuleSet.SuspendLayout();
      this.tabPageReleaseNotes.SuspendLayout();
      this.SuspendLayout();
      // 
      // button_FindDir
      // 
      this.button_FindDir.Location = new System.Drawing.Point(221, 143);
      this.button_FindDir.Name = "button_FindDir";
      this.button_FindDir.Size = new System.Drawing.Size(65, 20);
      this.button_FindDir.TabIndex = 2;
      this.button_FindDir.Text = "Browse...";
      this.button_FindDir.Click += new System.EventHandler(this.button_FindDir_Click);
      // 
      // textBox_path
      // 
      this.textBox_path.Location = new System.Drawing.Point(7, 143);
      this.textBox_path.Name = "textBox_path";
      this.textBox_path.Size = new System.Drawing.Size(216, 20);
      this.textBox_path.TabIndex = 6;
      this.textBox_path.Text = "Shows the current path";
      this.textBox_path.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBox_path_KeyPress);
      this.textBox_path.MouseHover += new System.EventHandler(this.textBox_path_MouseHover);
      // 
      // labelWorkingDir
      // 
      this.labelWorkingDir.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.labelWorkingDir.Location = new System.Drawing.Point(4, 122);
      this.labelWorkingDir.Name = "labelWorkingDir";
      this.labelWorkingDir.Size = new System.Drawing.Size(219, 18);
      this.labelWorkingDir.TabIndex = 8;
      this.labelWorkingDir.Text = "Working Directory (DB Files)";
      // 
      // buttonOK
      // 
      this.buttonOK.Location = new System.Drawing.Point(273, 190);
      this.buttonOK.Name = "buttonOK";
      this.buttonOK.Size = new System.Drawing.Size(75, 23);
      this.buttonOK.TabIndex = 9;
      this.buttonOK.Text = "Ok";
      this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
      // 
      // buttonCancel
      // 
      this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.buttonCancel.Location = new System.Drawing.Point(354, 190);
      this.buttonCancel.Name = "buttonCancel";
      this.buttonCancel.Size = new System.Drawing.Size(75, 23);
      this.buttonCancel.TabIndex = 10;
      this.buttonCancel.Text = "Cancel";
      this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
      // 
      // treeViewSettings
      // 
      this.treeViewSettings.Location = new System.Drawing.Point(8, 3);
      this.treeViewSettings.Name = "treeViewSettings";
      treeNode1.Checked = true;
      treeNode1.Name = "General";
      treeNode1.Text = "General";
      treeNode2.Name = "SortControl";
      treeNode2.Text = "SortControl";
      treeNode3.Name = "Generate";
      treeNode3.Text = "Generate";
      treeNode4.Name = "ReleaseNotes";
      treeNode4.Text = "ReleaseNotes";
      treeNode5.Name = "Environment";
      treeNode5.Tag = "Env";
      treeNode5.Text = "Environment";
      this.treeViewSettings.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode5});
      this.treeViewSettings.Scrollable = false;
      this.treeViewSettings.Size = new System.Drawing.Size(130, 170);
      this.treeViewSettings.TabIndex = 11;
      this.treeViewSettings.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.treeViewSettings_AfterSelect);
      // 
      // tabControl
      // 
      this.tabControl.Appearance = System.Windows.Forms.TabAppearance.FlatButtons;
      this.tabControl.Controls.Add(this.tabPageGeneral);
      this.tabControl.Controls.Add(this.tabPageGenerate);
      this.tabControl.Controls.Add(this.tabPageSortControl);
      this.tabControl.Controls.Add(this.tabPageReleaseNotes);
      this.tabControl.Location = new System.Drawing.Point(136, -22);
      this.tabControl.Name = "tabControl";
      this.tabControl.SelectedIndex = 0;
      this.tabControl.Size = new System.Drawing.Size(297, 200);
      this.tabControl.SizeMode = System.Windows.Forms.TabSizeMode.FillToRight;
      this.tabControl.TabIndex = 12;
      this.tabControl.SelectedIndexChanged += new System.EventHandler(this.tabControl_SelectedIndexChanged);
      // 
      // tabPageGeneral
      // 
      this.tabPageGeneral.Controls.Add(this.labelTapGeneralVersion);
      this.tabPageGeneral.Controls.Add(this.groupBoxFilter);
      this.tabPageGeneral.Controls.Add(this.labelTapGeneral);
      this.tabPageGeneral.Controls.Add(this.labelWorkingDir);
      this.tabPageGeneral.Controls.Add(this.textBox_path);
      this.tabPageGeneral.Controls.Add(this.button_FindDir);
      this.tabPageGeneral.Location = new System.Drawing.Point(4, 25);
      this.tabPageGeneral.Name = "tabPageGeneral";
      this.tabPageGeneral.Padding = new System.Windows.Forms.Padding(3);
      this.tabPageGeneral.Size = new System.Drawing.Size(289, 171);
      this.tabPageGeneral.TabIndex = 1;
      this.tabPageGeneral.Text = "General";
      this.tabPageGeneral.UseVisualStyleBackColor = true;
      // 
      // labelTapGeneralVersion
      // 
      this.labelTapGeneralVersion.AutoSize = true;
      this.labelTapGeneralVersion.Location = new System.Drawing.Point(4, 31);
      this.labelTapGeneralVersion.Name = "labelTapGeneralVersion";
      this.labelTapGeneralVersion.Size = new System.Drawing.Size(42, 13);
      this.labelTapGeneralVersion.TabIndex = 11;
      this.labelTapGeneralVersion.Text = "Version";
      // 
      // groupBoxFilter
      // 
      this.groupBoxFilter.Controls.Add(this.checkBoxDisableUserWildCard);
      this.groupBoxFilter.ForeColor = System.Drawing.SystemColors.ControlText;
      this.groupBoxFilter.Location = new System.Drawing.Point(7, 59);
      this.groupBoxFilter.Name = "groupBoxFilter";
      this.groupBoxFilter.Size = new System.Drawing.Size(279, 60);
      this.groupBoxFilter.TabIndex = 10;
      this.groupBoxFilter.TabStop = false;
      this.groupBoxFilter.Text = "Filter";
      // 
      // checkBoxDisableUserWildCard
      // 
      this.checkBoxDisableUserWildCard.AutoSize = true;
      this.checkBoxDisableUserWildCard.Location = new System.Drawing.Point(6, 19);
      this.checkBoxDisableUserWildCard.Name = "checkBoxDisableUserWildCard";
      this.checkBoxDisableUserWildCard.Size = new System.Drawing.Size(126, 17);
      this.checkBoxDisableUserWildCard.TabIndex = 9;
      this.checkBoxDisableUserWildCard.Text = "Disable user wildcard";
      this.checkBoxDisableUserWildCard.UseVisualStyleBackColor = true;
      this.checkBoxDisableUserWildCard.CheckedChanged += new System.EventHandler(this.checkBoxIsFilterOn_CheckedChanged);
      this.checkBoxDisableUserWildCard.MouseHover += new System.EventHandler(this.checkBoxIsFilterOn_MouseHover);
      // 
      // labelTapGeneral
      // 
      this.labelTapGeneral.AutoSize = true;
      this.labelTapGeneral.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.labelTapGeneral.Location = new System.Drawing.Point(4, 5);
      this.labelTapGeneral.Name = "labelTapGeneral";
      this.labelTapGeneral.Size = new System.Drawing.Size(59, 17);
      this.labelTapGeneral.TabIndex = 0;
      this.labelTapGeneral.Text = "General";
      // 
      // tabPageGenerate
      // 
      this.tabPageGenerate.Controls.Add(this.labelGen);
      this.tabPageGenerate.Controls.Add(this.labelGenerate);
      this.tabPageGenerate.Location = new System.Drawing.Point(4, 25);
      this.tabPageGenerate.Name = "tabPageGenerate";
      this.tabPageGenerate.Size = new System.Drawing.Size(289, 171);
      this.tabPageGenerate.TabIndex = 3;
      this.tabPageGenerate.Text = "Genrate";
      this.tabPageGenerate.UseVisualStyleBackColor = true;
      // 
      // labelGen
      // 
      this.labelGen.AutoSize = true;
      this.labelGen.Location = new System.Drawing.Point(4, 31);
      this.labelGen.Name = "labelGen";
      this.labelGen.Size = new System.Drawing.Size(86, 13);
      this.labelGen.TabIndex = 2;
      this.labelGen.Text = "Option is actived";
      // 
      // labelGenerate
      // 
      this.labelGenerate.AutoSize = true;
      this.labelGenerate.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.labelGenerate.Location = new System.Drawing.Point(4, 5);
      this.labelGenerate.Name = "labelGenerate";
      this.labelGenerate.Size = new System.Drawing.Size(68, 17);
      this.labelGenerate.TabIndex = 1;
      this.labelGenerate.Text = "Generate";
      // 
      // tabPageSortControl
      // 
      this.tabPageSortControl.Controls.Add(this.buttonAdd);
      this.tabPageSortControl.Controls.Add(this.textBoxNewRuleSetValue);
      this.tabPageSortControl.Controls.Add(this.labelRuleSet);
      this.tabPageSortControl.Controls.Add(this.listBoxRuleSet);
      this.tabPageSortControl.Controls.Add(this.checkBoxSortControllManualMethodSort);
      this.tabPageSortControl.Controls.Add(this.labelTapSortControl);
      this.tabPageSortControl.Location = new System.Drawing.Point(4, 25);
      this.tabPageSortControl.Name = "tabPageSortControl";
      this.tabPageSortControl.Size = new System.Drawing.Size(289, 171);
      this.tabPageSortControl.TabIndex = 2;
      this.tabPageSortControl.Text = "SortControl";
      this.tabPageSortControl.UseVisualStyleBackColor = true;
      // 
      // buttonAdd
      // 
      this.buttonAdd.Enabled = false;
      this.buttonAdd.Location = new System.Drawing.Point(128, 150);
      this.buttonAdd.Name = "buttonAdd";
      this.buttonAdd.Size = new System.Drawing.Size(39, 20);
      this.buttonAdd.TabIndex = 5;
      this.buttonAdd.Text = "Add";
      this.buttonAdd.UseVisualStyleBackColor = true;
      this.buttonAdd.Visible = false;
      this.buttonAdd.Click += new System.EventHandler(this.buttonAdd_Click);
      // 
      // textBoxNewRuleSetValue
      // 
      this.textBoxNewRuleSetValue.ContextMenuStrip = this.contextMenuRuleSet;
      this.textBoxNewRuleSetValue.Location = new System.Drawing.Point(4, 150);
      this.textBoxNewRuleSetValue.MaxLength = 30;
      this.textBoxNewRuleSetValue.Name = "textBoxNewRuleSetValue";
      this.textBoxNewRuleSetValue.Size = new System.Drawing.Size(123, 20);
      this.textBoxNewRuleSetValue.TabIndex = 4;
      this.textBoxNewRuleSetValue.Text = "Enter RuleSet Value";
      this.textBoxNewRuleSetValue.Visible = false;
      this.textBoxNewRuleSetValue.TextChanged += new System.EventHandler(this.textBoxNewRuleSetValue_TextChanged);
      this.textBoxNewRuleSetValue.Click += new System.EventHandler(this.textBoxNewRuleSetValue_Click);
      this.textBoxNewRuleSetValue.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBoxNewRuleSetValue_KeyDown);
      // 
      // contextMenuRuleSet
      // 
      this.contextMenuRuleSet.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.deleteToolStripMenuItem,
            this.moveToolStripMenuItem});
      this.contextMenuRuleSet.Name = "contextMenuRuleSet";
      this.contextMenuRuleSet.Size = new System.Drawing.Size(163, 70);
      this.contextMenuRuleSet.Opening += new System.ComponentModel.CancelEventHandler(this.contextMenuRuleSet_Opening);
      // 
      // newToolStripMenuItem
      // 
      this.newToolStripMenuItem.Name = "newToolStripMenuItem";
      this.newToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
      this.newToolStripMenuItem.Text = "Add RuleSet Value";
      this.newToolStripMenuItem.Click += new System.EventHandler(this.newToolStripMenuItem_Click);
      // 
      // deleteToolStripMenuItem
      // 
      this.deleteToolStripMenuItem.Enabled = false;
      this.deleteToolStripMenuItem.Name = "deleteToolStripMenuItem";
      this.deleteToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
      this.deleteToolStripMenuItem.Text = "Delete";
      this.deleteToolStripMenuItem.Click += new System.EventHandler(this.deleteToolStripMenuItem_Click);
      // 
      // moveToolStripMenuItem
      // 
      this.moveToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.upToolStripMenuItem,
            this.downToolStripMenuItem});
      this.moveToolStripMenuItem.Enabled = false;
      this.moveToolStripMenuItem.Name = "moveToolStripMenuItem";
      this.moveToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
      this.moveToolStripMenuItem.Text = "Move";
      // 
      // upToolStripMenuItem
      // 
      this.upToolStripMenuItem.Name = "upToolStripMenuItem";
      this.upToolStripMenuItem.Size = new System.Drawing.Size(101, 22);
      this.upToolStripMenuItem.Text = "Up";
      this.upToolStripMenuItem.Click += new System.EventHandler(this.upToolStripMenuItem_Click);
      // 
      // downToolStripMenuItem
      // 
      this.downToolStripMenuItem.Name = "downToolStripMenuItem";
      this.downToolStripMenuItem.Size = new System.Drawing.Size(101, 22);
      this.downToolStripMenuItem.Text = "Down";
      this.downToolStripMenuItem.Click += new System.EventHandler(this.downToolStripMenuItem_Click);
      // 
      // labelRuleSet
      // 
      this.labelRuleSet.AutoSize = true;
      this.labelRuleSet.Location = new System.Drawing.Point(1, 59);
      this.labelRuleSet.Name = "labelRuleSet";
      this.labelRuleSet.Size = new System.Drawing.Size(164, 13);
      this.labelRuleSet.TabIndex = 3;
      this.labelRuleSet.Text = "RuleSet (Default: init,select,copy)";
      this.labelRuleSet.Visible = false;
      // 
      // listBoxRuleSet
      // 
      this.listBoxRuleSet.ContextMenuStrip = this.contextMenuRuleSet;
      this.listBoxRuleSet.FormattingEnabled = true;
      this.listBoxRuleSet.Location = new System.Drawing.Point(4, 77);
      this.listBoxRuleSet.MultiColumn = true;
      this.listBoxRuleSet.Name = "listBoxRuleSet";
      this.listBoxRuleSet.Size = new System.Drawing.Size(123, 69);
      this.listBoxRuleSet.TabIndex = 2;
      this.listBoxRuleSet.Visible = false;
      // 
      // checkBoxSortControllManualMethodSort
      // 
      this.checkBoxSortControllManualMethodSort.AutoSize = true;
      this.checkBoxSortControllManualMethodSort.Location = new System.Drawing.Point(4, 31);
      this.checkBoxSortControllManualMethodSort.Name = "checkBoxSortControllManualMethodSort";
      this.checkBoxSortControllManualMethodSort.Size = new System.Drawing.Size(116, 17);
      this.checkBoxSortControllManualMethodSort.TabIndex = 1;
      this.checkBoxSortControllManualMethodSort.Text = "ManualMethodSort";
      this.checkBoxSortControllManualMethodSort.UseVisualStyleBackColor = true;
      this.checkBoxSortControllManualMethodSort.CheckedChanged += new System.EventHandler(this.checkBoxSortControllManualMethodSort_CheckedChanged);
      this.checkBoxSortControllManualMethodSort.MouseHover += new System.EventHandler(this.checkBoxSortControllManualMethodSort_MouseHover);
      // 
      // labelTapSortControl
      // 
      this.labelTapSortControl.AutoSize = true;
      this.labelTapSortControl.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.labelTapSortControl.Location = new System.Drawing.Point(4, 5);
      this.labelTapSortControl.Name = "labelTapSortControl";
      this.labelTapSortControl.Size = new System.Drawing.Size(79, 17);
      this.labelTapSortControl.TabIndex = 0;
      this.labelTapSortControl.Text = "SortControl";
      // 
      // tabPageReleaseNotes
      // 
      this.tabPageReleaseNotes.Controls.Add(this.richTextBoxReleaseNotes);
      this.tabPageReleaseNotes.Location = new System.Drawing.Point(4, 25);
      this.tabPageReleaseNotes.Name = "tabPageReleaseNotes";
      this.tabPageReleaseNotes.Size = new System.Drawing.Size(289, 171);
      this.tabPageReleaseNotes.TabIndex = 4;
      this.tabPageReleaseNotes.Text = "ReleaseNotes";
      this.tabPageReleaseNotes.UseVisualStyleBackColor = true;
      // 
      // textBoxDescription
      // 
      this.textBoxDescription.Location = new System.Drawing.Point(8, 181);
      this.textBoxDescription.Multiline = true;
      this.textBoxDescription.Name = "textBoxDescription";
      this.textBoxDescription.ReadOnly = true;
      this.textBoxDescription.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
      this.textBoxDescription.Size = new System.Drawing.Size(259, 32);
      this.textBoxDescription.TabIndex = 13;
      this.textBoxDescription.Text = "Description";
      // 
      // richTextBoxReleaseNotes
      // 
      this.richTextBoxReleaseNotes.BackColor = System.Drawing.SystemColors.ActiveBorder;
      this.richTextBoxReleaseNotes.Location = new System.Drawing.Point(0, 0);
      this.richTextBoxReleaseNotes.Name = "richTextBoxReleaseNotes";
      this.richTextBoxReleaseNotes.ReadOnly = true;
      this.richTextBoxReleaseNotes.Size = new System.Drawing.Size(289, 170);
      this.richTextBoxReleaseNotes.TabIndex = 0;
      this.richTextBoxReleaseNotes.Text = "";
      // 
      // Settings
      // 
      this.AcceptButton = this.buttonOK;
      this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
      this.CancelButton = this.buttonCancel;
      this.ClientSize = new System.Drawing.Size(435, 218);
      this.Controls.Add(this.textBoxDescription);
      this.Controls.Add(this.tabControl);
      this.Controls.Add(this.treeViewSettings);
      this.Controls.Add(this.buttonCancel);
      this.Controls.Add(this.buttonOK);
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
      this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
      this.Name = "Settings";
      this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
      this.Text = "Settings";
      this.Closing += new System.ComponentModel.CancelEventHandler(this.Settings_Closing);
      this.tabControl.ResumeLayout(false);
      this.tabPageGeneral.ResumeLayout(false);
      this.tabPageGeneral.PerformLayout();
      this.groupBoxFilter.ResumeLayout(false);
      this.groupBoxFilter.PerformLayout();
      this.tabPageGenerate.ResumeLayout(false);
      this.tabPageGenerate.PerformLayout();
      this.tabPageSortControl.ResumeLayout(false);
      this.tabPageSortControl.PerformLayout();
      this.contextMenuRuleSet.ResumeLayout(false);
      this.tabPageReleaseNotes.ResumeLayout(false);
      this.ResumeLayout(false);
      this.PerformLayout();

    }
    #endregion

    private void button_FindDir_Click(object sender, System.EventArgs e)
    {
      string Filename = null;
      // Displays a OpenFolderDialog 
      FolderBrowserDialog openFolderDialog1 = new FolderBrowserDialog();
      string str = "Select a folder to be searched.\n";  
      str += "Confirm your choice 'OK'";
      openFolderDialog1.Description = str;
      openFolderDialog1.SelectedPath = CData.Instance.getWorkingDirectory();

      // If the Path name is not an empty string open it
      if((openFolderDialog1.ShowDialog() == DialogResult.OK) && (openFolderDialog1.SelectedPath != ""))
      {
        Filename = openFolderDialog1.SelectedPath;
        textBox_path.Text = Filename;
        CData.Instance.setWorkingDirectory(Filename);
        CData.Instance.WriteSetting("UserSettings", "WorkingDirectory", CData.Instance.getWorkingDirectory());
      }            

      if (System.IO.Path.IsPathRooted(textBox_path.Text) && System.IO.Directory.Exists(textBox_path.Text))
      {
        CData.Instance.setWorkingDirectory(textBox_path.Text);
        CData.Instance.WriteSetting("UserSettings", "WorkingDirectory", CData.Instance.getWorkingDirectory());
      }
      else
      {
        MessageBox.Show("Invalid path! note: use FindDir",
          "IsPathRooted", MessageBoxButtons.OK, MessageBoxIcon.Error);
      }
    }

    private void Settings_Closing(object sender, System.ComponentModel.CancelEventArgs e)
    {
      //this.Close(); 
    }

    private void textBox_path_KeyPress(object sender, System.Windows.Forms.KeyEventArgs e)
    {
      // If the ENTER key is pressed, make a ok
      if ( e.KeyValue == 13 )
      {
        buttonOK.PerformClick(); 
      }
    }

    private void buttonOK_Click(object sender, System.EventArgs e)
    {
      if (System.IO.Path.IsPathRooted(textBox_path.Text) && System.IO.Directory.Exists(textBox_path.Text))
      {
        CData.Instance.setWorkingDirectory(textBox_path.Text);
        CData.Instance.WriteSetting("UserSettings", "WorkingDirectory", CData.Instance.getWorkingDirectory());
        this.Close();
      }
      else
      {
        MessageBox.Show("Invalid path! note: use FindDir",
          "IsPathRooted", MessageBoxButtons.OK, MessageBoxIcon.Error);
      }
    }

    private void buttonCancel_Click(object sender, EventArgs e)
    {
      this.Close();
    }

    private void treeViewSettings_AfterSelect(object sender, TreeViewEventArgs e)
    {
      string sTreeViewSettingName = treeViewSettings.SelectedNode.Name.ToString();

      if (sTreeViewSettingName == treeViewSettings.Nodes[0].Name.ToString())
      {
        sTreeViewSettingName = treeViewSettings.Nodes[0].Nodes[0].Name.ToString();
      }

      string tabPageName = "tabPage" + sTreeViewSettingName;

      try
      {
        tabControl.SelectTab(tabPageName);

        if (tabControl.SelectedTab.TabIndex == this.tabPageGeneral.TabIndex) // General
        {
          textBox_path.Text = CData.Instance.getWorkingDirectory();

          if (CData.Instance.ReadSetting("UserSettings", "WildCardFilter") == "yes")
          {
            checkBoxDisableUserWildCard.Checked = false;
          }
          else
          {
            checkBoxDisableUserWildCard.Checked = true;
          }
        }//if (tabControl.SelectedTab.TabIndex == this.tabPageGeneral.TabIndex) // General
        else if (tabControl.SelectedTab.TabIndex == this.tabPageGenerate.TabIndex) // Generate
        {
          labelGen.Text = "Option \"" + CData.Instance.ReadSetting("UserSettings", "Gen") + "\" is actived";
        }//else if (tabControl.SelectedTab.TabIndex == this.tabPageGenerate.TabIndex) // Generate
        else if (tabControl.SelectedTab.TabIndex == this.tabPageSortControl.TabIndex) // SortControl
        {
          textBoxNewRuleSetValue.Text = sTextBoxNewRuleSetValue;
          buttonAdd.Enabled = false;

          listBoxRuleSet.Items.Clear();

          ArrayList mrs = CData.Instance.getMethodRuleSet();

          foreach (string s in mrs)
          {
            listBoxRuleSet.Items.Add(s);
          }

          if (CData.Instance.ReadSetting("UserSettings", "ManualMethodSort") == "yes")
          {
            listBoxRuleSet.Visible = true;
            labelRuleSet.Visible = true;
            textBoxNewRuleSetValue.Visible = true;
            buttonAdd.Visible = true;
            checkBoxSortControllManualMethodSort.Checked = true;
          }
          else
          {
            listBoxRuleSet.Visible = false;
            labelRuleSet.Visible = false;
            textBoxNewRuleSetValue.Visible = false;
            buttonAdd.Visible = false;
            checkBoxSortControllManualMethodSort.Checked = false;
          }
        }//else if (tabControl.SelectedTab.TabIndex == this.tabPageSortControl.TabIndex) // SortControl
        else if (tabControl.SelectedTab.TabIndex == this.tabPageReleaseNotes.TabIndex) // ReleaseNotes
        {
          string ReleaseNotesRtf = CData.Instance.ReadSetting("UserSettings", "OutPutPath");
          
          if (System.IO.Path.IsPathRooted(ReleaseNotesRtf) && System.IO.Directory.Exists(ReleaseNotesRtf))
          {
            ReleaseNotesRtf += "\\DBClassCodeUtility_ReleaseNotes.rtf";
            richTextBoxReleaseNotes.LoadFile(ReleaseNotesRtf);
          }
        }//else if (tabControl.SelectedTab.TabIndex == this.tabPageReleaseNotes.TabIndex) // ReleaseNotes
      }
      // Catch the IOException generated if the 
      // specified part of the file is locked.
      catch (System.IO.IOException ioEx)
      {
        MessageBox.Show(ioEx.GetType().Name,
            "IOException",
            MessageBoxButtons.OK, MessageBoxIcon.Error);
      }
      catch (ArgumentException arg)
      {
        //The exception that is thrown when one of the arguments provided to a method is not valid. 
        MessageBox.Show(arg.Message,
            "Arguments provided to a method is not valid",
            MessageBoxButtons.OK, MessageBoxIcon.Error);
      }
      catch 
      {
        MessageBox.Show(tabPageName + " not selected",
              "Error after select", 
              MessageBoxButtons.OK, MessageBoxIcon.Error);
      } 
    }

    
    private void checkBoxIsFilterOn_CheckedChanged(object sender, EventArgs e)
    {
      if ( checkBoxDisableUserWildCard.Checked )
      {
        CData.Instance.WriteSetting("UserSettings", "WildCardFilter", "no");
      }
      else 
      {
        CData.Instance.WriteSetting("UserSettings", "WildCardFilter", "yes");
      }
    }

    private void WriteSetting_ManualMethodRuleSet()
    {
      string RuleSet = "";
      foreach (string s in listBoxRuleSet.Items)
      {
        if (RuleSet.Length > 0)
        {
          RuleSet += ",";
        }

        RuleSet += s;
      }

      CData.Instance.WriteSetting("UserSettings", "ManualMethodRuleSet", RuleSet);
    }

    private void checkBoxSortControllManualMethodSort_CheckedChanged(object sender, EventArgs e)
    {
      if ( checkBoxSortControllManualMethodSort.Checked )
      {
        listBoxRuleSet.Visible = true;
        labelRuleSet.Visible = true;
        textBoxNewRuleSetValue.Visible = true;
        buttonAdd.Visible = true;
        CData.Instance.WriteSetting("UserSettings", "ManualMethodSort", "yes");
      }
      else
      {
        listBoxRuleSet.Visible = false;
        labelRuleSet.Visible = false;
        textBoxNewRuleSetValue.Visible = false;
        buttonAdd.Visible = false;
        CData.Instance.WriteSetting("UserSettings", "ManualMethodSort", "no");
      }
    }

    private void contextMenuRuleSet_Opening(object sender, CancelEventArgs e)
    {
      string sName = ((ContextMenuStrip)sender).SourceControl.Name;

      if (sName == listBoxRuleSet.Name)
      {
        int index = listBoxRuleSet.SelectedIndex;

        if (index >= 0)
        {
          moveToolStripMenuItem.Enabled = true;
          deleteToolStripMenuItem.Enabled = true;
        }
        else
        {
          moveToolStripMenuItem.Enabled = false;
          deleteToolStripMenuItem.Enabled = false;
        }
      }
      else if (sName == textBoxNewRuleSetValue.Name)
      {
        moveToolStripMenuItem.Enabled = false;
        deleteToolStripMenuItem.Enabled = false;
      }

      if ( textBoxNewRuleSetValue.Text.Equals(sTextBoxNewRuleSetValue) )
      {
        buttonAdd.Enabled = false;
        newToolStripMenuItem.Enabled = false;
      }
      else
      {
        buttonAdd.Enabled = true;
        newToolStripMenuItem.Enabled = true;
      } 
    }

    private void textBoxNewRuleSetValue_KeyDown(object sender, KeyEventArgs e)
    {
      // If the ENTER key is pressed,
      if (e.KeyValue == 13)
      {
        listBoxRuleSet.Items.Add(textBoxNewRuleSetValue.Text);
        newToolStripMenuItem.Enabled = false;
        textBoxNewRuleSetValue.Text = sTextBoxNewRuleSetValue;
      }
    }

    private void textBoxNewRuleSetValue_TextChanged(object sender, EventArgs e)
    {
      if (textBoxNewRuleSetValue.TextLength < 1 || textBoxNewRuleSetValue.Text.Equals(sTextBoxNewRuleSetValue))
      {
        buttonAdd.Enabled = false;
        newToolStripMenuItem.Enabled = false;
      }
      else
      {
        buttonAdd.Enabled = true;
        newToolStripMenuItem.Enabled = true;
      }
    }

    private void newToolStripMenuItem_Click(object sender, EventArgs e)
    {
      listBoxRuleSet.Items.Add(textBoxNewRuleSetValue.Text);
      WriteSetting_ManualMethodRuleSet();
      buttonAdd.Enabled = false;
      newToolStripMenuItem.Enabled = false;
      textBoxNewRuleSetValue.Text = sTextBoxNewRuleSetValue;
    }

    private void buttonAdd_Click(object sender, EventArgs e)
    {
      listBoxRuleSet.Items.Add(textBoxNewRuleSetValue.Text);
      WriteSetting_ManualMethodRuleSet();
      buttonAdd.Enabled = false;
      newToolStripMenuItem.Enabled = false;
      textBoxNewRuleSetValue.Text = sTextBoxNewRuleSetValue;
    }

    private void deleteToolStripMenuItem_Click(object sender, EventArgs e)
    {
      int index = listBoxRuleSet.SelectedIndex;

      if ( index >= 0 )
      {
        listBoxRuleSet.Items.RemoveAt(index);
        WriteSetting_ManualMethodRuleSet();
      }
    }

    private void upToolStripMenuItem_Click(object sender, EventArgs e)
    {
      int index = listBoxRuleSet.SelectedIndex;

      if ( index > 0 )
      {
        string Temp = listBoxRuleSet.Items[index-1].ToString();
        listBoxRuleSet.Items[index - 1] = listBoxRuleSet.Items[index];
        listBoxRuleSet.Items[index] = Temp;
        WriteSetting_ManualMethodRuleSet();
      }
    }

    private void downToolStripMenuItem_Click(object sender, EventArgs e)
    {
      int index = listBoxRuleSet.SelectedIndex;

      if (index >= 0 && index != listBoxRuleSet.Items.Count-1 )
      {
        string Temp = listBoxRuleSet.Items[index + 1].ToString();
        listBoxRuleSet.Items[index + 1] = listBoxRuleSet.Items[index];
        listBoxRuleSet.Items[index] = Temp;
        WriteSetting_ManualMethodRuleSet();
      }

    }

    private void textBoxNewRuleSetValue_Click(object sender, EventArgs e)
    {
      textBoxNewRuleSetValue.SelectAll();
    }

    private void tabControl_SelectedIndexChanged(object sender, EventArgs e)
    {
      textBoxDescription.Text = "Description";
    }

    private void checkBoxIsFilterOn_MouseHover(object sender, EventArgs e)
    {
      if (checkBoxDisableUserWildCard.Checked == true)
      {
        textBoxDescription.Text = "Filter tables with owner = 'User'";
      }
      else
      {
        textBoxDescription.Text = "Filter tables with owner = 'User%'";
      }
    }

    private void textBox_path_MouseHover(object sender, EventArgs e)
    {
      textBoxDescription.Text = "Shows the current path"; 
    }

    private void checkBoxSortControllManualMethodSort_MouseHover(object sender, EventArgs e)
    {
      textBoxDescription.Text = "When this option is activated own methods will be sorted by name from A to Z." +
                                "The Rule Set bring important methods to the front, that starts with the given rule value(s)";
    }
  }
}
