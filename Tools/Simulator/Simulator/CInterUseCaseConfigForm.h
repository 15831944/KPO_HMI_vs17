#pragma once
//-----------------------------------------------------------
#include "CTlgInterfaceWrapper.h"
#include "CXmlInterConfigReader.h"
#include "CXmlInterConfigWriter.h"
#include "CAppSetting.h"
#include "CNewUseCaseForm.h"
//-----------------------------------------------------------
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#undef GetObject

namespace simulator
{
	/// <summary> 
	/// Zusammenfassung für CInterUseCaseConfigForm
	///
	/// Achtung: Wenn Sie den Namen dieser Klasse ändern, müssen Sie die Eigenschaft
	///          'Ressourcendateiname' für das Compilertool für verwaltete Ressourcen ändern, 
	///          das allen .resx-Dateien zugewiesen ist, von denen diese Klasse abhängt. 
	///          Anderenfalls können die Designer nicht korrekt mit den lokalisierten Ressourcen
	///          arbeiten, die diesem Formular zugewiesen sind.
	/// </summary>
	public ref class CInterUseCaseConfigForm : public System::Windows::Forms::Form
	{
	public: 
		CInterUseCaseConfigForm(void)
		{
			InitializeComponent();
			UseCaseInfoListe = gcnew ArrayList();
		}
    void updateConfFileFromView();
		void setInterface(CTlgInterfaceWrapper^ inter);
		value struct UseCaseInfo
    {
			String^ Name;
			array <String^>^ Descr;
			String^ Items;
		};
	protected: 
		//void Dispose(Boolean disposing)
		//{
		//	if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}
	private: System::Windows::Forms::Panel ^  panUseCaseView;
	private: System::Windows::Forms::Splitter ^  splitter1;
	private: System::Windows::Forms::Panel ^  panDetailView;
	private: System::Windows::Forms::Panel ^  panel1;
	private: System::Windows::Forms::Label ^  label1;
	private: System::Windows::Forms::Panel ^  panel2;
	private: System::Windows::Forms::Panel ^  panel3;
	private: System::Windows::Forms::Panel ^  panel4;
	private: System::Windows::Forms::Splitter ^  splitter2;
	private: System::Windows::Forms::Panel ^  panel5;
	private: System::Windows::Forms::Splitter ^  splitter3;
	private: System::Windows::Forms::Panel ^  panel6;
	private: System::Windows::Forms::Button ^  butAdd;
	private: System::Windows::Forms::Button ^  butRemove;
	private: System::Windows::Forms::Label ^  label4;
	private: System::Windows::Forms::Label ^  label5;
	private: System::Windows::Forms::CheckedListBox ^  checkListBxAllTlg;
	private: System::Windows::Forms::Button ^  butAddToUsCase;
	private: System::Windows::Forms::CheckedListBox ^  checkListBxUseCaseTlg;
	private: System::Windows::Forms::Button ^  butRemFromUseCase;
  private: System::Windows::Forms::ListBox ^  listBxUseCase;
  private: System::Windows::Forms::Label ^  label2;
  private: System::Windows::Forms::TextBox ^  txtBxInterDescr;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container^ components;

		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung. 
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
      System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager((CInterUseCaseConfigForm::typeid)));
      this->panUseCaseView = (gcnew System::Windows::Forms::Panel());
      this->panel2 = (gcnew System::Windows::Forms::Panel());
      this->txtBxInterDescr = (gcnew System::Windows::Forms::TextBox());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->listBxUseCase = (gcnew System::Windows::Forms::ListBox());
      this->panel1 = (gcnew System::Windows::Forms::Panel());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->splitter1 = (gcnew System::Windows::Forms::Splitter());
      this->panDetailView = (gcnew System::Windows::Forms::Panel());
      this->panel6 = (gcnew System::Windows::Forms::Panel());
      this->checkListBxAllTlg = (gcnew System::Windows::Forms::CheckedListBox());
      this->label5 = (gcnew System::Windows::Forms::Label());
      this->splitter3 = (gcnew System::Windows::Forms::Splitter());
      this->panel5 = (gcnew System::Windows::Forms::Panel());
      this->butRemFromUseCase = (gcnew System::Windows::Forms::Button());
      this->butAddToUsCase = (gcnew System::Windows::Forms::Button());
      this->splitter2 = (gcnew System::Windows::Forms::Splitter());
      this->panel4 = (gcnew System::Windows::Forms::Panel());
      this->checkListBxUseCaseTlg = (gcnew System::Windows::Forms::CheckedListBox());
      this->label4 = (gcnew System::Windows::Forms::Label());
      this->panel3 = (gcnew System::Windows::Forms::Panel());
      this->butRemove = (gcnew System::Windows::Forms::Button());
      this->butAdd = (gcnew System::Windows::Forms::Button());
      this->panUseCaseView->SuspendLayout();
      this->panel2->SuspendLayout();
      this->panel1->SuspendLayout();
      this->panDetailView->SuspendLayout();
      this->panel6->SuspendLayout();
      this->panel5->SuspendLayout();
      this->panel4->SuspendLayout();
      this->panel3->SuspendLayout();
      this->SuspendLayout();
      // 
      // panUseCaseView
      // 
      this->panUseCaseView->Controls->Add(this->panel2);
      this->panUseCaseView->Controls->Add(this->listBxUseCase);
      this->panUseCaseView->Controls->Add(this->panel1);
      this->panUseCaseView->Dock = System::Windows::Forms::DockStyle::Left;
      this->panUseCaseView->Location = System::Drawing::Point(0, 0);
      this->panUseCaseView->Name = "panUseCaseView";
      this->panUseCaseView->Size = System::Drawing::Size(120, 273);
      this->panUseCaseView->TabIndex = 0;
      // 
      // panel2
      // 
      this->panel2->Controls->Add(this->txtBxInterDescr);
      this->panel2->Controls->Add(this->label2);
      this->panel2->Dock = System::Windows::Forms::DockStyle::Top;
      this->panel2->Location = System::Drawing::Point(0, 128);
      this->panel2->Name = "panel2";
      this->panel2->Size = System::Drawing::Size(120, 52);
      this->panel2->TabIndex = 2;
      // 
      // txtBxInterDescr
      // 
      this->txtBxInterDescr->BorderStyle = System::Windows::Forms::BorderStyle::None;
      this->txtBxInterDescr->Dock = System::Windows::Forms::DockStyle::Fill;
      this->txtBxInterDescr->Location = System::Drawing::Point(40, 0);
      this->txtBxInterDescr->Multiline = true;
      this->txtBxInterDescr->Name = "txtBxInterDescr";
      this->txtBxInterDescr->ReadOnly = true;
      this->txtBxInterDescr->Size = System::Drawing::Size(80, 52);
      this->txtBxInterDescr->TabIndex = 1;
      // 
      // label2
      // 
      this->label2->Dock = System::Windows::Forms::DockStyle::Left;
      this->label2->Location = System::Drawing::Point(0, 0);
      this->label2->Name = "label2";
      this->label2->Size = System::Drawing::Size(40, 52);
      this->label2->TabIndex = 0;
      this->label2->Text = "Descr";
      // 
      // listBxUseCase
      // 
      this->listBxUseCase->Dock = System::Windows::Forms::DockStyle::Top;
      this->listBxUseCase->Location = System::Drawing::Point(0, 20);
      this->listBxUseCase->Name = "listBxUseCase";
      this->listBxUseCase->Size = System::Drawing::Size(120, 108);
      this->listBxUseCase->TabIndex = 1;
      this->listBxUseCase->SelectedIndexChanged += gcnew System::EventHandler(this, &CInterUseCaseConfigForm::OnListBoxSelIndexChange);
      // 
      // panel1
      // 
      this->panel1->Controls->Add(this->label1);
      this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
      this->panel1->Location = System::Drawing::Point(0, 0);
      this->panel1->Name = "panel1";
      this->panel1->Size = System::Drawing::Size(120, 20);
      this->panel1->TabIndex = 0;
      // 
      // label1
      // 
      this->label1->Dock = System::Windows::Forms::DockStyle::Fill;
      this->label1->Location = System::Drawing::Point(0, 0);
      this->label1->Name = "label1";
      this->label1->Size = System::Drawing::Size(120, 20);
      this->label1->TabIndex = 0;
      this->label1->Text = "Use Case";
      this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // splitter1
      // 
      this->splitter1->Location = System::Drawing::Point(120, 0);
      this->splitter1->Name = "splitter1";
      this->splitter1->Size = System::Drawing::Size(8, 273);
      this->splitter1->TabIndex = 1;
      this->splitter1->TabStop = false;
      // 
      // panDetailView
      // 
      this->panDetailView->Controls->Add(this->panel6);
      this->panDetailView->Controls->Add(this->splitter3);
      this->panDetailView->Controls->Add(this->panel5);
      this->panDetailView->Controls->Add(this->splitter2);
      this->panDetailView->Controls->Add(this->panel4);
      this->panDetailView->Controls->Add(this->panel3);
      this->panDetailView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panDetailView->Location = System::Drawing::Point(128, 0);
      this->panDetailView->Name = "panDetailView";
      this->panDetailView->Size = System::Drawing::Size(368, 273);
      this->panDetailView->TabIndex = 2;
      // 
      // panel6
      // 
      this->panel6->Controls->Add(this->checkListBxAllTlg);
      this->panel6->Controls->Add(this->label5);
      this->panel6->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panel6->Location = System::Drawing::Point(176, 20);
      this->panel6->Name = "panel6";
      this->panel6->Size = System::Drawing::Size(192, 253);
      this->panel6->TabIndex = 5;
      // 
      // checkListBxAllTlg
      // 
      this->checkListBxAllTlg->CheckOnClick = true;
      this->checkListBxAllTlg->Dock = System::Windows::Forms::DockStyle::Fill;
      this->checkListBxAllTlg->Location = System::Drawing::Point(0, 16);
      this->checkListBxAllTlg->Name = "checkListBxAllTlg";
      this->checkListBxAllTlg->Size = System::Drawing::Size(192, 229);
      this->checkListBxAllTlg->TabIndex = 1;
      // 
      // label5
      // 
      this->label5->Dock = System::Windows::Forms::DockStyle::Top;
      this->label5->Location = System::Drawing::Point(0, 0);
      this->label5->Name = "label5";
      this->label5->Size = System::Drawing::Size(192, 16);
      this->label5->TabIndex = 0;
      this->label5->Text = "All Telegram";
      this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // splitter3
      // 
      this->splitter3->Location = System::Drawing::Point(168, 20);
      this->splitter3->Name = "splitter3";
      this->splitter3->Size = System::Drawing::Size(8, 253);
      this->splitter3->TabIndex = 4;
      this->splitter3->TabStop = false;
      // 
      // panel5
      // 
      this->panel5->Controls->Add(this->butRemFromUseCase);
      this->panel5->Controls->Add(this->butAddToUsCase);
      this->panel5->Dock = System::Windows::Forms::DockStyle::Left;
      this->panel5->Location = System::Drawing::Point(128, 20);
      this->panel5->Name = "panel5";
      this->panel5->Size = System::Drawing::Size(40, 253);
      this->panel5->TabIndex = 3;
      // 
      // butRemFromUseCase
      // 
      this->butRemFromUseCase->Image = (safe_cast<System::Drawing::Image^  >(resources->GetObject("butRemFromUseCase.Image")));
      this->butRemFromUseCase->Location = System::Drawing::Point(0, 72);
      this->butRemFromUseCase->Name = "butRemFromUseCase";
      this->butRemFromUseCase->Size = System::Drawing::Size(40, 23);
      this->butRemFromUseCase->TabIndex = 1;
      this->butRemFromUseCase->Click += gcnew System::EventHandler(this, &CInterUseCaseConfigForm::OnButRemFromUseCaseClick);
      // 
      // butAddToUsCase
      // 
      this->butAddToUsCase->Image = (safe_cast<System::Drawing::Image^  >(resources->GetObject("butAddToUsCase.Image")));
      this->butAddToUsCase->Location = System::Drawing::Point(0, 40);
      this->butAddToUsCase->Name = "butAddToUsCase";
      this->butAddToUsCase->Size = System::Drawing::Size(40, 23);
      this->butAddToUsCase->TabIndex = 0;
      this->butAddToUsCase->Click += gcnew System::EventHandler(this, &CInterUseCaseConfigForm::OnButAddToUseCaseClick);
      // 
      // splitter2
      // 
      this->splitter2->Location = System::Drawing::Point(120, 20);
      this->splitter2->Name = "splitter2";
      this->splitter2->Size = System::Drawing::Size(8, 253);
      this->splitter2->TabIndex = 2;
      this->splitter2->TabStop = false;
      // 
      // panel4
      // 
      this->panel4->Controls->Add(this->checkListBxUseCaseTlg);
      this->panel4->Controls->Add(this->label4);
      this->panel4->Dock = System::Windows::Forms::DockStyle::Left;
      this->panel4->Location = System::Drawing::Point(0, 20);
      this->panel4->Name = "panel4";
      this->panel4->Size = System::Drawing::Size(120, 253);
      this->panel4->TabIndex = 1;
      // 
      // checkListBxUseCaseTlg
      // 
      this->checkListBxUseCaseTlg->CheckOnClick = true;
      this->checkListBxUseCaseTlg->Dock = System::Windows::Forms::DockStyle::Fill;
      this->checkListBxUseCaseTlg->Location = System::Drawing::Point(0, 16);
      this->checkListBxUseCaseTlg->Name = "checkListBxUseCaseTlg";
      this->checkListBxUseCaseTlg->Size = System::Drawing::Size(120, 229);
      this->checkListBxUseCaseTlg->TabIndex = 1;
      // 
      // label4
      // 
      this->label4->Dock = System::Windows::Forms::DockStyle::Top;
      this->label4->Location = System::Drawing::Point(0, 0);
      this->label4->Name = "label4";
      this->label4->Size = System::Drawing::Size(120, 16);
      this->label4->TabIndex = 0;
      this->label4->Text = "Use Case Telegram";
      this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
      // 
      // panel3
      // 
      this->panel3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->panel3->Controls->Add(this->butRemove);
      this->panel3->Controls->Add(this->butAdd);
      this->panel3->Dock = System::Windows::Forms::DockStyle::Top;
      this->panel3->Location = System::Drawing::Point(0, 0);
      this->panel3->Name = "panel3";
      this->panel3->Size = System::Drawing::Size(368, 20);
      this->panel3->TabIndex = 0;
      // 
      // butRemove
      // 
      this->butRemove->Dock = System::Windows::Forms::DockStyle::Right;
      this->butRemove->Location = System::Drawing::Point(254, 0);
      this->butRemove->Name = "butRemove";
      this->butRemove->Size = System::Drawing::Size(56, 18);
      this->butRemove->TabIndex = 1;
      this->butRemove->Text = "Remove";
      this->butRemove->Click += gcnew System::EventHandler(this, &CInterUseCaseConfigForm::OnButRemoveClick);
      // 
      // butAdd
      // 
      this->butAdd->Dock = System::Windows::Forms::DockStyle::Right;
      this->butAdd->Location = System::Drawing::Point(310, 0);
      this->butAdd->Name = "butAdd";
      this->butAdd->Size = System::Drawing::Size(56, 18);
      this->butAdd->TabIndex = 0;
      this->butAdd->Text = "Add";
      this->butAdd->Click += gcnew System::EventHandler(this, &CInterUseCaseConfigForm::OnAddUseCaseClick);
      // 
      // CInterUseCaseConfigForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(496, 273);
      this->Controls->Add(this->panDetailView);
      this->Controls->Add(this->splitter1);
      this->Controls->Add(this->panUseCaseView);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
      this->Name = "CInterUseCaseConfigForm";
      this->Text = "CInterUseCaseConfigForm";
      this->panUseCaseView->ResumeLayout(false);
      this->panel2->ResumeLayout(false);
      this->panel2->PerformLayout();
      this->panel1->ResumeLayout(false);
      this->panDetailView->ResumeLayout(false);
      this->panel6->ResumeLayout(false);
      this->panel5->ResumeLayout(false);
      this->panel4->ResumeLayout(false);
      this->panel3->ResumeLayout(false);
      this->ResumeLayout(false);

    }		
		//-----------------------------------------------
		System::Void OnButAddToUseCaseClick(System::Object ^  sender, System::EventArgs ^  e);
		System::Void OnButRemFromUseCaseClick(System::Object ^  sender, System::EventArgs ^  e);
		System::Void OnAddUseCaseClick(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnListBoxSelIndexChange(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnButRemoveClick(System::Object ^  sender, System::EventArgs ^  e);

		CTlgInterfaceWrapper^ Interface;
		ArrayList^ UseCaseInfoListe;
		void updateViewFromConfFile();
		bool readUseCaseInfoFromConfFile();
		void showAllTlg();
    void updateUseCaseInfoListe(String^ useCaseName);
    UseCaseInfo^ findUseCaseItem(String^ useCaseName);
};
}
