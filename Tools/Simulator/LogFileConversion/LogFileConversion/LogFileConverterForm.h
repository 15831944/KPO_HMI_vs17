#pragma once

#include "CInterConvertForm.h"
#include "CInterAssignment.h"
#include "CInterAssignment.h"

//#using <mscorlib.dll>

namespace LogFileConversion
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary> 
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class LogFileConverterForm : public System::Windows::Forms::Form
	{	
	public:
		LogFileConverterForm(void)
		{
			InitializeComponent();
            initComponent();
		}
  
	protected:
		//void Dispose(Boolean disposing)
		//{
		//	if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}

    private: System::Windows::Forms::Panel ^  panel2;
    private: System::Windows::Forms::Splitter ^  splitter1;
    private: System::Windows::Forms::Panel ^  panel3;
    private: System::Windows::Forms::Panel ^  panel5;
    private: System::Windows::Forms::Label ^  label1;
    private: System::Windows::Forms::Label ^  label2;
    private: System::Windows::Forms::Panel ^  panInterAssign;
    private: System::Windows::Forms::Panel ^  panSetting;
    private: System::Windows::Forms::Button ^  butLoadInter;
    private: System::Windows::Forms::OpenFileDialog ^  openFileDialog;
    private: System::Windows::Forms::ComboBox ^  comBxDestInter;
    private: System::Windows::Forms::ComboBox ^  comBxSourceInter;
    private: System::Windows::Forms::SaveFileDialog ^  saveFileDialog;
    private: System::Windows::Forms::Label ^  label3;
    private: System::Windows::Forms::Button ^  butLoadConfig;
    private: System::Windows::Forms::Label ^  label4;
    private: System::Windows::Forms::Button ^  butSaveConfig;
    private: System::Windows::Forms::Label ^  label5;
    private: System::Windows::Forms::Button ^  butClearAssign;
    private: System::Windows::Forms::Label ^  label6;
    private: System::Windows::Forms::Button ^  butConvertLogFile;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^ components;

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
            this->panel2 = gcnew System::Windows::Forms::Panel();
            this->splitter1 = gcnew System::Windows::Forms::Splitter();
            this->panel3 = gcnew System::Windows::Forms::Panel();
            this->panInterAssign = gcnew System::Windows::Forms::Panel();
            this->panSetting = gcnew System::Windows::Forms::Panel();
            this->butLoadInter = gcnew System::Windows::Forms::Button();
            this->panel5 = gcnew System::Windows::Forms::Panel();
            this->comBxDestInter = gcnew System::Windows::Forms::ComboBox();
            this->label2 = gcnew System::Windows::Forms::Label();
            this->comBxSourceInter = gcnew System::Windows::Forms::ComboBox();
            this->label1 = gcnew System::Windows::Forms::Label();
            this->openFileDialog = gcnew System::Windows::Forms::OpenFileDialog();
            this->saveFileDialog = gcnew System::Windows::Forms::SaveFileDialog();
            this->label3 = gcnew System::Windows::Forms::Label();
            this->butLoadConfig = gcnew System::Windows::Forms::Button();
            this->label4 = gcnew System::Windows::Forms::Label();
            this->butSaveConfig = gcnew System::Windows::Forms::Button();
            this->label5 = gcnew System::Windows::Forms::Label();
            this->butClearAssign = gcnew System::Windows::Forms::Button();
            this->label6 = gcnew System::Windows::Forms::Label();
            this->butConvertLogFile = gcnew System::Windows::Forms::Button();
            this->panel3->SuspendLayout();
            this->panSetting->SuspendLayout();
            this->panel5->SuspendLayout();
            this->SuspendLayout();
            // 
            // panel2
            // 
            this->panel2->Dock = System::Windows::Forms::DockStyle::Top;
            this->panel2->Location = System::Drawing::Point(0, 0);
            this->panel2->Name = "panel2";
            this->panel2->Size = System::Drawing::Size(616, 24);
            this->panel2->TabIndex = 1;
            // 
            // splitter1
            // 
            this->splitter1->Dock = System::Windows::Forms::DockStyle::Bottom;
            this->splitter1->Location = System::Drawing::Point(0, 322);
            this->splitter1->Name = "splitter1";
            this->splitter1->Size = System::Drawing::Size(616, 3);
            this->splitter1->TabIndex = 5;
            this->splitter1->TabStop = false;
            // 
            // panel3
            // 
            this->panel3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->panel3->Controls->Add(this->panInterAssign);
            this->panel3->Controls->Add(this->panSetting);
            this->panel3->Controls->Add(this->panel5);
            this->panel3->Dock = System::Windows::Forms::DockStyle::Fill;
            this->panel3->Location = System::Drawing::Point(0, 24);
            this->panel3->Name = "panel3";
            this->panel3->Size = System::Drawing::Size(616, 298);
            this->panel3->TabIndex = 6;
            // 
            // panInterAssign
            // 
            this->panInterAssign->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
            this->panInterAssign->Dock = System::Windows::Forms::DockStyle::Fill;
            this->panInterAssign->Location = System::Drawing::Point(0, 24);
            this->panInterAssign->Name = "panInterAssign";
            this->panInterAssign->Size = System::Drawing::Size(614, 242);
            this->panInterAssign->TabIndex = 2;
            // 
            // panSetting
            // 
            this->panSetting->Controls->Add(this->butConvertLogFile);
            this->panSetting->Controls->Add(this->label6);
            this->panSetting->Controls->Add(this->butClearAssign);
            this->panSetting->Controls->Add(this->label5);
            this->panSetting->Controls->Add(this->butSaveConfig);
            this->panSetting->Controls->Add(this->label4);
            this->panSetting->Controls->Add(this->butLoadConfig);
            this->panSetting->Controls->Add(this->label3);
            this->panSetting->Controls->Add(this->butLoadInter);
            this->panSetting->Dock = System::Windows::Forms::DockStyle::Bottom;
            this->panSetting->DockPadding->All = 5;
            this->panSetting->Location = System::Drawing::Point(0, 266);
            this->panSetting->Name = "panSetting";
            this->panSetting->Size = System::Drawing::Size(614, 30);
            this->panSetting->TabIndex = 1;
            // 
            // butLoadInter
            // 
            this->butLoadInter->Dock = System::Windows::Forms::DockStyle::Left;
            this->butLoadInter->Location = System::Drawing::Point(5, 5);
            this->butLoadInter->Name = "butLoadInter";
            this->butLoadInter->Size = System::Drawing::Size(88, 20);
            this->butLoadInter->TabIndex = 0;
            this->butLoadInter->Text = "Load Interface";
            this->butLoadInter->Click += gcnew System::EventHandler(this, &LogFileConverterForm::OnButLoadInterClick);
            // 
            // panel5
            // 
            this->panel5->Controls->Add(this->comBxDestInter);
            this->panel5->Controls->Add(this->label2);
            this->panel5->Controls->Add(this->comBxSourceInter);
            this->panel5->Controls->Add(this->label1);
            this->panel5->Dock = System::Windows::Forms::DockStyle::Top;
            this->panel5->Location = System::Drawing::Point(0, 0);
            this->panel5->Name = "panel5";
            this->panel5->Size = System::Drawing::Size(614, 24);
            this->panel5->TabIndex = 0;
            // 
            // comBxDestInter
            // 
            this->comBxDestInter->Dock = System::Windows::Forms::DockStyle::Left;
            this->comBxDestInter->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->comBxDestInter->Location = System::Drawing::Point(288, 0);
            this->comBxDestInter->Name = "comBxDestInter";
            this->comBxDestInter->Size = System::Drawing::Size(120, 21);
            this->comBxDestInter->TabIndex = 3;
            this->comBxDestInter->SelectedIndexChanged += gcnew System::EventHandler(this, &LogFileConverterForm::OnComBxDestInterSelIndexChanged);
            // 
            // label2
            // 
            this->label2->Dock = System::Windows::Forms::DockStyle::Left;
            this->label2->Location = System::Drawing::Point(176, 0);
            this->label2->Name = "label2";
            this->label2->Size = System::Drawing::Size(112, 24);
            this->label2->TabIndex = 2;
            this->label2->Text = "convert to interface";
            this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            // 
            // comBxSourceInter
            // 
            this->comBxSourceInter->Dock = System::Windows::Forms::DockStyle::Left;
            this->comBxSourceInter->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->comBxSourceInter->Location = System::Drawing::Point(56, 0);
            this->comBxSourceInter->Name = "comBxSourceInter";
            this->comBxSourceInter->Size = System::Drawing::Size(120, 21);
            this->comBxSourceInter->TabIndex = 1;
            this->comBxSourceInter->SelectedIndexChanged += gcnew System::EventHandler(this, &LogFileConverterForm::OnComBxDestInterSelIndexChanged);
            // 
            // label1
            // 
            this->label1->Dock = System::Windows::Forms::DockStyle::Left;
            this->label1->Location = System::Drawing::Point(0, 0);
            this->label1->Name = "label1";
            this->label1->Size = System::Drawing::Size(56, 24);
            this->label1->TabIndex = 0;
            this->label1->Text = "Interface ";
            this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            // 
            // label3
            // 
            this->label3->Dock = System::Windows::Forms::DockStyle::Left;
            this->label3->Location = System::Drawing::Point(93, 5);
            this->label3->Name = "label3";
            this->label3->Size = System::Drawing::Size(10, 20);
            this->label3->TabIndex = 5;
            // 
            // butLoadConfig
            // 
            this->butLoadConfig->Dock = System::Windows::Forms::DockStyle::Left;
            this->butLoadConfig->Location = System::Drawing::Point(103, 5);
            this->butLoadConfig->Name = "butLoadConfig";
            this->butLoadConfig->Size = System::Drawing::Size(75, 20);
            this->butLoadConfig->TabIndex = 6;
            this->butLoadConfig->Text = "Load Config";
            this->butLoadConfig->Click += gcnew System::EventHandler(this, &LogFileConverterForm::OnButLoadConfig);
            // 
            // label4
            // 
            this->label4->Dock = System::Windows::Forms::DockStyle::Left;
            this->label4->Location = System::Drawing::Point(178, 5);
            this->label4->Name = "label4";
            this->label4->Size = System::Drawing::Size(10, 20);
            this->label4->TabIndex = 7;
            // 
            // butSaveConfig
            // 
            this->butSaveConfig->Dock = System::Windows::Forms::DockStyle::Left;
            this->butSaveConfig->Location = System::Drawing::Point(188, 5);
            this->butSaveConfig->Name = "butSaveConfig";
            this->butSaveConfig->Size = System::Drawing::Size(75, 20);
            this->butSaveConfig->TabIndex = 8;
            this->butSaveConfig->Text = "Save Config";
            this->butSaveConfig->Click += gcnew System::EventHandler(this, &LogFileConverterForm::OnButSaveConfig);
            // 
            // label5
            // 
            this->label5->Dock = System::Windows::Forms::DockStyle::Left;
            this->label5->Location = System::Drawing::Point(263, 5);
            this->label5->Name = "label5";
            this->label5->Size = System::Drawing::Size(10, 20);
            this->label5->TabIndex = 9;
            // 
            // butClearAssign
            // 
            this->butClearAssign->Dock = System::Windows::Forms::DockStyle::Left;
            this->butClearAssign->Location = System::Drawing::Point(273, 5);
            this->butClearAssign->Name = "butClearAssign";
            this->butClearAssign->Size = System::Drawing::Size(72, 20);
            this->butClearAssign->TabIndex = 10;
            this->butClearAssign->Text = "Clear Assignment";
            this->butClearAssign->Click += gcnew System::EventHandler(this, &LogFileConverterForm::OnButClearAssign);
            // 
            // label6
            // 
            this->label6->Dock = System::Windows::Forms::DockStyle::Left;
            this->label6->Location = System::Drawing::Point(345, 5);
            this->label6->Name = "label6";
            this->label6->Size = System::Drawing::Size(10, 20);
            this->label6->TabIndex = 11;
            // 
            // butConvertLogFile
            // 
            this->butConvertLogFile->Dock = System::Windows::Forms::DockStyle::Left;
            this->butConvertLogFile->Location = System::Drawing::Point(355, 5);
            this->butConvertLogFile->Name = "butConvertLogFile";
            this->butConvertLogFile->Size = System::Drawing::Size(75, 20);
            this->butConvertLogFile->TabIndex = 12;
            this->butConvertLogFile->Text = "Convert Log File";
            this->butConvertLogFile->Click += gcnew System::EventHandler(this, &LogFileConverterForm::OnButConvertLogFile);
            // 
            // LogFileConverterForm
            // 
            this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
            this->ClientSize = System::Drawing::Size(616, 325);
            this->Controls->Add(this->panel3);
            this->Controls->Add(this->splitter1);
            this->Controls->Add(this->panel2);
            this->Name = "LogFileConverterForm";
            this->Text = "LogFileConverterForm";
            this->Load += gcnew System::EventHandler(this, &LogFileConverterForm::OnLoadLogFileForm);
            this->panel3->ResumeLayout(false);
            this->panSetting->ResumeLayout(false);
            this->panel5->ResumeLayout(false);
            this->ResumeLayout(false);

        }	
        System::Void OnLoadLogFileForm(System::Object ^  sender, System::EventArgs ^  e);
        System::Void OnButLoadInterClick(System::Object ^  sender, System::EventArgs ^  e);
        System::Void OnButLoadConfig(System::Object ^  sender, System::EventArgs ^  e);
        System::Void OnButSaveConfig(System::Object ^  sender, System::EventArgs ^  e);
        System::Void OnButClearAssign(System::Object ^  sender, System::EventArgs ^  e);
        System::Void OnButConvertLogFile(System::Object ^  sender, System::EventArgs ^  e);
        //System::Void OnComBoxAvailInterValueChanged(System::Object ^  sender, System::EventArgs ^  e);
        System::Void OnComBxDestInterSelIndexChanged(System::Object ^  sender, System::EventArgs ^  e);
        //------------------------------------------------------------------
        //GUI - Elements
        CInterConvertForm^ InterConvertForm;
        //Data - Elements
        ArrayList^ InterListe;
        ArrayList^ InterAssignmentListe;
		//Flags - Elements
		bool UpInterAssViewFlag;
        //------------------------------------------------------------------
        void initComponent();
        void initView();
        bool loadInterface();
        void updateSourceInterView(String^ interName);
        CTlgInterfaceWrapper^ findInter(String^ name);
        CInterAssignment^ findInterAssignment(String^ source,String^ dest);
        bool isInterLoaded(String^ name);
};
}


