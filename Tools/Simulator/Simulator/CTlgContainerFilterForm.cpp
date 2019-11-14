#include "StdAfx.h"
#include "CTlgContainerFilterForm.h"
using namespace simulator;

//--------------------------------------------------------------
System::Void CTlgContainerFilterForm::OnOkButtonClick(System::Object ^  sender, System::EventArgs ^  e)
{
	if(RegExpr)
  {
		::Cursor::Current = ::Cursors::WaitCursor;
    //Array - String mit reg. Ausdruecken
    RegExpr->Invoke(this->mMultiFilterForm->getRegExAsString());
    ::Cursor::Current = ::Cursors::Default;
  }
}
//--------------------------------------------------------------
void CTlgContainerFilterForm::setRegExprEvent(DelRegExprTyp^ DelExp)
{
	RegExpr=DelExp;
}
//--------------------------------------------------------------
void CTlgContainerFilterForm::initToolTips()
{
  //Clear Button
  Windows::Forms::ToolTip^ tmp =gcnew Windows::Forms::ToolTip();
  String^ mess = "All filter criteria are removed. In log-file-container all messages are visible.";
  tmp->SetToolTip(this->butClear,mess);
  //Aplly Button
  tmp =gcnew Windows::Forms::ToolTip();
  mess = "Telegrams are filtered.";
  tmp->SetToolTip(this->button1,mess);
  //Close Button
  tmp =gcnew Windows::Forms::ToolTip();
  mess = "This dialog is closed.";
  tmp->SetToolTip(this->butClose,mess);
}
//--------------------------------------------------------------
System::Void CTlgContainerFilterForm::panCenterView_Resize(System::Object^  sender, System::EventArgs^  e) 
{
    //this->Height += (this->panCenterView->Height -  this->LastHeightCenterPanel); 
}
//--------------------------------------------------------------
System::Void CTlgContainerFilterForm::butClear_Click(System::Object^  sender, System::EventArgs^  e) 
{
   ::Cursor::Current = ::Cursors::WaitCursor;
   this->mMultiFilterForm->Clear();
 	 if(RegExpr)
    RegExpr->Invoke(this->mMultiFilterForm->getRegExAsString());
   ::Cursor::Current = ::Cursors::Default;
}
//--------------------------------------------------------------
System::Void  CTlgContainerFilterForm::butClose_Click(System::Object^  sender, System::EventArgs^  e) 
{
    this->Close();
}
