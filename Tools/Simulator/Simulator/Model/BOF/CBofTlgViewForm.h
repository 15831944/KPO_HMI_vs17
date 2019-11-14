#pragma once

#include "CTlgWrapper.h"
#include "CInterConfigWrapper.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

delegate void ShowTlgEvent();
//delegate void TelElemEditEve();

namespace simulator
{
	/// <summary> 
	/// Summary for CBofTlgViewForm
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CBofTlgViewForm : public System::Windows::Forms::Form
	{
	public: 
		CBofTlgViewForm(void)
		{
			InitializeComponent();
      panCon = nullptr;
      showtlgevent = nullptr;
      LenChange = false;
      TlgLenTxtBx=nullptr;
		}
    
    CBofTlgViewForm(Panel^ parent);
    void showTlg(CItemWrapper^ tlg);

	protected: 
		//void Dispose(Boolean disposing)
		//{
		//	if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}
  private: System::Windows::Forms::Panel ^  panelinfo;


  private: System::Windows::Forms::Panel ^  panelbutton;
  private: System::Windows::Forms::Button ^  button1;
  private: System::Windows::Forms::Button ^  button2;
  private: System::Windows::Forms::Button ^  button3;
  private: System::Windows::Forms::Panel ^  panelbody;
  private: System::Windows::Forms::Label ^  labelTlgName;
  private: System::Windows::Forms::Label ^  labelTlgDescr;
  

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;
    
    System::Void OnEnterTextBox(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnLeaveTextBox(System::Object ^  sender, System::EventArgs ^  e);

    CItemWrapper^ Tlg;
    String^ TlgId;
	  String^ TlgElemId;
	  String^ TlgLenId;
	  String^ TlgIdValue;
	  int LenIdModus;
    bool LenChange;
    TextBox^ TlgLenTxtBx;
    Panel^ panCon;
    bool UpdateFlag;
    bool NavModi;
    int ActTextBox;
    ArrayList^  TxtBoxArray;
 
    //delegate  objekt
    ShowTlgEvent^ showtlgevent;
   // TelElemEditEve^ telelemediteve;

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      this->panelinfo = gcnew System::Windows::Forms::Panel();
      this->labelTlgDescr = gcnew System::Windows::Forms::Label();
      this->labelTlgName = gcnew System::Windows::Forms::Label();
      this->panelbutton = gcnew System::Windows::Forms::Panel();
      this->button3 = gcnew System::Windows::Forms::Button();
      this->button2 = gcnew System::Windows::Forms::Button();
      this->button1 = gcnew System::Windows::Forms::Button();
      this->panelbody = gcnew System::Windows::Forms::Panel();
      this->panelinfo->SuspendLayout();
      this->panelbutton->SuspendLayout();
      this->SuspendLayout();
      // 
      // panelinfo
      // 
      this->panelinfo->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->panelinfo->Controls->Add(this->labelTlgDescr);
      this->panelinfo->Controls->Add(this->labelTlgName);
      this->panelinfo->Dock = System::Windows::Forms::DockStyle::Top;
      this->panelinfo->Location = System::Drawing::Point(0, 0);
      this->panelinfo->Name = "panelinfo";
      this->panelinfo->Size = System::Drawing::Size(292, 48);
      this->panelinfo->TabIndex = 0;
      // 
      // labelTlgDescr
      // 
      this->labelTlgDescr->Location = System::Drawing::Point(136, 8);
      this->labelTlgDescr->Name = "labelTlgDescr";
      this->labelTlgDescr->Size = System::Drawing::Size(144, 23);
      this->labelTlgDescr->TabIndex = 1;
      // 
      // labelTlgName
      // 
      this->labelTlgName->Location = System::Drawing::Point(8, 8);
      this->labelTlgName->Name = "labelTlgName";
      this->labelTlgName->TabIndex = 0;
      // 
      // panelbutton
      // 
      this->panelbutton->Controls->Add(this->button3);
      this->panelbutton->Controls->Add(this->button2);
      this->panelbutton->Controls->Add(this->button1);
      this->panelbutton->Dock = System::Windows::Forms::DockStyle::Top;
      this->panelbutton->Location = System::Drawing::Point(0, 48);
      this->panelbutton->Name = "panelbutton";
      this->panelbutton->Size = System::Drawing::Size(292, 24);
      this->panelbutton->TabIndex = 1;
      // 
      // button3
      // 
      this->button3->Location = System::Drawing::Point(171, 0);
      this->button3->Name = "button3";
      this->button3->Size = System::Drawing::Size(128, 23);
      this->button3->TabIndex = 2;
      this->button3->Text = "Unit";
      // 
      // button2
      // 
      this->button2->Location = System::Drawing::Point(96, 0);
      this->button2->Name = "button2";
      this->button2->TabIndex = 1;
      this->button2->Text = "Value";
      // 
      // button1
      // 
      this->button1->Location = System::Drawing::Point(0, 0);
      this->button1->Name = "button1";
      this->button1->Size = System::Drawing::Size(96, 23);
      this->button1->TabIndex = 0;
      this->button1->Text = "Element";
      // 
      // panelbody
      // 
      this->panelbody->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panelbody->Location = System::Drawing::Point(0, 72);
      this->panelbody->Name = "panelbody";
      this->panelbody->Size = System::Drawing::Size(292, 236);
      this->panelbody->TabIndex = 2;
      // 
      // CBofTlgViewForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(292, 308);
      this->Controls->Add(this->panelbody);
      this->Controls->Add(this->panelbutton);
      this->Controls->Add(this->panelinfo);
      this->Name = "CBofTlgViewForm";
      this->Text = "CBofTlgViewForm";
      this->panelinfo->ResumeLayout(false);
      this->panelbutton->ResumeLayout(false);
      this->ResumeLayout(false);

    }		

    
    void addnewpanel();
    void addTlgelement(String^& Name,String^& Val,String^& Unit,Panel^ panElem);
	};
}