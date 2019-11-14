// Copyright 2006 SMS - Demag AG
//----------------------------------------------------------------
#include "stdafx.h"
#include "CAppSetting.h"
#include "CXmlInterConfigWriter.h"
//----------------------------------------------------------------
CXmlInterConfigWriter::CXmlInterConfigWriter():
XmlDocWriter(nullptr),InterWr(nullptr),Section(nullptr),FilePath(nullptr)
{
}
//----------------------------------------------------------------
CXmlInterConfigWriter::~CXmlInterConfigWriter()
{
}
//------------------------------------------------------------------
void CXmlInterConfigWriter::createInterConfigFile(CTlgInterfaceWrapper^ interWr,String^ path)
{
  System::Xml::XmlTextWriter^ confWr = nullptr;
  String^ interPath = nullptr;

  InterWr = interWr;
  if (path->IndexOf(".icnf")==-1)
    interPath = String::Concat(path,"\\",interWr->getInterfaceName(),".icnf");
  else
    interPath = path;

  confWr = gcnew System::Xml::XmlTextWriter(interPath,nullptr);
  confWr->Formatting = Formatting::None;
  confWr->WriteStartDocument();
  confWr->WriteStartElement(interWr->getInterfaceName());
  createSegmentTelId(confWr);
  createSegmentLogFile(confWr);
  createSegmentTransport(confWr);
  createSegmentLimitValue(confWr);
  createSegmentArrayView(confWr);
  createSegmentUseCaseView(confWr);
  confWr->WriteEndElement();
  confWr->WriteEndDocument();
  confWr->Flush();
  confWr->Close();
}
//------------------------------------------------------------------
void CXmlInterConfigWriter::createSegmentTelId(XmlTextWriter^ wr)
{
  CTlgWrapper^ wrTlg=nullptr;
  String^ nameTlg=nullptr;
  int count,i;

  CAppSetting^ Sett = CAppSetting::getApp();
  String^ HeaderTlg = Sett->getHeaderTlg();

  wr->WriteStartElement("TelegramId");
  //wr->WriteAttributeString("TelId","Head");
  wr->WriteAttributeString("TelId",HeaderTlg);
  wr->WriteAttributeString("ElemId","");
  wr->WriteAttributeString("TypId","");
  wr->WriteAttributeString("LenId","");
  wr->WriteAttributeString("LenTreat","Total Length");

  wrTlg = gcnew CTlgWrapper();
  count = InterWr->getTlgCount();
  for(i=1;i<=count;i++)
  {
    InterWr->getClonedTlg(wrTlg,i);
    wr->WriteStartElement(wrTlg->getName());
    wr->WriteEndElement();
  }
  wr->WriteEndElement();
}
//------------------------------------------------------------------
bool CXmlInterConfigWriter::loadInterConfigFile(String^ path)
{
  bool ret = true;
  //String^ confFile = String::Concat(path,"\\",interWr->getInterfaceName(),".icnf");
  XmlDocWriter = gcnew XmlDocument();
  XmlDocWriter->Load(path);
  FilePath = path;
  return ret;
}
//------------------------------------------------------------------
bool CXmlInterConfigWriter::setSectionFocus(String^ sec)
{
  bool ret = false;

  if(XmlDocWriter)
  {
    Section = XmlDocWriter->DocumentElement[sec];
      
    if(Section)
      ret = true;
  }

  return ret;
}
//------------------------------------------------------------------
void CXmlInterConfigWriter::setTelId(String^ telName,String^ id)
{
  if(Section)
  {
    System::Xml::XmlElement^ elem = Section[telName];
    if(elem)
    {
      elem->InnerText = id;
    }
    else
    {
      elem = XmlDocWriter->CreateElement(telName);
      elem->InnerText = id;
      Section->AppendChild(elem);
    }
    //XmlElement* elem = XmlDocWriter->CreateElement(telName);
    //if(id)
    //  elem->SetAttribute("Id",id);
    //else
    //  elem->SetAttribute("Id","");
    //Section->AppendChild(elem);
  }
}
//------------------------------------------------------------------
void CXmlInterConfigWriter::beginUpdate()
{
  if(Section)
    Section->RemoveAll();
}
//------------------------------------------------------------------
void CXmlInterConfigWriter::endUpdate()
{
  XmlDocWriter->Save(FilePath);
}
//------------------------------------------------------------------
void CXmlInterConfigWriter::setTelIdInfo(String^ telId,String^ elemId,String^ typId,String^ lenId,String^ treatLenId)
{
  Section->SetAttribute("TelId",telId);
  Section->SetAttribute("ElemId",elemId);
  Section->SetAttribute("TypId",typId);
  Section->SetAttribute("LenId",lenId);
  Section->SetAttribute("LenTreat",treatLenId);
}
//------------------------------------------------------------------
void CXmlInterConfigWriter::createSegmentLogFile(XmlTextWriter^ wr)
{
  wr->WriteStartElement("LogFile");

  wr->WriteStartElement("Date");
  wr->WriteString("YYYY-MM-DD");
  wr->WriteEndElement();

  wr->WriteStartElement("Time");
  wr->WriteString("HH:MM:SS.mm");
  wr->WriteEndElement();

  wr->WriteStartElement("Separator");
  wr->WriteString("|");
  wr->WriteEndElement();

  //wr->WriteStartElement("Limit");
  //wr->WriteString("NotTreat");
  //wr->WriteEndElement();

  wr->WriteEndElement();
}
//------------------------------------------------------------------
void CXmlInterConfigWriter::createSegmentTransport(XmlTextWriter^ wr)
{
  wr->WriteStartElement("Transport");

  wr->WriteAttributeString("Swapping","NotSwapping");
  wr->WriteAttributeString("PaddingDir","Left");
  wr->WriteAttributeString("PaddingStr","");

  wr->WriteEndElement();
}
//------------------------------------------------------------------
void CXmlInterConfigWriter::createSegmentLimitValue(XmlTextWriter^ wr)
{
  wr->WriteStartElement("Limit");
  wr->WriteString("NotTreat");
  wr->WriteEndElement();
}
//------------------------------------------------------------------
void CXmlInterConfigWriter::createSegmentArrayView(XmlTextWriter^ wr)
{
  int countTlg,i;
  int countElem,j;
  int typ;
  String^ nameElem = nullptr;
  String^ nameTlg = nullptr;
  int countSubElem = 0;
  CTlgWrapper^ wrTlg = gcnew CTlgWrapper();

  wr->WriteStartElement("ArrayView");

  countTlg = InterWr->getTlgCount();
  for(i=1;i<=countTlg;i++)
  {
    InterWr->getClonedTlg(wrTlg,i);
    countElem = wrTlg->getTlgElemCount();
    for(j=1;j<=countElem;j++)
    {
      typ=wrTlg->getElemTyp(j);
      if(typ == 2)
      {
        nameElem = wrTlg->getElemName(j);
        nameTlg  = wrTlg->getName();
        countSubElem = wrTlg->getSubElemCount(j);
        wr->WriteStartElement(nameElem);
        wr->WriteAttributeString("tel",nameTlg);
        wr->WriteAttributeString("count",System::Convert::ToString(countSubElem));
        wr->WriteStartElement("Row1");
        wr->WriteString("Not Name");
        wr->WriteEndElement();
        wr->WriteEndElement();
      }
    }
  }

  wr->WriteEndElement();
}
//------------------------------------------------------------------
void CXmlInterConfigWriter::setLogFileSeparator(String^ sep)
{
  Section["Separator"]->InnerText = sep;
}
//------------------------------------------------------------------
void CXmlInterConfigWriter::setLimitTreatmentTyp(String^ lim)
{
  Section->InnerText = lim;
}
//------------------------------------------------------------------
void CXmlInterConfigWriter::setLogFileDate(String^ date)
{
  Section["Date"]->InnerText = date;
}
//------------------------------------------------------------------
void CXmlInterConfigWriter::setLogFileTime(String^ time)
{
  Section["Time"]->InnerText = time;
}
//------------------------------------------------------------------
void CXmlInterConfigWriter::setTranspSwapping(String^ swapping)
{
  Section["Swapping"]->InnerText = swapping;
}
//------------------------------------------------------------------
void CXmlInterConfigWriter::setTranspPaddingDir(String^ dir)
{
  Section["PaddingDir"]->InnerText = dir;
}
//-----------------------------------------------------------------
void CXmlInterConfigWriter::setTranspPaddingStr(String^ str)
{
  Section["PaddingStr"]->InnerText = str;
}
//-----------------------------------------------------------------
void CXmlInterConfigWriter::setTransportInfo(String^& Swapping, String^& PaddingDir, String^& PaddingStr)
{
  Section->SetAttribute("Swapping",Swapping);
  Section->SetAttribute("PaddingDir",PaddingDir);
  Section->SetAttribute("PaddingStr",PaddingStr);
}
//------------------------------------------------------------------
void CXmlInterConfigWriter::addArrayRow(String^ nameElem,String^ nameTel,String^ countElem,array <String^>^ rowName)
{
  int count,i;
  XmlElement^ elem = XmlDocWriter->CreateElement(nameElem);
  XmlElement^ subelem = nullptr;
  elem->SetAttribute("tel",nameTel);
  elem->SetAttribute("count",countElem);

  count = rowName->Length;
  for(i=0;i<count;i++)
  {
    subelem = XmlDocWriter->CreateElement(String::Concat("Row",System::Convert::ToString(i+1)));
    subelem->InnerText = rowName[i];
    elem->AppendChild(subelem);
  }

  Section->AppendChild(elem);
}
//------------------------------------------------------------------
void CXmlInterConfigWriter::createSegmentUseCaseView(XmlTextWriter^ wr)
{
  wr->WriteStartElement("UseCase");
  wr->WriteEndElement();
}
//------------------------------------------------------------------
void CXmlInterConfigWriter::addUseCase(String^ name,array <String^>^ descr,String^ items)
{
  String^ UseCaseDescr = nullptr;
  int count = descr->Length;
  for(int i=0;i<count;i++)
  {
    UseCaseDescr = String::Concat(UseCaseDescr,descr[i]);
    UseCaseDescr = String::Concat(UseCaseDescr,"\n");
  }

  XmlElement^ elem = XmlDocWriter->CreateElement(name);
  XmlElement^ subElem = XmlDocWriter->CreateElement("Item");
  elem->SetAttribute("descr",UseCaseDescr);
  subElem->InnerText = items;
  elem->AppendChild(subElem);

  Section->AppendChild(elem);
}
//------------------------------------------------------------------