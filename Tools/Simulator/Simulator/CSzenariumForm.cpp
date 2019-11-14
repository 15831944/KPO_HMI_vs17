#include "StdAfx.h"
#include "CSzenariumForm.h"
#include "CTimeWrapper.h"
#include "CStdConverter.h"
#include "CAppSetting.h"
#include "CFormatConverterWrapper.h"
#include "CXmlSzenWriter.h"
#include "CCyclicTlgForm.h"
#include "CXmlCyclicTlgReader.h"
#include "CSendItemsServer.h"
#include "CXmlInterConfigReader.h"
#include "CXmlInterConfigWriter.h"
#include "CInterConfigWrapper.h"
#include "CSzenarium.h"
#include "CProgressBarViewForm.h"
#include "CLogWriterWrapper.h"

//#include "CTlgDescription.h"

using namespace simulator;
//---------------------------------------------------------
CSzenariumForm::CSzenariumForm(Panel^ parent)
{
  InitializeComponent();
  this->TopLevel = false;
  this->Parent = parent;
  this->Dock = DockStyle::Fill;
	this->FormBorderStyle = ::FormBorderStyle::None;
  Szenarium = gcnew CSzenarium();
  Szenarium->setMessScenDel(gcnew CSzenarium::MessageScenarioDelTyp(this,&CSzenariumForm::getMassageFromSzenario));
  Szenarium->setUpdateRemoveCyclicTlgInScenarioDel(gcnew CSzenarium::UpdateRemoveCyclicTlgInScenarioDelTyp(this,&CSzenariumForm::UpdateProgressBar));
  SzenItemInfoArray = gcnew ArrayList();
  butModi->Text= this->mEditMode;
  changeMode();
  MessageBox = nullptr;
  panScrollBar->Hide();
  FocucedItem = 0;
  SelectItemEvent = nullptr;
  DebugModus = 0;
  SzenariumModusEvent=nullptr;
  UpdateSzenEvent=nullptr;
  SelItemColor=Color::FromKnownColor(KnownColor::MediumSlateBlue);
  SendItemColor=Color::FromKnownColor(KnownColor::Green);
  DefaultColor=Color::FromKnownColor(KnownColor::Control);
  //ChangeValueColor=Color::Yellow;
  ChangeValueColor=Color::YellowGreen;
  UpDataFlag=false;
  this->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this,&CSzenariumForm::MouseWheelHandler);
  StopSendSzenario = false;
  timerWatch = nullptr;
  this->IgnoreDelayTimeOfUnselctedTlgs = false;
}
//---------------------------------------------------------
System::Void CSzenariumForm::MouseWheelHandler(System::Object ^  sender, System::Windows::Forms::MouseEventArgs^ e)
{
  //int step = int(treeViewTlgCon->Nodes->Count*0.1);
  //if (step <= 0)
  //  step=1;

  //Up
  if (e->Delta > 0 && vScrollBar1->Minimum != vScrollBar1->Value)
  {
    if ((vScrollBar1->Value - 3) > vScrollBar1->Minimum)
      vScrollBar1->Value -= 3;
    else 
      vScrollBar1->Value = vScrollBar1->Minimum;
  }
  //Down
  if (e->Delta < 0 && vScrollBar1->Maximum != vScrollBar1->Value)
  {
     if ((vScrollBar1->Value + 3) < vScrollBar1->Maximum)
      vScrollBar1->Value += 3;
    else 
      vScrollBar1->Value = vScrollBar1->Maximum;
  } 
}
//---------------------------------------------------------
System::Void CSzenariumForm::OnLoadForm(System::Object ^  sender, System::EventArgs ^  e)
{
  this->buttStep->Enabled=false;
  this->butRun->Enabled=false;
  trackBarTime->Minimum =(-10);
  trackBarTime->Maximum =(10);
  trackBarTime->Value = (0);
  tabCntrlTime->SelectedIndex = 1;  //tabCntrlTime; 
}
//---------------------------------------------------------
System::Void CSzenariumForm::OnActivated(System::Object ^  sender, System::EventArgs ^  e)
{
  tabCntrlTime->SelectedTab = (tabPageRealTime);
}
//---------------------------------------------------------
// !!!
//System::Void CSzenariumForm::OnButSzenCloseClick(System::Object ^  sender, System::EventArgs ^  e)
//{
//   updateSzenFile(); 
//}
//---------------------------------------------------------
System::Void CSzenariumForm::OnButtRemoveClick(System::Object ^  sender, System::EventArgs ^  e)
 {  
  int removeItemNum = Szenarium->getFocusedItem();
  if(removeItemNum > 0)
  {
    clearSzenView();
    Szenarium->remouteAt(removeItemNum);
    if(Szenarium->getSzenItemCount() < removeItemNum)
    {
      Szenarium->setFocusedItem(removeItemNum-1);
      if (SelectItemEvent && Szenarium && (Szenarium->getSzenItemCount() > 0) && (Szenarium->getFocusedItem() > 0) && !IsSendMode())
        SelectItemEvent->Invoke(Szenarium->getSzenItem(Szenarium->getFocusedItem())->getTlgWrapper(),CItemView::CreateTypForm::Szenario);
    }
    if(Szenarium->getSzenItemCount() == 0)
    {
      if(UpdateSzenEvent)
        UpdateSzenEvent->Invoke(false);
      if (RemoveSzenarioItemFromViewEvent)
        RemoveSzenarioItemFromViewEvent->Invoke();
    }
    else
    {
      updateScrollPosition();
      showSzenFromScrollPos();
    }
    updateSzenView();
  }
 }
