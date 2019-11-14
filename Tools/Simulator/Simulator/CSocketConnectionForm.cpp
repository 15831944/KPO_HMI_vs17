#include "StdAfx.h"
#include "CSocketConnectionForm.h"
#include "CXmlInterConnInfoSave.h"
#include "CXmlInterConnInfoOpen.h"
#include "CLogWriterWrapper.h"
#include "CInterConfigWrapper.h"
#include "CAppSetting.h"

using namespace simulator;

//-------------------------------------------------------------------------
System::Void CSocketConnectionForm::OnLoad(System::Object ^  sender, System::EventArgs ^  e)
{
   initInterfaceListe();  
   initCompConfiguration();  
}
//-------------------------------------------------------------------------
System::Void CSocketConnectionForm::OnCheckedLocHost(System::Object ^  sender, System::EventArgs ^  e)
{
  comBxIpAddr->Items->Clear();
  if(chkBxLocHost->Checked)
  {
    String^ host=System::Net::Dns::GetHostName();
    System::Net::IPHostEntry^ hostInfo=System::Net::Dns::GetHostByName(host);
    int count=hostInfo->AddressList->Length;
    for(int i=0;i<count;i++)
    {
      comBxIpAddr->Items->Add(hostInfo->AddressList[i]);
    }
    comBxIpAddr->SelectedIndex=0;
    txtBxIpCount->Text = System::Convert::ToString(count);
    labHost->Text = host;
  }
  else
  {
    comBxIpAddr->Text = "";
    txtBxIpCount->Text = "";
    labHost->Text = "";
  }
}
//-------------------------------------------------------------------------
System::Void CSocketConnectionForm::OnListBoxInterEnter(System::Object ^  sender, System::EventArgs ^  e)
{
  updateFromViewToConn();
}
//-------------------------------------------------------------------------
System::Void  CSocketConnectionForm::OnListBoxSelIndexChanged(System::Object ^  sender, System::EventArgs ^  e)
{
  updateFromConnToView();
  /*button1->Enabled=true;
  button2->Enabled=true;*/
}
//-------------------------------------------------------------------------
System::Void CSocketConnectionForm::OnClickButtConnection(System::Object ^  sender, System::EventArgs ^  e)
{
  int index;
  String^ mess=nullptr;
  String^ hostName=nullptr;
  String^ ipAddr=nullptr;
  int port = 0;
  int ret;
  bool ip = false;
  
  //Pruefen, ob die Interface Einstellung richtig sind
  index = listBoxInter->SelectedIndex;
  //Interface Name
  String^ interName = InterConnectionListe->getInterfaceName(index+1);
  //Interface Einstellungen
  CInterConfigWrapper^ interWr = gcnew CInterConfigWrapper();
  
  if (interWr->isIdElementDefined(interName))
  { 
    try
    {
      if (index > -1)
      {
        button1->Enabled = false;
        ipAddr = comBxIpAddr->Text;
        //Ueberpruefen, ob String in einer IP Adresse konvertiert werden kann.
        System::Net::IPAddress::Parse(ipAddr);

        //System::Net::IPAddress::Any(ipAddr);

        ip = true;
        port = System::Convert::ToInt32(txtBxPort->Text);
        hostName = labHost->Text;
        InterConnectionListe->setHostInfo(index+1, hostName, ipAddr,port);
        if(ConnectionFlag) // DirectionType::Send
        {
          //Wenn Sender
          try
          {
            ret = InterConnectionListe->buildConnection(index+1);
          }
          catch (ObjectDisposedException^ e) 
          {
            mess = e->Message;
            CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                                    __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
            MessageForm->writeLine(mess,CMessageForm::MessTyp::Error);
            ret = -1;
          }
          catch (SocketException^ e) 
          {
            mess = e->Message;
            MessageForm->writeLine(mess  + "\nError COde : " + e->ErrorCode,CMessageForm::MessTyp::Error);
            CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                                    __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
            InterConnectionListe->disConnect(index+1);
            ret = -1;
          }
          catch(Exception^ e)
          {  
            mess = e->Message;
            CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                             __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
            MessageForm->writeLine(mess,CMessageForm::MessTyp::Error);
            ret = -1;
          }

          if(ret == 0)
          {
            String^ conTyp=nullptr;
            if(radioButtServer->Checked)
              conTyp="Bind to: ";
            else
              conTyp="Connecting to: ";
            mess = String::Concat(conTyp,"IP-Addres: ",
            ipAddr," Port: ",System::Convert::ToString(port));
            CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                                             __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
            MessageForm->writeLine(mess,CMessageForm::MessTyp::Info);
            InterConnectionListe->getInterfaceAt(index+1)->waitingForConnection();
            System::Threading::Thread::CurrentThread->Sleep(100);
            button2->Enabled = true;
            button1->Enabled = false;
            updateFromConnToView();
          }
          else
          {
            String^ stat;
            if (InterConnectionListe->getInterfaceAt(index+1))
              stat = InterConnectionListe->getInterfaceAt(index+1)->getStatusMessage();

            stat = String::Concat(" IP ");
            mess = String::Concat(stat, ipAddr, " PORT: ", System::Convert::ToString(port));
            CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                             __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
            MessageForm->writeLine(mess,CMessageForm::MessTyp::Error);
            button2->Enabled = false;
            button1->Enabled = true;
          }
        }
        else
        {
          labStatusInfo->Text = "Ready for receiving";
        }
        //button2->Enabled = true;
      }// if (index...
    }
    catch(System::ArgumentException^ e) 
    {
      String^ mes;
      mes = String::Concat("Input of port is notvalid number value.",e->Message);
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mes,
                                                             __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      turnOnOffConnDisconnButtons(CConnectionInfo::ConnectionStatus::Disconnected);
      System::Windows::Forms::MessageBox::Show(nullptr,mes,"Error");
    }
    catch(System::FormatException^ e)
    {
      String^ mes;
      if (ip)
        mes = String::Concat("Input of port has invalid format.",e->Message);
      else
        mes = String::Concat("",e->Message);
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mes,
                                                             __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      turnOnOffConnDisconnButtons(CConnectionInfo::ConnectionStatus::Disconnected);
      System::Windows::Forms::MessageBox::Show(nullptr,mes,"Error");
     
    }
    catch(System::OverflowException^ e)
    {
      String^ mes;
      mes = String::Concat("Port-number is out of range.",e->Message);
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mes,
                                                             __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      turnOnOffConnDisconnButtons(CConnectionInfo::ConnectionStatus::Disconnected);
      System::Windows::Forms::MessageBox::Show(nullptr,mes,"Error");  
    }
    catch(System::Exception^ e)
    {
      String^ mes;
      mes = String::Concat("Some System::Exception during connection! ",e->Message);
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mes,
                                                             __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      MessageForm->writeLine(mes,CMessageForm::MessTyp::Error);
      turnOnOffConnDisconnButtons(CConnectionInfo::ConnectionStatus::Disconnected);
    }
    /*catch(System::ArgumentNullException* e)
    {
      String^ mes;
      mes = String::Concat("aaa",e->Message);
      MessageForm->writeLine(mes,CMessageForm::MessTyp::Error);
      turnOnOffConnDisconnButtons(CConnectionInfo::ConnectionStatus::Disconnected);
    }*/
  }
  else
  {
    String^ mess = "Interface configuration is wrong (Id element not defined), configure first!";
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    MessageForm->writeLine(mess,CMessageForm::MessTyp::Error);
  }
}
//-------------------------------------------------------------------------
System::Void  CSocketConnectionForm::OnClickButtDisconnect(System::Object ^  sender, System::EventArgs ^  e)
{
  String^ mess=nullptr;
  String^ hostName;
  String^ ipAddr;
  int port;
  int index = listBoxInter->SelectedIndex;
  if (index > -1)
  {
    button2->Enabled = false;
    InterConnectionListe->getHostInfo(index+1,hostName,ipAddr,&port);
    mess= String::Concat("Closed Connection: ","IP - Address: ",ipAddr,"Port: ",System::Convert::ToString(port));
		CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    MessageForm->writeLine(mess,CMessageForm::MessTyp::Info);
    
    try
    {
      InterConnectionListe->disConnect(index+1);
    }
    catch(System::Net::Sockets::SocketException^ e)
    {
			CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,e->Message,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
			MessageForm->writeLine(e->Message,CMessageForm::MessTyp::Error);
    }
    
    updateFromConnToView();
    button1->Enabled = true;
  }
}

