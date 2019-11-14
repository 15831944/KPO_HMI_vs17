// Copyright 2006 SMS - Demag AG
#ifndef _CInterListenElemView_H_
#define _CInterListenElemView_H_

//-------------------------------------------------
using namespace System;
using namespace System::Collections;
//-------------------------------------------------
//-------------------------------------------
// Name:  CInterListenElemView.h
// Descr: Mit der Klasse wird Darstelleng Listenelementen
//        als mehrspaltige Tabele organisiert
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
public ref class CInterListenElemView
{
	public:
			//! gibt ein Objekt der Klasse CInterListenElemView zurueck
			static CInterListenElemView^ getInterListenElemView(String^ interName);
			~CInterListenElemView();

			String^ getInterName();
			void setInterName(String^ interName);
			void addListenElem(String^ elemName,String^ tlgName,int count,array <String^>^ rows);
			String^ getElemName(int index);
			String^ getTlgName(int index);
			array <String^>^ getRows(int index);
			int getElemCount(int index);
			array <String^>^ getRowListe(String^ tlg,String^ elem);
			value struct ListenElemTyp
			{
				String^ ElemName;
				String^ TlgName;
				array <String^>^ Rows;
				int Count;
			};
	protected:
			CInterListenElemView();
	private:
			static ArrayList^ InterListe = gcnew ArrayList();
			String^ InterfaceName;
			ArrayList^ ListenElemArray;
};

#endif