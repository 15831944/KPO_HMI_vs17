#pragma once

//--------------------------------------------------
#include "CTlgInterfaceWrapper.h"
#include "CItemBaseContainerWrapper.h"
//--------------------------------------------------

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace simulator
{
	/// <summary> 
	/// Summary for CTlgContainerFindForm
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CTlgContainerFindForm : public System::Windows::Forms::Form
	{
  public: delegate void EventDownOkTyp(int pos);
  public: 
		CTlgContainerFindForm(void)
		{
			InitializeComponent();
			EventDownOk=nullptr;
			ContainerToFind=nullptr;
			PosInContainer=0;
		}
    void setInterface(CTlgInterfaceWrapper^ inter); 
    String^ getTel();
    String^ getElem();
    String^ getRelation();
    String^ getValue();
	  void setContainerToFind(CItemBaseContainerWrapper^ con);
    void initTlgFromInterface();
    void initTlgFromContainer();
	//bool isFindExpand();
	void setOkDownEvent(EventDownOkTyp^ event);
	protected: 
		//void Dispose(Boolean disposing)
		//{
		//	if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}
  private: System::Windows::Forms::GroupBox ^  groupBox1;
  private: System::Windows::Forms::Label ^  label1;
  private: System::Windows::Forms::Label ^  label2;
  private: System::Windows::Forms::Button ^  button1;
  private: System::Windows::Forms::Button ^  button2;
  private: System::Windows::Forms::GroupBox ^  groupBox2;
  private: System::Windows::Forms::Label ^  label3;
  private: System::Windows::Forms::ComboBox ^  comBxRelation;
  private: System::Windows::Forms::ComboBox ^  comBxelem;
  private: System::Windows::Forms::ComboBox ^  comBxAllTlg;
	private: System::Windows::Forms::TextBox ^  txtBxVal;

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
      this->groupBox1 = gcnew System::Windows::Forms::GroupBox();
      this->comBxAllTlg = gcnew System::Windows::Forms::ComboBox();
      this->label1 = gcnew System::Windows::Forms::Label();
      this->comBxelem = gcnew System::Windows::Forms::ComboBox();
      this->label2 = gcnew System::Windows::Forms::Label();
      this->button1 = gcnew System::Windows::Forms::Button();
      this->button2 = gcnew System::Windows::Forms::Button();
      this->groupBox2 = gcnew System::Windows::Forms::GroupBox();
      this->txtBxVal = gcnew System::Windows::Forms::TextBox();
      this->comBxRelation = gcnew System::Windows::Forms::ComboBox();
      this->label3 = gcnew System::Windows::Forms::Label();
      this->groupBox1->SuspendLayout();
      this->groupBox2->SuspendLayout();
      this->SuspendLayout();
      // 
      // groupBox1
      // 
      this->groupBox1->Controls->Add(this->comBxAllTlg);
      this->groupBox1->Controls->Add(this->label1);
      this->groupBox1->Location = System::Drawing::Point(16, 16);
      this->groupBox1->Name = "groupBox1";
      this->groupBox1->Size = System::Drawing::Size(344, 64);
      this->groupBox1->TabIndex = 0;
      this->groupBox1->TabStop = false;
      // 
      // comBxAllTlg
      // 
      this->comBxAllTlg->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->comBxAllTlg->Location = System::Drawing::Point(90, 22);
      this->comBxAllTlg->Name = "comBxAllTlg";
      this->comBxAllTlg->Size = System::Drawing::Size(246, 21);
      this->comBxAllTlg->TabIndex = 2;
			this->comBxAllTlg->SelectedIndexChanged += gcnew System::EventHandler(this, &CTlgContainerFindForm::OnSelectedIndexChange);
      // 
      // label1
      // 
      this->label1->Location = System::Drawing::Point(8, 18);
      this->label1->Name = "label1";
      this->label1->Size = System::Drawing::Size(64, 23);
      this->label1->TabIndex = 0;
      this->label1->Text = "Telegramm";
      this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // comBxelem
      // 
      this->comBxelem->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->comBxelem->Location = System::Drawing::Point(88, 24);
      this->comBxelem->Name = "comBxelem";
      this->comBxelem->Size = System::Drawing::Size(168, 21);
      this->comBxelem->TabIndex = 3;
      // 
      // label2
      // 
      this->label2->Location = System::Drawing::Point(8, 24);
      this->label2->Name = "label2";
      this->label2->Size = System::Drawing::Size(64, 23);
      this->label2->TabIndex = 1;
      this->label2->Text = "Element";
      this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // button1
      // 
      this->button1->Location = System::Drawing::Point(368, 24);
      this->button1->Name = "button1";
      this->button1->TabIndex = 1;
      this->button1->Text = "Find";
			this->button1->Click += gcnew System::EventHandler(this, &CTlgContainerFindForm::OnFindButtonClick);
      // 
      // button2
      // 
      this->button2->Location = System::Drawing::Point(368, 64);
      this->button2->Name = "button2";
      this->button2->TabIndex = 2;
      this->button2->Text = "Close";
			this->button2->Click += gcnew System::EventHandler(this, &CTlgContainerFindForm::OnCloseButtonClick);
      // 
      // groupBox2
      // 
      this->groupBox2->Controls->Add(this->txtBxVal);
      this->groupBox2->Controls->Add(this->comBxRelation);
      this->groupBox2->Controls->Add(this->label3);
      this->groupBox2->Controls->Add(this->label2);
      this->groupBox2->Controls->Add(this->comBxelem);
      this->groupBox2->Location = System::Drawing::Point(16, 96);
      this->groupBox2->Name = "groupBox2";
      this->groupBox2->Size = System::Drawing::Size(344, 96);
      this->groupBox2->TabIndex = 3;
      this->groupBox2->TabStop = false;
      this->groupBox2->Text = "Relation for Element";
      // 
      // txtBxVal
      // 
      this->txtBxVal->Location = System::Drawing::Point(120, 64);
      this->txtBxVal->Name = "txtBxVal";
      this->txtBxVal->Size = System::Drawing::Size(136, 20);
      this->txtBxVal->TabIndex = 2;
      this->txtBxVal->Text = "";
      // 
      // comBxRelation
      // 
      this->comBxRelation->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->comBxRelation->Items->AddRange(gcnew array< System::Object^ >(5) {"=","<","<=",">",">="});
      this->comBxRelation->Location = System::Drawing::Point(56, 64);
      this->comBxRelation->Name = "comBxRelation";
      this->comBxRelation->Size = System::Drawing::Size(56, 21);
      this->comBxRelation->TabIndex = 1;
      // 
      // label3
      // 
      this->label3->Location = System::Drawing::Point(8, 64);
      this->label3->Name = "label3";
      this->label3->Size = System::Drawing::Size(48, 16);
      this->label3->TabIndex = 0;
      this->label3->Text = "Value";
      // 
      // CTlgContainerFindForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(458, 216);
      this->Controls->Add(this->groupBox2);
      this->Controls->Add(this->button2);
      this->Controls->Add(this->button1);
      this->Controls->Add(this->groupBox1);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
      this->Name = "CTlgContainerFindForm";
      this->ShowInTaskbar = false;
      this->Text = "Find Telegramm";
			this->Load += gcnew System::EventHandler(this, &CTlgContainerFindForm::OnLoadForm);
      this->groupBox1->ResumeLayout(false);
      this->groupBox2->ResumeLayout(false);
      this->ResumeLayout(false);
    }		
    System::Void OnLoadForm(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnFindButtonClick(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnCloseButtonClick(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnSelectedIndexChange(System::Object ^  sender, System::EventArgs ^  e);

    //void initInterfaceTlg();
    CTlgInterfaceWrapper^ Interface;
	  CItemBaseContainerWrapper^ ContainerToFind;
	  EventDownOkTyp^ EventDownOk;
	  int PosInContainer;
    bool InterfaceTlgFlag;

};
}