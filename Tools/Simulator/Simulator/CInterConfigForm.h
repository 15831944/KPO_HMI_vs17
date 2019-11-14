#pragma once

//-----------------------------------------------------------
#include "CTlgInterfaceWrapper.h"
#include "CTlgIdentForm.h"
#include "CLogFileConfigForm.h"
#include "CTlgTranspConfigForm.h"
#include "CArrayViewConfigForm.h"
#include "CInterUseCaseConfigForm.h"
#include "CLimValSettingForm.h"
//-----------------------------------------------------------

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Collections::Generic;


namespace simulator
{
	/// <summary> 
	/// Summary for CInterConfigForm
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CInterConfigForm : public System::Windows::Forms::Form
	{
	public: 
		CInterConfigForm(void)
		{
			InitializeComponent();
      ActiveInterface=nullptr;
      InterfaceList=nullptr;
      TlgIdentForm=nullptr;
		  UpdateInterfaceListe = gcnew ArrayList();
      initViewComponet();
		}
    void setInterfaceList(List<CTlgInterfaceWrapper^>^ liste);
    void setActiveInterface(String^ inter);
		array <String^>^ getUpdateInterfacListe();
	protected: 
		//void Dispose(Boolean disposing)
		//{
		//	if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}
    private: System::Windows::Forms::Panel ^  panAllInter;
    private: System::Windows::Forms::Label ^  label1;
    private: System::Windows::Forms::Splitter ^  splitter1;
    private: System::Windows::Forms::Panel ^  panConfigInter;
    private: System::Windows::Forms::ListBox ^  listBoxAvailInter;
    private: System::Windows::Forms::Label ^  label2;
    private: System::Windows::Forms::Label ^  label3;
    private: System::Windows::Forms::Label ^  labDescr;
    private: System::Windows::Forms::Panel ^  panSetting;
    private: System::Windows::Forms::Button ^  butAply;
    private: System::Windows::Forms::Button ^  butOk;
	  private: System::Windows::Forms::Label ^  label4;
	  private: System::Windows::Forms::Panel ^  panel1;
	  private: System::Windows::Forms::Button ^  butBrowse;
	  private: System::Windows::Forms::TextBox ^  txtBxBrowse;
	  private: System::Windows::Forms::TabControl ^  tabCntrlInter;
	  private: System::Windows::Forms::TabPage ^  tabPageTlgId;
    private: System::Windows::Forms::TabPage ^  tabPageLogFile;
    private: System::Windows::Forms::TabPage ^  tabPageTransp;
	  private: System::Windows::Forms::Panel ^  panel2;
	  private: System::Windows::Forms::Panel ^  panel3;
	  private: System::Windows::Forms::Label ^  labInterVer;
	  private: System::Windows::Forms::TabPage ^  tabPageLimVal;

	  private: System::Windows::Forms::TabPage ^  tabPageUseCase;
	  private: System::Windows::Forms::Button ^  butCancel;
    private: System::Windows::Forms::Label ^  labIncfPath;

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
      this->panAllInter = (gcnew System::Windows::Forms::Panel());
      this->panel3 = (gcnew System::Windows::Forms::Panel());
      this->labDescr = (gcnew System::Windows::Forms::Label());
      this->label3 = (gcnew System::Windows::Forms::Label());
      this->panel2 = (gcnew System::Windows::Forms::Panel());
      this->labInterVer = (gcnew System::Windows::Forms::Label());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->panel1 = (gcnew System::Windows::Forms::Panel());
      this->labIncfPath = (gcnew System::Windows::Forms::Label());
      this->label4 = (gcnew System::Windows::Forms::Label());
      this->listBoxAvailInter = (gcnew System::Windows::Forms::ListBox());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->txtBxBrowse = (gcnew System::Windows::Forms::TextBox());
      this->butBrowse = (gcnew System::Windows::Forms::Button());
      this->splitter1 = (gcnew System::Windows::Forms::Splitter());
      this->panConfigInter = (gcnew System::Windows::Forms::Panel());
      this->tabCntrlInter = (gcnew System::Windows::Forms::TabControl());
      this->tabPageTlgId = (gcnew System::Windows::Forms::TabPage());
      this->tabPageLogFile = (gcnew System::Windows::Forms::TabPage());
      this->tabPageTransp = (gcnew System::Windows::Forms::TabPage());
      this->tabPageLimVal = (gcnew System::Windows::Forms::TabPage());
      this->tabPageUseCase = (gcnew System::Windows::Forms::TabPage());
      this->panSetting = (gcnew System::Windows::Forms::Panel());
      this->butCancel = (gcnew System::Windows::Forms::Button());
      this->butOk = (gcnew System::Windows::Forms::Button());
      this->butAply = (gcnew System::Windows::Forms::Button());
      this->panAllInter->SuspendLayout();
      this->panel3->SuspendLayout();
      this->panel2->SuspendLayout();
      this->panel1->SuspendLayout();
      this->panConfigInter->SuspendLayout();
      this->tabCntrlInter->SuspendLayout();
      this->panSetting->SuspendLayout();
      this->SuspendLayout();
      // 
      // panAllInter
      // 
      this->panAllInter->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->panAllInter->Controls->Add(this->panel3);
      this->panAllInter->Controls->Add(this->panel2);
      this->panAllInter->Controls->Add(this->panel1);
      this->panAllInter->Controls->Add(this->label4);
      this->panAllInter->Controls->Add(this->listBoxAvailInter);
      this->panAllInter->Controls->Add(this->label1);
      this->panAllInter->Controls->Add(this->txtBxBrowse);
      this->panAllInter->Controls->Add(this->butBrowse);
      this->panAllInter->Dock = System::Windows::Forms::DockStyle::Left;
      this->panAllInter->Location = System::Drawing::Point(0, 0);
      this->panAllInter->Name = L"panAllInter";
      this->panAllInter->Size = System::Drawing::Size(192, 332);
      this->panAllInter->TabIndex = 0;
      // 
      // panel3
      // 
      this->panel3->Controls->Add(this->labDescr);
      this->panel3->Controls->Add(this->label3);
      this->panel3->Dock = System::Windows::Forms::DockStyle::Top;
      this->panel3->Location = System::Drawing::Point(0, 204);
      this->panel3->Name = L"panel3";
      this->panel3->Size = System::Drawing::Size(190, 48);
      this->panel3->TabIndex = 11;
      // 
      // labDescr
      // 
      this->labDescr->Dock = System::Windows::Forms::DockStyle::Fill;
      this->labDescr->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->labDescr->Location = System::Drawing::Point(40, 0);
      this->labDescr->Name = L"labDescr";
      this->labDescr->Size = System::Drawing::Size(150, 48);
      this->labDescr->TabIndex = 5;
      // 
      // label3
      // 
      this->label3->Dock = System::Windows::Forms::DockStyle::Left;
      this->label3->Location = System::Drawing::Point(0, 0);
      this->label3->Name = L"label3";
      this->label3->Size = System::Drawing::Size(40, 48);
      this->label3->TabIndex = 3;
      this->label3->Text = L"Descr:";
      // 
      // panel2
      // 
      this->panel2->Controls->Add(this->labInterVer);
      this->panel2->Controls->Add(this->label2);
      this->panel2->Dock = System::Windows::Forms::DockStyle::Top;
      this->panel2->Location = System::Drawing::Point(0, 184);
      this->panel2->Name = L"panel2";
      this->panel2->Size = System::Drawing::Size(190, 20);
      this->panel2->TabIndex = 10;
      // 
      // labInterVer
      // 
      this->labInterVer->Dock = System::Windows::Forms::DockStyle::Fill;
      this->labInterVer->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->labInterVer->Location = System::Drawing::Point(48, 0);
      this->labInterVer->Name = L"labInterVer";
      this->labInterVer->Size = System::Drawing::Size(142, 20);
      this->labInterVer->TabIndex = 3;
      this->labInterVer->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // label2
      // 
      this->label2->Dock = System::Windows::Forms::DockStyle::Left;
      this->label2->Location = System::Drawing::Point(0, 0);
      this->label2->Name = L"label2";
      this->label2->Size = System::Drawing::Size(48, 20);
      this->label2->TabIndex = 2;
      this->label2->Text = L"Version:";
      this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // panel1
      // 
      this->panel1->Controls->Add(this->labIncfPath);
      this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
      this->panel1->Location = System::Drawing::Point(0, 128);
      this->panel1->Name = L"panel1";
      this->panel1->Size = System::Drawing::Size(190, 56);
      this->panel1->TabIndex = 9;
      // 
      // labIncfPath
      // 
      this->labIncfPath->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->labIncfPath->Dock = System::Windows::Forms::DockStyle::Fill;
      this->labIncfPath->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->labIncfPath->Location = System::Drawing::Point(0, 0);
      this->labIncfPath->Name = L"labIncfPath";
      this->labIncfPath->Size = System::Drawing::Size(190, 56);
      this->labIncfPath->TabIndex = 0;
      // 
      // label4
      // 
      this->label4->Dock = System::Windows::Forms::DockStyle::Top;
      this->label4->Location = System::Drawing::Point(0, 111);
      this->label4->Name = L"label4";
      this->label4->Size = System::Drawing::Size(190, 17);
      this->label4->TabIndex = 8;
      this->label4->Text = L"Interface Configuration File Path :";
      this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // listBoxAvailInter
      // 
      this->listBoxAvailInter->Dock = System::Windows::Forms::DockStyle::Top;
      this->listBoxAvailInter->Location = System::Drawing::Point(0, 16);
      this->listBoxAvailInter->Name = L"listBoxAvailInter";
      this->listBoxAvailInter->Size = System::Drawing::Size(190, 95);
      this->listBoxAvailInter->TabIndex = 1;
      this->listBoxAvailInter->SelectedIndexChanged += gcnew System::EventHandler(this, &CInterConfigForm::OnSelectedIndexChanged);
      // 
      // label1
      // 
      this->label1->Dock = System::Windows::Forms::DockStyle::Top;
      this->label1->Location = System::Drawing::Point(0, 0);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(190, 16);
      this->label1->TabIndex = 0;
      this->label1->Text = L"Available Interface";
      this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // txtBxBrowse
      // 
      this->txtBxBrowse->Enabled = false;
      this->txtBxBrowse->Location = System::Drawing::Point(0, 272);
      this->txtBxBrowse->Name = L"txtBxBrowse";
      this->txtBxBrowse->Size = System::Drawing::Size(140, 20);
      this->txtBxBrowse->TabIndex = 1;
      this->txtBxBrowse->Visible = false;
      // 
      // butBrowse
      // 
      this->butBrowse->Enabled = false;
      this->butBrowse->Location = System::Drawing::Point(144, 272);
      this->butBrowse->Name = L"butBrowse";
      this->butBrowse->Size = System::Drawing::Size(50, 20);
      this->butBrowse->TabIndex = 0;
      this->butBrowse->Text = L"Browse";
      this->butBrowse->Visible = false;
      this->butBrowse->Click += gcnew System::EventHandler(this, &CInterConfigForm::OnButBrowseClick);
      // 
      // splitter1
      // 
      this->splitter1->Location = System::Drawing::Point(192, 0);
      this->splitter1->Name = L"splitter1";
      this->splitter1->Size = System::Drawing::Size(8, 332);
      this->splitter1->TabIndex = 1;
      this->splitter1->TabStop = false;
      // 
      // panConfigInter
      // 
      this->panConfigInter->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->panConfigInter->Controls->Add(this->tabCntrlInter);
      this->panConfigInter->Controls->Add(this->panSetting);
      this->panConfigInter->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panConfigInter->Location = System::Drawing::Point(200, 0);
      this->panConfigInter->Name = L"panConfigInter";
      this->panConfigInter->Size = System::Drawing::Size(673, 332);
      this->panConfigInter->TabIndex = 2;
      // 
      // tabCntrlInter
      // 
      this->tabCntrlInter->Controls->Add(this->tabPageTlgId);
      this->tabCntrlInter->Controls->Add(this->tabPageLogFile);
      this->tabCntrlInter->Controls->Add(this->tabPageTransp);
      this->tabCntrlInter->Controls->Add(this->tabPageLimVal);
      this->tabCntrlInter->Controls->Add(this->tabPageUseCase);
      this->tabCntrlInter->Dock = System::Windows::Forms::DockStyle::Fill;
      this->tabCntrlInter->Location = System::Drawing::Point(0, 0);
      this->tabCntrlInter->Name = L"tabCntrlInter";
      this->tabCntrlInter->Padding = System::Drawing::Point(0, 0);
      this->tabCntrlInter->SelectedIndex = 0;
      this->tabCntrlInter->Size = System::Drawing::Size(669, 304);
      this->tabCntrlInter->TabIndex = 2;
      // 
      // tabPageTlgId
      // 
      this->tabPageTlgId->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->tabPageTlgId->Location = System::Drawing::Point(4, 22);
      this->tabPageTlgId->Name = L"tabPageTlgId";
      this->tabPageTlgId->Size = System::Drawing::Size(661, 278);
      this->tabPageTlgId->TabIndex = 0;
      this->tabPageTlgId->Text = L"Tel Id";
      this->tabPageTlgId->UseVisualStyleBackColor = true;
      // 
      // tabPageLogFile
      // 
      this->tabPageLogFile->Location = System::Drawing::Point(4, 22);
      this->tabPageLogFile->Name = L"tabPageLogFile";
      this->tabPageLogFile->Size = System::Drawing::Size(661, 278);
      this->tabPageLogFile->TabIndex = 1;
      this->tabPageLogFile->Text = L"Log File";
      this->tabPageLogFile->UseVisualStyleBackColor = true;
      // 
      // tabPageTransp
      // 
      this->tabPageTransp->Location = System::Drawing::Point(4, 22);
      this->tabPageTransp->Name = L"tabPageTransp";
      this->tabPageTransp->Size = System::Drawing::Size(661, 278);
      this->tabPageTransp->TabIndex = 2;
      this->tabPageTransp->Text = L"Transport";
      this->tabPageTransp->UseVisualStyleBackColor = true;
      // 
      // tabPageLimVal
      // 
      this->tabPageLimVal->Location = System::Drawing::Point(4, 22);
      this->tabPageLimVal->Name = L"tabPageLimVal";
      this->tabPageLimVal->Size = System::Drawing::Size(661, 278);
      this->tabPageLimVal->TabIndex = 3;
      this->tabPageLimVal->Text = L"Limit";
      this->tabPageLimVal->UseVisualStyleBackColor = true;
      // 
      // tabPageUseCase
      // 
      this->tabPageUseCase->Location = System::Drawing::Point(4, 22);
      this->tabPageUseCase->Name = L"tabPageUseCase";
      this->tabPageUseCase->Size = System::Drawing::Size(661, 278);
      this->tabPageUseCase->TabIndex = 5;
      this->tabPageUseCase->Text = L"Use Case";
      this->tabPageUseCase->UseVisualStyleBackColor = true;
      // 
      // panSetting
      // 
      this->panSetting->Controls->Add(this->butCancel);
      this->panSetting->Controls->Add(this->butOk);
      this->panSetting->Controls->Add(this->butAply);
      this->panSetting->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->panSetting->Location = System::Drawing::Point(0, 304);
      this->panSetting->Name = L"panSetting";
      this->panSetting->Size = System::Drawing::Size(669, 24);
      this->panSetting->TabIndex = 1;
      // 
      // butCancel
      // 
      this->butCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
      this->butCancel->Location = System::Drawing::Point(290, 1);
      this->butCancel->Name = L"butCancel";
      this->butCancel->Size = System::Drawing::Size(75, 23);
      this->butCancel->TabIndex = 2;
      this->butCancel->Text = L"Cancel";
      this->butCancel->Click += gcnew System::EventHandler(this, &CInterConfigForm::OnButtCancelClick);
      // 
      // butOk
      // 
      this->butOk->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->butOk->Location = System::Drawing::Point(194, 1);
      this->butOk->Name = L"butOk";
      this->butOk->Size = System::Drawing::Size(75, 23);
      this->butOk->TabIndex = 1;
      this->butOk->Text = L"OK";
      this->butOk->Click += gcnew System::EventHandler(this, &CInterConfigForm::OnButOkClick);
      // 
      // butAply
      // 
      this->butAply->Location = System::Drawing::Point(387, 1);
      this->butAply->Name = L"butAply";
      this->butAply->Size = System::Drawing::Size(75, 23);
      this->butAply->TabIndex = 0;
      this->butAply->Text = L"Apply";
      this->butAply->Click += gcnew System::EventHandler(this, &CInterConfigForm::OnButAplyClick);
      // 
      // CInterConfigForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(873, 332);
      this->Controls->Add(this->panConfigInter);
      this->Controls->Add(this->splitter1);
      this->Controls->Add(this->panAllInter);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
      this->Name = L"CInterConfigForm";
      this->ShowInTaskbar = false;
      this->Text = L"CInterConfigForm";
      this->Load += gcnew System::EventHandler(this, &CInterConfigForm::OnLoadForm);
      this->panAllInter->ResumeLayout(false);
      this->panAllInter->PerformLayout();
      this->panel3->ResumeLayout(false);
      this->panel2->ResumeLayout(false);
      this->panel1->ResumeLayout(false);
      this->panConfigInter->ResumeLayout(false);
      this->tabCntrlInter->ResumeLayout(false);
      this->panSetting->ResumeLayout(false);
      this->ResumeLayout(false);

    }		






