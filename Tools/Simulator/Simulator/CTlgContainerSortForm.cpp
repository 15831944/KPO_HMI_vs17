#include "StdAfx.h"
#include "CTlgContainerSortForm.h"
#include "CTlgElemWrapper.h"
#include "CTlgElem.h"
//-------------------------------------------------------------------
using namespace simulator;
//-------------------------------------------------------------------
System::Void CTlgContainerSortForm::buttDown_Click(System::Object^  sender, System::EventArgs^  e) 
{
  int index = listViewSort->SelectedItems[0]->Index;

  //Wenn markierte Item nicht die letzte ist.
  if (index < (listViewSort->Items->Count-1))
  {
    String^ tlgName1=listViewSort->Items[index]->Text;
	  String^ elemNamePath1=listViewSort->Items[index]->SubItems[1]->Text;
    String^ elemTyp1 = listViewSort->Items[index]->SubItems[2]->Text; 

    listViewSort->Items[index]->Text = listViewSort->Items[index + 1]->Text; 
	  listViewSort->Items[index]->SubItems[1]->Text = listViewSort->Items[index + 1]->SubItems[1]->Text; 
    listViewSort->Items[index]->SubItems[2]->Text = listViewSort->Items[index +1]->SubItems[2]->Text;  

    listViewSort->Items[index + 1]->Text = tlgName1;
    listViewSort->Items[index + 1]->SubItems[1]->Text = elemNamePath1;
    listViewSort->Items[index+1]->SubItems[2]->Text = elemTyp1;
  }
}
//-------------------------------------------------------------------
System::Void CTlgContainerSortForm::buttUp_Click(System::Object^  sender, System::EventArgs^  e) 
{
  int index = listViewSort->SelectedItems[0]->Index;

  //Wenn markierte Item nicht die erste ist.
  if (index > 0)
  {
    String^ tlgName1=listViewSort->Items[index]->Text;
	  String^ elemNamePath1=listViewSort->Items[index]->SubItems[1]->Text;
    String^ elemTyp1 = listViewSort->Items[index]->SubItems[2]->Text; 

    listViewSort->Items[index]->Text = listViewSort->Items[index - 1]->Text; 
	  listViewSort->Items[index]->SubItems[1]->Text = listViewSort->Items[index - 1]->SubItems[1]->Text; 
    listViewSort->Items[index]->SubItems[2]->Text = listViewSort->Items[index - 1]->SubItems[2]->Text;  

    listViewSort->Items[index - 1]->Text = tlgName1;
    listViewSort->Items[index - 1]->SubItems[1]->Text = elemNamePath1;
    listViewSort->Items[index - 1]->SubItems[2]->Text = elemTyp1;
  }

}
//-------------------------------------------------------------------
System::Void CTlgContainerSortForm::OnComBxTelSelectedIndexChanged(System::Object ^  sender, System::EventArgs ^  e)
{
    int count;
    int subCount;
    String^ tlgName=nullptr;
    String^ elemName=nullptr;
    String^ subElemName=nullptr;
    String^ typ=nullptr;
    //Tlg Prototyp anhand der Name aus dem virtuellen Container holen
    CTlgWrapper^ tlg=gcnew CTlgWrapper();
    tlgName=comBxTel->Text;
    Container->getClonedVirtualTlg(tlg,tlgName);
    //Description
    label3->Text = tlg->getTlgDescr();
    
    //Elemente des Telegramms
    comBxTelElem->Items->Clear();
    //Anzahl der Root Elementen
    count=tlg->getTlgElemCount();
    for(int i=1;i<=count;i++)
    {
        subCount=tlg->getSubElemCount(i);
        elemName=tlg->getElemName(i);
        //Wenn keine weiteren SubElementen exist.
        if(subCount == 0)
        {
            typ=tlg->getElemTypAsString(i);
            if(typ->Equals("Integer") || typ->Equals("Double"))
                comBxTelElem->Items->Add(elemName);
        }
        //sonst
        else
        {
          CTlgElemWrapper^ subElem = gcnew CTlgElemWrapper();   
          subElem->setTlgElem(tlg->getElem(i));
          addSubElemNameToComBx(subElem,elemName);
          
            /*subCount=tlg->getSubElemCount(i);
            for(j=1;j<=subCount;j++)
            {
                subElemName=tlg->getSubElemName(i,j);
                typ=tlg->getSubElemTypAsString(i,j);
                if(typ->Equals("Integer") || typ->Equals("Double"))
                {
                    elemName = String::Concat(elemName,"\\",subElemName);
                    comBxTelElem->Items->Add(elemName);
                }
            }*/
        }
        
    }
    comBxTelElem->SelectedIndex=0;
}
//-------------------------------------------------------------------
void CTlgContainerSortForm::addSubElemNameToComBx(CTlgElemWrapper^ elem,String^ text)
{
  
  String^ elemName = elem->getElemName();
  String^ elemTyp = elem->getElemType();
  
  //text = String::Concat(text,"\\",elemName);

  if (elem->getSubElemCount() == 0)
  {
    if(elemTyp ->Equals("Integer") || elemTyp ->Equals("Double"))
    {
      comBxTelElem->Items->Add(text);
    }
  }
  else
  {
    //
    CTlgElemWrapper^ subElem = gcnew CTlgElemWrapper(); 
    for (int i=1;i<=elem->getSubElemCount();i++)
    {
      subElem->setTlgElem(elem->getSubElem(i));
      addSubElemNameToComBx(subElem,String::Concat(text,"\\",subElem->getElemName()));
    }
  }
}
//-------------------------------------------------------------------
System::Void CTlgContainerSortForm::OnComBxTlgElemSelectIndexChanged(System::Object ^  sender, System::EventArgs ^  e)
{
    String^ tlgName=nullptr;
    String^ elemName=nullptr;
    String^ subElemName=nullptr;
    int pos=-1;
    //int index;

    CTlgWrapper^ wr = gcnew CTlgWrapper();
    tlgName=comBxTel->Text;
    elemName=comBxTelElem->Text;
    Container->getClonedVirtualTlg(wr,tlgName);

    CTlgElem* elemStd = wr->getTlgElem(elemName);
    if (elemStd)
    {
      CTlgElemWrapper^ elem = gcnew CTlgElemWrapper();
      elem->setTlgElem(elemStd);
      label2->Text = elem->getElemDescription();
    }
    /*pos=elemName->IndexOf("\\");
    if(pos != -1)
    {
        subElemName = elemName->Substring(pos+1,elemName->Length-pos-1);
        elemName = elemName->Substring(0,pos);
    }
    Container->getClonedVirtualTlg(wr,tlgName);
    if(subElemName)
    {
         index=wr->getElemIndex(elemName);
         //wr->get
    }
    else
    {
        index=wr->getElemIndex(elemName);
        label2->Text = wr->getElemDescr(index);
    }*/
}
//-------------------------------------------------------------------
System::Void CTlgContainerSortForm::OnAddButtonClick(System::Object ^  sender, System::EventArgs ^  e)
{
  String^ tlgName=nullptr;
  String^ elemName=nullptr;
  String^ typ=nullptr;
  int index;
  //bool flag;
  tlgName=comBxTel->Text;
  elemName=comBxTelElem->Text;
  CTlgWrapper^ wr = gcnew CTlgWrapper();
  Container->getClonedVirtualTlg(wr,tlgName);
  
  CTlgElemWrapper^ subElem = gcnew CTlgElemWrapper(); 
  CTlgElem* subElemTemp = wr->getTlgElem(elemName);
  if (subElemTemp)
  {
    subElem->setTlgElem(subElemTemp);
    typ = subElem->getElemType();
  }
  
  //String^ a = test->getElemName();
  //index=wr->getElemIndex(elemName);
  //typ=wr->getElemTypAsString(index);

  if(!isInSortList(tlgName))
  {
	  index=listViewSort->Items->Count;
	  listViewSort->Items->Add(tlgName);
	  listViewSort->Items[index]->SubItems->Add(elemName);
	  listViewSort->Items[index]->SubItems->Add(typ);
  }
  else
  {
	  System::Windows::Forms::MessageBox::Show(nullptr,"Following interface already exists.","Error",System::Windows::Forms::MessageBoxButtons::OK,
		  System::Windows::Forms::MessageBoxIcon::Error);
  }
}
//-------------------------------------------------------------------
System::Void CTlgContainerSortForm::OnRemoveButtonClick(System::Object ^  sender, System::EventArgs ^  e)
{
	if(listViewSort->SelectedItems->Count > 0)
  {
		listViewSort->Items->Remove(listViewSort->SelectedItems[0]);
  }
}
//-------------------------------------------------------------------
System::Void CTlgContainerSortForm::OnSortButtonClick(System::Object ^  sender, System::EventArgs ^  e)
{
	int count,i;
	String^ tlgName=nullptr;
	String^ elemNamePath=nullptr;
  //String^ elemName=0;
	//String^ subElemName=0;
	//int pos;
  ::Cursor::Current = ::Cursors::WaitCursor;
	//set sort Condition
	count=listViewSort->Items->Count;

	for(i=0;i<count;i++)
	{
		tlgName=listViewSort->Items[i]->Text;
		elemNamePath=listViewSort->Items[i]->SubItems[1]->Text;
		//pos = elemName->IndexOf("\\");
		//if(pos != -1)
		//{
		//	elemName = elemName->Substring(0,pos);
		//	subElemName = elemName->Substring(pos+1,elemName->Length - pos -1);
		//}
		//else
		//{
		//	subElemName = 0;
		//}
		/*Container->addSortCondition(tlgName,elemName,subElemName);*/
    Container->addSortCondition(tlgName,elemNamePath);
	}
	//sort container
	Container->sortContainer();
	if(SortedEvent)
		SortedEvent->Invoke();
}
//-------------------------------------------------------------------
System::Void CTlgContainerSortForm::OnClickSortbyTimeButton(System::Object ^  sender, System::EventArgs ^  e)
{
	Container->reset();
	if(SortedEvent)
  {
		SortedEvent->Invoke();
  }
}
//-------------------------------------------------------------------
System::Void CTlgContainerSortForm::OnClickCloseButton(System::Object ^  sender, System::EventArgs ^  e)
{
	Close();
}
//-------------------------------------------------------------------
void CTlgContainerSortForm::setContainerToSort(CItemBaseContainerWrapper^ con)
{
    this->Container = con;
    initTelFromContainer();
}
//-------------------------------------------------------------------
void CTlgContainerSortForm::initTelFromContainer()
{
    int count,i;
    String^ tlgName=nullptr;
    comBxTel->Items->Clear();
    if(Container)
    {   
        CTlgWrapper^ wr = gcnew CTlgWrapper();
        count=Container->getVirtualTlgCount();
        for(i=1;i<=count;i++)
        {
            Container->getClonedVirtualTlg(wr,i);
            tlgName=wr->getName();
            if(!comBxTel->Items->Contains(tlgName))
            {
                comBxTel->Items->Add(tlgName);
            }

        }
    }
}
//-------------------------------------------------------------------
bool CTlgContainerSortForm::isInSortList(String^ tlg)
{
	bool ret=false;
	int i=0;
	int count = listViewSort->Items->Count;
	while((!ret) && (i<count))
	{
		if(listViewSort->Items[i]->Text->Equals(tlg))
		{
			ret=true;
		}
		else
		{
			i++;
		}
	}
	return ret;
}
//-------------------------------------------------------------------
void CTlgContainerSortForm::setSortedEvent(sortedEventTyp^ event)
{
	this->SortedEvent = event;
}
//-------------------------------------------------------------------