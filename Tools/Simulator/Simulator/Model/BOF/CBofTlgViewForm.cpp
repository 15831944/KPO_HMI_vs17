#include "StdAfx.h"
#include "CBofTlgViewForm.h"

//-----------------------------------------------
using namespace simulator;
//-----------------------------------------------

CBofTlgViewForm::CBofTlgViewForm(Panel^ parent){
 InitializeComponent();
  this->TopLevel = false;
  this->Parent = parent;
  this->Dock = DockStyle::Fill;
	this->FormBorderStyle = ::FormBorderStyle::None;
}

void CBofTlgViewForm::showTlg(CItemWrapper^ tlg){
  ShowTlgEvent^ addnewelment = gcnew ShowTlgEvent(this,&CBofTlgViewForm::addnewpanel);
  Tlg = tlg;
  String^ lenIdTyp=nullptr;
  String^ interName=Tlg->getInterfece();
  CInterConfigWrapper^ interConf = gcnew CInterConfigWrapper();
  TlgId = interConf->getTlgIdName(interName);
  TlgElemId = interConf->getElemId(interName);
  TlgLenId = interConf->getElemLenId(interName);
  TlgIdValue=interConf->getTlgId(interName,Tlg->getName());
  LenIdModus=interConf->getLenIdTreatModus(interName);
  this->panelbody->Invoke(addnewelment);
}

void CBofTlgViewForm::addnewpanel(){
 try{ 
  int count;
  int elemTyp;
  int len;
  TextBox^ txtBx;
  array <String^>^ elemArrStr = nullptr;
  Panel^ panElem = nullptr;
  String^ elemDescr=nullptr;
  String^ transTyp=nullptr;
  String^ unit=nullptr;
  String^ factor=nullptr; 
  String^ min=nullptr;
  String^ max=nullptr;
  String^ elemName=nullptr;
  String^ val=nullptr;
  String^ lenStr=nullptr;
  String^ typ=nullptr;
  
  this->UpdateFlag = false;
  //if(panCon != nullptr)
  //  panCon->Dispose();
  if(panCon != nullptr)
    delete panCon;
  panCon = gcnew Panel();
  TxtBoxArray = gcnew ArrayList();

  this->panelbody->Controls->Add(panCon);
  panCon->Visible = false;
  panCon->SuspendLayout();
  this->labelTlgName->Text = Tlg->getName();
  this->labelTlgDescr->Text = Tlg->getTlgDescr();
  TxtBoxArray->Clear();
  count = Tlg->getTlgElemCount();
       for(int i = count;i>=1;i--){
            panElem = gcnew Panel();
            panElem->SuspendLayout();
            panCon->Controls->Add(panElem);
            panElem->Dock = DockStyle::Top;
            panElem->Height = 20;
            elemTyp = Tlg->getElemTyp(i);
            Tlg->getElementDescr(i,elemDescr,transTyp,unit,factor,min,max);
            typ = Tlg->getElemTypAsString(i);
            elemName = Tlg->getElemName(i);
            val=Tlg->getElemValue(i);
            len=Tlg->getElemLen(i);
            lenStr = System::Convert::ToString(len);
            panElem->Visible=false;
            this->addTlgelement(elemName,val,unit,panElem);
            panElem->ResumeLayout();
            panElem->Visible=true;
       }
       count = TxtBoxArray->Count;
       panCon->Left = 0;
       panCon->Top = 20;
       panCon->Width = panelbody->Width;
       panCon->ResumeLayout();
       if(panCon->Controls->Count>0){
         panCon->Height=panCon->Controls[0]->Top+panCon->Controls[0]->Top+10;
       }
       panCon->Visible = true;
       for(int i=0;i<count;i++){
        txtBx = safe_cast<TextBox^>(TxtBoxArray[i]);
        txtBx->Tag = System::Convert::ToString(i);
        txtBx->Enter += gcnew System::EventHandler(this, &CBofTlgViewForm::OnEnterTextBox);
        txtBx->Leave += gcnew System::EventHandler(this, &CBofTlgViewForm::OnLeaveTextBox);
       }
       UpdateFlag=true;
       panelbody->Show();
       } 
       catch(System::Exception^ e){
       String^ test=nullptr;

       test = e->ToString();
       UpdateFlag=true;
      }
}

void CBofTlgViewForm::addTlgelement(String^& Name,String^& Val,String^& Unit,Panel^ panElem){
  TextBox^ txtBx;
  Label^ lab; 
  //setBaseTlgElemView(descr,max,min,factor,trans,typ,len,unit,panElem,modi);
  txtBx = gcnew TextBox();
  panElem->Controls->Add(txtBx);
  TxtBoxArray->Add(txtBx);
  txtBx->Dock = DockStyle::Left;
  txtBx->Width = 91;
  txtBx->Text = Val;
  if((Name->Equals(TlgElemId)) || (Name->Equals(TlgLenId)))
  {
    if(Name->Equals(TlgElemId))
    {
      txtBx->Text = TlgIdValue;
      txtBx->Enabled = false;
    }
    if(Name->Equals(TlgLenId))
    {
            if(!LenChange)
            {
          if(LenIdModus == 1)
          {
            txtBx->Enabled = false;
            txtBx->Text = System::Convert::ToString(Tlg->getTlgTransBytesCount());
          }
          if(LenIdModus == 2)
          {
            txtBx->Enabled = false;
            txtBx->Text = System::Convert::ToString(Tlg->getTlgBodyTransBytesCount());
          }
          if(LenIdModus == 3)
          {
            txtBx->Enabled = true;
          }
            }
            else
            {
                txtBx->Enabled = true;
            }
      TlgLenTxtBx=txtBx;
    }
  }
  lab = gcnew Label();
  panElem->Controls->Add(lab);
  lab->Dock = DockStyle::Left;
  lab->Width = 131;
  lab->BorderStyle = BorderStyle::FixedSingle;
  lab->Text = Name;
  lab->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
}

System::Void CBofTlgViewForm::OnEnterTextBox(System::Object ^  sender, System::EventArgs ^  e)
{
  TextBox^ txtBx=nullptr;

  txtBx = safe_cast<TextBox^>(sender);
  ActTextBox = System::Convert::ToInt32(txtBx->Tag);
  NavModi = true;
    //if(telelemediteve)
      //  telelemediteve->Invoke();
}
//------------------------------------------------
System::Void CBofTlgViewForm::OnLeaveTextBox(System::Object ^  sender, System::EventArgs ^  e)
{
   NavModi=false;
}