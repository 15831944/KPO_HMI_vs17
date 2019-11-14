#include "StdAfx.h"
#include "CAppSettingsForm.h"
#include "CAppSetting.h"
#include "CLogWriterWrapper.h"
#include "CFormatConverterWrapper.h"
#include "CExpWrapper.h"
#include "CItemView.h"

using namespace simulator;
//-------------------------------------------
void CAppSettingsForm::initToolTips()
{
  //Cancel Button
  Windows::Forms::ToolTip^ tmp =gcnew Windows::Forms::ToolTip();
  String^ mess = "This dialog is closed. All settings made will be lost.";
  tmp->SetToolTip(this->ButCancel,mess);
  //Ok Button
  tmp =gcnew Windows::Forms::ToolTip();
  mess = "This dialog is closed. All settings are applied.";
  tmp->SetToolTip(this->ButOk,mess);
}
//-------------------------------------------
void CAppSettingsForm::initComp()
{
  CAppSetting^ Sett = CAppSetting::getApp();
  array <String^>^ typs = Sett->getMessageTypsInLogFiles();
  //Alle Steuerelemente initialisieren
  int tmp = CFormatConverterWrapper::StringToInt(Sett->getNodesInTlgViewCollapsed());
  if (tmp < 0)
  {
    this->radCollapseBut->Checked = false;
    this->radExpandBut->Checked = true;
    this->radCollapseAllBut->Checked = false;
  }
  else if (tmp > 0)
  {
    this->radCollapseBut->Checked = false;
    this->radExpandBut->Checked = false;
    this->radCollapseAllBut->Checked = true;
  }
  else
  {
    this->radCollapseBut->Checked = true;
    this->radExpandBut->Checked = false;
    this->radCollapseAllBut->Checked = false;
  }
  
  numMaxSize->Value = (CFormatConverterWrapper::StringToInt(Sett->getMaxSizeOfLogFiles()));
  numMaxCount->Value = (CFormatConverterWrapper::StringToInt(Sett->getMaxCountOfLogFiles()));
    
  if (typs[0]->Equals("0"))
    chkBoxInfo->Checked = false;
  else
    chkBoxInfo->Checked = true;
  
  if (typs[1]->Equals("0"))
    chkBoxWarning->Checked = false;
  else
    chkBoxWarning->Checked = true;
  
  if (typs[2]->Equals("0"))
    chkBoxError->Checked = false;
  else
    chkBoxError->Checked = true;

  initToolTips();
}
//-------------------------------------------
System::Void CAppSettingsForm::ButOk_Click(System::Object^  sender, System::EventArgs^  e) 
{
  int size = 0;
  int count = 0;
  String^ typMess = nullptr;
  CAppSetting^ Sett = CAppSetting::getApp();
  array <String^>^ typs = gcnew array <String^>(4);
  
  //TlgView
  if (radExpandBut->Checked)
  {
    CItemView::setNodesCollapsed(-1);
    Sett->setNodesInTlgViewCollapsed("-1");
  }
  else if (radCollapseAllBut->Checked)
  {
    CItemView::setNodesCollapsed(1);
    Sett->setNodesInTlgViewCollapsed("1");
  }
  else
  {
    CItemView::setNodesCollapsed(0);
    Sett->setNodesInTlgViewCollapsed("0");
  }
  
  //Message Typs
  if (chkBoxInfo->Checked)
    typs[0] = "1";
  else
    typs[0] = "0";

  if (chkBoxWarning->Checked)
    typs[1] = "1";
  else
    typs[1] = "0";

  if (chkBoxError->Checked)
    typs[2] = "1";
  else
    typs[2] = "0";

  CLogWriterWrapper::getLogWriterWrapper()->setSettings(int(numMaxSize->Value),chkBoxInfo->Checked,chkBoxWarning->Checked,
                                                        chkBoxError->Checked);

  //Max Size
  Sett->setMaxSizeOfLogFiles(CFormatConverterWrapper::IntToString(int(numMaxSize->Value)));
  //Max Count
  Sett->setMaxCountOfLogFiles(CFormatConverterWrapper::IntToString(int(numMaxCount->Value)));
  Sett->setMessageTypsInLogFiles(typs);
  Close();

}
//-------------------------------------------
System::Void CAppSettingsForm::ButCancel_Click(System::Object^  sender, System::EventArgs^  e) 
{
  Close();       
}