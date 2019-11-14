// Copyright (C) 2007 SMS Demag AG, Germany 

#include "CSMC_EventLogFrameController.h"
#include "CGC_HEAT_STATUS.h"
#include "cCBS_StdLog_Task.h"

#include "CHeatStatusContainer.h"


//##ModelId=4679433101D9
CHeatStatusContainer::CHeatStatusContainer(cCBS_StdConnection* Connection)
{
  CGC_HEAT_STATUS GC_HEAT_STATUS (Connection);
  if (GC_HEAT_STATUS.select(CSMC_DBData::unspecLong))
  {
    std::string Plant;
    HeatStat HS;
    for (long i=1;i<=GC_HEAT_STATUS.getLastRow(); i++)
    {
      HS.HeatStatus   = GC_HEAT_STATUS.getHEATSTATUS(i);
      HS.HeatStatusNo = GC_HEAT_STATUS.getHEATSTATUSNO(i);
      Plant           = GC_HEAT_STATUS.getPLANT(i);
      m_StatusTable.insert(std::pair <std::string,HeatStat>(Plant, HS));
    }
  }
  else
  {
    std::string SearchKey = " * ";
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.c_str(),"GC_HEAT_STATUS");
  }
}

//##ModelId=467942AE0234
CHeatStatusContainer::~CHeatStatusContainer()
{
}

//##ModelId=4679433101CE
long CHeatStatusContainer::getHeatStatus(const std::string& PLANT, std::string HEATSTATUS)
{
  long ret = -1;
  std::multimap<const std::string,HeatStat>::const_iterator it;

  for (it = m_StatusTable.lower_bound(PLANT);it != m_StatusTable.upper_bound(PLANT);++it)
  {
    if (HEATSTATUS == (it->second).HeatStatus)
    {
      ret = (it->second).HeatStatusNo;
      break;
    }
  }

  if ( ret == -1 )
  {
    std::stringstream Message;
    Message << "CHeatStatusContainer::getHeatStatus - System cannot detect Heat Status for plant " << PLANT << " and HeatStatusNo " << HEATSTATUS;

    cCBS_StdLog_Task::getInstance()->log(Message.str(), 3);

  }

  return ret;
}
