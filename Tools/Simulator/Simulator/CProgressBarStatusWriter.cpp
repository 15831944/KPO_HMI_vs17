// Copyright 2007 SMS - Demag AG
//----------------------------------------------------
#include "stdafx.h"
#include "CProgressBarStatusWriter.h"

//-----------------------------------------------------
CProgressBarStatusWriter::CProgressBarStatusWriter (CProgressBarViewForm^ view)
{
	TimerWriter = nullptr;
  ProgressBarView = view;
  InfoByFileLogRead = CProgressInfoByFileLogRead::getProgressInfoByFileLogRead();
}
//-----------------------------------------------------
CProgressBarStatusWriter::~CProgressBarStatusWriter()
{
  
}
//-----------------------------------------------------
void CProgressBarStatusWriter::startWrite()
{
  System::Threading::ThreadStart^ timeCallBack = gcnew System::Threading::ThreadStart(this,&CProgressBarStatusWriter::write);
  TimerWriter = gcnew System::Threading::Thread(timeCallBack);
  TimerWriter->Start();
}
//-----------------------------------------------------
void CProgressBarStatusWriter::endWrite()
{
	TimerWriter->Abort();
  InfoByFileLogRead->resetData();
	//write(0);
}
//-----------------------------------------------------
void CProgressBarStatusWriter::write()
{
  long temp = 0;
  do
  {
    if (System::Threading::Monitor::TryEnter(ProgressBarView))
    {
      temp = InfoByFileLogRead->getData();
      if (!ProgressBarView->isFormClosed())
        ProgressBarView->updateStep(temp);
      System::Threading::Monitor::Exit(ProgressBarView);
    }
    TimerWriter->Sleep(200);
  }
  while (!InfoByFileLogRead->getStatusReady());
  InfoByFileLogRead->setStatusReady(false);
  ProgressBarView->setAfterInfoView();
}
