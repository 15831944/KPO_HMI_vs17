#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#include "CItemWrapper.h"

namespace simulator
{
	/// <summary> 
	/// Summary for CTlgDataGridView
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CTlgDataGridViewForm : public System::Windows::Forms::Form
	{
	public: 
		CTlgDataGridViewForm(Panel^ parent)
		{
			this->components = gcnew System::ComponentModel::Container();
			InitializeComponent();
      initViewComponent(parent);
		}

    void addItem(CItemWrapper^ item);
    void addItemValue(CItemWrapper^ item);
    System::String^ getItemName();
    int getCountOfRows();
    void ShowData();
        
	protected: 
		//void Dispose(Boolean disposing)
		//{
		//	if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
      
    System::String^ ItemName;
    System::Data::DataTable^ table;
	private: System::ComponentModel::IContainer^  components;
  private: System::Windows::Forms::Panel^  panTableView;
  private: System::Windows::Forms::DataGridViewTextBoxColumn^  Name_;
  private: System::Windows::Forms::DataGridViewTextBoxColumn^  Value_;
	private: System::Windows::Forms::Panel^  panDataGridView;
  private: DevExpress::XtraGrid::GridControl^  gridControl1;
  private: DevExpress::XtraGrid::Views::Grid::GridView^  gridView1;
		
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
  
    void addItemElem(CTlgElemWrapper^ itemElem);
    void addItemElemValue(CTlgElemWrapper^ item,System::Data::DataRow^ row);
    void initViewComponent(Panel^ parent);
    
		void InitializeComponent(void)
		{
      this->panTableView = (gcnew System::Windows::Forms::Panel());
      this->panDataGridView = (gcnew System::Windows::Forms::Panel());
      this->gridControl1 = (gcnew DevExpress::XtraGrid::GridControl());
      this->gridView1 = (gcnew DevExpress::XtraGrid::Views::Grid::GridView());
      this->Name_ = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->Value_ = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->panTableView->SuspendLayout();
      this->panDataGridView->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridControl1))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridView1))->BeginInit();
      this->SuspendLayout();
      // 
      // panTableView
      // 
      this->panTableView->Controls->Add(this->panDataGridView);
      this->panTableView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panTableView->Location = System::Drawing::Point(0, 0);
      this->panTableView->Name = L"panTableView";
      this->panTableView->Size = System::Drawing::Size(883, 508);
      this->panTableView->TabIndex = 1;
      // 
      // panDataGridView
      // 
      this->panDataGridView->Controls->Add(this->gridControl1);
      this->panDataGridView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panDataGridView->Location = System::Drawing::Point(0, 0);
      this->panDataGridView->Name = L"panDataGridView";
      this->panDataGridView->Size = System::Drawing::Size(883, 508);
      this->panDataGridView->TabIndex = 2;
      // 
      // gridControl1
      // 
      this->gridControl1->Dock = System::Windows::Forms::DockStyle::Fill;
      this->gridControl1->EmbeddedNavigator->Name = L"";
      this->gridControl1->Location = System::Drawing::Point(0, 0);
      this->gridControl1->MainView = this->gridView1;
      this->gridControl1->Name = L"gridControl1";
      this->gridControl1->Size = System::Drawing::Size(883, 508);
      this->gridControl1->TabIndex = 3;
      this->gridControl1->ViewCollection->AddRange(gcnew cli::array< DevExpress::XtraGrid::Views::Base::BaseView^  >(1) {this->gridView1});
      // 
      // gridView1
      // 
      this->gridView1->Appearance->ColumnFilterButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(212)), 
        static_cast<System::Int32>(static_cast<System::Byte>(208)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
      this->gridView1->Appearance->ColumnFilterButton->BackColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(232)), 
        static_cast<System::Int32>(static_cast<System::Byte>(228)), static_cast<System::Int32>(static_cast<System::Byte>(220)));
      this->gridView1->Appearance->ColumnFilterButton->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(212)), 
        static_cast<System::Int32>(static_cast<System::Byte>(208)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
      this->gridView1->Appearance->ColumnFilterButton->ForeColor = System::Drawing::Color::Gray;
      this->gridView1->Appearance->ColumnFilterButton->Options->UseBackColor = true;
      this->gridView1->Appearance->ColumnFilterButton->Options->UseBorderColor = true;
      this->gridView1->Appearance->ColumnFilterButton->Options->UseForeColor = true;
      this->gridView1->Appearance->ColumnFilterButtonActive->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(232)), 
        static_cast<System::Int32>(static_cast<System::Byte>(228)), static_cast<System::Int32>(static_cast<System::Byte>(220)));
      this->gridView1->Appearance->ColumnFilterButtonActive->BackColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(238)), 
        static_cast<System::Int32>(static_cast<System::Byte>(235)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
      this->gridView1->Appearance->ColumnFilterButtonActive->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(232)), 
        static_cast<System::Int32>(static_cast<System::Byte>(228)), static_cast<System::Int32>(static_cast<System::Byte>(220)));
      this->gridView1->Appearance->ColumnFilterButtonActive->ForeColor = System::Drawing::Color::Blue;
      this->gridView1->Appearance->ColumnFilterButtonActive->Options->UseBackColor = true;
      this->gridView1->Appearance->ColumnFilterButtonActive->Options->UseBorderColor = true;
      this->gridView1->Appearance->ColumnFilterButtonActive->Options->UseForeColor = true;
      this->gridView1->Appearance->Empty->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(232)), 
        static_cast<System::Int32>(static_cast<System::Byte>(228)), static_cast<System::Int32>(static_cast<System::Byte>(220)));
      this->gridView1->Appearance->Empty->Options->UseBackColor = true;
      this->gridView1->Appearance->EvenRow->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(212)), 
        static_cast<System::Int32>(static_cast<System::Byte>(208)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
      this->gridView1->Appearance->EvenRow->BackColor2 = System::Drawing::Color::GhostWhite;
      this->gridView1->Appearance->EvenRow->ForeColor = System::Drawing::Color::Black;
      this->gridView1->Appearance->EvenRow->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::ForwardDiagonal;
      this->gridView1->Appearance->EvenRow->Options->UseBackColor = true;
      this->gridView1->Appearance->EvenRow->Options->UseForeColor = true;
      this->gridView1->Appearance->FilterCloseButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(212)), 
        static_cast<System::Int32>(static_cast<System::Byte>(208)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
      this->gridView1->Appearance->FilterCloseButton->BackColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(118)), 
        static_cast<System::Int32>(static_cast<System::Byte>(170)), static_cast<System::Int32>(static_cast<System::Byte>(225)));
      this->gridView1->Appearance->FilterCloseButton->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(212)), 
        static_cast<System::Int32>(static_cast<System::Byte>(208)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
      this->gridView1->Appearance->FilterCloseButton->ForeColor = System::Drawing::Color::Black;
      this->gridView1->Appearance->FilterCloseButton->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::ForwardDiagonal;
      this->gridView1->Appearance->FilterCloseButton->Options->UseBackColor = true;
      this->gridView1->Appearance->FilterCloseButton->Options->UseBorderColor = true;
      this->gridView1->Appearance->FilterCloseButton->Options->UseForeColor = true;
      this->gridView1->Appearance->FilterPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(28)), 
        static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(135)));
      this->gridView1->Appearance->FilterPanel->BackColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(212)), 
        static_cast<System::Int32>(static_cast<System::Byte>(208)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
      this->gridView1->Appearance->FilterPanel->ForeColor = System::Drawing::Color::White;
      this->gridView1->Appearance->FilterPanel->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::ForwardDiagonal;
      this->gridView1->Appearance->FilterPanel->Options->UseBackColor = true;
      this->gridView1->Appearance->FilterPanel->Options->UseForeColor = true;
      this->gridView1->Appearance->FixedLine->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(58)), 
        static_cast<System::Int32>(static_cast<System::Byte>(58)), static_cast<System::Int32>(static_cast<System::Byte>(58)));
      this->gridView1->Appearance->FixedLine->Options->UseBackColor = true;
      this->gridView1->Appearance->FocusedCell->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
        static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(225)));
      this->gridView1->Appearance->FocusedCell->ForeColor = System::Drawing::Color::Black;
      this->gridView1->Appearance->FocusedCell->Options->UseBackColor = true;
      this->gridView1->Appearance->FocusedCell->Options->UseForeColor = true;
      this->gridView1->Appearance->FocusedRow->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(10)), 
        static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(106)));
      this->gridView1->Appearance->FocusedRow->BackColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), 
        static_cast<System::Int32>(static_cast<System::Byte>(86)), static_cast<System::Int32>(static_cast<System::Byte>(156)));
      this->gridView1->Appearance->FocusedRow->ForeColor = System::Drawing::Color::White;
      this->gridView1->Appearance->FocusedRow->Options->UseBackColor = true;
      this->gridView1->Appearance->FocusedRow->Options->UseForeColor = true;
      this->gridView1->Appearance->FooterPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(212)), 
        static_cast<System::Int32>(static_cast<System::Byte>(208)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
      this->gridView1->Appearance->FooterPanel->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(212)), 
        static_cast<System::Int32>(static_cast<System::Byte>(208)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
      this->gridView1->Appearance->FooterPanel->ForeColor = System::Drawing::Color::Black;
      this->gridView1->Appearance->FooterPanel->Options->UseBackColor = true;
      this->gridView1->Appearance->FooterPanel->Options->UseBorderColor = true;
      this->gridView1->Appearance->FooterPanel->Options->UseForeColor = true;
      this->gridView1->Appearance->GroupButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(212)), 
        static_cast<System::Int32>(static_cast<System::Byte>(208)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
      this->gridView1->Appearance->GroupButton->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(212)), 
        static_cast<System::Int32>(static_cast<System::Byte>(208)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
      this->gridView1->Appearance->GroupButton->ForeColor = System::Drawing::Color::Black;
      this->gridView1->Appearance->GroupButton->Options->UseBackColor = true;
      this->gridView1->Appearance->GroupButton->Options->UseBorderColor = true;
      this->gridView1->Appearance->GroupButton->Options->UseForeColor = true;
      this->gridView1->Appearance->GroupFooter->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(222)), 
        static_cast<System::Int32>(static_cast<System::Byte>(218)), static_cast<System::Int32>(static_cast<System::Byte>(210)));
      this->gridView1->Appearance->GroupFooter->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(222)), 
        static_cast<System::Int32>(static_cast<System::Byte>(218)), static_cast<System::Int32>(static_cast<System::Byte>(210)));
      this->gridView1->Appearance->GroupFooter->ForeColor = System::Drawing::Color::Black;
      this->gridView1->Appearance->GroupFooter->Options->UseBackColor = true;
      this->gridView1->Appearance->GroupFooter->Options->UseBorderColor = true;
      this->gridView1->Appearance->GroupFooter->Options->UseForeColor = true;
      this->gridView1->Appearance->GroupPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(58)), 
        static_cast<System::Int32>(static_cast<System::Byte>(110)), static_cast<System::Int32>(static_cast<System::Byte>(165)));
      this->gridView1->Appearance->GroupPanel->BackColor2 = System::Drawing::Color::White;
      this->gridView1->Appearance->GroupPanel->Font = (gcnew System::Drawing::Font(L"Tahoma", 8, System::Drawing::FontStyle::Bold));
      this->gridView1->Appearance->GroupPanel->ForeColor = System::Drawing::Color::White;
      this->gridView1->Appearance->GroupPanel->Options->UseBackColor = true;
      this->gridView1->Appearance->GroupPanel->Options->UseFont = true;
      this->gridView1->Appearance->GroupPanel->Options->UseForeColor = true;
      this->gridView1->Appearance->GroupRow->BackColor = System::Drawing::Color::Gray;
      this->gridView1->Appearance->GroupRow->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(212)), 
        static_cast<System::Int32>(static_cast<System::Byte>(208)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
      this->gridView1->Appearance->GroupRow->Options->UseBackColor = true;
      this->gridView1->Appearance->GroupRow->Options->UseForeColor = true;
      this->gridView1->Appearance->HeaderPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(212)), 
        static_cast<System::Int32>(static_cast<System::Byte>(208)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
      this->gridView1->Appearance->HeaderPanel->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(212)), 
        static_cast<System::Int32>(static_cast<System::Byte>(208)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
      this->gridView1->Appearance->HeaderPanel->Font = (gcnew System::Drawing::Font(L"Tahoma", 8, System::Drawing::FontStyle::Bold));
      this->gridView1->Appearance->HeaderPanel->ForeColor = System::Drawing::Color::Black;
      this->gridView1->Appearance->HeaderPanel->Options->UseBackColor = true;
      this->gridView1->Appearance->HeaderPanel->Options->UseBorderColor = true;
      this->gridView1->Appearance->HeaderPanel->Options->UseFont = true;
      this->gridView1->Appearance->HeaderPanel->Options->UseForeColor = true;
      this->gridView1->Appearance->HideSelectionRow->BackColor = System::Drawing::Color::Gray;
      this->gridView1->Appearance->HideSelectionRow->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(212)), 
        static_cast<System::Int32>(static_cast<System::Byte>(208)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
      this->gridView1->Appearance->HideSelectionRow->Options->UseBackColor = true;
      this->gridView1->Appearance->HideSelectionRow->Options->UseForeColor = true;
      this->gridView1->Appearance->HorzLine->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(212)), 
        static_cast<System::Int32>(static_cast<System::Byte>(208)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
      this->gridView1->Appearance->HorzLine->Options->UseBackColor = true;
      this->gridView1->Appearance->OddRow->BackColor = System::Drawing::Color::White;
      this->gridView1->Appearance->OddRow->BackColor2 = System::Drawing::Color::White;
      this->gridView1->Appearance->OddRow->ForeColor = System::Drawing::Color::Black;
      this->gridView1->Appearance->OddRow->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::BackwardDiagonal;
      this->gridView1->Appearance->OddRow->Options->UseBackColor = true;
      this->gridView1->Appearance->OddRow->Options->UseForeColor = true;
      this->gridView1->Appearance->Preview->BackColor = System::Drawing::Color::White;
      this->gridView1->Appearance->Preview->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(10)), 
        static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(106)));
      this->gridView1->Appearance->Preview->Options->UseBackColor = true;
      this->gridView1->Appearance->Preview->Options->UseForeColor = true;
      this->gridView1->Appearance->Row->BackColor = System::Drawing::Color::White;
      this->gridView1->Appearance->Row->ForeColor = System::Drawing::Color::Black;
      this->gridView1->Appearance->Row->Options->UseBackColor = true;
      this->gridView1->Appearance->Row->Options->UseForeColor = true;
      this->gridView1->Appearance->RowSeparator->BackColor = System::Drawing::Color::White;
      this->gridView1->Appearance->RowSeparator->BackColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(232)), 
        static_cast<System::Int32>(static_cast<System::Byte>(228)), static_cast<System::Int32>(static_cast<System::Byte>(220)));
      this->gridView1->Appearance->RowSeparator->Options->UseBackColor = true;
      this->gridView1->Appearance->SelectedRow->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), 
        static_cast<System::Int32>(static_cast<System::Byte>(46)), static_cast<System::Int32>(static_cast<System::Byte>(116)));
      this->gridView1->Appearance->SelectedRow->ForeColor = System::Drawing::Color::White;
      this->gridView1->Appearance->SelectedRow->Options->UseBackColor = true;
      this->gridView1->Appearance->SelectedRow->Options->UseForeColor = true;
      this->gridView1->Appearance->VertLine->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(212)), 
        static_cast<System::Int32>(static_cast<System::Byte>(208)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
      this->gridView1->Appearance->VertLine->Options->UseBackColor = true;
      this->gridView1->GridControl = this->gridControl1;
      this->gridView1->Name = L"gridView1";
      this->gridView1->OptionsBehavior->Editable = false;
      this->gridView1->OptionsMenu->EnableColumnMenu = false;
      this->gridView1->OptionsMenu->EnableFooterMenu = false;
      this->gridView1->OptionsMenu->EnableGroupPanelMenu = false;
      this->gridView1->OptionsNavigation->AutoFocusNewRow = true;
      this->gridView1->OptionsSelection->MultiSelect = true;
      this->gridView1->OptionsView->ColumnAutoWidth = false;
      this->gridView1->OptionsView->EnableAppearanceEvenRow = true;
      this->gridView1->OptionsView->EnableAppearanceOddRow = true;
      this->gridView1->OptionsView->RowAutoHeight = true;
      // 
      // Name_
      // 
      this->Name_->Name = L"Name_";
      // 
      // Value_
      // 
      this->Value_->Name = L"Value_";
      // 
      // CTlgDataGridViewForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(883, 508);
      this->Controls->Add(this->panTableView);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
      this->Name = L"CTlgDataGridViewForm";
      this->Text = L"CTlgDataGridView";
      this->panTableView->ResumeLayout(false);
      this->panDataGridView->ResumeLayout(false);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridControl1))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridView1))->EndInit();
      this->ResumeLayout(false);

    }		
	};
}