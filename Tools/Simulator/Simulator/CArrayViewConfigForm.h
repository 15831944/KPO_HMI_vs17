#pragma once

//-------------------------------------------------------------
#include "CTlgInterfaceWrapper.h"
#include "CAppSetting.h"
#include  "CXmlInterConfigReader.h"
#include "CXmlInterConfigWriter.h"
#include "CItemWrapper.h"
//-------------------------------------------------------------

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace simulator
{
	/// <summary> 
	/// Zusammenfassung für CArrayViewConfigForm
	///
	/// Achtung: Wenn Sie den Namen dieser Klasse ändern, müssen Sie die Eigenschaft
	///          'Ressourcendateiname' für das Compilertool für verwaltete Ressourcen ändern, 
	///          das allen .resx-Dateien zugewiesen ist, von denen diese Klasse abhängt. 
	///          Anderenfalls können die Designer nicht korrekt mit den lokalisierten Ressourcen
	///          arbeiten, die diesem Formular zugewiesen sind.
	/// </summary>
	public ref class CArrayViewConfigForm : public System::Windows::Forms::Form
	{
  public: 
  public: 
		CArrayViewConfigForm(void)
		{
			InitializeComponent();
            Interface=nullptr;
            InterInfo = gcnew ArrayList();
		}
    void setInterface(CTlgInterfaceWrapper^ inter);
    void updateConfFileFromView();
		value struct InterfaceInfo
    {
      int Count;
      String^ Tel;
      String^ ElemName;
      String^ Descr;
      String^ Typ;
      ArrayList^ RowNameArray;
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
    private: System::Windows::Forms::Panel ^  panArrayElemView;
    private: System::Windows::Forms::Splitter ^  splitter1;
    private: System::Windows::Forms::Panel ^  panArrayElemAdd;
    private: System::Windows::Forms::Panel ^  panArrElemInfo2;
    private: System::Windows::Forms::Panel ^  panArrElemInfo1;
    private: System::Windows::Forms::ListBox ^  listBxArrElem;
    private: System::Windows::Forms::Panel ^  panel1;
    private: System::Windows::Forms::Label ^  label1;
    private: System::Windows::Forms::Panel ^  panel2;
    private: System::Windows::Forms::Label ^  label2;
    private: System::Windows::Forms::Panel ^  panel3;


    private: System::Windows::Forms::Label ^  label4;


    private: System::Windows::Forms::Button ^  button1;
    private: System::Windows::Forms::Label ^  labCount;
    private: System::Windows::Forms::Label ^  labTyp;
    private: System::Windows::Forms::Panel ^  panel4;
    private: System::Windows::Forms::Label ^  label3;
    private: System::Windows::Forms::Label ^  labDescr;
    private: System::Windows::Forms::Label ^  label6;
    private: System::Windows::Forms::Label ^  labTel;
    private: System::Windows::Forms::Label ^  label7;
    private: System::Windows::Forms::Label ^  labRowCount;
    private: System::Windows::Forms::ListView ^  listViewDetailInfo;
    private: System::Windows::Forms::ColumnHeader ^  columnHeader1;
    private: System::Windows::Forms::Button ^  butAdd;


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
            this->panArrayElemView = gcnew System::Windows::Forms::Panel();
            this->panel4 = gcnew System::Windows::Forms::Panel();
            this->labDescr = gcnew System::Windows::Forms::Label();
            this->label3 = gcnew System::Windows::Forms::Label();
            this->panel3 = gcnew System::Windows::Forms::Panel();
            this->labTel = gcnew System::Windows::Forms::Label();
            this->label6 = gcnew System::Windows::Forms::Label();
            this->panel2 = gcnew System::Windows::Forms::Panel();
            this->labTyp = gcnew System::Windows::Forms::Label();
            this->label2 = gcnew System::Windows::Forms::Label();
            this->panel1 = gcnew System::Windows::Forms::Panel();
            this->labCount = gcnew System::Windows::Forms::Label();
            this->label1 = gcnew System::Windows::Forms::Label();
            this->listBxArrElem = gcnew System::Windows::Forms::ListBox();
            this->panArrElemInfo1 = gcnew System::Windows::Forms::Panel();
            this->label7 = gcnew System::Windows::Forms::Label();
            this->splitter1 = gcnew System::Windows::Forms::Splitter();
            this->panArrayElemAdd = gcnew System::Windows::Forms::Panel();
            this->listViewDetailInfo = gcnew System::Windows::Forms::ListView();
            this->columnHeader1 = gcnew System::Windows::Forms::ColumnHeader();
            this->panArrElemInfo2 = gcnew System::Windows::Forms::Panel();
            this->button1 = gcnew System::Windows::Forms::Button();
            this->butAdd = gcnew System::Windows::Forms::Button();
            this->labRowCount = gcnew System::Windows::Forms::Label();
            this->label4 = gcnew System::Windows::Forms::Label();
            this->panArrayElemView->SuspendLayout();
            this->panel4->SuspendLayout();
            this->panel3->SuspendLayout();
            this->panel2->SuspendLayout();
            this->panel1->SuspendLayout();
            this->panArrElemInfo1->SuspendLayout();
            this->panArrayElemAdd->SuspendLayout();
            this->panArrElemInfo2->SuspendLayout();
            this->SuspendLayout();
            // 
            // panArrayElemView
            // 
            this->panArrayElemView->Controls->Add(this->panel4);
            this->panArrayElemView->Controls->Add(this->panel3);
            this->panArrayElemView->Controls->Add(this->panel2);
            this->panArrayElemView->Controls->Add(this->panel1);
            this->panArrayElemView->Controls->Add(this->listBxArrElem);
            this->panArrayElemView->Controls->Add(this->panArrElemInfo1);
            this->panArrayElemView->Dock = System::Windows::Forms::DockStyle::Left;
            this->panArrayElemView->Location = System::Drawing::Point(0, 0);
            this->panArrayElemView->Name = "panArrayElemView";
            this->panArrayElemView->Size = System::Drawing::Size(128, 333);
            this->panArrayElemView->TabIndex = 0;
            // 
            // panel4
            // 
            this->panel4->Controls->Add(this->labDescr);
            this->panel4->Controls->Add(this->label3);
            this->panel4->Dock = System::Windows::Forms::DockStyle::Top;
            this->panel4->Location = System::Drawing::Point(0, 161);
            this->panel4->Name = "panel4";
            this->panel4->Size = System::Drawing::Size(128, 100);
            this->panel4->TabIndex = 5;
            // 
            // labDescr
            // 
            this->labDescr->Dock = System::Windows::Forms::DockStyle::Fill;
            this->labDescr->Location = System::Drawing::Point(48, 0);
            this->labDescr->Name = "labDescr";
            this->labDescr->Size = System::Drawing::Size(80, 100);
            this->labDescr->TabIndex = 2;
            // 
            // label3
            // 
            this->label3->Dock = System::Windows::Forms::DockStyle::Left;
            this->label3->Location = System::Drawing::Point(0, 0);
            this->label3->Name = "label3";
            this->label3->Size = System::Drawing::Size(48, 100);
            this->label3->TabIndex = 1;
            this->label3->Text = "Descr";
            // 
            // panel3
            // 
            this->panel3->Controls->Add(this->labTel);
            this->panel3->Controls->Add(this->label6);
            this->panel3->Dock = System::Windows::Forms::DockStyle::Top;
            this->panel3->Location = System::Drawing::Point(0, 147);
            this->panel3->Name = "panel3";
            this->panel3->Size = System::Drawing::Size(128, 14);
            this->panel3->TabIndex = 4;
            // 
            // labTel
            // 
            this->labTel->Dock = System::Windows::Forms::DockStyle::Fill;
            this->labTel->Location = System::Drawing::Point(48, 0);
            this->labTel->Name = "labTel";
            this->labTel->Size = System::Drawing::Size(80, 14);
            this->labTel->TabIndex = 1;
            this->labTel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            // 
            // label6
            // 
            this->label6->Dock = System::Windows::Forms::DockStyle::Left;
            this->label6->Location = System::Drawing::Point(0, 0);
            this->label6->Name = "label6";
            this->label6->Size = System::Drawing::Size(48, 14);
            this->label6->TabIndex = 0;
            this->label6->Text = "Tel";
            this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            // 
            // panel2
            // 
            this->panel2->Controls->Add(this->labTyp);
            this->panel2->Controls->Add(this->label2);
            this->panel2->Dock = System::Windows::Forms::DockStyle::Top;
            this->panel2->Location = System::Drawing::Point(0, 133);
            this->panel2->Name = "panel2";
            this->panel2->Size = System::Drawing::Size(128, 14);
            this->panel2->TabIndex = 3;
            // 
            // labTyp
            // 
            this->labTyp->Dock = System::Windows::Forms::DockStyle::Fill;
            this->labTyp->Location = System::Drawing::Point(48, 0);
            this->labTyp->Name = "labTyp";
            this->labTyp->Size = System::Drawing::Size(80, 14);
            this->labTyp->TabIndex = 1;
            this->labTyp->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            // 
            // label2
            // 
            this->label2->Dock = System::Windows::Forms::DockStyle::Left;
            this->label2->Location = System::Drawing::Point(0, 0);
            this->label2->Name = "label2";
            this->label2->Size = System::Drawing::Size(48, 14);
            this->label2->TabIndex = 0;
            this->label2->Text = "Typ";
            this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            // 
            // panel1
            // 
            this->panel1->Controls->Add(this->labCount);
            this->panel1->Controls->Add(this->label1);
            this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
            this->panel1->Location = System::Drawing::Point(0, 119);
            this->panel1->Name = "panel1";
            this->panel1->Size = System::Drawing::Size(128, 14);
            this->panel1->TabIndex = 2;
            // 
            // labCount
            // 
            this->labCount->Dock = System::Windows::Forms::DockStyle::Fill;
            this->labCount->Location = System::Drawing::Point(48, 0);
            this->labCount->Name = "labCount";
            this->labCount->Size = System::Drawing::Size(80, 14);
            this->labCount->TabIndex = 1;
            this->labCount->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            // 
            // label1
            // 
            this->label1->Dock = System::Windows::Forms::DockStyle::Left;
            this->label1->Location = System::Drawing::Point(0, 0);
            this->label1->Name = "label1";
            this->label1->Size = System::Drawing::Size(48, 14);
            this->label1->TabIndex = 0;
            this->label1->Text = "Count";
            this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            // 
            // listBxArrElem
            // 
            this->listBxArrElem->Dock = System::Windows::Forms::DockStyle::Top;
            this->listBxArrElem->Location = System::Drawing::Point(0, 24);
            this->listBxArrElem->Name = "listBxArrElem";
            this->listBxArrElem->Size = System::Drawing::Size(128, 95);
            this->listBxArrElem->TabIndex = 1;
						this->listBxArrElem->SelectedIndexChanged += gcnew System::EventHandler(this, &CArrayViewConfigForm::OnSelIndexChange);
            // 
            // panArrElemInfo1
            // 
            this->panArrElemInfo1->Controls->Add(this->label7);
            this->panArrElemInfo1->Dock = System::Windows::Forms::DockStyle::Top;
            this->panArrElemInfo1->Location = System::Drawing::Point(0, 0);
            this->panArrElemInfo1->Name = "panArrElemInfo1";
            this->panArrElemInfo1->Size = System::Drawing::Size(128, 24);
            this->panArrElemInfo1->TabIndex = 0;
            // 
            // label7
            // 
            this->label7->Dock = System::Windows::Forms::DockStyle::Fill;
            this->label7->Location = System::Drawing::Point(0, 0);
            this->label7->Name = "label7";
            this->label7->Size = System::Drawing::Size(128, 24);
            this->label7->TabIndex = 0;
            this->label7->Text = "Available Array Element";
            this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            // 
            // splitter1
            // 
            this->splitter1->Location = System::Drawing::Point(128, 0);
            this->splitter1->Name = "splitter1";
            this->splitter1->Size = System::Drawing::Size(7, 333);
            this->splitter1->TabIndex = 1;
            this->splitter1->TabStop = false;
            // 
            // panArrayElemAdd
            // 
            this->panArrayElemAdd->Controls->Add(this->listViewDetailInfo);
            this->panArrayElemAdd->Controls->Add(this->panArrElemInfo2);
            this->panArrayElemAdd->Dock = System::Windows::Forms::DockStyle::Fill;
            this->panArrayElemAdd->Location = System::Drawing::Point(135, 0);
            this->panArrayElemAdd->Name = "panArrayElemAdd";
            this->panArrayElemAdd->Size = System::Drawing::Size(433, 333);
            this->panArrayElemAdd->TabIndex = 2;
            // 
            // listViewDetailInfo
            // 
            this->listViewDetailInfo->Columns->AddRange(gcnew array< System::Windows::Forms::ColumnHeader^ >(1) {columnHeader1});
						this->listViewDetailInfo->Dock = System::Windows::Forms::DockStyle::Fill;
            this->listViewDetailInfo->FullRowSelect = true;
            this->listViewDetailInfo->LabelEdit = true;
            this->listViewDetailInfo->LabelWrap = false;
            this->listViewDetailInfo->Location = System::Drawing::Point(0, 22);
            this->listViewDetailInfo->MultiSelect = false;
            this->listViewDetailInfo->Name = "listViewDetailInfo";
            this->listViewDetailInfo->Size = System::Drawing::Size(433, 311);
            this->listViewDetailInfo->TabIndex = 1;
            this->listViewDetailInfo->View = System::Windows::Forms::View::Details;
						this->listViewDetailInfo->Leave += gcnew System::EventHandler(this, &CArrayViewConfigForm::OnListViewLeave);
            // 
            // columnHeader1
            // 
            this->columnHeader1->Text = "Name Of Row";
            this->columnHeader1->Width = 420;
            // 
            // panArrElemInfo2
            // 
            this->panArrElemInfo2->Controls->Add(this->button1);
            this->panArrElemInfo2->Controls->Add(this->butAdd);
            this->panArrElemInfo2->Controls->Add(this->labRowCount);
            this->panArrElemInfo2->Controls->Add(this->label4);
            this->panArrElemInfo2->Dock = System::Windows::Forms::DockStyle::Top;
            this->panArrElemInfo2->Location = System::Drawing::Point(0, 0);
            this->panArrElemInfo2->Name = "panArrElemInfo2";
            this->panArrElemInfo2->Size = System::Drawing::Size(433, 22);
            this->panArrElemInfo2->TabIndex = 0;
            // 
            // button1
            // 
            this->button1->Dock = System::Windows::Forms::DockStyle::Right;
            this->button1->Location = System::Drawing::Point(313, 0);
            this->button1->Name = "button1";
            this->button1->Size = System::Drawing::Size(64, 22);
            this->button1->TabIndex = 3;
            this->button1->Tag = "";
            this->button1->Text = "Remove";
						this->button1->Click += gcnew System::EventHandler(this, &CArrayViewConfigForm::OnButRemoteClick);
            // 
            // butAdd
            // 
            this->butAdd->Dock = System::Windows::Forms::DockStyle::Right;
            this->butAdd->Location = System::Drawing::Point(377, 0);
            this->butAdd->Name = "butAdd";
            this->butAdd->Size = System::Drawing::Size(56, 22);
            this->butAdd->TabIndex = 2;
            this->butAdd->Text = "Add";
						this->butAdd->Click += gcnew System::EventHandler(this, &CArrayViewConfigForm::OnButAddClick);
            // 
            // labRowCount
            // 
            this->labRowCount->Dock = System::Windows::Forms::DockStyle::Left;
            this->labRowCount->Location = System::Drawing::Point(64, 0);
            this->labRowCount->Name = "labRowCount";
            this->labRowCount->Size = System::Drawing::Size(56, 22);
            this->labRowCount->TabIndex = 1;
            this->labRowCount->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            // 
            // label4
            // 
            this->label4->Dock = System::Windows::Forms::DockStyle::Left;
            this->label4->Location = System::Drawing::Point(0, 0);
            this->label4->Name = "label4";
            this->label4->Size = System::Drawing::Size(64, 22);
            this->label4->TabIndex = 0;
            this->label4->Text = "Row Count";
            this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            // 
            // CArrayViewConfigForm
            // 
            this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
            this->ClientSize = System::Drawing::Size(568, 333);
            this->Controls->Add(this->panArrayElemAdd);
            this->Controls->Add(this->splitter1);
            this->Controls->Add(this->panArrayElemView);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->Name = "CArrayViewConfigForm";
            this->Text = "CArrayViewConfigForm";
            this->panArrayElemView->ResumeLayout(false);
            this->panel4->ResumeLayout(false);
            this->panel3->ResumeLayout(false);
            this->panel2->ResumeLayout(false);
            this->panel1->ResumeLayout(false);
            this->panArrElemInfo1->ResumeLayout(false);
            this->panArrayElemAdd->ResumeLayout(false);
            this->panArrElemInfo2->ResumeLayout(false);
            this->ResumeLayout(false);

        }		
        //------------------------------------------------------------------
        System::Void OnSelIndexChange(System::Object ^  sender, System::EventArgs ^  e);
        System::Void OnButAddClick(System::Object ^  sender, System::EventArgs ^  e);
        System::Void OnButRemoteClick(System::Object ^  sender, System::EventArgs ^  e);
        System::Void CArrayViewConfigForm::OnListViewLeave(System::Object ^  sender, System::EventArgs ^  e);
        //-------------------------------------------------------------------

        CTlgInterfaceWrapper^ Interface;
        ArrayList^ InterInfo;

        void updateViewFromConfFile();
        bool readInterInfoFromConfFile();
        void showInterInfo();
        void showRowDetailInfo();
		void removeRow(String^ elemName,int index);
};
}
