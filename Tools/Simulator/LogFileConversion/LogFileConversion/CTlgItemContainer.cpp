#include "stdafx.h"
#include "CTlgItemContainer.h"

//----------------------------------------------
CTlgItemContainer::CTlgItemContainer(String^ tlgBody,CTlgAssignment^ tlgAss,CTlgWrapper^ wrSource,CTlgWrapper^ wrDest)
{
  this->TlgName=tlgAss->getSourceTlgName();
  this->DestTlgName=tlgAss->getDestTlgName();
  ItemList = gcnew ArrayList();
  intiTlgItem(tlgBody,tlgAss,wrDest,wrSource);
}
//----------------------------------------------
CTlgItemContainer::~CTlgItemContainer()
{
}
//----------------------------------------------
String^ CTlgItemContainer::getTlgLine()
{
  String^ ret = nullptr;
  int count,i;

  count = ItemList->Count;
  for(i=0;i<count;i++)
  {
    ret = String::Concat(ret,System::Convert::ToString(ItemList[i]),"|");
  }
  return ret;
}
//----------------------------------------------
void CTlgItemContainer::intiTlgItem(String^ tlgBody,CTlgAssignment^ tlgAss,CTlgWrapper^ wrDest,CTlgWrapper^ wrSource)
{   
  array <String^>^ arrItem = nullptr;
  int countElem,i;
  int countSubElem,j;
  //int destElem,destSubElem;
  int sourceElem,sourceSubElem;
  int pos;

  ItemList->Clear();
  arrItem = tlgBodyParser(tlgBody);
  countElem = wrDest->getTlgElemCount();
  for(i=1;i<=countElem;i++)
  {
    countSubElem = wrDest->getSubElemCount(i);
    if(countSubElem == 0)
    {
      tlgAss->getSourceTlgElem(i,0,sourceElem,sourceSubElem);
      if(sourceElem == 0)
      {
        ItemList->Add("");
      }
      else
      {
        pos = wrSource->getElemNummber(sourceElem,sourceSubElem);
        if(arrItem->Length > pos)
        {
            ItemList->Add(arrItem[pos-1]);
        }
        else
        {
            ItemList->Add("");
        }
      }
    }
    else
    {
      //countSubElem = wr->getSubElemCount(i);
      for(j=1;j<=countSubElem;j++)
      {
        tlgAss->getSourceTlgElem(i,j,sourceElem,sourceSubElem);
        if(sourceElem == 0)
        {
          ItemList->Add("");
        }
        else
        {
          pos = wrSource->getElemNummber(sourceElem,sourceSubElem);
          if(arrItem->Length > pos)
          {
            ItemList->Add(arrItem[pos-1]);
          }
          else
          {
            ItemList->Add("");
          }
        }
      }
    }
  }
  //tlgAss->get
}
//----------------------------------------------
array <String^>^ CTlgItemContainer::tlgBodyParser(String^ line)
{
  array <String^>^ ret = nullptr;
  String^ delStr = "|";
  array <Char>^ delCharArray = delStr->ToCharArray();
  ret = line->Split(delCharArray);
  return ret;
}
//----------------------------------------------
String^ CTlgItemContainer::getDestTlgName()
{
  return DestTlgName;
}
//----------------------------------------------