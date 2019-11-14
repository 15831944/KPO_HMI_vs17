#include "StdAfx.h"
#include "CNewUseCaseForm.h"

//---------------------------------------
using namespace simulator;
//----------------------------------------
String^ CNewUseCaseForm::getUseCaseName()
{
  return txtBxName->Text;
}
//-----------------------------------------
array <String^>^ CNewUseCaseForm::getUseCaseDescription()
{
  return txtBxDescr->Lines;
}
//-------------------------------------------