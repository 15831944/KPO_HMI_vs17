// Copyright 2006 SMS - Demag AG
//---------------------------------------------------------------
#include "stdafx.h"
#include "CXmlInterConfigReader.h"
#include "CLogWriterWrapper.h"
//---------------------------------------------------------------
CXmlInterConfigReader::CXmlInterConfigReader():
XmlDoc(nullptr),Section(nullptr),Node(nullptr)
{
}
//---------------------------------------------------------------
CXmlInterConfigReader::~CXmlInterConfigReader()
{
}
//----------------------------------------------------------------
bool CXmlInterConfigReader::setInterConfigFile(String^ path)
{
  bool ret = true;
  XmlDoc = gcnew System::Xml::XmlDocument();
	XmlDoc->PreserveWhitespace = false;
  XmlDoc->Load(path);
  return ret;
}
//----------------------------------------------------------------
bool CXmlInterConfigReader::setSectionFocus(String^ sec)
{
  bool ret = false;
  
  if(XmlDoc)
  {
		Section = XmlDoc->DocumentElement[sec];
    //Section = XmlDoc[sec);
	  if(Section)
		  ret = true;
    Node = nullptr;
  }

  return ret;
}
//----------------------------------------------------------------
bool CXmlInterConfigReader::getNextTlgId(String^& tel,String^& id)
{
  bool ret = false;
  if(Node == nullptr)
  {
    Node = Section->FirstChild;
  }
  else
  {       
    //Node = Section->NextSibling();
		Node = Node->NextSibling;
  }
  if(Node)
  {
    tel = Node->Name;
	  id = Node->InnerText;
    ret = true;
  }
  else
  {
    ret = false;
    tel = nullptr;
    id = nullptr;
  }

  return ret;
}
//----------------------------------------------------------------
void CXmlInterConfigReader::getElemIdName (String^& telIdName,String^& elemIdName)
{
  System::Xml::XmlAttributeCollection^ attrCol = Section->Attributes;
  elemIdName = attrCol["ElemId"]->Value;
  telIdName = attrCol["TelId"]->Value;
}
//----------------------------------------------------------------
void CXmlInterConfigReader::getTelIdInfo(String^& telIdName,String^& elemIdName,String^& typId,String^& ElemLenName,String^& LenTreat)
{
  System::Xml::XmlAttributeCollection^ attrCol = Section->Attributes;
	telIdName = attrCol["TelId"]->Value;
  elemIdName = attrCol["ElemId"]->Value;
  typId = attrCol["TypId"]->Value;
  ElemLenName = attrCol["LenId"]->Value;
	LenTreat = attrCol["LenTreat"]->Value;
}
//----------------------------------------------------------------
String^ CXmlInterConfigReader::getLogFileSeparator()
{
  String^ ret = nullptr;
  ret = Section["Separator"]->InnerText;
  return ret; 
}
//----------------------------------------------------------------
String^ CXmlInterConfigReader::getLimitValueTreatment()
{
  String^ ret = nullptr;
	ret = Section->InnerText;
  return ret; 
}
//----------------------------------------------------------------
String^ CXmlInterConfigReader::getLogFileDateFormat()
{
  String^ ret = nullptr;
  ret = Section["Date"]->InnerText;
  return ret;
}
//----------------------------------------------------------------
String^ CXmlInterConfigReader::getLogFileTimeFormat()
{
  String^ ret = nullptr;
  ret = Section["Time"]->InnerText;
  return ret;
}
//----------------------------------------------------------------
String^ CXmlInterConfigReader::getTranspSwapping()
{
	String^ ret = nullptr;
  ret = Section["Swapping"]->InnerText;
  return ret;
}
//----------------------------------------------------------------
String^ CXmlInterConfigReader::getTranspPaddingDir()
{
	String^ ret = nullptr;
  ret = Section["PaddingDir"]->InnerText;
  return ret;
}
//----------------------------------------------------------------
String^ CXmlInterConfigReader::getTranspPaddingStr()
{
	String^ ret = nullptr;
  ret = Section["PaddingStr"]->InnerText;
  return ret;
}

//----------------------------------------------------------------
void CXmlInterConfigReader::getTransportInfo(String^& Swapping, String^& PaddingDir, String^& PaddingStr)
{
  System::Xml::XmlAttributeCollection^ attrCol = Section->Attributes;
	Swapping    = attrCol["Swapping"]->Value;
	PaddingDir  = attrCol["PaddingDir"]->Value;
  PaddingStr  = attrCol["PaddingStr"]->Value;
}
//----------------------------------------------------------------
array <String^>^ CXmlInterConfigReader::getNextArrayElemInfo(String^& elemName,String^& telName,String^& elemCount)
{
  array <String^>^ ret = nullptr;
  if(Node == nullptr)
  {
    Node = Section->FirstChild;
  }
  else
  {       
    Node = Node->NextSibling;
  }
  if(Node)
  {
    elemName = Node->Name;
    System::Xml::XmlAttributeCollection^ atr =  Node->Attributes;
    telName = atr["tel"]->Value;
    elemCount = elemCount = atr["count"]->Value;
    int count = Node->ChildNodes->Count;
    ret = gcnew array <String^>(count);
    for(int i=0;i<count;i++)
    {
      ret[i]=Node->ChildNodes[i]->InnerText;
    }
  }
  return ret;
}
//----------------------------------------------------------------
bool CXmlInterConfigReader::getNextUseCase(String^& name,String^& descr,String^& items) 
{
	bool ret = true;
  if(Node == nullptr)
  {
    Node = Section->FirstChild;
  }
  else
  {       
    Node = Node->NextSibling;
  }
  if(Node)
  {
	  name = Node->Name;
	  descr = Node->Attributes["descr"]->Value;
	  items = Node->ChildNodes[0]->InnerText;
	}
	else
	{
		ret = false;
	}

	return ret;
}
//
//----------------------------------------------------------------
String^ CXmlInterConfigReader::getTlgId(String^ tel)
{
  String^ ret = nullptr;

  if (Section[tel])
    ret = Section[tel]->InnerText;

  return ret;
}
//----------------------------------------------------------------