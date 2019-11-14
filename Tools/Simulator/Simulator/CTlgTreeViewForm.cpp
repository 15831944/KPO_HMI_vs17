#include "StdAfx.h"
#include "CTlgTreeViewForm.h"
#include "CMessageForm.h"
#include "CProgressBarViewForm.h"
//-----------------------------------------------
using namespace simulator;
//-----------------------------------------------
Void CTlgTreeViewForm::tabPage1_Resize(System::Object ^  sender, System::EventArgs ^  e)
{
  /*if (PrototypForm)
    PrototypForm->setTreeViewSize(tabPage2->Size.get_Width(), tabPage2->Size.get_Height());*/
}
//-----------------------------------------------
Void CTlgTreeViewForm::panHinterTreeView_Resize(System::Object ^  sender, System::EventArgs ^  e)
{
 /* if (FileReaderForm)
    FileReaderForm->setTreeViewSize(panHinterTreeView->Size.get_Width(), panHinterTreeView->Size.get_Height());*/
}
//-----------------------------------------------
CTlgTreeViewForm::CTlgTreeViewForm(Panel^ parent):
TlgContainer(nullptr)
{
  InitializeComponent();
  this->TopLevel = false;
  this->Parent = parent;
  this->Dock = DockStyle::Fill;
	this->FormBorderStyle = ::FormBorderStyle::None;

  LabArray = gcnew System::Collections::ArrayList();
  panFilter->Visible = false;

  UpdateModus = true;
  Flag=true;
  myWr = gcnew CTlgWrapper();
  Count = 0;
  ChekedLabArray=nullptr;
  initViewComponente();
  buttAdd->Enabled=false;
  SzenUpFlag=true;
  LogFileViewEvent=nullptr;
  ToolTipFileName = gcnew System::Windows::Forms::ToolTip();
  ToolTipFileName->InitialDelay = 50;
}
//-------------------------------------------------------------------------------
System::Void CTlgTreeViewForm::OnSizeFormChanged(System::Object ^  sender, System::EventArgs ^  e)
{
  if(panTreeViewBack->Height < tabControl->Height-30)
    panTreeViewBack->Height = tabControl->Height-28;
  panHinterTreeView->Width=tabPage2->Width-panLabArray->Width;
  
}
//--------------------------------------------------------------------------------
System::Void CTlgTreeViewForm::OnResizePanel(System::Object ^  sender, System::EventArgs ^  e)
{
  panHinterTreeView->Width=tabPage2->Width-panLabArray->Width;
  setLabArrayPanPosition();
}
//--------------------------------------------------------------------------------
System::Void CTlgTreeViewForm::OnKeyDownEvent(System::Object ^  sender, System::Windows::Forms::KeyEventArgs ^  e)
{
  if(e->Control)
  {
    if(e->KeyCode == System::Windows::Forms::Keys::A)
      selectAllTlgFromLogFile();
    if(e->KeyCode == System::Windows::Forms::Keys::N)
      removeSelectionTlgFrommLogFile();
  }
}

