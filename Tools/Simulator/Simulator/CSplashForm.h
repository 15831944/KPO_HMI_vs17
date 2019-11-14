#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace simulator {

	/// <summary>
	/// Summary for CSplashForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CSplashForm : public System::Windows::Forms::Form
	{
	public:
		CSplashForm(void)
		{
			InitializeComponent();
		}

  public: void SetText(String^ mess);
  
  private: System::Windows::Forms::Label^  labStaticDesc;
  private: System::Windows::Forms::Label^  labDynamicDesc;
  private: System::Windows::Forms::Label^  label1;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/*~CSplashForm()
		{
			if (components)
			{
				delete components;
			}
		}*/

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(CSplashForm::typeid));
      this->labStaticDesc = (gcnew System::Windows::Forms::Label());
      this->labDynamicDesc = (gcnew System::Windows::Forms::Label());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->SuspendLayout();
      // 
      // labStaticDesc
      // 
      this->labStaticDesc->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->labStaticDesc->Location = System::Drawing::Point(239, 0);
      this->labStaticDesc->Name = L"labStaticDesc";
      this->labStaticDesc->Size = System::Drawing::Size(504, 34);
      this->labStaticDesc->TabIndex = 0;
      this->labStaticDesc->Text = L"Loading simulator ...";
      this->labStaticDesc->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
      // 
      // labDynamicDesc
      // 
      this->labDynamicDesc->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->labDynamicDesc->Location = System::Drawing::Point(236, 40);
      this->labDynamicDesc->Name = L"labDynamicDesc";
      this->labDynamicDesc->Size = System::Drawing::Size(504, 122);
      this->labDynamicDesc->TabIndex = 1;
      this->labDynamicDesc->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
      // 
      // label1
      // 
      this->label1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"label1.Image")));
      this->label1->Location = System::Drawing::Point(2, 14);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(207, 137);
      this->label1->TabIndex = 2;
      // 
      // CSplashForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->BackColor = System::Drawing::SystemColors::HighlightText;
      this->ClientSize = System::Drawing::Size(752, 171);
      this->ControlBox = false;
      this->Controls->Add(this->label1);
      this->Controls->Add(this->labDynamicDesc);
      this->Controls->Add(this->labStaticDesc);
      this->Name = L"CSplashForm";
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
      this->ResumeLayout(false);

    }
#pragma endregion
	};
}
