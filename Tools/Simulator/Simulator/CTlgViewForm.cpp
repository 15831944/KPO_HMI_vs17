#include "StdAfx.h"
#include "CTlgViewForm.h"

//-------------------------------------------------
using namespace simulator;
//--------------------------------------------------
CTlgViewForm::CTlgViewForm(Panel^ parent)
{
  InitializeComponent();
  this->TopLevel = false;
  this->Parent = parent;
  this->Dock = DockStyle::Fill;
	this->FormBorderStyle = ::FormBorderStyle::None;
  FlagShowModi=0;
  TxtBoxArray = gcnew ArrayList();
  UpdateFlag=true;
  PanFlag=0;
  DelAddTlg=nullptr;
  DelUpTlg=nullptr;
  panCon=nullptr;
  ErrorMessageDel=nullptr;
  TlgLenTxtBx=nullptr;
  TelElemEditEvent=nullptr;
  LenChange=false;
}
//------------------------------------------------
System::Void CTlgViewForm::OnLabelHeaderClick(System::Object ^  sender, System::EventArgs ^  e)
{
  Label^ lab = safe_cast<Label^>(sender);
  Panel^ pan=nullptr;
  System::Windows::Forms::Control^ panTemp=nullptr;
  System::Windows::Forms::Control^ panTemp1=nullptr;
  System::Windows::Forms::Control^ panTemp2=nullptr;
  
  int count;
  lab->ImageIndex = (lab->ImageIndex+1)%2;
  FlagShowModi=lab->ImageIndex;
  pan = safe_cast<Panel^>(lab->Parent->Parent);

  if(lab->ImageIndex == 0)
  {
    pan->Height=20;
  }
  else
  {
    count=pan->Controls->Count;
    pan->Height = (20*count);

    for (int i=0;i<count;i++)
    {
      panTemp=pan->Controls[i];
      if (panTemp->Controls->Count>7)
      {
        panTemp1=panTemp->Controls[8];
        if (panTemp1->Controls->Count>0)
        {
          panTemp2 = panTemp1->Controls[0];
         
          /*pan->Height += (panTemp2->Controls->Count-2)*20;*/
          pan->Height += panTemp1->Height - 20;
        }
      }
    }

  }
  if(panCon->Controls->Count>0)
  {
    panCon->Height=panCon->Controls[0]->Top+panCon->Controls[0]->Top+10;
  }
}
//------------------------------------------------
System::Void CTlgViewForm::OnAddButtonClick(System::Object ^  sender, System::EventArgs ^  e)
{
  int count,i;
  String^ line=nullptr;
  TextBox^ txtBx=nullptr;
  CItemWrapper^ tlgWr=nullptr;
  String^ tlgId=nullptr;

	count= TxtBoxArray->Count;
  for(i=count-1;i>=0;i--)
  {
    txtBx = safe_cast<TextBox^>(TxtBoxArray[i]);
    if(i == (count-1))
    {
      line = String::Concat(txtBx->Text);
      tlgId = line;
    }
    else
      line = String::Concat(line,"|",txtBx->Text);
  }
  line = String::Concat(line,"|");
  if(DelAddTlg != nullptr)
  {
    String^ Error=nullptr;
    tlgWr=Tlg->clone();
    Error=tlgWr->fillTlg(line);
    if(Error == nullptr)
    {
      DelAddTlg->Invoke(tlgWr,false);
    }
    else
    {
      if(ErrorMessageDel)
      {
        ErrorMessageDel->Invoke(Error);
      }
    }
  }
//  Szen->addToSzenarium(tlgWr);
  //Szen
  txtBxByteValue->Text = line;
}
//------------------------------------------------
System::Void CTlgViewForm::OnButtUpdateClick(System::Object ^  sender, System::EventArgs ^  e)
{
  int count,i;
  String^ line=nullptr;
  TextBox^ txtBx=nullptr;
  CItemWrapper^ tlgWr=nullptr;
  String^ tlgId=nullptr;
  String^ Error = nullptr;

  count=TxtBoxArray->Count;
  for(i=count-1;i>=0;i--)
  {
    txtBx = safe_cast<TextBox^>(TxtBoxArray[i]);
    if(i == (count-1))
    {
      line = String::Concat(txtBx->Text);
      tlgId = line;
    }
    else
      line = String::Concat(line,"|",txtBx->Text);
        
  }
  line = String::Concat(line,"|");
  if(DelUpTlg != nullptr)
  {
    String^ Error=nullptr;
    tlgWr=Tlg->clone();
    Error=tlgWr->fillTlg(line);
    if(Error == nullptr)
    {
      DelUpTlg->Invoke(tlgWr);
      showTlg(tlgWr);
    }
    else
    {
      if(ErrorMessageDel)
      {
        ErrorMessageDel->Invoke(Error);
      }
    }
  }
  
  txtBxByteValue->Text = line;
}
//------------------------------------------------
System::Void CTlgViewForm::OnKeyFormDown(System::Object ^  sender, System::Windows::Forms::KeyEventArgs ^  e)
{
  TextBox^ txtBx=nullptr;
  Keys key;
  key=e->KeyCode;
  //if((ActTextBox >0) && (ActTextBox < TxtBoxArray->Count-1))
  if(NavModi)
  {
    if(key == Keys::Down)
    {
      if(ActTextBox >0)
         ActTextBox--;
    }
    if(key == Keys::Up)
    {
       if(ActTextBox < TxtBoxArray->Count-1)
          ActTextBox++;
    }
  
  txtBx = safe_cast<TextBox^>(TxtBoxArray[ActTextBox]);
  txtBx->Focus();
  }
}
//------------------------------------------------
System::Void CTlgViewForm::OnEnterTextBox(System::Object ^  sender, System::EventArgs ^  e)
{
  TextBox^ txtBx=nullptr;

  txtBx = safe_cast<TextBox^>(sender);
  ActTextBox = System::Convert::ToInt32(txtBx->Tag);
  NavModi = true;
  if(TelElemEditEvent)
      TelElemEditEvent->Invoke();
}
//------------------------------------------------
System::Void CTlgViewForm::OnLeaveTextBox(System::Object ^  sender, System::EventArgs ^  e)
{
   NavModi=false;
}
//------------------------------------------------
System::Void CTlgViewForm::OnLayout(System::Object ^  sender, System::Windows::Forms::LayoutEventArgs ^  e)
{
  if(panCon)
    panCon->Width = panBody->Width;
}
//------------------------------------------------
/*System::Void CTlgViewForm::OnRadButtClick(System::Object *  sender, System::EventArgs *  e)
{
  if(TlgLenTxtBx)
  {
    RadioButton* radButt = safe_cast<RadioButton*>(sender);
    if(radButt == radButtBodyLenght)
    {
      TlgLenTxtBx->Enabled=false;
      TlgLenTxtBx->Text = System::Convert::ToString(Tlg->getTlgBodyLen());
    }
    if(radButt == radButtWithHeader)
    {
      TlgLenTxtBx->Enabled=false;
      TlgLenTxtBx->Text = System::Convert::ToString(Tlg->getTlgLen());
    }
    if(radButt == radButtUserDefined)
    {
      TlgLenTxtBx->Enabled=true;
    }
  }
}*/
//------------------------------------------------
void CTlgViewForm::showTlg(CItemWrapper^ tlg)
{
  DelShowTlgView^ addNewCon = gcnew DelShowTlgView(this,&CTlgViewForm::addNewPanel);
  Tlg=tlg;
  String^ lenIdTyp=nullptr;
  String^ interName=Tlg->getInterfece();
  CInterConfigWrapper^ interConf = gcnew CInterConfigWrapper();
  TlgId = interConf->getTlgIdName(interName);
  TlgElemId = interConf->getElemId(interName);
  TlgLenId = interConf->getElemLenId(interName);
  TlgIdValue=interConf->getTlgId(interName,Tlg->getName());
  LenIdModus=interConf->getLenIdTreatModus(interName);
  panBody->Invoke(addNewCon);
}
//--------------------------------------------------------------------
void CTlgViewForm::addSimpleTlgElem(String^& Name,String^& val,String^& descr,String^& len,String^& typ,String^& unit,String^& trans,
           String^& factor,String^& min,String^& max,Panel^ panElem,int modi)
{
  TextBox^ txtBx;
  Label^ lab; 
  setBaseTlgElemView(descr,max,min,factor,trans,typ,len,unit,panElem,modi);
  txtBx = gcnew TextBox();
  panElem->Controls->Add(txtBx);
  TxtBoxArray->Add(txtBx);
  txtBx->Dock = DockStyle::Left;
  txtBx->Width = 91;
  txtBx->Text = val;
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
    if(modi == 0)
      lab->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
    if(modi == 1)
      lab->TextAlign = System::Drawing::ContentAlignment::MiddleRight;

}
//--------------------------------------------------------------------
void CTlgViewForm::addArrayTlgElem(int id,String^& Name,String^& val,String^& descr,String^& len,String^& unit,String^& trans,
                String^& factor,String^& min,String^& max,Panel^ panElem)
{
  Panel^ pan=nullptr; 
  Panel^ pan1=nullptr;
  Panel^ pan2=nullptr;
  Panel^ pan3=nullptr;
  Label^ lab=nullptr;
  Button^ but1=nullptr;
  //Button^ but2;
  TextBox^ txtBx1=nullptr;
  TextBox^ txtBx2=nullptr;
  String^ value=nullptr;
  int count,i;
  int item_count;
  int height;

  setBaseTlgElemView(descr,max,min,factor,trans,"",len,unit,panElem,0);
  panElem->Height = 80;

  String^ interName=Tlg->getInterfece();
  CInterListenElemView^ interElemView = CInterListenElemView::getInterListenElemView(interName);
  
  pan= gcnew Panel();
  pan->SuspendLayout();
  pan->Dock = DockStyle::Left;
  panElem->Controls->Add(pan);
  pan->Width=91;
  pan->AutoScroll = true;
 
  //========================================
  array <String^>^ items=nullptr;
  items = interElemView->getRowListe(Tlg->getName(),Name);
  if(items == nullptr)
  {
    items = gcnew array <String^>(1);
    items[0]="Not Name";
  }
    //=========================================
  count=Tlg->getSubElemCount(id);
	item_count=items->Length; 
  array <Panel^>^ panArray = gcnew array <Panel^> (item_count);
  for(i=0;i<item_count;i++)
  {
    pan1 = gcnew Panel();
    //pan1->Dock=DockStyle::Left;
    pan1->BorderStyle=BorderStyle::FixedSingle;
    //pan1->Width = 40;
    panArray[i]=pan1;
  }
  for(i=item_count-1;i>=0;i--)
  pan->Controls->Add(panArray[i]);

  int index;
  index = item_count-1;
  for(i=count;i>=1;i--)
  { 
    txtBx1 = gcnew TextBox();
    //txtBx1->Text = System::Convert::ToString(i);
    TxtBoxArray->Add(txtBx1);
    txtBx1->Dock = DockStyle::Top;
    panArray[index]->Controls->Add(txtBx1);
    index--;
    if(index<0)
      index=item_count-1;
    //pan->Controls->Add(txtBx1);
    value =  Tlg->getSubElemValue(id,i);
    if(value)
      txtBx1->Text = value;
  }
  for(i=0;i<item_count;i++)
  {
    lab= gcnew Label();
    lab->Dock=DockStyle::Top;
    lab->Height=15;
    lab->BorderStyle=BorderStyle::FixedSingle;
    if(!(items[i]->Equals("Not Name")))
      lab->Text=items[i];
    panArray[i]->Controls->Add(lab);
    if(item_count == 1)
    {
      panArray[i]->Width=pan->Width-18;
    }
    else
    {
      panArray[i]->Width=40;
    }
    panArray[i]->Top=0;
    panArray[i]->Height=(count/item_count+1)*20;
    panArray[i]->Left=40*i;
  }

  height = 20*((count/2)+1);
  if(panElem->Height > height)
      panElem->Height=height;
  lab = gcnew Label();
  panElem->Controls->Add(lab);
  lab->Dock = DockStyle::Left;
  lab->Width = 131;
  lab->BorderStyle = BorderStyle::FixedSingle;
  lab->Text = Name;//Tlg->getElemName(id);
  lab->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
  pan->ResumeLayout();   
}
//---------------------------------------------------------------------
void CTlgViewForm::addRecordsTlgElem(int id,Panel^ panElem)
{
  int count;
  int len;
  Panel^ recordPan=nullptr;
  Panel^ pan;
  Label^ lab;

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
  
 
  count = Tlg->getSubElemCount(id);
  CTlgElemWrapper^ elem = gcnew CTlgElemWrapper();
  CTlgElemWrapper^ elem1= gcnew CTlgElemWrapper();
  elem->setTlgElem(Tlg->getElem(id));
  int countSubElem;
  
  for(int i = count;i>=1;i--)
  {
    elem1->setTlgElem(elem->getSubElem(i));
    countSubElem = elem1->getSubElemCount();
    
    
    
    
    pan = gcnew Panel();
    panElem->Controls->Add(pan);
    pan->Dock = DockStyle::Top;
    pan->Height = 20;
    elemName=Tlg->getSubElemName(id,i);
    Tlg->getSubElementDescr(id,i,elemDescr,transTyp,unit,factor,min,max);
    typ=Tlg->getSubElemTypAsString(id,i);
    len=Tlg->getSubElemLen(id,i);
    lenStr = System::Convert::ToString(len);
    val=Tlg->getSubElemValue(id,i);
    
  
  

    if (countSubElem==0)
      addSimpleTlgElem(elemName,val,elemDescr,lenStr,typ,unit,transTyp,factor,min,max,pan,1);
    else
    {
      /*for (int j = 0;j<countSubElem;j++)
      {
      pan = new Panel();
      panElem->Controls->Add(pan);
      pan->Dock = DockStyle::Top;
      pan->Height = 20;
      elemName=Tlg->getSubElemName(id,i);
      Tlg->getSubElementDescr(id,i,elemDescr,transTyp,unit,factor,min,max);
      typ=Tlg->getSubElemTypAsString(id,i);
      len=Tlg->getSubElemLen(id,i);
      lenStr = System::Convert::ToString(len);
      val=Tlg->getSubElemValue(id,i);
      addSimpleTlgElem(elemName,val,elemDescr,lenStr,typ,unit,transTyp,factor,min,max,pan,1);
      }*/
      pan->Height = 20 * (countSubElem+1);
      addArrayTlgElem_ (elem1,elemName,val,elemDescr,lenStr,unit,transTyp,factor,min,max,pan);

    }
  }
  pan = gcnew Panel();
  panElem->Controls->Add(pan);
  pan->Height = 20;
  pan->Dock = DockStyle::Top;
  pan->BackColor = System::Drawing::Color::Gray;
  lab = gcnew Label();
  pan->Controls->Add(lab);
  lab->Dock = DockStyle::Left;
  lab->ImageList = imageList;
  lab->ImageIndex = FlagShowModi;
	lab->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
	lab->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
  lab->Text=Tlg->getElemName(id);
  lab->Click += gcnew System::EventHandler(this, &CTlgViewForm::OnLabelHeaderClick);
  if(FlagShowModi == 0)
    panElem->Height = 20;
  if(FlagShowModi == 1)
  {
    count = panElem->Controls->Count;
    panElem->Height = 20*count;
    System::Windows::Forms::Control^ panTemp=nullptr;
    System::Windows::Forms::Control^ panTemp1=nullptr;
    System::Windows::Forms::Control^ panTemp2=nullptr;

    for (int i=0;i<count;i++)
    {
      panTemp=panElem->Controls[i];
      if (panTemp->Controls->Count>7)
      {
        panTemp1=panTemp->Controls[8];
        if (panTemp1->Controls->Count>0)
        {
          panTemp2 = panTemp1->Controls[0];
         
          /*pan->Height += (panTemp2->Controls->Count-2)*20;*/
          panElem->Height += panTemp1->Height - 20;
        }
      }
    }
  }
}
//----------------------------------------------------------------------
void CTlgViewForm::setBaseTlgElemView(String^& descr,String^& max,String^& min,String^& factor,
     String^& transp,String^ typ,String^& len,String^& unit,Panel^ panElem,int modi)
{
  Label^ lab;
  int pos=0;
  
  lab = gcnew Label();
  panElem->Controls->Add(lab);
  lab->Dock = DockStyle::Fill;
  //lab->Dock = DockStyle::Left;
  //lab->AutoSize = false;
  //lab->Width  = 320;
  lab->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
  lab->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
  pos = descr->IndexOf("\n");
  if(pos != -1)
    descr = String::Concat(descr->Substring(0,pos-1)," ",descr->Substring(pos+1,descr->Length-pos-1));
  lab->Text=descr;
  //---max---
  lab = gcnew Label();
  panElem->Controls->Add(lab);
  lab->Dock = DockStyle::Left;
  lab->Width = 40;
  lab->BorderStyle = BorderStyle::FixedSingle;
  lab->Text = max;
   //---min--
  lab = gcnew Label();
  panElem->Controls->Add(lab);
  lab->Dock = DockStyle::Left;
  lab->Width = 40;
  lab->BorderStyle = BorderStyle::FixedSingle;
  lab->Text = min;
   //---Factor---
  lab = gcnew Label();
  panElem->Controls->Add(lab);
  lab->Dock = DockStyle::Left;
  lab->Width = 40;
  lab->BorderStyle = BorderStyle::FixedSingle;
  lab->Text = factor;
   //---transportTyp---
  lab = gcnew Label();
  panElem->Controls->Add(lab);
  lab->Dock = DockStyle::Left;
  lab->Width = 40;
  lab->BorderStyle = BorderStyle::FixedSingle;
  lab->Text = transp;
   //---Length---
  lab = gcnew Label();
  panElem->Controls->Add(lab);
  lab->Dock = DockStyle::Left;
  lab->Width = 40;
  lab->BorderStyle = BorderStyle::FixedSingle;
  lab->Text = len;
   //---Typ---------
  lab = gcnew Label();
  panElem->Controls->Add(lab);
  lab->Dock = DockStyle::Left;
  lab->Width = 40;
  lab->BorderStyle = BorderStyle::FixedSingle;
  lab->Text = typ;
   //---Unit
  lab = gcnew Label();
  panElem->Controls->Add(lab);
  lab->Dock = DockStyle::Left;
  lab->Width = 80;
  lab->BorderStyle = BorderStyle::FixedSingle;
  lab->Text = unit;    
}
 //----------------------------------------------------------------------
 void CTlgViewForm::setDelAddToSzen(AddTlgToSzen^ del)
 {
   DelAddTlg=del;
 }
 //----------------------------------------------------------------------
 void CTlgViewForm::setDelUpTlgToSzen(UpdateTlgToSzen^ del)
 {
   DelUpTlg = del;
 }
 //----------------------------------------------------------------------
 bool CTlgViewForm::isUpdate()
 {
   return UpdateFlag;
 }
 //----------------------------------------------------------------------
