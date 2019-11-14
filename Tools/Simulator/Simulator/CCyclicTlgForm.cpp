#include "StdAfx.h"
#include "CCyclicTlgForm.h"
#include "CTlgElemWrapper.h"
#include "CItemWrapper.h"
#include "CFormatConverterWrapper.h"
#include "CCyclicElemTable.h"
#include "CCyclicElemStatus.h"
#include "CCyclicItemContainer.h"
#include "CXmlCyclicTlgWriter.h"
#include "CXmlCyclicTlgReader.h"
#include "CExpWrapper.h"
#include "CLogWriterWrapper.h"
#include "CAppSetting.h"

using namespace simulator;
using namespace System;

//------------------------------------------------------------
void CCyclicTlgForm::initComponent()
{
  ClearView();
  showAll();
  initToolTips();
}
//------------------------------------------------------------
void CCyclicTlgForm::initToolTips()
{
  //Math. Operation
  Windows::Forms::ToolTip^ tmp =gcnew Windows::Forms::ToolTip();
  String^ mess = "This mathematical operation is used in the calculation of cyclical values.";
  tmp->SetToolTip(this->labMathOp,mess);
  tmp->SetToolTip(this->comBxChange,mess);
  //Start value
  tmp = gcnew Windows::Forms::ToolTip();
  mess = "By default this value with a real value of the element is initialized.";
  tmp->SetToolTip(this->labStartValue,mess);
  tmp->SetToolTip(this->txtBxStartValue,mess);
  //Value of Op.
  tmp = gcnew Windows::Forms::ToolTip();
  mess = "With each cyclical operation of this value is used together with the mathematical operation.\n"; 
  mess += "With this information cyclical value is calculated.";
  tmp->SetToolTip(this->labValueChange,mess);
  tmp->SetToolTip(this->txtBxValueChange,mess);
  //Max. Value
  tmp = gcnew Windows::Forms::ToolTip();
  mess = "This declaration indicates the upper bound.";
  tmp->SetToolTip(this->labMax,mess);
  tmp->SetToolTip(this->txtBxMaxValue,mess);
  //Min. Value
  tmp = gcnew Windows::Forms::ToolTip();
  mess = "This declaration indicates the lower limit.";
  tmp->SetToolTip(this->labMin,mess);
  tmp->SetToolTip(this->txtBxMinValue,mess);
  //Set Default Values
  tmp = gcnew Windows::Forms::ToolTip();
  mess = "Maximal value is set to 10000 and minimal value is set to 1";
  tmp->SetToolTip(this->butDefaultsValues,mess);
  //Close Button
  tmp = gcnew Windows::Forms::ToolTip();
  mess = "This dialog is thus closed. Settings made, however, not automatically saved to the file.";
  tmp->SetToolTip(this->butClose,mess);
  //XML Load
  tmp = gcnew Windows::Forms::ToolTip();
  mess = "Configuration is loaded from a xml file.";
  tmp->SetToolTip(this->butLoad,mess);
  //XML Save
  tmp = gcnew Windows::Forms::ToolTip();
  mess = "Configuration is saved in a xml file.";
  tmp->SetToolTip(this->butSave,mess);
  //Minimum Value
  tmp = gcnew Windows::Forms::ToolTip();
  mess = "Expression to a minimum possible value set";
  tmp->SetToolTip(this->butMinValue,mess);
  //Maximum value
  tmp = gcnew Windows::Forms::ToolTip();
  mess = "Expression to a maximum possible value set.";
  tmp->SetToolTip(this->butMaxValue,mess);
  //Remove selected Item
  tmp = gcnew Windows::Forms::ToolTip();
  mess = "Selected telegram or telegram selected item is removed by pressing this button.";
  tmp->SetToolTip(this->butRemove,mess);
  //Cyclic Time
  tmp = gcnew Windows::Forms::ToolTip();
  mess = "Time interval for sending a cyclic telegram. Time, measured in milliseconds.";
  tmp->SetToolTip(this->textBxTimeInterval,mess);
  tmp->SetToolTip(this->labTimeInterval,mess);
  
}
//------------------------------------------------------------
System::Void CCyclicTlgForm::txtBxValueChange_Leave(System::Object^  sender, System::EventArgs^  e) 
{
  try
  {
    if (selectedElemTable && selectedElem)
    {
      //Zeitangabe in Double konventieren
      selectedElemTable->getElemStatus(selectedElem)->setVariabelValue(CFormatConverterWrapper::StringToDouble(txtBxValueChange->Text));
      //neue Wert Text zuweisen
      txtBxValueChange->Text = CFormatConverterWrapper::DoubleToString(selectedElemTable->getElemStatus(selectedElem)->getVariabelValue());
    }
  }
    catch (CExpWrapper^ e)
    {
			CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,e->getMessage(),
																														__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
			System::Windows::Forms::MessageBox::Show(nullptr,e->getMessage(),
                                        "",
                                        MessageBoxButtons::OK,
                                        MessageBoxIcon::Warning);
      //Fokus zurueck setzen
      txtBxValueChange->Focus();
  }      
}
//------------------------------------------------------------
System::Void CCyclicTlgForm::txtBxValueChange_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) 
{
  if (e->KeyChar == 13) //Enter
   {
     try
      {
        if (selectedElemTable && selectedElem)
        {
          //Zeitangabe in Double konventieren
          selectedElemTable->getElemStatus(selectedElem)->setVariabelValue(CFormatConverterWrapper::StringToDouble(txtBxValueChange->Text));
          //neue Wert Text zuweisen
          txtBxValueChange->Text = CFormatConverterWrapper::DoubleToString(selectedElemTable->getElemStatus(selectedElem)->getVariabelValue());
          //Fokus weiter setzen
          txtBxMinValue->Focus();
        }
      }
      catch (CExpWrapper^ e)
      {
				CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,e->getMessage(),
																														__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        System::Windows::Forms::MessageBox::Show(nullptr,e->getMessage(),
                                          "",
                                          MessageBoxButtons::OK,
                                          MessageBoxIcon::Warning);
        //Fokus zurueck setzen
        txtBxValueChange->Focus();
      }
   }
   else if (e->KeyChar == 27) //Escape
   {
    txtBxValueChange->Text = CFormatConverterWrapper::DoubleToString(selectedElemTable->getElemStatus(selectedElem)->getVariabelValue());
    //Fokus weiter setzen
    txtBxMinValue->Focus();
   }       
}
//------------------------------------------------------------
System::Void CCyclicTlgForm::txtBxMinValue_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
{
  if (e->KeyChar == 13) //Enter
   {
     try
      {
        if (selectedElemTable && selectedElem)
        {
          //Zeitangabe in Double konventieren
          selectedElemTable->getElemStatus(selectedElem)->setMinValue(CFormatConverterWrapper::StringToDouble(txtBxMinValue->Text));
          //neue Wert Text zuweisen
          txtBxMinValue->Text = CFormatConverterWrapper::DoubleToString(selectedElemTable->getElemStatus(selectedElem)->getMinValue());
          //Fokus weiter setzen
          txtBxMaxValue->Focus();
        }
      }
      catch (CExpWrapper^ e)
      {
				CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,e->getMessage(),
																															__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        System::Windows::Forms::MessageBox::Show(nullptr,e->getMessage(),
                                          "",
                                          MessageBoxButtons::OK,
                                          MessageBoxIcon::Warning);
        //Fokus zurueck setzen
        txtBxMinValue->Focus();
      }
   }
   else if (e->KeyChar == 27) //escape
   {
      txtBxMinValue->Text = CFormatConverterWrapper::DoubleToString(selectedElemTable->getElemStatus(selectedElem)->getMinValue());
      //Fokus weiter setzen
      txtBxMaxValue->Focus();
   }                    
}
//------------------------------------------------------------
System::Void CCyclicTlgForm::txtBxMinValue_Leave(System::Object^  sender, System::EventArgs^  e) 
{
  try
  {
    if (selectedElemTable && selectedElem)
    {
      //Zeitangabe in Double konventieren
      selectedElemTable->getElemStatus(selectedElem)->setMinValue(CFormatConverterWrapper::StringToDouble(txtBxMinValue->Text));
      //neue Wert Text zuweisen
      txtBxMinValue->Text = CFormatConverterWrapper::DoubleToString(selectedElemTable->getElemStatus(selectedElem)->getMinValue());
    }
  }
    catch (CExpWrapper^ e)
    {
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,e->getMessage(),
																														__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
			System::Windows::Forms::MessageBox::Show(nullptr,e->getMessage(),
                                        "",
                                        MessageBoxButtons::OK,
                                        MessageBoxIcon::Warning);
      //Fokus zurueck setzen
      txtBxMinValue->Focus();
  }        
}
//------------------------------------------------------------
System::Void CCyclicTlgForm::txtBxMaxValue_Leave(System::Object^  sender, System::EventArgs^  e) 
{
  try
  {
    if (selectedElemTable && selectedElem)
    {
      //Zeitangabe in Double konventieren
      selectedElemTable->getElemStatus(selectedElem)->setMaxValue(CFormatConverterWrapper::StringToDouble(txtBxMaxValue->Text));
      //neue Wert Text zuweisen
      txtBxMaxValue->Text = CFormatConverterWrapper::DoubleToString(selectedElemTable->getElemStatus(selectedElem)->getMaxValue());
    }
  }
  catch (CExpWrapper^ e)
  {
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,e->getMessage(),
																													__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
		System::Windows::Forms::MessageBox::Show(nullptr,e->getMessage(),
                                      "",
                                      MessageBoxButtons::OK,
                                      MessageBoxIcon::Warning);
    //Fokus zurueck setzen
    txtBxMaxValue->Focus();
	}   
         
}
//------------------------------------------------------------
System::Void CCyclicTlgForm::txtBxMaxValue_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) 
{
   if (e->KeyChar == 13)//Enter
   {
     try
      {
        if (selectedElemTable && selectedElem)
        {
          //Zeitangabe in Double konventieren
          selectedElemTable->getElemStatus(selectedElem)->setMaxValue(CFormatConverterWrapper::StringToDouble(txtBxMaxValue->Text));
          //neue Wert Text zuweisen
          txtBxMaxValue->Text = CFormatConverterWrapper::DoubleToString(selectedElemTable->getElemStatus(selectedElem)->getMaxValue());
          //Fokus weiter setzen
        }
      }
      catch (CExpWrapper^ e)
      {
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,e->getMessage(),
																														__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
				System::Windows::Forms::MessageBox::Show(nullptr,e->getMessage(),
                                          "",
                                          MessageBoxButtons::OK,
                                          MessageBoxIcon::Warning);
        //Fokus zurueck setzen
        txtBxMaxValue->Focus();
      }
   }
   else if (e->KeyChar == 27)//escape
   {
      txtBxMaxValue->Text = CFormatConverterWrapper::DoubleToString(selectedElemTable->getElemStatus(selectedElem)->getMinValue());
      //Fokus weiter setzen
   }               
}
//------------------------------------------------------------
System::Void CCyclicTlgForm::txtBxStartValue_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) 
{
  String^ value = nullptr;
  if (e->KeyChar == 13)//enter
  {
    if (selectedElem && selectedItem)
    {
      value = txtBxStartValue->Text;
      String^ ret = nullptr;
      ret = selectedElem->setValue(value,selectedItem->getInterfece());
      //Keine Errors
      if (!ret)
      {
        selectedElem->getElemValue(value);
        txtBxStartValue->Text = value;
        labElemValue->Text = value;
        SetMinOrMaxValue(CFormatConverterWrapper::StringToDouble(value));
        txtBxValueChange->Focus();
      }//Errors
      else
      {
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,ret,
																														__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
				System::Windows::Forms::MessageBox::Show(nullptr,ret,
                                          "",
                                          MessageBoxButtons::OK,
                                          MessageBoxIcon::Warning);
        txtBxStartValue->Focus();
      }
    }
  } 
  else if (e->KeyChar == 27)//escape
  {
    selectedElem->getElemValue(value);
    txtBxStartValue->Text = value;
    txtBxValueChange->Focus();
  }
}
//------------------------------------------------------------
System::Void CCyclicTlgForm::txtBxStartValue_Leave(System::Object^  sender, System::EventArgs^  e) 
{
  if (selectedElem && selectedItem)
  {
    String^ value = txtBxStartValue->Text;
    String^ ret = nullptr;
    ret = selectedElem->setValue(value,selectedItem->getInterfece());
    //Keine Errors
    if (!ret)
    {
      selectedElem->getElemValue(value);
      txtBxStartValue->Text = value;
      labElemValue->Text = value;
      SetMinOrMaxValue(CFormatConverterWrapper::StringToDouble(value));
    }//Errors
    else
    {
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,ret,
																														__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
			System::Windows::Forms::MessageBox::Show(nullptr,ret,
                                        "",
                                        MessageBoxButtons::OK,
                                        MessageBoxIcon::Warning);
      txtBxStartValue->Focus();
    }
  }     
}
//------------------------------------------------------------
System::Void CCyclicTlgForm::textBxTimeInterval_Leave(System::Object^  sender, System::EventArgs^  e) 
{ 
  try
  {
    if (selectedElemTable)
    {
      int time = -1;
      //Zeitangabe in Int konventieren
      time = CFormatConverterWrapper::StringToInt(textBxTimeInterval->Text);
      if (time > 0)
      {
        selectedElemTable->setTimeInterval(time);
        //neue Wert Text zuweisen
        textBxTimeInterval->Text = CFormatConverterWrapper::IntToString(selectedElemTable->getTimeInterval());
        //Fokus weiter setzen
        comBxChange->Focus();
      }      
      else
      {
        System::Windows::Forms::MessageBox::Show(nullptr,"Time interval should be positive!",
                                      "",
                                      MessageBoxButtons::OK,
                                      MessageBoxIcon::Warning);
        textBxTimeInterval->Focus();
      }
    }
  }
    catch (CExpWrapper^ e)
    {
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,e->getMessage(),
																														__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
			System::Windows::Forms::MessageBox::Show(nullptr,e->getMessage(),
                                        "",
                                        MessageBoxButtons::OK,
                                        MessageBoxIcon::Warning);
      //Fokus zurueck setzen
      textBxTimeInterval->Focus();
  }
}
//------------------------------------------------------------
System::Void CCyclicTlgForm::textBxTimeInterval_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) 
{
   if (e->KeyChar == 13)//Enter
   {
     try
      {
        if (selectedElemTable)
        {
          int time = -1;
          //Zeitangabe in Int konventieren
          time = CFormatConverterWrapper::StringToInt(textBxTimeInterval->Text);
          if (time > 0)
          {
            selectedElemTable->setTimeInterval(time);
            //neue Wert Text zuweisen
            textBxTimeInterval->Text = CFormatConverterWrapper::IntToString(selectedElemTable->getTimeInterval());
            //Fokus weiter setzen
            comBxChange->Focus();
          }
          else
          {
            System::Windows::Forms::MessageBox::Show(nullptr,"Time interval should be positive!",
                                          "",
                                          MessageBoxButtons::OK,
                                          MessageBoxIcon::Warning);
            textBxTimeInterval->Focus();
          }
        }
      }
      catch (CExpWrapper^ e)
      {
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,e->getMessage(),
																														__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
				System::Windows::Forms::MessageBox::Show(nullptr,e->getMessage(),
                                          "",
                                          MessageBoxButtons::OK,
                                          MessageBoxIcon::Warning);
        //Fokus zurueck setzen
        textBxTimeInterval->Focus();
      }
   }
   else if (e->KeyChar == 27)//escape
   {
    textBxTimeInterval->Text = CFormatConverterWrapper::IntToString(selectedElemTable->getTimeInterval());
    //Fokus weiter setzen
    comBxChange->Focus();
   }
}
//------------------------------------------------------------
System::Void CCyclicTlgForm::checkBxDefaultValues_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
  //txtBxMaxValue->Clear();
  //txtBxMinValue->Clear();

  //CTlgElemWrapper^ elem = safe_cast <CTlgElemWrapper^>(trItemView->SelectedNode->Tag);
  //if (elem)
  //{
  //  //Element Status
  //  CCyclicElemStatus^ elemStatus = selectedElemTable->getElemStatus(elem);
  //  if (checkBxDefaultValues->Checked)
  //    elemStatus->setDafaultDataTypeValuesForMinAndMax(elem);
  //  //Max
  //  txtBxMaxValue->Enabled = true;
  //  txtBxMaxValue->Text = CFormatConverterWrapper::DoubleToString(elemStatus->getMaxValue());
  //  //Min
  //  txtBxMinValue->Enabled = true;
  //  txtBxMinValue->Text = CFormatConverterWrapper::DoubleToString(elemStatus->getMinValue());
  //}
}
//------------------------------------------------------------
System::Void CCyclicTlgForm::butLoad_Click(System::Object^  sender, System::EventArgs^  e) 
{
  CAppSetting^ Sett = CAppSetting::getApp();
  String^ directory = nullptr;
  OpenFileDialog^ OpenFile = gcnew OpenFileDialog();
  OpenFile->Title = "Open cyclic telegrams to file";
  OpenFile->Filter = "Cyclic-file (*.xml)|*.xml|All files(*.*)|*.*";

  //Letze Pfad zum Verzeichnis auslesen
  directory = Sett->getCyclicDirectory();
  if(directory)
  {
    OpenFile->InitialDirectory = (directory);
  }

  if(OpenFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
  {
		::Cursor::Current = ::Cursors::WaitCursor;
    CXmlCyclicTlgReader^ writer = gcnew CXmlCyclicTlgReader();
    writer->setMessageXmlCyclicReaderDelTyp(gcnew CXmlCyclicTlgReader::MessageXmlCyclicReaderDelTyp(this,&CCyclicTlgForm::WriteMessage));
    writer->readCyclicItems(OpenFile->FileName,InterfaceProtoArray);
    showAll();

    //Letze Pfad zum Verzeichnis merken
    int pos = OpenFile->FileName->LastIndexOf("\\");
    if(pos != -1)
    {
      directory = OpenFile->FileName->Substring(0,pos);
      Sett->setCyclicDirectory(directory);
    }
		::Cursor::Current = ::Cursors::Default;
  }         
}
//------------------------------------------------------------
System::Void CCyclicTlgForm::butSave_Click(System::Object^  sender, System::EventArgs^  e) 
{
  CAppSetting^ Sett = CAppSetting::getApp();
  String^ directory = nullptr;
  SaveFileDialog^ SaveFile = gcnew SaveFileDialog();
  SaveFile->Title = "Safe cyclic telegrams to file";
  SaveFile->Filter = "Cyclic-file (*.xml)|*.xml|All files(*.*)|*.*";

  //Letze Pfad zum Verzeichnis auslesen
  directory = Sett->getConnDirectory();
  if(directory)
  {
    SaveFile->InitialDirectory = (directory);
  }
  
  if(SaveFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
  {
		::Cursor::Current = ::Cursors::WaitCursor;
    CXmlCyclicTlgWriter^ writer = gcnew CXmlCyclicTlgWriter();
    writer->writeCyclicItems(SaveFile->FileName);
		::Cursor::Current = ::Cursors::Default;

    //Letze Pfad zum Verzeichnis merken
    int pos = SaveFile->FileName->LastIndexOf("\\");
    if(pos != -1)
    {
      directory = SaveFile->FileName->Substring(0,pos);
      Sett->setCyclicDirectory(directory);
    }
  }  
}
//------------------------------------------------------------
System::Void CCyclicTlgForm::butRemove_Click(System::Object^  sender, System::EventArgs^  e) 
{
	::Cursor::Current = ::Cursors::WaitCursor;
  Windows::Forms::TreeNode^ node = nullptr;
  node = trViewCyclicTlgInSzenario->SelectedNode;
  if (node)
  {
    CItemWrapper^ item = nullptr;
    item = safe_cast <CItemWrapper^> (node->Tag);
    if (item)
    {
      textBxTimeInterval->Text="";
      textBxTimeInterval->Enabled=false;
      //Item aus dem CyclicContainer entfernen
      CCyclicItemContainer::getCyclicItemContainer()->removeItem(item);
      //Item aus dem TreeView entfernen
      trItemView->Nodes->Clear();
      trViewCyclicTlgInSzenario->Nodes->Remove(node);
      ClearView();
 
      if (trViewCyclicTlgInSzenario->Nodes->Count==0)
      {
        trViewCyclicTlgInSzenario->Nodes->Clear();
        comBoxInterfaces->Items->RemoveAt(comBoxInterfaces->SelectedIndex); 
      }

      //Buttons Save und Remove (de)aktivieren
      //Naechste Interface selektieren
      if (CCyclicItemContainer::getCyclicItemContainer()->getCountOfInterface()>0)
      {
        butSave->Enabled=true;
        butRemove->Enabled=true;
        
        if (trViewCyclicTlgInSzenario->Nodes->Count==0)
        {
          selectedInterfaceName=CCyclicItemContainer::getCyclicItemContainer()->getNextInterface();
          comBoxInterfaces->Text = selectedInterfaceName;
          ClearView();
          showAllItems();
        }
      }
      else
      {
        butSave->Enabled=false;
        butRemove->Enabled=false;
        comBoxInterfaces->Items->Clear();
        comBoxInterfaces->Text = "";
      }
    }
  }
	::Cursor::Current = ::Cursors::Default;
}
//------------------------------------------------------------
System::Void CCyclicTlgForm::comBoxInterfaces_TextChanged(System::Object^  sender, System::EventArgs^  e) 
{
  if (comBoxInterfaces->Items->Count > 0 && !comBoxInterfaces->Text->Equals(""))
  {
    selectedInterfaceName = comBoxInterfaces->Text;
    ClearView();
    showAllItems();
  }
}
//------------------------------------------------------------
System::Void CCyclicTlgForm::butClose_Click(System::Object^  sender, System::EventArgs^  e) 
{
  Close();
}
//------------------------------------------------------------
System::Void CCyclicTlgForm::trViewCyclicTlgInSzenario_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) 
{
  if (trViewCyclicTlgInSzenario->SelectedNode)
  {
    CItemWrapper^ tlg = safe_cast <CItemWrapper^>(trViewCyclicTlgInSzenario->SelectedNode->Tag);
    if (tlg)
    {
      selectedElemTable=nullptr;
      selectedItem=tlg;
      selectedElemTable = safe_cast <CCyclicElemTable^> (cyclicItemContainer->getElemTable(selectedItem->getInterfece(),selectedItem));      
      showItem();
      gpBoxElements->Text = String::Concat("Elements of ",tlg->getName());
    }
  }
}
//------------------------------------------------------------
System::Void CCyclicTlgForm::trViewCyclicTlgInSzenario_BeforeSelect(System::Object^  sender, System::Windows::Forms::TreeViewCancelEventArgs^  e) 
{
  if (trViewCyclicTlgInSzenario->SelectedNode)
  {
    CItemWrapper^ tlg = safe_cast <CItemWrapper^>(trViewCyclicTlgInSzenario->SelectedNode->Tag);
    if (tlg)
      ClearView();
  }      
}
//------------------------------------------------------------
void CCyclicTlgForm::ClearView()
{
  selectedItem = nullptr;
  selectedElem = nullptr;
  labElemName->Text = "";;
  labElemTyp->Text = "";
  labElemValue->Text = "";
	txtBxValueChange->Enabled = false;
	txtBxMinValue->Enabled = false;
  txtBxMaxValue->Enabled = false;
	radBtVariabel->Enabled = false;
	comBxChange->Enabled = false;
  //checkBxDefaultValues->Enabled = false;
  txtBxStartValue->Text="";
  txtBxStartValue->Enabled=false;
  //butMaxMinValues->Enabled=false;
  butMaxValue->Enabled=false;
  butMinValue->Enabled=false;
  butDefaultsValues->Enabled=false;
}
//------------------------------------------------------------
System::Void CCyclicTlgForm::comBxChange_TextChanged(System::Object^  sender, System::EventArgs^  e) 
{
  //if (comBxChange->Text->Equals("none"))
  //{
  //  //txtBxValueChange->Text="";
  //  //txtBxMaxValue->Text ="";
  //  //txtBxMinValue->Text ="";
  //  txtBxValueChange->Enabled=false;
  //  txtBxMaxValue->Enabled=false;
  //  txtBxMinValue->Enabled=false;
  //  checkBxDefaultValues->Enabled=false;
  //  txtBxStartValue->Enabled=false;
  //}
  //else
  //{
  //  txtBxValueChange->Enabled=true;
  //  txtBxMaxValue->Enabled=true;
  //  txtBxMinValue->Enabled=true;
  //  checkBxDefaultValues->Enabled=true;
  //  checkBxDefaultValues->Checked=false;
  //  txtBxStartValue->Enabled=true;
  //  String^ value;
		//selectedElem->getElemValue(value);
		//txtBxStartValue->Text = value;
  //}

  txtBxStartValue->Text="";
  txtBxValueChange->Text="";
  txtBxMaxValue->Text ="";
  txtBxMinValue->Text ="";

  CCyclicElemStatus::changeTyp typ;

  if (comBxChange->Text->Equals("+"))
    typ = CCyclicElemStatus::changeTyp::plus;
  else if (comBxChange->Text->Equals("-"))
    typ = CCyclicElemStatus::changeTyp::minus;
  else if (comBxChange->Text->Equals("*"))
    typ = CCyclicElemStatus::changeTyp::multiple;
  else if (comBxChange->Text->Equals("/"))
    typ = CCyclicElemStatus::changeTyp::divide;
  else
    typ = CCyclicElemStatus::changeTyp::none;

  if (selectedElemTable && selectedElem)
  {
    selectedElemTable->getElemStatus(selectedElem)->setVariabelTyp(typ);
  }

  //Konfigurierte Element kennzeichnen
  if (selectedElemTable->getElemStatus(selectedElem)->getVariabelTyp() != CCyclicElemStatus::changeTyp::none)
    trItemView->SelectedNode->BackColor = Drawing::Color::LightGray;
  else
    trItemView->SelectedNode->BackColor = Drawing::Color::White;

  trItemView_AfterSelect(nullptr,nullptr);
}
//------------------------------------------------------------
System::Void CCyclicTlgForm::trItemView_BeforeSelect(System::Object^  sender, System::Windows::Forms::TreeViewCancelEventArgs^  e) 
{
  //if (trItemView->get_SelectedNode())
  //{
  //  if (trItemView->get_SelectedNode()->get_Tag())
  //  {
  //    CTlgElemWrapper* elem = safe_cast <CTlgElemWrapper*>(trItemView->get_SelectedNode()->get_Tag());
  //    try
  //    {
  //      if (elem)
  //      {
  //        //Werte von GUI lesen
  //        double max;
  //        double min;
  //        double variabelValue;
  //        CCyclicElemStatus::changeTyp typ;

  //        if (comBxChange->Text->Equals("+"))
  //          typ = CCyclicElemStatus::changeTyp::plus;
  //        else if (comBxChange->Text->Equals("-"))
  //          typ = CCyclicElemStatus::changeTyp::minus;
  //        else if (comBxChange->Text->Equals("*"))
  //          typ = CCyclicElemStatus::changeTyp::multiple;
  //        else if (comBxChange->Text->Equals("/"))
  //          typ = CCyclicElemStatus::changeTyp::divide;
  //        else
  //          typ = CCyclicElemStatus::changeTyp::none;

  //        if (typ == CCyclicElemStatus::changeTyp::none)
  //        {
  //          variabelValue = 0.0;
  //          max = 0.0;
  //          min = 0.0;
  //        }
  //        else
  //        {
  //          variabelValue = CFormatConverterWrapper::StringToDouble(txtBxValueChange->Text);
  //          max = CFormatConverterWrapper::StringToDouble(txtBxMaxValue->Text);
  //          min = CFormatConverterWrapper::StringToDouble(txtBxMinValue->Text);
  //        }
  //        //Elem Status update elem,typ,limit,variabelValue);
  //        selectedElemTable->updateElemStatus(elem,typ,max,min,variabelValue); 
  //      }
  //    }
  //    catch (CExpWrapper* e)
  //    {
  //      System::Windows::Forms::MessageBox::Show(0,e->getMessage(),
  //                                        "",
  //                                        MessageBoxButtons::OK,
  //                                        MessageBoxIcon::Warning);
  //    }
  //  }
  //}
}
//------------------------------------------------------------
Void CCyclicTlgForm:: trItemView_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e)
{
	if (trItemView->SelectedNode->Tag)
	{
		CTlgElemWrapper^ elem = safe_cast <CTlgElemWrapper^>(trItemView->SelectedNode->Tag);
		if (elem)
		{
      selectedElem=elem;
      this->labElemName->Text = elem->getElemName();
			//Element Status
      CCyclicElemStatus^ elemStatus = selectedElemTable->getElemStatus(elem);
			//ChangeComboBox
      if (elemStatus)
      {
        //Label Value Type
			  String^ value;
			  elem->getElemValue(value);
			  labElemValue->Text = value;
			  labElemTyp->Text=elem->getElemType();
        //
        /*checkBxDefaultValues->Text = String::Concat("Max. and min. possible value of <",elem->getElemType(),"> data type");*/
        
        comBxChange->Enabled = true;
        
        if (elemStatus->getVariabelTyp() == CCyclicElemStatus::changeTyp::plus)
          comBxChange->SelectedItem = ("+");
        else  if (elemStatus->getVariabelTyp() == CCyclicElemStatus::changeTyp::multiple)
          comBxChange->SelectedItem = ("*");
        else  if (elemStatus->getVariabelTyp() == CCyclicElemStatus::changeTyp::minus)
          comBxChange->SelectedItem = ("-");
        else  if (elemStatus->getVariabelTyp() == CCyclicElemStatus::changeTyp::divide)
          comBxChange->SelectedItem = ("/");
        
        if (elemStatus->getVariabelTyp() != CCyclicElemStatus::changeTyp::none)
        {
          //TextBox Start Value
          txtBxStartValue->Enabled = true;
          txtBxStartValue->Text = value;
          //TextBox Change Value
          txtBxValueChange->Enabled = true;
          txtBxValueChange->Text = CFormatConverterWrapper::DoubleToString(elemStatus->getVariabelValue());
          //Max
			    txtBxMaxValue->Enabled = true;
          txtBxMaxValue->Text = CFormatConverterWrapper::DoubleToString(elemStatus->getMaxValue());
          //Min
			    txtBxMinValue->Enabled = true;
          txtBxMinValue->Text = CFormatConverterWrapper::DoubleToString(elemStatus->getMinValue());
          //checkBxDefaultValues->Enabled=true;
          //butMaxMinValues->Enabled=true;
          butMinValue->Enabled=true;
          butMaxValue->Enabled=true;
          butDefaultsValues->Enabled=true;
        }
        else
        {
          comBxChange->SelectedItem = ("none");
          txtBxStartValue->Enabled = false;
          txtBxValueChange->Enabled = false;
          //Max
			    txtBxMaxValue->Enabled = false;
          //Min
			    txtBxMinValue->Enabled = false;
          //checkBxDefaultValues->Enabled=false;
          //butMaxMinValues->Enabled=false;
          butMinValue->Enabled=false;
          butMaxValue->Enabled=false;
          butDefaultsValues->Enabled=false;
        }       
      }
		}
	}
	else
	{
		ClearView();
	}
}
//------------------------------------------------------------
void CCyclicTlgForm::showAll() 
{
  comBoxInterfaces->Items->Clear();
  comBoxInterfaces->BeginUpdate();
  trViewCyclicTlgInSzenario->BeginUpdate();
  trItemView->BeginUpdate();
  String^ interName = nullptr;
  if (cyclicItemContainer->getCountOfInterface()>0)
  {
    //Interface Namen 
    cyclicItemContainer->iterReset();
    bool ok = true;
    while (ok)
    {
      interName = cyclicItemContainer->getNextInterface();
      if (interName)
      {
        comBoxInterfaces->Items->Add(interName);
      }
      else
      {
        ok = false;
      }
    }
    trViewCyclicTlgInSzenario->EndUpdate();
    comBoxInterfaces->EndUpdate();
    trItemView->EndUpdate();
    //Letze Interface selektieren
    if (cyclicItemContainer->getLastAddedItem())
      comBoxInterfaces->SelectedItem=cyclicItemContainer->getLastAddedItem()->getInterfece();
    butSave->Enabled=true;
    butRemove->Enabled=true;
  }
  else
  {
    butSave->Enabled=false;
    butRemove->Enabled=false;
  }
}
//------------------------------------------------------------
void CCyclicTlgForm::showAllItems()
{
  CCyclicElemTable^ elemTable;
  System::Windows::Forms::TreeNode^ node = nullptr;
  trViewCyclicTlgInSzenario->Nodes->Clear();
  
  //Items Namen 
  bool ok = true;
  trViewCyclicTlgInSzenario->BeginUpdate();
  while (ok)
  {
    elemTable = cyclicItemContainer->getNextItem(selectedInterfaceName);
    if (elemTable)
    {
      node = gcnew System::Windows::Forms::TreeNode(elemTable->getItemName());
      //this->selectedElemTable=elemTable;
      node->Tag = (elemTable->getItem());
      trViewCyclicTlgInSzenario->Nodes->Add(node);
    }
    else
    {
      ok = false;
    }
  }
  trViewCyclicTlgInSzenario->EndUpdate();
  trViewCyclicTlgInSzenario->SelectedNode=trViewCyclicTlgInSzenario->Nodes[0];
}
//------------------------------------------------------------
void CCyclicTlgForm::showItem()
{
  int count = selectedItem->getTlgElemCount();
  int itemCount = 0;
  System::Windows::Forms::TreeNode^ node = nullptr;
  
  if (selectedElemTable)
  {
    textBxTimeInterval->Enabled = true;
    textBxTimeInterval->Text = CFormatConverterWrapper::IntToString(selectedElemTable->getTimeInterval());
    if (selectedItem)
    {

      trItemView->BeginUpdate();
      trItemView->Nodes->Clear();
      //Elemente 
      for (int j=1;j<=count;j++)
      {
        
        CTlgElemWrapper^ elem = gcnew CTlgElemWrapper();
        elem->setTlgElem(selectedItem->getElem(j)); 
        
        if (elem->getSubElemCount() > 0)
        {
	        trItemView->Nodes->Add(buildElemNodes (elem));
        }
        else
        {
	        node = gcnew System::Windows::Forms::TreeNode(); 
	        setNodeColorText(elem,node);
	        trItemView->Nodes->Add(node);
        }
      }
      trItemView->EndUpdate();
    }
  }
}
//------------------------------------------------------------
System::Windows::Forms::TreeNode^ CCyclicTlgForm::buildElemNodes (CTlgElemWrapper^ elem)
{
  System::Windows::Forms::TreeNode^ subElemNodeRet = gcnew System::Windows::Forms::TreeNode ();
  int elemCount = elem->getSubElemCount(); 
	setNodeColorText(elem,subElemNodeRet);

  if (elemCount>0)
  {
    for (int j=1;j<=elemCount;j++)
    {
      CTlgElemWrapper^ elemSub = gcnew CTlgElemWrapper();
      elemSub->setTlgElem(elem->getSubElem(j));
      //Rekursive Aufruf
      subElemNodeRet->Nodes->Add(buildElemNodes(elemSub));
    }
  }

 return subElemNodeRet; 
}
//------------------------------------------------------------
void CCyclicTlgForm::setNodeColorText(CTlgElemWrapper^ elem,System::Windows::Forms::TreeNode^ subElemNodeRet )
{
	if (elem->getElemType()->Equals("Double") || elem->getElemType()->Equals("Float")
			|| elem->getElemType()->Equals("Integer") || elem->getElemType()->Equals("ShortInteger"))
	{
    subElemNodeRet->ForeColor = (System::Drawing::Color::Black);
		subElemNodeRet->Tag = (elem);
    //Konfigurierte Element kennzeichnen
    if (selectedElemTable->getElemStatus(elem)->getVariabelTyp() != CCyclicElemStatus::changeTyp::none)
      subElemNodeRet->BackColor = Drawing::Color::LightGray;
    else
      subElemNodeRet->BackColor = Drawing::Color::White;
  }
	else
	{
		subElemNodeRet->ForeColor=(System::Drawing::Color::Red);
		subElemNodeRet->Tag = nullptr;
	}
	subElemNodeRet->Text = (elem->getElemName());
}
//----------------------------------------------------
void CCyclicTlgForm::SetMinOrMaxValue(double value)
{
  if (selectedElemTable && selectedElem)
  {
    CCyclicElemStatus::changeTyp typ = selectedElemTable->getElemStatus(selectedElem)->getVariabelTyp();
    if (typ == CCyclicElemStatus::changeTyp::minus || typ == CCyclicElemStatus::changeTyp::divide)
    {
      if (txtBxMaxValue->Text->Equals("") || txtBxMaxValue->Text->Equals("-1"))
      {
        txtBxMaxValue->Text = txtBxStartValue->Text;
        selectedElemTable->getElemStatus(selectedElem)->setMaxValue(value);
      }
    }
    else if (typ == CCyclicElemStatus::changeTyp::plus || typ == CCyclicElemStatus::changeTyp::multiple)
    {
      if (txtBxMinValue->Text->Equals("") || txtBxMaxValue->Text->Equals("-1"))
      {
        txtBxMinValue->Text = txtBxStartValue->Text;
        selectedElemTable->getElemStatus(selectedElem)->setMinValue(value);
      }
    }
  }
}
//--------------------------------------------------------
void CCyclicTlgForm::WriteMessage(String^ mes,int typ)
{
  CMessageForm::MessTyp messType;
  if(typ == 0)
    messType=CMessageForm::MessTyp::Info;
  if(typ == 1)
    messType=CMessageForm::MessTyp::Warning;
  if(typ == 2)
    messType=CMessageForm::MessTyp::Error;
  
  MessageForm->writeLine(mes,messType);
}
//---------------------------------------------------------
System::Void CCyclicTlgForm::butDefaultsValues_Click(System::Object^  sender, System::EventArgs^  e) 
{
  txtBxMaxValue->Clear();
  txtBxMinValue->Clear();

  CTlgElemWrapper^ elem = safe_cast <CTlgElemWrapper^>(trItemView->SelectedNode->Tag);
  if (elem)
  {
    //Element Status
    CCyclicElemStatus^ elemStatus = selectedElemTable->getElemStatus(elem);
    //elemStatus->setDafaultDataTypeValuesForMinAndMax(elem);
    elemStatus->setMinValue(0.0);
    elemStatus->setMaxValue(10000.0);
    //Max
    txtBxMaxValue->Enabled = true;
    txtBxMaxValue->Text = CFormatConverterWrapper::DoubleToString(elemStatus->getMaxValue());
    //Min
    txtBxMinValue->Enabled = true;
    txtBxMinValue->Text = CFormatConverterWrapper::DoubleToString(elemStatus->getMinValue());
  }
}
//---------------------------------------------------------
System::Void CCyclicTlgForm::butMaxMinValues_Click(System::Object^  sender, System::EventArgs^  e) 
{
  txtBxMaxValue->Clear();
  txtBxMinValue->Clear();

  CTlgElemWrapper^ elem = safe_cast <CTlgElemWrapper^>(trItemView->SelectedNode->Tag);
  if (elem)
  {
    //Element Status
    CCyclicElemStatus^ elemStatus = selectedElemTable->getElemStatus(elem);
    elemStatus->setMinimalAndMaximalValuesForMinAndMax(elem);
    //Max
    txtBxMaxValue->Enabled = true;
    txtBxMaxValue->Text = CFormatConverterWrapper::DoubleToString(elemStatus->getMaxValue());
    //Min
    txtBxMinValue->Enabled = true;
    txtBxMinValue->Text = CFormatConverterWrapper::DoubleToString(elemStatus->getMinValue());
  }       
}
//--------------------------------------------------------
System::Void CCyclicTlgForm::butMaxValue_Click(System::Object^  sender, System::EventArgs^  e) 
{
  txtBxMaxValue->Clear();

  CTlgElemWrapper^ elem = safe_cast <CTlgElemWrapper^>(trItemView->SelectedNode->Tag);
  if (elem)
  {
    //Element Status
    CCyclicElemStatus^ elemStatus = selectedElemTable->getElemStatus(elem);
    elemStatus->setMaximumValueForMax(elem);
    //Max
    txtBxMaxValue->Enabled = true;
    txtBxMaxValue->Text = CFormatConverterWrapper::DoubleToString(elemStatus->getMaxValue());
  }      
}
//--------------------------------------------------------
System::Void CCyclicTlgForm::butMinValue_Click(System::Object^  sender, System::EventArgs^  e) 
{
  txtBxMinValue->Clear();

  CTlgElemWrapper^ elem = safe_cast <CTlgElemWrapper^>(trItemView->SelectedNode->Tag);
  if (elem)
  {
    //Element Status
    CCyclicElemStatus^ elemStatus = selectedElemTable->getElemStatus(elem);
    elemStatus->setMinimumValueForMin(elem);
    //Min
    txtBxMinValue->Enabled = true;
    txtBxMinValue->Text = CFormatConverterWrapper::DoubleToString(elemStatus->getMinValue());
  }      
}