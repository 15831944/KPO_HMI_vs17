#pragma once
#include <string>
#include <vector>
#include <process.h> 
#include <cstring>
#include "backupstring.h"
#include "CAppSetting.h"
#include <sstream>


namespace BackupUtility
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Configuration;
	using namespace std;
    
	/// <summary> 
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class Form1 : public System::Windows::Forms::Form
	{	
	public:
		Form1(void)
		{
			InitializeComponent();
			readIniFile();
		}

		Form1(System::String* CMD)
		{
			InitializeComponent();
			readIniFile();

			if (  String::CompareOrdinal (CMD,"-c") == 0 )
			{
				//this->BackupButton->PerformClick();
				System::Object *  sender;
				System::EventArgs *  e;
				BackupButton_Click(sender, e);
				exit(0);
			}
		}

  
	protected:
		void Dispose(Boolean disposing)
		{
			if (disposing && components)
			{
				components->Dispose();
			}
			__super::Dispose(disposing);
		}

	private: System::Windows::Forms::Label *  label1;
	private: System::Windows::Forms::Label *  label2;





	private: System::Windows::Forms::FolderBrowserDialog *  folderBrowserDialog1;
	private: System::Windows::Forms::Button *  button1;
	private: System::Windows::Forms::Button *  button2;




	private: System::Windows::Forms::CheckBox *  checkBoxDate;
	private: System::Windows::Forms::TextBox *  textBoxSourceDir;
	private: System::Windows::Forms::TextBox *  textBoxBackupDir;
	private: System::Windows::Forms::CheckBox *  checkBoxZip;
	private: System::Windows::Forms::CheckBox *  checkBoxNew;

  private: System::Windows::Forms::DateTimePicker *  dateTimePicker;
  private: System::Windows::Forms::Button *  CancelButton;
  private: System::Windows::Forms::CheckBox *  checkBoxDateAct;
  private: System::Windows::Forms::CheckBox *  checkBoxBackupDir;
  private: System::Windows::Forms::TextBox *  textBoxFileList;
  private: System::Windows::Forms::Label *  label3;
  private: System::Windows::Forms::Label *  label4;
  private: System::Windows::Forms::Button *  button3;

  private: System::Windows::Forms::Label *  label5;
  private: System::Windows::Forms::TextBox *  textBoxZipDir;

  private: System::Windows::Forms::CheckBox *  checkBoxExisting;


  private: System::Windows::Forms::Button *  BackupButton;



	private:

    void  readIniFile(void)
    {
      textBoxSourceDir->Text  = CAppSetting::getApp()->getValue("Config","textBoxSourceDir");
      textBoxBackupDir->Text  = CAppSetting::getApp()->getValue("Config","textBoxBackupDir");
      textBoxZipDir->Text     = CAppSetting::getApp()->getValue("Config","textBoxZipDir");
      textBoxFileList->Text   = CAppSetting::getApp()->getValue("Config","textBoxFileList");

      dateTimePicker->Text = CAppSetting::getApp()->getValue("Config","dateTimePicker");

      String * strcheckBoxBackupDir = CAppSetting::getApp()->getValue("Config","checkBoxBackupDir");
      if ( String::CompareOrdinal (strcheckBoxBackupDir,"1") == 0 )
        checkBoxBackupDir->set_Checked(true);
      else
        checkBoxBackupDir->set_Checked(false);


      String * strcheckBoxExisting = CAppSetting::getApp()->getValue("Config","checkBoxExisting");
      if ( String::CompareOrdinal (strcheckBoxExisting,"1") == 0 )
        checkBoxExisting->set_Checked(true);
      else
        checkBoxExisting->set_Checked(false);


      String * strcheckBoxDateAct = CAppSetting::getApp()->getValue("Config","checkBoxDateAct");
      if ( String::CompareOrdinal (strcheckBoxDateAct,"1") == 0 )
        checkBoxDateAct->set_Checked(true);
      else
        checkBoxDateAct->set_Checked(false);



      String * strcheckBoxDate = CAppSetting::getApp()->getValue("Config","checkBoxDate");
      if ( String::CompareOrdinal (strcheckBoxDate,"1") == 0 )
        checkBoxDate->set_Checked(true);
      else
        checkBoxDate->set_Checked(false);

      String * strcheckBoxZip = CAppSetting::getApp()->getValue("Config","checkBoxZip");
      if ( String::CompareOrdinal (strcheckBoxZip,"1") == 0 )
        checkBoxZip->set_Checked(true);
      else
        checkBoxZip->set_Checked(false);

      String * strcheckBoxNew = CAppSetting::getApp()->getValue("Config","checkBoxNew");
      if ( String::CompareOrdinal (strcheckBoxNew ,"1") == 0 )
        checkBoxNew->set_Checked(true);
      else
        checkBoxNew->set_Checked(false);

    }

    void  writeIniFile(void)
    {
      CAppSetting::getApp()->createIniFile();
      CAppSetting::getApp()->setValue("Config","textBoxSourceDir",textBoxSourceDir->get_Text());
      CAppSetting::getApp()->setValue("Config","textBoxZipDir",textBoxZipDir->get_Text());
      CAppSetting::getApp()->setValue("Config","textBoxBackupDir",textBoxBackupDir->get_Text());
      CAppSetting::getApp()->setValue("Config","textBoxFileList",textBoxFileList->get_Text());

      CAppSetting::getApp()->setValue("Config","dateTimePicker",dateTimePicker->get_Text());

      String * strcheckBoxBackupDir;
      if (checkBoxBackupDir->Checked) 
        strcheckBoxBackupDir = "1";
      else
        strcheckBoxBackupDir = "0";
      CAppSetting::getApp()->setValue("Config","checkBoxBackupDir",strcheckBoxBackupDir);

      String * strcheckBoxExisting;
      if (checkBoxExisting->Checked) 
        strcheckBoxExisting = "1";
      else
        strcheckBoxExisting = "0";
      CAppSetting::getApp()->setValue("Config","checkBoxExisting",strcheckBoxExisting);

      String * strcheckBoxDateAct;
      if (checkBoxDateAct->Checked) 
        strcheckBoxDateAct = "1";
      else
        strcheckBoxDateAct = "0";
      CAppSetting::getApp()->setValue("Config","checkBoxDateAct",strcheckBoxDateAct);


      String * strcheckBoxDate;
      if (checkBoxDate->Checked) 
        strcheckBoxDate = "1";
      else
        strcheckBoxDate = "0";
      CAppSetting::getApp()->setValue("Config","checkBoxDate",strcheckBoxDate);


      String * strcheckBoxZip;
      if (checkBoxZip->Checked) 
        strcheckBoxZip = "1";
      else
        strcheckBoxZip = "0";
      CAppSetting::getApp()->setValue("Config","checkBoxZip",strcheckBoxZip);

      String * strcheckBoxNew;
      if (checkBoxNew->Checked) 
        strcheckBoxNew = "1";
      else
        strcheckBoxNew = "0";
      CAppSetting::getApp()->setValue("Config","checkBoxNew",strcheckBoxNew);

    }


		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container * components;

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      this->textBoxSourceDir = (new System::Windows::Forms::TextBox());
      this->label1 = (new System::Windows::Forms::Label());
      this->label2 = (new System::Windows::Forms::Label());
      this->textBoxBackupDir = (new System::Windows::Forms::TextBox());
      this->checkBoxZip = (new System::Windows::Forms::CheckBox());
      this->checkBoxNew = (new System::Windows::Forms::CheckBox());
      this->folderBrowserDialog1 = (new System::Windows::Forms::FolderBrowserDialog());
      this->button1 = (new System::Windows::Forms::Button());
      this->button2 = (new System::Windows::Forms::Button());
      this->dateTimePicker = (new System::Windows::Forms::DateTimePicker());
      this->checkBoxDate = (new System::Windows::Forms::CheckBox());
      this->BackupButton = (new System::Windows::Forms::Button());
      this->CancelButton = (new System::Windows::Forms::Button());
      this->checkBoxDateAct = (new System::Windows::Forms::CheckBox());
      this->checkBoxBackupDir = (new System::Windows::Forms::CheckBox());
      this->textBoxFileList = (new System::Windows::Forms::TextBox());
      this->label3 = (new System::Windows::Forms::Label());
      this->label4 = (new System::Windows::Forms::Label());
      this->button3 = (new System::Windows::Forms::Button());
      this->textBoxZipDir = (new System::Windows::Forms::TextBox());
      this->label5 = (new System::Windows::Forms::Label());
      this->checkBoxExisting = (new System::Windows::Forms::CheckBox());
      this->SuspendLayout();
      // 
      // textBoxSourceDir
      // 
      this->textBoxSourceDir->Location = System::Drawing::Point(153, 35);
      this->textBoxSourceDir->Name = S"textBoxSourceDir";
      this->textBoxSourceDir->Size = System::Drawing::Size(407, 20);
      this->textBoxSourceDir->TabIndex = 0;
      this->textBoxSourceDir->Text = S"x:\\";
      this->textBoxSourceDir->TextChanged += new System::EventHandler(this, &Form1::textBox1_TextChanged);
      // 
      // label1
      // 
      this->label1->Location = System::Drawing::Point(13, 35);
      this->label1->Name = S"label1";
      this->label1->Size = System::Drawing::Size(94, 20);
      this->label1->TabIndex = 1;
      this->label1->Text = S"Source path";
      this->label1->Click += new System::EventHandler(this, &Form1::label1_Click);
      // 
      // label2
      // 
      this->label2->Location = System::Drawing::Point(13, 69);
      this->label2->Name = S"label2";
      this->label2->Size = System::Drawing::Size(94, 20);
      this->label2->TabIndex = 2;
      this->label2->Text = S"Destination path";
      this->label2->Click += new System::EventHandler(this, &Form1::label2_Click);
      // 
      // textBoxBackupDir
      // 
      this->textBoxBackupDir->Location = System::Drawing::Point(153, 69);
      this->textBoxBackupDir->Name = S"textBoxBackupDir";
      this->textBoxBackupDir->Size = System::Drawing::Size(407, 20);
      this->textBoxBackupDir->TabIndex = 2;
      this->textBoxBackupDir->Text = S"d:\\SMS_Demag\\backup\\";
      this->textBoxBackupDir->TextChanged += new System::EventHandler(this, &Form1::textBoxBackupDir_TextChanged);
      // 
      // checkBoxZip
      // 
      this->checkBoxZip->Location = System::Drawing::Point(80, 400);
      this->checkBoxZip->Name = S"checkBoxZip";
      this->checkBoxZip->Size = System::Drawing::Size(133, 21);
      this->checkBoxZip->TabIndex = 12;
      this->checkBoxZip->Text = S"Zip Backup";
      // 
      // checkBoxNew
      // 
      this->checkBoxNew->Location = System::Drawing::Point(80, 368);
      this->checkBoxNew->Name = S"checkBoxNew";
      this->checkBoxNew->Size = System::Drawing::Size(368, 21);
      this->checkBoxNew->TabIndex = 11;
      this->checkBoxNew->Text = S"create new Backup (will delete destination files and directories !)";
      // 
      // button1
      // 
      this->button1->Location = System::Drawing::Point(576, 35);
      this->button1->Name = S"button1";
      this->button1->Size = System::Drawing::Size(33, 20);
      this->button1->TabIndex = 1;
      this->button1->Text = S"...";
      this->button1->Click += new System::EventHandler(this, &Form1::label1_Click);
      // 
      // button2
      // 
      this->button2->Location = System::Drawing::Point(576, 69);
      this->button2->Name = S"button2";
      this->button2->Size = System::Drawing::Size(33, 20);
      this->button2->TabIndex = 3;
      this->button2->Text = S"...";
      this->button2->Click += new System::EventHandler(this, &Form1::label2_Click);
      // 
      // dateTimePicker
      // 
      this->dateTimePicker->Enabled = false;
      this->dateTimePicker->Location = System::Drawing::Point(286, 242);
      this->dateTimePicker->Name = S"dateTimePicker";
      this->dateTimePicker->Size = System::Drawing::Size(260, 20);
      this->dateTimePicker->TabIndex = 9;
      // 
      // checkBoxDate
      // 
      this->checkBoxDate->Location = System::Drawing::Point(80, 242);
      this->checkBoxDate->Name = S"checkBoxDate";
      this->checkBoxDate->Size = System::Drawing::Size(200, 20);
      this->checkBoxDate->TabIndex = 8;
      this->checkBoxDate->Text = S"backup files modified since";
      this->checkBoxDate->Click += new System::EventHandler(this, &Form1::checkBoxDate_Click);
      this->checkBoxDate->CheckedChanged += new System::EventHandler(this, &Form1::checkBoxDate_CheckedChanged);
      // 
      // BackupButton
      // 
      this->BackupButton->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->BackupButton->Location = System::Drawing::Point(256, 424);
      this->BackupButton->Name = S"BackupButton";
      this->BackupButton->Size = System::Drawing::Size(62, 20);
      this->BackupButton->TabIndex = 13;
      this->BackupButton->Text = S"Backup";
      this->BackupButton->Click += new System::EventHandler(this, &Form1::BackupButton_Click);
      // 
      // CancelButton
      // 
      this->CancelButton->DialogResult = System::Windows::Forms::DialogResult::Abort;
      this->CancelButton->Location = System::Drawing::Point(344, 424);
      this->CancelButton->Name = S"CancelButton";
      this->CancelButton->Size = System::Drawing::Size(62, 20);
      this->CancelButton->TabIndex = 14;
      this->CancelButton->Text = S"Cancel";
      this->CancelButton->Click += new System::EventHandler(this, &Form1::CancelButton_Click);
      // 
      // checkBoxDateAct
      // 
      this->checkBoxDateAct->Location = System::Drawing::Point(80, 216);
      this->checkBoxDateAct->Name = S"checkBoxDateAct";
      this->checkBoxDateAct->Size = System::Drawing::Size(256, 20);
      this->checkBoxDateAct->TabIndex = 7;
      this->checkBoxDateAct->Text = S"backup younger files only (/D)";
      this->checkBoxDateAct->Click += new System::EventHandler(this, &Form1::checkBoxDateAct_Click);
      this->checkBoxDateAct->CheckedChanged += new System::EventHandler(this, &Form1::checkBoxDateAct_CheckedChanged);
      // 
      // checkBoxBackupDir
      // 
      this->checkBoxBackupDir->Location = System::Drawing::Point(108, 281);
      this->checkBoxBackupDir->Name = S"checkBoxBackupDir";
      this->checkBoxBackupDir->Size = System::Drawing::Size(368, 20);
      this->checkBoxBackupDir->TabIndex = 10;
      this->checkBoxBackupDir->Text = S"create differential backup directory";
      this->checkBoxBackupDir->CheckedChanged += new System::EventHandler(this, &Form1::checkBoxBackupDir_CheckedChanged);
      // 
      // textBoxFileList
      // 
      this->textBoxFileList->Location = System::Drawing::Point(152, 160);
      this->textBoxFileList->Name = S"textBoxFileList";
      this->textBoxFileList->Size = System::Drawing::Size(407, 20);
      this->textBoxFileList->TabIndex = 6;
      this->textBoxFileList->Text = S"*.*";
      this->textBoxFileList->TextChanged += new System::EventHandler(this, &Form1::textBoxFileList_TextChanged);
      // 
      // label3
      // 
      this->label3->Location = System::Drawing::Point(8, 160);
      this->label3->Name = S"label3";
      this->label3->Size = System::Drawing::Size(136, 20);
      this->label3->TabIndex = 18;
      this->label3->Text = S"Backup only following files";
      // 
      // label4
      // 
      this->label4->Location = System::Drawing::Point(568, 160);
      this->label4->Name = S"label4";
      this->label4->Size = System::Drawing::Size(112, 20);
      this->label4->TabIndex = 19;
      this->label4->Text = S"separate by \" ; \"";
      // 
      // button3
      // 
      this->button3->Location = System::Drawing::Point(576, 112);
      this->button3->Name = S"button3";
      this->button3->Size = System::Drawing::Size(33, 20);
      this->button3->TabIndex = 5;
      this->button3->Text = S"...";
      this->button3->Click += new System::EventHandler(this, &Form1::button3_Click);
      // 
      // textBoxZipDir
      // 
      this->textBoxZipDir->Location = System::Drawing::Point(152, 112);
      this->textBoxZipDir->Name = S"textBoxZipDir";
      this->textBoxZipDir->Size = System::Drawing::Size(407, 20);
      this->textBoxZipDir->TabIndex = 4;
      this->textBoxZipDir->Text = S"d:\\SMS_Demag\\Archive\\";
      this->textBoxZipDir->TextChanged += new System::EventHandler(this, &Form1::textBox1_TextChanged_1);
      // 
      // label5
      // 
      this->label5->Location = System::Drawing::Point(8, 112);
      this->label5->Name = S"label5";
      this->label5->Size = System::Drawing::Size(94, 20);
      this->label5->TabIndex = 20;
      this->label5->Text = S"Zip path";
      this->label5->Click += new System::EventHandler(this, &Form1::label5_Click);
      // 
      // checkBoxExisting
      // 
      this->checkBoxExisting->Location = System::Drawing::Point(80, 336);
      this->checkBoxExisting->Name = S"checkBoxExisting";
      this->checkBoxExisting->Size = System::Drawing::Size(368, 21);
      this->checkBoxExisting->TabIndex = 22;
      this->checkBoxExisting->Text = S"perform update only (/U)";
      // 
      // Form1
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(720, 509);
      this->Controls->Add(this->checkBoxExisting);
      this->Controls->Add(this->button3);
      this->Controls->Add(this->textBoxZipDir);
      this->Controls->Add(this->label5);
      this->Controls->Add(this->label4);
      this->Controls->Add(this->label3);
      this->Controls->Add(this->textBoxFileList);
      this->Controls->Add(this->checkBoxBackupDir);
      this->Controls->Add(this->checkBoxDateAct);
      this->Controls->Add(this->CancelButton);
      this->Controls->Add(this->BackupButton);
      this->Controls->Add(this->checkBoxDate);
      this->Controls->Add(this->dateTimePicker);
      this->Controls->Add(this->button2);
      this->Controls->Add(this->button1);
      this->Controls->Add(this->checkBoxNew);
      this->Controls->Add(this->checkBoxZip);
      this->Controls->Add(this->textBoxBackupDir);
      this->Controls->Add(this->label2);
      this->Controls->Add(this->label1);
      this->Controls->Add(this->textBoxSourceDir);
      this->Name = S"Form1";
      this->Text = S"SMS Demag BackupUtility";
      this->Load += new System::EventHandler(this, &Form1::Form1_Load);
      this->ResumeLayout(false);
      this->PerformLayout();

    }	
	private: System::Void label1_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
				{
					textBoxSourceDir->Text = folderBrowserDialog1->SelectedPath;
				}

			 }

	private: System::Void label2_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
				{
					textBoxBackupDir->Text = folderBrowserDialog1->SelectedPath;
				}
			 }

	private: System::Void checkBoxDate_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 if (checkBoxDate->Checked)
				 {
					 dateTimePicker->Enabled = true;
           checkBoxDateAct->set_Checked(false); 
           checkBoxBackupDir->set_Checked(false);
				 }
				 else
				 {
					 dateTimePicker->Enabled = false;
				 }
			 }

	private: System::Void checkBoxDateAct_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 if (checkBoxDateAct->Checked)
				 {
					 dateTimePicker->Enabled = false;
           checkBoxDate->set_Checked(false); 
           checkBoxBackupDir->set_Checked(false);
				 }
			 }