//-------------------------------------------------------------------------
System::Void CSocketConnectionForm::OnClickButtOk(System::Object ^  sender, System::EventArgs ^  e)
{
  Close();
}
//-------------------------------------------------------------------------
System::Void CSocketConnectionForm::OnClickButtCancel(System::Object ^  sender, System::EventArgs ^  e)
{
  Close();
}
//-------------------------------------------------------------------------
System::Void CSocketConnectionForm::OnCheckedChangedRadButtServer(System::Object ^  sender, System::EventArgs ^  e)
{
  int index;

  if(listBoxInter->Items->Count > 0)
  {
    index = listBoxInter->SelectedIndex;
    if(radioButtServer->Checked)
      InterConnectionListe->getInterfaceAt(index+1)->setConnectionType(CConnectionInfo::ConnectionType::Server);
    /*else
      InterConnectionListe->getInterfaceAt(index+1)->setConnectionType(CConnectionInfo::ConnectionType::Client);*/
    else
      radioButtServer->Checked = (true);

    radioButtClient->Checked = (false);
    labTypeInfo->Text="Server";
  }
}
//-------------------------------------------------------------------------
System::Void CSocketConnectionForm::OnCheckedChangedRadButtClient(System::Object ^  sender, System::EventArgs ^  e)
{
  int index;

  if(listBoxInter->Items->Count > 0)
  {
    index = listBoxInter->SelectedIndex;
    if(radioButtClient->Checked)
      InterConnectionListe->getInterfaceAt(index+1)->setConnectionType(CConnectionInfo::ConnectionType::Client);
    /*else
      InterConnectionListe->getInterfaceAt(index+1)->setConnectionType(CConnectionInfo::ConnectionType::Client);*/
    else
      radioButtClient->Checked = (true);

    radioButtServer->Checked = (false);
    labTypeInfo->Text="Client";
  }
}
//-------------------------------------------------------------------------
System::Void CSocketConnectionForm::OnClickButtSave(System::Object ^  sender, System::EventArgs ^  e)
{
  CAppSetting^ Sett = CAppSetting::getApp();
  String^ directory = nullptr;
  SaveFileDialog^ saveConnInfo = gcnew SaveFileDialog();
  String^ path=nullptr;
  CXmlInterConnInfoSave^ XmlInterConnInfoSave=nullptr;
  saveConnInfo->Filter = "Interface Connection info(*.ici)|*.ici";
  saveConnInfo->RestoreDirectory = true;
  //Letze Pfad zum Verzeichnis auslesen
  directory = Sett->getConnDirectory();
  if(directory)
  {
    saveConnInfo->InitialDirectory = (directory);
  }
  if(saveConnInfo->ShowDialog() == ::DialogResult::OK)
  {
    path=saveConnInfo->FileName;
    if(path != nullptr)
    {
      updateFromViewToConn();
      XmlInterConnInfoSave = gcnew CXmlInterConnInfoSave(InterConnectionListe);
      XmlInterConnInfoSave->saveConnectionInfo(path);
      //updateConnListeView();
      //Letze Pfad zum Verzeichnis merken
      int pos = path->LastIndexOf("\\");
      if(pos != -1)
      {
        directory = path->Substring(0,pos);
        Sett->setConnDirectory(directory);
      }
    }
  }
}
//-------------------------------------------------------------------------
System::Void CSocketConnectionForm::OnClickButtLoad(System::Object ^  sender, System::EventArgs ^  e)
{
  CAppSetting^ Sett = CAppSetting::getApp();
  String^ directory = nullptr;
  CXmlInterConnInfoOpen^ reader=nullptr;
  OpenFileDialog^ OpenModFile = gcnew OpenFileDialog();
  System::String^ fileName;

  OpenModFile->Title = "Open Connection Info";
  OpenModFile->Filter="Interface Connection Info(*.ici)|*.ici";

  //Letze Pfad zum Verzeichnis auslesen
  directory = Sett->getConnDirectory();
  if(directory)
  {
    OpenModFile->InitialDirectory = (directory);
  }

  if(OpenModFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
  {
    fileName=OpenModFile->FileName; 
    if(fileName != nullptr)
    {
      reader = gcnew CXmlInterConnInfoOpen(InterConnectionListe);
      reader->readInterConnectionInfo(fileName);
      updateFromConnToView();

      //Letze Pfad zum Verzeichnis merken
      int pos = fileName->LastIndexOf("\\");
      if(pos != -1)
      {
        directory = fileName->Substring(0,pos);
        Sett->setConnDirectory(directory);
      }
    }
  }

}
//-------------------------------------------------------------------------
//---Delegate Methods------------------------------------------------------
void CSocketConnectionForm::setDelTreatmentRecConn(DelTreatmentRecConn^ trConn)
{
  this->TreatmentRecConn = trConn;
}
//--------------------------------------------------------------------------
void CSocketConnectionForm::updateConnectionInfo(bool status)
{
  int index = this->listBoxInter->SelectedIndex;
  if(InterConnectionListe->isConnected(index+1))
    MessageForm->writeLine("Connected!",CMessageForm::MessTyp::Info);
  if(InterConnectionListe != nullptr)
  {
    if(InterConnectionListe->isConnected(index+1))
    {
       labStatusInfo->Text = "Connected";
       labTypeInfo->Text = InterConnectionListe->getConnType(index+1);
       turnOnOffConnDisconnButtons(CConnectionInfo::ConnectionStatus::Connected);
    }
    else
    {
      if(InterConnectionListe->isWaiting(index+1))
      {
        labStatusInfo->Text = "Waiting";
        labTypeInfo->Text = InterConnectionListe->getConnType(index+1);
        turnOnOffConnDisconnButtons(CConnectionInfo::ConnectionStatus::Waiting);
      }
      else
      {
        labStatusInfo->Text = "Disconnected";
        labTypeInfo->Text = InterConnectionListe->getConnType(index+1);
        turnOnOffConnDisconnButtons(CConnectionInfo::ConnectionStatus::Disconnected);
      }
    }
  }
}
//--------------------------------------------------------------------------
//---Private Methods--------------------------------------------------------
//--------------------------------------------------------------------------
void CSocketConnectionForm::initInterfaceListe()
{
  int count;
  int index;
  count = InterConnectionListe->getInterfaceCount();
  for(int i=1;i<=count;i++)
  {
    listBoxInter->Items->Add(InterConnectionListe->getInterfaceName(i));
  }
  index = InterConnectionListe->getInterNummber(Interface);
  index--;
  if(index<0)
    index=0;
  if(listBoxInter->Items->Count > index)
    listBoxInter->SelectedIndex = index;  
}
//--------------------------------------------------------------------------
void CSocketConnectionForm::initCompConfiguration()
{
  //DelIsConnected^ con = new DelIsConnected(this,&CSocketConnectionForm::updateConnectionInfo);
  //radioButtServer->Checked = true;
  Text = (InterConnectionListe->getDirection());
  MessageForm->setShowModi(1);
  MessageForm->Show();
}
//--------------------------------------------------------------------------
void CSocketConnectionForm::updateFromConnToView()
{
  int index;
  String^ hostName=nullptr;
  String^ ipAddr=nullptr;
  int port = 0;
  CConnectionInfo::ConnectionType conType;

  if(InterConnectionListe != nullptr)
  {
    index = listBoxInter->SelectedIndex;
    if (index > -1)
    {
      chkBxLocHost->Checked = false;

      InterConnectionListe->getHostInfo(index+1,hostName,ipAddr,&port);
      if(hostName)
        labHost->Text = hostName;
      else
        labHost->Text = "";
      if(ipAddr)
        comBxIpAddr->Text = ipAddr;
      else
        comBxIpAddr->Text = "";

      if(port != -1)
        txtBxPort->Text = System::Convert::ToString(port);
      else
        txtBxPort->Text = "";
      conType = InterConnectionListe->getInterfaceAt(index+1)->getConnectionType();
      if(conType == CConnectionInfo::ConnectionType::Server)
      {
        radioButtServer->Checked = true;
        labTypeInfo->Text = "Server";
      }
      if(conType == CConnectionInfo::ConnectionType::Client)
      {
        radioButtClient->Checked = true;
        labTypeInfo->Text = "Client";
      }
      if(conType == CConnectionInfo::ConnectionType::None)
      {
        radioButtServer->Checked = true;
        InterConnectionListe->getInterfaceAt(index+1)->setConnectionType(CConnectionInfo::ConnectionType::Server);
        labTypeInfo->Text = "Server";
        turnOnOffConnDisconnButtons(CConnectionInfo::ConnectionStatus::Disconnected);
      }
      //labTypeInfo->Text = InterConnectionListe->getConnType(index+1);
      if(InterConnectionListe->isConnected(index+1))
      {
        labStatusInfo->Text = "Connected";
        //labTypeInfo->Text = InterConnectionListe->getConnType(index+1);
        turnOnOffConnDisconnButtons(CConnectionInfo::ConnectionStatus::Connected);      
      }
      else
      {
        if(InterConnectionListe->isWaiting(index+1))
        {
          labStatusInfo->Text = "Waiting";
          //labTypeInfo->Text = InterConnectionListe->getConnType(index+1);
          turnOnOffConnDisconnButtons(CConnectionInfo::ConnectionStatus::Waiting);
        }
        else
        {
          labStatusInfo->Text = "Disconnected";
          //labTypeInfo->Text = InterConnectionListe->getConnType(index+1);
          turnOnOffConnDisconnButtons(CConnectionInfo::ConnectionStatus::Disconnected);
        }
      }
    }// if (index....
  }// if(InterConnectionListe 
}
//--------------------------------------------------------------------------
void CSocketConnectionForm::updateFromViewToConn()
{
  int index;
  int value;
  
  index = listBoxInter->SelectedIndex;
  if((labHost->Text) && (comBxIpAddr->Text))
  {
    try
    {
      value = System::Convert::ToInt32(txtBxPort->Text);
      InterConnectionListe->setHostInfo(index+1,labHost->Text,comBxIpAddr->Text,value);
    }
    catch(...)
    {
    }
  }
  
}
//--------------------------------------------------------------------------
void CSocketConnectionForm::turnOnOffConnDisconnButtons(String^ status)
{
  if (status->Equals(CConnectionInfo::ConnectionStatus::Connected))
  {
    button1->Enabled = false;
    button2->Enabled = true;
  }
  else if (status->Equals(CConnectionInfo::ConnectionStatus::Waiting)) 
  {
    button1->Enabled = false;
    button2->Enabled = true;
  }
  else
  {
    button1->Enabled = true;
    button2->Enabled = false;
  }
}