#include "StdAfx.h"
#include "CAnalyzeTlgForm.h"
#include "CLogWriterWrapper.h"

using namespace System;
using namespace simulator;
using namespace Steema;

void CAnalyzeTlgForm::ResumeZoom()
{
  for (int i=0;i<axTChartTlgDiagram->Axes->Custom->Count;i++)
  {
     axTChartTlgDiagram->Axes->Custom[i]->Visible = true;  
     axTChartTlgDiagram->Axes->Custom[i]->Horizontal = true;
     axTChartTlgDiagram->Series[i]->CustomHorizAxis = axTChartTlgDiagram->Axes->Custom[i];
  }
}
//---------------------------------------------
void CAnalyzeTlgForm::setCustomAxisMode(bool mode)
{
  axTChartTlgDiagram->Chart->Zoom->Undo();
  if (mode)
  {
      for (int i=0;i<axTChartTlgDiagram->Axes->Custom->Count;i++)
      {
         axTChartTlgDiagram->Axes->Custom[i]->Visible = true;  
         axTChartTlgDiagram->Axes->Custom[i]->Horizontal = true;
         axTChartTlgDiagram->Axes->Custom[i]->Automatic=true;
         axTChartTlgDiagram->Series[i]->CustomHorizAxis = axTChartTlgDiagram->Axes->Custom[i];
         axTChartTlgDiagram->Axes->Bottom->Visible = false;
         
      }
      axTChartTlgDiagram->Zoom->Allow = false;
      /*axTChartTlgDiagram->Panning->Dispose();*/
      axTChartTlgDiagram->Panning->Allow = Steema::TeeChart::ScrollModes::None;
  }
  else
  {
    for (int i=0;i<axTChartTlgDiagram->Axes->Custom->Count;i++)
    {
       axTChartTlgDiagram->Axes->Custom[i]->Visible = false; 
       axTChartTlgDiagram->Axes->Custom[i]->Horizontal = false;
       axTChartTlgDiagram->Series[i]->CustomHorizAxis = nullptr;
    }

     axTChartTlgDiagram->Axes->Bottom->Visible = true;
     axTChartTlgDiagram->Axes->Bottom->Automatic=true;
     axTChartTlgDiagram->Axes->Bottom->Horizontal = true;
     axTChartTlgDiagram->Axes->Bottom->StartPosition = 0.5;
     axTChartTlgDiagram->Axes->Bottom->EndPosition = 99.5;
     axTChartTlgDiagram->Zoom->Allow = true;
     axTChartTlgDiagram->Panning->Allow = Steema::TeeChart::ScrollModes::Horizontal; 
  }
}
//---------------------------------------------
void CAnalyzeTlgForm::setCursor(bool edit)
{
  axTChartTlgDiagram->Tools[0]->Active=edit;
}
//---------------------------------------------
System::Void CAnalyzeTlgForm::axTChartTlgDiagram_Zoomed(System::Object^  sender, System::EventArgs^  e) 
{
   //for (int i=0;i<axTChartTlgDiagram->Axes->Custom->Count;i++)
   //{
   //  axTChartTlgDiagram->Axes->Custom[i)->set_Visible(false); 
   //  axTChartTlgDiagram->Axes->Custom[i)->Horizontal = false;
   //  axTChartTlgDiagram->Series[i)->CustomHorizAxis = 0;
   //}

   //axTChartTlgDiagram->Axes->Bottom->set_Visible(true);
   //axTChartTlgDiagram->Axes->Bottom->Automatic=true;
   //axTChartTlgDiagram->Axes->Bottom->Horizontal = true;
}
//---------------------------------------------
System::Void CAnalyzeTlgForm::axTChartTlgDiagram_UndoneZoom(System::Object^  sender, System::EventArgs^  e) 
{
  //ResumeZoom();
}
//---------------------------------------------
void CAnalyzeTlgForm::setStartTime(double TlgNullTime)
{
  minTime=TlgNullTime;
}
//---------------------------------------------
void CAnalyzeTlgForm::set3DMode(bool mode)
{
  axTChartTlgDiagram->Aspect->View3D = mode;
}
//---------------------------------------------
void CAnalyzeTlgForm::setPointerOfMessage(CMessageForm^ MessageForm)
{
  this->MessageForm=MessageForm;
}
//---------------------------------------------
bool CAnalyzeTlgForm::get3DMode(void)
{
  return axTChartTlgDiagram->Aspect->View3D; 
}
//---------------------------------------------
String^ CAnalyzeTlgForm::getSeriesTlgNames(int index)
{
  if (index<axTChartTlgDiagram->SeriesCount)
	{
    return (axTChartTlgDiagram->Series[index]->Title);
	}
  else
	{
    return ("-1");
	}
}
//---------------------------------------------
void CAnalyzeTlgForm::removeAll()
{
  String^ mess = nullptr;
	if (axTChartTlgDiagram->SeriesCount != 0)
  {
    numOfSeries->Clear();
    axTChartTlgDiagram->Series->Clear();
    axTChartTlgDiagram->Axes->Custom->RemoveAll();
    TeeChart::Axis^ leftAxis = axTChartTlgDiagram->Axes->Left;
    leftAxis->Labels->Items->Clear();
    leftAxis->Automatic = false; 
    leftAxis->Maximum = 5; 
    leftAxis->Minimum = 0;
    for (int i=0;i<=5;i++)
    {
      leftAxis->Increment = i;
    }
    mess = "All telegrams removed.";
		CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
		MessageForm->writeLine(mess,CMessageForm::MessTyp::Info);
  }
  else
	{
    mess = "No telegrams in diagram found";
		CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
		MessageForm->writeLine(mess,CMessageForm::MessTyp::Error);
	}
}
//---------------------------------------------
ArrayList^ CAnalyzeTlgForm::removeFromSeries(String^ TlgName)
{
  String^ mess = nullptr;
	ArrayList^ tempListe = gcnew ArrayList(); 
  TeeChart::Axis^ leftAxis = axTChartTlgDiagram->Axes->Left;
  //Wenn Serie mit TlgName exis.
  if (numOfSeries->ContainsKey(TlgName))
  {
    String^ tempString=nullptr;
    int tempInt=0;
    int temp=0;
    //Nummer der Serie wird aus NummerListe geholt
    int number= (int) (numOfSeries[TlgName]);
    //Serie wirs aus axTChartDiagram entfernt 
    axTChartTlgDiagram->Series->RemoveAt(number-1);
    axTChartTlgDiagram->Refresh();
	  //Serie aus numOfSeries entfernen
    numOfSeries->Remove(TlgName);
    //Restrliche Series in die Liste speichern
    for (int i=0;i<axTChartTlgDiagram->SeriesCount;i++)
    {
      tempListe->Add(axTChartTlgDiagram->Series[i]->Title);
      numOfSeries->Remove(axTChartTlgDiagram->Series[i]->Title);
    }
    axTChartTlgDiagram->Series->RemoveAllSeries();
    axTChartTlgDiagram->Axes->Custom->RemoveAll();
    leftAxis->Labels->Items->Clear();
		mess = System::String::Concat(TlgName," removed.");
		CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    MessageForm->writeLine(mess,CMessageForm::MessTyp::Info);
    //Linke Achse anpassen
    temp=(int)leftAxis->Maximum;
		if (temp-(axTChartTlgDiagram->SeriesCount) > 5)
    {
      temp =(int)leftAxis->Maximum;
      temp -=5;
      leftAxis->Maximum=temp;
      for (int i=0;i<=leftAxis->Maximum;i++)
      {
        leftAxis->Increment = i;
      }
    }
  }
  else
	{
    mess = System::String::Concat(TlgName," in diagram not found.");
		CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
		MessageForm->writeLine(mess,CMessageForm::MessTyp::Error);
	}
  return tempListe;
}
//---------------------------------------------
void CAnalyzeTlgForm::addToSeries(String^ TlgName,double TlgTime,bool newTlg)
{ 
    axTChartTlgDiagram->Chart->Zoom->Undo();
    //Hilfsvariablen
    TeeChart::Styles::Series^ ser=nullptr;
    TeeChart::Axis^ leftAxis = axTChartTlgDiagram->Axes->Left;
    double zeit;
    int number;
    bool neu=true;

    //MaxTime bestimmen
    if (maxTime < TlgTime-(minTime))
    {
      maxTime=TlgTime-(minTime);
    }
   
    //Wenn keine Series exis oder keine Series mit gleichen TlgName vorhanden ist.
    for (int i=0;i<axTChartTlgDiagram->SeriesCount;i++)
    {
			if (TlgName->Equals(axTChartTlgDiagram->Series[i]->Title))
	    {
		    // Zeichnen Tlg
		     zeit=(TlgTime-(minTime));
		    //Nummer der Serie wird aus List mit Serie geholt
		    number= (int) (numOfSeries[TlgName]);
        ser=axTChartTlgDiagram->Series[i];
		    //Zeichnen
		    if (TlgTime==0.0)
		    {
          ser->Add(0.0,(double)number);
			    ser->Add(maxTime,(double)number);
		    }
		    else
		    {
          ser->Add(0.0,(double)number);
			    ser->Add(zeit,(double)number);
			    ser->Add(zeit,(double)number+0.3);
			    ser->Add(zeit,(double)number);
		    }
		    neu=false;
		    break;
	    }
    }
  	
    if (axTChartTlgDiagram->Series->Count < 14 && neu)
    {
      //Wenn's Telegramm nicht in Charts - Diagramm enhalten ist
      createNewSeries(TlgName);
      // Zeichnen Tlg
      zeit=(TlgTime-(minTime));
      //Nummer der Serie wird aus Serie geholt
      number= (int)(numOfSeries[TlgName]);
      ser=axTChartTlgDiagram->Series[axTChartTlgDiagram->SeriesCount-1];
      //Zeichnen
      if (TlgTime==0.0)
      {
        ser->Add(0.0,(double)number);
        ser->Add(maxTime,number);
      }
      else
      {
        ser->Add(0.0,(double)number);
        ser->Add(zeit,(double)number);
        ser->Add(zeit,(double)number+0.3);
        ser->Add(zeit,(double)number);
      } 
    }
    else if (axTChartTlgDiagram->Series->Count >= 14)
		{
      String^ mess = "The diagram can contain only 14 telegrams.";
			CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
			MessageForm->writeLine(mess,CMessageForm::MessTyp::Warning);
		}

    //Linke Achse Maximum merken
    leftAxisMax=leftAxis->Maximum;
    ////restliche Series Linie erweitern
   // for (int i=0;i<axTChartTlgDiagram->get_SeriesCount();i++)
   // {
   //   ser=axTChartTlgDiagram->Series[i);
   //   ser->Add(maxTime,(double)(i+1));
   //   ser=0;
   // }
 
}