//--------------------------------------------------------------------------------
System::Void CTlgTreeViewForm::OnClickLabel(System::Object ^  sender, System::EventArgs ^  e)
{
  int index;
  Label^ lab = safe_cast<Label^>(sender);
  lab->ImageIndex = (lab->ImageIndex+1)%2;
  index = System::Convert::ToInt32(lab->Tag);
  index=FileReaderForm->getTlgPosInContainer(index);
  if(lab->ImageIndex == 0)
  {
    //ChekedLabArray[FileReaderForm->calcViewIndexToContainerIndex(index)]=false;
    ChekedLabArray[index-1]=false;
  }
  else
  {
    int count = ChekedLabArray->Length;
    //ChekedLabArray[FileReaderForm->calcViewIndexToContainerIndex(index)]=true;
    ChekedLabArray[index-1]=true;
  }
}
//---------------------------------------------
System::Void CTlgTreeViewForm::OnClickButtonFilter(System::Object ^  sender, System::EventArgs ^  e)
{

}
//---------------------------------------------
System::Void CTlgTreeViewForm::OnClickButtonAdd(System::Object ^  sender, System::EventArgs ^  e)
{
  if(AddToSzenDel != nullptr)
  {
    int i,count;
    int tlgCount,curentCount;
    double time;
    CProgressBarViewForm^ progressBar = gcnew CProgressBarViewForm(); 
    Label^ lab = nullptr;
    CItemWrapper^ tlg = gcnew CTlgWrapper();
    //count = LabArray->Count;
    count = ChekedLabArray->Length;
    tlgCount = getCheckedTlgCount();
    curentCount = 0;

    progressBar->setMinAndMax(0,count);
    String^ source = "Adding Telegrams to Szenario.";
    progressBar->setSourceLab(source);
    progressBar->Show();
    for(i=0;i<count;i++)
    {
      //lab = safe_cast<Label*>(LabArray[i-1));
      //if(lab->ImageIndex == 1)
      //{
      if(ChekedLabArray[i] == true)
      {
        //tlg = FileReaderForm->getTlg(count-i+1);
        tlg=FileReaderForm->getClonedVirtualTlg(i+1);
        //time = FileReaderForm->getTlgTime(i+1);//!!!  
        time=FileReaderForm->getVirtualTlgTime(i+1);
        curentCount++;
        if(curentCount == tlgCount)
          AddToSzenDel->Invoke(tlg,time,false);
        else
          AddToSzenDel->Invoke(tlg,time,true);
      }
      progressBar->updateStep(1);
    }
    progressBar->Close();
  }
}
//----------------------------------------------------------------------------
System::Void CTlgTreeViewForm::OnSelectedIndexChanged(System::Object ^  sender, System::EventArgs ^  e)
{
  if(tabControl->SelectedIndex == 0)
  {
    labInterDesc->Show();
    labInterVer->Show();
    if(PrototypForm)
    {
      setTlgCount(PrototypForm->getTlgCount());
      String^ path=PrototypForm->getPathFile();
      setFileName(path);
    }
    else
    {
      setTlgCount(0);
      labFileName->Text = "";
    }
    buttAdd->Enabled=false;
    if(LogFileViewEvent)
      LogFileViewEvent->Invoke(false);
  }
  if(tabControl->SelectedIndex == 1)
  {
    labInterDesc->Hide();
    labInterVer->Hide();
    if(FileReaderForm)
    {
      int pos = -1;
      String^ logName=nullptr;
      setTlgCount(FileReaderForm->getTlgCount());
      logName=FileReaderForm->getPathFile();
      setFileName(logName);
      FileReaderForm->ShowContainer();
      //FileReaderForm->ShowTlgContainer();
      initLabelArray(FileReaderForm->getItemViewCount());
    }
    else
    {
      setTlgCount(0);
      labFileName->Text = "";
    }
    if(SzenUpFlag)
      buttAdd->Enabled=true;
    if(LogFileViewEvent)
      LogFileViewEvent->Invoke(true);
  }
}
//---------------------------------------------
void CTlgTreeViewForm::setFileName(String^ fileName)
{
  int pos=-1;
  if(fileName)
  {
    pos=fileName->LastIndexOf("\\");
    if(pos == -1)
      labFileName->Text = fileName;
    else
      labFileName->Text = fileName->Substring(pos+1,fileName->Length-pos-1);
  }
  else
  {
    labFileName->Text="";
  }
}
//---------------------------------------------
//---------------------------------------------
void CTlgTreeViewForm::getTreeNode(TreeNode^ node,CItemWrapper^ tlg)
{
  String^ name=nullptr;
  TreeNode^ subNode=nullptr;
  TreeNode^ subSubNode=nullptr;
  int count,count1;
  int flag;
  array <String^>^ str;

  count = tlg->getTlgElemCount();
  name=tlg->getName();
  node->Text = name;
  for(int i=1;i<=count;i++)
  {
    str=tlg->getElemAsStringArray(i,&flag);
    if(flag == 0)
    {
      subNode = gcnew System::Windows::Forms::TreeNode();
      //subNode->set_
      subNode->Text = String::Concat(str[0],"  ",str[2]);
      node->Nodes->Add(subNode);
    }
    if(flag == 1)
    {
      count1 = str->Length;
      count1 = (count1-2)/3;
      subNode = gcnew System::Windows::Forms::TreeNode();
      subNode->Text = str[0];
      for(int j=1;j<=count1;j++)
      {
        subSubNode = gcnew System::Windows::Forms::TreeNode();
        subSubNode->Text = String::Concat(str[j*3-1],"  ",str[j*3+1]);
        subNode->Nodes->Add(subSubNode);
      }
        node->Nodes->Add(subNode);
    }
    if(flag==2)
    {
      count1 = str->Length;
      count1 = count1/2;
      subNode = gcnew System::Windows::Forms::TreeNode();
      subNode->Text = str[0];
      for(int j=1;j<count1;j++)
      {
        subSubNode = gcnew System::Windows::Forms::TreeNode();
        subSubNode->Text = String::Concat(str[j*2],"   ",str[j*2+1]);
        subNode->Nodes->Add(subSubNode);
      }
      node->Nodes->Add(subNode);
    }
  }
}
//---------------------------------------------
void CTlgTreeViewForm::initLabelArray(int count)
{
  int height=16;
  int i,countItem;
  Label^ lab;
   
  if(count != LabArray->Count)
  {
    countItem = LabArray->Count;
    for(i=0;i<countItem;i++)
    {
      lab = safe_cast<Label^>(LabArray[i]);
      delete lab;
    }
  
    LabArray->Clear();
    panLabArray->Visible = false;
    panLabArray->SuspendLayout();
    panLabArray->Controls->Clear();
    for(int i=0;i<count;i++)
    {
      lab = gcnew Label();
      panLabArray->Controls->Add(lab);
      lab->Dock = DockStyle::Top;
      lab->Height = height;
      lab->ImageList=imageList;
      lab->ImageAlign = System::Drawing::ContentAlignment::TopCenter;
      lab->ImageIndex = 0;
      lab->Click += gcnew System::EventHandler(this, &CTlgTreeViewForm::OnClickLabel);
      lab->Tag = (count-i);
      LabArray->Add(lab);
    }
    panLabArray->ResumeLayout();
    panLabArray->Visible = true;
  }
}
//---------------------------------------------
int CTlgTreeViewForm::calcNewHeight(TreeNode^ node)
{
  int ret = 0;
  int count=0;

  ret=ret+node->TreeView->ItemHeight;
  if(node->IsExpanded)
  {
    count=node->Nodes->Count;
    for(int i=0;i<count;i++)
    {
      //if(!node->get_Nodes()[i)->IsExpanded)
      //{
        //ret=ret+node->get_TreeView()->ItemHeight;
      //}
      //else
      //{
      ret=ret+calcNewHeight(node->Nodes[i]);
      //}
    }
  }
  return ret;
}
//---------------------------------------------
void CTlgTreeViewForm::setTreeViewHeight()
{
  Label^ lab = safe_cast<Label^>(LabArray[0]);
  int height=0;

  height = lab->Top+lab->Height;
  
  
  if(height > this->panTreeViewBack->Height)
  {
    panTreeViewBack->Height = height;
  }
  else
  {
    if(height > tabControl->Height-30-this->panFilterTopView->Height)
      panTreeViewBack->Height = height;
    else
      panTreeViewBack->Height = tabControl->Height-28-this->panFilterTopView->Height;
  }
}
//---------------------------------------------
void CTlgTreeViewForm::setTlgCount(int count)
{
  try
  {
    textBox2->Text = System::Convert::ToString(count);
  }
  catch(Exception^ e)
  {
  }
}
//--------------------------------------------
void CTlgTreeViewForm::initViewComponente()
{
  PrototypForm = gcnew CItemPrototypContainerForm();
  PrototypForm->TopLevel = false;
  PrototypForm->Parent = tabPage1;
  PrototypForm->Dock = DockStyle::Fill;
  /*PrototypForm->setPrototypMode(true);*/
  PrototypForm->Visible = true;

  FileReaderForm = gcnew CTlgContainerTreeViewForm();
  FileReaderForm->TopLevel = false;
  FileReaderForm->Parent = panHinterTreeView;
  TreeViewEventHandler^ colEvent = gcnew TreeViewEventHandler(this,&CTlgTreeViewForm::AfterCollapseTreeView);
  FileReaderForm->setAfterCollapsEvent(colEvent);
  TreeViewEventHandler^ expEvent = gcnew TreeViewEventHandler(this,&CTlgTreeViewForm::AfterExpandTreeView);
  FileReaderForm->setAfterExpandEvent(expEvent);
  CTlgContainerTreeViewForm::ScrollPositionUpdateTyp^ scrollEvent = gcnew CTlgContainerTreeViewForm::ScrollPositionUpdateTyp(this,&CTlgTreeViewForm::scrollTreeViewValChange);
  FileReaderForm->setScrollUpdateEvent(scrollEvent);
  FileReaderForm->Dock = DockStyle::Fill;
  panLabArray->Width =10;
  FileReaderForm->setPrototypMode(false);
  FileReaderForm->Visible = true;
  CTlgContainerTreeViewForm::DataUpdateEvent^ dataUp = gcnew CTlgContainerTreeViewForm::DataUpdateEvent(this,&CTlgTreeViewForm::updateContainerView);
  FileReaderForm->setDataUpdateEvent(dataUp);
  CTlgContainerTreeViewForm::ItemViewChangeEvent^ itemChange = gcnew CTlgContainerTreeViewForm::ItemViewChangeEvent(this,&CTlgTreeViewForm::updateCheckedState);
  FileReaderForm->setItemViewChangeEvent(itemChange);
  FileReaderForm->setUpdateFilterTextTyp(gcnew CTlgContainerTreeViewForm::UpdateFilterTextTyp(this,&CTlgTreeViewForm::UpdateLogFileFilter));
  FilterLogFileToolTip = gcnew ToolTip();
  buttAdd->Enabled=false;
}
//---------------------------------------------
 void CTlgTreeViewForm::setTlgPrototypContainer(CItemBaseContainerWrapper^ con)
 {
   PrototypForm->setPrototypContainer(con);
   PrototypForm->setCyclicContextMenuActiv();
 }
