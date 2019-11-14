
#include "stdafx.h"
#include "CSzenItemForm.h"

//using namespace simulator;
using namespace System::Drawing;

//-------------------------------------------
CSzenItemForm::CSzenItemForm():
pan(0),but(0),lab(0),txtBx(0),Item(0),Focuced(false)
{
}
//-------------------------------------------
CSzenItemForm::~CSzenItemForm()
{
}
//--------------------------------------------
System::Void CSzenItemForm::OnClickButton(System::Object *  sender, System::EventArgs *  e)
{
  Button* but = __try_cast<Button*>(sender);
  
  but->ImageIndex = (but->ImageIndex + 1)%2;
  if(but->ImageIndex == 0)
    Item->setSendStatus(true);
  else
    Item->setSendStatus(false);
}
//--------------------------------------------------------------------------------
System::Void CSzenItemForm::OnValidatedTextBox(System::Object *  sender, System::EventArgs *  e)
{
  TextBox* txt = __try_cast<TextBox*>(sender);
  Item->setDelay(System::Convert::ToDouble(txt->Text));
}
//--------------------------------------------------------------------------------
System::Void CSzenItemForm::OnTextChanged(System::Object *  sender, System::EventArgs *  e)
{
  TextBox* txt = __try_cast<TextBox*>(sender);
  Item->setDelay(System::Convert::ToDouble(txt->Text));
}
//--------------------------------------------------------------------------------
System::Void CSzenItemForm::OnLabelClick(System::Object *  sender, System::EventArgs *  e)
{
  Del->Invoke();
  lab->BackColor=System::Drawing::Color::LightBlue;
  txtBx->Focus();
  TlgViewForm->showTlg(Item->getTlgWrapper());
  this->Focuced = true;
}
//--------------------------------------------------------------------------------
Panel* CSzenItemForm::createSzenItemForm(CSzenItem* item,ImageList* image)
{
  this->Item=item;
  this->Image=image;
  
  pan = new Panel();
  but = new Button();
  lab = new Label();
  txtBx = new TextBox();

  pan->Height = 20;
  pan->BackColor = Color::FromKnownColor(KnownColor::Control);
  pan->Dock = DockStyle::Top;
  pan->BorderStyle = BorderStyle::FixedSingle;

  but->Width=20;
  but->Dock = DockStyle::Left;
  but->ImageList = image;
  but->ImageIndex = 0;
  but->Click += new System::EventHandler(this, OnClickButton);

  lab->Dock = DockStyle::Fill;
  lab->Text = item->getItemName();
  lab->Click += new System::EventHandler(this, OnLabelClick);

  txtBx->Dock = DockStyle::Right;
  txtBx->Width = 40;
  txtBx->Validated += new System::EventHandler(this, OnValidatedTextBox);
  txtBx->TextChanged += new System::EventHandler(this, OnTextChanged);

  pan->Controls->Add(lab);
  pan->Controls->Add(txtBx);
  pan->Controls->Add(but);

  return pan;
}
//--------------------------------------------
Panel* CSzenItemForm::getPanel()
{
  return pan; 
}
//--------------------------------------------
void CSzenItemForm::updateTime(double delay)
{
  txtBx->Text = System::Convert::ToString(delay);
}
//--------------------------------------------
 void CSzenItemForm::setLabelColor(System::Drawing::Color color)
 {
   lab->BackColor=color;
 }
//--------------------------------------------
 void CSzenItemForm::setDelegateLabClick(NotifyLabelClick* del)
 {
   Del=del;
 }
 //-------------------------------------------
void CSzenItemForm::setTlgViewForm(CTlgViewForm* tlgView)
{
  this->TlgViewForm = tlgView;
}
 //-------------------------------------------
 void CSzenItemForm::setFocuc(bool f)
 {
	 this->Focuced = f;
 }
//--------------------------------------------
bool CSzenItemForm::getFocus()
{
	return this->Focuced;
}
//--------------------------------------------
void CSzenItemForm::erase()
{
	pan->Dispose();
}
//--------------------------------------------