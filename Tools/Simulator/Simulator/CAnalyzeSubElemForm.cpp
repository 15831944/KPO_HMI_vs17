#include "StdAfx.h"
#include "CAnalyzeSubElemForm.h"
#include "CLogWriterWrapper.h"

using namespace simulator;
//--------------------------------------------
void CAnalyzeSubElemForm::setCursorTool(bool mode)
{
  axTChartValueDiagram->Tools[0]->Active=mode;
}
//--------------------------------------------
void CAnalyzeSubElemForm::removeAll()
{
  String^ mess = nullptr;
	if (axTChartValueDiagram->SeriesCount!=0)
  {
    axTChartValueDiagram->Series->RemoveAllSeries();
    mess = "All Telegram - Values removed.";
		CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
		MessageForm->writeLine(mess,CMessageForm::MessTyp::Info);
  }
  else
	{
    mess = "No Telegram - Values in diagram found";
		CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
		MessageForm->writeLine(mess,CMessageForm::MessTyp::Error);
	}
}
//--------------------------------------------
void CAnalyzeSubElemForm::setStartTime(double TlgNullTime)
{
  minTime=TlgNullTime;
}
//---------------------------------------------
void CAnalyzeSubElemForm::set3DMode(bool mode)
{
  axTChartValueDiagram->Aspect->View3D = mode;
}
//---------------------------------------------
bool CAnalyzeSubElemForm::get3DMode(void)
{
  return axTChartValueDiagram->Aspect->View3D;
}
//---------------------------------------------
void CAnalyzeSubElemForm::setPointerOfMessage(CMessageForm^ MessageForm)
{
  this->MessageForm=MessageForm;
}
//------------------------------------------------------------------
String^ CAnalyzeSubElemForm::getSeriesValueNames(int index)
{
  if (index<axTChartValueDiagram->SeriesCount)
    return (axTChartValueDiagram->Series[index]->Title);
  else
    return ("-1");
}
//------------------------------------------------------------------
void CAnalyzeSubElemForm::addToSeries(String^ tlgName,String^ elemName,double tlgTime,double elemValue)
{
	bool neu=true;
	String^ temp=nullptr;
  int lastValue;
	
	temp=temp->Concat(tlgName,elemName);
	
	if (axTChartValueDiagram->SeriesCount==0)
		neu=true;

	for (int i=0;i<axTChartValueDiagram->SeriesCount;i++)
	{
		//Name
    if (temp->Equals(axTChartValueDiagram->Series[i]->Title))
		{
      lastValue=axTChartValueDiagram->Series[i]->LastVisibleIndex;
			axTChartValueDiagram->Series[i]->Add(tlgTime-(minTime),elemValue);    
      neu=false;
			break;
		}
	}
	if (neu)
	{
    //Hilfsvariablen
    Steema::TeeChart::Styles::Series^ ser=nullptr;
    /* tabDiagramControl->set_SelectedIndex(1);*/
		createNewSeries(tlgName,elemName);
		axTChartValueDiagram->Series[axTChartValueDiagram->SeriesCount-1]->Add(0.0,0.0);
    //axTChartValueDiagram->get_aSeries((axTChartValueDiagram->get_SeriesCount())-1)->AddXY(tlgTime-(minTime),0,"",1);
    axTChartValueDiagram->Series[axTChartValueDiagram->SeriesCount-1]->Add(tlgTime-(minTime),elemValue);
  }
}
//------------------------------------------------------------------
void CAnalyzeSubElemForm::createNewSeries(String^ tlgName,String^ elemName)
{
	String^ strtemp=nullptr;
	int temp;
	temp=axTChartValueDiagram->SeriesCount;
  
  Steema::TeeChart::Styles::FastLine^ ser = gcnew Steema::TeeChart::Styles::FastLine();
  axTChartValueDiagram->Series->Add(ser);
	
  ser->Marks->Symbol->Shadow->Visible = true;
  ser->Stairs = true;
  /*ser->Marks->Callout->Brush->Color = System::Drawing::Color::Black;
  ser->Marks->Callout->Distance = 0;
  ser->Marks->Callout->Draw3D = false;
  ser->Marks->Callout->Length = 10;
  ser->Marks->Callout->Style = Steema::TeeChart::Styles::PointerStyles::Rectangle;
  ser->Marks->Shadow->Visible = true;
  ser->Marks->Visible = true;*/

  // //Name fuer Serie erzeugen
  // strtemp=strtemp->Concat(tlgName,elemName);
	////Serie benennen
	//ser->(strtemp);
	//Serie Title benennen
	strtemp=strtemp->Concat(tlgName,elemName);
	ser->Title = strtemp;
}

//---------------------------------------------------------
void CAnalyzeSubElemForm::removeFromSeries(String^ TlgName,String^ elemName)
{
	String^ temp=nullptr;
	temp=temp->Concat(TlgName,elemName);

  for (int i=0;i<axTChartValueDiagram->SeriesCount;i++)
  {
	 if (temp->Equals(axTChartValueDiagram->Series[i]->Title))
	 {
		 String^ mess = System::String::Concat(axTChartValueDiagram->Series[i]->Title," removed.");
		 CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
		 MessageForm->writeLine(mess,CMessageForm::MessTyp::Info);
		 axTChartValueDiagram->Series->RemoveAt(i);
     axTChartValueDiagram->Refresh();
		 break;
	 }
  }
}
 //-----------------------------------------------------------------------------
 void CAnalyzeSubElemForm::initViewComponent(Panel^ parent,double TlgNullTime,double maxTime)
{
  MessageForm=nullptr;
  maxTime=maxTime;
  //---------------
  Dock = DockStyle::Fill;
	TopLevel = false;
	Parent = parent;
  //---------------
  minTime=TlgNullTime;
  maxTime=1;
  //---------------
  axTChartValueDiagram->Zoom->Animated = true;
  axTChartValueDiagram->Zoom->AnimatedSteps = 50;
  //Commander
  commander1->Chart = axTChartValueDiagram;
  ////Legend
  axTChartValueDiagram->Legend->CheckBoxes=true;
  axTChartValueDiagram->Legend->Gradient->Visible = true;
  axTChartValueDiagram->Legend->Symbol->Width = 10;
  //Cursor Tool
  Steema::TeeChart::Tools::CursorTool^  cursorTool1;
  cursorTool1 = gcnew Steema::TeeChart::Tools::CursorTool();
  cursorTool1->Pen->Style = System::Drawing::Drawing2D::DashStyle::Dot;
  cursorTool1->FollowMouse = true;
  axTChartValueDiagram->Tools->Add(cursorTool1);
  axTChartValueDiagram->Tools[0]->Active=false;
  //Linie - Farbe
  axTChartValueDiagram->Aspect->ColorPaletteIndex = 4;
 }