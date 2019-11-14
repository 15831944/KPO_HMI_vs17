#pragma once
#include "IBASConnection.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Collections::Generic;


namespace Meltshop {

	/// <summary>
	/// Summary for DlgSelectConnection
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class DlgSelectConnection : public System::Windows::Forms::Form
	{
  private:
    Dictionary<String^, IBASConnection^>^ connections;

  private:
    void updateConnectionsList()
    {
      for each (String^ name in connections->Keys)
        listBox1->Items->Add(name);

			//sankar 
			if ( listBox1->Items->Count > 0)
				listBox1->SelectedIndex = 0;
						
    }
  private: System::Windows::Forms::Label^  label1;

  private: String^ context;

	public:
		DlgSelectConnection(String^ _context, Dictionary<String^, IBASConnection^>^ connDict)
		{
      connections = connDict;
      context = _context;

			InitializeComponent();

      updateConnectionsList();      
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DlgSelectConnection()
		{
			if (components)
			{
				delete components;
			}
		}
  private: System::Windows::Forms::ListBox^  listBox1;
  private: System::Windows::Forms::GroupBox^  groupBox1;
  private: System::Windows::Forms::Button^  button3;
  private: System::Windows::Forms::TextBox^  textBox1;
  private: System::Windows::Forms::Button^  button1;
  private: System::Windows::Forms::Button^  button2;
  private: System::Windows::Forms::Panel^  panel1;
  public: IBASConnection^ SelectedConnection;
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
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// listBox1
			// 
			this->listBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(0, 40);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(292, 233);
			this->listBox1->TabIndex = 0;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->button3);
			this->groupBox1->Controls->Add(this->textBox1);
			this->groupBox1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->groupBox1->Location = System::Drawing::Point(0, 190);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(292, 48);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"new Connection";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(226, 17);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(60, 23);
			this->button3->TabIndex = 1;
			this->button3->Text = L"add";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &DlgSelectConnection::button3_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(6, 19);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(214, 20);
			this->textBox1->TabIndex = 0;
			// 
			// button1
			// 
			//this->button1->DialogResult = System::Windows::Forms::DialogResult::OK; //Sankar
			this->button1->DialogResult = System::Windows::Forms::DialogResult::None;
			this->button1->Location = System::Drawing::Point(33, 9);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"select";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &DlgSelectConnection::button1_Click);
			// 
			// button2
			// 
			this->button2->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button2->Location = System::Drawing::Point(173, 9);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 3;
			this->button2->Text = L"cancel";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->button2);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel1->Location = System::Drawing::Point(0, 238);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(292, 35);
			this->panel1->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->Dock = System::Windows::Forms::DockStyle::Top;
			this->label1->Location = System::Drawing::Point(0, 0);
			this->label1->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(292, 40);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Select a connection:\r\ne.g. fb or EAF_1 or EAF_2";
			// 
			// DlgSelectConnection
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 273);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->label1);
			this->Name = L"DlgSelectConnection";
			this->Text = L"select a connection";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->ResumeLayout(false);

            
		}
#pragma endregion
  private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
						 
             IBASConnection^ newConn = gcnew IBASConnection();
             newConn->initialize(context, "iBAS_SERVER_FRAME", textBox1->Text);
             connections->Add(textBox1->Text, newConn);
             updateConnectionsList();
           }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
					 
					 // sankar					 
          if ( listBox1->SelectedIndices->Count == 0 || listBox1->SelectedItems ->Count == 0)
          {
              MessageBox::Show("Please select the item from the list");
              return;
          }
					else
					{
					 this->button1->DialogResult = System::Windows::Forms::DialogResult::OK;
					}

           System::String^ test = listBox1->SelectedItem->ToString();
           SelectedConnection = connections[listBox1->SelectedItem->ToString()];
         }
};
}
