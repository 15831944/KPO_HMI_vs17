#include "StdAfx.h"
#include "CInterConvertForm.h"

using namespace LogFileConversion;
//-----------------------------------------------------------------------------
System::Void CInterConvertForm::OnResizeForm(System::Object ^  sender, System::EventArgs ^  e)
{
  int mWidth = (listViewInterConv->Width - imageListTlg->ImageSize.Width)/2 - 4;
  listViewInterConv->Visible = false;
  listViewInterConv->BeginUpdate();
  listViewInterConv->Columns[0]->Width = mWidth;
  listViewInterConv->Columns[1]->Width = mWidth;
  listViewInterConv->EndUpdate();
  listViewInterConv->Visible = true;
  showComboBoxChose();
}
//-----------------------------------------------------------------------------
System::Void CInterConvertForm::OnResizeListView(System::Object ^  sender, System::EventArgs ^  e)
{
  /*int mWidth = (listViewInterConv->Width - imageListTlg->ImageSize.Width)/2 - 4;
  listViewInterConv->Visible = false;
  listViewInterConv->BeginUpdate();
  listViewInterConv->Columns->get_Item(0)->Width = mWidth;
  listViewInterConv->Columns->get_Item(1)->Width = mWidth;
  listViewInterConv->EndUpdate();
  listViewInterConv->Visible = true;*/
  //showComboBoxChose();
   //showComboBoxChose();
}
//------------------------------------------------------------------------------
System::Void CInterConvertForm::OnSizeChanged(System::Object ^  sender, System::EventArgs ^  e)
{
  /*int mWidth = (listViewInterConv->Width - imageListTlg->ImageSize.Width)/2 - 4;
  listViewInterConv->Visible = false;
  listViewInterConv->BeginUpdate();
  listViewInterConv->Columns->get_Item(0)->Width = mWidth;
  listViewInterConv->Columns->get_Item(1)->Width = mWidth;
  listViewInterConv->EndUpdate();
  listViewInterConv->Visible = true;*/
  //showComboBoxChose();
}
//------------------------------------------------------------------------------
System::Void CInterConvertForm::OnMouseDownTreeView(System::Object ^  sender, System::Windows::Forms::MouseEventArgs ^  e)
{
  if(listViewInterConv->Items->Count != 0)
  {
    int m_X = e->X;
    int m_heigth = listViewInterConv->Items[0]->Bounds.Height;
	  ListViewItem^ item=nullptr;
    int m_Y = e->Y;
    int topIndex = listViewInterConv->TopItem->Index;
    int clIndex = (m_Y-19)/m_heigth+1+topIndex;
    item=listViewInterConv->Items[clIndex-1];
    if(imageListTlg->ImageSize.Width >= m_X)
    {
      if(item->Tag != nullptr)
      {
        item->ImageIndex = (item->ImageIndex+1)%2;
        if(item->ImageIndex == 0)
        {
	        collapsItem(clIndex-1);
        }
        else
        {
	        if(item->ImageIndex == 1)
	        {
		        extendItem(clIndex-1);
	        }
        }
      }
    }
    else
    {
      int pos_X = listViewInterConv->Columns[0]->Width;
      if(m_X >= pos_X)
      {
        String^ tlgName=nullptr;
        String^ elemName=nullptr;
        String^ subElemName=nullptr;
        bool updateFlag=false;
        ListViewItem^ item = listViewInterConv->Items[clIndex-1]; 
        getTlgElemFromItem(item,tlgName,elemName,subElemName);
        if((elemName == nullptr) || (elemName->Equals("")))
        {
          updateFlag = true;
        }
        else
        {
          if(isSimpleTlgElem(tlgName,elemName))
          {
            updateFlag = true;
          }
          else
          {
            if((elemName != nullptr) && (subElemName != nullptr) && (!elemName->Equals("")) && (!subElemName->Equals("")))
              updateFlag = true;
          }
        }
        if(updateFlag)
        {
          ComboBoxChose->Tag = item;
          setComboBoxItem();
          showComboBoxChose();
          TopItemIndex = clIndex-1;
        }  
      }
    }
  }
}
//------------------------------------------------------------------------------
System::Void CInterConvertForm::OnSelIndexChange(System::Object ^  sender, System::EventArgs ^  e)
{
  if(ComboBoxChose->Tag != nullptr)
  {
    String^ val = ComboBoxChose->Text;
    String^ tlgName=nullptr;
    String^ elemName=nullptr;
    String^ subElemName=nullptr;
    String^ destElemName=nullptr;
    String^ destSubElemName=nullptr;
    ListViewItem^ item = safe_cast<ListViewItem^>(ComboBoxChose->Tag);
    item->SubItems[1]->Text=(val);
    getTlgElemFromItem(item,tlgName,elemName,subElemName);
    if((elemName == nullptr) && (subElemName == nullptr))// tlg item
    {
      InterAssignment->setAssignedTlgName(item->SubItems[0]->Text,val);
    }
    else  //elem item
    {
      int pos;
      pos = val->IndexOf("\\");
      if(pos == -1)
      {
        destElemName=val;
        destSubElemName=nullptr;
      }
      else
      {
        destElemName = val->Substring(0,pos);
        destSubElemName = val->Substring(pos+1,val->Length-pos-1);
      }
      InterAssignment->setAssignedTlgElem(tlgName,elemName,subElemName,destElemName,destSubElemName);
    }
  }
}
//------------------------------------------------------------------------------
System::Void CInterConvertForm::OnDrawItemComBx(System::Object ^  sender, System::Windows::Forms::DrawItemEventArgs ^  e)
{
  if(e->Index >= 0)
  {
    System::Drawing::Brush^ br = System::Drawing::Brushes::Black;
    e->Graphics->DrawString(ComboBoxChose->Items[e->Index]->ToString(),e->Font,br,e->Bounds.Location);
    e->DrawFocusRectangle();
  }
}
//------------------------------------------------------------------------------
void CInterConvertForm::setInterAssignment(CInterAssignment^ interAss)
{
  InterAssignment = interAss;
  SourceInter = InterAssignment->getSourceInter();
  DestinationInter = InterAssignment->getDestInter();
  updateView();
}
//-----------------------------------------------------------------------------
void CInterConvertForm::updateView()
{
  listViewInterConv->BeginUpdate();
  listViewInterConv->Items->Clear();

  if(SourceInter)
  {
    int tlgCount = SourceInter->getTlgCount();
    CTlgWrapper^ tlgWr = gcnew CTlgWrapper();
    ListViewItem^ item = nullptr;
    String^ destTlgName=nullptr;
    value struct ItemStateInfoTyp^ itemStateInfo=nullptr;
    for(int i=0;i<tlgCount;i++)
    {
      SourceInter->getClonedTlg(tlgWr,i+1);
      item = gcnew ListViewItem(tlgWr->getName(), 0);
      item->ImageIndex = 0;
      itemStateInfo = gcnew value struct ItemStateInfoTyp;
      itemStateInfo->TlgName = tlgWr->getName();
      itemStateInfo->ElemName = nullptr;
      itemStateInfo->Extendet = false;
	    itemStateInfo->ElemTyp = NodeTyp::None;

      destTlgName=InterAssignment->getAssignedTlgName(tlgWr->getName());
      if(destTlgName == nullptr)
      {
        destTlgName="";
      }
      item->SubItems->Add(destTlgName);

      item->Tag = itemStateInfo; 
      item->BackColor = TelColor;
      listViewInterConv->Items->Add(item);
    }
  }
  listViewInterConv->EndUpdate();
}
//-----------------------------------------------------------------------------
void CInterConvertForm::extendItem(int index)
{
	ListViewItem^ item = listViewInterConv->Items[index]; 
	value struct ItemStateInfoTyp^ itemStateInfo = safe_cast<ItemStateInfoTyp^>(item->Tag);
	CTlgWrapper^ tlgWr = gcnew CTlgWrapper();
	SourceInter->getFlatTlg(tlgWr,itemStateInfo->TlgName);
	if(itemStateInfo->ElemName == nullptr)
	{
		extendItemAsTlg(tlgWr,index);
	}
	else
	{
		extendItemAsTlgElem(tlgWr,itemStateInfo->ElemName,index);
	}
	itemStateInfo->Extendet = true;
    showComboBoxChose();
}
//------------------------------------------------------------------------------
void CInterConvertForm::extendItemAsTlg(CTlgWrapper^ tlg,int index)
{
	int count = tlg->getTlgElemCount();
	int elemCount;
	int insertIndex=index+1;
	String^ elemTyp = nullptr;
  String^ assTlgElem = nullptr;
  array <String^>^ arr;
  int indexElem;
  arr = InterAssignment->getTlgElemAssignment(tlg->getName(),nullptr);
	listViewInterConv->BeginUpdate();
	for(int i=0;i<count;i++)
	{
		ListViewItem^ item = gcnew ListViewItem(String::Concat("-----",tlg->getElemName(i+1)),0);
		elemCount = tlg->getSubElemCount(i+1);
		if(elemCount == 0)
		{
			item->BackColor = SimpleElemColor;
			item->ImageIndex=-1;
		}
		else
		{
			item->BackColor = ComplexElemColor;
            //item->Sm = imageListElem;
			item->ImageIndex=0;
			value struct ItemStateInfoTyp^ itemStateInfo = gcnew ItemStateInfoTyp();
			itemStateInfo->TlgName = tlg->getName();
			itemStateInfo->ElemName = tlg->getElemName(i+1);
			itemStateInfo->Extendet = false;
			elemTyp=tlg->getElemTypAsString(i+1);
			if(elemTyp->Equals("Record"))
			{
				itemStateInfo->ElemTyp = NodeTyp::Rekords;
			}
			else
			{
				if(elemTyp->Equals("Array"))
				{
					itemStateInfo->ElemTyp = NodeTyp::Array;
					elemTyp = String::Concat(elemTyp," ",System::Convert::ToString(elemCount));
				}
			}
			item->SubItems[0]->Text = String::Concat(item->SubItems[0]->Text," (",elemTyp,")");
			item->Tag = itemStateInfo;
		}
    String^ test = tlg->getElemName(i+1);
    indexElem = System::Array::IndexOf(arr,tlg->getElemName(i+1));
    if(indexElem != -1)
    {
      while(indexElem%2 != 0)
      {
        indexElem = System::Array::IndexOf(arr,tlg->getElemName(i+1),indexElem+1);
      }
    }
        
    if(indexElem != -1)
    {
      item->SubItems->Add(arr[indexElem+1]);
    }
    else
    {
      item->SubItems->Add("");
    }
		listViewInterConv->Items->Insert(insertIndex,item);
		insertIndex++;
	}
	listViewInterConv->EndUpdate();
}
//------------------------------------------------------------------------------
int CInterConvertForm::extendItemAsTlgElem(CTlgWrapper^ tlg,String^ elem,int index)
{
  int elemIndex = tlg->getElemIndex(elem);
  int count = tlg->getSubElemCount(elemIndex);
  String^ elemName = nullptr;
  ListViewItem^ item = nullptr;
  int insertIndex = index+1;
  array <String^>^ arr;
  //String^ itemName = 0;
  int pos;
  arr = InterAssignment->getTlgElemAssignment(tlg->getName(),nullptr);
  listViewInterConv->BeginUpdate();
  for(int i=0;i<count;i++)
  {
    elemName=tlg->getSubElemName(elemIndex,i+1);
    item = gcnew ListViewItem(String::Concat("     -----",elemName),0);
    pos=System::Array::IndexOf(arr,String::Concat(elem,"\\",elemName));
    if(pos != -1)
    {
      while(pos%2 != 0)
      {
        pos = System::Array::IndexOf(arr,String::Concat(elem,"\\",elemName),pos+1);
      }
    }
    if(pos != -1)
    {
      item->SubItems->Add(arr[pos+1]);
    }
    else
    {
      item->SubItems->Add("");
    }
    item->BackColor = SimpleElemColor;
	  item->ImageIndex=-1;
    listViewInterConv->Items->Insert(insertIndex,item);
    insertIndex++;
  }
  listViewInterConv->EndUpdate();
  return count;
}
//------------------------------------------------------------------------------
void CInterConvertForm::collapsItem(int index)
{
	value struct ItemStateInfoTyp^ itemStateInfo = safe_cast<ItemStateInfoTyp^>(listViewInterConv->Items[index]->Tag);
  if(itemStateInfo->ElemName == nullptr)
  {
    collapsItemAsTlg(index);
  }
  else
  {
    CTlgWrapper^ wrTlg = gcnew CTlgWrapper();
    SourceInter->getFlatTlg(wrTlg,itemStateInfo->TlgName);
    collapsItemAsTlgElem(wrTlg,itemStateInfo->ElemName,index);
  }
  showComboBoxChose();
}
//-----------------------------------------------------------------------------
void CInterConvertForm::collapsItemAsTlg(int index)
{
  bool flag;
  ListViewItem^ item = nullptr;
  value struct ItemStateInfoTyp^ itemStateInfo = nullptr;
  flag=false;
  listViewInterConv->BeginUpdate();
  while((!flag))
  {
    if(listViewInterConv->Items->Count - 1 < index+1)
    {
      flag=true;
    }
    else
    {
      item=listViewInterConv->Items[index+1];
      if(item->Tag != nullptr)
      {
        itemStateInfo = safe_cast<value struct ItemStateInfoTyp^>(item->Tag);
        if(itemStateInfo->ElemName == nullptr)
        {
          flag = true;
        }
      }
      if(!flag)
      {
        listViewInterConv->Items->Remove(item);
      }
    }
  }
  listViewInterConv->EndUpdate();
}
//-----------------------------------------------------------------------------
void CInterConvertForm::collapsItemAsTlgElem(CTlgWrapper^ tlg,String^ elemName,int index)
{
  int elemInd = tlg->getElemIndex(elemName);
  int count = tlg->getSubElemCount(elemInd);
  listViewInterConv->BeginUpdate();
  for(int i=0;i<count;i++)
  {
    listViewInterConv->Items->RemoveAt(index+1);
  }
  listViewInterConv->EndUpdate();
}
//-----------------------------------------------------------------------------
void CInterConvertForm::showComboBoxChose()
{
  if(ComboBoxChose->Tag)
  {
    int m_left;
    System::Drawing::Rectangle rect;
    ListViewItem^ item = safe_cast<ListViewItem^>(ComboBoxChose->Tag);
    String^ tlgName=nullptr;
    String^ elemName=nullptr;
    String^ subElemName=nullptr;

    getTlgElemFromItem(item,tlgName,elemName,subElemName);

    ComboBoxChose->Visible = false;
    rect = item->Bounds;
    m_left=listViewInterConv->Columns[0]->Width;
    ComboBoxChose->Top = rect.Top;
    ComboBoxChose->ItemHeight = rect.Height-6;
   // ComboBoxChose->Width = 100;
    ComboBoxChose->Left = m_left;
    ComboBoxChose->Visible = true;
  }
}
//-----------------------------------------------------------------------------
void CInterConvertForm::setComboBoxItem()
{
  if(ComboBoxChose->Tag != nullptr)
  {
    String^ tlgName=nullptr;
    String^ elemName=nullptr;
    String^ subElemName=nullptr;
    ListViewItem^ item = safe_cast<ListViewItem^>(ComboBoxChose->Tag);
    getTlgElemFromItem(item,tlgName,elemName,subElemName);
    if((elemName == nullptr) && (subElemName == nullptr))
    {
      initComboBoxAsTlg(tlgName);
    }
    else
    {
      initComboBoxAsTlgElem(tlgName,elemName,subElemName);
    }
  }
}
//-----------------------------------------------------------------------------
int CInterConvertForm::getTlgElemFromItem(ListViewItem^ item,String^& tlgName,String^& elemName,String^& subElemName)
{
  value struct ItemStateInfoTyp^ itemInfo=nullptr;
  ListViewItem^ listItem = item;
  bool flag=false;
	int pos1,pos2;
  int ret = 0;
  String^ elem = listItem->SubItems[0]->Text;
  if(elem->IndexOf(" ") != -1)
  {
    flag=true;
    elem=elem->Replace(" ","");
  }
  elem=elem->Replace("-","");
	pos1=elem->IndexOf("(");
	pos2=elem->LastIndexOf(")");
	if((pos1 != -1) && (pos2 != -1) && (pos1 < pos2))
	{
		elem=elem->Remove(pos1,pos2-pos1+1);
	}
  while(listItem->Tag == nullptr)
    listItem = listViewInterConv->Items[listItem->Index-1];  
  itemInfo = safe_cast<value struct ItemStateInfoTyp^>(listItem->Tag);
  if(itemInfo->ElemName == nullptr) // tlg item
  {
    tlgName = itemInfo->TlgName;
    elemName = nullptr;
    subElemName = nullptr;

  }
  else                        // elem item
  {
    if((itemInfo->Extendet) && (flag)) // komplexes Element
    {
      tlgName = itemInfo->TlgName;
      elemName = itemInfo->ElemName;
      subElemName = elem;
    }
    else // einfaches Element;
    {
      tlgName = itemInfo->TlgName;
      elemName = elem;
      subElemName = nullptr;
    }
  }
  return ret;
}
//-----------------------------------------------------------------------------
void CInterConvertForm::initComboBoxAsTlg(String^ sourceTlgName)
{
  String^ assTlgName = nullptr;
  int count;
  CTlgWrapper^ wr = gcnew CTlgWrapper();
  //SourceInter->getFlatTlg(wr,sourceTlgName);
  ComboBoxChose->BeginUpdate();
  ComboBoxChose->Items->Clear();
  assTlgName = InterAssignment->getAssignedTlgName(sourceTlgName);
  if(DestinationInter)
  {
    count=DestinationInter->getTlgCount();
    if(assTlgName == nullptr)
      ComboBoxChose->Items->Add("");
    else
    ComboBoxChose->Items->Add(assTlgName);
    for(int i=0;i<count;i++)
    {
      DestinationInter->getClonedTlg(wr,i+1);
      if(!ComboBoxChose->Items->Contains(wr->getName()))
        ComboBoxChose->Items->Add(wr->getName());
    }
  }
  ComboBoxChose->EndUpdate();
}
//-----------------------------------------------------------------------------
void CInterConvertForm::initComboBoxAsTlgElem(String^ sourceTlg,String^ sourceElem,String^ sourceSubElem)
{
  String^ assTlgName = nullptr;
  String^ assElemName = nullptr;
  String^ assSubElemName = nullptr;
  int count,i;
  int subCount,j;
  String^ destTlgName = findItem(sourceTlg);
  ComboBoxChose->BeginUpdate();
  ComboBoxChose->Items->Clear();
  if((destTlgName != nullptr) && (!destTlgName->Equals("")))
  {
    CTlgWrapper^ wr = gcnew CTlgWrapper();
    DestinationInter->getFlatTlg(wr,destTlgName);
    count = wr->getTlgElemCount();
    for(i=0;i<count;i++)
    {
      subCount = wr->getSubElemCount(i+1);
      assElemName = wr->getElemName(i+1);
      if(subCount == 0)
      {
        ComboBoxChose->Items->Add(assElemName);
      }
      else
      {
        for(j=0;j<subCount;j++)
        {
            assSubElemName = wr->getSubElemName(i+1,j+1);
            ComboBoxChose->Items->Add(String::Concat(assElemName,"\\",assSubElemName));
        }
      }
    }
  }
  ComboBoxChose->EndUpdate();
}
//-----------------------------------------------------------------------------
String^ CInterConvertForm::findItem(String^ name)
{
  String^ ret = nullptr;
  int count = listViewInterConv->Items->Count;
  bool flag = false;
  int i=0;
  ListViewItem^ item=nullptr;
  while((!flag) && (i<count))
  {
    item = listViewInterConv->Items[i];
    if(name->Equals(item->SubItems[0]->Text))
    {
      ret = item->SubItems[1]->Text;
      flag = true;
    }
    else
    {
      i++;
    }
  }
  return ret;
}
//-----------------------------------------------------------------------------
bool CInterConvertForm::isSimpleTlgElem(String^ tlgName,String^ elemName)
{
  bool ret = true;
  CTlgWrapper^ wr = gcnew CTlgWrapper();
  SourceInter->getFlatTlg(wr,tlgName);
  if(wr->getSubElemCount(wr->getElemIndex(elemName)) > 0)
    ret = false;
  return ret;
}
//-----------------------------------------------------------------------------
CInterAssignment^ CInterConvertForm::getInterAssignment()
{
  return InterAssignment;
}
//-----------------------------------------------------------------------------
void CInterConvertForm::clearAssignment()
{
  if(InterAssignment != nullptr)
  {
    InterAssignment->clearAssignment();
    updateView();
  }
}
//-----------------------------------------------------------------------------