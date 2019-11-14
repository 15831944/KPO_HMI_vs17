#include "StdAfx.h"
#include "CLogWriterWrapper.h"
#include "CTlgIdentForm.h"

using namespace simulator;
//-------------------------------------------------------------------------------------------
System::Void CTlgIdentForm::OnListBoxIndexChange(System::Object ^  sender, System::EventArgs ^  e)
{
  int index = listBxIdElemChouse->SelectedIndex;
  CItemWrapper^ tlgWr = gcnew CTlgWrapper();

  CXmlInterConfigReader^ confFileReader = gcnew CXmlInterConfigReader();
  CAppSetting^ Sett = CAppSetting::getApp();
  String^ confPath = Sett->getInterConfigFilePath(Interface->getInterfaceName());

  confFileReader->setInterConfigFile(confPath);

  String^ elemIdName = nullptr;
  String^ tlgIdName = nullptr;
  confFileReader->setSectionFocus("TelegramId");
  confFileReader->getElemIdName(tlgIdName,elemIdName);
  
  Interface->getFlatTlg(tlgWr,tlgIdName);

  //labElemInterDescr->Text = tlgWr->getElemDescr(index+1);
}
//--------------------------------------------------------------------------------------------
System::Void CTlgIdentForm::OnKeyDown(System::Object ^  sender, System::Windows::Forms::KeyEventArgs ^  e)
{
  System::Windows::Forms::Keys key = e->KeyCode;
  if((key == System::Windows::Forms::Keys::Down) || (key == System::Windows::Forms::Keys::Up))
  {
    int index = getTlgIdIndex();
    if(index != -1)
    {
      TextBox^ txtBx = nullptr;
      int count = TlgIdList->Count;
      if((key == System::Windows::Forms::Keys::Up) && (index < count-1))
      {
        txtBx = safe_cast<TextBox^>(TlgIdList[index+1]);
        txtBx->Focus();
      }
      if((key == System::Windows::Forms::Keys::Down) && (index > 0))
      {
         txtBx = safe_cast<TextBox^>(TlgIdList[index-1]);
         txtBx->Focus();
      }
    }
  }
}
//--------------------------------------------------------------------------------------------
System::Void CTlgIdentForm::OnCheckBoxClick(System::Object ^  sender, System::EventArgs ^  e)
{
  System::Windows::Forms::CheckBox^ checkBx = nullptr;
  System::Windows::Forms::Control^ con = nullptr;
  checkBx = safe_cast<System::Windows::Forms::CheckBox^>(sender);
  con=checkBx->Parent;
  if(con == panLenId)
  {
    changeIdElement(ElemLenChouse,checkBx);
  }
  if(con == panId)
  {
    changeIdElement(ElemIdChouse,checkBx);
  }
}
//--------------------------------------------------------------------------------------------
System::Void CTlgIdentForm::OnCheckBoxIdNameChecked(System::Object ^  sender, System::EventArgs ^  e)
{
  bool flag = checkBxNameId->Checked;
  TextBox^ txtBx = nullptr;
  Label^ lab = nullptr;
  int count,i;

  count = TlgIdList->Count;
  for(i=0;i<count;i++)
  {
    txtBx = safe_cast<TextBox^>(TlgIdList[i]);
    if(flag)
  {
      lab = safe_cast<Label^>(TlgNameList[i]);
      txtBx->Text = lab->Text;
    }
    else
    {
      txtBx->Text = "";
    }
  }
}
//--------------------------------------------------------------------------------------------
System::Void CTlgIdentForm::OnSelIndexChange(System::Object ^  sender, System::EventArgs ^  e)
{
	//if(comBxModi->Text->Equals("Id"))
  //{
	//	panLenConfig->Visible=false;
	//	panIdConfig->Dock=DockStyle::Fill;
	//	panIdConfig->Visible=true;
	//	checkBxNameId->Visible=true;

	//}
	//else
	//{
	//	panIdConfig->Visible=false;
	//	panLenConfig->Dock = DockStyle::Fill;
	//	panLenConfig->Visible = true;
	//	checkBxNameId->Visible=false;
	//}
}
//--------------------------------------------------------------------------------------------
void CTlgIdentForm::setInterface(CTlgInterfaceWrapper^ inter)
{
//String^ path;
  Interface = inter;
  updateViewFromConfFile();
}
//--------------------------------------------------------------------------------------------
void CTlgIdentForm::updateViewFromConfFile()
{
  CAppSetting^ Sett = CAppSetting::getApp();
  String^ confPath = Sett->getInterConfigFilePath(Interface->getInterfaceName());
  CXmlInterConfigReader^ confFileReader = gcnew CXmlInterConfigReader();
  confFileReader->setInterConfigFile(confPath);

  initIdChouse(confFileReader);
  initIdInfo(confFileReader);
	setIdInfo(confFileReader);
  checkBxNameId->Checked = false;
	//comBxModi->SelectedIndex = 0;
}
//--------------------------------------------------------------------------------------------
void CTlgIdentForm::updateConfFileFromView()
{
  bool flagSec;
  String^ name=nullptr;
  String^ len = nullptr;
  String^ typ;
	String^ treatLenId;
  TextBox^ txtBx = nullptr;
  Label^ lab = nullptr;
  int count,i;
  CAppSetting^ Sett = CAppSetting::getApp();
	String^ path = Sett->getInterConfigFilePath(Interface->getInterfaceName());
  //String^ HeaderTlg = Sett->getHeaderTlg();

	CXmlInterConfigWriter^ interConfWr = gcnew CXmlInterConfigWriter();
	interConfWr->loadInterConfigFile(path);
  flagSec = interConfWr->setSectionFocus("TelegramId");
  if(flagSec)
  {
	  // interConfWr->setSectionFocus("UseCase");
    interConfWr->beginUpdate();
    name = getElemIdName();
    len = getElemLenIdName();
    typ = getElemTypId();
		if(radButTotal->Checked)
		{
			treatLenId="Total Length";
		}
		else
		{
			if(radButtBody->Checked)
			{
				treatLenId="Body Length";
			}
			else
			{
				treatLenId="User Defined";
			}
		}

    CXmlInterConfigReader^ confFileReader = gcnew CXmlInterConfigReader();
    CAppSetting^ Sett = CAppSetting::getApp();
    String^ confPath = Sett->getInterConfigFilePath(Interface->getInterfaceName());

    confFileReader->setInterConfigFile(confPath);

    String^ elemIdName = nullptr;
    String^ tlgIdName = nullptr;
    confFileReader->setSectionFocus("TelegramId");
    confFileReader->getElemIdName(tlgIdName,elemIdName);

    interConfWr->setTelIdInfo(tlgIdName,name,typ,len,treatLenId);
    //interConfWr->setTelIdInfo(HeaderTlg,name,typ,len,treatLenId);
    count = TlgNameList->Count;
    for(i=0;i<count;i++)
    {
      txtBx = safe_cast<TextBox^>(TlgIdList[i]);
      lab = safe_cast<Label^>(TlgNameList[i]);
      interConfWr->setTelId(lab->Text,txtBx->Text);
     }
		interConfWr->endUpdate();
  }
}
//--------------------------------------------------------------------------------------------
void CTlgIdentForm::initIdChouse(CXmlInterConfigReader^ confFileReader)
{
  int count,i;
  String^ name = nullptr;
  String^ type = nullptr;
  int len = 0;
  String^ telIdName = nullptr;
  String^ elemIdName = nullptr;
  String^ typId = nullptr;
  String^ elemLenName = nullptr;
	String^ treatLen = nullptr;

  confFileReader->setSectionFocus("TelegramId");
  confFileReader->getTelIdInfo(telIdName,elemIdName,typId,elemLenName,treatLen);

  try
  {
	  setTreatLenModus(treatLen);
      //CInterConfigWrapper^ interConfWr = gcnew CInterConfigWrapper();
      //idTlg = interConfWr->getTlgIdName(Interface->getInterfaceName());

    if (typId->Equals("String"))
      checkBxNameId->Enabled=true;
    else
      checkBxNameId->Enabled=false;
    
    if(telIdName)
    {
      CItemWrapper^ tlgWr = gcnew CTlgWrapper();
      listBxIdElemChouse->Items->Clear();
      Interface->getFlatTlg(tlgWr,telIdName);
      count=tlgWr->getTlgElemCount();
      for(i=1;i<=count;i++)
      {
        name = tlgWr->getElemName(i);
        type = tlgWr->getElemTypAsString(i);
        len = tlgWr->getElemLen(i);
        listBxIdElemChouse->Items->Add(String::Concat(name,"\t",type,"  ",System::Convert::ToString(len)));
      }
      initLenIdCheckBox(telIdName,elemIdName,elemLenName);
    }
  }
  catch(...)
  {
    String^ mess = System::String::Concat("The name of the element <",telIdName,"> was not found in interface.");

    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,
																													__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
		System::Windows::Forms::MessageBox::Show(nullptr,mess,
                                      "",
                                      MessageBoxButtons::OK,
                                      MessageBoxIcon::Warning);
  }
}
//--------------------------------------------------------------------------------------------
void CTlgIdentForm::initIdInfo(CXmlInterConfigReader^ confFileReader)
{
  int count,i;
  Panel^ pan=nullptr;
  TextBox^ txtBx=nullptr;
  Label^ lab;
  CItemWrapper^ tlgWr = gcnew CTlgWrapper();

  panIdConfig->Controls->Clear();
  for(i=0;i<TlgIdList->Count;i++)
  {
    txtBx= safe_cast<TextBox^>(TlgIdList[i]);
    delete txtBx;
    lab = safe_cast<Label^>(TlgNameList[i]);
    delete lab;
    pan = safe_cast<Panel^>(TlgIdPanList[i]);
    delete pan;
  }
  TlgIdList->Clear();
  TlgNameList->Clear();
  TlgIdPanList->Clear();
  count = Interface->getTlgCount();
    
  panIdConfig->Visible = false;
  panIdConfig->SuspendLayout();
  for(i=1;i<=count;i++)
  {
    pan = gcnew Panel();
    TlgIdPanList->Add(pan);
    pan->Height = 20;
    pan->BorderStyle=BorderStyle::FixedSingle;
    pan->Dock = DockStyle::Top;
    panIdConfig->Controls->Add(pan);
    txtBx = gcnew TextBox();
    lab = gcnew Label();
    TlgIdList->Add(txtBx);
    TlgNameList->Add(lab); 
    lab->Width = 150;
    txtBx->Dock = DockStyle::Fill;
    lab->Dock = DockStyle::Left;
    //txtBx->Dock = DockStyle::Right;
    pan->Controls->Add(txtBx);
    pan->Controls->Add(lab);
    
    Interface->getClonedTlg(tlgWr,i);
    lab->Text = tlgWr->getName();
    
    txtBx->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &CTlgIdentForm::OnKeyDown);
  }
  panIdConfig->ResumeLayout();
  panIdConfig->AutoScroll = true;
  panIdConfig->Visible = true;
}
//--------------------------------------------------------------------------------------------
int CTlgIdentForm::getTlgIdIndex()
{
  int ret = -1;
  int count,i;
  bool flag;
  TextBox^ txtBx = nullptr;

  count=TlgIdList->Count;
  flag = false;
  i=0;
  while((!flag) && (i<count))
  {
    txtBx = safe_cast<TextBox^>(TlgIdList[i]);
    if(txtBx->Focused)
    {
      flag=true;
      ret = i;
    }
    else
    {
      i++;
    }
  }
  return ret;
}
//--------------------------------------------------------------------------------------------
void CTlgIdentForm::initLenIdCheckBox(String^ telName,String^ idElem,String^ lenElem)
{
  int i,count;
  System::Windows::Forms::CheckBox^ checkBx = nullptr;
  CItemWrapper^ tlgWr = gcnew CTlgWrapper();
  ElemIdChouse->Clear();
  ElemLenChouse->Clear();

  panId->Visible = false;
  panLenId->Visible = false;
  panId->SuspendLayout();
  panLenId->SuspendLayout();
  panId->Controls->Clear();
  panLenId->Controls->Clear();

  Interface->getFlatTlg(tlgWr,telName);
  count = tlgWr->getTlgElemCount();
  for(i=0;i<count;i++)
  {
    checkBx = gcnew System::Windows::Forms::CheckBox();
    checkBx->Height = 13;
    checkBx->Dock = DockStyle::Top;
    checkBx->Click += gcnew System::EventHandler(this, &CTlgIdentForm::OnCheckBoxClick);
    ElemIdChouse->Add(checkBx);
    panId->Controls->Add(checkBx);

    checkBx = gcnew System::Windows::Forms::CheckBox();
    checkBx->Height = 13;
    checkBx->Dock = DockStyle::Top;
    checkBx->Click += gcnew System::EventHandler(this, &CTlgIdentForm::OnCheckBoxClick);
    ElemLenChouse->Add(checkBx);
    panLenId->Controls->Add(checkBx);
  }
  checkElement(ElemIdChouse,idElem);
	checkElement(ElemLenChouse,lenElem);
  panId->ResumeLayout();
  panId->Visible = true;
  panLenId->ResumeLayout();
  panLenId->Visible = true;
}
//--------------------------------------------------------------------------------------------
void CTlgIdentForm::changeIdElement(ArrayList^ list,CheckBox^ checkBx)
{
  CheckBox^ box=nullptr;
  int count,i;
  count = list->Count;
  for(i=0;i<count;i++)
  {
    box = safe_cast<System::Windows::Forms::CheckBox^>(list[i]);
    box->Checked = false;
  }
  checkBx->Checked = true;
}
//--------------------------------------------------------------------------------------------
String^ CTlgIdentForm::getElemIdName()
{
  String^ ret = nullptr;
  int index = 0;
  CItemWrapper^ tlgWr = gcnew CTlgWrapper();

  CXmlInterConfigReader^ confFileReader = gcnew CXmlInterConfigReader();
  CAppSetting^ Sett = CAppSetting::getApp();
  String^ confPath = Sett->getInterConfigFilePath(Interface->getInterfaceName());

  confFileReader->setInterConfigFile(confPath);

  String^ elemIdName = nullptr;
  String^ tlgIdName = nullptr;
  confFileReader->setSectionFocus("TelegramId");
  confFileReader->getElemIdName(tlgIdName,elemIdName);

  index = getIdIndex(ElemIdChouse);
  Interface->getFlatTlg(tlgWr,tlgIdName);
  ret = tlgWr->getElemName(index+1);

  return ret;
}
//--------------------------------------------------------------------------------------------
String^ CTlgIdentForm::getElemLenIdName()
{
  String^ ret = nullptr;
  int index = 0;
  // len = 0;
  CItemWrapper^ tlgWr = gcnew CTlgWrapper();

  CXmlInterConfigReader^ confFileReader = gcnew CXmlInterConfigReader();
  CAppSetting^ Sett = CAppSetting::getApp();
  String^ confPath = Sett->getInterConfigFilePath(Interface->getInterfaceName());

  confFileReader->setInterConfigFile(confPath);

  String^ elemIdName = nullptr;
  String^ tlgIdName = nullptr;
  confFileReader->setSectionFocus("TelegramId");
  confFileReader->getElemIdName(tlgIdName,elemIdName);


  index = getIdIndex(ElemLenChouse);
  Interface->getFlatTlg(tlgWr,tlgIdName);

  ret = tlgWr->getElemName(index+1);
 // ret = System::Convert::ToString(len);

  return ret;
}
//--------------------------------------------------------------------------------------------
String^ CTlgIdentForm::getElemTypId()
{
  String^ ret = nullptr;
  int index = 0;
  CItemWrapper^ tlgWr = gcnew CTlgWrapper();

  CXmlInterConfigReader^ confFileReader = gcnew CXmlInterConfigReader();
  CAppSetting^ Sett = CAppSetting::getApp();
  String^ confPath = Sett->getInterConfigFilePath(Interface->getInterfaceName());

  confFileReader->setInterConfigFile(confPath);

  String^ elemIdName = nullptr;
  String^ tlgIdName = nullptr;
  confFileReader->setSectionFocus("TelegramId");
  confFileReader->getElemIdName(tlgIdName,elemIdName);

  index = getIdIndex(ElemIdChouse);
  Interface->getFlatTlg(tlgWr,tlgIdName);
  ret = tlgWr->getElemTypAsString(index+1);
  return ret;
}
//--------------------------------------------------------------------------------------------
int CTlgIdentForm::getIdIndex(ArrayList^ list)
{
  int ret = 0;
  int count,i;
  bool flag;
  CheckBox^ checkBx=nullptr;

  count = list->Count;
  flag=false;
  i=0;
  while((!flag) && (i<count))
  {
    checkBx = safe_cast<CheckBox^>(list[i]);
    if(checkBx->Checked)
    {
      flag = true;
      ret = count - i-1;
    }
    else
    {
       i++;
    }
  }

  return ret;
}
//--------------------------------------------------------------------------------------------
void CTlgIdentForm::setIdInfo(CXmlInterConfigReader^ confFileReader)
{
  TextBox^ txtBx = nullptr;
  Label^ lab = nullptr;
  confFileReader->setSectionFocus("TelegramId");
  for(int i=0;i<TlgIdList->Count;i++)
  {
    txtBx= safe_cast<TextBox^>(TlgIdList[i]);
    lab = safe_cast<Label^>(TlgNameList[i]);
    txtBx->Text = confFileReader->getTlgId(lab->Text);
  }
}
//--------------------------------------------------------------------------------------------
void CTlgIdentForm::setIdElements()
{
    //String^ idTel = nullptr;
    //String^ idLen = nullptr;
    //CInterConfigWrapper^ interConfWr = gcnew CInterConfigWrapper();
    //idTel = interConfWr->getElemId(Interface->getInterfaceName());
    //idLen = interConfWr->getElemLenId(Interface->getInterfaceName());
	//checkElement(ElemIdChouse,idTel);
	//checkElement(ElemLenChouse,idLen);
}
//--------------------------------------------------------------------------------------------
void CTlgIdentForm::checkElement(ArrayList^ list,String^ elem)
{
  CInterConfigWrapper^ interConfWr = gcnew CInterConfigWrapper();
  String^ telName = nullptr;
	int index,count;
  CItemWrapper^ tlgWr = gcnew CTlgWrapper();
  telName = interConfWr->getTlgIdName(Interface->getInterfaceName());
  Interface->getFlatTlg(tlgWr,telName);
	index = tlgWr->getElemIndex(elem);
	if(index != -1)
	{
		count = list->Count;
		CheckBox^ chBx = safe_cast<CheckBox^>(list[count-index]); 
		chBx->Checked = true;
	}
}
//--------------------------------------------------------------------------------------------
void CTlgIdentForm::setTreatLenModus(String^ mode)
{
	if(mode->Equals("Total Length"))
	{
		radButTotal->Checked = true;
	}
	else
	{
		if(mode->Equals("Body Length"))
		{
			radButtBody->Checked = true;
		}
		else
		{
			radButtUserDef->Checked = true;
		}
	}
}