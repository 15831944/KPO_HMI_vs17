#pragma once

//----------------------------CBofform.h-------------------------------------
//Zweck:realisieren,dass Telegramm "Bof211" zu senden.
//---------------------------------------------------------------------------

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#include "./CTlgInterfaceWrapper.h"
#include "./CInterConnection.h"
#include "./CStdConverter.h"
#include "./CTlgContainerWrapper.h"
#include "./CInterReceiverManager.h"
#include "./CInterBaseManager.h"
#include "./CInterConfigWrapper.h"
#include "./CBofProzessForm.h"
#include "./CBofAnimationForm.h"
#include "./CBofTlgViewForm.h"



namespace simulator
{
	/// <summary> 
	/// Summary for CBofForm
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CBofForm : public System::Windows::Forms::Form
	{
	public: 
		//Construktor
		CBofForm(void)
    {
      InitializeComponent();
      initviewComponent();
    }
    
		//...set and get Interface des Telegramms
		void setTlgInterface(CTlgInterfaceWrapper ^W);
        CTlgInterfaceWrapper^ getTlgInterface();
		//...set and get InterConnection als Receiver
		void setInterConnectionReceive(CInterConnection ^R);
        CInterConnection^ getInterConnectionReceive();
		//...set and get InterConnection als Sender
		void setInterConnectionSenden(CInterConnection ^I);
        CInterConnection^ getInterConnectionSenden();
    
    //...set Array der Listboxen
	protected: 
		//void Dispose(Boolean disposing)
		//{
		//	if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}

  
  private: System::Windows::Forms::Splitter ^  splitter1;
  private: System::Windows::Forms::Panel ^  panel2;
  private: System::Windows::Forms::Splitter ^  splitter2;
  private: System::Windows::Forms::Splitter ^  splitter3;

  private: System::Windows::Forms::Panel ^  BofProzesspanel;
  private: System::Windows::Forms::Panel ^  BofTlgViewpanel;
  private: System::Windows::Forms::Panel ^  BofAnimationpanel;

  private: System::ComponentModel::IContainer ^  components;

  private: System::Void OnLoad(System::Object ^  sender, System::EventArgs ^  e);
           

   private:
		 /// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
    //private Attribut fuer Telegramm
	  CTlgInterfaceWrapper ^C_Wr;            //Objekt des Class TlgInterfaceWrapper von Wrapper
		CInterConnection ^C_Receiver;          //Objekt des Class CInterConnection von Socket
		CInterConnection ^C_Sender;            //Objekt des Class CInterConnection von Socket
	  CTlgWrapper ^C_tlgWr;                  //Objeke des Class TlgWrapper von Wrapper
    CStdConverter ^C_Std;                 //Objekt des Class CStdConverte
    CTlgContainerWrapper ^C_TlgContainer;  //Objekt des Class CTlgContainerWrapper;
    CInterReceiverManager ^C_interReceiverMan;
    
    CBofProzessForm^ BofProzessForm;
    CBofTlgViewForm^ BofTlgViewForm;
    CBofAnimationForm^ BofAnimationForm;

		void InitializeComponent(void)
		{   
      this->BofProzesspanel = gcnew System::Windows::Forms::Panel();
      this->splitter1 = gcnew System::Windows::Forms::Splitter();
      this->panel2 = gcnew System::Windows::Forms::Panel();
      this->splitter2 = gcnew System::Windows::Forms::Splitter();
      this->BofTlgViewpanel = gcnew System::Windows::Forms::Panel();
      this->splitter3 = gcnew System::Windows::Forms::Splitter();
      this->BofAnimationpanel = gcnew System::Windows::Forms::Panel();
      this->SuspendLayout();
      // 
      // BofProzesspanel
      // 
      this->BofProzesspanel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->BofProzesspanel->Dock = System::Windows::Forms::DockStyle::Left;
      this->BofProzesspanel->Location = System::Drawing::Point(0, 0);
      this->BofProzesspanel->Name = "BofProzesspanel";
      this->BofProzesspanel->Size = System::Drawing::Size(216, 380);
      this->BofProzesspanel->TabIndex = 0;
      // 
      // splitter1
      // 
      this->splitter1->Location = System::Drawing::Point(216, 0);
      this->splitter1->Name = "splitter1";
      this->splitter1->Size = System::Drawing::Size(3, 380);
      this->splitter1->TabIndex = 3;
      this->splitter1->TabStop = false;
      // 
      // panel2
      // 
      this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->panel2->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->panel2->Location = System::Drawing::Point(219, 260);
      this->panel2->Name = "panel2";
      this->panel2->Size = System::Drawing::Size(389, 120);
      this->panel2->TabIndex = 4;
      // 
      // splitter2
      // 
      this->splitter2->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->splitter2->Location = System::Drawing::Point(219, 257);
      this->splitter2->Name = "splitter2";
      this->splitter2->Size = System::Drawing::Size(389, 3);
      this->splitter2->TabIndex = 5;
      this->splitter2->TabStop = false;
      // 
      // BofTlgViewpanel
      // 
      this->BofTlgViewpanel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->BofTlgViewpanel->Dock = System::Windows::Forms::DockStyle::Left;
      this->BofTlgViewpanel->Location = System::Drawing::Point(219, 0);
      this->BofTlgViewpanel->Name = "BofTlgViewpanel";
      this->BofTlgViewpanel->Size = System::Drawing::Size(309, 257);
      this->BofTlgViewpanel->TabIndex = 6;
      // 
      // splitter3
      // 
      this->splitter3->Location = System::Drawing::Point(528, 0);
      this->splitter3->Name = "splitter3";
      this->splitter3->Size = System::Drawing::Size(3, 257);
      this->splitter3->TabIndex = 7;
      this->splitter3->TabStop = false;
      // 
      // BofAnimationpanel
      // 
      this->BofAnimationpanel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->BofAnimationpanel->Dock = System::Windows::Forms::DockStyle::Fill;
      this->BofAnimationpanel->Location = System::Drawing::Point(531, 0);
      this->BofAnimationpanel->Name = "BofAnimationpanel";
      this->BofAnimationpanel->Size = System::Drawing::Size(77, 257);
      this->BofAnimationpanel->TabIndex = 9;
      // 
      // CBofForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(608, 380);
      this->Controls->Add(this->BofAnimationpanel);
      this->Controls->Add(this->splitter3);
      this->Controls->Add(this->BofTlgViewpanel);
      this->Controls->Add(this->splitter2);
      this->Controls->Add(this->panel2);
      this->Controls->Add(this->splitter1);
      this->Controls->Add(this->BofProzesspanel);
      this->KeyPreview = true;
      this->Name = "CBofForm";
      this->Text = "CBofForm";
      this->TopMost = true;
      this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &CBofForm::OnLoad);
      this->ResumeLayout(false);

    }	
        
    void initviewComponent();
    
    void updateTlgView(CItemWrapper^ wrp);
};
}
