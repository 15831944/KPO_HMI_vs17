#include "stdafx.h"
#include "CXmlSzenWriter.h"
#include "CFormatConverterWrapper.h"


//------------------------------------------
CXmlSzenWriter::CXmlSzenWriter():
Writer(nullptr)
{
}
//------------------------------------------
CXmlSzenWriter::~CXmlSzenWriter()
{
}
//------------------------------------------
void CXmlSzenWriter::writeSzenarium(String^ path,CSzenarium^ szen)
{
   String^ name=nullptr;
   int count,i;

   Szen=szen;
   
   Writer = gcnew XmlTextWriter(path,nullptr);
   Writer->Formatting = Formatting::Indented;

   

   Writer->WriteStartDocument();
   Writer->WriteStartElement("Szenarium");

   name=getNameSzen(path);

   Writer->WriteAttributeString("name",name);

   count=Szen->getSzenItemCount();
   for(i=0;i<count;i++)
   {
      writeTlg(i);
   }

   Writer->WriteEndElement();

   Writer->Flush();
	 Writer->Close();


}
//------------------------------------------
void CXmlSzenWriter::writeTlg(int index)
{
   String^ value=nullptr;
   double d;
   bool status;

   Writer->WriteStartElement("telegram");
   value=Szen->getSzenItem(index+1)->getItemName();
   Writer->WriteAttributeString("name",value);

   //--------------------------------------------
   Writer->WriteStartElement("body");
   //d=Szen->getSzenItem(index+1)->getDelay();
   value=Szen->getSzenItem(index+1)->SerializeTlgAsString();
   Writer->WriteString(value);
   Writer->WriteEndElement();
   //--------------------------------------------
    Writer->WriteStartElement("statu");
    status=Szen->getSzenItem(index+1)->getSendStatus();
    if(status)
      Writer->WriteString("On");
    else
     Writer->WriteString("Off");
    Writer->WriteEndElement();
   //--------------------------------------------
   Writer->WriteStartElement("delay");
   d=Szen->getSzenItem(index+1)->getDelay();
   Writer->WriteString(CFormatConverterWrapper::DoubleToString(d));
   Writer->WriteEndElement();
   //------------------------------------------
   
   //------------------------------------------

   Writer->WriteEndElement();
}
//------------------------------------------
String^ CXmlSzenWriter::getNameSzen(String^ name)
{
  String^ ret=nullptr;
  int pos=-1;
  
  pos=name->LastIndexOf("\\");
  if(pos != -1)
  {
    ret = name->Substring(pos+1,name->Length-pos-1);
    pos=ret->LastIndexOf(".");
    if(pos != -1)
      ret = ret->Substring(0,pos);
  }
  else
  {
    ret=name;
  }
  return ret;
}
//------------------------------------------
