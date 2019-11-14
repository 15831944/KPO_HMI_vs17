// Copyright 2006 SMS - Demag AG

//----------------------------------------------------------------------
#include "stdafx.h"
#include "CInterUseCase.h"
//----------------------------------------------------------------------
CInterUseCase::CInterUseCase()
{
	UseCaseInfoListe = gcnew ArrayList();
}
//----------------------------------------------------------------------
CInterUseCase::~CInterUseCase()
{
}
//----------------------------------------------------------------------
CInterUseCase^ CInterUseCase::getInterUseCase(String^ inter)
{
	CInterUseCase^ ret = nullptr;
	CInterUseCase^ useCase = nullptr;
	int count = InterUseCaseListe->Count;
	int i=0;
	bool flag=false;
	String^ interName=nullptr;


	while((!flag) && (i<count))
	{
		useCase = safe_cast<CInterUseCase^>(InterUseCaseListe[i]);
		interName=useCase->getInterfaceName();
		if(interName->Equals(inter))
		{
			flag=true;
			ret=useCase;
		}
		else
		{
			i++;
		}
	}
	if(ret == nullptr)
	{
		ret = gcnew CInterUseCase();
		ret->setInterfaceName(inter);
		InterUseCaseListe->Add(ret);
	}

	return ret;
}
//----------------------------------------------------------------------
String^ CInterUseCase::getInterfaceName()
{
	return Interface;
}
//----------------------------------------------------------------------
void CInterUseCase::setInterfaceName(String^ interName)
{
	Interface = interName;
}
//----------------------------------------------------------------------
void CInterUseCase::addUseCase(String^ name,String^ description,array <String^>^ items)
{
	UseCaseInfoTyp^ useCase = gcnew UseCaseInfoTyp();
	useCase->Name = name;
	useCase->Description = description;
	useCase->Items = items;
	UseCaseInfoListe->Add(useCase);
}
//----------------------------------------------------------------------
int CInterUseCase::getUseCaseCount()
{
	return UseCaseInfoListe->Count;
}
//----------------------------------------------------------------------
String^ CInterUseCase::getUseCaseName(int index)
{
	String^ ret = nullptr;
	UseCaseInfoTyp^ useCaseInfo = safe_cast<UseCaseInfoTyp^>(UseCaseInfoListe[index-1]);
	ret=useCaseInfo->Name;
	return ret;
}
//----------------------------------------------------------------------
array <String^>^ CInterUseCase::getUseCaseTelName(String^ useCaseName)
{
	UseCaseInfoTyp^ useCase=findUseCaseName(useCaseName);
	if(useCase)
		return useCase->Items;
	else
		return nullptr;
}
//----------------------------------------------------------------------
CInterUseCase::UseCaseInfoTyp^ CInterUseCase::findUseCaseName(String^ name)
{
	UseCaseInfoTyp^ ret=nullptr;
	UseCaseInfoTyp^ temp=nullptr;
	int count,i;
	bool flag;
	count=UseCaseInfoListe->Count;
	flag=false;
	i=0;
	while((!flag) && (i<count))
	{
		temp=safe_cast<UseCaseInfoTyp^>(UseCaseInfoListe[i]);
		if(temp->Name->Equals(name))
		{
			ret=temp;
			flag=true;
		}
		else
		{
			i++;
		}
	}

	return ret;
}
//----------------------------------------------------------------------
void CInterUseCase::clearUseCaseInfo()
{
	UseCaseInfoListe->Clear();
}
//----------------------------------------------------------------------

