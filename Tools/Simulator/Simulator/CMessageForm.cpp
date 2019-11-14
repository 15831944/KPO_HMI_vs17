#include "StdAfx.h"
#include "CMessageForm.h"
#include "CLogWriterWrapper.h"
#include <assert.h>

//--------------------------------------

using namespace simulator;

//----------------------------------------
System::Void CMessageForm::OnClickPopUpMenuClear(System::Object ^  sender, System::EventArgs ^  e)
{
	richTxtBxEdit->ReadOnly=false;
	richTxtBxEdit->Clear();
	richTxtBxEdit->ReadOnly=true;
}
//----------------------------------------
System::Void CMessageForm::OnClickPopUpMenuSave(System::Object ^  sender, System::EventArgs ^  e)
{
	SaveFileDialog^ saveSzen = gcnew SaveFileDialog();
	String^ path=nullptr;
	if(saveSzen->ShowDialog() == ::DialogResult::OK)
	{
		path=saveSzen->FileName;
		if(path != nullptr)
		{
			richTxtBxEdit->SaveFile(path,System::Windows::Forms::RichTextBoxStreamType::PlainText);
		}
	}
}
//----------------------------------------
void CMessageForm::writeLine(System::String^ txt,MessTyp typ)
{
  try
  {
    if(richTxtBxEdit != nullptr)
	  {
      String^ timeStr=nullptr;
      int pos;
      DateTime time = DateTime::Now;
      timeStr=time.TimeOfDay.ToString();
      pos=timeStr->LastIndexOf(".");
		  if(pos != -1)
		  timeStr=timeStr->Substring(0,timeStr->Length-pos);
      timeStr=String::Concat(timeStr,":   ");
      richTxtBxEdit->Focus();
      richTxtBxEdit->SelectionColor=getColor(MessTyp::Info);
      richTxtBxEdit->AppendText(timeStr);
      richTxtBxEdit->SelectionColor=getColor(typ); 
      richTxtBxEdit->AppendText(System::String::Concat(txt,"\n"));

      richTxtBxEdit->SelectionStart = richTxtBxEdit->Text->Length;
      richTxtBxEdit->ScrollToCaret();


      //richTxtBxEdit->Top = richTxtBxEdit->Lines->Count +1;
      /*richTxtBxEdit->Cursor->set_Position(richTxtBxEdit->Cursor->HotSpot);*/
      richTxtBxEdit->Refresh();
	  }
  }
  catch (Exception^ ex)
  {
    return;
  }
}
//----------------------------------------
void CMessageForm::setActionName(TextCaption caption)
{
  if (caption == TextCaption::Sender)
  {
    labTitel->Text = "Sender";
    labTitel->Refresh();
    return;
  }
  if (caption == TextCaption::LogFile)
  {
    labTitel->Text = "Log file";
    labTitel->Refresh();
    return;
  }
  if (caption == TextCaption::LoadInterfaces)
  {
    labTitel->Text = "Load interfaces";
    labTitel->Refresh();
    return;
  }
  if (caption == TextCaption::LoadLogFile)
  {
    labTitel->Text = "Load log - file";
    labTitel->Refresh();
    return;
  }
  if (caption == TextCaption::Receiver)
  {
    labTitel->Text = "Receiver";
    labTitel->Refresh();
    return;
  }
  if (caption == TextCaption::SendTelegrams)
  {
    labTitel->Text = "Send telegrams";
    labTitel->Refresh();
    return;
  }
  if (caption == TextCaption::Szenario)
  {
    labTitel->Text = "Szenario";
    labTitel->Refresh();
    return;
  }
  if (caption == TextCaption::LoadSzenario)
  {
    labTitel->Text = "Load szenario";
    labTitel->Refresh();
    return;
  }
}
//----------------------------------------
void CMessageForm::setActionName(String^ str)
{
  labTitel->Text = str;
  labTitel->Refresh();
}
 //---------------------------------------
 System::Drawing::Color CMessageForm::getColor(MessTyp typ)
 {
    System::Drawing::Color c;
    switch(typ)
    {
      case 0:
        c=System::Drawing::Color::Gray;
        break;
      case 1:
        c=System::Drawing::Color::Blue;
        break;
      case 2:
        c=System::Drawing::Color::Red;
        break;
       case 3:
         c=System::Drawing::Color::Black;
        break;
      default:
        c=System::Drawing::Color::Gray;
        break;
    }
    return c;
 }
//----------------------------------------
 System::Void CMessageForm::OnTextChanged(System::Object ^  sender, System::EventArgs ^  e)
 {
	 //his-> richTxtBxEdit->set_S
 }
 //---------------------------------------
void CMessageForm::setShowModi(int mode)
{
  if(mode == 1)
  {
    panTitel->Visible = false;
  }
}
 //---------------------------------------
