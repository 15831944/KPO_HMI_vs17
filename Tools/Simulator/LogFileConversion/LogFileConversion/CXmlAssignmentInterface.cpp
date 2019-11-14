#include "stdafx.h"
#include "CXmlAssignmentInterface.h"
#include "CLogFileWriter.h"
//using namespace System::Xml;

//-------------------------------------------------------
CXmlAssignmentInterface::CXmlAssignmentInterface()
{
  this->SourceName = nullptr;
  this->DestinationName = nullptr;
  //this->xmlReader = nullptr;
  this->Path = nullptr;
}
//-------------------------------------------------------
CXmlAssignmentInterface::~CXmlAssignmentInterface()
{
}
//-------------------------------------------------------
void CXmlAssignmentInterface::getAssignmentInterfaces(String^& sourceName,String^& destName)
{
  sourceName = this->SourceName;
  destName = this->DestinationName;
}
//-------------------------------------------------------
void CXmlAssignmentInterface::setAssignmentCofigFileForRead(String^ path)
{
  bool flag=false;
  Path = path;
  XmlTextReader^ xmlReader = gcnew XmlTextReader(Path);
  while((!flag) && (xmlReader->Read()))
  {
    if(xmlReader->NodeType == System::Xml::XmlNodeType::Element)
    {
      if(xmlReader->Name->Equals("Assignment"))
      {
        flag = true;
        if(xmlReader->HasAttributes)
        {
          SourceName = xmlReader[0];
          DestinationName = xmlReader[1];
        }
      }
    }
  }
  xmlReader->Close();
}
//-------------------------------------------------------
void CXmlAssignmentInterface::readAssignmentCofigFile(CInterAssignment^ interAss)
{
  String^ sourceTlg = nullptr;
  String^ destTlg = nullptr;
  XmlTextReader^ xmlReader = gcnew XmlTextReader(Path);
  interAss->clearAssignment();
  CLogFileWriter^ wr = CLogFileWriter::getLogFileWriter();
  while(xmlReader->Read())
  {
    if(xmlReader->NodeType == System::Xml::XmlNodeType::Element)
    {
      if(xmlReader->Name->Equals("TlgAssignment"))
      {
        if(xmlReader->HasAttributes)
        {
          sourceTlg = xmlReader[0];
          destTlg = xmlReader[1];
					if(sourceTlg)
						interAss->setAssignedTlgName(sourceTlg,destTlg);

          wr->writeMessage(String::Concat("Source  ",sourceTlg,"  Dest ",destTlg));
        }
      }
      else
      {
        if(xmlReader->Name->Equals("ElemAssignment"))
        {
				  if((sourceTlg) && (destTlg) && (!sourceTlg->Equals("")) && (!destTlg->Equals("")))
          {
					  if(xmlReader->HasAttributes)
					  {
						  String^ sourceElem = nullptr;
						  String^ sourceSubElem = nullptr;
						  String^ destElem = nullptr;
						  String^ destSubElem = nullptr;
						  int pos;
						  sourceElem = xmlReader[0];
						  destElem = xmlReader[1];
						  pos = sourceElem->IndexOf("\\");
						  if(pos != -1)
						  {
							  sourceSubElem = sourceElem->Substring(pos+1,sourceElem->Length - pos -1);
							  sourceElem = sourceElem->Substring(0,pos);
						  }
						  pos = destElem->IndexOf("\\");
						  if(pos != -1)
						  {
							  destSubElem = destElem->Substring(pos+1,destElem->Length - pos -1);
							  destElem = destElem->Substring(0,pos);
						  }
						  interAss->setAssignedTlgElem(sourceTlg,sourceElem,sourceSubElem,destElem,destSubElem);
						}
          }
        }
      }
    }
  }
}
//-------------------------------------------------------
int CXmlAssignmentInterface::writeAssignmentInterface(String^ path,CInterAssignment^ interAss)
{
  int ret=0;
	int countTlg,i;
	int countElem,j;
	String^ sourceTlgName = nullptr;
	String^ destTlgName = nullptr;
	CTlgAssignment^ tlgAss = nullptr;
	array <String^>^ elemAssArray = nullptr;
  XmlTextWriter^ xmlWriter;

  Path = path;
  System::IO::File::Delete(path);
  xmlWriter = gcnew XmlTextWriter(path,nullptr); 
  xmlWriter->Formatting = Formatting::Indented;
  xmlWriter->WriteStartDocument();
  xmlWriter->WriteStartElement("Assignment");

  xmlWriter->WriteAttributeString("Source",interAss->getSourceInter()->getInterfaceName());
  xmlWriter->WriteAttributeString("Destination",interAss->getDestInter()->getInterfaceName());

	countTlg=interAss->getSourceTlgCount();
	for(i=1;i<=countTlg;i++)
	{
		sourceTlgName = interAss->getSourceTlgName(i);
		destTlgName = interAss->getAssignedTlgName(sourceTlgName);
		
		xmlWriter->WriteStartElement("TlgAssignment");
		xmlWriter->WriteAttributeString("Source",sourceTlgName);
		if(destTlgName == nullptr)
			destTlgName = "";
		xmlWriter->WriteAttributeString("Destination",destTlgName);

		elemAssArray=interAss->getTlgElemAssignment(sourceTlgName,destTlgName);
		countElem = elemAssArray->Length/2;
		for(j=1;j<=countElem;j++)
		{
			xmlWriter->WriteStartElement("ElemAssignment");
			xmlWriter->WriteAttributeString("Source",elemAssArray[(j-1)*2]);
			xmlWriter->WriteAttributeString("Destination",elemAssArray[(j-1)*2+1]);
			xmlWriter->WriteEndElement();
		}
		xmlWriter->WriteEndElement();
	}
  xmlWriter->WriteEndElement();
  xmlWriter->WriteEndDocument();
  xmlWriter->Flush();
  xmlWriter->Close();
  return ret;
}