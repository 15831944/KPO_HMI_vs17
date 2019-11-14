#include "StdAfx.h"
#include "CAnalyzeLogFileForm.h"
#include "CMessageWriter.h"
#include "CProgressBarStatusWriter.h"
#include "CTlgWrapper.h"
#include "CProgressBarViewForm.h"
#include "CFormatConverterWrapper.h"
#include "CLogWriterWrapper.h"
#include "CDataGridContainerForm.h"

bool AbortLogFileReaderThreadInAnalyzer = false;

using namespace simulator;
//----------------------------------------------------------------
System::Void CAnalyzeLogFileForm::OnMenuItemCursorToolClick(System::Object^  sender, System::EventArgs^  e) 
{
    TlgForm->setCursor(!menuItemCursorTool->Checked);
    SubElemForm->setCursorTool(!menuItemCursorTool->Checked);
    menuItemCursorTool->Checked = (!menuItemCursorTool->Checked);
}
//----------------------------------------------------------------
System::Void CAnalyzeLogFileForm::CAnalyzeLogFileForm_Closing(System::Object ^  sender, System::ComponentModel::CancelEventArgs ^  e)
{
  tabDiagramControl->SelectedIndex = (2);
  //Threads beenden
  if (timerThread)
    timerThread->Abort();
  if (LogFileReadThread)
    LogFileReadThread->Abort();
  //Forms schliessen
  if (barView)
    barView->Close();
  if (TlgForm)
    TlgForm->Close();
  if (SubElemForm)
    SubElemForm->Close();
  if (MessageForm)
    MessageForm->Close();
  if (TlgConFromLogFile)
    TlgConFromLogFile->clearContainer();
}
//----------------------------------------------------------------
System::Void CAnalyzeLogFileForm::butAddToTable_Click(System::Object^  sender, System::EventArgs^  e) 
{
  TlgDataTableCon->Show();
  TlgDataTableCon->addItem(nullptr);
}
//----------------------------------------------------------------
System::Void CAnalyzeLogFileForm::menuItemContents_Click(System::Object^  sender, System::EventArgs^  e)
{
  Help::ShowHelp(this,"Simulator.chm",HelpNavigator::TableOfContents,nullptr);
}
//----------------------------------------------------------------
System::Void CAnalyzeLogFileForm::menuItemIndex_Click(System::Object^  sender, System::EventArgs^  e) 
{
  Help::ShowHelp(this,"Simulator.chm",HelpNavigator::Index,nullptr); 
}
//----------------------------------------------------------------
System::Void CAnalyzeLogFileForm::OnSplitter3Click(System::Object^  sender, System::EventArgs^  e) 
{
  if (this->panViewMessageBox->Visible)
  {
    this->panViewMessageBox->Hide();
  }
  else
  {
    this->panViewMessageBox->Show();
  }
}
//----------------------------------------------------------------
System::Void CAnalyzeLogFileForm::OnSplitter1Click(System::Object^  sender, System::EventArgs^  e) 
{
  if (this->panViewLeft->Visible)
  {
    this->panViewLeft->Hide();
  }
  else
  {
    this->panViewLeft->Show();
  }
}
//----------------------------------------------------------------
System::Void CAnalyzeLogFileForm::OnRemoveAllClick(System::Object ^  sender, System::EventArgs ^  e)
{
	if (!this->isTimerActive)
	{
		int index = tabDiagramControl->SelectedIndex;
		if (index==0)
			TlgForm->removeAll();
		else 
			SubElemForm->removeAll();
	}
}
//----------------------------------------------------------------
System::Void CAnalyzeLogFileForm::OnMenuItemFillClick(System::Object^  sender, System::EventArgs^  e) 
{
  if (menuItemFill->Checked)
  {
    menuItemFill->Checked = (false);
    this->panViewLeft->Show();
    this->panViewMessageBox->Show();
  }
  else
  {
    menuItemFill->Checked = (true);
    this->panViewLeft->Hide();
    this->panViewMessageBox->Hide();
  }        
}
//----------------------------------------------------------------
System::Void CAnalyzeLogFileForm::OnMenuItem3DClick(System::Object ^  sender, System::EventArgs ^  e)
{
  int index = tabDiagramControl->SelectedIndex;
 
  if (menuItem3D->Checked)
  {
    menuItem3D->Checked = (false);
    if (index==0)
      TlgForm->set3DMode(false);
    else
      SubElemForm->set3DMode(false);
  }
  else
  {
    menuItem3D->Checked = (true);
    if (index==0)
      TlgForm->set3DMode(true);
    else
      SubElemForm->set3DMode(true);
  }
}
//----------------------------------------------------------------
System::Void CAnalyzeLogFileForm::tabDiagramControl_SelectedIndexChanged(System::Object ^  sender, System::EventArgs ^  e)
{
  int index = tabDiagramControl->SelectedIndex;
  if (index==0)
  {
    menuItem3D->Checked = (TlgForm->get3DMode());
    menuItem3D->Enabled = (true);
    menuItemRemoveAll->Enabled = (!isTimerActive);
    menuItemCustomAxis->Enabled = (!isTimerActive);
    menuItemCursorTool->Enabled = (true);
  }
  else if (index==1)
  {
    menuItem3D->Checked = (SubElemForm->get3DMode());
    menuItem3D->Enabled = (true);
    menuItemRemoveAll->Enabled = (!isTimerActive);
    menuItemCustomAxis->Enabled = (false);
    menuItemCursorTool->Enabled = (true);
  }
  else
  {
   menuItem3D->Checked = (false);
   menuItem3D->Enabled = (false);
   menuItemRemoveAll->Enabled = (false);
   menuItemCustomAxis->Enabled = (false);
   menuItemCursorTool->Enabled = (false);
  }
}
//----------------------------------------------------------------
System::Void CAnalyzeLogFileForm::LoadAnalyzeForm(System::Object ^  sender, System::EventArgs ^  e)
{
  //---------------------------------------------------------------------------
  //alle Telegramme vom LogFile ins Container laden
  this->barView = gcnew CProgressBarViewForm(); 
  CProgressBarStatusWriter^ ProgressWriter = gcnew CProgressBarStatusWriter(barView);
  CMessageWriter^ MessageWriter = gcnew CMessageWriter(MessageForm);
  this->MessageForm->setActionName("Load Log File");
  this->TlgConFromLogFile->setTlgProtoTyp(TlgPrototypCon->getTlgProtoTypSet());
   
  //--------Datei Groesse ermitteln -------
  System::IO::FileInfo^ file = gcnew System::IO::FileInfo(path);
  //File Groesse an ProgressBar ubergeben
  barView->setMinAndMax(0,file->Length);
  barView->setSourceLab(path);
  barView->setCancelButtonVisible(true);
  CProgressBarViewForm::BarViewAbortDelTyp^ barViewAbort = gcnew CProgressBarViewForm::BarViewAbortDelTyp(this,&CAnalyzeLogFileForm::AbortLogFileReadThread); 
  barView->setBarViewAbortDelTyp(barViewAbort);
  
  
  //Thread fuer LogFileReader
  System::Threading::ThreadStart^ delStart = gcnew System::Threading::ThreadStart(this,&CAnalyzeLogFileForm::logFileReadThread);
  LogFileReadThread= gcnew System::Threading::Thread(delStart);
  LogFileReadThread->Start();
  
  MessageWriter->startWrite();
  ProgressWriter->startWrite();
  
  //BarView als Modal anzeigen
  barView->ShowDialog();
  
  //Thread beenden
  LogFileReadThread->Abort();
  ProgressWriter->endWrite();
  MessageWriter->endWrite();
  barView = nullptr;
  //---------------------------------------------------------------------------
  //Ausgabe
  String^ mess = String::Concat(System::Convert::ToString(TlgConFromLogFile->getTlgCount()),
																" from ",System::Convert::ToString(TlgConFromLogFile->getCountTlgTotal()),
																" telegrams accepted.");
	CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
	this->MessageForm->writeLine(mess,CMessageForm::MessTyp::Info);
  //TlgConFromLogFile->getCountTlgTotal();
	/*this->last_pos=pos;*/
	//Ueberpruefen, ob Con nicht leer ist.
  
  if (this->TlgConFromLogFile->getTlgCount()!=0)
  {
    double maxTime=this->TlgConFromLogFile->getTlgTime(this->TlgConFromLogFile->getTlgCount()-1);
    //Tlg TeeChart Diagramm
    TlgForm = gcnew CAnalyzeTlgForm(panTlgDiagramView,TlgConFromLogFile->getTlgTime(1),maxTime); 
    TlgForm->setPointerOfMessage(MessageForm);  
    TlgForm->Show();
    //SubElem Tee Chart Diagramm
    SubElemForm = gcnew CAnalyzeSubElemForm(panValueDiagramView,TlgConFromLogFile->getTlgTime(1),maxTime);  
    SubElemForm->setPointerOfMessage(MessageForm);  
    SubElemForm->Show();

    //Selected Page
    tabDiagramControl->SelectedIndex = (0);
    menuItem3D->Checked = (TlgForm->get3DMode());
    menuItem3D->Enabled = (true);
    
    
    /*CAnalyzeSubElemForm* SubElemForm;
    CAnalyzeTlgForm* TlgForm;
    CAnalyzeSubElemForm* SubElemForm;*/
    
    /*this->AnalyzeDiagramForm = gcnew CAnalyzeDiagramForm(this->panViewTeeChart,this->TlgConFromLogFile->getTlgTime(1),maxTime);
    this->AnalyzeDiagramForm->setPointerOfMessage(MessageForm);
    this->AnalyzeDiagramForm->Show();*/
  }
  else
  {
    this->panViewLeft->Hide();
    this->panViewTeeChart->Hide();
    this->panViewMessageBox->Dock = DockStyle::Fill;
  }
  /*InterfaceContainerView->ShowContainer();*/
  //DataTable
 /* this->TlgDataTable = gcnew CTlgDataGridViewForm(panDataGridView);*/
  this->TlgDataTableCon = nullptr;       
}
//------------------------------------------------------------------------------
void CAnalyzeLogFileForm::AbortLogFileReadThread()
{
	//Thread Log File auslesen, beenden.
	 AbortLogFileReaderThreadInAnalyzer = true;
	/*LogFileReadThread->Abort();
	LogFileReadThread->Join();*/
		 
	//Alle schon geladene LogFiles entfernen
  //SenderForm->clearLogFile(interName);
	//ProgressBar schliessen
  //barView->Close();
}
//----------------------------------------------------------------
void CAnalyzeLogFileForm::logFileReadThread()
{
  long pos =0;
  AbortLogFileReaderThreadInAnalyzer = false;
  TlgConFromLogFile->loadFromFileToAnalyze(pos,path,AbortLogFileReaderThreadInAnalyzer);
  //LogFileReadThread->Sleep(100);
  System::Threading::Thread::CurrentThread->Sleep(100);
  bool ok = true;
  do
  {
    if (System::Threading::Monitor::TryEnter(barView))
    {
      barView->Close();
      System::Threading::Monitor::Exit(barView);
      ok = false;
    }
    else
      System::Threading::Thread::CurrentThread->Sleep(100);
  }
  while (ok);

 this->last_pos=pos;
}
//----------------------------------------------------------------
System::Void CAnalyzeLogFileForm::OnAddToAnalyzeClick(System::Object ^  sender, System::EventArgs ^  e)
{
  //this->Cursor = Cursors::WaitCursor;
  //if (InterfaceContainerView->getNodeFillPathAfterSelect()=="0")
  //{
  //  tabDiagramControl->set_SelectedIndex(0);
  //  // Hilfsvariable
  //  CItemWrapper^ Tlg= 0;
  //  Tlg=InterfaceContainerView->getClonedTlg( TlgPrototypCon->getSelectedItem());
  //  addTlgToDiagram(Tlg->getName());
  //  tabDiagramControl->set_SelectedIndex(0);
  //}
  //else
  //{
  //  tabDiagramControl->set_SelectedIndex(1);
  //  String^ temp=this->InterfaceContainerView->getNodeFillPathAfterSelect();
  //  //Hilfsvariablen
  //  CItemWrapper^ tlg=gcnew CTlgWrapper();
		//String^ tlgName=0;
  //  String^ elemName=0;
  //  String^ subElemName=0;
  //  String^ typ=0;
  //  int index;
  //  int tlgFoundIndex;
  //  bool ok=true;
		//// TlgName, elemName und subElemName aus String auslesen
  //  {
  //    int temp_ = temp->IndexOf(" ");
  //    if (temp_ != -1)
  //      tlgName=temp->Substring(0,temp_);
  //  }
  //  
  //  temp=temp->Remove(0,temp->IndexOf("\\")+1);
  //  if (temp->IndexOf("\\")==-1)
  //  {
		//	elemName=temp;
  //    if (elemName->IndexOf(" ")!=-1)
  //      elemName=elemName->Substring(0,elemName->IndexOf(" "));
  //    subElemName="-1";
  //  }
  //  else
  //  {
  //    elemName=temp->Substring(0,temp->IndexOf("\\"));
  //    temp=temp->Remove(0,temp->IndexOf("\\")+1);
  //    subElemName=temp;
  //    subElemName=subElemName->Substring(0,subElemName->IndexOf(" "));
  //  }
  //  //TellegrammWert aus InterfacePrototypCon pruefen
  //  //int x = this->TlgPrototypCon->findTelegramm(1,tlgName);

  //  {
  //    tlgFoundIndex = this->TlgPrototypCon->findTelegramm(1,tlgName);
  //    //this->MessageForm->writeLine(System::Convert::ToString(test),CMessageForm::MessTyp::Error);
  //    if (tlgFoundIndex!=0)
  //    {
  //      this->TlgPrototypCon->getClonedTlg(tlg,tlgFoundIndex);
  //      if (subElemName->Equals("-1"))
  //      {
  //        index = tlg->getElemIndex(elemName);
  //        if  (index!=-1)
  //        {
  //          typ=tlg->getElemTypAsString(index);
  //          if ((typ->Equals("Integer")) || (typ->Equals("Double")))
  //          {
  //            //elem in Container suchen und zu TeeChartDiagramm hinzufuegen
  //            this->addTlgElemToDiagram(tlgName,elemName,subElemName);
  //          }
  //          else
  //          {
  //            // Ausgabe kein Integer oder kein Double
  //             this->MessageForm->writeLine(System::String::Concat(elemName," is invalid value."),CMessageForm::MessTyp::Error);
  //          }
  //        }
  //      }
  //      else
  //      {
  //        index = tlg->getElemIndex(elemName);
  //        int index2=tlg->getSubElemIndex(elemName,subElemName);
  //        if  (index!=-1 && index2!=-1)
  //        {
  //          typ=tlg->getSubElemTypAsString(index,index2);
  //          if ((typ->Equals("Integer")) || (typ->Equals("Double")))
  //          {
  //            //elem in Container suchen und zu TeeChartDiagramm hinzufuegen
  //            this->addTlgElemToDiagram(tlg->getSubElemName(index,index2),elemName,subElemName);
  //          }
  //          else
  //          {
  //            // Ausgabe kein Integer oder kein Double
  //            this->MessageForm->writeLine(System::String::Concat(subElemName," is invalid value."),CMessageForm::MessTyp::Error);
  //          }
  //        }
  //      }
  //    }
  //  }
  //}
  //this->Cursor = Cursors::Default;
}
//-------------------------------------------------------------------
void CAnalyzeLogFileForm::nodePathToTreeStrings(String^ tlgName,String^ elemName,String^ subElemName)
{
	String^ temp=this->InterfaceContainerView->getNodeFillPathAfterSelect();
	// TlgName, elemName und subElemName aus String auslesen
    tlgName=temp->Substring(0,temp->IndexOf(" "));
    temp=temp->Remove(0,temp->IndexOf("\\")+1);
    if (temp->IndexOf("\\")==-1)
    {
      
      elemName=temp;
      if (elemName->IndexOf(" ")!=-1)
        elemName=elemName->Substring(0,elemName->IndexOf(" "));
      subElemName="-1";
    }
    else
    {
      elemName=temp->Substring(0,temp->IndexOf("\\"));
      temp=temp->Remove(0,temp->IndexOf("\\")+1);
      subElemName=temp;
      subElemName=subElemName->Substring(0,subElemName->IndexOf(" "));
    }
}
//----------------------------------------------------------------
System::Void CAnalyzeLogFileForm::OnRemoveFromAnalyzeClick(System::Object ^  sender, System::EventArgs ^  e)
{
 // if (this->InterfaceContainerView->getNodeFillPathAfterSelect()=="0")
	//{
	//	// Hilfsvariable
	//	CItemWrapper^ Tlg= 0;
	//	ArrayList* tlgListe=0;
	//	Tlg=InterfaceContainerView->getClonedTlg( TlgPrototypCon->getSelectedItem());
	//	tlgListe=TlgForm->removeFromSeries(Tlg->getName());
	//	for (int i=0;i<tlgListe->Count;i++)
	//		this->addTlgToDiagram(safe_cast <String^> (tlgListe[i)));
	//	delete Tlg;
	//}
	//else
	//{
	//	String^ temp=this->InterfaceContainerView->getNodeFillPathAfterSelect();
 //   //Hilfsvariablen
	//	String^ tlgName=0;
 //   String^ elemName=0;
 //   String^ subElemName=0;
 //   // TlgName, elemName und subElemName aus String auslesen
 //   tlgName=temp->Substring(0,temp->IndexOf(" "));
 //   temp=temp->Remove(0,temp->IndexOf("\\")+1);
 //   if (temp->IndexOf("\\")==-1)
 //   {
	//		elemName=temp;
 //     if (elemName->IndexOf(" ")!=-1)
 //       elemName=elemName->Substring(0,elemName->IndexOf(" "));
 //     subElemName="-1";
 //   }
 //   else
 //   {
 //     elemName=temp->Substring(0,temp->IndexOf("\\"));
 //     temp=temp->Remove(0,temp->IndexOf("\\")+1);
 //     subElemName=temp;
 //     subElemName=subElemName->Substring(0,subElemName->IndexOf(" "));
 //   }
	//	//this->SubElemForm->removeFromSeries(tlgName,elemName,subElemName);
	//}
}
//---------------------------------------------------------------
void CAnalyzeLogFileForm::updateTlgOfDiagram(String^ name,int pos)
{
  int lastPos=0;
  double temp=0;
  bool ok=true;

  while(ok)
	{
		lastPos=TlgConFromLogFile->findTelegramm(pos,name);
		if (lastPos>0)
		{ 
			pos=lastPos;
			temp=TlgConFromLogFile->getTlgTime(pos);
			TlgForm->addToSeries(name,temp,true);
			pos++;
		}
		else 
		  ok=false;
		}
}

