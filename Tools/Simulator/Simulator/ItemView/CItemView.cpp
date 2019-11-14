#include "StdAfx.h"
#include "CItemView.h"
#include "CItemWrapper.h"
#include "CTlgElemWrapper.h"
#include "CExpWrapper.h"
#include "CTlgElemWrapper.h"
#include "CTlgWrapper.h"
#include "CInterConfigWrapper.h"
#include "CCyclicItemContainer.h"
#include "CLogWriterWrapper.h"
#include "CFormatConverterWrapper.h"

using namespace simulator;
using namespace System;

//-------------------------------------------------------
void CItemView::InitComponets(Panel^ parent)
{
  this->Parent = parent;

  //Initialisierung der Variablen mit Default Werten
  this->editMode = true;
  this->typForm = CreateTypForm::none;
  this->selectNode = nullptr;
  this->ErrorMessageDel = nullptr;
  this->interfaceName = nullptr;
  //this->isProtoTypItem = false;
  this->isReciever = false;
  this->protoItem = nullptr;
  this->ItemId = nullptr;
  this->ItemElemId = nullptr;
  this->ItemLenId = nullptr;
  this->ItemIdValue = nullptr;
  this->LenIdModus = 0;
  this->SzenarioChangeEvent = nullptr;
  
  //Context Menu
  this->m_contextMenu = gcnew System::Windows::Forms::ContextMenu();
  this->m_contextMenu->MenuItems->Add(gcnew MenuItem("Collapse all node", gcnew EventHandler(this,&CItemView::OnCollapseAllNodes)));
	this->m_contextMenu->MenuItems->Add(gcnew MenuItem("Expand all node", gcnew EventHandler(this,&CItemView::OnExpandAllNodes)));
 
  //m_tree
  this->m_tree->ContextMenu = this->m_contextMenu;

  //
  this->m_validator = gcnew CNodeCollectionUnit(m_tree->Nodes);
  
  //Input Text Box
  this->txtBx = gcnew System::Windows::Forms::TextBox();
	this->txtBx->AutoSize = false;
	this->txtBx->Parent=m_tree;
	this->txtBx->Hide();
  this->txtBx->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this,&CItemView::txtBoxEnter);
  this->txtBx->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this,&CItemView::TxtBox_KeyDown);
	
  //ToolBar
  this->toolBar=gcnew System::Windows::Forms::ToolBar();
  this->toolBar->Hide(); 
  //
  this->KeyPreview = true;
  //
  ItemViewList->Add(this);
  //
  //this->DoubleBuffered = true;
  this->SetStyle(ControlStyles::DoubleBuffer, true);

  /*InfoDesc->Parent=m_tree;*/
  /*InfoDesc->Hide();*/
  /*this->txtBoxDLL = new CtrlLib::NumEdit();
  this->txtBoxDLL->AutoSize = false;
  this->txtBoxDLL->Name = "txtBoxDLL";
  this->txtBoxDLL->Parent=m_tree;
  this->txtBoxDLL->Hide();
  this->txtBoxDLL->KeyPress += new System::Windows::Forms::KeyPressEventHandler(this,&CItemView::txtBoxEnter);*/   
}
//-------------------------------------------------------
void CItemView::InitMTree()
{
  //Columns
  CommonTools::TreeListColumn^ treeListColumn1 = gcnew CommonTools::TreeListColumn("element","Element");
  CommonTools::TreeListColumn^ treeListColumn2 = gcnew CommonTools::TreeListColumn("value", "Value");
  CommonTools::TreeListColumn^ treeListColumn3 = gcnew CommonTools::TreeListColumn("unit", "Unit");
  CommonTools::TreeListColumn^ treeListColumn4 = gcnew CommonTools::TreeListColumn("typ", "Typ");
  CommonTools::TreeListColumn^ treeListColumn5 = gcnew CommonTools::TreeListColumn("len", "Len");
  CommonTools::TreeListColumn^ treeListColumn6 = gcnew CommonTools::TreeListColumn("tran", "Tran");
  CommonTools::TreeListColumn^ treeListColumn7 = gcnew CommonTools::TreeListColumn("factor", "Factor");
  CommonTools::TreeListColumn^ treeListColumn8 = gcnew CommonTools::TreeListColumn("min", "Min");
  CommonTools::TreeListColumn^ treeListColumn9 = gcnew CommonTools::TreeListColumn("max", "Max");
  CommonTools::TreeListColumn^ treeListColumn10 = gcnew CommonTools::TreeListColumn("decription", "Description");
  
	treeListColumn1->AutoSizeMinSize = 0;
  treeListColumn1->CellFormat->TextAlignment = System::Drawing::ContentAlignment::MiddleLeft;
  treeListColumn1->HeaderFormat->TextAlignment = System::Drawing::ContentAlignment::MiddleCenter;
  treeListColumn1->Width = 60;
  //----------------------------------------
  treeListColumn2->AutoSizeMinSize = 0;
  //treeListColumn2->AutoSizeMinSize = Windows::Forms::TextRenderer::MeasureText("Value",m_tree->Columns->Font).Width;
  //treeListColumn2->AutoSizeRatio = 2.0;
  //treeListColumn2->AutoSize=true;
  treeListColumn2->CellFormat->TextAlignment = System::Drawing::ContentAlignment::MiddleCenter;
  treeListColumn2->HeaderFormat->TextAlignment = System::Drawing::ContentAlignment::MiddleCenter;
  treeListColumn2->Width = 80;
  //----------------------------------------
  treeListColumn3->AutoSizeMinSize = 0;
  treeListColumn3->CellFormat->TextAlignment = System::Drawing::ContentAlignment::MiddleCenter;
  treeListColumn3->HeaderFormat->TextAlignment = System::Drawing::ContentAlignment::MiddleCenter;
  treeListColumn3->Width = 50;
  //----------------------------------------
  treeListColumn4->AutoSizeMinSize = 0;
  treeListColumn4->CellFormat->TextAlignment = System::Drawing::ContentAlignment::MiddleCenter;
  treeListColumn4->HeaderFormat->TextAlignment = System::Drawing::ContentAlignment::MiddleCenter;
  treeListColumn4->Width = 50;
  //----------------------------------------
  treeListColumn5->AutoSizeMinSize = 0;
  treeListColumn5->CellFormat->TextAlignment = System::Drawing::ContentAlignment::MiddleCenter;
  treeListColumn5->HeaderFormat->TextAlignment = System::Drawing::ContentAlignment::MiddleCenter;
  treeListColumn5->Width = 50;
  //----------------------------------------
  treeListColumn6->AutoSizeMinSize = 0;
  treeListColumn6->CellFormat->TextAlignment = System::Drawing::ContentAlignment::MiddleCenter;
  treeListColumn6->HeaderFormat->TextAlignment = System::Drawing::ContentAlignment::MiddleCenter;
  treeListColumn6->Width = 50;
  //----------------------------------------
  treeListColumn7->AutoSizeMinSize = 0;
  treeListColumn7->CellFormat->TextAlignment = System::Drawing::ContentAlignment::MiddleCenter;
  treeListColumn7->HeaderFormat->TextAlignment = System::Drawing::ContentAlignment::MiddleCenter;
  treeListColumn7->Width = 50;
  //----------------------------------------
  treeListColumn8->AutoSizeMinSize = 0;
  treeListColumn8->CellFormat->TextAlignment = System::Drawing::ContentAlignment::MiddleCenter;
  treeListColumn8->HeaderFormat->TextAlignment = System::Drawing::ContentAlignment::MiddleCenter;
  treeListColumn8->Width = 50;
  //----------------------------------------
  treeListColumn9->AutoSizeMinSize = 0;
  treeListColumn9->CellFormat->TextAlignment = System::Drawing::ContentAlignment::MiddleCenter;
  treeListColumn9->HeaderFormat->TextAlignment = System::Drawing::ContentAlignment::MiddleCenter;
  treeListColumn9->Width = 50;
  //----------------------------------------
  treeListColumn10->AutoSizeMinSize = Windows::Forms::TextRenderer::MeasureText("Description",m_tree->Columns->Font).Width;
  //treeListColumn10->AutoSizeRatio = 0.2;
  treeListColumn10->AutoSize=true;
  treeListColumn10->CellFormat->TextAlignment = System::Drawing::ContentAlignment::MiddleLeft;
  treeListColumn10->CellFormat->ForeColor = System::Drawing::Color::Blue;
  treeListColumn10->HeaderFormat->ForeColor = System::Drawing::Color::Blue;
  treeListColumn10->HeaderFormat->TextAlignment = System::Drawing::ContentAlignment::MiddleCenter;
  //treeListColumn10->Width = 300;

  //m_tree->MouseDoubleClick
  //System::Windows::Forms::TextRenderer::MeasureText(


  //CommonTools::TreeListColumn* temp __gc[] = {treeListColumn1, treeListColumn2, 
  //      treeListColumn3, treeListColumn4, treeListColumn5, treeListColumn6, treeListColumn7, treeListColumn8,
  //      treeListColumn9, treeListColumn10};

  //CommonTools::TreeListColumn* temp __gc[] = new CommonTools::TreeListColumn* __gc[10];
  
  //m_tree->Columns[9)->AutoSize=true;
  this->m_tree->Columns->AddRange(gcnew array <CommonTools::TreeListColumn^> {
            treeListColumn1,
            treeListColumn2,
            treeListColumn3,
            treeListColumn4,
            treeListColumn5,
            treeListColumn6,
            treeListColumn7,
            treeListColumn8,
            treeListColumn9,
            treeListColumn10});

  //Zeilenhoehe auf 19 Pixel setzen
  this->m_tree->RowOptions->ItemHeight = 19;
}
System::Void CItemView::OnMouseDoubleClick(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
  //Die Breite aller Felder auﬂer Description Feld berechnen
  int width = 0;
  for (int i = 0;i<m_tree->Columns->Count-1;i++)
    width+=m_tree->Columns[i]->Width;
  //Horizintale Scroll - Wert abziehen
  width-=m_tree->getHScrollValue();
  //Die Hoehe des Feldes 
  int height = m_tree->ColumnsOptions->HeaderHeight;

  //Wenn im Desc - Header - Bereich geklickt wurde
  if ((e->X > width && e->X < m_tree->Width) && e->Y < height)
  {
    if (m_tree->Columns[m_tree->Columns->Count-1]->AutoSize)
    {
      //max. Sting - Desc - Grieﬂe berechnen
      String^ desc = m_validator->getMaxDescription();
      Drawing::Size size = Windows::Forms::TextRenderer::MeasureText(desc,m_tree->Columns->Font);
      //AutoSize in Description Feld deaktivieren
      m_tree->Columns[m_tree->Columns->Count-1]->AutoSize=false;
      m_tree->Columns[m_tree->Columns->Count-1]->Width = size.Width;
    }
    else  //AutoSize in Description Feld aktivieren
      m_tree->Columns[m_tree->Columns->Count-1]->AutoSize=true;
    //Ansicht neu zeichnen
    m_tree->Columns->RecalcVisibleColumsRect(true);
    m_tree->RecalcLayout();
    m_tree->Refresh();
  }
}
//-------------------------------------------------------
System::Void CItemView::OnCloseForm(System::Object ^  sender, System::EventArgs ^  e)
{
}
//-------------------------------------------------------
System::Void CItemView::OnMouseWheel(System::Object^ sender,System::Windows::Forms::MouseEventArgs ^ e)
{
  this->txtBx->Hide();
}
//-------------------------------------------------------
System::Void CItemView::OnCollapseAllChildrenNodes(System::Object ^ sender,System::EventArgs ^ e)
{
  this->selectNode->Collapse();
}
//-------------------------------------------------------
System::Void CItemView::OnCollapseAllNodes(System::Object ^ sender,System::EventArgs ^ e)
{
  for (int i = 0;i<m_tree->Nodes->Count;i++)
  {
    safe_cast <CommonTools::Node^> (m_tree->Nodes[i])->Collapse();
  } 
  this->txtBx->Hide();
}
//-------------------------------------------------------
System::Void CItemView::OnExpandAllNodes(System::Object ^ sender,System::EventArgs ^ e)
{
  for (int i = 0;i<m_tree->Nodes->Count;i++)
  {
    safe_cast <CommonTools::Node^> (m_tree->Nodes[i])->ExpandAll();
  }
  this->txtBx->Hide();
}
//-------------------------------------------------------
void CItemView::setReceiveView()
{
  this->isReciever = true;  
  this->butAddToSzen->Visible = false;
  //panSenderSpez->Hide();
  // LenChange=true;
}
//-------------------------------------------------------
void CItemView::setCreateTypForm(CreateTypForm typ)
{
	this->typForm = typ;
}
//-------------------------------------------------------
void CItemView::setEditMode(bool edit)
{
  if (this->typForm == CreateTypForm::Szenario)
  {
    if (!edit)
    {
      this->txtBx->Hide();
      this->txtBx->Clear();
    }
    this->editMode = edit;
  }
}
//-------------------------------------------------------
bool CItemView::getEditMode(void)
{
  return this->editMode;
}
//-------------------------------------------------------
void CItemView::closeItemView (CreateTypForm typ)
{
	if (typ == this->typForm)
	{
		//Txt Box ausblenden
    this->txtBx->Clear();
		this->txtBx->Hide();
		this->m_validator->clear();
    //Groeﬂe des Desc-Feldes auf Auto wieder setzen
    m_tree->Columns[m_tree->Columns->Count-1]->AutoSize=true;
    //Ansicht neu zeichnen
    m_tree->Columns->RecalcVisibleColumsRect(true);
    m_tree->RecalcLayout();
    m_tree->Refresh();
	}
}
//-------------------------------------------------------
void CItemView::ShowItem(CItemWrapper^ item,CreateTypForm typ)
{ 
  maxElemDepth = 1;
  SavePreviousValue();
  
  this->typForm=typ;

  //Im Bezug auf TypForm EdidMode False oder True zuornden
  if ((typ == CreateTypForm::LogFile) || (typ == CreateTypForm::Receiver))
  {
    this->editMode=false;
  }
  else
  {
    this->editMode=true;
  }

	//Txt Box ausblenden
  this->txtBx->Clear();
  this->txtBx->Hide();

  ////Ansicht neu zeichnen
  //m_tree->Columns->RecalcVisibleColumsRect(true);
  //m_tree->RecalcLayout();
  //m_tree->Refresh();
  
  //Wenn Item Objekt existiert anzeigen
  if (item)
  {
    m_tree->BeginUpdate();
    this->interfaceName=item->getInterfece();
    CInterConfigWrapper^ interConf = gcnew CInterConfigWrapper();

    this->ItemId = interConf->getTlgIdName(interfaceName);
    this->ItemElemId = interConf->getElemId(interfaceName);
    this->ItemLenId = interConf->getElemLenId(interfaceName);
    this->LenIdModus = interConf->getLenIdTreatModus(interfaceName);
    this->ItemIdValue=interConf->getTlgId(interfaceName,item->getName());

    //Labels
    this->labDirectionInfo->Text=item->getTlgDirection();
    this->labItemName->Text=item->getName();
    if (CCyclicItemContainer::getCyclicItemContainer()->isItemInContainer(item))
      this->labItemDescr->Text=String::Concat("Cyclic          ",item->getTlgDescr());
    else
      this->labItemDescr->Text=item->getTlgDescr();
        
    switch (typ)
    {
      case CreateTypForm::Prototyp :
        this->labCreateTypForm->Text = "Interface";
        break;

      case CreateTypForm::LogFile :
        this->labCreateTypForm->Text = "LogFile";
        break;

      case CreateTypForm::Szenario :
        this->labCreateTypForm->Text = "Szenario";
        break;

      case CreateTypForm::Receiver :
        this->labCreateTypForm->Text = "Receiver";
        break;

      default :
        this->labCreateTypForm->Text = "None";
        break;
    }

    //ToolTips
    this->tBarItemName->SetToolTip(labItemName,item->getName());
    this->tBarItemDescription->SetToolTip(labItemDescr,item->getTlgDescr());
    this->tBarItemDirection->SetToolTip(labDirectionInfo,item->getTlgDirection());
    
    //Wenn Item Prototyp oder wenn Telegramm aus dem LogFile
    if ((typ == CreateTypForm::Prototyp))
    {
      this->butAddToSzen->Visible = true;
      //this->isProtoTypItem=true;
      CTlg* tlg = item->getClonedTlg();
      this->protoItem=gcnew CTlgWrapper();
      this->protoItem->setTlg(tlg);
      maxElemDepth = this->m_validator->ShowItem(protoItem,(int)typ);
    }
    else
    {
      this->butAddToSzen->Visible = false;
      //this->isProtoTypItem=false;
      this->protoItem=nullptr;
      maxElemDepth = this->m_validator->ShowItem(item,(int)typ);
    }

    //Collapse of all nodes, if requiet, else expand.
    CollapseOrExpandAllNode();

    CalcColumnsWidth();
    m_tree->EndUpdate();

    //Ansicht neu zeichnen
    m_tree->Columns->RecalcVisibleColumsRect(true);
    //Groeﬂe des Desc-Feldes auf Auto wieder setzen
    //Die Breite aller Felder auﬂer Description Feld berechnen
    int width = 0;
    for (int i = 0;i<m_tree->Columns->Count-1;i++)
      width+=m_tree->Columns[i]->Width;
    //Horizintale Scroll - Wert abziehen
    //width-=m_tree->getHScrollValue();
    //
    if (m_tree->Width - width< 0)
    {
      m_tree->Columns[m_tree->Columns->Count-1]->AutoSizeMinSize = Windows::Forms::TextRenderer::MeasureText("Description",m_tree->Columns->Font).Width;
      m_tree->Columns[m_tree->Columns->Count-1]->AutoSizeRatio=1.0;
      m_tree->Columns[m_tree->Columns->Count-1]->AutoSize=true;
    }
    else
    {
      //m_tree->Columns[m_tree->Columns->Count-1)->AutoSizeMinSize = Windows::Forms::TextRenderer::MeasureText("Description",m_tree->Columns->Font).Width;
      m_tree->Columns[m_tree->Columns->Count-1]->AutoSizeMinSize = m_tree->Width - width;
      //m_tree->Columns[m_tree->Columns->Count-1)->Width =m_tree->Width - width - m_tree->getVScroll()->Width;
      m_tree->Columns[m_tree->Columns->Count-1]->AutoSizeRatio=0.0;
      m_tree->Columns[m_tree->Columns->Count-1]->AutoSize=true;
    }
    /*m_tree->Columns[m_tree->Columns->Count-1)->AutoSizeMinSize = 0.0;
    m_tree->Columns[m_tree->Columns->Count-1)->AutoSizeMinSize = Windows::Forms::TextRenderer::MeasureText("Description",m_tree->Columns->Font).Width;*/
    
    
    
    
    //m_tree->Columns[m_tree->Columns->Count-1)->AutoSize=true;
    //Ansicht neu zeichnen
    m_tree->Columns->RecalcVisibleColumsRect(true);
    m_tree->RecalcLayout();
    m_tree->Refresh();
  } //end if (item) 

}
//--------------------------------------------------------
Void CItemView::VScrollChanged(Object ^ sender,Windows::Forms::ScrollEventArgs ^ e)
{
  this->txtBx->Hide();
}
//--------------------------------------------------------
Void CItemView::HScrollChanged(Object ^ sender,Windows::Forms::ScrollEventArgs ^ e)
{
  this->txtBx->Hide();
}
//--------------------------------------------------------
Void CItemView::OnEnterKey(Object ^ sender,Windows::Forms::KeyPressEventArgs ^ e)
{
  bool goodKey = (e->KeyChar >64 && e->KeyChar < 91) || (e->KeyChar >96 && e->KeyChar < 123)
      || (e->KeyChar >47 && e->KeyChar < 58);
  
  if ((e->KeyChar == '\r' || goodKey) && (this->m_tree->NodesSelection->Count > 0))
  {
    if (!this->txtBx->Visible)
    {        
      selectNode = nullptr;
      //int selCount = m_tree->get_NodesSelection()->Count-1;
      selectNode = this->m_tree->NodesSelection[0];
      if (selectNode)
      {
        if (selectNode->Expanded)
        {
          selectNode->Expanded = false;
        }
        else
        {
          if (selectNode->HasChildren)
          {
            selectNode->Expanded = true;
          }
          else
          {
            if (this->editMode)
            {
							 CTlgElemWrapper^ itemElem=nullptr;
							 String^ elemTyp=nullptr;
							 itemElem= safe_cast <CTlgElemWrapper^> (selectNode->Tag);
							 elemTyp=itemElem->getElemType();
							 bool ok = true;

							 if ((itemElem->getElemName()->Equals(ItemElemId)) && (!this->m_validator->getisIdTxtEnabled()))
							 {
									ok = false;
							 }
							 else if ((itemElem->getElemName()->Equals(ItemLenId)) && (!this->m_validator->getisLenTxtEnabled()))
							 {
									ok = false;
							 }

							if (ok)
						  {
									int itemHeight = m_tree->RowOptions->ItemHeight;
								 //int number = (Y - m_tree->RowOptions->get_HeaderWidth()) / itemHeight;
								 int itemNummer = getIndexOfNode(selectNode);
								 System::String^ tempValue = nullptr;
								 
								 if (m_tree->getHScrollValue()>0)
								 {
									 //Scroll aus 0 setzen
									 m_tree->getHScroll()->Value = 0;
									 //neu zeichen
									 m_tree->Refresh();
								 }
								 
								 int x = m_tree->Columns[0]->Width;
                 int test = m_tree->getVScrollValue();
                 int y = (itemHeight*(itemNummer - m_tree->getVScrollValue()));

								 //TextBox leeren
								this->txtBx->Clear();
                //TextBox fokusieren
			          this->txtBx->Focus();
                //X Position setzen
			          this->txtBx->Left = x + 15;
								//Y Position setzen
								this->txtBx->Top = y;
								
								this->txtBx->Height = itemHeight;
								this->txtBx->Width = m_tree->Columns[1]->Width;

								//Text aus dem Feld in Text Box kopieren
                if (goodKey)
                {
                  /*wchar_t * tmpKey =  e->KeyChar;*/                  
                  this->txtBx->Text = Convert::ToString(e->KeyChar);
                }
                else
                {
                  itemElem->getElemValue(tempValue);
                  if (tempValue)
                  {                    
                    this->txtBx->Text = tempValue;
                  }
                }

								//TextBox einbleden
                this->txtBx->Show();
                //TextBox fokusieren
		            this->txtBx->Focus();

                if (goodKey)
                  this->txtBx->SelectionStart=this->txtBx->SelectionLength;
        

								/*OkMessageDel->Invoke(System::Convert::ToString(getIndexOfNode(selectNode)));
								m_tree->Focus();*/
								
							}
						  else
							{
								//Textbox verstecken, wenn's Id oder Len Element ist
								this->txtBx->Hide();
							}  
            }
          }
        }
      } 
    }
  }

}
//--------------------------------------------------------
int CItemView::CalcNodeIndex(CommonTools::Node^ node)
{
  CommonTools::Node^ temp = node->Parent;
  //Falls Vater Node existiert
  if (temp)
  {
    return (node->NodeIndex + 1) + CalcNodeIndex(temp);
  }
  else
  {
    return node->NodeIndex+1;
  }
}
//--------------------------------------------------------
Void CItemView::OnMouseDownListViewEquals(Object ^ sender, Windows::Forms::MouseEventArgs ^ e)
{
  if ((!this->isReciever) && (this->editMode))
  {
    CTlgElemWrapper^ itemElem=nullptr;
    String^ elemTyp=nullptr;
    //Position des Scrolls
    int vScroll = m_tree->getVScrollValue();
    int hScroll = m_tree->getHScrollValue();
    int item_height = m_tree->RowOptions->ItemHeight;
    /*int item_height = 18;*/
    bool ok = true;
    
    
    if(m_validator->getItemCount() > 0)
    {
      //Wenn Mouse nicht auﬂer von Nodes geklickt wird oder wenn 
      //keine Node da ist.
      bool selectOk = (e->Y > m_tree->ColumnsOptions->HeaderHeight) 
                      && (e->Y < ((m_tree->Nodes->VisibleNodeCount*item_height) 
                       + m_tree->ColumnsOptions->HeaderHeight));
      
      if (true)
      {
        //Vorhandene Wert uebernehmen
        SavePreviousValue();
        //Selektierte Node rausholen 
        this->selectNode = nullptr;
        if (m_tree->NodesSelection->Count > 0)
          this->selectNode = this->m_tree->NodesSelection[0];
      }

      if (selectNode)
      {
        //Wenn kein Item zugeordnet wurde  
        if(this->selectNode->Tag!=nullptr)
        {
          itemElem= safe_cast <CTlgElemWrapper^> (selectNode->Tag);
          elemTyp=itemElem->getElemType();
        
          //String^ test = itemElem->getElemName();

          if ((itemElem->getElemName()->Equals(ItemElemId)) && (!this->m_validator->getisIdTxtEnabled()))
          {
            ok = false;
          }
          else if ((itemElem->getElemName()->Equals(ItemLenId)) && (!this->m_validator->getisLenTxtEnabled()))
          {
            ok = false;
          }
          else 
          {
            ok = true;
          }

          if (ok)
          {
            int itemNummer = (e->Y/item_height) - 1;
	          if(itemNummer < this->m_tree->Nodes->VisibleNodeCount)
	          {
		          int i=0;
		          bool flag = false;
		          int m_width=0;
			        int columnCount = m_tree->Columns->Count; 

		          while((i<columnCount) && (!flag))
		          {
			          m_width=m_width+m_tree->Columns[i]->Width; 
			          if((e->X + hScroll) <= m_width)
			          {
				          flag=true;
			          }
                else
			          {
				          i++;
			          }
		          }
          
		          if((flag) && i==1)
		          {
                  int top = ((getIndexOfNode(selectNode)-1)*item_height);
                  top += m_tree->ColumnsOptions->HeaderHeight;
                  top -= m_tree->getVScrollValue()*item_height;
              
                  System::String^ tempValue = nullptr;
                  //Textbox verstecken
                  this->toolBar->Hide();
			            //Scroll beruecksichtigen 
                  m_width-=(this->m_tree->Columns[i]->Width + hScroll);
                  //TextBox leeren
                  this->txtBx->Clear();
                  //TextBox fokusieren
			            this->txtBx->Focus();
                  //X Position setzen
			            this->txtBx->Left = m_width + 15;
                  //Y Position setzen
			            this->txtBx->Top = top;
			            this->txtBx->Height = item_height;
			            this->txtBx->Width = m_tree->Columns[i]->Width;
                  //Text aus dem Feld in Text Box kopieren
                  itemElem->getElemValue(tempValue);
                  if (tempValue)
                  {
                    this->txtBx->Text = tempValue;
                  }
                  //TextBox einbleden
                  this->txtBx->Show();
                  //TextBox fokusieren
		              this->txtBx->Focus();
                
              }
		          else if ((flag) && i==9) //Wenn Feld 9 also Description
              {
               /* System::Drawing::Point point;
                point.set_X(e->X);
                point.set_Y(e->Y);
                String^ a = safe_cast <String^> (m_tree->CalcHitNode(point)[9));*/
               /* System::Windows::Forms::ToolTip* tip = new System::Windows::Forms::ToolTip(m_tree->CalcHitNode(point)->get);*/
     
                this->txtBx->Hide();
                //m_width-=this->m_tree->Columns[i)->Width;
                //this->InfoDesc->setFillDescription(itemElem->getElemDescription(),e->Y,e->X);
                ///*this->InfoDesc->setFillDescription(itemElem->getElemDescription(),m_width,
                //                             (itemNummer*item_height)+this->m_tree->ColumnsOptions->get_HeaderHeight());*/
                //this->InfoDesc->Show();
              }
		          else
              {
			         this-> txtBx->Hide();
		          }
            }
            else
            {
              //Textbox verstecken, wenn auﬂerhalb geklickt wurde
              this->txtBx->Hide();
            }
          }
          else
          {
            //Textbox verstecken, wenn's Id oder Len Element ist
            this->txtBx->Hide();
          }
        }
        else
        {
          //Textbox verstecken, wenn zu dem Node kein ItemElem gesetzt wurde
          this->txtBx->Hide();
        }
      }
      else
      {
         //Textbox verstecken, wenn kein Node selektiert wurde
        this->txtBx->Hide();
      }
    }
  }
  else
  {
    this->txtBx->Hide();
  }
}
//----------------------------------------------------
System::Void CItemView::TxtBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
  if ((!this->isReciever) && (this->editMode))
  {
    if (e->KeyCode == System::Windows::Forms::Keys::Up || e->KeyCode == System::Windows::Forms::Keys::Down)
    {
     /* m_tree->BeginUpdate();*/
      /*e->Handled = true;*/
      if (SavePreviousValue())
      {
        this->txtBx->Hide();
			  this->txtBx->Clear();
        if (e->KeyCode == System::Windows::Forms::Keys::Down)
          SelectNextEditableNode(this->selectNode,true);
        else
          SelectNextEditableNode(this->selectNode,false);
      }
      //else
      //{
      //  this->txtBx->Focus();
      //}
      ///*m_tree->EndUpdate();*/
      this->txtBx->Focus();
      //
      //this->txtBx->ResetCursor();
      //this->txtBx->ResetBindings();
      //this->txtBx->ResetImeMode();
      //this->txtBx->ResetFont();
      //this->txtBx->ResetRightToLeft();
      //this->txtBx->ResetText();
      //TextBox fokusieren
      this->txtBx->SelectAll();
      
      
      //txtBoxEnter(nullptr,nullptr);
    }
  }
}
//----------------------------------------------------
System::Void CItemView::txtBoxEnter(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) 
{ 
  if ((!this->isReciever) && (this->editMode))
  {
    if (e->KeyChar == '\r')
    {
      e->Handled = true;
      SavePreviousValue();
      return;
    }
    if (e->KeyChar == 27 )
    {
      e->Handled = true;
      this->txtBx->Hide();
			this->txtBx->Clear();
			m_tree->Focus();
      return;
    }
  }

  //Mit dieser Paramtern wird diese Ereigniss aus der Methode TxtBox_KeyDown aufgerufen,
  //weil da Text nicht selektiert werden kann.
  //if (sender == nullptr && e == nullptr)
  //{
  //  this->txtBx->SelectAll();
  //  return;
  //}


  //Fokus zurueck setzen
  //this->Focus();
}
//-----------------------------------------------------------------------
void CItemView::setErrorMessageDel(ErrorMessageDelTyp^ del)
{
  this->ErrorMessageDel = del;
}
//-----------------------------------------------------------------------
void CItemView::setOkMessageDel(OkMessageDelTyp^ info)
{
  this->OkMessageDel = info;
}
//-----------------------------------------------------------------------
void CItemView::setDelAddToSzen(AddItemToSzen^ del)
{
 this->DelAddItem=del;
}
//-----------------------------------------------------------------------
void CItemView::setSzenarioChangeEventTyp(SzenarioChangeEventTyp^ TypEvent)
{
  this->SzenarioChangeEvent=TypEvent;
}
//-----------------------------------------------------------------------
void CItemView::setTelElemEditEvent(TelElemEditEventTyp^ editEvent)
{
  this->TelElemEditEvent=editEvent;
}
//------------------------------------------------
System::Void CItemView::OnAddButtonClick(System::Object ^  sender, System::EventArgs ^  e)
{
  if ((this->typForm == CreateTypForm::Prototyp))
  {
    CItemWrapper^ tlgWr=nullptr;
    CTlgElemWrapper^ elem = nullptr; 
    String^ elemIdName = nullptr;
    int index = -1;
    CInterConfigWrapper^ interConf = gcnew CInterConfigWrapper();
    String^ line = nullptr;
    
    if(this->DelAddItem != nullptr)
    {
      String^ Error=nullptr;
      tlgWr=protoItem->clone();
      /*tlgWr->get*/
      String^ tempId=interConf->getTlgId(this->interfaceName,tlgWr->getName());
      
      if ((tempId->Equals("")) || (tempId->Equals(" ")))
      {
        String^ mess = String::Concat("No value for id - element in <",tlgWr->getName(),"> was defined");
				CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
																																__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
				this->ErrorMessageDel->Invoke(mess);
      }
      else
      {
        elemIdName = interConf->getElemId(interfaceName);
        elem = gcnew CTlgElemWrapper();
        if (tlgWr->getElem(1)->getSubElemCount()>0)
        {
          index = tlgWr->getSubElemIndex(tlgWr->getElemName(1),elemIdName);
          elem->setTlgElem(tlgWr->getElem(1)->getSubElem(index));
        }
        else
        {
          index = tlgWr->getElemIndex(elemIdName);
          elem->setTlgElem(tlgWr->getElem(index));
        }
        elem->setValue(tempId,interfaceName);
        
        line=tlgWr->getSerialiseTlgAsString("|");
        Error=tlgWr->fillTlg(line);
        if(!Error)
        {
          DelAddItem->Invoke(tlgWr,false);
        }
        else
        {
          CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,Error,
																																__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
					if(this->ErrorMessageDel)
          {
            this->ErrorMessageDel->Invoke(Error);
          }
        }
      }//end if ID empty 
    }//end if no deligate
  }//end if no prototyp
  /*DelAddItem->Invoke(protoItem,false);*/
}

