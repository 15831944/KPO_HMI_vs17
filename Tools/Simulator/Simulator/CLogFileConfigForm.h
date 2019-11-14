#pragma once

//----------------------------------------------------------------------------
#include "CTlgInterfaceWrapper.h"
#include "CAppSetting.h"
#include "CXmlInterConfigReader.h"
#include "CXmlInterConfigWriter.h"
//----------------------------------------------------------------------------

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace simulator
{
	/// <summary> 
	/// Summary for CLogFileConfigForm
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CLogFileConfigForm : public System::Windows::Forms::Form
	{
	public: 
		CLogFileConfigForm(void)
		{
			InitializeComponent();
      Interface = nullptr;
		}
    void setInterface(CTlgInterfaceWrapper^ inter);
		void updateConfFileFromView();
	protected: 
		//void Dispose(Boolean disposing)
		//{
		//	if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}
    private: System::Windows::Forms::GroupBox ^  grpBxTime;
    private: System::Windows::Forms::Panel ^  panDateFormat;
    private: System::Windows::Forms::Panel ^  panTimeFormat;
    private: System::Windows::Forms::Label ^  label1;
    private: System::Windows::Forms::Label ^  label2;
    private: System::Windows::Forms::ComboBox ^  comBxDateItem1;
    private: System::Windows::Forms::TextBox ^  txtBxDateDel1;
    private: System::Windows::Forms::ComboBox ^  comBxDateItem2;
    private: System::Windows::Forms::TextBox ^  txtBxDateDel2;
    private: System::Windows::Forms::ComboBox ^  comBxDateItem3;
    private: System::Windows::Forms::ComboBox ^  comBxTimeItem1;
    private: System::Windows::Forms::TextBox ^  txtBxTimeDel1;
    private: System::Windows::Forms::ComboBox ^  comBxTimeItem2;
    private: System::Windows::Forms::TextBox ^  txtBxTimeDel2;
    private: System::Windows::Forms::ComboBox ^  comBxTimeItem3;
    private: System::Windows::Forms::TextBox ^  txtBxTimeDel3;
    private: System::Windows::Forms::ComboBox ^  comBxTimeItem4;
    private: System::Windows::Forms::Label ^  label3;
    private: System::Windows::Forms::TextBox ^  txtBxLogFileSep;
	  private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->grpBxTime = gcnew System::Windows::Forms::GroupBox();
			this->panTimeFormat = gcnew System::Windows::Forms::Panel();
			this->comBxTimeItem4 = gcnew System::Windows::Forms::ComboBox();
			this->txtBxTimeDel3 = gcnew System::Windows::Forms::TextBox();
			this->comBxTimeItem3 = gcnew System::Windows::Forms::ComboBox();
			this->txtBxTimeDel2 = gcnew System::Windows::Forms::TextBox();
			this->comBxTimeItem2 = gcnew System::Windows::Forms::ComboBox();
			this->txtBxTimeDel1 = gcnew System::Windows::Forms::TextBox();
			this->comBxTimeItem1 = gcnew System::Windows::Forms::ComboBox();
			this->label2 = gcnew System::Windows::Forms::Label();
			this->panDateFormat = gcnew System::Windows::Forms::Panel();
			this->comBxDateItem3 = gcnew System::Windows::Forms::ComboBox();
			this->txtBxDateDel2 = gcnew System::Windows::Forms::TextBox();
			this->comBxDateItem2 = gcnew System::Windows::Forms::ComboBox();
			this->txtBxDateDel1 = gcnew System::Windows::Forms::TextBox();
			this->comBxDateItem1 = gcnew System::Windows::Forms::ComboBox();
			this->label1 = gcnew System::Windows::Forms::Label();
			this->txtBxLogFileSep = gcnew System::Windows::Forms::TextBox();
			this->label3 = gcnew System::Windows::Forms::Label();
			this->grpBxTime->SuspendLayout();
			this->panTimeFormat->SuspendLayout();
			this->panDateFormat->SuspendLayout();
			this->SuspendLayout();
			// 
			// grpBxTime
			// 
			this->grpBxTime->Controls->Add(this->panTimeFormat);
			this->grpBxTime->Controls->Add(this->panDateFormat);
			this->grpBxTime->Location = System::Drawing::Point(16, 16);
			this->grpBxTime->Name = "grpBxTime";
			this->grpBxTime->Size = System::Drawing::Size(400, 104);
			this->grpBxTime->TabIndex = 0;
			this->grpBxTime->TabStop = false;
			this->grpBxTime->Text = "Time";
			// 
			// panTimeFormat
			// 
			this->panTimeFormat->Controls->Add(this->comBxTimeItem4);
			this->panTimeFormat->Controls->Add(this->txtBxTimeDel3);
			this->panTimeFormat->Controls->Add(this->comBxTimeItem3);
			this->panTimeFormat->Controls->Add(this->txtBxTimeDel2);
			this->panTimeFormat->Controls->Add(this->comBxTimeItem2);
			this->panTimeFormat->Controls->Add(this->txtBxTimeDel1);
			this->panTimeFormat->Controls->Add(this->comBxTimeItem1);
			this->panTimeFormat->Controls->Add(this->label2);
			this->panTimeFormat->Location = System::Drawing::Point(16, 56);
			this->panTimeFormat->Name = "panTimeFormat";
			this->panTimeFormat->Size = System::Drawing::Size(352, 22);
			this->panTimeFormat->TabIndex = 1;
			// 
			// comBxTimeItem4
			// 
			this->comBxTimeItem4->Dock = System::Windows::Forms::DockStyle::Left;
			this->comBxTimeItem4->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comBxTimeItem4->Items->AddRange(gcnew array< System::Object^ >(5) {"HH","MM","S","mmm","mm"});
			this->comBxTimeItem4->Location = System::Drawing::Point(284, 0);
			this->comBxTimeItem4->Name = "comBxTimeItem4";
			this->comBxTimeItem4->Size = System::Drawing::Size(50, 21);
			this->comBxTimeItem4->TabIndex = 7;
			// 
			// txtBxTimeDel3
			// 
			this->txtBxTimeDel3->Dock = System::Windows::Forms::DockStyle::Left;
			this->txtBxTimeDel3->Location = System::Drawing::Point(264, 0);
			this->txtBxTimeDel3->Name = "txtBxTimeDel3";
			this->txtBxTimeDel3->Size = System::Drawing::Size(20, 20);
			this->txtBxTimeDel3->TabIndex = 6;
			this->txtBxTimeDel3->Text = "";
			this->txtBxTimeDel3->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// comBxTimeItem3
			// 
			this->comBxTimeItem3->Dock = System::Windows::Forms::DockStyle::Left;
			this->comBxTimeItem3->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comBxTimeItem3->Items->AddRange(gcnew array< System::Object^ >(5) {"HH","MM","S","mmm","mm"});
      this->comBxTimeItem3->Location = System::Drawing::Point(214, 0);
			this->comBxTimeItem3->Name = "comBxTimeItem3";
			this->comBxTimeItem3->Size = System::Drawing::Size(50, 21);
			this->comBxTimeItem3->TabIndex = 5;
			// 
			// txtBxTimeDel2
			// 
			this->txtBxTimeDel2->Dock = System::Windows::Forms::DockStyle::Left;
			this->txtBxTimeDel2->Location = System::Drawing::Point(194, 0);
			this->txtBxTimeDel2->Name = "txtBxTimeDel2";
			this->txtBxTimeDel2->Size = System::Drawing::Size(20, 20);
			this->txtBxTimeDel2->TabIndex = 4;
			this->txtBxTimeDel2->Text = "";
			this->txtBxTimeDel2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// comBxTimeItem2
			// 
			this->comBxTimeItem2->Dock = System::Windows::Forms::DockStyle::Left;
			this->comBxTimeItem2->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comBxTimeItem2->Items->AddRange(gcnew array< System::Object^ >(4) {"HH","MM","mmm","mm"});
			this->comBxTimeItem2->Location = System::Drawing::Point(144, 0);
			this->comBxTimeItem2->Name = "comBxTimeItem2";
			this->comBxTimeItem2->Size = System::Drawing::Size(50, 21);
			this->comBxTimeItem2->TabIndex = 3;
			// 
			// txtBxTimeDel1
			// 
			this->txtBxTimeDel1->Dock = System::Windows::Forms::DockStyle::Left;
			this->txtBxTimeDel1->Location = System::Drawing::Point(124, 0);
			this->txtBxTimeDel1->Name = "txtBxTimeDel1";
			this->txtBxTimeDel1->Size = System::Drawing::Size(20, 20);
			this->txtBxTimeDel1->TabIndex = 2;
			this->txtBxTimeDel1->Text = "";
			this->txtBxTimeDel1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// comBxTimeItem1
			// 
			this->comBxTimeItem1->Dock = System::Windows::Forms::DockStyle::Left;
			this->comBxTimeItem1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comBxTimeItem1->Items->AddRange(gcnew array< System::Object^ >(5) {"HH","MM","S","mmm","mm"});
			this->comBxTimeItem1->Location = System::Drawing::Point(72, 0);
			this->comBxTimeItem1->Name = "comBxTimeItem1";
			this->comBxTimeItem1->Size = System::Drawing::Size(52, 21);
			this->comBxTimeItem1->TabIndex = 1;
			// 
			// label2
			// 
			this->label2->Dock = System::Windows::Forms::DockStyle::Left;
			this->label2->Location = System::Drawing::Point(0, 0);
			this->label2->Name = "label2";
			this->label2->Size = System::Drawing::Size(72, 22);
			this->label2->TabIndex = 0;
			this->label2->Text = "Time Format";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// panDateFormat
			// 
			this->panDateFormat->Controls->Add(this->comBxDateItem3);
			this->panDateFormat->Controls->Add(this->txtBxDateDel2);
			this->panDateFormat->Controls->Add(this->comBxDateItem2);
			this->panDateFormat->Controls->Add(this->txtBxDateDel1);
			this->panDateFormat->Controls->Add(this->comBxDateItem1);
			this->panDateFormat->Controls->Add(this->label1);
			this->panDateFormat->Location = System::Drawing::Point(16, 24);
			this->panDateFormat->Name = "panDateFormat";
			this->panDateFormat->Size = System::Drawing::Size(352, 22);
			this->panDateFormat->TabIndex = 0;
			// 
			// comBxDateItem3
			// 
			this->comBxDateItem3->Dock = System::Windows::Forms::DockStyle::Left;
			this->comBxDateItem3->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comBxDateItem3->Items->AddRange(gcnew array< System::Object^ >(4) {"YY","YYYY","MM","DD"});
			this->comBxDateItem3->Location = System::Drawing::Point(212, 0);
			this->comBxDateItem3->Name = "comBxDateItem3";
			this->comBxDateItem3->Size = System::Drawing::Size(50, 21);
			this->comBxDateItem3->TabIndex = 5;
			// 
			// txtBxDateDel2
			// 
			this->txtBxDateDel2->Dock = System::Windows::Forms::DockStyle::Left;
			this->txtBxDateDel2->Location = System::Drawing::Point(192, 0);
			this->txtBxDateDel2->Name = "txtBxDateDel2";
			this->txtBxDateDel2->Size = System::Drawing::Size(20, 20);
			this->txtBxDateDel2->TabIndex = 4;
			this->txtBxDateDel2->Text = "";
			this->txtBxDateDel2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// comBxDateItem2
			// 
			this->comBxDateItem2->Dock = System::Windows::Forms::DockStyle::Left;
			this->comBxDateItem2->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comBxDateItem2->Items->AddRange(gcnew array< System::Object^ >(4) {"YY","YYYY","MM","DD"});
			this->comBxDateItem2->Location = System::Drawing::Point(142, 0);
			this->comBxDateItem2->Name = "comBxDateItem2";
			this->comBxDateItem2->Size = System::Drawing::Size(50, 21);
			this->comBxDateItem2->TabIndex = 3;
			// 
			// txtBxDateDel1
			// 
			this->txtBxDateDel1->Dock = System::Windows::Forms::DockStyle::Left;
			this->txtBxDateDel1->Location = System::Drawing::Point(122, 0);
			this->txtBxDateDel1->Name = "txtBxDateDel1";
			this->txtBxDateDel1->Size = System::Drawing::Size(20, 20);
			this->txtBxDateDel1->TabIndex = 2;
			this->txtBxDateDel1->Text = "";
			this->txtBxDateDel1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// comBxDateItem1
			// 
			this->comBxDateItem1->Dock = System::Windows::Forms::DockStyle::Left;
			this->comBxDateItem1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comBxDateItem1->Items->AddRange(gcnew array< System::Object^ >(4) {"YY","YYYY","MM","DD"});
			this->comBxDateItem1->Location = System::Drawing::Point(72, 0);
			this->comBxDateItem1->Name = "comBxDateItem1";
			this->comBxDateItem1->Size = System::Drawing::Size(50, 21);
			this->comBxDateItem1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->Dock = System::Windows::Forms::DockStyle::Left;
			this->label1->Location = System::Drawing::Point(0, 0);
			this->label1->Name = "label1";
			this->label1->Size = System::Drawing::Size(72, 22);
			this->label1->TabIndex = 0;
			this->label1->Text = "Date Format";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// txtBxLogFileSep
			// 
			this->txtBxLogFileSep->Location = System::Drawing::Point(168, 160);
			this->txtBxLogFileSep->Name = "txtBxLogFileSep";
			this->txtBxLogFileSep->Size = System::Drawing::Size(32, 20);
			this->txtBxLogFileSep->TabIndex = 2;
			this->txtBxLogFileSep->Text = "";
			this->txtBxLogFileSep->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label3
			// 
			this->label3->Location = System::Drawing::Point(16, 160);
			this->label3->Name = "label3";
			this->label3->Size = System::Drawing::Size(144, 16);
			this->label3->TabIndex = 3;
			this->label3->Text = "Separator between Element";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// CLogFileConfigForm
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(520, 312);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->txtBxLogFileSep);
			this->Controls->Add(this->grpBxTime);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = "CLogFileConfigForm";
			this->Text = "CLogFileConfigForm";
			this->grpBxTime->ResumeLayout(false);
			this->panTimeFormat->ResumeLayout(false);
			this->panDateFormat->ResumeLayout(false);
			this->ResumeLayout(false);
		}		
    CTlgInterfaceWrapper^ Interface;
    void updateViewFromConfFile();
    void updateViewDateFormat(String^ date);
    void updateViewTimeFormat(String^ time);
		String^ getDateAsConfFileItem();
		String^ getTimeAsConfFileItem();
    ComboBox^ getNextComBoxDate(ComboBox^ comBx);
		ComboBox^ getNextComBoxTime(ComboBox^ comBx);
		TextBox^ getNextTextBoxTime(TextBox^ txtBx);
	};
}