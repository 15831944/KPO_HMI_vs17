#include "StdAfx.h"
#include "CBofProzessForm.h"

//-----------------------------------------------
using namespace simulator;
//-----------------------------------------------

CBofProzessForm::CBofProzessForm(Panel^ parent){
 	InitializeComponent();
	this->TopLevel = false;
	this->Parent = parent;
	this->Dock = DockStyle::Fill;
	this->FormBorderStyle = ::FormBorderStyle::None;
}

void CBofProzessForm::setProzessEvent(SelectProzessEvent^ event){
  this->prozessevent = event;
}

System::Void CBofProzessForm::buttonHMC_Click(System::Object ^  sender, System::EventArgs ^  e){
 int index;
 CItemWrapper^ wr = nullptr;

}