#pragma once

#include "CInterConnectionListe.h"
//#include "CSocketConnState.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace simulator
{
	/// <summary> 
	/// Zusammenfassung für CStatusConnectionForm
	///
	/// Achtung: Wenn Sie den Namen dieser Klasse ändern, müssen Sie die Eigenschaft
	///          'Ressourcendateiname' für das Compilertool für verwaltete Ressourcen ändern, 
	///          das allen .resx-Dateien zugewiesen ist, von denen diese Klasse abhängt. 
	///          Anderenfalls können die Designer nicht korrekt mit den lokalisierten Ressourcen
	///          arbeiten, die diesem Formular zugewiesen sind.
	/// </summary>
	public ref class CStatusConnectionForm : public System::Windows::Forms::Form
	{
	public: 
		CStatusConnectionForm(CInterConnectionListe^ sendListe,CInterConnectionListe^ recListe)
		{
			InitializeComponent();
      SendInterConnectionListe = sendListe;
      RecInterConnectionListe = recListe;
		}
         
	    void updateConSendInfoToView(String^ inter);
        void updateConRecInfoToView(String^ inter);

	protected: 
		//void Dispose(Boolean disposing)
		//{
		//	if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}
	private: System::Windows::Forms::Panel ^  panHinter;
	private: System::Windows::Forms::ListView ^  listViewConnStatus;
	private: System::Windows::Forms::ColumnHeader ^  columnHeader1;
	private: System::Windows::Forms::ColumnHeader ^  columnHeader2;
	private: System::Windows::Forms::ColumnHeader ^  columnHeader3;
	private: System::Windows::Forms::ColumnHeader ^  columnHeader4;
	private: System::Windows::Forms::ColumnHeader ^  columnHeader5;
	private: System::Windows::Forms::ColumnHeader ^  columnHeader6;




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
      this->panHinter = (gcnew System::Windows::Forms::Panel());
      this->listViewConnStatus = (gcnew System::Windows::Forms::ListView());
      this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
      this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
      this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
      this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
      this->columnHeader5 = (gcnew System::Windows::Forms::ColumnHeader());
      this->columnHeader6 = (gcnew System::Windows::Forms::ColumnHeader());
      this->panHinter->SuspendLayout();
      this->SuspendLayout();
      // 
      // panHinter
      // 
      this->panHinter->Controls->Add(this->listViewConnStatus);
      this->panHinter->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panHinter->Location = System::Drawing::Point(0, 0);
      this->panHinter->Name = L"panHinter";
      this->panHinter->Size = System::Drawing::Size(544, 269);
      this->panHinter->TabIndex = 0;
      // 
      // listViewConnStatus
      // 
      this->listViewConnStatus->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(6) {this->columnHeader1, 
        this->columnHeader2, this->columnHeader3, this->columnHeader4, this->columnHeader5, this->columnHeader6});
      this->listViewConnStatus->Dock = System::Windows::Forms::DockStyle::Fill;
      this->listViewConnStatus->Location = System::Drawing::Point(0, 0);
      this->listViewConnStatus->Name = L"listViewConnStatus";
      this->listViewConnStatus->Size = System::Drawing::Size(544, 269);
      this->listViewConnStatus->TabIndex = 0;
      this->listViewConnStatus->UseCompatibleStateImageBehavior = false;
      this->listViewConnStatus->View = System::Windows::Forms::View::Details;
      // 
      // columnHeader1
      // 
      this->columnHeader1->Text = L"Interface";
      this->columnHeader1->Width = 80;
      // 
      // columnHeader2
      // 
      this->columnHeader2->Text = L"Direction";
      this->columnHeader2->Width = 80;
      // 
      // columnHeader3
      // 
      this->columnHeader3->Text = L"Status";
      this->columnHeader3->Width = 120;
      // 
      // columnHeader4
      // 
      this->columnHeader4->Text = L"Type";
      this->columnHeader4->Width = 80;
      // 
      // columnHeader5
      // 
      this->columnHeader5->Text = L"IP-Address";
      this->columnHeader5->Width = 80;
      // 
      // columnHeader6
      // 
      this->columnHeader6->Text = L"Port";
      this->columnHeader6->Width = 80;
      // 
      // CStatusConnectionForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(544, 269);
      this->Controls->Add(this->panHinter);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
      this->Name = L"CStatusConnectionForm";
      this->ShowInTaskbar = false;
      this->Text = L"CStatusConnectionForm";
      this->Load += gcnew System::EventHandler(this, &CStatusConnectionForm::OnLoad);
      this->Closed += gcnew System::EventHandler(this, &CStatusConnectionForm::OnClosedForm);
      this->panHinter->ResumeLayout(false);
      this->ResumeLayout(false);

    }		

		System::Void OnLoad(System::Object ^  sender, System::EventArgs ^  e);
        System::Void OnClosedForm(System::Object ^  sender, System::EventArgs ^  e);


		void initComp();
        void showConnInfo(CInterConnectionListe^ liste,int index);
        void updateListeToView(int pos,int inter,CInterConnectionListe^ liste);


    //void updateConnInfo(int inter,int dir,int status);
    //void updateConnInfo(int index,int status);

    CInterConnectionListe^ SendInterConnectionListe;
		CInterConnectionListe^ RecInterConnectionListe;

    //CSocketConnState^ SocketConnStateSend;
    //CSocketConnState^ SocketConnStateRec;
    
   
//private: System::Void OnClosingForm(System::Object ^  sender, System::ComponentModel::CancelEventArgs ^  e)
  //       {
             //e->set_Cancel(
    //     }

private: System::Void listViewConnStatus_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
         }
};
}