/*
//--------------------------------------------------------
void CItemView::CalcSelectedNode(int Y)
{ 
  bool ok = true;
  //Item Hoehe
  int itemHeight = m_tree->RowOptions->get_ItemHeight();
  int number = (Y - m_tree->RowOptions->get_HeaderWidth()) / itemHeight;
	int countOfNode = getIndexOfNode(selectNode);
	
	
	number++;
  //Entgueltige Index des markierten Nodes
  int index = 0;
  CommonTools::Node* node = 0;
  CommonTools::Node* selNode = 0;

  do
  {
    node = m_tree->Nodes[index);
    if (node->get_Expanded())
    {
      index++;
      number--;
      selNode = getIndexOfNode(number,node);
      if (selNode)
      {
        ok = false;
        this->selectNode = selNode;
      }
    }
    else
    {
      index++;
      number--;
    }
  }
  while (number>0 || ok || index<m_tree->Nodes->Count); //Do While
}


/*
//Wird nicht gebraucht
//--------------------------------------------------------
CommonTools::Node* CItemView::getIndexOfNode(int &number,CommonTools::Node* node)
{
  int index = 0;
  CommonTools::Node* subNode = 0;
  CommonTools::Node* retNode = 0;

  do
  {
    subNode = node->Nodes[index);

    if (subNode->get_Expanded())
    {
      number--;
      retNode = getIndexOfNode (number,subNode);
      
      if (retNode)
      {
        return retNode; 
      }
    }
    else
    {
      number--; 
      index++;
      if (number == 0)
        return subNode;
    }
  }
  while ((index < node->Nodes->Count) || number>0);
  
  return 0;
}*/
//--------------------------------------------------------
////--------------------------------------------------------
//Void CItemView::OnColumnEnter(Object * sender,Windows::Forms::ColumnClickEventArgs * e)
//{
// 
//}

