#include "StdAfx.h"
#include "CItemPrototypContainerForm.h"
#include "CItemWrapper.h"
#include "CTlgWrapper.h"
#include "CTlgElemWrapper.h"
#include "CTlgElem.h"
#include "CCyclicItemContainer.h"
#include "CCyclicTlgForm.h"
#include "CLogWriterWrapper.h"

using namespace simulator;
//-------------------------------------------------------
void CItemPrototypContainerForm::setIsReceiver ()
{
  isReceiver=true;
}
//-------------------------------------------------------
void CItemPrototypContainerForm::setKontextMenuVisible(bool view)
{
	for (int i=0;i<m_contextMenu->MenuItems->Count;i++)
	{
		m_contextMenu->MenuItems[i]->Enabled = view;
	}
}
//-------------------------------------------------------
System::Void CItemPrototypContainerForm::treeViewPrototypCon_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
{
  TreeNode^ node = nullptr;
  node = treeViewPrototypCon->GetNodeAt(e->X,e->Y);
  if (node)
    this->treeViewPrototypCon->SelectedNode = node;
}
//-------------------------------------------------------
System::Void CItemPrototypContainerForm::treeViewPrototypCon_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e)
{  
  if(UpdateFlag)
  {
	  int index;
	  CItemWrapper^ wr=nullptr;
	  TreeNode^ node = e->Node;
    TreeNode^ rootNode = nullptr;
	  
    if(node->Parent == nullptr)
	  {
		  rootNode = node;
      
	  }
    // emal
    if(node->Parent)
    {
      //NodeFillPathAfterSelect=node->get_FullPath();
      NodeFillPathAfterSelect=BuildPathAfterSelect(node); 
      NodeIndexList = gcnew ArrayList();
      BuildPathAfterSelect(node,NodeIndexList);
      SelectedItem=nullptr;
    }
    if (rootNode)
    {
      wr = gcnew CTlgWrapper();
		  index=node->Index;
      index= System::Convert::ToInt32(node->Tag);   //getIndexTlgInConFromTreeView(index);   
      PrototypCon->getClonedVirtualTlg(wr,index);
		  PrototypCon->setSelectedItem(index);
		  SelectedItem=wr;
      NodeFillPathAfterSelect="0";
      if(SelectEvent)
      {
        if (isReceiver)
        {
          SelectEvent->Invoke(wr,CItemView::CreateTypForm::Receiver);
        }
        else
        {
          SelectEvent->Invoke(wr,CItemView::CreateTypForm::Prototyp);
        }
      }
    }
  }
}
//-------------------------------------------------------
void CItemPrototypContainerForm::BuildPathAfterSelect(TreeNode^ node,ArrayList^ IndexList)
{
  if (node->Parent != nullptr)
    BuildPathAfterSelect (node->Parent,IndexList);
  IndexList->Add(node->Tag);
}
//-------------------------------------------------------
String^ CItemPrototypContainerForm::BuildPathAfterSelect(TreeNode^ node)
{
  if (node->Parent == nullptr)
    return node->Text;
  else
    return String::Concat(BuildPathAfterSelect(node->Parent),"\\",node->Text);
}
//-------------------------------------------------------
void CItemPrototypContainerForm::setContextMenuActiv()
{
  m_contextMenu = gcnew System::Windows::Forms::ContextMenu();
  m_contextMenu->MenuItems->Add(gcnew System::Windows::Forms::MenuItem("Add to table", gcnew EventHandler(this,&CItemPrototypContainerForm::OnAddToTable)));
	m_contextMenu->MenuItems->Add(gcnew System::Windows::Forms::MenuItem("Add to diagram", gcnew EventHandler(this,&CItemPrototypContainerForm::OnAddToDiagram)));
  m_contextMenu->MenuItems->Add(gcnew System::Windows::Forms::MenuItem("Remove from diagram", gcnew EventHandler(this,&CItemPrototypContainerForm::OnRemoveFromDiagram)));
  m_contextMenu->MenuItems->Add(gcnew System::Windows::Forms::MenuItem("Remove from table", gcnew EventHandler(this,&CItemPrototypContainerForm::OnRemoveFromDataTable)));
  ContextMenu = m_contextMenu;
}
//-------------------------------------------------------
void CItemPrototypContainerForm::setCyclicContextMenuActiv()
{
  m_contextMenu = gcnew System::Windows::Forms::ContextMenu();
  m_contextMenu->MenuItems->Add(gcnew System::Windows::Forms::MenuItem("Add to cyclic", gcnew EventHandler(this,&CItemPrototypContainerForm::OnAddNodeToCyclicTable)));
  m_contextMenu->Popup += gcnew System::EventHandler(this, &CItemPrototypContainerForm::OnPopupMenuClick);
  ContextMenu = m_contextMenu;
}
//-------------------------------------------------------
System::Void CItemPrototypContainerForm::OnPopupMenuClick(System::Object ^  sender, System::EventArgs ^  e)
{
  if (SelectedItem)
  {
    CCyclicItemContainer^ cyclic = CCyclicItemContainer::getCyclicItemContainer();
    if (!cyclic->isItemInContainer(SelectedItem))
      ContextMenu->MenuItems[0]->Text = "Add To Cyclic Container";
    else
      ContextMenu->MenuItems[0]->Text = "Remove From Cyclic Container";
  }
  else
    ContextMenu->MenuItems[0]->Text = "";
}
//-------------------------------------------------------
System::Void CItemPrototypContainerForm::OnAddToTable(System::Object ^  sender, System::EventArgs ^ e)
{
  if (addToTableEvent)
  {
    //Bevor Kontextmenu kommt, Node selektieren
    //OnBeforeSelect(sender,e);
    addToTableEvent->Invoke();
  }
}
//-------------------------------------------------------
System::Void CItemPrototypContainerForm::OnAddToDiagram(System::Object ^  sender, System::EventArgs ^ e)
{
  if (addToDiagramEvent)
  {
    //Bevor Kontextmenu kommt, Node selektieren
    //OnBeforeSelect(sender,e);
    addToDiagramEvent->Invoke();
  }
}
//-------------------------------------------------------
System::Void CItemPrototypContainerForm::OnRemoveFromDataTable(System::Object ^  sender, System::EventArgs ^ e)
{
  if (removeFromDataTableEvent)
  {
    removeFromDataTableEvent->Invoke();
  }
}
//-------------------------------------------------------
System::Void CItemPrototypContainerForm::OnRemoveFromDiagram(System::Object ^  sender, System::EventArgs ^ e)
{
  if (removeFromDiagramEvent)
  {
    //Bevor Kontextmenu kommt, Node selektieren
    //OnBeforeSelect(sender,e);
    removeFromDiagramEvent->Invoke();
  }
}
//-------------------------------------------------------
void CItemPrototypContainerForm::setPrototypContainer (CItemBaseContainerWrapper^ itemCon)
{
  PrototypCon = itemCon;
}
//-------------------------------------------------------
void CItemPrototypContainerForm::showContainer()
{
  int count = PrototypCon->getVirtualTlgCount();
  int itemCount = 0;
  System::Windows::Forms::TreeNode^ node = nullptr;
  
  clearView();
  
  UpdateFlag = false;
	treeViewPrototypCon->BeginUpdate();

  for (int i=1;i<=count;i++)
  {
    CItemWrapper^ item = gcnew CTlgWrapper();
    PrototypCon->getClonedVirtualTlg(item,i);
    
    node = gcnew System::Windows::Forms::TreeNode(); 
    node->Text = System::String::Concat(item->getName()," ",item->getTlgDescr());
    node->Tag = (i);
    //Elemente 
    itemCount = item->getTlgElemCount();
    for (int j=1;j<=itemCount;j++)
    {
      CTlgElemWrapper^ elem = gcnew CTlgElemWrapper();
      elem->setTlgElem(item->getElem(j)); 
      node->Nodes->Add(buildElemNodes (elem,j));
    }
    treeViewPrototypCon->Nodes->Add(node);
  }

  treeViewPrototypCon->EndUpdate();
  UpdateFlag = true;
  //Erste Node selektieren
  if (treeViewPrototypCon->Nodes->Count>0)
  {
    treeViewPrototypCon->Focus();
    treeViewPrototypCon->SelectedNode = treeViewPrototypCon->Nodes[0];
    treeViewPrototypCon->Focus();
  }
}
//-------------------------------------------------------
System::Windows::Forms::TreeNode^ CItemPrototypContainerForm::buildElemNodes (CTlgElemWrapper^ elem,const int i)
{
  System::Windows::Forms::TreeNode^ subElemNodeRet = gcnew System::Windows::Forms::TreeNode();
  String^ name = elem->getElemName();
  int elemCount = elem->getSubElemCount(); 
  
  subElemNodeRet->Text = (elem->getElemName());
  subElemNodeRet->Tag = (i);
  
  if (elemCount>0)
  {
    for (int j=1;j<=elemCount;j++)
    {
      CTlgElemWrapper^ elemSub = gcnew CTlgElemWrapper();
      elemSub->setTlgElem(elem->getSubElem(j));
      //Rekursive Aufruf
      subElemNodeRet->Nodes->Add(buildElemNodes(elemSub,j));
    }
  }
 return subElemNodeRet; 
}
//-------------------------------------------------------
void CItemPrototypContainerForm::setSelectEvent(AfterSelectPrototypEvent^ event)
{
  SelectEvent = event;
}
//-------------------------------------------------------
void CItemPrototypContainerForm::setAddToTableEvent(DelAddToTable^ event)
{
  addToTableEvent = event;
}
//-------------------------------------------------------
void CItemPrototypContainerForm::setAddToDiagramEvent(DelAddToDiagram^ event)
{
  addToDiagramEvent = event;
}
//-------------------------------------------------------
void CItemPrototypContainerForm::setRemoveFromDataTableEvent(DelRemoveFromDataTable^ event)
{
  removeFromDataTableEvent = event;
}
//-------------------------------------------------------------------------------
void CItemPrototypContainerForm::setRemoveFromDiagramEvent(DelRemoveFromDiagram^ event)
{
  removeFromDiagramEvent = event;
}
//-------------------------------------------------------------------------------
String^ CItemPrototypContainerForm::getNodeFillPathAfterSelect()
{
  return NodeFillPathAfterSelect;
}
//------------------------------------------------------------------------------
ArrayList^ CItemPrototypContainerForm::getIndexListAfterSelect()
{
  return NodeIndexList;
}
//------------------------------------------------------------------------------
System::Void CItemPrototypContainerForm::OnBeforeSelect(System::Object^  sender, System::Windows::Forms::TreeViewCancelEventArgs^  e) 
{
  if(UpdateFlag)
	{
		int index;
		CItemWrapper^ wr=nullptr;
		TreeNode^ node = e->Node;

		if(node->Parent == nullptr)
		{
			wr = gcnew CTlgWrapper();
			index=node->Index;
      index= System::Convert::ToInt32(node->Tag);   //getIndexTlgInConFromTreeView(index);   
      PrototypCon->getClonedVirtualTlg(wr,index);
			PrototypCon->setSelectedItem(index);
			SelectedItem=wr;
      NodeFillPathAfterSelect="0";
      if(SelectEvent)
				SelectEvent->Invoke(wr,CItemView::CreateTypForm::Prototyp);
		}
    // emal
    if(node->Parent)
    {
      NodeFillPathAfterSelect=node->FullPath;
      SelectedItem=nullptr;
    }
  }         
}

