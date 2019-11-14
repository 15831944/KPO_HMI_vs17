// Copyright 2006 SMS - Demag AG
//---------------------------------------------------------
#include "stdafx.h"
#include "CXmlInterConnInfoOpen.h"

//----------------------------------------------------------
CXmlInterConnInfoOpen::CXmlInterConnInfoOpen(CInterConnectionListe^ liste):
InterConnectionListe(liste),Reader(nullptr)
{
}
//----------------------------------------------------------
CXmlInterConnInfoOpen::~CXmlInterConnInfoOpen()
{
}
//----------------------------------------------------------
int CXmlInterConnInfoOpen::readInterConnectionInfo(String^ path)
{
    int ret=0;
    String^ interName=nullptr;
  
    Reader = gcnew XmlTextReader(path);
    while(Reader->Read())
    {
        int test;
        test = 0;
        if(Reader->NodeType == XmlNodeType::Element)
        {
            if((Reader->Name)->Equals("Interface"))
            {
                if(Reader->HasAttributes)
                {
                    interName = Reader[0];
                    setInterConnInfo(interName);
                }
            }    
        }
    }
    Reader->Close();
    return ret;
}
//----------------------------------------------------------
void CXmlInterConnInfoOpen::setInterConnInfo(String^ name)
{
   int index;
   String^ hostName = nullptr;
   String^ ipAddr = nullptr;
   String^ ident = nullptr;
   int port = 0;
   long ConnTimeOut = 0;

   CConnectionInfo::ConnectionType connType;
   if(name != nullptr)
   {
     index = InterConnectionListe->getInterNummber(name);
     if(index != -1)
     {
       if(Reader->Read())
       {
         while(!((Reader->NodeType == XmlNodeType::EndElement) && (Reader->Name->Equals("Interface"))))
         {
           if(Reader->NodeType == XmlNodeType::Element)
           {
             ident = Reader->Name;
           }
           if(Reader->NodeType == XmlNodeType::Text)
           {
             if(ident->Equals("Host"))
               hostName = Reader->Value;
             if(ident->Equals("IP-Addresse"))
               ipAddr = Reader->Value;
             if(ident->Equals("Port"))
               port = System::Convert::ToInt32(Reader->Value);
             if(ident->Equals("ConnType"))
               connType = getConnType(Reader->Value);
             if(ident->Equals("ConnTimeOut"))
               ConnTimeOut = System::Convert::ToInt32(Reader->Value);
            }
            Reader->Read();
         }
         InterConnectionListe->setHostInfo(index,hostName,ipAddr,port);
         InterConnectionListe->getInterfaceAt(index)->setConnectionType(connType);
         InterConnectionListe->getInterfaceAt(index)->setConnectionTimeOut(ConnTimeOut);
       }
     }
   }
}
//----------------------------------------------------------
CConnectionInfo::ConnectionType CXmlInterConnInfoOpen::getConnType(String^ connTypeStr)
{
  CConnectionInfo::ConnectionType ret = CConnectionInfo::ConnectionType::None;
  if(connTypeStr->Equals("Client"))
    ret =  CConnectionInfo::ConnectionType::Client;
  if(connTypeStr->Equals("Server"))
    ret =  CConnectionInfo::ConnectionType::Server;

  return ret;
}
//----------------------------------------------------------