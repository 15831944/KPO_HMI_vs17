#pragma once

//--------------------------------------------------------------------------
#include "CItemBaseContainerWrapper.h"
#include "CTlgWrapper.h"
//--------------------------------------------------------------------------

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

//---------------------------------------------------------------------------
namespace simulator
{
	/// <summary> 
	/// Summary for CTlgContainerSortForm
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CTlgContainerSortForm : public System::Windows::Forms::Form
	{
    public: delegate void sortedEventTyp();
    public: 
	  CTlgContainerSortForm(void)
	  {
		  InitializeComponent();
		  Container=nullptr;
		  SortedEvent=nullptr;
      this->selectedItemIndex=-1;
	  }
    void setContainerToSort(CItemBaseContainerWrapper^ con);   
    void setSortedEvent(sortedEventTyp^ event);
	  protected: 
		  //void Dispose(Boolean disposing)
		  //{
			 // if (disposing && components)
			 // {
				//  components->Dispose();
			 // }
			 // __super::Dispose(disposing);
		  //}

    private: System::Windows::Forms::Label ^  label1;
    private: System::Windows::Forms::Label ^  label2;
    private: System::Windows::Forms::Label ^  label3;
    private: System::Windows::Forms::Button ^  button1;
    private: System::Windows::Forms::Button ^  button2;
    private: System::Windows::Forms::GroupBox ^  groupBox1;
    private: System::Windows::Forms::Label ^  label4;
    private: System::Windows::Forms::Button ^  button3;
    private: System::Windows::Forms::Button ^  button4;
    private: System::Windows::Forms::Button ^  button5;
    private: System::Windows::Forms::ComboBox ^  comBxTel;
    private: System::Windows::Forms::ComboBox ^  comBxTelElem;
    private: System::Windows::Forms::ColumnHeader ^  Telegram;
    private: System::Windows::Forms::ColumnHeader ^  Element;
    private: System::Windows::Forms::ColumnHeader ^  Typ;
    private: System::Windows::Forms::ListView ^  listViewSort;
    private: System::Windows::Forms::Button^  buttUp;
    private: System::Windows::Forms::Button^  buttDown;
	  private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager((CTlgContainerSortForm::typeid)));
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->comBxTelElem = (gcnew System::Windows::Forms::ComboBox());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->label3 = (gcnew System::Windows::Forms::Label());
      this->button1 = (gcnew System::Windows::Forms::Button());
      this->button2 = (gcnew System::Windows::Forms::Button());
      this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
      this->comBxTel = (gcnew System::Windows::Forms::ComboBox());
      this->label4 = (gcnew System::Windows::Forms::Label());
      this->button3 = (gcnew System::Windows::Forms::Button());
      this->button4 = (gcnew System::Windows::Forms::Button());
      this->button5 = (gcnew System::Windows::Forms::Button());
      this->listViewSort = (gcnew System::Windows::Forms::ListView());
      this->Telegram = (gcnew System::Windows::Forms::ColumnHeader());
      this->Element = (gcnew System::Windows::Forms::ColumnHeader());
      this->Typ = (gcnew System::Windows::Forms::ColumnHeader());
      this->buttUp = (gcnew System::Windows::Forms::Button());
      this->buttDown = (gcnew System::Windows::Forms::Button());
      this->groupBox1->SuspendLayout();
      this->SuspendLayout();
      // 
      // label1
      // 
      this->label1->Location = System::Drawing::Point(271, 16);
      this->label1->Name = "label1";
      this->label1->Size = System::Drawing::Size(41, 23);
      this->label1->TabIndex = 0;
      this->label1->Text = "Sort by";
      this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // comBxTelElem
      // 
      this->comBxTelElem->Location = System::Drawing::Point(318, 16);
      this->comBxTelElem->Name = "comBxTelElem";
      this->comBxTelElem->Size = System::Drawing::Size(205, 21);
      this->comBxTelElem->TabIndex = 1;
      this->comBxTelElem->SelectedIndexChanged += gcnew System::EventHandler(this, &CTlgContainerSortForm::OnComBxTlgElemSelectIndexChanged);
      // 
      // label2
      // 
      this->label2->Location = System::Drawing::Point(274, 40);
      this->label2->Name = "label2";
      this->label2->Size = System::Drawing::Size(249, 48);
      this->label2->TabIndex = 2;
      this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
      // 
      // label3
      // 
      this->label3->Location = System::Drawing::Point(11, 48);
      this->label3->Name = "label3";
      this->label3->Size = System::Drawing::Size(254, 40);
      this->label3->TabIndex = 3;
      this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
      // 
      // button1
      // 
      this->button1->Location = System::Drawing::Point(477, 238);
      this->button1->Name = "button1";
      this->button1->Size = System::Drawing::Size(85, 25);
      this->button1->TabIndex = 4;
      this->button1->Text = "Sort";
      this->button1->Click += gcnew System::EventHandler(this, &CTlgContainerSortForm::OnSortButtonClick);
      // 
      // button2
      // 
      this->button2->Location = System::Drawing::Point(477, 309);
      this->button2->Name = "button2";
      this->button2->Size = System::Drawing::Size(85, 25);
      this->button2->TabIndex = 5;
      this->button2->Text = "Close";
      this->button2->Click += gcnew System::EventHandler(this, &CTlgContainerSortForm::OnClickCloseButton);
      // 
      // groupBox1
      // 
      this->groupBox1->Controls->Add(this->comBxTel);
      this->groupBox1->Controls->Add(this->label4);
      this->groupBox1->Controls->Add(this->label1);
      this->groupBox1->Controls->Add(this->comBxTelElem);
      this->groupBox1->Controls->Add(this->label3);
      this->groupBox1->Controls->Add(this->label2);
      this->groupBox1->Location = System::Drawing::Point(16, 16);
      this->groupBox1->Name = "groupBox1";
      this->groupBox1->Size = System::Drawing::Size(536, 104);
      this->groupBox1->TabIndex = 7;
      this->groupBox1->TabStop = false;
      // 
      // comBxTel
      // 
      this->comBxTel->Location = System::Drawing::Point(80, 16);
      this->comBxTel->Name = "comBxTel";
      this->comBxTel->Size = System::Drawing::Size(185, 21);
      this->comBxTel->TabIndex = 1;
      this->comBxTel->SelectedIndexChanged += gcnew System::EventHandler(this, &CTlgContainerSortForm::OnComBxTelSelectedIndexChanged);
      // 
      // label4
      // 
      this->label4->Location = System::Drawing::Point(8, 16);
      this->label4->Name = "label4";
      this->label4->Size = System::Drawing::Size(72, 23);
      this->label4->TabIndex = 0;
      this->label4->Text = "Telegramm";
      this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // button3
      // 
      this->button3->Location = System::Drawing::Point(477, 166);
      this->button3->Name = "button3";
      this->button3->Size = System::Drawing::Size(85, 25);
      this->button3->TabIndex = 9;
      this->button3->Text = "Add";
      this->button3->Click += gcnew System::EventHandler(this, &CTlgContainerSortForm::OnAddButtonClick);
      // 
      // button4
      // 
      this->button4->Location = System::Drawing::Point(477, 197);
      this->button4->Name = "button4";
      this->button4->Size = System::Drawing::Size(85, 25);
      this->button4->TabIndex = 10;
      this->button4->Text = "Remove";
      this->button4->Click += gcnew System::EventHandler(this, &CTlgContainerSortForm::OnRemoveButtonClick);
      // 
      // button5
      // 
      this->button5->Location = System::Drawing::Point(477, 269);
      this->button5->Name = "button5";
      this->button5->Size = System::Drawing::Size(85, 25);
      this->button5->TabIndex = 11;
      this->button5->Text = "Sort by Time";
      this->button5->Click += gcnew System::EventHandler(this, &CTlgContainerSortForm::OnClickSortbyTimeButton);
      // 
      // listViewSort
      // 
      this->listViewSort->Columns->AddRange(gcnew array< System::Windows::Forms::ColumnHeader^ >(3) {Telegram, Element, Typ});
      this->listViewSort->FullRowSelect = true;
      this->listViewSort->Location = System::Drawing::Point(16, 126);
      this->listViewSort->MultiSelect = false;
      this->listViewSort->Name = "listViewSort";
      this->listViewSort->Size = System::Drawing::Size(455, 208);
      this->listViewSort->TabIndex = 12;
      this->listViewSort->UseCompatibleStateImageBehavior = false;
      this->listViewSort->View = System::Windows::Forms::View::Details;
      // 
      // Telegram
      // 
      this->Telegram->Text = "Telegram";
      this->Telegram->Width = 141;
      // 
      // Element
      // 
      this->Element->Text = "Element";
      this->Element->Width = 144;
      // 
      // Typ
      // 
      this->Typ->Text = "Typ";
      // 
      // buttUp
      // 
      this->buttUp->Image = (safe_cast<System::Drawing::Image^  >(resources->GetObject("buttUp.Image")));
      this->buttUp->Location = System::Drawing::Point(518, 126);
      this->buttUp->Name = "buttUp";
      this->buttUp->Size = System::Drawing::Size(34, 24);
      this->buttUp->TabIndex = 14;
      this->buttUp->Click += gcnew System::EventHandler(this, &CTlgContainerSortForm::buttUp_Click);
      // 
      // buttDown
      // 
      this->buttDown->Image = (safe_cast<System::Drawing::Image^  >(resources->GetObject("buttDown.Image")));
      this->buttDown->Location = System::Drawing::Point(478, 126);
      this->buttDown->Name = "buttDown";
      this->buttDown->Size = System::Drawing::Size(34, 24);
      this->buttDown->TabIndex = 15;
      this->buttDown->Click += gcnew System::EventHandler(this, &CTlgContainerSortForm::buttDown_Click);
      // 
      // CTlgContainerSortForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(564, 346);
      this->Controls->Add(this->buttDown);
      this->Controls->Add(this->buttUp);
      this->Controls->Add(this->listViewSort);
      this->Controls->Add(this->button5);
      this->Controls->Add(this->button4);
      this->Controls->Add(this->button3);
      this->Controls->Add(this->groupBox1);
      this->Controls->Add(this->button2);
      this->Controls->Add(this->button1);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
      this->Name = "CTlgContainerSortForm";
      this->Text = "Sort Telegramm";
      this->groupBox1->ResumeLayout(false);
      this->ResumeLayout(false);

    }		

    System::Void OnComBxTelSelectedIndexChanged(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnComBxTlgElemSelectIndexChanged(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnAddButtonClick(System::Object ^  sender, System::EventArgs ^  e);
		System::Void OnRemoveButtonClick(System::Object ^  sender, System::EventArgs ^  e);
		System::Void OnSortButtonClick(System::Object ^  sender, System::EventArgs ^  e);
		System::Void OnClickSortbyTimeButton(System::Object ^  sender, System::EventArgs ^  e);
		System::Void OnClickCloseButton(System::Object ^  sender, System::EventArgs ^  e);
    System::Void buttDown_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void buttUp_Click(System::Object^  sender, System::EventArgs^  e);
    void initTelFromContainer();
    void CTlgContainerSortForm::addSubElemNameToComBx(CTlgElemWrapper^ elem,String^ text);
		bool isInSortList(String^ tlg);
    CItemBaseContainerWrapper^ Container;
		sortedEventTyp^ SortedEvent;	 
    int selectedItemIndex;
private: System::Void listViewSort_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
         {
            //this->c
         }
};
}