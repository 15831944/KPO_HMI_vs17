#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace simulator {

	/// <summary>
	/// Summary for CAppSettingsForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CAppSettingsForm : public System::Windows::Forms::Form
	{
	public:
		CAppSettingsForm(void)
		{
			InitializeComponent();
			initComp();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CAppSettingsForm()
		{
			/*if (components)
			{
				delete components;
			}*/
		}
  private: System::Windows::Forms::Panel^  PanUpView;
  private: System::Windows::Forms::TabControl^  TabControl;
  private: System::Windows::Forms::TabPage^  TabLogFilesPage;
  private: System::Windows::Forms::Splitter^  splitter1;
  private: System::Windows::Forms::Panel^  PanDownView;
  private: System::Windows::Forms::Button^  ButCancel;
  private: System::Windows::Forms::Button^  ButOk;
  private: System::Windows::Forms::Label^  LabMaxLogFilesCount;
  private: System::Windows::Forms::Label^  LabMaxSizeUnit;
  private: System::Windows::Forms::Label^  labMaxSize;
  private: System::Windows::Forms::GroupBox^  grpBxMessage;
  private: System::Windows::Forms::CheckBox^  chkBoxError;
  private: System::Windows::Forms::CheckBox^  chkBoxInfo;
  private: System::Windows::Forms::CheckBox^  chkBoxWarning;
  private: System::Windows::Forms::NumericUpDown^  numMaxSize;
  private: System::Windows::Forms::TabPage^  TabTlgViewPage;
  private: System::Windows::Forms::GroupBox^  grpBoxNodesCol;
  private: System::Windows::Forms::RadioButton^  radExpandBut;
  private: System::Windows::Forms::RadioButton^  radCollapseBut;
  private: System::Windows::Forms::RadioButton^  radCollapseAllBut;
  private: System::Windows::Forms::NumericUpDown^  numMaxCount;
  private: System::Void ButOk_Click(System::Object^  sender, System::EventArgs^  e);
  private: System::Void ButCancel_Click(System::Object^  sender, System::EventArgs^  e);
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

    void initComp();
    void initToolTips();

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      this->PanUpView = (gcnew System::Windows::Forms::Panel());
      this->TabControl = (gcnew System::Windows::Forms::TabControl());
      this->TabLogFilesPage = (gcnew System::Windows::Forms::TabPage());
      this->numMaxCount = (gcnew System::Windows::Forms::NumericUpDown());
      this->numMaxSize = (gcnew System::Windows::Forms::NumericUpDown());
      this->grpBxMessage = (gcnew System::Windows::Forms::GroupBox());
      this->chkBoxError = (gcnew System::Windows::Forms::CheckBox());
      this->chkBoxInfo = (gcnew System::Windows::Forms::CheckBox());
      this->chkBoxWarning = (gcnew System::Windows::Forms::CheckBox());
      this->LabMaxLogFilesCount = (gcnew System::Windows::Forms::Label());
      this->LabMaxSizeUnit = (gcnew System::Windows::Forms::Label());
      this->labMaxSize = (gcnew System::Windows::Forms::Label());
      this->TabTlgViewPage = (gcnew System::Windows::Forms::TabPage());
      this->grpBoxNodesCol = (gcnew System::Windows::Forms::GroupBox());
      this->radCollapseAllBut = (gcnew System::Windows::Forms::RadioButton());
      this->radExpandBut = (gcnew System::Windows::Forms::RadioButton());
      this->radCollapseBut = (gcnew System::Windows::Forms::RadioButton());
      this->splitter1 = (gcnew System::Windows::Forms::Splitter());
      this->PanDownView = (gcnew System::Windows::Forms::Panel());
      this->ButCancel = (gcnew System::Windows::Forms::Button());
      this->ButOk = (gcnew System::Windows::Forms::Button());
      this->PanUpView->SuspendLayout();
      this->TabControl->SuspendLayout();
      this->TabLogFilesPage->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numMaxCount))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numMaxSize))->BeginInit();
      this->grpBxMessage->SuspendLayout();
      this->TabTlgViewPage->SuspendLayout();
      this->grpBoxNodesCol->SuspendLayout();
      this->PanDownView->SuspendLayout();
      this->SuspendLayout();
      // 
      // PanUpView
      // 
      this->PanUpView->Controls->Add(this->TabControl);
      this->PanUpView->Dock = System::Windows::Forms::DockStyle::Top;
      this->PanUpView->Location = System::Drawing::Point(0, 0);
      this->PanUpView->Name = L"PanUpView";
      this->PanUpView->Size = System::Drawing::Size(324, 190);
      this->PanUpView->TabIndex = 0;
      // 
      // TabControl
      // 
      this->TabControl->Controls->Add(this->TabLogFilesPage);
      this->TabControl->Controls->Add(this->TabTlgViewPage);
      this->TabControl->Dock = System::Windows::Forms::DockStyle::Fill;
      this->TabControl->Location = System::Drawing::Point(0, 0);
      this->TabControl->Name = L"TabControl";
      this->TabControl->SelectedIndex = 0;
      this->TabControl->Size = System::Drawing::Size(324, 190);
      this->TabControl->TabIndex = 0;
      // 
      // TabLogFilesPage
      // 
      this->TabLogFilesPage->Controls->Add(this->numMaxCount);
      this->TabLogFilesPage->Controls->Add(this->numMaxSize);
      this->TabLogFilesPage->Controls->Add(this->grpBxMessage);
      this->TabLogFilesPage->Controls->Add(this->LabMaxLogFilesCount);
      this->TabLogFilesPage->Controls->Add(this->LabMaxSizeUnit);
      this->TabLogFilesPage->Controls->Add(this->labMaxSize);
      this->TabLogFilesPage->Location = System::Drawing::Point(4, 22);
      this->TabLogFilesPage->Name = L"TabLogFilesPage";
      this->TabLogFilesPage->Padding = System::Windows::Forms::Padding(3);
      this->TabLogFilesPage->Size = System::Drawing::Size(316, 164);
      this->TabLogFilesPage->TabIndex = 0;
      this->TabLogFilesPage->Text = L"Log - Files";
      this->TabLogFilesPage->UseVisualStyleBackColor = true;
      // 
      // numMaxCount
      // 
      this->numMaxCount->Location = System::Drawing::Point(161, 52);
      this->numMaxCount->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      this->numMaxCount->Name = L"numMaxCount";
      this->numMaxCount->Size = System::Drawing::Size(48, 20);
      this->numMaxCount->TabIndex = 7;
      this->numMaxCount->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      // 
      // numMaxSize
      // 
      this->numMaxSize->Location = System::Drawing::Point(161, 17);
      this->numMaxSize->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {20, 0, 0, 0});
      this->numMaxSize->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      this->numMaxSize->Name = L"numMaxSize";
      this->numMaxSize->Size = System::Drawing::Size(48, 20);
      this->numMaxSize->TabIndex = 6;
      this->numMaxSize->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      // 
      // grpBxMessage
      // 
      this->grpBxMessage->Controls->Add(this->chkBoxError);
      this->grpBxMessage->Controls->Add(this->chkBoxInfo);
      this->grpBxMessage->Controls->Add(this->chkBoxWarning);
      this->grpBxMessage->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->grpBxMessage->Location = System::Drawing::Point(3, 89);
      this->grpBxMessage->Name = L"grpBxMessage";
      this->grpBxMessage->Size = System::Drawing::Size(310, 72);
      this->grpBxMessage->TabIndex = 5;
      this->grpBxMessage->TabStop = false;
      this->grpBxMessage->Text = L"Messagetyps in log-file";
      // 
      // chkBoxError
      // 
      this->chkBoxError->AutoSize = true;
      this->chkBoxError->Location = System::Drawing::Point(244, 33);
      this->chkBoxError->Name = L"chkBoxError";
      this->chkBoxError->Size = System::Drawing::Size(48, 17);
      this->chkBoxError->TabIndex = 3;
      this->chkBoxError->Text = L"Error";
      this->chkBoxError->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
      this->chkBoxError->UseVisualStyleBackColor = true;
      // 
      // chkBoxInfo
      // 
      this->chkBoxInfo->AutoSize = true;
      this->chkBoxInfo->Location = System::Drawing::Point(17, 33);
      this->chkBoxInfo->Name = L"chkBoxInfo";
      this->chkBoxInfo->Size = System::Drawing::Size(75, 17);
      this->chkBoxInfo->TabIndex = 2;
      this->chkBoxInfo->Text = L"Infomation";
      this->chkBoxInfo->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
      this->chkBoxInfo->UseVisualStyleBackColor = true;
      // 
      // chkBoxWarning
      // 
      this->chkBoxWarning->AutoSize = true;
      this->chkBoxWarning->Location = System::Drawing::Point(132, 33);
      this->chkBoxWarning->Name = L"chkBoxWarning";
      this->chkBoxWarning->Size = System::Drawing::Size(66, 17);
      this->chkBoxWarning->TabIndex = 1;
      this->chkBoxWarning->Text = L"Warning";
      this->chkBoxWarning->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
      this->chkBoxWarning->UseVisualStyleBackColor = true;
      // 
      // LabMaxLogFilesCount
      // 
      this->LabMaxLogFilesCount->AutoSize = true;
      this->LabMaxLogFilesCount->Location = System::Drawing::Point(38, 54);
      this->LabMaxLogFilesCount->Name = L"LabMaxLogFilesCount";
      this->LabMaxLogFilesCount->Size = System::Drawing::Size(117, 13);
      this->LabMaxLogFilesCount->TabIndex = 2;
      this->LabMaxLogFilesCount->Text = L"Max. count of log - file :";
      // 
      // LabMaxSizeUnit
      // 
      this->LabMaxSizeUnit->AutoSize = true;
      this->LabMaxSizeUnit->Location = System::Drawing::Point(216, 19);
      this->LabMaxSizeUnit->Name = L"LabMaxSizeUnit";
      this->LabMaxSizeUnit->Size = System::Drawing::Size(23, 13);
      this->LabMaxSizeUnit->TabIndex = 1;
      this->LabMaxSizeUnit->Text = L"MB";
      // 
      // labMaxSize
      // 
      this->labMaxSize->AutoSize = true;
      this->labMaxSize->Location = System::Drawing::Point(47, 19);
      this->labMaxSize->Name = L"labMaxSize";
      this->labMaxSize->Size = System::Drawing::Size(108, 13);
      this->labMaxSize->TabIndex = 0;
      this->labMaxSize->Text = L"Max. size of log - file :";
      // 
      // TabTlgViewPage
      // 
      this->TabTlgViewPage->Controls->Add(this->grpBoxNodesCol);
      this->TabTlgViewPage->Location = System::Drawing::Point(4, 22);
      this->TabTlgViewPage->Name = L"TabTlgViewPage";
      this->TabTlgViewPage->Size = System::Drawing::Size(316, 164);
      this->TabTlgViewPage->TabIndex = 1;
      this->TabTlgViewPage->Text = L"Telegram View";
      this->TabTlgViewPage->UseVisualStyleBackColor = true;
      // 
      // grpBoxNodesCol
      // 
      this->grpBoxNodesCol->Controls->Add(this->radCollapseAllBut);
      this->grpBoxNodesCol->Controls->Add(this->radExpandBut);
      this->grpBoxNodesCol->Controls->Add(this->radCollapseBut);
      this->grpBoxNodesCol->Dock = System::Windows::Forms::DockStyle::Top;
      this->grpBoxNodesCol->Location = System::Drawing::Point(0, 0);
      this->grpBoxNodesCol->Name = L"grpBoxNodesCol";
      this->grpBoxNodesCol->Size = System::Drawing::Size(316, 92);
      this->grpBoxNodesCol->TabIndex = 0;
      this->grpBoxNodesCol->TabStop = false;
      this->grpBoxNodesCol->Text = L"Elements View";
      // 
      // radCollapseAllBut
      // 
      this->radCollapseAllBut->AutoSize = true;
      this->radCollapseAllBut->Location = System::Drawing::Point(18, 42);
      this->radCollapseAllBut->Name = L"radCollapseAllBut";
      this->radCollapseAllBut->Size = System::Drawing::Size(84, 17);
      this->radCollapseAllBut->TabIndex = 2;
      this->radCollapseAllBut->TabStop = true;
      this->radCollapseAllBut->Text = L"Collapsed all";
      this->radCollapseAllBut->UseVisualStyleBackColor = true;
      // 
      // radExpandBut
      // 
      this->radExpandBut->AutoSize = true;
      this->radExpandBut->Location = System::Drawing::Point(18, 65);
      this->radExpandBut->Name = L"radExpandBut";
      this->radExpandBut->Size = System::Drawing::Size(86, 17);
      this->radExpandBut->TabIndex = 1;
      this->radExpandBut->TabStop = true;
      this->radExpandBut->Text = L"Expanded all";
      this->radExpandBut->UseVisualStyleBackColor = true;
      // 
      // radCollapseBut
      // 
      this->radCollapseBut->AutoSize = true;
      this->radCollapseBut->Location = System::Drawing::Point(18, 19);
      this->radCollapseBut->Name = L"radCollapseBut";
      this->radCollapseBut->Size = System::Drawing::Size(160, 17);
      this->radCollapseBut->TabIndex = 0;
      this->radCollapseBut->TabStop = true;
      this->radCollapseBut->Text = L"Collapsed except the header";
      this->radCollapseBut->UseVisualStyleBackColor = true;
      // 
      // splitter1
      // 
      this->splitter1->Dock = System::Windows::Forms::DockStyle::Top;
      this->splitter1->Location = System::Drawing::Point(0, 190);
      this->splitter1->Name = L"splitter1";
      this->splitter1->Size = System::Drawing::Size(324, 3);
      this->splitter1->TabIndex = 1;
      this->splitter1->TabStop = false;
      // 
      // PanDownView
      // 
      this->PanDownView->Controls->Add(this->ButCancel);
      this->PanDownView->Controls->Add(this->ButOk);
      this->PanDownView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->PanDownView->Location = System::Drawing::Point(0, 193);
      this->PanDownView->Name = L"PanDownView";
      this->PanDownView->Size = System::Drawing::Size(324, 33);
      this->PanDownView->TabIndex = 2;
      // 
      // ButCancel
      // 
      this->ButCancel->Location = System::Drawing::Point(63, 5);
      this->ButCancel->Name = L"ButCancel";
      this->ButCancel->Size = System::Drawing::Size(75, 23);
      this->ButCancel->TabIndex = 1;
      this->ButCancel->Text = L"Cancel";
      this->ButCancel->UseVisualStyleBackColor = true;
      this->ButCancel->Click += gcnew System::EventHandler(this, &CAppSettingsForm::ButCancel_Click);
      // 
      // ButOk
      // 
      this->ButOk->Location = System::Drawing::Point(177, 6);
      this->ButOk->Name = L"ButOk";
      this->ButOk->Size = System::Drawing::Size(75, 23);
      this->ButOk->TabIndex = 0;
      this->ButOk->Text = L"Ok";
      this->ButOk->UseVisualStyleBackColor = true;
      this->ButOk->Click += gcnew System::EventHandler(this, &CAppSettingsForm::ButOk_Click);
      // 
      // CAppSettingsForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(324, 226);
      this->ControlBox = false;
      this->Controls->Add(this->PanDownView);
      this->Controls->Add(this->splitter1);
      this->Controls->Add(this->PanUpView);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
      this->Name = L"CAppSettingsForm";
      this->Text = L"Application configuration";
      this->PanUpView->ResumeLayout(false);
      this->TabControl->ResumeLayout(false);
      this->TabLogFilesPage->ResumeLayout(false);
      this->TabLogFilesPage->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numMaxCount))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numMaxSize))->EndInit();
      this->grpBxMessage->ResumeLayout(false);
      this->grpBxMessage->PerformLayout();
      this->TabTlgViewPage->ResumeLayout(false);
      this->grpBoxNodesCol->ResumeLayout(false);
      this->grpBoxNodesCol->PerformLayout();
      this->PanDownView->ResumeLayout(false);
      this->ResumeLayout(false);

    }
#pragma endregion
};
}