//----------------------------------------------
void CAnalyzeLogFileForm::updateValueOfDiagram(String^ name,int pos)
{
  int index;
  double temp=0;
  int lastPos=0;
  bool ok=true;
  //Liste mit der zug. Indezes 
  ArrayList^ list = safe_cast <ArrayList^>(NamesOfSubValues[name]);
  if (list)
  {
    CItemWrapper^ tlg=gcnew CTlgWrapper();
    String^ tlgName = nullptr;
    Int32 indexOfTlg = (int)(list[0]);
    TlgPrototypCon->getClonedTlg(tlg,indexOfTlg);
    tlgName = tlg->getName();
    CTlgElemWrapper^ elem = nullptr;
    elem = nullptr;
    String^ value = nullptr;
    Int32 index;
    while (ok)
	  {
		  lastPos=TlgConFromLogFile->findTelegramm(pos,tlgName);
		  if (lastPos>0)
		  { 
			  pos=lastPos;
        //Zeit des Tlgs
			  temp=TlgConFromLogFile->getTlgTime(pos);
        //Tlg holen
			  TlgConFromLogFile->getClonedTlg(tlg,pos);
        //Element ermitteln
        index = (int)(list[1]);
        if (!elem)
          elem = gcnew CTlgElemWrapper();
        elem->setTlgElem(tlg->getElem(index));
        for (int i=2;i<list->Count;i++)
        {
          index= (int)(list[i]);
          elem->setTlgElem(elem->getSubElem(index));
        }
        elem->getElemValue(value);
			  //Zur Diagramm hinzufuegen
        SubElemForm->addToSeries(tlgName,elem->getElemName(),temp,CFormatConverterWrapper::StringToDouble(value));
        //
			  pos++;
		  }
		  else 
			  ok=false;
    }
  }
  else
    return;
}
//----------------------------------------------------------------
void CAnalyzeLogFileForm::addItemToTable()
{
  CItemWrapper^ item = nullptr;
  if (InterfaceContainerView->getNodeFillPathAfterSelect()=="0")
  {
		//CItemWrapper^ Tlg= 0;
		item=InterfaceContainerView->getClonedTlg( TlgPrototypCon->getSelectedItem());
  }
  else
  {
    ArrayList^ list = InterfaceContainerView->getIndexListAfterSelect();
    item = gcnew CTlgWrapper();
    CTlgElemWrapper^ elem = gcnew CTlgElemWrapper();
    Int32 indexOfTlg = (int)(list[0]);
    TlgPrototypCon->getClonedTlg(item,indexOfTlg);
  }

  if (item)
  {
		::Cursor::Current = ::Cursors::WaitCursor;
    //Falls TableForm nicht erzeugt, erstellt
    if (!TlgDataTableCon)
          this->TlgDataTableCon = gcnew CDataGridContainerForm(panDataGridView,this->MessageForm);
    
    if (this->TlgDataTableCon)
    {
      if (!TlgDataTableCon->IsItemInside(item->getName()))
      {
        try
        {
          this->TlgDataTableCon->Hide();
          //lastPosForTable=0;
          tabDiagramControl->SelectedIndex = (2);
          this->TlgDataTableCon->addItem(item);
          this->addItemValuesToTable(item->getName());
          this->TlgDataTableCon->ShowDataGrid(item->getName());
          this->TlgDataTableCon->setFilter(item->getName());
          this->TlgDataTableCon->Show();
        }
        catch (System::Data::DuplicateNameException^ e)
        {
          String^ mess = System::String::Concat("The name of the elements is not unique. This telegram <",item->getName(),"> is not supported.");
          if (MessageForm)
            MessageForm->writeLine(mess,CMessageForm::MessTyp::Error);
          CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
																																		__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
          CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,e->Message,
																																		__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
          this->TlgDataTableCon->Show();
        }
      }
    }
		::Cursor::Current = ::Cursors::Default;
  }
}
//----------------------------------------------------------------
void CAnalyzeLogFileForm::removeItemFromDataTable()
{
	::Cursor::Current = ::Cursors::WaitCursor;
  
  CItemWrapper^ item = nullptr;
  if (InterfaceContainerView->getNodeFillPathAfterSelect()=="0")
  {
		//CItemWrapper^ Tlg= 0;
		item=InterfaceContainerView->getClonedTlg( TlgPrototypCon->getSelectedItem());
  }
  else
  {
    ArrayList^ list = InterfaceContainerView->getIndexListAfterSelect();
    item = gcnew CTlgWrapper();
    CTlgElemWrapper^ elem = gcnew CTlgElemWrapper();
    Int32 indexOfTlg = (int)(list[0]);
    TlgPrototypCon->getClonedTlg(item,indexOfTlg);
  }
 
  if (item)
	  if (TlgDataTableCon)
      TlgDataTableCon->removeItem(item->getName());	
  
  Cursor = Cursors::Default;
}
//----------------------------------------------------------------
void CAnalyzeLogFileForm::removeItemFromDiagram()
{
  Cursor = Cursors::WaitCursor;
  if (InterfaceContainerView->getNodeFillPathAfterSelect()=="0")
  {
    // Hilfsvariable
		CItemWrapper^ Tlg= nullptr;
		ArrayList^ tlgListe=nullptr;
		Tlg=InterfaceContainerView->getClonedTlg( TlgPrototypCon->getSelectedItem());
		tlgListe=TlgForm->removeFromSeries(Tlg->getName());
		
    for (int i=0;i<tlgListe->Count;i++)
			addTlgToDiagram(safe_cast <String^> (tlgListe[i]));
		delete Tlg;
  }
  else
  {
    ArrayList^ list = InterfaceContainerView->getIndexListAfterSelect();
    CItemWrapper^ tlg=gcnew CTlgWrapper();
    CTlgElemWrapper^ elem = gcnew CTlgElemWrapper();
    Int32 indexOfTlg = (int)(list[0]);
    TlgPrototypCon->getClonedTlg(tlg,indexOfTlg);
    getTlgElem(list,tlg,elem);
    //Sub Element entfernen
    SubElemForm->removeFromSeries(tlg->getName(),elem->getElemName());
    NamesOfSubValues->Remove(String::Concat(tlg->getName(),elem->getElemName()));
    delete tlg;
    delete elem;
  }
  Cursor = Cursors::Default;
}
//----------------------------------------------------------------
String^ CAnalyzeLogFileForm::getTlgElem (ArrayList^ list,CItemWrapper^ tlg,CTlgElemWrapper^ elem)
{
  String^ ret = nullptr;
  String^ typ = nullptr;
  //Element ermitteln
  Int32 index = (int)(list[1]);
  elem->setTlgElem(tlg->getElem(index));
  for (int i=2;i<list->Count;i++)
  {
    index= (int)(list[i]);
    elem->setTlgElem(elem->getSubElem(index));
  }

  typ=elem->getElemType();
  if (!(typ->Equals("Integer")) && !(typ->Equals("Double")))
    ret = String::Concat(elem->getElemName()," is invalid numeric value.");
  
  return ret;
}
//----------------------------------------------------------------
void CAnalyzeLogFileForm::addITemToDiagram(void)
{
  this->Cursor = Cursors::WaitCursor;
  if (InterfaceContainerView->getNodeFillPathAfterSelect()=="0")
  {
    tabDiagramControl->SelectedIndex = (0);
    // Hilfsvariable
    CItemWrapper^ Tlg= nullptr;
    Tlg=InterfaceContainerView->getClonedTlg( TlgPrototypCon->getSelectedItem());
    addTlgToDiagram(Tlg->getName());
    tabDiagramControl->SelectedIndex = (0);
  }
  else
  {
    tabDiagramControl->SelectedIndex = (1);
    addTlgElemToDiagram (InterfaceContainerView->getIndexListAfterSelect());
  }
  this->Cursor = Cursors::Default;
}
//----------------------------------------------------------------
void CAnalyzeLogFileForm::addTlgElemToDiagram (ArrayList^ ElemOrderList)
{
  String^ mess = nullptr;
	CItemWrapper^ tlg=gcnew CTlgWrapper();
  String^ tlgName = nullptr;
  String^ elemName = nullptr;
  Int32 indexOfTlg = (int)(ElemOrderList[0]);
  TlgPrototypCon->getClonedTlg(tlg,indexOfTlg);
  tlgName = tlg->getName();

  if (tlgName)
  {
    bool ok=true;
    bool found=false;
    bool firstRound = true;
	  int pos=0;
	  int lastPos=0;
    CTlgElemWrapper^ elem = gcnew CTlgElemWrapper();
    String^ error = nullptr;
    error = getTlgElem(ElemOrderList,tlg,elem);

    if (!error)
    {
      String^ tmp = String::Concat(tlgName,elem->getElemName());
      if (!NamesOfSubValues->Contains(tmp))
        NamesOfSubValues->Add(tmp,ElemOrderList);
      CProgressBarViewForm^ progressBar = gcnew CProgressBarViewForm(); 
      progressBar->setMinAndMax(0,TlgConFromLogFile->getCountTlgTotal());
      progressBar->setSourceLab(String::Concat("Add <",elem->getElemName(),"> to diagram ..."));

      while (ok)
	    {
        lastPos = this->TlgConFromLogFile->findTelegramm(pos+1,tlgName);
        if (lastPos>0)
		    {
          if (firstRound)
          {
            progressBar->Show();
            firstRound=false;
          }
          found=true;
          progressBar->updateStep(lastPos-pos);
			    pos=lastPos;
			    //Tlg holen
			    TlgConFromLogFile->getClonedTlg(tlg,lastPos);
          //TlgTime
			    double tlgTime=TlgConFromLogFile->getTlgTime(pos);
          //Element ermitteln
          CTlgElemWrapper^ elem = nullptr;
          String^ value = nullptr;
          Int32 index = (int)(ElemOrderList[1]);
          elem = gcnew CTlgElemWrapper();
          elem->setTlgElem(tlg->getElem(index));
          for (int i=2;i<ElemOrderList->Count;i++)
          {
            index= (int)(ElemOrderList[i]);
            elem->setTlgElem(elem->getSubElem(index));
          }
          elem->getElemValue(value);
          //Zur Diagramm hinzufuegen
          SubElemForm->addToSeries(tlgName,elem->getElemName(),tlgTime,CFormatConverterWrapper::StringToDouble(value));
        }
        else
        {
			    ok=false;
          if (!found)
					{
            mess = System::String::Concat(tlgName," is in ",this->path," not found.");
						CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,
																																		__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
						MessageForm->writeLine(mess,CMessageForm::MessTyp::Warning);
					}
        }
      }//while
      progressBar->Close();
    }
    else
    {
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,error,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
			MessageForm->writeLine(error,CMessageForm::MessTyp::Error);
      return;
    }
  }
  else
    return;
}
//----------------------------------------------------------------
void CAnalyzeLogFileForm::addTlgElemToDiagram (String^ tlgName,String^ tlgElem, String^ tlgSubElem)
{
	//CItemWrapper^ tlg=gcnew CTlgWrapper();
	//bool ok=true;
 // bool found=false;
 // bool firstRound = true;
	//int pos=0;
	//int last_pos=0;
	////int temp;
	//int elemId;
	//int subElemId;
	//double value=0.0;
	//double tlgTime;
	//std::string str (""); // !!
 // CProgressBarViewForm* progressBar = gcnew CProgressBarViewForm(); 
 // progressBar->setMinAndMax(0,TlgConFromLogFile->getCountTlgTotal());
 // if (!tlgSubElem->Equals("-1"))
 //   progressBar->setSourceLab(String::Concat("Add <",tlgSubElem,"> to diagram ..."));
 // else
 //   progressBar->setSourceLab(String::Concat("Add <",tlgElem,"> to diagram ..."));
 // 
	//while (ok)
	//{
	//	last_pos = this->TlgConFromLogFile->findTelegramm(pos+1,tlgName);
	//	if (last_pos>0)
	//	{
 //     if (firstRound)
 //     {
 //       progressBar->Show();
 //       firstRound=false;
 //     }
 //     found=true;
 //     progressBar->updateStep(last_pos-pos);
	//		pos=last_pos;
	//		//TlgTime
	//		tlgTime=TlgConFromLogFile->getTlgTime(pos);
	//		//Element finden
	//		this->TlgConFromLogFile->getClonedTlg(tlg,last_pos);
	//		
 //     
 //     if (tlgSubElem->Equals("-1"))
	//		{
	//			elemId=tlg->getElemIndex(tlgElem);
	//			CStdConverter::StringToStdStr(tlg->getElemValue(elemId),str);
	//			value=CFormatConverter::StringToDouble(str);
	//			//Zur Diagramm hinzufuegen
 //       this->SubElemForm->addToSeries(tlgName,tlgElem,tlgSubElem,tlgTime,value);
 //       /*this->AnalyzeDiagramForm->addToSeries(tlgName,tlgElem,tlgSubElem,tlgTime,value);*/
	//		}
	//		else
	//		{
	//			elemId=tlg->getElemIndex(tlgElem);
	//			subElemId=tlg->getSubElemIndex(tlgElem,tlgSubElem);
	//			CStdConverter::StringToStdStr(tlg->getSubElemValue(elemId,subElemId),str);
	//			value=value=CFormatConverter::StringToDouble(str);
	//			/*this->AnalyzeDiagramForm->addToSeries(tlgName,tlgElem,tlgSubElem,tlgTime,value);*/
	//		  this->SubElemForm->addToSeries(tlgName,tlgElem,tlgSubElem,tlgTime,value);
 //     }
	//	}
	//	else
 //   {
	//		ok=false;
 //     if (!found)
 //       MessageForm->writeLine(System::String::Concat(tlgName," is in ",this->path," not found."),CMessageForm::MessTyp::Warning);
 //   }
	//}//while
 // progressBar->Close();
}
//----------------------------------------------------------------
void CAnalyzeLogFileForm::addItemValuesToTable (String^ name)
{
  if (this->TlgDataTableCon)
  {
    CProgressBarViewForm^ progressBar = gcnew CProgressBarViewForm(); 
    int tlgCount,curentCount;
    tlgCount = TlgConFromLogFile->getCountTlgTotal();
    curentCount = 0;

    progressBar->setMinAndMax(0,tlgCount);
    String^ source = "Adding Telegrams to Data - Table.";
    progressBar->setSourceLab(source);
    progressBar->Show();

    int  counter = 0;
    int pos=0;
    int lastPos=0;
    double temp=0;
    bool ok=true;
    CItemWrapper^ item = gcnew CTlgWrapper();
    //-------------------------
    while (ok)
    {
      lastPos=TlgConFromLogFile->findTelegramm(pos+1,name);
		  if (lastPos>0)
      { 
        progressBar->updateStep(lastPos-pos);
        pos=lastPos;
        TlgConFromLogFile->getClonedTlg(item,pos);
        TlgDataTableCon->addItemValue(item);  
      }
      else 
      {
        ok=false;
 /*       lastPosForTable=pos;*/
        progressBar->updateStep(tlgCount);
      }

      //Wenn, 50 Telegramms gefunden wurde, PAUSE! CPU LAST VERMEIDEN!
      if ((++counter % 50) == 0)
        System::Threading::Thread::CurrentThread->Sleep(15);
    }
    progressBar->Close();
  }
}
//----------------------------------------------------------------
void CAnalyzeLogFileForm::UpdateValuesInTable(String^ name,int countTlg)
{
  if (this->TlgDataTableCon)
  {
    int  counter = 0;
    int pos=countTlg+1;
    //int pos=lastPosForTable;
    int lastPos=0;
    double temp=0;
    bool ok=true;
    CItemWrapper^ item = gcnew CTlgWrapper();
    //-------------------------
    while (ok)
    {
      lastPos=TlgConFromLogFile->findTelegramm(pos,name);
		  if (lastPos>0)
      { 
        pos=lastPos;
        TlgConFromLogFile->getClonedTlg(item,pos);
        TlgDataTableCon->addItemValue(item); 
        pos++;
      }
      else
      {
        ok=false;
        //lastPosForTable=pos;
      }

      //Wenn, 50 Telegramms gefunden wurde, PAUSE! CPU LAST VERMEIDEN!
      if ((++counter % 50) == 0)
        System::Threading::Thread::CurrentThread->Sleep(5);
    } 
  }
}
//----------------------------------------------------------------
void CAnalyzeLogFileForm::addTlgToDiagram (String^ name)
{
  bool checked = menuItemCustomAxis->Checked;
  
  if (!checked)
  {
    OnMenuCustomAxisClick(nullptr,nullptr);
    //menuItemCustomAxis->Checked=false;
  }
  
  //if (menuItemCustomAxis->Checked)
  //{
    int pos=0;
    int lastPos=0;
    double temp=0;
    bool ok=true;
    bool firstRound=true;
    CProgressBarViewForm^ progressBar = gcnew CProgressBarViewForm(); 
    progressBar->setMinAndMax(0,TlgConFromLogFile->getCountTlgTotal());
    progressBar->setSourceLab(String::Concat("Add <",name,"> to diagram ..."));
    //-------------------------
    while (ok)
    {
      lastPos=TlgConFromLogFile->findTelegramm(pos+1,name);
      if (pos==0 && lastPos<=0)
        TlgForm->addToSeries(name,0.0,true);
		  if (lastPos>0)
      { 
        if (firstRound)
        {
          progressBar->Show();
          firstRound=false;
        }
        progressBar->updateStep(lastPos-pos);
        pos=lastPos;
        temp=TlgConFromLogFile->getTlgTime(pos);
        TlgForm->addToSeries(name,temp,true);
        /*AnalyzeDiagramForm->addToSeries(name,temp,true);*/
      }
      else 
        ok=false;
    }
    progressBar->Close();
 /* }
  else
	{
    String^ mess = "Adds the telegram is allowed only in the custom axis mode.";
		CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3); 
		MessageForm->writeLine(mess,CMessageForm::MessTyp::Warning);
	}*/

    if (!checked)
       OnMenuCustomAxisClick(nullptr,nullptr);

}
//----------------------------------------------------------------
System::Void CAnalyzeLogFileForm:: OnResizeInterfaceConTlg(System::Object ^  sender, System::EventArgs ^  e)
{

}
//----------------------------------------------------------------
System::Void CAnalyzeLogFileForm :: OnTimeForUpdateTxtBox(System::Object ^  sender, System::EventArgs ^  e)
{
  /*bool ok=false;
  for (int i=48;i<58;i++)
  {
    char temp;
    temp=this->txtBoxTimeUpdate->Text->String::get_Chars(txtBoxTimeUpdate->get_TextLength()-1);
    if (temp==i)
    {
      ok=true;
      break;
    }
  }
  if (!ok)
  {
    this->txtBoxTimeUpdate->remove_
  }*/
  
  //int temp;
  //temp=System::Convert::ToInt32(txtBoxTimeUpdate->Text);
  ////temp=(int)System::IConvertible::ToInt32();
}
//----------------------------------------------------------------
System::Void CAnalyzeLogFileForm:: OnTimeForUpdateClick(System::Object ^  sender, System::EventArgs ^  e)
{
  String^ mess = nullptr;
  if (this->isTimerActive==false)
  {
    //Text Box Eingabe wird auf Gueltigkeit ueberprueft.
    System::String^ temp=nullptr;
    bool ok=true;
    //Wenn TextBox nicht leer ist.
    if (this->txtBoxTimeUpdate->Text->Length!=0)
    {
      temp=this->txtBoxTimeUpdate->Text;
      //Wenn este Zeichen gleich 0 ist.
			if (temp->default[0]==48)
        ok=false;
    }
    //Wenn nichts eigegeben wurde.
    else
      ok=false;
    
    if (ok)
    { 
      int i=0;
      //Wenn Sting mehr als 9 Zeichen enthält.
      if (temp->Length>9)
      {
        ok=false;
				mess = System::String::Concat(temp," is too long.");
				CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,
                                                         __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        MessageForm->writeLine(mess,CMessageForm::MessTyp::Warning);
      }
      //Ueberpruefen, ob String nur die Zahhlen enthaelt
      while (ok && i<temp->Length)
      {
        for (int j=48;j<=58;j++)
        {
          if (temp->default[i]==j)
            break;
          if (j==58)
            ok=false;
        }
        i++;
     }
    }
    if (!ok)
		{
      mess = System::String::Concat(temp," is no valid time.");
			CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,
																															__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
			MessageForm->writeLine(mess,CMessageForm::MessTyp::Warning);
		}
    else
    {
      //String in Integer konvertieren
      this->timeForUpdate=System::Convert::ToInt32(this->txtBoxTimeUpdate->Text);
      //Button auf Gruen setzen
      this->isTimerActive=true;
      this->butTimeForUpdate->BackColor = System::Drawing::Color::Green;
      this->butTimeForUpdate->Text = "Stop";
      //ToolTip setzen
      this->ToolTipStartAndStop->SetToolTip(butTimeForUpdate,rm->GetString("IDS_ANALYZER_STOP"));
      //Add and Remove Button deaktivieren
		  this->InterfaceContainerView->setKontextMenuVisible(false);
      this->butRemoveFromAnalyze->Enabled = false;
      this->butAddToAnalyze->Enabled = false;
      menuItemRemoveAll->Enabled=(false);
      menuItemCustomAxis->Enabled=(false);
      //Modus Custom Axis wechseln
      if (!menuItemCustomAxis->Checked)
      {
        OnMenuCustomAxisClick(nullptr,nullptr);
      }
      //Thread starten
      System::Threading::ThreadStart ^del;
      del = gcnew System::Threading::ThreadStart (this,&CAnalyzeLogFileForm::readLogFileWithTimer);
      this->timerThread=gcnew System::Threading::Thread(del);
      this->timerThread->Start();
    }
  }
  // (Green)
  else
  {
    this->isTimerActive=false;
    this->butTimeForUpdate->BackColor = System::Drawing::Color::Red;
    this->butTimeForUpdate->Text = "Start";
    this->ToolTipStartAndStop->SetToolTip(butTimeForUpdate,rm->GetString("IDS_ANALYZER_START"));
    //this->timerThread->Abort();
    //this->timerThread=0;
    //Add and Remove Button aktivieren
	  this->InterfaceContainerView->setKontextMenuVisible(true);
    this->butRemoveFromAnalyze->Enabled = true;
    this->butAddToAnalyze->Enabled = true;
    tabDiagramControl_SelectedIndexChanged(nullptr,nullptr);
  }
}

