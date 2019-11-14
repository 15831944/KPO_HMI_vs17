#include "StdAfx.h"
#include "CTree.h"


using namespace simulator;
//------------------------------------------------------------------------------------
int CTree::getHScrollValue()
{
  return TreeListView::getHScrollValue();
}
//------------------------------------------------------------------------------------
int CTree::getColumnsHeaderHeight()
{
	return TreeListView::ColumnsOptions->HeaderHeight;
}
//------------------------------------------------------------------------------------
int CTree::getColumnsCount()
{
	/* TreeListView::Columns->Draw(*/
	/*CommonTools::TreeList::ViewSetting::set_ShowLine(true);*/
  return TreeListView::Columns->Count;
}
//------------------------------------------------------------------------------------
int CTree::getColumnWidht(int index)
{
  return TreeListView::Columns[index]->Width;
}
//------------------------------------------------------------------------------------
int CTree::getColumnsWidht()
{
  return TreeListView::Columns->ColumnsWidth;
}
//------------------------------------------------------------------------------------
int CTree::getColumnsHeight()
{
  if (!RowSetting)
    RowSetting = gcnew CommonTools::TreeList::RowSetting(this);
  
  return RowSetting->ItemHeight;
}
//------------------------------------------------------------------------------------
//System::Void CTree::OnCollapseAllChildren(System::Object * sender,System::EventArgs * e)
//{
//	TreeListView::Nodes->Count;
//
//	/*TreeListView::BeginUpdate();
//
//	if (TreeListView::MultiSelect && TreeListView::NodesSelection->Count > 0)
//	{
//		
//		CommonTools::Node* selnode=0;
//		CommonTools::Node* node=0;
//		for (int i=0;i<NodesSelection->Count;i++)
//		{
//			selnode = safe_cast <CommonTools::Node*> (NodesSelection[i));
//			for (int j=0;;j++)
//			{
//				node = safe_cast <CommonTools::Node*> (selnode->Nodes[i));
//				node->Collapse();
//			}
//		}
//		NodesSelection->Clear();
//	}
//	
//	if (TreeListView::FocusedNode != 0 && TreeListView::FocusedNode->HasChildren)
//	{
//		CommonTools::Node* node=0;
//		for (int i=0;i<FocusedNode->Nodes->Count;i++)
//		{
//			node = node = safe_cast <CommonTools::Node*> (FocusedNode->Nodes[i));
//			node->Collapse();
//		}
//	}
//	TreeListView::EndUpdate();*/
//}

//------------------------------------------------------------------------------------
//System::Void CTree::OnExpandAllChildren(System::Object * sender,System::EventArgs * e)
//{
//	/*TreeListView::BeginUpdate();
//	if (TreeListView::MultiSelect && TreeListView::NodesSelection->Count > 0)
//	{
//		CommonTools::Node* selnode=0;
//		for (int i=0;i<NodesSelection->Count;i++)
//		{
//			selnode = safe_cast <CommonTools::Node*> (NodesSelection[i));
//			selnode->ExpandAll();
//		}
//		NodesSelection->Clear();
//	}
//	if (TreeListView::FocusedNode != 0)
//		TreeListView::FocusedNode->ExpandAll();
//	TreeListView::EndUpdate();*/
//}
//------------------------------------------------------------------------------------
//System::Void CTree::OnDeleteSelectedNode(System::Object * sender,System::EventArgs * e)
//{
//	/*TreeListView::BeginUpdate();
//	CommonTools::Node* node = FocusedNode;
//			if (node != 0 && node->Owner != 0)
//			{
//				node->Collapse();
//				CommonTools::Node* nextnode = CommonTools::NodeCollection::GetNextNode(node, 1);
//				if (nextnode == 0)
//					nextnode = CommonTools::NodeCollection::GetNextNode(node, -1);
//				node->Owner->Remove(node);
//				FocusedNode = nextnode;
//			}
//	TreeListView::EndUpdate();*/
//}
//------------------------------------------------------------------------------------
//void CTree::BeforeShowContextMenu()
//{
//  if (TreeListView::GetHitNode() == 0)
//		ContextMenu = 0;
//	else
//		ContextMenu = m_contextMenu;
//}
//------------------------------------------------------------------------------------
//System::Object* CTree::GetData(CommonTools::Node *node, CommonTools::TreeListColumn *column)
//{
//  System::Object* data = CommonTools::TreeListView::GetData(node, column);
//	if (data != 0)
//		return data;
//
//	if (column->Fieldname == "childCount")
//	{
//		if (node->HasChildren)
//			return __box(node->Nodes->Count);
//		return "<none>";
//	}
//	if (column->Fieldname == "visibleCount")
//	{
//		if (node->HasChildren)
//			return __box(node->VisibleNodeCount);
//		return "<none>";
//	}
//	return System::String::Empty;
//}
//------------------------------------------------------------------------------------