#pragma once

//----------------------------------------------------------------
#include "CItemWrapper.h"
#include "CInterConfigWrapper.h"

//----------------------------------------------------------------

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace simulator
{
	/// <summary> 
	/// Zusammenfassung für CTlgViewForm
	///
	/// Achtung: Wenn Sie den Namen dieser Klasse ändern, müssen Sie die Eigenschaft
	///          'Ressourcendateiname' für das Compilertool für verwaltete Ressourcen ändern, 
	///          das allen .resx-Dateien zugewiesen ist, von denen diese Klasse abhängt. 
	///          Anderenfalls können die Designer nicht korrekt mit den lokalisierten Ressourcen
	///          arbeiten, die diesem Formular zugewiesen sind.
	/// </summary>
	public ref class CTlgViewForm : public System::Windows::Forms::Form
	{
    public: delegate void UpdateTlgToSzen(CItemWrapper^ wr);
    public: delegate void AddTlgToSzen(CItemWrapper^ wrp,bool modi);
    public: delegate void ErrorMessageDelTyp(String^ mess);
    public: delegate void TelElemEditEventTyp();
    public: delegate void DelShowTlgView();

  public: 
		CTlgViewForm(void)
		{
			InitializeComponent();
			FlagShowModi=0;
			UpdateFlag=true;
			PanFlag = 0;
			panCon=nullptr;
			ErrorMessageDel=nullptr;
      TelElemEditEvent=nullptr;
      LenChange=false;
		}
    CTlgViewForm(Panel^ parent);
		void showTlg(CItemWrapper^ tlg);
    void setTelElemEditEvent(TelElemEditEventTyp^ editEvent);
    bool isUpdate();
    //void setSzenForm(CSzenariumForm^ Sz);
    //void setFactory(CBaseTlgFactoryWrapper^ fac);
    void setDelAddToSzen(AddTlgToSzen^ del);
    void setDelUpTlgToSzen(UpdateTlgToSzen^ del);
    void setReceiveView();
	  void setErrorMessageDel(ErrorMessageDelTyp^ del);
    void setEditMode(bool flag);
	protected: 
		//void Dispose(Boolean disposing)
		//{
		//	if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}
	  private: System::Windows::Forms::Panel ^  panInfo;
	  private: System::Windows::Forms::Panel ^  panBody;
	  private: System::Windows::Forms::Panel ^  panButton;
	  private: System::Windows::Forms::Panel ^  panTlgName;
	  private: System::Windows::Forms::Label ^  labTlgName;
	  private: System::Windows::Forms::Label ^  labTlgDescr;
	  private: System::Windows::Forms::Label ^  TlgByteValue;
	  private: System::Windows::Forms::TextBox ^  txtBxByteValue;
    private: System::Windows::Forms::Label ^  label1;
    private: System::Windows::Forms::Label ^  labDirect;
    private: System::Windows::Forms::Button ^  button1;
    private: System::Windows::Forms::Button ^  button2;
    private: System::Windows::Forms::Button ^  button3;
    private: System::Windows::Forms::Button ^  button4;
    private: System::Windows::Forms::Button ^  button5;
    private: System::Windows::Forms::Button ^  button6;
    private: System::Windows::Forms::Button ^  button7;
    private: System::Windows::Forms::Button ^  button8;
    private: System::Windows::Forms::Button ^  button9;
    private: System::Windows::Forms::Button ^  button11;
    private: System::Windows::Forms::ImageList ^  imageList;
    private: System::Windows::Forms::Button ^  buttUpdate;
    private: System::Windows::Forms::Panel ^  panSenderSpez;
	  private: System::Windows::Forms::Button ^  button10;
    private: System::ComponentModel::IContainer ^  components;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>


		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung. 
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
      this->components = gcnew System::ComponentModel::Container();
			System::Resources::ResourceManager ^  resources = gcnew System::Resources::ResourceManager((simulator::CTlgViewForm::typeid));
      this->panInfo = gcnew System::Windows::Forms::Panel();
      this->panSenderSpez = gcnew System::Windows::Forms::Panel();
      this->buttUpdate = gcnew System::Windows::Forms::Button();
      this->button9 = gcnew System::Windows::Forms::Button();
      this->labDirect = gcnew System::Windows::Forms::Label();
      this->label1 = gcnew System::Windows::Forms::Label();
      this->txtBxByteValue = gcnew System::Windows::Forms::TextBox();
      this->TlgByteValue = gcnew System::Windows::Forms::Label();
      this->panTlgName = gcnew System::Windows::Forms::Panel();
      this->labTlgDescr = gcnew System::Windows::Forms::Label();
      this->labTlgName = gcnew System::Windows::Forms::Label();
      this->panBody = gcnew System::Windows::Forms::Panel();
      this->panButton = gcnew System::Windows::Forms::Panel();
      this->button10 = gcnew System::Windows::Forms::Button();
      this->button11 = gcnew System::Windows::Forms::Button();
      this->button8 = gcnew System::Windows::Forms::Button();
      this->button7 = gcnew System::Windows::Forms::Button();
      this->button6 = gcnew System::Windows::Forms::Button();
      this->button5 = gcnew System::Windows::Forms::Button();
      this->button4 = gcnew System::Windows::Forms::Button();
      this->button3 = gcnew System::Windows::Forms::Button();
      this->button2 = gcnew System::Windows::Forms::Button();
      this->button1 = gcnew System::Windows::Forms::Button();
      this->imageList = gcnew System::Windows::Forms::ImageList(this->components);
      this->panInfo->SuspendLayout();
      this->panSenderSpez->SuspendLayout();
      this->panTlgName->SuspendLayout();
      this->panBody->SuspendLayout();
      this->panButton->SuspendLayout();
      this->SuspendLayout();
      // 
      // panInfo
      // 
      this->panInfo->Controls->Add(this->panSenderSpez);
      this->panInfo->Controls->Add(this->labDirect);
      this->panInfo->Controls->Add(this->label1);
      this->panInfo->Controls->Add(this->txtBxByteValue);
      this->panInfo->Controls->Add(this->TlgByteValue);
      this->panInfo->Controls->Add(this->panTlgName);
      this->panInfo->Dock = System::Windows::Forms::DockStyle::Top;
      this->panInfo->Location = System::Drawing::Point(0, 0);
      this->panInfo->Name = "panInfo";
      this->panInfo->Size = System::Drawing::Size(664, 104);
      this->panInfo->TabIndex = 0;
      // 
      // panSenderSpez
      // 
      this->panSenderSpez->BackColor = System::Drawing::SystemColors::Control;
      this->panSenderSpez->Controls->Add(this->buttUpdate);
      this->panSenderSpez->Controls->Add(this->button9);
      this->panSenderSpez->Dock = System::Windows::Forms::DockStyle::Left;
      this->panSenderSpez->Location = System::Drawing::Point(0, 24);
      this->panSenderSpez->Name = "panSenderSpez";
      this->panSenderSpez->Size = System::Drawing::Size(112, 80);
      this->panSenderSpez->TabIndex = 7;
      // 
      // buttUpdate
      // 
      this->buttUpdate->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
      this->buttUpdate->Location = System::Drawing::Point(3, 44);
      this->buttUpdate->Name = "buttUpdate";
      this->buttUpdate->Size = System::Drawing::Size(93, 25);
      this->buttUpdate->TabIndex = 1;
      this->buttUpdate->Text = "  Update Tlg";
      this->buttUpdate->Click += gcnew System::EventHandler(this, &CTlgViewForm::OnButtUpdateClick);
      // 
      // button9
      // 
      this->button9->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
      this->button9->Location = System::Drawing::Point(3, 16);
      this->button9->Name = "button9";
      this->button9->Size = System::Drawing::Size(93, 25);
      this->button9->TabIndex = 0;
      this->button9->Text = "Add to Scenario";
      this->button9->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
      this->button9->Click += gcnew System::EventHandler(this, &CTlgViewForm::OnAddButtonClick);
      // 
      // labDirect
      // 
      this->labDirect->Location = System::Drawing::Point(304, 32);
      this->labDirect->Name = "labDirect";
      this->labDirect->Size = System::Drawing::Size(100, 16);
      this->labDirect->TabIndex = 6;
      this->labDirect->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // label1
      // 
      this->label1->Location = System::Drawing::Point(224, 32);
      this->label1->Name = "label1";
      this->label1->Size = System::Drawing::Size(56, 16);
      this->label1->TabIndex = 5;
      this->label1->Text = "Direction:";
      this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // txtBxByteValue
      // 
      this->txtBxByteValue->Location = System::Drawing::Point(296, 72);
      this->txtBxByteValue->Name = "txtBxByteValue";
      this->txtBxByteValue->Size = System::Drawing::Size(360, 20);
      this->txtBxByteValue->TabIndex = 4;
      this->txtBxByteValue->Text = "";
      // 
      // TlgByteValue
      // 
      this->TlgByteValue->Location = System::Drawing::Point(226, 75);
      this->TlgByteValue->Name = "TlgByteValue";
      this->TlgByteValue->Size = System::Drawing::Size(75, 16);
      this->TlgByteValue->TabIndex = 2;
      this->TlgByteValue->Text = "Byte Value:";
      // 
      // panTlgName
      // 
      this->panTlgName->Controls->Add(this->labTlgDescr);
      this->panTlgName->Controls->Add(this->labTlgName);
      this->panTlgName->Dock = System::Windows::Forms::DockStyle::Top;
      this->panTlgName->Location = System::Drawing::Point(0, 0);
      this->panTlgName->Name = "panTlgName";
      this->panTlgName->Size = System::Drawing::Size(664, 24);
      this->panTlgName->TabIndex = 0;
      // 
      // labTlgDescr
      // 
      this->labTlgDescr->Dock = System::Windows::Forms::DockStyle::Fill;
      this->labTlgDescr->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
      this->labTlgDescr->Location = System::Drawing::Point(128, 0);
      this->labTlgDescr->Name = "labTlgDescr";
      this->labTlgDescr->Size = System::Drawing::Size(536, 24);
      this->labTlgDescr->TabIndex = 1;
      this->labTlgDescr->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // labTlgName
      // 
      this->labTlgName->Dock = System::Windows::Forms::DockStyle::Left;
      this->labTlgName->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
      this->labTlgName->Location = System::Drawing::Point(0, 0);
      this->labTlgName->Name = "labTlgName";
      this->labTlgName->Size = System::Drawing::Size(128, 24);
      this->labTlgName->TabIndex = 0;
      this->labTlgName->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // panBody
      // 
      this->panBody->AutoScroll = true;
      this->panBody->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->panBody->Controls->Add(this->panButton);
      this->panBody->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panBody->Location = System::Drawing::Point(0, 104);
      this->panBody->Name = "panBody";
      this->panBody->Size = System::Drawing::Size(664, 301);
      this->panBody->TabIndex = 1;
      this->panBody->Layout += gcnew System::Windows::Forms::LayoutEventHandler(this, &CTlgViewForm::OnLayout);
      // 
      // panButton
      // 
      this->panButton->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->panButton->Controls->Add(this->button10);
      this->panButton->Controls->Add(this->button11);
      this->panButton->Controls->Add(this->button8);
      this->panButton->Controls->Add(this->button7);
      this->panButton->Controls->Add(this->button6);
      this->panButton->Controls->Add(this->button5);
      this->panButton->Controls->Add(this->button4);
      this->panButton->Controls->Add(this->button3);
      this->panButton->Controls->Add(this->button2);
      this->panButton->Controls->Add(this->button1);
      this->panButton->Dock = System::Windows::Forms::DockStyle::Top;
      this->panButton->Location = System::Drawing::Point(0, 0);
      this->panButton->Name = "panButton";
      this->panButton->Size = System::Drawing::Size(660, 20);
      this->panButton->TabIndex = 0;
      // 
      // button10
      // 
      this->button10->Dock = System::Windows::Forms::DockStyle::Fill;
      this->button10->Location = System::Drawing::Point(540, 0);
      this->button10->Name = "button10";
      this->button10->Size = System::Drawing::Size(118, 18);
      this->button10->TabIndex = 17;
      this->button10->Text = "Description";
      // 
      // button11
      // 
      this->button11->Dock = System::Windows::Forms::DockStyle::Left;
      this->button11->Location = System::Drawing::Point(500, 0);
      this->button11->Name = "button11";
      this->button11->Size = System::Drawing::Size(40, 18);
      this->button11->TabIndex = 16;
      this->button11->Text = "Max";
      // 
      // button8
      // 
      this->button8->Dock = System::Windows::Forms::DockStyle::Left;
      this->button8->Location = System::Drawing::Point(460, 0);
      this->button8->Name = "button8";
      this->button8->Size = System::Drawing::Size(40, 18);
      this->button8->TabIndex = 14;
      this->button8->Text = "Min";
      // 
      // button7
      // 
      this->button7->Dock = System::Windows::Forms::DockStyle::Left;
      this->button7->Location = System::Drawing::Point(420, 0);
      this->button7->Name = "button7";
      this->button7->Size = System::Drawing::Size(40, 18);
      this->button7->TabIndex = 12;
      this->button7->Text = "Factor";
      // 
      // button6
      // 
      this->button6->Dock = System::Windows::Forms::DockStyle::Left;
      this->button6->Location = System::Drawing::Point(380, 0);
      this->button6->Name = "button6";
      this->button6->Size = System::Drawing::Size(40, 18);
      this->button6->TabIndex = 10;
      this->button6->Text = "Tran";
      // 
      // button5
      // 
      this->button5->Dock = System::Windows::Forms::DockStyle::Left;
      this->button5->Location = System::Drawing::Point(340, 0);
      this->button5->Name = "button5";
      this->button5->Size = System::Drawing::Size(40, 18);
      this->button5->TabIndex = 8;
      this->button5->Text = "Len";
      // 
      // button4
      // 
      this->button4->Dock = System::Windows::Forms::DockStyle::Left;
      this->button4->Location = System::Drawing::Point(300, 0);
      this->button4->Name = "button4";
      this->button4->Size = System::Drawing::Size(40, 18);
      this->button4->TabIndex = 6;
      this->button4->Text = "Typ";
      // 
      // button3
      // 
      this->button3->Dock = System::Windows::Forms::DockStyle::Left;
      this->button3->Location = System::Drawing::Point(220, 0);
      this->button3->Name = "button3";
      this->button3->Size = System::Drawing::Size(80, 18);
      this->button3->TabIndex = 4;
      this->button3->Text = "Unit";
      // 
      // button2
      // 
      this->button2->Dock = System::Windows::Forms::DockStyle::Left;
      this->button2->Location = System::Drawing::Point(130, 0);
      this->button2->Name = "button2";
      this->button2->Size = System::Drawing::Size(90, 18);
      this->button2->TabIndex = 2;
      this->button2->Text = "Value";
      // 
      // button1
      // 
      this->button1->Dock = System::Windows::Forms::DockStyle::Left;
      this->button1->Location = System::Drawing::Point(0, 0);
      this->button1->Name = "button1";
      this->button1->Size = System::Drawing::Size(130, 18);
      this->button1->TabIndex = 0;
      this->button1->Text = "Element";
      // 
      // imageList
      // 
      this->imageList->ImageSize = System::Drawing::Size(16, 16);
      this->imageList->ImageStream = (safe_cast<System::Windows::Forms::ImageListStreamer ^  >(resources->GetObject("imageList.ImageStream")));
      this->imageList->TransparentColor = System::Drawing::Color::Transparent;
      // 
      // CTlgViewForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(664, 405);
      this->Controls->Add(this->panBody);
      this->Controls->Add(this->panInfo);
      this->KeyPreview = true;
      this->Name = "CTlgViewForm";
      this->Text = "CTlgViewForm";
      this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &CTlgViewForm::OnKeyFormDown);
      this->panInfo->ResumeLayout(false);
      this->panSenderSpez->ResumeLayout(false);
      this->panTlgName->ResumeLayout(false);
      this->panBody->ResumeLayout(false);
      this->panButton->ResumeLayout(false);
      this->ResumeLayout(false);

    }		




		//--------------------------------------------
    System::Void OnLabelHeaderClick(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnAddButtonClick(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnKeyFormDown(System::Object ^  sender, System::Windows::Forms::KeyEventArgs ^  e);
    System::Void OnEnterTextBox(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnLeaveTextBox(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnButtUpdateClick(System::Object ^  sender, System::EventArgs ^  e);
	  System::Void OnLayout(System::Object ^  sender, System::Windows::Forms::LayoutEventArgs ^  e);
	  //System::Void OnRadButtClick(System::Object ^  sender, System::EventArgs ^  e);
    //--------------------------------------------
		 void addSimpleTlgElem(String^& Name,String^& val,String^& descr,String^& len,String^& typ,String^& unit,String^& trans,
          String^& factor,String^& min,String^& max,Panel^ panElem,int modi);
     void addArrayTlgElem(int id,String^& Name,String^& val,String^& descr,String^& len,String^& unit,String^& trans,
          String^& factor,String^& min,String^& max,Panel^ panElem);
     void CTlgViewForm::addArrayTlgElem_(CTlgElemWrapper^ elem,String^& Name,String^& val,String^& descr,String^& len,String^& unit,String^& trans,
                String^& factor,String^& min,String^& max,Panel^ panElem);
    void addRecordsTlgElem(int id,Panel^ panElem);
    void setBaseTlgElemView(String^& descr,String^& max,String^& min,String^& factor,
        String^& transp,String^ typ,String^& len,String^& unit,Panel^ panElem,int modi);
    void addNewPanel();
	  CItemWrapper^ Tlg;
	  String^ TlgId;
	  String^ TlgElemId;
	  String^ TlgLenId;
	  String^ TlgIdValue;
	  TextBox^ TlgLenTxtBx;
	  int LenIdModus;
    bool LenChange;
    int FlagShowModi;
    int ActTextBox;
    bool NavModi;
    bool UpdateFlag;
    int PanFlag;
    ArrayList^  TxtBoxArray;
    //CSzenariumForm^ Szen;
    //CBaseTlgFactoryWrapper^ TlgFactory;
    AddTlgToSzen^ DelAddTlg;
    UpdateTlgToSzen^ DelUpTlg;
	  ErrorMessageDelTyp^ ErrorMessageDel;
    TelElemEditEventTyp^ TelElemEditEvent;
    Panel^ panCon;

    private: System::Void splitter3_SplitterMoved(System::Object ^  sender, System::Windows::Forms::SplitterEventArgs ^  e)
           {
           } 

    private: System::Void OnEnterTest(System::Object ^  sender, System::EventArgs ^  e)
         {
           int i;

           i=5;
		 }
};
}
