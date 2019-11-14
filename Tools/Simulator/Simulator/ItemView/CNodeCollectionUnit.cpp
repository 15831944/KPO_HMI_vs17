#include "StdAfx.h"
#include "CNodeCollectionUnit.h"
#include "CItemWrapper.h"
#include "CTlgElemWrapper.h"
#include "CTlgElem.h"
#include "CInterConfigWrapper.h"

//---------------------------------------------
int CNodeCollectionUnit::getAllNodesCount()
{
  return m_allNodes->Count;
}
//---------------------------------------------
CNodeCollectionUnit::CNodeCollectionUnit(CommonTools::NodeCollection^ collection)
{
	/*m_allNodes = new System::Collections::ArrayList();
	m_leafNodes = new System::Collections::ArrayList();*/
	
  m_allNodes = gcnew System::Collections::Generic::List <CommonTools::Node^>();
  m_leafNodes = gcnew System::Collections::Generic::List <CommonTools::Node^>();
  
  /*System::Collections::Generic::List<CommonTools::Node*>* m_allNodes;
  System::Collections::Generic::List<CommonTools::Node*>* m_leafNodes;new List<CommonTools.Node>();*/
  
  m_maxDepth = 8;
	m_collection = collection;
	itemCount=0;
  isItemEmpty=false;
  //Interface Einstelungen - Werten
  ItemId = nullptr;
  ItemElemId = nullptr;
  ItemLenId = nullptr;
  ItemIdValue = nullptr;
  LenIdModus = 0; 
  maxDesc ="";
  ElemValue = nullptr;
  //
  isIdTxtEnabled = true;
  isLenTxtEnabled = false;
  LenChange = false;
}
//---------------------------------------------
bool CNodeCollectionUnit::getisIdTxtEnabled()
{
  return this->isIdTxtEnabled;
}
//---------------------------------------------

bool CNodeCollectionUnit::getisLenTxtEnabled()
{
  return this->isLenTxtEnabled;
}
void CNodeCollectionUnit::clear()
{
	this->clearAllAtributte();
	this->m_collection->Clear();
	this->m_allNodes->Clear();
}
//---------------------------------------------
void CNodeCollectionUnit::clearAllAtributte()
{
  typ = 5;
  Item=nullptr;
  itemCount=0;
  isItemEmpty=false;
  //Interface Einstelungen - Werten
  ItemId = nullptr;
  ItemElemId = nullptr;
  ItemLenId = nullptr;
  ItemIdValue = nullptr;
  LenIdModus = 0; 
  maxDesc ="";
  ElemValue = nullptr;
  //
  isIdTxtEnabled = true;
  isLenTxtEnabled = false;
  LenChange = false;
}
//---------------------------------------------
CNodeCollectionUnit::~CNodeCollectionUnit(void)
{
	 
}
//---------------------------------------------
int CNodeCollectionUnit::ShowItem(CItemWrapper^ item,int typ)
{
  int ret = 0;
  int tmpRet=0;
  //Item Ansicht leeren
  m_collection->Clear();
  clearAllAtributte();
  this->typ = typ;
  Item = item;
  //Wenn es eine leere Tellegramm ist (Prototyp)
  isItemEmpty=item->getTlgEmpty();
  //Name der Inteface
  String^ interfaceName = item->getInterfece();
  //Interface Konfiguration
  CInterConfigWrapper^ interConf = gcnew CInterConfigWrapper();
  //Einige Einstellungen aus Interface - Konfigutiuion
  ItemId = interConf->getTlgIdName(interfaceName);
  ItemElemId = interConf->getElemId(interfaceName);
  ItemLenId = interConf->getElemLenId(interfaceName);
  LenIdModus = interConf->getLenIdTreatModus(interfaceName);
  ItemIdValue=interConf->getTlgId(interfaceName,item->getName());
  //Hilfsvariablen
  int nextId = 0;
  CommonTools::Node^ node=nullptr;
  CTlgElemWrapper^ itemElem=nullptr;
  int rootItemCount = item->getTlgElemCount();
	itemCount = rootItemCount;
  //Ein Schleife iteriert zwischen Root - Elementen und ruft
  //ggf. Rekursiv - Methode fuer SubElementen aufgerufen
  for (int index = 1; index<=rootItemCount; index++) 
  {
    itemElem = gcnew CTlgElemWrapper();
    itemElem->setTlgElem(item->getElem(index)); 
    
    String^ test = itemElem->getElemName();
    
    array <System::Object^>^ obj = gcnew array <System::Object^>(10);
    obj[0] = itemElem->getElemName();
    if (itemElem->getSubElemCount() == 0)
      fillElemValue(itemElem,obj);
		
    node = gcnew CommonTools::Node(obj);
    
    if (itemElem->getSubElemCount() == 0)
      node->Tag = itemElem;
    else
      node->Tag = nullptr;

    m_collection->Add(node);
    m_allNodes->Add(node);
    //Elemente des Items
    if (itemElem->getSubElemCount() > 0)
    {
      tmpRet = buildElemNodes (itemElem,node);
      if (tmpRet > ret)
        ret = tmpRet;
    }
    node->ExpandAll();
  }
  return ret+1;
}
//---------------------------------------------
void CNodeCollectionUnit::fillElemValue(CTlgElemWrapper^ itemElem,array <System::Object^>^ obj)
{
  String^ value=nullptr;
  String^ unit=nullptr;
  String^ factor=nullptr;
  String^ max=nullptr;
  String^ min=nullptr;
  String^ type=nullptr;
  int len=0;
  String^ tran=nullptr;
  String^ tmpValue = nullptr;

  /* obj[0] = itemElem->getElemName();*/
  if (itemElem->getSubElemCount()==0)
  {
    //Element Wert 1
    if(itemElem->getElemName()->Equals(ItemElemId))
    {
      //Wenn Prototyp
      if (typ == 1)
      {
        obj[1] = ItemIdValue;
      }
      else //Wenn Logfile,Szenario oder Receiver
      {
        itemElem->getElemValue(value);
        obj[1] = value;
        value = nullptr;  
      }
      
      isIdTxtEnabled = false;
    }
    else if (itemElem->getElemName()->Equals(ItemLenId))
    {
        if(LenIdModus == 1)
        {
          isLenTxtEnabled = false;
          //Wenn Prototyp
          if (typ == 1)
            obj[1] = System::Convert::ToString(Item->getTlgTransBytesCount());
          else
          {
            itemElem->getElemValue(value);
            if (value)
              obj[1]= value;
          }
        }
        else if(LenIdModus == 2)
        {
          isLenTxtEnabled = false;
          //Wenn Prototyp
          if (typ == 1)
            obj[1] = System::Convert::ToString(Item->getTlgBodyTransBytesCount());
          else
          {
            itemElem->getElemValue(value);
            if (value)
              obj[1]= value;
          }
        }
        else if(LenIdModus == 3)
        {
          isLenTxtEnabled = true;
          itemElem->getElemValue(value);
          if (value)
            obj[1]= value;
        }
        
        if (typ == 1 && LenIdModus !=3)
        {
          itemElem->setValue(safe_cast <System::String^> (obj[1]),this->Item->getName());
        }
    }
    else
    {
      if (typ == 1)
      {
        obj[1]="";
      }
      else
      {
        itemElem->getElemValue(value);
        if (value)
          obj[1]= value;
      }
    }

    tmpValue = safe_cast <String^> (obj[1]);
    if (ElemValue == nullptr || tmpValue->Length > ElemValue->Length)
      ElemValue = tmpValue;

    //Element Wert 3
    type=itemElem->getElemType();
    if (type)
    {
      obj[3] = type;
    }
    //Element Wert 4
    len = itemElem->getElemLenght();
    if (len)
    {
      obj[4] = len;
    }
    //Element Wert 5
    tran=itemElem->getElemTransport();
    if (tran)
    {
      obj[5] = tran;
    }
    //Element Wert 2
    itemElem->getElemInfo(unit,factor,min,max);
    if (unit)
    {
      obj[2]=unit;
    }
    //Element Wert 6
    if (factor)
    {
      obj[6]=factor;
    }
    //Element Wert 7
    if (min)
    {
      obj[7]=min;
    }
    //Element Wert 8
    if (max)
    {
      obj[8]=max;
    }
    //Element Wert 9
    obj[9]=itemElem->getElemDescription();
    if (itemElem->getElemDescription()->Length > maxDesc->Length)
      maxDesc = itemElem->getElemDescription();
  }
}

