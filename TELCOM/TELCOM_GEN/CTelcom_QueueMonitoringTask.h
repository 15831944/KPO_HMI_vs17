// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELCOM_QUEUEMONITORINGTASK_45AF933E0336_INCLUDED
#define _INC_CTELCOM_QUEUEMONITORINGTASK_45AF933E0336_INCLUDED

#include "CTelcom_Task.h"

class CTelcom_QueueMonitoringTask : public CTelcom_Task
{
public:
	void getOwnStateDetails(CORBA::String_out details);

  //counter for lost messages since start up of application
	long m_LostMessages;

  //last message in the queue
	std::string m_LastMessage;

  //Current queue size
	int m_QueueSize;

	CTelcom_QueueMonitoringTask();

	virtual ~CTelcom_QueueMonitoringTask();

	static CTelcom_QueueMonitoringTask* getInstance();

  //date/time when last message was lost
  std::string m_LostMessageTimestamp;

  //reset of counter for lost messages since last connection establishing
  void resetLostMessagesConnect();

  //set reciver of telegrams
  void setReciver(const std::string& _reciver);

  //return the reciver of telegrams
  std::string getReciver();

  virtual void setCORBAConnections();

private:
	static CTelcom_QueueMonitoringTask* m_Instance;

  //counter for lost messages since last connection establishing
  long m_LostMessagesConnect;

  //reciver for event log message
  std::string m_Reciver;
};

#endif /* _INC_CTELCOM_QUEUEMONITORINGTASK_45AF933E0336_INCLUDED */