private: System::Void textBox1_TextChanged(System::Object *  sender, System::EventArgs *  e)
		 {
		 }

private: System::Void BackupButton_Click(System::Object *  sender, System::EventArgs *  e)
		 {

			 String * sourcedir   = textBoxSourceDir->get_Text();
			 String * backupdir   = textBoxBackupDir->get_Text(); 
			 String * zipdir      = textBoxZipDir->get_Text(); 
			 String * FileList    = textBoxFileList->get_Text();

			 String * execXcopy;
			 String * execNew;
			 String * deleteZip;
			 String * backupZip;
			 String * defaultZip;
			 String * sDate;
			 String * sActDate;
			 String * exeMakeDir;
			 string execString;
			 int result = 0;
			 String * copySwitches;

			 DateTime DateNow;
			 sActDate = String::Concat(sActDate,System::Convert::ToString(DateNow.Now.Year),"_");
			 sActDate = String::Concat(sActDate,System::Convert::ToString(DateNow.Now.Month),"_");
			 sActDate = String::Concat(sActDate,System::Convert::ToString(DateNow.Now.Day),"_");
			 sActDate = String::Concat(sActDate,System::Convert::ToString(DateNow.Now.Hour),"_");
			 sActDate = String::Concat(sActDate,System::Convert::ToString(DateNow.Now.Minute),"_");
			 sActDate = String::Concat(sActDate,System::Convert::ToString(DateNow.Now.Second));

			 copySwitches = "/S /E /Y /R";


			 BackupString * bs;

			 // removing complete backup if "create new backup" is selected
			 if ( checkBoxNew->Checked )
			 {
				 execNew = String::Concat("rd ",backupdir," /S /Q ");
				 bs->MarshalString(execNew,execString);
				 result = system(execString.c_str());
			 }

			 // creating backup and zip directory
			 exeMakeDir = String::Concat(S"md ",backupdir);
			 bs->MarshalString(exeMakeDir,execString);
			 result = system(execString.c_str());

			 exeMakeDir = String::Concat(S"md ",zipdir);
			 bs->MarshalString(exeMakeDir,execString);
			 result = system(execString.c_str());

			 // check FileList for entries
			 vector<string> FileListCont;

			 if ( FileList->Length <= 0 )
			 {
				 FileListCont.push_back("*.*");
			 }
			 else
			 {
				 std::string ActValue ;

				 bs->MarshalString(FileList,ActValue);

				 while (!ActValue.empty())
				 {
					 std::string ActSubstr = ActValue;

					 std::basic_string <char>::size_type pos = ActValue.find(";");

					 if ( std::string::npos != pos )
					 {
						 ActSubstr = ActValue.substr(0,pos );
						 ActValue = ActValue.substr(pos+1,ActValue.length());
					 }
					 else
					 {
						 ActValue.erase();
					 }

					 FileListCont.push_back(ActSubstr);        
				 }
			 }

			 if (checkBoxExisting->Checked) 
			 {
				 // reset execXcopy
				 copySwitches = String::Concat(copySwitches," /U");
			 }


			 // iteration for all files, *.* is includes as default!
			 vector<std::string>::iterator it;

			 for ( it = FileListCont.begin() ; it != FileListCont.end() ; ++ it )
			 {
				 String * ActFile = (*it).c_str();
				 DateTime Date;

				 if ( checkBoxDateAct->Checked )
				 {
					 copySwitches = String::Concat(copySwitches, " /D");
				 }
				 else if ( checkBoxDate->Checked )
				 {
					 Date = dateTimePicker->Value;
					 sDate = String::Concat(System::Convert::ToString(Date.Month),"-");
					 sDate = String::Concat(sDate,System::Convert::ToString(Date.Day),"-");
					 sDate = String::Concat(sDate,System::Convert::ToString(Date.Year));

					 copySwitches = String::Concat(copySwitches, " /D:", sDate);
				 }

				 if (checkBoxBackupDir->Checked) 
				 {
					 String * sActDate2;
					 sActDate2 = String::Concat(sActDate2,System::Convert::ToString(Date.Now.Year),"_");
					 sActDate2 = String::Concat(sActDate2,System::Convert::ToString(Date.Now.Month),"_");
					 sActDate2 = String::Concat(sActDate2,System::Convert::ToString(Date.Now.Day));

					 backupdir = String::Concat(backupdir,"\\",sActDate2);
				 }

				 // execute xcopy call
				 execXcopy = String::Concat("xcopy ",sourcedir,"\\",ActFile);
				 execXcopy = String::Concat(execXcopy," ",backupdir);
				 execXcopy = String::Concat(execXcopy, "\\*.*",copySwitches);

				 bs->MarshalString(execXcopy,execString);
				 result = system(execString.c_str());
			 }

			 // zipping backupdirectory
			 if (checkBoxZip->Checked)
			 {	
				 // remove backup.zip file
				 deleteZip = String::Concat("del ",zipdir,"\\backup.zip ");
				 bs->MarshalString(deleteZip,execString);
				 result = system(execString.c_str());

				 defaultZip = String::Concat("zip -r -u ",zipdir,"\\backup.zip ");
				 defaultZip = String::Concat(defaultZip,backupdir,"\\*");

				 bs->MarshalString(defaultZip,execString);
				 result = system(execString.c_str());

				 backupZip = String::Concat("copy ",zipdir,"\\backup.zip ");
				 backupZip = String::Concat(backupZip,zipdir,"\\update_",sActDate);
				 backupZip = String::Concat(backupZip,".zip");

				 bs->MarshalString(backupZip,execString);
				 result = system(execString.c_str());
			 }

			 writeIniFile();
		 }


