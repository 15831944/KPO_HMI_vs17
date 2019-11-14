#pragma once

#include "CTlgElemWrapper.h"
#include "CItemWrapper.h"
#include "CCyclicElemTable.h"
#include "CCyclicItemContainer.h"
#include "CMessageForm.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Collections::Generic;


namespace simulator {

	/// <summary>
	/// Summary for CInfoDescriptionForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CCyclicTlgForm : public System::Windows::Forms::Form
	{
	public:
    CCyclicTlgForm(CMessageForm^ MessageForm,List<CTlgInterfaceWrapper^>^ InterfaceProtoArray)
		{
			InitializeComponent();
      selectedItem = nullptr;
      selectedElem = nullptr;
      selectedInterfaceName = nullptr;
      selectedElemTable = nullptr;
      firstView = true;
      cyclicItemContainer = CCyclicItemContainer::getCyclicItemContainer();
      this->MessageForm = MessageForm;
      this->InterfaceProtoArray = InterfaceProtoArray;
			initComponent();
		}
	private: System::Windows::Forms::Panel^  panLeftView;
	private: System::Windows::Forms::Splitter^  splitter1;
	private: System::Windows::Forms::Panel^  panRightView;
	private: System::Windows::Forms::Splitter^  splitter2;
	private: System::Windows::Forms::Panel^  panButtonsBottomView;
  private: System::Windows::Forms::Button^  butClose;
	private: System::Windows::Forms::Panel^  panElemDetailView;
	private: System::Windows::Forms::TextBox^  textBxTimeInterval;
	private: System::Windows::Forms::RadioButton^  radBtVariabel;
	private: System::Windows::Forms::Label^  labTimeInterval;
	private: System::Windows::Forms::Label^  labElemName;
	private: System::Windows::Forms::TextBox^  txtBxValueChange;
	private: System::Windows::Forms::ComboBox^  comBxChange;

	private: System::Windows::Forms::TreeView^  trItemView;
	private: System::Windows::Forms::Panel^  panTimeIntervalView;
	private: System::Windows::Forms::Panel^  panVariabelView;
	private: System::Windows::Forms::Splitter^  splitter4;
	private: System::Windows::Forms::Panel^  panElemInfoView;
	private: System::Windows::Forms::Label^  labElemValue;
	private: System::Windows::Forms::Label^  labElemTyp;
	private: System::Windows::Forms::Splitter^  splitter3;
  private: System::Windows::Forms::TreeView^  trViewCyclicTlgInSzenario;
  private: System::Windows::Forms::GroupBox^  gpBoxOptions;
  private: System::Windows::Forms::GroupBox^  gpBoxInfo;
  private: System::Windows::Forms::GroupBox^  gpBoxButtons;
  private: System::Windows::Forms::GroupBox^  gpBoxElements;
  private: System::Windows::Forms::GroupBox^  gpBoxItems;
  private: System::Windows::Forms::Label^  label3;
  private: System::Windows::Forms::Label^  label2;
  private: System::Windows::Forms::Label^  label1;

  private: System::Windows::Forms::GroupBox^  grBoxInterface;
  private: System::Windows::Forms::ComboBox^  comBoxInterfaces;
  private: System::Windows::Forms::Button^  butRemove;
  private: System::Windows::Forms::Button^  butSave;
  private: System::Windows::Forms::Button^  butLoad;
  private: System::Windows::Forms::TextBox^  txtBxMinValue;
  private: System::Windows::Forms::TextBox^  txtBxMaxValue;
  private: System::Windows::Forms::Label^  labMax;
  private: System::Windows::Forms::Label^  labMin;

  private: System::Windows::Forms::Label^  labSec;
  private: System::Windows::Forms::Label^  labStartValue;
  private: System::Windows::Forms::Label^  labValueChange;
  private: System::Windows::Forms::TextBox^  txtBxStartValue;
  private: System::Windows::Forms::Label^  labMathOp;
  private: System::Windows::Forms::GroupBox^  groupBox1;

  private: System::Windows::Forms::Button^  butDefaultsValues;
  private: System::Windows::Forms::Button^  butMinValue;
  private: System::Windows::Forms::Button^  butMaxValue;
  private: System::Windows::Forms::GroupBox^  gpBoxTime;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/*~CInfoDescriptionForm()
		{
    if (components)
			{
				delete components;
			}
		}*/
	private:
		void setNodeColorText(CTlgElemWrapper^ elem,System::Windows::Forms::TreeNode^ subElemNodeRet );
		void initComponent();
		void showItem();
    void showAllItems();
		void showAll();
    void ClearView();
    void SetMinOrMaxValue(double value);
    void WriteMessage(String^ mes,int typ);
    void initToolTips();
   
    System::Windows::Forms::TreeNode^ buildElemNodes (CTlgElemWrapper^ elem);
		CItemWrapper^ selectedItem;
    CTlgElemWrapper^ selectedElem;
		//System::Collections::Hashtable^ elemTable; 
    String^ selectedInterfaceName;
    CCyclicElemTable^ selectedElemTable;
    CCyclicItemContainer^ cyclicItemContainer;
    CMessageForm^ MessageForm;
    List<CTlgInterfaceWrapper^>^ InterfaceProtoArray;
    bool firstView;
		/*__value enum changeTyp 
		{
			none,
			plus,
			minus,
			multiple,
			divide
		};*/

		//__gc struct ElemStatus
    //  {
    //    double limit;
    //    changeTyp change;
		//	double changeValue;

		//	ElemStatus()
		//	{
		//		limit = 0.0;
		//		change = none;
		//		changeValue = 0.0;
		//	}

		//	ElemStatus(double l,changeTyp typ, double value)
		//	{
		//		limit = l;
		//		change = typ;
		//		changeValue = value;
		//	}
    //  };

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
		System::Void trItemView_BeforeSelect(System::Object^  sender, System::Windows::Forms::TreeViewCancelEventArgs^  e);
    System::Void comBxChange_TextChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void trItemView_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e);
    System::Void trViewCyclicTlgInSzenario_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e);
    System::Void trViewCyclicTlgInSzenario_BeforeSelect(System::Object^  sender, System::Windows::Forms::TreeViewCancelEventArgs^  e);
    System::Void butClose_Click(System::Object^  sender, System::EventArgs^  e); 
    System::Void butRemove_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void comBoxInterfaces_TextChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void butSave_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void butLoad_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void checkBxDefaultValues_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void textBxTimeInterval_Leave(System::Object^  sender, System::EventArgs^  e);
    System::Void textBxTimeInterval_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
    System::Void txtBxStartValue_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
    System::Void txtBxStartValue_Leave(System::Object^  sender, System::EventArgs^  e);
    System::Void txtBxValueChange_Leave(System::Object^  sender, System::EventArgs^  e);
    System::Void txtBxValueChange_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e); 
    System::Void txtBxMinValue_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e); 
    System::Void txtBxMinValue_Leave(System::Object^  sender, System::EventArgs^  e); 
    System::Void txtBxMaxValue_Leave(System::Object^  sender, System::EventArgs^  e); 
    System::Void txtBxMaxValue_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
    System::Void butMaxMinValues_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void butDefaultsValues_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void butMaxValue_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void butMinValue_Click(System::Object^  sender, System::EventArgs^  e);

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      this->panLeftView = (gcnew System::Windows::Forms::Panel());
      this->gpBoxElements = (gcnew System::Windows::Forms::GroupBox());
      this->trItemView = (gcnew System::Windows::Forms::TreeView());
      this->gpBoxItems = (gcnew System::Windows::Forms::GroupBox());
      this->trViewCyclicTlgInSzenario = (gcnew System::Windows::Forms::TreeView());
      this->grBoxInterface = (gcnew System::Windows::Forms::GroupBox());
      this->comBoxInterfaces = (gcnew System::Windows::Forms::ComboBox());
      this->splitter1 = (gcnew System::Windows::Forms::Splitter());
      this->panRightView = (gcnew System::Windows::Forms::Panel());
      this->panElemDetailView = (gcnew System::Windows::Forms::Panel());
      this->panVariabelView = (gcnew System::Windows::Forms::Panel());
      this->gpBoxOptions = (gcnew System::Windows::Forms::GroupBox());
      this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
      this->butMinValue = (gcnew System::Windows::Forms::Button());
      this->butDefaultsValues = (gcnew System::Windows::Forms::Button());
      this->butMaxValue = (gcnew System::Windows::Forms::Button());
      this->txtBxMinValue = (gcnew System::Windows::Forms::TextBox());
      this->txtBxMaxValue = (gcnew System::Windows::Forms::TextBox());
      this->labMin = (gcnew System::Windows::Forms::Label());
      this->labMax = (gcnew System::Windows::Forms::Label());
      this->labMathOp = (gcnew System::Windows::Forms::Label());
      this->labStartValue = (gcnew System::Windows::Forms::Label());
      this->labValueChange = (gcnew System::Windows::Forms::Label());
      this->txtBxStartValue = (gcnew System::Windows::Forms::TextBox());
      this->comBxChange = (gcnew System::Windows::Forms::ComboBox());
      this->txtBxValueChange = (gcnew System::Windows::Forms::TextBox());
      this->splitter4 = (gcnew System::Windows::Forms::Splitter());
      this->panElemInfoView = (gcnew System::Windows::Forms::Panel());
      this->gpBoxInfo = (gcnew System::Windows::Forms::GroupBox());
      this->label3 = (gcnew System::Windows::Forms::Label());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->labElemTyp = (gcnew System::Windows::Forms::Label());
      this->labElemValue = (gcnew System::Windows::Forms::Label());
      this->labElemName = (gcnew System::Windows::Forms::Label());
      this->splitter3 = (gcnew System::Windows::Forms::Splitter());
      this->panTimeIntervalView = (gcnew System::Windows::Forms::Panel());
      this->gpBoxTime = (gcnew System::Windows::Forms::GroupBox());
      this->labSec = (gcnew System::Windows::Forms::Label());
      this->labTimeInterval = (gcnew System::Windows::Forms::Label());
      this->textBxTimeInterval = (gcnew System::Windows::Forms::TextBox());
      this->radBtVariabel = (gcnew System::Windows::Forms::RadioButton());
      this->splitter2 = (gcnew System::Windows::Forms::Splitter());
      this->panButtonsBottomView = (gcnew System::Windows::Forms::Panel());
      this->gpBoxButtons = (gcnew System::Windows::Forms::GroupBox());
      this->butClose = (gcnew System::Windows::Forms::Button());
      this->butRemove = (gcnew System::Windows::Forms::Button());
      this->butLoad = (gcnew System::Windows::Forms::Button());
      this->butSave = (gcnew System::Windows::Forms::Button());
      this->panLeftView->SuspendLayout();
      this->gpBoxElements->SuspendLayout();
      this->gpBoxItems->SuspendLayout();
      this->grBoxInterface->SuspendLayout();
      this->panRightView->SuspendLayout();
      this->panElemDetailView->SuspendLayout();
      this->panVariabelView->SuspendLayout();
      this->gpBoxOptions->SuspendLayout();
      this->groupBox1->SuspendLayout();
      this->panElemInfoView->SuspendLayout();
      this->gpBoxInfo->SuspendLayout();
      this->panTimeIntervalView->SuspendLayout();
      this->gpBoxTime->SuspendLayout();
      this->panButtonsBottomView->SuspendLayout();
      this->gpBoxButtons->SuspendLayout();
      this->SuspendLayout();
      // 
      // panLeftView
      // 
      this->panLeftView->Controls->Add(this->gpBoxElements);
      this->panLeftView->Controls->Add(this->gpBoxItems);
      this->panLeftView->Controls->Add(this->grBoxInterface);
      this->panLeftView->Dock = System::Windows::Forms::DockStyle::Left;
      this->panLeftView->Location = System::Drawing::Point(0, 0);
      this->panLeftView->Name = L"panLeftView";
      this->panLeftView->Size = System::Drawing::Size(170, 511);
      this->panLeftView->TabIndex = 0;
      // 
      // gpBoxElements
      // 
      this->gpBoxElements->Controls->Add(this->trItemView);
      this->gpBoxElements->Dock = System::Windows::Forms::DockStyle::Fill;
      this->gpBoxElements->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->gpBoxElements->Location = System::Drawing::Point(0, 135);
      this->gpBoxElements->Name = L"gpBoxElements";
      this->gpBoxElements->Size = System::Drawing::Size(170, 376);
      this->gpBoxElements->TabIndex = 2;
      this->gpBoxElements->TabStop = false;
      this->gpBoxElements->Text = L"Elements of cyclic telegram";
      // 
      // trItemView
      // 
      this->trItemView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->trItemView->HideSelection = false;
      this->trItemView->Location = System::Drawing::Point(3, 17);
      this->trItemView->Name = L"trItemView";
      this->trItemView->Size = System::Drawing::Size(164, 356);
      this->trItemView->TabIndex = 2;
      this->trItemView->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &CCyclicTlgForm::trItemView_AfterSelect);
      this->trItemView->BeforeSelect += gcnew System::Windows::Forms::TreeViewCancelEventHandler(this, &CCyclicTlgForm::trItemView_BeforeSelect);
      // 
      // gpBoxItems
      // 
      this->gpBoxItems->Controls->Add(this->trViewCyclicTlgInSzenario);
      this->gpBoxItems->Dock = System::Windows::Forms::DockStyle::Top;
      this->gpBoxItems->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->gpBoxItems->Location = System::Drawing::Point(0, 41);
      this->gpBoxItems->Name = L"gpBoxItems";
      this->gpBoxItems->Size = System::Drawing::Size(170, 94);
      this->gpBoxItems->TabIndex = 1;
      this->gpBoxItems->TabStop = false;
      this->gpBoxItems->Text = L"Telegrams";
      // 
      // trViewCyclicTlgInSzenario
      // 
      this->trViewCyclicTlgInSzenario->Dock = System::Windows::Forms::DockStyle::Fill;
      this->trViewCyclicTlgInSzenario->HideSelection = false;
      this->trViewCyclicTlgInSzenario->Location = System::Drawing::Point(3, 17);
      this->trViewCyclicTlgInSzenario->Name = L"trViewCyclicTlgInSzenario";
      this->trViewCyclicTlgInSzenario->ShowLines = false;
      this->trViewCyclicTlgInSzenario->Size = System::Drawing::Size(164, 74);
      this->trViewCyclicTlgInSzenario->TabIndex = 1;
      this->trViewCyclicTlgInSzenario->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &CCyclicTlgForm::trViewCyclicTlgInSzenario_AfterSelect);
      this->trViewCyclicTlgInSzenario->BeforeSelect += gcnew System::Windows::Forms::TreeViewCancelEventHandler(this, &CCyclicTlgForm::trViewCyclicTlgInSzenario_BeforeSelect);
      // 
      // grBoxInterface
      // 
      this->grBoxInterface->Controls->Add(this->comBoxInterfaces);
      this->grBoxInterface->Dock = System::Windows::Forms::DockStyle::Top;
      this->grBoxInterface->Location = System::Drawing::Point(0, 0);
      this->grBoxInterface->Name = L"grBoxInterface";
      this->grBoxInterface->Size = System::Drawing::Size(170, 41);
      this->grBoxInterface->TabIndex = 0;
      this->grBoxInterface->TabStop = false;
      this->grBoxInterface->Text = L"Interfaces";
      // 
      // comBoxInterfaces
      // 
      this->comBoxInterfaces->FormattingEnabled = true;
      this->comBoxInterfaces->Location = System::Drawing::Point(23, 16);
      this->comBoxInterfaces->Name = L"comBoxInterfaces";
      this->comBoxInterfaces->Size = System::Drawing::Size(121, 21);
      this->comBoxInterfaces->TabIndex = 0;
      this->comBoxInterfaces->TextChanged += gcnew System::EventHandler(this, &CCyclicTlgForm::comBoxInterfaces_TextChanged);
      // 
      // splitter1
      // 
      this->splitter1->BackColor = System::Drawing::SystemColors::Control;
      this->splitter1->Location = System::Drawing::Point(170, 0);
      this->splitter1->Name = L"splitter1";
      this->splitter1->Size = System::Drawing::Size(3, 511);
      this->splitter1->TabIndex = 1;
      this->splitter1->TabStop = false;
      // 
      // panRightView
      // 
      this->panRightView->Controls->Add(this->panElemDetailView);
      this->panRightView->Controls->Add(this->splitter2);
      this->panRightView->Controls->Add(this->panButtonsBottomView);
      this->panRightView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panRightView->Location = System::Drawing::Point(173, 0);
      this->panRightView->Name = L"panRightView";
      this->panRightView->Size = System::Drawing::Size(401, 511);
      this->panRightView->TabIndex = 1;
      // 
      // panElemDetailView
      // 
      this->panElemDetailView->Controls->Add(this->panVariabelView);
      this->panElemDetailView->Controls->Add(this->splitter4);
      this->panElemDetailView->Controls->Add(this->panElemInfoView);
      this->panElemDetailView->Controls->Add(this->splitter3);
      this->panElemDetailView->Controls->Add(this->panTimeIntervalView);
      this->panElemDetailView->Controls->Add(this->radBtVariabel);
      this->panElemDetailView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panElemDetailView->Location = System::Drawing::Point(0, 0);
      this->panElemDetailView->Name = L"panElemDetailView";
      this->panElemDetailView->Size = System::Drawing::Size(401, 438);
      this->panElemDetailView->TabIndex = 0;
      // 
      // panVariabelView
      // 
      this->panVariabelView->Controls->Add(this->gpBoxOptions);
      this->panVariabelView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panVariabelView->Location = System::Drawing::Point(0, 175);
      this->panVariabelView->Name = L"panVariabelView";
      this->panVariabelView->Size = System::Drawing::Size(401, 263);
      this->panVariabelView->TabIndex = 2;
      // 
      // gpBoxOptions
      // 
      this->gpBoxOptions->Controls->Add(this->groupBox1);
      this->gpBoxOptions->Controls->Add(this->labMathOp);
      this->gpBoxOptions->Controls->Add(this->labStartValue);
      this->gpBoxOptions->Controls->Add(this->labValueChange);
      this->gpBoxOptions->Controls->Add(this->txtBxStartValue);
      this->gpBoxOptions->Controls->Add(this->comBxChange);
      this->gpBoxOptions->Controls->Add(this->txtBxValueChange);
      this->gpBoxOptions->Dock = System::Windows::Forms::DockStyle::Fill;
      this->gpBoxOptions->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->gpBoxOptions->Location = System::Drawing::Point(0, 0);
      this->gpBoxOptions->Name = L"gpBoxOptions";
      this->gpBoxOptions->Size = System::Drawing::Size(401, 263);
      this->gpBoxOptions->TabIndex = 2;
      this->gpBoxOptions->TabStop = false;
      this->gpBoxOptions->Text = L"Options";
      // 
      // groupBox1
      // 
      this->groupBox1->Controls->Add(this->butMinValue);
      this->groupBox1->Controls->Add(this->butDefaultsValues);
      this->groupBox1->Controls->Add(this->butMaxValue);
      this->groupBox1->Controls->Add(this->txtBxMinValue);
      this->groupBox1->Controls->Add(this->txtBxMaxValue);
      this->groupBox1->Controls->Add(this->labMin);
      this->groupBox1->Controls->Add(this->labMax);
      this->groupBox1->Location = System::Drawing::Point(12, 105);
      this->groupBox1->Name = L"groupBox1";
      this->groupBox1->Size = System::Drawing::Size(305, 133);
      this->groupBox1->TabIndex = 3;
      this->groupBox1->TabStop = false;
      // 
      // butMinValue
      // 
      this->butMinValue->Location = System::Drawing::Point(219, 96);
      this->butMinValue->Name = L"butMinValue";
      this->butMinValue->Size = System::Drawing::Size(75, 28);
      this->butMinValue->TabIndex = 7;
      this->butMinValue->Text = L"Min. value";
      this->butMinValue->UseVisualStyleBackColor = true;
      this->butMinValue->Click += gcnew System::EventHandler(this, &CCyclicTlgForm::butMinValue_Click);
      // 
      // butDefaultsValues
      // 
      this->butDefaultsValues->Location = System::Drawing::Point(4, 96);
      this->butDefaultsValues->Name = L"butDefaultsValues";
      this->butDefaultsValues->Size = System::Drawing::Size(95, 28);
      this->butDefaultsValues->TabIndex = 5;
      this->butDefaultsValues->Text = L"Default values";
      this->butDefaultsValues->UseVisualStyleBackColor = true;
      this->butDefaultsValues->Click += gcnew System::EventHandler(this, &CCyclicTlgForm::butDefaultsValues_Click);
      // 
      // butMaxValue
      // 
      this->butMaxValue->Location = System::Drawing::Point(138, 96);
      this->butMaxValue->Name = L"butMaxValue";
      this->butMaxValue->Size = System::Drawing::Size(75, 28);
      this->butMaxValue->TabIndex = 6;
      this->butMaxValue->Text = L"Max. value";
      this->butMaxValue->UseVisualStyleBackColor = true;
      this->butMaxValue->Click += gcnew System::EventHandler(this, &CCyclicTlgForm::butMaxValue_Click);
      // 
      // txtBxMinValue
      // 
      this->txtBxMinValue->Location = System::Drawing::Point(6, 20);
      this->txtBxMinValue->Name = L"txtBxMinValue";
      this->txtBxMinValue->Size = System::Drawing::Size(77, 21);
      this->txtBxMinValue->TabIndex = 3;
      this->txtBxMinValue->Leave += gcnew System::EventHandler(this, &CCyclicTlgForm::txtBxMinValue_Leave);
      this->txtBxMinValue->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &CCyclicTlgForm::txtBxMinValue_KeyPress);
      // 
      // txtBxMaxValue
      // 
      this->txtBxMaxValue->Location = System::Drawing::Point(6, 59);
      this->txtBxMaxValue->Name = L"txtBxMaxValue";
      this->txtBxMaxValue->Size = System::Drawing::Size(77, 21);
      this->txtBxMaxValue->TabIndex = 4;
      this->txtBxMaxValue->Leave += gcnew System::EventHandler(this, &CCyclicTlgForm::txtBxMaxValue_Leave);
      this->txtBxMaxValue->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &CCyclicTlgForm::txtBxMaxValue_KeyPress);
      // 
      // labMin
      // 
      this->labMin->AutoSize = true;
      this->labMin->Location = System::Drawing::Point(89, 23);
      this->labMin->Name = L"labMin";
      this->labMin->Size = System::Drawing::Size(99, 15);
      this->labMin->TabIndex = 3;
      this->labMin->Text = L"- Minimum value";
      // 
      // labMax
      // 
      this->labMax->AutoSize = true;
      this->labMax->Location = System::Drawing::Point(89, 62);
      this->labMax->Name = L"labMax";
      this->labMax->Size = System::Drawing::Size(102, 15);
      this->labMax->TabIndex = 4;
      this->labMax->Text = L"- Maximum value";
      // 
      // labMathOp
      // 
      this->labMathOp->AutoSize = true;
      this->labMathOp->Location = System::Drawing::Point(99, 28);
      this->labMathOp->Name = L"labMathOp";
      this->labMathOp->Size = System::Drawing::Size(144, 15);
      this->labMathOp->TabIndex = 0;
      this->labMathOp->Text = L"- Mathematical operation";
      // 
      // labStartValue
      // 
      this->labStartValue->AutoSize = true;
      this->labStartValue->Location = System::Drawing::Point(99, 54);
      this->labStartValue->Name = L"labStartValue";
      this->labStartValue->Size = System::Drawing::Size(71, 15);
      this->labStartValue->TabIndex = 1;
      this->labStartValue->Text = L"- Start value";
      // 
      // labValueChange
      // 
      this->labValueChange->AutoSize = true;
      this->labValueChange->Location = System::Drawing::Point(99, 81);
      this->labValueChange->Name = L"labValueChange";
      this->labValueChange->Size = System::Drawing::Size(135, 15);
      this->labValueChange->TabIndex = 2;
      this->labValueChange->Text = L"- Value of this operation";
      // 
      // txtBxStartValue
      // 
      this->txtBxStartValue->Location = System::Drawing::Point(16, 51);
      this->txtBxStartValue->Name = L"txtBxStartValue";
      this->txtBxStartValue->Size = System::Drawing::Size(77, 21);
      this->txtBxStartValue->TabIndex = 1;
      this->txtBxStartValue->Leave += gcnew System::EventHandler(this, &CCyclicTlgForm::txtBxStartValue_Leave);
      this->txtBxStartValue->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &CCyclicTlgForm::txtBxStartValue_KeyPress);
      // 
      // comBxChange
      // 
      this->comBxChange->FormattingEnabled = true;
      this->comBxChange->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"none", L"+", L"-", L"*", L"/"});
      this->comBxChange->Location = System::Drawing::Point(16, 25);
      this->comBxChange->Name = L"comBxChange";
      this->comBxChange->Size = System::Drawing::Size(77, 23);
      this->comBxChange->TabIndex = 0;
      this->comBxChange->TextChanged += gcnew System::EventHandler(this, &CCyclicTlgForm::comBxChange_TextChanged);
      // 
      // txtBxValueChange
      // 
      this->txtBxValueChange->Location = System::Drawing::Point(16, 78);
      this->txtBxValueChange->Name = L"txtBxValueChange";
      this->txtBxValueChange->Size = System::Drawing::Size(77, 21);
      this->txtBxValueChange->TabIndex = 2;
      this->txtBxValueChange->Leave += gcnew System::EventHandler(this, &CCyclicTlgForm::txtBxValueChange_Leave);
      this->txtBxValueChange->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &CCyclicTlgForm::txtBxValueChange_KeyPress);
      // 
      // splitter4
      // 
      this->splitter4->Dock = System::Windows::Forms::DockStyle::Top;
      this->splitter4->Location = System::Drawing::Point(0, 174);
      this->splitter4->Name = L"splitter4";
      this->splitter4->Size = System::Drawing::Size(401, 1);
      this->splitter4->TabIndex = 12;
      this->splitter4->TabStop = false;
      // 
      // panElemInfoView
      // 
      this->panElemInfoView->Controls->Add(this->gpBoxInfo);
      this->panElemInfoView->Dock = System::Windows::Forms::DockStyle::Top;
      this->panElemInfoView->Location = System::Drawing::Point(0, 51);
      this->panElemInfoView->Name = L"panElemInfoView";
      this->panElemInfoView->Size = System::Drawing::Size(401, 123);
      this->panElemInfoView->TabIndex = 1;
      // 
      // gpBoxInfo
      // 
      this->gpBoxInfo->Controls->Add(this->label3);
      this->gpBoxInfo->Controls->Add(this->label2);
      this->gpBoxInfo->Controls->Add(this->label1);
      this->gpBoxInfo->Controls->Add(this->labElemTyp);
      this->gpBoxInfo->Controls->Add(this->labElemValue);
      this->gpBoxInfo->Controls->Add(this->labElemName);
      this->gpBoxInfo->Dock = System::Windows::Forms::DockStyle::Fill;
      this->gpBoxInfo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->gpBoxInfo->Location = System::Drawing::Point(0, 0);
      this->gpBoxInfo->Name = L"gpBoxInfo";
      this->gpBoxInfo->Size = System::Drawing::Size(401, 123);
      this->gpBoxInfo->TabIndex = 1;
      this->gpBoxInfo->TabStop = false;
      this->gpBoxInfo->Text = L"Element infomation";
      // 
      // label3
      // 
      this->label3->AutoSize = true;
      this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->label3->Location = System::Drawing::Point(9, 53);
      this->label3->Name = L"label3";
      this->label3->Size = System::Drawing::Size(45, 15);
      this->label3->TabIndex = 8;
      this->label3->Text = L"  Type :";
      this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // label2
      // 
      this->label2->AutoSize = true;
      this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->label2->Location = System::Drawing::Point(9, 86);
      this->label2->Name = L"label2";
      this->label2->Size = System::Drawing::Size(44, 15);
      this->label2->TabIndex = 7;
      this->label2->Text = L"Value :";
      this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->label1->Location = System::Drawing::Point(9, 17);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(47, 15);
      this->label1->TabIndex = 3;
      this->label1->Text = L"Name :";
      this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // labElemTyp
      // 
      this->labElemTyp->AutoSize = true;
      this->labElemTyp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->labElemTyp->Location = System::Drawing::Point(84, 53);
      this->labElemTyp->Name = L"labElemTyp";
      this->labElemTyp->Size = System::Drawing::Size(0, 15);
      this->labElemTyp->TabIndex = 5;
      this->labElemTyp->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // labElemValue
      // 
      this->labElemValue->AutoSize = true;
      this->labElemValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->labElemValue->Location = System::Drawing::Point(87, 86);
      this->labElemValue->Name = L"labElemValue";
      this->labElemValue->Size = System::Drawing::Size(0, 15);
      this->labElemValue->TabIndex = 6;
      this->labElemValue->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // labElemName
      // 
      this->labElemName->AutoSize = true;
      this->labElemName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->labElemName->Location = System::Drawing::Point(84, 17);
      this->labElemName->Name = L"labElemName";
      this->labElemName->Size = System::Drawing::Size(0, 15);
      this->labElemName->TabIndex = 3;
      this->labElemName->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // splitter3
      // 
      this->splitter3->Dock = System::Windows::Forms::DockStyle::Top;
      this->splitter3->Location = System::Drawing::Point(0, 50);
      this->splitter3->Name = L"splitter3";
      this->splitter3->Size = System::Drawing::Size(401, 1);
      this->splitter3->TabIndex = 10;
      this->splitter3->TabStop = false;
      // 
      // panTimeIntervalView
      // 
      this->panTimeIntervalView->Controls->Add(this->gpBoxTime);
      this->panTimeIntervalView->Dock = System::Windows::Forms::DockStyle::Top;
      this->panTimeIntervalView->Location = System::Drawing::Point(0, 0);
      this->panTimeIntervalView->Name = L"panTimeIntervalView";
      this->panTimeIntervalView->Size = System::Drawing::Size(401, 50);
      this->panTimeIntervalView->TabIndex = 0;
      // 
      // gpBoxTime
      // 
      this->gpBoxTime->Controls->Add(this->labSec);
      this->gpBoxTime->Controls->Add(this->labTimeInterval);
      this->gpBoxTime->Controls->Add(this->textBxTimeInterval);
      this->gpBoxTime->Dock = System::Windows::Forms::DockStyle::Fill;
      this->gpBoxTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->gpBoxTime->Location = System::Drawing::Point(0, 0);
      this->gpBoxTime->Name = L"gpBoxTime";
      this->gpBoxTime->Size = System::Drawing::Size(401, 50);
      this->gpBoxTime->TabIndex = 0;
      this->gpBoxTime->TabStop = false;
      this->gpBoxTime->Text = L"Cyclic time";
      // 
      // labSec
      // 
      this->labSec->AutoSize = true;
      this->labSec->Location = System::Drawing::Point(154, 25);
      this->labSec->Name = L"labSec";
      this->labSec->Size = System::Drawing::Size(27, 15);
      this->labSec->TabIndex = 5;
      this->labSec->Text = L"ms.";
      // 
      // labTimeInterval
      // 
      this->labTimeInterval->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->labTimeInterval->Location = System::Drawing::Point(9, 26);
      this->labTimeInterval->Name = L"labTimeInterval";
      this->labTimeInterval->Size = System::Drawing::Size(53, 21);
      this->labTimeInterval->TabIndex = 0;
      this->labTimeInterval->Text = L"Interval :";
      // 
      // textBxTimeInterval
      // 
      this->textBxTimeInterval->Location = System::Drawing::Point(68, 25);
      this->textBxTimeInterval->Name = L"textBxTimeInterval";
      this->textBxTimeInterval->Size = System::Drawing::Size(80, 21);
      this->textBxTimeInterval->TabIndex = 4;
      this->textBxTimeInterval->Leave += gcnew System::EventHandler(this, &CCyclicTlgForm::textBxTimeInterval_Leave);
      this->textBxTimeInterval->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &CCyclicTlgForm::textBxTimeInterval_KeyPress);
      // 
      // radBtVariabel
      // 
      this->radBtVariabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->radBtVariabel->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
      this->radBtVariabel->Location = System::Drawing::Point(177, 253);
      this->radBtVariabel->Name = L"radBtVariabel";
      this->radBtVariabel->Size = System::Drawing::Size(89, 195);
      this->radBtVariabel->TabIndex = 1;
      this->radBtVariabel->TabStop = true;
      this->radBtVariabel->UseVisualStyleBackColor = true;
      // 
      // splitter2
      // 
      this->splitter2->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->splitter2->Location = System::Drawing::Point(0, 438);
      this->splitter2->Name = L"splitter2";
      this->splitter2->Size = System::Drawing::Size(401, 1);
      this->splitter2->TabIndex = 4;
      this->splitter2->TabStop = false;
      // 
      // panButtonsBottomView
      // 
      this->panButtonsBottomView->Controls->Add(this->gpBoxButtons);
      this->panButtonsBottomView->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->panButtonsBottomView->Location = System::Drawing::Point(0, 439);
      this->panButtonsBottomView->Name = L"panButtonsBottomView";
      this->panButtonsBottomView->Size = System::Drawing::Size(401, 72);
      this->panButtonsBottomView->TabIndex = 1;
      // 
      // gpBoxButtons
      // 
      this->gpBoxButtons->Controls->Add(this->butClose);
      this->gpBoxButtons->Controls->Add(this->butRemove);
      this->gpBoxButtons->Controls->Add(this->butLoad);
      this->gpBoxButtons->Controls->Add(this->butSave);
      this->gpBoxButtons->Dock = System::Windows::Forms::DockStyle::Fill;
      this->gpBoxButtons->Location = System::Drawing::Point(0, 0);
      this->gpBoxButtons->Name = L"gpBoxButtons";
      this->gpBoxButtons->Size = System::Drawing::Size(401, 72);
      this->gpBoxButtons->TabIndex = 1;
      this->gpBoxButtons->TabStop = false;
      // 
      // butClose
      // 
      this->butClose->Location = System::Drawing::Point(301, 12);
      this->butClose->Name = L"butClose";
      this->butClose->Size = System::Drawing::Size(95, 54);
      this->butClose->TabIndex = 3;
      this->butClose->Text = L"Close dialog";
      this->butClose->UseVisualStyleBackColor = true;
      this->butClose->Click += gcnew System::EventHandler(this, &CCyclicTlgForm::butClose_Click);
      // 
      // butRemove
      // 
      this->butRemove->Location = System::Drawing::Point(6, 12);
      this->butRemove->Name = L"butRemove";
      this->butRemove->Size = System::Drawing::Size(95, 54);
      this->butRemove->TabIndex = 0;
      this->butRemove->Text = L"Remove selected telegramm";
      this->butRemove->UseVisualStyleBackColor = true;
      this->butRemove->Click += gcnew System::EventHandler(this, &CCyclicTlgForm::butRemove_Click);
      // 
      // butLoad
      // 
      this->butLoad->Location = System::Drawing::Point(203, 12);
      this->butLoad->Name = L"butLoad";
      this->butLoad->Size = System::Drawing::Size(95, 54);
      this->butLoad->TabIndex = 2;
      this->butLoad->Text = L"Load configuration from xml file";
      this->butLoad->UseVisualStyleBackColor = true;
      this->butLoad->Click += gcnew System::EventHandler(this, &CCyclicTlgForm::butLoad_Click);
      // 
      // butSave
      // 
      this->butSave->Location = System::Drawing::Point(104, 12);
      this->butSave->Name = L"butSave";
      this->butSave->Size = System::Drawing::Size(95, 54);
      this->butSave->TabIndex = 1;
      this->butSave->Text = L"Save configuration at xml file";
      this->butSave->UseVisualStyleBackColor = true;
      this->butSave->Click += gcnew System::EventHandler(this, &CCyclicTlgForm::butSave_Click);
      // 
      // CCyclicTlgForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
      this->BackColor = System::Drawing::SystemColors::Control;
      this->ClientSize = System::Drawing::Size(574, 511);
      this->ControlBox = false;
      this->Controls->Add(this->panRightView);
      this->Controls->Add(this->splitter1);
      this->Controls->Add(this->panLeftView);
      this->Cursor = System::Windows::Forms::Cursors::Default;
      this->Name = L"CCyclicTlgForm";
      this->ShowInTaskbar = false;
      this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Show;
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
      this->Text = L"Configuration of cyclic telegram";
      this->TopMost = true;
      this->panLeftView->ResumeLayout(false);
      this->gpBoxElements->ResumeLayout(false);
      this->gpBoxItems->ResumeLayout(false);
      this->grBoxInterface->ResumeLayout(false);
      this->panRightView->ResumeLayout(false);
      this->panElemDetailView->ResumeLayout(false);
      this->panVariabelView->ResumeLayout(false);
      this->gpBoxOptions->ResumeLayout(false);
      this->gpBoxOptions->PerformLayout();
      this->groupBox1->ResumeLayout(false);
      this->groupBox1->PerformLayout();
      this->panElemInfoView->ResumeLayout(false);
      this->gpBoxInfo->ResumeLayout(false);
      this->gpBoxInfo->PerformLayout();
      this->panTimeIntervalView->ResumeLayout(false);
      this->gpBoxTime->ResumeLayout(false);
      this->gpBoxTime->PerformLayout();
      this->panButtonsBottomView->ResumeLayout(false);
      this->gpBoxButtons->ResumeLayout(false);
      this->ResumeLayout(false);

    }
#pragma endregion


};
}
