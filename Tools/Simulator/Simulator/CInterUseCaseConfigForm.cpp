#include "StdAfx.h"
#include "CInterUseCaseConfigForm.h"
#include "CLogWriterWrapper.h"

//------------------------------------------------------------------
using namespace simulator;
//------------------------------------------------------------------
System::Void CInterUseCaseConfigForm::OnButAddToUseCaseClick(System::Object ^  sender, System::EventArgs ^  e)
{
  String^ mess = nullptr;
	if (UseCaseInfoListe->Count!=0)
  {
    if (listBxUseCase->SelectedIndex != -1) 
    {
      int count,i;
      int index;
      String^ telName = nullptr;
      CItemWrapper^ wrTlg = gcnew CTlgWrapper();
      System::Windows::Forms::CheckedListBox::CheckedIndexCollection^ indexCol = nullptr;
      indexCol = checkListBxAllTlg->CheckedIndices;
      count=indexCol->Count;

      int index1 = listBxUseCase->SelectedIndex;
      UseCaseInfo^ useCaseIn = safe_cast<UseCaseInfo^>(UseCaseInfoListe[index1]);
      for(i=0;i<count;i++)
      {
	      index=indexCol[i];
	      Interface->getClonedTlg(wrTlg,index+1);
	      telName = wrTlg->getName();
	      index = checkListBxUseCaseTlg->Items->IndexOf(telName);
	      if(index < 0)
        {
		      checkListBxUseCaseTlg->Items->Add(telName,true);
          //checkListBxUseCaseTlg->Items->Add(telName,false);
          if(useCaseIn->Items != nullptr)
            useCaseIn->Items = String::Concat(useCaseIn->Items,",");
          useCaseIn->Items = String::Concat(useCaseIn->Items,telName);
        }
      }
    }
    else
    {
      mess = "No use case is selected.";
			CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,
																														__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
			MessageBox::Show(mess,"", MessageBoxButtons::OK,MessageBoxIcon::Warning);
    }
  }
  else
  {
    mess = "No use case is created.";
		CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,
																													__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
		MessageBox::Show(mess,"", MessageBoxButtons::OK,MessageBoxIcon::Warning);
  }
}
//------------------------------------------------------------------
System::Void CInterUseCaseConfigForm::OnButRemFromUseCaseClick(System::Object ^  sender, System::EventArgs ^  e)
{
	int count;
	int index;
	bool flag = false;

	System::Windows::Forms::CheckedListBox::CheckedIndexCollection^ indexCol = nullptr;
	checkListBxUseCaseTlg->BeginUpdate();
	while(!flag)
	{
		indexCol = checkListBxUseCaseTlg->CheckedIndices;
		count = indexCol->Count;
		if(count > 0)
		{
			index = indexCol[0];
			checkListBxUseCaseTlg->Items->RemoveAt(index);
		}
		else
		{
			flag = true;
		}
	}
	checkListBxUseCaseTlg->EndUpdate();
    updateUseCaseInfoListe(listBxUseCase->SelectedItem->ToString());
}
//------------------------------------------------------------------
System::Void CInterUseCaseConfigForm::OnAddUseCaseClick(System::Object ^  sender, System::EventArgs ^  e)
{
  CNewUseCaseForm^ form = gcnew CNewUseCaseForm();
  if(form->ShowDialog() == System::Windows::Forms::DialogResult::OK)
  {
    String^ useCaseName = nullptr;
    array <String^>^ useCaseDescr;
    
    useCaseName = form->getUseCaseName();
    int length = useCaseName->Length;

    if (length > 2)
      length=3;
    
    //Wenn UseCaseName mit XML anfaengt, Fehler!
    if (useCaseName->Substring(0,length)->Equals("XML") || useCaseName->Substring(0,length)->Equals("xml") )
    {
      String^ mes = "Name cannot begin with 'xml' or 'XML' !";
			CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mes,
																															__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      System::Windows::Forms::MessageBox::Show(nullptr,mes,"Error");
    }
    //Wenn UseCaseName mit mit einer Zahl anfaengt, Fehler!
    else if ((useCaseName[0]>=48) && (useCaseName[0]<=56))
    {
      String^ mes = "Name cannot begin with decimal value!";
			CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mes,
																														__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      System::Windows::Forms::MessageBox::Show(nullptr,mes,"Error");
    }
    //Wenn UseCaseName ein Leerzeichen enthaelt
    else if (useCaseName->IndexOf(' ') != -1)
    {
      String^ mes = "Name cannot contain ' ' character!";
			CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mes,
																														__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      System::Windows::Forms::MessageBox::Show(nullptr,mes,"Error");
    }
    else
    {
      useCaseDescr = form->getUseCaseDescription();
      UseCaseInfo^ useCase = gcnew UseCaseInfo();
      useCase->Descr = useCaseDescr;
      useCase->Name = useCaseName;

      UseCaseInfoListe->Add(useCase);
      listBxUseCase->Items->Add(useCaseName);
    }
  }
}
//------------------------------------------------------------------
System::Void CInterUseCaseConfigForm::OnListBoxSelIndexChange(System::Object ^  sender, System::EventArgs ^  e)
{
  UseCaseInfo^ useCase = nullptr;
  int index = listBxUseCase->SelectedIndex;
  if(index > -1)
  {
    checkListBxUseCaseTlg->Items->Clear();
    useCase = safe_cast<UseCaseInfo^>(UseCaseInfoListe[index]);

    txtBxInterDescr->Lines = useCase->Descr;

    if(useCase->Items != nullptr)
    {
      String^ delimStr = ",";
      array <Char>^ delimiter = delimStr->ToCharArray();
      array <String^>^ it;
      it = useCase->Items->Split(delimiter);
      int count = it->Length;
      for(int i=0;i<count;i++)
      {
        checkListBxUseCaseTlg->Items->Add(it[i],false);
      }
    }
  }
}
//------------------------------------------------------------------
System::Void CInterUseCaseConfigForm::OnButRemoveClick(System::Object ^  sender, System::EventArgs ^  e)
{
  int index = listBxUseCase->SelectedIndex;
  listBxUseCase->BeginUpdate();
  listBxUseCase->Items->RemoveAt(index);
  listBxUseCase->EndUpdate();
  UseCaseInfoListe->RemoveAt(index);
  checkListBxUseCaseTlg->Items->Clear();
  //if(index > 0)
    //  listBxUseCase->SelectedIndex = index-1;
}
//------------------------------------------------------------------
void CInterUseCaseConfigForm::setInterface(CTlgInterfaceWrapper^ inter)
{
	Interface = inter;
	updateViewFromConfFile();   
}
//------------------------------------------------------------------
void CInterUseCaseConfigForm::updateViewFromConfFile()
{
	bool flag;
	flag = readUseCaseInfoFromConfFile();
	showAllTlg();
}
//------------------------------------------------------------------
bool CInterUseCaseConfigForm::readUseCaseInfoFromConfFile()
{
	bool flag;
	String^ Name = nullptr;
	String^ Descr = nullptr;
	String^ Items = nullptr;

	CAppSetting^ Sett = CAppSetting::getApp();
  String^ confPath = Sett->getInterConfigFilePath(Interface->getInterfaceName());
  CXmlInterConfigReader^ confFileReader = gcnew CXmlInterConfigReader();
  confFileReader->setInterConfigFile(confPath);
  flag = confFileReader->setSectionFocus("UseCase");
	
  if(flag)
	{
    UseCaseInfo^ useCase = nullptr;
    //String^ arr[];
    String^ delimStr = "\n";
    array <Char>^ delimiter = delimStr->ToCharArray();
		while(confFileReader->getNextUseCase(Name,Descr,Items))
		{
      listBxUseCase->Items->Add(Name);
      useCase = gcnew UseCaseInfo();
      useCase->Items = Items;
      useCase->Name = Name;
      useCase->Descr = Descr->Split(delimiter);
      UseCaseInfoListe->Add(useCase);
		}
    if(listBxUseCase->Items->Count > 0)
    {
      listBxUseCase->SelectedIndex = 0;
    }
	}
	return flag;
}
//------------------------------------------------------------------
void CInterUseCaseConfigForm::showAllTlg()
{
	int count,i;
	String^ telName = nullptr;
	String^ telDescr = nullptr;
	CItemWrapper^ wrTlg = gcnew CTlgWrapper();

	checkListBxAllTlg->Items->Clear();
	count = Interface->getTlgCount();
	for(i=1;i<=count;i++)
	{
		Interface->getClonedTlg(wrTlg,i);
		telName = wrTlg->getName();
		telDescr = wrTlg->getTlgDescr();
		checkListBxAllTlg->Items->Add(String::Concat(telName,"  (",telDescr,")"),false);
	}
}
//------------------------------------------------------------------
void CInterUseCaseConfigForm::updateConfFileFromView()
{
  CAppSetting^ Sett = CAppSetting::getApp();
	String^ path = Sett->getInterConfigFilePath(Interface->getInterfaceName());
	CXmlInterConfigWriter^ interConfWr = gcnew CXmlInterConfigWriter();
	interConfWr->loadInterConfigFile(path);
	interConfWr->setSectionFocus("UseCase");
  interConfWr->beginUpdate();

  int count = UseCaseInfoListe->Count;
  UseCaseInfo^ useCase = nullptr;
  for(int i=0;i<count;i++)
  {
		 useCase = safe_cast<UseCaseInfo^>(UseCaseInfoListe[i]);
		 interConfWr->addUseCase(useCase->Name,useCase->Descr,useCase->Items);
  }

  interConfWr->endUpdate();
}
//------------------------------------------------------------------
void CInterUseCaseConfigForm::updateUseCaseInfoListe(String^ useCaseName)
{
  int count,i;
  String^ itemName=nullptr;
  UseCaseInfo^ useCase = findUseCaseItem(useCaseName);
  if(useCase)
  { 
    count=checkListBxUseCaseTlg->Items->Count;
    for(i=0;i<count;i++)
    {
      itemName=checkListBxUseCaseTlg->Items[i]->ToString();
      if(i == 0)
      {
          useCase->Items = itemName;
      }
      else
      {
          useCase->Items = String::Concat(useCase->Items,itemName);
      }
      if(i<(count-1))
        useCase->Items = String::Concat(useCase->Items,",");
    }
  }
}
//------------------------------------------------------------------
CInterUseCaseConfigForm::UseCaseInfo^ CInterUseCaseConfigForm::findUseCaseItem(String^ useCaseName)
{
  UseCaseInfo^ ret=nullptr;
  UseCaseInfo^ temp=nullptr;
  int count,i;
  bool flag;

  count = UseCaseInfoListe->Count;
  i=0;
  flag=false;
  while((!flag) && (i<count))
  {
		temp = safe_cast<UseCaseInfo^>(UseCaseInfoListe[i]);
		if(temp->Name->Equals(useCaseName))
		{
			flag=true;
			ret=temp;
		}
		else
		{
			i++;
		}
  }
	return ret;
}
//------------------------------------------------------------------