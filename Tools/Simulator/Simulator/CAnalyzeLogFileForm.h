#pragma once

#include "CTlgContainerTreeViewForm.h"
#include "CTlgInterfaceWrapper.h"
#include "CTlgLogFileReaderWrapper.h"
#include "CMessageForm.h"
#include "CProgressBarViewForm.h"
#include "CItemPrototypContainerForm.h"
//#include "CAnalyzeDiagramForm.h"
#include "CAnalyzeTlgForm.h"
#include "CAnalyzeSubElemForm.h"
#include "CTlgDataGridViewForm.h"
#include "CDataGridContainerForm.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace simulator
{
	/// <summary> 
	/// Summary for CAnalyzeLogFileForm
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CAnalyzeLogFileForm : public System::Windows::Forms::Form
	{
	public: 
		CAnalyzeLogFileForm(ArrayList^ InterfaceListe,int index,String^ path)
		{
			InitializeComponent();
      initViewComponent(InterfaceListe,index,path);
		}

  public: 
    void addTlgToDiagram (String^ name);
    void addTlgElemToDiagram (String^ tlgName,String^ tlgElem, String^ tlgSubElem);
    void addTlgElemToDiagram (ArrayList^ ElemOrderList);
    void readLogFileWithTimer(); 
    void updateTlgOfDiagram(String^ name,int pos);
    void updateValueOfDiagram(String^ name,int pos);
    void nodePathToTreeStrings(String^ tlgName,String^ elemName,String^ subElemName);
    void addItemToTable();
    void addITemToDiagram(void);
    void addItemValuesToTable (String^ name);
    void removeItemFromDiagram();
    void removeItemFromDataTable();
  protected: 
		//void Dispose(Boolean disposing)
		//{
		//	if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}

	private: System::Windows::Forms::Splitter ^  splitter1;
  private: System::Windows::Forms::Splitter ^  splitter3;
  private: System::Windows::Forms::Splitter ^  splitter6;
	private: System::Windows::Forms::Panel ^  panView1;
  private: System::Windows::Forms::Panel ^  panView2;
	private: System::Windows::Forms::Panel ^  panViewMessageBox;
	private: System::Windows::Forms::Panel ^  panViewTeeChart;
  private: System::Windows::Forms::Panel ^  panViewLeft;
  private: System::Windows::Forms::Panel ^  panViewButAddToAnalyze;
  private: System::Windows::Forms::Button ^  butAddToAnalyze;
  private: System::Windows::Forms::Panel ^  panViewNoButAddToAnalyze;
  private: System::Windows::Forms::Panel ^  panViewOptions;
  private: System::Windows::Forms::TextBox ^  txtBoxTimeUpdate;
  private: System::Windows::Forms::ImageList ^  imgListRedGreen;
  private: System::Windows::Forms::Button ^  butTimeForUpdate;
  private: System::Windows::Forms::Button ^  butRemoveFromAnalyze;
  private: System::Windows::Forms::Panel ^  panViewTeeChartDiagram_;
  private: System::Windows::Forms::TabControl ^  tabDiagramControl;
  private: System::Windows::Forms::TabPage ^  tabTlgDiagram;
  private: System::Windows::Forms::TabPage ^  tabValueDiagram;
  private: System::Windows::Forms::MenuItem ^  menuItem1;
  private: System::Windows::Forms::MenuItem ^  menuItem2;
  private: System::Windows::Forms::Panel ^  panTlgDiagramView;
  private: System::Windows::Forms::Panel ^  panValueDiagramView;
  private: System::Windows::Forms::TabPage ^  tabDataGrid;
  private: System::Windows::Forms::Panel ^  panDataGridView;
  private: System::Windows::Forms::MenuItem ^  menuItem5;
  private: System::Windows::Forms::MainMenu ^  mainMenu;
  private: System::Windows::Forms::MenuItem ^  menuItem3D;
  private: System::Windows::Forms::MenuItem ^  menuItemIndex;
  private: System::Windows::Forms::Splitter ^  splitter2;
  private: System::Windows::Forms::Splitter ^  splitter4;
  private: System::Windows::Forms::Panel ^  panViewInterfaceConTlg;
  private: System::Windows::Forms::Button^  butAddToTable;
  private: System::Windows::Forms::MenuItem^  menuItemFill;
	private: System::Windows::Forms::MenuItem^  menuItemRemoveAll;
  private: System::Windows::Forms::HelpProvider^  helpProvider1;
  private: System::Windows::Forms::MenuItem^  menuItemContents;
  private: System::Windows::Forms::Label^  labMiliSec;
  private: System::Windows::Forms::MenuItem^  menuItemCursorTool;
  private: System::Windows::Forms::MenuItem^  menuItemCustomAxis;
  private: System::ComponentModel::IContainer ^  components;
  private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      this->components = (gcnew System::ComponentModel::Container());
      System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(CAnalyzeLogFileForm::typeid));
      this->panViewLeft = (gcnew System::Windows::Forms::Panel());
      this->panViewNoButAddToAnalyze = (gcnew System::Windows::Forms::Panel());
      this->panViewInterfaceConTlg = (gcnew System::Windows::Forms::Panel());
      this->splitter2 = (gcnew System::Windows::Forms::Splitter());
      this->panViewButAddToAnalyze = (gcnew System::Windows::Forms::Panel());
      this->butAddToTable = (gcnew System::Windows::Forms::Button());
      this->butRemoveFromAnalyze = (gcnew System::Windows::Forms::Button());
      this->butAddToAnalyze = (gcnew System::Windows::Forms::Button());
      this->panViewOptions = (gcnew System::Windows::Forms::Panel());
      this->labMiliSec = (gcnew System::Windows::Forms::Label());
      this->splitter4 = (gcnew System::Windows::Forms::Splitter());
      this->butTimeForUpdate = (gcnew System::Windows::Forms::Button());
      this->imgListRedGreen = (gcnew System::Windows::Forms::ImageList(this->components));
      this->txtBoxTimeUpdate = (gcnew System::Windows::Forms::TextBox());
      this->splitter1 = (gcnew System::Windows::Forms::Splitter());
      this->panView1 = (gcnew System::Windows::Forms::Panel());
      this->panView2 = (gcnew System::Windows::Forms::Panel());
      this->panViewTeeChart = (gcnew System::Windows::Forms::Panel());
      this->panViewTeeChartDiagram_ = (gcnew System::Windows::Forms::Panel());
      this->tabDiagramControl = (gcnew System::Windows::Forms::TabControl());
      this->tabTlgDiagram = (gcnew System::Windows::Forms::TabPage());
      this->panTlgDiagramView = (gcnew System::Windows::Forms::Panel());
      this->tabValueDiagram = (gcnew System::Windows::Forms::TabPage());
      this->panValueDiagramView = (gcnew System::Windows::Forms::Panel());
      this->tabDataGrid = (gcnew System::Windows::Forms::TabPage());
      this->panDataGridView = (gcnew System::Windows::Forms::Panel());
      this->splitter3 = (gcnew System::Windows::Forms::Splitter());
      this->panViewMessageBox = (gcnew System::Windows::Forms::Panel());
      this->splitter6 = (gcnew System::Windows::Forms::Splitter());
      this->mainMenu = (gcnew System::Windows::Forms::MainMenu(this->components));
      this->menuItem1 = (gcnew System::Windows::Forms::MenuItem());
      this->menuItem2 = (gcnew System::Windows::Forms::MenuItem());
      this->menuItem3D = (gcnew System::Windows::Forms::MenuItem());
      this->menuItemFill = (gcnew System::Windows::Forms::MenuItem());
      this->menuItemRemoveAll = (gcnew System::Windows::Forms::MenuItem());
      this->menuItemCursorTool = (gcnew System::Windows::Forms::MenuItem());
      this->menuItemCustomAxis = (gcnew System::Windows::Forms::MenuItem());
      this->menuItem5 = (gcnew System::Windows::Forms::MenuItem());
      this->menuItemContents = (gcnew System::Windows::Forms::MenuItem());
      this->menuItemIndex = (gcnew System::Windows::Forms::MenuItem());
      this->helpProvider1 = (gcnew System::Windows::Forms::HelpProvider());
      this->panViewLeft->SuspendLayout();
      this->panViewNoButAddToAnalyze->SuspendLayout();
      this->panViewButAddToAnalyze->SuspendLayout();
      this->panViewOptions->SuspendLayout();
      this->panView1->SuspendLayout();
      this->panView2->SuspendLayout();
      this->panViewTeeChart->SuspendLayout();
      this->panViewTeeChartDiagram_->SuspendLayout();
      this->tabDiagramControl->SuspendLayout();
      this->tabTlgDiagram->SuspendLayout();
      this->tabValueDiagram->SuspendLayout();
      this->tabDataGrid->SuspendLayout();
      this->panViewMessageBox->SuspendLayout();
      this->SuspendLayout();
      // 
      // panViewLeft
      // 
      this->panViewLeft->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->panViewLeft->Controls->Add(this->panViewNoButAddToAnalyze);
      this->panViewLeft->Dock = System::Windows::Forms::DockStyle::Left;
      this->panViewLeft->Location = System::Drawing::Point(0, 0);
      this->panViewLeft->Name = L"panViewLeft";
      this->panViewLeft->Size = System::Drawing::Size(235, 536);
      this->panViewLeft->TabIndex = 0;
      // 
      // panViewNoButAddToAnalyze
      // 
      this->panViewNoButAddToAnalyze->Controls->Add(this->panViewInterfaceConTlg);
      this->panViewNoButAddToAnalyze->Controls->Add(this->splitter2);
      this->panViewNoButAddToAnalyze->Controls->Add(this->panViewButAddToAnalyze);
      this->panViewNoButAddToAnalyze->Controls->Add(this->panViewOptions);
      this->panViewNoButAddToAnalyze->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panViewNoButAddToAnalyze->Location = System::Drawing::Point(0, 0);
      this->panViewNoButAddToAnalyze->Name = L"panViewNoButAddToAnalyze";
      this->panViewNoButAddToAnalyze->Padding = System::Windows::Forms::Padding(5);
      this->panViewNoButAddToAnalyze->Size = System::Drawing::Size(233, 534);
      this->panViewNoButAddToAnalyze->TabIndex = 0;
      this->panViewNoButAddToAnalyze->Resize += gcnew System::EventHandler(this, &CAnalyzeLogFileForm::OnResizeInterfaceConTlg);
      // 
      // panViewInterfaceConTlg
      // 
      this->panViewInterfaceConTlg->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panViewInterfaceConTlg->Location = System::Drawing::Point(5, 55);
      this->panViewInterfaceConTlg->Name = L"panViewInterfaceConTlg";
      this->panViewInterfaceConTlg->Size = System::Drawing::Size(223, 377);
      this->panViewInterfaceConTlg->TabIndex = 3;
      // 
      // splitter2
      // 
      this->splitter2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->splitter2->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->splitter2->Location = System::Drawing::Point(5, 432);
      this->splitter2->Name = L"splitter2";
      this->splitter2->Size = System::Drawing::Size(223, 7);
      this->splitter2->TabIndex = 2;
      this->splitter2->TabStop = false;
      // 
      // panViewButAddToAnalyze
      // 
      this->panViewButAddToAnalyze->Controls->Add(this->butAddToTable);
      this->panViewButAddToAnalyze->Controls->Add(this->butRemoveFromAnalyze);
      this->panViewButAddToAnalyze->Controls->Add(this->butAddToAnalyze);
      this->panViewButAddToAnalyze->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->panViewButAddToAnalyze->Location = System::Drawing::Point(5, 439);
      this->panViewButAddToAnalyze->Name = L"panViewButAddToAnalyze";
      this->panViewButAddToAnalyze->Padding = System::Windows::Forms::Padding(5);
      this->panViewButAddToAnalyze->Size = System::Drawing::Size(223, 90);
      this->panViewButAddToAnalyze->TabIndex = 1;
      // 
      // butAddToTable
      // 
      this->butAddToTable->Location = System::Drawing::Point(8, 64);
      this->butAddToTable->Name = L"butAddToTable";
      this->butAddToTable->Size = System::Drawing::Size(144, 23);
      this->butAddToTable->TabIndex = 2;
      this->butAddToTable->Text = L"Add to Table";
      this->butAddToTable->UseVisualStyleBackColor = true;
      this->butAddToTable->Click += gcnew System::EventHandler(this, &CAnalyzeLogFileForm::butAddToTable_Click);
      // 
      // butRemoveFromAnalyze
      // 
      this->butRemoveFromAnalyze->Location = System::Drawing::Point(88, 5);
      this->butRemoveFromAnalyze->Name = L"butRemoveFromAnalyze";
      this->butRemoveFromAnalyze->Size = System::Drawing::Size(72, 25);
      this->butRemoveFromAnalyze->TabIndex = 1;
      this->butRemoveFromAnalyze->Text = L"Remove";
      this->butRemoveFromAnalyze->Click += gcnew System::EventHandler(this, &CAnalyzeLogFileForm::OnRemoveFromAnalyzeClick);
      // 
      // butAddToAnalyze
      // 
      this->butAddToAnalyze->Location = System::Drawing::Point(5, 5);
      this->butAddToAnalyze->Name = L"butAddToAnalyze";
      this->butAddToAnalyze->Size = System::Drawing::Size(72, 25);
      this->butAddToAnalyze->TabIndex = 0;
      this->butAddToAnalyze->Text = L"Add";
      this->butAddToAnalyze->Click += gcnew System::EventHandler(this, &CAnalyzeLogFileForm::OnAddToAnalyzeClick);
      // 
      // panViewOptions
      // 
      this->panViewOptions->Controls->Add(this->labMiliSec);
      this->panViewOptions->Controls->Add(this->splitter4);
      this->panViewOptions->Controls->Add(this->butTimeForUpdate);
      this->panViewOptions->Controls->Add(this->txtBoxTimeUpdate);
      this->panViewOptions->Dock = System::Windows::Forms::DockStyle::Top;
      this->panViewOptions->Location = System::Drawing::Point(5, 5);
      this->panViewOptions->Name = L"panViewOptions";
      this->panViewOptions->Size = System::Drawing::Size(223, 50);
      this->panViewOptions->TabIndex = 0;
      // 
      // labMiliSec
      // 
      this->labMiliSec->AutoSize = true;
      this->labMiliSec->Location = System::Drawing::Point(86, 11);
      this->labMiliSec->Name = L"labMiliSec";
      this->labMiliSec->Size = System::Drawing::Size(23, 13);
      this->labMiliSec->TabIndex = 4;
      this->labMiliSec->Text = L"ms.";
      // 
      // splitter4
      // 
      this->splitter4->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->splitter4->Location = System::Drawing::Point(0, 42);
      this->splitter4->Name = L"splitter4";
      this->splitter4->Size = System::Drawing::Size(223, 8);
      this->splitter4->TabIndex = 3;
      this->splitter4->TabStop = false;
      // 
      // butTimeForUpdate
      // 
      this->butTimeForUpdate->BackColor = System::Drawing::Color::Red;
      this->butTimeForUpdate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      this->butTimeForUpdate->ForeColor = System::Drawing::SystemColors::ControlText;
      this->butTimeForUpdate->ImageAlign = System::Drawing::ContentAlignment::BottomLeft;
      this->butTimeForUpdate->ImageList = this->imgListRedGreen;
      this->butTimeForUpdate->Location = System::Drawing::Point(131, 8);
      this->butTimeForUpdate->Name = L"butTimeForUpdate";
      this->butTimeForUpdate->Size = System::Drawing::Size(64, 20);
      this->butTimeForUpdate->TabIndex = 2;
      this->butTimeForUpdate->Text = L"Start";
      this->butTimeForUpdate->UseVisualStyleBackColor = false;
      this->butTimeForUpdate->Click += gcnew System::EventHandler(this, &CAnalyzeLogFileForm::OnTimeForUpdateClick);
      // 
      // imgListRedGreen
      // 
      this->imgListRedGreen->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"imgListRedGreen.ImageStream")));
      this->imgListRedGreen->TransparentColor = System::Drawing::Color::Transparent;
      this->imgListRedGreen->Images->SetKeyName(0, L"");
      this->imgListRedGreen->Images->SetKeyName(1, L"");
      // 
      // txtBoxTimeUpdate
      // 
      this->txtBoxTimeUpdate->Location = System::Drawing::Point(16, 8);
      this->txtBoxTimeUpdate->Name = L"txtBoxTimeUpdate";
      this->txtBoxTimeUpdate->Size = System::Drawing::Size(64, 20);
      this->txtBoxTimeUpdate->TabIndex = 0;
      this->txtBoxTimeUpdate->TextChanged += gcnew System::EventHandler(this, &CAnalyzeLogFileForm::OnTimeForUpdateTxtBox);
      // 
      // splitter1
      // 
      this->splitter1->BackColor = System::Drawing::SystemColors::InactiveBorder;
      this->splitter1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->splitter1->Location = System::Drawing::Point(235, 0);
      this->splitter1->Name = L"splitter1";
      this->splitter1->Size = System::Drawing::Size(7, 536);
      this->splitter1->TabIndex = 1;
      this->splitter1->TabStop = false;
      this->splitter1->DoubleClick += gcnew System::EventHandler(this, &CAnalyzeLogFileForm::OnSplitter1Click);
      // 
      // panView1
      // 
      this->panView1->Controls->Add(this->panView2);
      this->panView1->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panView1->Location = System::Drawing::Point(242, 0);
      this->panView1->Name = L"panView1";
      this->panView1->Size = System::Drawing::Size(506, 536);
      this->panView1->TabIndex = 2;
      // 
      // panView2
      // 
      this->panView2->Controls->Add(this->panViewTeeChart);
      this->panView2->Controls->Add(this->splitter3);
      this->panView2->Controls->Add(this->panViewMessageBox);
      this->panView2->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panView2->Location = System::Drawing::Point(0, 0);
      this->panView2->Name = L"panView2";
      this->panView2->Size = System::Drawing::Size(506, 536);
      this->panView2->TabIndex = 2;
      // 
      // panViewTeeChart
      // 
      this->panViewTeeChart->Controls->Add(this->panViewTeeChartDiagram_);
      this->panViewTeeChart->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panViewTeeChart->Location = System::Drawing::Point(0, 0);
      this->panViewTeeChart->Name = L"panViewTeeChart";
      this->panViewTeeChart->Size = System::Drawing::Size(506, 399);
      this->panViewTeeChart->TabIndex = 5;
      // 
      // panViewTeeChartDiagram_
      // 
      this->panViewTeeChartDiagram_->Controls->Add(this->tabDiagramControl);
      this->panViewTeeChartDiagram_->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panViewTeeChartDiagram_->Location = System::Drawing::Point(0, 0);
      this->panViewTeeChartDiagram_->Name = L"panViewTeeChartDiagram_";
      this->panViewTeeChartDiagram_->Size = System::Drawing::Size(506, 399);
      this->panViewTeeChartDiagram_->TabIndex = 1;
      // 
      // tabDiagramControl
      // 
      this->tabDiagramControl->Controls->Add(this->tabTlgDiagram);
      this->tabDiagramControl->Controls->Add(this->tabValueDiagram);
      this->tabDiagramControl->Controls->Add(this->tabDataGrid);
      this->tabDiagramControl->Dock = System::Windows::Forms::DockStyle::Fill;
      this->tabDiagramControl->Location = System::Drawing::Point(0, 0);
      this->tabDiagramControl->Name = L"tabDiagramControl";
      this->tabDiagramControl->SelectedIndex = 0;
      this->tabDiagramControl->Size = System::Drawing::Size(506, 399);
      this->tabDiagramControl->TabIndex = 0;
      this->tabDiagramControl->SelectedIndexChanged += gcnew System::EventHandler(this, &CAnalyzeLogFileForm::tabDiagramControl_SelectedIndexChanged);
      this->tabDiagramControl->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &CAnalyzeLogFileForm::tabDiagramControl_KeyDown);
      // 
      // tabTlgDiagram
      // 
      this->tabTlgDiagram->Controls->Add(this->panTlgDiagramView);
      this->tabTlgDiagram->Location = System::Drawing::Point(4, 22);
      this->tabTlgDiagram->Name = L"tabTlgDiagram";
      this->tabTlgDiagram->Size = System::Drawing::Size(498, 373);
      this->tabTlgDiagram->TabIndex = 0;
      this->tabTlgDiagram->Text = L"Telegrams";
      this->tabTlgDiagram->UseVisualStyleBackColor = true;
      // 
      // panTlgDiagramView
      // 
      this->panTlgDiagramView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panTlgDiagramView->Location = System::Drawing::Point(0, 0);
      this->panTlgDiagramView->Name = L"panTlgDiagramView";
      this->panTlgDiagramView->Size = System::Drawing::Size(498, 373);
      this->panTlgDiagramView->TabIndex = 0;
      // 
      // tabValueDiagram
      // 
      this->tabValueDiagram->Controls->Add(this->panValueDiagramView);
      this->tabValueDiagram->Location = System::Drawing::Point(4, 22);
      this->tabValueDiagram->Name = L"tabValueDiagram";
      this->tabValueDiagram->Size = System::Drawing::Size(498, 373);
      this->tabValueDiagram->TabIndex = 1;
      this->tabValueDiagram->Text = L"Values";
      this->tabValueDiagram->UseVisualStyleBackColor = true;
      // 
      // panValueDiagramView
      // 
      this->panValueDiagramView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panValueDiagramView->Location = System::Drawing::Point(0, 0);
      this->panValueDiagramView->Name = L"panValueDiagramView";
      this->panValueDiagramView->Size = System::Drawing::Size(498, 373);
      this->panValueDiagramView->TabIndex = 0;
      // 
      // tabDataGrid
      // 
      this->tabDataGrid->Controls->Add(this->panDataGridView);
      this->tabDataGrid->Location = System::Drawing::Point(4, 22);
      this->tabDataGrid->Name = L"tabDataGrid";
      this->tabDataGrid->Size = System::Drawing::Size(498, 373);
      this->tabDataGrid->TabIndex = 2;
      this->tabDataGrid->Text = L"Data table";
      this->tabDataGrid->UseVisualStyleBackColor = true;
      // 
      // panDataGridView
      // 
      this->panDataGridView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panDataGridView->Location = System::Drawing::Point(0, 0);
      this->panDataGridView->Name = L"panDataGridView";
      this->panDataGridView->Size = System::Drawing::Size(498, 373);
      this->panDataGridView->TabIndex = 0;
      // 
      // splitter3
      // 
      this->splitter3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->splitter3->Cursor = System::Windows::Forms::Cursors::HSplit;
      this->splitter3->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->splitter3->Location = System::Drawing::Point(0, 399);
      this->splitter3->Name = L"splitter3";
      this->splitter3->Size = System::Drawing::Size(506, 7);
      this->splitter3->TabIndex = 1;
      this->splitter3->TabStop = false;
      this->splitter3->DoubleClick += gcnew System::EventHandler(this, &CAnalyzeLogFileForm::OnSplitter3Click);
      // 
      // panViewMessageBox
      // 
      this->panViewMessageBox->Controls->Add(this->splitter6);
      this->panViewMessageBox->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->panViewMessageBox->Location = System::Drawing::Point(0, 406);
      this->panViewMessageBox->Name = L"panViewMessageBox";
      this->panViewMessageBox->Size = System::Drawing::Size(506, 130);
      this->panViewMessageBox->TabIndex = 0;
      // 
      // splitter6
      // 
      this->splitter6->Dock = System::Windows::Forms::DockStyle::Top;
      this->splitter6->Location = System::Drawing::Point(0, 0);
      this->splitter6->Name = L"splitter6";
      this->splitter6->Size = System::Drawing::Size(506, 3);
      this->splitter6->TabIndex = 0;
      this->splitter6->TabStop = false;
      // 
      // mainMenu
      // 
      this->mainMenu->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(3) {this->menuItem1, this->menuItem2, 
        this->menuItem5});
      // 
      // menuItem1
      // 
      this->menuItem1->Index = 0;
      this->menuItem1->Text = L"Edit";
      // 
      // menuItem2
      // 
      this->menuItem2->Index = 1;
      this->menuItem2->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(5) {this->menuItem3D, this->menuItemFill, 
        this->menuItemRemoveAll, this->menuItemCursorTool, this->menuItemCustomAxis});
      this->menuItem2->Text = L"View";
      // 
      // menuItem3D
      // 
      this->menuItem3D->Index = 0;
      this->menuItem3D->Text = L"3D View";
      this->menuItem3D->Click += gcnew System::EventHandler(this, &CAnalyzeLogFileForm::OnMenuItem3DClick);
      // 
      // menuItemFill
      // 
      this->menuItemFill->Index = 1;
      this->menuItemFill->Text = L"Full Screen";
      this->menuItemFill->Click += gcnew System::EventHandler(this, &CAnalyzeLogFileForm::OnMenuItemFillClick);
      // 
      // menuItemRemoveAll
      // 
      this->menuItemRemoveAll->Index = 2;
      this->menuItemRemoveAll->Text = L"Remove All";
      this->menuItemRemoveAll->Click += gcnew System::EventHandler(this, &CAnalyzeLogFileForm::OnRemoveAllClick);
      // 
      // menuItemCursorTool
      // 
      this->menuItemCursorTool->Index = 3;
      this->menuItemCursorTool->Text = L"Cursor Tool";
      this->menuItemCursorTool->Click += gcnew System::EventHandler(this, &CAnalyzeLogFileForm::OnMenuItemCursorToolClick);
      // 
      // menuItemCustomAxis
      // 
      this->menuItemCustomAxis->Index = 4;
      this->menuItemCustomAxis->Text = L"Custom Axis";
      this->menuItemCustomAxis->Click += gcnew System::EventHandler(this, &CAnalyzeLogFileForm::OnMenuCustomAxisClick);
      // 
      // menuItem5
      // 
      this->menuItem5->Index = 2;
      this->menuItem5->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(2) {this->menuItemContents, this->menuItemIndex});
      this->menuItem5->Text = L"Help";
      // 
      // menuItemContents
      // 
      this->menuItemContents->Index = 0;
      this->menuItemContents->Text = L"Content";
      this->menuItemContents->Click += gcnew System::EventHandler(this, &CAnalyzeLogFileForm::menuItemContents_Click);
      // 
      // menuItemIndex
      // 
      this->menuItemIndex->Index = 1;
      this->menuItemIndex->Text = L"Index";
      this->menuItemIndex->Click += gcnew System::EventHandler(this, &CAnalyzeLogFileForm::menuItemIndex_Click);
      // 
      // helpProvider1
      // 
      this->helpProvider1->HelpNamespace = L"Simulator.chm";
      // 
      // CAnalyzeLogFileForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(748, 536);
      this->Controls->Add(this->panView1);
      this->Controls->Add(this->splitter1);
      this->Controls->Add(this->panViewLeft);
      this->HelpButton = true;
      this->helpProvider1->SetHelpKeyword(this, L"Log–Fileanalysieren");
      this->helpProvider1->SetHelpNavigator(this, System::Windows::Forms::HelpNavigator::TableOfContents);
      this->helpProvider1->SetHelpString(this, L"Log–Fileanalysieren");
      this->Menu = this->mainMenu;
      this->Name = L"CAnalyzeLogFileForm";
      this->helpProvider1->SetShowHelp(this, true);
      this->Text = L"CAnalyzeLogFileForm";
      this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
      this->Load += gcnew System::EventHandler(this, &CAnalyzeLogFileForm::LoadAnalyzeForm);
      this->SizeChanged += gcnew System::EventHandler(this, &CAnalyzeLogFileForm::OnResizeInterfaceConTlg);
      this->Closing += gcnew System::ComponentModel::CancelEventHandler(this, &CAnalyzeLogFileForm::CAnalyzeLogFileForm_Closing);
      this->panViewLeft->ResumeLayout(false);
      this->panViewNoButAddToAnalyze->ResumeLayout(false);
      this->panViewButAddToAnalyze->ResumeLayout(false);
      this->panViewOptions->ResumeLayout(false);
      this->panViewOptions->PerformLayout();
      this->panView1->ResumeLayout(false);
      this->panView2->ResumeLayout(false);
      this->panViewTeeChart->ResumeLayout(false);
      this->panViewTeeChartDiagram_->ResumeLayout(false);
      this->tabDiagramControl->ResumeLayout(false);
      this->tabTlgDiagram->ResumeLayout(false);
      this->tabValueDiagram->ResumeLayout(false);
      this->tabDataGrid->ResumeLayout(false);
      this->panViewMessageBox->ResumeLayout(false);
      this->ResumeLayout(false);

    }		

	  //private: System::Void OnClickComInterfaceBox(System::Object ^  sender, System::EventArgs ^  e);
	  //private: System::Void OnSelIndexComIntefaceBox(System::Object ^  sender, System::EventArgs ^  e);
    //private: System::Void OnClickAddToFilter(System::Object ^  sender, System::EventArgs ^  e);
    private: 
      void UpdateValuesInTable(String^ name,int countTlg);
      String^ getTlgElem (ArrayList^ list,CItemWrapper^ tlg,CTlgElemWrapper^ elem);
      void logFileReadThread();
      void AbortLogFileReadThread();

      CItemPrototypContainerForm::DelAddToTable^ delAddToTableEvent;
      CItemPrototypContainerForm::DelAddToDiagram^ delAddToDiagramEvent;
      CItemPrototypContainerForm^ InterfaceContainerView;
      CItemPrototypContainerForm::DelRemoveFromDiagram^ delRemoveFromDiagramEvent;
      CItemPrototypContainerForm::DelRemoveFromDataTable^ delRemoveFromDataTableEvent;
      CAnalyzeTlgForm^ TlgForm;
      CAnalyzeSubElemForm^ SubElemForm;
      
      //CTlgDataGridViewForm^ TlgDataTable;
      CDataGridContainerForm^ TlgDataTableCon;
		  
      CMessageForm^ MessageForm;
      CProgressBarViewForm^ barView;
      CTlgInterfaceWrapper^ TlgPrototypCon; 
      //! Enthaelt Tellegramme, die vom Log-File geladen sind.
      CTlgLogFileReaderWrapper^ TlgConFromLogFile; 
      String^ path;
      //int lastPosForTable;
			long last_pos;
      //Zeitinterval, um LogFile automatisch auszulesen.
      int timeForUpdate;
      //ThreadTimer
      System::Threading::Thread^ timerThread;
      System::Threading::Thread^ LogFileReadThread;
      bool isTimerActive;
      bool isThreadReady;
      Hashtable^ NamesOfSubValues;
      //
      System::Windows::Forms::ToolTip^ ToolTipStartAndStop;
      System::Windows::Forms::ToolTip^ ToolTipAdd;
      System::Windows::Forms::ToolTip^ ToolTipRemove;
      System::Windows::Forms::ToolTip^ ToolTipTimeUpdate;
      System::Resources::ResourceManager^ rm;
   
    private: void initViewComponent(ArrayList^ InterfaceListe,int index,String^ path);
    private: System::Void OnAddToAnalyzeClick(System::Object ^  sender, System::EventArgs ^  e);
    private: System::Void OnResizeInterfaceConTlg(System::Object ^  sender, System::EventArgs ^  e);
    private: System::Void OnTimeForUpdateTxtBox(System::Object ^  sender, System::EventArgs ^  e);
    private: System::Void OnTimeForUpdateClick(System::Object ^  sender, System::EventArgs ^  e);
    private: System::Void OnRemoveFromAnalyzeClick(System::Object ^  sender, System::EventArgs ^  e);
    private: System::Void LoadAnalyzeForm(System::Object ^  sender, System::EventArgs ^  e);
    private: System::Void OnMenuItemFillClick(System::Object^  sender, System::EventArgs^  e);
    private: System::Void OnSplitter1Click(System::Object^  sender, System::EventArgs^  e);
    private: System::Void OnSplitter3Click(System::Object^  sender, System::EventArgs^  e);
    private: System::Void CAnalyzeLogFileForm_Closing(System::Object ^  sender, System::ComponentModel::CancelEventArgs ^  e);
    private: System::Void butAddToTable_Click(System::Object^  sender, System::EventArgs^  e);
    private: System::Void tabDiagramControl_SelectedIndexChanged(System::Object ^  sender, System::EventArgs ^  e);
    private: System::Void OnMenuItem3DClick(System::Object ^  sender, System::EventArgs ^  e);
    private: System::Void OnRemoveAllClick(System::Object ^  sender, System::EventArgs ^  e);
    private: System::Void menuItemIndex_Click(System::Object^  sender, System::EventArgs^  e);
    private: System::Void menuItemContents_Click(System::Object^  sender, System::EventArgs^  e); 
    private: System::Void OnMenuItemCursorToolClick(System::Object^  sender, System::EventArgs^  e);
         
private: System::Void OnMenuCustomAxisClick(System::Object^  sender, System::EventArgs^  e) 
         {
           if (tabDiagramControl->SelectedIndex==0)
           {
                TlgForm->setCustomAxisMode(!menuItemCustomAxis->Checked);
                menuItemCustomAxis->Checked = (!menuItemCustomAxis->Checked);
           }
         }
private: System::Void tabDiagramControl_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) 
         {
           if (e->Control)
						 if(e->KeyCode == System::Windows::Forms::Keys::F4) //F4
               if (tabDiagramControl->SelectedIndex == 2 && TlgDataTableCon)
                  this->TlgDataTableCon->CloseSelectedTabPage();
         }
};
}