//---------------------------------------------------------
void CAnalyzeTlgForm::createNewSeries(String^ TlgName)
{
  TeeChart::Axis^ leftAxis = axTChartTlgDiagram->Axes->Left;
  int temp=axTChartTlgDiagram->SeriesCount;
  //TeeChart::Styles::FastLine^ fastLine = gcnew TeeChart::Styles::FastLine();
  TeeChart::Styles::FastLine^ fastLine = gcnew TeeChart::Styles::FastLine();

  //Custom Axis
  Steema::TeeChart::Axis^ axis1 = gcnew Steema::TeeChart::Axis(axTChartTlgDiagram->Chart);
  axis1->Automatic = true;
  axis1->Horizontal = true;
  axis1->Grid->Visible = false;
  //axis1->PosAxis=true;
	axis1->RelativePosition = ((axTChartTlgDiagram->SeriesCount+1)*(100/leftAxis->Maximum))-0.6;
  axis1->MaximumOffset = 5;
  axis1->AxisPen->Color = System::Drawing::Color::FromArgb((System::Int32)(System::Byte)127, (System::Int32)(System::Byte)0, 
                          (System::Int32)(System::Byte)0, (System::Int32)(System::Byte)255);
  axis1->AxisPen->Transparency = 50;
  axis1->AxisPen->Width = 1;
  //Title
  axis1->Title->Right = true;
  axis1->Title->Text = "ms.";
  axTChartTlgDiagram->Axes->Custom->Add(axis1);
  fastLine->CustomHorizAxis = axis1;
  //new Serie
  axTChartTlgDiagram->Series->Add(fastLine);
  TeeChart::Styles::Series^ ser = axTChartTlgDiagram->Series[temp];
  ser->Title = TlgName;
  //Add new serie to hashmap table
  numOfSeries->Add(TlgName,(axTChartTlgDiagram->SeriesCount));
  //Farbe setzen 
  if (axTChartTlgDiagram->SeriesCount % 4 == 1)
    ser->Color = Drawing::Color::Black;
  else if (axTChartTlgDiagram->SeriesCount % 4 == 2)
    ser->Color = Drawing::Color::Red;
  else if (axTChartTlgDiagram->SeriesCount % 4 == 3)
    ser->Color = Drawing::Color::Green;
  else
    ser->Color = Drawing::Color::Blue;
  
  
  //
  axis1->ZPosition = ser->ZOrder;

  //Linke Achse und Custom Achse Position anpassen, falls erforderlich
  leftAxis->Labels->Items->Add(axTChartTlgDiagram->SeriesCount,TlgName);
  if (axTChartTlgDiagram->SeriesCount >= leftAxis->Maximum)
  {
    int temp2 =(int)leftAxis->Maximum;
    temp2 +=5;
    leftAxis->Maximum=temp2;
    for (int i=0;i<=leftAxis->Maximum;i++)
    {
      leftAxis->Increment = i;
    }
    
    //Custom Achse Position zu jeder Serie anpassen
    double relPos;
    for (int i = 0;i<=temp;i++)
    {
      relPos = ((i+1)*(100/leftAxis->Maximum))-0.6;
      axTChartTlgDiagram->Series[i]->CustomHorizAxis->RelativePosition = relPos;
    }
  }
  //Untere Achse
  TeeChart::Axis^ bottomAxis = axTChartTlgDiagram->Axes->Bottom;
  bottomAxis->Visible = true;
}

