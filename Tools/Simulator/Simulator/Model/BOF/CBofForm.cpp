#include "stdAfx.h"
#include "CBofForm.h"

//------------------------------CBofForm.cpp-----------------------------------------
//Zweck:CBofForm.cpp Class implementiert die Methode in CBofForm.h.um den Telegramm 
//      "Bof211" zu senden.

//-------------------------------------------------------------------------------------
using namespace simulator;
//-------------------------------------------------------------------------------------

void CBofForm::initviewComponent(){
  this->BofProzessForm = gcnew CBofProzessForm(this->BofProzesspanel);
  SelectProzessEvent^ event = gcnew SelectProzessEvent(this,&CBofForm::updateTlgView);
  this->BofProzessForm->setProzessEvent(event);

  this->BofTlgViewForm = gcnew CBofTlgViewForm(this->BofTlgViewpanel);

  this->BofAnimationForm = gcnew CBofAnimationForm(this->BofAnimationpanel);
}


//--------------setter und getter Methode-----------------
//...set und get Interface des Telegramm
Void CBofForm::setTlgInterface(CTlgInterfaceWrapper ^W){
  C_Wr = W;
}
CTlgInterfaceWrapper^ CBofForm::getTlgInterface(){
  return C_Wr;
}

//...set und get InterConnection als Receiver
System::Void CBofForm::setInterConnectionReceive(CInterConnection ^R){
 C_Receiver = R;
}
CInterConnection^ CBofForm::getInterConnectionReceive(){
 return C_Receiver;
}

//...set und get InterConnection als Sender
System::Void CBofForm::setInterConnectionSenden(CInterConnection ^I){
 C_Sender = I;
}
CInterConnection^ CBofForm::getInterConnectionSenden(){
  return C_Sender;
}

System::Void CBofForm::OnLoad(System::Object ^  sender, System::EventArgs ^  e){
  this->BofAnimationForm->Show();
  this->BofProzessForm->Show();
  this->BofTlgViewForm->Show();
}

void CBofForm::updateTlgView(CItemWrapper^ wrp){
  BofTlgViewForm->showTlg(wrp);
}
