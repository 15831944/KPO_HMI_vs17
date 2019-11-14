#include "StdAfx.h"
#include "CArrayViewConfigForm.h"
//--------------------------------------------------
using namespace simulator;
//--------------------------------------------------
System::Void CArrayViewConfigForm::OnSelIndexChange(System::Object ^  sender, System::EventArgs ^  e)
{
  int index = listBxArrElem->SelectedIndex;
  InterfaceInfo^ interIn = safe_cast<InterfaceInfo^>(InterInfo[index]);
  labCount->Text = System::Convert::ToString(interIn->Count);
  labTyp->Text = interIn->Typ;
  labDescr->Text = interIn->Descr;
  labTel->Text = interIn->Tel;
  labRowCount->Text = System::Convert::ToString(interIn->RowNameArray->Count);

  showRowDetailInfo();   
}
//----------------------------------------------------------------------------------------
System::Void CArrayViewConfigForm::OnButAddClick(System::Object ^  sender, System::EventArgs ^  e)
{
  bool flag;
  int count,i;
  int index;

  //if(listBxArrElem->Focused)
  //{
  count = listViewDetailInfo->Items->Count;
  flag = false;
  i=0;
  while((!flag) && (i<count))
  {
    if(listViewDetailInfo->Items[i]->Selected)
      flag = true;
    else
      i++;
  }
  if(flag)
    index = i+1;
  else
    index = count;

  listViewDetailInfo->BeginUpdate();
  listViewDetailInfo->Items->Insert(index,"Not Name");
  listViewDetailInfo->EndUpdate();
 // }
}
//-----------------------------------------------------------------------------------------
System::Void CArrayViewConfigForm::OnButRemoteClick(System::Object ^  sender, System::EventArgs ^  e)
{
  bool flag;
  int count,i;
  int index;
  String^ elemName=nullptr;

  //if(listBxArrElem->Focused)
  //{
  count = listViewDetailInfo->Items->Count;
  flag = false;
  i=0;
  while((!flag) && (i<count))
  {
    if(listViewDetailInfo->Items[i]->Selected)
      flag = true;
    else
      i++;
  }
  if(flag)
  {
    listViewDetailInfo->Items->RemoveAt(i);
    index=listBxArrElem->SelectedIndex;
    elemName=listBxArrElem->Items[index]->ToString();
    removeRow(elemName,i);
  }
  //}
}
//-----------------------------------------------------------------------------------------
System::Void CArrayViewConfigForm::OnListViewLeave(System::Object ^  sender, System::EventArgs ^  e)
{
  int index,count,i;
  //String^ nameArray[];
  index = listBxArrElem->SelectedIndex;
  InterfaceInfo^ interIn = safe_cast<InterfaceInfo^>(InterInfo[index]);
    
  count = listViewDetailInfo->Items->Count;
  //nameArray = new String^[count];
  interIn->RowNameArray->Clear();
  for(i=0;i<count;i++)
  {
    interIn->RowNameArray->Add(listViewDetailInfo->Items[i]->SubItems[0]->Text);
    //nameArray[i]=listViewDetailInfo->Items[i)->SubItems[0)->Text;
  }
  //interIn->RowNameArray = nameArray;
}
//--------------------------------------------------
void CArrayViewConfigForm::setInterface(CTlgInterfaceWrapper^ inter)
{
  Interface = inter;
  updateViewFromConfFile();   
}
//--------------------------------------------------
void CArrayViewConfigForm::updateViewFromConfFile()
{
  bool flag;
  flag = readInterInfoFromConfFile();
  showInterInfo();
  if(listBxArrElem->Items->Count > 0)
    listBxArrElem->SelectedIndex = 0;
}
//--------------------------------------------------
bool CArrayViewConfigForm::readInterInfoFromConfFile()
{
  bool ret=true;
  int count,i;
  array <String^>^ elemIt;
  String^ elemName = nullptr;
  String^ telName = nullptr;
  String^ elemCount = nullptr;
  CAppSetting^ Sett = CAppSetting::getApp();
  String^ confPath = Sett->getInterConfigFilePath(Interface->getInterfaceName());
  CXmlInterConfigReader^ confFileReader = gcnew CXmlInterConfigReader();
  confFileReader->setInterConfigFile(confPath);
  ret = confFileReader->setSectionFocus("ArrayView");
  InterInfo->Clear();
  if(ret)
  {
    int index;
    CItemWrapper^ tlgWr = gcnew CTlgWrapper();
    while((elemIt=confFileReader->getNextArrayElemInfo(elemName,telName,elemCount)) != nullptr)
    {
      InterfaceInfo^ inInfo = gcnew InterfaceInfo;

      inInfo->Count = System::Convert::ToInt32(elemCount);
      inInfo->Tel = telName;
      inInfo->ElemName = elemName;
      inInfo->RowNameArray = gcnew ArrayList();
      count=elemIt->Length;
      for(i=0;i<count;i++)
      {
        inInfo->RowNameArray->Add(elemIt[i]);
      }
      //inInfo->RowNameArray = elemIt;
      
      Interface->getFlatTlg(tlgWr,telName);
      /*index=tlgWr->getElemIndex(elemName);
      inInfo->Descr = tlgWr->getElemDescr(index);
      inInfo->Typ = tlgWr->getSubElemTypAsString(index,1);*/
      
      InterInfo->Add(inInfo);
    }
  }
  return ret;
}
//--------------------------------------------------
void CArrayViewConfigForm::showInterInfo()
{
  int count,i;
  InterfaceInfo^ interIn = nullptr;
  listBxArrElem->Items->Clear();
  listBxArrElem->BeginUpdate();

  count = InterInfo->Count;
  for(i=0;i<count;i++)
  {
    interIn = safe_cast<InterfaceInfo^>(InterInfo[i]);
    listBxArrElem->Items->Add(interIn->ElemName);
  }
  listBxArrElem->EndUpdate();
}
//--------------------------------------------------
void CArrayViewConfigForm::showRowDetailInfo()
{
  int count,i;
  int index;
  InterfaceInfo^ interIn = nullptr;
  index = listBxArrElem->SelectedIndex;
  String^ nameRow = nullptr;
  interIn = safe_cast<InterfaceInfo^>(InterInfo[index]);
  count = interIn->RowNameArray->Count;
  listViewDetailInfo->BeginUpdate();
  listViewDetailInfo->Items->Clear();
  for(i=0;i<count;i++)
  {
    nameRow = safe_cast<String^>(interIn->RowNameArray[i]);
    if((nameRow == nullptr) || (nameRow->Equals("")) || (nameRow->Equals(" ")))
        nameRow = "Not Name";
    listViewDetailInfo->Items->Add(nameRow,100);
  }
  listViewDetailInfo->EndUpdate();
}
//--------------------------------------------------
void CArrayViewConfigForm::updateConfFileFromView()
{
  String^ elemName = nullptr;
  String^ telName = nullptr;
  String^ elemCount = nullptr;
  array <String^>^ nameRow;
  InterfaceInfo^ interIn = nullptr;
  int count,i;
  int count1,j;
  CAppSetting^ Sett = CAppSetting::getApp();
  String^ path = Sett->getInterConfigFilePath(Interface->getInterfaceName());
  CXmlInterConfigWriter^ interConfWr = gcnew CXmlInterConfigWriter();
  interConfWr->loadInterConfigFile(path);
  interConfWr->setSectionFocus("ArrayView");
  interConfWr->beginUpdate();
  count = InterInfo->Count;
  for(i=0;i<count;i++)
  {
    interIn = safe_cast<InterfaceInfo^>(InterInfo[i]);
    elemCount = System::Convert::ToString(interIn->Count);
    telName = interIn->Tel;
    elemName = interIn->ElemName;
    count1=interIn->RowNameArray->Count;
    nameRow=gcnew array <String^> (count1);
    for(j=0;j<count1;j++)
    {
      nameRow[j]=safe_cast<String^>(interIn->RowNameArray[j]);
    }
    //nameRow = interIn->RowNameArray;
    interConfWr->addArrayRow(elemName,telName,elemCount,nameRow);
  }
  interConfWr->endUpdate();
}
//--------------------------------------------------
void CArrayViewConfigForm::removeRow(String^ elemName,int index)
{
  int count,i;
  bool flag;
  InterfaceInfo^ interInfo=nullptr;
  //String^ itemArray[];
  count=InterInfo->Count;
  flag=false;
  i=0;
  while((!flag) && (i<count))
  {
    interInfo=safe_cast<InterfaceInfo^>(InterInfo[i]);
    if(elemName->Equals(interInfo->ElemName))
    {
      flag=true;
      interInfo->RowNameArray->RemoveAt(index);
    }
    else
    {
      i++;
    }
  }
}
//--------------------------------------------------
