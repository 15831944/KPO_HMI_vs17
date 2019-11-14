#pragma once
//---------------------------------------------------
#include "CItemBaseContainerWrapper.h"
#include "CItemView.h"
#include "CItemWrapper.h"
//---------------------------------------------------
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

//---------------------------------------------------
namespace simulator
{

  
  
  /// <summary> 
  /// Summary for CTlgContainerTreeViewForm
  ///
  /// WARNING: If you change the name of this class, you will need to change the 
  ///          'Resource File Name' property for the managed resource compiler tool 
  ///          associated with all .resx files this class depends on.  Otherwise,
  ///          the designers will not be able to interact properly with localized
  ///          resources associated with this form.
  /// </summary>
  public ref class CTlgContainerTreeViewForm : public System::Windows::Forms::Form
  {
  //public ref class m_TreeView : public System::Windows::Forms::TreeView
  //{
  //  public: m_TreeView()
  //  {
  //    /*DoubleBuffered = true;*/
  //    SetStyle(ControlStyles::DoubleBuffer, true);

  //  }
  //};
  
  
  public: delegate void DelMessageHandlerTyp(String^ mess,int messTyp);
  public: delegate void DelAddNodeType(); 
  public: delegate void AfterSelectEvent(CItemWrapper^ wrp,CItemView::CreateTypForm typ);
  public: delegate void DataUpdateEvent();
  public: delegate void ItemViewChangeEvent(int pos,int count);
  public: delegate void enableScrollEventTyp();
  public: delegate void ScrollPositionUpdateTyp();
  public: delegate void UpdateFilterTextTyp(String^ filter);
  
  public:
    CTlgContainerTreeViewForm(void)
    {
      InitializeComponent();
      TlgContainer = nullptr;
      SelectEvent = nullptr;
      UpdateFlag=true;
      DataUpdate=nullptr;
      ItemViewChange=nullptr;
      MessageHandler=nullptr;
      scrollPositionUpdate=nullptr;
      //enableScrollEvent = gcnew enableScrollEventTyp(this,&CTlgContainerTreeViewForm::enableScroll);
      ItemStateList = gcnew ArrayList();
      SelItemColor=Color::FromKnownColor(KnownColor::MediumSlateBlue);
      SendItemColor=Color::FromKnownColor(KnownColor::Green);
      DefaultColor=Color::FromKnownColor(KnownColor::Control);
      RecFlag=false;
      NodeFillPathAfterSelect=nullptr;
      InitViewComponent();
    }
    CTlgContainerTreeViewForm(Panel^ parent)
    {
      InitializeComponent();
      this->TopLevel = false;
      this->Parent = parent;
      this->Dock = DockStyle::Fill;
      TlgContainer = nullptr;
      SelectEvent = nullptr;
      UpdateFlag=true;
      IsPrototypContainer=true;
      DataUpdate=nullptr;
      ItemViewChange=nullptr;
      MessageHandler=nullptr;
      scrollPositionUpdate=nullptr;
      //enableScrollEvent = gcnew enableScrollEventTyp(this,&CTlgContainerTreeViewForm::enableScroll);
      ItemStateList = gcnew ArrayList();
      SelItemColor=Color::FromKnownColor(KnownColor::MediumSlateBlue);
      SendItemColor=Color::FromKnownColor(KnownColor::Green);
      DefaultColor=Color::FromKnownColor(KnownColor::Control);
      RecFlag=false;
      NodeFillPathAfterSelect=nullptr;
      InitViewComponent();
    }
    //---------------------------------------------------------------------
    String^ getNodeFillPathAfterSelect();
    void setSelectEvent(AfterSelectEvent^ event);
    void setTlgContainer(CItemBaseContainerWrapper^ Contaier);
    void updateTlgView(int modi);
    int getTlgCount();
    CItemWrapper^ getClonedTlg(int index);
    CItemWrapper^ getClonedVirtualTlg(int index);
    int getVirtualTlgCount();
    double getTlgTime(int index);
    double getVirtualTlgTime(int index);
    void ShowContainer();
    void ShowFromScroll();
    void setAfterCollapsEvent(TreeViewEventHandler^ event);
    void setAfterExpandEvent(TreeViewEventHandler^ event);
    String^ getPathFile();
    void clearView();
    void updateContainerView(ArrayList^ liste);
    void resetContainer();
    void setPrototypMode(bool mode);
    int getItemViewCount();
    void setDataUpdateEvent(DataUpdateEvent^ datUp);
    void setItemViewChangeEvent(ItemViewChangeEvent^ itemChange);
    int calcViewIndexToContainerIndex(int index);
    int getItemHeigth();
    bool  setFilterRegExp(array <String^>^ reg);
    void selectTelegram(int index);
    void setMessageHandler(DelMessageHandlerTyp^ handMess);
    void setScrollUpdateEvent(ScrollPositionUpdateTyp^ event);
    int getNodeHeight(int index);
    int getTreeViewTop();
    int getTlgPosInContainer(int index);
    void setRecModus();
		value struct TreeNodeStateTyp
    {
      bool Expand;
      ArrayList^ ExpandListe;
    };
    void setUpdateFilterTextTyp(UpdateFilterTextTyp^ del);
  protected: 
    //void Dispose(Boolean disposing)
    //{
    //  if (disposing && components)
    //  {
    //    components->Dispose();
    //  }
    //  __super::Dispose(disposing);
    //}

  private: System::Windows::Forms::VScrollBar ^  vScrollBar1;
  private: System::Windows::Forms::TreeView ^  treeViewTlgCon;
         //private: simulator::m_TreeView^ treeViewTlgCon;

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
      this->vScrollBar1 = (gcnew System::Windows::Forms::VScrollBar());
      this->treeViewTlgCon = (gcnew System::Windows::Forms::TreeView());
      this->SuspendLayout();
      // 
      // vScrollBar1
      // 
      this->vScrollBar1->Dock = System::Windows::Forms::DockStyle::Right;
      this->vScrollBar1->LargeChange = 1;
      this->vScrollBar1->Location = System::Drawing::Point(280, 0);
      this->vScrollBar1->Minimum = 1;
      this->vScrollBar1->Name = L"vScrollBar1";
      this->vScrollBar1->Size = System::Drawing::Size(12, 273);
      this->vScrollBar1->TabIndex = 1;
      this->vScrollBar1->Value = 1;
      this->vScrollBar1->Visible = false;
      this->vScrollBar1->VisibleChanged += gcnew System::EventHandler(this, &CTlgContainerTreeViewForm::OnScrollVisibleChanged);
      this->vScrollBar1->ValueChanged += gcnew System::EventHandler(this, &CTlgContainerTreeViewForm::OnScrollBarValChange);
      // 
      // treeViewTlgCon
      // 
      this->treeViewTlgCon->HideSelection = false;
      this->treeViewTlgCon->Location = System::Drawing::Point(12, 12);
      this->treeViewTlgCon->Name = L"treeViewTlgCon";
      this->treeViewTlgCon->Scrollable = false;
      this->treeViewTlgCon->ShowPlusMinus = false;
      this->treeViewTlgCon->Size = System::Drawing::Size(243, 232);
      this->treeViewTlgCon->TabIndex = 2;
      this->treeViewTlgCon->AfterCollapse += gcnew System::Windows::Forms::TreeViewEventHandler(this, &CTlgContainerTreeViewForm::OnAfterCollapseTreeView);
      this->treeViewTlgCon->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &CTlgContainerTreeViewForm::OnAfterSelect);
      this->treeViewTlgCon->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &CTlgContainerTreeViewForm::OnKeyDownTreeView);
      // 
      // CTlgContainerTreeViewForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(292, 273);
      this->Controls->Add(this->vScrollBar1);
      this->Controls->Add(this->treeViewTlgCon);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
      this->Name = L"CTlgContainerTreeViewForm";
      this->ShowInTaskbar = false;
      this->Text = L"CTlgContainerTreeViewForm";
      this->Load += gcnew System::EventHandler(this, &CTlgContainerTreeViewForm::OnLoadForm);
      this->Resize += gcnew System::EventHandler(this, &CTlgContainerTreeViewForm::OnResizeForm);
      this->ResumeLayout(false);

    }    

    //Events
    System::Void OnAfterSelect(System::Object ^  sender, System::Windows::Forms::TreeViewEventArgs ^  e);
    System::Void OnBeforeExpandTreeView(System::Object ^  sender, System::Windows::Forms::TreeViewCancelEventArgs ^  e);
    System::Void OnAfterCollapseTreeView(System::Object ^  sender, System::Windows::Forms::TreeViewEventArgs ^  e);
    System::Void OnBeforeCollapsTreeView(System::Object ^  sender, System::Windows::Forms::TreeViewCancelEventArgs ^  e);
    //System::Void OnScrollBarScroll(System::Object ^  sender, System::Windows::Forms::ScrollEventArgs ^  e);
    System::Void OnScrollBarValChange(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnResizeForm(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnScrollVisibleChanged(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnLoadForm(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnKeyDownTreeView(System::Object ^  sender, System::Windows::Forms::KeyEventArgs ^  e);
    System::Void OnAddNodeToCyclicTable(System::Object ^  sender, System::EventArgs ^ e);
    System::Void MouseWheelHandler(System::Object ^  sender, System::Windows::Forms::MouseEventArgs^ e);
    System::Void OnPopupMenuClick(System::Object ^  sender, System::EventArgs ^  e);
    //Methods
    void InitViewComponent();
    String^ NodeFillPathAfterSelect;
    CItemBaseContainerWrapper^ TlgContainer;
    AfterSelectEvent^ SelectEvent;
    DelMessageHandlerTyp^ MessageHandler;
    enableScrollEventTyp^ enableScrollEvent;
    UpdateFilterTextTyp^ UpdateFilterTextDel;
    void getTreeNode(TreeNode^ node,CItemWrapper^ tlg);
    void getSubNode(TreeNode^ node,CItemWrapper^ tlg,int id);
    void getProtoTypTreeNode(TreeNode^ node,CItemWrapper^ tlg);
    void UpdateFilterText();
    void addNewNode();
    void scrolViewUpdate();
    void initTreeItemState();
    void initTreeViewItem(int count);
    int getIndexTlgInConFromTreeView(int index);
    void buildTreeViewNode(TreeNode^ node,CItemWrapper^ tlg);
    int setTreeViewNodeState(int node,int pos);
    int getCountCollapsedItems(TreeNode^ node);
    void setTreeViewPosition();
    int getUnderTelegramm(int& scroll);
    
    //Attributes
    System::Windows::Forms::TreeNode^ MyNode;
    bool UpdateFlag;
    int ItemsCount;
    int ItemsLow;
    bool IsPrototypContainer;
    DataUpdateEvent^ DataUpdate;
    ItemViewChangeEvent^ ItemViewChange;
    ScrollPositionUpdateTyp^ scrollPositionUpdate;
    ArrayList^ ItemStateList;
    Color SelItemColor;
    Color SendItemColor;
    Color DefaultColor;

    bool RecFlag;
    System::Windows::Forms::ContextMenu^ m_contextMenu;
    CItemWrapper^ selectedItem;
};
}