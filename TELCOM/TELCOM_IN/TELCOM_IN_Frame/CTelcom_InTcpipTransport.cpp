// Copyright (C) 2007 SMS Demag AG

#include "CTelcom_InTcpipTransport.h"
#include "CTelcom_InTask.h"
#include "cCBS_StdLog_Task.h"
#include "CSMC_EventLogFrameController.h"


//##ModelId=45AB96E8003D
CTelcom_InTcpipTransport::CTelcom_InTcpipTransport()
{
  m_iHeaderLen = 8;
}

//##ModelId=45AB96E801C3
CTelcom_InTcpipTransport::~CTelcom_InTcpipTransport()
{
}

//##ModelId=45ABB0FA0161
int CTelcom_InTcpipTransport::readMsgHeader(char* msg, int msgmax, int* plmsg)
{
  // See description of the Header of Communication Standards.
  // Here we read m_iHeaderLen bytes defined in telegram
  // and get message length from first two bytes.
  //////////////////////////////////////////////////////////////
  // If a header have another structure, overwrite this message in the subclass
  //
  int rec = 0;
  if( (rec = _receive(msg, m_iHeaderLen)) && (rec >0) ) // consume first bytes with check for timeout
  {
    unsigned short len = 0;          // for Length
    // all bytes in len are 0
    // we get msg length inverted 
    // because it is defined as binary and not as ascii.

    if (BigEndPlatf)
    {
      len = (unsigned char)msg[0]; // copy byte 0
      len = len << 8;     // shift 8 bits left
      len = len | (unsigned char)msg[1]; // copy byte 1
    }
    else
    {
      len = (unsigned char)msg[1]; // copy byte 1
      len = len << 8;     // shift 8 bits left
      len = len | (unsigned char)msg[0]; // copy byte 0
    }
    *plmsg = len-m_iHeaderLen; // still to read msg_length - header_length

    return m_iHeaderLen;    // length read 
  }
  else
  {
    // TIMEOUT ! Didn't receive any message for n seconds. 
    *plmsg = 0;
    return -1;
  } // signal timeout
}

//##ModelId=45AC9EE60092
int CTelcom_InTcpipTransport::doDisconnect()
{
  CTelcom_InTask::getInstance()->setWorking(false);

  int sta = 0;

  sta = TcpipTransport::doDisconnect();
  if (sta == -1)
  {
    cCBS_StdLog_Task::getInstance()->log("Dis-Connection timeout!", 1);
  }
  else
  {
    long HideDisconnectMsg = 0; // if set to 1, message will not be shown
    cCBS_StdInitBase::getInstance()->replaceWithEntry("SMS_Definition","HideDisconnectMsg",HideDisconnectMsg);
    if (HideDisconnectMsg != 1)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_LostConnection(sMessage,cCBS_StdInitBase::getInstance()->m_ServerName.c_str());

      cCBS_StdLog_Task::getInstance()->log("CTelcom_InTcpipTransport::doDisconnect: Dis-Connected!",2);
    }
  }
  return sta;
}

