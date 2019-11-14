#include "StdAfx.h"
#include "CBofMainForm.h"
#include <windows.h>
#include "CLogWriterWrapper.h"

//-------------------------------------------------
using namespace simulator;
//--------------------------------------------------

/**CBofMainForm::CBofMainForm(Panel* parent)
 {
	InitializeComponent();
	this->TopLevel = false;
	this->Parent = parent;
	this->Dock = DockStyle::Fill;
	this->FormBorderStyle = FormBorderStyle::None;
 }**/

//--------------set- und get -Methode-----------------
//--------------------------------------------------------
Void CBofMainForm::setTlgInterface(CTlgInterfaceWrapper ^W)
{
  C_Wr = W;
}
//--------------------------------------------------------
CTlgInterfaceWrapper^ CBofMainForm::getTlgInterface()
{
  return C_Wr;
}
//--------------------------------------------------------
System::Void CBofMainForm::setInterConnectionReceive(CInterConnection ^R)
{
 C_Receiver = R;
}
//--------------------------------------------------------
CInterConnection^ CBofMainForm::getInterConnectionReceive()
{
 return C_Receiver;
}
//--------------------------------------------------------
System::Void CBofMainForm::setInterConnectionSenden(CInterConnection ^I)
{
 C_Sender = I;
}
//--------------------------------------------------------
CInterConnection^ CBofMainForm::getInterConnectionSenden()
{
  return C_Sender;
}
//--------------------------------------------------------
Void CBofMainForm::initComponent()
{
  LogWriter = CLogWriterWrapper::getLogWriterWrapper();
  C_ArrayTextBox = gcnew ArrayList();
  C_InterReceiverManList = gcnew ArrayList();
  C_Receiver = nullptr;
	C_Sender   = nullptr;
}
//--------------------------------------------------------
Void CBofMainForm::Tlgreceiven(CItemWrapper^ tlg)
{
  String^ name = nullptr;
  String^ tlgAsString = nullptr;
  int Count = 0;
  int len = 0;
  int bytesCount = 0;
  //  char buffer[1000];
  int ret = 0;
  C_interReceiverMan = gcnew CInterReceiverManager(C_Wr,C_Receiver);
}
//--------------------------------------------------------
Void CBofMainForm::Tlgsenden()
{
  try
  {
    String^ text = nullptr;
    std::string buf;
    int bytesCount;
    char* buffer = nullptr;
    //...Kodieren des Telegramm
    bytesCount = C_tlgWr->getTlgTransBytesCount();
    if(bytesCount != 1)
    {
     buffer = new char[bytesCount*sizeof(char)];
    }
    else
    {
     this->textBoxmessage->Text =("Bytescount ist -1");
    }
    C_tlgWr->getSerializeTlg(buffer,bytesCount);

    //...senden Telegramm
    if(C_Sender->isConnected())
    {
      if(C_Sender->sendByteStream((unsigned char*)buffer,bytesCount)<= 0)
      {
       this->textBoxmessage->Text =("senden ist nicht erfolgt");
      }
      else
      {
       this->textBoxmessage->Text =("senden ist erfolgt");
      }
    }
    else
    {
     this->textBoxmessage->Text =("connection failed");
    }
    delete [] buffer;
  }
  catch (System::Exception^ e)
  {
    String^ mess = e->Message;
    this->textBoxmessage->Text=mess;
    LogWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  }
}
//--------------------------------------------------------
Void CBofMainForm::maketlgbody()
{
  int count,i;
  String^ line = nullptr;
  String^ ret;
  TextBox^ txtBx = nullptr;
  String^ tlgId = nullptr;
  count = C_ArrayTextBox->Count;
  String^ s = count.ToString();

  for(i=count-1;i>=0;i--){
   txtBx = safe_cast<TextBox^>(C_ArrayTextBox[i]);
   if(i==(count-1)){
     line = String::Concat(txtBx->Text);
     tlgId = line;
   }
   else
     line = String::Concat(line,"|",txtBx->Text);
  }
  line = String::Concat(line,"|");
  C_tlgWr = C_Wr->makeTlg(C_TlgName);
  ret = C_tlgWr->fillTlg(line);
  this->textBoxmessage->Text =(ret);
  this->textBoxmessage->Text =(line);
}
//--------------------------------------------------------
System::Void CBofMainForm::onLoad(System::Object ^  sender, System::EventArgs ^  e)
{
  //ThreadStart *myThreadDelegate = new ThreadStart(this, repeat);
  //C_trd = new Thread(myThreadDelegate);
  //C_trd->IsBackground = true;
  this->TlgHeadStatusgroupBox->Visible=(false);
  this->prozessbuttonEnableF();
 }
