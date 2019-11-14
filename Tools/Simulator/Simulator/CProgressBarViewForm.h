#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

//#include "CProgressBarStatusWriter.h"


using namespace System;

#undef GetObject

namespace simulator
{
	/// <summary> 
	/// Summary for CProgressBarViewForm
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CProgressBarViewForm : public System::Windows::Forms::Form
	{
	
  public: delegate void BarViewAbortDelTyp();
  
  public: 
		CProgressBarViewForm(long min, __int64 max)
		{
			InitializeComponent();
      minimum=0;
      maximum=0;
      totalStep=0;
      restDif=0;
      formClosed = false;
      BarViewAbortEvent=nullptr;
      /* pictureBoxView->Image = Image::FromFile("Animation\\GUI_Simulator\\progress.gif");*/
		}

    CProgressBarViewForm()
		{
			InitializeComponent();
      minimum=0;
      maximum=0;
      totalStep=0;
      restDif=0;
      formClosed = false;
      BarViewAbortEvent=nullptr;
      /*  panAfterInfoView->Hide();*/
      /*pictureBoxView->Image = Image::FromFile("X:\\EXT1\\source\\Tools\\Simulator\\Simulator\\Animation\\GUI_Simulator\\progress.gif");*/
		}
    
    void setMinAndMax(long min,__int64 max);
    void updateStep(long step);
    void setSourceLab(String^ source);
    bool isFormClosed();
    void setCancelButtonVisible(bool mode);
    void setBarViewAbortDelTyp(BarViewAbortDelTyp^ event);
    void setAfterInfoView();
    void Close();
	protected: 
		//void Dispose(Boolean disposing)
		//{
		//	if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}
  private: System::Windows::Forms::ProgressBar ^  progressBar;
  private: System::Windows::Forms::Button ^  butCancel;
  private: System::Windows::Forms::Label ^  labSource;
  private: System::Windows::Forms::Panel ^  panSourceView;
  private: System::Windows::Forms::Panel ^  panCancelView;

  private: System::Windows::Forms::Label ^  labPerCentView;
  private: System::Windows::Forms::Panel ^  panProgressView;
  private: System::Windows::Forms::Label ^  label1;
  private: System::Windows::Forms::Panel ^  panAfterInfoView;


  private: System::Windows::Forms::Label ^  labPreCendDesc;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;
    System::Void butCancel_Click(System::Object ^  sender, System::EventArgs ^  e);
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      this->progressBar = (gcnew System::Windows::Forms::ProgressBar());
      this->butCancel = (gcnew System::Windows::Forms::Button());
      this->labSource = (gcnew System::Windows::Forms::Label());
      this->panSourceView = (gcnew System::Windows::Forms::Panel());
      this->labPreCendDesc = (gcnew System::Windows::Forms::Label());
      this->labPerCentView = (gcnew System::Windows::Forms::Label());
      this->panCancelView = (gcnew System::Windows::Forms::Panel());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->panProgressView = (gcnew System::Windows::Forms::Panel());
      this->panAfterInfoView = (gcnew System::Windows::Forms::Panel());
      this->panSourceView->SuspendLayout();
      this->panCancelView->SuspendLayout();
      this->panProgressView->SuspendLayout();
      this->SuspendLayout();
      // 
      // progressBar
      // 
      this->progressBar->AccessibleRole = System::Windows::Forms::AccessibleRole::Animation;
      this->progressBar->Location = System::Drawing::Point(8, 64);
      this->progressBar->Name = L"progressBar";
      this->progressBar->Size = System::Drawing::Size(360, 16);
      this->progressBar->Step = 1;
      this->progressBar->TabIndex = 0;
      // 
      // butCancel
      // 
      this->butCancel->Location = System::Drawing::Point(136, 24);
      this->butCancel->Name = L"butCancel";
      this->butCancel->Size = System::Drawing::Size(96, 24);
      this->butCancel->TabIndex = 1;
      this->butCancel->Text = L"Cancel";
      this->butCancel->Visible = false;
      this->butCancel->Click += gcnew System::EventHandler(this, &CProgressBarViewForm::butCancel_Click);
      // 
      // labSource
      // 
      this->labSource->Dock = System::Windows::Forms::DockStyle::Top;
      this->labSource->Location = System::Drawing::Point(0, 0);
      this->labSource->Name = L"labSource";
      this->labSource->Size = System::Drawing::Size(374, 24);
      this->labSource->TabIndex = 2;
      // 
      // panSourceView
      // 
      this->panSourceView->Controls->Add(this->labPreCendDesc);
      this->panSourceView->Controls->Add(this->labSource);
      this->panSourceView->Controls->Add(this->labPerCentView);
      this->panSourceView->Dock = System::Windows::Forms::DockStyle::Top;
      this->panSourceView->Location = System::Drawing::Point(0, 0);
      this->panSourceView->Name = L"panSourceView";
      this->panSourceView->Size = System::Drawing::Size(374, 56);
      this->panSourceView->TabIndex = 3;
      // 
      // labPreCendDesc
      // 
      this->labPreCendDesc->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->labPreCendDesc->Location = System::Drawing::Point(192, 32);
      this->labPreCendDesc->Name = L"labPreCendDesc";
      this->labPreCendDesc->Size = System::Drawing::Size(32, 16);
      this->labPreCendDesc->TabIndex = 4;
      this->labPreCendDesc->Text = L"%";
      this->labPreCendDesc->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
      // 
      // labPerCentView
      // 
      this->labPerCentView->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->labPerCentView->Location = System::Drawing::Point(160, 32);
      this->labPerCentView->Name = L"labPerCentView";
      this->labPerCentView->Size = System::Drawing::Size(24, 16);
      this->labPerCentView->TabIndex = 3;
      // 
      // panCancelView
      // 
      this->panCancelView->Controls->Add(this->label1);
      this->panCancelView->Controls->Add(this->butCancel);
      this->panCancelView->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->panCancelView->Location = System::Drawing::Point(0, 86);
      this->panCancelView->Name = L"panCancelView";
      this->panCancelView->Size = System::Drawing::Size(374, 56);
      this->panCancelView->TabIndex = 5;
      // 
      // label1
      // 
      this->label1->ForeColor = System::Drawing::Color::Red;
      this->label1->Location = System::Drawing::Point(8, 8);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(360, 16);
      this->label1->TabIndex = 2;
      this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
      this->label1->Visible = false;
      // 
      // panProgressView
      // 
      this->panProgressView->Controls->Add(this->progressBar);
      this->panProgressView->Controls->Add(this->panCancelView);
      this->panProgressView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panProgressView->Location = System::Drawing::Point(0, 0);
      this->panProgressView->Name = L"panProgressView";
      this->panProgressView->Size = System::Drawing::Size(374, 142);
      this->panProgressView->TabIndex = 6;
      // 
      // panAfterInfoView
      // 
      this->panAfterInfoView->Location = System::Drawing::Point(48, 256);
      this->panAfterInfoView->Name = L"panAfterInfoView";
      this->panAfterInfoView->Size = System::Drawing::Size(296, 64);
      this->panAfterInfoView->TabIndex = 1;
      this->panAfterInfoView->Visible = false;
      // 
      // CProgressBarViewForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(374, 142);
      this->ControlBox = false;
      this->Controls->Add(this->panSourceView);
      this->Controls->Add(this->panProgressView);
      this->Controls->Add(this->panAfterInfoView);
      this->DoubleBuffered = true;
      this->ForeColor = System::Drawing::SystemColors::ControlText;
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
      this->Name = L"CProgressBarViewForm";
      this->ShowInTaskbar = false;
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
      this->TopMost = true;
      this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &CProgressBarViewForm::CProgressBarViewForm_FormClosed);
      this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &CProgressBarViewForm::CProgressBarViewForm_FormClosing);
      this->panSourceView->ResumeLayout(false);
      this->panCancelView->ResumeLayout(false);
      this->panProgressView->ResumeLayout(false);
      this->ResumeLayout(false);

    }		
   /* void initViewComponent();	*/
    double restDif;
    int totalStep;
    long minimum;
    __int64 maximum;
    
    bool formClosed;
    BarViewAbortDelTyp^ BarViewAbortEvent;

private: System::Void CProgressBarViewForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
           formClosed = true;
         }
private: System::Void CProgressBarViewForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
           formClosed = true;
         }

//public : void CloseForm()
//         {
//          formClosed = true;
//          this->Close();
//         }
};
}