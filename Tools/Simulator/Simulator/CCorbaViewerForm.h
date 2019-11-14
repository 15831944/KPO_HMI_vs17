#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#include "CCorbaIdlWrapper.h"
#include "CLogWriterWrapper.h"

namespace simulator {

	/// <summary>
	/// Summary for CCorbaViewerForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CCorbaViewerForm : public System::Windows::Forms::Form
	{
	public:
		CCorbaViewerForm(void)
		{
			InitializeComponent();
      init();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CCorbaViewerForm()
		{
			if (components)
			{
				delete components;
			}
		}
  private: System::Windows::Forms::Panel^  panTopView;
  private: System::Windows::Forms::Splitter^  splitter1;
  private: System::Windows::Forms::Panel^  panLeftLeftView;
  private: System::Windows::Forms::Splitter^  splitter2;
  private: System::Windows::Forms::Panel^  panLeftView;
  private: System::Windows::Forms::Splitter^  splitter3;
  private: System::Windows::Forms::Panel^  panBottomButtonsView;
  private: System::Windows::Forms::Splitter^  splitter4;
  private: System::Windows::Forms::TreeView^  trKeysView;
  private: System::Windows::Forms::TreeView^  trNamesView;
  private: System::Windows::Forms::Button^  butClose;


  private: System::Windows::Forms::Panel^  panMiddleView;
  protected: 

  private: System::Void Buttons_Click(System::Object^  sender, System::EventArgs^  e);
  private: System::Void butClose_Click(System::Object^  sender, System::EventArgs^  e);
  private: System::Void trKeysView_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e);
  private: System::Void trNamesView_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e);
  private: void AddInterfaceButtons (array<String^>^ names);

  private: Windows::Forms::Button^ LastGreenTopButton;
           CCorbaIdlWrapper^ CorbaIdl;
           String^ SelectedInterfaceName;
           SimGuiDialogs::CCorbaTypeOfNameView^ DetailView;
           CLogWriterWrapper^ LogWriter;
  private: System::ComponentModel::IContainer^  components;

