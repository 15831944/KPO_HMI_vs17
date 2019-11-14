// Copyright 2006 SMS - Demag AG

//----------------------------------------------------
#include "stdafx.h"
#include "CTlgContainerWrapper.h"
#include "CLogWriterWrapper.h"
//---------------------------------------------------
//----------------------------------------------------
CTlgContainerWrapper::CTlgContainerWrapper():
CItemBaseContainerWrapper()
{
	Container = gcnew ArrayList();
}
//----------------------------------------------------
CTlgContainerWrapper::~CTlgContainerWrapper()
{
}
//----------------------------------------------------
void CTlgContainerWrapper::getClonedTlg(CItemWrapper^ tlg,int id)
{
	//CItemWrapper^ temp=0;
  ConElementTyp^ elemCon = safe_cast<ConElementTyp^>(Container[id-1]);
	//temp= 
  tlg->setTlg(elemCon->Tlg->getClonedTlg());
}
//----------------------------------------------------
void CTlgContainerWrapper::getClonedTlg(CItemWrapper^ tlg,String^ tlgName)
{
	bool flag=false;
	int count,i;
	ConElementTyp^ elemCon;
	i=0;
	count = getTlgCount();
	while((!flag) && (i<count))
	{
		elemCon = safe_cast<ConElementTyp^>(Container[i]);
		if(elemCon->Tlg->getName()->Equals(tlgName))
		{
			tlg->setTlg(elemCon->Tlg->getClonedTlg());
			flag=true;
		}
		else
		{
			i++;
		}
	}
}
//----------------------------------------------------
String^ CTlgContainerWrapper::getTlgTimeAsString(int id)
{
  String^ timeStr=nullptr;
  String^ ret=nullptr;
  int pos;
  ConElementTyp^ elemCon = safe_cast<ConElementTyp^>(Container[id-1]);
  ret=elemCon->TimeTlg.TimeOfDay.ToString();
  pos=ret->LastIndexOf(".");
	if(pos != -1)
	ret=ret->Substring(0,ret->Length-pos);
  return ret;
}
//----------------------------------------------------
int CTlgContainerWrapper::getTlgCount()
{
  return Container->Count;
}
//----------------------------------------------------
int CTlgContainerWrapper::loadFromFile(String^ path,const bool &abort)
{
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,
                                                        "This methode is not implement in this clas",
                                                        __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  return 0;
}
//----------------------------------------------------
void CTlgContainerWrapper::addTlgToContainer(CItemWrapper^ tlgWr)
{
  ConElementTyp^ elemCon = gcnew ConElementTyp();
  elemCon->Tlg=tlgWr; 
  elemCon->TimeTlg=System::DateTime::Now;
  Container->Add(elemCon);
	VirtuallContainer->Add((Container->Count-1));
}
//----------------------------------------------------
/*void CTlgContainerWrapper::reset()
{
	int count,i;
	VirtuallContainer->Clear();
	count = getTlgCount();
	for(i=0;i<count;i++)
	{
		VirtuallContainer->Add(__box(i));
	}
}*/
//----------------------------------------------------
//void CTlgContainerWrapper::setFilterByTelName(ArrayList* nameListe)
//{
//}
//----------------------------------------------------
/*void CTlgContainerWrapper::setFilterByRegExp(String^ reg)
{
}*/
 //----------------------------------------------------
void CTlgContainerWrapper::getClonedVirtualTlg(CItemWrapper^ tlg,int id)
{
  int index = System::Convert::ToInt32(VirtuallContainer[id-1]);
  /*__gc struct */ConElementTyp^ elem = safe_cast<ConElementTyp^>(Container[index]);  
  tlg->setTlg(elem->Tlg->getClonedTlg()->clone());
}
//----------------------------------------------------
void CTlgContainerWrapper::getClonedVirtualTlg(CItemWrapper^ tlg,String^ tlgName)
{
	bool flag = false;
	int count,i;
	ConElementTyp^ elemCon;
	i=0;
	count = getTlgCount();
	while((!flag) && (i<count))
	{
		elemCon = safe_cast<ConElementTyp^>(Container[i]);
		if(elemCon->Tlg->getName()->Equals(tlgName))
		{
      tlg->setTlg(elemCon->Tlg->getClonedTlg());
			flag = true;
		}
		else
		{
			i++;
		}
	}
}
//----------------------------------------------------
void CTlgContainerWrapper::clearContainer()
{
	CItemBaseContainerWrapper::clearContainer();
	Container->Clear();
}
//----------------------------------------------------
String^ CTlgContainerWrapper::getVirtualTlgDescr(int id)
{
  // not implemented yet
	String^ ret=nullptr;
	return ret;
}
//----------------------------------------------------
CItemWrapper^ CTlgContainerWrapper::getTlg(int id)
{
  ConElementTyp^ elemCon = safe_cast<ConElementTyp^>(Container[id-1]);
  return elemCon->Tlg;
}
//----------------------------------------------------
CItemWrapper^ CTlgContainerWrapper::getTlg(String^ tlgName)
{
	bool flag = false;
  CItemWrapper^ tlg = nullptr;
	int count,i;
	ConElementTyp^ elemCon;
	i=0;
	count = getTlgCount();
	while((!flag) && (i<count))
	{
		elemCon = safe_cast<ConElementTyp^>(Container[i]);
		if(elemCon->Tlg->getName()->Equals(tlgName))
		{
			flag = true;
      tlg = elemCon->Tlg;
		}
		else
		{
			i++;
		}
	}
  return tlg;
}
//----------------------------------------------------