//---------------------------------------------------------
void CAnalyzeTlgForm::initViewComponent(Panel^ parent,double TlgNullTime,double maxTime)
{
  MessageForm=nullptr;
  maxTime=maxTime;
  //---------------
  Dock = DockStyle::Fill;
	TopLevel = false;
	Parent = parent;
  //---------------
  axTChartTlgDiagram->AutoRepaint=true;
  minTime=TlgNullTime;
  maxTime=1;
  //axTChartTlgDiagram->Dock = System::Windows::Forms::DockStyle::Fill;
  axTChartTlgDiagram->Aspect->View3D = true;
  axTChartTlgDiagram->Aspect->View3D = false;
  //--------
  /* checkBox3D->Visible=false;*/
  /* tabDiagramControl->set_SelectedIndex(0);*/
  //Map mit Series
  numOfSeries= gcnew Hashtable();
  //Axis
  //Linke Achse anpassen 
  TeeChart::Axis^ leftAxis = axTChartTlgDiagram->Axes->Left;
  leftAxis->Automatic = false; 
  leftAxis->Maximum = 5; 
  leftAxis->Minimum = 0; 
  leftAxis->TickOnLabelsOnly = true;
  leftAxis->Labels->Font->Shadow->Visible = true;
  leftAxis->Labels->Style = TeeChart::AxisLabelStyle::Text;
  leftAxis->Labels->RoundFirstLabel = false;
  leftAxis->Labels->MultiLine = true;
  for (int i=0;i<=5;i++)
  {
    leftAxis->Increment = i;
  }
  //Untere Achse anpassen
  axTChartTlgDiagram->Axes->Bottom->Automatic=true;
  axTChartTlgDiagram->Axes->Bottom->AutomaticMaximum=true;
  axTChartTlgDiagram->Axes->Bottom->AutomaticMinimum=true;
  axTChartTlgDiagram->Axes->Bottom->Labels->Style = TeeChart::AxisLabelStyle::Value;
  axTChartTlgDiagram->Axes->Bottom->Visible = true;
  //Title
  axTChartTlgDiagram->Axes->Bottom->Title->Right = true;
  axTChartTlgDiagram->Axes->Bottom->Title->Text = "ms.";
  //Commander
  commander1->Chart = this->axTChartTlgDiagram;
  //Legend
  this->axTChartTlgDiagram->Legend->Visible=false;
  /*this->axTChartTlgDiagram->Legend->CheckBoxes=true;
  this->axTChartTlgDiagram->Legend->Gradient->Visible = true;
  this->axTChartTlgDiagram->Legend->Symbol->Width = 10;*/
  
  //Cursor Tool
  Steema::TeeChart::Tools::CursorTool^  cursorTool1;
  cursorTool1 = gcnew Steema::TeeChart::Tools::CursorTool();
  cursorTool1->Pen->Style = System::Drawing::Drawing2D::DashStyle::Dot;
  cursorTool1->FollowMouse = true;
  axTChartTlgDiagram->Tools->Add(cursorTool1);
	axTChartTlgDiagram->Tools[0]->Active=false;
  axTChartTlgDiagram->Zoom->Allow = false;
}