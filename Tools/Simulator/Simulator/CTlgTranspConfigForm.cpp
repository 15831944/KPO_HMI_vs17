#include "StdAfx.h"
#include "CTlgTranspConfigForm.h"

using namespace simulator;
//--------------------------------------------------
void CTlgTranspConfigForm::setInterface(CTlgInterfaceWrapper^ inter)
{
	Interface = inter;
	updateViewFromConfFile();
}
//--------------------------------------------------
void CTlgTranspConfigForm::updateViewFromConfFile()
{
	bool flag;
	String^ Swapping    = nullptr;
  String^ PaddingDir  = nullptr;
  String^ PaddingStr  = nullptr;

	CAppSetting^ Sett = CAppSetting::getApp();
  String^ confPath  = Sett->getInterConfigFilePath(Interface->getInterfaceName());
  
  CXmlInterConfigReader^ confFileReader = gcnew CXmlInterConfigReader();
  confFileReader->setInterConfigFile(confPath);
  flag = confFileReader->setSectionFocus("Transport");

	if(flag)
	{
    confFileReader->getTransportInfo(Swapping, PaddingDir, PaddingStr);

		if(Swapping->Equals("NotSwapping"))
			checkBxSwopping->Checked = false;
		else
			checkBxSwopping->Checked = true;

		comBxPaddDir->SelectedItem = PaddingDir;

  	txtBxPaddStr->Text = PaddingStr;
	}
}
//--------------------------------------------------
void CTlgTranspConfigForm::updateConfFileFromView()
{
	CAppSetting^ Sett = CAppSetting::getApp();
	String^ path = Sett->getInterConfigFilePath(Interface->getInterfaceName());
	CXmlInterConfigWriter^ interConfWr = gcnew CXmlInterConfigWriter();
	interConfWr->loadInterConfigFile(path);
	interConfWr->beginUpdate();
	interConfWr->setSectionFocus("Transport");

	String^ Swapping    = nullptr;
  String^ PaddingDir  = nullptr;
  String^ PaddingStr  = nullptr;
	
	if(checkBxSwopping->Checked)
    Swapping = "Swapping";
	else
    Swapping = "NotSwapping";

  PaddingDir = comBxPaddDir->Text;
  PaddingStr = txtBxPaddStr->Text;

  interConfWr->setTransportInfo(Swapping,PaddingDir,PaddingStr);

	interConfWr->endUpdate();
}
//--------------------------------------------------
