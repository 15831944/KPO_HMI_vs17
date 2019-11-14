#pragma once

//-----------------------------------------------------------------------------
#include "CTlgInterfaceWrapper.h"
#include "CItemWrapper.h"
#include "CXmlInterConfigWriter.h"
#include "CAppSetting.h"
#include "CInterConfigWrapper.h"
//-----------------------------------------------------------------------------

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace simulator
{
	/// <summary> 
	/// Summary for CTlgIdentForm
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CTlgIdentForm : public System::Windows::Forms::Form
	{
	public: 
		CTlgIdentForm(void)
		{
			InitializeComponent();
      
      panIdentTel->Dock = DockStyle::Fill; //test
      Interface = nullptr;
      TlgIdList = gcnew ArrayList();
      TlgNameList = gcnew ArrayList();
      TlgIdPanList = gcnew ArrayList();
      ElemIdChouse = gcnew ArrayList();
      ElemLenChouse = gcnew ArrayList();
		}
    void setInterface(CTlgInterfaceWrapper^ inter);
    void updateConfFileFromView();
	protected: 
		//void Dispose(Boolean disposing)
		//{
		//	if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}

    private: System::Windows::Forms::Panel ^  panIdentTel;
    private: System::Windows::Forms::Panel ^  panIdChouse;
    private: System::Windows::Forms::Panel ^  panIdConf;
    private: System::Windows::Forms::Panel ^  panDescr;
    private: System::Windows::Forms::Panel ^  panIdDescr;
    private: System::Windows::Forms::Panel ^  panIdConfig;
    private: System::Windows::Forms::Label ^  label1;
    private: System::Windows::Forms::Label ^  label2;
    private: System::Windows::Forms::Label ^  label3;
    private: System::Windows::Forms::CheckBox ^  checkBxNameId;
    private: System::Windows::Forms::Panel^  panId;
    private: System::Windows::Forms::Panel^  panLstBoxElemChouseView;
    private: System::Windows::Forms::ListBox^  listBxIdElemChouse;
    private: System::Windows::Forms::Panel^  panLenId;
    private: System::Windows::Forms::Panel^  panLenConfig;
    private: System::Windows::Forms::GroupBox^  groupBox1;
    private: System::Windows::Forms::RadioButton^  radButtUserDef;
    private: System::Windows::Forms::RadioButton^  radButtBody;
    private: System::Windows::Forms::RadioButton^  radButTotal;
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
      this->panIdentTel = (gcnew System::Windows::Forms::Panel());
      this->panIdConf = (gcnew System::Windows::Forms::Panel());
      this->panIdConfig = (gcnew System::Windows::Forms::Panel());
      this->panIdDescr = (gcnew System::Windows::Forms::Panel());
      this->checkBxNameId = (gcnew System::Windows::Forms::CheckBox());
      this->panIdChouse = (gcnew System::Windows::Forms::Panel());
      this->panLstBoxElemChouseView = (gcnew System::Windows::Forms::Panel());
      this->listBxIdElemChouse = (gcnew System::Windows::Forms::ListBox());
      this->panLenId = (gcnew System::Windows::Forms::Panel());
      this->panId = (gcnew System::Windows::Forms::Panel());
      this->panLenConfig = (gcnew System::Windows::Forms::Panel());
      this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
      this->radButtUserDef = (gcnew System::Windows::Forms::RadioButton());
      this->radButtBody = (gcnew System::Windows::Forms::RadioButton());
      this->radButTotal = (gcnew System::Windows::Forms::RadioButton());
      this->panDescr = (gcnew System::Windows::Forms::Panel());
      this->label3 = (gcnew System::Windows::Forms::Label());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->panIdentTel->SuspendLayout();
      this->panIdConf->SuspendLayout();
      this->panIdDescr->SuspendLayout();
      this->panIdChouse->SuspendLayout();
      this->panLstBoxElemChouseView->SuspendLayout();
      this->panLenConfig->SuspendLayout();
      this->groupBox1->SuspendLayout();
      this->panDescr->SuspendLayout();
      this->SuspendLayout();
      // 
      // panIdentTel
      // 
      this->panIdentTel->Controls->Add(this->panIdConf);
      this->panIdentTel->Controls->Add(this->panIdChouse);
      this->panIdentTel->Location = System::Drawing::Point(24, 40);
      this->panIdentTel->Name = "panIdentTel";
      this->panIdentTel->Size = System::Drawing::Size(408, 248);
      this->panIdentTel->TabIndex = 1;
      // 
      // panIdConf
      // 
      this->panIdConf->Controls->Add(this->panIdConfig);
      this->panIdConf->Controls->Add(this->panIdDescr);
      this->panIdConf->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panIdConf->Location = System::Drawing::Point(200, 0);
      this->panIdConf->Name = "panIdConf";
      this->panIdConf->Size = System::Drawing::Size(208, 248);
      this->panIdConf->TabIndex = 1;
      // 
      // panIdConfig
      // 
      this->panIdConfig->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panIdConfig->Location = System::Drawing::Point(0, 24);
      this->panIdConfig->Name = "panIdConfig";
      this->panIdConfig->Size = System::Drawing::Size(208, 224);
      this->panIdConfig->TabIndex = 3;
      // 
      // panIdDescr
      // 
      this->panIdDescr->Controls->Add(this->checkBxNameId);
      this->panIdDescr->Dock = System::Windows::Forms::DockStyle::Top;
      this->panIdDescr->Location = System::Drawing::Point(0, 0);
      this->panIdDescr->Name = "panIdDescr";
      this->panIdDescr->Size = System::Drawing::Size(208, 24);
      this->panIdDescr->TabIndex = 2;
      // 
      // checkBxNameId
      // 
      this->checkBxNameId->Dock = System::Windows::Forms::DockStyle::Fill;
      this->checkBxNameId->Location = System::Drawing::Point(0, 0);
      this->checkBxNameId->Name = "checkBxNameId";
      this->checkBxNameId->Size = System::Drawing::Size(208, 24);
      this->checkBxNameId->TabIndex = 0;
      this->checkBxNameId->Text = "Use Telegramm Name";
      this->checkBxNameId->CheckedChanged += gcnew System::EventHandler(this, &CTlgIdentForm::OnCheckBoxIdNameChecked);
      // 
      // panIdChouse
      // 
      this->panIdChouse->Controls->Add(this->panLstBoxElemChouseView);
      this->panIdChouse->Controls->Add(this->panLenConfig);
      this->panIdChouse->Controls->Add(this->panDescr);
      this->panIdChouse->Dock = System::Windows::Forms::DockStyle::Left;
      this->panIdChouse->Location = System::Drawing::Point(0, 0);
      this->panIdChouse->Name = "panIdChouse";
      this->panIdChouse->Size = System::Drawing::Size(200, 248);
      this->panIdChouse->TabIndex = 0;
      // 
      // panLstBoxElemChouseView
      // 
      this->panLstBoxElemChouseView->AutoScroll = true;
      this->panLstBoxElemChouseView->Controls->Add(this->listBxIdElemChouse);
      this->panLstBoxElemChouseView->Controls->Add(this->panId);
      this->panLstBoxElemChouseView->Controls->Add(this->panLenId);
      this->panLstBoxElemChouseView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panLstBoxElemChouseView->Location = System::Drawing::Point(0, 24);
      this->panLstBoxElemChouseView->Name = "panLstBoxElemChouseView";
      this->panLstBoxElemChouseView->Size = System::Drawing::Size(200, 146);
      this->panLstBoxElemChouseView->TabIndex = 16;
      // 
      // listBxIdElemChouse
      // 
      this->listBxIdElemChouse->Dock = System::Windows::Forms::DockStyle::Fill;
      this->listBxIdElemChouse->Location = System::Drawing::Point(0, 0);
      this->listBxIdElemChouse->Name = "listBxIdElemChouse";
      this->listBxIdElemChouse->Size = System::Drawing::Size(168, 134);
      this->listBxIdElemChouse->TabIndex = 14;
      // 
      // panLenId
      // 
      this->panLenId->Dock = System::Windows::Forms::DockStyle::Right;
      this->panLenId->Location = System::Drawing::Point(184, 0);
      this->panLenId->Name = "panLenId";
      this->panLenId->Size = System::Drawing::Size(16, 146);
      this->panLenId->TabIndex = 4;
      // 
      // panId
      // 
      this->panId->Dock = System::Windows::Forms::DockStyle::Right;
      this->panId->Location = System::Drawing::Point(168, 0);
      this->panId->Name = "panId";
      this->panId->Size = System::Drawing::Size(16, 146);
      this->panId->TabIndex = 5;
      // 
      // panLenConfig
      // 
      this->panLenConfig->Controls->Add(this->groupBox1);
      this->panLenConfig->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->panLenConfig->Location = System::Drawing::Point(0, 170);
      this->panLenConfig->Name = "panLenConfig";
      this->panLenConfig->Size = System::Drawing::Size(200, 78);
      this->panLenConfig->TabIndex = 14;
      // 
      // groupBox1
      // 
      this->groupBox1->Controls->Add(this->radButtUserDef);
      this->groupBox1->Controls->Add(this->radButtBody);
      this->groupBox1->Controls->Add(this->radButTotal);
      this->groupBox1->Dock = System::Windows::Forms::DockStyle::Fill;
      this->groupBox1->Location = System::Drawing::Point(0, 0);
      this->groupBox1->Name = "groupBox1";
      this->groupBox1->Size = System::Drawing::Size(200, 78);
      this->groupBox1->TabIndex = 0;
      this->groupBox1->TabStop = false;
      this->groupBox1->Text = "Length";
      // 
      // radButtUserDef
      // 
      this->radButtUserDef->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->radButtUserDef->Font = (gcnew System::Drawing::Font("Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        (System::Byte)0));
      this->radButtUserDef->Location = System::Drawing::Point(3, 15);
      this->radButtUserDef->Name = "radButtUserDef";
      this->radButtUserDef->Size = System::Drawing::Size(194, 20);
      this->radButtUserDef->TabIndex = 2;
      this->radButtUserDef->Text = "User Defined Length";
      // 
      // radButtBody
      // 
      this->radButtBody->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->radButtBody->Font = (gcnew System::Drawing::Font("Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        (System::Byte)0));
      this->radButtBody->Location = System::Drawing::Point(3, 35);
      this->radButtBody->Name = "radButtBody";
      this->radButtBody->Size = System::Drawing::Size(194, 20);
      this->radButtBody->TabIndex = 1;
      this->radButtBody->Text = "Body Length";
      // 
      // radButTotal
      // 
      this->radButTotal->Checked = true;
      this->radButTotal->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->radButTotal->Font = (gcnew System::Drawing::Font("Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        (System::Byte)0));
      this->radButTotal->Location = System::Drawing::Point(3, 55);
      this->radButTotal->Name = "radButTotal";
      this->radButTotal->Size = System::Drawing::Size(194, 20);
      this->radButTotal->TabIndex = 0;
      this->radButTotal->TabStop = true;
      this->radButTotal->Text = "Complete Length";
      // 
      // panDescr
      // 
      this->panDescr->Controls->Add(this->label3);
      this->panDescr->Controls->Add(this->label2);
      this->panDescr->Controls->Add(this->label1);
      this->panDescr->Dock = System::Windows::Forms::DockStyle::Top;
      this->panDescr->Location = System::Drawing::Point(0, 0);
      this->panDescr->Name = "panDescr";
      this->panDescr->Size = System::Drawing::Size(200, 24);
      this->panDescr->TabIndex = 2;
      // 
      // label3
      // 
      this->label3->Dock = System::Windows::Forms::DockStyle::Left;
      this->label3->Location = System::Drawing::Point(0, 0);
      this->label3->Name = "label3";
      this->label3->Size = System::Drawing::Size(144, 24);
      this->label3->TabIndex = 2;
      this->label3->Text = "Elements of Header";
      this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // label2
      // 
      this->label2->Dock = System::Windows::Forms::DockStyle::Right;
      this->label2->Font = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Pixel, 
        (System::Byte)0));
      this->label2->Location = System::Drawing::Point(164, 0);
      this->label2->Name = "label2";
      this->label2->Size = System::Drawing::Size(16, 24);
      this->label2->TabIndex = 1;
      this->label2->Text = "Id";
      this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // label1
      // 
      this->label1->Dock = System::Windows::Forms::DockStyle::Right;
      this->label1->Font = (gcnew System::Drawing::Font("Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Pixel, 
        (System::Byte)0));
      this->label1->Location = System::Drawing::Point(180, 0);
      this->label1->Name = "label1";
      this->label1->Size = System::Drawing::Size(20, 24);
      this->label1->TabIndex = 0;
      this->label1->Text = "Len";
      this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // CTlgIdentForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(576, 350);
      this->Controls->Add(this->panIdentTel);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
      this->Name = "CTlgIdentForm";
      this->Text = "CTlgIdentForm";
      this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &CTlgIdentForm::OnKeyDown);
      this->panIdentTel->ResumeLayout(false);
      this->panIdConf->ResumeLayout(false);
      this->panIdDescr->ResumeLayout(false);
      this->panIdChouse->ResumeLayout(false);
      this->panLstBoxElemChouseView->ResumeLayout(false);
      this->panLenConfig->ResumeLayout(false);
      this->groupBox1->ResumeLayout(false);
      this->panDescr->ResumeLayout(false);
      this->ResumeLayout(false);

    }		
    System::Void OnListBoxIndexChange(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnKeyDown(System::Object ^  sender, System::Windows::Forms::KeyEventArgs ^  e);
    System::Void OnCheckBoxClick(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnCheckBoxIdNameChecked(System::Object ^  sender, System::EventArgs ^  e);
		System::Void OnSelIndexChange(System::Object ^  sender, System::EventArgs ^  e);

    CTlgInterfaceWrapper^ Interface;
    ArrayList^ TlgNameList;
    ArrayList^ TlgIdList;
    ArrayList^ TlgIdPanList;
    ArrayList^ ElemIdChouse;
    ArrayList^ ElemLenChouse;

		void updateViewFromConfFile();
    void initIdChouse(CXmlInterConfigReader^ confFileReader);
    void initIdInfo(CXmlInterConfigReader^ confFileReader);
    void initLenIdCheckBox(String^ telName,String^ idElem,String^ lenElem);
    int getTlgIdIndex();
    void changeIdElement(ArrayList^ list,CheckBox^ checkBx);
    String^ getElemIdName();
    String^ getElemLenIdName();
    String^ getElemTypId();
    int getIdIndex(ArrayList^ list);
    void setIdInfo(CXmlInterConfigReader^ confFileReader);
    void setIdElements();
    void checkElement(ArrayList^ list,String^ elem);
		void setTreatLenModus(String^ mode);
	 
};
}