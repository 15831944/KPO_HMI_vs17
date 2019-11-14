// Copyright 2006 SMS - Demag AG

#include "stdafx.h"
#include "CItemBaseContainerWrapper.h"
#include "CStdConverter.h"
#include "CTlgWrapper.h"
#include "CTlgElem.h"
#include "CTlgElemWrapper.h"
#include "CLogWriterWrapper.h"

//------------------------------------------------------------
CItemBaseContainerWrapper::CItemBaseContainerWrapper():
ErrorMessage(nullptr),Path(nullptr)
{
	VirtuallContainer = gcnew ArrayList();
	SortConditonArray = gcnew ArrayList();
	SelectedItem=0;
  regExpArray = nullptr;
}
//------------------------------------------------------------
CItemBaseContainerWrapper::~CItemBaseContainerWrapper()
{
	//delete TlgContainer;
}
//-------------------------------------------------------------
String^ CItemBaseContainerWrapper::getErrorMessage()
{
  return this->ErrorMessage;
}
//-------------------------------------------------------------
String^ CItemBaseContainerWrapper::getPathFile()
{
	return Path;
}
//-------------------------------------------------------------
double CItemBaseContainerWrapper::getTlgTime(int id)
{
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,
                                                      "This methode is not implement in this cla",
                                                      __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
	return 0.0;
}
//-------------------------------------------------------------
double CItemBaseContainerWrapper::getVirtualTlgTime(int id)
{
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,
                                                      "This methode is not implement in this cla",
                                                      __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  return 0.0;
}
//-------------------------------------------------------------
int CItemBaseContainerWrapper::getVirtualTlgCount()
{
  return VirtuallContainer->Count;
}
//-------------------------------------------------------------
int CItemBaseContainerWrapper::findTelegramm(int pos,String^ tlgName)
{
  int ret=0;
	int count,i;
	bool flag;
	count = this->getVirtualTlgCount();
	CItemWrapper^ wr = gcnew CTlgWrapper();
  if(pos <= count)
	{
		flag=false;
		i=pos;
		while((i<=count) && (!flag))
		{
			this->getClonedVirtualTlg(wr,i);
			if(wr->getName()->Equals(tlgName))
			{
				flag=true;
				ret=i;
			}
			else
			{
				i++;
			}
		}
	}
	
	return ret;
}
//-------------------------------------------------------------
int CItemBaseContainerWrapper::findTelegramm(int pos,String^ tlgName,String^ elemName,String^ rel,String^ val)
{
  int ret=0;
	int count,i;
  int pos_del;
  int relInt;
	bool flag;
	String^ elem=nullptr;
	String^ subelem=nullptr;
	count = this->getVirtualTlgCount();
	if(pos <= count)
	{
		CItemWrapper^ wr = gcnew CTlgWrapper();
		flag=false;
		i=pos;
		while((i<=count) && (!flag))
		{
			this->getClonedVirtualTlg(wr,i);
			if(wr->getName()->Equals(tlgName))
			{
        pos_del=elemName->IndexOf("\\");
        if(pos_del == -1)
        {
            subelem="";
        }
        else
        {
            subelem=elemName->Substring(pos_del+1,elemName->Length-pos_del-1);
            elemName=elemName->Substring(0,pos_del);
        }
        relInt=wr->compareElem(elemName,subelem,val);
        flag = ((relInt==0) && ((rel->Equals("=")) || (rel->Equals("<=")) || (rel->Equals(">=")))) || 
            ((relInt==1) && ((rel->Equals(">")) || (rel->Equals(">=")))) || 
            ((relInt == -1) && ((rel->Equals("<")) || (rel->Equals("<="))));

        if(flag)
            ret=i;
		  }
			if(!flag)
				i++;
		}
	}
	return ret;
}
////-------------------------------------------------------------
//void CItemBaseContainerWrapper::addSortCondition(String^ tel,String^ elem,String^ subElem)
//{
//	__gc struct SortConditionTyp^ sortCond = gcnew SortConditionTyp();
//	sortCond->TlgName=tel;
//	sortCond->ElemName=elem;
//	sortCond->SubElemName=subElem;
//	SortConditonArray->Add(sortCond);
//}
//-------------------------------------------------------------
void CItemBaseContainerWrapper::addSortCondition(String^ tel,String^ elemPath)
{
	value struct SortConditionTyp^ sortCond = gcnew SortConditionTyp();
	sortCond->TlgName=tel;
  sortCond->ElemNamePath=elemPath;
	SortConditonArray->Add(sortCond);
}
//-------------------------------------------------------------
void CItemBaseContainerWrapper::sortContainer()
{
	SortConditionTyp^ cond=nullptr;
  String^ valStr=nullptr;
	ArrayList^ temp= gcnew ArrayList(); 
	//Anzahl der Elementen in der Liste mit Sortierungskriterien
  int count = SortConditonArray->Count;
	//int countTlgInCon;
	
  int pos=0;
	int index;
  //int indexOfElem;
	int i,j;
	
  String^ tlgName=nullptr;
	String^ elemNamePath=nullptr;
	//String^ subElemName=nullptr;
	CItemWrapper^ wr = gcnew CTlgWrapper();
	CTlgElemWrapper^ elemWr = gcnew CTlgElemWrapper();
  
  
  for(i=0;i<count;i++)
	{
		cond=safe_cast<SortConditionTyp^>(SortConditonArray[i]);
		tlgName=cond->TlgName;
    elemNamePath=cond->ElemNamePath;
		//subElemName=cond->SubElemName;
		//countTlgInCon=getVirtualTlgCount();
		j=1;
    //Virtuelle Container durchlaufen
		while(j<=getVirtualTlgCount())
		{
			getClonedVirtualTlg(wr,j);
			//Wenn Telegramme gleiche Namen haben
      if(wr->getName()->Equals(tlgName))
			{
        
        /*indexOfElem=wr->getElemIndex(elemName);
        valStr=wr->getElemValue(indexOfElem);*/
				
        elemWr->setTlgElem(wr->getTlgElem(elemNamePath));
        elemWr->getElemValue(valStr);
        
        //if(valStr->Equals("551"))
				//{
				//	int k;
				//	k=1;
				//}
				
        if(temp->Count == 0)
        {
					index=0;
        }
				else
        {
					index=getPosInContainer(valStr,temp,pos,temp->Count-1,elemNamePath);
        }
				
        temp->Insert(index,VirtuallContainer[j-1]); //add->insert
				VirtuallContainer->RemoveAt(j-1);
			}
			else
			{
				j++;
			}
		}//end while
		pos=temp->Count;
	}
	count=VirtuallContainer->Count;
	
  for(i=0;i<count;i++)
  {
		temp->Add(VirtuallContainer[i]);
  }
	
  VirtuallContainer->Clear();
	VirtuallContainer=temp;
	SortConditonArray->Clear();
}
//-------------------------------------------------------------
int CItemBaseContainerWrapper::getPosInContainer(String^ val,ArrayList^ list,int unten,int oben,String^ ElemName)
{
	int ret=0;
  //String^ valStr=0;
  int flag;
  CItemWrapper^ wr = gcnew CTlgWrapper();
  int index;
	int index_in_array;

  CTlgElem* elem = nullptr;
  CTlgElemWrapper^ elemWr = gcnew CTlgElemWrapper();
  //elemWr->setTlgElem(wr->getTlgElem(ElemName));
  
  /*CStdConverter::StdStrToString(wr->getTlgElem(ElemName)->getComment())*/
  
  if(unten == oben)
  {
		index = System::Convert::ToInt32(list[unten]);
		//getVirtualTlg(wr,index+1);
    getClonedTlg(wr,index+1);
    
    elemWr->setTlgElem(wr->getTlgElem(ElemName));
    flag=elemWr->compare(val,elemWr->getElemName());
    
    //flag=wr->compareElem(ElemName,"",val);
    switch(flag)
    {
      case 0:
          ret=unten+1;
          break;
      case 1:
          ret=unten;
          break;
      case -1:
          ret=unten+1;
          break;
      default:
          ret=-1;
    }
  }
  else
  {
	  index=(unten+oben)/2;
    index_in_array = System::Convert::ToInt32(list[index]);
		//getVirtualTlg(wr,index+1);
    getClonedTlg(wr,index_in_array+1);
    
    
    elem = wr->getTlgElem(ElemName);
    if (elem !=0)
    {
      elemWr->setTlgElem(elem);
      flag=elemWr->compare(val,elemWr->getElemName());
    }
    else
    {
      flag = -2;
    }
    
    
    //flag=wr->compareElem(ElemName,"",val);
    
    if((unten == index) && ((flag == 1)))
    {
			ret=unten;
      //ret=getPosInContainer(val,list,oben,oben,ElemName);
    }
    else
    {
      if((unten == index) && ((flag == -1)))
      {
				ret=getPosInContainer(val,list,oben,oben,ElemName);
        //ret=unten+1;
      }
      else
      {
        if(flag==1)
        {
          ret=getPosInContainer(val,list,unten,index,ElemName);
        }
        else
        {
          if(flag==-1)
          {
            ret=getPosInContainer(val,list,index,oben,ElemName);
          }
          else
          {
            ret=index+1;
          }
        }
      }
    }
  }
	return ret;
}
//-------------------------------------------------------------
void CItemBaseContainerWrapper::setFilterByInterfaceName(String^ inter)
{
	int count,i;
	CItemWrapper^ wr=gcnew CTlgWrapper();
	VirtuallContainer->Clear();
	count=getTlgCount();
	for(i=0;i<count;i++)
	{
		getClonedTlg(wr,i+1);
		if(wr->getInterfece()->Equals(inter))
			VirtuallContainer->Add(i);
	}
  this->regExpArray = nullptr;
}
//-------------------------------------------------------------
void CItemBaseContainerWrapper::removeFromVirtuallContainer(int pos)
{
	VirtuallContainer->RemoveAt(pos-1);
}
//-------------------------------------------------------------
void CItemBaseContainerWrapper::clearContainer()
{
	VirtuallContainer->Clear();
  this->regExpArray = nullptr;
}
//--------------------------------------------------------------
void CItemBaseContainerWrapper::setSelectedItem(int item)
{
	SelectedItem=item;
}
//------------------------------------------------------------
int CItemBaseContainerWrapper::getSelectedItem()
{
	return SelectedItem;
}
//------------------------------------------------------------
void CItemBaseContainerWrapper::reset()
{
	int count,i;
	VirtuallContainer->Clear();
	count = getTlgCount();
	for(i=0;i<count;i++)
	{
		VirtuallContainer->Add(i);
	}
  this->regExpArray = nullptr;
}
//------------------------------------------------------------
void CItemBaseContainerWrapper::setFilterByTelName(ArrayList^ nameListe)
{
  int count,i;
  int index;
  String^ name=nullptr;
  ArrayList^ tempListe= gcnew ArrayList(); 
  count = VirtuallContainer->Count;
	
  CItemWrapper^ wr=gcnew CTlgWrapper();
  
  for(i=0;i<count;i++)
  {
    //index = System::Convert::ToInt32(VirtuallContainer[i));
    //name=CStdConverter::StdStrToString(TlgProtoTypSet->makeFlatTlg(index+1)->getTlgName());
    //if(nameListe->IndexOf(name) != -1)
    //tempListe->Add(__box(index));
		index = System::Convert::ToInt32(VirtuallContainer[i]);
    //name=CStdConverter::StdStrToString(TlgProtoTypSet->makeFlatTlg(index+1)->getTlgName());
    getClonedTlg(wr,index+1);
    name = wr->getName();
    if(nameListe->IndexOf(name) != -1)
      tempListe->Add(index);
  }

  this->regExpArray = nullptr;
  VirtuallContainer->Clear();
  VirtuallContainer=tempListe;
}
//------------------------------------------------------------
void CItemBaseContainerWrapper::setFilterByPositions(List<int>^ pos)
{
  if (pos == nullptr)
    return;

  VirtuallContainer->Clear();
  
  for (int i=0;i<pos->Count;i++)
  {
    VirtuallContainer->Add(pos[i]-1);
  }
}
//------------------------------------------------------------
bool CItemBaseContainerWrapper::setFilterByRegExp(array <String^>^ reg)
{
	bool ret=true;
  
  int count;
	//System::Text::RegularExpressions::Match^ matchEx=nullptr;
	String^ tlgName=nullptr;
	CItemWrapper^ wr=nullptr;
  /*System::Text::RegularExpressions::Regex^ regEx = nullptr;*/
  
  this->regExpArray = gcnew array <System::Text::RegularExpressions::Regex^> (reg->Length);
  for (int index = 0; index < reg->Length;index++)
    this->regExpArray[index] = gcnew System::Text::RegularExpressions::Regex(regToNetReg(reg[index]),System::Text::RegularExpressions::RegexOptions::IgnoreCase);
  
  VirtuallContainer->Clear();
  count = getTlgCount();

  try
  { 
	  wr=gcnew CTlgWrapper();
	  
    for(int i=1;i<=count;i++)
	  {
		  getClonedTlg(wr,i);
		  tlgName=wr->getName();
		  
      //Kriterien mit alle RegEx checken
      for (int j = 0;j < this->regExpArray->Length;j++)
      {
        if(this->regExpArray[j]->IsMatch(tlgName))
		    {
          VirtuallContainer->Add(i-1);
          break;
		    }
      }
    }
  }
  catch(System::Exception^ e)
  {
	  ret=false;
  }
 
	return ret;
}
//------------------------------------------------------------
String^ CItemBaseContainerWrapper::regToNetReg(String^ reg)
{
	String^ ret=reg;
	ret=treatmentOfStar(ret);
	ret=treatmentOfQuestionMark(ret);
	return ret;
}
//------------------------------------------------------------
String^ CItemBaseContainerWrapper::treatmentOfStar(String^ reg)
{
	String^ ret=reg;
	if(reg->Equals("*"))
	{
		ret="";
	}
	else
	{
		if(reg->StartsWith("*"))
		{
			reg=reg->Remove(0,1);
			ret=String::Concat(reg,"\\z");
		}
		if(reg->EndsWith("*"))
		{
			reg=reg->Remove(reg->Length-1,1);
			ret=String::Concat("\\A",reg);
		}
	}
	return ret;
}
//------------------------------------------------------------
String^ CItemBaseContainerWrapper::treatmentOfQuestionMark(String^ reg)
{
	String^ ret=reg;
	ret=reg->Replace("?",".");
	return ret;
}
//------------------------------------------------------------
String^ CItemBaseContainerWrapper::getFilterRegExpAsString()
{
  if (this->regExpArray != nullptr)
  {
    System::Text::StringBuilder^ tmp = gcnew System::Text::StringBuilder();
    for (int i = 0;i<this->regExpArray->Length;i++)
    {
      tmp->Append(this->regExpArray[i]->ToString());
      tmp->Append(" | ");
    }

    if (tmp->Length > 3)
    {
      tmp->Remove(tmp->Length-3,3); 
      return tmp->ToString();
    }
  }
  return nullptr;
}
//-------------------------------------------------------------
array <String^>^ CItemBaseContainerWrapper::getFilterRegExpAsStringArray()
{
  if (this->regExpArray != nullptr)
  {
    array <String^>^ ret = gcnew array <String^>(regExpArray->Length);
    for (int i=0;i<regExpArray->Length;i++)
      ret[i]=regExpArray[i]->ToString();
    return ret;
  }
  return nullptr;
}