// Copyright 2006 SMS - Demag AG
//------------------------------------------------------------------
#include "stdafx.h"
#include "CInterSenderManager.h"
#include "CLogWriterWrapper.h"

//-------------------------------------------------------------------------------
CInterSenderManager::CInterSenderManager(CTlgInterfaceWrapper^ InterMap,CInterConnection^ interConSock):
CInterBaseManager(InterMap,interConSock)
{
  LogFileReader = gcnew CTlgLogFileReaderWrapper();
  LogFileReader->setTlgProtoTyp(InterSet->getTlgProtoTypSet());
  interConSock->setReceiveThreadInSenderManagerEvent (gcnew CInterConnection::ReceiveThreadInSenderManagerEventTyp(this,&CInterSenderManager::InvokeReceiveThread));
  RecThr = nullptr;
}
//-------------------------------------------------------------------------------
bool CInterSenderManager::checkInterface(String^ path)
{
  bool ret = false;
  ret = LogFileReader->checkInterface(path);
  return ret;
}
//-------------------------------------------------------------------------------
int CInterSenderManager::getTlgCount()
{
  return LogFileReader->getTlgCount();
}
//-------------------------------------------------------------------------------
String^ CInterSenderManager::getInterfaceName()
{
  return InterSet->getInterfaceName();
}
//-------------------------------------------------------------------------------
int CInterSenderManager::loadLogFile(String^ path,const bool &abort)
{
	int ret = 0;
	ret=LogFileReader->loadFromFile(path,abort);
	return ret;
}
//-------------------------------------------------------------------------------
CTlgLogFileReaderWrapper^ CInterSenderManager::getLogFileContainer()
{
	return LogFileReader;
}
//-------------------------------------------------------------------------------
int CInterSenderManager::sendBytes(unsigned char* bytes,int len)
{
  int ret = 0;
  bool ok = true;
  while(ok)
  {
    //Versucht, den Inter Objekt zu sperren
    if (Threading::Monitor::TryEnter(InterConn))
    {
      ret=InterConn->sendByteStream(bytes,len);
      //Sperre aufheben
      Threading::Monitor::Exit(InterConn);
      ok=false;
    }
    else
    {
      //Sonst warten
      Threading::Thread::CurrentThread->Sleep(1);
    }
  }
  return ret;
}
//-------------------------------------------------------------------------------
void CInterSenderManager::clearLogFile()
{
	if(LogFileReader)
		LogFileReader->clearContainer();
}
//-------------------------------------------------------------------------------
bool CInterSenderManager::isLogFileLoad()
{
  bool ret=false;
  if(LogFileReader)
    if(LogFileReader->getVirtualTlgCount() != 0)
        ret=true;
  return ret;
}
//-------------------------------------------------------------------------------
void CInterSenderManager::InvokeReceiveThread(bool start)
{
  String^ mess = nullptr;
  if (start)
  {
    RecThr = gcnew Threading::Thread(gcnew Threading::ThreadStart(this,&CInterSenderManager::receive));
    RecThr->Start();
    mess = "Receive thread (checks server connection) started";
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  }
  else if (RecThr)
  {
    RecThr->Abort();
    RecThr = nullptr;
    mess = "Receive thread (checks server connection) aborted";
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  }
}
//------------------------------------------------------------------------------
void CInterSenderManager::receive()
{
  if (InterConn)
  {
    bool ok = true;
    char* tlgIdBuff=new char(8192);
    while (ok && InterConn && InterConn->isConnected())
    {
      InterConn->receiveByteStream(tlgIdBuff,8192);
      RecThr->Sleep(50);
    } 
   }
}
//-------------------------------------------------------------------------------
CInterConnection^ CInterSenderManager::getInterConn (void)
{
  return this->InterConn;
}