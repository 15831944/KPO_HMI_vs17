// Copyright 2006 SMS - Demag AG
//----------------------------------------------------
#include "stdafx.h"
#include "CMessageWriter.h"
//-----------------------------------------------------
CMessageWriter::CMessageWriter(CMessageForm^ txtBx)
{
	this->TextBox = txtBx;
	TimerWriter = nullptr;
}
//-----------------------------------------------------
CMessageWriter::~CMessageWriter()
{
}
//-----------------------------------------------------
void CMessageWriter::startWrite()
{
	//CMessageStack::getMessageStack()->clearMessage();
	//System::Threading::TimerCallback* timeCallBack = new System::Threading::TimerCallback(this,&CMessageWriter::write);
	//TimerWriter = new System::Threading::Timer(timeCallBack,0,0,20000);//500

  System::Threading::ThreadStart^ timeCallBack = gcnew System::Threading::ThreadStart(this,&CMessageWriter::write);
	TimerWriter = gcnew System::Threading::Thread(timeCallBack);//500#
  TimerWriter->Start();
}
//-----------------------------------------------------
void CMessageWriter::endWrite()
{
	//Zuerst wird Thread mit Whileschleife beendet.
  TimerWriter->Abort();
  
  // //Ganze Messages werden herausgeholt
  // //----
  // CMessageStack* messStack = CMessageStack::getMessageStack();
  // std::string messstr("");
  // int messtype;
  // String^ mess=0;
  // 
  // while(messStack->getActMessage(messstr,&messtype))
	//{
	//  mess = CStdConverter::StdStrToString(messstr);
	//	if(messtype == 0)
	//		TextBox->writeLine(mess,CMessageForm::MessTyp::Error);
	//	if(messtype == 1)
	//		TextBox->writeLine(mess,CMessageForm::MessTyp::Warning);
	//	if(messtype == 2)
	//		TextBox->writeLine(mess,CMessageForm::MessTyp::Ok);
	//	if(messtype == 3)
	//		TextBox->writeLine(mess,CMessageForm::MessTyp::Info);

  //   TextBox->Refresh();
  // }
  // ----
  CMessageStack::getMessageStack()->clearMessage();
	TextBox->Refresh();
}
//-----------------------------------------------------
void CMessageWriter::write()
{
  CMessageStack* messStack = CMessageStack::getMessageStack();
  std::string messstr("");
  int messtype;
  String^ mess=nullptr;

  do
  {
    while(messStack->getActMessage(messstr,&messtype))
	  {
	    mess = CStdConverter::StdStrToString(messstr);
		  if(messtype == 0)
			  TextBox->writeLine(mess,CMessageForm::MessTyp::Info);
		  if(messtype == 1)
			  TextBox->writeLine(mess,CMessageForm::MessTyp::Warning);
		  if(messtype == 2)
			  TextBox->writeLine(mess,CMessageForm::MessTyp::Error);

      TextBox->Refresh();
    }
    TimerWriter->Sleep(100);
	}
  while (true);
}
//-----------------------------------------------------