#include "StdAfx.h"
#include "CReceiverForm.h"
#include "CAppSetting.h"
#include "CAnalyzeLogFileForm.h"
#include "TinyXml.h"
#include "CItemView.h"
#include "CLogWriterWrapper.h"

using namespace simulator;

//-------------------------------------------
CReceiverForm::CReceiverForm(Panel^ parent)
{
  InitializeComponent();
  this->TopLevel = false;
  this->Parent = parent;
  this->Dock = DockStyle::Fill;
  this->FormBorderStyle = ::FormBorderStyle::None;

  BaseFactoryArray=nullptr;
  ActiveInterface = nullptr;
  //  ConnState = gcnew CSocketConnState();
  InterReceiverManListe = gcnew ArrayList();
  ReceiveTlgContainer = gcnew CTlgContainerWrapper();
  InterfaceListe = gcnew ArrayList();
  initViewComponent();
  DynamicTlgContainer = gcnew CTlgContainerWrapper();
  AnalyzeLogFileForm = nullptr;
}
//------------------------------------------
System::Void CReceiverForm::OnResizeForm(System::Object ^  sender, System::EventArgs ^  e)
{
  panLeft->Width = 216;  //this->Width/4;
}
//-------------------------------------------------------------
System::Void CReceiverForm::OnCheckBxAllTlgCheckedChanged(System::Object ^  sender, System::EventArgs ^  e)
{
  if(checkBxAllTlg->Checked)
  {
    ReceiveTlgContainer->reset();
  }
  else
  {
    ReceiveTlgContainer->setFilterByInterfaceName(ActiveInterface);
  }
  TlgTreeViewForm->clearView();
  TlgTreeViewForm->updateTlgView(1);
  txtBxCount->Text = System::Convert::ToString(ReceiveTlgContainer->getVirtualTlgCount());
  //TlgTreeViewForm->ShowTlgContainer();
}
//--------------------------------------------------------------
System::Void CReceiverForm::OnButClearViewClick(System::Object ^  sender, System::EventArgs ^  e)
{
  TlgTreeViewForm->clearView();
  ReceiveTlgContainer->clearContainer();
  txtBxCount->Text="0";
  TlgViewForm->closeItemView(CItemView::CreateTypForm::Receiver);
}
//--------------------------------------------------------------
System::Void CReceiverForm::OnButtRecClick(System::Object ^  sender, System::EventArgs ^  e)
{
  CAppSetting^ Sett = CAppSetting::getApp();
  m_dynAdaptation = Sett->useDynamicAdaptation();
  if (m_dynAdaptation)
    loadConfigForDynSimulation(ActiveInterface);
  
  CInterReceiverManager^ recMan = getInterface(ActiveInterface);
 
  try
  {
    if(recMan)
    {
      if (!recMan->isConnected())
      {
        if (!recMan->isWaiting())
          recMan->receiveTlg();
        else
        {
          int index=RecConnListe->getInterNummber(this->ActiveInterface);
          RecConnListe->disConnect(index);
        }
      }
      else
      {
        int index=RecConnListe->getInterNummber(this->ActiveInterface);
        RecConnListe->disConnect(index);
      }
    }
  }
  catch (System::Net::Sockets::SocketException^ e)
  {
    String^ mess = String::Concat("Error by connecting in receiver : ",e->Message);
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                  __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),2);
    MessageForm->writeLine(mess,CMessageForm::MessTyp::Error);
    if (RecConnListe)
    {
      int index=RecConnListe->getInterNummber(this->ActiveInterface);
      RecConnListe->disConnect(index);
    }
  }
}
//--------------------------------------------------------------
void CReceiverForm::initViewComponent()
{
   TlgTreeViewForm = gcnew  CItemPrototypContainerForm(panTreeViewCon);
   TlgTreeViewForm->Show();
   CItemPrototypContainerForm::AfterSelectPrototypEvent^ selectEvent = gcnew CItemPrototypContainerForm::AfterSelectPrototypEvent(this,&CReceiverForm::showTlgDetailView);
   TlgTreeViewForm->setSelectEvent(selectEvent);
   TlgTreeViewForm->setPrototypContainer(ReceiveTlgContainer);
   TlgTreeViewForm->setIsReceiver();

   /*TlgTreeViewForm->setRecModus();*/

   TlgViewForm = gcnew CItemView(panTlgView);
   /*TlgViewForm = new CTlgViewForm(panTlgView); */
   TlgViewForm->setReceiveView();
   TlgViewForm->Show();

   txtBxCount->Text = System::Convert::ToString(ReceiveTlgContainer->getVirtualTlgCount());
}
//------------------------------------------
void CReceiverForm::setInterfaceList(ArrayList^ arr)
{
  this->BaseFactoryArray = arr;
}
//------------------------------------------
void CReceiverForm::setActiveInterface(String^ inter)
 {
  CInterReceiverManager^ interMan = nullptr;
    
  interMan = getInterface(inter);
  if(interMan)
  {
    //TlgTreeViewForm->clearView();
    ActiveInterface = inter;
    if(!checkBxAllTlg->Checked)
    {
      ReceiveTlgContainer->setFilterByInterfaceName(ActiveInterface);
      TlgTreeViewForm->clearView();
      TlgTreeViewForm->updateTlgView(1);
    }
    //TlgTreeViewForm->setTlgContainer(interMan->getTlgContainer());
    //showContainerTlg();
    showInterConnInfo();
  }
}
//------------------------------------------
void CReceiverForm::updateInterfaceInfo()
{
  //labHostName->Text = RecConnList->getHost(ActInterface);
//  labPortNummber->Text = System::Convert::ToString(RecConnList->getPort(ActInterface));
//  labConnType->Text = RecConnList->getConnTyp(ActInterface);
}
//------------------------------------------
void CReceiverForm::setMessageForm(CMessageForm^ messForm)
{
  MessageForm = messForm;
  MessageForm->Parent = (panBottom);
  MessageForm->Show();
}
//------------------------------------------
//------------------------------------------------------------------
void CReceiverForm::setInterConnListe(CInterConnectionListe^ liste)
{
  this->InterConnectionListe = liste;
//  ConnState->setInterConnListe(liste);
//  ConnStateCheckDel = new  DelConnStateCheck(this,&CReceiverForm::updateConnection);
//  ConnState->setDelConnStateCheck(ConnStateCheckDel);
//  ConnState->startConnStateCheck();
  InterRecArray = gcnew ArrayList(InterConnectionListe->getInterfaceCount());
}
//------------------------------------------------------------------
void CReceiverForm::updateConnection(int inter,int dir,int status)
{
  //  CTlgInterRec^ TlgInterRec = nullptr;
  //  CBaseTlgFactoryWrapper^ facWr=nullptr;
   
  if(status == 2)
  {
    // TlgInterRec = new CTlgInterRec();
    //DelNewTlg^ tlgEvent = new DelNewTlg(this,&CReceiverForm::updateTlgView);
    //    TlgInterRec->setInterConnListe(InterConnectionListe,inter);
    //  TlgInterRec->setEventNewTlg(tlgEvent);
    //  facWr = safe_cast<CBaseTlgFactoryWrapper^>(BaseFactoryArray[inter-1));
    //TlgInterRec->setBaseTlgFactory(facWr);
    udateRecListe();
    //    InterRecArray->set_Item(inter-1,TlgInterRec);
    //    TlgInterRec->receiveTlg();
  }
  String^ mess = System::Convert::ToString(inter);
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  MessageForm->writeLine(mess,CMessageForm::MessTyp::Info);
}
//------------------------------------------------------------------
void CReceiverForm::udateRecListe()
{
  int countInter,countTlgInterRec;
  //   CTlgInterRec^ TlgInterRec = nullptr;

  countInter = InterConnectionListe->getInterfaceCount();
  countTlgInterRec = InterRecArray->Count;

  for(int i=0;i<(countInter-countTlgInterRec);i++)
  {
  //      InterRecArray->Add(TlgInterRec);
  }
}
//------------------------------------------------------------------
void CReceiverForm::updateTlgView()
{
  String^ tlgAsString=nullptr;
  CItemWrapper^ tlgWr=nullptr; 
  int count;

 
  //  CTlgInterRec^ interRec = safe_cast<CTlgInterRec^>(InterRecArray[0));
  //  CBaseTlgFactoryWrapper^ fac = safe_cast<CBaseTlgFactoryWrapper^>(BaseFactoryArray[0));
  //TlgTreeViewForm->setTlgContainer(interRec->getTlgContainer());
  TlgTreeViewForm->updateTlgView(1);
  //TlgViewForm->setFactory(fac);
  //  count=interRec->getTlgCount();

  count =  TlgTreeViewForm->getTlgCount();
  txtBxCount->Text = System::Convert::ToString(count);
  updateConnInfo();

  tlgWr=TlgTreeViewForm->getClonedTlg(count);
  tlgAsString=tlgWr->getSerialiseTlgAsString("|");
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,tlgAsString,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  MessageForm->writeLine(tlgAsString,CMessageForm::MessTyp::Info);
	TlgViewForm->ShowItem(tlgWr,CItemView::CreateTypForm::Receiver);

  //TlgViewForm->showTlg(tlgWr);
}
//------------------------------------------------------------------
void CReceiverForm::updateConnInfo()
{
  String^ hostName=nullptr;
  String^ ipAddr=nullptr;
  String^ interName;
  int port=0;
  InterConnectionListe->getHostInfo(1,hostName,ipAddr,&port);
  interName=InterConnectionListe->getInterfaceName(1);

  this->labHostName->Text = hostName;
  this->labIpAddr->Text = ipAddr;
  this->labPort->Text = System::Convert::ToString(port);
  this->labInter->Text = interName;
}
//------------------------------------------------------------------
void CReceiverForm::setConnListe(CInterConnectionListe^ recListe)
{
  this->RecConnListe = recListe;
}
//------------------------------------------------------------------
void CReceiverForm::addInterface(CTlgInterfaceWrapper^ inter,CInterConnection^ interConn)
{
  CInterReceiverManager^ pInterMan = gcnew CInterReceiverManager(inter,interConn);
  MessageHandlerSendRecTyp^ messHandler = gcnew MessageHandlerSendRecTyp(this,&CReceiverForm::showMessage);
  pInterMan->setMessageHandler(messHandler);
  InterReceiverManListe->Add(pInterMan);
  // create event for invoke call
  // showNewTlg will be called by InterReceiverManager
  NewTlgEventTyp^ event = gcnew NewTlgEventTyp(this,&CReceiverForm::showNewTlg);
  pInterMan->setNewTlgEvent(event);
}
// !!!
//------------------------------------------------------------------
void CReceiverForm::addInterface(CTlgInterfaceWrapper^ inter)
{
  InterfaceListe->Add(inter);

}

