// Copyright (C) 2005 SMS Demag AG Germany

#include "cCBS_StdLog_Task.h"
#include "CDH_Wrapper.h"
#include "CDH_Task.h"

//##ModelId=4253DC470040
CDH_Wrapper::~CDH_Wrapper()
{
}

//##ModelId=4253DC470237
CDH_Wrapper::CDH_Wrapper() 
: m_pGC_Plant_Container(0), m_pHeatDataConverter(0)
{
}

//##ModelId=4253DC4C02A0
void CDH_Wrapper::log(const std::string& Message, long Level /* =1 */)
{
  cCBS_StdLog_Task::getInstance()->log(Message, Level);
}
