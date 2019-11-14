#include "StdAfx.h"
#include "CStatusConnectionForm.h"


using namespace simulator;

//-------------------------------------------------------------
System::Void CStatusConnectionForm::OnLoad(System::Object ^  sender, System::EventArgs ^  e)
{
  initComp();
  this->Text = ("Status Connection Info");
}
//-------------------------------------------------------------
System::Void  CStatusConnectionForm::OnClosedForm(System::Object ^  sender, System::EventArgs ^  e)
{
    
}
//-------------------------------------------------------------
/*void CStatusConnectionForm::setInterConnListe(CInterConnectionListe^ liste)
{
  DelConnStateCheck^ ConnState = gcnew DelConnStateCheck(this,&CStatusConnectionForm::updateConnInfo);
//	this->InterConnectionListe = liste;
  SocketConnStateRec = gcnew CSocketConnState();
//  SocketConnStateRec->setInterConnListe(InterConnectionListe);
  SocketConnStateRec->setDelConnStateCheck(ConnState);
//  SocketConnStateRec->setDirection(CInterConnectionListe::DirectionType::Receiver);


  SocketConnStateSend = gcnew CSocketConnState();
//  SocketConnStateSend->setInterConnListe(InterConnectionListe);
  SocketConnStateSend->setDelConnStateCheck(ConnState);
  //SocketConnStateSend->setDirection(CInterConnectionListe::DirectionType::Sender);
  //SocketConnState->setDelConnStateCheck
}*/
//-------------------------------------------------------------
void CStatusConnectionForm::initComp()
{ 
	int count;

  count = SendInterConnectionListe->getInterfaceCount();
	for(int i=0;i<count;i++)
	{
    
    showConnInfo(SendInterConnectionListe,i);
    if (RecInterConnectionListe != nullptr)
      showConnInfo(RecInterConnectionListe,i); 
	}   

 // CInterConnectionListe::ChangeConnectionEvent^ chSendEvent = gcnew CInterConnectionListe::ChangeConnectionEvent(this,&CStatusConnectionForm::updateConSendInfoToView);
//  CInterConnectionListe::ChangeConnectionEvent^ chRecEvent = gcnew CInterConnectionListe::ChangeConnectionEvent(this,&CStatusConnectionForm::updateConRecInfoToView);
  //SendInterConnectionListe->addObserver(chSendEvent);
  //RecInterConnectionListe->addObserver(chRecEvent);
}
//-------------------------------------------------------------
void CStatusConnectionForm::showConnInfo(CInterConnectionListe^ liste,int index)
{
  String^ inter=nullptr;
  String^ dir=nullptr;
  String^ status=nullptr;
  String^ type=nullptr;
  String^ hostName=nullptr;
  String^ ipAddr=nullptr;
  String^ portStr=nullptr;
  int port = 0;
  System::Threading::ThreadStart^ ThSt=nullptr;

  inter=liste->getInterfaceName(index+1);
  ListViewItem^ item = gcnew ListViewItem(inter, 0);

  dir = liste->getDirection();
  item->SubItems->Add(dir);

  if(liste->isConnected(index+1))
  {
    status = "connected";
  }
  else
  {
    if(liste->isWaiting(index+1))
    {
      status = "waiting for connection";
    }
    else
    {
      status = "not connected";
    }
  }
  item->SubItems->Add(status);

  type = liste->getConnType(index+1);
  if(type == nullptr)
      type = "-----";

  item->SubItems->Add(type);

  liste->getHostInfo(index+1,hostName,ipAddr,&port);

  if(!hostName)
  {
    //hostName = "-----";
    portStr = "-----";
  }
  else
  {
    portStr = System::Convert::ToString(port);
  }
  if(!ipAddr)
    ipAddr = "-----";
 
  item->SubItems->Add(ipAddr);
  item->SubItems->Add(portStr);
 
  listViewConnStatus->Items->Add(item);
 
  //SocketConnStateRec->startConnStateCheck();
  //SocketConnStateSend->startConnStateCheck();
}

//-------------------------------------------------------------
/*void CStatusConnectionForm::updateConnInfo(int inter,int direction,int status)
{
  int index;

  index = (inter-1)*2+direction;
  //if(direction == 0)
    //InterConnectionListe->setDirectionMode(CInterConnectionListe::DirectionType::Sender);
   //if(direction == 1)
     //InterConnectionListe->setDirectionMode(CInterConnectionListe::DirectionType::Receiver);
  updateConnInfo(index,status);

}*/
//-------------------------------------------------------------
/*void CStatusConnectionForm::updateConnInfo(int index,int status)
{
  String^ hostName=0;
  String^ ipAddr=0;
  int port=0;
  System::Windows::Forms::ListViewItem::ListViewSubItemCollection* items = 0;
  items = listViewConnStatus->Items[index)->get_SubItems();
  if(status == 0)
    items[2)->Text = "not connected";
  if(status == 1)
    items[2)->Text = "waiting for connection";
  if(status == 3)
    items[2)->Text = "connected";
//  items[3)->Text = InterConnectionListe->getConnType(index);

//  InterConnectionListe->getHostInfo(index,hostName,ipAddr,&port);

  items[4)->Text = ipAddr;
  items[5)->Text = System::Convert::ToString(port);
  //listViewConnStatus->Items[index)->get_SubItems() [2)->Text = "fffffffffff";
}*/
//-------------------------------------------------------------
void CStatusConnectionForm::updateConSendInfoToView(String^ inter)
{
  int index,inter_num;
  if (SendInterConnectionListe != nullptr)
  {
    inter_num = SendInterConnectionListe->getInterNummber(inter);
    index = (inter_num-1)*2;
    updateListeToView(index,inter_num,SendInterConnectionListe);
  }
}
//-------------------------------------------------------------
void CStatusConnectionForm::updateConRecInfoToView(String^ inter)
{
   int index,inter_num;
   if (SendInterConnectionListe != nullptr &&  RecInterConnectionListe)
   {
      inter_num = SendInterConnectionListe->getInterNummber(inter);
      index = (inter_num-1)*2+1;
      updateListeToView(index,inter_num,RecInterConnectionListe);
   }
}
//-------------------------------------------------------------
void CStatusConnectionForm::updateListeToView(int pos,int inter,CInterConnectionListe^ liste)
{
  String^ hostName=nullptr;
  String^ ipAddr=nullptr;
  int port=0;
  String^ status = nullptr;
  String^ typConn = nullptr;
  System::Windows::Forms::ListViewItem::ListViewSubItemCollection^ items = nullptr;
  items = listViewConnStatus->Items[pos]->SubItems;
  
  liste->getHostInfo(inter,hostName,ipAddr,&port);
  if(liste->isConnected(inter))
  {
      status = "connected";
  }
  else
  {
      if(liste->isWaiting(inter))
      {
          status = "waiting for connection";
      }
      else
      {
          status = "not connected";
      }
  }
  typConn = liste->getConnType(inter);
  items[2]->Text = status; 
  items[3]->Text = typConn;
  items[4]->Text = ipAddr;
  items[5]->Text = System::Convert::ToString(port);
  //listViewConnStatus->Items[index)->get_SubItems() [2)->Text = "fffffffffff";
}
//-------------------------------------------------------------