// Copyright 2006 SMS - Demag AG
#include "stdafx.h"
#include "CInterConnectionListe.h"

//----------------------------------------------
CInterConnectionListe::CInterConnectionListe():
ActiveInterface(0),IsConnectedEvent(nullptr)
{
  InterConnectionListe = gcnew ArrayList();
  ConEventListe = gcnew ArrayList();
}
//----------------------------------------------
CInterConnectionListe::~CInterConnectionListe()
{
}
//------------------------------------------------
void CInterConnectionListe::setActiveInterface(int number)
{
	this->ActiveInterface = number;
}
//------------------------------------------------
int CInterConnectionListe::getActiveInterface()
{
	return this->ActiveInterface;
}
//------------------------------------------------
void CInterConnectionListe::setHostInfo(int index,String^ hostName,String^ ipAddr,int port)
{
  CInterConnection^ inter = safe_cast<CInterConnection^>(InterConnectionListe[index-1]);
  inter->setHostInfo(hostName,ipAddr,port);
}
//------------------------------------------------
void CInterConnectionListe::getHostInfo(int index,String^& hostName,String^& ipAddr,int* port)
{
   CInterConnection^ inter = safe_cast<CInterConnection^>(InterConnectionListe[index-1]);
   inter->getHostInfo(hostName,ipAddr,port);
}
void CInterConnectionListe::addInterface(String^ interName)
{
   //CSocketConnection::updateConnEvent* conEvent = new CSocketConnection::updateConnEvent(this,&CInterConnectionListe::notifyToObserver);
   CInterConnection^ inter = gcnew CInterConnection(interName);
   //inter->setInterName(TlgFactory->getFactoryName());
   InterConnectionListe->Add(inter);
   //inter->setUpdateConEvent(conEvent);  
}
//------------------------------------------------
void CInterConnectionListe::addInterface(CInterConnection^ inter)
{
    InterConnectionListe->Add(inter);
}
//------------------------------------------------
int CInterConnectionListe::getInterfaceCount()
{
  if(InterConnectionListe != nullptr)
	  return InterConnectionListe->Count;

  else
    return 0;
}
//------------------------------------------------
String^  CInterConnectionListe::getInterfaceName(int id)
{
	CInterConnection^ inter = safe_cast<CInterConnection^>(InterConnectionListe[id-1]);
	return inter->getInterName();
}
//------------------------------------------------
int CInterConnectionListe::buildConnection(int index)
{
  int ret = 0;
  CConnectionInfo::ConnectionType type;
  CInterConnection^ inter = safe_cast<CInterConnection^>(InterConnectionListe[index-1]);
  type=inter->getConnectionType();
 
  if(type == CConnectionInfo::ConnectionType::Client)
  {
    ret=inter->buildConnAsClient();
  }
  else
  {
    if(type == CConnectionInfo::ConnectionType::Server)
    {
      ret = inter->buildConnAsServer();
    }
    else
    {
      ret = 1;
    }
  }

  return ret;
}
//------------------------------------------------
void CInterConnectionListe::setDelConnection(DelIsConnected^ conn)
{
	this->IsConnectedEvent = conn;
}
//------------------------------------------------
bool CInterConnectionListe::isConnected(int index)
{
	CInterConnection^ inter = safe_cast<CInterConnection^>(InterConnectionListe[index-1]);

	return inter->isConnected();
}
//------------------------------------------------
 bool CInterConnectionListe::isWaiting(int index)
 {
	 CInterConnection^ inter = safe_cast<CInterConnection^>(InterConnectionListe[index-1]);
	return inter->isWaiting();
 }
//------------------------------------------------
String^ CInterConnectionListe::getConnType(int index)
{
	CInterConnection^ inter = safe_cast<CInterConnection^>(InterConnectionListe[index-1]);
	return inter->getConnType();
}
//------------------------------------------------
bool CInterConnectionListe::disConnect(int index)
{
  CInterConnection^ inter = safe_cast<CInterConnection^>(InterConnectionListe[index-1]);

  return inter->disConnect();
}
//------------------------------------------------
void CInterConnectionListe::disConnectAll()
{
  CInterConnection^ inter = nullptr;
  int count = InterConnectionListe->Count;

  for(int i=0;i<count;i++)
  {
     inter = safe_cast<CInterConnection^>(InterConnectionListe[i]);
     inter->disConnect();
  }
}
//------------------------------------------------
int CInterConnectionListe::sendByteStream(unsigned char* bytes,int len,int index)
{
  int ret = -1;
  CInterConnection^ inter = safe_cast<CInterConnection^>(InterConnectionListe[index-1]);
  ret=inter->sendByteStream(bytes,len);

  return ret;
}
//------------------------------------------------
int CInterConnectionListe::receiveByteStream(char* bytes,int len,int index)
{
  int ret = -1;
  
  CInterConnection^ inter = safe_cast<CInterConnection^>(InterConnectionListe[index-1]);
  ret=inter->receiveByteStream(bytes,len);

  return ret;
}
//------------------------------------------------
void CInterConnectionListe::setDirection(String^ dir)
{
  this->Dir = dir;
}
//--------------------------------------------------
String^ CInterConnectionListe::getDirection()
{
  return Dir;
}
//------------------------------------------------
int CInterConnectionListe::getInterNummber(String^ name)
{
  int ret = -1;
  int count,i;
  bool flag;
  CInterConnection^ inter=nullptr;

  count=InterConnectionListe->Count;
  i=0;
  flag = true;
  while((flag) && (i<count))
  {
    inter = safe_cast<CInterConnection^>(InterConnectionListe[i]);
    if(inter->getInterName()->Equals(name))
    {
      flag = false;
    }
    else
    {
      i++;
    }
  }
  if(!flag)
    ret = i+1;

  return ret;
}
//------------------------------------------------
void CInterConnectionListe::addObserver(ChangeConnectionEvent^ event)
{
  ConEventListe->Add(event);
}
//------------------------------------------------
void CInterConnectionListe::notifyToObserver(String^ interName,int status)
{
  int count,i;
  ChangeConnectionEvent^ conEvent = nullptr;

  count = ConEventListe->Count;
  for(i=0;i<count;i++)
  {
    conEvent = safe_cast<ChangeConnectionEvent^>(ConEventListe[i]);
    conEvent->Invoke(interName,status);
  }
}
//------------------------------------------------
void CInterConnectionListe::setConnectionUpdateInterEvent(ConnectionUpdateInterEventTyp^ event,String^ inter)
{
   int index = getInterNummber(inter)-1;
   CInterConnection^ interConn=nullptr;

   if(index>=0)
   {
       interConn = safe_cast<CInterConnection^>(InterConnectionListe[index]);
       interConn->addConnectionUpdateInterEvent(event);
   }

}
//------------------------------------------------
void CInterConnectionListe::removeInerface(String^ inter)
{
	int index=getInterNummber(inter);
	if(index > 0)
	{
		disConnect(index);
		InterConnectionListe->RemoveAt(index-1);
	}
}
//------------------------------------------------
CInterConnection^ CInterConnectionListe::getInterfaceAt(int index)
{
  if (index <= InterConnectionListe->Count)
    return safe_cast<CInterConnection^>(InterConnectionListe[index-1]);
  else
    return nullptr;
}
//------------------------------------------------
