#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#include "CTree.h"
#include "CNodeCollectionUnit.h"
#include "CItemWrapper.h"

namespace simulator {

	/// <summary>
	/// Zusammenfassung für CItemView
	///
	/// Warnung: Wenn Sie den Namen dieser Klasse ändern, müssen Sie auch
	///          die Ressourcendateiname-Eigenschaft für das Tool zur Kompilierung verwalteter Ressourcen ändern,
	///          das allen RESX-Dateien zugewiesen ist, von denen diese Klasse abhängt.
	///          Anderenfalls können die Designer nicht korrekt mit den lokalisierten Ressourcen
	///          arbeiten, die diesem Formular zugewiesen sind.
	/// </summary>
	public ref class CItemView : public System::Windows::Forms::Form
	{
	  public: delegate void ErrorMessageDelTyp(String^ mess);
            delegate void OkMessageDelTyp(String^ info);
            delegate void TelElemEditEventTyp();
            delegate void AddItemToSzen(CItemWrapper^ wrp,bool modi);
            delegate void SzenarioChangeEventTyp();  
  
    public: enum class CreateTypForm 
		{
      LogFile,
			Prototyp,
      Szenario,
			Receiver,
			none
		};
  
    public:
		  CItemView(Panel^ parent)
		  {
        InitializeComponent();
        InitComponets(parent);
		  }

	  public: 
			void ShowItem(CItemWrapper^ item, CreateTypForm typ);
      void setEditMode(bool edit);
      bool getEditMode(void);
      void setReceiveView();
			void setCreateTypForm(CreateTypForm typ);
      void setSzenarioChangeEventTyp(SzenarioChangeEventTyp^ TypEvent);
			void closeItemView (CreateTypForm typ);
      void setTelElemEditEvent(TelElemEditEventTyp^ editEvent);
      void setDelAddToSzen(AddItemToSzen^ del);
      void setErrorMessageDel(ErrorMessageDelTyp^ del);
      void setOkMessageDel(OkMessageDelTyp^ info);
      static void setNodesCollapsed(int val);
		
	  protected:
		  /// <summary>
		  /// Verwendete Ressourcen bereinigen.
		  /// </summary>
		  ~CItemView()
		  {
        ItemViewList->Remove(this);
        /*if (components)
			  {
				  delete components;
			  }*/
		  }

	  private:
		  /// <summary>
		  /// Erforderliche Designervariable.
		  /// </summary>
      //Intitialisierungsmethoden
      void SelectNextEditableNode(CommonTools::Node^ node,bool forward);
      void CompareValueForColumnsWidth(CTlgElemWrapper^ itemElem);
      void CalcColumnsWidth(CommonTools::Node^ node);
      void CalcColumnsWidth();
      void InitMTree();
      void InitComponets(Panel^ parent);
      bool SavePreviousValue();
	    int getIndexOfNode (CommonTools::Node^ node);
      void CollapseOrExpandAllNode();
      //Rekursive Methode zum Index Visible Node Berechnung
      int CalcNodeIndex(CommonTools::Node^ node);
      ////void CalcSelectedNode(int Y);
      //CommonTools::Node* getIndexOfNode(int &number,CommonTools::Node* node);
      //Standard .Net - Komponenten
		  System::ComponentModel::Container ^ components;
		  System::Windows::Forms::TextBox ^ txtBx;
		  System::Windows::Forms::ToolBar ^ toolBar;
      System::Windows::Forms::ToolTip ^ tBarItemName;
      System::Windows::Forms::ToolTip ^ tBarItemDescription;
      System::Windows::Forms::ToolTip ^ tBarItemDirection;
      System::Windows::Forms::Button ^ butAddToSzen;
      System::Windows::Forms::Panel ^ panInfo;
      /*System::Windows::Forms::Panel * panBody;*/
      System::Windows::Forms::Panel ^ panButtons;
      System::Windows::Forms::Panel ^ panItemInfo;
      System::Windows::Forms::Splitter ^ splitTopHor;
	    System::Windows::Forms::Label ^ labItemName;
	    System::Windows::Forms::Label ^ labItemDescr;
      System::Windows::Forms::Label ^ labDirectionInfo;
      System::Windows::Forms::Label ^ labCreateTypForm;
      //
      System::Windows::Forms::ContextMenu^ m_contextMenu;
      //Externe Steuerkomponenten
      CommonTools::Node^ selectNode;
      //System::Windows::Forms::ColumnHeader^ Element;
      CommonTools::TreeListView^ m_tree;
		  CNodeCollectionUnit^ m_validator;
      //
      System::String^ interfaceName;
      int maxElemDepth;
			CreateTypForm typForm;

      bool editMode;
      //bool isProtoTypItem;
      bool isReciever;
      
      CItemWrapper^ protoItem;
      
      //Deligate - Objekten
      ErrorMessageDelTyp^ ErrorMessageDel;
      OkMessageDelTyp^ OkMessageDel;
      AddItemToSzen^ DelAddItem;
      TelElemEditEventTyp^ TelElemEditEvent;
      SzenarioChangeEventTyp^ SzenarioChangeEvent;
      
      //Interface Einstelungen - Werten
      String^ ItemId;
      String^ ItemElemId;
      String^ ItemIdValue;
      String^ ItemLenId;
      int LenIdModus;

      //Nodes Collapsed
      static int NodesCollapsed;
      static ArrayList^ ItemViewList = gcnew ArrayList();
      
      //Ereignisse
      System::Void OnMouseDownListViewEquals(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e);
      System::Void OnMouseDoubleClick(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e);
      System::Void CItemView::txtBoxEnter(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
      System::Void OnAddButtonClick(System::Object ^  sender, System::EventArgs ^  e);
      System::Void VScrollChanged(Object ^ sender,Windows::Forms::ScrollEventArgs ^ e);
      System::Void HScrollChanged(Object ^ sender,Windows::Forms::ScrollEventArgs ^ e);
      System::Void OnCloseForm(System::Object ^  sender, System::EventArgs ^  e);
      System::Void OnEnterKey(Object ^ sender,Windows::Forms::KeyPressEventArgs ^ e);
      //Void OnColumnEnter(Object ^ sender,Windows::Forms::ColumnClickEventArgs ^ e);
      System::Void OnCollapseAllNodes(System::Object ^ sender,System::EventArgs ^ e);
		  System::Void OnExpandAllNodes(System::Object ^ sender,System::EventArgs ^ e);
      System::Void OnCollapseAllChildrenNodes(System::Object ^ sender,System::EventArgs ^ e);
      System::Void OnMouseWheel(System::Object^ sender,System::Windows::Forms::MouseEventArgs ^ e);
  #pragma region Windows Form Designer generated code
		  /// <summary>
		  /// Erforderliche Methode für die Designerunterstützung.
		  /// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		  /// </summary>
		  void InitializeComponent(void)
		  {
        this->m_tree = gcnew CommonTools::TreeListView();
        this->panInfo = gcnew System::Windows::Forms::Panel();
        this->panButtons = gcnew System::Windows::Forms::Panel();
        this->panItemInfo = gcnew System::Windows::Forms::Panel();
        this->splitTopHor = gcnew System::Windows::Forms::Splitter();
        this->butAddToSzen = gcnew System::Windows::Forms::Button();
        this->labItemDescr = gcnew System::Windows::Forms::Label();
        this->labItemName = gcnew System::Windows::Forms::Label();
        this->labDirectionInfo = gcnew System::Windows::Forms::Label();
        this->labCreateTypForm = gcnew System::Windows::Forms::Label();
        this->tBarItemName = gcnew System::Windows::Forms::ToolTip();
        this->tBarItemDescription = gcnew System::Windows::Forms::ToolTip();
        this->tBarItemDirection = gcnew System::Windows::Forms::ToolTip();

        (safe_cast <System::ComponentModel::ISupportInitialize^>(this->m_tree))->BeginInit();
        this->SuspendLayout();
        // 
        // panInfo
        // 
        this->panInfo->Controls->Add(this->panItemInfo);
        this->panInfo->Controls->Add(this->panButtons);
        this->panInfo->Dock = System::Windows::Forms::DockStyle::Top;
        this->panInfo->Location = System::Drawing::Point(0, 0);
        this->panInfo->Name = "panInfo";
        this->panInfo->Size = System::Drawing::Size(664, 33);
        this->panInfo->TabIndex = 1;
        // 
        // panButtons
        // 
        this->panButtons->Controls->Add(this->butAddToSzen);
        this->panButtons->Dock = System::Windows::Forms::DockStyle::Left;
        this->panButtons->Location = System::Drawing::Point(0,0);
        this->panButtons->AutoScroll = false;
        this->panButtons->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
        this->panButtons->Name = "panButton";
        this->panButtons->Size = System::Drawing::Size(102, 40);
        this->panButtons->TabIndex = 0;
        //
        //panItemInfo
        //
        this->panItemInfo->Controls->Add(this->labItemDescr);
        this->panItemInfo->Controls->Add(this->labCreateTypForm);
        this->panItemInfo->Controls->Add(this->labDirectionInfo);
        this->panItemInfo->Controls->Add(this->labItemName);
        this->panItemInfo->Dock = System::Windows::Forms::DockStyle::Fill;
        this->panButtons->Location = System::Drawing::Point(102,0);
        this->panItemInfo->AutoScroll = false;
        this->panItemInfo->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
        this->panItemInfo->Name = "panItemInfo";
        this->panItemInfo->TabIndex = 1;
        // 
        // splitTopHor
        // 
        this->splitTopHor->Dock = System::Windows::Forms::DockStyle::Top;
        this->splitTopHor->Location = System::Drawing::Point(0, 0);
        this->splitTopHor->Name = L"splitTopHor";
        this->splitTopHor->Size = System::Drawing::Size(673, 3);
        this->splitTopHor->TabIndex = 0;
        this->splitTopHor->TabStop = false;
        // 
        // butAddToSzen
        // 
        this->butAddToSzen->Dock = System::Windows::Forms::DockStyle::Fill;
        this->butAddToSzen->Location = System::Drawing::Point(3,5);
        this->butAddToSzen->Name = "butAddToSzen";
        this->butAddToSzen->Size = System::Drawing::Size(93, 25);
        this->butAddToSzen->Text = "Add to Scenario";
        this->butAddToSzen->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
        this->butAddToSzen->Click += gcnew System::EventHandler(this, &CItemView::OnAddButtonClick);
        // 
        // labDirectionInfo
        // 
        this->labDirectionInfo->AutoSize = false;
        this->labDirectionInfo->Dock = System::Windows::Forms::DockStyle::Left;
        this->labDirectionInfo->Font = (gcnew System::Drawing::Font("Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
          static_cast<System::Byte>(0)));
        this->labDirectionInfo->Location = System::Drawing::Point(0, 0);
        this->labDirectionInfo->Name = "labItemName";
        this->labDirectionInfo->Size = System::Drawing::Size(120, 35);
        this->labDirectionInfo->TabIndex = 0;
        this->labDirectionInfo->Text = "";
        this->labDirectionInfo->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
        // 
        // labItemName
        // 
        this->labItemName->AutoSize = false;
        this->labItemName->Dock = System::Windows::Forms::DockStyle::Left;
        this->labItemName->Font = (gcnew System::Drawing::Font("Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
          static_cast<System::Byte>(0)));
        this->labItemName->Location = System::Drawing::Point(90, 0);
        this->labItemName->Name = "labItemName";
        this->labItemName->Size = System::Drawing::Size(90, 35);
        this->labItemName->TabIndex = 0;
        this->labItemName->Text = "";
        this->labItemName->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
        //
        //labCreateTypForm
        //
        this->labCreateTypForm->AutoSize = false;
        this->labCreateTypForm->Dock = System::Windows::Forms::DockStyle::Left;
        this->labCreateTypForm->Font = (gcnew System::Drawing::Font("Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
          static_cast<System::Byte>(0)));
        this->labCreateTypForm->Location = System::Drawing::Point(180, 0);
        this->labCreateTypForm->Name = "labCreateTypForm";
        this->labCreateTypForm->Size = System::Drawing::Size(90, 35);
        this->labCreateTypForm->TabIndex = 1;
        this->labCreateTypForm->Text = "";
        this->labCreateTypForm->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
        // 
        // labItemDescr
        // 
        this->labItemDescr->AutoSize = false;
        this->labItemDescr->Dock = System::Windows::Forms::DockStyle::Left;
        this->labItemDescr->Font = (gcnew System::Drawing::Font("Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
          static_cast<System::Byte>(0)));
        this->labItemDescr->Location = System::Drawing::Point(270, 0);
        this->labItemDescr->Name = "labItemDescr";
        this->labItemDescr->Size = System::Drawing::Size(350, 35);
        this->labItemDescr->TabIndex = 1;
        this->labItemDescr->Text = "";
        this->labItemDescr->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
        // 
			  // m_tree
			  // 
        this->m_tree->Anchor = ((System::Windows::Forms::AnchorStyles)((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				  | System::Windows::Forms::AnchorStyles::Left)
 				  | System::Windows::Forms::AnchorStyles::Right)));
        this->InitMTree();

        this->m_tree->Cursor = System::Windows::Forms::Cursors::Arrow;
        this->m_tree->Images = nullptr;
	      this->m_tree->Location = System::Drawing::Point(3, 33);
        this->m_tree->Name = "m_tree";
	      this->m_tree->Size =  System::Drawing::Size(933, 354);
        this->m_tree->TabIndex = 0;
        this->m_tree->ViewOptions->BorderStyle = System::Windows::Forms::BorderStyle::None;
        this->m_tree->Dock = System::Windows::Forms::DockStyle::Fill;
        this->m_tree->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this,&CItemView::OnMouseDownListViewEquals);
        this->m_tree->getVScroll()->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this,&CItemView::HScrollChanged);
        this->m_tree->getHScroll()->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this,&CItemView::VScrollChanged);
        this->m_tree->KeyPress += gcnew Windows::Forms::KeyPressEventHandler(this,&CItemView::OnEnterKey);
        this->m_tree->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this,&CItemView::OnMouseWheel);
        this->m_tree->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this,&CItemView::OnMouseDoubleClick);
        this->m_tree->Capture = true;
        // 
	      // CItemView
	      // 
	      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	      this->ClientSize = System::Drawing::Size(552, 458);
        this->Controls->Add(this->m_tree);
        this->Controls->Add(this->panInfo);  
	      this->Name = "CItemView";
        this->Text = "CItemView";
        this->Closed += gcnew System::EventHandler(this, &CItemView::OnCloseForm);
        this->TopLevel = false;
        this->Dock = DockStyle::Fill;
				this->FormBorderStyle = ::FormBorderStyle::None;
        (safe_cast <System::ComponentModel::ISupportInitialize^>(this->m_tree))->EndInit();
        this->ResumeLayout(false);
      }

      private: System::Void TxtBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e); 
  #pragma endregion
	};
}
