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
	/// Summary for CBofAnimationForm
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CBofAnimationForm : public System::Windows::Forms::Form
	{
	public: 
		CBofAnimationForm(void)
		{
			InitializeComponent();
		}
     
    CBofAnimationForm(Panel^ parent);

	protected: 
		//void Dispose(Boolean disposing)
		//{
		//	if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}

  private: System::Windows::Forms::Button ^  startbutton;
  private: System::Windows::Forms::Button ^  stopbutton;
  private: System::Windows::Forms::Button ^  weiterbutton;
  private: System::Windows::Forms::TextBox ^  textBox14;
  private: System::Windows::Forms::Panel ^  panel1;
  private: System::Windows::Forms::Panel ^  panel2;
  private: System::Windows::Forms::PictureBox ^  pictureBox1;

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
			System::Resources::ResourceManager ^  resources = gcnew System::Resources::ResourceManager((simulator::CBofAnimationForm::typeid));
      this->panel1 = gcnew System::Windows::Forms::Panel();
      this->startbutton = gcnew System::Windows::Forms::Button();
      this->stopbutton = gcnew System::Windows::Forms::Button();
      this->weiterbutton = gcnew System::Windows::Forms::Button();
      this->textBox14 = gcnew System::Windows::Forms::TextBox();
      this->panel2 = gcnew System::Windows::Forms::Panel();
      this->pictureBox1 = gcnew System::Windows::Forms::PictureBox();
      this->panel1->SuspendLayout();
      this->panel2->SuspendLayout();
      this->SuspendLayout();
      // 
      // panel1
      // 
      this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->panel1->Controls->Add(this->startbutton);
      this->panel1->Controls->Add(this->stopbutton);
      this->panel1->Controls->Add(this->weiterbutton);
      this->panel1->Controls->Add(this->textBox14);
      this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
      this->panel1->Location = System::Drawing::Point(0, 0);
      this->panel1->Name = "panel1";
      this->panel1->Size = System::Drawing::Size(464, 40);
      this->panel1->TabIndex = 6;
      // 
      // startbutton
      // 
      this->startbutton->Location = System::Drawing::Point(8, 8);
      this->startbutton->Name = "startbutton";
      this->startbutton->TabIndex = 7;
      this->startbutton->Text = "START";
      // 
      // stopbutton
      // 
      this->stopbutton->Image = (safe_cast<System::Drawing::Image ^  >(resources->GetObject("stopbutton.Image")));
      this->stopbutton->Location = System::Drawing::Point(88, 8);
      this->stopbutton->Name = "stopbutton";
      this->stopbutton->Size = System::Drawing::Size(24, 23);
      this->stopbutton->TabIndex = 5;
      // 
      // weiterbutton
      // 
      this->weiterbutton->Image = (safe_cast<System::Drawing::Image ^  >(resources->GetObject("weiterbutton.Image")));
      this->weiterbutton->Location = System::Drawing::Point(120, 8);
      this->weiterbutton->Name = "weiterbutton";
      this->weiterbutton->Size = System::Drawing::Size(24, 23);
      this->weiterbutton->TabIndex = 8;
      // 
      // textBox14
      // 
      this->textBox14->Location = System::Drawing::Point(152, 8);
      this->textBox14->Name = "textBox14";
      this->textBox14->Size = System::Drawing::Size(196, 20);
      this->textBox14->TabIndex = 6;
      this->textBox14->Text = "";
      // 
      // panel2
      // 
      this->panel2->Controls->Add(this->pictureBox1);
      this->panel2->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panel2->Location = System::Drawing::Point(0, 40);
      this->panel2->Name = "panel2";
      this->panel2->Size = System::Drawing::Size(464, 340);
      this->panel2->TabIndex = 7;
      // 
      // pictureBox1
      // 
      this->pictureBox1->BackColor = System::Drawing::SystemColors::HighlightText;
      this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
      this->pictureBox1->Image = (safe_cast<System::Drawing::Image ^  >(resources->GetObject("pictureBox1.Image")));
      this->pictureBox1->Location = System::Drawing::Point(0, 0);
      this->pictureBox1->Name = "pictureBox1";
      this->pictureBox1->Size = System::Drawing::Size(464, 340);
      this->pictureBox1->TabIndex = 0;
      this->pictureBox1->TabStop = false;
      // 
      // CBofAnimationForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(464, 380);
      this->Controls->Add(this->panel2);
      this->Controls->Add(this->panel1);
      this->Name = "CBofAnimationForm";
      this->Text = "CBofAnimationForm";
      this->panel1->ResumeLayout(false);
      this->panel2->ResumeLayout(false);
      this->ResumeLayout(false);

    }		
	};
}