//------------------------------------------------------------------
void CReceiverForm::updateConnectionStatus(String^ inter)
{
  //CInterReceiverManager^ interMan = nullptr;
  //interMan = getInterface(inter);
  //
  //if(interMan->isConnected())
  //{
  //  // MessageForm->writeLine("fffffff",CMessageForm::MessTyp::Ok);
  //  interMan->receiveTlg();
  //}
  //else
  //{
  //  if(interMan->isWaiting())
  //  {
  //  }
  //  else
  //  {
  //  }
  //}
  showInterConnInfo();
}
//------------------------------------------------------------------
CInterReceiverManager^ CReceiverForm::getInterface(String^ inter)
{
  CInterReceiverManager^ ret = nullptr;
  int count = InterReceiverManListe->Count;
  bool flag = false;
  int i=0;
  CInterReceiverManager^ interMan = nullptr;
  while((!flag) && (i<count))
  {
    interMan = safe_cast<CInterReceiverManager^>(InterReceiverManListe[i]);
    if(inter->Equals(interMan->getInterfaceName()))
      flag = true;

    if(!flag)
      i++;
  }
  if(flag)
    ret = interMan;
  return ret;
}
//------------------------------------------------------------------
int CReceiverForm::getInterfaceIndex(String^ inter)
{
    int ret=-1;
    //CInterReceiverManager^ inter = nullptr;
    int count = InterReceiverManListe->Count;
    bool flag = false;
    int i=0;
    CInterReceiverManager^ interMan = nullptr;
    while((!flag) && (i<count))
    {
        interMan = safe_cast<CInterReceiverManager^>(InterReceiverManListe[i]);
        if(inter->Equals( interMan->getInterfaceName()))
            flag = true;
        if(!flag)
            i++;
    }
    if(flag)
      ret=i;
    return ret;
}
//------------------------------------------------------------------
void CReceiverForm::showContainerTlg()
{
  //TlgTreeViewForm->ShowTlgContainer();
  TlgTreeViewForm->showContainer();
}
//------------------------------------------------------------------
void CReceiverForm::showAnazyzeForm(int index,String^ path)
{
  AnalyzeLogFileForm = gcnew CAnalyzeLogFileForm(InterfaceListe,index,path);
  AnalyzeLogFileForm->Show();
}
//------------------------------------------------------------------
void CReceiverForm ::closeAnazyzeForm()
{
  if (AnalyzeLogFileForm)
    AnalyzeLogFileForm->Close();
}
//------------------------------------------------------------------
void CReceiverForm::showInterConnInfo()
{
  String^ host = nullptr;
  String^ ip = nullptr;
  int port;
  String^ typ=nullptr;

  if (!ActiveInterface)
    return;
  
  CInterReceiverManager^ interMan = nullptr;
  interMan = getInterface(ActiveInterface);
  if (!interMan)
    return;


  labInter->Text = interMan->getInterfaceName();
  interMan->getHostInfo(host,ip,&port);
  labHostName->Text = host;
  labIpAddr->Text = ip;
  if(port != -1)
  {
    labPort->Text = System::Convert::ToString(port);
  }
  else
  {
    labPort->Text = "";
  }
  typ=interMan->getConnectionTyp();
  labConTyp->Text = typ;
  if(interMan->isConnected())
  {
    buttRec->BackColor = (Color::Green);
    labConStatus->Text = "Connected";
    buttRec->Text="Stop recieve";
  }
  else if (interMan->isWaiting())
  {
    buttRec->BackColor = (Color::Yellow);
    buttRec->Text="Stop waiting";
    labConStatus->Text = "Waiting for Connection";
  }
  else
  {
    buttRec->BackColor = (Color::Red);
    buttRec->Text="Connect";
    //JOGE
    labConStatus->Text = "Unconnected";
  }
}
//------------------------------------------------------------------
void CReceiverForm::showNewTlg(CItemWrapper^ tlg)
{
  int count;
  ReceiveTlgContainer->addTlgToContainer(tlg);
  if (m_dynAdaptation)
  {
    int pos = 0;
    if ((pos = DynamicTlgContainer->findTelegramm(1,tlg->getName()))>0)
    {
      CItemWrapper^ u_tlg = nullptr;
      u_tlg = DynamicTlgContainer->getTlg(pos);
      if (u_tlg->getInterfece()->Equals(tlg->getInterfece()))
      {
        u_tlg->clearWrapperTlg();
        CTlg* tm = tlg->getClonedTlg();
        u_tlg->setTlg(tm);
      }
    }
  }
  if((checkBxAllTlg->Checked)||(ActiveInterface->Equals(tlg->getInterfece())))
  {
    TlgTreeViewForm->updateTlgView(1);
    txtBxCount->Text = System::Convert::ToString(ReceiveTlgContainer->getVirtualTlgCount());
  }
  else
  {
    count=ReceiveTlgContainer->getVirtualTlgCount();
    ReceiveTlgContainer->removeFromVirtuallContainer(count);
  }
}
//------------------------------------------------------------------
void CReceiverForm::removeInter(String^ inter)
{
  int index = getInterfaceIndex(inter);
  InterReceiverManListe->RemoveAt(index);
  TlgTreeViewForm->clearView();
}
//------------------------------------------------------------------
void CReceiverForm::showTlgDetailView(CItemWrapper^ tlg,CItemView::CreateTypForm typ)
{
	TlgViewForm->ShowItem(tlg,typ);
}
//------------------------------------------------------------------
void CReceiverForm::showMessage(String^ mess,int modi)
{
  switch(modi)
  {  
    case 0:
      MessageForm->writeLine(mess,CMessageForm::MessTyp::Info);
      break;
    case 1:
      MessageForm->writeLine(mess,CMessageForm::MessTyp::Warning);
      break;
    case 2:
      MessageForm->writeLine(mess,CMessageForm::MessTyp::Error);
      break;
    case 3:
      MessageForm->writeLine(mess,CMessageForm::MessTyp::Info);
      break;
  }
  //updateConnectionStatus(ActiveInterface);
}
//------------------------------------------------------------------
void CReceiverForm::loadConfigForDynSimulation(String^ act_int)
{
  String^ path;
  path = Application::ExecutablePath;
  int pos = path->LastIndexOf("\\");
  path = String::Concat(path->Substring(0,pos+1),"AdaptSimConfigRules.xml");

  std::string s_path;
  CStdConverter::StringToStdStr(path, s_path);
  TiXmlDocument doc(s_path.c_str());// create instance to handle xml file
	bool loadOkay = doc.LoadFile();
	if ( loadOkay )
  {
	  TiXmlElement* RootElement = nullptr;
    TiXmlElement* Interface = nullptr;
    TiXmlElement* Telegram = nullptr;
    TiXmlNode*    inerf = nullptr;
    TiXmlNode*    telegs = nullptr;
    TiXmlNode*    elems = nullptr;

    RootElement = doc.RootElement(); // get root element from file
    // gehe dürch alle Interfaces in der Datei
    for( inerf=RootElement->FirstChild("interface"); inerf; inerf=inerf->NextSibling("interface"))
    {
      Interface = inerf->ToElement();
      String ^IntName = "";
      IntName = gcnew String(Interface->Attribute("name"));

      // nur für das aktuelle Interface 
      if (act_int && act_int->Equals(IntName))
      {
        // instanziiere obj. der Tlg's die in diesem Interface definiert sind und
        // speichere diese in den DynamicTlgContainer un diese später zu actualisieren
        for( telegs=Interface->FirstChild("telegram"); telegs; telegs=telegs->NextSibling("telegram"))
        {
          CItemWrapper^ tlg_w;
          Telegram = telegs->ToElement();
          String ^TelegName = gcnew String(telegs->ToElement()->Attribute("name"));
          String ^ForInt = gcnew String(telegs->ToElement()->Attribute("interface"));
          try
          {
            // prüfe, ob das Interface geladen ist
            if (getInterface(IntName))
            {
              tlg_w = getInterface(IntName)->getInterProtoSet()->makeTlg(TelegName);
              String ^ ii = tlg_w->getInterfece();
              if (! DynamicTlgContainer->findTelegramm(1, TelegName))
                DynamicTlgContainer->addTlgToContainer(tlg_w);

              std::string ElemName;

              // go through sub-elements of record element and find Blen 
              for( elems=Telegram->FirstChild("element"); elems; elems=elems->NextSibling("element"))
              {
                ElemName = elems->ToElement()->Attribute("name");
              }
            }
            else
            {
              String ^Message;
              Message = "loadConfigForDynSimulation: Interface: ";
              String::Concat(Message, ForInt," to create tlgs isn't loaded.");
              if (MessageForm)
                MessageForm->writeLine(Message,CMessageForm::MessTyp::Error);
            }
          }
          catch(CExpWrapper^ e)
          {
            CExpWrapper::ErrorTyp err = e->getErrorTyp();
            String^ mess = "loadConfigForDynSimulation: ";
            String::Concat(mess, e->getMessage());
            switch(err)
            {
              case CExpWrapper::ErrorTyp::tUnknowTlg:
                mess = String::Concat(mess,". No dynamic simulation for this Telegram!");
              break;
              default:
                break;
            }
						CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
																																		__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
            if (MessageForm)
            {
              MessageForm->writeLine(mess,CMessageForm::MessTyp::Error);
            }
          }
        }
      }
    }
  }//	if ( loadOkay )
  else
  {
    String ^Message;
    Message = "loadConfigForDynSimulation: Could not load file 'ConfigRules.xml'. Error=\'";
    Message = String::Concat(Message, gcnew String(doc.ErrorDesc()),"\'");
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,Message,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    if (MessageForm)
      MessageForm->writeLine(Message,CMessageForm::MessTyp::Error);
	}
}