//---------------------------------------------
void CTlgTreeViewForm::showTlgPrototypContainer(String^ InterDesc,String^ InterVersion)
{
  this->labInterDesc->Text ="Description : " + InterDesc;
  this->labInterVer->Text = "Version : " + InterVersion;
  PrototypForm->showContainer();
  tabControl->SelectedIndex = 0;
  setTlgCount(PrototypForm->getTlgCount());
  setFileName(PrototypForm->getPathFile());
}
//---------------------------------------------
void CTlgTreeViewForm::setTlgContainer(CItemBaseContainerWrapper^ con)
{
  int countTlg;//,i;
  FileReaderForm->setTlgContainer(con);
  if(ChekedLabArray != nullptr)
  System::Array::Clear(ChekedLabArray,0,ChekedLabArray->Length);
  countTlg=FileReaderForm->getVirtualTlgCount();
  ChekedLabArray = gcnew array <bool> (countTlg);
  for(int i=0;i<countTlg;i++)
    ChekedLabArray[i]=false;
}
//---------------------------------------------
void CTlgTreeViewForm::showTlgContainer()
{
  String^ logFileName=nullptr;
  int pos=-1;
  FileReaderForm->ShowContainer();
  initLabelArray(FileReaderForm->getItemViewCount());
  tabControl->SelectedIndex = 1;
  setTlgCount(FileReaderForm->getTlgCount());
  logFileName=FileReaderForm->getPathFile();
  setFileName(logFileName);
  setTlgCount(FileReaderForm->getTlgCount());
}
//---------------------------------------------
void CTlgTreeViewForm::setAfterSelectPrototypEvent(CItemPrototypContainerForm::AfterSelectPrototypEvent^ event)
{
  PrototypForm->setSelectEvent(event); 
}
//---------------------------------------------
void CTlgTreeViewForm::setAfterSelectTlgContainerEvent(CTlgContainerTreeViewForm::AfterSelectEvent^ event)
{
  FileReaderForm->setSelectEvent(event);
}
//---------------------------------------------
System::Void CTlgTreeViewForm::AfterCollapseTreeView(System::Object ^  sender, System::Windows::Forms::TreeViewEventArgs ^  e)
{
  int index,count,height;
  Label^ lab=nullptr;
  TreeNode^ node=nullptr;

  node = e->Node;
  //height = calcNewHeight(node);
  while(node->Parent != nullptr)
    node = node->Parent;
  
  height = calcNewHeight(node);

	count = node->TreeView->Nodes->Count;

  index=node->Index;
  lab = safe_cast<Label^>(LabArray[count-index-1]); 
  lab->Height = height; //lab->Height-height+node->get_TreeView()->ItemHeight;

  //setTreeViewHeight();
}
//---------------------------------------------
System::Void CTlgTreeViewForm::AfterExpandTreeView(System::Object ^  sender, System::Windows::Forms::TreeViewEventArgs ^  e)
{
  int index,height,count;
  Label^ lab=nullptr;
  TreeNode^ node=nullptr;

  node = e->Node;
  height = calcNewHeight(node);
  while(node->Parent != nullptr)
    node = node->Parent;

  count=node->TreeView->Nodes->Count;

  index=node->Index;
  lab = safe_cast<Label^>(LabArray[count-index-1]);
  lab->Height = lab->Height+height-node->TreeView->ItemHeight;

  //setTreeViewHeight();
}
//---------------------------------------------
void CTlgTreeViewForm::setAddToSzenDel(addToSzenDelTyp^ del)
{
   AddToSzenDel = del;
}
//---------------------------------------------
void CTlgTreeViewForm::clearView()
{
  PrototypForm->clearView();
  FileReaderForm->clearView();
}
//---------------------------------------------
void CTlgTreeViewForm::clearLogFileView()
{
  FileReaderForm->clearView();
  LabArray->Clear();
  panLabArray->Controls->Clear();
  if(ChekedLabArray != nullptr)
    System::Array::Clear(ChekedLabArray,0,ChekedLabArray->Length);
}
//---------------------------------------------
int CTlgTreeViewForm::getCheckedTlgCount()
{
  int ret = 0;
  int count;
  Label^ lab = nullptr;
  //count = LabArray->Count;
  count = ChekedLabArray->Length;
  for(int i=0;i<count;i++)
  {
    //lab = safe_cast<Label*>(LabArray[i-1));
    //if(lab->ImageIndex == 1)
      //ret++;
    if(ChekedLabArray[i] == true)
      ret++;
  }
  return ret;
}
//---------------------------------------------
void CTlgTreeViewForm::updateUseCaseView(String^ interName,String^ useCaseName)
{
  array <String^>^ use;
  int i,count;
  ArrayList^ arr = gcnew ArrayList();
  if(!useCaseName->Equals("All"))
  {
    CInterUseCase^ interUseCase = CInterUseCase::getInterUseCase(interName);
    use=interUseCase->getUseCaseTelName(useCaseName);
    count=use->Length;
    for(i=0;i<count;i++)
    {
      arr->Add(use[i]);
    }
    //update proto-container
    PrototypForm->clearView();
    PrototypForm->resetContainer();
    PrototypForm->updateContainerView(arr);
    //PrototypForm->ShowProtoTypContainer();
    PrototypForm->showContainer();
    
    //update log-file container
    FileReaderForm->clearView();
    FileReaderForm->resetContainer();
    FileReaderForm->updateContainerView(arr);
    
    //FileReaderForm->ShowTlgContainer();
    FileReaderForm->ShowContainer();
    setTlgCount(FileReaderForm->getTlgCount());
  }
  else
  {
    PrototypForm->resetContainer();
    PrototypForm->clearView();
    //PrototypForm->ShowProtoTypContainer();
    PrototypForm->showContainer();
    FileReaderForm->resetContainer();
    FileReaderForm->clearView();
    //FileReaderForm->ShowTlgContainer();
    FileReaderForm->ShowContainer();
    setTlgCount(FileReaderForm->getTlgCount());
  }
}
//---------------------------------------------
void CTlgTreeViewForm::updateContainerView()
{
  int countTlg;
  if(ChekedLabArray != nullptr)
    System::Array::Clear(ChekedLabArray,0,ChekedLabArray->Length);
  countTlg=FileReaderForm->getVirtualTlgCount();
  ChekedLabArray = gcnew array <bool> (countTlg);
  for(int i=0;i<countTlg;i++)
    ChekedLabArray[i]=false;

  initLabelArray(FileReaderForm->getItemViewCount());

}
//---------------------------------------------
void CTlgTreeViewForm::updateCheckedState(int pos,int count)
{
  int i,j;
  int itemCount,itemheigth;
  itemCount=LabArray->Count;
  j=itemCount-1;
  Label^ lab=nullptr;
  //int t;

  itemheigth=FileReaderForm->getItemHeigth();
  for(i=pos;i<pos+count;i++)
  {
    if(i < itemCount)
    {
      lab = safe_cast<Label^>(LabArray[j]);
      if(ChekedLabArray[i])
        lab->ImageIndex = 1;
      else
        lab->ImageIndex = 0;
      j--;
      lab->Height=itemheigth;
    }
  }
}
//---------------------------------------------
void CTlgTreeViewForm::setFilterLogFile(String^ inter,array <String^>^ reg)
{
  if(FileReaderForm->setFilterRegExp(reg))
  {
    FileReaderForm->clearView();
    FileReaderForm->ShowContainer();
    setTlgCount(FileReaderForm->getTlgCount());
    //Filter Status
  }
  else
  {
    System::Windows::Forms::MessageBox::Show(nullptr,"Regular Exprecion is wrong","Error");
  }
  //initLabelArray(FileReaderForm->getItemViewCount());
}
//---------------------------------------------
void CTlgTreeViewForm::selectLogFileTelegramm(int index)
{
  FileReaderForm->selectTelegram(index);
  setTlgCount(FileReaderForm->getTlgCount());
}
//---------------------------------------------
void CTlgTreeViewForm::enableSzenMode(bool mode)
{
  SzenUpFlag=mode;
  if(tabControl->SelectedIndex == 1)
    buttAdd->Enabled=mode;
}
//---------------------------------------------
void CTlgTreeViewForm::setMessageHandler(CTlgContainerTreeViewForm::DelMessageHandlerTyp^ messHandl,CItemPrototypContainerForm::DelMessageHandlerPrototyp^ messHandl1)
{
  PrototypForm->setMessageHandler(messHandl1);
  FileReaderForm->setMessageHandler(messHandl);
}
//---------------------------------------------
void CTlgTreeViewForm::scrollTreeViewValChange()
{
  int count,i;
  int mheight;
  int mtop;
  int telInCon;
  Label^ lab=nullptr;
  count = FileReaderForm->getItemViewCount();
  mtop = FileReaderForm->getTreeViewTop();
  initLabelArray(count);
  panLabArray->SuspendLayout();
  panLabArray->Top = mtop;
  setLabArrayPanPosition();
  for(i=1;i<=count;i++)
  {
    lab = safe_cast<Label^>(LabArray[count-i]);
    mheight=FileReaderForm->getNodeHeight(i-1);
    lab->Height=mheight;
    telInCon=FileReaderForm->getTlgPosInContainer(i);
    if(ChekedLabArray[telInCon-1])
      lab->ImageIndex=1;
    else
      lab->ImageIndex=0;
  }
  panLabArray->ResumeLayout();
}
//---------------------------------------------
void CTlgTreeViewForm::setLabArrayPanPosition()
{
  int mtop = panLabArray->Top;
  int mheight = panTreeViewBack->Height+(-1)*mtop;
  //panLabArray->Top= mtop;
  if(panLabArray->Height < mheight)
    panLabArray->Height = mheight;
}
//---------------------------------------------
void CTlgTreeViewForm::selectAllTlgFromLogFile()
{
  int count,i;
  Label^ lab;
  count = LabArray->Count;
  for(i=0;i<count;i++)
  {
    lab = safe_cast<Label^>(LabArray[i]);
    lab->ImageIndex = 1;
  }
  count = ChekedLabArray->Length;
  for(i=0;i<count;i++)
  {
    ChekedLabArray[i]=true;
  }
}
//----------------------------------------------
void CTlgTreeViewForm::removeSelectionTlgFrommLogFile()
{
  int count,i;
  Label^ lab;
  count = LabArray->Count;
  for(i=0;i<count;i++)
  {
    lab = safe_cast<Label^>(LabArray[i]);
    lab->ImageIndex = 0;
  }
  count = ChekedLabArray->Length;
  for(i=0;i<count;i++)
  {
    ChekedLabArray[i]=false;
  }
}
//---------------------------------------------
void CTlgTreeViewForm::setLogFileViewEvent(LogFileViewEventTyp^ event)
{
  LogFileViewEvent=event;
}
//---------------------------------------------
void CTlgTreeViewForm::UpdateLogFileFilter(String^ filter)
{
  if (filter != nullptr)
  {
    this->labFilterText->Text = filter;
    this->panFilterTopView->Visible = true;
    this->FilterLogFileToolTip->SetToolTip(labFilterText,filter);
  }
  else
  {
    this->labFilterText->Text = "none";
    //this->panFilterTopView->Visible = false;
    this->FilterLogFileToolTip->SetToolTip(labFilterText,"");
  }
}