//------------------------------------------------------------------------------
System::Void CItemPrototypContainerForm::OnAfterSelect(System::Object ^  sender, System::Windows::Forms::TreeViewEventArgs ^  e)
{
	//if(UpdateFlag)
	//{
	//	int index;
	//	CItemWrapper^ wr=0;
	//	TreeNode^ node = e->get_Node();

	//	if(node->get_Parent() == 0)
	//	{
	//		wr = gcnew CTlgWrapper();
	//		index=node->get_Index();
 //     index= System::Convert::ToInt32(node->Tag);   //getIndexTlgInConFromTreeView(index);   
 //     PrototypCon->getClonedVirtualTlg(wr,index);
	//		PrototypCon->setSelectedItem(index);
	//		SelectedItem=wr;
 //     NodeFillPathAfterSelect="0";
 //     if(SelectEvent)
	//			SelectEvent->Invoke(wr);
	//	}
 //   // emal
 //   if(node->get_Parent())
 //   {
 //     NodeFillPathAfterSelect=node->get_FullPath();
 //     SelectedItem=0;
 //   }
 // }
}

//-------------------------------------------------------------------------------
void CItemPrototypContainerForm::clearView()
{
  UpdateFlag = false;
	treeViewPrototypCon->BeginUpdate();
	treeViewPrototypCon->Nodes->Clear();
  treeViewPrototypCon->Refresh();
	treeViewPrototypCon->EndUpdate();
  UpdateFlag = true;
}

