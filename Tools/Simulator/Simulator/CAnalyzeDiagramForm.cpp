#include "StdAfx.h"
#include "CAnalyzeDiagramForm.h"
#include "CMessageForm.h"
using namespace simulator;

void CAnalyzeDiagramForm::setStartTime(double TlgNullTime)
{
  this->minTime=TlgNullTime;
}

//---------------------------------------------
System::Void CAnalyzeDiagramForm::OnClickRemoveAll(System::Object *  sender, System::EventArgs *  e)
{
  if (this->tabDiagramControl->get_SelectedIndex()==0)
  {
    if (this->axTChartDiagram->get_SeriesCount()!=0)
    {
      this->axTChartDiagram->RemoveAllSeries();
      this->numOfSeries->Clear();
      this->MessageForm->writeLine(S"All Telegrams removed.",CMessageForm::MessTyp::Info);
    }
    else
      this->MessageForm->writeLine(S"No Telegrams in diagram found",CMessageForm::MessTyp::Error);
  }
  else
  {
    if (this->axTChartValueDiagram->get_SeriesCount()!=0)
    {
      this->axTChartValueDiagram->RemoveAllSeries();
      this->MessageForm->writeLine(S"All Telegram - Values removed.",CMessageForm::MessTyp::Info);
    }
    else
       this->MessageForm->writeLine(S"No Telegram - Values in diagram found",CMessageForm::MessTyp::Error);
  }
}