/*
if(itemElem->getElemName()->Equals(ItemLenId))
    {
      if(!LenChange)
      {
        if(LenIdModus == 1)
        {
          isLenTxtEnabled = false;
          obj[4] = System::Convert::ToString(Item->getTlgTransBytesCount());
        }
        if(LenIdModus == 2)
        {
          isLenTxtEnabled = false;
          obj[4] = System::Convert::ToString(Item->getTlgBodyTransBytesCount());
        }
        if(LenIdModus == 3)
        {
          isLenTxtEnabled = true;
        }
      }
      else
      {
        isLenTxtEnabled = true;
      }
    }
    else
    {
      len=itemElem->getElemLenght();
      obj[4] = __box (len);
    }

*/



//-------------------------------------------------------
int CNodeCollectionUnit::buildElemNodes (CTlgElemWrapper^ elem,CommonTools::Node^ node)
{
  int maxDeath = 0;
  int tmpDeath;
  CommonTools::Node^ subNode; 
  CTlgElemWrapper^ subElem = nullptr;
	itemCount += elem->getSubElemCount();
  array <System::Object^>^ obj = gcnew array <System::Object^> (10);
  for (int i = 1;i<=elem->getSubElemCount();i++)
  {
    subElem = gcnew CTlgElemWrapper();
    subElem->setTlgElem(elem->getSubElem(i)); 

    obj[0] = subElem->getElemName();
    if (subElem->getSubElemCount()==0)
      fillElemValue(subElem,obj);
    
    subNode = gcnew CommonTools::Node(obj);

    String^ a = subElem->getElemName();

    if (subElem->getSubElemCount()==0)
      subNode->Tag = subElem;
    else
      subNode->Tag = nullptr;

    node->Nodes->Add(subNode);

    if (subElem->getSubElemCount()>0)
    {
      tmpDeath = buildElemNodes(subElem,subNode);
      if (tmpDeath > maxDeath)
        maxDeath = tmpDeath;
    }
  }
  return maxDeath + 1;
}
//-----------------------------------------------------------
int CNodeCollectionUnit::getItemCount()
{
	return itemCount;
}
//-----------------------------------------------------------
String^ CNodeCollectionUnit::getMaxDescription()
{
  return maxDesc;
}
//------------------------------------------------------------
String^ CNodeCollectionUnit::getElemValue()
{
  return ElemValue;
}
  