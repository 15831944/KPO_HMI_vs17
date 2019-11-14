#include "stdafx.h"
#include "LogFileConverterForm.h"
#include <windows.h>

#include "CTlgInterfaceWrapper.h"
#include "CXmlAssignmentInterface.h"
#include "CConverterForm.h"

using namespace LogFileConversion;

#undef MessageBox

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	System::Threading::Thread::CurrentThread->ApartmentState = System::Threading::ApartmentState::STA;
	Application::Run(gcnew LogFileConverterForm());
	return 0;
}
//------------------------------------------------
System::Void LogFileConverterForm::OnLoadLogFileForm(System::Object ^  sender, System::EventArgs ^  e)
{
  initView();
}
//----------------------------------------------------------------------------
System::Void LogFileConverterForm::OnButLoadInterClick(System::Object ^  sender, System::EventArgs ^  e)
{
  loadInterface();
}
//----------------------------------------------------------------------------
System::Void LogFileConverterForm::OnButLoadConfig(System::Object ^  sender, System::EventArgs ^  e)
{
	openFileDialog->Filter = "Assignment Interfaces(*.iaf)|*.iaf";
	openFileDialog->Title = "Open Interface Assignment Configuration File";
	if(openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		String^ path = openFileDialog->FileName;
		if(path)
		{
			String^ sourceInter=nullptr;
			String^ destInter=nullptr;
			CInterAssignment^ interAss = nullptr;
      bool sourceInterFlag;
      bool destInterFlag;
			CXmlAssignmentInterface^ xmlAssInterSave = gcnew CXmlAssignmentInterface();
			xmlAssInterSave->setAssignmentCofigFileForRead(path);
			xmlAssInterSave->getAssignmentInterfaces(sourceInter,destInter);
      if((sourceInter != nullptr) && (destInter != nullptr))
      {
        sourceInterFlag = isInterLoaded(sourceInter);
        destInterFlag = isInterLoaded(destInter);
        if((sourceInterFlag) && (destInterFlag))
        {
          interAss=findInterAssignment(sourceInter,destInter);
          interAss = findInterAssignment(sourceInter,destInter);
          xmlAssInterSave->readAssignmentCofigFile(interAss);
					UpInterAssViewFlag = false;
					InterConvertForm->setInterAssignment(interAss);
					comBxSourceInter->SelectedValue = (interAss->getSourceInter()->getInterfaceName());
					comBxDestInter->SelectedValue = (interAss->getDestInter()->getInterfaceName());
					UpInterAssViewFlag = true;
        }
        else
        {
            //Error: Interfaces could'n loaded
        }
      }
      else
      {
          //Error: xml assignment file wrong!!!
      }
		}         
	}
}
//----------------------------------------------------------------------------
System::Void LogFileConverterForm::OnButSaveConfig(System::Object ^  sender, System::EventArgs ^  e)
{
  CInterAssignment^ interAss = InterConvertForm->getInterAssignment();
  if(interAss)
  {
    String^ sourceInter = interAss->getSourceInter()->getInterfaceName();
    String^ destInter = interAss->getDestInter()->getInterfaceName();
    saveFileDialog->Filter = "Assignment Interfaces(*.iaf)|*.iaf";
    saveFileDialog->Title = String::Concat("Save Assignment Interface(",sourceInter," to ",destInter,")");
    if(saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
      CXmlAssignmentInterface^ xmlAssInterSave = gcnew CXmlAssignmentInterface();
      saveFileDialog->FileName;
      xmlAssInterSave->writeAssignmentInterface(saveFileDialog->FileName,interAss);
    }
  }
}
//----------------------------------------------------------------------------
System::Void LogFileConverterForm::OnButClearAssign(System::Object ^  sender, System::EventArgs ^  e)
{
    InterConvertForm->clearAssignment();
}
//----------------------------------------------------------------------------
System::Void LogFileConverterForm::OnButConvertLogFile(System::Object ^  sender, System::EventArgs ^  e)
{
    CConverterForm^ converterForm = gcnew CConverterForm();
    converterForm->setInterfaceAssignment(findInterAssignment(comBxSourceInter->Text,comBxDestInter->Text));
    converterForm->ShowDialog();
}
//----------------------------------------------------------------------------
/*System::Void LogFileConverterForm::OnComBoxAvailInterValueChanged(System::Object ^  sender, System::EventArgs ^  e)
{
    updateSourceInterView(comBxSourceInter->Text);
}*/
//----------------------------------------------------------------------------
System::Void LogFileConverterForm::OnComBxDestInterSelIndexChanged(System::Object ^  sender, System::EventArgs ^  e)
{
	if(UpInterAssViewFlag)
	{
		String^ dest=nullptr;
		if(comBxDestInter->Items->Count > 0)
			dest = comBxDestInter->Text;
		InterConvertForm->setInterAssignment(findInterAssignment(comBxSourceInter->Text,dest));
	}
}
//----------------------------------------------------------------------------
void LogFileConverterForm::initComponent()
{
  InterConvertForm = gcnew CInterConvertForm();
  InterConvertForm->TopLevel = false;
  InterConvertForm->Parent = panInterAssign;
  InterConvertForm->Dock = DockStyle::Fill;
  InterConvertForm->FormBorderStyle = ::FormBorderStyle::None;
  
  InterListe = gcnew ArrayList();
  InterAssignmentListe = gcnew ArrayList();
	UpInterAssViewFlag = true;
}
//-----------------------------------------------------------------------------
void LogFileConverterForm::initView()
{
    InterConvertForm->Show();
    //MessageForm->Show();
    this->Text = "Log - File Converter";
}
//-----------------------------------------------------------------------------
bool LogFileConverterForm::loadInterface()
{
  bool ret=true;
  openFileDialog->Filter="Interface File(*.xml)|*.xml";
  if(openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
  {
    String^ errMess=nullptr;
    String^ fileName=openFileDialog->FileName;
    if(fileName)
    {
     CTlgInterfaceWrapper^ interWr = gcnew CTlgInterfaceWrapper();
     interWr->loadFromFile(fileName,false);
     if((errMess=interWr->getErrorMessage()) == nullptr)
     {
       CInterAssignment^ interAss = nullptr; 
       InterListe->Add(interWr);
       interAss = gcnew CInterAssignment(interWr,nullptr);
       InterAssignmentListe->Add(interAss);
       comBxSourceInter->Items->Add(interWr->getInterfaceName());
       if(comBxSourceInter->Items->Count == 1)
            comBxSourceInter->SelectedIndex=0;
       comBxDestInter->Items->Add(interWr->getInterfaceName());
     }
     else
     {
        System::Windows::Forms::MessageBox::Show(nullptr,errMess,"Error by read",MessageBoxButtons::OK);
     }
    }
  }
  return ret;
}
//-----------------------------------------------------------------------------
void LogFileConverterForm::updateSourceInterView(String^ interName)
{
    //InterConvertForm->updateSourceInterView(findInter(interName));
}
//-----------------------------------------------------------------------------
CTlgInterfaceWrapper^ LogFileConverterForm::findInter(String^ name)
{
  CTlgInterfaceWrapper^ ret = nullptr;
  CTlgInterfaceWrapper^ inter=nullptr;
  int count = InterListe->Count;
  bool flag = false;
  int i=0;
  while((!flag) && (i<count))
  {
    inter = safe_cast<CTlgInterfaceWrapper^>(InterListe[i]);
    if(inter->getInterfaceName()->Equals(name))
    {
      ret=inter;
      flag=true;
    }
    else
    {
      i++;
    }
  }
  return ret;
}
//-----------------------------------------------------------------------------
CInterAssignment^ LogFileConverterForm::findInterAssignment(String^ source,String^ dest)
{
  CInterAssignment^ ret = nullptr;
  int count = InterAssignmentListe->Count;
  bool flag=false;
  int i=0;
  CInterAssignment^ interAss = nullptr;
  if((source != nullptr) && (!source->Equals("")))
  {
    while((!flag) && (i<count))
    {
      interAss = safe_cast<CInterAssignment^>(InterAssignmentListe[i]);
      if(interAss->isMatchAssignment(source,dest))
      {
        ret = interAss;
        flag=true;
      }
      else
      {
        i++;
      }
    }
    if(!flag)
    {
      ret = gcnew CInterAssignment(findInter(source),findInter(dest));
      InterAssignmentListe->Add(ret);
    }
  }
  return ret;
}
//-----------------------------------------------------------------------------
bool LogFileConverterForm::isInterLoaded(String^ name)
{
  bool ret = false;
  int count = InterListe->Count;
  int i = 0;
  CTlgInterfaceWrapper^ interWr = nullptr;
  while((!ret) && (i<count))
  {
    interWr = safe_cast<CTlgInterfaceWrapper^>(InterListe[i]);
	  if(interWr->getInterfaceName()->Equals(name))
    {
      ret = true;
    }
    else
    {
      i++;
    }
  }
    return ret;
}
//-----------------------------------------------------------------------------