//---------------------------------------------
System::Void CAnalyzeDiagramForm::OnClickTabControlChanged(System::Object *  sender, System::EventArgs *  e)
{
  if (this->tabDiagramControl->get_SelectedIndex()==0)
    this->checkBox3D->Visible=false;
  else
     this->checkBox3D->Visible=true;
}
//---------------------------------------------
System::Void CAnalyzeDiagramForm::OnClickCheckBox3D(System::Object *  sender, System::EventArgs *  e)
{
  if (this->checkBox3D->get_Checked())
  {
    /*this->axTChartValueDiagram->Zoom->ZoomRect(0,0,120,5200);*/
    /*this->axTChartDiagram->Aspect->View3D = true;
    this->axTChartDiagram->Repaint();*/
    this->axTChartValueDiagram->Aspect->View3D = true;
    this->axTChartValueDiagram->Repaint();
  }
  else
  {
    /*this->axTChartDiagram->Aspect->View3D = false;
    this->axTChartDiagram->Repaint();*/
    this->axTChartValueDiagram->Aspect->View3D = false;
    this->axTChartValueDiagram->Repaint();
  }
}
//---------------------------------------------
System::Void CAnalyzeDiagramForm::axTChartDiagram_OnSeriesAfterDrawValues (System::Object *  sender, AxInterop::TeeChart::ITChartEvents_OnSeriesAfterDrawValuesEvent *  e)
{
		/*Interop::TeeChart::IAxis* leftAxis = axTChartDiagram->Axis->Left;
		if (leftAxis->Maximum!=this->leftAxisMax)
		{
			int index;
			String* temp=0;
			Interop::TeeChart::ISeries* ser=0;
			
			for (int i=0;i<this->axTChartDiagram->get_SeriesCount();i++)
			{
				temp=this->axTChartDiagram->get_aSeries(i)->get_Name();
				if (!(temp->Substring(0,4)->Equals(S"Value")))
				{
					ser=this->axTChartDiagram->get_aSeries(i);
					index++;
					ser->CalcYSizeValue(leftAxis->Maximum/leftAxisMax);

				}
			}

			ser->RefreshSeries();
			this->axTChartDiagram->Repaint();
		}
		*/
		
		
		
		

		/*if (leftAxis->Maximum!=this->leftAxisMax)
		{
			Interop::TeeChart::ISeries::get_XValues();
			Interop::TeeChart::ISeries::CalcXPos(
			


		}*/
}
//---------------------------------------------
void CAnalyzeDiagramForm::setPointerOfMessage(CMessageForm* MessageForm)
{
  this->MessageForm=MessageForm;
}
//---------------------------------------------
String* CAnalyzeDiagramForm::getSeriesTlgNames(int index)
{
  if (index<this->axTChartDiagram->get_SeriesCount())
    return (axTChartDiagram->get_aSeries(index)->get_Name());
  else
    return (S"-1");
}
//---------------------------------------------
//---------------------------------------------
String* CAnalyzeDiagramForm::getSeriesValueNames(int index)
{
  if (index<this->axTChartValueDiagram->get_SeriesCount())
    return (axTChartValueDiagram->get_aSeries(index)->get_Title());
  else
    return (S"-1");
}
//---------------------------------------------
void CAnalyzeDiagramForm::addToSeries(String* tlgName,String* elemName,String* subElemName,double tlgTime,double elemValue)
{
	bool neu=true;
	String* temp=0;
  int lastValue;
	
	if (subElemName->Equals(S"-1"))
		temp=temp->Concat(tlgName,elemName);
	else
		temp=temp->Concat(tlgName,elemName,subElemName);
	
	if (this->axTChartValueDiagram->get_SeriesCount()==0)
		neu=true;

	for (int i=0;i<this->axTChartValueDiagram->get_SeriesCount();i++)
	{
		if (temp->Equals(this->axTChartValueDiagram->get_aSeries(i)->get_Name()))
		{
      lastValue=this->axTChartValueDiagram->get_aSeries(i)->get_LastValueIndex();
      //this->axTChartValueDiagram->get_aSeries(i)->AddXY(tlgTime-(this->minTime),lastValue,S"",1);
      this->axTChartValueDiagram->get_aSeries(i)->AddXY(tlgTime-(this->minTime),elemValue,S"",10000);
			//this->axTChartValueDiagram->get_aSeries((this->axTChartValueDiagram->get_SeriesCount())-1)->AddXY(tlgTime-(this->minTime),this->maxTime,S"",1);
      //this->axTChartValueDiagram->get_aSeries((this->axTChartValueDiagram->get_SeriesCount())-1)->set_PointValue(tlgTime-(this->minTime),elemValue);
      //this->axTChartValueDiagram->get_aSeries(i)->set_PointLabel(1,subElemName);
      //this->axTChartValueDiagram->Repaint();       
      neu=false;
			break;
		}
	}
	if (neu)
	{
    this->tabDiagramControl->set_SelectedIndex(1);
		this->createNewSeries(tlgName,elemName,subElemName);
		this->axTChartValueDiagram->get_aSeries((this->axTChartValueDiagram->get_SeriesCount())-1)->AddXY(0,0,S"",1);
    //this->axTChartValueDiagram->get_aSeries((this->axTChartValueDiagram->get_SeriesCount())-1)->AddXY(tlgTime-(this->minTime),0,S"",1);
    this->axTChartValueDiagram->get_aSeries((this->axTChartValueDiagram->get_SeriesCount())-1)->AddXY(tlgTime-(this->minTime),elemValue,S"aaaaaaaa",10000);
    
 
	}
}
//---------------------------------------------
void CAnalyzeDiagramForm::addToSeries(String* TlgName,double TlgTime,bool newTlg)
{ 
  //Hilfsvariablen
  Interop::TeeChart::ISeries * ser=0;
  //Interop::TeeChart::ISeries::get_LastValueIndex()
  double zeit;
  int number;
	int
	neu=true;
  //MaxTime bestimmen
  if (this->maxTime < TlgTime-(this->minTime))
    this->maxTime=TlgTime-(this->minTime);
  //Wenn keine Series exis oder keine Series mit gleichen TlgName vorhanden ist.
	for (int i=0;i<this->axTChartDiagram->get_SeriesCount();i++)
		if (TlgName->Equals(this->axTChartDiagram->get_aSeries(i)->get_Name()))
		{
			// Zeichnen Tlg
			 zeit=(TlgTime-(this->minTime));
			//Nummer der Serie wird aus Serie geholt
			number= (*dynamic_cast<__box int*> (numOfSeries->get_Item(TlgName)));
			ser=axTChartDiagram->get_aSeries(i);
			//Zeichnen
			if (TlgTime==0.0)
			{
				ser->AddXY(0,number,S"",1);
				ser->AddXY(this->maxTime,number,S"",1);
			}
			else
			{
				ser->AddXY(0,number,S"",1);
				ser->AddXY(zeit,number,S"",1);
				ser->AddXY(zeit,number+0.4,S"",1);
				ser->AddXY(zeit,number,S"",1);
			}
			neu=false;
			break;
		}
	
	if (neu)
	{
		this->createNewSeries(TlgName);
		//zeichnen
		// Zeichnen Tlg
			 zeit=(TlgTime-(this->minTime));
			//Nummer der Serie wird aus Serie geholt
			number= (*dynamic_cast<__box int*> (numOfSeries->get_Item(TlgName)));
			ser=axTChartDiagram->get_aSeries(this->axTChartDiagram->get_SeriesCount()-1);
			//Zeichnen
			if (TlgTime==0.0)
			{
				ser->AddXY(0,number,S"",1);
				ser->AddXY(this->maxTime,number,S"",1);
			}
			else
			{
				ser->AddXY(0,number,S"",1);
				ser->AddXY(zeit,number,S"",1);
				ser->AddXY(zeit,number+0.4,S"",1);
				ser->AddXY(zeit,number,S"",1);
				
			}
      this->tabDiagramControl->set_SelectedIndex(0);
	}
	//Linke Achse Maximum merken
	Interop::TeeChart::IAxis* leftAxis = axTChartDiagram->Axis->Left;
	this->leftAxisMax=leftAxis->Maximum;
  //restliche Series Linie erweitern
  for (int i=0;i<this->axTChartDiagram->get_SeriesCount();i++)
  {
    ser=axTChartDiagram->get_aSeries(i);
    ser->AddXY(this->maxTime,i+1,S"",1);
    ser=0;
  }
	
	
	
	
	//if (this->axTChartDiagram->get_SeriesCount()==0 || !this->numOfSeries->ContainsKey(TlgName) )
 //   this->createNewSeries(TlgName);

  ////Neue angekommene Tlg aktualisieren
  //{
  //  zeit=(TlgTime-(this->minTime));
  //  //Nummer der Serie wird aus Serie geholt
  //  number= (*dynamic_cast<__box int*> (numOfSeries->get_Item(TlgName)));
  //  ser=axTChartDiagram->get_aSeries(number-1);
  //  //Zeichnen
  //  if (TlgTime==0.0)
  //  {
  //    ser->AddXY(0,number,S"",1);
  //    ser->AddXY(this->maxTime,number,S"",1);
  //  }
  //  else
  //  {
  //    ser->AddXY(0,number,S"",1);
  //    ser->AddXY(zeit,number,S"",1);
  //    ser->AddXY(zeit,number+0.4,S"",1);
  //    ser->AddXY(zeit,number,S"",1);
  //  }
  //  ser=0;
  //}
  
 }
