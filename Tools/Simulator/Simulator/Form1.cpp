#include "stdafx.h"
#include "Form1.h"
#include <windows.h>
#include "CSzenariumForm.h"
#include "CTlgDescription.h"
#include "CElemDescription.h"
#include "CProgressBarStatusWriter.h"
#include "CThreadsManager.h"
#include "CCyclicTlgForm.h"
#include "CSendItemsServer.h"
#include "CLogWriterWrapper.h"
#include "CSplashForm.h"
#include "CAppSettingsForm.h"
#include "CFormatConverterWrapper.h"
#include "CItemView.h"
#include "CCorbaViewerForm.h"

using namespace simulator;
#undef MessageBox

bool AbortLogFileReaderThread = false;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
  System::Threading::Thread::CurrentThread->ApartmentState = System::Threading::ApartmentState::STA;
  try
  {
    Cursor::Current = Cursors::WaitCursor;
    
    CSplashForm^ splash = gcnew CSplashForm();
    splash->Show();
    Application::DoEvents();
    Application::Run(gcnew Form1(splash));
  }
  catch (System::Exception^ e)
  {
    String^ mess = String::Concat("The application will be terminated.\n",e->Message);
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    System::Windows::Forms::MessageBox::Show(nullptr,mess,
                                        "",
                                        MessageBoxButtons::OK,
                                        MessageBoxIcon::Error);
  }
  catch (...)
  {
    String^ mess = "The application will be terminated.";
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    System::Windows::Forms::MessageBox::Show(nullptr,mess,
                                        "",
                                        MessageBoxButtons::OK,
                                        MessageBoxIcon::Error);
  }
  return 0;
}

//static void Main() 
//{  
//  System::Threading::Thread::CurrentThread->ApartmentState = System::Threading::ApartmentState::STA;
//  try
//  {
//    Cursor::Current = Cursors::WaitCursor;
//    
//    CSplashForm^ splash = gcnew CSplashForm();
//    splash->Show();
//    Application::DoEvents();
//    Application::Run(gcnew Form1(splash));
//  }
//  catch (System::Exception^ e)
//  {
//    String^ mess = String::Concat("The application will be terminated.\n",e->Message);
//    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
//                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
//    System::Windows::Forms::MessageBox::Show(nullptr,mess,
//                                        "",
//                                        MessageBoxButtons::OK,
//                                        MessageBoxIcon::Error);
//  }
//  catch (...)
//  {
//    String^ mess = "The application will be terminated.";
//    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
//                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
//    System::Windows::Forms::MessageBox::Show(nullptr,mess,
//                                        "",
//                                        MessageBoxButtons::OK,
//                                        MessageBoxIcon::Error);
//  }
//}  

