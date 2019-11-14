#include "StdAfx.h"
#include "CTlgDataGridViewForm.h"
#include "CItemWrapper.h"
#include "CTlgElemWrapper.h"
#include "CElemDescription.h"

using namespace simulator;
//--------------------------------------------------------
void CTlgDataGridViewForm::initViewComponent(Panel^ parent)
{
	this->Dock = DockStyle::Fill;
  this->TopLevel = false;
  this->Parent = parent;
  this->ItemName = nullptr;
  this->table = gcnew System::Data::DataTable();
}
//--------------------------------------------------------
System::String^ CTlgDataGridViewForm::getItemName()
{
  return this->ItemName;
}
//--------------------------------------------------------
void CTlgDataGridViewForm::addItemElem(CTlgElemWrapper^ item)
{
  int rootCount = item->getSubElemCount();
  CTlgElemWrapper^ itemElem=nullptr;
  System::Data::DataColumn^ dataColumn=nullptr;
  itemElem = gcnew CTlgElemWrapper();

  for (int i=1;i<=rootCount;i++)
  {
    itemElem->setTlgElem(item->getSubElem(i)); 

		//Wenn Sub-Elementen enthalten sind
    if (itemElem->getSubElemCount() > 0)
    {
      addItemElem(itemElem);
    }
    else
    {
      switch (itemElem->getElemTypeAsEnum())
		  {
			  case CElemDescription::tInteger :
				  dataColumn = gcnew System::Data::DataColumn(itemElem->getElemName(),System::Type::GetType("System.Int32"));
				  break;

			  case CElemDescription::tFloat :
				  dataColumn = gcnew System::Data::DataColumn(itemElem->getElemName(),System::Type::GetType("System.Float"));
				  break;

			  case CElemDescription::tDouble :
				  dataColumn = gcnew System::Data::DataColumn(itemElem->getElemName(),System::Type::GetType("System.Double"));
				  break;

			  default:
				  dataColumn = gcnew System::Data::DataColumn(itemElem->getElemName(),System::Type::GetType("System.String"));
				  break;
		  }
  		
		  //Column Erzeugen
      dataColumn->Caption = itemElem->getElemName();
      dataColumn->ReadOnly=true;
      //Add to table
      table->Columns->Add(dataColumn);
    } 
  }
}
//--------------------------------------------------------
int CTlgDataGridViewForm::getCountOfRows()
{
  return table->Rows->Count;
}
//--------------------------------------------------------
void CTlgDataGridViewForm::addItem(CItemWrapper^ item) 
{
  this->ItemName = item->getName();
  //this->dataGridView1->AutoGenerateColumns = true;

	if (item)
  {
    int rootCount = item->getTlgElemCount();
    CTlgElemWrapper^ itemElem=nullptr;
    System::Data::DataColumn^ dataColumn=nullptr;
    itemElem = gcnew CTlgElemWrapper();

    for (int i=1;i<=rootCount;i++)
    {
      itemElem->setTlgElem(item->getElem(i)); 
      
      if (itemElem->getSubElemCount() > 0)
      {
        addItemElem(itemElem);
      }
      else
      {
        //Column Erzeugen
			  switch (itemElem->getElemTypeAsEnum())
			  {
				  case CElemDescription::tInteger :
					  dataColumn = gcnew System::Data::DataColumn(itemElem->getElemName(),System::Type::GetType("System.Int32"));
					  break;

				  case CElemDescription::tFloat :
					  dataColumn = gcnew System::Data::DataColumn(itemElem->getElemName(),System::Type::GetType("System.Float"));
					  break;

				  case CElemDescription::tDouble :
					  dataColumn = gcnew System::Data::DataColumn(itemElem->getElemName(),System::Type::GetType("System.Double"));
					  break;

				  default:
					  dataColumn = gcnew System::Data::DataColumn(itemElem->getElemName(),System::Type::GetType("System.String"));
					  break;
			  }
        dataColumn->Caption = itemElem->getElemName();
        dataColumn->ReadOnly=true;
        //Add to table
        table->Columns->Add(dataColumn);
      } 
    }

    this->gridView1->BeginInit();
    //Table zu DataView als Source zuweisen
    this->gridControl1->DataSource = table;
    //Die Breite des Haeders automatisch anpassen
    int widht;
    DevExpress::XtraGrid::Columns::GridColumn^ tmp = nullptr;
    for (int i=0;i < this->gridView1->Columns->Count;i++)
    {
      tmp = this->gridView1->Columns[i];
      if (tmp)
      {
        widht = Windows::Forms::TextRenderer::MeasureText(tmp->FieldName,this->gridView1->Appearance->HeaderPanel->Font).Width;      
        if (tmp->Width < (widht + 15))
          tmp->Resize(widht + 15);
      }
    }
    this->gridView1->EndInit();
  }
}
//--------------------------------------------------------
void CTlgDataGridViewForm::addItemValue(CItemWrapper^ item)
{
    System::Data::DataRow^ row = table->NewRow();

    CTlgElemWrapper^ itemElem=nullptr;
    itemElem = gcnew CTlgElemWrapper();
    String^ value=nullptr;

    for (int i=1;i<=item->getTlgElemCount();i++)
    {
      value=nullptr;
      itemElem->setTlgElem(item->getElem(i)); 

      if (itemElem->getSubElemCount() > 0)
        addItemElemValue(itemElem,row);
      else
      {
        itemElem->getElemValue(value);
        if (value)
          row[itemElem->getElemName()] = value;
        else
          row[itemElem->getElemName()] = " ";
      }
    }
    table->Rows->Add(row); 
    this->gridView1->ClearSelection();
    this->gridView1->SelectRow( this->gridView1->RowCount - 1);
    //this->dataGridView1->Refresh();
}
//--------------------------------------------------------
void CTlgDataGridViewForm::addItemElemValue(CTlgElemWrapper^ item,System::Data::DataRow^ row)
{
  CTlgElemWrapper^ itemElem=nullptr;
  itemElem = gcnew CTlgElemWrapper();
  String^ value=nullptr;
  String^ name=nullptr;

  for (int i=1;i<=item->getSubElemCount();i++)
  {
    itemElem->setTlgElem(item->getSubElem(i)); 
  
    if (itemElem->getSubElemCount() > 0)
      addItemElemValue(itemElem,row);
    else
    {
      itemElem->getElemValue(value);
      if (value)
        row[itemElem->getElemName()] = value;
      else
        row[itemElem->getElemName()] = " ";
    }
  }
}
void CTlgDataGridViewForm::ShowData()
{
  //int widht;
  //this->gridView1->BeginInit();
  //this->gridControl1->DataSource = table;
  //DevExpress::XtraGrid::Columns::GridColumn^ tmp = nullptr;
  //for (int i=0;i < this->gridView1->Columns->Count;i++)
  //{
  //  tmp = this->gridView1->Columns[i);
  //  if (tmp)
  //  {
  //    widht = Windows::Forms::TextRenderer::MeasureText(tmp->FieldName,this->gridView1->Appearance->HeaderPanel->Font).get_Width();      
  //    if (tmp->Width < (widht + 15))
  //      tmp->Resize(widht + 15);
  //  }
  //}
  //this->gridView1->EndInit();
}