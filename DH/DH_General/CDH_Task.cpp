// Copyright (C) 2005 SMS Demag AG Germany

#include "cCBS_StdLog_Task.h"
#include "cCBS_StdDB_Task.h"
#include "CSMC_DataProvider_Impl.h"
#include "CDH_Task.h"

CDH_Task::CDH_Task()
: m_pDMProxyManager(0)
{

}

CDH_Task::~CDH_Task()
{
}

void CDH_Task::log(const std::string& Message, long Level)
{
  cCBS_StdLog_Task::getInstance()->log(Message, Level);
}

bool CDH_Task::initialize()
{
  bool ret = CSMC_FrameTask::initialize();

  setCORBAConnections();
  return ret;
}
