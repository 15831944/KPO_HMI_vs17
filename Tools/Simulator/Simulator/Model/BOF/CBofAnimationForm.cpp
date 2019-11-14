#include "StdAfx.h"
#include "CBofAnimationForm.h"
//------------------------------------
using namespace simulator;
//------------------------------------
CBofAnimationForm::CBofAnimationForm(Panel^ parent){
  InitializeComponent();
  this->TopLevel = false;
  this->Parent = parent;
  this->Dock = DockStyle::Fill;
	this->FormBorderStyle = ::FormBorderStyle::None;
}