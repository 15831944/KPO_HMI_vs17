#pragma once

//------------------------------------------------------------------
#include "CTlgInterfaceWrapper.h"
#include "CXmlInterConfigReader.h"
#include "CXmlInterConfigWriter.h"
#include "CAppSetting.h"
//------------------------------------------------------------------

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace simulator
{
	/// <summary> 
	/// Summary for CTlgTranspConfigForm
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CTlgTranspConfigForm : public System::Windows::Forms::Form
	{
	public: 
		CTlgTranspConfigForm(void)
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

    private: System::Windows::Forms::GroupBox ^  groupBox1;
    private: System::Windows::Forms::Label ^  label1;
    private: System::Windows::Forms::Label ^  label2;
	  private: System::Windows::Forms::CheckBox ^  checkBxSwopping;
	  private: System::Windows::Forms::ComboBox ^  comBxPaddDir;
	  private: System::Windows::Forms::TextBox ^  txtBxPaddStr;
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
			this->checkBxSwopping = gcnew System::Windows::Forms::CheckBox();
			this->groupBox1 = gcnew System::Windows::Forms::GroupBox();
			this->label2 = gcnew System::Windows::Forms::Label();
			this->txtBxPaddStr = gcnew System::Windows::Forms::TextBox();
			this->label1 = gcnew System::Windows::Forms::Label();
			this->comBxPaddDir = gcnew System::Windows::Forms::ComboBox();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// checkBxSwopping
			// 
			this->checkBxSwopping->Location = System::Drawing::Point(24, 32);
			this->checkBxSwopping->Name = "checkBxSwopping";
			this->checkBxSwopping->TabIndex = 0;
			this->checkBxSwopping->Text = "Byte Swaping";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->txtBxPaddStr);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->comBxPaddDir);
			this->groupBox1->Location = System::Drawing::Point(160, 32);
			this->groupBox1->Name = "groupBox1";
			this->groupBox1->Size = System::Drawing::Size(200, 120);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = "Padding";
			// 
			// label2
			// 
			this->label2->Location = System::Drawing::Point(104, 64);
			this->label2->Name = "label2";
			this->label2->Size = System::Drawing::Size(80, 23);
			this->label2->TabIndex = 3;
			this->label2->Text = "Padding String";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// txtBxPaddStr
			// 
			this->txtBxPaddStr->Location = System::Drawing::Point(16, 64);
			this->txtBxPaddStr->Name = "txtBxPaddStr";
			this->txtBxPaddStr->Size = System::Drawing::Size(48, 20);
			this->txtBxPaddStr->TabIndex = 2;
			this->txtBxPaddStr->Text = "";
			// 
			// label1
			// 
			this->label1->Location = System::Drawing::Point(104, 24);
			this->label1->Name = "label1";
			this->label1->Size = System::Drawing::Size(72, 23);
			this->label1->TabIndex = 1;
			this->label1->Text = "Padding";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// comBxPaddDir
			// 
			this->comBxPaddDir->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comBxPaddDir->Items->AddRange(gcnew array< System::Object^ >(2) {"Left","Right"});
			this->comBxPaddDir->Location = System::Drawing::Point(16, 24);
			this->comBxPaddDir->Name = "comBxPaddDir";
			this->comBxPaddDir->Size = System::Drawing::Size(80, 21);
			this->comBxPaddDir->TabIndex = 0;
			// 
			// CTlgTranspConfigForm
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(432, 273);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->checkBxSwopping);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = "CTlgTranspConfigForm";
			this->Text = "CTlgTranspConfigForm";
			this->groupBox1->ResumeLayout(false);
			this->ResumeLayout(false);

		}		

		CTlgInterfaceWrapper^ Interface;
		void updateViewFromConfFile();
	};
}