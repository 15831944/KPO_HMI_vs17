#include "StdAfx.h"
#include "CAutoCreateSzenarioForm.h"
#include "CAppSetting.h"
#include "CTlgLogFileReaderWrapper.h"
#include "CLogWriterWrapper.h"
#include "CProgressBarViewForm.h"
#include "CProgressBarStatusWriter.h"

using namespace System::Threading;
using namespace simulator;

bool AbortLogInAutoCreatingFileReaderThread = false;
//---------------------------------------------------------------------------------
void CAutoCreateSzenarioForm::initToolTips()
{
  //Apply Button
  Windows::Forms::ToolTip^ tmp =gcnew Windows::Forms::ToolTip();
  String^ mess = "Scenario is generated automatically by specified criteria. This dialog is not closed.";
  tmp->SetToolTip(this->butApply,mess);
  //Close Button
  tmp =gcnew Windows::Forms::ToolTip();
  mess = "This dialog is closed.\nAll configurations will be lost.";
  tmp->SetToolTip(this->butCancel,mess);
  //Log-Files Auswahl Combo-Box
  tmp =gcnew Windows::Forms::ToolTip();
  mess = "Here are all loaded log files.";
  tmp->SetToolTip(this->cmbSourceBox,mess);
  //Combo-Box Reg. Ausdruecke und Positions
  tmp =gcnew Windows::Forms::ToolTip();
  mess = "The following types of criteria can be selected.";
  mess += "\nTelegrams can be filtered using regular expressions.";
  mess += "\nSecond chance offers, telegrams to filter on their position in the container.";
  tmp->SetToolTip(this->cmbCondTypBox,mess);
}
//---------------------------------------------------------------------------------
void CAutoCreateSzenarioForm::init()
{
  logWriter = CLogWriterWrapper::getLogWriterWrapper();
  //Source Box initialisieren
  this->cmbSourceBox->Items->Add("Choose new log file ...");
  this->ActiveInterface = nullptr;
  
  //Interface Name
  for (int i=0;i<this->LogFileContainer->Count;i++)
  {
    if (LogFileContainer[i]->getTlgCount() == 0)
      this->cmbSourceBox->Items->Add("Loaded log file < ... >");
    else
      this->cmbSourceBox->Items->Add("Loaded log file < " + LogFileContainer[i]->getTlg(1)->getInterfece() + " >");
  }
  //Change Event 
  this->cmbSourceBox->SelectedIndexChanged += gcnew System::EventHandler(this, &CAutoCreateSzenarioForm::cmbSourceBox_SelectedIndexChanged);
  //Select first item
  this->cmbSourceBox->SelectedItem = this->cmbSourceBox->Items[0];
  //
  this->mPositionCondForm = gcnew SimGuiDialogs::CPositionCondForm(this->panCondFillView);
  this->mMultiFilterForm = gcnew SimGuiDialogs::CMultiFilterForm(this->panCondFillView,nullptr);
  //this->mPositionCondForm->Hide();
  //this->mMultiFilterForm->Hide();
  this->mPositionCondForm->Dock = System::Windows::Forms::DockStyle::None;
  this->mMultiFilterForm->Dock = System::Windows::Forms::DockStyle::None;
  //Tooltips
  initToolTips();
}
//---------------------------------------------------------------------------------
void CAutoCreateSzenarioForm::WriteLogFileInfo(CItemBaseContainerWrapper^ logFile)
{
  if (logFile == nullptr)
  {
    labCountOfTlgsValue->Text = "";
    labInterInfoValue->Text = "";
    return;
  }
  //Anzahl der Telegramme
  labCountOfTlgsValue->Text = Convert::ToString(logFile->getTlgCount());
  //Interface Name
  if (logFile->getTlgCount() == 0)
  {
    labInterInfoValue->Text = "";
    return;
  }
  labInterInfoValue->Text = logFile->getTlg(1)->getInterfece();
}
//---------------------------------------------------------------------------------
void CAutoCreateSzenarioForm::OpenLogFile()
{
  CAppSetting^ Sett = CAppSetting::getApp();
  String^ directory = nullptr;
  bool ok = false;
  ::Cursor::Current = ::Cursors::WaitCursor;

  // Open-Dailog starten
  OpenFileDialog^ OpenLogFile = gcnew OpenFileDialog();
  System::String^ fileName;
  OpenLogFile->Title = "Open LogFile";
  OpenLogFile->Filter="Log File(*.log)|*.log";

  directory = Sett->getLogFileDirectory();
  if(directory)
  {
    OpenLogFile->InitialDirectory = (directory);
  }

  //Wenn im Open Dialog der Button ok gedruckt wurde.
  if(OpenLogFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
  {
    if((fileName=OpenLogFile->FileName) != nullptr)
    {
      LogFileReader=gcnew CTlgLogFileReaderWrapper();
      CTlgInterfaceWrapper^ inter = nullptr;
      //Testen, ob fuer Log-File eine Schnittstelle geladen ist
      for (int index=0;index<InterfaceContainer->Count;index++)
      {
        inter = InterfaceContainer[index];
        LogFileReader->setTlgProtoTyp(inter->getTlgProtoTypSet());
        if (LogFileReader->checkInterface(fileName))
        {
          ok=true;
          this->ActiveInterface = inter;
          break;
        }
      }
      if (ok)
      {
        Thread^ LogFileReadThread = nullptr;
        barView = gcnew CProgressBarViewForm();
        CProgressBarStatusWriter^ ProgressWriter = gcnew CProgressBarStatusWriter(barView);
        //--------Datei Groesse ermitteln -------
        System::IO::FileInfo^ file = gcnew System::IO::FileInfo(fileName);
        //File Groesse an ProgressBar ubergeben
        barView->setMinAndMax(0,file->Length);
        barView->setSourceLab(fileName);
        barView->setCancelButtonVisible(true);
        CProgressBarViewForm::BarViewAbortDelTyp^ barViewAbort = gcnew CProgressBarViewForm::BarViewAbortDelTyp(this,&CAutoCreateSzenarioForm::AbortLogFileReadThread); 
        barView->setBarViewAbortDelTyp(barViewAbort);
        //Thread fuer LogFileReader
        LogFileReadThread= gcnew Thread( gcnew ParameterizedThreadStart(this,&CAutoCreateSzenarioForm::LoadLogFileInThread));
        LogFileReadThread->Start(fileName);
        //Aktualisiert PrograssBarView
        ProgressWriter->startWrite();
        //BarView als Modal anzeigen
        if (!barView->isFormClosed())
          barView->ShowDialog();
        //Beenden
        ProgressWriter->endWrite(); 
        barView = nullptr;
        LogFileReader = nullptr;

        if (!AbortLogInAutoCreatingFileReaderThread)
        {
          this->cmbSourceBox->Items->Add(fileName);
          this->cmbSourceBox->SelectedItem = this->cmbSourceBox->Items[(this->cmbSourceBox->Items->Count - 1)];
        }
      
        //Pfad des Verzeichnisses merken
        int pos=fileName->LastIndexOf("\\");
        if(pos != -1)
        {
          directory = fileName->Substring(0,pos);
          Sett->setLogFileDirectory(directory);
        }
      
      }
      else
      {
        String^ mess = "No interface for this log-file is loaded.";
        logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                            __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        System::Windows::Forms::MessageBox::Show(nullptr,mess,
                                        "",
                                        MessageBoxButtons::OK,
                                        MessageBoxIcon::Error);
      }
    }
  }
  ::Cursor::Current = ::Cursors::Default;
}
//------------------------------------------------------------------------------
void CAutoCreateSzenarioForm::AbortLogFileReadThread()
{
	//Thread Log File auslesen, beenden.
	 AbortLogInAutoCreatingFileReaderThread = true;
}
//--------------------------------------------------------------------------
void CAutoCreateSzenarioForm::LoadLogFileInThread (Object^ path)
{
  try
  {
    AbortLogInAutoCreatingFileReaderThread = false;
    LogFileReader->loadFromFile((String^)path,AbortLogInAutoCreatingFileReaderThread);
    if (!AbortLogInAutoCreatingFileReaderThread)
      this->LogFileContainer->Add(LogFileReader);
    barView->Close();
  }
  catch (Exception^ ex)
  {
                      logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,ex->Message,
                                              __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);

  }
}