//---------------------------------------------------------
void CAnalyzeDiagramForm::createNewSeries(String* tlgName,String* elemName,String* subElemName)
{
	String* strtemp=0;
	int temp;
	temp=this->axTChartValueDiagram->get_SeriesCount();
  this->axTChartValueDiagram->AddSeries(Interop::TeeChart::ESeriesClass::scFastLine);
	Interop::TeeChart::ISeries* ser = axTChartValueDiagram->Series(temp);
  //ser->set_PointColor(35,35);
  //Name fuer Serie erzeugen
	if (subElemName->Equals(S"-1"))
	{
		strtemp=strtemp->Concat(tlgName,elemName);
		//Serie benennen
		ser->set_Name(strtemp);
		//Serie Title benennen
		strtemp=strtemp->Concat(tlgName,S" - ",elemName);
		ser->set_Title(strtemp);
	}
	else
	{
		strtemp=strtemp->Concat(tlgName,elemName,subElemName);
		//Serie benennen
		ser->set_Name(strtemp);
		//Serie Title benennen
		strtemp=strtemp->Concat(tlgName,S" - ",elemName);
		strtemp->Concat(S" - ",subElemName);
		ser->set_Title(strtemp);
	}
}
//---------------------------------------------------------
 void CAnalyzeDiagramForm::createNewSeries(String* TlgName)
 {
    int temp=this->axTChartDiagram->get_SeriesCount();
    this->axTChartDiagram->AddSeries(Interop::TeeChart::ESeriesClass::scFastLine);
    Interop::TeeChart::ISeries* ser = axTChartDiagram->Series(temp);
    ser->set_Name( TlgName);
    ser->set_Title(TlgName);
   

    this->numOfSeries->Add(TlgName,__box (this->axTChartDiagram->get_SeriesCount()));
    
    //Linke Achse anpassen, falls erforderlich
    Interop::TeeChart::IAxis* leftAxis = axTChartDiagram->Axis->Left;
    if (this->axTChartDiagram->get_SeriesCount()>=leftAxis->Maximum)
    {
      int temp =(int)leftAxis->Maximum;
      temp +=5;
      leftAxis->Maximum=temp;
      for (int i=0;i<=leftAxis->Maximum;i++)
        leftAxis->Increment = i;
    }
}
//---------------------------------------------------------
 void CAnalyzeDiagramForm::removeFromSeries(String* TlgName,String* elemName,String* subElemName)
 {
	 String* temp=0;
	 if (subElemName->Equals(S"-1"))
		temp=temp->Concat(TlgName,elemName);
	 else
		temp=temp->Concat(TlgName,elemName,subElemName);
	 for (int i=0;i<this->axTChartValueDiagram->get_SeriesCount();i++)
	 {
		 if (temp->Equals(this->axTChartValueDiagram->get_aSeries(i)->get_Name()))
		 {
			 this->MessageForm->writeLine(System::String::Concat(this->axTChartValueDiagram->get_aSeries(i)->get_Title(),S" removed."),
																		CMessageForm::MessTyp::Info);
			 this->axTChartValueDiagram->RemoveSeries(i);
			 break;
		 }
	 }
 }
