#include "StdAfx.h"
#include "CTlgContainerFindForm.h"
#include "CTlgWrapper.h"
//-------------------------------------------------------------------------
using namespace simulator;
#undef MessageBox
//-------------------------------------------------------------------------
System::Void CTlgContainerFindForm::OnLoadForm(System::Object ^  sender, System::EventArgs ^  e)
{
  comBxRelation->SelectedIndex=0;
  //initInterfaceTlg();
}
//-------------------------------------------------------------------------
System::Void CTlgContainerFindForm::OnFindButtonClick(System::Object ^  sender, System::EventArgs ^  e)
{
	int pos;
	PosInContainer++;
  if(comBxelem->Text->Equals(""))
	{
		pos=ContainerToFind->findTelegramm(PosInContainer,comBxAllTlg->Text);
		PosInContainer=pos;
	}
	else
	{
		pos=ContainerToFind->findTelegramm(PosInContainer,comBxAllTlg->Text,comBxelem->Text,comBxRelation->Text,txtBxVal->Text);
		PosInContainer=pos;
	}
  if(pos == 0)
  {
      System::Windows::Forms::MessageBox::Show(nullptr,"Telegram not found","");
  }
	if(EventDownOk)
		EventDownOk->Invoke(pos);
}
//-------------------------------------------------------------------------
System::Void CTlgContainerFindForm::OnCloseButtonClick(System::Object ^  sender, System::EventArgs ^  e)
{
   Close();
}
//-------------------------------------------------------------------------
System::Void CTlgContainerFindForm::OnSelectedIndexChange(System::Object ^  sender, System::EventArgs ^  e)
{
  int count,i;
  int subElemCount,j;
  CItemWrapper^ wr = gcnew CTlgWrapper();
  String^ tlgName=nullptr;
  String^ elemName=nullptr;
  String^ subElemName=nullptr;
  tlgName=comBxAllTlg->Text;
  if(InterfaceTlgFlag)
    Interface->getFlatTlg(wr,tlgName);
  else
	  ContainerToFind->getClonedTlg(wr,tlgName);
  comBxelem->Items->Clear();
  comBxelem->Items->Add("");
  count = wr->getTlgElemCount();
  for(i=1;i<=count;i++)
  {
    elemName=wr->getElemName(i);
    subElemCount=wr->getSubElemCount(i);
    if(subElemCount > 0)
    {
      for(j=1;j<subElemCount;j++)
      {
        subElemName=wr->getSubElemName(i,j);
        comBxelem->Items->Add(String::Concat(elemName,"\\",subElemName));
      }
    }
    else
    {
        comBxelem->Items->Add(elemName);
    }
  }
  comBxelem->SelectedIndex=0;
}
//-------------------------------------------------------------------------
void CTlgContainerFindForm::setInterface(CTlgInterfaceWrapper^ inter)
{
  this->Interface = inter;
  //initInterfaceTlg();
}
//-------------------------------------------------------------------------
/*void CTlgContainerFindForm::initInterfaceTlg()
{
    //String^ tlgName=0;
    int count,i,j;
    CItemWrapper^ wr = gcnew CTlgWrapper();
    comBxAllTlg->Items->Clear();
    count=Interface->getTlgCount();
    for(i=1;i<=count;i++)
    {
      Interface->getTlg(wr,i);
      comBxAllTlg->Items->Add(wr->getName());
       //wr->getName();
    }
    comBxAllTlg->SelectedIndex = 0;
}*/
//-------------------------------------------------------------------------
String^ CTlgContainerFindForm::getTel()
{
	return comBxAllTlg->Text;
}
//-------------------------------------------------------------------------
String^ CTlgContainerFindForm::getElem()
{
	return comBxelem->Text;
}
//--------------------------------------------------------------------------
String^ CTlgContainerFindForm::getRelation()
{
	return comBxRelation->Text;
}
//--------------------------------------------------------------------------
String^ CTlgContainerFindForm::getValue()
{
	return txtBxVal->Text;
}
//-------------------------------------------------------------------------
void CTlgContainerFindForm::setOkDownEvent(EventDownOkTyp^ event)
{
	EventDownOk = event;
}
//-------------------------------------------------------------------------
void CTlgContainerFindForm::setContainerToFind(CItemBaseContainerWrapper^ con)
{
	ContainerToFind=con;
	PosInContainer=0;
}
//-------------------------------------------------------------------------
void CTlgContainerFindForm::initTlgFromInterface()
{
    int count,i;
    CItemWrapper^ wr = gcnew CTlgWrapper();
    InterfaceTlgFlag=true;
    comBxAllTlg->Items->Clear();
    if(Interface)
    {
      count=Interface->getTlgCount();
      for(i=1;i<=count;i++)
      {
        Interface->getClonedTlg(wr,i);
        comBxAllTlg->Items->Add(wr->getName());
       //wr->getName();
      }
      comBxAllTlg->SelectedIndex = 0;
    }
}
//-------------------------------------------------------------------------
void CTlgContainerFindForm::initTlgFromContainer()
{
    int count,i;
    String^ itemStr=nullptr;
    CItemWrapper^ wr = gcnew CTlgWrapper();
    InterfaceTlgFlag=false;
    comBxAllTlg->Items->Clear();
    if(ContainerToFind)
    {
        count=ContainerToFind->getTlgCount();
        for(i=1;i<=count;i++)
        {
          ContainerToFind->getClonedTlg(wr,i);
          itemStr=wr->getName();
          if(!comBxAllTlg->Items->Contains(itemStr))
          {
            comBxAllTlg->Items->Add(itemStr);
          }
        }
       comBxAllTlg->SelectedIndex = 0;
    }

}
//-------------------------------------------------------------------------