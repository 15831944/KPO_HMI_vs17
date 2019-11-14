// Copyright 2006 SMS - Demag AG

#ifndef _CInterUseCase_H_
#define _CInterUseCase_H_
//------------------------------------------
using namespace System;
using namespace System::Collections;
//------------------------------------------
//-------------------------------------------
// Name:  CInterUseCase.h
// Descr: Mit der Klasse wird die Aufteilung der Telegrammen einer Schnittstelle
//        aif verschiedene Gruppen(Use-Case) gemacht
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
public ref class  CInterUseCase
{
	public:
			~CInterUseCase();
			static CInterUseCase^ getInterUseCase(String^ inter);
			String^ getInterfaceName();
			void setInterfaceName(String^ interName);
			void addUseCase(String^ name,String^ description,array <String^>^ items);
			int getUseCaseCount();
			String^ getUseCaseName(int index);
			array <String^>^ getUseCaseTelName(String^ useCaseName);
			void clearUseCaseInfo();
			value struct UseCaseInfoTyp
			{
				String^ Name;
				String^ Description;
				array <String^>^ Items;
			};
	protected:
			CInterUseCase();

	private:
			static ArrayList^ InterUseCaseListe = gcnew ArrayList();
			String^ Interface;
			ArrayList^ UseCaseInfoListe;
		   
			UseCaseInfoTyp^ findUseCaseName(String^ name);
			
};
//-------------------------------------------

#endif