//--------------------------------------------------------------------------
System::Void CAutoCreateSzenarioForm::cmbSourceBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
{
   int selectedIndex = this->cmbSourceBox->SelectedIndex;
   if (selectedIndex == 0)
   {
      WriteLogFileInfo(nullptr);
      butLoadLogFile->Enabled = true;
      ActiveInterface = nullptr;
      this->cmbCondTypBox->Enabled = false;
      return;
   }

   //if (ActiveInterface == nullptr)
     ActiveInterface = this->DetectInterface(this->LogFileContainer[selectedIndex - 1]);
   
   if (ActiveInterface == nullptr || !ActiveInterface->getInterfaceName()->Equals(labInterInfoValue->Text))
   {
     this->mMultiFilterForm->Clear();
     this->mPositionCondForm->Clear();
   }
  
   WriteLogFileInfo(this->LogFileContainer[selectedIndex - 1]); 
   if (this->LogFileContainer[selectedIndex-1]->getTlgCount() >= 0)
   {
     butLoadLogFile->Enabled = false;
     this->cmbCondTypBox->Enabled = true;
     cmbCondTypBox_SelectedIndexChanged(nullptr,nullptr);
   }
   else
   {
      butLoadLogFile->Enabled = false;
      this->cmbCondTypBox->Enabled = false;
   }
}
//---------------------------------------------------------------------------
System::Void CAutoCreateSzenarioForm::butLoadLogFile_Click(System::Object^  sender, System::EventArgs^  e) 
{
  int selectedIndex = this->cmbSourceBox->SelectedIndex;
  
  if (selectedIndex == 0)
  {
    OpenLogFile();
    return;
  }
}
System::Void CAutoCreateSzenarioForm::butCancel_Click(System::Object^  sender, System::EventArgs^  e) 
{
  this->Close();
}
//----------------------------------------------------------------------------
System::Void CAutoCreateSzenarioForm::butApply_Click(System::Object^  sender, System::EventArgs^  e) 
{  
 int selectedIndex = this->cmbSourceBox->SelectedIndex;
 if (selectedIndex > 0 && this->CloseSzenDel != nullptr && this->AddToSzenDel != nullptr)
 {
   CItemWrapper^ item = nullptr;
   CTlgLogFileReaderWrapper^ tmp = (CTlgLogFileReaderWrapper^)this->LogFileContainer[selectedIndex-1];
   
   //Kriterien an Log File Container anwenden
   ::Cursor::Current = ::Cursors::WaitCursor;
   if (this->cmbCondTypBox->SelectedIndex == 0)
   {
     tmp->setFilterByRegExp(mMultiFilterForm->getRegExAsString());
   }
   else
   {
     List<int>^ tmpList = mPositionCondForm->getPositions();
     if (tmpList->Count > 0)
       tmp->setFilterByPositions(tmpList);
     else //Falls keine Tellegramme, dann nichts ausfuehren
     {
       String^ mess = gcnew String("No telegrams in log-file for configuration of this criteria.");
                System::Windows::Forms::MessageBox::Show(nullptr,mess,
                                        "",
                                        MessageBoxButtons::OK,
                                        MessageBoxIcon::Warning);
       return;
     }

   }
   ::Cursor::Current = ::Cursors::Default;
   
   //Szenario schliessen, falls  gewuescht
   if (radNewSzenarioBut->Checked)
      CloseSzenDel->Invoke();

    //Progress Bar 
    CProgressBarViewForm^ progressBar = gcnew CProgressBarViewForm(); 
    progressBar->setMinAndMax(0,tmp->getVirtualTlgCount());    
    if (radExistedSzenarioBut->Checked)
      progressBar->setSourceLab("Adding Telegrams to existed szenario ...");
    else
      progressBar->setSourceLab("Adding Telegrams to new szenario ...");
    progressBar->Show();

   for (int i=1;i<=tmp->getVirtualTlgCount();i++)
   {
     item = gcnew CTlgWrapper();
     tmp->getClonedVirtualTlg(item,i);
     progressBar->updateStep(1);
     AddToSzenDel->Invoke(item,tmp->getVirtualTlgTime(i),false);        
   }
   progressBar->Close();
   //this->Close();
 }
}
//----------------------------------------------------------------------------
System::Void CAutoCreateSzenarioForm::cmbCondTypBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
{
  if (this->cmbCondTypBox->SelectedIndex == 0)
  {
    ::Cursor::Current = ::Cursors::WaitCursor;
    mPositionCondForm->Hide();
    mPositionCondForm->Dock = System::Windows::Forms::DockStyle::None;
    mMultiFilterForm->Dock = System::Windows::Forms::DockStyle::Fill;
    mMultiFilterForm->Show();
    ::Cursor::Current = ::Cursors::Default;
    return;
  }
  if (this->cmbCondTypBox->SelectedIndex == 1)
  {
    ::Cursor::Current = ::Cursors::WaitCursor;
    mMultiFilterForm->Hide();
    mMultiFilterForm->Dock = System::Windows::Forms::DockStyle::None;
    mPositionCondForm->Dock = System::Windows::Forms::DockStyle::Fill;
    array <String^>^ tmpInterTlgs = gcnew array<String^>(ActiveInterface->getTlgCount());
    
    CItemWrapper^ item = gcnew CTlgWrapper();
    for (int i = 1;i<=ActiveInterface->getTlgCount();i++)
    {
      ActiveInterface->getClonedVirtualTlg(item,i);
      tmpInterTlgs[i-1]=item->getName();
    }
    

    if (this->cmbSourceBox->SelectedIndex > 0)
    {
      CItemWrapper^ item = nullptr;
      CTlgLogFileReaderWrapper^ tmp = (CTlgLogFileReaderWrapper^)this->LogFileContainer[this->cmbSourceBox->SelectedIndex-1];


      Dictionary<String^, List<int>^>^ dicPosNames = gcnew Dictionary<String^,  List<int>^>();

      item = gcnew CTlgWrapper();
      for (int i=1;i<=tmp->getVirtualTlgCount();i++)
      { 
        tmp->getClonedVirtualTlg(item,i);
         if (!dicPosNames->ContainsKey(item->getName()))
           dicPosNames->Add(item->getName(),gcnew List<int>());

         dicPosNames[item->getName()]->Add(i);
      }

      mPositionCondForm->setTlgNames(tmpInterTlgs,dicPosNames);
      mPositionCondForm->Show();
    }

    ::Cursor::Current = ::Cursors::Default;
    return;
  }
  if (this->cmbCondTypBox->SelectedIndex < 0)
  {
    mPositionCondForm->Hide();
    mMultiFilterForm->Hide();
  }
}
//----------------------------------------------------------------------
CTlgInterfaceWrapper^ CAutoCreateSzenarioForm::DetectInterface(CItemBaseContainerWrapper^ con)
{
  if (con == nullptr || con->getVirtualTlgCount() == 0)
    return nullptr;

  CItemWrapper^ tlg = gcnew CTlgWrapper();
  ((CTlgLogFileReaderWrapper^)con)->getClonedVirtualTlg(tlg,1);
  String^ inter = tlg->getInterfece();

  for (int i=0;i<this->InterfaceContainer->Count;i++)
    if (InterfaceContainer[i]->getInterfaceName()->Equals(inter))
      return this->ActiveInterface = InterfaceContainer[i];

  return nullptr;
}