//--------------------------------------------------------
System::Void CBofMainForm::onClosed(System::Object ^ sender,System::EventArgs ^ e)
{
    if(C_trd->IsAlive)
    C_trd->Abort();
}
//--------------------------------------------------------
System::Void CBofMainForm::onClosing(System::Object ^  sender, System::ComponentModel::CancelEventArgs ^  e)
{
    Hide();
    e->Cancel=(true);
}
//--------------------------------------------------------
System::Void CBofMainForm::startbutton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
   C_prozessIndex = 0;
   textBox14->Text =("trd erzeugt");
   ThreadStart ^myThreadDelegate = gcnew ThreadStart(this, &CBofMainForm::repeat);
   C_trd = gcnew Thread(myThreadDelegate);
   C_trd->IsBackground = true;
   C_trd->Start();  
   getled(1)->Status = true;
}
//--------------------------------------------------------
System::Void CBofMainForm::stopbutton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
   if (C_trd->IsAlive)
   {
    C_trd->Suspend();
    textBox14->Text = "ist Stop";
   }
}
//--------------------------------------------------------
System::Void CBofMainForm::weiterbutton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
   if (C_trd->IsAlive)
     C_trd->Resume();
}
//--------------------------------------------------------
System::Void CBofMainForm::sendeTlgnbutton_Click(System::Object ^  sender, System::EventArgs ^  e)
{
if(Flag == 0)
  timer1->Enabled = true;
else
  timer1->Enabled = false; 
}
//--------------------------------------------------------
System::Void CBofMainForm::Sendbutton_Click(System::Object ^  sender, System::EventArgs ^  e)
{
  this->initgroupboxF();
  if(TlgHeadStatusgroupBox->Visible==false)
  HeatStahide();
  prozessbuttonEnableT();
  this->label52->Text = "Telegramm senden";
  this->startbutton->Enabled = false;
  this->stopbutton->Enabled = false;
  this->weiterbutton->Enabled = false;
}
//--------------------------------------------------------
System::Void CBofMainForm::Receivenbutton_Click(System::Object ^  sender, System::EventArgs ^  e)
{
  this->initgroupboxT();
   if(TlgHeadStatusgroupBox->Visible==false)
   HeatStahide();
   this->label52->Text = "Telegramm receiven";
   prozessbuttonEnableF();
   this->startbutton->Enabled = true;
   this->stopbutton->Enabled = true;
   this->weiterbutton->Enabled = true;
}
//--------------------------------------------------------
System::Void CBofMainForm::TlgHeadbutton_Click(System::Object ^  sender, System::EventArgs ^  e)
{
  if (HeadStaFlag == 0){
    HeadStaFlag = 1;
    this->TlgHeadStatusgroupBox->Visible =(true);
    HeatStadisplay();
    }
  else if(HeadStaFlag == 1){
    HeadStaFlag = 0;
    this->TlgHeadStatusgroupBox->Visible =(false);
     HeatStahide();
   }
}
//--------------------------------------------------------
System::Void CBofMainForm::buttonMakeTlg_Click(System::Object ^  sender, System::EventArgs ^  e)
{
  try
  {
    maketlgbody();
  }
  catch (System::Exception^ e)
  {
    String^ mess = e->Message;
    this->textBoxmessage->Text=mess;
    LogWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  }
}
//--------------------------------------------------------
System::Void CBofMainForm::timer_Elapsed(System::Object ^  sender, System::Timers::ElapsedEventArgs ^  e)
{
 String^ xc = gcnew String(".\\Animation\\");
 String^ xc1 = gcnew String("\\");
 //...imageflag fangt von 1 an
 C_imageIndex++;
 //...fill complete Image name
 C_imagename = String::Concat(C_Pname,C_imageIndex.ToString(),".gif");
 //...directory von entsprechendes Image
 xc = String::Concat(xc,C_Pname,xc1,C_imagename);
 //...Suchen ob das Image existiert ist
 C_filename = stringtochar(xc);
 file_exists(C_filename)?  C_obfileexsit=1 : C_obfileexsit=0;
 if(C_obfileexsit == 1)
   {
     C_image = Image::FromFile(xc);
     pictureBox1->Image = (C_image);
     Tlgsenden();
     String^ T = String::Concat(C_Pname,"Tlg",C_TlgName,C_imageIndex.ToString());
     textBox14->Text =(T);
   }
 else
  {
    String^ S = String::Concat("Proces",C_Pname,"ist fertig");
    textBox14->Text =(S);
    Flag = 1;
  }
}
//--------------------------------------------------------
Void CBofMainForm::ThreadTask()
{
   C_Pname = p[C_prozessIndex];
   //...imageflag fangt von 1 an
   C_imageIndex++;
   //...fill complete Image name
   C_imagename = String::Concat(C_Pname,C_imageIndex.ToString(),".gif");
   //...directory von entsprechendes Image
   String^ xc = gcnew String(".\\Animation\\");
   String^ xc1 = gcnew String("\\");
   xc = String::Concat(xc,C_Pname,xc1,C_imagename);
   //...Suchen ob das Image existiert ist
   C_filename = stringtochar(xc);
   file_exists(C_filename)?  C_obfileexsit=1 : C_obfileexsit=0;
   if(C_obfileexsit == 1)
   {
     //textBox14->Text =(String::Concat("dirctory ist",C_xc));
     textBox14->Text =(C_Pname);
     C_image = Image::FromFile(xc);
     pictureBox1->Image = (C_image);
   }
    else
   {
     getled(C_prozessIndex+1)->Status = false;
     C_prozessIndex++;
     C_imageIndex = 0;
     getled(C_prozessIndex+1)->Status = true;
   }
}
//--------------------------------------------------------
Void CBofMainForm::repeat()
{
  while(true)
 {
  ThreadTask();
  Thread::Sleep(1000);
 }
}
//--------------------------------------------------------
int CBofMainForm::file_exists(char  *filename)
{
  return   (access(filename,   0)   ==   0);   
}
//--------------------------------------------------------
char* CBofMainForm::stringtochar(String ^str)
{
  IntPtr sptr = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(str);
  void* stemp = sptr.ToPointer();
  char* cc = static_cast<char*>(stemp);
  return cc;
}
//--------------------------------------------------------
L1SimulatorControls::Led ^ CBofMainForm::getled(int i)
{
  if(i==1) return led1;
  if(i==2) return led2; 
  if(i==3) return led3;
  if(i==4) return led4;
  if(i==5) return led5;
  if(i==6) return led6;
  if(i==7) return led7;
  if(i==8) return led8;
  if(i==9) return led9;
  if(i==10) return led10;
  if(i==11) return led11;
  if(i==12) return led12;
  if(i==13) return led13;
  if(i==14) return led14;
  if(i==15) return led15;
  if(i==16) return led16;
  if(i==17) return led17;
}
//--------------------------------------------------------
//...1.Prozess Heat Announce
System::Void CBofMainForm::buttonHA_Click(System::Object ^  sender, System::EventArgs ^  e)
{
 initgroupboxF();
 textBoxMsgID->Text = "BOL206";
 textBoxMsgID->Enabled = false;
 textBoxBlen->Text = "50";
 textBoxBlen->Enabled = false;
}
//--------------------------------------------------------
//...2.Converter in up Position
System::Void CBofMainForm::buttonCIP_Click(System::Object ^  sender, System::EventArgs ^  e)
{
 initgroupboxF();
 textBoxMsgID->Text = "BOL214";
 textBoxMsgID->Enabled = false;
 textBoxBlen->Text = "58";
 textBoxBlen->Enabled = false;
}
//--------------------------------------------------------
//...3.Scrap Charging
System::Void CBofMainForm::buttonSC_Click(System::Object ^  sender, System::EventArgs ^  e)
{
 initgroupboxF();
 textBoxMsgID->Text = "BOL214";
 textBoxMsgID->Enabled = false;
 textBoxBlen->Text = "58";
 textBoxBlen->Enabled = false;
}
//--------------------------------------------------------
//...4.Stirring Start????
System::Void CBofMainForm::buttonSS_Click(System::Object ^  sender, System::EventArgs ^  e)
{
 initgroupboxF();
 textBoxMsgID->Text = "BOL214";
 textBoxMsgID->Enabled = false;
 textBoxBlen->Text = "58";
 textBoxBlen->Enabled = false;
}
//--------------------------------------------------------
//...5.Prozess Hot Metal Charging
System::Void CBofMainForm::button5_Click(System::Object ^  sender, System::EventArgs ^  e)
{
  if(HeatgroupBox->Visible == true)
   HMCgroupBox->Location = System::Drawing::Point(0,192);
  else 
   HMCgroupBox->Location = System::Drawing::Point(0,184);
  this->HMCgroupBox->Visible =(true);
  this->FreespacegroupBox->Visible =(true);
  this->textBoxFreespare1->Enabled = false;
  //...Head fuellen
  textBoxMsgID->Text = "BOL271";
  textBoxMsgID->Enabled = false;
  textBoxBlen->Text = "62";
  textBoxBlen->Enabled = false;
  //..Tlg init
  C_Pname = "HMC";
  C_TlgName = "BOL271";
  C_TlgBody = "";
  C_ArrayTextBox->Clear();
  C_ArrayTextBox->Add(textBoxFreespare5);
  C_ArrayTextBox->Add(textBoxFreespare4);
  C_ArrayTextBox->Add(textBoxFreespare3);
  C_ArrayTextBox->Add(textBoxFreespare2);
  C_ArrayTextBox->Add(textBoxHMLocation);
  C_ArrayTextBox->Add(textBoxMatWgt);
  C_ArrayTextBox->Add(textBoxWgtstat);
  C_ArrayTextBox->Add(textBoxLDINo);
  C_ArrayTextBox->Add(textBoxRetreatID);
  C_ArrayTextBox->Add(textBoxHeatNo);
  C_ArrayTextBox->Add(textBoxTime);
  C_ArrayTextBox->Add(textBoxDate);
  C_ArrayTextBox->Add(textBoxPlantID);
  C_ArrayTextBox->Add(textBoxProductID);
  C_ArrayTextBox->Add(textBoxReserve);
  C_ArrayTextBox->Add(textBoxBlen);
  C_ArrayTextBox->Add(textBoxOrg);
  C_ArrayTextBox->Add(textBoxCreaTime);
  C_ArrayTextBox->Add(textBoxCreaDate);
  C_ArrayTextBox->Add(textBoxMsgID);
}
//--------------------------------------------------------
//...6.Heat Start
System::Void CBofMainForm::buttonHS_Click(System::Object ^  sender, System::EventArgs ^  e)
{
 initgroupboxF();
 textBoxMsgID->Text = "BOL204";
 textBoxMsgID->Enabled = false;
 textBoxBlen->Text = "50";
 textBoxBlen->Enabled = false;
}
//--------------------------------------------------------
//...7.Lance down
System::Void CBofMainForm::buttonLD_Click(System::Object ^  sender, System::EventArgs ^  e)
{
 initgroupboxF();
 textBoxMsgID->Text = "BOL221";
 textBoxMsgID->Enabled = false;
 textBoxBlen->Text = "62";
 textBoxBlen->Enabled = false;
}
//--------------------------------------------------------
//...8.Blow start
System::Void CBofMainForm::buttonBS_Click(System::Object ^  sender, System::EventArgs ^  e)
{
 initgroupboxF();
 textBoxMsgID->Text = "BOL221";
 textBoxMsgID->Enabled = false;
 textBoxBlen->Text = "62";
 textBoxBlen->Enabled = false;
}
//--------------------------------------------------------
//...9.Blow End
System::Void CBofMainForm::buttonBE_Click(System::Object ^  sender, System::EventArgs ^  e)
{
 initgroupboxF();
 textBoxMsgID->Text = "BOL221";
 textBoxMsgID->Enabled = false;
 textBoxBlen->Text = "62";
 textBoxBlen->Enabled = false;
}
//--------------------------------------------------------
//...10.Temperatur Measurement
System::Void CBofMainForm::buttonTM_Click(System::Object ^  sender, System::EventArgs ^  e)
{
 initgroupboxF();
 textBoxMsgID->Text = "BOL221";
 textBoxMsgID->Enabled = false;
 textBoxBlen->Text = "62";
 textBoxBlen->Enabled = false;
}
//--------------------------------------------------------
//...11.Reblow start
System::Void CBofMainForm::buttonRS_Click(System::Object ^  sender, System::EventArgs ^  e)
{
 initgroupboxF();
 textBoxMsgID->Text = "BOL221";
 textBoxMsgID->Enabled = false;
 textBoxBlen->Text = "62";
 textBoxBlen->Enabled = false;
}
//--------------------------------------------------------
//...12.Reblow end
System::Void CBofMainForm::buttonRE_Click(System::Object ^  sender, System::EventArgs ^  e)
{
 initgroupboxF();
 textBoxMsgID->Text = "BOL221";
 textBoxMsgID->Enabled = false;
 textBoxBlen->Text = "62";
 textBoxBlen->Enabled = false;
}
//--------------------------------------------------------
//...13.Lance Up
System::Void CBofMainForm::buttonLU_Click(System::Object ^  sender, System::EventArgs ^  e)
{
 initgroupboxF();
 textBoxMsgID->Text = "BOL221";
 textBoxMsgID->Enabled = false;
 textBoxBlen->Text = "62";
 textBoxBlen->Enabled = false;
}
//--------------------------------------------------------
//...14.Tapping start
System::Void CBofMainForm::buttonTS_Click(System::Object ^  sender, System::EventArgs ^  e)
{
 initgroupboxF();
 textBoxMsgID->Text = "BOL221";
 textBoxMsgID->Enabled = false;
 textBoxBlen->Text = "62";
 textBoxBlen->Enabled = false;
}
//--------------------------------------------------------
//...15.Tapping end
System::Void CBofMainForm::buttonTE_Click(System::Object ^  sender, System::EventArgs ^  e)
{
 initgroupboxF();
 textBoxMsgID->Text = "BOL221";
 textBoxMsgID->Enabled = false;
 textBoxBlen->Text = "62";
 textBoxBlen->Enabled = false;
}
//--------------------------------------------------------
//...16.Delslag start
System::Void CBofMainForm::buttonDS_Click(System::Object ^  sender, System::EventArgs ^  e)
{
 initgroupboxF();
 textBoxMsgID->Text = "BOL221";
 textBoxMsgID->Enabled = false;
 textBoxBlen->Text = "62";
 textBoxBlen->Enabled = false;
}
//--------------------------------------------------------
//...17.Delslag end
System::Void CBofMainForm::buttonDE_Click(System::Object ^  sender, System::EventArgs ^  e)
{
 initgroupboxF();
 textBoxMsgID->Text = "BOL221";
 textBoxMsgID->Enabled = false;
 textBoxBlen->Text = "62";
 textBoxBlen->Enabled = false;
}
//--------------------------------------------------------
//...18.Stirring end
System::Void CBofMainForm::buttonSE_Click(System::Object ^  sender, System::EventArgs ^  e)
{
 initgroupboxF();
 textBoxMsgID->Text = "BOL221";
 textBoxMsgID->Enabled = false;
 textBoxBlen->Text = "62";
 textBoxBlen->Enabled = false;
}
//--------------------------------------------------------
Void CBofMainForm::initgroupboxF()
{
 this->GasModelgroupBox->Visible =(false);
 this->WaterGasgroupBox->Visible =(false);
 this->GasStatusgroupBox->Visible =(false);
 this->LanceStatusgroupBox->Visible =(false);
 this->ConposgroupBox->Visible =(false);
 this->labellancehigh->Visible =(false);
 this->textBoxlancehigh->Visible =(false);
 this->HMCgroupBox->Visible =(false);
 this->TappinggroupBox->Visible =(false);
 this->DeslagginggroupBox->Visible =(false);
 this->TappinggroupBox->Visible =(false);
 this->BlowStartgroupBox->Visible =(false);
 this->lanceblowstatusgroupBox->Visible =(false);
 this->ReadyforBlowgroupBox->Visible =(false);
 this->SampleTakengroupBox->Visible =(false);
 this->TlgHeadStatusgroupBox->Visible =(false);
 this->FreespacegroupBox->Visible =(false);
}
//--------------------------------------------------------
Void CBofMainForm::initgroupboxT()
{
 this->GasModelgroupBox->Visible =(true);
 this->WaterGasgroupBox->Visible =(true);
 this->GasStatusgroupBox->Visible =(true);
 this->LanceStatusgroupBox->Visible =(true);
 this->ConposgroupBox->Visible =(true);
 this->labellancehigh->Visible =(true);
 this->textBoxlancehigh->Visible =(true);
 this->HMCgroupBox->Visible =(true);
 this->TappinggroupBox->Visible =(true);
 this->DeslagginggroupBox->Visible =(true);
 this->TappinggroupBox->Visible =(true);
 this->BlowStartgroupBox->Visible =(true);
 this->lanceblowstatusgroupBox->Visible =(true);
 this->ReadyforBlowgroupBox->Visible =(true);
 this->SampleTakengroupBox->Visible =(true);
 this->FreespacegroupBox->Visible =(true);
 this->TlgHeadStatusgroupBox->Visible =(false);
}
//--------------------------------------------------------
Void CBofMainForm::HeatStahide()
{
    this->HeatgroupBox->Location = Point(0,32);
    this->ReadyforBlowgroupBox->Location = System::Drawing::Point(0,104);
    this->LanceStatusgroupBox->Location = System::Drawing::Point(176,104);
    this->HMCgroupBox->Location = System::Drawing::Point(0,184);
    this->ConposgroupBox->Location = System::Drawing::Point(176,208);
    this->lanceblowstatusgroupBox->Location = System::Drawing::Point(0,304);
    this->BlowStartgroupBox->Location = System::Drawing::Point(176,296);
}
//--------------------------------------------------------
Void CBofMainForm::HeatStadisplay()
{
    this->HeatgroupBox->Location = System::Drawing::Point(0,152);
    this->ReadyforBlowgroupBox->Location = System::Drawing::Point(0,224);
    this->LanceStatusgroupBox->Location = System::Drawing::Point(176,224);
    this->HMCgroupBox->Location = System::Drawing::Point(0,304);
    this->ConposgroupBox->Location = System::Drawing::Point(176,304);
    this->lanceblowstatusgroupBox->Location = System::Drawing::Point(0,424);
    this->BlowStartgroupBox->Location = System::Drawing::Point(176,416);
}
//--------------------------------------------------------
Void CBofMainForm::prozessbuttonEnableF()
{
  this->buttonHA->Enabled = false;
  this->buttonCIP->Enabled = false;
  this->buttonSC->Enabled = false;
  this->buttonSS->Enabled = false;
  this->button5->Enabled = false;
  this->buttonHS->Enabled = false;
  this->buttonLD->Enabled = false;
  this->buttonBS->Enabled = false;
  this->buttonBE->Enabled = false;
  this->buttonTM->Enabled = false;
  this->buttonRS->Enabled = false;
  this->buttonRE->Enabled = false;
  this->buttonLU->Enabled = false;
  this->buttonTS->Enabled = false;
  this->buttonTE->Enabled = false;
  this->buttonDS->Enabled = false;
  this->buttonDE->Enabled = false;
  this->buttonSE->Enabled = false;
}
//--------------------------------------------------------
Void CBofMainForm::prozessbuttonEnableT()
{
  this->buttonHA->Enabled = true;
  this->buttonCIP->Enabled = true;
  this->buttonSC->Enabled = true;
  this->buttonSS->Enabled = true;
  this->button5->Enabled = true;
  this->buttonHS->Enabled = true;
  this->buttonLD->Enabled = true;
  this->buttonBS->Enabled = true;
  this->buttonBE->Enabled = true;
  this->buttonTM->Enabled = true;
  this->buttonRS->Enabled = true;
  this->buttonRE->Enabled = true;
  this->buttonLU->Enabled = true;
  this->buttonTS->Enabled = true;
  this->buttonTE->Enabled = true;
  this->buttonDS->Enabled = true;
  this->buttonDE->Enabled = true;
  this->buttonSE->Enabled = true;
}