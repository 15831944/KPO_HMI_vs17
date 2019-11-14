#include "StdAfx.h"
#include "CLimValSettingForm.h"

using namespace simulator;

//----------------------------------------------------------------
void CLimValSettingForm::setInterface(CTlgInterfaceWrapper^ inter)
{
	Interface = inter;
    updateViewFromConfFile();
}
//----------------------------------------------------------------
void CLimValSettingForm::updateConfFileFromView()
{
	String^ lim = nullptr;
	CAppSetting^ Sett = CAppSetting::getApp();
	String^ path = Sett->getInterConfigFilePath(Interface->getInterfaceName());
	CXmlInterConfigWriter^ interConfWr = gcnew CXmlInterConfigWriter();
	interConfWr->loadInterConfigFile(path);
	interConfWr->beginUpdate();
	interConfWr->setSectionFocus("Limit");
	if(radButNotTreat->Checked)
	{
		lim = "NotTreat";
	}
	else if(radButError->Checked)
	{
		lim = "AsError";
	}
	else if(radButAsWarning->Checked)
	{
		lim = "AsWarning";
	}
	else
	{
		lim = "SetToMin(Max)";
	}
	interConfWr->setLimitTreatmentTyp(lim);
	interConfWr->endUpdate();
}
//----------------------------------------------------------------
void CLimValSettingForm::updateViewFromConfFile()
{
	bool flag;
	String^ limModi = nullptr;
	CAppSetting^ Sett = CAppSetting::getApp();
	String^ confPath = Sett->getInterConfigFilePath(Interface->getInterfaceName());
	CXmlInterConfigReader^ confFileReader = gcnew CXmlInterConfigReader();
  confFileReader->setInterConfigFile(confPath);
  flag = confFileReader->setSectionFocus("Limit");
	if(flag)
	{
		limModi = confFileReader->getLimitValueTreatment();
		if(limModi->Equals("NotTreat"))
		{
			radButNotTreat->Checked = true;
		}
		else if(limModi->Equals("AsError"))
		{
			radButError->Checked = true;
		}
		else if(limModi->Equals("AsWarning"))
		{
			radButAsWarning->Checked = true;	
		}
		else
		{
			radButMinMax->Checked = true;
		}
	}	
}
//----------------------------------------------------------------
