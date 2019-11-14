#include "StdAfx.h"
#include "CCorbaViewerForm.h"

using namespace simulator;
using namespace System;

//---------------------------------------------------------------
void CCorbaViewerForm::init()
{
  this->Size = System::Drawing::Size(1280,800); 
  
  CCorbaIdlWrapper^ CorbaIdl = gcnew CCorbaIdlWrapper();
  LogWriter = CLogWriterWrapper::getLogWriterWrapper();
  
  if (CorbaIdl->getInterfaceNames() == nullptr || CorbaIdl->getContext() == nullptr)
  {
    String^ mess="";
    if (CorbaIdl->getInterfaceNames() == nullptr)
      mess = "No corba interfaces in <simulator.ini> defined.";
    if (CorbaIdl->getContext() == nullptr)
      mess += "\nNo corba context in <simulator.ini> defined.";

    System::Windows::Forms::MessageBox::Show(nullptr,mess,
                                    "",
                                    MessageBoxButtons::OK,
                                    MessageBoxIcon::Error);

    LogWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  }
  else
  {
    AddInterfaceButtons(CorbaIdl->getInterfaceNames());
  }
  
  LastGreenTopButton = nullptr;
  SelectedInterfaceName = nullptr;
  //
  DetailView = gcnew SimGuiDialogs::CCorbaTypeOfNameView();
  DetailView->Dock = System::Windows::Forms::DockStyle::Fill;
  //this->panMiddleView->Controls->Clear();
  this->panMiddleView->Controls->Add(DetailView);
}
//---------------------------------------------------------------
void CCorbaViewerForm::AddInterfaceButtons (array<String^>^ names)
{
    if (names == nullptr)
      return;
    
    Windows::Forms::Button^ butTmp = nullptr;
    for (int i=0;i<names->Length;i++)
    {
      //Neues Button erzeugen
      butTmp = gcnew System::Windows::Forms::Button();
      butTmp->Size = System::Drawing::Size(150, 35);
      butTmp->Name = names[i];
      
      if (names[i]->IndexOf(".CORBA_Object") > 0)
        butTmp->Text = names[i]->Substring(0,(names[i]->IndexOf(".CORBA_Object")));
      else
        butTmp->Text = names[i];
        
      butTmp->Dock = System::Windows::Forms::DockStyle::Left;
      butTmp->Margin = System::Windows::Forms::Padding(10);
      butTmp->Click += gcnew System::EventHandler(this, &CCorbaViewerForm::Buttons_Click);
      panTopView->Controls->Add(butTmp);
    }
    //gcnew array<String^>
}
//----------------------------------------------------------------
System::Void CCorbaViewerForm::Buttons_Click(System::Object^  sender, System::EventArgs^  e) 
{
   ::Cursor::Current = ::Cursors::WaitCursor;
   if (this->LastGreenTopButton != nullptr)
     this->LastGreenTopButton->ResetBackColor();

   Windows::Forms::Button^ tmp = (Windows::Forms::Button^) sender;
   if (this->CorbaIdl->connect(tmp->Name))
   {
      tmp->BackColor = Drawing::Color::LightGreen;
      SelectedInterfaceName = tmp->Name;
      this->addKeys(tmp->Name);  
   }
   else
   {
      tmp->BackColor = Drawing::Color::Red;
      SelectedInterfaceName = nullptr;
      this->trKeysView->Nodes->Clear();
      this->trNamesView->Nodes->Clear();
      this->DetailView->Clear();
   }
   this->LastGreenTopButton = tmp;
   ::Cursor::Current = ::Cursors::Default;
}
//-----------------------------------------------------------------
void CCorbaViewerForm::addKeys(String^ InterfaceName)
{
  array <String^>^ tmp = this->CorbaIdl->getKeys(InterfaceName);
  this->trKeysView->Nodes->Clear();
  this->trNamesView->Nodes->Clear();
  this->DetailView->Clear();
  if (tmp != nullptr)
    for (int i=0;i<tmp->Length;i++)
      this->trKeysView->Nodes->Add(tmp[i]);
}
//-----------------------------------------------------------------
void CCorbaViewerForm::addNames(String^ InterfaceName,String^ key)
{
  if (this->SelectedInterfaceName == nullptr || key == nullptr)
    return;

  array <String^>^ tmp = this->CorbaIdl->getNames(InterfaceName,key);
  this->trNamesView->Nodes->Clear();
  this->DetailView->Clear();
  if (tmp != nullptr)
    for(int i=0;i<tmp->Length;i++)
      this->trNamesView->Nodes->Add(tmp[i]);
}
//-----------------------------------------------------------------
System::Void CCorbaViewerForm::butClose_Click(System::Object^  sender, System::EventArgs^  e) 
{
  this->Close();
}
//-----------------------------------------------------------------
System::Void CCorbaViewerForm::trKeysView_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) 
{
  ::Cursor::Current = ::Cursors::WaitCursor;
  String^ tmp = this->trKeysView->SelectedNode->Text;
  this->addNames(this->SelectedInterfaceName,tmp);
  ::Cursor::Current = ::Cursors::Default;
}
//-----------------------------------------------------------------
System::Void CCorbaViewerForm::trNamesView_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) 
{
  ::Cursor::Current = ::Cursors::WaitCursor;
  setDetailView();
  ::Cursor::Current = ::Cursors::Default;
}
//-----------------------------------------------------------------
void CCorbaViewerForm::setDetailView()
{
  String^ key = this->trKeysView->SelectedNode->Text;
  String^ name = this->trNamesView->SelectedNode->Text;

  if (this->SelectedInterfaceName == nullptr || key == nullptr || name == nullptr)
    return;

  this->DetailView->Clear();

  //Value anzeigen
  System::Text::StringBuilder^ tmp = this->CorbaIdl->getValue(SelectedInterfaceName,key,name);
  //Datentyp anzeigen
  this->DetailView->setValues(this->CorbaIdl->getDataType(SelectedInterfaceName,key,name),tmp->ToString());
}