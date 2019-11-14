// Copyright 2006 SMS - Demag AG
//----------------------------------------------------------------
#include "stdafx.h"
//#include "CAppSetting.h"
#include "CInterConfigWrapper.h"
//----------------------------------------------------------------
CInterConfigWrapper::CInterConfigWrapper()
{
}
//----------------------------------------------------------------
CInterConfigWrapper::~CInterConfigWrapper()
{
}
//----------------------------------------------------------------
void CInterConfigWrapper::readInterConfigurationFile(String^ interName,String^ filePath)
{
  std::string interNameStr("");
  CInterConfig* interConf = nullptr;
  CXmlInterConfigReader^ XmlConfReader = nullptr;
  CStdConverter::StringToStdStr(interName,interNameStr);
	XmlConfReader = gcnew CXmlInterConfigReader();
  
  XmlConfReader->setInterConfigFile(filePath);
  interConf = CInterConfig::getInterConfig(interNameStr);
   
  readTelIdConfiguration(interConf,XmlConfReader);
  readTransportConfiguration(interConf,XmlConfReader);
  readLimitTreatConfiguration(interConf,XmlConfReader);
  readLogFileConfiguration(interConf,XmlConfReader);

  CInterUseCase^ interUseCase = CInterUseCase::getInterUseCase(interName);
  readUseCaseConfiguration(interUseCase,XmlConfReader);

  CInterListenElemView^ interListElem = CInterListenElemView::getInterListenElemView(interName);
  readListenElemConfiguration(interListElem,XmlConfReader);
}
//----------------------------------------------------------------
void CInterConfigWrapper::readTelIdConfiguration(CInterConfig* inter,CXmlInterConfigReader^ xmlReader)
{
  bool flag;
  String^ tel = nullptr;
  String^ id = nullptr;
  String^ telIdName = nullptr;
  String^ elemIdName = nullptr;
  String^ typId = nullptr;
  String^ ElemLenName = nullptr;
	String^ TreatLen=nullptr;
  std::string telIdNameStr("");
  std::string elemIdNameStr("");
  std::string typIdStr("");
  std::string ElemLenNameStr("");
  std::string telStr("");
  std::string idStr("");

  // lese header telegram
  //CAppSetting^ Sett = CAppSetting::getApp();
  //telIdName = Sett->getHeaderTlg();

  flag = xmlReader->setSectionFocus("TelegramId");
  if(flag)
  {
    xmlReader->getTelIdInfo(telIdName,elemIdName,typId,ElemLenName,TreatLen);
	  if(TreatLen->Equals("Total Length"))
	  {
		  inter->setTreatLenIdMode(CInterConfig::Total);
	  }
	  else
	  {
		  if(TreatLen->Equals("Body Length"))
		  {
			  inter->setTreatLenIdMode(CInterConfig::Body);
		  }
		  else
		  {
			  inter->setTreatLenIdMode(CInterConfig::User);
		  }
    }
    CStdConverter::StringToStdStr(telIdName,telIdNameStr);
    CStdConverter::StringToStdStr(elemIdName,elemIdNameStr);
    CStdConverter::StringToStdStr(typId,typIdStr);
    CStdConverter::StringToStdStr(ElemLenName,ElemLenNameStr);
    inter->setTelIdInfo(telIdNameStr,elemIdNameStr,typIdStr,ElemLenNameStr);
	  inter->clearTelId();
    while(xmlReader->getNextTlgId(tel,id))
    {
      CStdConverter::StringToStdStr(tel,telStr);
      CStdConverter::StringToStdStr(id,idStr);
      inter->addTelId(telStr,idStr);
    }
  }
}
//----------------------------------------------------------------
bool CInterConfigWrapper::isIdElementDefined(String^ interName)
{
  return (!(getTlgIdName(interName)->Equals("")) && !(getElemId(interName)->Equals("")));
}
//----------------------------------------------------------------
String^ CInterConfigWrapper::getTlgIdName(String^ interName)
{
  String^ ret = nullptr;
  CInterConfig* interConf = nullptr;
  std::string interNameStr("");
  std::string idStr("");
  CStdConverter::StringToStdStr(interName,interNameStr);
  interConf = CInterConfig::getInterConfig(interNameStr);
  idStr = interConf->getTelIdName();
  ret = CStdConverter::StdStrToString(idStr);
  return ret;
}
//----------------------------------------------------------------
String^ CInterConfigWrapper::getTlgId(String^ interName,String^ telName)
{
  String^ ret = nullptr;
  CInterConfig* interConf = nullptr;
  std::string interNameStr("");
  std::string telNameStr("");
  std::string val("");
  CStdConverter::StringToStdStr(interName,interNameStr);
  CStdConverter::StringToStdStr(telName,telNameStr);
  interConf = CInterConfig::getInterConfig(interNameStr);
  interConf->getTelId(telNameStr,val);
  ret = CStdConverter::StdStrToString(val);
  return ret;
}
//----------------------------------------------------------------
String^ CInterConfigWrapper::getTlgName(String^ interName,String^ id)
{
	String^ ret = nullptr;
  CInterConfig* interConf = nullptr;
	std::string interNameStr("");
	std::string telIdStr("");
	std::string val("");
	CStdConverter::StringToStdStr(interName,interNameStr);
	CStdConverter::StringToStdStr(id,telIdStr);
	interConf = CInterConfig::getInterConfig(interNameStr);
	interConf->getTelName(telIdStr,val);
	ret = CStdConverter::StdStrToString(val);
	return ret;
}
//----------------------------------------------------------------
String^ CInterConfigWrapper::getElemId(String^ interName)
{
  String^ ret = nullptr;
  CInterConfig* interConf = nullptr;
  std::string interNameStr("");
  std::string val("");
  CStdConverter::StringToStdStr(interName,interNameStr);
  interConf = CInterConfig::getInterConfig(interNameStr);
  val = interConf->getElemIdName();
  ret = CStdConverter::StdStrToString(val);
  return ret;
}
//-----------------------------------------------------------------
String^ CInterConfigWrapper::getElemLenId(String^ interName)
{
  String^ ret = nullptr;
  CInterConfig* interConf = nullptr;
  std::string interNameStr("");
  std::string val("");
  CStdConverter::StringToStdStr(interName,interNameStr);
  interConf = CInterConfig::getInterConfig(interNameStr);
  val = interConf->getElemLenName();
  ret = CStdConverter::StdStrToString(val);
  return ret;
}
//----------------------------------------------------------------
void CInterConfigWrapper::readTransportConfiguration(CInterConfig* inter,CXmlInterConfigReader^ xmlReader)
{
	bool flag;
	String^ Swapping    = nullptr;
  String^ PaddingDir  = nullptr;
  String^ PaddingStr  = nullptr;
	std::string padd("");
	
  flag = xmlReader->setSectionFocus("Transport");

	if(flag)
	{
    xmlReader->getTransportInfo(Swapping, PaddingDir, PaddingStr);

		if(Swapping->Equals("NotSwapping"))
			inter->setSwapping(false);
		else
			inter->setSwapping(true);

		if(PaddingDir->Equals("Left"))
			inter->setPaddingDirection(CInterConfig::Left);
		else
			inter->setPaddingDirection(CInterConfig::Right);

		CStdConverter::StringToStdStr(PaddingStr,padd);
		inter->setPaddingString(padd);
	}
}
//----------------------------------------------------------------
void CInterConfigWrapper::readLimitTreatConfiguration(CInterConfig* inter,CXmlInterConfigReader^ xmlReader)
{
	bool flag;
	String^ val=nullptr;
	flag = xmlReader->setSectionFocus("Limit");
	if(flag)
	{
		val=xmlReader->getLimitValueTreatment();
		if(val->Equals("AsError"))
		{
			inter->setLimitTreatment(CInterConfig::Error);
		}
		else
		{
			if(val->Equals("AsWarning"))
			{
				inter->setLimitTreatment(CInterConfig::Warning);
			}
			else
			{
				if(val->Equals("SetToMin(Max)"))
				{
					inter->setLimitTreatment(CInterConfig::SetToMinMax);
				}
				else
				{
					inter->setLimitTreatment(CInterConfig::Accept);
				}
			}
		}
		//inter->setLimitTreatment(
	}
}
//----------------------------------------------------------------
void CInterConfigWrapper::readLogFileConfiguration(CInterConfig* inter,CXmlInterConfigReader^ xmlReader)
{
	bool flag;
	String^ del=nullptr;
	std::string delStr("");
	String^ date=nullptr;
	String^ time=nullptr;
	std::string dateStr("");
	std::string timeStr("");
	flag = xmlReader->setSectionFocus("LogFile");
	if(flag)
	{
		del=xmlReader->getLogFileSeparator();
		CStdConverter::StringToStdStr(del,delStr);
		inter->setLogDelimeter(delStr[0]);
		date=xmlReader->getLogFileDateFormat();
		time=xmlReader->getLogFileTimeFormat();
		CStdConverter::StringToStdStr(date,dateStr);
		CStdConverter::StringToStdStr(time,timeStr);
		inter->setTime(dateStr,timeStr);
	}
}
//----------------------------------------------------------------
bool CInterConfigWrapper::isSwapping(String^ interName)
{
	CInterConfig* interConf = nullptr;
  std::string interNameStr("");
  CStdConverter::StringToStdStr(interName,interNameStr);
  interConf = CInterConfig::getInterConfig(interNameStr);
	return interConf->getSwapping();
}
//----------------------------------------------------------------
void CInterConfigWrapper::readUseCaseConfiguration(CInterUseCase^ interUseCase,CXmlInterConfigReader^ xmlReader)
{
	bool flag;
	//int count;
	String^ delimStr = ",";
	array <Char>^ delimiter = delimStr->ToCharArray();
	String^ useCaseName=nullptr;
	String^ useCaseDescr=nullptr;
	String^ useCaseItems=nullptr;
	array <String^>^ itemsArray;

	interUseCase->clearUseCaseInfo();

	flag = xmlReader->setSectionFocus("UseCase");
	if(flag)
	{
		while(xmlReader->getNextUseCase(useCaseName,useCaseDescr,useCaseItems))
		{
			itemsArray=useCaseItems->Split(delimiter);
			interUseCase->addUseCase(useCaseName,useCaseDescr,itemsArray);
		}
	}
}
//----------------------------------------------------------------
void CInterConfigWrapper::readListenElemConfiguration(CInterListenElemView^ interListenElem,CXmlInterConfigReader^ xmlReader)
{
	bool flag;
	array <String^>^ it;
	String^ elemName=nullptr;
	String^ tlgName=nullptr;
	String^ elemCount=nullptr;
	flag = xmlReader->setSectionFocus("ArrayView");
	if(flag)
	{
		while((it=xmlReader->getNextArrayElemInfo(elemName,tlgName,elemCount)) != nullptr)
		{
			interListenElem->addListenElem(elemName,tlgName,System::Convert::ToInt32(elemCount),it);
		}
	}
}
//----------------------------------------------------------------
int CInterConfigWrapper::getLenIdTreatModus(String^ interName)
{
	int ret = 0;
	CInterConfig::LenTlgIdTyp treat;
	CInterConfig* interConf = nullptr;
  std::string interNameStr("");
  CStdConverter::StringToStdStr(interName,interNameStr);
  interConf = CInterConfig::getInterConfig(interNameStr);
	treat=interConf->getTreatLenIdMode();
	if(treat == CInterConfig::Total)
	{
		ret = 1;
	}
	else
	{
		if(treat == CInterConfig::Body)
		{
			ret = 2;
		}
		else
		{
			ret = 3;
		}
	}
	return ret;
}
