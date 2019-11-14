// Copyright (C) 2006 SMS Demag AG
#include "iSMC_DataDefinitions_s.hh"

#include "CDH_IN_Telcom_Impl.h"
#include "CTelegram_Adapter.h"
#include "CDH_IN_Task.h"


//##ModelId=4582D8E20205
long CDH_IN_Telcom_Impl::onComplete(const std::string & Key, const std::string & Action)
{
  // we expect the caller of onComplete to be a TELCOM process
  // return value of "0" indicated success
  // otherwise value of ErrorCode will be forwarded
  long RetValue = 0;

  if ( !CDH_IN_Task::getInstance()->getpTelegramAdapter()->doOnComplete(Key, Action) )
  {
    RetValue = getLong(Key,DATA::ErrorCode);
  }

  return RetValue;
}

//##ModelId=4582D964034C
CDH_IN_Telcom_Impl::CDH_IN_Telcom_Impl()
{
}

//##ModelId=4582D965016D
CDH_IN_Telcom_Impl::~CDH_IN_Telcom_Impl()
{
}
