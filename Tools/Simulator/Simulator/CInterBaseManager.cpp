// Copyright 2006 SMS - Demag AG
//-----------------------------------------------
#include "stdafx.h"
#include "CInterBaseManager.h"
//--------------------------------------------------------------------------
CInterBaseManager::CInterBaseManager(CTlgInterfaceWrapper^ InterMap,CInterConnection^ interConSock)
{
	this->InterSet = InterMap;
	this->InterConn = interConSock;
  MessageHandler=nullptr;
}
//--------------------------------------------------------------------------
String^ CInterBaseManager::getInterfaceDescr()
{
  return InterSet->getInterfaceDescr();
}
//--------------------------------------------------------------------------
String^ CInterBaseManager::getInterfaceVersion()
{
  return InterSet->getInterfaceVersion();
}
//--------------------------------------------------------------------------
String^ CInterBaseManager::getInterfaceName()
{
	return InterSet->getInterfaceName();
}
//--------------------------------------------------------------------------
CTlgInterfaceWrapper^ CInterBaseManager::getInterProtoSet()
{
	return InterSet;
}
//--------------------------------------------------------------------------
CItemWrapper^ CInterBaseManager::makeTlg(String^ name)
{
	CItemWrapper^ ret=nullptr;
	ret=InterSet->makeTlg(name);
	return ret;
}
//--------------------------------------------------------------------------
bool CInterBaseManager::isConnected()
{
  return InterConn->isConnected();
}
//--------------------------------------------------------------------------
bool CInterBaseManager::isWaiting()
{
	return InterConn->isWaiting();
}
//--------------------------------------------------------------------------
void CInterBaseManager::getHostInfo(String^& host,String^& ip,int* port)
{
	InterConn->getHostInfo(host,ip,port);
}
//--------------------------------------------------------------------------
String^ CInterBaseManager::getConnectionTyp()
{
  return InterConn->getConnType();
}
//--------------------------------------------------------------------------
void CInterBaseManager::setMessageHandler(MessageHandlerSendRecTyp^ handler)
{
  this->MessageHandler = handler;
}
//--------------------------------------------------------------------------