  private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      this->panTopView = (gcnew System::Windows::Forms::Panel());
      this->splitter1 = (gcnew System::Windows::Forms::Splitter());
      this->panLeftLeftView = (gcnew System::Windows::Forms::Panel());
      this->trKeysView = (gcnew System::Windows::Forms::TreeView());
      this->splitter2 = (gcnew System::Windows::Forms::Splitter());
      this->panLeftView = (gcnew System::Windows::Forms::Panel());
      this->trNamesView = (gcnew System::Windows::Forms::TreeView());
      this->splitter3 = (gcnew System::Windows::Forms::Splitter());
      this->panBottomButtonsView = (gcnew System::Windows::Forms::Panel());
      this->butClose = (gcnew System::Windows::Forms::Button());
      this->splitter4 = (gcnew System::Windows::Forms::Splitter());
      this->panMiddleView = (gcnew System::Windows::Forms::Panel());
      this->panLeftLeftView->SuspendLayout();
      this->panLeftView->SuspendLayout();
      this->panBottomButtonsView->SuspendLayout();
      this->SuspendLayout();
      // 
      // panTopView
      // 
      this->panTopView->AutoScroll = true;
      this->panTopView->Dock = System::Windows::Forms::DockStyle::Top;
      this->panTopView->Location = System::Drawing::Point(0, 0);
      this->panTopView->Name = L"panTopView";
      this->panTopView->Size = System::Drawing::Size(812, 45);
      this->panTopView->TabIndex = 0;
      // 
      // splitter1
      // 
      this->splitter1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->splitter1->Dock = System::Windows::Forms::DockStyle::Top;
      this->splitter1->Location = System::Drawing::Point(0, 45);
      this->splitter1->Name = L"splitter1";
      this->splitter1->Size = System::Drawing::Size(812, 3);
      this->splitter1->TabIndex = 1;
      this->splitter1->TabStop = false;
      // 
      // panLeftLeftView
      // 
      this->panLeftLeftView->Controls->Add(this->trKeysView);
      this->panLeftLeftView->Dock = System::Windows::Forms::DockStyle::Left;
      this->panLeftLeftView->Location = System::Drawing::Point(0, 48);
      this->panLeftLeftView->Name = L"panLeftLeftView";
      this->panLeftLeftView->Size = System::Drawing::Size(137, 457);
      this->panLeftLeftView->TabIndex = 2;
      // 
      // trKeysView
      // 
      this->trKeysView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->trKeysView->FullRowSelect = true;
      this->trKeysView->HideSelection = false;
      this->trKeysView->HotTracking = true;
      this->trKeysView->Location = System::Drawing::Point(0, 0);
      this->trKeysView->Name = L"trKeysView";
      this->trKeysView->ShowLines = false;
      this->trKeysView->ShowPlusMinus = false;
      this->trKeysView->ShowRootLines = false;
      this->trKeysView->Size = System::Drawing::Size(137, 457);
      this->trKeysView->TabIndex = 0;
      this->trKeysView->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &CCorbaViewerForm::trKeysView_AfterSelect);
      // 
      // splitter2
      // 
      this->splitter2->Location = System::Drawing::Point(137, 48);
      this->splitter2->Name = L"splitter2";
      this->splitter2->Size = System::Drawing::Size(3, 457);
      this->splitter2->TabIndex = 3;
      this->splitter2->TabStop = false;
      // 
      // panLeftView
      // 
      this->panLeftView->Controls->Add(this->trNamesView);
      this->panLeftView->Dock = System::Windows::Forms::DockStyle::Left;
      this->panLeftView->Location = System::Drawing::Point(140, 48);
      this->panLeftView->Name = L"panLeftView";
      this->panLeftView->Size = System::Drawing::Size(132, 457);
      this->panLeftView->TabIndex = 4;
      // 
      // trNamesView
      // 
      this->trNamesView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->trNamesView->FullRowSelect = true;
      this->trNamesView->HideSelection = false;
      this->trNamesView->HotTracking = true;
      this->trNamesView->Location = System::Drawing::Point(0, 0);
      this->trNamesView->Name = L"trNamesView";
      this->trNamesView->ShowLines = false;
      this->trNamesView->ShowPlusMinus = false;
      this->trNamesView->ShowRootLines = false;
      this->trNamesView->Size = System::Drawing::Size(132, 457);
      this->trNamesView->TabIndex = 0;
      this->trNamesView->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &CCorbaViewerForm::trNamesView_AfterSelect);
      // 
      // splitter3
      // 
      this->splitter3->Location = System::Drawing::Point(272, 48);
      this->splitter3->Name = L"splitter3";
      this->splitter3->Size = System::Drawing::Size(3, 457);
      this->splitter3->TabIndex = 5;
      this->splitter3->TabStop = false;
      // 
      // panBottomButtonsView
      // 
      this->panBottomButtonsView->Controls->Add(this->butClose);
      this->panBottomButtonsView->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->panBottomButtonsView->Location = System::Drawing::Point(275, 477);
      this->panBottomButtonsView->Name = L"panBottomButtonsView";
      this->panBottomButtonsView->Size = System::Drawing::Size(537, 28);
      this->panBottomButtonsView->TabIndex = 6;
      // 
      // butClose
      // 
      this->butClose->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->butClose->Location = System::Drawing::Point(473, 1);
      this->butClose->Name = L"butClose";
      this->butClose->Size = System::Drawing::Size(61, 24);
      this->butClose->TabIndex = 0;
      this->butClose->Text = L"Close";
      this->butClose->UseVisualStyleBackColor = true;
      this->butClose->Click += gcnew System::EventHandler(this, &CCorbaViewerForm::butClose_Click);
      // 
      // splitter4
      // 
      this->splitter4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->splitter4->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->splitter4->Location = System::Drawing::Point(275, 474);
      this->splitter4->Name = L"splitter4";
      this->splitter4->Size = System::Drawing::Size(537, 3);
      this->splitter4->TabIndex = 7;
      this->splitter4->TabStop = false;
      // 
      // panMiddleView
      // 
      this->panMiddleView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panMiddleView->Location = System::Drawing::Point(275, 48);
      this->panMiddleView->Name = L"panMiddleView";
      this->panMiddleView->Size = System::Drawing::Size(537, 426);
      this->panMiddleView->TabIndex = 8;
      // 
      // CCorbaViewerForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(812, 505);
      this->Controls->Add(this->panMiddleView);
      this->Controls->Add(this->splitter4);
      this->Controls->Add(this->panBottomButtonsView);
      this->Controls->Add(this->splitter3);
      this->Controls->Add(this->panLeftView);
      this->Controls->Add(this->splitter2);
      this->Controls->Add(this->panLeftLeftView);
      this->Controls->Add(this->splitter1);
      this->Controls->Add(this->panTopView);
      this->Name = L"CCorbaViewerForm";
      this->Text = L"Corba Viewer";
      this->panLeftLeftView->ResumeLayout(false);
      this->panLeftView->ResumeLayout(false);
      this->panBottomButtonsView->ResumeLayout(false);
      this->ResumeLayout(false);

    }
#pragma endregion


  private: void init();
           void addKeys(String^ InterfaceName);
           void addNames(String^ InterfaceName,String^ key);
           void setDetailView();
};


}
