#pragma once

//----------------------------------------------------
//#include "CTlgBaseWrapper.h"
#include "CItemWrapper.h"
#include "CTlgWrapper.h"
#include "CTlgViewForm.h"
//#include "CBaseTlgFactoryWrapper.h"
//----------------------------------------------------

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace simulator
{
	/// <summary> 
	/// Zusammenfassung für CTlgPrototypTreeViewForm
	///
	/// Achtung: Wenn Sie den Namen dieser Klasse ändern, müssen Sie die Eigenschaft
	///          'Ressourcendateiname' für das Compilertool für verwaltete Ressourcen ändern, 
	///          das allen .resx-Dateien zugewiesen ist, von denen diese Klasse abhängt. 
	///          Anderenfalls können die Designer nicht korrekt mit den lokalisierten Ressourcen
	///          arbeiten, die diesem Formular zugewiesen sind.
	/// </summary>
	public ref class CTlgPrototypTreeViewForm : public System::Windows::Forms::Form
	{
	public: 
		CTlgPrototypTreeViewForm(void)
		{
			InitializeComponent();
      this->TopLevel = false;
      this->Dock = DockStyle::Fill;
      this->FormBorderStyle = ::FormBorderStyle::None;
      this->label1->Visible = false;
      UpdateModus = true;
		}
		CTlgPrototypTreeViewForm(Panel^ parent);
		void setTlgViewForm(CTlgViewForm^ tlgView);
		void showTlgPrototyp();
//    int showTlgPrototyp(CBaseTlgFactoryWrapper^ TlgFactory);
	protected: 
		//void Dispose(Boolean disposing)
		//{
		//	if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}
	private: System::Windows::Forms::Label ^  label1;
	private: System::Windows::Forms::TreeView ^  treeViewTlgPrototyp;
	private: System::Windows::Forms::Panel ^  panTlgView;


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
            this->label1 = gcnew System::Windows::Forms::Label();
            this->panTlgView = gcnew System::Windows::Forms::Panel();
            this->treeViewTlgPrototyp = gcnew System::Windows::Forms::TreeView();
            this->panTlgView->SuspendLayout();
            this->SuspendLayout();
            // 
            // label1
            // 
            this->label1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->label1->Dock = System::Windows::Forms::DockStyle::Top;
            this->label1->Location = System::Drawing::Point(0, 0);
            this->label1->Name = "label1";
            this->label1->Size = System::Drawing::Size(296, 23);
            this->label1->TabIndex = 0;
            this->label1->Text = "Available Telegram";
            this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            // 
            // panTlgView
            // 
            this->panTlgView->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
            this->panTlgView->Controls->Add(this->treeViewTlgPrototyp);
            this->panTlgView->Dock = System::Windows::Forms::DockStyle::Fill;
            this->panTlgView->Location = System::Drawing::Point(0, 23);
            this->panTlgView->Name = "panTlgView";
            this->panTlgView->Size = System::Drawing::Size(296, 250);
            this->panTlgView->TabIndex = 1;
            // 
            // treeViewTlgPrototyp
            // 
            this->treeViewTlgPrototyp->BorderStyle = System::Windows::Forms::BorderStyle::None;
            this->treeViewTlgPrototyp->Dock = System::Windows::Forms::DockStyle::Fill;
            this->treeViewTlgPrototyp->ImageIndex = -1;
            this->treeViewTlgPrototyp->Location = System::Drawing::Point(0, 0);
            this->treeViewTlgPrototyp->Name = "treeViewTlgPrototyp";
            this->treeViewTlgPrototyp->SelectedImageIndex = -1;
            this->treeViewTlgPrototyp->Size = System::Drawing::Size(292, 246);
            this->treeViewTlgPrototyp->TabIndex = 0;
						this->treeViewTlgPrototyp->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &CTlgPrototypTreeViewForm::OnAfterSelectTreeView);
            // 
            // CTlgPrototypTreeViewForm
            // 
            this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
            this->ClientSize = System::Drawing::Size(296, 273);
            this->Controls->Add(this->panTlgView);
            this->Controls->Add(this->label1);
            this->Name = "CTlgPrototypTreeViewForm";
            this->Text = "CTlgPrototypTreeViewForm";
            this->panTlgView->ResumeLayout(false);
            this->ResumeLayout(false);

        }		

		System::Void OnAfterSelectTreeView(System::Object ^  sender, System::Windows::Forms::TreeViewEventArgs ^  e);

//    CBaseTlgFactoryWrapper^ TlgFactoryWrapper;
		CTlgViewForm^ TlgViewForm;

    bool UpdateModus;
	};
}
