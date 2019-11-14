// Copyright 2006 SMS - Demag AG

//---------------------------------------------------------------
#include "stdafx.h"
#include "CConnectionInfo.h"
//----------------------------------------------------------------
CConnectionInfo::CConnectionInfo():
HostName(nullptr),IpAddr(nullptr),Port(-1),ConnnectionTimeOut(0)
{
  this->Type = CConnectionInfo::ConnectionType::None;
}
//----------------------------------------------------------------
CConnectionInfo::~CConnectionInfo()
{
}
//-----------------------------------------------------------------
void CConnectionInfo::setPort(int port)
{
  this->Port = port;
}
//-----------------------------------------------------------------
void CConnectionInfo::setIpAddresse(String^ ipAddr)
{
  this->IpAddr = ipAddr;
}
//-----------------------------------------------------------------
void CConnectionInfo::setHostName(String^ hostName)
{
  this->HostName = hostName;
}
//-----------------------------------------------------------------
void CConnectionInfo::setConnectionType(ConnectionType type)
{
  this->Type = type;
}
//-----------------------------------------------------------------
int CConnectionInfo::getPort()
{
  return this->Port;
}
//------------------------------------------------------------------
String^ CConnectionInfo::getIpAddresse()
{
  if(IpAddr != nullptr)
    return IpAddr;
  else
    return nullptr;
}
//-----------------------------------------------------------------
String^ CConnectionInfo::getHostName()
{
  if(HostName != nullptr)
    return HostName;
  else
    return nullptr;
}
//------------------------------------------------------------------
CConnectionInfo::ConnectionType CConnectionInfo::getConnectionType()
{
  return this->Type;
}
//------------------------------------------------------------------
void CConnectionInfo::setConnectionTimeOut(long ctime_)
{
  ConnnectionTimeOut = ctime_;
}
//-----------------------------------------------------------------
long CConnectionInfo::getConnectionTimeOut()
{
  return ConnnectionTimeOut;
}
//-----------------------------------------------------------------
