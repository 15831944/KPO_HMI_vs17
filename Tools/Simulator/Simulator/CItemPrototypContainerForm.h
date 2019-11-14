#pragma once

#include "CItemBaseContainerWrapper.h"
#include "CItemWrapper.h"
#include "CTlgElemWrapper.h"
#include "CTlgElemWrapper.h"
#include "CItemView.h"
#include "CTlgWrapper.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

//------------------------------------------------------

namespace simulator
{
	/// <summary> 
	/// Summary for CItemPrototypContainerForm
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CItemPrototypContainerForm : public System::Windows::Forms::Form
	{
	
  public: delegate void DelAddNodePrototypType(); 
  public: delegate void AfterSelectPrototypEvent(CItemWrapper^ wrp,CItemView::CreateTypForm typ);
  public: delegate void DelMessageHandlerPrototyp(String^ mess,int messTyp);
  //Analyzer Delegate
  public: delegate void DelAddToTable();
  public: delegate void DelAddToDiagram();
  public: delegate void DelRemoveFromDiagram();
  public: delegate void DelRemoveFromDataTable();
  public: 
		CItemPrototypContainerForm(Panel^ parent)
		{
			InitializeComponent();

      this->TopLevel = false;
      this->Parent = parent;
      this->Dock = DockStyle::Fill;
      SelectEvent = nullptr;
      UpdateFlag=true;
      NodeFillPathAfterSelect=nullptr;
      m_contextMenu=nullptr;
      this->addToTableEvent=nullptr;
      this->addToDiagramEvent=nullptr;
      this->removeFromDiagramEvent=nullptr;
      SelectedItem=nullptr;
      isReceiver = false;
		}

    CItemPrototypContainerForm()
		{
			InitializeComponent();

      this->TopLevel = false;
      this->Dock = DockStyle::Fill;
      SelectEvent = nullptr;
      UpdateFlag=true;
      NodeFillPathAfterSelect=nullptr;
      m_contextMenu=nullptr;
      this->addToTableEvent=nullptr;
      this->addToDiagramEvent=nullptr;
      SelectedItem=nullptr;
      isReceiver = false;
		}

     void showContainer();
     void clearView();
     void resetContainer();
     void updateContainerView(ArrayList^ liste);
     void setIsReceiver ();
     void setPrototypContainer (CItemBaseContainerWrapper^ itemCon);
     void setMessageHandler(DelMessageHandlerPrototyp^ handMess);
     void setSelectEvent(AfterSelectPrototypEvent^ event);
     void setAddToTableEvent(DelAddToTable^ event);
     void setAddToDiagramEvent(DelAddToDiagram^ event);
     void setRemoveFromDiagramEvent(DelRemoveFromDiagram^ event);
     void setRemoveFromDataTableEvent(DelRemoveFromDataTable^ event);
     void updateTlgView(int modi);
     int getTlgCount();
     void getTreeNode(TreeNode^ node,CItemWrapper^ tlg);
     void addNewNode();
     void getSubNode(TreeNode^ node,CItemWrapper^ tlg,int id);
     String^ getPathFile();
     CItemWrapper^ getClonedTlg(int index);
     String^ getNodeFillPathAfterSelect();
     ArrayList^ getIndexListAfterSelect();
     Windows::Forms::TreeNode^ buildElemNodes (CTlgElemWrapper^ elem,const int i);
     void setContextMenuActiv();   
		 void setCyclicContextMenuActiv();
     void setKontextMenuVisible(bool view);

	protected: 
		//void Dispose(Boolean disposing)
  //  {
		//	if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}
  private: 
    System::Windows::Forms::TreeView ^  treeViewPrototypCon;

	private:
    /// <summary>
		/// Required designer variable.
		/// </summary>
    System::Windows::Forms::ContextMenu^ m_contextMenu;
 

  private: System::ComponentModel::IContainer^  components;

    System::Void OnAfterSelect(System::Object ^  sender, System::Windows::Forms::TreeViewEventArgs ^  e);
    System::Void OnAddToTable(System::Object ^  sender, System::EventArgs ^ e);
    System::Void OnAddToDiagram(System::Object ^  sender, System::EventArgs ^ e);
    System::Void CItemPrototypContainerForm::OnRemoveFromDiagram(System::Object ^  sender, System::EventArgs ^ e);
    System::Void CItemPrototypContainerForm::OnRemoveFromDataTable(System::Object ^  sender, System::EventArgs ^ e);
    System::Void OnBeforeSelect(System::Object^  sender, System::Windows::Forms::TreeViewCancelEventArgs^  e);
    System::Void OnAddNodeToCyclicTable(System::Object ^  sender, System::EventArgs ^ e);
    System::Void treeViewPrototypCon_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e);
    System::Void treeViewPrototypCon_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
    System::Void OnPopupMenuClick(System::Object ^  sender, System::EventArgs ^  e);
    /// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      this->treeViewPrototypCon = (gcnew System::Windows::Forms::TreeView());
      this->SuspendLayout();
      // 
      // treeViewPrototypCon
      // 
      this->treeViewPrototypCon->Dock = System::Windows::Forms::DockStyle::Fill;
      this->treeViewPrototypCon->HideSelection = false;
      this->treeViewPrototypCon->Location = System::Drawing::Point(0, 0);
      this->treeViewPrototypCon->Name = "treeViewPrototypCon";
      this->treeViewPrototypCon->Size = System::Drawing::Size(292, 273);
      this->treeViewPrototypCon->TabIndex = 0;
      this->treeViewPrototypCon->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &CItemPrototypContainerForm::treeViewPrototypCon_AfterSelect);
      this->treeViewPrototypCon->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &CItemPrototypContainerForm::treeViewPrototypCon_MouseDown);
      // 
      // CItemPrototypContainerForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(292, 273);
      this->Controls->Add(this->treeViewPrototypCon);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
      this->Name = "CItemPrototypContainerForm";
      this->Text = "CItemPrototypContainerForm";
      this->ResumeLayout(false);

    }		
    
    ArrayList^ NodeIndexList;
    String^ BuildPathAfterSelect(TreeNode^ node);
    void BuildPathAfterSelect(TreeNode^ node,ArrayList^ IndexList);

    CItemBaseContainerWrapper^ PrototypCon;
    System::Windows::Forms::TreeNode^ MyNode;
    
    String^ NodeFillPathAfterSelect;
    bool UpdateFlag;
    CItemWrapper^ SelectedItem;
    bool isReceiver;

    AfterSelectPrototypEvent^ SelectEvent;
    DelMessageHandlerPrototyp^ MessageHandler;
    DelAddToTable^ addToTableEvent;
    DelAddToDiagram^ addToDiagramEvent;  

    DelRemoveFromDiagram^ removeFromDiagramEvent;
    DelRemoveFromDataTable^ removeFromDataTableEvent;
};
}