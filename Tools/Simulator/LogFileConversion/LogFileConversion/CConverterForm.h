#pragma once

//---------------------------------------------------------------------
#include "CInterAssignment.h"
#include "CTlgLogFileContainer.h"
//---------------------------------------------------------------------

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace LogFileConversion
{
	/// <summary> 
	/// Summary for CConverterForm
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CConverterForm : public System::Windows::Forms::Form
	{
	public: 
		CConverterForm(void)
		{
			InitializeComponent();
            InterAssignment = nullptr;
            LogFileContainer = gcnew CTlgLogFileContainer();
		}
        void setInterfaceAssignment(CInterAssignment^ interAss);
	protected: 
		//void Dispose(Boolean disposing)
		//{
		//	if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}
    private: System::Windows::Forms::Panel ^  panel1;
    private: System::Windows::Forms::Panel ^  panel2;
    private: System::Windows::Forms::Panel ^  panel3;
    private: System::Windows::Forms::Button ^  buttOpenLogFile;
    private: System::Windows::Forms::OpenFileDialog ^  openFileDialog;
    private: System::Windows::Forms::Button ^  buttSaveLogFile;
    private: System::Windows::Forms::SaveFileDialog ^  saveFileDialog;
    private: System::Windows::Forms::RichTextBox ^  richTextBox;

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
            this->panel1 = gcnew System::Windows::Forms::Panel();
            this->buttSaveLogFile = gcnew System::Windows::Forms::Button();
            this->buttOpenLogFile = gcnew System::Windows::Forms::Button();
            this->panel2 = gcnew System::Windows::Forms::Panel();
            this->panel3 = gcnew System::Windows::Forms::Panel();
            this->richTextBox = gcnew System::Windows::Forms::RichTextBox();
            this->openFileDialog = gcnew System::Windows::Forms::OpenFileDialog();
            this->saveFileDialog = gcnew System::Windows::Forms::SaveFileDialog();
            this->panel1->SuspendLayout();
            this->panel3->SuspendLayout();
            this->SuspendLayout();
            // 
            // panel1
            // 
            this->panel1->Controls->Add(this->buttSaveLogFile);
            this->panel1->Controls->Add(this->buttOpenLogFile);
            this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
            this->panel1->Location = System::Drawing::Point(0, 241);
            this->panel1->Name = "panel1";
            this->panel1->Size = System::Drawing::Size(472, 32);
            this->panel1->TabIndex = 0;
            // 
            // buttSaveLogFile
            // 
            this->buttSaveLogFile->Location = System::Drawing::Point(104, 8);
            this->buttSaveLogFile->Name = "buttSaveLogFile";
            this->buttSaveLogFile->TabIndex = 1;
            this->buttSaveLogFile->Text = "Save";
            this->buttSaveLogFile->Click += gcnew System::EventHandler(this, &CConverterForm::OnButtSaveClick);
            // 
            // buttOpenLogFile
            // 
            this->buttOpenLogFile->Location = System::Drawing::Point(8, 8);
            this->buttOpenLogFile->Name = "buttOpenLogFile";
            this->buttOpenLogFile->TabIndex = 0;
            this->buttOpenLogFile->Text = "Open";
            this->buttOpenLogFile->Click += gcnew System::EventHandler(this, &CConverterForm::OnButtOpenClick);
            // 
            // panel2
            // 
            this->panel2->Dock = System::Windows::Forms::DockStyle::Top;
            this->panel2->Location = System::Drawing::Point(0, 0);
            this->panel2->Name = "panel2";
            this->panel2->Size = System::Drawing::Size(472, 40);
            this->panel2->TabIndex = 1;
            // 
            // panel3
            // 
            this->panel3->Controls->Add(this->richTextBox);
            this->panel3->Dock = System::Windows::Forms::DockStyle::Fill;
            this->panel3->Location = System::Drawing::Point(0, 40);
            this->panel3->Name = "panel3";
            this->panel3->Size = System::Drawing::Size(472, 201);
            this->panel3->TabIndex = 2;
            // 
            // richTextBox
            // 
            this->richTextBox->Dock = System::Windows::Forms::DockStyle::Fill;
            this->richTextBox->Location = System::Drawing::Point(0, 0);
            this->richTextBox->Name = "richTextBox";
            this->richTextBox->Size = System::Drawing::Size(472, 201);
            this->richTextBox->TabIndex = 0;
            this->richTextBox->Text = "";
            // 
            // CConverterForm
            // 
            this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
            this->ClientSize = System::Drawing::Size(472, 273);
            this->Controls->Add(this->panel3);
            this->Controls->Add(this->panel2);
            this->Controls->Add(this->panel1);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
            this->Name = "CConverterForm";
            this->ShowInTaskbar = false;
            this->Text = "CConverterForm";
            this->panel1->ResumeLayout(false);
            this->panel3->ResumeLayout(false);
            this->ResumeLayout(false);

        }		
        System::Void OnButtOpenClick(System::Object ^  sender, System::EventArgs ^  e);
        System::Void OnButtSaveClick(System::Object ^  sender, System::EventArgs ^  e);

        void showConvertedFile(String^ path);
        void showLogFileContainer();

        CInterAssignment^ InterAssignment;
        CTlgLogFileContainer^ LogFileContainer;
        
};
}