#include "StdAfx.h"
#include "CDataGridContainerForm.h"
#include "CItemWrapper.h"
#include "CTlgDataGridViewForm.h"
#include "CMessageForm.h"
#include "CLogWriterWrapper.h"

using namespace simulator;

//-----------------------------------------------------------------
void CDataGridContainerForm::CloseSelectedTabPage()
{
  if (tabControl1 && tabControl1->TabCount > 0 && tabControl1->SelectedTab)
    removeItem(tabControl1->SelectedTab->Name);
}
//-----------------------------------------------------------------
void CDataGridContainerForm::AddNewTabPage(CItemWrapper^ item)
{
  // NewTabPage 
  System::Windows::Forms::TabPage^ newTabPage;
  newTabPage = gcnew System::Windows::Forms::TabPage();
  newTabPage->Name = item->getName();
  newTabPage->Text = item->getName();
  CTlgDataGridViewForm^ newDataGrid = gcnew CTlgDataGridViewForm(newTabPage);
  newDataGrid->addItem(item);
  //Add To HashTable
  DataGridCon->Add(item->getName(),newDataGrid);
  //Add Page To TabControl
  this->tabControl1->SuspendLayout();
  this->SuspendLayout();
  tabControl1->TabPages->Add(newTabPage);  
  this->tabControl1->ResumeLayout(false);
  this->ResumeLayout(false);
  //Select New TabPage
  tabControl1->SelectedTab = newTabPage;
}
//-----------------------------------------------------------------
void CDataGridContainerForm::ShowDataGrid(String^ name)
{
  Show();
  if (!DataGridCon->Contains(name))
    return;
  
  CTlgDataGridViewForm ^ tmp = nullptr;
  tmp = safe_cast <CTlgDataGridViewForm^> (DataGridCon[name]);
 
  if (!tmp)
    return;

  tmp->Show();
}
//-----------------------------------------------------------------
void CDataGridContainerForm::removeItem(String^ name)
{
  if (!DataGridCon->Contains(name))
  {
     String^ mess = System::String::Concat("Telegramm <",name,"> not found");
		 CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
		 if (MessageForm)
       MessageForm->writeLine(mess,CMessageForm::MessTyp::Error);
    return;
  }

  DataGridCon->Remove(name);
  this->tabControl1->SuspendLayout();
  this->SuspendLayout();
  tabControl1->TabPages->Remove(tabControl1->TabPages[name]); 
  this->tabControl1->ResumeLayout(false);
  this->ResumeLayout(false);

  if (tabControl1->TabPages->Count > 0)
    tabControl1->SelectedIndex = 0;
  tabControl1->Refresh();
}
//-----------------------------------------------------------------
void CDataGridContainerForm::addItem(CItemWrapper^ item)
{
  if (DataGridCon->Contains(item->getName()))
    return;
  
  AddNewTabPage(item);
  
  //CTlgDataGridViewForm ^ tmp = nullptr;
  //
  //tmp = safe_cast <CTlgDataGridViewForm^> (DataGridCon[item->getName()));
  //if (!tmp)
  //  return;
  //tmp->addItem(item);
}
//-----------------------------------------------------------------
void CDataGridContainerForm::addItemValue(CItemWrapper^ item)
{
  if (!DataGridCon->Contains(item->getName()))
    return;
  
  CTlgDataGridViewForm ^ tmp = nullptr;
  tmp = safe_cast <CTlgDataGridViewForm^> (DataGridCon[item->getName()]);

  if (!tmp)
    return;

  tmp->addItemValue(item);
}
//-----------------------------------------------------------------
bool CDataGridContainerForm::IsItemInside(String^ name)
{
  return DataGridCon->Contains(name);
}
//-----------------------------------------------------------------
ArrayList^ CDataGridContainerForm::getItemNames()
{
  ArrayList^ ret = gcnew ArrayList();
  String^ name = nullptr;
  System::Collections::IEnumerator^ iterator = nullptr;
  //Mit dem Iterator alle Sting - Keys in HashTable auslesen
  iterator = DataGridCon->Keys->GetEnumerator();
  iterator->Reset();
  while(iterator->MoveNext())
  {
    name = safe_cast <String^> (iterator->Current);
    if (name)
      ret->Add(name);
  }
  return ret;
}
//-----------------------------------------------------------------
int CDataGridContainerForm::getCountOfRows(String^ name)
{
  CTlgDataGridViewForm ^ tmp = nullptr;
  if (!DataGridCon->Contains(name))
    return 0;
  tmp = safe_cast <CTlgDataGridViewForm^> (DataGridCon[name]);
  if (!tmp)
    return 0;
  return tmp->getCountOfRows();
}
//-----------------------------------------------------------------
void CDataGridContainerForm::setFilter(String^ name)
{
  if (!DataGridCon->Contains(name))
    return;
  
  CTlgDataGridViewForm ^ tmp = nullptr;
  tmp = safe_cast <CTlgDataGridViewForm^> (DataGridCon[name]);
 
  if (!tmp)
    return;

  tmp->ShowData();
}
//---------------------------------------------
void CDataGridContainerForm::setPointerOfMessage(CMessageForm^ MessageForm)
{
  this->MessageForm=MessageForm;
}