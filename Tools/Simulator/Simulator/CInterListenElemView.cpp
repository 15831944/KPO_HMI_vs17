// Copyright 2006 SMS - Demag AG
//-----------------------------------------------------------------------
#include "stdafx.h"
#include "CInterListenElemView.h"
//-----------------------------------------------------------------------
CInterListenElemView^ CInterListenElemView::getInterListenElemView(String^ interName)
{
	CInterListenElemView^ ret = nullptr;
	CInterListenElemView^ listenElem=nullptr;
	int i;
	bool flag;
	int count = InterListe->Count;

	i=0;
	flag=false;
	while((!flag) && (i<count))
	{
		listenElem = safe_cast<CInterListenElemView^>(InterListe[i]);
		if(listenElem->getInterName()->Equals(interName))
		{
			ret = listenElem;
			flag=true;
		}
		else
		{
			i++;
		}
	}
	if(!flag)
	{
		ret = gcnew CInterListenElemView();
		InterListe->Add(ret);
		ret->setInterName(interName);
	}
	return ret;
}
//------------------------------------------------------------------------
String^ CInterListenElemView::getInterName()
{
	return InterfaceName;
}
//------------------------------------------------------------------------
void CInterListenElemView::setInterName(String^ interName)
{
	InterfaceName = interName;
}
//------------------------------------------------------------------------
CInterListenElemView::~CInterListenElemView()
{
}
//------------------------------------------------------------------------
CInterListenElemView::CInterListenElemView()
{
	ListenElemArray = gcnew ArrayList();
}
//-------------------------------------------------------------------------
void CInterListenElemView::addListenElem(String^ elemName,String^ tlgName,int count,array <String^>^ rows)
{
	ListenElemTyp^ listenElem = gcnew ListenElemTyp();
	listenElem->Count = count;
	listenElem->ElemName = elemName;
	listenElem->TlgName = tlgName;
	listenElem->Rows = rows;
	ListenElemArray->Add(listenElem);
}
//-------------------------------------------------------------------------
String^ CInterListenElemView::getElemName(int index)
{
	ListenElemTyp^ elemListe = safe_cast<ListenElemTyp^>(ListenElemArray[index-1]);
	return elemListe->ElemName;
}
//--------------------------------------------------------------------------
String^ CInterListenElemView::getTlgName(int index)
{
	ListenElemTyp^ elemListe = safe_cast<ListenElemTyp^>(ListenElemArray[index-1]);
	return elemListe->TlgName;
}
//-------------------------------------------------------------------------
array <String^>^ CInterListenElemView::getRows(int index)
{
	ListenElemTyp^ elemListe = safe_cast<ListenElemTyp^>(ListenElemArray[index-1]);
	return elemListe->Rows;
}
//-------------------------------------------------------------------------
int CInterListenElemView::getElemCount(int index)
{
	return ListenElemArray->Count;
}
//-----------------------------------------------------------------------
array <String^>^ CInterListenElemView::getRowListe(String^ tlg,String^ elem)
{
	array <String^>^ ret=nullptr;
	bool flag;
	int i,count;

	count = ListenElemArray->Count;
	i=0;
	flag=false;
	ListenElemTyp^ liste=nullptr;
	while((!flag) && (i<count))
	{
		liste = safe_cast<ListenElemTyp^>(ListenElemArray[i]);
		if((liste->TlgName->Equals(tlg)) && (liste->ElemName->Equals(elem)))
		{
			ret = liste->Rows;
			flag=true;
		}
		else
		{
			i++;
		}
	}

	return ret;
}
//-------------------------------------------------------------------------