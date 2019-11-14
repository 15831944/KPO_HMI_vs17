#include "StdAfx.h"
#include "CLogFileConfigForm.h"

using namespace simulator;

//---------------------------------------------------------
void CLogFileConfigForm::setInterface(CTlgInterfaceWrapper^ inter)
{
  Interface = inter;
  updateViewFromConfFile();
}
//---------------------------------------------------------
void CLogFileConfigForm::updateViewFromConfFile()
{
  bool flag;
  String^ lim = nullptr;
  String^ date = nullptr;
  String^ time = nullptr;
  CAppSetting^ Sett = CAppSetting::getApp();
  String^ confPath = Sett->getInterConfigFilePath(Interface->getInterfaceName());
  CXmlInterConfigReader^ confFileReader = gcnew CXmlInterConfigReader();
  confFileReader->setInterConfigFile(confPath);
  flag = confFileReader->setSectionFocus("LogFile");
  if(flag)
  {
    txtBxLogFileSep->Text = confFileReader->getLogFileSeparator();
    date = confFileReader->getLogFileDateFormat();
    time = confFileReader->getLogFileTimeFormat();
    updateViewDateFormat(date);
    updateViewTimeFormat(time);
  }
}
//---------------------------------------------------------
void CLogFileConfigForm::updateViewDateFormat(String^ date)
{
  //String^ yearTyp = 0;
  //String^ yearId = "Y";
  //String^ monId = "M";
  //String^ dayId = "D";
  //String^ del = 0;
  //String^ actStr = 0;
  //ComboBox* comBx = comBxDateItem1;
  //TextBox* txtBx = txtBxDateDel1;
  //int count,i;

	String^ sym=nullptr;
	int pos;
	sym=date->Substring(0,1);
	pos=date->LastIndexOf(sym);
	comBxDateItem1->SelectedItem = (date->Substring(0,pos+1));
	date=date->Substring(pos+1,date->Length-pos-1);
	txtBxDateDel1->Text=date->Substring(0,1);
	date=date->Substring(1,date->Length-1);
	
	sym=date->Substring(0,1);
	pos=date->LastIndexOf(sym);
	comBxDateItem2->SelectedItem = (date->Substring(0,pos+1));
	date=date->Substring(pos+1,date->Length-pos-1);
	txtBxDateDel2->Text=date->Substring(0,1);
	date=date->Substring(1,date->Length-1);
	comBxDateItem3->Text=date;

  /*count = date->Length;
	yearTyp = date->Substring(count-1,1);
    for(i=0;i<count-1;i++)
    {	
        actStr = date->Substring(i,1);
        if(actStr->Equals(yearId))
        {
			if(del)
			{
				txtBx->Text = del;
				txtBx = txtBxDateDel2;
				del=0;
			}
            if(yearTyp->Equals(""))
                comBx->SelectedItem = ("YY");
            else
                comBx->SelectedItem = ("YYYY");
            comBx=getNextComBoxDate(comBx);
        }
        else if(actStr->Equals(monId))
        {
			if(del)
			{
				txtBx->Text = del;
				txtBx = txtBxDateDel2;
				del=0;
			}
            comBx->SelectedItem = ("MM");
            comBx=getNextComBoxDate(comBx);
        }
        else if(actStr->Equals(dayId))
        {
			if(del)
			{
				txtBx->Text = del;
				txtBx = txtBxDateDel2;
				del=0;
			}
            comBx->SelectedItem = ("DD");
            comBx=getNextComBoxDate(comBx);
        }
        else
        {
			del = System::String::Concat(del,actStr);
        }
    }*/
}
//---------------------------------------------------------
void CLogFileConfigForm::updateViewTimeFormat(String^ time)
{
	String^ sym=nullptr;
	int pos;

	sym=time->Substring(0,1);
	pos=time->LastIndexOf(sym);
	comBxTimeItem1->SelectedItem = (time->Substring(0,pos+1));
	time=time->Substring(pos+1,time->Length-pos-1);
	txtBxTimeDel1->Text=time->Substring(0,1);
	time=time->Substring(1,time->Length-1);

	sym=time->Substring(0,1);
	pos=time->LastIndexOf(sym);
	comBxTimeItem2->SelectedItem = (time->Substring(0,pos+1));
	time=time->Substring(pos+1,time->Length-pos-1);
	txtBxTimeDel2->Text=time->Substring(0,1);
	time=time->Substring(1,time->Length-1);

	sym=time->Substring(0,1);
	pos=time->LastIndexOf(sym);
	comBxTimeItem3->SelectedItem = (time->Substring(0,pos+1));
	time=time->Substring(pos+1,time->Length-pos-1);
	txtBxTimeDel3->Text=time->Substring(0,1);
	time=time->Substring(1,time->Length-1);

	comBxTimeItem4->SelectedItem = (time->Substring(0,pos+1));
	/*String^ hourId = "H";
	String^ minId = "M";
	String^ secId = "";
	String^ msecId = "m";
	int msecCount = 0;
	String^ del = 0;
	String^ actStr = 0;
	String^ mmm = 0;
	ComboBox* comBx = comBxTimeItem1;
	TextBox* txtBx = txtBxTimeDel1;
	int count,i;

    count = time->Length;
	msecCount = System::Convert::ToInt32(time->Substring(count-1,1));
	for(i=0;i<msecCount;i++)
		mmm = String::Concat(mmm,"m");
	for(i=0;i<count-1;i++)
	{
		actStr = time->Substring(i,1);
		if(actStr->Equals(hourId))
		{
			if(del)
			{
				txtBx->Text = del;
				txtBx = getNextTextBoxTime(txtBx);
				del=0;
			}
			comBx->SelectedItem = ("HH");
			comBx=getNextComBoxTime(comBx);
		}
		else if(actStr->Equals(minId))
		{
			if(del)
			{
				txtBx->Text = del;
				txtBx = getNextTextBoxTime(txtBx);
				del=0;
			}
			comBx->SelectedItem = ("MM");
			comBx=getNextComBoxTime(comBx);
		}
		else if(actStr->Equals(secId))
		{
			if(del)
			{
				txtBx->Text = del;
				txtBx = getNextTextBoxTime(txtBx);
				del=0;
			}
			comBx->SelectedItem = ("S");
			comBx=getNextComBoxTime(comBx);
		}
		else if(actStr->Equals(msecId))
		{
			if(del)
			{
				txtBx->Text = del;
				txtBx = getNextTextBoxTime(txtBx);
				del=0;
			}
			comBx->SelectedItem = (mmm);
			comBx=getNextComBoxTime(comBx);
		}
		else
		{
			del = System::String::Concat(actStr);
		}
	}*/
}
//---------------------------------------------------------
ComboBox^ CLogFileConfigForm::getNextComBoxDate(ComboBox^ comBx)
{
	ComboBox^ ret = nullptr;
  String^ name = comBx->Name;
  if(name->Equals("comBxDateItem1"))
  {
    ret = comBxDateItem2;
  }
  else if(name->Equals("comBxDateItem2"))
  {
    ret = comBxDateItem3;
  }
	return ret;
}
//---------------------------------------------------------
ComboBox^ CLogFileConfigForm::getNextComBoxTime(ComboBox^ comBx)
{
	ComboBox^ ret = nullptr;
	String^ name = comBx->Name;
	if(name->Equals("comBxTimeItem1"))
	{
		ret = comBxTimeItem2;
	}
	else if(name->Equals("comBxTimeItem2"))
	{
		ret = comBxTimeItem3;
	}
	else if(name->Equals("comBxTimeItem3"))
	{
		ret = comBxTimeItem4;
	}

	return ret;
}
//---------------------------------------------------------
TextBox^ CLogFileConfigForm::getNextTextBoxTime(TextBox^ txtBx)
{
	TextBox^ ret = nullptr;
	String^ name = txtBx->Name;
	if(name->Equals("txtBxTimeDel1"))
	{
		ret = txtBxTimeDel2;
	}
	else if(name->Equals("txtBxTimeDel2"))
	{
		ret = txtBxTimeDel3;
	}
	return ret;
}
//---------------------------------------------------------
void CLogFileConfigForm::updateConfFileFromView()
{
	String^ lim = nullptr;
	String^ date = nullptr;
	String^ time = nullptr;
	CAppSetting^ Sett = CAppSetting::getApp();
	String^ path = Sett->getInterConfigFilePath(Interface->getInterfaceName());
	CXmlInterConfigWriter^ interConfWr = gcnew CXmlInterConfigWriter();
	interConfWr->loadInterConfigFile(path);
	interConfWr->beginUpdate();
	interConfWr->setSectionFocus("LogFile");
	interConfWr->setLogFileSeparator(txtBxLogFileSep->Text);

	//if(checkBxNotTreat->Checked)
	//{
		//lim = "NotTreat";
	//}
	//else if(checkBxError->Checked)
	//{
		//lim = "Error";
	//} 
	//else if(checkBxWarning->Checked)
	//{
		//lim = "Warning";
	//}
	//else if(checkBxToLim->Checked)
	//{
		//lim = "SetToLimit";
	//}
	//if(lim)
		//interConfWr->setLimitTreatmentTyp(lim);

	date=getDateAsConfFileItem();
	time=getTimeAsConfFileItem();
	interConfWr->setLogFileDate(date);
	interConfWr->setLogFileTime(time);

	interConfWr->endUpdate();
}
//---------------------------------------------------------
String^ CLogFileConfigForm::getDateAsConfFileItem()
{
	String^ ret = nullptr;
	String^ text = nullptr;
	int max = 0;
	ret=String::Concat(ret,comBxDateItem1->Text,txtBxDateDel1->Text);
	ret=String::Concat(ret,comBxDateItem2->Text,txtBxDateDel2->Text);
	ret=String::Concat(ret,comBxDateItem3->Text);
	/*text = comBxDateItem1->Text;
	if(max < text->Length)
		max = text->Length;
	ret = String::Concat(ret,text->Substring(0,1),txtBxDateDel1->Text);
	text = comBxDateItem2->Text;
	if(max < text->Length)
		max = text->Length;
	ret = String::Concat(ret,text->Substring(0,1),txtBxDateDel2->Text);
	text = comBxDateItem3->Text;
	if(max < text->Length)
		max = text->Length;
	ret = String::Concat(ret,text->Substring(0,1));
	if(max > 2)
		ret = String::Concat(ret,"L");
	else
		ret = String::Concat(ret,"");*/
	return ret;
}
//---------------------------------------------------------
String^ CLogFileConfigForm::getTimeAsConfFileItem()
{
	String^ ret = nullptr;
	String^ text = nullptr;
	int count = 0;

	ret=String::Concat(ret,comBxTimeItem1->Text,txtBxTimeDel1->Text);
	ret=String::Concat(ret,comBxTimeItem2->Text,txtBxTimeDel2->Text);
	ret=String::Concat(ret,comBxTimeItem3->Text,txtBxTimeDel3->Text);
	ret=String::Concat(ret,comBxTimeItem4->Text);
	/*text = comBxTimeItem1->Text;
	if(text->IndexOf("m") != -1)
		count = text->Length / 2;
	ret = String::Concat(ret,text->Substring(0,1),txtBxTimeDel1->Text);
	text = comBxTimeItem2->Text;
	if(text->IndexOf("m") != -1)
		count = text->Length / 2;
	ret = String::Concat(ret,text->Substring(0,1),txtBxTimeDel2->Text);
	text = comBxTimeItem3->Text;
	if(text->IndexOf("m") != -1)
		count = text->Length / 2;
	ret = String::Concat(ret,text->Substring(0,1),txtBxTimeDel3->Text);
	text = comBxTimeItem4->Text;
	if(text->IndexOf("m") != -1)
		count = text->Length / 2;
	ret = String::Concat(ret,text->Substring(0,1),System::Convert::ToString(count));*/

	return ret;
}
//---------------------------------------------------------
//---------------------------------------------------------