        //
        //
    System::Void OnLoadForm(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnSelectedIndexChanged(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnButAplyClick(System::Object ^  sender, System::EventArgs ^  e);
	  System::Void OnButBrowseClick(System::Object ^  sender, System::EventArgs ^  e);
	  System::Void OnButOkClick(System::Object ^  sender, System::EventArgs ^  e);
	  System::Void OnButtCancelClick(System::Object ^  sender, System::EventArgs ^  e);

    String^ ActiveInterface;
    List<CTlgInterfaceWrapper^>^ InterfaceList;
	  ArrayList^ UpdateInterfaceListe;

    CTlgIdentForm^ TlgIdentForm;
    CLogFileConfigForm^ LogFileConfigForm;
    CTlgTranspConfigForm^ TlgTranspConfigForm;
    CLimValSettingForm^ LimitValueSettingForm;
	  CArrayViewConfigForm^ ArrayViewConfigForm;
	  CInterUseCaseConfigForm^ UseCaseConfigForm;

    void initAvailableInterface();
    int getActInterfaceNummber();
    void updateInterfaceInfo(String^ inter);
    CTlgInterfaceWrapper^ getInterface(String^ inter);
    void initViewComponet();
	  void updateConfFileFromView();
	  void addInterfaceToUpdateListe();
};
}