//--------------------------------------------------------------------------------
int CItemPrototypContainerForm::getTlgCount()
{
	if(PrototypCon)
		return PrototypCon->getVirtualTlgCount();
	else
		return 0;
}
//-------------------------------------------------------------------------------
CItemWrapper^ CItemPrototypContainerForm::getClonedTlg(int index)
{
	CItemWrapper^ wrTlg = gcnew CTlgWrapper();
	PrototypCon->getClonedTlg(wrTlg,index);
	return wrTlg;
}

//-------------------------------------------------------------------------------
String^ CItemPrototypContainerForm::getPathFile()
{
	if(PrototypCon)
		return PrototypCon->getPathFile();
	else
		return "";
}
//-------------------------------------------------------------------------------
void CItemPrototypContainerForm::resetContainer()
{
    PrototypCon->reset();
    /*if(DataUpdate != 0)
       DataUpdate->Invoke();*/
}
//-------------------------------------------------------------------------------
void CItemPrototypContainerForm::updateContainerView(ArrayList^ liste)
{
    PrototypCon->setFilterByTelName(liste);
    /*if(DataUpdate != 0)
       DataUpdate->Invoke();*/
}
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
void CItemPrototypContainerForm::setMessageHandler(DelMessageHandlerPrototyp^ handMess)
{
	MessageHandler=handMess;
}
//-------------------------------------------------------------------------------
void CItemPrototypContainerForm::updateTlgView(int modi)
{
 int countConTlg;
 int countTreeTlg;
 String^ name=nullptr;
 String^ time=nullptr;
 String^ descr=nullptr;

 countConTlg=PrototypCon->getVirtualTlgCount();
 countTreeTlg=treeViewPrototypCon->Nodes->Count;
 if(countConTlg > countTreeTlg)
 {
   DelAddNodePrototypType^ delAddNode = gcnew DelAddNodePrototypType(this,&CItemPrototypContainerForm::addNewNode);
   treeViewPrototypCon->BeginUpdate();
   TreeNode^ node=nullptr;
   CItemWrapper^ Tlg = gcnew CTlgWrapper();
   for(int i = countTreeTlg; i<countConTlg;i++)
   {
    node = gcnew System::Windows::Forms::TreeNode();
    PrototypCon->getClonedVirtualTlg(Tlg,i+1);
    name=Tlg->getName();
    node->Text = name;
	  if(modi == 1)
	  {
		  time = PrototypCon->getTlgTimeAsString(i+1);
		  node->Text = String::Concat(node->Text," (",time,")");
	  }
	  getTreeNode(node,Tlg);
    node->Tag = (i+1);
	  MyNode = node;
	  treeViewPrototypCon->Invoke(delAddNode);
  }
  treeViewPrototypCon->EndUpdate();
 //Invoke(enableScrollEvent);
 }
}
//-------------------------------------------------------------------------------
void CItemPrototypContainerForm::getTreeNode(TreeNode^ node,CItemWrapper^ tlg)
{
	 String^ val1 = nullptr;
	 //String^ val2 = nullptr;
	 int count,i;

	 //val1=tlg->getName();
	 //val2=tlg->getTlgDescr();
	 //node->Text = String::Concat(val1,"  (",val2,")");

	 count = tlg->getTlgElemCount();
	 for(i=1;i<=count;i++)
	 {
		 TreeNode^ node1 = gcnew TreeNode();
			 val1 = tlg->getElemName(i);
		 node1->Text = val1;
			 getSubNode(node1,tlg,i);
		 node->Nodes->Add(node1);
	 }
}
//-------------------------------------------------------------------------------
void CItemPrototypContainerForm::addNewNode()
{
  treeViewPrototypCon->Nodes->Add(MyNode);
}
//-------------------------------------------------------------------------------
void CItemPrototypContainerForm::getSubNode(TreeNode^ node,CItemWrapper^ tlg,int id)
{
  int count,i;
  String^ val = nullptr;
  String^ val1 = nullptr;

  count = tlg->getSubElemCount(id);
  if(count == 0)
  {
    val = tlg->getElemValue(id);
    node->Text = String::Concat(node->Text,"   ",val);
  }
  else
  {
    TreeNode^ node1=nullptr;
    for(i=1;i<=count;i++)
    {
      node1 = gcnew TreeNode();
      val = tlg->getSubElemName(id,i);
      val1 = tlg->getSubElemValue(id,i);
      node1->Text = String::Concat(val,"  ",val1);
      node->Nodes->Add(node1);
    }
  }
}
//------------------------------------------------------------------------------
System::Void CItemPrototypContainerForm::OnAddNodeToCyclicTable(System::Object ^  sender, System::EventArgs ^ e)
{
  CCyclicItemContainer^ cyclic = CCyclicItemContainer::getCyclicItemContainer();

  if (SelectedItem)
  {
    if (!cyclic->isItemInContainer(SelectedItem))
      cyclic->addItemToContainer(SelectedItem->getInterfece(),SelectedItem,true);
    else
      cyclic->removeItem(SelectedItem);
  }
  else if (MessageHandler)
  {
    String^ mess="The selected node is a element of telegram.";
    MessageHandler->Invoke(mess,1);
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage((CLogWriterWrapper::MessTyp) 1,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  }

  //CCyclicTlgForm^ cyclicForm = gcnew CCyclicTlgForm();
  //cyclicForm->ShowDialog();
}