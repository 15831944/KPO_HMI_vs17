//	Copyright 2006 SMS - Demag AG

//------------------------------------------------------------------
#include "stdafx.h"
#include "CSzenarium.h"
#include "CInterBaseManager.h"
#include "CFormatConverterWrapper.h"
#include "CCyclicElemTable.h"
#include "CXmlCyclicTlgWriter.h"
#include "CXmlInterConfigReader.h"
#include "CInterConfigWrapper.h"
#include "CCyclicItemContainer.h"
#include "CItemWrapper.h"
#include "CLogWriterWrapper.h"

//-------------------------------------------------------------------
#include <string>
#include "CStdConverter.h"
//-------------------------------------------------------------------
CSzenarium::CSzenarium()
{
  InterCounterTable = gcnew Hashtable();
  ItemArray = gcnew ArrayList();	
  IndexArray = gcnew ArrayList();
  CyclicTable = gcnew Hashtable();
	Name = "Unknow";
  DelayRel = 1.0;
  FocusedItem=0;
  SendItem=0;
  ChangeSzenFlag=false;
	Path=nullptr;
  MessageScenarioDel=nullptr;
  MessageScenSafeProgressDel=nullptr;
  CCyclicItemContainer::getCyclicItemContainer()->addSzenariumPointer(this);
}
//-------------------------------------------------------------------
CSzenarium::~CSzenarium()
{
	ItemArray->Clear();
	IndexArray->Clear();
  CCyclicItemContainer::getCyclicItemContainer()->removeSzenariumPointer();
}
//-------------------------------------------------------------------
void CSzenarium::setDelayRel(double rel)
{
  DelayRel = rel;
}
//-------------------------------------------------------------------
void CSzenarium::calcDelay()
{
  double total = 0.0;
  double lastT2 = 0.0;
  CSzenItem^ item1 = nullptr;
  CSzenItem^ item2 = nullptr;
  int count = ItemArray->Count;
  double t1,t2;

  if(count != 0)
  {
    item1 = getSzenItem(1);
    //item1->setDelay(0.0); //!!!
    t1=item1->getTime(); //Zeit das erste Element des Szenariums

    //if (!item1->getSendStatus())
    //   total+=t1;
    lastT2 = t1;

	  //Berechnung die Verzoegerungszeiten fuer restliche Elemente(von 2 bis count)
    for(int i=2;i<=count;i++)
    {
      item2 = getSzenItem(i);
      t2 = item2->getTime();
      item2->setDelay((t2-t1)*DelayRel);

      item2->setBarredDelay((t2-t1-total)*DelayRel);

      if (!item2->getSendStatus())
         total+= (t2-lastT2);
      
      lastT2 = t2;
    }
  }
}
//-------------------------------------------------------------------
void CSzenarium::calcDelay(double rel)
{
  DelayRel = rel;
  calcDelay();
}
//-------------------------------------------------------------------
void CSzenarium::AddToInterCounterTable(String^ interName)
{
  int count = 1;
  if (InterCounterTable->Contains(interName))
  {
    count = *dynamic_cast <Int32^> (InterCounterTable[interName]);
    InterCounterTable[interName] = ++count;
  }
  else
    InterCounterTable->Add(interName,count);
}
//-------------------------------------------------------------------
bool CSzenarium::TlgsFromInterInSzenario(String^ interName)
{
  if (InterCounterTable->Contains(interName))
    return true;
  return false;
}
//-------------------------------------------------------------------
int CSzenarium::addToSzenarium(CItemWrapper^ tlg,double time)
{
	int count;
	int index;
  bool flag = false;
  int ret = 0;
  //Vergelichen Id Value von Conf
  CInterConfigWrapper^ interConfig = gcnew CInterConfigWrapper();
  CompareConfigIdWithFileId(tlg,interConfig);
  //erzeugen neues Element des Szenarium
	CSzenItem^ item = gcnew CSzenItem(tlg,time);
	
  item->setDelay(0.0);
	count = ItemArray->Count;
	if(count > 0)
	{
		index = getIndex(time,0,count-1);
		addIndex(index,count);
    ret = index+1;
	}
	else
	{
		addIndex(0,0);
    ret = 1;
	}
	ItemArray->Add(item);
  ChangeSzenFlag=true;

  AddToInterCounterTable(item->getInterface());
  if (CCyclicItemContainer::getCyclicItemContainer()->isItemInContainer(tlg))
    item->setIsCyclic(true);
 
	return ret;
}
//-------------------------------------------------------------------
void CSzenarium::addToSzenarium(CItemWrapper^ tlg,int index)
{
	CSzenItem^ item=nullptr;
	int count = ItemArray->Count;
	double t0 = 0.0;
	double t1;

	//berechnung die Zeit fuer neues Szenariumelement
	if((count > 0) && (index > 0))
		t0 = getSzenItem(index)->getTime();
	
	if(index < count)
	{
		t1 = getSzenItem(index+1)->getTime();
		t1 = t0+(t1-t0)/2.0;
	}
	else
	{
		t1=t0+1.0;
	}
 
  //Vergelichen Id Value von Conf
  CInterConfigWrapper^ interConfig = gcnew CInterConfigWrapper();
  CompareConfigIdWithFileId(tlg,interConfig);
  //erzeugen neues Telegrammelement
	item = gcnew CSzenItem(tlg,t1);
	ItemArray->Add(item);
	addIndex(index,ItemArray->Count-1);
	calcDelay();
	ChangeSzenFlag=true;

  AddToInterCounterTable(item->getInterface());
  if (CCyclicItemContainer::getCyclicItemContainer()->isItemInContainer(tlg))
    item->setIsCyclic(true);
}
//-------------------------------------------------------------------
int CSzenarium::addToSzenarium(CSzenItem^ item)
{
  int index;
  CSzenItem^ szenItem=nullptr;
  CItemWrapper^ wr=nullptr;
  double t = item->getTime();
  wr=item->getTlgWrapper();
  index=addToSzenarium(wr,t);
  szenItem=getSzenItem(index);
  szenItem->setBreakPoint(item->getBreakPoint());
  szenItem->setDelay(item->getDelay());
  szenItem->setSendStatus(item->getSendStatus());
  szenItem->setTime(item->getTime());
  if(item->getChangeTimeStatus())
  {
    szenItem->setChangeTime(item->getChangeTime());
  }
  AddToInterCounterTable(item->getInterface());
  szenItem->setIsCyclic(item->getIsCyclic());
  return index;
}
//-------------------------------------------------------------------
void CSzenarium::swapItems(int index1,int index2)
{
  int valToMove,valToReplace,val;
	CSzenItem^ itemToMove=nullptr;
	CSzenItem^ itemToReplace=nullptr;
  CSzenItem^ item=nullptr;
  int temp,i;
	
  //Item, welche verschoben werden muss.
  valToMove=System::Convert::ToInt32(IndexArray[index1-1]);
	itemToMove = safe_cast<CSzenItem^>(ItemArray[valToMove]);
  
  //If down-button
  if (index1 < index2)
  {
    //Zeit berechnen
    if (IndexArray->Count>index2)
    {
      temp=index2;
      valToReplace=System::Convert::ToInt32(IndexArray[index2-1]);
      itemToReplace = safe_cast<CSzenItem^>(ItemArray[valToReplace]);
      
      val=System::Convert::ToInt32(IndexArray[index2]);
      item= safe_cast<CSzenItem^>(ItemArray[val]);
      itemToMove->setTime((item->getTime() + itemToReplace->getTime())/2);
    }
    else
    {
      double summe=0;
      int index=0;
      CSzenItem ^item_1;
      CSzenItem ^item_2;
      
      temp=IndexArray->Count-1; 
   
      if (IndexArray->Count>100)
        index=100;
      else
        index=IndexArray->Count;
      
      for (i=ItemArray->Count-index;i<ItemArray->Count-1;i++)
      {
        item_1= safe_cast<CSzenItem^>(ItemArray[i]);
        item_2= safe_cast<CSzenItem^>(ItemArray[i+1]);
        summe+=item_2->getTime() - item_1->getTime();
      }
      summe/=index-1;
      itemToMove->setTime(getSzenItem(ItemArray->Count)->getTime()+summe);
    }
    //Verschieben
    for (int i=index1-1;i<temp;i++)
    {
      IndexArray[i] = System::Convert::ToInt32(IndexArray[i+1]);
    }
    //Setzen
    IndexArray[index2-1] = valToMove;

    if (index1-1==0)
    {
      CSzenItem^ item_temp=safe_cast<CSzenItem^>(ItemArray[System::Convert::ToInt32(IndexArray[index1-1])]);
      item_temp->setDelay(0.0);
    }
  }
  
  //If up-button
  if (index1 > index2)
  {
    bool first = false;
    valToReplace=System::Convert::ToInt32(IndexArray[index2-1]);
    itemToReplace = safe_cast<CSzenItem^>(ItemArray[valToReplace]);
    //Zeit berechnen
    if (index2>1)
    {
      val=System::Convert::ToInt32(IndexArray[index2-2]);
      item= safe_cast<CSzenItem^>(ItemArray[val]);
      itemToMove->setTime((item->getTime() + itemToReplace->getTime())/2 );
    }
    else
    {
      itemToMove->setTime(getSzenItem(1)->getTime());
      first=true;
      //itemToMove->setTime(itemToMove->getTime()-itemToMove->getDelay());
      itemToMove->setDelay(0.0);
    }
    //Verschieben
    for (int i=index1-1;i>index2-1;i--)
    {
      IndexArray[i] = System::Convert::ToInt32(IndexArray[i-1]);
    }
    //Setzen
    IndexArray[index2-1] = valToMove;
    
    if (first)
    {
      CSzenItem^ item1 = safe_cast<CSzenItem^>(ItemArray[System::Convert::ToInt32(IndexArray[1])]);
      CSzenItem^ item2 = safe_cast<CSzenItem^>(ItemArray[System::Convert::ToInt32(IndexArray[2])]);
      item1->setTime((item2->getTime()+getSzenItem(1)->getTime())/2);
    }
  }
	calcDelay();
  //Ausgabe in Log - Datei
  String^ mess = String::Concat(itemToMove->getItemName()," swapped");
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
																												  __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
	ChangeSzenFlag=true;
}
//-------------------------------------------------------------------
int CSzenarium::getIndex(double time,int unten,int oben)
{
	int ret = -1;
	int index;
	double val;
	CSzenItem^ it = nullptr;

	if(unten == oben)
	{
    it = getSzenItem(unten+1);
    val = it->getTime();
		if(time >= val)
		{
			ret = unten+1;
			//ret=unten;
		}
		else
		{
			//ret=unten-1;
			ret = unten;
		}
	}
	else
	{
		if((oben-unten) == 1)
		{
			it = getSzenItem(oben+1);
			val = it->getTime();
			if(time >= val)
			{
				//ret=oben;
				ret = oben+1;
			}
			else
			{
				it = getSzenItem(unten+1);
				val = it->getTime();
				if(time >= val)
				{
					//ret = unten;
					ret=oben;
				}
				else
				{
					ret=oben-1;
				}
			}
		}
		else
		{
			index = (int)(IndexArray[unten + (oben - unten)/2]);
			it = safe_cast<CSzenItem^>(ItemArray[index]);
			val = it->getTime();
			if(val >= time)
			{
				ret = getIndex(time,unten,unten + (oben - unten)/2);
			}
			else
			{
				ret = getIndex(time,unten + (oben - unten)/2,oben);
			}
		}
	}
  return ret;
}
//-------------------------------------------------------------------
void CSzenarium::addIndex(int index,int value)
{
	IndexArray->Insert(index,value);
}
//-------------------------------------------------------------------
int CSzenarium::updateItem(int index,double delay)
{
  CSzenItem^ item1 = getSzenItem(index);
  CItemWrapper^ tlgWr = item1->getTlgWrapper()->clone();
  double t0,t1;
  double d0;
  int ret = 0;

  remouteAt(index);
	if(ItemArray->Count != 0)
	{
		t0 = getSzenItem(1)->getTime();
		d0 = getSzenItem(1)->getDelay();
		t1 = (delay-d0)/DelayRel + t0;
	}
	else
	{
		t1 = item1->getTime();
	}
	ret = addToSzenarium(tlgWr,t1);
	getSzenItem(ret)->setDelay(delay);
	
  return ret;
}
//-------------------------------------------------------------------
int CSzenarium::getSzenItemCount()
{
  return ItemArray->Count;
}
//-------------------------------------------------------------------
CSzenItem^ CSzenarium::getSzenItem(int pos)
{
	CSzenItem^ item=nullptr;
	int index;

	if((pos > 0) && (pos <= getSzenItemCount()))
	{
		index = System::Convert::ToInt32(IndexArray[pos-1]); 
		item = safe_cast<CSzenItem^>(ItemArray[index]);
		/*test=item->getItemName();*/
	}

  return item;
}
//-------------------------------------------------------------------
int CSzenarium::getSerializeTlg(int id,char* buffer,int length)
{
  CSzenItem^ item=nullptr;
  int count,index;

  index = System::Convert::ToInt32(IndexArray[id-1]); 
  item = safe_cast<CSzenItem^>(ItemArray[index]);
  count=item->getSerializeTlg(buffer,length);

  return count;
}
//-------------------------------------------------------------------
void CSzenarium::setName(String^ name)
{
  Name = name;
}
//-------------------------------------------------------------------
String^ CSzenarium::getName()
{
  return Name;
}
//-------------------------------------------------------------------
void CSzenarium::removeAllCyclicTlg()
{ 
  for (int i=1;i<=getSzenItemCount();i++)
  {
    if (getSzenItem(i)->getIsCyclic())
        remouteAt(i--);
    if (UpdateRemoveCyclicTlgInScenarioDel)
      UpdateRemoveCyclicTlgInScenarioDel->Invoke(1);
  }
  //Ausgabe in Log - Datei
  String^ mess = "All cyclic telegrams in szenario removed";
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
																												  __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
}
//-------------------------------------------------------------------
void CSzenarium::remouteAt(int index)
{
  if(index > 0)
  {
    int item_in = System::Convert::ToInt32(IndexArray[index-1]);
    CSzenItem^ item = safe_cast<CSzenItem^>(ItemArray[item_in]);
     //Counter erniedrigen
    if (InterCounterTable->Contains(item->getInterface()))
    {
      int count = 0; 
			count = (Int32) (InterCounterTable[item->getInterface()]);
      if (count>1)
        InterCounterTable[item->getInterface()] = --count;
      else
        InterCounterTable->Remove(item->getInterface());
    }

    item->clearItem();
    ItemArray->RemoveAt(item_in);
    IndexArray->RemoveAt(index-1);
    indexCorection(item_in);
    ChangeSzenFlag=true;
  }
}
//------------------------------------------------------------------
void CSzenarium::duplicateItem(int index,int count)
{
  double d1,d2;
  CSzenItem^ it1 = nullptr;
  CSzenItem^ it2 = nullptr;
  CSzenItem^ item = nullptr;
  
  double offset;
  int item_count = ItemArray->Count;
  it1 = getSzenItem(index);
  d1 = it1->getTime();
  if(index < item_count)
  {       
    it2 = getSzenItem(index+1);
    d2 = it2->getTime();
    offset = (d2 - d1)/(count+1.0);
  }
  else
  {
    offset = 1.0;
  }
  CItemWrapper^ tlgWr=nullptr;
  tlgWr = it1->getTlgWrapper();
  for(int i=1;i<=count;i++)
  {
    //item = getSzenItem(index)->clone();
    //item->setTime(d1+offset*1);
    this->addToSzenarium(tlgWr,d1+offset*i);
  }
  //ChangeSzenFlag=true;
  //Ausgabe in Log - Datei
  String^ mess = String::Concat("Telegram <",it1->getItemName(), "> ",count.ToString()," - fold duplicated");
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
																												  __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
}
//------------------------------------------------------------------
void CSzenarium::updateItem(int index,CItemWrapper^ tlg)
{
  CSzenItem^ item;
  int indexIt;
  indexIt = System::Convert::ToInt32(IndexArray[index-1]); 
  item = safe_cast<CSzenItem^>(ItemArray[indexIt]);
  item->setItem(tlg);
  ChangeSzenFlag=true;
}
//------------------------------------------------------------------
String^ CSzenarium::getSzenItemAsString(int id)
{
	String^ ret = nullptr;
	CSzenItem^ item;
	int indexIt;
	indexIt = System::Convert::ToInt32(IndexArray[id-1]); 
	item = safe_cast<CSzenItem^>(ItemArray[indexIt]);
	ret = item->getItemAsString();
	return ret;
}
//------------------------------------------------------------------
void CSzenarium::clearSzenarium()
{
  int count,i;
  CSzenItem^ item = nullptr;
  Name = "";
  IndexArray->Clear();
  count = ItemArray->Count;
  for(i=0;i<count;i++)
  {
    item = safe_cast<CSzenItem^>(ItemArray[i]);
    item->clearItem();
  }
  ItemArray->Clear();
  InterCounterTable->Clear();
  //Ausgabe in Log - Datei
  String^ mess = "All telegrams in szenario removed";
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
																												  __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  FocusedItem=0;
  ChangeSzenFlag=false;
}
//------------------------------------------------------------------
void CSzenarium::indexCorection(int val)
{
  int i,val1;
  int count = IndexArray->Count;
  for(i=0;i<count;i++)
  {
    val1 = System::Convert::ToInt32(IndexArray[i]);
    if(val1 > val)
      IndexArray[i] = val1-1;
  }
}
//------------------------------------------------------------------
double CSzenarium::getDelayRel()
{
	return DelayRel;
}
//------------------------------------------------------------------
void CSzenarium::setSimpleDelay(double del)
{
	int i;
	double delay = 0.0;
  int total = 0;
	int count = ItemArray->Count;
	if(count > 0)
	{
    getSzenItem(1)->setDelay(0.0);
    for(i=2;i<=count;i++)
		{
			getSzenItem(i)->setDelay(del*(i-1));
      getSzenItem(i)->setBarredDelay(del*(i-1-total));

      if (!getSzenItem(i)->getSendStatus())
        total++;
		}
  }
}
//------------------------------------------------------------------
void CSzenarium::moveDelay(double offset)
{
	int i;
	double del;
	CSzenItem^ item=nullptr;
	int count = ItemArray->Count;
	for(i=1;i<=count;i++)
	{
		item=getSzenItem(i);
		del=item->getDelay();
		item->setDelay(del+offset);
	}
  //ChangeSzenFlag=true;
}
//------------------------------------------------------------------
CItemBaseContainerWrapper^ CSzenarium::getSzenariumContainer()
{
  int count,i;
  CItemWrapper^ wr=nullptr;
  CTlgContainerWrapper^ con = gcnew CTlgContainerWrapper();
  count=getSzenItemCount();
  for(i=1;i<=count;i++)
  {
    wr=getSzenItem(i)->getTlgWrapper();
    con->addTlgToContainer(wr);
  }
  return con;
}
//------------------------------------------------------------------
void CSzenarium::setFocusedItem(int index)
{
  FocusedItem=index;
}
//-------------------------------------------------------------------
int CSzenarium::getFocusedItem()
{
  return FocusedItem;
}
//------------------------------------------------------------------
void CSzenarium::setSzenChangeModus(bool flag)
{
  ChangeSzenFlag=flag;
}
//------------------------------------------------------------------
bool CSzenarium::getSzenChangeModus()
{
  return ChangeSzenFlag;
}
//------------------------------------------------------------------
void CSzenarium::setPath(String^ szenPfad)
{
	Path=szenPfad;
}
//------------------------------------------------------------------
String^ CSzenarium::getPath()
{
	return Path;
}
//------------------------------------------------------------------
void CSzenarium::setSendSzenItem(int index)
{
  SendItem=index;
}
//-------------------------------------------------------------------
int CSzenarium::getSendSzenItem()
{
  return SendItem;
}
//------------------------------------------------------------------
void CSzenarium::removeAllInterTlgFromSzenarium(String^ inter)
{
  String^ interName=nullptr;
  int i,count;
  int offset;
  offset=0;
  count=getSzenItemCount();
  for(i=1;i<=count;i++)
  {
    interName=getSzenItem(i-offset)->getInterface();
    if(inter->Equals(interName))
    {
        remouteAt(i-offset);
        offset++;
    }
  }
  if(getSzenItemCount() > 0)
  {
      setFocusedItem(1);
  }
  else
  {
      setFocusedItem(0);
  }
  //Ausgabe in Log - Datei
  String^ mess = String::Concat("All telegrams (interface : ",inter,"in szenario removed");
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
																												  __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
}
//------------------------------------------------------------------
void CSzenarium::setAllSameItemToCyclic(CItemWrapper^ item,bool mod)
{
  String^ name = item->getName(); 
  for (int i=1;i<=getSzenItemCount();i++)
  {
    if (name->Equals(getSzenItem(i)->getItemName()))
      if (item->getInterfece()->Equals(getSzenItem(i)->getInterface()))
        getSzenItem(i)->setIsCyclic(mod);
  }
}
//------------------------------------------------------------------
CItemWrapper^ CSzenarium::findItemFromSzenarium(String^ name)
{
  CItemWrapper^ ret=nullptr;
  String^ compareName=nullptr;
  int counter=1;
  bool ok = true;
  while (ok && counter<=getSzenItemCount())
  {
    if (name->Equals(getSzenItem(counter)->getItemName()))
    {
      ok = false;
      ret = getSzenItem(counter)->getTlgWrapper();
    }
    counter++;
  }
  return ret;
}
//------------------------------------------------------------------
void CSzenarium::acceptChangeTime()
{
  bool flag1;
  bool flag2;
	int i,count;
	CSzenItem^ szenItem=nullptr;
	CSzenItem^ szenItem1=nullptr;
  CSzenItem^ szenItemFirst=nullptr;
  flag1=true;
  double t0=0;
  double d0=0;

  while(flag1)
  {
    count = getSzenItemCount();
    i=0;
    flag2=true;
      
    while((flag2) && (i<count))
    {
      szenItem=getSzenItem(i+1);
      if(szenItem->getChangeTimeStatus())
      {
        if (i==0)
        {
          szenItemFirst=getSzenItem(2);
          d0=szenItemFirst->getDelay();
          t0=szenItemFirst->getTime();
                
          if (d0>=szenItem->getChangeTime())
          {
            szenItem->setDelay(szenItem->getChangeTime());
            szenItem->setChangeTime(0.0);
            szenItem->setChangeTimeStatus(false);
            flag2=false;
          }
          else
          {
            szenItem1=szenItem->clone();

            remouteAt(i+1);
            this->calcDelay();
            
            szenItem1->acceptChangeTime(true,DelayRel,t0,d0);
            
            addToSzenarium(szenItem1);
            this->calcDelay();
            flag2=false;
          }
        }
        else
        {
          szenItemFirst=getSzenItem(1);
          d0=szenItemFirst->getDelay();
          t0=szenItemFirst->getTime();
        
          szenItem1=szenItem->clone();
          szenItem1->acceptChangeTime(true,DelayRel,t0,d0);
          remouteAt(i+1);
          addToSzenarium(szenItem1);
          flag2=false;
        }
      }
      else
      {
          i++;
      }
    }
    if(flag2)
    {
      flag1=false;
    }
  }
  //calcDelay();
}
//------------------------------------------------------------------
bool CSzenarium::readScenarioFromFileInPart(System::IO::StreamReader^ sr,ArrayList^ protoSet,
                                            int TlgCount,double &t0,String^ name, double rel,String^ path,double &d0_par,
                                            int haveTime)
{
	bool ret = true;
  bool ok = true;
	String^ line = nullptr;
  String^ delStr = " ";
  array <Char>^ delChar = delStr->ToCharArray();
  array <String^>^ items = nullptr;
	CInterBaseManager^ interMan = nullptr;
	CItemWrapper^ Tlg=nullptr;
	String^ Error=nullptr;
  int count=0;
  int countItem=0;
	int tlgCountIndex=0;
	double t1=0;
  double d1=0;
	double d0 = -1.0;
	//double offset=0.0;
	int index;

  //int timeForSpeep = 0;
  //System::DateTime beginTime;

  //const int Factor = TlgCount / 10;
	
  clearSzenarium();
 
	setName(name);
	setDelayRel(rel);
	
  //-----------------------------------
  //while((tlgCountIndex<TlgCount)&& ((line = sr->ReadLine())!=0)
  while(ok && (tlgCountIndex<TlgCount))
  {
    if ((line = sr->ReadLine())== nullptr)
    {
      ok = false;
      ret = false;
    }

    ////Aktuelle Zeit merken, bei ersten Tellegramm
    //if ((haveTime > 0) && (tlgCountIndex == 0))
    //{
    //  beginTime = System::DateTime::Now;
    //}
    if (ok)
    {
      try
		  {
        String^ testEmpty=nullptr;
        testEmpty=line->Replace(" ","");
        if(!testEmpty->Equals(""))
        {
				  items = line->Split(delChar,5);
				  if(items->Length != 5)
				  {
            String^ mess = "Format of Line is wrong";
            CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
																											__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
				    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,line,
																											__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
            if(MessageScenarioDel)
            {
                MessageScenarioDel->Invoke(mess);
                MessageScenarioDel->Invoke(line);
            }
				  }
				  else
				  {
					  interMan = getProtoInterface(items[0],protoSet);
					  if(interMan == nullptr)
					  {
              String^ mess = String::Concat("Unknown Interface: ",items[0]);
              CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
																												__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
				      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,line,
																												__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
              if (MessageScenarioDel)
              {
                MessageScenarioDel->Invoke(mess);
                MessageScenarioDel->Invoke(line);
              }
					  }
					  else
					  {   
              Tlg = interMan->makeTlg(items[1]);
              Error = Tlg->fillTlg(items[4]);
						  if(Error)
						  {
							  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,Error,
																													__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
				        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,line,
																													__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
                if(MessageScenarioDel)
							  {
                  MessageScenarioDel->Invoke(Error);
                  MessageScenarioDel->Invoke(line);
							  }
						  }
						  else
						  {
							  //Wenn erste Tellegramm
                if(d0 < 0.0)
							  {
								  if (d0_par < 0.0)
                    d0 = CFormatConverterWrapper::StringToDouble(items[2]);
                  else
                    d0 = d0_par;

								  d1 = CFormatConverterWrapper::StringToDouble(items[2]);
                  //d1 = d0;
								  //////offset=d0;
							  }
                else
                {
								  d1 = CFormatConverterWrapper::StringToDouble(items[2]);
								  //////if(d1<offset)
									 ////// offset=d1;
							  }

							  t1 = (d1-d0)/rel + t0;
							  index = addToSzenarium(Tlg,t1);
                
                Tlg->clearWrapperTlg();
							  if(items[3]->Equals("On"))
							  {
								  getSzenItem(index)->setSendStatus(true);
							  }
							  else
							  {
								  getSzenItem(index)->setSendStatus(false);
							  }
              }
            }
          }
         /* if (tlgCountIndex == (TlgCount - 1))
          {
            d0_par = d0;
          }*/
          count++;
          tlgCountIndex++;
        }
      }
      catch(String^ mess)
		  {
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
																																__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
				CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,line,
																																__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
				if(MessageScenarioDel)
        {
          MessageScenarioDel->Invoke(mess);
          MessageScenarioDel->Invoke(line);
        }
		  }
		  catch(...)
		  {
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,"Unknown Error",
																																__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
				CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,line,
																																__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
				if(MessageScenarioDel)
        {
            MessageScenarioDel->Invoke("Unknown Error");
            MessageScenarioDel->Invoke(line);
        }
      }

      ////Dieferenz berechnen beim ersten Telegramm
      //if ((haveTime > 0) && (tlgCountIndex == Factor))
      //{
      //  System::DateTime endTime = System::DateTime::Now;
      //  int diffTime = endTime.get_Millisecond() - beginTime.get_Millisecond();
      //  
      // 
      //  
      //  
      //  timeForSpeep = ((haveTime*1000) / TlgCount) -   (((diffTime/Factor)*3)/2);
      //  //ACCEPT
      //  if (timeForSpeep < 0)
      //  {
      //    timeForSpeep = 0;
      //  }
      //}
      
      //Warten, um die CPU - Vollauslastung zu vermeiden
      System::Threading::Thread::CurrentThread->Sleep(1);
	  }
  }// end while

  /*if (line == 0)
  {
   ret = false;
  }*/
  //---------------------------------------


  //Letze d0 Wert merken
  if (d1 > 0.0)
    d0_par = d1;
  t0 = t1;
  
  /* if ((d1 > 0.0) && (d0 > 0.0))
  {
    d0_par = d1 - d0;
  }
  else
  {

  }*/
  
  //Wenn die Datei ausgelesen wurde dann true sonst false
  if ((line == nullptr) || (sr->Peek() == -1))
    ret = false;

  setPath(path);
  if(getSzenItemCount() != 0)
  {
		calcDelay();
		//moveDelay(offset);
  }
  if(MessageScenarioDel)
  {
	  countItem=getSzenItemCount();
    //MessageScenarioDel->Invoke(String::Concat("Total: ",System::Convert::ToString(count)));
    //MessageScenarioDel->Invoke(String::Concat("Accept: ",System::Convert::ToString(countItem)));
    //MessageScenarioDel->Invoke(String::Concat("Not Accept: ",System::Convert::ToString(count-countItem)));
  }
  return ret;
}
//------------------------------------------------------------------
void CSzenarium::readScenarioFromFile(String^ path,ArrayList^ protoSet)
{
  String^ line = nullptr;
  String^ delStr = " ";
  array <Char>^ delChar = delStr->ToCharArray();
  array <String^>^ items = nullptr;
	CInterBaseManager^ interMan = nullptr;
	CItemWrapper^ Tlg=nullptr;
	String^ Error=nullptr;
  int count=0;
  int countItem=0;
	double t0,t1,d1;
	double d0 = -1.0;
	double rel;
	double offset=0.0;
	int index;
	System::IO::StreamReader^ sr = gcnew System::IO::StreamReader(path);
	//-----------------------------------------------------------------------------------
  clearSzenarium();
  //-----------------------------------------------------------------------------------
	try
	{
		//Xml Reader
		//System::IO::StreamReader* xmlCheck = new System::IO::StreamReader(path);
		//line = xmlCheck->ReadLine();
		//xmlCheck->Close();
		//int pos = line->IndexOf("<?xml");
		//if(pos>-1)
		//{
			//String^ mess=0;
			//CXmlSzenReader* szenReader = new CXmlSzenReader();
			//Szenarium=szenReader->loadSzenarium(path,protoSet);
			//showSzenarium();
			//mess = String::Concat(mess,"Dieses Szenarium hat die alte Formatierung.");
			//mess = String::Concat(mess,"Um die richtige Bearbeitung zu gewährleisten,");
			//mess = String::Concat(mess,"muss es neu gespeichert werden.");
      //if(MessageScenarioDel)
      //  MessageScenarioDel->Invoke(mess);
			//System::Windows::Forms::MessageBox::Show(0,mess,"Warning",System::Windows::Forms::MessageBoxButtons::OK);
		//}
		//-----------------------------------------------------------------------------------
		//else
		//{
		line = sr->ReadLine();
		items = line->Split(delChar);
		if(items->Length == 2)
			setName(items[1]);
		else
			setName("Unknow");

		line = sr->ReadLine();
		items = line->Split(delChar);
		if(items->Length == 2)
		{
			rel = CFormatConverterWrapper::StringToDouble(items[1]);
			setDelayRel(rel);
		}
		else
		{
			setDelayRel(1.0);
		}

		line = sr->ReadLine();
		items = line->Split(delChar);
		if(items->Length == 2)
			t0 = CFormatConverterWrapper::StringToDouble(items[1]);
		else
			t0 = 0.0;
		while((line = sr->ReadLine()) != nullptr)
		{
			try
			{
        String^ testEmpty=nullptr;
        testEmpty=line->Replace(" ","");
        if(!testEmpty->Equals(""))
        {
				  items = line->Split(delChar,5);
				  if(items->Length != 5)
				  {
            String^ mess = "Format of Line is wrong";
            CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
																											__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
            CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,line,
																											__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
            if(MessageScenarioDel)
            {
                MessageScenarioDel->Invoke(mess);
                MessageScenarioDel->Invoke(line);
            }
					}
					else
					{
						interMan = getProtoInterface(items[0],protoSet);
						if((interMan == nullptr))
						{
              String^ mess = String::Concat("Unknown Interface: ",items[0]);
              CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
																												__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
              CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,line,
																												__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
              if (MessageScenarioDel)
              {
                MessageScenarioDel->Invoke(mess);
                MessageScenarioDel->Invoke(line);
              }
						}
						else
						{   
              Tlg = interMan->makeTlg(items[1]);
              Error = Tlg->fillTlg(items[4]);
							if(Error)
							{
								CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,Error,
																													__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
                CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,line,
																													__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
                if(MessageScenarioDel)
								{
                  MessageScenarioDel->Invoke(Error);
                  MessageScenarioDel->Invoke(line);
                  //MessageBox->writeLine(Error,CMessageForm::MessTyp::Error);
                  //MessageBox->writeLine(line,CMessageForm::MessTyp::Error);
								}
							}
							else
							{
								if(d0 < 0.0)
								{
									d0 = CFormatConverterWrapper::StringToDouble(items[2]);
									d1 = d0;
									offset=d0;
								}
								else
								{
									d1 = CFormatConverterWrapper::StringToDouble(items[2]);
									if(d1<offset)
										offset=d1;
								}
								t1 = (d1-d0)/rel + t0;
								index = addToSzenarium(Tlg,t1);
                Tlg->clearWrapperTlg();
								if(items[3]->Equals("On"))
								{
									getSzenItem(index)->setSendStatus(true);
								}
								else
								{
									getSzenItem(index)->setSendStatus(false);
								}
							}
						}
					}
          count++;
        }
			}
			catch(String^ mess)
			{
      	CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
																															__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
				CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,line,
																																__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
				if(MessageScenarioDel)
        {
          MessageScenarioDel->Invoke(mess);
          MessageScenarioDel->Invoke(line);
        }			
			}
			catch(...)
			{
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,"Unknown Error",
																																__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
				CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,line,
																																__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
				if(MessageScenarioDel)
        {
          MessageScenarioDel->Invoke("Unknown Error");
          MessageScenarioDel->Invoke(line);
        }
      }
		}
		sr->Close();
    //SelItemColor=Color::FromKnownColor(KnownColor::MediumSlateBlue);
    setPath(path);
    if(getSzenItemCount() != 0)
    {
			calcDelay();
			moveDelay(offset);
      //setFocusedItem(1);
      // if(SelectItemEvent)
		  // {
            //   CItemWrapper^ tlgWr=0;
			      // tlgWr=Szenarium->getSzenItem(1)->getTlgWrapper();
			      // SelectItemEvent->Invoke(tlgWr);
		    //}
			  //updateScrollPosition();
			  //showSzenFromScrollPos();
              //Szenarium->setSzenChangeModus(false);
			  //updateSzenView();
			  //UpdateSzenEvent->Invoke(true);
      }
		  //}
      if(MessageScenarioDel)
      {
		    String^ mess = nullptr;
        countItem=getSzenItemCount();
        mess = String::Concat("Total: ",System::Convert::ToString(count));
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
																																__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        MessageScenarioDel->Invoke(mess);
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
																																__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        mess = String::Concat("Accept: ",System::Convert::ToString(countItem));
        MessageScenarioDel->Invoke(mess);
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
																																__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        mess = String::Concat("Not Accept: ",System::Convert::ToString(count-countItem));
        MessageScenarioDel->Invoke(mess);
      }
}
	catch(...)
	{
		sr->Close();
		clearSzenarium();
		String^ mess=nullptr;
		mess = String::Concat("The file ",path," can't to read");
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                            __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
		if(MessageScenarioDel)
		{
			//UpdateSzenEvent->Invoke(false);
			MessageScenarioDel->Invoke(mess);
    }
	}
}
//------------------------------------------------------------------
CInterBaseManager^ CSzenarium::getProtoInterface(String^ interName,ArrayList^ liste)
{
  CInterBaseManager^ ret = nullptr;
	CInterBaseManager^ inter = nullptr;
	int count,i;

	i=0;
	count = liste->Count;
	while((ret == nullptr) && (i<count))
	{
		inter = safe_cast<CInterBaseManager^>(liste[i]);
		if(inter->getInterfaceName()->Equals(interName))
		{
			ret = inter;
		}
		else
		{
			i++;
		}
	}

	return ret;
}
//------------------------------------------------------------------
void CSzenarium::setMessScenDel(MessageScenarioDelTyp^ del)
{
    MessageScenarioDel = del;
}
//------------------------------------------------------------------
void CSzenarium::setMessageScenSafeProgressDel(MessageScenSafeProgressDelTyp^ del)
{
    MessageScenSafeProgressDel = del;
}
//------------------------------------------------------------------
void CSzenarium::setUpdateRemoveCyclicTlgInScenarioDel (UpdateRemoveCyclicTlgInScenarioDelTyp^ del)
{
  UpdateRemoveCyclicTlgInScenarioDel = del;
}
//------------------------------------------------------------------
void CSzenarium::saveSzenarium(String^ path)
{
  int count,i;
  int index;
  int lenght;
  String^ str=nullptr;
  String^ tel=nullptr;
  String^ inter=nullptr;
  String^ tlgName=nullptr;
  String^ szenName=nullptr;
  String^ strDelay=nullptr;
  bool status;
  String^ statusStr=nullptr;
  double delay;
  double t0,rel;
  System::IO::StreamWriter^ sw = gcnew System::IO::StreamWriter(path);

  count=getSzenItemCount();
  if(count > 0)
  {
    szenName = getName();
    rel = getDelayRel();
    t0 = getSzenItem(1)->getTime();
    sw->WriteLine(String::Concat("Name ",szenName));
    sw->WriteLine(String::Concat("DelayRel ",CFormatConverterWrapper::DoubleToString(rel)));
    sw->WriteLine(String::Concat("Time ",CFormatConverterWrapper::DoubleToString(t0)));
  }
  

  //int indexSubElem = -1;
  //String^ valueFromConfig = 0;
  //String^ valueFromTlg = 0;
  //String^ tlgIdName = 0;
  //String^ elemIdName = 0;
  //CAppSetting* Sett = CAppSetting::getApp();
  //String^ confPath = 0;  
  //CXmlInterConfigReader* configFileReader = 0;
  
  //CInterConfigWrapper* interConfig = new CInterConfigWrapper();

  //System::Collections::Hashtable* configFileTable = new System::Collections::Hashtable();
  //CTlgElemWrapper* elem = new CTlgElemWrapper();
  
  for(i=1;i<=count;i++)
  {
    delay = getSzenItem(i)->getDelay();
    tlgName= getSzenItem(i)->getItemName();
    inter = getSzenItem(i)->getInterface();

    //valueFromConfig = interConfig->getTlgId(inter,tlgName);
    //elemIdName = interConfig->getElemId(inter);
    //indexSubElem = getSzenItem(i)->getTlgWrapper()->getSubElemIndex(getSzenItem(i)->getTlgWrapper()->getElemName(1),elemIdName);  
    //elem->setTlgElem(getSzenItem(i)->getTlgWrapper()->getElem(1)->getSubElem(indexSubElem));
    //elem->setValue(valueFromConfig,inter);

    //
    status = getSzenItem(i)->getSendStatus();
    if(status)
        statusStr = "On";
    else
        statusStr = "Off";
    str=getSzenItemAsString(i);

    //!! Delay Zeit wird auf 4 Nachkommastellen abgekuertzt
    //-----------------------------------------
    strDelay=CFormatConverterWrapper::DoubleToString(delay);
    lenght=strDelay->Length;
    
    index=strDelay->IndexOf('.');
    if (index==-1)
       index=strDelay->IndexOf(',');
    
    if (index==-1)
        strDelay=strDelay->Concat(strDelay,".0000");
    else
    {
      if (index>0)
      {
        if (index+5<=lenght)
          strDelay=strDelay->Remove((index+5),(strDelay->Length)-(index+5));
        else if (lenght-(index+1)==1)
          strDelay=strDelay->Concat(strDelay,"000");
        else if (lenght-(index+1)==2)
          strDelay=strDelay->Concat(strDelay,"00");
        else if (lenght-(index+1)==3)
          strDelay=strDelay->Concat(strDelay,"0");
       }
    }
    tel = String::Concat(inter," ",tlgName," ",strDelay," ",statusStr," ",str);
    sw->WriteLine(tel);
    if (MessageScenSafeProgressDel)
      MessageScenSafeProgressDel->Invoke(1);
  }
  setSzenChangeModus(false);
  sw->Close();
}
//---------------------------------------------------------------------------
//------------------------------------------------------------
void CSzenarium::CompareConfigIdWithFileId (CItemWrapper^ item,CInterConfigWrapper^ interConfig)
{
  String^ valueFromConfig = interConfig->getTlgId(item->getInterfece(),item->getName());
  String^ elemIdName = interConfig->getElemId(item->getInterfece());
  int indexSubElem = item->getSubElemIndex(item->getElemName(1),elemIdName);  
  
  String^ valueFromTlg = item->getSubElemValue(1,indexSubElem);
  
  if (valueFromConfig && valueFromTlg && !valueFromTlg->Equals(valueFromConfig))
  {
    String^ mess = nullptr;
    
    mess = "Id value of ";    
    mess = mess->Concat(mess,item->getName()," from interface configuration and from szenario file are not identity");
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,
                                                            __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    
    bool ok = true;
    #if defined __CONSOLE__
      ok = false;
    #endif
    if (ok && MessageScenarioDel)
    {
      MessageScenarioDel->Invoke(mess);
    }
  }
   
  //elem->setTlgElem(getSzenItem(i)->getTlgWrapper()->getElem(1)->getSubElem(indexSubElem));
  //elem->setValue(valueFromConfig,inter);
  
  //CAppSetting* Sett = CAppSetting::getApp();
  //String^ confPath = Sett->getInterConfigFilePath(item->getInterfece());   
  //CXmlInterConfigReader* confFileReader = new CXmlInterConfigReader();
  //confFileReader->setInterConfigFile(confPath);     
  //
  //String^ elemIdName = 0;
  //String^ tlgIdName = 0;
  //String^ valueFromConfig = 0;
  //String^ valueFromTlg = 0;
  //int index = -1;

  //confFileReader->setSectionFocus("TelegramId");
  //valueFromConfig = confFileReader->getTlgId(item->getName());
  //
  //confFileReader->setSectionFocus("TelegramId");
  //confFileReader->getElemIdName(tlgIdName,elemIdName);
  //
  //index = item->getSubElemIndex(item->getElemName(1),elemIdName);
  //
  //if (index > 0)
  //  valueFromTlg=item->getSubElemValue(1,index);
  //
  ////Wenn Id aus der Szenario Datei und von 
  ////Konfigurationsdatei nicht uebereinstimmen
  //if (valueFromTlg && !valueFromTlg->Equals(valueFromConfig))
  //{
  //  CInterConfigWrapper* confWr = 0;
  //  String^ mess = 0;
  //  bool flagSec = false;
  //     
  //  CXmlInterConfigWriter* configFileWriter = new  CXmlInterConfigWriter();
  //  configFileWriter->loadInterConfigFile(confPath);
  //
  //  if (MessageScenarioDel)
  //  {
  //    mess = "Id value of ";    
  //    mess = mess->Concat(mess,item->getName()," from interface configuration and from szenario file are not identity");
  //    MessageScenarioDel->Invoke(mess);
  //  }
  //  
  //  flagSec = configFileWriter->setSectionFocus("TelegramId");
  //  if (flagSec)
  //  {
  //    configFileWriter->setTelId(item->getName(),valueFromTlg);
  //    if (MessageScenarioDel)
  //    {
  //      mess = "Id value <";
  //      mess = mess->Concat(mess,valueFromTlg,"> from szenario file taked");
  //      MessageScenarioDel->Invoke(mess);
  //    }
  //  }
  //  configFileWriter->endUpdate();

  //  //Konfigurationseinstellungen updaten
  //  confWr = new CInterConfigWrapper();
  //  confWr->readInterConfigurationFile(item->getInterfece(),confPath);
  //}
}