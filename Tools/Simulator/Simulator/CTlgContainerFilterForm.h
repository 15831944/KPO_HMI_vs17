#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace simulator
{  
  /// <summary> 
	/// Summary for CTlgContainerFilterForm
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CTlgContainerFilterForm : public System::Windows::Forms::Form
	{
  public: delegate void DelRegExprTyp(array <String^>^ expr); 
  
  public: 
		CTlgContainerFilterForm(array <String^>^ regExp)
		{
			InitializeComponent();
			RegExpr=nullptr;
      mMultiFilterForm = gcnew SimGuiDialogs::CMultiFilterForm(this->panCenterView,regExp);
      mMultiFilterForm->Show();
      //this->LastHeightCenterPanel = this->panCenterView->Height;
      //this->panCenterView->Resize += gcnew System::EventHandler(this, &CTlgContainerFilterForm::panCenterView_Resize);
      initToolTips();
		}
    void setRegExprEvent(DelRegExprTyp^ DelExp);
	
  protected: 
		//void Dispose(Boolean disposing)
		//{
		//	if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}
	private: System::Windows::Forms::Label ^  label1;
	private: System::Windows::Forms::Button ^  button1;
  private: System::Windows::Forms::Panel^  panBottomView;
  private: System::Windows::Forms::Splitter^  splitter1;
  private: System::Windows::Forms::Panel^  panTopView;
  private: System::Windows::Forms::Panel^  panCenterView;
  private: System::Windows::Forms::Button^  butClear;
  private: System::Windows::Forms::TextBox^  textBox1;
  private: System::Windows::Forms::Button^  butClose;

  private: System::Void panCenterView_Resize(System::Object^  sender, System::EventArgs^  e);
  private: System::Void butClear_Click(System::Object^  sender, System::EventArgs^  e); 
  private: System::Void butClose_Click(System::Object^  sender, System::EventArgs^  e);
  private: System::Void OnOkButtonClick(System::Object ^  sender, System::EventArgs ^  e);

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
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->button1 = (gcnew System::Windows::Forms::Button());
      this->panBottomView = (gcnew System::Windows::Forms::Panel());
      this->butClose = (gcnew System::Windows::Forms::Button());
      this->butClear = (gcnew System::Windows::Forms::Button());
      this->splitter1 = (gcnew System::Windows::Forms::Splitter());
      this->panTopView = (gcnew System::Windows::Forms::Panel());
      this->textBox1 = (gcnew System::Windows::Forms::TextBox());
      this->panCenterView = (gcnew System::Windows::Forms::Panel());
      this->panBottomView->SuspendLayout();
      this->panTopView->SuspendLayout();
      this->SuspendLayout();
      // 
      // label1
      // 
      this->label1->Location = System::Drawing::Point(12, 9);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(48, 16);
      this->label1->TabIndex = 0;
      this->label1->Text = L"Filter by:";
      this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      this->label1->Visible = false;
      // 
      // button1
      // 
      this->button1->Location = System::Drawing::Point(300, 4);
      this->button1->Name = L"button1";
      this->button1->Size = System::Drawing::Size(48, 23);
      this->button1->TabIndex = 2;
      this->button1->Text = L"Apply";
      this->button1->Click += gcnew System::EventHandler(this, &CTlgContainerFilterForm::OnOkButtonClick);
      // 
      // panBottomView
      // 
      this->panBottomView->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->panBottomView->Controls->Add(this->butClose);
      this->panBottomView->Controls->Add(this->butClear);
      this->panBottomView->Controls->Add(this->button1);
      this->panBottomView->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->panBottomView->Location = System::Drawing::Point(0, 188);
      this->panBottomView->Name = L"panBottomView";
      this->panBottomView->Size = System::Drawing::Size(409, 32);
      this->panBottomView->TabIndex = 3;
      // 
      // butClose
      // 
      this->butClose->Location = System::Drawing::Point(354, 4);
      this->butClose->Name = L"butClose";
      this->butClose->Size = System::Drawing::Size(48, 23);
      this->butClose->TabIndex = 4;
      this->butClose->Text = L"Close";
      this->butClose->UseVisualStyleBackColor = true;
      this->butClose->Click += gcnew System::EventHandler(this, &CTlgContainerFilterForm::butClose_Click);
      // 
      // butClear
      // 
      this->butClear->Location = System::Drawing::Point(246, 4);
      this->butClear->Name = L"butClear";
      this->butClear->Size = System::Drawing::Size(48, 23);
      this->butClear->TabIndex = 3;
      this->butClear->Text = L"Clear";
      this->butClear->UseVisualStyleBackColor = true;
      this->butClear->Click += gcnew System::EventHandler(this, &CTlgContainerFilterForm::butClear_Click);
      // 
      // splitter1
      // 
      this->splitter1->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->splitter1->Location = System::Drawing::Point(0, 185);
      this->splitter1->Name = L"splitter1";
      this->splitter1->Size = System::Drawing::Size(409, 3);
      this->splitter1->TabIndex = 4;
      this->splitter1->TabStop = false;
      // 
      // panTopView
      // 
      this->panTopView->Controls->Add(this->label1);
      this->panTopView->Controls->Add(this->textBox1);
      this->panTopView->Dock = System::Windows::Forms::DockStyle::Top;
      this->panTopView->Location = System::Drawing::Point(0, 0);
      this->panTopView->Name = L"panTopView";
      this->panTopView->Size = System::Drawing::Size(409, 15);
      this->panTopView->TabIndex = 5;
      // 
      // textBox1
      // 
      this->textBox1->Location = System::Drawing::Point(170, 5);
      this->textBox1->Name = L"textBox1";
      this->textBox1->Size = System::Drawing::Size(100, 20);
      this->textBox1->TabIndex = 1;
      this->textBox1->Text = L"*";
      this->textBox1->Visible = false;
      // 
      // panCenterView
      // 
      this->panCenterView->AutoScroll = true;
      this->panCenterView->AutoSize = true;
      this->panCenterView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panCenterView->Location = System::Drawing::Point(0, 15);
      this->panCenterView->Name = L"panCenterView";
      this->panCenterView->Size = System::Drawing::Size(409, 170);
      this->panCenterView->TabIndex = 6;
      // 
      // CTlgContainerFilterForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->AutoSize = true;
      this->ClientSize = System::Drawing::Size(409, 220);
      this->Controls->Add(this->panCenterView);
      this->Controls->Add(this->panTopView);
      this->Controls->Add(this->splitter1);
      this->Controls->Add(this->panBottomView);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
      this->Name = L"CTlgContainerFilterForm";
      this->Text = L"Filter of Telegrams";
      this->panBottomView->ResumeLayout(false);
      this->panTopView->ResumeLayout(false);
      this->panTopView->PerformLayout();
      this->ResumeLayout(false);
      this->PerformLayout();

    }		
		
		DelRegExprTyp^ RegExpr;
    int LastHeightCenterPanel;
    SimGuiDialogs::CMultiFilterForm^ mMultiFilterForm;
    void initToolTips();
};
}