//---------------------------------------------------------------------------
System::Void Form1::MenuAppConf_Click(System::Object^  sender, System::EventArgs^  e) 
{
  CAppSettingsForm^ appSetting = gcnew CAppSettingsForm();
  appSetting->ShowDialog();
}
//---------------------------------------------------------------------------
System::Void Form1::MenuModel_Click(System::Object^  sender, System::EventArgs^  e) 
{
  CTlgInterfaceWrapper^ inter=nullptr;
  if (InterfaceProtoArray->Count > 0)
  {
    inter = safe_cast<CTlgInterfaceWrapper^>(InterfaceProtoArray[ActInterface]);
    /*MenuInterfaceRemove->Enabled = !inter->checkRefOfAllPrototypTlg();*/
    String^ interName = inter->getInterfaceName();
    
    
    //WennnTlgs in Szenario, LogFileContainer und Cycliccontainer vorkommen
    if (CCyclicItemContainer::getCyclicItemContainer()->TlgsFromInterInCyclicCon(interName) ||
        SenderForm->TlgsFromInterInSzenario(interName) || (SenderForm->getLogFileTlgCount(interName) > 0))
      MenuInterfaceRemove->Enabled = false;
    else
      MenuInterfaceRemove->Enabled = true;
  }
  else
    MenuInterfaceRemove->Enabled = false;
}
//---------------------------------------------------------------------------
System::Void Form1::OnLoadSimForm(System::Object ^  sender, System::EventArgs ^  e)
{
 
}
//---------------------------------------------------------------------------
System::Void Form1::MenuRemoveAllCyclicTelegrams_Click(System::Object^  sender, System::EventArgs^  e) 
{
  ::Cursor::Current = ::Cursors::WaitCursor;
  SenderForm->removeAllCyclicTlgInSzenario();  
  ::Cursor::Current = ::Cursors::Default;
}
//---------------------------------------------------------------------------
System::Void Form1::MenuCyclicStop_Click(System::Object^  sender, System::EventArgs^  e) 
{
  CCyclicItemContainer::getCyclicItemContainer()->StopAll();
}
//---------------------------------------------------------------------------
System::Void Form1::MenuCyclicSend_Click(System::Object^  sender, System::EventArgs^  e) 
{
  CCyclicItemContainer^ cycCon = CCyclicItemContainer::getCyclicItemContainer();
  CLogWriterWrapper^ logWriter = CLogWriterWrapper::getLogWriterWrapper();
  CSendItemsServer^ itemSer = CSendItemsServer::getSendItemsServer();

  if (cycCon->getCountOfInterface() > 0)
  {
    if (!cycCon->IsSending())
    {
      Windows::Forms::DialogResult result = Windows::Forms::DialogResult::None;
      if (SenderForm->getCountOfSzenarioItems() > 0 && !SenderForm->isSzenarioSending())
         result = MessageBox::Show("Do you want send cyclic telegrams with szenario?",
                                "Send Cyclic Telegram",
                                MessageBoxButtons::YesNoCancel,  
                                MessageBoxIcon::Question,  
                                MessageBoxDefaultButton::Button2);

      if (result != Windows::Forms::DialogResult::Cancel)
      {
        itemSer->setMessageHandler (gcnew CSendItemsServer::MessageHandlerTyp(this,&Form1::WriteMessage));
        /*CCyclicItemContainer::getCyclicItemContainer()->setWriteMessageDelTyp
              (gcnew CCyclicItemContainer::WriteMessageDelTyp(this,&Form1::WriteMessage));*/

       if (result == Windows::Forms::DialogResult::Yes)
       {
         if (SenderForm->isSendMode()) 
         {
           SenderForm->sendSzenarium();
           cycCon->Send(SendInterConnectionListe);
         }
         else
         {
           String^ mess = "Send mode is not activated";
           MessageForm->writeLine(mess,CMessageForm::MessTyp::Error);
           logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
         }
       }
       else
        cycCon->Send(SendInterConnectionListe);
      }
    }
    else
    {
      String^ mess = "Process of send cyclic telegrams already run";
      MessageForm->writeLine(mess,CMessageForm::MessTyp::Warning);
      logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    }
  }
  else //Wenn keine zyklische Tlg im Con drin sind
  {
    String^ mess = "No cyclic telegrams found";
    MessageForm->writeLine(mess,CMessageForm::MessTyp::Error);
    logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  }
}
//---------------------------------------------------------------------------
System::Void Form1::MenuCyclicShow_Click(System::Object^  sender, System::EventArgs^  e) 
{
  //Wenn keine zyklische Telegramme gesendet werden
  if (!CCyclicItemContainer::getCyclicItemContainer()->IsSending())
  {
    CCyclicTlgForm^ cyclicForm = gcnew CCyclicTlgForm(MessageForm,InterfaceProtoArray);
    cyclicForm->ShowDialog();
  }
  else
  {
    String^ mess = "Configuration of the cyclic telegrams in send mode ist not allowed.";
    MessageForm->writeLine(mess,CMessageForm::MessTyp::Warning);
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  }
}
//---------------------------------------------------------------------------
System::Void Form1::OnCloseForm(System::Object ^  sender, System::EventArgs ^  e)
{
  CloseForm();
}
//---------------------------------------------------------------------------
System::Void Form1::OnSizeChange(System::Object ^  sender, System::EventArgs ^  e)
{
  setKompPos();
}
//---------------------------------------------------------------------------
System::Void Form1::menuItemHelpAbout_Click(System::Object^  sender, System::EventArgs^  e) 
{
  MessageBox::Show("         Simulator 2.1.1\nCopyright 2011, SMS Siemag","About Simulator",  
                MessageBoxButtons::OK,  
                MessageBoxIcon::Information,  
                MessageBoxDefaultButton::Button3);  
}
//---------------------------------------------------------------------------
System::Void Form1::OnMenOpenFileClick(System::Object ^  sender, System::EventArgs ^  e)
{
  String^ mess = nullptr;
  barView = gcnew CProgressBarViewForm(); 
  CProgressBarStatusWriter^ ProgressWriter = gcnew CProgressBarStatusWriter(barView);
  CTlgLogFileReaderWrapper^ fileReader=nullptr;
  CTlgInterfaceWrapper^ inter=nullptr;
  /*String^ fileName = 0;*/
  String^ Directory=nullptr;
  bool flag;
  int i;//count;
  int count_tlg;
  int ret=0;
  MenuItem^ item = safe_cast<MenuItem^>(sender);
  OpenFileDialog^ OpenModFile = gcnew OpenFileDialog();
  OpenModFile->Title = item->Text;
  CAppSetting^ Sett = CAppSetting::getApp();
  Directory=Sett->getLogFileDirectory();
  if(Directory)
  {
    OpenModFile->InitialDirectory = (Directory);
  }
  OpenModFile->Filter = "Log-File (*.log)|*.log|All files(*.*)|*.*";
  MessageForm->setActionName("Load Log - File");
  if(OpenModFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
  {
    ::Cursor::Current = ::Cursors::WaitCursor;
    if((fileName=OpenModFile->FileName) != nullptr)
    {
      flag = true;
      i=0;
      /*String^ interName = 0;*/
      CMessageWriter^ MessageWriter = gcnew CMessageWriter(MessageForm); 
      mess = String::Concat("Load Log File: ",fileName);
      MessageForm->writeLine(mess,CMessageForm::MessTyp::Info);
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                                            __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      //int inter_num = findInterface(fileName);
      //interName="BAS_AOD";
      int inter_num = 0;
      interName = SenderForm->findInterface(fileName);
      CInterConfigWrapper^ confWr = gcnew CInterConfigWrapper();
  
      if(interName != nullptr)
      {
        if (confWr->isIdElementDefined(interName))
        {
          if(item->Text == "As New File")
          {
            SenderForm->clearLogFile(interName);
          }
          count_tlg=SenderForm->getLogTlgCount(interName);
          changeActiveInterface(interName);
          MessageForm->setActionName(CMessageForm::TextCaption::LoadLogFile);
          
          //--------Datei Groesse ermitteln -------
          System::IO::FileInfo^ file = gcnew System::IO::FileInfo(fileName);
          //File Groesse an ProgressBar ubergeben
          barView->setMinAndMax(0,file->Length);
          barView->setSourceLab(fileName);
          barView->setCancelButtonVisible(true);
          CProgressBarViewForm::BarViewAbortDelTyp^ barViewAbort = gcnew CProgressBarViewForm::BarViewAbortDelTyp(this,&Form1::AbortLogFileReadThread); 
          barView->setBarViewAbortDelTyp(barViewAbort);
          
          //Thread fuer LogFileReader
          System::Threading::ThreadStart^ delStart = gcnew System::Threading::ThreadStart(this,&Form1::logFileReadThread);
          LogFileReadThread= gcnew System::Threading::Thread(delStart);
          LogFileReadThread->Start();
          //Liest Messages aus
          MessageWriter->startWrite();
					//Aktualisiert PrograssBarView
          ProgressWriter->startWrite();
          //BarView als Modal anzeigen
          barView->ShowDialog();
          //Beenden
          ProgressWriter->endWrite();
          MessageWriter->endWrite();
          ////Thread beenden
          //LogFileReadThread->Abort();
          barView=nullptr;
          ret = RetLogFileReader;
          if(ret == 0)
          {
            int count = SenderForm->getLogTlgCount(interName);
            int total = SenderForm->getLogTlgTotalCount(interName);
            count=count-count_tlg;
            mess = String::Concat("Total: ",System::Convert::ToString(total));
            CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                                              __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
            MessageForm->writeLine(mess,CMessageForm::MessTyp::Info);
            mess = String::Concat("Accept: ",System::Convert::ToString(count));
            CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                                              __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
            MessageForm->writeLine(mess,CMessageForm::MessTyp::Info);
            mess = String::Concat("Not Accept:",System::Convert::ToString(total-count));
            CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                                              __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
            MessageForm->writeLine(mess,CMessageForm::MessTyp::Info);
            SenderForm->showLogTlg(interName);
          }
          MessageForm->setActionName(CMessageForm::TextCaption::Sender);
        }
        else
        {
        mess = "Id and lenght not defined, configure first!";
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                  __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        System::Windows::Forms::MessageBox::Show(nullptr,mess,
                                        "",
                                        MessageBoxButtons::OK,
                                        MessageBoxIcon::Error);
        }
      }
      else
      {
        mess = "No loaded interface found for this log file!";
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                            __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        MessageForm->writeLine(mess,CMessageForm::MessTyp::Error);
      }
      
      int pos=fileName->LastIndexOf("\\");
      if(pos != -1)
      {
        Directory = fileName->Substring(0,pos);
        Sett->setLogFileDirectory(Directory);
      }
    }
  }
}
//---------------------------------------------------------------------------
System::Void Form1::OnMenuFileLoadModelClick(System::Object ^  sender, System::EventArgs ^  e)
{
  // bool flag;
  int index;
  int loadInterRet;
  OpenFileDialog^ OpenModFile = gcnew OpenFileDialog();
  System::String^ fileName;
  String^ itemName=nullptr;
  String^ directory=nullptr;
  OpenModFile->Title = "Load Interface";
  OpenModFile->Filter="Interface File(*.xml)|*.xml";

  CAppSetting^ Sett = CAppSetting::getApp();
  directory = Sett->getInterDirectory();
  if(directory)
  {
    OpenModFile->InitialDirectory = (directory);
  }

  if(OpenModFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
  {
    if((fileName=OpenModFile->FileName) != nullptr)
    {
      ifNewIncfFile->newFile = false;
      //Uberpruefen, ob im Standardverzeichnis schon eine INCF - Datei mit
      //gleichen Namen existiert
      if (setIncfFile(fileName))
      {
        //----------------------------
        loadInterRet=loadInterface(fileName);
        if(loadInterRet == 0)
        {
            CTlgInterfaceWrapper^ inter=nullptr;
            index=InterfaceProtoArray->Count;
            inter = safe_cast<CTlgInterfaceWrapper^>(InterfaceProtoArray[index-1]);
            itemName=inter->getInterfaceName();
            //-----
            if (ifNewIncfFile->newFile)
            {
              CXmlInterConfigWriter^ confWriter = gcnew CXmlInterConfigWriter();
              confWriter->createInterConfigFile(inter,ifNewIncfFile->path);
              /*Sett->addInterDefaultConfigFile(ifNewIncfFile->path,ifNewIncfFile->inter);*/
            }
            //-----
            
            System::Windows::Forms::MenuItem^ Item = gcnew System::Windows::Forms::MenuItem(itemName);
            Item->Click += gcnew System::EventHandler(this, &Form1::OnMenuModelClick);
            //mainMenu->MenuItems[1)->MenuItems->Add(Item);
            mainMenu->MenuItems[0]->MenuItems[1]->MenuItems->Add(Item);
            Item->PerformClick();

            int flag=0;
            

            //CInfoForm^ form = gcnew CInfoForm();
            //form->setMessage("Load this interface always on application start?");
            //form->ShowDialog();
            //if(form->getAnswer())
            //{
            //  CAppSetting::getApp()->addInterface(fileName);
            //}
            //else
            //{
            //  // write error
            //}

            CAppSetting::getApp()->addInterface(fileName);

            int pos = fileName->LastIndexOf("\\");
            if(pos != -1)
            {
              directory = fileName->Substring(0,pos);
              Sett->setInterDirectory(directory);
            }
          {
            System::Windows::Forms::MenuItem^ ItemConfig;
            ItemConfig=mainMenu->MenuItems[0]->MenuItems[5];
            ItemConfig->PerformClick();
          }
        }
        else
        {
          if(loadInterRet != 1)
          {
            String^ mess = "File couldn't be read!";
            CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                            __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
            MessageBox::Show(nullptr,mess,"Error",System::Windows::Forms::MessageBoxButtons::OK);
          }
        }
      }
      //----------------------------
    }
  }
}
//---------------------------------------------------------------------------
System::Void Form1::menuItemContents_Click(System::Object^  sender, System::EventArgs^  e) 
{
  Help::ShowHelp(this,"Simulator.chm",HelpNavigator::TableOfContents,nullptr);     
}
//---------------------------------------------------------------------------
System::Void Form1::menuItemHelpIndex_Click(System::Object^  sender, System::EventArgs^  e) 
{
  Help::ShowHelp(this,"Simulator.chm",HelpNavigator::Index,nullptr); 
}
//---------------------------------------------------------------------------
System::Void Form1::OnMenuModelClick(System::Object ^  sender, System::EventArgs ^  e)
{
  int count=0;
  int i,index;
  MenuItem^ Item = safe_cast<MenuItem^>(sender);
  String^ descr=nullptr;
  String^ ItemName=nullptr;

  count = mainMenu->MenuItems[0]->MenuItems[1]->MenuItems->Count;
  for(i=0;i<count;i++)
    mainMenu->MenuItems[0]->MenuItems[1]->MenuItems[i]->Checked = false;

  Item->Checked = true;
  
  ItemName = Item->Text;
  Interface = Item->Text;
  index=Item->Index;
  ActInterface = index;
  
  ReceiverForm->setActiveInterface(ItemName);
  SenderForm->setActiveInterface(ItemName);

  descr=SenderForm->getInterfaceDescr(ItemName);
  labInterfaceName->Text = String::Concat(ItemName,"(",descr,")");
  labVersionInfo->Text = SenderForm->getInterfaceVersion(ItemName);

  updateConnStatusLabel(Interface);
}
//---------------------------------------------------------------------------
System::Void Form1::MenuSaveSimpleTimeSzen_Click(System::Object^  sender, System::EventArgs^  e) 
{
  SaveFileDialog^ saveSzen = gcnew SaveFileDialog();
  String^ path=nullptr;
  String^ directory=nullptr;

  CAppSetting^ Sett = CAppSetting::getApp();
  directory = Sett->getSzenDirectory();
  if(directory)
  {
    saveSzen->InitialDirectory = (directory);
  }
  saveSzen->Filter = "Szenarium-Text (*.szn)|*.szn|Szenarium-XML (*.xml)|*.xml|All files(*.*)|*.*";
                     
  if(saveSzen->ShowDialog() == ::DialogResult::OK)
  {
    ::Cursor::Current = ::Cursors::WaitCursor;
    path=saveSzen->FileName;
    if(path != nullptr)
    {
      SenderForm->saveSimpleTimeSzenarium(path);
      int pos = path->LastIndexOf("\\");
      if(pos != -1)
      {
        directory = path->Substring(0,pos);
        Sett->setSzenDirectory(directory);
      }
    }
  }
}
//---------------------------------------------------------------------------
System::Void Form1::OnMenuFileSaveSzen(System::Object ^  sender, System::EventArgs ^  e)
{
  SaveFileDialog^ saveSzen = gcnew SaveFileDialog();
  String^ path=nullptr;
  String^ directory=nullptr;

  CAppSetting^ Sett = CAppSetting::getApp();
  directory = Sett->getSzenDirectory();
  if(directory)
  {
    saveSzen->InitialDirectory = directory;
  }
  saveSzen->Filter = "Szenarium-Text (*.szn)|*.szn|Szenarium-XML (*.xml)|*.xml|All files(*.*)|*.*";
                     
  if(saveSzen->ShowDialog() == ::DialogResult::OK)
  {
    ::Cursor::Current = ::Cursors::WaitCursor;
    path=saveSzen->FileName;
    if(path != nullptr)
    {
      SenderForm->saveSzenarium(path);
      int pos = path->LastIndexOf("\\");
      if(pos != -1)
      {
        directory = path->Substring(0,pos);
        Sett->setSzenDirectory(directory);
      }
    }
  }
}
//---------------------------------------------------------------------------
//Menu->Szenario->Open
//---------------------------------------------------------------------------
System::Void Form1::OnMenuFileSzenOpenClick(System::Object ^  sender, System::EventArgs ^  e)
{
  OpenFileDialog^ OpenModFile = gcnew OpenFileDialog();
  System::String^ fileName;
  String^ directory=nullptr;

  OpenModFile->Title = "Open Szenarium";
  OpenModFile->Filter = "Szenarium-Text (*.szn)|*.szn|Szenarium-XML (*.xml)|*.xml|All files(*.*)|*.*";

  CAppSetting^ Sett = CAppSetting::getApp();
  directory = Sett->getSzenDirectory();
  if(directory)
  {
    OpenModFile->InitialDirectory = (directory);
  }

  if(OpenModFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
  {
    ::Cursor::Current = ::Cursors::WaitCursor;
    if((fileName=OpenModFile->FileName) != nullptr)
    {
      MessageForm->setActionName(CMessageForm::TextCaption::LoadSzenario);
      SenderForm->loadSzenarium(fileName);
      int pos = fileName->LastIndexOf("\\");
      if(pos != -1)
      {
        directory = fileName->Substring(0,pos);
        Sett->setSzenDirectory(directory);
      }
      MessageForm->setActionName(CMessageForm::TextCaption::Sender);
      // System::Windows::Forms::Menu::MenuItemCollection^ col=0;
      //col=mainMenu->MenuItems[2)->MenuItems;
      //col[1)->Enabled=true;
      //col[2)->Enabled=true;
    }
    // !!! Close-Button aktivieren
    //menuItem7->Enabled=true;
  }
}
//---------------------------------------------------------------------------
System::Void Form1::OnMenuConnectionClick(System::Object ^  sender, System::EventArgs ^  e)
{
  CSocketConnectionForm^ conForm = nullptr;

  if(Direction == DirectionType::Send)
  {
    // if a connection for sending should be established
    // then this interface will be connected immediately
    conForm = gcnew CSocketConnectionForm(SendInterConnectionListe,Interface,true);
  }
  else
  {
    if(Direction == DirectionType::Rec)
    {
      conForm = gcnew CSocketConnectionForm(RecInterConnectionListe,Interface,false);
    }
  } 
  conForm->ShowDialog();
  ReceiverForm->showInterConnInfo();
}
//---------------------------------------------------------------------------
System::Void Form1::OnClickMenuInterConfig(System::Object ^  sender, System::EventArgs ^  e)
{
  CInterConfigForm^ configForm = gcnew CInterConfigForm();
  System::Windows::Forms::DialogResult res;

  configForm->setInterfaceList(InterfaceProtoArray);
  configForm->setActiveInterface(Interface);
  res = configForm->ShowDialog();
  if(res == System::Windows::Forms::DialogResult::OK)
  {
    array <String^>^ liste = nullptr;
    int count;
    
    liste = configForm->getUpdateInterfacListe(); 
    if(liste != nullptr)
    {
      CInterConfigWrapper^ confWr = gcnew CInterConfigWrapper();
      CAppSetting^ Sett = CAppSetting::getApp();
      String^ confFilePath;
      count = liste->Length;
      for(int i=0;i<count;i++)
      {
        confFilePath = Sett->getInterConfigFilePath(liste[i]);
        confWr->readInterConfigurationFile(liste[i],confFilePath);
      }
      if (count!=0)
        SenderForm->updateUseCaseView();
    }

    //Aktuell geoeffnete Tlg - Ansicht rechts schliessen
    this->SenderForm->ClosePrototypItemView();
  }
}
//---------------------------------------------------------------------------
System::Void Form1::OnMenuInterConnStatus(System::Object ^  sender, System::EventArgs ^  e)
{
  StatusConnectionForm  = gcnew CStatusConnectionForm(SendInterConnectionListe,RecInterConnectionListe);
  StatusConnectionForm->TopMost = (true);
  StatusConnectionForm->Show();
  StatusConnectionForm = nullptr;
}
//---------------------------------------------------------------------------
void Form1::OpenSenderConnectionStatusDialog()
{
  StatusConnectionForm  = gcnew CStatusConnectionForm(SendInterConnectionListe,nullptr);
  StatusConnectionForm->TopMost = (true);
  StatusConnectionForm->Show();
  StatusConnectionForm = nullptr;
}
//---------------------------------------------------------------------------
System::Void Form1::OnMenuSzenSendClick(System::Object ^  sender, System::EventArgs ^  e)
{
  MessageForm->setActionName("Send Szenarium");
  SenderForm->sendSzenarium();  
}
//---------------------------------------------------------------------------
System::Void Form1::OnSzenStopClick(System::Object ^  sender, System::EventArgs ^  e)
{
  SenderForm->stopSendSzenarium(false);
}
//---------------------------------------------------------------------------
// !!!
System::Void Form1:: OnSzenCloseClick(System::Object ^  sender, System::EventArgs ^  e)
{
  if (!SenderForm->isSendMode())
  {
    SenderForm->updateSzenFile();
    //setSzenUpdateModus(false);
    updateSzenariumMidus(0);
  }
  else
  {
    String^ mess = "Close the szenario in the send mode is not allowed.";
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,
                                              __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    MessageForm->writeLine(mess,CMessageForm::MessTyp::Warning);
  }
  // !!! Close-Button deaktivieren
  // menuItem7->Enabled=false;
}
//---------------------------------------------------------------------------
System::Void Form1::OnMenuViewSenderClick(System::Object ^  sender, System::EventArgs ^  e)
{
    MenuItem^ Item = safe_cast<MenuItem^>(sender);
    Item->Checked = true;
    if(Item->Index == 0)
    {
      menuViewReceiver->Checked = false;
      ReceiverForm->Hide();
      SenderForm->setMessageForm(MessageForm);
      SenderForm->Show();
      Direction = DirectionType::Send;
      activateSenderMenu();
      Text = "Simulator-Level 2 (Sender)";
      MessageForm->setActionName(CMessageForm::TextCaption::Sender);

    }
    else
    {
      menuViewSender->Checked = false;
      SenderForm->Hide();
      ReceiverForm->setMessageForm(MessageForm);
      ReceiverForm->Show();
      Direction = DirectionType::Rec;
      activateReceiverMenu();
      Text = "Simulator-Level 2 (Receiver)";
      MessageForm->setActionName(CMessageForm::TextCaption::Receiver);
    }
}
//---------------------------------------------------------------------------
//Menu->Interface->Remove Interface
//---------------------------------------------------------------------------
System::Void Form1::OnInterfaceRemoveClick(System::Object ^  sender, System::EventArgs ^  e)
{   
  System::Windows::Forms::DialogResult res;
  res=System::Windows::Forms::MessageBox::Show(nullptr,"Remove this interface?","",
																								MessageBoxButtons::YesNo,MessageBoxIcon::Question);

  if(res == System::Windows::Forms::DialogResult::Yes)
  {
    if(ActInterface >= 0)
    {
      int count;
      String^ interName=nullptr;
      CTlgInterfaceWrapper^ inter = safe_cast<CTlgInterfaceWrapper^>(InterfaceProtoArray[ActInterface]);
      interName=inter->getInterfaceName();
      SenderForm->removeInter(interName);
      ReceiverForm->removeInter(interName);
      SenderForm->clearUseCaseView();
      inter->removeInter();
      InterfaceProtoArray->RemoveAt(ActInterface);
       
      //mainMenu->MenuItems->
      mainMenu->MenuItems[0]->MenuItems[1]->MenuItems->RemoveAt(ActInterface);
      count=mainMenu->MenuItems[0]->MenuItems[1]->MenuItems->Count;

      if(count>0)
      {
        ActInterface=0;
        mainMenu->MenuItems[0]->MenuItems[1]->MenuItems[0]->PerformClick();
      }
      else
      {
        ActInterface=-1;
      }
  
      //entfernen aus IniFile
      CAppSetting::getApp()->removeInterface(interName);
      //entfernen aus Socket - Verbindungen
      SendInterConnectionListe->removeInerface(interName);
      RecInterConnectionListe->removeInerface(interName);
    }
  }
}
//---------------------------------------------------------------------------
System::Void Form1::OnMenuLogFileSortClick(System::Object ^  sender, System::EventArgs ^  e)
{
  TlgContainerSortForm = gcnew CTlgContainerSortForm();
  TlgContainerSortForm->TopMost = true;
  TlgContainerSortForm->setContainerToSort(SenderForm->getLogFileContainer());
  CTlgContainerSortForm::sortedEventTyp^ event = gcnew CTlgContainerSortForm::sortedEventTyp(this,&Form1::sortedLogFileView); 
  TlgContainerSortForm->setSortedEvent(event);
  TlgContainerSortForm->Show();
}
//---------------------------------------------------------------------------
System::Void Form1::OnMenuLogFileFilterClick(System::Object ^  sender, System::EventArgs ^  e)
{
  TlgContainerFilterForm = gcnew CTlgContainerFilterForm(this->SenderForm->getLogFileContainer()->getFilterRegExpAsStringArray());
  CTlgContainerFilterForm::DelRegExprTyp^ regEven = gcnew CTlgContainerFilterForm::DelRegExprTyp(this,&Form1::setFilterLogFile);
  TlgContainerFilterForm->setRegExprEvent(regEven);
  TlgContainerFilterForm->TopMost = true;
  TlgContainerFilterForm->Show();
}
//---------------------------------------------------------------------------
System::Void Form1::OnMenuLogFileFindTelClick(System::Object ^  sender, System::EventArgs ^  e)
{
  CTlgContainerFindForm::EventDownOkTyp^ event=nullptr;
  TlgContainerFindForm = gcnew CTlgContainerFindForm(); 
  TlgContainerFindForm->TopMost=true;
  System::Windows::Forms::MenuItem^ item = safe_cast<System::Windows::Forms::MenuItem^>(sender);
  if(item == Menu->MenuItems[1]->MenuItems[3])
  {
    event = gcnew CTlgContainerFindForm::EventDownOkTyp(this,&Form1::findInLogFile);
    TlgContainerFindForm->setInterface(getActiveInterfaceWrapper());
    TlgContainerFindForm->setContainerToFind(SenderForm->getLogFileContainer());
    TlgContainerFindForm->initTlgFromInterface();
  }
  else
  {
    event = gcnew CTlgContainerFindForm::EventDownOkTyp(this,&Form1::findInSzenarium);
    TlgContainerFindForm->setContainerToFind(SenderForm->getSzenariumContainer());
    TlgContainerFindForm->initTlgFromContainer();
  }
  TlgContainerFindForm->setOkDownEvent(event);
  TlgContainerFindForm->Show();
}
//---------------------------------------------------------------------------
System::Void Form1::OnMenuLogFileCloseClick(System::Object ^  sender, System::EventArgs ^  e)
{
  SenderForm->closeLogFile();
  updateMenuLogFileView(false);
}
//---------------------------------------------------------------------------
System::Void Form1::OnMenuSzenariumFindClick(System::Object ^  sender, System::EventArgs ^  e)
{
  TlgContainerFindForm = gcnew CTlgContainerFindForm(); 
  TlgContainerFindForm->Show();
}
//---------------------------------------------------------------------------
System::Void  Form1::OnMenuLogFileSelectAll(System::Object ^  sender, System::EventArgs ^  e)
{
  SenderForm->selectAllTlgFromLogFile();
}
//---------------------------------------------------------------------------
System::Void Form1::OnMenuLogFileRemoveSel(System::Object ^  sender, System::EventArgs ^  e)
{
  SenderForm->removeSelectionTlgFromLogFile();
}
//---------------------------------------------------------------------------
System::Void Form1::OnMenuModelSpezBof(System::Object ^  sender, System::EventArgs ^  e)
{  
  //BofForm->Show();
  if (BofMainForm && BofMainForm->getTlgInterface() && BofMainForm->getInterConnectionReceive() && BofMainForm->getInterConnectionSenden())
    BofMainForm->Show();
  else
  {
    String^ mess = "No <BAS_BOF> interface is loaded.";
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                        __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    MessageForm->writeLine(mess,CMessageForm::MessTyp::Error);
  }
}
// !!!
//----------------------------------------------------------------------------
System::Void Form1::OnMenuLogFileTraceClick(System::Object ^  sender, System::EventArgs ^  e)
{
  CAppSetting^ Sett = CAppSetting::getApp();
  String^ directory = nullptr;
  String ^InterfaceName=gcnew String(" ");
  bool ok=false;
  int index=0;
  
  ::Cursor::Current = ::Cursors::WaitCursor;
  // Open-Dailog starten
  OpenFileDialog^ OpenLogFile = gcnew OpenFileDialog();
  System::String^ fileName;
  OpenLogFile->Title = "Open LogFile";
  OpenLogFile->Filter="Szenarium File(*.log)|*.log";

  directory = Sett->getAnalyzerDirectory();
  if(directory)
  {
    OpenLogFile->InitialDirectory = (directory);
  }

  if(OpenLogFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
  {
    ::Cursor::Current = ::Cursors::WaitCursor;
    if((fileName=OpenLogFile->FileName) != nullptr)
    {
      CTlgLogFileReaderWrapper^ LogFileReader=gcnew CTlgLogFileReaderWrapper();
      CTlgInterfaceWrapper^ a = gcnew CTlgInterfaceWrapper();
      //Testen, ob fuer Log-File eine Schnittstelle geladen ist
      for (index=0;index<InterfaceProtoArray->Count;index++)
      {
        a=safe_cast <CTlgInterfaceWrapper^> (InterfaceProtoArray[index]);
        LogFileReader->setTlgProtoTyp(a->getTlgProtoTypSet());
        if (LogFileReader->checkInterface(fileName))
        {
          ok=true;
          break;
        }
      }
      if (ok)
      {
        ReceiverForm->showAnazyzeForm(index,fileName);
      }
      else
      {
        String^ mess = "No interface for this log-file is loaded.";
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                            __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        MessageForm->writeLine(mess,CMessageForm::MessTyp::Error);
      }
   
      int pos = fileName->LastIndexOf("\\");
      if(pos != -1)
      {
        directory = fileName->Substring(0,pos);
        Sett->setAnalyzerDirectory(directory);
      }
    }
  }
}
//----------------------------------------------------------------------------
void Form1::initViewComponent()
{
  bool neuIniFile = false;
  labInterfaceName->Left = panHead->Width/2 - 80;
  CAppSetting^ Sett = CAppSetting::getApp();
  if(!Sett->checkIniFile())
  {
    Splash->SetText("Creating INI - File ...");
    String^ mess = nullptr;
    String^ ini = Sett->getIniFileName();
    mess = String::Concat("File ",ini," is not found!");
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                              __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    MessageForm->writeLine(mess,CMessageForm::MessTyp::Info);
    Sett->createIniFile();
    mess = String::Concat(ini," is created");
    Splash->SetText(mess);
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                              __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    MessageForm->writeLine(mess,CMessageForm::MessTyp::Info);
    neuIniFile = true;
  }
  //ItemView
  CItemView::setNodesCollapsed(CFormatConverterWrapper::StringToInt(Sett->getNodesInTlgViewCollapsed()));  
  //Pfad fuer LogWriter festlegen und entsprechende Ordner erzeugen
  String^ path = String::Concat(System::Windows::Forms::Application::StartupPath,"\\SimLog\\");
  try
  {
    IO::Directory::CreateDirectory(path);
    CLogWriterWrapper::getLogWriterWrapper()->setPath(path);
  }
  catch (Exception^ ex)
  {
    MessageForm->writeLine(ex->Message,CMessageForm::MessTyp::Error);
    MessageForm->writeLine("It will write no mesages into the log-file",CMessageForm::MessTyp::Error);
  }
  //
  CLogWriterWrapper::getLogWriterWrapper()->ReadSettingsFromIniFile();
  Splash->SetText("Remove all needless Log - File ...");
  CLogWriterWrapper::getLogWriterWrapper()->removeNeedlessLogFiles();
  
  if (!neuIniFile)
  {
    isSimFormLoaded = true;
    loadInterfaces();
    isSimFormLoaded = false;
  }
  
  Show();
  SenderForm->Show();
  ::Cursor::Current = ::Cursors::Default;
  Focus();
  SenderForm->Focus();
}
//-----------------------------------------------------------------------------
void Form1::loadInterfaces()
{
  int count,i;
  array <String^>^ interPath = nullptr;
  CAppSetting^ Sett = CAppSetting::getApp();

  interPath = Sett->getInterfacePath();
  count = interPath->Length;
  if(count != 0)
  {
    MessageForm->setActionName("Load Interface");
    for(i=0;i<count;i++)
    {
      if(System::IO::File::Exists(interPath[i]))
      {
          loadInterface(interPath[i]);
      }
      else
      {
        String^ mess = String::Concat("File: ",interPath[i],"  not found"); 
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                              __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        MessageForm->writeLine(mess,CMessageForm::MessTyp::Error);
      }
    }
  }
  
  String^ itemName=nullptr;
  System::Windows::Forms::MenuItem^ Item=nullptr;
  CTlgInterfaceWrapper^ inter=nullptr;

  count = InterfaceProtoArray->Count;
  for(i=0;i<count;i++)
  {
    inter = safe_cast<CTlgInterfaceWrapper^>(InterfaceProtoArray[i]);
    itemName=inter->getInterfaceName();
    System::Windows::Forms::MenuItem^ Item = gcnew System::Windows::Forms::MenuItem(itemName);
		Item->Click += gcnew System::EventHandler(this, &Form1::OnMenuModelClick);
    mainMenu->MenuItems[0]->MenuItems[1]->MenuItems->Add(Item);
  }
  
  
  String^ lastActiveInterface = Sett->getLastActivInterfaceName();
  if (String::Equals(lastActiveInterface,""))
  {
    if(count != 0)
      mainMenu->MenuItems[0]->MenuItems[1]->MenuItems[0]->PerformClick();
  }
  else
  {
    this->changeActiveInterface(lastActiveInterface);
  }
}
//-----------------------------------------------------------------------------
void Form1::sendTlg()
{
  /* Byte array_byte[];
   int count,len;
   unsigned char buffer[1024];
   double delay;
   double delay_vor=0.0;
   int delay1;
   String^ mess = 0;
    //CClientSynch* ClientSynch=0;
    //CInterManagement* InterMan=0;
    //CMessageForm* MessForm=CMessageForm::getMessageForm();
   
    //InterMan=SenderConnectList->getInterMan(ActInterface);

    //if(InterMan->isServer())


    Szen=FileReaderViewForm->getSzenarium();
    count=Szen->getSzenItemCount();
   
    for(int i=1;i<=count;i++)
    { 
      len = Szen->getSerializeTlg(i,buffer,1024);
      //array_byte = new Byte[len];
      //for(int j=0;j<len;j++)
      //{
        //array_byte[j] = buffer[j];
      //}
      delay = Szen->getTimeDelay(i);
      if(i != 1)
        FileReaderViewForm->setColor( System::Drawing::Color::FromKnownColor(System::Drawing::KnownColor::Control),i-2);
      FileReaderViewForm->setColor(System::Drawing::Color::Green,i-1);
      if(delay > delay_vor)
         System::Threading::Thread::get_CurrentThread()->Sleep((delay-delay_vor)*1000);
      //bool test;
      //test=InterConnectionListe->isConnected(ActInterface+1);
      //InterConnectionListe->sendByteStream( buffer,len,ActInterface+1);
      //InterMan->sendTlg(array_byte,len);  
      mess = String::Concat(" Telegram war gesendet: Delay(",System::Convert::ToString(delay-delay_vor),")");
      //MessForm->writeLine(mess,CMessageForm::MessTyp::Ok);
      delay_vor=delay;
   }
      FileReaderViewForm->setColor( System::Drawing::Color::FromKnownColor(System::Drawing::KnownColor::Control),count-1);
    mess = String::Concat(System::Convert::ToString(count)," Telegram war gesendet");
//     MessForm->writeLine(mess,CMessageForm::MessTyp::Ok);*/
}
//-----------------------------------------------------------------------------
//void Form1::setModel(CTlgBaseWrapper::ModelTyp mod)
//{
  //Model=mod;
//  CTlgBaseWrapper::getBaseTlgWrapper(Model);
//}
//-----------------------------------------------------------------------------
void Form1::initComponent()
{
  Splash->SetText("Creating all contol elements ...");
  isSimFormLoaded = false;
  //InterConnectionListe = gcnew CInterConnectionListe(); 
  MessageForm = gcnew CMessageForm();
  MessageForm->Visible = true;
  StatusConnectionForm = nullptr;
  InterfaceProtoArray = gcnew List<CTlgInterfaceWrapper^>();
  //Sender
  SenderForm = gcnew CSenderForm(panViewBackGround);
  CSzenariumForm::UpdateSzenEventTyp^ upSzen = gcnew CSzenariumForm::UpdateSzenEventTyp(this,&Form1::setSzenUpdateModus);
  SenderForm->setSzenUpdateEvent(upSzen);
  CTlgTreeViewForm::LogFileViewEventTyp^ LogFileViewEvent = gcnew  CTlgTreeViewForm::LogFileViewEventTyp(this,&Form1::updateMenuLogFileView);
  SenderForm->setLogFileViewEventTyp(LogFileViewEvent);
  SenderForm->setOpenSenderConnectionDialogTyp(gcnew CSenderForm::OpenSenderConnectionDialogTyp(this,&Form1::OpenSenderConnectionStatusDialog));
  //Receiver
  ReceiverForm = gcnew  CReceiverForm(panViewBackGround);
  ReceiverForm->setMessageForm(MessageForm);
  SenderForm->setMessageForm(MessageForm);
  //Conn Liste
  SendInterConnectionListe = gcnew  CInterConnectionListe();
  SendInterConnectionListe->setDirection("Sender");
  RecInterConnectionListe = gcnew  CInterConnectionListe();
  RecInterConnectionListe->setDirection("Receiver");
  ReceiverForm->setConnListe(RecInterConnectionListe);
  CSzenariumForm::SzenariumModusEventTyp^ szenMod=gcnew CSzenariumForm::SzenariumModusEventTyp(this,&Form1::updateSzenariumMidus);
  SenderForm->setUpdateSzenariumModus(szenMod);
  //´Bof Form
  BofMainForm = gcnew CBofMainForm();
  //BofForm = new CBofForm();
  
  //Variablen initialisieren
  Splash->SetText("Initialized all instances and variables ...");
  TlgContainerSortForm=nullptr;
  RetLogFileReader=0;
  String^ interName=nullptr;
  String^ fileName=nullptr;
  LogFileReadThread=nullptr;
	barView=nullptr;
  ifNewIncfFile = gcnew value struct ifNewIncfFileTyp();
  ifNewIncfFile->newFile = false;
  ifNewIncfFile->path = nullptr;
  ifNewIncfFile->inter = nullptr;
  //Deligate erzeugen, um beim Beenden, alle Threads schliessen.
  CThreadsManager::CloseAppDelTyp^ CloseAppDel = gcnew CThreadsManager::CloseAppDelTyp(this,&Form1::CloseForm);
  CThreadsManager::getThreadsManager(CloseAppDel);
  //Messager in CyclicItemContainer setzen 
  CCyclicItemContainer::getCyclicItemContainer()->setWriteMessageDelTyp
    (gcnew CCyclicItemContainer::WriteMessageDelTyp(this,&Form1::WriteMessage));
  //Groesse der Steuerelementen einstellen
  Splash->SetText("Setting size of contol elements ...");
  setKompPos();
  //Menu - Einstellungen vornehmen
  updateSzenariumMidus(0);
  mainMenu->MenuItems[3]->MenuItems[0]->Checked=true;
  ////Szenarium Modus deaktivieren
  //setSzenUpdateModus(false);
  //Send Modus deaktivieren
  updateSzenariumMidus(0);
  //LogFile Modus deaktivieren
  updateMenuLogFileView(false);
  //BOF Model
  mainMenu->MenuItems[4]->MenuItems[0]->Enabled=false;

  initViewComponent(); 
}
//-----------------------------------------------------------------------------
int Form1::loadInterface(String^ path)
{
  int flag;
  int ret=0;
  String^ interName=nullptr;
  String^ mess = String::Concat("Interface: ",path);
  Splash->SetText(mess);
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                              __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  MessageForm->writeLine(mess,CMessageForm::MessTyp::Info);

  CTlgInterfaceWrapper^ inter = gcnew CTlgInterfaceWrapper();
  //Hilfsvariable, hat in diesem Fall keine Auswirkung auf die unten aufgerufene Methode
	const bool tmp = false;
	flag = inter->loadFromFile(path,tmp);
  
  if(flag == 0)
  {
    interName=inter->getInterfaceName();
    if(!IsInterLoaded(interName))
    {
      int count = inter->getTlgCount();
      mess = String::Concat("     ",System::Convert::ToString(count),"  Telegrams found");
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                              __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      MessageForm->writeLine(mess,CMessageForm::MessTyp::Info);

      //********************
      InterfaceProtoArray->Add(inter);

      //---------------------------------------
      CInterConnection^ interConnectionSend = gcnew CInterConnection(inter->getInterfaceName());
      ConnectionUpdateInterEventTyp^ updateSendConn = gcnew ConnectionUpdateInterEventTyp(this,&Form1::updateConnectionSenderInfo);
      SenderForm->addInterface(inter,interConnectionSend);
      SendInterConnectionListe->addInterface(interConnectionSend);
      SendInterConnectionListe->setConnectionUpdateInterEvent(updateSendConn,inter->getInterfaceName());

      CInterConnection^ interConnectionRec = gcnew CInterConnection(inter->getInterfaceName());
      RecInterConnectionListe->addInterface(interConnectionRec);
      ReceiverForm->addInterface(inter,interConnectionRec);
      // !!!
      ReceiverForm->addInterface(inter);

      ConnectionUpdateInterEventTyp^ updateRecConn = gcnew ConnectionUpdateInterEventTyp(this,&Form1::updateConnectionReceiverInfo);
      RecInterConnectionListe->setConnectionUpdateInterEvent(updateRecConn,inter->getInterfaceName());
      
      interName = inter->getInterfaceName();
      if(interName->Equals("BAS_BOF"))  // to activate bof form for simulation
      {
        if(BofMainForm != nullptr)
        {
          BofMainForm->setTlgInterface(inter);
          BofMainForm->setInterConnectionSenden(interConnectionSend);
          BofMainForm->setInterConnectionReceive(interConnectionRec);
        }
      }
      
      if (isSimFormLoaded)
      {
        CAppSetting^ Sett = CAppSetting::getApp();
        if(Sett->checkInterConfigFile(interName))
        {
          CInterConfigWrapper^ confWr = gcnew CInterConfigWrapper();
          String^ confFilePath = Sett->getInterConfigFilePath(interName);
          confWr->readInterConfigurationFile(interName,confFilePath);
        }
        else
        {  
          String^ confPath = Sett->getWorkingDirectory();
          CXmlInterConfigWriter^ confWriter = gcnew CXmlInterConfigWriter();
          confWriter->createInterConfigFile(inter,confPath);
          Sett->addInterDefaultConfigFile(confPath,interName);
        }
      }
      ret = 0;
    }
    else
    {
      String^ mess=System::String::Concat("The Interface ",interName," is allready loaded" );
      //std::string mesStr("");
      //CStdConverter::StringToStdStr(mess,mesStr);
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,
                                                                  __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      MessageBox::Show(nullptr,mess,"Message",System::Windows::Forms::MessageBoxButtons::OK);
      ret=1;
      //System::Windows::Forms::MessageBox::Show(0,,"Message");
    }
  }
  else
  {
    String^ mess_ = inter->getErrorMessage();
    mess = String::Concat("Error: ",mess_);
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                            __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    MessageForm->writeLine(mess,CMessageForm::MessTyp::Error);
    ret=2;
  }
  return ret;
}
//-----------------------------------------------------------------------------
//void Form1::addInterfaceToSimulator (CTlgInterfaceWrapper* inter)
//{
//  InterfaceProtoArray->Add(inter);
//
//  //---------------------------------------
//  CInterConnection* interConnectionSend = new CInterConnection(inter->getInterfaceName());
//  ConnectionUpdateInterEventTyp* updateSendConn = new ConnectionUpdateInterEventTyp(this,&Form1::updateConnectionSenderInfo);
//  SenderForm->addInterface(inter,interConnectionSend);
//  SendInterConnectionListe->addInterface(interConnectionSend);
//  SendInterConnectionListe->setConnectionUpdateInterEvent(updateSendConn,inter->getInterfaceName());
//
//  CInterConnection* interConnectionRec = new CInterConnection(inter->getInterfaceName());
//  RecInterConnectionListe->addInterface(interConnectionRec);
//  ReceiverForm->addInterface(inter,interConnectionRec);
//  // !!!
//  ReceiverForm->addInterface(inter);
//
//  ConnectionUpdateInterEventTyp* updateRecConn = new ConnectionUpdateInterEventTyp(this,&Form1::updateConnectionReceiverInfo);
//  RecInterConnectionListe->setConnectionUpdateInterEvent(updateRecConn,inter->getInterfaceName());
//  
//  interName = inter->getInterfaceName();
//  if(interName->Equals("BAS_BOF"))  // to activate bof form for simulation
//  {
//    if(BofMainForm != 0)
//    {
//      BofMainForm->setTlgInterface(inter);
//      BofMainForm->setInterConnectionSenden(interConnectionSend);
//      BofMainForm->setInterConnectionReceive(interConnectionRec);
//    }
//  }
//}
////-----------------------------------------------------------------------------
void Form1::treatRecConnection(int index)
{  
   
}
//-----------------------------------------------------------------------------
 void Form1::disSocketConnection()
 {
    SendInterConnectionListe->disConnectAll();
    RecInterConnectionListe->disConnectAll();
 }
//-----------------------------------------------------------------------------
void Form1::setKompPos()
{
  labInter->Left = panHead->Width/3;
  labVersion->Left =  panHead->Width/3;
  labInterfaceName->Left = labInter->Left + labInter->Width;
  labInterfaceName->Width = 400;
  labInterfaceName->Top = labInter->Top;
  labInterfaceName->Height = labInter->Height;
  labVersionInfo->Left = labInter->Left + labInter->Width;
  labVersionInfo->Height = labVersion->Height;
  labVersionInfo->Width = 200;
  labVersionInfo->Top = labVersion->Top;
}
//------------------------------------------------------------------------------
void Form1::updateConnectionSenderInfo(String^ inter)
{
  try
  {
    if (StatusConnectionForm && inter)
      StatusConnectionForm->updateConSendInfoToView(inter);    
  }
  catch(System::Exception^ e)
  {
    MessageForm->writeLine(e->Message,CMessageForm::MessTyp::Error);
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,e->Message,
                                                            __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),7);
  }
  updateConnStatusLabel(inter);
}
//------------------------------------------------------------------------------
void Form1::updateConnectionReceiverInfo(String^ inter)
{
  try
  {
    if (StatusConnectionForm && inter)
      StatusConnectionForm->updateConRecInfoToView(inter);
  }
  catch(System::Exception^ e)
  {
    MessageForm->writeLine(e->Message,CMessageForm::MessTyp::Error);
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,e->Message,
                                                            __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),7);
  }
  
  ReceiverForm->updateConnectionStatus(inter);
  //EMAL
  //MessageForm->writeLine("ssss",CMessageForm::MessTyp::Error);
}
//------------------------------------------------------------------------------
void Form1::changeActiveInterface(String^ inter)
{
  //int index;
  bool flag=false;
  String^ interName=nullptr;
  int i=0;
  int count = mainMenu->MenuItems[0]->MenuItems[1]->MenuItems->Count;
  while((!flag) && (i<count))
  {
    interName=mainMenu->MenuItems[0]->MenuItems[1]->MenuItems[i]->Text;
    if(interName->Equals(inter))
      flag=true;
    else
      i++;
  }

  if(flag)
  {
    mainMenu->MenuItems[0]->MenuItems[1]->MenuItems[i]->PerformClick();
  }
  else
  {
    if(count != 0)
    {
      mainMenu->MenuItems[0]->MenuItems[1]->MenuItems[0]->PerformClick();
    }
  }
}
//------------------------------------------------------------------------------
bool Form1::IsInterLoaded(String^ name)
{
  bool ret = false;
  int count,i;
  CTlgInterfaceWrapper^ mod=nullptr;
  count = InterfaceProtoArray->Count;
  i=0;
  while((i<count) && (!ret))
  {
    mod=safe_cast<CTlgInterfaceWrapper^>(InterfaceProtoArray[i]);
    if(mod->getInterfaceName()->Equals(name))
    {
      ret = true;
    }
    else
    {
      i++;
    }
  }
  return ret;
}
//------------------------------------------------------------------------------
void Form1::updateSzenariumMidus(int modi)
{
  //System::Windows::Forms::Menu::MenuItemCollection^ item = mainMenu->MenuItems[2]->MenuItems;
  //if(modi == 0)
  //{
  //  item[4]->Enabled=false;
  //  item[5]->Enabled=false;
  //}
  //else
  //{
  //  if(modi == 1)
  //  {
  //    item[4]->Enabled=true;
  //    item[5]->Enabled=true;
  //  }
  //}
  SenderForm->enableSzenChangeMode(modi);
}
//------------------------------------------------------------------------------
void Form1::activateSenderMenu()
{
  int count,count1,i,j;
  //Alle aktivieren
  System::Windows::Forms::Menu::MenuItemCollection^ itemCol=nullptr;
  count=mainMenu->MenuItems->Count;
  for(i=0;i<count;i++)
  {
    itemCol=mainMenu->MenuItems[i]->MenuItems;
    count1=itemCol->Count;
    for(j=0;j<count1;j++)
      itemCol[j]->Enabled=true;
  }
  //Log - File Menu
  updateMenuLogFileView(true);
  ////Szenarium Ansicht
  //setSzenUpdateModus(SenderForm->isSzenarioCreated());
  //Send Modus Ansicht
  if (SenderForm->isSendMode())
    updateSzenariumMidus(1);
  else
    updateSzenariumMidus(0);
  //Analyzer
  // emal
  itemCol=mainMenu->MenuItems[1]->MenuItems;
  itemCol[7]->Enabled=true;
  //BOF Model
  itemCol=mainMenu->MenuItems[4]->MenuItems;
  itemCol[0]->Enabled=false;

}
//------------------------------------------------------------------------------
void Form1::activateReceiverMenu()
{
  int i,count;
  //Log File Ansicht
  System::Windows::Forms::Menu::MenuItemCollection^ itemCol=nullptr;
  itemCol=mainMenu->MenuItems[1]->MenuItems;
  count=itemCol->Count;
  for(i=0;i<count;i++)
    itemCol[i]->Enabled=false;
  //Szenario Ansicht
  itemCol=mainMenu->MenuItems[2]->MenuItems;
  count=itemCol->Count;
  for(i=0;i<count;i++)
    itemCol[i]->Enabled=false;
  //Cyclic Tlg Ansicht
  itemCol=mainMenu->MenuItems[5]->MenuItems;
  count=itemCol->Count;
  for(i=0;i<count;i++)
    itemCol[i]->Enabled=false;
  // emal
  itemCol=mainMenu->MenuItems[1]->MenuItems;
  itemCol[7]->Enabled=true;
}
//------------------------------------------------------------------------------
void Form1::setFilterLogFile(array <String^>^ reg)
{
  SenderForm->setFilterLogFile(reg);
}
//------------------------------------------------------------------------------
CTlgInterfaceWrapper^ Form1::getActiveInterfaceWrapper()
{
  CTlgInterfaceWrapper^ ret=nullptr;
  CTlgInterfaceWrapper^ temp=nullptr;
  int count,i;
  bool flag=false;
  //CTlgInterfaceWrapper^
  count=InterfaceProtoArray->Count;
  i=0;
  while((i<count) && (!flag))
  {
    temp = safe_cast<CTlgInterfaceWrapper^>(InterfaceProtoArray[i]);
    if(Interface->Equals(temp->getInterfaceName()))
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
//------------------------------------------------------------------------------
void Form1::findInLogFile(int pos)
{
  if(pos != 0)
  {
    SenderForm->selectLogFileTelegram(pos);  
  }
}
//------------------------------------------------------------------------------
void Form1::findInSzenarium(int pos)
{
  if(pos != 0)
  {
    SenderForm->selectSzenariumTelegram(pos);
  }
}
//------------------------------------------------------------------------------
void Form1::sortedLogFileView()
{
  SenderForm->showLogTlg(Interface);
}
//------------------------------------------------------------------------------
void Form1::setSzenUpdateModus(bool flag)
{
  //System::Windows::Forms::Menu::MenuItemCollection^ col=nullptr;
  //col=mainMenu->MenuItems[2]->MenuItems;
  //col[1]->Enabled=flag;
  //col[2]->Enabled=flag;
  //col[3]->Enabled=flag;
  //col[6]->Enabled=flag;
}
//------------------------------------------------------------------------------
void Form1::updateMenuLogFileView(bool flag)
{
  //bool flagLogFile=false;
  //if(Interface)
  //  flagLogFile=SenderForm->isLogFileLoad(Interface);

  //flagLogFile=flagLogFile && flag;

  //System::Windows::Forms::Menu::MenuItemCollection^ col = mainMenu->MenuItems[1]->MenuItems;
  //for(int i=1;i<=6;i++)
  //{
  //  col[i]->Enabled=flagLogFile;
  //}
}
//------------------------------------------------------------------------------
void Form1::updateConnStatusLabel(String^ inter)
{
  int index=0;
  index = SendInterConnectionListe->getInterNummber(inter);
  if (SendInterConnectionListe->isConnected(index))
    SenderForm->setLabConnStatus(2);
  else if (SendInterConnectionListe->isWaiting(index))
    SenderForm->setLabConnStatus(1);
  else
    SenderForm->setLabConnStatus(0);
}

//------------------------------------------------------------------------------
void Form1::logFileReadThread()
{
  bool ok = true;
  AbortLogFileReaderThread = false;
	try
	{
		/*CMessageWriter* MessageWriter = gcnew CMessageWriter(MessageForm); 
		MessageForm->writeLine(String::Concat("Load Log File: ",fileName),CMessageForm::MessTyp::Info);
		MessageForm->setActionName("Load Log File");*/
	  
		LogFileReadThread->Sleep(100);
		
    RetLogFileReader=SenderForm->loadLogFile(fileName,interName,AbortLogFileReaderThread);
	  
		// ProgressForm zum Beenden zwingen
		do
		{
			if (System::Threading::Monitor::TryEnter(barView))
			{
				barView->Close();
				System::Threading::Monitor::Exit(barView);
				ok = false;
			}
			else
				LogFileReadThread->Sleep(100);
		}
		while (ok);
	}
	catch (System::Threading::ThreadAbortException^ e)
	{
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,e->Message,
                                                            __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
		RetLogFileReader = -1;
    LogFileReadThread->ResetAbort();
		if (barView)
			barView->Close();
	}
}
//------------------------------------------------------------------------------
String^ Form1::getInterfaceNameFromXmlFile(String^ path)
{
  System::Xml::XmlDocument^ XmlDoc;
  System::Xml::XmlElement^ elem = nullptr;
  System::Xml::XmlAttributeCollection^ attrCol = nullptr;
  String^ ret = nullptr;
  
  XmlDoc = gcnew System::Xml::XmlDocument();
  XmlDoc->PreserveWhitespace = (false);
  XmlDoc->Load(path);
 
  elem = XmlDoc->DocumentElement;
  attrCol = elem->Attributes;
  
  ret = attrCol["name"]->Value;
  
  return ret; 
}
//------------------------------------------------------------------------------
bool Form1::setIncfFile(String^ path)
{
  bool ret = true;
  String^ interName = nullptr;
  interName = getInterfaceNameFromXmlFile (path); 
  CAppSetting^ Sett = CAppSetting::getApp();
      
  if(Sett->checkInterConfigFile(interName))
  {
    CInterConfigWrapper^ confWr = gcnew CInterConfigWrapper();
    String^ confFilePath = Sett->getInterConfigFilePath(interName);
    confWr->readInterConfigurationFile(interName,confFilePath);
  }
  else
  {  
    String^ confPath = Sett->getWorkingDirectory();
    CXmlInterConfigWriter^ confWriter = gcnew CXmlInterConfigWriter();
        //-------------------
    System::IO::FileInfo^ fileInfo = gcnew System::IO::FileInfo(System::String::Concat(confPath,"\\",interName,".icnf")); 
    //Wenn die Datei schon existiert
    if (fileInfo->Exists)
    {
      CInfoForm^ form = gcnew CInfoForm();
      String^ Mes = "The configuration file for interface '";
      Mes = String::Concat(Mes,interName, "' already exists.\n");
      Mes = String::Concat(Mes,"To load settings from it choose Yes.\n");
      Mes = String::Concat(Mes,"To create new configuration file choose No.\n");
      form->setMessage(Mes);
      form->ShowDialog();
      if(form->getAnswer())
      {
        Sett->addInterDefaultConfigFile(confPath,interName);
        ifNewIncfFile->newFile = false;
      }
      else
      {
        //----------Safe Dialog -------------
        SaveFileDialog^ saveConfFile = gcnew SaveFileDialog();
        //String^ path=^;
        String^ directory=nullptr;
        saveConfFile->Reset();
        String^ confFilename=nullptr;
        directory = Sett->getWorkingDirectory();
        
        if(directory)
        {
          saveConfFile->InitialDirectory = (directory);
        }
        saveConfFile->Filter = ("Interface Configuration File(*.icnf)|*.icnf");
        saveConfFile->DefaultExt = ("icnf");
        saveConfFile->AddExtension = (false);
        
        if(saveConfFile->ShowDialog() == ::DialogResult::OK)
        {
          ::Cursor::Current = ::Cursors::WaitCursor;
          confPath=saveConfFile->FileName;
          if(confPath != nullptr)
          {
            if (confPath->IndexOf(".icnf")==-1)
              confPath=confPath->Concat(confPath,".icnf");
            
            ifNewIncfFile->newFile = true;
            ifNewIncfFile->path = confPath;
            ifNewIncfFile->inter = interName;
            /*confWriter->createInterConfigFile(inter,confPath);*/
            Sett->addInterDefaultConfigFile(confPath,interName);
          }
        }
        else
        {
          ret = false;
          ifNewIncfFile->newFile = false;
          String^ mess = "The interface file was not loaded!";
          CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,
                                                                  __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
          Windows::Forms::MessageBox::Show(mess,"",MessageBoxButtons::OK,MessageBoxIcon::Warning);   
        }
      }
    }
      else
      {
        ifNewIncfFile->newFile = true;
        ifNewIncfFile->path = confPath;
        ifNewIncfFile->inter = interName;
        /*confWriter->createInterConfigFile(inter,confPath);*/
        Sett->addInterDefaultConfigFile(confPath,interName);
      }
  }
  return ret;
}
//------------------------------------------------------------------------------
void Form1::AbortLogFileReadThread()
{
	//Thread Log File auslesen, beenden.
   AbortLogFileReaderThread = true;
  // 
  //LogFileReadThread->Abort();
	/*LogFileReadThread->ResetAbort();*/
  //ProgressBar schliessen
  /*barView->Close();*/
   
  //Alle schon geladene LogFiles entfernen
  //SenderForm->clearLogFile(interName);
	//ProgressBar schliessen
  //barView->Close();
}
//------------------------------------------------------------------------------
void Form1::CloseForm()
{
  ReceiverForm->closeAnazyzeForm();
  //Letzte aktive Interfache merken
  CAppSetting^ Sett = CAppSetting::getApp();
  if (Sett)
  {
    CTlgInterfaceWrapper^ temp = this->getActiveInterfaceWrapper();
    if (temp)
    {
      Sett->setLastActivInterfaceName(temp->getInterfaceName());
    }
  }
  //Senden zyklischer Telegramme beenden, falls aktiv
  CCyclicItemContainer::getCyclicItemContainer()->StopAll();
  //Szenario beenden, falls aktiv
  SenderForm->stopSendSzenarium(true);
  //Alle Connection schliessen
  disSocketConnection();
  //Szenario, falls modifiziert, abfragen
  SenderForm->updateSzenFile();
}
//-------------------------------------------------------------------------------
void Form1::WriteMessage(String^ mes,int typ)
{
  CMessageForm::MessTyp messType;
  if(typ == 0 || typ == 3)
    messType=CMessageForm::MessTyp::Info;
  if(typ == 1)
    messType=CMessageForm::MessTyp::Warning;
  if(typ == 2)
    messType=CMessageForm::MessTyp::Error;
  
  MessageForm->writeLine(mes,messType);
}
//-------------------------------------------------------------------------------
System::Void Form1::CreateSzenarioWithConditions_Click(System::Object^  sender, System::EventArgs^  e) 
{
  SenderForm->OpenAutoCreateSzenarioForm(this->InterfaceProtoArray);
}
//-------------------------------------------------------------------------------
System::Void Form1::menuSzenarium_Select(System::Object^  sender, System::EventArgs^  e) 
{                      
  System::Windows::Forms::Menu::MenuItemCollection^ col=nullptr;
  col=mainMenu->MenuItems[2]->MenuItems;
  
  //Wenn keine Interface geladen wurde
  if (this->InterfaceProtoArray->Count == 0)
  {
    for (int i=0;i<col->Count;i++) //Alle Felder mit False initialisieren
      col[i]->Enabled = false; 
      return;
  }
  
  //Wenn Receiver Ansicht aktiviert ist
  if (mainMenu->MenuItems[3]->MenuItems[1]->Checked)
  {
    for (int i=0;i<col->Count;i++) //Alle Felder mit False initialisieren
      col[i]->Enabled = false; 
      return;
  }
                          

   bool flag = this->SenderForm->isSendMode();
   //Alle Felder ausser dem letzten mit False/True initialisieren
   for (int i=0;i<col->Count-1;i++)
      col[i]->Enabled = !flag;

   //Options 
   menuItem8->Enabled = true;
     
   //Falls Send-Modus /false
   if (flag)
   {
     //Stop  //Send
     if (this->SenderForm->isSzenarioSending())
     {
       col[5]->Enabled = true;
       //Options
       menuItem8->Enabled = false;
     }
     else if (this->SenderForm->isSzenarioCreated())
       col[4]->Enabled = true;

     //Close Szenario
     col[6]->Enabled = false;
   }
   else
   {
     //Stop  //Send
     col[5]->Enabled = false;
     col[4]->Enabled = false;
     //Close Szenario
     if (this->SenderForm->isSzenarioCreated())
       col[6]->Enabled = true;
     else
       col[6]->Enabled = false;
   }
}
//-------------------------------------------------------------------------------
System::Void Form1::MenuCyclicTelegrams_Select(System::Object^  sender, System::EventArgs^  e) 
{
  System::Windows::Forms::Menu::MenuItemCollection^ col=nullptr;
  col=mainMenu->MenuItems[5]->MenuItems;
  
  //Wenn keine Interface geladen wurde
  if (this->InterfaceProtoArray->Count == 0)
  {
    for (int i=0;i<col->Count;i++) //Alle Felder mit False initialisieren
      col[i]->Enabled = false; 
      return;
  }
  
  //Wenn Receiver Ansicht aktiviert ist
  if (mainMenu->MenuItems[3]->MenuItems[1]->Checked)
  {
    for (int i=0;i<col->Count;i++) //Alle Felder mit False initialisieren
      col[i]->Enabled = false; 
      return;
  }

  //Configuration
  this->MenuCyclicShow->Enabled = !this->SenderForm->isSendMode();
  //Send
  this->MenuCyclicSend->Enabled = this->SenderForm->isSendMode();
  //Stop
  this->MenuCyclicStop->Enabled = this->SenderForm->isSendMode();    
}
//-------------------------------------------------------------------------------
System::Void Form1::MenuLogFile_Select(System::Object^  sender, System::EventArgs^  e) 
{
  System::Windows::Forms::Menu::MenuItemCollection^ col=nullptr;
  col=mainMenu->MenuItems[1]->MenuItems;
  
  //Wenn keine Interface geladen wurde
  if (this->InterfaceProtoArray->Count == 0 || ActInterface < 0)
  {
    for (int i=0;i<col->Count;i++) //Alle Felder mit False initialisieren
      col[i]->Enabled = false; 
      return;
  }

  //Wenn Receiver Ansicht aktiviert ist
  if (mainMenu->MenuItems[1]->MenuItems[1]->Checked)
  {
    for (int i=0;i<col->Count-1;i++) //Alle Felder mit False initialisieren
      col[i]->Enabled = false; 
      return;
  }
  //Analyzer
  col[col->Count-1]->Enabled = true;

  bool flag = this->SenderForm->isLogFileLoad(InterfaceProtoArray[ActInterface]->getInterfaceName());
  for (int i = 1; i<col->Count-1; i++)
    col[i]->Enabled = flag;
}
//--------------------------------------------------------------------------------
System::Void Form1::menuItemCorbaViewer_Click(System::Object^  sender, System::EventArgs^  e) 
{
  CCorbaViewerForm^ CorbaViewer = gcnew CCorbaViewerForm();
  CorbaViewer->Show();
}