// Copyright 2006 SMS - Demag AG
#include "stdafx.h"
#include "CXmlInterConnInfoSave.h"

//--------------------------------------------------------
CXmlInterConnInfoSave::CXmlInterConnInfoSave(CInterConnectionListe^ liste):
InterConnectionListe(liste),Writer(nullptr)
{
}
//--------------------------------------------------------
CXmlInterConnInfoSave::~CXmlInterConnInfoSave()
{
}
//--------------------------------------------------------
int CXmlInterConnInfoSave::saveConnectionInfo(String^ path)
{
   int ret = 0;
   int count,i;
   String^ name=nullptr;
   String^ hostName=nullptr;
   String^ ipAddr=nullptr;
   int port = 0;
   CConnectionInfo::ConnectionType conType;
   String^ conTypeStr="None";

   System::IO::File::Delete(path);

   Writer = gcnew XmlTextWriter(path,nullptr);
   Writer->Formatting = Formatting::Indented;

   
   Writer->WriteStartDocument();
   Writer->WriteStartElement("Connection-Info");

   count = InterConnectionListe->getInterfaceCount();
   for(i=0;i<count;i++)
   {
     name=InterConnectionListe->getInterfaceName(i+1);
     Writer->WriteStartElement("Interface");
     Writer->WriteAttributeString("name",name);

     InterConnectionListe->getHostInfo(i+1,hostName,ipAddr,&port);
     conType = InterConnectionListe->getInterfaceAt(i+1)->getConnectionType();
     if(conType == CConnectionInfo::ConnectionType::Client)
       conTypeStr = "Client";
     if(conType == CConnectionInfo::ConnectionType::Server)
       conTypeStr = "Server";
     //if(conType == CConnectionInfo::ConnectionType::None)
       //conTypeStr = "None";

     writeElement("Host",hostName);
     writeElement("IP-Addresse",ipAddr);
     writeElement("Port",System::Convert::ToString(port));
     writeElement("ConnType",conTypeStr);
     

     Writer->WriteEndElement();

   }

    Writer->WriteEndElement();

    Writer->Flush();
    Writer->Close();

  return ret;
}
//--------------------------------------------------------
void CXmlInterConnInfoSave::writeElement(String^ elem,String^ val)
{
   Writer->WriteStartElement(elem);
   Writer->WriteString(val);
   Writer->WriteEndElement();
}
//--------------------------------------------------------