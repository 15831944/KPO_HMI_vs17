#pragma once
#include "CItemBaseContainerWrapper.h"
#include "CTlgInterfaceWrapper.h"
#include "CTlgLogFileReaderWrapper.h"
#include "CProgressBarViewForm.h"
#include "CLogWriterWrapper.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Collections::Generic;

namespace simulator {

	/// <summary>
	/// Summary for CAutoCreateSzenarioForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CAutoCreateSzenarioForm : public System::Windows::Forms::Form
	{
    public: delegate void AddToSzenDelTyp(CItemWrapper^ wrp,double time,bool modi);
    public: delegate void CloseSzenDelTyp();
	public:
		CAutoCreateSzenarioForm(List<CItemBaseContainerWrapper^>^ LogFileContainer,List<CTlgInterfaceWrapper^>^ InterfaceContainer)
		{
			InitializeComponent();
      this->LogFileContainer = LogFileContainer;
      this->InterfaceContainer = InterfaceContainer;
      this->CondPanCon = gcnew List<Panel^>();
      init();
		}

  public: void setAddToSzenDelTyp(AddToSzenDelTyp^ typ){
            this->AddToSzenDel = typ;}
  public: void setCloseSzenDelTyp(CloseSzenDelTyp^ typ){ 
            this->CloseSzenDel = typ;}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CAutoCreateSzenarioForm()
		{
			if (components)
			{
				delete components;
			}
		}

  private: void init();

  private: System::Windows::Forms::Panel^  panSourceView;
  private: System::Windows::Forms::GroupBox^  grSorceBox;
  private: System::Windows::Forms::Panel^  panOptionsView;
  private: System::Windows::Forms::GroupBox^  grBox;
  private: System::Windows::Forms::Panel^  panButtonsView;
  private: System::Windows::Forms::Panel^  panConditionsView;
  private: System::Windows::Forms::GroupBox^  gpSourceInfoBox;
  private: System::Windows::Forms::Button^  butLoadLogFile;
  private: System::Windows::Forms::Label^  labCountOfTlgsValue;
  private: System::Windows::Forms::Label^  labCountOfTlgs;
  private: System::Windows::Forms::Label^  labInterInfoValue;
  private: System::Windows::Forms::Label^  labInterInfo;

  private: System::Windows::Forms::RadioButton^  radExistedSzenarioBut;
  private: System::Windows::Forms::RadioButton^  radNewSzenarioBut;
  private: System::Windows::Forms::Button^  butCancel;
  private: System::Windows::Forms::Button^  butApply;
  private: System::Windows::Forms::Panel^  panConditionsTopView;
  private: System::Windows::Forms::ComboBox^  cmbCondTypBox;
  private: System::Windows::Forms::Panel^  panCondFillView;
  private: System::Windows::Forms::Label^  labInfoCondTypeView;

  private: System::Windows::Forms::ComboBox^  cmbSourceBox;

  private: void OpenLogFile();
  private: void LoadLogFileInThread (Object^ path);
  private: CTlgInterfaceWrapper^ DetectInterface(CItemBaseContainerWrapper^ con);
  private: void AbortLogFileReadThread();
  private: void initToolTips();

  private: void WriteLogFileInfo(CItemBaseContainerWrapper^ logFile);
  private: List<CItemBaseContainerWrapper^>^ LogFileContainer;
  private: List<CTlgInterfaceWrapper^>^ InterfaceContainer;
  private: CTlgInterfaceWrapper^ ActiveInterface;

  private: CTlgLogFileReaderWrapper^ LogFileReader;
  private: CProgressBarViewForm^ barView;

  private: List<System::Windows::Forms::Panel^>^ CondPanCon;
  private: SimGuiDialogs::CMultiFilterForm^ mMultiFilterForm;
  private: SimGuiDialogs::CPositionCondForm^ mPositionCondForm;

  private: AddToSzenDelTyp^ AddToSzenDel;
  private: CloseSzenDelTyp^ CloseSzenDel;
	private: CLogWriterWrapper^ logWriter;
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
      this->panSourceView = (gcnew System::Windows::Forms::Panel());
      this->grSorceBox = (gcnew System::Windows::Forms::GroupBox());
      this->gpSourceInfoBox = (gcnew System::Windows::Forms::GroupBox());
      this->labInterInfo = (gcnew System::Windows::Forms::Label());
      this->labInterInfoValue = (gcnew System::Windows::Forms::Label());
      this->labCountOfTlgsValue = (gcnew System::Windows::Forms::Label());
      this->labCountOfTlgs = (gcnew System::Windows::Forms::Label());
      this->butLoadLogFile = (gcnew System::Windows::Forms::Button());
      this->cmbSourceBox = (gcnew System::Windows::Forms::ComboBox());
      this->panOptionsView = (gcnew System::Windows::Forms::Panel());
      this->grBox = (gcnew System::Windows::Forms::GroupBox());
      this->labInfoCondTypeView = (gcnew System::Windows::Forms::Label());
      this->cmbCondTypBox = (gcnew System::Windows::Forms::ComboBox());
      this->radNewSzenarioBut = (gcnew System::Windows::Forms::RadioButton());
      this->radExistedSzenarioBut = (gcnew System::Windows::Forms::RadioButton());
      this->panButtonsView = (gcnew System::Windows::Forms::Panel());
      this->butCancel = (gcnew System::Windows::Forms::Button());
      this->butApply = (gcnew System::Windows::Forms::Button());
      this->panConditionsView = (gcnew System::Windows::Forms::Panel());
      this->panCondFillView = (gcnew System::Windows::Forms::Panel());
      this->panConditionsTopView = (gcnew System::Windows::Forms::Panel());
      this->panSourceView->SuspendLayout();
      this->grSorceBox->SuspendLayout();
      this->gpSourceInfoBox->SuspendLayout();
      this->panOptionsView->SuspendLayout();
      this->grBox->SuspendLayout();
      this->panButtonsView->SuspendLayout();
      this->panConditionsView->SuspendLayout();
      this->SuspendLayout();
      // 
      // panSourceView
      // 
      this->panSourceView->Controls->Add(this->grSorceBox);
      this->panSourceView->Dock = System::Windows::Forms::DockStyle::Top;
      this->panSourceView->Location = System::Drawing::Point(0, 0);
      this->panSourceView->Name = L"panSourceView";
      this->panSourceView->Size = System::Drawing::Size(568, 103);
      this->panSourceView->TabIndex = 0;
      // 
      // grSorceBox
      // 
      this->grSorceBox->Controls->Add(this->gpSourceInfoBox);
      this->grSorceBox->Controls->Add(this->butLoadLogFile);
      this->grSorceBox->Controls->Add(this->cmbSourceBox);
      this->grSorceBox->Dock = System::Windows::Forms::DockStyle::Fill;
      this->grSorceBox->Location = System::Drawing::Point(0, 0);
      this->grSorceBox->Name = L"grSorceBox";
      this->grSorceBox->Size = System::Drawing::Size(568, 103);
      this->grSorceBox->TabIndex = 0;
      this->grSorceBox->TabStop = false;
      this->grSorceBox->Text = L"Source";
      // 
      // gpSourceInfoBox
      // 
      this->gpSourceInfoBox->Controls->Add(this->labInterInfo);
      this->gpSourceInfoBox->Controls->Add(this->labInterInfoValue);
      this->gpSourceInfoBox->Controls->Add(this->labCountOfTlgsValue);
      this->gpSourceInfoBox->Controls->Add(this->labCountOfTlgs);
      this->gpSourceInfoBox->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->gpSourceInfoBox->Location = System::Drawing::Point(3, 46);
      this->gpSourceInfoBox->Name = L"gpSourceInfoBox";
      this->gpSourceInfoBox->Size = System::Drawing::Size(562, 54);
      this->gpSourceInfoBox->TabIndex = 2;
      this->gpSourceInfoBox->TabStop = false;
      this->gpSourceInfoBox->Text = L"Source Information";
      // 
      // labInterInfo
      // 
      this->labInterInfo->Location = System::Drawing::Point(9, 29);
      this->labInterInfo->Name = L"labInterInfo";
      this->labInterInfo->Size = System::Drawing::Size(106, 17);
      this->labInterInfo->TabIndex = 3;
      this->labInterInfo->Text = L"Name of Interface :";
      // 
      // labInterInfoValue
      // 
      this->labInterInfoValue->AutoSize = true;
      this->labInterInfoValue->Location = System::Drawing::Point(114, 29);
      this->labInterInfoValue->Name = L"labInterInfoValue";
      this->labInterInfoValue->Size = System::Drawing::Size(33, 13);
      this->labInterInfoValue->TabIndex = 2;
      this->labInterInfoValue->Text = L"value";
      // 
      // labCountOfTlgsValue
      // 
      this->labCountOfTlgsValue->AutoSize = true;
      this->labCountOfTlgsValue->Location = System::Drawing::Point(114, 16);
      this->labCountOfTlgsValue->Name = L"labCountOfTlgsValue";
      this->labCountOfTlgsValue->Size = System::Drawing::Size(33, 13);
      this->labCountOfTlgsValue->TabIndex = 1;
      this->labCountOfTlgsValue->Text = L"value";
      // 
      // labCountOfTlgs
      // 
      this->labCountOfTlgs->Location = System::Drawing::Point(9, 16);
      this->labCountOfTlgs->Name = L"labCountOfTlgs";
      this->labCountOfTlgs->Size = System::Drawing::Size(85, 13);
      this->labCountOfTlgs->TabIndex = 0;
      this->labCountOfTlgs->Text = L"Count of Tlgs :";
      // 
      // butLoadLogFile
      // 
      this->butLoadLogFile->Location = System::Drawing::Point(497, 19);
      this->butLoadLogFile->Name = L"butLoadLogFile";
      this->butLoadLogFile->Size = System::Drawing::Size(68, 23);
      this->butLoadLogFile->TabIndex = 1;
      this->butLoadLogFile->Text = L"Load";
      this->butLoadLogFile->UseVisualStyleBackColor = true;
      this->butLoadLogFile->Click += gcnew System::EventHandler(this, &CAutoCreateSzenarioForm::butLoadLogFile_Click);
      // 
      // cmbSourceBox
      // 
      this->cmbSourceBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cmbSourceBox->FormattingEnabled = true;
      this->cmbSourceBox->Location = System::Drawing::Point(12, 19);
      this->cmbSourceBox->Name = L"cmbSourceBox";
      this->cmbSourceBox->Size = System::Drawing::Size(479, 21);
      this->cmbSourceBox->TabIndex = 0;
      // 
      // panOptionsView
      // 
      this->panOptionsView->Controls->Add(this->grBox);
      this->panOptionsView->Dock = System::Windows::Forms::DockStyle::Top;
      this->panOptionsView->Location = System::Drawing::Point(0, 103);
      this->panOptionsView->Name = L"panOptionsView";
      this->panOptionsView->Size = System::Drawing::Size(568, 80);
      this->panOptionsView->TabIndex = 1;
      // 
      // grBox
      // 
      this->grBox->Controls->Add(this->labInfoCondTypeView);
      this->grBox->Controls->Add(this->cmbCondTypBox);
      this->grBox->Controls->Add(this->radNewSzenarioBut);
      this->grBox->Controls->Add(this->radExistedSzenarioBut);
      this->grBox->Dock = System::Windows::Forms::DockStyle::Fill;
      this->grBox->Location = System::Drawing::Point(0, 0);
      this->grBox->Name = L"grBox";
      this->grBox->Size = System::Drawing::Size(568, 80);
      this->grBox->TabIndex = 0;
      this->grBox->TabStop = false;
      this->grBox->Text = L"Options";
      // 
      // labInfoCondTypeView
      // 
      this->labInfoCondTypeView->AutoSize = true;
      this->labInfoCondTypeView->Location = System::Drawing::Point(12, 50);
      this->labInfoCondTypeView->Name = L"labInfoCondTypeView";
      this->labInfoCondTypeView->Size = System::Drawing::Size(149, 13);
      this->labInfoCondTypeView->TabIndex = 2;
      this->labInfoCondTypeView->Text = L"Kind of filter for telegram name";
      // 
      // cmbCondTypBox
      // 
      this->cmbCondTypBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cmbCondTypBox->FormattingEnabled = true;
      this->cmbCondTypBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Reg. exp.", L"Positions"});
      this->cmbCondTypBox->Location = System::Drawing::Point(178, 47);
      this->cmbCondTypBox->Name = L"cmbCondTypBox";
      this->cmbCondTypBox->Size = System::Drawing::Size(154, 21);
      this->cmbCondTypBox->TabIndex = 0;
      this->cmbCondTypBox->SelectedIndexChanged += gcnew System::EventHandler(this, &CAutoCreateSzenarioForm::cmbCondTypBox_SelectedIndexChanged);
      // 
      // radNewSzenarioBut
      // 
      this->radNewSzenarioBut->AutoSize = true;
      this->radNewSzenarioBut->Location = System::Drawing::Point(15, 19);
      this->radNewSzenarioBut->Name = L"radNewSzenarioBut";
      this->radNewSzenarioBut->Size = System::Drawing::Size(102, 17);
      this->radNewSzenarioBut->TabIndex = 1;
      this->radNewSzenarioBut->Text = L"As new szenario";
      this->radNewSzenarioBut->UseVisualStyleBackColor = true;
      // 
      // radExistedSzenarioBut
      // 
      this->radExistedSzenarioBut->AutoSize = true;
      this->radExistedSzenarioBut->Checked = true;
      this->radExistedSzenarioBut->Location = System::Drawing::Point(178, 19);
      this->radExistedSzenarioBut->Name = L"radExistedSzenarioBut";
      this->radExistedSzenarioBut->Size = System::Drawing::Size(133, 17);
      this->radExistedSzenarioBut->TabIndex = 0;
      this->radExistedSzenarioBut->TabStop = true;
      this->radExistedSzenarioBut->Text = L"Add to loaded szenario";
      this->radExistedSzenarioBut->UseVisualStyleBackColor = true;
      // 
      // panButtonsView
      // 
      this->panButtonsView->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->panButtonsView->Controls->Add(this->butCancel);
      this->panButtonsView->Controls->Add(this->butApply);
      this->panButtonsView->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->panButtonsView->Location = System::Drawing::Point(0, 542);
      this->panButtonsView->Name = L"panButtonsView";
      this->panButtonsView->Size = System::Drawing::Size(568, 32);
      this->panButtonsView->TabIndex = 2;
      // 
      // butCancel
      // 
      this->butCancel->Location = System::Drawing::Point(496, 3);
      this->butCancel->Name = L"butCancel";
      this->butCancel->Size = System::Drawing::Size(68, 23);
      this->butCancel->TabIndex = 1;
      this->butCancel->Text = L"Close";
      this->butCancel->UseVisualStyleBackColor = true;
      this->butCancel->Click += gcnew System::EventHandler(this, &CAutoCreateSzenarioForm::butCancel_Click);
      // 
      // butApply
      // 
      this->butApply->Location = System::Drawing::Point(422, 3);
      this->butApply->Name = L"butApply";
      this->butApply->Size = System::Drawing::Size(68, 23);
      this->butApply->TabIndex = 0;
      this->butApply->Text = L"Apply";
      this->butApply->UseVisualStyleBackColor = true;
      this->butApply->Click += gcnew System::EventHandler(this, &CAutoCreateSzenarioForm::butApply_Click);
      // 
      // panConditionsView
      // 
      this->panConditionsView->Controls->Add(this->panCondFillView);
      this->panConditionsView->Controls->Add(this->panConditionsTopView);
      this->panConditionsView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panConditionsView->Location = System::Drawing::Point(0, 183);
      this->panConditionsView->Name = L"panConditionsView";
      this->panConditionsView->Size = System::Drawing::Size(568, 359);
      this->panConditionsView->TabIndex = 3;
      // 
      // panCondFillView
      // 
      this->panCondFillView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panCondFillView->Location = System::Drawing::Point(0, 0);
      this->panCondFillView->Name = L"panCondFillView";
      this->panCondFillView->Size = System::Drawing::Size(568, 359);
      this->panCondFillView->TabIndex = 1;
      // 
      // panConditionsTopView
      // 
      this->panConditionsTopView->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->panConditionsTopView->Dock = System::Windows::Forms::DockStyle::Top;
      this->panConditionsTopView->Location = System::Drawing::Point(0, 0);
      this->panConditionsTopView->Name = L"panConditionsTopView";
      this->panConditionsTopView->Size = System::Drawing::Size(568, 0);
      this->panConditionsTopView->TabIndex = 0;
      // 
      // CAutoCreateSzenarioForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(568, 574);
      this->Controls->Add(this->panConditionsView);
      this->Controls->Add(this->panButtonsView);
      this->Controls->Add(this->panOptionsView);
      this->Controls->Add(this->panSourceView);
      this->Name = L"CAutoCreateSzenarioForm";
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
      this->Text = L"CAutoCreateSzenarioForm";
      this->panSourceView->ResumeLayout(false);
      this->grSorceBox->ResumeLayout(false);
      this->gpSourceInfoBox->ResumeLayout(false);
      this->gpSourceInfoBox->PerformLayout();
      this->panOptionsView->ResumeLayout(false);
      this->grBox->ResumeLayout(false);
      this->grBox->PerformLayout();
      this->panButtonsView->ResumeLayout(false);
      this->panConditionsView->ResumeLayout(false);
      this->ResumeLayout(false);

    }
#pragma endregion
  private: System::Void cmbSourceBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
  private: System::Void butLoadLogFile_Click(System::Object^  sender, System::EventArgs^  e);
  private: System::Void butCancel_Click(System::Object^  sender, System::EventArgs^  e);
  private: System::Void butApply_Click(System::Object^  sender, System::EventArgs^  e);
  private: System::Void cmbCondTypBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
};
}
