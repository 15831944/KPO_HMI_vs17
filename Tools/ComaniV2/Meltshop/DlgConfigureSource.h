#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace Meltshop {

	/// <summary>
	/// Summary for DlgConfigureSource
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class DlgConfigureSource : public System::Windows::Forms::Form
	{
	public:
		DlgConfigureSource(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DlgConfigureSource()
		{
			if (components)
			{
				delete components;
			}
		}
  private: System::Windows::Forms::Label^  label1;
  private: System::Windows::Forms::Button^  btnCancel;


  private: System::Windows::Forms::Button^  btnOK;


  private: System::Windows::Forms::TextBox^  tbContext;


  protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->btnCancel = (gcnew System::Windows::Forms::Button());
      this->btnOK = (gcnew System::Windows::Forms::Button());
      this->tbContext = (gcnew System::Windows::Forms::TextBox());
      this->SuspendLayout();
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->Location = System::Drawing::Point(14, 14);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(46, 13);
      this->label1->TabIndex = 0;
      this->label1->Text = L"Context:";
      // 
      // btnCancel
      // 
      this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
      this->btnCancel->Location = System::Drawing::Point(159, 41);
      this->btnCancel->Name = L"btnCancel";
      this->btnCancel->Size = System::Drawing::Size(75, 23);
      this->btnCancel->TabIndex = 2;
      this->btnCancel->Text = L"cancel";
      this->btnCancel->UseVisualStyleBackColor = true;
      // 
      // btnOK
      // 
      this->btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->btnOK->Location = System::Drawing::Point(40, 41);
      this->btnOK->Name = L"btnOK";
      this->btnOK->Size = System::Drawing::Size(75, 23);
      this->btnOK->TabIndex = 3;
      this->btnOK->Text = L"OK";
      this->btnOK->UseVisualStyleBackColor = true;
      this->btnOK->Click += gcnew System::EventHandler(this, &DlgConfigureSource::btnOK_Click);
      // 
      // tbContext
      // 
      this->tbContext->Location = System::Drawing::Point(121, 11);
      this->tbContext->Name = L"tbContext";
      this->tbContext->Size = System::Drawing::Size(140, 20);
      this->tbContext->TabIndex = 4;
      this->tbContext->Text = L"JSW-SMS-3";
      // 
      // DlgConfigureSource
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(273, 74);
      this->Controls->Add(this->tbContext);
      this->Controls->Add(this->btnOK);
      this->Controls->Add(this->btnCancel);
      this->Controls->Add(this->label1);
      this->Name = L"DlgConfigureSource";
      this->Text = L"Select context";
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion

    public: String^ ContextName;
  private: System::Void btnOK_Click(System::Object^  sender, System::EventArgs^  e) {
             ContextName = tbContext->Text;
           }
};
}
