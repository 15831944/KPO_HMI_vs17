#pragma once
#include "CMessageForm.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace simulator
{
	/// <summary> 
	/// Zusammenfassung für CAnalyzeDiagramForm
	///
	/// Achtung: Wenn Sie den Namen dieser Klasse ändern, müssen Sie die Eigenschaft
	///          'Ressourcendateiname' für das Compilertool für verwaltete Ressourcen ändern, 
	///          das allen .resx-Dateien zugewiesen ist, von denen diese Klasse abhängt. 
	///          Anderenfalls können die Designer nicht korrekt mit den lokalisierten Ressourcen
	///          arbeiten, die diesem Formular zugewiesen sind.
	/// </summary>
	public __gc class CAnalyzeDiagramForm : public System::Windows::Forms::Form
	{
	public: 
		CAnalyzeDiagramForm(Panel* parent,double TlgNullTime,double maxTime)
		{
			InitializeComponent();
			initViewComponent(parent,TlgNullTime,maxTime);

		}
  public: void addToSeries(String* TlgName,double TlgTime,bool newTlg);
	public: void addToSeries(String* tlgName,String* elemName,String* subElemName,double tlgTime,double elemValue);
  public: ArrayList* removeFromSeries(String* TlgName);
	public:	void removeFromSeries(String* TlgName,String* elemName,String* subElemName);
  public: void setStartTime(double TlgTime);
  public: String* getSeriesTlgNames(int index);
  public: String* getSeriesValueNames(int index);
  public: void setPointerOfMessage(CMessageForm* MessageForm);
        
	protected: 
		void Dispose(Boolean disposing)
		{
			if (disposing && components)
			{
				components->Dispose();
			}
			__super::Dispose(disposing);
		}

  private: double minTime;
           double maxTime;
					 int tlgCount;
					 double leftAxisMax;
           /*int countAllSeries;*/
           Hashtable __gc* numOfSeries;
  private: System::Windows::Forms::Panel *  panViewOptions;

  private: System::Windows::Forms::CheckBox *  checkBox3D;
  private: System::Windows::Forms::TabControl *  tabDiagramControl;

  private: AxInterop::TeeChart::AxTChart *  axTChartDiagram;

  private: System::Windows::Forms::Panel *  panViewTeeChartDiagram;
  private: System::Windows::Forms::TabPage *  tabTlgDiagram;
  private: System::Windows::Forms::TabPage *  tabValueDiagram;
  private: AxInterop::TeeChart::AxTChart *  axTChartValueDiagram;
  private: System::Windows::Forms::Button *  butRemoveAll;




           //Hashtable  __gc*  mySeries;
           CMessageForm* MessageForm;
  private: void createNewSeries(String* TlgName);
	private: void createNewSeries(String* tlgName,String* elemName,String* subElemName);
           

  //         private System:: allSeries 
  //{
  //  public static int id=0;
  //  public Interop::TeeChart::ISeries * ser;

  //  public allSeries() 
  //  {
  //    //this->id++;
  //    this->ser=axTChartDiagram->Series(id++); 
  //  }
  //}



	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container* components;

		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung. 
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
      System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(simulator::CAnalyzeDiagramForm));
      this->panViewOptions = new System::Windows::Forms::Panel();
      this->butRemoveAll = new System::Windows::Forms::Button();
      this->checkBox3D = new System::Windows::Forms::CheckBox();
      this->tabDiagramControl = new System::Windows::Forms::TabControl();
      this->tabTlgDiagram = new System::Windows::Forms::TabPage();
      this->axTChartDiagram = new AxInterop::TeeChart::AxTChart();
      this->tabValueDiagram = new System::Windows::Forms::TabPage();
      this->axTChartValueDiagram = new AxInterop::TeeChart::AxTChart();
      this->panViewTeeChartDiagram = new System::Windows::Forms::Panel();
      this->panViewOptions->SuspendLayout();
      this->tabDiagramControl->SuspendLayout();
      this->tabTlgDiagram->SuspendLayout();
      (__try_cast<System::ComponentModel::ISupportInitialize *  >(this->axTChartDiagram))->BeginInit();
      this->tabValueDiagram->SuspendLayout();
      (__try_cast<System::ComponentModel::ISupportInitialize *  >(this->axTChartValueDiagram))->BeginInit();
      this->panViewTeeChartDiagram->SuspendLayout();
      this->SuspendLayout();
      // 
      // panViewOptions
      // 
      this->panViewOptions->Controls->Add(this->butRemoveAll);
      this->panViewOptions->Controls->Add(this->checkBox3D);
      this->panViewOptions->Dock = System::Windows::Forms::DockStyle::Top;
      this->panViewOptions->Location = System::Drawing::Point(0, 0);
      this->panViewOptions->Name = S"panViewOptions";
      this->panViewOptions->Size = System::Drawing::Size(416, 24);
      this->panViewOptions->TabIndex = 1;
      this->panViewOptions->Click += new System::EventHandler(this, OnClickCheckBox3D);
      // 
      // butRemoveAll
      // 
      this->butRemoveAll->Dock = System::Windows::Forms::DockStyle::Right;
      this->butRemoveAll->Location = System::Drawing::Point(301, 0);
      this->butRemoveAll->Name = S"butRemoveAll";
      this->butRemoveAll->Size = System::Drawing::Size(75, 24);
      this->butRemoveAll->TabIndex = 1;
      this->butRemoveAll->Text = S"Remove All";
      this->butRemoveAll->Visible = false;
      this->butRemoveAll->Click += new System::EventHandler(this, OnClickRemoveAll);
      // 
      // checkBox3D
      // 
      this->checkBox3D->Checked = true;
      this->checkBox3D->CheckState = System::Windows::Forms::CheckState::Checked;
      this->checkBox3D->Dock = System::Windows::Forms::DockStyle::Right;
      this->checkBox3D->Location = System::Drawing::Point(376, 0);
      this->checkBox3D->Name = S"checkBox3D";
      this->checkBox3D->Size = System::Drawing::Size(40, 24);
      this->checkBox3D->TabIndex = 0;
      this->checkBox3D->Text = S"3D";
      this->checkBox3D->CheckedChanged += new System::EventHandler(this, OnClickCheckBox3D);
      // 
      // tabDiagramControl
      // 
      this->tabDiagramControl->Controls->Add(this->tabTlgDiagram);
      this->tabDiagramControl->Controls->Add(this->tabValueDiagram);
      this->tabDiagramControl->Dock = System::Windows::Forms::DockStyle::Fill;
      this->tabDiagramControl->ItemSize = System::Drawing::Size(42, 18);
      this->tabDiagramControl->Location = System::Drawing::Point(0, 0);
      this->tabDiagramControl->Name = S"tabDiagramControl";
      this->tabDiagramControl->SelectedIndex = 0;
      this->tabDiagramControl->Size = System::Drawing::Size(416, 272);
      this->tabDiagramControl->TabIndex = 1;
      this->tabDiagramControl->SelectedIndexChanged += new System::EventHandler(this, OnClickTabControlChanged);
      // 
      // tabTlgDiagram
      // 
      this->tabTlgDiagram->Controls->Add(this->axTChartDiagram);
      this->tabTlgDiagram->Location = System::Drawing::Point(4, 22);
      this->tabTlgDiagram->Name = S"tabTlgDiagram";
      this->tabTlgDiagram->Size = System::Drawing::Size(408, 246);
      this->tabTlgDiagram->TabIndex = 0;
      this->tabTlgDiagram->Tag = S"axTChartDiagram";
      this->tabTlgDiagram->Text = S"Telegrams";
      // 
      // axTChartDiagram
      // 
      this->axTChartDiagram->ContainingControl = this;
      this->axTChartDiagram->Enabled = true;
      this->axTChartDiagram->Location = System::Drawing::Point(16, 0);
      this->axTChartDiagram->Name = S"axTChartDiagram";
      this->axTChartDiagram->OcxState = (__try_cast<System::Windows::Forms::AxHost::State *  >(resources->GetObject(S"axTChartDiagram.OcxState")));
      this->axTChartDiagram->Size = System::Drawing::Size(288, 208);
      this->axTChartDiagram->TabIndex = 0;
      this->axTChartDiagram->Tag = S"axTChartDiagram";
      this->axTChartDiagram->OnSeriesAfterDrawValues += new AxInterop::TeeChart::ITChartEvents_OnSeriesAfterDrawValuesEventHandler(this, axTChartDiagram_OnSeriesAfterDrawValues);
      // 
      // tabValueDiagram
      // 
      this->tabValueDiagram->Controls->Add(this->axTChartValueDiagram);
      this->tabValueDiagram->Location = System::Drawing::Point(4, 22);
      this->tabValueDiagram->Name = S"tabValueDiagram";
      this->tabValueDiagram->Size = System::Drawing::Size(408, 246);
      this->tabValueDiagram->TabIndex = 1;
      this->tabValueDiagram->Text = S"Values";
      // 
      // axTChartValueDiagram
      // 
      this->axTChartValueDiagram->ContainingControl = this;
      this->axTChartValueDiagram->Enabled = true;
      this->axTChartValueDiagram->Location = System::Drawing::Point(24, 8);
      this->axTChartValueDiagram->Name = S"axTChartValueDiagram";
      this->axTChartValueDiagram->OcxState = (__try_cast<System::Windows::Forms::AxHost::State *  >(resources->GetObject(S"axTChartValueDiagram.OcxState")));
      this->axTChartValueDiagram->Size = System::Drawing::Size(352, 208);
      this->axTChartValueDiagram->TabIndex = 0;
      // 
      // panViewTeeChartDiagram
      // 
      this->panViewTeeChartDiagram->Controls->Add(this->tabDiagramControl);
      this->panViewTeeChartDiagram->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panViewTeeChartDiagram->Location = System::Drawing::Point(0, 24);
      this->panViewTeeChartDiagram->Name = S"panViewTeeChartDiagram";
      this->panViewTeeChartDiagram->Size = System::Drawing::Size(416, 272);
      this->panViewTeeChartDiagram->TabIndex = 2;
      this->panViewTeeChartDiagram->Click += new System::EventHandler(this, OnClickCheckBox3D);
      this->panViewTeeChartDiagram->Paint += new System::Windows::Forms::PaintEventHandler(this, panViewTeeChartDiagram_Paint);
      // 
      // CAnalyzeDiagramForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(416, 296);
      this->Controls->Add(this->panViewTeeChartDiagram);
      this->Controls->Add(this->panViewOptions);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
      this->Name = S"CAnalyzeDiagramForm";
      this->Text = S"CAnalyzeDiagramForm";
      this->panViewOptions->ResumeLayout(false);
      this->tabDiagramControl->ResumeLayout(false);
      this->tabTlgDiagram->ResumeLayout(false);
      (__try_cast<System::ComponentModel::ISupportInitialize *  >(this->axTChartDiagram))->EndInit();
      this->tabValueDiagram->ResumeLayout(false);
      (__try_cast<System::ComponentModel::ISupportInitialize *  >(this->axTChartValueDiagram))->EndInit();
      this->panViewTeeChartDiagram->ResumeLayout(false);
      this->ResumeLayout(false);

    }		
	
		void initViewComponent(Panel* parent,double TlgNullTime,double maxTime);
	private: System::Void axTChartDiagram_OnSeriesAfterDrawValues(System::Object *  sender, AxInterop::TeeChart::ITChartEvents_OnSeriesAfterDrawValuesEvent *  e);
					 
					

  private: System::Void OnClickCheckBox3D(System::Object *  sender, System::EventArgs *  e);
           

private: System::Void panViewTeeChartDiagram_Paint(System::Object *  sender, System::Windows::Forms::PaintEventArgs *  e)
         {
         }

private: System::Void OnClickTabControlChanged(System::Object *  sender, System::EventArgs *  e);
         
         

private: System::Void OnClickRemoveAll(System::Object *  sender, System::EventArgs *  e);
         
         

};
}
