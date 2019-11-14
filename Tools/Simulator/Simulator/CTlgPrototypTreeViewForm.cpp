#include "StdAfx.h"
#include "CTlgPrototypTreeViewForm.h"

using namespace simulator;

//---------------------------------------
CTlgPrototypTreeViewForm::CTlgPrototypTreeViewForm(Panel^ parent)
{
	InitializeComponent();
	this->TopLevel = false;
	this->Parent = parent;
	this->Dock = DockStyle::Fill;
  this->FormBorderStyle = ::FormBorderStyle::None;
  UpdateModus = true;
}
//---------------------------------------
System::Void CTlgPrototypTreeViewForm::OnAfterSelectTreeView(System::Object ^  sender, System::Windows::Forms::TreeViewEventArgs ^  e)
{
	String^ val=nullptr;
	int index;
  
  if(UpdateModus)
  {
	  index=e->Node->Index;
	  val=e->Node->Text;
//	labTlgName->Text = String::Concat("Telegramm: ",val);
 
	  CItemWrapper^ tlg = gcnew CTlgWrapper();
//    tlg->setTlg(TlgFactoryWrapper->getTlgPrototyp(index+1));
	//tlg->setTlgPrototyp(index+1);

	//panTlgView->Visible = false;
	  TlgViewForm->showTlg(tlg);
    TlgViewForm->Refresh();
	//panTlgView->Visible = true;
  }
	
}
//-------------------------------------------------------------
void CTlgPrototypTreeViewForm::setTlgViewForm(CTlgViewForm^ tlgView)
{
	TlgViewForm = tlgView;
}
//-------------------------------------------------------------
void CTlgPrototypTreeViewForm::showTlgPrototyp()
{
	/*CTlgBaseWrapper* wrapper = CTlgBaseWrapper::getBaseTlgWrapper();
	int count;
	String^ val=0;

	if(wrapper != 0)
	{
		treeViewTlgPrototyp->Nodes->Clear();
		System::Windows::Forms::TreeNode* node=0;
		count = wrapper->getTlgPrototypCount();
		for(int i=1;i<=count;i++)
		{
			val=wrapper->getTlgPrototypName(i);
			node = new System::Windows::Forms::TreeNode(val);
			treeViewTlgPrototyp->Nodes->Add(node);
		}
	}*/
}
//---------------------------------------
 /*int CTlgPrototypTreeViewForm::showTlgPrototyp(CBaseTlgFactoryWrapper* TlgFactory)
 {
    int count;
    int ret=0;
    String^ val=0;
    String^ Descr=0;
    String^ Direc=0;

    TlgFactoryWrapper=TlgFactory;
    if( TlgFactoryWrapper != 0)
	  {
      UpdateModus = false;
      treeViewTlgPrototyp->BeginUpdate();
      //treeViewTlgPrototyp->is
       //treeViewTlgPrototyp->Af
      treeViewTlgPrototyp->Nodes->Clear();
		  System::Windows::Forms::TreeNode* node=0;
      count=TlgFactory->getTlgCount();
      ret=count;
      for(int i=1;i<=count;i++)
		  {
        val =  TlgFactoryWrapper->getTlgName(i);
        TlgFactoryWrapper->getTlgDescr(i,Descr,Direc);
        val = String::Concat(val,"  (",Descr,")");
        node = new System::Windows::Forms::TreeNode(val);
			  treeViewTlgPrototyp->Nodes->Add(node);
      }
      treeViewTlgPrototyp->EndUpdate();
      UpdateModus = true;
    }
 
    treeViewTlgPrototyp->set_SelectedNode(treeViewTlgPrototyp->Nodes[0));

    return ret;
 }*/
//---------------------------------------