//----------------------------------------------------------------
void CAnalyzeLogFileForm :: readLogFileWithTimer()
{ 
  String^ mess = nullptr;
  CLogWriterWrapper^ logWriter = CLogWriterWrapper::getLogWriterWrapper();
  bool ok;
  bool okTimer=true;
  long pos=0;
  int index;
  int countTlg=0;
  String^ temp;
  DateTime before;
  /* DateTime after;*/
	int afterTemp = 0;
  int different = 0;
  //Hilfsvariable, hat auf Aufruf der Funktion keine Bedeutung
  const bool tmp = false;
  
  while (okTimer)
  {
    //Zeit merken
    before = DateTime::Now;

    //Anzahl der Tlgs merken
    countTlg = TlgConFromLogFile->getTlgCount();
    //Log File ab letzte Stelle auslesen
    pos = this->last_pos;
    TlgConFromLogFile->loadFromFileToAnalyze(pos,this->path,tmp);
    this->last_pos=pos;

    //Pruefen, ob neue Tlg da sind
    if (TlgConFromLogFile->getTlgCount()>countTlg)
    { 
      mess = String::Concat(CFormatConverterWrapper::IntToString(TlgConFromLogFile->getTlgCount() - countTlg),
                      " new telegrams accepted.");
      logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
																__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3); 
      MessageForm->writeLine(mess,CMessageForm::MessTyp::Info);

      ok=true;
      index=0;

      //Tlg uberpruefern
      while (ok)
      {
        temp=TlgForm->getSeriesTlgNames(index);
        if (temp->Equals("-1"))
				{
          ok=false;
				}
        else
			  {
          this->updateTlgOfDiagram(temp,countTlg);
			  }
        index++;
      }

      //Values uberpruefen
      ok=true;
      index=0;

      while (ok)
      {
        temp=SubElemForm->getSeriesValueNames(index);
        if (temp->Equals("-1"))
          ok=false;
        else
			  {
          this->updateValueOfDiagram(temp,countTlg);
			  }
        index++;
      }
      //countTlg=TlgConFromLogFile->getTlgCount();

      //Telegramm in DataGrid aktualisieren
      if (TlgDataTableCon)
      {
        String^ tmpName = nullptr;
        ArrayList^ names = TlgDataTableCon->getItemNames();
        if (names->Count > 0)
        {
          for (int i=0;i<names->Count;i++)
          {
            tmpName = safe_cast <String^> (names[i]);
            UpdateValuesInTable(tmpName,countTlg);
          }
        }
      }

    }
    /*after = DateTime::Now;*/
		/*System::DateTime::Now::Subtract(StartZeit).TotalMilliseconds)*/
		
		afterTemp = System::DateTime::Now.Subtract(before).TotalMilliseconds;
    different = timeForUpdate-afterTemp;
    if(different > 0)
		{
			System::Threading::Thread::CurrentThread->Sleep(different);
      mess = String::Concat("Thread Pause in ms. : ",CFormatConverterWrapper::IntToString(different));
      logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
																__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3); 
			//this->timerThread->Sleep(afterTemp);
		}
    if (!(this->isTimerActive))
		{
      okTimer=false;
		}
   }
  this->isThreadReady=true;
  //this->timerThread->Abort(); //?
}

