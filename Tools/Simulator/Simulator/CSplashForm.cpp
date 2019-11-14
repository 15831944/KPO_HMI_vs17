#include "StdAfx.h"
#include "CSplashForm.h"

using namespace simulator;

//----------------------------------------------------------
void CSplashForm::SetText(String^ mess)
{
  this->labDynamicDesc->Text = mess;
  this->Refresh();
}