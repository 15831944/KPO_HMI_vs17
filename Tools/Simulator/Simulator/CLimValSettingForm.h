#pragma once

//-----------------------------------------------------------------
#include "CTlgInterfaceWrapper.h"
#include "CAppSetting.h"
#include "CXmlInterConfigWriter.h"
#include "CXmlInterConfigReader.h"
//-----------------------------------------------------------------

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace simulator
{
	/// <summary> 
	/// Zusammenfassung für CLimValSettingForm
	///
	/// Achtung: Wenn Sie den Namen dieser Klasse ändern, müssen Sie die Eigenschaft
	///          'Ressourcendateiname' für das Compilertool für verwaltete Ressourcen ändern, 
	///          das allen .resx-Dateien zugewiesen ist, von denen diese Klasse abhängt. 
	///          Anderenfalls können die Designer nicht korrekt mit den lokalisierten Ressourcen
	///          arbeiten, die diesem Formular zugewiesen sind.
	/// </summary>
	public ref class CLimValSettingForm : public System::Windows::Forms::Form
	{
	public: 
		CLimValSettingForm(void)
		{
			InitializeComponent();
			Interface = nullptr;
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
	private: System::Windows::Forms::GroupBox ^  groupBox1;
	private: System::Windows::Forms::RadioButton ^  radButNotTreat;
	private: System::Windows::Forms::RadioButton ^  radButError;
	private: System::Windows::Forms::RadioButton ^  radButAsWarning;
	private: System::Windows::Forms::RadioButton ^  radButMinMax;
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
			this->groupBox1 = gcnew System::Windows::Forms::GroupBox();
			this->radButMinMax = gcnew System::Windows::Forms::RadioButton();
			this->radButAsWarning = gcnew System::Windows::Forms::RadioButton();
			this->radButError = gcnew System::Windows::Forms::RadioButton();
			this->radButNotTreat = gcnew System::Windows::Forms::RadioButton();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->radButMinMax);
			this->groupBox1->Controls->Add(this->radButAsWarning);
			this->groupBox1->Controls->Add(this->radButError);
			this->groupBox1->Controls->Add(this->radButNotTreat);
			this->groupBox1->Location = System::Drawing::Point(16, 16);
			this->groupBox1->Name = "groupBox1";
			this->groupBox1->Size = System::Drawing::Size(360, 152);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = "Limit of Value";
			// 
			// radButMinMax
			// 
			this->radButMinMax->Location = System::Drawing::Point(24, 120);
			this->radButMinMax->Name = "radButMinMax";
			this->radButMinMax->TabIndex = 3;
			this->radButMinMax->Text = "Set to Min(Max)";
			// 
			// radButAsWarning
			// 
			this->radButAsWarning->Location = System::Drawing::Point(24, 88);
			this->radButAsWarning->Name = "radButAsWarning";
			this->radButAsWarning->TabIndex = 2;
			this->radButAsWarning->Text = "As Warning";
			// 
			// radButError
			// 
			this->radButError->Checked = true;
			this->radButError->Location = System::Drawing::Point(24, 56);
			this->radButError->Name = "radButError";
			this->radButError->TabIndex = 1;
			this->radButError->TabStop = true;
			this->radButError->Text = "As Error";
			// 
			// radButNotTreat
			// 
			this->radButNotTreat->Location = System::Drawing::Point(24, 24);
			this->radButNotTreat->Name = "radButNotTreat";
			this->radButNotTreat->TabIndex = 0;
			this->radButNotTreat->Text = "Accept";
			// 
			// CLimValSettingForm
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(416, 273);
			this->Controls->Add(this->groupBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = "CLimValSettingForm";
			this->Text = "CLimValSettingForm";
			this->groupBox1->ResumeLayout(false);
			this->ResumeLayout(false);

		}		
		CTlgInterfaceWrapper^ Interface;
		void updateViewFromConfFile();
	};
}