void CTlgViewForm::setReceiveView()
{
    panSenderSpez->Hide();
    LenChange=true;
}
//-----------------------------------------------------------------------
void CTlgViewForm::addNewPanel()
{
  try
  {
    int count;
    int elemTyp;
    int len;
    TextBox^ txtBx=nullptr;
    array <String^>^ elemArrStr = nullptr;
    Panel^ panElem=nullptr;
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
  

    UpdateFlag = false;
    if(panCon != nullptr)
      delete panCon;
    panCon = gcnew Panel(); 
    TxtBoxArray = gcnew ArrayList();
    panBody->Controls->Add(panCon);

    panCon->Visible = false;
    panCon->SuspendLayout();
    labTlgName->Text = Tlg->getName();
    labTlgDescr->Text = Tlg->getTlgDescr();
    labDirect->Text = Tlg->getTlgDirection();
    TxtBoxArray->Clear();
    count = Tlg->getTlgElemCount();
    for(int i = count;i>=1;i--)
    {
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
      switch(elemTyp)
      {
        case 0:
          addSimpleTlgElem(elemName,val,elemDescr,lenStr,typ,unit,transTyp,factor,min,max,panElem,0);
          break;
        case 1:
          addRecordsTlgElem(i,panElem);
          break;
        case 2:
          addArrayTlgElem(i,elemName,val,elemDescr,lenStr,unit,transTyp,factor,min,max,panElem);
          break;
      };
      panElem->ResumeLayout();
      panElem->Visible=true;
    }
    count=TxtBoxArray->Count;
    //panCon->Height = 20*(count+1);
    panCon->Left = 0;
    panCon->Top = 20;
    panCon->Width = panBody->Width;
    panCon->ResumeLayout();
    if(panCon->Controls->Count>0)
    {
      panCon->Height=panCon->Controls[0]->Top+panCon->Controls[0]->Top+10;
    }
    panCon->Visible = true;
    // txtBxByteValue->Text=Tlg->getSerialiseTlgAsString("|");
    for(int i=0;i<count;i++)
    {
      txtBx = safe_cast<TextBox^>(TxtBoxArray[i]);
      txtBx->Tag = System::Convert::ToString(i);
      txtBx->Enter += gcnew System::EventHandler(this, &CTlgViewForm::OnEnterTextBox);
			txtBx->Leave += gcnew System::EventHandler(this,&CTlgViewForm::OnLeaveTextBox);
    } 
      UpdateFlag=true;
      panBody->Show();
  }
  catch(System::Exception^ e)
  {
    String^ test=nullptr;

    test = e->ToString();
    UpdateFlag=true;
  }
}
//-----------------------------------------------------------------------
void CTlgViewForm::setErrorMessageDel(ErrorMessageDelTyp^ del)
{
  ErrorMessageDel = del;
}
//-----------------------------------------------------------------------
void CTlgViewForm::setEditMode(bool flag)
{
    buttUpdate->Enabled=flag;
    button9->Enabled=flag;
}
//-----------------------------------------------------------------------
void CTlgViewForm::setTelElemEditEvent(TelElemEditEventTyp^ editEvent)
{
    TelElemEditEvent=editEvent;
}
//--------------------------------------------------------------------
void CTlgViewForm::addArrayTlgElem_(CTlgElemWrapper^ elem,String^& Name,String^& val,String^& descr,String^& len,String^& unit,String^& trans,
                String^& factor,String^& min,String^& max,Panel^ panElem)
{
  Panel^ pan=nullptr; 
  Panel^ pan1=nullptr;
  Panel^ pan2=nullptr;
  Panel^ pan3=nullptr;
  Label^ lab=nullptr;
  Button^ but1=nullptr;
  //Button^ but2;
  TextBox^ txtBx1=nullptr;
  TextBox^ txtBx2=nullptr;
  String^ value=nullptr;
  int count,i;
  int item_count;
  int height;
  CTlgElemWrapper^ subElem = gcnew CTlgElemWrapper(); 
  

  setBaseTlgElemView(descr,max,min,factor,trans,"",len,unit,panElem,0);
  /*panElem->Height = 80;*/

  String^ interName=Tlg->getInterfece();
  CInterListenElemView^ interElemView = CInterListenElemView::getInterListenElemView(interName);
  
  pan= gcnew Panel();
  pan->SuspendLayout();
  pan->Dock = DockStyle::Left;
  panElem->Controls->Add(pan);
  pan->Width=91;
  pan->AutoScroll = true;
 
  //========================================
  array <String^>^ items=nullptr;
  items = interElemView->getRowListe(Tlg->getName(),Name);
  if(items == nullptr)
  {
    items = gcnew array <String^> (1);
    items[0]="Not Name";
  }
    //=========================================
  count=elem->getSubElemCount();
 /* count=Tlg->getSubElemCount(id);*/
  item_count=items->Length; 
  array <Panel^>^ panArray = gcnew array <Panel^> (item_count);
  for(i=0;i<item_count;i++)
  {
    pan1 = gcnew Panel();
    //pan1->Dock=DockStyle::Left;
    pan1->BorderStyle=BorderStyle::FixedSingle;
    //pan1->Width = 40;
    panArray[i]=pan1;
  }
  for(i=item_count-1;i>=0;i--)
    pan->Controls->Add(panArray[i]);

  int index;
  index = item_count-1;
  for(i=count;i>=1;i--)
  { 
    txtBx1 = gcnew TextBox();
    //txtBx1->Text = System::Convert::ToString(i);
    TxtBoxArray->Add(txtBx1);
    txtBx1->Dock = DockStyle::Top;
    panArray[index]->Controls->Add(txtBx1);
    index--;
    if(index<0)
      index=item_count-1;
    //pan->Controls->Add(txtBx1);
    if (!Tlg->getTlgEmpty())
    {
      subElem->setTlgElem(elem->getSubElem(i));
      subElem->getElemValue(value);
      /*value =  Tlg->getSubElemValue(id,i);*/
      if(value)
        txtBx1->Text = value;
    }
  }
  for(i=0;i<item_count;i++)
  {
    lab= gcnew Label();
    lab->Dock=DockStyle::Top;
    lab->Height=15;
    lab->BorderStyle=BorderStyle::FixedSingle;
    if(!(items[i]->Equals("Not Name")))
      lab->Text=items[i];
    panArray[i]->Controls->Add(lab);
    if(item_count == 1)
    {
      panArray[i]->Width=pan->Width-18;
    }
    else
    {
      panArray[i]->Width=40;
    }
    panArray[i]->Top=0;
    panArray[i]->Height=(count/item_count+1)*20;
    panArray[i]->Left=40*i;
  }

  height = 20*((count/2)+1);
  if(panElem->Height > height)
      panElem->Height=height;
  lab = gcnew Label();
  panElem->Controls->Add(lab);
  lab->Dock = DockStyle::Left;
  lab->Width = 131;
  lab->BorderStyle = BorderStyle::FixedSingle;
  lab->Text = Name;//Tlg->getElemName(id);
  lab->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
  pan->ResumeLayout();   
}