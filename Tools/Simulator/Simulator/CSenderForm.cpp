#include "StdAfx.h"
#include "CSenderForm.h"
#include "CItemView.h"
#include "CCyclicItemContainer.h"
#include "CLogWriterWrapper.h"
#include "CAutoCreateSzenarioForm.h"

using namespace simulator;

//------------------------------------
CSenderForm::CSenderForm(Panel^ parent)
{
  InitializeComponent();
  this->TopLevel = false;
  this->Parent = parent;
  this->Dock = DockStyle::Fill;
	this->FormBorderStyle = ::FormBorderStyle::None;
  SendSzenThread=nullptr;
  initViewComponent();
}
//------------------------------------
System::Void CSenderForm::splitHor_DoubleClick(System::Object^  sender, System::EventArgs^  e) 
{
  if (this->panMessage->Visible)
  {
    this->panMessage->Hide(); 
  }
  else
  {
    this->panMessage->Show();
  }
}
//------------------------------------

System::Void CSenderForm::splitVer2_DoubleClick(System::Object^  sender, System::EventArgs^  e) 
{
  if (this->panSzen->Visible)
  {
    if (this->panTlgFileReader->Visible)
    {
      this->panSzenAndConnStatus->Hide();
    }
  }
  else
  {
    this->panSzenAndConnStatus->Show();
  }
}
//--------------------------------------
System::Void CSenderForm::splitVer1_DoubleClick(System::Object^  sender, System::EventArgs^  e) 
{
  this->splitVer1->Size = System::Drawing::Size(3, 365);
  this->TlgTreeViewForm->Dock =DockStyle::Fill;

  if (this->panTlgFileReader->Visible)
  {
    if(this->panSzen->Visible)
    {
      this->panTlgFileReader->Hide(); 
    }
    else
    {
      this->panTlgFileReader->Show();
    }
  }
  else
  {
    this->panTlgFileReader->Show();
  }
}
//--------------------------------------
System::Void CSenderForm::OnLoadForm(System::Object ^  sender, System::EventArgs ^  e)
{
  TlgTreeViewForm->Show();
  TlgViewForm->Show();
  SzenariumForm->Show();
}
//---------------------------------------
System::Void CSenderForm::OnSizeChangedForm(System::Object ^  sender, System::EventArgs ^  e)
{
  this->panTlgFileReader->Width = this->Width/6;
  this->panMessage->Height = this->Height/6;
  this->panSzenAndConnStatus->Width = 202;
}
//------------------------------------------------------------------------------------------------------
System::Void CSenderForm::OnButtUseCaseClick(System::Object ^  sender, System::EventArgs ^  e)
{
  Button^ butt = safe_cast<Button^>(sender);
  TlgTreeViewForm->updateUseCaseView(ActiveInterface,butt->Text);
}
//------------------------------------------------------------------------------------------------------
void CSenderForm::initViewComponent()
{
  TlgTreeViewForm = gcnew CTlgTreeViewForm(this->panTlgFileReaderNew);
  
  CTlgContainerTreeViewForm::AfterSelectEvent^ event = gcnew CTlgContainerTreeViewForm::AfterSelectEvent(this,&CSenderForm::updateTlgPrototypView);
  TlgTreeViewForm->setAfterSelectTlgContainerEvent(event);
  
  CItemPrototypContainerForm::AfterSelectPrototypEvent^ eventPro = gcnew CItemPrototypContainerForm::AfterSelectPrototypEvent(this,&CSenderForm::																																						updateTlgPrototypView);
  TlgTreeViewForm->setAfterSelectPrototypEvent(eventPro);
  
  CTlgTreeViewForm::addToSzenDelTyp^ addToSzen = gcnew CTlgTreeViewForm::addToSzenDelTyp(this,&CSenderForm::addToSzenarium);
  TlgTreeViewForm->setAddToSzenDel(addToSzen);
  
  CTlgContainerTreeViewForm::DelMessageHandlerTyp^ MessDel = gcnew CTlgContainerTreeViewForm::DelMessageHandlerTyp(this,&CSenderForm::messageHandler);
  CItemPrototypContainerForm::DelMessageHandlerPrototyp^ MessDel1 = gcnew CItemPrototypContainerForm::DelMessageHandlerPrototyp(this,&CSenderForm::messageHandler);
  TlgTreeViewForm->setMessageHandler(MessDel,MessDel1);

  /*TlgViewForm = new CTlgViewForm(this->panTlgView);*/
  TlgViewForm = gcnew CItemView(this->panTlgView);
  TlgViewForm->Show();
  CItemView::AddItemToSzen^ addTlg = gcnew CItemView::AddItemToSzen(this,&CSenderForm::addToSzenarium);
  TlgViewForm->setDelAddToSzen(addTlg);
  //Falls Teleframm in Szenario geandert wird
  TlgViewForm->setSzenarioChangeEventTyp(gcnew CItemView::SzenarioChangeEventTyp(this,&CSenderForm::updateSzenarioChange));
  /*UpdateTlgToSzen* upTlg = new UpdateTlgToSzen(this,&CSenderForm::updateTlgInSzenarium);
  TlgViewForm->setDelUpTlgToSzen(upTlg);*/
  CItemView::ErrorMessageDelTyp^ ErrorMessageDel = gcnew CItemView::ErrorMessageDelTyp(this,&CSenderForm::messageErrorHandler);
  TlgViewForm->setErrorMessageDel(ErrorMessageDel);
  /*TelElemEditEventTyp* editEvent = new TelElemEditEventTyp(this,&CSenderForm::updateContainerViewFromDeteilView);
  TlgViewForm->setTelElemEditEvent(editEvent);*/
  CItemView::OkMessageDelTyp^ OkMessageDel = gcnew CItemView::OkMessageDelTyp(this,&CSenderForm::messageOkHandler);
  TlgViewForm->setOkMessageDel(OkMessageDel);

  SzenariumForm = gcnew CSzenariumForm(panSzen);
  CSzenariumForm::SelectSzenItemTyp^ selItemEvent = gcnew CSzenariumForm::SelectSzenItemTyp(this,&CSenderForm::updateTlgPrototypView);
  SzenariumForm->setSelectSzenItemTyp(selItemEvent);

  CSzenariumForm::RemoveSzenarioItemFromViewTyp^ selRemoveSzenItemEvent = gcnew CSzenariumForm::RemoveSzenarioItemFromViewTyp(this,&CSenderForm::removeSzenarioItemFromView);
  SzenariumForm->setRemoveSzenarioItemFromViewTyp(selRemoveSzenItemEvent);
  
  CSzenariumForm::MessageHandlerTyp^ messHandler = gcnew CSzenariumForm::MessageHandlerTyp(this,&CSenderForm::messageHandler);
  SzenariumForm->setMessageHandler(messHandler);

  InterSenderManListe = gcnew ArrayList();

  labConnStatus->Location = System::Drawing::Point(105, 0);
  labConnStatusDesc->Size = System::Drawing::Size(100,23);
  labConnStatusDesc->Text = "Connection status:";
  
  ConnStatusToolTip=gcnew System::Windows::Forms::ToolTip();
  ConnStatusToolTip->SetToolTip(labConnStatus,"Red- unconected\nYellow - waiting\nGreen - connected");
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
/*CSzenarium* CSenderForm::getSzenarium()
{
//  return SzenariumForm->getSzenarium();
  return 0;
}*/

//----------------------------------------------------------------------
 /*void CSenderForm::setColor(System::Drawing::Color col,int id)
 {
   //this->SzenariumForm->setColor(col,id);
 }*/
//-----------------------------------------------------------------------
/*void CSenderForm::showSzenarium(CSzenarium* szen)
{
//  SzenariumForm->showSzenarium(szen);
}*/
//-----------------------------------------------------------------------
void CSenderForm::setMessageForm(CMessageForm^ messForm)
{
  messForm->Parent = (panMessage);
  MessageForm = messForm;
  SzenariumForm->setMessageBox(MessageForm);
}
//-----------------------------------------------------------------------
//void CSenderForm::setActiveInterface(int index)
//{
//  this->ActiveInterface = index;
//}
//-----------------------------------------------------------------------
void CSenderForm::setTlgProtoTypContainer(CItemBaseContainerWrapper^ con)
{
  TlgTreeViewForm->setTlgPrototypContainer(con);
}
void CSenderForm::removeSzenarioItemFromView()
{
  TlgViewForm->closeItemView(CItemView::CreateTypForm::Szenario);
}
//-----------------------------------------------------------------------
void CSenderForm::showInterfaceTlg()
{
  if (this->ActiveInterface != nullptr)
    TlgTreeViewForm->showTlgPrototypContainer(getInterface(this->ActiveInterface)->getInterfaceDescr(),
      getInterface(this->ActiveInterface)->getInterfaceVersion());
  else
      TlgTreeViewForm->showTlgPrototypContainer("","");

}
//-----------------------------------------------------------------------
void CSenderForm::setTlgContainer(CItemBaseContainerWrapper^ con)
{
  TlgTreeViewForm->setTlgContainer(con);
}
//-----------------------------------------------------------------------
void CSenderForm::showContainerTlg()
{
  TlgTreeViewForm->showTlgContainer();
}
//-----------------------------------------------------------------------
void CSenderForm::updateTlgPrototypView(CItemWrapper^ wrp,CItemView::CreateTypForm typ)
{
  TlgViewForm->ShowItem(wrp,typ);
}
//-----------------------------------------------------------------------
void CSenderForm::addToSzenarium(CItemWrapper^ tlg,double time,bool modi)
{
  SzenariumForm->addToSzenarium(tlg,time);

  if(!modi)
  {
    SzenariumForm->calcDelay(1.0);
    SzenariumForm->showSzenarium();
  }
}
//-----------------------------------------------------------------------
void CSenderForm::addToSzenarium(CItemWrapper^ tlg,bool modi)
{
  SzenariumForm->addToSzenarium(tlg);

  if(!modi)
  {
    SzenariumForm->showSzenarium();
  }
}
//-----------------------------------------------------------------------
void CSenderForm::ClosePrototypItemView()
{
  this->TlgViewForm->closeItemView(CItemView::CreateTypForm::Prototyp);
}
//-----------------------------------------------------------------------
void CSenderForm::updateTlgInSzenarium(CItemWrapper^ tlg)
{
  SzenariumForm->updateItem(tlg);
}
//-----------------------------------------------------------------------
void CSenderForm::messageHandler(String^ mess,int type)
{
  CMessageForm::MessTyp messType;
  if(type == 0 || type == 3)
    messType=CMessageForm::MessTyp::Info;
  if(type == 1)
    messType=CMessageForm::MessTyp::Warning;
  if(type == 2)
    messType=CMessageForm::MessTyp::Error;

  MessageForm->writeLine(mess,messType);
}
//-----------------------------------------------------------------------
void CSenderForm::messageOkHandler(String^ info)
{
  MessageForm->writeLine(info,CMessageForm::MessTyp::Info);
}
//-----------------------------------------------------------------------
void CSenderForm::messageErrorHandler(String^ error)
{
  MessageForm->writeLine(error,CMessageForm::MessTyp::Error);
}
//-----------------------------------------------------------------------
void CSenderForm::sendSzenarium()
{
  SzenariumForm->setInterConnListe(InterSenderManListe);
  SzenariumForm->sendSzenarium(true);
}
//-----------------------------------------------------------------------
void CSenderForm::stopSendSzenarium(bool abort)
{
  SzenariumForm->stopSendSzenarium(abort);
}
//-----------------------------------------------------------------------
/*void CSenderForm::sendTelegrams()
{
//  CSzenarium* Szen = SzenariumForm->getSzenarium();
//  int count = Szen->getSzenItemCount();
  //char buffer[2048];
    //unsigned char buffer1[2048]; 
    //double delay;
    // double delay_vor=0.0;
  //int len;
    //String^ interName;
    //CInterSenderManager* inter = 0;
  //MessageForm->setActionName("Send Szenarium");

  for(int i=1;i<=count;i++)
  {
    len=Szen->getSerializeTlg(i,buffer,2048);
        interName=Szen->getSzenItem(i)->getInterface();
        inter = getInterface(interName);
    if(len>0)
    {
      //Byte sendByte[] = new Byte[len];
      for(int j=0;j<len;j++)
        buffer1[j]=buffer[j];
        
            //?delay = Szen->getTimeDelay(i);    
            if(i != 1)
                setColor( System::Drawing::Color::FromKnownColor(System::Drawing::KnownColor::Control),i-2);
            setColor(System::Drawing::Color::Green,i-1);
            if(delay > delay_vor)
              System::Threading::Thread::get_CurrentThread()->Sleep((delay-delay_vor)*1000);
            inter->sendBytes(buffer1,len);
            delay_vor=delay;
 
    }

  }

  //SendSzenThread->Abort();
  //SendSzenThread=0;

}*/
//-----------------------------------------------------------------------
void CSenderForm::addInterface(CTlgInterfaceWrapper^ inter,CInterConnection^ interConn)
{
  CInterSenderManager^ interMan = gcnew CInterSenderManager(inter,interConn);

  InterSenderManListe->Add(interMan);
  SzenariumForm->setInterConnListe(InterSenderManListe);
}
//-----------------------------------------------------------------------
String^ CSenderForm::findInterface(String^ path)
{
    String^ ret = nullptr;
    int count = InterSenderManListe->Count;
    bool flag = false;
    int i=0;
    CInterSenderManager^ interMan = nullptr;
    
    while((!flag) && (i<count))
    {
      interMan = safe_cast<CInterSenderManager^>(InterSenderManListe[i]);
      flag = interMan->checkInterface(path);
      if(!flag)
        i++;
    }
    
    if(flag)
      ret = interMan->getInterfaceName();

    return ret;
}
//-----------------------------------------------------------------------
void CSenderForm::setActiveInterface(String^ inter)
{
  CInterSenderManager^ interMan = nullptr;

  if(inter)
  {
	  //Schliesst Item View
	  this->TlgViewForm->closeItemView(CItemView::CreateTypForm::Prototyp);
      
	  interMan = getInterface(inter);
    if(interMan)
    {
		  this->ActiveInterface = inter;
      TlgTreeViewForm->clearView();
		  setTlgProtoTypContainer(interMan->getInterProtoSet());
		  setTlgContainer(interMan->getLogFileContainer());
		  showInterfaceTlg();
		  CInterUseCase^ interUseCase = CInterUseCase::getInterUseCase(ActiveInterface);
		  updateUseCaseView(interUseCase);
    }
    TlgTreeViewForm->showTlgPrototypContainer(getInterface(this->ActiveInterface)->getInterfaceDescr(),
      getInterface(this->ActiveInterface)->getInterfaceVersion());
  }
  else
  {
      //TlgTreeViewForm->clearView();
  }
}
//-----------------------------------------------------------------------
String^ CSenderForm::getInterfaceDescr(String^ inter)
{
  String^ ret = nullptr;
  CInterSenderManager^ interMan=nullptr;

  interMan = getInterface(inter);
  if(interMan)
    ret = interMan->getInterfaceDescr();
  return ret;
}
//-----------------------------------------------------------------------
String^ CSenderForm::getInterfaceVersion(String^ inter)
{
  String^ ret = nullptr;
  CInterSenderManager^ interMan=nullptr;

  interMan = getInterface(inter);
  if(interMan)
    ret = interMan->getInterfaceVersion();
  return ret;
}
//-----------------------------------------------------------------------
CInterSenderManager^ CSenderForm::getInterface(String^ inter)
{
  CInterSenderManager^ ret = nullptr;
  int count = InterSenderManListe->Count;
  bool flag = false;
  int i=0;
  CInterSenderManager^ interMan = nullptr;
  while((!flag) && (i<count))
  {
    interMan = safe_cast<CInterSenderManager^>(InterSenderManListe[i]);
    if(inter->Equals( interMan->getInterfaceName()))
      flag = true;
    if(!flag)
      i++;
  }
  if(flag)
    ret = interMan;
  return ret;
}
//-----------------------------------------------------------------------
int CSenderForm::getLogFileTlgCount(String^ interName)
{
  return getInterface(interName)->getTlgCount();
}
//-----------------------------------------------------------------------
int CSenderForm::getInterfaceIndex(String^ inter)
{
  int ret = -1;
  int count = InterSenderManListe->Count;
  bool flag = false;
  int i=0;
  CInterSenderManager^ interMan = nullptr;
  while((!flag) && (i<count))
  {
    interMan = safe_cast<CInterSenderManager^>(InterSenderManListe[i]);
    if(inter->Equals( interMan->getInterfaceName()))
      flag = true;
    if(!flag)
      i++;
  }
  if(flag)
    ret = i;
  return ret;
}
//-----------------------------------------------------------------------
int CSenderForm::loadLogFile(String^ path,String^ interName,bool const& abort)
{
  int ret = 0;
  CInterSenderManager^ interMan=nullptr;
  interMan = getInterface(interName);
  ret=interMan->loadLogFile(path,abort);
  return ret;
}
//-----------------------------------------------------------------------
int CSenderForm::getLogTlgCount(String^ interName)
{
  int ret=0;
  CInterSenderManager^ interMan=nullptr;
  interMan = getInterface(interName);
  ret=interMan->getLogFileContainer()->getTlgCount();
  return ret;
}
//-----------------------------------------------------------------------
int CSenderForm::getLogTlgTotalCount(String^ interName)
{
  int ret=0;
  CInterSenderManager^ interMan=nullptr;
  interMan = getInterface(interName);
  ret=interMan->getLogFileContainer()->getCountTlgTotal();
  return ret;
}
//-----------------------------------------------------------------------
void CSenderForm::showLogTlg(String^ interName)
{
  CInterSenderManager^ interMan=nullptr;
  interMan = getInterface(interName);
  setTlgContainer(interMan->getLogFileContainer());
  showContainerTlg();
}
//-----------------------------------------------------------------------
void CSenderForm::saveSimpleTimeSzenarium(String^ path)
{
  MessageForm->setActionName("Save Szenarium");
  MessageForm->Refresh();
  String^ mess = String::Concat("Save to file;  ",path);
  MessageForm->writeLine(mess,CMessageForm::MessTyp::Info);
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  SzenariumForm->saveSimpleTimeSzenarium(path);
}
//-----------------------------------------------------------------------
void CSenderForm::saveSzenarium(String^ path)
{
  MessageForm->setActionName("Save Szenarium");
  MessageForm->Refresh();
  String^ mess = String::Concat("Save to file;  ",path);
  MessageForm->writeLine(mess,CMessageForm::MessTyp::Info);
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  SzenariumForm->saveSzenarium(path);
}
//-----------------------------------------------------------------------
void CSenderForm::loadSzenarium(String^ path)
{
  MessageForm->setActionName("Load Szenarium");
  MessageForm->Refresh();
  String^ mess = String::Concat("Load:  ",path);
  MessageForm->writeLine(mess,CMessageForm::MessTyp::Info);
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  SzenariumForm->loadSzenarium(path,InterSenderManListe);
}
//-----------------------------------------------------------------------
void CSenderForm::updateUseCaseView(CInterUseCase^ interUseCase)
{
  int i;
  int count; 
  String^ useCaseName = nullptr;
  Button^ but = nullptr;

  count=panUseCaseView->Controls->Count;
  for(i=count-1;i>=0;i--)
  {
    but = safe_cast<Button^>(panUseCaseView->Controls[i]);
    panUseCaseView->Controls->Remove(panUseCaseView->Controls[i]);
    delete but;
  }
  
  panUseCaseView->Controls->Clear();
  
  count = interUseCase->getUseCaseCount();
  for(i=count;i>0;i--)
  {
    useCaseName = interUseCase->getUseCaseName(i);
    but = gcnew Button();
    but->Text = useCaseName;
    but->Dock = DockStyle::Left;
    panUseCaseView->Controls->Add(but);
    but->Click += gcnew System::EventHandler(this, &CSenderForm::OnButtUseCaseClick);
  }
  but = gcnew Button();
  but->Text = "All";
  but->Dock = DockStyle::Left;
  panUseCaseView->Controls->Add(but);
  but->Click += gcnew System::EventHandler(this, &CSenderForm::OnButtUseCaseClick);
}
//-----------------------------------------------------------------------
void CSenderForm::clearUseCaseView()
{
  panUseCaseView->Controls->Clear();
}
//-----------------------------------------------------------------------
void CSenderForm::updateUseCaseView()
{
  CInterUseCase^ interUseCase = CInterUseCase::getInterUseCase(ActiveInterface);
  updateUseCaseView(interUseCase);
}
//-----------------------------------------------------------------------
void CSenderForm::setUpdateSzenariumModus(CSzenariumForm::SzenariumModusEventTyp^ event)
{
  SzenariumForm->setSzenariumModusEvent(event);
}
//-----------------------------------------------------------------------
void CSenderForm::removeInter(String^ inter)
{
  int index = getInterfaceIndex(inter);
  clearLogFile(inter);
  TlgTreeViewForm->clearView();
  InterSenderManListe->RemoveAt(index);
  SzenariumForm->removeInterfaceFromSzenarium(inter);
}
//-----------------------------------------------------------------------
void CSenderForm::clearLogFile(String^ inter)
{
  CInterSenderManager^ interMan = getInterface(inter);
  interMan->clearLogFile();
  TlgTreeViewForm->clearLogFileView();
}
//-----------------------------------------------------------------------
void CSenderForm::setFilterLogFile(array <String^>^ reg)
{
  TlgTreeViewForm->setFilterLogFile(ActiveInterface,reg);
}
//-----------------------------------------------------------------------
CItemBaseContainerWrapper^ CSenderForm::getLogFileContainer()
{
  return getInterface(ActiveInterface)->getLogFileContainer();
}
//-----------------------------------------------------------------------
CItemBaseContainerWrapper^ CSenderForm::getSzenariumContainer()
{
  return SzenariumForm->getSzenariumContainer();
}
//-----------------------------------------------------------------------
void CSenderForm::selectLogFileTelegram(int index)
{
  TlgTreeViewForm->selectLogFileTelegramm(index);
}
//-----------------------------------------------------------------------
void CSenderForm::selectSzenariumTelegram(int index)
{
  SzenariumForm->selectTelegram(index);
}
//-----------------------------------------------------------------------
void CSenderForm::enableSzenChangeMode(int mode)
{
  if(mode == 0)
  {
    TlgViewForm->setEditMode(true);
    TlgTreeViewForm->enableSzenMode(true);
  }
  else
  {
    TlgViewForm->setEditMode(false);
    TlgTreeViewForm->enableSzenMode(false);
  }
}
//-----------------------------------------------------------------------
void CSenderForm::setSzenUpdateEvent(CSzenariumForm::UpdateSzenEventTyp^ szenUpdateEvent)
{
  SzenariumForm->setUpdateSzenEvent(szenUpdateEvent);
}
//-----------------------------------------------------------------------
void CSenderForm::updateSzenFile()
{
  SzenariumForm->updateSzenFile();
	this->TlgViewForm->closeItemView(CItemView::CreateTypForm::Szenario);
}
//-----------------------------------------------------------------------
void CSenderForm::updateContainerViewFromDeteilView()
{
  SzenariumForm->ShowFromDateilView();
}
//-----------------------------------------------------------------------
int CSenderForm::getSelSzenItem()
{
  return SzenariumForm->getSelSzenItem();
}
//-----------------------------------------------------------------------
void CSenderForm::closeLogFile()
{
  clearLogFile(ActiveInterface);
  TlgViewForm->closeItemView(CItemView::CreateTypForm::LogFile);
}
//-----------------------------------------------------------------------
void CSenderForm::selectAllTlgFromLogFile()
{
  TlgTreeViewForm->selectAllTlgFromLogFile();
}
//-----------------------------------------------------------------------
void CSenderForm::removeSelectionTlgFromLogFile()
{
  TlgTreeViewForm->removeSelectionTlgFrommLogFile();
}
//-----------------------------------------------------------------------
bool CSenderForm::isLogFileLoad(String^ inter)
{
  bool ret=true;
  CInterSenderManager^ interMan=nullptr;
  interMan = getInterface(inter);
  if(!interMan->isLogFileLoad())
  {
      ret=false;
  }
  return ret;
}
//-----------------------------------------------------------------------
void CSenderForm::setLogFileViewEventTyp(CTlgTreeViewForm::LogFileViewEventTyp^ event)
{
  TlgTreeViewForm->setLogFileViewEvent(event);
}
//-----------------------------------------------------------------------
void CSenderForm::setLabConnStatus (int status)
{
  labConnStatus->ImageIndex = (status);
}
//-----------------------------------------------------------------------
int CSenderForm::getCountOfSzenarioItems()
{
  return SzenariumForm->getCountOfItems();
}
//-----------------------------------------------------------------------
bool CSenderForm::isSendMode()
{
  return SzenariumForm->IsSendMode();
}
//-----------------------------------------------------------------------
bool CSenderForm::isSzenarioSending()
{
  return SzenariumForm->IsSzenarionSending();
}
//-----------------------------------------------------------------------
void CSenderForm::removeAllCyclicTlgInSzenario()
{
  SzenariumForm->removeAllCyclicTlgInSzenario();
}
//-----------------------------------------------------------------------
bool CSenderForm::isSzenarioCreated()
{
  if (SzenariumForm->getCountOfItems() == 0)
    return false;
  else
    return true;
}
//-----------------------------------------------------------------------
bool CSenderForm::TlgsFromInterInSzenario(String^ inter)
{
  return SzenariumForm->TlgsFromInterInSzenario(inter);
}
//-----------------------------------------------------------------------
void CSenderForm::updateSzenarioChange()
{
  SzenariumForm->setSzenChangeModus();
}
//-----------------------------------------------------------------------
List<CItemBaseContainerWrapper^>^ CSenderForm::getAllLoadedLogFiles()
{
  List<CItemBaseContainerWrapper^>^ ret = gcnew List<CItemBaseContainerWrapper^>();
  CInterSenderManager^ interMan = nullptr;
  for (int i=0;i<InterSenderManListe->Count;i++)
  {
    interMan = safe_cast<CInterSenderManager^>(InterSenderManListe[i]);
    if (interMan->getLogFileContainer()->getCountTlgTotal() > 0)
    {
      ret->Add(interMan->getLogFileContainer());
    }
  }  
  return ret;
}
//-------------------------------------------------------------------------
void CSenderForm::OpenAutoCreateSzenarioForm (List<CTlgInterfaceWrapper^>^ InterfaceProtoArray)
{
  CAutoCreateSzenarioForm^ CreateSzen = gcnew CAutoCreateSzenarioForm(getAllLoadedLogFiles(),InterfaceProtoArray);
  CreateSzen->setAddToSzenDelTyp(gcnew CAutoCreateSzenarioForm::AddToSzenDelTyp(this,&CSenderForm::addToSzenarium));
  CreateSzen->setCloseSzenDelTyp(gcnew CAutoCreateSzenarioForm::CloseSzenDelTyp(this,&CSenderForm::updateSzenFile));
  CreateSzen->ShowDialog();

  //SenderForm->isSzenarioCreated();
  //SzenariumForm->set
}
//-------------------------------------------------------------------------
void CSenderForm::setOpenSenderConnectionDialogTyp(OpenSenderConnectionDialogTyp^ del)
{
  this->OpenSenderConnectionDialogDel = del;
}
//-------------------------------------------------------------------------
System::Void CSenderForm::labConnStatus_DoubleClick(System::Object^  sender, System::EventArgs^  e) 
{
  if (this->OpenSenderConnectionDialogDel != nullptr)
    OpenSenderConnectionDialogDel->Invoke();
}//-------------------------------------------------------------------------
System::Void CSenderForm::butShowAllConStatus_Click(System::Object^  sender, System::EventArgs^  e) 
{
  if (this->OpenSenderConnectionDialogDel != nullptr)
    OpenSenderConnectionDialogDel->Invoke();       
}
//--------------------------------------------------------------------------
void CSenderForm::setIgnoreDelayTimeOfUnselctedTlgs(bool value)
{
  this->SzenariumForm->setIgnoreDelayTimeOfUnselctedTlgs(value);
}