int CItemView::getIndexOfNode (CommonTools::Node^ node)
{
	int anzahl = 1;
	CommonTools::Node^ tempNode = nullptr;
	tempNode = node->PrevSibling;

	while (tempNode)
	{
		anzahl += tempNode->VisibleNodeCount;
		tempNode = tempNode->PrevSibling; 
	}

	if (node->Parent == nullptr)
		return (anzahl);
	else
		return (anzahl + getIndexOfNode(node->Parent));
}
//---------------------------------------------------------
bool CItemView::SavePreviousValue()
{
  if (selectNode && txtBx->Visible)
  {
    CTlgElemWrapper^ elem = safe_cast <CTlgElemWrapper^> (selectNode->Tag); 
    String^ text = txtBx->Text;
    String^ error = nullptr;
    String^ value = gcnew String("");
    error=elem->setValue(text,interfaceName);
    if (error == nullptr)
    {
      this->txtBx->Hide();
      elem->getElemValue(value);
      this->selectNode->setFieldData(1,value);
      //if (OkMessageDel)
      //{
      //  this->OkMessageDel->Invoke(String::Concat("Value : ",text," in ",
      //                                            elem->getElemName()," accepted"));
      //}
      
      if (SzenarioChangeEvent && typForm == CreateTypForm::Szenario)
        SzenarioChangeEvent->Invoke();
      //Falls die Breite des neuen eingegeben Wert groeﬂer ist, Breite des Feldes
      //in Item - Ansicht anpassen
      int tmpWidth = Windows::Forms::TextRenderer::MeasureText(text,m_tree->Columns->Font).Width;
      if (tmpWidth > m_tree->Columns[1]->Width)
        m_tree->Columns[1]->Width = tmpWidth;
      
      //Ansicht neu zeichnen
      m_tree->Columns->RecalcVisibleColumsRect(true);
      m_tree->RecalcLayout();
      m_tree->Refresh();
		  m_tree->Focus();
    }
    else
    {
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,error,
																																__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
			this->ErrorMessageDel->Invoke(error);
      elem->getElemValue(value);
      this->selectNode->setFieldData(1,value);
		  txtBx->Focus();
      return false;
    }
  }
  return true;
}
//---------------------------------------------------------------
void CItemView::CalcColumnsWidth()
{
  CTlgElemWrapper^ itemElem=nullptr;
  CommonTools::Node^ node = nullptr;
  int depth = 1;  

  m_tree->Columns[0]->Width = Windows::Forms::TextRenderer::MeasureText("Element",m_tree->Columns->Font).Width;
  m_tree->Columns[1]->Width = Windows::Forms::TextRenderer::MeasureText("Value",m_tree->Columns->Font).Width;
  m_tree->Columns[2]->Width = Windows::Forms::TextRenderer::MeasureText("Unit",m_tree->Columns->Font).Width;
  m_tree->Columns[3]->Width = Windows::Forms::TextRenderer::MeasureText("Typ",m_tree->Columns->Font).Width;
  m_tree->Columns[4]->Width = Windows::Forms::TextRenderer::MeasureText("Len",m_tree->Columns->Font).Width;
  m_tree->Columns[5]->Width = Windows::Forms::TextRenderer::MeasureText("Tran",m_tree->Columns->Font).Width;
  m_tree->Columns[6]->Width = Windows::Forms::TextRenderer::MeasureText("Factor",m_tree->Columns->Font).Width;
  m_tree->Columns[7]->Width = Windows::Forms::TextRenderer::MeasureText("Min",m_tree->Columns->Font).Width;
  m_tree->Columns[8]->Width = Windows::Forms::TextRenderer::MeasureText("Max",m_tree->Columns->Font).Width;
  
  for (int i=0; i<m_tree->Nodes->Count; i++)
  {
    node = m_tree->Nodes[i];
    if (node->Tag != nullptr)
    {
      itemElem = safe_cast <CTlgElemWrapper^> (node->Tag);
      CompareValueForColumnsWidth(itemElem);
    }
    else
    {
			CalcColumnsWidth(m_tree->Nodes[i]);
    }
  }
}
//--------------------------------------------------------------
void CItemView::CalcColumnsWidth(CommonTools::Node^ node)
{
  CTlgElemWrapper^ itemElem=nullptr;
  CommonTools::Node^ subNode = nullptr;
  for (int i=0; i<node->Nodes->Count; i++)
  {
    subNode = node->Nodes[i];
    if (subNode->Tag != nullptr)
    {
      itemElem = safe_cast <CTlgElemWrapper^> (subNode->Tag);
      CompareValueForColumnsWidth(itemElem);
    }
    else   
      CalcColumnsWidth(subNode);
  }
}
//---------------------------------------------------------------
void CItemView::CompareValueForColumnsWidth(CTlgElemWrapper^ itemElem)
{
  int tmpWidth = 0; 
  String^ value = nullptr;
  String^ unit = "";
  String^ factor = "";
  String^ max = "";
  String^ min = "";

  //Element
  value = itemElem->getElemName();
  tmpWidth = Windows::Forms::TextRenderer::MeasureText(value,m_tree->Columns->Font).Width;
  if ((tmpWidth + (maxElemDepth*20)) > m_tree->Columns[0]->Width)
      m_tree->Columns[0]->Width = (tmpWidth + (maxElemDepth*20));
  //Value
  tmpWidth = Windows::Forms::TextRenderer::MeasureText(m_validator->getElemValue(),m_tree->Columns->Font).Width;
  if (tmpWidth > m_tree->Columns[1]->Width)
      m_tree->Columns[1]->Width = tmpWidth;
  //Unit,Factor,Min,Max
  itemElem->getElemInfo(unit,factor,min,max);
  //Unit
  tmpWidth = Windows::Forms::TextRenderer::MeasureText(unit,m_tree->Columns->Font).Width;
  if (tmpWidth > m_tree->Columns[2]->Width)
      m_tree->Columns[2]->Width = tmpWidth;
  //Factor
  tmpWidth = Windows::Forms::TextRenderer::MeasureText(factor,m_tree->Columns->Font).Width;
  if (tmpWidth > m_tree->Columns[6]->Width)
      m_tree->Columns[6]->Width = tmpWidth;
  //Min
  tmpWidth = Windows::Forms::TextRenderer::MeasureText(min,m_tree->Columns->Font).Width;
  if (tmpWidth > m_tree->Columns[7]->Width)
      m_tree->Columns[7]->Width = tmpWidth;
  //Max
  tmpWidth = Windows::Forms::TextRenderer::MeasureText(max,m_tree->Columns->Font).Width;
  if (tmpWidth > m_tree->Columns[8]->Width)
      m_tree->Columns[8]->Width = tmpWidth;
  //Typ
  value = itemElem->getElemType();
  tmpWidth = Windows::Forms::TextRenderer::MeasureText(value,m_tree->Columns->Font).Width;
  if (tmpWidth > m_tree->Columns[3]->Width)
      m_tree->Columns[3]->Width = tmpWidth;
  //Len
  value = CFormatConverterWrapper::IntToString(itemElem->getElemLenght());     
  tmpWidth = Windows::Forms::TextRenderer::MeasureText(value,m_tree->Columns->Font).Width;
  if (tmpWidth > m_tree->Columns[4]->Width)
      m_tree->Columns[4]->Width = tmpWidth;
  //Tran
  value = itemElem->getElemTransport();     
  tmpWidth = Windows::Forms::TextRenderer::MeasureText(value,m_tree->Columns->Font).Width;
  if (tmpWidth > m_tree->Columns[5]->Width)
      m_tree->Columns[5]->Width = tmpWidth;
}
//--------------------------------------------------------------
void CItemView::SelectNextEditableNode(CommonTools::Node^ node,bool forward)
{
  CommonTools::Node^ tmpNode;
  if (forward)
    tmpNode = m_tree->Nodes->GetNextNode(node,1);
  else
    tmpNode = m_tree->Nodes->GetNextNode(node,-1);
  
  if (tmpNode)
  {
    if (tmpNode->HasChildren)
    {
      tmpNode->Expand();
      SelectNextEditableNode(tmpNode,forward);
      return;
    }
    else
    {
      CTlgElemWrapper^ itemElem=nullptr;
			String^ elemTyp=nullptr;
			itemElem= safe_cast <CTlgElemWrapper^> (tmpNode->Tag);
			elemTyp=itemElem->getElemType();
		
			if (((itemElem->getElemName()->Equals(ItemElemId)) && (!this->m_validator->getisIdTxtEnabled()))  || 
        ((itemElem->getElemName()->Equals(ItemLenId)) && (!this->m_validator->getisLenTxtEnabled())))
      {
        SelectNextEditableNode(tmpNode,forward);
        return;
      }

      m_tree->NodesSelection->Clear();
      m_tree->FocusedNode = nullptr;
      m_tree->Update();
     
      //Node selektieren
      m_tree->NodesSelection->Add(tmpNode);
      this->selectNode = tmpNode;
      m_tree->FocusedNode = tmpNode;
      //Ansicht neu zeichnen
      m_tree->Columns->RecalcVisibleColumsRect(true);
      m_tree->RecalcLayout();
      m_tree->Refresh();
   
      //Breite und Hoehe des Textboxes berechnen
      int itemHeight = m_tree->RowOptions->ItemHeight;
		   //int number = (Y - m_tree->RowOptions->get_HeaderWidth()) / itemHeight;
		   int itemNummer = getIndexOfNode(tmpNode);
		   System::String^ tempValue = nullptr;
  		 
		   if (m_tree->getHScrollValue()>0)
		   {
			   //Scroll aus 0 setzen
			   m_tree->getHScroll()->Value = 0;
			   //neu zeichen
			   m_tree->Refresh();
		   }
  		 
		   int x = m_tree->Columns[0]->Width;
       int y = (itemHeight*(itemNummer - m_tree->getVScrollValue()));

		    //TextBox leeren
		    this->txtBx->Clear();
        //TextBox fokusieren
        this->txtBx->Focus();
        //X Position setzen
        this->txtBx->Left = x + 15;
		    //Y Position setzen
		    this->txtBx->Top = y;
		
		    this->txtBx->Height = itemHeight;
		    this->txtBx->Width = m_tree->Columns[1]->Width;

        itemElem->getElemValue(tempValue);
        if (tempValue)
        {
          this->txtBx->Text = tempValue;
        }
    
				//TextBox einbleden
        this->txtBx->Show();
        this->txtBx->Focus();
        ////Selektierung vorheriges Nodes aufheben
        //m_tree->NodesSelection->Remove(node);
    }
  }
}
//---------------------------------------------------------------------
void CItemView::setNodesCollapsed(int val)
{
  if (val < 0)
    NodesCollapsed = -1;
  else if (val > 0)
    NodesCollapsed = 1;
  else
    NodesCollapsed = 0;

  if (ItemViewList)
  {
    CItemView^ tmp = nullptr;
    for (int i = 0;i<ItemViewList->Count;i++)
    {
      tmp = safe_cast <CItemView^> (ItemViewList[i]);
      if (tmp)
        tmp->CollapseOrExpandAllNode();
    }
  }
}
//---------------------------------------------------------------------
void CItemView::CollapseOrExpandAllNode()
{
  if (NodesCollapsed >= 0)
  {
    OnCollapseAllNodes(nullptr,nullptr);
    if (NodesCollapsed == 0 && m_tree->Nodes->FirstNode)
    {
      if (m_tree->Nodes->FirstNode->HasChildren)
      {
        CommonTools::Node^ tmp = nullptr;
        m_tree->Nodes->FirstNode->Expand();
        for (int i=0;i<m_tree->Nodes->FirstNode->Nodes->Count;i++)
        {
          tmp = m_tree->Nodes->FirstNode->Nodes[i];
          if (tmp && tmp->HasChildren)
            tmp->Collapse();
        }
      }
    }
  }
  else
    OnExpandAllNodes(nullptr,nullptr);
  
}