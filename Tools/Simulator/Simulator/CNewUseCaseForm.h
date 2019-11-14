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
	/// Zusammenfassung für CNewUseCaseForm
	///
	/// Achtung: Wenn Sie den Namen dieser Klasse ändern, müssen Sie die Eigenschaft
	///          'Ressourcendateiname' für das Compilertool für verwaltete Ressourcen ändern, 
	///          das allen .resx-Dateien zugewiesen ist, von denen diese Klasse abhängt. 
	///          Anderenfalls können die Designer nicht korrekt mit den lokalisierten Ressourcen
	///          arbeiten, die diesem Formular zugewiesen sind.
	/// </summary>
	public ref class CNewUseCaseForm : public System::Windows::Forms::Form
	{
	public: 
		CNewUseCaseForm(void)
		{
			InitializeComponent();
		}
    String^ getUseCaseName();
    array <String^>^ getUseCaseDescription();
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
	private: System::Windows::Forms::Label ^  label2;
  private: System::Windows::Forms::Button ^  buttOk;
  private: System::Windows::Forms::Button ^  buttCancel;
  private: System::Windows::Forms::TextBox ^  txtBxName;
  private: System::Windows::Forms::TextBox ^  txtBxDescr;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container^ components;

		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung. 
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
        this->label1 = gcnew System::Windows::Forms::Label();
        this->txtBxName = gcnew System::Windows::Forms::TextBox();
        this->label2 = gcnew System::Windows::Forms::Label();
        this->txtBxDescr = gcnew System::Windows::Forms::TextBox();
        this->buttOk = gcnew System::Windows::Forms::Button();
        this->buttCancel = gcnew System::Windows::Forms::Button();
        this->SuspendLayout();
        // 
        // label1
        // 
        this->label1->Location = System::Drawing::Point(24, 24);
        this->label1->Name = "label1";
        this->label1->Size = System::Drawing::Size(88, 16);
        this->label1->TabIndex = 0;
        this->label1->Text = "Use Case Name";
        // 
        // txtBxName
        // 
        this->txtBxName->Location = System::Drawing::Point(120, 24);
        this->txtBxName->Name = "txtBxName";
        this->txtBxName->Size = System::Drawing::Size(176, 20);
        this->txtBxName->TabIndex = 1;
        this->txtBxName->Text = "";
        // 
        // label2
        // 
        this->label2->Location = System::Drawing::Point(24, 64);
        this->label2->Name = "label2";
        this->label2->Size = System::Drawing::Size(88, 23);
        this->label2->TabIndex = 2;
        this->label2->Text = "Description";
        // 
        // txtBxDescr
        // 
        this->txtBxDescr->Location = System::Drawing::Point(120, 64);
        this->txtBxDescr->Multiline = true;
        this->txtBxDescr->Name = "txtBxDescr";
        this->txtBxDescr->Size = System::Drawing::Size(176, 40);
        this->txtBxDescr->TabIndex = 3;
        this->txtBxDescr->Text = "";
        // 
        // buttOk
        // 
        this->buttOk->DialogResult = System::Windows::Forms::DialogResult::OK;
        this->buttOk->Location = System::Drawing::Point(96, 128);
        this->buttOk->Name = "buttOk";
        this->buttOk->Size = System::Drawing::Size(64, 23);
        this->buttOk->TabIndex = 4;
        this->buttOk->Text = "OK";
        // 
        // buttCancel
        // 
        this->buttCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
        this->buttCancel->Location = System::Drawing::Point(200, 128);
        this->buttCancel->Name = "buttCancel";
        this->buttCancel->TabIndex = 5;
        this->buttCancel->Text = "Cancel";
        // 
        // CNewUseCaseForm
        // 
        this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
        this->ClientSize = System::Drawing::Size(376, 168);
        this->Controls->Add(this->buttCancel);
        this->Controls->Add(this->buttOk);
        this->Controls->Add(this->txtBxDescr);
        this->Controls->Add(this->label2);
        this->Controls->Add(this->txtBxName);
        this->Controls->Add(this->label1);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
        this->Name = "CNewUseCaseForm";
        this->Text = "New Use Case";
        this->ResumeLayout(false);
    }		
	};
}