//---------------------------------------------------------
ArrayList* CAnalyzeDiagramForm::removeFromSeries(String* TlgName)
{
  ArrayList *tempListe=new ArrayList(); 
  //Wenn Serie mit TlgName exis.
  if (this->numOfSeries->ContainsKey(TlgName))
  {
    String* tempString=0;
    int tempInt=0;
    int temp=0;
    
    //Nummer der Serie wird aus NummerListe geholt
    int number= (*dynamic_cast<__box int*> (this->numOfSeries->get_Item(TlgName)));
    //Serie wirs aus axTChartDiagram entfernt 
    this->axTChartDiagram->RemoveSeries(number-1);
	  //Serie aus numOfSeries entfernen
    this->numOfSeries->Remove(TlgName);
    //Restrliche Series in die Liste speichern
    for (int i=0;i<this->axTChartDiagram->get_SeriesCount();i++)
    {
      tempListe->Add(this->axTChartDiagram->get_aSeries(i)->get_Name());
      this->numOfSeries->Remove(this->axTChartDiagram->get_aSeries(i)->get_Name());
    }
    this->axTChartDiagram->RemoveAllSeries();
    this->MessageForm->writeLine(System::String::Concat(TlgName,S" removed."),CMessageForm::MessTyp::Info);
    //Linke Achse anpassen
    Interop::TeeChart::IAxis* leftAxis = axTChartDiagram->Axis->Left;
    temp=(int)leftAxis->Maximum;
    if ((temp-(this->axTChartDiagram->get_SeriesCount()))>5)
    {
      temp =(int)leftAxis->Maximum;
      temp -=5;
      leftAxis->Maximum=temp;
      for (int i=0;i<=leftAxis->Maximum;i++)
        leftAxis->Increment = i;
    }
  }
  else
    this->MessageForm->writeLine(System::String::Concat(TlgName,S" in diagram not found."),CMessageForm::MessTyp::Error);
  return tempListe;
}
//---------------------------------------------------------
void CAnalyzeDiagramForm::initViewComponent(Panel* parent,double TlgNullTime,double maxTime)
{
  this->MessageForm=0;
  this->maxTime=maxTime;
  //---------------
  this->Dock = DockStyle::Fill;
	this->TopLevel = false;
	this->Parent = parent;
  //---------------
  this->axTChartDiagram->AutoRepaint=true;
  this->minTime=TlgNullTime;
  this->maxTime=1;
  this->axTChartDiagram->Dock = System::Windows::Forms::DockStyle::Fill;
  this->axTChartDiagram->Aspect->View3D = true;
  this->axTChartValueDiagram->Dock = System::Windows::Forms::DockStyle::Fill;
  this->axTChartDiagram->Aspect->View3D = false;
  //--------
   this->checkBox3D->Visible=false;
   this->tabDiagramControl->set_SelectedIndex(0);
  //Map mit Series
  numOfSeries= new Hashtable();
  //Axis
  //axTChartDiagram->Axis->Visible = true; 
  Interop::TeeChart::IAxis* leftAxis = axTChartDiagram->Axis->Left;
  leftAxis->Automatic = false; 
  leftAxis->Maximum = 5; 
  leftAxis->Minimum = 0; 
  //Linke Achse anpassen 
  for (int i=0;i<=5;i++)
    leftAxis->Increment = i;

  //zoom
  /*Rectangle r = new Rectangle(x,y,width,height); */
  this->axTChartValueDiagram->Zoom->Animated = true;
  this->axTChartValueDiagram->Zoom->AnimatedSteps = 50;
 /* this->axTChartValueDiagram->Zoom->ZoomRect(100,100,5000,5000);*/
  /*tChart1.Zoom.Animated = true; 
  tChart1.Zoom.AnimatedSteps = 100; 
  tChart1.Zoom.ZoomRect(r); */
  //Scroll
  //tChart1.Axes.Bottom.Scroll(3, false);
  //this->axTChartValueDiagram->Axis->Left->Scroll (3000,true); 
  
}