//-------------------------------------------------------------------------------------
System::Void CSzenariumForm::OnScrollTrackBar(System::Object ^  sender, System::EventArgs ^  e)
{
  updateRelationDelay();
}
//-------------------------------------------------------------------------------------
System::Void CSzenariumForm::butModi_Click(System::Object^  sender, System::EventArgs^  e) 
{
  if (this->butModi->Text->Equals(this->mSendMode))
 {
    this->butModi->Text = this->mEditMode;
    this->butModi->BackColor = System::Drawing::Color::LightGreen;
    return;
 }
  if (this->butModi->Text->Equals(this->mEditMode))
 {
    this->butModi->Text = this->mSendMode;
    this->butModi->BackColor = System::Drawing::Color::LightBlue;
    return;
 }
}
//-------------------------------------------------------------------------------------
System::Void CSzenariumForm::OnSelectedIndexChanged(System::Object ^  sender, System::EventArgs ^  e)
{
  if(tabCntrlTime->SelectedIndex == 0)
  {
    if(txtBxTime != nullptr)
    {
      double del = CFormatConverterWrapper::StringToDouble(txtBxTime->Text);
      Szenarium->setSimpleDelay(del);
      showSzenarium();
      setItemTxtBoxModus(false);
    }
    setItemTxtBoxModus(false);
  }
  else
  {
    updateRelationDelay();
    setItemTxtBoxModus(true);
  }
}
//-------------------------------------------------------------------------------------
System::Void CSzenariumForm::OnButtCopyClick(System::Object ^  sender, System::EventArgs ^  e)
{
  int count;
  int scrollVal,newScrollVal;
  int selSzenItem;
  selSzenItem=Szenarium->getFocusedItem();
  if(selSzenItem > 0)
  {
    scrollVal=vScrollBar1->Value;
    count = System::Convert::ToInt32(numericUpCopyDown->Value);
    Szenarium->duplicateItem(selSzenItem,count);
    Szenarium->setFocusedItem(selSzenItem+count);
    Szenarium->calcDelay();
    updateScrollPosition();
    if(SzenItemInfoArray->Count+scrollVal < Szenarium->getFocusedItem()+1)
    {
     /*newScrollVal=Szenarium->getFocusedItem()-(SzenItemInfoArray->Count-1);*/
     newScrollVal=Szenarium->getFocusedItem()-(SzenItemInfoArray->Count-1);
      if(newScrollVal < vScrollBar1->Minimum)
      {
        newScrollVal = vScrollBar1->Minimum;
      }
      else
      {
        if(newScrollVal > vScrollBar1->Maximum)
        {
          newScrollVal=vScrollBar1->Maximum;
        }
      }
     vScrollBar1->Value = (newScrollVal);
    }
    /*updateScrollPosition();*/
    showSzenFromScrollPos();
    updateSzenView();
  }
}
//---Button Sort Click-----------------------------------------------------------------
System::Void CSzenariumForm::OnClickButtSort(System::Object ^  sender, System::EventArgs ^  e)
{
  //---test-------------------------------
  // int count,i;
  //CSzenItem* szenItem=0;
  //count=Szenarium->getSzenItemCount();
  //MessageHandler->Invoke("===================================",0);
  //for(i=1;i<=count;i++)
  //{
      //szenItem=Szenarium->getSzenItem(i);
      //MessageHandler->Invoke(String::Concat("Name: ",szenItem->getItemName()),0);
      //MessageHandler->Invoke(String::Concat("Time: ",System::Convert::ToString(szenItem->getTime())),0);
      //MessageHandler->Invoke(String::Concat("Delay: ",System::Convert::ToString(szenItem->getDelay())),0);
  //}
  //MessageHandler->Invoke("===================================",0);

  Szenarium->acceptChangeTime();
  clearSzenView();
  updateScrollPosition();
  showSzenFromScrollPos();
  updateSzenView();
  //---test------------------------------------
  //int count,i;
  //CSzenItem* szenItem=0;
  //count=Szenarium->getSzenItemCount();
  //MessageHandler->Invoke("===================================",0);
  //for(i=1;i<=count;i++)
  //{
      //szenItem=Szenarium->getSzenItem(i);
      //MessageHandler->Invoke(String::Concat("Name: ",szenItem->getItemName()),0);
      //MessageHandler->Invoke(String::Concat("Time: ",System::Convert::ToString(szenItem->getTime())),0);
      //MessageHandler->Invoke(String::Concat("Delay: ",System::Convert::ToString(szenItem->getDelay())),0);
  //}
  //MessageHandler->Invoke("===================================",0);
  //-------------------------------------------
  //showSzenarium();
}
//-------------------------------------------------------------------------------------
System::Void CSzenariumForm::OnScrollValueChange(System::Object ^  sender, System::EventArgs ^  e)
{
  UpDataFlag=true;
  showSzenFromScrollPos();
  UpDataFlag=false;
}
//-------------------------------------------------------------------------------------
System::Void CSzenariumForm::OnSzenLabelClick(System::Object ^  sender, System::EventArgs ^  e)
{
  CItemWrapper^ tlgWr=nullptr;
  int count = SzenItemInfoArray->Count;
  SzenItemInfo^ itemInfo = nullptr;
  Label^ lab = safe_cast<Label^>(sender);
  int index = System::Convert::ToInt32(lab->Tag);
  int actItem;
  setLabDefaultColor();
  itemInfo = safe_cast<SzenItemInfo^>(SzenItemInfoArray[count-index]);
  actItem = getFocusedSzenItem(index);
  Szenarium->setFocusedItem(actItem);
  FocucedItem = index;
  lab->Focus();
  lab->BackColor = Color::FromKnownColor(KnownColor::MediumSlateBlue);
  lab->Refresh();
  itemInfo->txtBx->Focus();
  SelItemColor=Color::FromKnownColor(KnownColor::MediumSlateBlue);
  if(SelectItemEvent)
  {
    //MessageBox->writeLine(Szenarium->getSzenItem(actItem)->getIsCyclic().ToString(),CMessageForm::MessTyp::Warning);  
    tlgWr=Szenarium->getSzenItem(actItem)->getTlgWrapper();
		SelectItemEvent->Invoke(tlgWr,CItemView::CreateTypForm::Szenario);
    this->EditModeUpdateToItemView();
  }
}
//-------------------------------------------------------------------------------------
//---Szenarium TextBox Validate Ereignis
//-------------------------------------------------------------------------------------
System::Void CSzenariumForm::OnSzenValidatedTextBox(System::Object ^  sender, System::EventArgs ^  e)
{
  if(!UpDataFlag)
  {
    double val;
    double diff;
    int index;
    int i=0;
    CSzenItem^ szenItem=nullptr;
    TextBox^ txtBx = safe_cast<TextBox^>(sender);
    bool ok=true;
    /* bool first_point = true;*/
    //if (txtBx->Text->Length!=0)
    //{
    //  temp=txtBx->Text;
    //  //Ueberpruefen, ob erste Buchstabe kein Punkt oder keine Komma ist.
    //  if (temp->get_Chars(0) == 44 || temp->get_Chars(0) == 46)
    //    ok=false;
    //  while (ok && i<temp->Length)
    //  {
    //    if (temp->get_Chars(i)!=44 && temp->get_Chars(i)!=46)
    //    {
    //      for (int j=48;j<=58;j++)
    //      {
    //        if (temp->get_Chars(i)==j)
    //          break;
    //        if (j==58)
    //          ok=false;
    //      }
    //    }
    //    else
    //    {
    //      if (first_point)
    //        first_point=false;
    //      else
    //        ok=false;
    //    }
    //    i++;
    //  }
 
    try
    {
      //val = System::Convert::ToDouble(txtBx->Text);
      val = CFormatConverterWrapper::StringToDouble(txtBx->Text);
    }
    catch (CExpConvertError e)
    {
      /*MessageBox->writeLine(String::Concat("New time input (",txtBx->Text,") is invalid."),CMessageForm::MessTyp::Error);*/
      String^ mess = String::Concat("New time input (",txtBx->Text,") is invalid.");
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                            __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      MessageBox::Show(mess,"Error", MessageBoxButtons::OK,MessageBoxIcon::Error);

      ok=false;
    }
    if (ok)
    {
      index = System::Convert::ToInt32(txtBx->Tag);
      index = getFocusedSzenItem(index);
      szenItem = Szenarium->getSzenItem(index);
      diff = szenItem->getDelay() - val;
      if((diff > 0.001) || (diff < -0.001))
      {
        Szenarium->getSzenItem(index)->setChangeTime(val);
        txtBx->BackColor = ChangeValueColor;
        /*MessageBox->writeLine(String::Concat("New time input ( ",System::Convert::ToString(val)," ) is validated."),
        CMessageForm::MessTyp::Info);*/
      }
    }
  }
}
//-------------------------------------------------------------------------------------
System::Void CSzenariumForm::OnSzenButtonClick(System::Object ^  sender, System::EventArgs ^  e)
{
  Button^ but = safe_cast<Button^>(sender);
  int index = System::Convert::ToInt32(but->Tag);
  int actItem;

  actItem = getFocusedSzenItem(index);
  but->ImageIndex = (but->ImageIndex+1) % 2;
  if(but->ImageIndex == 0)
  {
  Szenarium->getSzenItem(actItem)->setSendStatus(true);
  }
  else
  {
    Szenarium->getSzenItem(actItem)->setSendStatus(false);
  }
}
//--------------------------------------------------------------------------------------
System::Void CSzenariumForm::CSzenariumForm_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) 
{
  bool flag=false;
  System::Windows::Forms::Keys key = e->KeyCode;
  int selItem=Szenarium->getFocusedItem();
  int itemCount=Szenarium->getSzenItemCount();
  int step = panItemCon->Controls->Count;
  //int focusedItemNumber = selItem - vScrollBar1->Value;
  
  if(key == System::Windows::Forms::Keys::Up)    //|| (key == System::Windows::Forms::Keys::Down))
  {
    if((selItem > 1))
    {
      Szenarium->setFocusedItem(selItem-1);
      setScrollFromSelectedItem(0,0);
      showSzenFromScrollPos();
      flag=true;
    }
  }
  if(key == System::Windows::Forms::Keys::Down)
  {
    if((selItem > 0) && (selItem < itemCount))
    {
      Szenarium->setFocusedItem(selItem+1);
      setScrollFromSelectedItem(0,1);
      showSzenFromScrollPos(); 
      flag=true;
    }
  }

  if(key == System::Windows::Forms::Keys::PageUp)
  {
    //Wenn selektierte Item nicht im Ansicht
    if (selItem < (vScrollBar1->Value-1) || selItem > (vScrollBar1->Value+panItemCon->Controls->Count))
    {
      Szenarium->setFocusedItem(vScrollBar1->Value+panItemCon->Controls->Count-1);
      showSzenFromScrollPos(); 
      flag=true;
    }
    else
    { 
      if(selItem > 0)
      {
        if (selItem - step  > 0)
          Szenarium->setFocusedItem(selItem-step);
        else
          Szenarium->setFocusedItem(1);
        
        if (vScrollBar1->Value == vScrollBar1->Maximum)
          vScrollBar1->Value-=step-1;
        else if ((vScrollBar1->Value - step) < vScrollBar1->Minimum)
          vScrollBar1->Value = vScrollBar1->Minimum;
        else
          vScrollBar1->Value-=step;
        showSzenFromScrollPos(); 
        flag=true;
      }
    }
  }
  if(key == System::Windows::Forms::Keys::PageDown)
  {
    //Wenn selektierte Item nicht im Ansicht
    if (selItem < (vScrollBar1->Value-1) || selItem > (vScrollBar1->Value+panItemCon->Controls->Count))
    {
      Szenarium->setFocusedItem(vScrollBar1->Value);
      showSzenFromScrollPos(); 
      flag=true;
    }
    else
    {
      if(selItem > 0)
      {
        if ((selItem + step) < itemCount)
          Szenarium->setFocusedItem(selItem+step);
        else
          Szenarium->setFocusedItem(itemCount);
        if ((vScrollBar1->Value + step) > vScrollBar1->Maximum)
          vScrollBar1->Value = vScrollBar1->Maximum;
        else
          vScrollBar1->Value+=step;
        showSzenFromScrollPos();
        flag=true;
      }
    }
  }
  if(SelectItemEvent && flag)
  {
    CItemWrapper^ tlgWr=nullptr;
    tlgWr=Szenarium->getSzenItem(Szenarium->getFocusedItem())->getTlgWrapper();
    SelectItemEvent->Invoke(tlgWr,CItemView::CreateTypForm::Szenario);
    this->EditModeUpdateToItemView();
  }
}
//--------------------------------------------------------------------------------------
System::Void CSzenariumForm::OnButtStepClick(System::Object ^  sender, System::EventArgs ^  e)
{
  DebugModus = 2;
  if(SendSzenThread->ThreadState == System::Threading::ThreadState::Suspended)
    SendSzenThread->Resume();
}
//--------------------------------------------------------------------------------------
System::Void CSzenariumForm::OnButRunClick(System::Object ^  sender, System::EventArgs ^  e)
{
  DebugModus = 1;
  if(SendSzenThread->ThreadState == System::Threading::ThreadState::Suspended)
    SendSzenThread->Resume();
}
//--------------------------------------------------------------------------------------
System::Void CSzenariumForm::OnDebugLabelClick(System::Object ^  sender, System::EventArgs ^  e)
{
  Label^ lab = safe_cast<Label^>(sender);
  int index = lab->ImageIndex;
  int itemIndex = System::Convert::ToInt32(lab->Tag);
  int itemSzen;
  lab->ImageIndex = index*(-1);
  itemSzen = getFocusedSzenItem(itemIndex);
  if(lab->ImageIndex == -1)
  {
    Szenarium->getSzenItem(itemSzen)->setBreakPoint(false);
  }
  else
  {
    Szenarium->getSzenItem(itemSzen)->setBreakPoint(true);
  }
}
//--------------------------------------------------------------------------------------
System::Void CSzenariumForm::OnResizeItemCountPanel(System::Object ^  sender, System::EventArgs ^  e)
{
  showSzenarium();
  panDebug->Show();
}
//--------------------------------------------------------------------------------------
System::Void CSzenariumForm::OnPopupMenuClick(System::Object ^  sender, System::EventArgs ^  e)
{
  Label^ lab = safe_cast<Label^>(PopUpMenu->SourceControl);
  lab->BackColor=Color::FromKnownColor(KnownColor::MediumSlateBlue);


  //Menu-Items (de)aktivieren
  if (!this->IsSendMode())
  {
    PopUpMenu->MenuItems[0]->Enabled=false;
    PopUpMenu->MenuItems[1]->Enabled=false;
    PopUpMenu->MenuItems[2]->Enabled=true;
  }
  else
  {
    PopUpMenu->MenuItems[2]->Enabled=false;
    if (this->IsSzenarionSending())
    {
      PopUpMenu->MenuItems[0]->Enabled=false;
      PopUpMenu->MenuItems[1]->Enabled=false;
    }
    else
    {
      PopUpMenu->MenuItems[0]->Enabled=true;
      PopUpMenu->MenuItems[1]->Enabled=true;
    }
  }

      CItemWrapper^ item = Szenarium->getSzenItem(Szenarium->getFocusedItem())->getTlgWrapper();
    CCyclicItemContainer^ itemContainer = CCyclicItemContainer::getCyclicItemContainer();
    if (!itemContainer->isItemInContainer(item))
      PopUpMenu->MenuItems[2]->Text = "Add To Cyclic Container";
    else
      PopUpMenu->MenuItems[2]->Text = "Remove From Cyclic Container";
}
//--------------------------------------------------------------------------------------
System::Void CSzenariumForm::OnClickMenuSendFromThis(System::Object ^  sender, System::EventArgs ^  e)
{
  SendTelIndex = getFocusedSzenItem(FocucedItem);
  sendSzenarium(false);
}
//--------------------------------------------------------------------------------------
System::Void CSzenariumForm::OnClickMenuItemSend(System::Object ^  sender, System::EventArgs ^  e)
{
  SendTelIndex = getFocusedSzenItem(FocucedItem);
  System::Threading::ThreadStart^ sendOneStart = gcnew System::Threading::ThreadStart(this,&CSzenariumForm::sendOneTelegram);
  System::Threading::Thread^ sendOneThread = gcnew System::Threading::Thread(sendOneStart);
  sendOneThread->Start();
  Label^ lab = safe_cast<Label^>(PopUpMenu->SourceControl);
  lab->BackColor=Color::FromKnownColor(KnownColor::Control);
}
//--------------------------------------------------------------------------------------
System::Void CSzenariumForm::OnClickMenuSetCyclicTlg(System::Object ^  sender, System::EventArgs ^  e)
{
  CItemWrapper^ item = Szenarium->getSzenItem(Szenarium->getFocusedItem())->getTlgWrapper();
  CCyclicItemContainer^ itemContainer = CCyclicItemContainer::getCyclicItemContainer();
  if (!itemContainer->isItemInContainer(item))
    itemContainer->addItemToContainer(item->getInterfece(),item,false);
  else
    itemContainer->removeItem(item);
  //CCyclicTlgForm^ cyclic = new CCyclicTlgForm();
  //cyclic->ShowDialog();
}
//--------------------------------------------------------------------------------------
System::Void CSzenariumForm::OnButtDelayOkClick(System::Object ^  sender, System::EventArgs ^  e)
{
  double del = CFormatConverterWrapper::StringToDouble(txtBxTime->Text);
  Szenarium->setSimpleDelay(del);
  showSzenarium();
  setItemTxtBoxModus(false);
}
//--------------------------------------------------------------------------------------
System::Void CSzenariumForm::OnButtTlgDownClick(System::Object ^  sender, System::EventArgs ^  e)
{
  int item=Szenarium->getFocusedItem();
  int newScrollVal;
  if((item > 0) && (item < Szenarium->getSzenItemCount()))
  {
    int posNew,itemCount;
    System::Decimal valDec = numUpDownTlg->Value;
    int val=System::Convert::ToInt32(valDec);
    posNew=item+val;
    // EMAL----------------------------------
    itemCount=Szenarium->getSzenItemCount();
    if(posNew > itemCount)
      posNew = itemCount;
    Szenarium->swapItems(item,posNew);
    //--------------------------------------
    Szenarium->setFocusedItem(posNew);
    newScrollVal=Szenarium->getFocusedItem()-(SzenItemInfoArray->Count-1);
    if(newScrollVal < vScrollBar1->Minimum)
    {
        newScrollVal = vScrollBar1->Minimum;
    }
    else
    {
      if(newScrollVal > vScrollBar1->Maximum)
      {
          newScrollVal=vScrollBar1->Maximum;
      }
    }
    vScrollBar1->Value = (newScrollVal);
    showSzenarium();
  }
}
//--------------------------------------------------------------------------------------
System::Void CSzenariumForm::OnButtTlgUpClick(System::Object ^  sender, System::EventArgs ^  e)
{
  int item=Szenarium->getFocusedItem();
  if(item > 1)
  {
    CItemWrapper^ wr = nullptr;
    int posNew;
    System::Decimal valDec = numUpDownTlg->Value;
    int val=System::Convert::ToInt32(valDec);
    posNew=item-val;
    if(posNew < 1)
    posNew = 1;
    Szenarium->swapItems(item,posNew);
    Szenarium->setFocusedItem(posNew);
    //EMAL-----------------------------------
    if(posNew < vScrollBar1->Minimum)
    {
      posNew = vScrollBar1->Minimum;
    }
    else
    {
      if(posNew > vScrollBar1->Maximum)
      {
        posNew=vScrollBar1->Maximum;
      }
    }
    vScrollBar1->Value = (posNew);
    //---------------------------------------
    showSzenarium();
  }
}
//--------------------------------------------------------------------------------------
System::Void CSzenariumForm::OnLeaveFocus(System::Object ^  sender, System::EventArgs ^  e)
{
    setDisableFocus();
}
//--------------------------------------------------------------------------------------
void CSzenariumForm::calcDelay(double rel)
{
    Szenarium->calcDelay(rel);
}
//-------------------------------------------------------------------------------------
void CSzenariumForm::addToSzenarium(CItemWrapper^ tlg,double time)
{
  Szenarium->addToSzenarium(tlg,time);
    if(UpdateSzenEvent)
        UpdateSzenEvent->Invoke(true);
}
//-------------------------------------------------------------------------------------
void CSzenariumForm::showCyclicTelegramsInSzenario()
{
  if (Szenarium)
  {
    if (Szenarium->getSzenItemCount() > 0)
    {
      CItemWrapper^ item = nullptr;
      item = Szenarium->getSzenItem(Szenarium->getFocusedItem())->getTlgWrapper();
      if (item)
      {
        //CCyclicTlgForm^ cyclic = new CCyclicTlgForm(item,Szenarium->getCyclicItemTable());
        //cyclic->ShowDialog();
      }
    }
  }
}
//-------------------------------------------------------------------------------------
void CSzenariumForm::showSzenarium()
{
  updateScrollPosition();
  showSzenFromScrollPos();
  updateSzenView();
}
//-------------------------------------------------------------------------------------
void CSzenariumForm::clearSzenView()
{
  //for(int i=0;i<panItemCon->Controls->Count;i++)
  //  panItemCon->Controls[i]->~Panel();
  //for(int i=0;i<panDebug->Controls->Count;i++)
		//panDebug->Controls[i]->~Controls;

  SzenItemInfo^ tmp;

  panItemCon->Controls->Clear();
  panDebug->Controls->Clear();
  for (int i=0;i<SzenItemInfoArray->Count;i++)
  {
     tmp = (SzenItemInfo^)SzenItemInfoArray[i];
     tmp->Clean();
  }
  SzenItemInfoArray->Clear();
  GC::Collect();
}
//---------------------------------------------------------
int CSzenariumForm::getFocusedSzenItem(int index)
{
  int ret = 0;
  int val;
  if(panScrollBar->Visible)
  {
  val=vScrollBar1->Value;
  if(val == 1)
  {
    ret=index;
  }
  else
  {
    if(val != vScrollBar1->Maximum)
      ret = val+index-1;
    else
      ret = val+index;
  }      
  }
  else
  {
    ret = index;
  }
  return ret;
}
//---------------------------------------------------------
void CSzenariumForm::setLabDefaultColor()
{
  int count = SzenItemInfoArray->Count;
  SzenItemInfo^ itemInfo = nullptr;
  for(int i=0;i<count;i++)
  {
    itemInfo = safe_cast<SzenItemInfo^>(SzenItemInfoArray[i]);
    itemInfo->lab->BackColor = DefaultColor;
  }
}
//---------------------------------------------------------
void CSzenariumForm::setSelectSzenItemTyp(SelectSzenItemTyp^ eventTyp)
{
  SelectItemEvent = eventTyp;
}
//---------------------------------------------------------
void CSzenariumForm::updateItem(CItemWrapper^ tlgWr)
{
  if(butModi->Text->Equals(this->mEditMode))
  {
    if(Szenarium->getSzenItemCount()>0)
    {
      // !!! 
      //int szenItem = getFocusedSzenItem(Szenarium->getFocusedItem());
      Szenarium->updateItem(Szenarium->getFocusedItem(),tlgWr);
    }
  }
}
//---------------------------------------------------------
void CSzenariumForm::addToSzenarium(CItemWrapper^ tlg)
{
  if(butModi->Text->Equals(this->mEditMode))
  {
    int ActuellItem = Szenarium->getFocusedItem();
    Szenarium->addToSzenarium(tlg,ActuellItem);
      if(UpdateSzenEvent)
        UpdateSzenEvent->Invoke(true);
  }
  else
  {
    String^ mess = "Add telegram to szenario is in send mode not allowed, please change to edit mode.";
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    MessageBox->writeLine(mess,CMessageForm::MessTyp::Warning);  
  }
}
//---------------------------------------------------------
void CSzenariumForm::saveSimpleTimeSzenarium(String^ path)
{
  int index;
  index=path->IndexOf(".szn");
  //In Simple Time Ansicht wechseln
  tabCntrlTime->SelectedIndex = (0);
  //XML - Datei
  if (index == -1)
  {
    CXmlSzenWriter^ szenWriter = gcnew CXmlSzenWriter();
    szenWriter->writeSzenarium(path,Szenarium);
  }//Textdatei
  else
  {
    Szenarium->setMessageScenSafeProgressDel(gcnew CSzenarium::MessageScenSafeProgressDelTyp(this,&CSzenariumForm::UpdateProgressBar));
    progressBar = gcnew CProgressBarViewForm();
    progressBar->setMinAndMax(0,Szenarium->getSzenItemCount());
    progressBar->setSourceLab("Save Szenario.");
    progressBar->Show();
    Szenarium->saveSzenarium(path);
    progressBar->Close();
    progressBar=nullptr;
  }
}
//---------------------------------------------------------
void CSzenariumForm::saveSzenarium(String^ path)
{
  int index;
  index=path->IndexOf(".szn");

  if (tabCntrlTime->SelectedIndex == 0)
  {
    tabCntrlTime->SelectedIndex = (1);
  }

  if (index == -1)
  {
    CXmlSzenWriter^ szenWriter = gcnew CXmlSzenWriter();
    szenWriter->writeSzenarium(path,Szenarium);
  }
  else
  {
    Szenarium->setMessageScenSafeProgressDel(gcnew CSzenarium::MessageScenSafeProgressDelTyp(this,&CSzenariumForm::UpdateProgressBar));
    progressBar = gcnew CProgressBarViewForm();
    progressBar->setMinAndMax(0,Szenarium->getSzenItemCount());
    progressBar->setSourceLab("Save Szenario.");
    progressBar->Show();
    Szenarium->saveSzenarium(path);
    progressBar->Close();
    progressBar=nullptr;
  }
  
  /*CXmlSzenWriter* szenWriter = new CXmlSzenWriter();
  szenWriter->writeSzenarium(path,Szenarium);*/
  //int count,i;
  //int index;
  //int lenght;
  //String^ str=0;
  //String^ tel=0;
  //String^ inter=0;
  //String^ tlgName=0;
  //String^ szenName=0;
  //String^ strDelay=0;
  //bool status;
  //String^ statusStr=0;
  //double delay;
  //double t0,rel;
  //System::IO::StreamWriter* sw = new System::IO::StreamWriter(path);

  //count=Szenarium->getSzenItemCount();
  //if(count > 0)
  //{
  //  szenName = Szenarium->getName();
  //  rel = Szenarium->getDelayRel();
  //  t0 = Szenarium->getSzenItem(1)->getTime();
  //  sw->WriteLine(String::Concat("Name ",szenName));
  //  sw->WriteLine(String::Concat("DelayRel ",System::Convert::ToString(rel)));
  //  sw->WriteLine(String::Concat("Time ",System::Convert::ToString(t0)));
  //}
  //for(i=1;i<=count;i++)
  //{
  //  delay = Szenarium->getSzenItem(i)->getDelay();
  //  tlgName=Szenarium->getSzenItem(i)->getItemName();
  //  status = Szenarium->getSzenItem(i)->getSendStatus();
  //  if(status)
  //      statusStr = "On";
  //  else
  //      statusStr = "Off";
  //  str=Szenarium->getSzenItemAsString(i);
  //  inter = Szenarium->getSzenItem(i)->getInterface();
  //   //!! Delay Zeit wird auf 4 Nachkommastellen abgekuertzt
  //  //-----------------------------------------
  //  strDelay=System::Convert::ToString(delay);
  //  lenght=strDelay->Length;
  //  
  //  index=strDelay->IndexOf(',');
  //  if (index==-1)
  //     index=strDelay->IndexOf('.');
  //  
  //  if (index==-1)
  //      strDelay=strDelay->Concat(strDelay,",0000");
  //  else
  //  {
  //    if (index>0)
  //    {
  //      if (index+5<=lenght)
  //        strDelay=strDelay->Remove((index+5),(strDelay->Length)-(index+5));
  //      else if (lenght-(index+1)==1)
  //        strDelay=strDelay->Concat(strDelay,"000");
  //      else if (lenght-(index+1)==2)
  //        strDelay=strDelay->Concat(strDelay,"00");
  //      else if (lenght-(index+1)==3)
  //        strDelay=strDelay->Concat(strDelay,"0");
  //     }
  //  }
  //  tel = String::Concat(inter," ",tlgName," ",strDelay," ",statusStr," ",str);
  //  //------------------------------------------
  //  //tel = String::Concat(inter," ",tlgName," ",System::Convert::ToString(delay)," ",statusStr," ",str);
  //  sw->WriteLine(tel);
  //}
  //Szenarium->setSzenChangeModus(false);
  //sw->Close();

  /*int count,i;
  String^ str=0;
  String^ tel=0;
  String^ inter=0;
  String^ tlgName=0;
  String^ szenName=0;

  bool status;
  String^ statusStr=0;
  double delay;
  double t0,rel;
  System::IO::StreamWriter* sw = new System::IO::StreamWriter(path);

  count=Szenarium->getSzenItemCount();
  if(count > 0)
  {
    szenName = Szenarium->getName();
    rel = Szenarium->getDelayRel();
    t0 = Szenarium->getSzenItem(1)->getTime();
    sw->WriteLine(String::Concat("Name ",szenName));
    sw->WriteLine(String::Concat("DelayRel ",System::Convert::ToString(rel)));
    sw->WriteLine(String::Concat("Time ",System::Convert::ToString(t0)));
  }
  for(i=1;i<=count;i++)
  {
    delay = Szenarium->getSzenItem(i)->getDelay();
    tlgName=Szenarium->getSzenItem(i)->getItemName();
    status = Szenarium->getSzenItem(i)->getSendStatus();
    if(status)
        statusStr = "On";
    else
        statusStr = "Off";
    str=Szenarium->getSzenItemAsString(i);
    inter = Szenarium->getSzenItem(i)->getInterface();
    tel = String::Concat(inter," ",tlgName," ",System::Convert::ToString(delay)," ",statusStr," ",str);
    
    sw->WriteLine(tel);
  }
  Szenarium->setSzenChangeModus(false);
  sw->Close();*/

}
//---------------------------------------------------------
void CSzenariumForm::loadSzenarium(String^ path,ArrayList^ protoSet)
{
  String^ line = nullptr;
  String^ delStr = " ";
  array <Char>^ delChar = delStr->ToCharArray();
  array <String^>^ items = nullptr;
  CInterBaseManager^ interMan = nullptr;
  CItemWrapper^ Tlg=nullptr;
  String^ Error=nullptr;
  int count=0;
  int countItem=0;
  double t0,t1,d1;
  double d0 = -1.0;
  double rel;
  double offset=0.0;
  int index;
  System::IO::StreamReader^ sr = gcnew System::IO::StreamReader(path);
  String^ mess=nullptr;
 
  clearSzenView();
  Szenarium->clearSzenarium();
 
  try
  {
    //Xml Reader
    System::IO::StreamReader^ xmlCheck = gcnew System::IO::StreamReader(path);
    line = xmlCheck->ReadLine();
    xmlCheck->Close();
    int pos = line->IndexOf("<?xml");
    
    //Wenn Szenarion in XML Format
    if(pos>-1)
    {
      CXmlSzenReader^ szenReader = gcnew CXmlSzenReader();
      Szenarium=szenReader->loadSzenarium(path,protoSet);
      showSzenarium();
      mess = "This scenario is present in an XML file to guarantee correct handling, the scenario must be saved in the text file.\n\n";
      mess = String::Concat(mess,"Dieses Szenario liegt in einer XML -Datei vor,.");
      mess = String::Concat(mess,"um die richtige Bearbeitung zu gewährleisten,");
      mess = String::Concat(mess,"muss das Szenario in der Textdatei gespeichert werden.");
      System::Windows::Forms::MessageBox::Show(nullptr,mess,"Warning",System::Windows::Forms::MessageBoxButtons::OK);
    
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,
                               __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    }
    //Wenn Szenario in Text Format    
    else
    {
      line = sr->ReadLine();
      items = line->Split(delChar);
      if(items->Length == 2)
        Szenarium->setName(items[1]);
      else
        Szenarium->setName("Unknow");

      line = sr->ReadLine();
      items = line->Split(delChar);
      if(items->Length == 2)
      {
        rel = CFormatConverterWrapper::StringToDouble(items[1]);
        Szenarium->setDelayRel(rel);
      }
      else
      {
        Szenarium->setDelayRel(1.0);
      }

      line = sr->ReadLine();
      items = line->Split(delChar);
      if(items->Length == 2)
      {
        //t0 = System::Convert::ToDouble(items[1]);
        t0 = CFormatConverterWrapper::StringToDouble(items[1]);
      }
      else
        t0 = 0.0;
    
      //CXmlInterConfigReader^ confFileReader = new CXmlInterConfigReader();

       
      //--------Datei Groesse ermitteln -------
      System::IO::FileInfo^ file = gcnew System::IO::FileInfo(path);
      //File Groesse an ProgressBar ubergeben
      CProgressBarViewForm^ progressBar = gcnew CProgressBarViewForm(); 
      progressBar->setMinAndMax(0,file->Length);
      progressBar->setSourceLab("Load Szenario ...");
      progressBar->Show();
      
      //Item aus Szenario einlesen
      while((line = sr->ReadLine()) != nullptr)
      {
        try
        {
          String^ testEmpty=nullptr;
          testEmpty=line->Replace(" ","");
          if(!testEmpty->Equals(""))
          {
            items = line->Split(delChar,5);
						if(items->Length != 5)
            {
              mess = "Format of Line is wrong";
              MessageBox->writeLine(mess,CMessageForm::MessTyp::Error);
              CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
              MessageBox->writeLine(line,CMessageForm::MessTyp::Error);
              CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,line,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
            }
            else
            {
              interMan = getProtoInterface(items[0],protoSet);
              if(interMan == nullptr)
              {
                mess = String::Concat("Unknown Interface: ",items[0]);
                CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
                MessageBox->writeLine(mess,CMessageForm::MessTyp::Error);
                CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,line,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
                MessageBox->writeLine(line,CMessageForm::MessTyp::Error);
              }
              else
              {   
                Tlg = interMan->makeTlg(items[1]);
                //CTlgDescription::writeTlgDescr("V:\\SMC\\L2S1\\Debug\\bin\\nachLoad1SzenariumTlg.txt");
                Error = Tlg->fillTlg(items[4]);
                //CTlgDescription::writeTlgDescr("V:\\SMC\\L2S1\\Debug\\bin\\nachLoad2SzenariumTlg.txt");
                if(Error)
                {
                  if(MessageBox)
                  {
                    MessageBox->writeLine(Error,CMessageForm::MessTyp::Error);
                    MessageBox->writeLine(line,CMessageForm::MessTyp::Error);
                  }
                  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,Error,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
                  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,line,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
                }
                else
                {
                  if(d0 < 0.0)
                  {
                    d0 = CFormatConverterWrapper::StringToDouble(items[2]);
                    d1 = d0;
                    offset=d0;
                  }
                  else
                  {
                    d1 = CFormatConverterWrapper::StringToDouble(items[2]);
                    if(d1<offset)
                      offset=d1;
                  }
                  t1 = (d1-d0)/rel + t0;
                  ////Id vergleichen
                  //CompareConfigIdWithFileId (Tlg,confFileReader);
                  index = Szenarium->addToSzenarium(Tlg,t1);
              
                  Tlg->clearWrapperTlg();
                  
                  //CTlgDescription::writeTlgDescr("V:\\SMC\\L2S1\\Debug\\bin\\nachLoad3SzenariumTlg.txt");
                  if(items[3]->Equals("On"))
                  {
                    Szenarium->getSzenItem(index)->setSendStatus(true);
                  }
                  else
                  {
                    Szenarium->getSzenItem(index)->setSendStatus(false);
                  }
                
                }
              }
            }
            count++;
            progressBar->updateStep(line->Length);
          }
        }
        catch(String^ mess)
        {
          MessageBox->writeLine(mess,CMessageForm::MessTyp::Error);
          MessageBox->writeLine(line,CMessageForm::MessTyp::Error);
        }
        catch(...)
        {
          MessageBox->writeLine("Unknown Error",CMessageForm::MessTyp::Error);
          MessageBox->writeLine(line,CMessageForm::MessTyp::Error);
        }
      }
      sr->Close();
      SelItemColor=Color::FromKnownColor(KnownColor::MediumSlateBlue);
      Szenarium->setPath(path);
      if(Szenarium->getSzenItemCount() != 0)
      {
        Szenarium->calcDelay();
        Szenarium->moveDelay(offset);
        Szenarium->setFocusedItem(1);
        if(SelectItemEvent)
        {
          CItemWrapper^ tlgWr=nullptr;
          tlgWr=Szenarium->getSzenItem(1)->getTlgWrapper();
					SelectItemEvent->Invoke(tlgWr,CItemView::CreateTypForm::Szenario);
          this->EditModeUpdateToItemView();
        }
        updateScrollPosition();
        showSzenFromScrollPos();
        Szenarium->setSzenChangeModus(false);
        updateSzenView();
        UpdateSzenEvent->Invoke(true);
      }
      progressBar->Close();
    }
    countItem=Szenarium->getSzenItemCount();

    updateRelationDelay();

    MessageBox->writeLine(String::Concat("Total: ",System::Convert::ToString(count)),CMessageForm::MessTyp::Info);  
    MessageBox->writeLine(String::Concat("Accept: ",System::Convert::ToString(countItem)),CMessageForm::MessTyp::Info);  
    MessageBox->writeLine(String::Concat("Not Accept: ",System::Convert::ToString(count-countItem)),CMessageForm::MessTyp::Info);  

  }
  catch( ... )
  {
    sr->Close();
    Szenarium->clearSzenarium();
    String^ mess=nullptr;
    UpdateSzenEvent->Invoke(false);
    mess = "The file " + path + " can not be read.";
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                            __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    System::Windows::Forms::MessageBox::Show(nullptr,mess,"Error",MessageBoxButtons::OK,MessageBoxIcon::Error);
  }
}
//---------------------------------------------------------
CInterBaseManager^ CSzenariumForm::getProtoInterface(String^ interName,ArrayList^ liste)
{
  CInterBaseManager^ ret = nullptr;
  CInterBaseManager^ inter = nullptr;
  int count,i;

  i=0;
  count = liste->Count;
  while((ret == nullptr) && (i<count))
  {
    inter = safe_cast<CInterBaseManager^>(liste[i]);
    if(inter->getInterfaceName()->Equals(interName))
    {
      ret = inter;
    }
    else
    {
      i++;
    }
  }

  return ret;
}
//---------------------------------------------------------
void CSzenariumForm::setMessageBox(CMessageForm^ messBox)
{
  MessageBox = messBox;
}
//---------------------------------------------------------
void CSzenariumForm::initSzenItem(int count)
{
  Panel^ pan = nullptr;
  Button^ but = nullptr;
  Label^ lab = nullptr;
  Label^ labDeb = nullptr;
  TextBox^ txtBx = nullptr;
  SzenItemInfo^ itemInfo = nullptr;

  if(SzenItemInfoArray->Count != count)
  {
    panItemCon->Visible = false;
    panItemCon->SuspendLayout();
    panDebug->Visible = false;
    panDebug->SuspendLayout();
    clearSzenView();
    for(int i=0;i<count;i++)
    {
      itemInfo = gcnew SzenItemInfo();
      pan = gcnew Panel();
      pan->Height = 20;
      pan->BackColor = Color::FromKnownColor(KnownColor::Control);
      pan->Dock = DockStyle::Top;
      pan->BorderStyle = BorderStyle::FixedSingle;
      but = gcnew Button();
      but->Width=20;
      but->Dock = DockStyle::Left;
      but->ImageList = imageList;
      but->ImageIndex = 0;
      lab = gcnew Label();
      lab->Dock = DockStyle::Fill;
      txtBx = gcnew TextBox();
      txtBx->Dock = DockStyle::Right;
      txtBx->Width = 60;
      labDeb = gcnew Label();
      labDeb->ImageList = imageList;
      labDeb->ImageIndex = -1;
      labDeb->Dock = DockStyle::Top;
      labDeb->Height=20;
      pan->Controls->Add(lab);
      pan->Controls->Add(txtBx);
      pan->Controls->Add(but);
      panItemCon->Controls->Add(pan);
      panDebug->Controls->Add(labDeb);
      itemInfo->pan = pan;
      itemInfo->lab = lab;
      itemInfo->txtBx = txtBx;
      itemInfo->but = but;
      itemInfo->LabDebug = labDeb;
      SzenItemInfoArray->Add(itemInfo);
      lab->Tag = (count-i);
      but->Tag = (count-i);
      txtBx->Tag = (count-i);
      labDeb->Tag = (count-i);
      lab->Click += gcnew System::EventHandler(this, &CSzenariumForm::OnSzenLabelClick);
      but->Click += gcnew System::EventHandler(this, &CSzenariumForm::OnSzenButtonClick);
      labDeb->Click += gcnew System::EventHandler(this,&CSzenariumForm::OnDebugLabelClick);
      lab->ContextMenu = (PopUpMenu);
            txtBx->Validated += gcnew System::EventHandler(this, &CSzenariumForm::OnSzenValidatedTextBox);
    
      // Sortieren deaktivieren : Eingabefelder deaktivieren
      itemInfo->txtBx->Enabled=false;
    
    }
    panItemCon->ResumeLayout();
    panItemCon->Visible = true;
    panDebug->ResumeLayout();
  }
}
//---------------------------------------------------------
void CSzenariumForm::setInterConnListe(ArrayList^ liste)
{
  InterConnListe = liste;
}
//---------------------------------------------------------
void CSzenariumForm::sendSzenarium(bool sendComplet)
{
  if(butModi->Text->Equals(this->mSendMode))
  {
    DebugModus = 1;
    
    if(SendSzenThread)
    {
      String^ mess = "Szenario is sending at the moment";
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage((CLogWriterWrapper::MessTyp)2,mess,
                                                              __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      if(MessageHandler)
        MessageHandler->Invoke(mess,2);
    }
    else
    {
      //Pruefen, ob zu allen entprechenden Schnistellen die Verbindung aufgebaut ist.
      CInterSenderManager^ tmp=nullptr;
      bool ok = true;
      for (int i = 0; i<InterConnListe->Count; i++)
      {
        tmp = safe_cast <CInterSenderManager^> (InterConnListe[i]);
        if (tmp && Szenarium->TlgsFromInterInSzenario(tmp->getInterfaceName()))
        {
          if (!tmp->isConnected())
          {
            //Ausgabe
            String^ mess = String::Concat("Interface <",tmp->getInterfaceName(),"> is not connected");
            CLogWriterWrapper::getLogWriterWrapper()->WriteMessage((CLogWriterWrapper::MessTyp)2,mess,
                                                              __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
            if (MessageHandler)
              MessageHandler->Invoke(mess,2);

            ok = false;
          }
        }
      }
      if (ok)
      {
        //Folgenden Code in eigene Methode einfügen:
        System::Threading::ParameterizedThreadStart^ sendSt = gcnew System::Threading::ParameterizedThreadStart(this,&CSzenariumForm::sendTelegrams);        
        //System::Threading::ThreadStart^ sendSt = gcnew System::Threading::ThreadStart(this,&CSzenariumForm::sendTelegrams);
        SendSzenThread = gcnew System::Threading::Thread(sendSt);
        SendSzenThread->Start(sendComplet);
        SzenItemInfo^ itemInfo = nullptr;
        itemInfo = safe_cast<SzenItemInfo^>(SzenItemInfoArray[SzenItemInfoArray->Count - 1]);
        itemInfo->lab->BackColor = Color::FromKnownColor(KnownColor::Control);

        timerWatch = gcnew System::Threading::Timer( gcnew TimerCallback(this, &CSzenariumForm::SzenStatusWatcher),nullptr,500,500 );
      }
    }
  }
}
//---------------------------------------------------------
void CSzenariumForm::SzenStatusWatcher(Object^ stateInfo)
{
  if (this->StopSendSzenario)
  {
     if (SendSzenThread != nullptr)
     {
       //Ausgabe
       String^ mess = String::Concat("Thread Status :" + CFormatConverterWrapper::IntToString((int)SendSzenThread->ThreadState));
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage((CLogWriterWrapper::MessTyp)2,mess,
                                                        __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
     }
    
    if (SendSzenThread != nullptr && SendSzenThread->ThreadState == System::Threading::ThreadState::WaitSleepJoin)
      SendSzenThread->Abort();
  }
}
//---------------------------------------------------------
void CSzenariumForm::stopSendSzenarium(bool abort)
{
  if(SendSzenThread)
  {
    System::Threading::ThreadState state=SendSzenThread->ThreadState;
    this->StopSendSzenario = true;
    if(state == System::Threading::ThreadState::Suspended)
    {
      SendSzenThread->Resume();
    }
    if (abort)
      SendSzenThread->Abort();
    
    //SendSzenThread->Abort();
    //SendSzenThread=0;
    //Szenarium->setSendSzenItem(0);
    //if(panScrollBar->Visible)
    //{
    //  //Scroll wieder zum selektierten Telegramm setzen
    //  setScrollFromSelectedItem(SzenItemInfoArray->Count/2,0);
    //  showSzenFromScrollPos(); 
    //  //vScrollBar1->set_Value(vScrollBar1->Minimum());
    //  //showSzenFromScrollPos();
    //}
  }
}
//---------------------------------------------------------
void CSzenariumForm::sendCyclicTelegrams()
{
  //bool flag = true;
  //Collections::IEnumerator* iter = Szenarium->getCyclicItemTable()->get_Keys()->GetEnumerator(); 
  //iter->Reset();

  //int len;
  //char* buffer=0; 
  //unsigned char* buffer1=0;
  //String^ interName = 0;
  //CItemWrapper^ item=0;
  //CItemWrapper^ itemTemp;
  //CCyclicElemTable* elemTable = 0;
  //CTlgElemWrapper* elem = 0;
  //CCyclicElemStatus* elemStatus = 0;
  //String^ oldValue = 0;
  //String^ newValue = 0;
  //String^ elemType = 0;
  //interName = item->getInterfece();
  //double totalTime = Szenarium->getSzenItem(Szenarium->getSzenItemCount() )->getTime() - Szenarium->getSzenItem(1)->getTime();
  //  
  //Debug::Assert(totalTime >= 0);

  //Collections::SortedList* cyclicList = new Collections::SortedList();
  //Collections::ArrayList* itemList = 0;

  //while(iter->MoveNext())
  //{
  //  itemList = 0;
  //  item = safe_cast <CItemWrapper^> (iter->get_Current());
  //  
  //  if (item)
  //  {
  //    itemTemp = new CTlgWrapper();
  //    itemTemp->setTlg(item->getClonedTlg());
  //    //Number Elementen in die Liste kopieren
  //    itemList = item->createNumberElemList();
  //    elemTable = safe_cast <CCyclicElemTable*> (Szenarium->getCyclicItemTable()[item));

  //    int timeInterval = elemTable->getTimeInterval();
  //    int startTime = elemTable->getStartTime();
  //    int count = 1;

  //    while (((count*timeInterval)+startTime) <= totalTime)
  //    {
  //      //Alle nummerische Werte in Item durchlaufen
  //      for (int i=0;i<itemList->Count;i++)
  //      {
  //        elem = safe_cast <CTlgElemWrapper*>(itemList[i));
  //        elemStatus = elemTable->getElemStatus(elem);
  //        
  //        bool isChanged = true;
  //        //Elementwert herausholen
  //        elem->getElemValue(oldValue);
  //        //Type des Elemments
  //        elemType = elem->getElemType();
  //        //Wenn Interger
  //        if (elemType->Equals("Interger") || elemType->Equals("ShortInterger"))  
  //        {
  //          //int oldIntValue = CFormatConverterWrapper::StringToInt(oldValue);
  //          //int newIntValue;

  //          //CCyclicElemStatus::changeTyp changeTyp = elemStatus->getVariabel();
  //          //switch(changeTyp)
  //          //{
  //          //  plus :
  //          //    newIntValue = oldIntValue + elemStatus->getVariabelValue();
  //          //    if  (newIntValue > elemStatus->getElemLimit())
  //          //      isChanged = false;
  //          //    break;
  //          //  minus:
  //          //    newIntValue = oldIntValue - elemStatus->getVariabelValue();
  //          //    if  (newIntValue < elemStatus->getElemLimit())
  //          //      isChanged = false;
  //          //    break;
  //          //  multiple:
  //          //    newIntValue = oldIntValue * elemStatus->getVariabelValue();
  //          //    if  (newIntValue > elemStatus->getElemLimit())
  //          //      isChanged = false;
  //          //    break;
  //          //  divide:
  //          //    newIntValue = oldIntValue / elemStatus->getVariabelValue();
  //          //    if  (newIntValue < elemStatus->getElemLimit())
  //          //      isChanged = false;
  //          //    break;
  //          //  none:
  //          //    isChanged = false;
  //          //  break;
  //          //}
  //          //if (isChanged)
  //          //{
  //          //  newValue = CFormatConverterWrapper::IntToString(newIntValue);  
  //          //  //neues Elementwert setzen
  //          //  elem->setValue(newValue,interName);
  //          //}
  //        }//Wenn double oder float
  //        else if (elemType->Equals("Double") || elemType->Equals("Float"))  
  //        {
  //          //double oldDoubleValue = CFormatConverterWrapper::StringToDouble(oldValue);;
  //          //double newDoubleValue;
  //          //
  //          //CCyclicElemStatus::changeTyp changeTyp = elemStatus->getVariabel();
  //          //switch(changeTyp)
  //          //{
  //          //  plus :
  //          //    newDoubleValue = oldDoubleValue + elemStatus->getVariabelValue();
  //          //    if  (newDoubleValue > elemStatus->getElemLimit())
  //          //      isChanged = false;
  //          //    break;
  //          //  minus:
  //          //    newDoubleValue = oldDoubleValue - elemStatus->getVariabelValue();
  //          //    if  (newDoubleValue < elemStatus->getElemLimit())
  //          //      isChanged = false;
  //          //    break;
  //          //  multiple:
  //          //    newDoubleValue = oldDoubleValue * elemStatus->getVariabelValue();
  //          //    if  (newDoubleValue > elemStatus->getElemLimit())
  //          //      isChanged = false;
  //          //    break;
  //          //  divide:
  //          //    newDoubleValue = oldDoubleValue / elemStatus->getVariabelValue();
  //          //    if  (newDoubleValue < elemStatus->getElemLimit())
  //          //      isChanged = false;
  //          //    break;
  //          //  none:
  //          //    isChanged = false;
  //          //  break;
  //          //}
  //          //if (isChanged)
  //          //{
  //          //  newValue = CFormatConverterWrapper::IntToString(newDoubleValue);  
  //          //  //neues Elementwert setzen
  //          //  elem->setValue(newValue,interName);
  //          //}
  //        }
  //      }

  //      ++count;
  //      
  //      buffer = new char[itemTemp->getTlgTransBytesCount()*sizeof(char)];
  //      buffer1 = (unsigned char*)buffer;
  //      len = itemTemp->getSerializeTlg(buffer,itemTemp->getTlgTransBytesCount());
  //      //In die sortierte Liste fuers Senden hinzufuegen
  //      cyclicList->Add( __box ((count*timeInterval)+startTime),new CSzenariumForm::sendItemByteInfo(buffer1,len));

  //    }//end while time
  //  }//end if item
  //}//end durchlauf alle cyclic items
}
//---------------------------------------------------------
void CSzenariumForm::sendTelegrams(Object^ sendComplet)
{
  try
  {
   bool complet = (bool)sendComplet;

    int count;
    String^ interName = nullptr;
    CInterSenderManager^ inter = nullptr;
    CSzenItem^ item = nullptr;
    double delay;
    count = Szenarium->getSzenItemCount();
    DateTime StartTime = DateTime::Now;
    DateTime ActualTime;
    DateTime SuspendTime;
    System::TimeSpan sendDelay;
    int sendDelayAsMili;
    SzenItemInfo^ itemInfo = nullptr;
    String^ mess = nullptr;
    bool ok = true;

    CSendItemsServer^ itemsServer = CSendItemsServer::getSendItemsServer(); 
    CSendItemsServer::MessageHandlerTyp^ messHandler_ = gcnew CSendItemsServer::MessageHandlerTyp(this,&CSzenariumForm::messageHandler);
    itemsServer->setMessageHandler(messHandler_);
    
    //Delay Time aktualisieren
    if(tabCntrlTime->SelectedIndex == 0)
    {
      double del = CFormatConverterWrapper::StringToDouble(txtBxTime->Text);
      Szenarium->setSimpleDelay(del);
      showSzenarium();
    }
    else
      updateRelationDelay();
    
    
    this->StopSendSzenario = false;
    int i=1;
    long DifferentOfDelayTime = 0;
    if (!complet)
    {
      i = this->SendTelIndex;
      DifferentOfDelayTime = Szenarium->getSzenItem(this->SendTelIndex)->getDelay();
    }

    for(i;i<=count;i++)
    {
      if (!this->StopSendSzenario)
      {
        Szenarium->setSendSzenItem(i);
        //Scroll abhängig vom aktuellen SendSzen - Telegramm setzen
        setScrollFromSendedItem();
        showSzenFromScrollPos(); 

        item = Szenarium->getSzenItem(i);
        if(item->getSendStatus())
        {
          /* JOGE ******************************************************
          // now try to set actual recived values
          String *TlgName;
          TlgName = String::Concat(TlgName,item->getTlgWrapper()->getTlg()->getTlgName().c_str());
          //******************************************************/

          interName = item->getInterface();
          inter = getInterface(interName);
          
          //Normale Delay Time 
          if (!this->IgnoreDelayTimeOfUnselctedTlgs)
            delay = item->getDelay() - DifferentOfDelayTime;
          else //Delay Time ohne Delay Time der ausgeschlossenen Tlgs
            delay = item->getBarredDelay() - DifferentOfDelayTime;

          ActualTime = DateTime::Now;
   
          if(!inter->isConnected() || ((DebugModus == 1) && (item->getBreakPoint())) || (DebugModus == 2))
          {
            this->butRun->Enabled=true;
            this->buttStep->Enabled=true;
            //Falls die Connections unterbrochen ist, ausgeben
            if (!inter->isConnected())
            {
              this->buttStep->Enabled=false;
              mess = String::Concat("No connection to interface <",interName,">.");
              mess = String::Concat(mess,"Please set up the connection again and then apply to press run.");
              CLogWriterWrapper::getLogWriterWrapper()->WriteMessage((CLogWriterWrapper::MessTyp)2,mess,
                                                                      __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
              MessageHandler->Invoke(mess,2);
            }
            SendSzenThread->Suspend();
            this->butRun->Enabled=false;
            this->buttStep->Enabled=false;
            SuspendTime = DateTime::Now;
            StartTime=StartTime +(SuspendTime - ActualTime);
          }
          ActualTime = DateTime::Now;//!!!!!
          sendDelay = ActualTime - StartTime;
         
          if(DebugModus != 2)
            sendDelayAsMili = (int)(delay*1000 - sendDelay.TotalMilliseconds);
          else
            sendDelayAsMili = 0;

          if( sendDelayAsMili > 0)
            System::Threading::Thread::CurrentThread->Sleep(sendDelayAsMili);  
          
          if (this->StopSendSzenario)
            break;
          
          itemsServer->sendSzenItem(inter,item);
        }
      }
      else
        break; //For - Schleife beenden
    }
    
    Szenarium->setSendSzenItem(0);
    itemInfo = safe_cast<SzenItemInfo^>(SzenItemInfoArray[0]);
    itemInfo->lab->BackColor = Color::FromKnownColor(KnownColor::Control);
    if(panScrollBar->Visible)
    {
      //Scroll wieder zum selektierten Telegramm setzen
      setScrollFromSelectedItem(SzenItemInfoArray->Count/2,0);
      showSzenFromScrollPos(); 
    }

    if (!this->StopSendSzenario)
    {
      mess = "Sending szenario completed.";
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage((CLogWriterWrapper::MessTyp)0,mess,
                                                              __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      MessageHandler->Invoke(mess,0);
    }
    else
    {
      mess = "Sending szenario stopped.";
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage((CLogWriterWrapper::MessTyp)1,mess,
                                                            __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      MessageHandler->Invoke(mess,1);
    }
  }  
  catch(Threading::ThreadAbortException^ e)
  {
    String^ mess = "Sending szenario aborted.";
    MessageHandler->Invoke(mess,1);
    mess = String::Concat(mess,", ",e->Message);
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage((CLogWriterWrapper::MessTyp)1,mess,
                                                          __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    SendSzenThread->ResetAbort();
    SendSzenThread = nullptr;
    return;
  }
  catch (System::Exception^ e)
  {
    String^ mess = String::Concat(e->Message, " --- ",e->InnerException);
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage((CLogWriterWrapper::MessTyp)2,mess,
                                                            __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    MessageHandler->Invoke(mess,2);
    SendSzenThread = nullptr;
  }
  catch(...)
  {
    String^ mess = String::Concat(mess,"Unknown exception.");
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage((CLogWriterWrapper::MessTyp)2,mess,
                                                            __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    MessageHandler->Invoke(mess,2);
    SendSzenThread = nullptr;
  }
  
  timerWatch->~Timer();
  timerWatch = nullptr;
  SendSzenThread = nullptr;
}
//---------------------------------------------------------
void CSzenariumForm::messageHandler(String^ mess,int type)
{
  MessageHandler->Invoke(mess,type);
}
//---------------------------------------------------------
void CSzenariumForm::setMessageHandler(MessageHandlerTyp^ handler)
{
  MessageHandler = handler;
}
//---------------------------------------------------------
CInterSenderManager^ CSzenariumForm::getInterface(String^ inter)
{
    CInterSenderManager^ ret = nullptr;
    int count = InterConnListe->Count;
    bool flag = false;
    int i=0;
    CInterSenderManager^ interMan = nullptr;
    while((!flag) && (i<count))
    {
        interMan = safe_cast<CInterSenderManager^>(InterConnListe[i]);
        if(inter->Equals( interMan->getInterfaceName()))
            flag = true;
        if(!flag)
            i++;
    }
    if(flag)
       ret = interMan;
    return ret;
}
//---------------------------------------------------------
void CSzenariumForm::changeMode()
{
  if(butModi->Text->Equals(this->mEditMode))
  {
    panel2->Height=46;
    panTitel->Height=panel2->Top+panel2->Height;
    panDebug->Visible=false;
    panDebugModus->Visible = false;
    DebugModus=0;
    tabCntrlTime->Enabled = true;
    numUpDownTlg->Visible = true;
    buttTlgDown->Visible=true;
    buttTlgUp->Visible=true;
    /*buttSort->Visible=true;*/
    panDebug->Width=0;
    if(tabCntrlTime->SelectedIndex == 1)
    {
      setItemTxtBoxModus(true);
    }
    else
    {
      setItemTxtBoxModus(false);
    }
    //PopUpMenu->MenuItems[0]->Enabled=false;
    //PopUpMenu->MenuItems[1]->Enabled=true;
    //PopUpMenu->MenuItems[2]->Enabled=false;
    if(SzenariumModusEvent)
      SzenariumModusEvent->Invoke(0);

    this->stopSendSzenarium(true);
  }
  else
  {
    int count;
    double dur;
    String^ val=nullptr;
    panel2->Height=23;
    panTitel->Height=panel2->Top+panel2->Height;
    panDebug->Visible=true;
    panDebugModus->Dock = DockStyle::Fill;
    panDebugModus->Visible = true;
    DebugModus=1;
    tabCntrlTime->Enabled = false;
    numUpDownTlg->Visible = false;
    buttTlgDown->Visible=false;
    buttTlgUp->Visible=false;
    buttSort->Visible=false;
    setItemTxtBoxModus(false);

    count = Szenarium->getSzenItemCount();
    if(count>0)
    {
      dur=Szenarium->getSzenItem(count)->getDelay();
      val=CFormatConverterWrapper::DoubleToString(dur);
      CStdConverter::FormatString(val,3);
      txtBxDauer->Text = val;
    }
    panDebug->Width=16;
    //PopUpMenu->MenuItems[0]->Enabled=true;
    //PopUpMenu->MenuItems[1]->Enabled=false;
    //PopUpMenu->MenuItems[2]->Enabled=true;
    if(SzenariumModusEvent)
      SzenariumModusEvent->Invoke(1);
  }
}
//---------------------------------------------------------
void CSzenariumForm::updateRelationDelay()
{
  //TrackBar* trBr = safe_cast<TrackBar*>(sender);
  int val=0;
  double rel;
  int count;
  double dur;

  val=trackBarTime->Value;
  if(val > 0)
  {
    txtBxSimTime->Text = System::Convert::ToString(val);
    rel = (double)val;
  }
  else
  {
    if(val == 0)
    {
        txtBxSimTime->Text = System::Convert::ToString(1);
        rel = 1.0;
    }
    else
    {
        rel = (1.0/val)*(-1.0);
        txtBxSimTime->Text = CFormatConverterWrapper::DoubleToString(rel);
    }
  }

  if(Szenarium->getSzenItemCount() > 0)
  {
    String^ val=nullptr;
    Szenarium->calcDelay(rel);
    showSzenarium();
    count = Szenarium->getSzenItemCount();
    dur=Szenarium->getSzenItem(count)->getDelay();
    val=CFormatConverterWrapper::DoubleToString(dur);
    CStdConverter::FormatString(val,3);
    txtBxDauer->Text = val;
  }
}
//---------------------------------------------------------
void CSzenariumForm::setItemTxtBoxModus(bool mode)
{
  int count = SzenItemInfoArray->Count;
//  int i;
  SzenItemInfo^ item = nullptr;
  //Sortieren deaktivieren : Mode Ein/Aus deaktivieren
  /*for(i=0;i<count;i++)
  {
    item = safe_cast<SzenItemInfo*>(SzenItemInfoArray[i));
    item->txtBx->Enabled = mode;
  }*/
    numUpDownTlg->Enabled=mode;
    numericUpCopyDown->Enabled=mode;
    buttDupl->Enabled=mode;
    buttRem->Enabled=mode;
    buttTlgDown->Enabled=mode;
    buttTlgUp->Enabled=mode;
    //Sortieren deaktivieren : Mode Ein/Aus deaktivieren
    /*buttSort->Enabled=mode;*/
}
//---------------------------------------------------------
void CSzenariumForm::setSzenariumModusEvent(SzenariumModusEventTyp^ szenModus)
{
  this->SzenariumModusEvent = szenModus;
}
//---------------------------------------------------------
CItemBaseContainerWrapper^ CSzenariumForm::getSzenariumContainer()
{
    return Szenarium->getSzenariumContainer();
}
//------------------------------------------------------------
void CSzenariumForm::selectTelegram(int index)
{
  Szenarium->setFocusedItem(index); 
  setScrollFromSelectedItem(0,0);
  showSzenFromScrollPos();
  
  if(SelectItemEvent)
  {
    CItemWrapper^ tlgWr=nullptr;
    tlgWr=Szenarium->getSzenItem(index)->getTlgWrapper();
		SelectItemEvent->Invoke(tlgWr,CItemView::CreateTypForm::Szenario);
    this->EditModeUpdateToItemView();
  }
}
//------------------------------------------------------------
void CSzenariumForm::EditModeUpdateToItemView()
{
  //Edit Modus setzen
  if(SzenariumModusEvent)
  {
    if(butModi->Text->Equals(this->mEditMode))
    {
      SzenariumModusEvent->Invoke(0);
    }
    else
    {
      SzenariumModusEvent->Invoke(1);
    }
  }
}
//------------------------------------------------------------
void CSzenariumForm::updateViewTelFromScroll()
{
  int pos,max,min,activ;

  //VScrollBar* scroll = safe_cast<VScrollBar*>(sender);
  min = vScrollBar1->Minimum;
  max = Szenarium->getSzenItemCount();
  pos = vScrollBar1->Value; //NewValue;
  activ = SzenItemInfoArray->Count;

  if(pos < max - activ)
  {
    //showItemContainer(pos-1,pos-2+activ);
  }
  else
  {
    //showItemContainer(max-activ,max-1);
  }
  //if(IndexOfSendSzenItem > 0)
  //  setFocusSendItem(IndexOfSendSzenItem);
}
//------------------------------------------------------------
void CSzenariumForm::sendOneTelegram()
{
    CSzenItem^ item = nullptr;
    /*int len;*/
    String^ interName=nullptr;
    //char buffer[16384];
    char* buffer=nullptr;
    CInterSenderManager^ inter = nullptr;
    String^ mess=nullptr;
    /*unsigned char* buffer1;*/


    item = Szenarium->getSzenItem(SendTelIndex);
    interName = item->getInterface();
    inter = getInterface(interName);

    if(inter->isConnected())
    {
      CSendItemsServer^ itemsServer = CSendItemsServer::getSendItemsServer(); 
      CSendItemsServer::MessageHandlerTyp^ messHandler_ = gcnew CSendItemsServer::MessageHandlerTyp(this,&CSzenariumForm::messageHandler);
      itemsServer->setMessageHandler(messHandler_);
      
      itemsServer->sendSzenItem(inter,item);

      if (item->getIsCyclic())
      {
        if(MessageHandler)
        {
          mess = "Telegram <"+item->getItemName()+"> is cyclic.";
          if(MessageHandler)
            MessageHandler->Invoke(mess,1);
          CLogWriterWrapper::getLogWriterWrapper()->WriteMessage((CLogWriterWrapper::MessTyp)1,mess,
                                                                  __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        }
      }

      /* buffer = new char[item->getTlgTransBytesCount()*sizeof(char)];
      len = item->getSerializeTlg(buffer,item->getTlgTransBytesCount());
      buffer1 = (unsigned char*)buffer;
      inter->sendBytes(buffer1,len);
      mess = "Send Tel: ";
      mess=String::Concat(mess,item->SerializeTlgAsString());
      MessageHandler->Invoke(mess,2);
      delete buffer;*/
    }
    else
    {
        mess = String::Concat("Telegram ",item->getItemName()," was not sent (");
        mess = String::Concat(mess,"no Connection to Interface ",interName,")");
        
        if(MessageHandler)
          MessageHandler->Invoke(mess,2);
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage((CLogWriterWrapper::MessTyp)2,mess,
                                                                __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    }
    
    //SendTelIndex
}
//------------------------------------------------------------
void CSzenariumForm::setDisableFocus()
{
  SzenItemInfo^ itemInfo = nullptr;
  int count,i;
  count=SzenItemInfoArray->Count;
  bool flag=false;
  for(i=0;i<count;i++)
  {
    itemInfo = safe_cast<SzenItemInfo^>(SzenItemInfoArray[i]);
    if(itemInfo->lab->BackColor == Color::FromKnownColor(KnownColor::MediumSlateBlue))
    {
      itemInfo->lab->BackColor = Color::FromKnownColor(KnownColor::InactiveCaption);
      flag=true;
    }
  }
  SelItemColor=Color::FromKnownColor(KnownColor::InactiveCaption);
  if(!flag)
  {
    updateScrollPosition();
    showSzenFromScrollPos();
  }
}
//------------------------------------------------------------
void CSzenariumForm::setUpdateSzenEvent(UpdateSzenEventTyp^ upSzen)
{
  UpdateSzenEvent = upSzen;
}
void CSzenariumForm::setRemoveSzenarioItemFromViewTyp(RemoveSzenarioItemFromViewTyp^ eventTyp)
{
  RemoveSzenarioItemFromViewEvent = eventTyp;
}
//------------------------------------------------------------
void CSzenariumForm::updateSzenView()
{
  int count;
  double dur;
  String^ val=nullptr;
  count = Szenarium->getSzenItemCount();
  if(count>0)
  {
    dur=Szenarium->getSzenItem(count)->getDelay();
    val=CFormatConverterWrapper::DoubleToString(dur);
    CStdConverter::FormatString(val,3);
    txtBxDauer->Text = val;
  }
  else
  {
    txtBxDauer->Text = "";
  }
}
//------------------------------------------------------------
void CSzenariumForm::updateScrollPosition()
{
  int count = Szenarium->getSzenItemCount();
  int countElem = (panItemCon->Height)/20;
  int scrollPos = vScrollBar1->Value;
  if(countElem < count)
  {
    vScrollBar1->Value = (1);
    vScrollBar1->Maximum =(count-countElem);
    vScrollBar1->Minimum =(1);
    if(scrollPos > vScrollBar1->Maximum)
    scrollPos=vScrollBar1->Maximum;
    vScrollBar1->Value = (scrollPos);
    panScrollBar->Show();
  }
  else
  {
    panScrollBar->Hide();
  }
}
//------------------------------------------------------------
void CSzenariumForm::showSzenFromScrollPos()
{
  int count = Szenarium->getSzenItemCount();
  int countElem = (panItemCon->Height)/20;
  if(count > countElem)
  {
    int posScroll=vScrollBar1->Value;
    //MessageHandler->Invoke(CFormatConverterWrapper::DoubleToString(posScroll),0); //test
    initSzenItem(countElem);
    //showItemContainer(posScroll-1);
    //if(posScroll>1)
      //showItemContainer(posScroll);
    //else
    if(posScroll == vScrollBar1->Maximum)
      showItemContainer(posScroll);
    else
      showItemContainer(posScroll-1);
  }
  else
  {
    initSzenItem(count);
    showItemContainer(0);
  }
  if (SelectItemEvent && Szenarium && (Szenarium->getSzenItemCount() > 0) && (Szenarium->getFocusedItem() > 0) && !IsSendMode())
        SelectItemEvent->Invoke(Szenarium->getSzenItem(Szenarium->getFocusedItem())->getTlgWrapper(),CItemView::CreateTypForm::Szenario);
}
//------------------------------------------------------------
void CSzenariumForm::showItemContainer(int underPos)
{
  int i;
  double delay;
  String^ tlgName=nullptr;
  SzenItemInfo^ szenInfo = nullptr;
  SzenItemInfo^ szenInfo1=nullptr;
  String^ val=nullptr;
  CSzenItem^ szenItem=nullptr;
  int itemIndexSel = Szenarium->getFocusedItem();
  int itemIndexSend = Szenarium->getSendSzenItem();
  int count = SzenItemInfoArray->Count;
  itemIndexSend++;
  for(i=0;i<count;i++)
  {
    szenItem = Szenarium->getSzenItem(underPos+i+1);
    tlgName = szenItem->getItemName();
    szenInfo = safe_cast<SzenItemInfo^>(SzenItemInfoArray[count-i-1]);
    szenInfo->lab->Text = tlgName;

    if((szenItem->getChangeTimeStatus()) && (tabCntrlTime->SelectedIndex == 1))
    {
      delay = szenItem->getChangeTime();
      szenInfo->txtBx->BackColor = ChangeValueColor;
    }
    else
    {
      delay = szenItem->getDelay();
      szenInfo->txtBx->BackColor = System::Drawing::Color::White;
    }

    val=CFormatConverterWrapper::DoubleToString(delay);
    CStdConverter::FormatString(val,3);
    szenInfo->txtBx->Text = val;
    if(szenItem->getSendStatus())
    {
      szenInfo->but->ImageIndex = 0;
    }
    else
    {
      szenInfo->but->ImageIndex = 1;
    }
    if(szenItem->getBreakPoint())
    {
      szenInfo->LabDebug->ImageIndex = 1;
    }
    else
    {
      szenInfo->LabDebug->ImageIndex = -1;
    }
      szenInfo->lab->BackColor = DefaultColor;
    if((underPos+i+1 == itemIndexSel) && (itemIndexSel != 0))
    {
      szenInfo->lab->BackColor = SelItemColor;
    }
    if((underPos+i+2 == itemIndexSend) && (itemIndexSend!= 0))
    {
      if(SendSzenThread)
      {
        if(SendSzenThread->ThreadState == System::Threading::ThreadState::Running)
          szenInfo->lab->BackColor = SendItemColor;
      }
    }
  }
}
//------------------------------------------------------------
void CSzenariumForm::updateSzenFile()
{
  if(Szenarium->getSzenChangeModus())
  {
    String^ path=nullptr;
    System::Windows::Forms::DialogResult res;
    res=System::Windows::Forms::MessageBox::Show(nullptr,"Save this Szeanario ?","",MessageBoxButtons::YesNo,MessageBoxIcon::Question);
    if(res == System::Windows::Forms::DialogResult::Yes)
    {
       SaveFileDialog^ SaveSzenFileDialog = gcnew SaveFileDialog();
       SaveSzenFileDialog->Title = "Save Scenario";
       SaveSzenFileDialog->Filter = "Szenarium(*.szn)|*.szn|Szenarium(*.xml)|*.xml";
       path=Szenarium->getPath();
       if(path)
       {
        SaveSzenFileDialog->FileName = (path);
       }
       else
       {
        String^ directory=nullptr;
        CAppSetting^ Sett = CAppSetting::getApp();
				directory=Sett->getSzenDirectory();
        if(directory)
          SaveSzenFileDialog->InitialDirectory = (directory);
       }
       
       if(SaveSzenFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
       {
         String^ file=nullptr;
         file=SaveSzenFileDialog->FileName;
         if(file)
          saveSzenarium(file);
       }
    }
  }
  clearSzenView();
  Szenarium->clearSzenarium();
  panScrollBar->Hide();
  if(UpdateSzenEvent)
      UpdateSzenEvent->Invoke(false);
}
//------------------------------------------------------------
void CSzenariumForm::ShowFromDateilView()
{
    setScrollFromSelectedItem(5,1);
    showSzenFromScrollPos();
}
//------------------------------------------------------------
void CSzenariumForm::setScrollFromSelectedItem(int offset,int dir)
{
  int newPos;
  int posScroll = vScrollBar1->Value;
  int countItem = SzenItemInfoArray->Count;
  int selItem = Szenarium->getFocusedItem();
  newPos=posScroll;
  if((selItem > posScroll) && (selItem <= (posScroll+countItem)))
  {
    if(dir == 0)
    {
      if((selItem-posScroll-1) < offset )
        newPos=selItem-offset;
    }
    else
    {
      if((posScroll+countItem-selItem) <= offset)
        newPos = selItem-countItem+offset+1;
    }
  }
  else
  {
    if(dir == 0)
    {
      newPos=selItem-offset;
    }
    else
    {
      newPos=selItem-countItem+offset;
    }
  }
  if(newPos < vScrollBar1->Minimum)
  {
    newPos=vScrollBar1->Minimum;
  }
  else
  {
    if(newPos >  vScrollBar1->Maximum)
      newPos= vScrollBar1->Maximum;
  }
  vScrollBar1->Value = (newPos);
}
//------------------------------------------------------------
void CSzenariumForm::setScrollFromSendedItem()
{
  int newPos;
  ////Wert aus dem Scroll 
  //int posScroll = vScrollBar1->Value;
  //Anzahl der Telegrammen im GUI - Con.
  int countItem = SzenItemInfoArray->Count;
  //Selektiertes Telegramm im Szenarium - Con.
  int selItem = Szenarium->getSendSzenItem();

  int uBound = (selItem/countItem)*countItem;
  int oBound =uBound + countItem;

  if (selItem >= uBound && selItem < oBound)
  {
    if (selItem >= 0 && selItem < (countItem/2))
      newPos=vScrollBar1->Minimum;
    else
      newPos = selItem - countItem/2;
  }
  else if (selItem < uBound)
    newPos = selItem -1;
  else if (selItem >= oBound)
    newPos = selItem;

  if(newPos < vScrollBar1->Minimum)
  {
    newPos=vScrollBar1->Minimum;
  }
  else
  {
    if(newPos >  vScrollBar1->Maximum)
      newPos= vScrollBar1->Maximum;
  }
  vScrollBar1->Value = (newPos);
}
//------------------------------------------------------------
int CSzenariumForm::getSelSzenItem()
{
    return Szenarium->getFocusedItem();
}
//------------------------------------------------------------
void CSzenariumForm::removeInterfaceFromSzenarium(String^ inter)
{
    Szenarium->removeAllInterTlgFromSzenarium(inter);
    clearSzenView();
    updateScrollPosition();
    showSzenFromScrollPos();
    updateSzenView();
}
//------------------------------------------------------------
void CSzenariumForm::removeAllCyclicTlgInSzenario()
{   
    progressBar = gcnew CProgressBarViewForm();
    progressBar->setMinAndMax(0,Szenarium->getSzenItemCount());
    progressBar->setSourceLab(String::Concat("Remove all cyclic telegrams from szenario ..."));
    progressBar->Show();
    Szenarium->removeAllCyclicTlg();
    progressBar->Close();
    progressBar = nullptr;

    clearSzenView();
    if(Szenarium->getSzenItemCount() == 0)
    {
      if(UpdateSzenEvent)
        UpdateSzenEvent->Invoke(false);
      if (RemoveSzenarioItemFromViewEvent)
        RemoveSzenarioItemFromViewEvent->Invoke();
    }
    else
    {
      Szenarium->setFocusedItem(1);
      updateScrollPosition();
      showSzenFromScrollPos();
    }
    updateSzenView();
}
//------------------------------------------------------------
void CSzenariumForm::CompareConfigIdWithFileId (CItemWrapper^ item,CXmlInterConfigReader^ confFileReader)
{
  CAppSetting^ Sett = CAppSetting::getApp();
  String^ confPath = Sett->getInterConfigFilePath(item->getInterfece());   
  confFileReader->setInterConfigFile(confPath);     
  
  String^ elemIdName = nullptr;
  String^ tlgIdName = nullptr;
  String^ valueFromConfig = nullptr;
  String^ valueFromTlg = nullptr;
  int index = -1;

  confFileReader->setSectionFocus("TelegramId");
  valueFromConfig = confFileReader->getTlgId(item->getName());
  
  confFileReader->setSectionFocus("TelegramId");
  confFileReader->getElemIdName(tlgIdName,elemIdName);
  
  index = item->getSubElemIndex(item->getElemName(1),elemIdName);
  
  if (index > 0)
    valueFromTlg=item->getSubElemValue(1,index);
  
  //Wenn Id aus der Szenario Datei und von 
  //Konfigurationsdatei nicht uebereinstimmen
  if (valueFromTlg && !valueFromTlg->Equals(valueFromConfig))
  {
    CInterConfigWrapper^ confWr = nullptr;
    String^ mess = nullptr;
    bool flagSec = false;
       
    CXmlInterConfigWriter^ configFileWriter = gcnew  CXmlInterConfigWriter();
    configFileWriter->loadInterConfigFile(confPath);
  
    mess = "Id value of ";    
    mess = mess->Concat(mess,item->getName()," from interface configuration and from szenario file are not identity");
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage((CLogWriterWrapper::MessTyp)1,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    MessageHandler->Invoke(mess,1);
    
    flagSec = configFileWriter->setSectionFocus("TelegramId");
    if (flagSec)
    {
      configFileWriter->setTelId(item->getName(),valueFromTlg);
      mess = "Id value <";
      mess = mess->Concat(mess,valueFromTlg,"> from szenario file taked");
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage((CLogWriterWrapper::MessTyp)0,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      MessageHandler->Invoke(mess,0);
    }
    configFileWriter->endUpdate();

    //Konfigurationseinstellungen updaten
    confWr = gcnew CInterConfigWrapper();
    confWr->readInterConfigurationFile(item->getInterfece(),confPath);
  }
}
//--------------------------------------------------------------
void CSzenariumForm::getMassageFromSzenario(String^ mess)
{
  MessageHandler->Invoke(mess,0);
}
//--------------------------------------------------------------
int CSzenariumForm::getCountOfItems()
{
  return Szenarium->getSzenItemCount();
}
//--------------------------------------------------------------
bool CSzenariumForm::IsSendMode()
{
   if (butModi->Text->Equals(this->mSendMode))
     return true;
   else
     return false;
}
//--------------------------------------------------------------
bool CSzenariumForm::IsSzenarionSending()
{
  if (SendSzenThread)
    return true;
  else
    return false; 
}
//--------------------------------------------------------------
void CSzenariumForm::UpdateProgressBar(int value)
{
  if (progressBar)
    progressBar->updateStep(value);
}
//--------------------------------------------------------------
bool CSzenariumForm::TlgsFromInterInSzenario(String^ inter)
{
  if (Szenarium) 
    return Szenarium->TlgsFromInterInSzenario(inter);
  return true;
}
//---------------------------------------------------------------
void CSzenariumForm::setSzenChangeModus()
{
  if (Szenarium)
    Szenarium->setSzenChangeModus(true);
}
//---------------------------------------------------------------
System::Void CSzenariumForm::butModi_TextChanged(System::Object^  sender, System::EventArgs^  e) 
{
  changeMode();
}
//---------------------------------------------------------------
void CSzenariumForm::setIgnoreDelayTimeOfUnselctedTlgs(bool value)
{
  this->IgnoreDelayTimeOfUnselctedTlgs = value;
}