#include "StdAfx.h"
#include "CInterConfigForm.h"

using namespace simulator;

//-----------------------------------------------
System::Void CInterConfigForm::OnLoadForm(System::Object ^  sender, System::EventArgs ^  e)
{
  initAvailableInterface();
}
//-----------------------------------------------
System::Void CInterConfigForm::OnSelectedIndexChanged(System::Object ^  sender, System::EventArgs ^  e)
{
  int index = listBoxAvailInter->SelectedIndex;
  String^ itemStr = listBoxAvailInter->Text;
  
  CAppSetting^ Sett = CAppSetting::getApp();
  String^ path = Sett->getInterConfigFilePath(itemStr);
  labIncfPath->Text = path;
  
  updateInterfaceInfo(itemStr);
}
//-----------------------------------------------
System::Void CInterConfigForm::OnButAplyClick(System::Object ^  sender, System::EventArgs ^  e)
{
  if (listBoxAvailInter->SelectedIndex>= 0)
  {
    updateConfFileFromView();
	  addInterfaceToUpdateListe();
  }
}
//-----------------------------------------------
System::Void CInterConfigForm::OnButOkClick(System::Object ^  sender, System::EventArgs ^  e)
{
	if (listBoxAvailInter->SelectedIndex>= 0)
  {
    try 
    {
      updateConfFileFromView();
	    addInterfaceToUpdateListe();
    }
    catch (System::Xml::XmlException^ e)
    {
      //
    }
	}
  Close();
}
//-----------------------------------------------
System::Void CInterConfigForm::OnButtCancelClick(System::Object ^  sender, System::EventArgs ^  e)
{
	Close();
}
//-----------------------------------------------
System::Void CInterConfigForm::OnButBrowseClick(System::Object ^  sender, System::EventArgs ^  e)
{
	OpenFileDialog^ fileConfDialog = gcnew OpenFileDialog();
	// !!!
	fileConfDialog->Filter="Interface Configuration File(*.icnf)|*.icnf";

  if(fileConfDialog->ShowDialog() == ::DialogResult::OK)
	{
		txtBxBrowse->Text = fileConfDialog->FileName;
		int index = listBoxAvailInter->SelectedIndex;
		String^ itemStr = listBoxAvailInter->Text;
		CAppSetting^ Sett = CAppSetting::getApp();
		Sett->addInterfaceConfigFile(txtBxBrowse->Text,itemStr);
		//CInterConfigWrapper^ confWr = gcnew CInterConfigWrapper();
		//confWr->readInterConfigurationFile(itemStr,txtBxBrowse->Text);
		updateInterfaceInfo(itemStr);
	}
}
//-----------------------------------------------
void CInterConfigForm::setInterfaceList(List<CTlgInterfaceWrapper^>^ liste)
{
  InterfaceList = liste;
}
//-----------------------------------------------
void CInterConfigForm::setActiveInterface(String^ inter)
{
  ActiveInterface = inter;
}
//-----------------------------------------------
void CInterConfigForm::initAvailableInterface()
{
  int count,i;
  int interAct;
  String^ interName=nullptr;
  CTlgInterfaceWrapper^ inter=nullptr;

  listBoxAvailInter->Items->Clear();

  //listViewAvailInter->set_View(System::Windows::Forms::View::Details);

  count = InterfaceList->Count;
  for(i=0;i<count;i++)
  {
    inter = InterfaceList[i];
    interName=inter->getInterfaceName();
    listBoxAvailInter->Items->Add(interName);
  }
  interAct = getActInterfaceNummber();
    
  if(interAct < 0)
  {
    interAct = 0;
  }

  if(listBoxAvailInter->Items->Count > interAct)
  {
    listBoxAvailInter->SelectedIndex = interAct;
  }
}
//-----------------------------------------------
int CInterConfigForm::getActInterfaceNummber()
{
  int ret=-1;
  int count,i;
  CTlgInterfaceWrapper^ inter=nullptr;
  bool flag = false;

  i=0;
  count = InterfaceList->Count;
  while((!flag) && (i<count))
  {
     inter = InterfaceList[i];
     if(inter->getInterfaceName()->Equals(ActiveInterface))
     {
       ret = i;
       flag=true;
     }
     else
     {
        i++;
     }
  }
  return ret;
}
//-----------------------------------------------
void CInterConfigForm::updateInterfaceInfo(String^ inter)
{
  CTlgInterfaceWrapper^ tlgInter =nullptr;
	String^ path = nullptr;
  tlgInter = getInterface(inter);
  if(tlgInter)
  {
    this->labInterVer->Text = tlgInter->getInterfaceVersion();
    this->labDescr->Text = tlgInter->getInterfaceDescr();

    TlgIdentForm->setInterface(tlgInter);
    LogFileConfigForm->setInterface(tlgInter);
	  TlgTranspConfigForm->setInterface(tlgInter);
	  LimitValueSettingForm->setInterface(tlgInter);
    //ArrayViewConfigForm->setInterface(tlgInter);
	  UseCaseConfigForm->setInterface(tlgInter);

	  CAppSetting^ Sett = CAppSetting::getApp();
	  path=Sett->getInterConfigFilePath(tlgInter->getInterfaceName());
	  txtBxBrowse->Text = path;
  }
}
//-----------------------------------------------
CTlgInterfaceWrapper^ CInterConfigForm::getInterface(String^ inter)
{
  CTlgInterfaceWrapper^ ret=nullptr;
  int count,i;
  CTlgInterfaceWrapper^ tlgInter =nullptr;
  bool flag = false;

  i=0;
  count = InterfaceList->Count;
  while((!flag) && (i<count))
  {
     tlgInter = InterfaceList[i];
     if(tlgInter->getInterfaceName()->Equals(inter))
     {
       ret = tlgInter;
       flag=true;
     }
     else
     {
        i++;
     }
  }

  return ret;
}
//-----------------------------------------------
void CInterConfigForm::initViewComponet()
{
	TlgIdentForm = gcnew CTlgIdentForm();
	TlgIdentForm->TopLevel = false;
	TlgIdentForm->Parent = tabPageTlgId;
	TlgIdentForm->Dock = System::Windows::Forms::DockStyle::Fill;
	TlgIdentForm->Show();

	LogFileConfigForm = gcnew CLogFileConfigForm();
	LogFileConfigForm->TopLevel = false;
	LogFileConfigForm->Parent = tabPageLogFile;
	LogFileConfigForm->Dock = System::Windows::Forms::DockStyle::Fill;
	LogFileConfigForm->Show();

	TlgTranspConfigForm = gcnew CTlgTranspConfigForm();
	TlgTranspConfigForm->TopLevel = false;
	TlgTranspConfigForm->Parent = tabPageTransp;
	TlgTranspConfigForm->Dock = System::Windows::Forms::DockStyle::Fill;
	TlgTranspConfigForm->Show();

	LimitValueSettingForm = gcnew CLimValSettingForm();
	LimitValueSettingForm->TopLevel = false;
	LimitValueSettingForm->Parent = tabPageLimVal;
	LimitValueSettingForm->Dock = System::Windows::Forms::DockStyle::Fill;
	LimitValueSettingForm->Show();

	//ArrayViewConfigForm = gcnew CArrayViewConfigForm();
	//ArrayViewConfigForm->TopLevel = false;
	//ArrayViewConfigForm->Parent = tabPageArrayView;
	//ArrayViewConfigForm->Dock = System::Windows::Forms::DockStyle::Fill;
	//ArrayViewConfigForm->Show();

	UseCaseConfigForm = gcnew CInterUseCaseConfigForm();
	UseCaseConfigForm->TopLevel = false;
	UseCaseConfigForm->Parent = tabPageUseCase;
	UseCaseConfigForm->Dock = System::Windows::Forms::DockStyle::Fill;
	UseCaseConfigForm->Show();
}
//-----------------------------------------------
void CInterConfigForm::updateConfFileFromView()
{
	int index = tabCntrlInter->SelectedIndex;
	if(index == 0)
	{
    TlgIdentForm->updateConfFileFromView();	
	}
	if(index == 1)
	{
		LogFileConfigForm->updateConfFileFromView();
	}
	if(index == 2)
	{
		TlgTranspConfigForm->updateConfFileFromView();
	}
	if(index == 3)
	{
		LimitValueSettingForm->updateConfFileFromView();
	}
  if(index == 4)
	{
		UseCaseConfigForm->updateConfFileFromView();
	}

	//if(index == 4)
	//{
	//	//ArrayViewConfigForm->updateConfFileFromView();
	//}
	//if(index == 5)
	//{
	//	UseCaseConfigForm->updateConfFileFromView();
	//}
}
//-----------------------------------------------
void CInterConfigForm::addInterfaceToUpdateListe()
{
	int index;
	String^ interName;

	interName=listBoxAvailInter->Items[listBoxAvailInter->SelectedIndex]->ToString();
	index=UpdateInterfaceListe->IndexOf(interName);
	if(index == -1)
  {
		UpdateInterfaceListe->Add(interName);
  }
}
//-----------------------------------------------
array <String^>^ CInterConfigForm::getUpdateInterfacListe()
{
	array <String^>^ ret = nullptr;
	int count = UpdateInterfaceListe->Count;
	ret = gcnew array <String^> (count);

	for(int i=0;i<count;i++)
	{
		ret[i] = System::Convert::ToString(UpdateInterfaceListe[i]);
	}

	return ret;
}
//-----------------------------------------------
