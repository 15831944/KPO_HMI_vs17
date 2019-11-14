#include "StdAfx.h"
#include "CInfoForm.h"

using namespace simulator;
//-----------------------------------------------------------------------------------
System::Void CInfoForm::OnClickYes(System::Object ^  sender, System::EventArgs ^  e)
{
  Chouse=true;
  Close();
}
//-----------------------------------------------------------------------------------
void CInfoForm::setMessage(String^ mess)
{
    //checkBox1->Text = mess;
    labMessage->Text = mess;
}
//-----------------------------------------------------------------------------------
bool CInfoForm::getAnswer()
{
    return Chouse;
}
//--------------------------------------------------------------------
System::Void CInfoForm::OnClickNo(System::Object ^  sender, System::EventArgs ^  e)
{
  Chouse=false;
  Close();
}
