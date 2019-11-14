#include "StdAfx.h"
#include "CTlgContainerTreeViewForm.h"
#include "CStdConverter.h"
#include "CTlgWrapper.h"
#include "CCyclicItemContainer.h"
#include "CCyclicTlgForm.h"

//-----------------------------------------------------------------------------
using namespace simulator;
//------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::InitViewComponent()
{
  this->DoubleBuffered = true;
  selectedItem=nullptr;
  m_contextMenu = gcnew System::Windows::Forms::ContextMenu();
  m_contextMenu->MenuItems->Add(gcnew System::Windows::Forms::MenuItem("Add to cyclic", gcnew EventHandler(this,&CTlgContainerTreeViewForm::OnAddNodeToCyclicTable)));
  this->ContextMenu = m_contextMenu; 
  ContextMenu->Popup += gcnew System::EventHandler(this, &CTlgContainerTreeViewForm::OnPopupMenuClick);
  this->treeViewTlgCon->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this,&CTlgContainerTreeViewForm::MouseWheelHandler);  
  this->UpdateFilterTextDel = nullptr;
}
//-------------------------------------------------------
System::Void CTlgContainerTreeViewForm::OnPopupMenuClick(System::Object ^  sender, System::EventArgs ^  e)
{  
  if (selectedItem)
  {
    CCyclicItemContainer^ cyclic = CCyclicItemContainer::getCyclicItemContainer();
    if (!cyclic->isItemInContainer(selectedItem))
      ContextMenu->MenuItems[0]->Text = "Add To Cyclic Container";
    else
      ContextMenu->MenuItems[0]->Text = "Remove From Cyclic Container";
  }
  else
    ContextMenu->MenuItems[0]->Text = "";
}
//------------------------------------------------------------------------------
System::Void CTlgContainerTreeViewForm::MouseWheelHandler(System::Object ^  sender, System::Windows::Forms::MouseEventArgs^ e)
{  
  int step = int(treeViewTlgCon->Nodes->Count*0.1);
  if (step <= 0)
    step=1;

  //Up
  if (e->Delta > 0)
  {
    this->treeViewTlgCon->BeginUpdate();
    if ((vScrollBar1->Value) != vScrollBar1->Minimum)
    {
      if((vScrollBar1->Value - step) > vScrollBar1->Minimum)
        vScrollBar1->Value=vScrollBar1->Value-step;
      else
        vScrollBar1->Value=vScrollBar1->Minimum;
      ShowFromScroll();
    }
    this->treeViewTlgCon->EndUpdate();
  }
  //Down
  if (e->Delta < 0)
  {
    this->treeViewTlgCon->BeginUpdate();
    if((vScrollBar1->Value) != vScrollBar1->Maximum)
    {
      if((vScrollBar1->Value + step) < vScrollBar1->Maximum)
        vScrollBar1->Value=vScrollBar1->Value+step;
      else
        vScrollBar1->Value=vScrollBar1->Maximum;
      ShowFromScroll();
    }
    this->treeViewTlgCon->EndUpdate();
  }    
} 
//------------------------------------------------------------------------------
System::Void CTlgContainerTreeViewForm::OnAddNodeToCyclicTable(System::Object ^  sender, System::EventArgs ^ e)
{  
  if (selectedItem)
  {
    CCyclicItemContainer^ cyclic = CCyclicItemContainer::getCyclicItemContainer();
    if (!cyclic->isItemInContainer(selectedItem))
      cyclic->addItemToContainer(selectedItem->getInterfece(),selectedItem,false);
    else
      cyclic->removeItem(selectedItem);
    //CCyclicTlgForm^ cyclicForm = gcnew CCyclicTlgForm();
    //cyclicForm->ShowDialog();
  }
}
//------------------------------------------------------------------------------
System::Void CTlgContainerTreeViewForm::OnAfterSelect(System::Object ^  sender, System::Windows::Forms::TreeViewEventArgs ^  e)
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
      TlgContainer->getClonedVirtualTlg(wr,index);
			TlgContainer->setSelectedItem(index);
			if(SelectEvent)
				SelectEvent->Invoke(wr,CItemView::CreateTypForm::LogFile); 
      this->NodeFillPathAfterSelect="0";
      selectedItem=wr;
		}
    // emal
    if(node->Parent)
    {
      this->NodeFillPathAfterSelect=node->FullPath;
      selectedItem=nullptr;
    }
  }
}
//------------------------------------------------------------------------------
System::Void CTlgContainerTreeViewForm::OnScrollBarValChange(System::Object ^  sender, System::EventArgs ^  e)
{
  UpdateFlag=false;
  //---test
  //MessageHandler->Invoke("Aufruf",1);
	ShowFromScroll();
	UpdateFlag=true;
}
//------------------------------------------------------------------------------
System::Void CTlgContainerTreeViewForm::OnBeforeExpandTreeView(System::Object ^  sender, System::Windows::Forms::TreeViewCancelEventArgs ^  e)
{
  if((UpdateFlag)&&(!RecFlag))
  {
    int index;
    int offScr=0;
    int count,i;
    CItemWrapper^ wr=nullptr;
    TreeNode^ node = e->Node;
    TreeNode^ parent=node->Parent;
    if(parent == nullptr)
    {
      index = System::Convert::ToInt32(node->Tag);
	    //index=node->get_Index();
	    //index=getIndexTlgInConFromTreeView(index);
	    wr=gcnew CTlgWrapper();
	    TlgContainer->getClonedVirtualTlg(wr,index);
      //-------test
      //MessageHandler->Invoke(String::Concat("BefExp: ",wr->getName()),0);
      //-------------------------------
	    buildTreeViewNode(node,wr);
	    offScr=node->Nodes->Count;
	    value struct TreeNodeStateTyp^ stateNode = safe_cast<value struct TreeNodeStateTyp^>(ItemStateList[index-1]);
	    stateNode->Expand=true;
	    count = stateNode->ExpandListe->Count;
	    for(i=0;i<count;i++)
	    {
		    index = System::Convert::ToInt32(stateNode->ExpandListe[i]);
		    node->Nodes[index]->Expand();
		    //offScr=offScr+node->Nodes[index)->Nodes->Count;
	    }
    }
    else
    {
      index=System::Convert::ToInt32(parent->Tag);
	    //index=parent->get_Index();
	    //index=getIndexTlgInConFromTreeView(index);
	    offScr=node->Nodes->Count;
	    value struct TreeNodeStateTyp^ stateNode = safe_cast<value struct TreeNodeStateTyp^>(ItemStateList[index-1]);
	    index=node->Index;
	    if(stateNode->ExpandListe->IndexOf((index)) == -1)
		  stateNode->ExpandListe->Add((index));
    }
    if(vScrollBar1->Visible)
    {
	    vScrollBar1->Maximum = (vScrollBar1->Maximum+offScr);
	    //--test
	    //MessageHandler->Invoke(System::Convert::ToString(vScrollBar1->Maximum),0);
    }
  }
}
//------------------------------------------------------------------------------
System::Void CTlgContainerTreeViewForm::OnAfterCollapseTreeView(System::Object ^  sender, System::Windows::Forms::TreeViewEventArgs ^  e)
{
  if((UpdateFlag)&&(!RecFlag))
  {
    int newMax;
    int offScr=0;
   
    TreeNode^ node=e->Node;
    offScr=getCountCollapsedItems(node);
    //MessageHandler->Invoke(System::Convert::ToString(offScr),2);
    if(vScrollBar1->Visible)
    {
      newMax=vScrollBar1->Maximum-offScr;
      // if(vScrollBar1->Value > vScrollBar1->Maximum-offScr)
      //   vScrollBar1->Value=vScrollBar1->Maximum-offScr;
	    //vScrollBar1->set_Maximum(vScrollBar1->Maximum-offScr);
	    //---test
	    //MessageHandler->Invoke(System::Convert::ToString(vScrollBar1->Maximum),0);
    }
    int index;
    // TreeNode^ node = e->get_Node();
    TreeNode^ parent=node->Parent;
    if(parent == nullptr)
    {
	    node->Nodes->Clear();
	    //node->Nodes->Add("dummy");
          index = System::Convert::ToInt32(node->Tag);
	    //index=node->get_Index();
	    //index=getIndexTlgInConFromTreeView(index);
	    value struct TreeNodeStateTyp^ stateNode = safe_cast<value struct TreeNodeStateTyp^>(ItemStateList[index-1]);
	    stateNode->Expand=false;
    }
    else
    {
      index = System::Convert::ToInt32(parent->Tag);
	    //index=parent->get_Index();
	    //index=getIndexTlgInConFromTreeView(index);
	    value struct TreeNodeStateTyp^ stateNode = safe_cast<value struct TreeNodeStateTyp^>(ItemStateList[index-1]);
	    index = node->Index;
	    stateNode->ExpandListe->Remove(index);
    }

    if(vScrollBar1->Visible)
    {
      //newMax=vScrollBar1->Maximum-offScr;
      if(vScrollBar1->Value > newMax)
        vScrollBar1->Value=newMax;
	    vScrollBar1->Maximum = newMax;
	    //---test
	    //MessageHandler->Invoke(System::Convert::ToString(vScrollBar1->Maximum),0);
    }
  }
}
//------------------------------------------------------------------------------
System::Void CTlgContainerTreeViewForm::OnBeforeCollapsTreeView(System::Object ^  sender, System::Windows::Forms::TreeViewCancelEventArgs ^  e)
{
  if((UpdateFlag) && (!RecFlag))
  {
  /*  int offScr=0;
      UpdateFlag=false;
    TreeNode* node=e->get_Node();
    offScr=getCountCollapsedItems(node);
    //MessageHandler->Invoke(System::Convert::ToString(offScr),2);
    if(vScrollBar1->Visible)
    {
          if(vScrollBar1->Value > vScrollBar1->Maximum-offScr)
              vScrollBar1->Value=vScrollBar1->Maximum-offScr;
	    vScrollBar1->set_Maximum(vScrollBar1->Maximum-offScr);
	    //---test
	    //MessageHandler->Invoke(System::Convert::ToString(vScrollBar1->Maximum),0);
    }
      UpdateFlag=true;*/
  }
}
//------------------------------------------------------------------------------
System::Void CTlgContainerTreeViewForm::OnKeyDownTreeView(System::Object ^  sender, System::Windows::Forms::KeyEventArgs ^  e)
{
  int selItem;
  //int selTel;
  int count;
  if(vScrollBar1->Visible)
  {
    System::Windows::Forms::Keys key = e->KeyCode;
     
    if(key == System::Windows::Forms::Keys::Down || key == System::Windows::Forms::Keys::Up
      || key == System::Windows::Forms::Keys::PageDown || key == System::Windows::Forms::Keys::PageUp)
    {
      if(treeViewTlgCon->SelectedNode && treeViewTlgCon->SelectedNode->Parent == nullptr)
      {
        selItem=treeViewTlgCon->SelectedNode->Index;
        count=treeViewTlgCon->Nodes->Count;
        
        //Down
        if((count == selItem+1) && (key == System::Windows::Forms::Keys::Down))
        {
          if(vScrollBar1->Value != vScrollBar1->Maximum)
          {
              vScrollBar1->Value++;
              ShowFromScroll();
          }
        }//Up
        else if (key == System::Windows::Forms::Keys::Up)
        {
          if((selItem == 0) && (key == System::Windows::Forms::Keys::Up))
          {
            if(vScrollBar1->Value != 1)
            {
              vScrollBar1->Value--;
              ShowFromScroll();
            }
          }
        }//PageDown
        else if (key == System::Windows::Forms::Keys::PageDown && vScrollBar1->Value!=vScrollBar1->Maximum)
        { 
          if((vScrollBar1->Value + treeViewTlgCon->Nodes->Count) < vScrollBar1->Maximum)
            vScrollBar1->Value += treeViewTlgCon->Nodes->Count;
          else
            vScrollBar1->Value = vScrollBar1->Maximum;
          
          ShowFromScroll();
        }//PageUp
        else if (key == System::Windows::Forms::Keys::PageUp && vScrollBar1->Value!=vScrollBar1->Minimum)
        {
          if((vScrollBar1->Value - treeViewTlgCon->Nodes->Count) > vScrollBar1->Minimum)
            vScrollBar1->Value=vScrollBar1->Value-treeViewTlgCon->Nodes->Count;
          else
            vScrollBar1->Value = vScrollBar1->Minimum;

          ShowFromScroll();
        }
      }
    }
  }
}
//------------------------------------------------------------------------------
System::Void CTlgContainerTreeViewForm::OnResizeForm(System::Object ^  sender, System::EventArgs ^  e)
{
	setTreeViewPosition();
  scrolViewUpdate();
}
//------------------------------------------------------------------------------
System::Void CTlgContainerTreeViewForm::OnLoadForm(System::Object ^  sender, System::EventArgs ^  e)
{
	setTreeViewPosition();
}
//------------------------------------------------------------------------------
System::Void CTlgContainerTreeViewForm::OnScrollVisibleChanged(System::Object ^  sender, System::EventArgs ^  e)
{
	setTreeViewPosition();
}
//------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::setTlgContainer(CItemBaseContainerWrapper^ Container)
{
  TlgContainer = Container;
	initTreeItemState();
}
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::updateTlgView(int modi)
{
   int countConTlg;
   int countTreeTlg;
   String^ name=nullptr;
   String^ time=nullptr;
   String^ descr=nullptr;
  
   countConTlg=TlgContainer->getVirtualTlgCount();
   countTreeTlg=treeViewTlgCon->Nodes->Count;
   if(countConTlg > countTreeTlg)
   {
     DelAddNodeType^ delAddNode = gcnew DelAddNodeType(this,&CTlgContainerTreeViewForm::addNewNode);
     treeViewTlgCon->BeginUpdate();
     TreeNode^ node=nullptr;
     CTlgWrapper^ Tlg = gcnew CTlgWrapper();
     for(int i = countTreeTlg; i<countConTlg;i++)
     {
		  node = gcnew System::Windows::Forms::TreeNode();
		  TlgContainer->getClonedVirtualTlg(Tlg,i+1);
		  name=Tlg->getName();
		  node->Text = name;
		  if(modi == 1)
		  {
			  time = TlgContainer->getTlgTimeAsString(i+1);
			  node->Text = String::Concat(node->Text," (",time,")");
		  }
		  getTreeNode(node,Tlg);
      node->Tag = i+1;
		  MyNode = node; 
		  treeViewTlgCon->Invoke(delAddNode);
    }
    treeViewTlgCon->EndUpdate();
	  //Invoke(enableScrollEvent);
  }
}
//-------------------------------------------------------------------------------
// emal
String^ CTlgContainerTreeViewForm::getNodeFillPathAfterSelect()
{
  return this->NodeFillPathAfterSelect;
}
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::getTreeNode(TreeNode^ node,CItemWrapper^ tlg)
{
 String^ val1 = nullptr;
 //String^ val2 = 0;
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
void CTlgContainerTreeViewForm::getSubNode(TreeNode^ node,CItemWrapper^ tlg,int id)
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
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::addNewNode()
{
   treeViewTlgCon->Nodes->Add(MyNode);
}
//-------------------------------------------------------------------------------
int CTlgContainerTreeViewForm::getTlgCount()
{
	if(TlgContainer)
		return TlgContainer->getVirtualTlgCount();
	else
		return 0;
  //return treeViewTlgCon->Nodes->Count;
}
//-------------------------------------------------------------------------------
CItemWrapper^ CTlgContainerTreeViewForm::getClonedTlg(int index)
{
	CItemWrapper^ wrTlg = gcnew CTlgWrapper();
	TlgContainer->getClonedTlg(wrTlg,index);
	return wrTlg;
}
//-------------------------------------------------------------------------------
CItemWrapper^ CTlgContainerTreeViewForm::getClonedVirtualTlg(int index)
{
	CItemWrapper^ wrTlg = gcnew CTlgWrapper();
	TlgContainer->getClonedVirtualTlg(wrTlg,index);
	return wrTlg;
}
//-------------------------------------------------------------------------------
double CTlgContainerTreeViewForm::getTlgTime(int index)
{
	double ret = 0.0;
	ret = TlgContainer->getTlgTime(index);
	return ret;
}
//-------------------------------------------------------------------------------
double CTlgContainerTreeViewForm::getVirtualTlgTime(int index)
{
  double ret = 0.0;
  ret=TlgContainer->getVirtualTlgTime(index);
  return ret;
}
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::getProtoTypTreeNode(TreeNode^ node,CItemWrapper^ tlg)
{
  String^ name = nullptr;
  String^ descr = nullptr;
  array <String^>^ str;
  int flag;
  int count = tlg->getTlgElemCount();
  TreeNode^ subNode=nullptr;
  TreeNode^ subSubNode = nullptr;

  name = tlg->getName();
  descr = tlg->getTlgDescr();
  node->Text = String::Concat(name,"     (",descr,")");
  for(int i=1;i<=count;i++)
  {
    str=tlg->getElemProtoTypInfo(i,&flag);
    if(flag == 1) //simple element
    {
       subNode = gcnew System::Windows::Forms::TreeNode();
       subNode->Text = str[0];
       node->Nodes->Add(subNode);
    }
    else
    {
      if(flag == 2) //array
      {
        subNode = gcnew System::Windows::Forms::TreeNode();
        subNode->Text = String::Concat(str[0]," (Liste: ",str[1],")");
        node->Nodes->Add(subNode);
      }
      else
      {
        if(flag == 3)
        {
          subNode = gcnew System::Windows::Forms::TreeNode();
          subNode->Text = str[0];
          for(int j=1;j<str->Length;j++)
          {
            subSubNode = gcnew System::Windows::Forms::TreeNode();
            subSubNode->Text = str[j];
            subNode->Nodes->Add(subSubNode);
          }
          node->Nodes->Add(subNode);
        }
      }
    }
  }
}
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::setSelectEvent(AfterSelectEvent^ event)
{
  SelectEvent = event;
}
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::setAfterCollapsEvent(TreeViewEventHandler^ event)
{
	/*treeViewTlgCon->add_AfterCollapse(event);*/
	treeViewTlgCon->AfterCollapse += event;
}
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::setAfterExpandEvent(TreeViewEventHandler^ event)
{
	//treeViewTlgCon->add_AfterExpand(event);
	treeViewTlgCon->AfterExpand += event;
}
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::clearView()
{
  UpdateFlag = false;
	treeViewTlgCon->BeginUpdate();
	//treeViewTlgCon->set_SelectedNode(0);
	treeViewTlgCon->Nodes->Clear();
	treeViewTlgCon->EndUpdate();
  UpdateFlag = true;
	//enableScroll();
	vScrollBar1->Hide();
	//if(enableScrollEvent)
		//Invoke(enableScrollEvent);
	//vScrollBar1->Hide();
}
//-------------------------------------------------------------------------------
String^ CTlgContainerTreeViewForm::getPathFile()
{
	if(TlgContainer)
		return TlgContainer->getPathFile();
	else
		return "";
}
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::updateContainerView(ArrayList^ liste)
{
  TlgContainer->setFilterByTelName(liste);
  if(DataUpdate != nullptr)
     DataUpdate->Invoke();
}
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::resetContainer()
{
    TlgContainer->reset();
    if(DataUpdate != nullptr)
       DataUpdate->Invoke();
}
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::setPrototypMode(bool mode)
{
	this->IsPrototypContainer=mode;
}
//-------------------------------------------------------------------------------
int CTlgContainerTreeViewForm::getItemViewCount()
{
	return treeViewTlgCon->Nodes->Count;
}
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::setDataUpdateEvent(DataUpdateEvent^ datUp)
{
  DataUpdate=datUp;
}
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::setItemViewChangeEvent(ItemViewChangeEvent^ itemChange)
{
  ItemViewChange=itemChange;
}
//-------------------------------------------------------------------------------
int CTlgContainerTreeViewForm::getVirtualTlgCount()
{
  return TlgContainer->getVirtualTlgCount();
}
//-------------------------------------------------------------------------------
int CTlgContainerTreeViewForm::calcViewIndexToContainerIndex(int index)
{
  int ret = -1;
  if(vScrollBar1->Visible)
  {
    ret = vScrollBar1->Value+index-1;
  }
  else
  {
    ret = index-1;
  }
  return ret;
}
//-------------------------------------------------------------------------------
int CTlgContainerTreeViewForm::getItemHeigth()
{
  return treeViewTlgCon->ItemHeight;
}
//-------------------------------------------------------------------------------
bool CTlgContainerTreeViewForm::setFilterRegExp(array <String^>^ reg)
{
	bool ret;
	ret=TlgContainer->setFilterByRegExp(reg);
  if(DataUpdate != nullptr)
     DataUpdate->Invoke();
	return ret;
}
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::selectTelegram(int index)
{
	int i,count;
	count=treeViewTlgCon->Nodes->Count;
	for(i=0;i<count;i++)
	{
		treeViewTlgCon->Nodes[i]->BackColor = System::Drawing::Color::White;
	}

	if(vScrollBar1->Visible)
	{
		if(ItemsCount < index)
		{
			vScrollBar1->Value = (index-ItemsCount+5);
			scrolViewUpdate();
      treeViewTlgCon->SelectedNode = treeViewTlgCon->Nodes[ItemsCount-5];
      //treeViewTlgCon->Nodes[ItemsCount-5)->set_BackColor(System::Drawing::Color::Blue);
		}
		else
		{
      treeViewTlgCon->SelectedNode = treeViewTlgCon->Nodes[index-1];
      //treeViewTlgCon->Nodes[index-1)->set_BackColor(System::Drawing::Color::Blue);
		}
	}
	else
	{
		treeViewTlgCon->SelectedNode = treeViewTlgCon->Nodes[index-1];
    //treeViewTlgCon->Nodes[index-1)->set_BackColor(System::Drawing::Color::Blue);
    //treeViewTlgCon->set_SelectedNode(node);
	}
	CItemWrapper^ wrp = getClonedVirtualTlg(index);
	SelectEvent->Invoke(wrp,CItemView::CreateTypForm::LogFile);
}
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::scrolViewUpdate()
{
	 //VScrollBar^ scrollBar = safe_cast<VScrollBar^>(sender);
  int index=vScrollBar1->Value;
  ItemsLow=index;
  //if(IsPrototypContainer)
	  //ShowProtoTypContainer();
  //else
	  //ShowTlgContainer();
	ShowContainer();
  if(ItemViewChange)
    ItemViewChange->Invoke(ItemsLow,ItemsCount);
}
//-------------------------------------------------------------------------------
/*void CTlgContainerTreeViewForm::enableScroll()
{
	if(TlgContainer)
	{
		int height,itemHeight;
    //this->TlgContainer = Container;
   // TlgContainer->reset();
		height=treeViewTlgCon->Height;
		itemHeight=treeViewTlgCon->ItemHeight;
		ItemsCount = height/itemHeight;
		ItemsLow=0;
	
		if(ItemsCount < TlgContainer->getVirtualTlgCount())
		{
			vScrollBar1->Hide();
			if(!vScrollBar1->Visible)
			{
				vScrollBar1->Visible=true;
				vScrollBar1->Value=0;
			}
			vScrollBar1->Minimum = (0);
			vScrollBar1->Maximum = (TlgContainer->getVirtualTlgCount()-ItemsCount+1);
			vScrollBar1->Value = (vScrollBar1->Value+1);
		}
		else
		{
			vScrollBar1->Hide();
			ItemsCount=TlgContainer->getVirtualTlgCount();
		}
		if(DataUpdate != nullptr)
			DataUpdate->Invoke();
	}
}*/
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::initTreeItemState()
{
	int count,i;
	value struct TreeNodeStateTyp^ state=nullptr;
	ItemStateList->Clear();
	count=TlgContainer->getVirtualTlgCount();
	for(i=0;i<count;i++)
	{
		state = gcnew value struct TreeNodeStateTyp();
		state->Expand = false;
		state->ExpandListe = gcnew ArrayList();
		ItemStateList->Add(state);
	}
}
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::ShowContainer()
{
	int countTlg,itemHeight,height,countItem;
	
	treeViewTlgCon->Left=0;
	treeViewTlgCon->Top=0;
	treeViewTlgCon->Height=this->Height;

  if(TlgContainer)
  {
    UpdateFilterText();
    
    countTlg=TlgContainer->getVirtualTlgCount();
    itemHeight=treeViewTlgCon->ItemHeight;
    height=treeViewTlgCon->Height;
    countItem = height / itemHeight;
	  ItemsCount = countItem;
    if(countTlg>countItem)
	    initTreeViewItem(countItem);
    else
	    initTreeViewItem(countTlg);
    if(countItem < countTlg)
    {
	    vScrollBar1->Minimum = (1);
	    vScrollBar1->Maximum = (countTlg-countItem+1);
	    //vScrollBar1->Value=1);
	    treeViewTlgCon->Scrollable=false;
	    vScrollBar1->Show();
	    treeViewTlgCon->Width=this->Width-vScrollBar1->Width;
	    ShowFromScroll();
    }
    else
    {
	    vScrollBar1->Value = (1);
	    vScrollBar1->Hide();
	    //treeViewTlgCon->Scrollable=true;
	    treeViewTlgCon->Width=this->Width;
	    ShowFromScroll();
	    treeViewTlgCon->Scrollable=true;
    }
  }
}
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::ShowFromScroll()
{
	CTlgWrapper^ wr=gcnew CTlgWrapper();
	String^ name=nullptr;
	String^ descr=nullptr;
  int selIndex;
  int itemHeight;
  int mHeight;
  int countExpNew;
	int pos,count,i,tlgCount;
  int restScroll;

	pos=getUnderTelegramm(restScroll);
   
  //MessageHandler->Invoke(String::Concat("max: ",System::Convert::ToString(vScrollBar1->Maximum)),0);
   
	count=treeViewTlgCon->Nodes->Count;
	tlgCount=TlgContainer->getVirtualTlgCount();

  selIndex=TlgContainer->getSelectedItem();
	treeViewTlgCon->BeginUpdate();
	
	treeViewTlgCon->SelectedNode = nullptr;
  countExpNew=0;
    //MessageHandler->Invoke(String::Concat("erse Tel: ",System::Convert::ToString(pos)),0);
    //if(pos > tlgCount - count+1)
        //pos--;
	for(i=pos;i<count+pos;i++)
	{
		if(tlgCount >= i)
		{
			TlgContainer->getClonedVirtualTlg(wr,i);
			name=wr->getName();
			descr=TlgContainer->getVirtualTlgDescr(i);
			treeViewTlgCon->Nodes[i-pos]->Text=String::Concat(name,"  ",descr);
			itemHeight=setTreeViewNodeState(i-pos,i);
      //itemHeight=1;
      countExpNew=countExpNew+itemHeight;
      if(i == selIndex)
      {
        treeViewTlgCon->SelectedNode = treeViewTlgCon->Nodes[i-pos];
      }
		}
	}

  mHeight=countExpNew*treeViewTlgCon->ItemHeight;
  treeViewTlgCon->Height=mHeight;
  
  if(treeViewTlgCon->Height < this->Height)
    treeViewTlgCon->Height = this->Height;

  if(treeViewTlgCon->Height > this->Height)
  {
      treeViewTlgCon->Top=(vScrollBar1->Value-restScroll-1)*treeViewTlgCon->ItemHeight*(-1);
      //MessageHandler->Invoke(String::Concat("restScroll: ",System::Convert::ToString(restScroll)),0);
      //MessageHandler->Invoke(String::Concat("Top: ",System::Convert::ToString(treeViewTlgCon->Top)),0);
      //treeViewTlgCon->Top=(vScrollBar1->Value-1-scrNoPos)*treeViewTlgCon->ItemHeight*(-1);
  }
  else
  {
      treeViewTlgCon->Top=0;
  }
  if(treeViewTlgCon->Top > 0)
      treeViewTlgCon->Top=0;
    
  //treeViewTlgCon->Top;

	if(!((selIndex>=pos)&&(selIndex<=tlgCount)))
	{
		treeViewTlgCon->SelectedNode = nullptr;
	}
	treeViewTlgCon->EndUpdate();
    //---test
    //MessageHandler->Invoke("Aufruf",0);
    //--------------------------------
	if(scrollPositionUpdate)
		scrollPositionUpdate->Invoke();
}
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::initTreeViewItem(int count)
{
	int i;
	System::Windows::Forms::TreeNode^ node=nullptr;
	if(treeViewTlgCon->Nodes->Count != count)
	{
		DelAddNodeType^ delAddNode = gcnew DelAddNodeType(this,&CTlgContainerTreeViewForm::addNewNode);
		treeViewTlgCon->BeginUpdate();
		treeViewTlgCon->Nodes->Clear();
		for(i=0;i<count;i++)
		{
			node = gcnew System::Windows::Forms::TreeNode();
			//node->Nodes->Add("dummy");
			node->Text="lll";
			MyNode = node; 
			treeViewTlgCon->Invoke(delAddNode);
		}
		treeViewTlgCon->EndUpdate();
	}
}
//-------------------------------------------------------------------------------
int CTlgContainerTreeViewForm::getIndexTlgInConFromTreeView(int index)
{
	int ret=index+1;
	if(vScrollBar1->Visible)
	{
		ret = vScrollBar1->Value + index;
	}
	return ret;
}
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::buildTreeViewNode(TreeNode^ node,CItemWrapper^ tlg)
{
	String^ val1 = nullptr;
	int count,i;

	node->Nodes->Clear();
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
int CTlgContainerTreeViewForm::setTreeViewNodeState(int node,int pos)
{
  int ret=0;
	value struct TreeNodeStateTyp^ stateNode = safe_cast<value struct TreeNodeStateTyp^>(ItemStateList[pos-1]);
	System::Windows::Forms::TreeNode^ trNode=nullptr;
	trNode=treeViewTlgCon->Nodes[node];
  trNode->Tag = (pos);
  ret=1;
	if(stateNode->Expand)
	{
		int count,i,index;
		//System::Windows::Forms::TreeNode^ trNode=0;
		CTlgWrapper^ wr = gcnew CTlgWrapper();
		TlgContainer->getClonedVirtualTlg(wr,pos);
    ret=ret+wr->getTlgElemCount();
		buildTreeViewNode(trNode,wr);
		trNode->Expand();
		count=stateNode->ExpandListe->Count;
		for(i=0;i<count;i++)
		{
			index = System::Convert::ToInt32(stateNode->ExpandListe[i]);
			trNode->Nodes[index]->Expand();
			ret= ret + trNode->Nodes[index]->Nodes->Count;
		}
	}
	else
	{
		trNode->Collapse();
		trNode->Nodes->Clear();
		//trNode->Nodes->Add("dummy");
		stateNode->Expand=false;
	}
  return ret;
}
//-------------------------------------------------------------------------------
int CTlgContainerTreeViewForm::getCountCollapsedItems(TreeNode^ node)
{
	int ret;
	int count,i;
	ret=node->Nodes->Count;
	count=node->Nodes->Count;
	for(i=0;i<count;i++)
	{
		if(node->Nodes[i]->IsExpanded)
			ret=ret+node->Nodes[i]->Nodes->Count;
	}
	return ret;
}
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::setMessageHandler(DelMessageHandlerTyp^ handMess)
{
	MessageHandler=handMess;
}
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::setTreeViewPosition()
{
	treeViewTlgCon->Top = 0;
	treeViewTlgCon->Left = 0;

	if(vScrollBar1->Visible)
		treeViewTlgCon->Width = this->Width - vScrollBar1->Width;
	else
		treeViewTlgCon->Width = this->Width;

	if(treeViewTlgCon->Height < this->Height)
		treeViewTlgCon->Height = this->Height;
	
}
//-------------------------------------------------------------------------------
int CTlgContainerTreeViewForm::getUnderTelegramm(int& scroll)
{
	int ret=1;
	int posScroll;
	bool flag=false;
  int i,count;
  int j,subElemCount;
  int itemCount;
  int extendSubElem;
	value struct TreeNodeStateTyp^ stateNode=nullptr;
	CTlgWrapper^ wr=nullptr;

	count=ItemStateList->Count;
	posScroll=vScrollBar1->Value;
	i=0;
  itemCount=0;
	wr=gcnew CTlgWrapper();
  scroll=0;

	while((!flag) && (i<count))
	{
    stateNode = safe_cast<value struct TreeNodeStateTyp^>(ItemStateList[i]);
    itemCount++;
    if(stateNode->Expand)
		{
       TlgContainer->getClonedVirtualTlg(wr,i+1);
       itemCount=itemCount+wr->getTlgElemCount();
       subElemCount=stateNode->ExpandListe->Count;
       for(j=0;j<subElemCount;j++)
       {
         extendSubElem=System::Convert::ToInt32(stateNode->ExpandListe[j]);
         itemCount=itemCount+wr->getSubElemCount(extendSubElem+1);      
       }
    }
    if(itemCount >= posScroll)
    {
      if(i != 0)
      {
        ret = i+1;
      }
      flag=true;
    }
    else
    {
      i++;
      scroll=itemCount;
    }
  }//end while
  if(ret > TlgContainer->getVirtualTlgCount() - treeViewTlgCon->Nodes->Count+1)
    ret--;
	return ret;
}
//-------------------------------------------------------------------------------
int CTlgContainerTreeViewForm::getNodeHeight(int index)
{
	int ret=0;
	int tel;
	int count,i;
	int mheight;
	CTlgWrapper^ wr=gcnew CTlgWrapper();
	mheight = treeViewTlgCon->ItemHeight;
	ret=mheight;
	tel=System::Convert::ToInt32(treeViewTlgCon->Nodes[index]->Tag);
  //---test
  //MessageHandler->Invoke(String::Concat("tel num  ",System::Convert::ToString(tel)),2);
  //-------------------------------------------------
	value struct TreeNodeStateTyp^ state = safe_cast<value struct TreeNodeStateTyp^>(ItemStateList[tel-1]); 
	if(state->Expand)
	{
		TlgContainer->getClonedVirtualTlg(wr,index+1);
    TlgContainer->getClonedVirtualTlg(wr,tel);
		ret=ret+wr->getTlgElemCount()*mheight;
		count=state->ExpandListe->Count;
    //---test
    //MessageHandler->Invoke(String::Concat("tel: ",wr->getName()),2);
    //MessageHandler->Invoke(String::Concat("telNumm: ",wr->getName()),2);
    //if(count>0)
        //MessageHandler->Invoke(System::Convert::ToString(count),2);
    //-------------------------------------------------------------
		for(i=0;i<count;i++)
		{
			ret=ret+wr->getSubElemCount(System::Convert::ToInt32(state->ExpandListe[i])+1)*mheight;
		}
	}
	//if(index == 0)
	//MessageHandler->Invoke(System::Convert::ToString(ret),2);
	return ret;
}
//-------------------------------------------------------------------------------
int CTlgContainerTreeViewForm::getTreeViewTop()
{
	//MessageHandler->Invoke(System::Convert::ToString(treeViewTlgCon->Top),0);
	return treeViewTlgCon->Top;
}
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::setScrollUpdateEvent(ScrollPositionUpdateTyp^ event)
{
	scrollPositionUpdate = event;
}
//-------------------------------------------------------------------------------
int CTlgContainerTreeViewForm::getTlgPosInContainer(int index)
{
	return System::Convert::ToInt32(treeViewTlgCon->Nodes[index-1]->Tag);
}
//-------------------------------------------------------------------------------
void CTlgContainerTreeViewForm::setRecModus()
{
  RecFlag=true;
  vScrollBar1->Visible=false;
  treeViewTlgCon->Scrollable=true;
}
//---------------------------------------------------------------
void CTlgContainerTreeViewForm::UpdateFilterText()
{
  if(TlgContainer)
  {
    String^ filter = TlgContainer->getFilterRegExpAsString();
    if (this->UpdateFilterTextDel != nullptr)
    {
      this->UpdateFilterTextDel->Invoke(filter);
    }
  }
}
//--------------------------------------------------------------
void CTlgContainerTreeViewForm::setUpdateFilterTextTyp(UpdateFilterTextTyp^ del)
{
  this->UpdateFilterTextDel = del;
}