//----------------------------------------------------------------
void CAnalyzeLogFileForm ::initViewComponent(ArrayList^ InterfaceListe,int index,String^ path)
{
  this->delAddToTableEvent = gcnew CItemPrototypContainerForm::DelAddToTable(this,&CAnalyzeLogFileForm::addItemToTable);
  this->delAddToDiagramEvent = gcnew CItemPrototypContainerForm::DelAddToDiagram(this,&CAnalyzeLogFileForm::addITemToDiagram);
  this->delRemoveFromDiagramEvent= gcnew CItemPrototypContainerForm::DelRemoveFromDiagram(this,&CAnalyzeLogFileForm::removeItemFromDiagram);
  this->delRemoveFromDataTableEvent= gcnew CItemPrototypContainerForm::DelRemoveFromDataTable(this,&CAnalyzeLogFileForm::removeItemFromDataTable);
  this->timerThread=nullptr;
  //this->TopMost = true;
  this->timeForUpdate=0;
  this->path=path;
  this->Text=this->path;
  //Thread-Timer
  //this->autoLogFileReading=0;
  this->isTimerActive=false;
  this->isThreadReady=false;
  //Merkt immer die letzt Stelle im LogFile fuer Table
	//lastPosForTable=0;
  //last_pos Merkt immer die letzt Stelle im LogFile
  this->last_pos=0;
  //Container enthaelt alle Tellegramme vom Log File
  this->TlgConFromLogFile = gcnew CTlgLogFileReaderWrapper();
  // Container fuer Tellegramme (von Inteface)
  this->TlgPrototypCon= nullptr;
	this->TlgPrototypCon=safe_cast <CTlgInterfaceWrapper ^>(InterfaceListe[index]);
  // Container mit Tellegrammen sortieren, bevor er angezeigt wird 
  this->TlgPrototypCon->sortContainer();
	//// View-Container fuer Telgramme
 // this->InterfaceContainerView = gcnew CTlgContainerTreeViewForm(panViewInterfaceConTlg);
	////InterfaceContainerView->Dock =DockStyle::Fill;
 // this->InterfaceContainerView->Show();
	//this->InterfaceContainerView->setTlgContainer(TlgPrototypCon);
 // this->InterfaceContainerView->ShowContainer();

   //View-Container fuer Telgramme
  this->InterfaceContainerView = gcnew CItemPrototypContainerForm(panViewInterfaceConTlg);
	//InterfaceContainerView->Dock =DockStyle::Fill;
  this->InterfaceContainerView->Show();
	this->InterfaceContainerView->setPrototypContainer(TlgPrototypCon);
  this->InterfaceContainerView->showContainer();
  this->InterfaceContainerView->setContextMenuActiv();
  this->InterfaceContainerView->setAddToTableEvent(delAddToTableEvent);
  this->InterfaceContainerView->setAddToDiagramEvent(delAddToDiagramEvent);
  this->InterfaceContainerView->setRemoveFromDiagramEvent(delRemoveFromDiagramEvent);
  this->InterfaceContainerView->setRemoveFromDataTableEvent(delRemoveFromDataTableEvent);
  //PrototypForm = gcnew CItemPrototypContainerForm(); 
  //PrototypForm->setPrototypContainer(TlgPrototypCon);
  //PrototypForm->Show();
  // Message Form
  this->MessageForm = gcnew  CMessageForm (panViewMessageBox);
  this->MessageForm->setActionName("MessageBox");
	this->MessageForm->Show();
  //Check Box
  /*this->checkBoxDiagramm->Checked = (true);*/
  /*this->checkBoxTable->Checked = (false);*/
  //Stellt Verbinung zur Ressource-Datei her
  this->rm = gcnew System::Resources::ResourceManager("ToolTipsStrings",System::Reflection::Assembly::GetExecutingAssembly());
  //ToolTips Erzeugen und Setzen
  this->ToolTipStartAndStop=gcnew System::Windows::Forms::ToolTip();
  this->ToolTipStartAndStop->SetToolTip(butTimeForUpdate,rm->GetString("IDS_ANALYZER_START"));
  this->ToolTipAdd=gcnew System::Windows::Forms::ToolTip();
  this->ToolTipAdd->SetToolTip(butAddToAnalyze,rm->GetString("IDS_ANALYZER_ADD"));
  this->ToolTipRemove=gcnew System::Windows::Forms::ToolTip();
  this->ToolTipRemove->SetToolTip(butRemoveFromAnalyze,rm->GetString("IDS_ANALYZER_REMOVE"));
  this->ToolTipTimeUpdate=gcnew System::Windows::Forms::ToolTip();
  this->ToolTipTimeUpdate->SetToolTip(txtBoxTimeUpdate,rm->GetString("IDS_ANALYZER_TIME_INPUT"));
	//Einige Panel verstecken
	this->panViewButAddToAnalyze->Hide();
	//this->panViewOptions->Hide();
  this->menuItemCustomAxis->Checked=true;
  //
  this->NamesOfSubValues = gcnew Hashtable();
  //
  this->KeyPreview = true;
}
//------------------------------------------------------------------