private: System::Void CancelButton_Click(System::Object *  sender, System::EventArgs *  e)
		 {
       writeIniFile();
			 this->Close();
		 }

private: System::Void label3_Click(System::Object *  sender, System::EventArgs *  e)
         {
         }

private: System::Void checkBoxDate_CheckedChanged(System::Object *  sender, System::EventArgs *  e)
         {
         }

private: System::Void textBoxBackupDir_TextChanged(System::Object *  sender, System::EventArgs *  e)
         {
         }

private: System::Void checkBoxDateAct_CheckedChanged(System::Object *  sender, System::EventArgs *  e)
         {
         }

private: System::Void Form1_Load(System::Object *  sender, System::EventArgs *  e)
         {
         }

private: System::Void label3_Click_1(System::Object *  sender, System::EventArgs *  e)
         {
         }

private: System::Void textBoxFileList_TextChanged(System::Object *  sender, System::EventArgs *  e)
         {
         }

private: System::Void button3_Click(System::Object *  sender, System::EventArgs *  e)
         {
				  if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
				  {
					  textBoxZipDir->Text = folderBrowserDialog1->SelectedPath;
				  }
         }

private: System::Void textBox1_TextChanged_1(System::Object *  sender, System::EventArgs *  e)
         {
         }

private: System::Void label5_Click(System::Object *  sender, System::EventArgs *  e)
         {
         }

private: System::Void checkBoxBackupDir_CheckedChanged(System::Object *  sender, System::EventArgs *  e)
         {
         }

};
}


