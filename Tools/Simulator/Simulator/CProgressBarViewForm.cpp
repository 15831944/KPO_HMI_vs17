#include "StdAfx.h"
#include "CProgressBarViewForm.h"
#include "CLogWriterWrapper.h"

using namespace simulator;

void CProgressBarViewForm::setAfterInfoView()
{
  labPreCendDesc->Visible = false;
  labPerCentView->Visible = false;
	//Cancel Button ausblenden
	butCancel->Visible = false;
	label1->Text=" ";
  /* panCancelView->Dock = System::Windows::Forms::DockStyle::;*/
  /*label1->Dock = System::Windows::Forms::DockStyle::Top;*/
  label1->ForeColor = System::Drawing::Color::Black;
  if (butCancel->Enabled)
    label1->Text="New telegrams are accepted and sorted ...";
  else
    label1->Text="New telegrams are removed ...";
  while (true)
  {
    progressBar->Value = 1;
    for (int i=1;i<=95;i++)
    {
      progressBar->Step =1;
      progressBar->PerformStep();
      progressBar->Refresh();
      System::Threading::Thread::Sleep(30);
    }
  }
}
//---------------------------------------------------------------------
void CProgressBarViewForm::Close()
{
  formClosed = true;
  Form::Close();
}
//-------------------------------------------------------------------
bool CProgressBarViewForm::isFormClosed()
{
  return formClosed;
}
//-------------------------------------------------------------------
void CProgressBarViewForm::updateStep(long step)
{
  if (step > 0)
  {
    double temp = 0;
    long temp1 = 0;

    temp = step;
    if ((maximum-minimum) > 0)
    {
      temp /= (maximum-minimum);
      temp *=100;
      if ((temp + restDif) < 1)
        restDif +=temp;
      else
      {
        progressBar->Step = restDif + temp;
        progressBar->PerformStep();
        
        totalStep += restDif + temp;
        if (totalStep <= 100)
          labPerCentView->Text=System::Convert::ToString(totalStep);
        else
          labPerCentView->Text=System::Convert::ToString(100);
        Refresh();
        
        temp1 = long ((restDif + temp)*100);
        temp1 = temp1 % 100;
        restDif /=100;
       }
    }

     /* if (totalStep>80 && butCancel->Visible == true)
      {
        butCancel->Visible = false;
        label1->Text=" ";
      }*/
  }
}  
//-------------------------------------------------------------------
void CProgressBarViewForm::setMinAndMax(long min,__int64 max)
{
  minimum=min;
  maximum=max;
}
//-------------------------------------------------------------------
void CProgressBarViewForm::setSourceLab(String^ source)
{
  labSource->Text=source;
}
//-------------------------------------------------------------------
void CProgressBarViewForm::setCancelButtonVisible(bool mode)
{
  butCancel->Visible = mode;
  /*label1->Text="By Cancel will removed all loaded telegramm";*/
  label1->Visible = mode;
}
 //-------------------------------------------------------------------
void CProgressBarViewForm::setBarViewAbortDelTyp(BarViewAbortDelTyp^ event)
{
  BarViewAbortEvent=event;
}
//-------------------------------------------------------------------
System::Void CProgressBarViewForm::butCancel_Click(System::Object ^  sender, System::EventArgs ^  e)
{
  if (BarViewAbortEvent != nullptr)
  {
		CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,
																													"AbortEvent triggered",
                                                          __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
		
		//Cancel Button deaktivieren
		butCancel->Enabled = false;
		label1->Text=" ";
		BarViewAbortEvent->Invoke();
  }
}